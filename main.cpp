#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <memory>

#include "Record.h"

constexpr int recordCountToRead = 114000;

int main()
{
    std::unordered_multimap<std::string, Record*> trackNameDatasetHashMap;
    std::unordered_multimap<std::string, Record*> albumNameDatasetHashMap;
    std::unordered_multimap<std::string, Record*> artistNameDatasetHashMap;

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

    std::cout << "Time Taken to Read Dataset (milliseconds): " << millisecondsToRun << std::endl;

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
                startTime = std::chrono::high_resolution_clock::now();

                result = trackNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != trackNameDatasetHashMap.end())
                {
                    for (auto it = result.first; it != result.second; ++it)
                    {
                        std::cout << "Tracks found for query \"" << it->first << "\": \n";
                        it->second->printRecord();
                    }
                }
                else
                {
                    std::cout << "Track not found.\n";
                }

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 2:
                startTime = std::chrono::high_resolution_clock::now();

                result = albumNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != albumNameDatasetHashMap.end())
                {
                    for (auto it = result.first; it != result.second; ++it)
                    {
                        std::cout << "Tracks under Album found for query \"" << it->first << "\": \n";
                        it->second->printRecord();
                    }
                }
                else
                {
                    std::cout << "Album not found.\n";
                }

                std::cout << "\nTime Taken to Find Album (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 3:
                startTime = std::chrono::high_resolution_clock::now();

                result = artistNameDatasetHashMap.equal_range(userQuery);

                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                if (result.first != artistNameDatasetHashMap.end())
                {
                    for (auto it = result.first; it != result.second; ++it)
                    {
                        std::cout << "Tracks under Artist found for query \"" << it->first << "\": \n";
                        it->second->printRecord();
                    }
                }
                else
                {
                    std::cout << "Artist not found.\n";
                }

                std::cout << "\nTime Taken to Find Artist (milliseconds): " << millisecondsToRun << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Exiting...\n" << std::endl;
                exit(-1);
                break;
        }
    }

    return 0;
}