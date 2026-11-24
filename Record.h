// AI Disclaimer: A.I. DISCLAIMER: ALL WORK FOR THIS ASSIGNMENT WAS COMPLETED BY
// MYSELF AND ENTIRELY WITHOUT THE USE OF ARTIFICIAL INTELLIGENCE TOOLS
// SUCH AS CHATGPT, MS COPILOT, OTHER LLMS, ETC

// Authors: Andrew Crane, Alexis Mann, Vixen Martin, Cesar Arteaga
// Project Description: This reads a list of the most popular songs from a dataset and then provides user options to search through it as well as add or delete records

#ifndef CSCI3110_RECORD_H
#define CSCI3110_RECORD_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

struct Record
{
public:
    void readRecord(std::ifstream& file);

    void printRecord();

    std::string getArtists() { return artists; }
    std::string getAlbum() { return albumName; }
    std::string getTrackName() { return trackName; }
    int getPopularityScore() { return popularity; }
    Record* getSelfPointer() { return this; }

    void setArtists(const std::string& title);
    void setAlbum(const std::string& title);
    void setTrackName(const std::string& title);
    void setPopularityScore(const int& score);

private:
    std::string artists;
    std::string albumName;
    std::string trackName;

    int popularity {0};

    std::vector<std::string> substrings;
};
#endif //CSCI3110_RECORD_H
