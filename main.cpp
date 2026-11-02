#include <iostream>
#include <fstream>

#include "Record.h"

int main()
{
    std::ifstream testFile;
    testFile.open("testrecords.csv");

    std::cout << "Record 1:\n";
    Record testRecord;
    testRecord.readRecord(testFile);
    testRecord.printRecord();

    std::cout << "\nRecord 2:\n";
    testRecord.readRecord(testFile);
    testRecord.printRecord();

    std::cout << "\nRecord 3:\n";

    testRecord.readRecord(testFile);
    testRecord.printRecord();

    testFile.close();

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}