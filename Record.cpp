//
// Created by andre on 10/26/2026.
//

#include "Record.h"

void Record::readDataset(std::ifstream &file)
{
    std::string t;
    std::istringstream stringStream;
    std::string line;
    while (std::getline(file, line))
    {
        std::getline(stringStream, , ',');
    }
}
