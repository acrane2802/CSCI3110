#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <memory>

#include "Record.h"

constexpr int recordCountToRead = 114000;

int main()
{
    std::unordered_map<std::string, Record*> datasetHashMap;

    std::ifstream datasetFile;
    datasetFile.open("dataset.csv");

    std::string firstLine;
    std::getline(datasetFile, firstLine);

    int datasetIndex = 0;

    std::chrono::duration<double, std::milli> processingTime{};
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    while (datasetIndex < recordCountToRead)
    {
        Record* rec = new Record;
        rec->readRecord(datasetFile);
        datasetHashMap.insert(std::pair(rec->getTrackName(), rec));
        ++datasetIndex;
    }

    datasetFile.close();

    std::chrono::time_point<std::chrono::high_resolution_clock> finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    double millisecondsToRun = processingTime.count();

    std::cout << "Time Taken to Read Dataset (milliseconds): " << millisecondsToRun << std::endl;

    std::string searchTrack;

    std::cout << "\nMusic Search\n";
    std::cout << "Enter Track name: ";

    std::getline(std::cin, searchTrack);

    startTime = std::chrono::high_resolution_clock::now();

    auto result = datasetHashMap.find(searchTrack);
    if (result != datasetHashMap.end())
    {
        std::cout << "Track data found: \n";
        datasetHashMap.at(searchTrack)->printRecord();
    }
    else
    {
        std::cout << "Track not found.\n";
    }

    finishedTime = std::chrono::high_resolution_clock::now();
    processingTime = finishedTime - startTime;
    millisecondsToRun = processingTime.count();

    std::cout << "Time Taken to Find Track (milliseconds): " << millisecondsToRun << std::endl;

    return 0;
}