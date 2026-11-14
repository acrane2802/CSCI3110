#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <memory>

#include "Record.h"

constexpr int recordCountToRead = 114000;

double vectorSearch(std::vector<Record*> &datasetVector, int userChoice, std::string userQuery);

int main()
{
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
                        it->second->printRecord();
                    }
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
                        it->second->printRecord();
                    }
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
                        it->second->printRecord();
                    }
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

//searches the Vector for any records matching what the user puts in
//takes in the dataset vector, and the user's search input
//prints the found records to the console and returns the milliseconds taken to find all matching records

double vectorSearch(std::vector<Record*> &datasetVector, int userChoice, std::string userQuery){
    //time tracking variables
    double millisecondsToRun;
    std::chrono::duration<double, std::milli> processingTime{};
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();
    int found = 0;

    std::cout << "\n\n\nVector Search:\n";
    std::cout << "Track(s) found for query \"" << userQuery << "\": \n";

    startTime = std::chrono::high_resolution_clock::now();

    //iterate through the loop, looking for any records that match the user's search
    for (int i = 0; i < recordCountToRead; ++i)
        {
            if (datasetVector[i]->getTrackName() == userQuery && userChoice == 1 )  //if the track name matches
                {
                    datasetVector[i]->printRecord();
                    found = 1;
                }
            else if(datasetVector[i]->getAlbum() == userQuery && userChoice == 2)   //if the album matches
                {
                    datasetVector[i]->printRecord();
                    found = 1;
                }
            else if(datasetVector[i]->getArtists() == userQuery && userChoice == 3) //if the artist matches
                {
                    datasetVector[i]->printRecord();
                    found = 1;
                }
        }

    //calculate the time it took to run
    std::chrono::time_point<std::chrono::high_resolution_clock> finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    millisecondsToRun = processingTime.count();

    if(found == 0)
    {
        std::cout << "No records match that Query\n";
    }

    //return the time in milliseconds
    return millisecondsToRun;
}