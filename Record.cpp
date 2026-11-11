//
// Created by andre on 10/26/2026.
//

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

    substrings.push_back(currentCSVColumn);

    number = stoi(substrings[0]);

    trackID = substrings[1];
    artists = substrings[2];
    albumName = substrings[3];
    trackName = substrings[4];

    popularity = stoi(substrings[5]);
    durationInMS = stoi(substrings[6]);

    if (substrings[7] == "true")
    {
        isExplicit = true;
    } else
    {
        isExplicit = false;
    }

    danceability = stof(substrings[8]);
    energy = stof(substrings[9]);
    key = stoi(substrings[10]);

    loudness = stof(substrings[11]);
    mode = stoi(substrings[12]);
    speechiness = stof(substrings[13]);
    acousticness = stof(substrings[14]);
    instrumentalness = stof(substrings[15]);
    liveliness = stof(substrings[16]);

    valence = stof(substrings[17]);

    tempo = stof(substrings[18]);
    timeSignature = stof(substrings[19]);

    genre = substrings[20];

    substrings.clear();
}

void Record::printRecord()
{
    std::cout << "Artist(s): " << artists << "\n" << "Album Name: " << albumName << "\n" << "Track Name: " << trackName << "\n";
}
