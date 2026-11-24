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