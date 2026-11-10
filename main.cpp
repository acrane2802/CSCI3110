#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <memory>

#include "Record.h"

constexpr int recordCountToRead = 114000;

int main()
{
    std::unordered_map<std::string, Record*> trackNameDatasetHashMap;
    std::unordered_map<std::string, Record*> albumNameDatasetHashMap;
    std::unordered_map<std::string, Record*> artistNameDatasetHashMap;

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
        //std::cout << rec->getSelfPointer() << std::endl;
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
            std::cout << "Exiting...\n" << std::endl;
            break;
        }

        std::cout << "Enter query: ";

        std::getline(std::cin, userQuery);
        std::cout << "\n";

        auto result = trackNameDatasetHashMap.find("");
        switch (userChoice)
        {
            case 1:
                startTime = std::chrono::high_resolution_clock::now();

                result = trackNameDatasetHashMap.find(userQuery);
                if (result != trackNameDatasetHashMap.end())
                {
                    std::cout << "Track data found for query \"" << result->first << "\": \n";
                    result->second->printRecord();
                }
                else
                {
                    std::cout << "Track not found.\n";
                }
                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 2:
                startTime = std::chrono::high_resolution_clock::now();

                result = albumNameDatasetHashMap.find(userQuery);
                if (result != albumNameDatasetHashMap.end())
                {
                    std::cout << "Track data found for query \"" << result->first << "\": \n";
                    result->second->printRecord();
                }
                else
                {
                    std::cout << "Track not found.\n";
                }
                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;
                break;
            case 3:
                startTime = std::chrono::high_resolution_clock::now();

                result = artistNameDatasetHashMap.find(userQuery);
                if (result != artistNameDatasetHashMap.end())
                {
                    std::cout << "Track data found for query \"" << result->first << "\": \n";
                    result->second->printRecord();
                }
                else
                {
                    std::cout << "Track not found.\n";
                }
                finishedTime = std::chrono::high_resolution_clock::now();
                processingTime = finishedTime - startTime;
                millisecondsToRun = processingTime.count();

                std::cout << "\nTime Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Exiting...\n" << std::endl;
                break;
        }

    }

    return 0;
}