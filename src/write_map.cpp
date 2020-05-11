//
// Created by Admin on 22.04.2020.
//

#include "../includes/write_map.h"

void writeKeySortedMap(const std::string& fileName, std::map<std::string, unsigned int>& map) {
//    std::cout << fileName << std::endl;
    FILE *fp = fopen(fileName.c_str(), "w");
    for(auto & it : map) {
        fprintf(fp, "%s : %u\n", it.first.c_str(), it.second);
    }
    fclose(fp);
}

void writeValueSortedMap(const std::string& fileName, std::map<std::string, unsigned int>& map){
    FILE *fp = fopen(fileName.c_str(), "w");
    typedef std::function<bool(std::pair<std::string, unsigned int>, std::pair<std::string, unsigned int>)> Comparator;
    // Lambda function to compare two pairs.
    Comparator compFunctor =
            [](const std::pair<std::string, int>& elem1 ,const std::pair<std::string, int>& elem2)
            {
                return elem1.second >= elem2.second;
            };
    std::set<std::pair<std::string, int>, Comparator> sortedMap(
            map.begin(), map.end(), compFunctor);
    for (std::pair<std::string, unsigned int> iter : sortedMap)
        fprintf(fp, "%s : %u\n", iter.first.c_str(), iter.second);

    fclose(fp);
}


void mapsJoin(std::map<std::string, unsigned int>& res_map, std::map<std::string, unsigned int>& map_to_join) {
    for (const auto& elem: map_to_join) {
        if (res_map.find(elem.first) == res_map.end()) {
            res_map[elem.first] = elem.second;
        }
        else {
            res_map[elem.first] += elem.second;
        }
    }

    map_to_join.clear();
}
