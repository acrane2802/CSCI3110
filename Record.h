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
    /* int number {0};

    std::string trackID; */
    std::string artists;
    std::string albumName;
    std::string trackName;

    int popularity {0};
    /* int durationInMS {0};
    bool isExplicit {false};

    float danceability {0.0f};
    float energy {0.0f};
    int key {0};

    float loudness {0.0f};
    int mode {0};
    float speechiness {0.0f};
    float acousticness {0.0f};
    float instrumentalness {0.0f};
    float liveliness {0.0f};

    float valence {0.0f};

    float tempo {0.0f};
    float timeSignature {0.0f};

    std::string genre; */

    std::vector<std::string> substrings;
};
#endif //CSCI3110_RECORD_H
