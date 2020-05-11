
#include "../includes/reader.h"


std::string extract_string(std::string& file_in){
    // Start reading file
    std::string text;
    if (file_in.substr(file_in.length() - 4, 4) == ".txt"){

        text = read_txt(file_in);}
    else {
        text = read_archive(file_in);
    }
    return text;
}

std::string read_txt (std::string &file_in) {
    std::ifstream ifs(file_in);
    if (ifs.is_open()){
        std::string content( (std::istreambuf_iterator<char>(ifs) ),
                             (std::istreambuf_iterator<char>()    ) );
        return content;}
    else{
        throw InvalidConfigurationException();
    }
}

std::string read_archive (std::string &file_in) {
    std::vector<std::string> words;
    std::ifstream raw_file(file_in, std::ios::binary);
    std::ostringstream buffer_ss;
    buffer_ss << raw_file.rdbuf();
    std::string buffer{buffer_ss.str()};
    return archive_to_memory(buffer);
}

std::string archive_to_memory(std::string &buffer) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    off_t filesize;
    std::string result;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_memory(a, buffer.c_str(), buffer.size());

    while (r > ARCHIVE_FATAL) {
        r = archive_read_next_header(a, &entry);

        archive_entry_set_filetype(entry, AE_IFREG);

        if (r == ARCHIVE_EOF) break;
        else if (r < ARCHIVE_OK) continue;

        filesize = archive_entry_size(entry);
        if (filesize > 0 && filesize < FILE_LIMIT &&\
            std::filesystem::path(archive_entry_pathname(entry)).extension() == ".txt") {

            std::string output(filesize, char{});
            r = archive_read_data(a, &output[0], output.size());
            result += " " + output;
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return result;
}

