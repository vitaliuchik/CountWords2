cmake_minimum_required(VERSION 3.15)
project(CountWords)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(LibArchive REQUIRED)
find_package(Boost COMPONENTS filesystem program_options system locale REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LibArchive_INCLUDE_DIR})
add_executable(CountWords main.cpp src/reader.cpp includes/reader.h src/one_threaded.cpp includes/one_threaded.h includes/time_counting.h src/multi_threaded.cpp includes/multi_threaded.h includes/constants.h src/count_words.cpp includes/count_words.h src/write_map.cpp includes/write_map.h includes/exceptions.h)
TARGET_LINK_LIBRARIES(CountWords LINK_PUBLIC ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(CountWords LINK_PUBLIC ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(CountWords LINK_PUBLIC ${LibArchive_LIBRARIES})




