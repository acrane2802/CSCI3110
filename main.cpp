#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <memory>
#include <algorithm>

#include "Record.h"
#include "RecordOperations.h"

int recordCountToRead = 114000;

bool compare(Record* first, Record* second);
double vectorSearch(std::vector<Record*> &datasetVector, int userChoice, const std::string& userQuery);

std::vector<Record*> top10;

int searchResultCount = 0;
int totalResult = 0;

int main(int argc, char** argv)
{
    recordCountToRead = atoi(argv[1]);
    std::unordered_multimap<std::string, Record*> trackNameDatasetHashMap;
    std::unordered_multimap<std::string, Record*> albumNameDatasetHashMap;
    std::unordered_multimap<std::string, Record*> artistNameDatasetHashMap;

    std::vector<Record*> datasetVector;

    std::ifstream datasetFile;
    datasetFile.open("dataset.csv");

    std::string firstLine;
    std::getline(datasetFile, firstLine);

    int datasetIndex = 0;

    std::chrono::duration<double, std::milli> processingTime{};
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    while (datasetIndex < recordCountToRead)
    {
        auto* rec = new Record;
        rec->readRecord(datasetFile);
        trackNameDatasetHashMap.insert(std::pair(rec->getTrackName(), rec->getSelfPointer()));
        albumNameDatasetHashMap.insert(std::pair(rec->getAlbum(), rec->getSelfPointer()));
        artistNameDatasetHashMap.insert(std::pair(rec->getArtists(), rec->getSelfPointer()));
        ++datasetIndex;
    }

    datasetFile.close();

    std::chrono::time_point<std::chrono::high_resolution_clock> finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    double millisecondsToRun = processingTime.count();

    std::cout << "Time Taken to Read Dataset into Hashmap (milliseconds): " << millisecondsToRun << std::endl;

    datasetFile.open("dataset.csv");
    std::getline(datasetFile, firstLine);

    datasetIndex = 0;

    startTime = std::chrono::high_resolution_clock::now();

    while (datasetIndex < recordCountToRead)
    {
        auto* rec = new Record;
        rec->readRecord(datasetFile);
        datasetVector.push_back(rec);
        ++datasetIndex;
    }

    datasetFile.close();

    finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    millisecondsToRun = processingTime.count();

    std::cout << "Time Taken to Read Dataset into Vector (milliseconds): " << millisecondsToRun << std::endl;

    runEditMenu(trackNameDatasetHashMap, albumNameDatasetHashMap, artistNameDatasetHashMap, datasetVector);


    int userChoice = 0;
    std::string userQuery;
    std::cout << "\nMusic Search\n";

    while (true)
    {
        std::cout << "Select search value type:\n(1) Track Name\n(2) Album Name\n(3) Artist Name\n(4) Exit Program: ";
        std::cin >> userChoice;
        std::cin.ignore();

        if (userChoice == 4)
        {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::cout << "Enter query: ";

        std::getline(std::cin, userQuery);
        std::cout << "\n";



        auto result = trackNameDatasetHashMap.equal_range("");
        switch (userChoice)
        {
            case 1:
                std::cout << "Hashmap Search:\n";
                startTime = std::chrono::high_resolution_clock::now();

                result = trackNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != trackNameDatasetHashMap.end())
                {
                    std::cout << "Track(s) found for query \"" << userQuery << "\": \n";

                    for (auto it = result.first; it != result.second; ++it)
                    {
                        ++searchResultCount;
                        top10.push_back(it->second);
                    }
                    std::sort(top10.begin(), top10.end(), compare);

                    totalResult = 0;
                    if (searchResultCount >= 10)
                    {
                        totalResult = 10;
                    } else
                    {
                        totalResult = searchResultCount;
                    }
                    for (int i = 0; i < totalResult; ++i)
                    {
                        std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                        top10[i]->printRecord();
                        std::cout << "\n";
                    }
                    searchResultCount = 0;
                    totalResult = 0;
                    top10.clear();
                }
                else
                {
                    std::cout << "Track not found.\n";
                }

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;

                //Vector Search
                millisecondsToRun = vectorSearch(datasetVector, userChoice, userQuery);

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 2:
                std::cout << "Hashmap Search:\n";
                startTime = std::chrono::high_resolution_clock::now();

                result = albumNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != albumNameDatasetHashMap.end())
                {
                    std::cout << "Track(s) found for query \"" << userQuery << "\": \n";

                    for (auto it = result.first; it != result.second; ++it)
                    {
                        ++searchResultCount;
                        top10.push_back(it->second);
                    }
                    std::sort(top10.begin(), top10.end(), compare);

                    totalResult = 0;
                    if (searchResultCount >= 10)
                    {
                        totalResult = 10;
                    } else
                    {
                        totalResult = searchResultCount;
                    }
                    for (int i = 0; i < totalResult; ++i)
                    {
                        std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                        top10[i]->printRecord();
                        std::cout << "\n";
                    }
                    searchResultCount = 0;
                    totalResult = 0;
                    top10.clear();
                }
                else
                {
                    std::cout << "Album not found.\n";
                }

                std::cout << "\nTime Taken to Find Album (milliseconds): " << millisecondsToRun << std::endl;

                //Vector Search
                millisecondsToRun = vectorSearch(datasetVector, userChoice, userQuery);

                std::cout << "\nTime Taken to Find Album (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 3:
                std::cout << "Hashmap Search:\n";
                startTime = std::chrono::high_resolution_clock::now();

                result = artistNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != artistNameDatasetHashMap.end())
                {
                    std::cout << "Track(s) found for query \"" << userQuery << "\": \n";

                    for (auto it = result.first; it != result.second; ++it)
                    {
                        ++searchResultCount;
                        top10.push_back(it->second);
                    }
                    std::sort(top10.begin(), top10.end(), compare);

                    totalResult = 0;
                    if (searchResultCount >= 10)
                    {
                        totalResult = 10;
                    } else
                    {
                        totalResult = searchResultCount;
                    }
                    for (int i = 0; i < totalResult; ++i)
                    {
                        std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                        top10[i]->printRecord();
                        std::cout << "\n";
                    }
                    searchResultCount = 0;
                    totalResult = 0;
                    top10.clear();
                }
                else
                {
                    std::cout << "Artist not found.\n";
                }

                std::cout << "\nTime Taken to Find Artist (milliseconds): " << millisecondsToRun << std::endl;

                //Vector Search
                millisecondsToRun = vectorSearch(datasetVector, userChoice, userQuery);
                

                std::cout << "\nTime Taken to Find Artist (milliseconds): " << millisecondsToRun << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Exiting...\n" << std::endl;
                return 0;
                break;
        }
    }

    return 0;
}

bool compare(Record* first, Record* second)
{
    int popOne = first->getPopularityScore();
    int popTwo = second->getPopularityScore();
    return popOne > popTwo;
}

//searches the Vector for any records matching what the user puts in
//takes in the dataset vector, and the user's search input
//prints the found records to the console and returns the milliseconds taken to find all matching records

double vectorSearch(std::vector<Record*> &datasetVector, int userChoice, const std::string& userQuery)
{
    //time tracking variables
    double millisecondsToRun;
    std::chrono::duration<double, std::milli> processingTime{};
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();
    bool found = false;

    std::cout << "\n\n\nVector Search:\n";
    std::cout << "Track(s) found for query \"" << userQuery << "\": \n";

    startTime = std::chrono::high_resolution_clock::now();

    //iterate through the loop, looking for any records that match the user's search
    switch (userChoice)
    {
        case 1:
            for (auto & i : datasetVector)
            {
                if (i->getTrackName() == userQuery)  //if the track name matches
                {
                    ++searchResultCount;
                    top10.push_back(i);
                    found = true;
                }
            }

            std::sort(top10.begin(), top10.end(), compare);

            totalResult = 0;
            if (searchResultCount >= 10)
            {
                totalResult = 10;
            } else
            {
                totalResult = searchResultCount;
            }
            for (int i = 0; i < totalResult; ++i)
            {
                std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                top10[i]->printRecord();
                std::cout << "\n";
            }
            searchResultCount = 0;
            totalResult = 0;
            top10.clear();

            break;
        case 2:
            for (auto & i : datasetVector)
            {
                if (i->getAlbum() == userQuery)  //if the track name matches
                {
                    ++searchResultCount;
                    top10.push_back(i);
                    found = true;
                }
            }

            std::sort(top10.begin(), top10.end(), compare);

            totalResult = 0;
            if (searchResultCount >= 10)
            {
                totalResult = 10;
            } else
            {
                totalResult = searchResultCount;
            }
            for (int i = 0; i < totalResult; ++i)
            {
                std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                top10[i]->printRecord();
                std::cout << "\n";
            }
            searchResultCount = 0;
            totalResult = 0;
            top10.clear();
            break;
        case 3:
            for (auto & i : datasetVector)
            {
                if (i->getArtists() == userQuery)  //if the track name matches
                {
                    ++searchResultCount;
                    top10.push_back(i);
                    found = true;
                }
            }

            std::sort(top10.begin(), top10.end(), compare);

            totalResult = 0;
            if (searchResultCount >= 10)
            {
                totalResult = 10;
            } else
            {
                totalResult = searchResultCount;
            }
            for (int i = 0; i < totalResult; ++i)
            {
                std::cout << "Popularity Rank " << top10[i]->getPopularityScore() << ": \n";
                top10[i]->printRecord();
                std::cout << "\n";
            }
            searchResultCount = 0;
            totalResult = 0;
            top10.clear();
            break;
    }

    //calculate the time it took to run
    std::chrono::time_point<std::chrono::high_resolution_clock> finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    millisecondsToRun = processingTime.count();

    if(!found)
    {
        std::cout << "No records match that query.\n";
    }

    //return the time in milliseconds
    return millisecondsToRun;
}