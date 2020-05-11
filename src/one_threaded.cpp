#include "../includes/one_threaded.h"


std::map<std::string, unsigned int> oneThreadCount(std::string& in){
    std::vector<std::string> words = extract_words(in);
    std::map<std::string, unsigned int> wordsCount = std::move(vectorToMap(words));
    return wordsCount;
}

void oneThreadExtract(const std::string& inPath, const std::string& outPathA,const std::string& outPathN){
    std::map<std::string, unsigned int> res_map1;
    std::map<std::string, unsigned int> res_map2;
    for(const auto& p: std::filesystem::recursive_directory_iterator(inPath)) {
        if (!std::filesystem::is_directory(p)) {
            unsigned long filesize = std::filesystem::file_size(p);
            if (filesize <= FILE_LIMIT){
                std::string path_string = p.path().u8string();
                std::string file = extract_string(path_string);
                res_map2 = oneThreadCount(file);
                mapsJoin(res_map1, res_map2);
            }
        }
    }
    writeKeySortedMap(outPathA,res_map1);
    writeValueSortedMap(outPathN, res_map1);
}