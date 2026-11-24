#include "Record.h"

void Record::readRecord(std::ifstream &file)
{
    std::string line;

    std::string substring;

    std::getline(file, line);

    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }
    // parse csv line
    std::string currentCSVColumn;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i)
    {
        char curChar = line[i];

        if (curChar == '"')
        {
            currentCSVColumn += '"';
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
            {
                currentCSVColumn += '"';
                ++i;
            }
            else
            {
                inQuotes = !inQuotes;
            }
        }
        else if (curChar == ',' && !inQuotes)
        {
            substrings.push_back(currentCSVColumn);
            currentCSVColumn.clear();
        }
        else
        {
            currentCSVColumn += curChar;
        }
    }

    // store all substrings into variables
    substrings.push_back(currentCSVColumn);

    artists = substrings[2];
    albumName = substrings[3];
    trackName = substrings[4];

    popularity = stoi(substrings[5]);

    substrings.clear();
}

void Record::printRecord()
{
    // print record
    std::cout << "Artist(s): " << artists << "\n" << "Album Name: " << albumName << "\n" << "Track Name: " << trackName << "\n";
}

void Record::setArtists(const std::string& title)
{
    this->artists = title;
}

void Record::setAlbum(const std::string& title)
{
    this->albumName = title;
}

void Record::setTrackName(const std::string& title)
{
    this->trackName = title;
}

void Record::setPopularityScore(const int& score)
{
    this->popularity = score;
}
