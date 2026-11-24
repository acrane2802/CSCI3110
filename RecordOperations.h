// AI Disclaimer: A.I. DISCLAIMER: ALL WORK FOR THIS ASSIGNMENT WAS COMPLETED BY
// MYSELF AND ENTIRELY WITHOUT THE USE OF ARTIFICIAL INTELLIGENCE TOOLS
// SUCH AS CHATGPT, MS COPILOT, OTHER LLMS, ETC

// Authors: Andrew Crane, Alexis Mann, Vixen Martin, Cesar Arteaga
// Project Description: This reads a list of the most popular songs from a dataset and then provides user options to search through it as well as add or delete records

#ifndef CSCI3110_RECORD_OPERATIONS_H
#define CSCI3110_RECORD_OPERATIONS_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Record.h"

using RecordMap = std::unordered_multimap<std::string, Record*>;

struct DeleteResult
{
    std::size_t fromHashMaps {0};
    std::size_t fromVector {0};
};


//Adds new record to all 3 hash tables and to the vector.
void insertRecord(RecordMap& trackMap,
                  RecordMap& albumMap,
                  RecordMap& artistMap,
                  std::vector<Record*>& datasetVector,
                  const std::string& artists,
                  const std::string& album,
                  const std::string& track,
                  int popularity);

//Deletes every record whose track, album, and artist all match exactly from the hash and the vectors.
DeleteResult deleteRecord(RecordMap& trackMap,
                          RecordMap& albumMap,
                          RecordMap& artistMap,
                          std::vector<Record*>& datasetVector,
                          const std::string& track,
                          const std::string& album,
                          const std::string& artists);

//Deletes every record whose track name matches exactly from the hash and the vectors.
DeleteResult deleteRecordsByTrackName(RecordMap& trackMap,
                                      RecordMap& albumMap,
                                      RecordMap& artistMap,
                                      std::vector<Record*>& datasetVector,
                                      const std::string& track);

//terminal menu to choose insertion/deletion operations
void runEditMenu(RecordMap& trackMap,
                 RecordMap& albumMap,
                 RecordMap& artistMap,
                 std::vector<Record*>& datasetVector);

#endif //CSCI3110_RECORD_OPERATIONS_H