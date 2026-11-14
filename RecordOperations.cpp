#include "RecordOperations.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <system_error>

namespace
{
    Record* makeRecord(const std::string& artists, const std::string& album,
                       const std::string& track, int popularity)
    {
        auto* rec = new Record;
        rec->setArtists(artists);
        rec->setAlbum(album);
        rec->setTrackName(track);
        rec->setPopularityScore(popularity);
        return rec;
    }


    void eraseFromMap(RecordMap& map, const std::string& key, Record* rec)
    {
        auto range = map.equal_range(key);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == rec)
            {
                map.erase(it);
                return;
            }
        }
    }


    DeleteResult deleteMatching(RecordMap& trackMap,
                                RecordMap& albumMap,
                                RecordMap& artistMap,
                                std::vector<Record*>& datasetVector,
                                const std::string& track,
                                const std::function<bool(Record*)>& matches)
    {
        DeleteResult result;


        std::vector<Record*> toDelete;
        auto range = trackMap.equal_range(track);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (matches(it->second))
            {
                toDelete.push_back(it->second);
            }
        }

        for (Record* rec : toDelete)
        {
            const std::string t = rec->getTrackName();
            const std::string al = rec->getAlbum();
            const std::string ar = rec->getArtists();

            eraseFromMap(trackMap, t, rec);
            eraseFromMap(albumMap, al, rec);
            eraseFromMap(artistMap, ar, rec);

            delete rec;
            ++result.fromHashMaps;
        }


        std::size_t write = 0;
        for (std::size_t read = 0; read < datasetVector.size(); ++read)
        {
            Record* rec = datasetVector[read];
            if (rec->getTrackName() == track && matches(rec))
            {
                delete rec;
                ++result.fromVector;
            }
            else
            {
                datasetVector[write++] = rec;
            }
        }
        datasetVector.resize(write);

        return result;
    }
}

void insertRecord(RecordMap& trackMap,
                  RecordMap& albumMap,
                  RecordMap& artistMap,
                  std::vector<Record*>& datasetVector,
                  const std::string& artists,
                  const std::string& album,
                  const std::string& track,
                  int popularity)
{
    Record* hashRec = makeRecord(artists, album, track, popularity);
    trackMap.insert(std::pair(hashRec->getTrackName(), hashRec));
    albumMap.insert(std::pair(hashRec->getAlbum(), hashRec));
    artistMap.insert(std::pair(hashRec->getArtists(), hashRec));

    datasetVector.push_back(makeRecord(artists, album, track, popularity));
}

DeleteResult deleteRecord(RecordMap& trackMap,
                          RecordMap& albumMap,
                          RecordMap& artistMap,
                          std::vector<Record*>& datasetVector,
                          const std::string& track,
                          const std::string& album,
                          const std::string& artists)
{
    return deleteMatching(trackMap, albumMap, artistMap, datasetVector, track,
                          [&](Record* r)
                          {
                              return r->getAlbum() == album && r->getArtists() == artists;
                          });
}

DeleteResult deleteRecordsByTrackName(RecordMap& trackMap,
                                      RecordMap& albumMap,
                                      RecordMap& artistMap,
                                      std::vector<Record*>& datasetVector,
                                      const std::string& track)
{
    return deleteMatching(trackMap, albumMap, artistMap, datasetVector, track,
                          [](Record*) { return true; });
}

namespace
{
    constexpr const char* kDatasetPath = "dataset.csv";


    struct PendingOp
    {
        enum class Kind { Insert, DeleteExact, DeleteByTrack } kind;
        std::string artists;
        std::string album;
        std::string track;
        int popularity {0};
    };

    struct Row
    {
        std::string raw;
        std::string artists;
        std::string album;
        std::string track;
        bool parsed {false};
    };


    std::vector<std::string> splitCsvLine(const std::string& rawLine)
    {
        std::string line = rawLine;
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        std::vector<std::string> cols;
        std::string cur;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i)
        {
            char c = line[i];
            if (c == '"')
            {
                cur += '"';
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
                {
                    cur += '"';
                    ++i;
                }
                else
                {
                    inQuotes = !inQuotes;
                }
            }
            else if (c == ',' && !inQuotes)
            {
                cols.push_back(cur);
                cur.clear();
            }
            else
            {
                cur += c;
            }
        }
        cols.push_back(cur);
        return cols;
    }


    std::string csvField(const std::string& s)
    {
        bool alreadyQuoted = s.size() >= 2 && s.front() == '"' && s.back() == '"';
        if (alreadyQuoted || s.find_first_of(",\"\n") == std::string::npos)
        {
            return s;
        }

        std::string out = "\"";
        for (char c : s)
        {
            if (c == '"') out += "\"\"";
            else out += c;
        }
        out += '"';
        return out;
    }


    bool saveChanges(const std::vector<PendingOp>& ops)
    {
        namespace fs = std::filesystem;

        std::ifstream in(kDatasetPath, std::ios::binary);
        if (!in)
        {
            std::cout << "Could not open " << kDatasetPath << " for saving.\n";
            return false;
        }

        std::string header;
        std::getline(in, header);

        std::vector<Row> rows;
        long long maxIndex = -1;
        std::string raw;
        while (std::getline(in, raw))
        {
            if (raw.empty())
            {
                continue;
            }

            Row row;
            row.raw = raw;

            std::vector<std::string> cols = splitCsvLine(raw);
            if (cols.size() >= 5)
            {
                row.artists = cols[2];
                row.album = cols[3];
                row.track = cols[4];
                row.parsed = true;
            }

            try
            {
                maxIndex = std::max(maxIndex, std::stoll(cols[0]));
            }
            catch (...)
            {
            }

            rows.push_back(std::move(row));
        }
        in.close();

        for (const PendingOp& op : ops)
        {
            if (op.kind == PendingOp::Kind::Insert)
            {
                Row row;
                row.artists = op.artists;
                row.album = op.album;
                row.track = op.track;
                row.parsed = true;

                row.raw = std::to_string(++maxIndex) + ",," + csvField(op.artists) + "," +
                          csvField(op.album) + "," + csvField(op.track) + "," +
                          std::to_string(op.popularity) + ",0,False,0,0,0,0,0,0,0,0,0,0,0,0,";
                rows.push_back(std::move(row));
            }
            else
            {
                rows.erase(std::remove_if(rows.begin(), rows.end(), [&](const Row& r)
                {
                    if (!r.parsed || r.track != op.track) return false;
                    if (op.kind == PendingOp::Kind::DeleteByTrack) return true;
                    return r.album == op.album && r.artists == op.artists;
                }), rows.end());
            }
        }

        const std::string backupPath = std::string(kDatasetPath) + ".bak";
        const std::string tempPath = std::string(kDatasetPath) + ".tmp";
        std::error_code ec;

        fs::copy_file(kDatasetPath, backupPath, fs::copy_options::overwrite_existing, ec);
        if (ec)
        {
            std::cout << "Could not create backup (" << ec.message() << "). Nothing was saved.\n";
            return false;
        }

        {
            std::ofstream out(tempPath, std::ios::binary);
            out << header << '\n';
            for (const Row& row : rows)
            {
                out << row.raw << '\n';
            }
            if (!out)
            {
                std::cout << "Failed writing " << tempPath << ". dataset.csv was not changed.\n";
                return false;
            }
        }

        fs::rename(tempPath, kDatasetPath, ec);
        if (ec)
        {
            std::cout << "Could not replace " << kDatasetPath << " (" << ec.message()
                      << "). Your original is untouched; the new data is in " << tempPath << ".\n";
            return false;
        }

        std::cout << "Saved to " << kDatasetPath << " (" << rows.size()
                  << " records). Backup of the previous file: " << backupPath << "\n";
        return true;
    }
}

void runEditMenu(RecordMap& trackMap,
                 RecordMap& albumMap,
                 RecordMap& artistMap,
                 std::vector<Record*>& datasetVector)
{
    std::vector<PendingOp> pending;

    auto ask = [](const std::string& prompt)
    {
        std::string line;
        std::cout << prompt;
        std::getline(std::cin, line);
        return line;
    };

    while (true)
    {
        std::cout << "\nEdit Records\n"
                  << "(1) Insert record\n"
                  << "(2) Delete record (track + album + artist)\n"
                  << "(3) Delete all records with a track name\n"
                  << "(4) Save changes to " << kDatasetPath << " (" << pending.size() << " unsaved)\n"
                  << "(5) Continue to search\n";
        std::string choice = ask("Choice: ");

        if (choice == "5")
        {
            if (!pending.empty())
            {
                std::string answer = ask("You have " + std::to_string(pending.size()) +
                                         " unsaved change(s). Save to " + kDatasetPath + " first? (y/n): ");
                if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y'))
                {
                    if (!saveChanges(pending))
                    {
                        continue;
                    }
                }
            }
            return;
        }
        else if (choice == "4")
        {
            if (pending.empty())
            {
                std::cout << "No changes to save.\n";
            }
            else if (saveChanges(pending))
            {
                pending.clear();
            }
        }
        else if (choice == "1")
        {
            std::string artists = ask("Artist(s): ");
            std::string album = ask("Album name: ");
            std::string track = ask("Track name: ");

            int popularity = 0;
            try
            {
                popularity = std::stoi(ask("Popularity (0-100): "));
            }
            catch (...)
            {
                std::cout << "Invalid popularity. Record not inserted.\n";
                continue;
            }

            insertRecord(trackMap, albumMap, artistMap, datasetVector,
                         artists, album, track, popularity);
            pending.push_back({PendingOp::Kind::Insert, artists, album, track, popularity});
            std::cout << "Inserted \"" << track << "\".\n";
        }
        else if (choice == "2")
        {
            std::string track = ask("Track name: ");
            std::string album = ask("Album name: ");
            std::string artists = ask("Artist(s): ");

            DeleteResult r = deleteRecord(trackMap, albumMap, artistMap, datasetVector,
                                          track, album, artists);
            std::cout << "Removed " << r.fromHashMaps << " from hash maps, "
                      << r.fromVector << " from vector.\n";
            if (r.fromHashMaps > 0 || r.fromVector > 0)
            {
                pending.push_back({PendingOp::Kind::DeleteExact, artists, album, track, 0});
            }
        }
        else if (choice == "3")
        {
            std::string track = ask("Track name: ");

            DeleteResult r = deleteRecordsByTrackName(trackMap, albumMap, artistMap,
                                                      datasetVector, track);
            std::cout << "Removed " << r.fromHashMaps << " from hash maps, "
                      << r.fromVector << " from vector.\n";
            if (r.fromHashMaps > 0 || r.fromVector > 0)
            {
                pending.push_back({PendingOp::Kind::DeleteByTrack, "", "", track, 0});
            }
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }
}