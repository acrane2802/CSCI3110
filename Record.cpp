//
// Created by andre on 10/26/2026.
//

#include "Record.h"

void Record::readRecord(std::ifstream &file)
{
    std::string line;

    std::string substring;
    std::string appendSubstring;

    int endOfRecord = 0;

    std::getline(file, line);
    std::istringstream stringStream(line);

    while (std::getline(stringStream, substring, ','))
    {
        if (substring.front() == '"' && substring.back() != '"')
        {
            endOfRecord = 0;

            while (!endOfRecord)
            {
                substring.append({','});

                std::getline(stringStream, appendSubstring, ',');

                substring.append(appendSubstring);

                if (substring.back() == '"')
                {
                    endOfRecord = 1;
                }
            }
        }
        substrings.push_back(substring);
    }

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

void Record::dummyReadRecord(std::ifstream &file)
{
    std::string line;
    std::getline(file, line);

    std::istringstream stringStream(line);

    std::string substring;
    char previousChar = ' ';
    int quoteCount = 0;
    bool finishedWithSubstring = false;

    for (int curChar = 0; finishedWithSubstring == false && (curChar == stringStream.get()) != EOF;)
    {
        if (curChar == '"')
        {
            ++quoteCount;
            break;
        }
        if (curChar == ',')
        {
            if (quoteCount == 0 || (previousChar == '"'  && (quoteCount % 2) == 0))
            {
                finishedWithSubstring = true;
            }
            break;
        }
        previousChar = static_cast<char>(curChar);
        substring.append({previousChar});
    }

    substrings.push_back(substring);
}

void Record::printRecord()
{
    std::cout << number << "\n"
              << trackID << "\n" << artists << "\n" << albumName << "\n" << trackName << "\n"
              << popularity << "\n" << durationInMS << "\n"
              << isExplicit << "\n"
              << danceability << "\n" << energy << "\n" << key << "\n"
              << loudness << "\n" << mode << "\n" << speechiness << "\n" << acousticness << "\n" << instrumentalness << "\n" << liveliness << "\n"
              << valence << "\n"
              << tempo << "\n" << timeSignature << "\n"
              << genre << "\n";
}
