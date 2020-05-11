#ifndef COUNTWORDS_READER_H
#define COUNTWORDS_READER_H

#include "exceptions.h"
#include "constants.h"

#include <iostream>
#include <archive.h>
#include <archive_entry.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <boost/locale.hpp>

std::string archive_to_memory(std::string &buffer);
std::string read_archive (std::string &file_in);
std::string read_txt (std::string &file_in);
std::string extract_string(std::string& file_in);

#endif //COUNTWORDS_READER_H
