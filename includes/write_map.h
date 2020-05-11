//
// Created by Admin on 22.04.2020.
//

#ifndef COUNTWORDS_WRITE_MAP_H
#define COUNTWORDS_WRITE_MAP_H

#include <string>
#include <map>
#include <functional>
#include <set>

void writeKeySortedMap(const std::string& fileName, std::map<std::string, unsigned int>& map);
void writeValueSortedMap(const std::string& fileName, std::map<std::string, unsigned int>& mapCount);

void mapsJoin(std::map<std::string, unsigned int>& res_map, std::map<std::string, unsigned int>& map_to_join);

#endif //COUNTWORDS_WRITE_MAP_H
