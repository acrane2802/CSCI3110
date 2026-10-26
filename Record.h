//
// Created by andre on 10/26/2026.
//

#ifndef CSCI3110_RECORD_H
#define CSCI3110_RECORD_H

#include <string>

struct Record
{
public:

private:
// ,
// track_id,artists,album_name,track_name,
// popularity,duration_ms,explicit,
// danceability,energy,key,
// loudness,mode,speechiness,
// acousticness,instrumentalness,liveness,
// valence,
// tempo,time_signature,
// track_genre

// 0,
// 5SuOikwiRyPMVoIQDJUgSV,Gen Hoshino,Comedy,Comedy,
// 73,230666,False,
// 0.676,0.461,1,
// -6.746,0,0.143,
// 0.0322,1.01e-06,0.358,
// 0.715,
// 87.917,4,
// acoustic
    int number {0};

    std::string trackID;
    std::string artists;
    std::string albumName;
    std::string trackName;

    int popularity {0};
    int durationInMS {0};
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

    std::string genre;
};
#endif //CSCI3110_RECORD_H
