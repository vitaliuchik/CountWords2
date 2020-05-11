#include "../includes/count_words.h"

namespace ba = boost::locale::boundary;

std::vector<std::string> extract_words(std::string& text) {
    std::vector<std::string> words;
    text = boost::locale::to_lower(boost::locale::fold_case(boost::locale::normalize(text)));

    ba::ssegment_index map(ba::word, text.begin(), text.end());
    map.rule(ba::word_letters);
    for (ba::ssegment_index::iterator it = map.begin(), e = map.end(); it != e; ++it)
        words.emplace_back(std::move(*it));
    return words;
}

std::map<std::string, unsigned int> vectorToMap(std::vector<std::string>& words) {
    std::map<std::string, unsigned int> wordsCount;
    for (auto &word: words){
        //Look if it's already there.
        if (wordsCount.find(word) == wordsCount.end()) // encountered the word for a first time.
            wordsCount[word] = 1; // initialize in map to 1.
        else
            wordsCount[word]++; // increment if already met word.
    }
    return wordsCount;
}