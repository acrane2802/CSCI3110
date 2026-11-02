#include <iostream>
#include <fstream>

#include "Record.h"

int main()
{
    std::vector<Record*> datasetRecords;

    std::ifstream testFile;
    testFile.open("testrecords.csv");

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

    int recordCountToRead = 100;

    datasetRecords.reserve(sizeof(Record*) * recordCountToRead);
    int datasetIndex = 0;

    while (datasetIndex < recordCountToRead)
    {
        datasetRecords[datasetIndex]->readRecord(testFile);
        ++datasetIndex;
    }
    testFile.close();

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}