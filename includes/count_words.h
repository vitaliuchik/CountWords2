#ifndef COUNTWORDS_COUNT_WORDS_H
#define COUNTWORDS_COUNT_WORDS_H

#include <vector>
#include <string>
#include <map>
#include <boost/locale.hpp>
#include <boost/locale/boundary.hpp>

std::vector<std::string> extract_words(std::string& text);
std::map<std::string, unsigned int> vectorToMap(std::vector<std::string>& words);


#endif //COUNTWORDS_COUNT_WORDS_H
