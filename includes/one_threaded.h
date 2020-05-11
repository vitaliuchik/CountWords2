#ifndef COUNTWORDS_ONE_THREADED_H
#define COUNTWORDS_ONE_THREADED_H

#include "constants.h"
#include "reader.h"
#include "count_words.h"
#include "write_map.h"

#include <string>
#include <map>
#include <cstdio>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <iostream>
#include <filesystem>

std::map<std::string, unsigned int> oneThreadCount(std::string& in);
void oneThreadExtract(const std::string& inPath, const std::string& outPathA,const std::string& outPathN);




#endif //COUNTWORDS_ONE_THREADED_H
