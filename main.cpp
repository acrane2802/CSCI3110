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

    std::chrono::time_point<std::chrono::high_resolution_clock> finishedTime = std::chrono::high_resolution_clock::now();

    processingTime = finishedTime - startTime;

    double millisecondsToRun = processingTime.count();

    std::cout << "Final Run Time (milliseconds): " << millisecondsToRun << std::endl;

    datasetFile.close();

    return 0;
}