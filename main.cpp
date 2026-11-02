#include <iostream>
#include <fstream>

#include "Record.h"

int main()
{
    int recordCountToRead = 114000;

    Record* datasetRecords[114000];

    std::ifstream testFile;
    testFile.open("dataset.csv");

    /*std::cout << "Record 1:\n";
    Record testRecord;
    testRecord.readRecord(testFile);
    testRecord.printRecord();

    std::cout << "\nRecord 2:\n";
    testRecord.readRecord(testFile);
    testRecord.printRecord();

    std::cout << "\nRecord 3:\n";

    testRecord.readRecord(testFile);
    testRecord.printRecord();*/

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

    delete[] &datasetRecords;

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}