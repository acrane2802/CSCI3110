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


void insertRecord(RecordMap& trackMap,
                  RecordMap& albumMap,
                  RecordMap& artistMap,
                  std::vector<Record*>& datasetVector,
                  const std::string& artists,
                  const std::string& album,
                  const std::string& track,
                  int popularity);


DeleteResult deleteRecord(RecordMap& trackMap,
                          RecordMap& albumMap,
                          RecordMap& artistMap,
                          std::vector<Record*>& datasetVector,
                          const std::string& track,
                          const std::string& album,
                          const std::string& artists);


DeleteResult deleteRecordsByTrackName(RecordMap& trackMap,
                                      RecordMap& albumMap,
                                      RecordMap& artistMap,
                                      std::vector<Record*>& datasetVector,
                                      const std::string& track);


void runEditMenu(RecordMap& trackMap,
                 RecordMap& albumMap,
                 RecordMap& artistMap,
                 std::vector<Record*>& datasetVector);

#endif //CSCI3110_RECORD_OPERATIONS_H