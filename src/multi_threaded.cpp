#include "../includes/multi_threaded.h"


void readRawFiles(const std::string& path, int indThreadNum, MultiThreadQueue<std::string>& q) {
    for(const auto& p: std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            unsigned long filesize = std::filesystem::file_size(p);
            if (filesize <= FILE_LIMIT) {
                std::string path_string = p.path().u8string();
                // std::cout << path_string << std::endl;
                std::string file = extract_string(path_string);
                q.push(file);
            }
        }
    }
    std::string pill = PILL;
    for (int i = 0; i < indThreadNum; i++) {
        q.push(pill);
    }
}


void fileIntoMap(MultiThreadQueue<std::string>& q_files,
        MultiThreadQueue<std::map<std::string, unsigned int>>& q_maps) {
    std::string raw_file;
    while (raw_file != PILL) {
        raw_file = q_files.pop();
        if (raw_file == PILL) break;
        std::vector<std::string> words = extract_words(raw_file);
        std::map<std::string, unsigned int> wordsCount = std::move(vectorToMap(words));
        q_maps.push(wordsCount);
    }
}


void mapUnion(MultiThreadQueue<words_map> &map_q, words_map &main_map) {
    words_map map_to_join;
    bool if_pill = false;
    do {
        map_to_join = map_q.pop();
        if (map_to_join.find(PILL) != map_to_join.end()) {
            if_pill = true;
        }
        mapsJoin(main_map, map_to_join);
    }
    while (!if_pill);
    main_map.erase(PILL);
}



void multiThreadCount(const std::string& path, const std::string& outPathA,const std::string& outPathN, int indThreadNum, int mergeThreadNum) {
    MultiThreadQueue<std::string> queue_files(1000);
    MultiThreadQueue<std::map<std::string, unsigned int>> queue_maps(1000);

    std::thread reader_thread = std::thread{
        readRawFiles,
        path,
        indThreadNum,
        std::ref(queue_files)
    };

    std::vector<std::thread> ind_threads(indThreadNum);

    for (auto & ind_thread : ind_threads) {
        ind_thread = std::thread{
                fileIntoMap,
                std::ref(queue_files),
                std::ref(queue_maps)
        };
    }


    std::vector<words_map> map_v(mergeThreadNum);
    std::vector<std::thread> map_threads(mergeThreadNum);
    // merging
    for (int i=0; i < mergeThreadNum; ++i) {
        map_threads[i] = std::thread{
                mapUnion,
                std::ref(queue_maps),
                std::ref(map_v[i])
        };
    }

    reader_thread.join();
    for(auto& t: ind_threads) {
        t.join();
    }
    for (int i = 0; i < mergeThreadNum; i++) {
        words_map pill_map;
        pill_map[PILL] = 0;
        queue_maps.push(pill_map);
    }
    for(auto& t: map_threads) {
        t.join();
    }


    int numOfActiveMaps = mergeThreadNum;
    int j = 1;
    while (numOfActiveMaps > 1) {
        for (int i = 0; i < static_cast<int>(numOfActiveMaps/2); ++i) {
            map_threads[i*j*2] = std::thread{
                    mapsJoin,
                    std::ref(map_v[i*j*2]),
                    std::ref(map_v[i*j*2 + j])
            };
        }
        for (int i = 0; i < static_cast<int>(numOfActiveMaps/2); ++i) {
            map_threads[i*j*2].join();
        }
        numOfActiveMaps = static_cast<int>(std::ceil(static_cast<float>(numOfActiveMaps)/2));
        j *= 2;
    }

    writeKeySortedMap(outPathA, map_v[0]);
    writeValueSortedMap(outPathN, map_v[0]);

}
