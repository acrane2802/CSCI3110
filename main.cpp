#include <iostream>
#include <fstream>

#include "Record.h"

int main()
{
    int recordCountToRead = 114000;

    Record* datasetRecords[114000];

    std::ifstream testFile;
    testFile.open("dataset.csv");

    std::string firstLine;
    std::getline(testFile, firstLine);

    int datasetIndex = 0;

    while (datasetIndex < recordCountToRead)
    {
        datasetRecords[datasetIndex] = new Record;
        datasetRecords[datasetIndex]->readRecord(testFile);
        datasetRecords[datasetIndex]->printRecord();
        ++datasetIndex;
    }

    testFile.close();

    return 0;
}