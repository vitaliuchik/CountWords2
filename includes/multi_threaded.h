//
// Created by Admin on 22.04.2020.
//

#ifndef COUNTWORDS_MULTI_THREADED_H
#define COUNTWORDS_MULTI_THREADED_H


#include "multi_thread_queue.h"
#include "constants.h"
#include "reader.h"
#include "count_words.h"
#include "multi_thread_queue.h"
#include "write_map.h"

#include <filesystem>
#include <thread>
#include <iostream>
#include <string>
#include <map>
#include <cmath>

typedef std::map<std::string, unsigned int> words_map;


void readRawFiles(const std::string& path, int indThreadNum, MultiThreadQueue<std::string>& q);
void fileIntoMap(MultiThreadQueue<std::string>& q_files,
        MultiThreadQueue<std::map<std::string, unsigned int>>& q_maps);
void mapUnion(MultiThreadQueue<words_map> &map_q, words_map &main_map);
void multiThreadCount(const std::string& path, const std::string& outPathA,const std::string& outPathN, int indThreadNum, int mergeThreadNum);


template <typename T, typename G>
void mergeMaps(std::map<T, G>& res_map, std::map<T, G>& map_to_join) {
    res_map.merge(map_to_join);
}


#endif //COUNTWORDS_MULTI_THREADED_H


