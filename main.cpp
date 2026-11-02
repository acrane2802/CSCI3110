#include <iostream>
#include <fstream>

#include "Record.h"

int main()
{
    std::ifstream testFile;
    testFile.open("testrecords.csv");

    Record testRecord;
    testRecord.readRecord(testFile);

    testRecord.printRecord();

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}