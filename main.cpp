#include "includes/one_threaded.h"
#include "includes/multi_threaded.h"
#include "includes/time_counting.h"
#include <iostream>

int main(int argc, char *argv[]) {
    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);

    std::string conf_file;
    if (argc == 2) {
        conf_file = argv[1];
    } else if (argc == 1) {
        conf_file = "config.dat";
    } else {
        std::cerr << "Invalid arguments.\n";
        exit(1);
    }
    std::string inFile, outByA, outByN;
    int indThreadsNum;
    int mergeThreadsNum;
    std::string conf = read_txt(conf_file);
    std::vector<std::string> confArgs;
    boost::split(confArgs, conf, boost::is_any_of("\n="));

    if (!confArgs[1].empty() && !confArgs[3].empty() && !confArgs[5].empty() && !confArgs[7].empty()&& !confArgs[9].empty()){
        inFile = confArgs[1].substr (1,confArgs[1].length()-2);
        outByA = confArgs[3].substr (1,confArgs[3].length()-2);;
        outByN = confArgs[5].substr (1,confArgs[5].length()-2);;
        indThreadsNum = std::stoi(confArgs[7]);
        mergeThreadsNum = std::stoi(confArgs[9]);
    }
    else
        throw InvalidConfigurationException();

    std::chrono::high_resolution_clock::time_point start_time, finish_time;
    start_time = get_current_time_fenced();

    if (indThreadsNum == 1 && mergeThreadsNum == 1){
        oneThreadExtract(inFile, outByA, outByN);
    }
    else {
        multiThreadCount(inFile,outByA, outByN, indThreadsNum, mergeThreadsNum);
    }

    finish_time = get_current_time_fenced();
    std::cout << to_us(finish_time - start_time) <<  std::endl;
    return EXIT_SUCCESS;
}





