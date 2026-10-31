//
// Created by andre on 10/26/2026.
//

#include "Record.h"

void Record::readRecord(std::ifstream &file)
{
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream stringStream(line);

        std::vector<std::string> substrings;
        std::string substring;

        while (std::getline(stringStream, substring, ','))
        {
            substrings.push_back(substring);
        }

        // store record data in variables from substring vector
    }
}
