#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <sys/stat.h>

#include <sls.h>

const int KB_SIZE = 1024;
const int MB_SIZE = 1024 * KB_SIZE;
const int GB_SIZE = 1024 * MB_SIZE;

int main(int argc, char** argv) {
	if (argc == 1) {
        // Search in this dir
        std::string path = "./";
        std::vector<SLS_FILE> files;
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            SLS_FILE sls; 
            if (entry.is_directory() == false)
                sls.file_size = entry.file_size();
            else
                sls.file_size = 0;
            sls.path = entry.path();
            sls.is_directory = entry.is_directory();
            files.push_back(sls);
        }
        print_filenames(files);
    } else {
        if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "--v") == 0 
            || strcmp(argv[1], "-version") == 0  || strcmp(argv[1], "-v") == 0) {
                std::cout << "\x1b[1;35mVersion: \x1b[0;0m" << VERSION << std::endl << "\x1b[1;35mTool created by:\x1b[0;0m https://github.com/SolindekDev/" << std::endl << "\x1b[1;35mOfficial repo of tool:\x1b[0;0m https://github.com/SolindekdDev/sls" << std::endl;
        } else {
            // Path exists?
            if (is_path_exists(argv[1]) == true) {
                std::string path = argv[1];
                std::vector<SLS_FILE> files;
                for (const auto &entry : std::filesystem::directory_iterator(path)) {
                    SLS_FILE sls; 
                    if (entry.is_directory() == false)
                        sls.file_size = entry.file_size();
                    else
                        sls.file_size = 0;
                    sls.path = entry.path();
                    sls.is_directory = entry.is_directory();
                    files.push_back(sls);
                }
                print_filenames(files);
            } else {
                error("Given path do not exists");
                exit(EXIT_FAILURE);
            }
        } 
    }

    return 0;
}

void error(std::string desc) {
    std::cout << "\x1b[1;31msls: \x1b[0;0m" << desc << std::endl;
}

bool is_path_exists(const std::string &s) {
    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
}

void print_filenames(std::vector<SLS_FILE> files) {
    auto mxlen_of_filenames = max_lenght_of_filenames(files);
    std::cout 
            << "\x1b[1;35m" 
            << "Filename"
            << print_spaces(mxlen_of_filenames, "Filename") 
            << "\x1b[0;0m | \x1b[0;33m" 
            << "Type of file "
            << "\x1b[0;0m | \x1b[0;33m" 
            << "Size of file"
            << "\x1b[0;0m" 
            << std::endl;
    for (size_t i = 0; i < files.size(); i++) {
        std::cout 
            << "\x1b[1;35m" 
            << files.at(i).path 
            << print_spaces(mxlen_of_filenames, files.at(i).path) 
            << "\x1b[0;0m | \x1b[0;33m" 
            << type_of_file(files.at(i).is_directory) 
            << print_spaces_between_type(files, i) 
            << "\x1b[0;0m | \x1b[0;33m" 
            << human_file_size(files.at(i).file_size) 
            << "\x1b[0;0m" 
            << std::endl;
    }
}

std::string type_of_file(bool is_dir) {
    if (is_dir == true)
        return "Directory";
    else
        return "File";
}   

std::string human_file_size(int file_size) {
    std::string formatString;

    if (file_size < KB_SIZE) {
        formatString += std::to_string(file_size);
        formatString += "B";
    } else {
        if (file_size < MB_SIZE) {
            formatString += std::to_string(file_size/KB_SIZE);
            formatString += ".";
            formatString += std::to_string((file_size * 100 / KB_SIZE) % 100);
            formatString += "kB";
        } else {
            if (file_size < GB_SIZE) {
                formatString += std::to_string(file_size/MB_SIZE);
                formatString += ".";
                formatString += std::to_string((file_size * 100 / MB_SIZE) % 100);
                formatString += "MB";
            } else {
                if (file_size >= GB_SIZE) {
                    formatString += std::to_string(file_size/GB_SIZE);
                    formatString += ".";
                    formatString += std::to_string((file_size * 100 / GB_SIZE) % 100);
                    formatString += "GB";
                }
            }
        }
    }

    if (formatString.find("-") != std::string::npos) {
        return formatString.replace(formatString.find("-"), 1, "");
    } else {
        return formatString;   
    }
}

int max_lenght_of_filenames(std::vector<SLS_FILE> files) {
    auto big_length = 0;
    for (size_t i = 0; i < files.size(); i++) {
        if (files.at(i).path.length() > (size_t)big_length) {
            big_length = files.at(i).path.length();
        }   
    }

    return big_length;
}

std::string print_spaces(int mxlen_of_filenames, std::string filepath) {
    auto spaces_len = (mxlen_of_filenames - filepath.length()) + 2;
    std::string spaces = "";
    for (size_t i = 0; i < spaces_len; i++)
        spaces.push_back(' ');
    return spaces;
}

bool is_directory_in_actual_dir(std::vector<SLS_FILE> files) {
    bool dirs = false;
    for (size_t i = 0; i < files.size(); i++) {
        if (files.at(i).is_directory == true) {
            dirs = true;
        }
    }
    return dirs;
}

std::string print_spaces_between_type(std::vector<SLS_FILE> files, int i) {
    bool is_there_dir = is_directory_in_actual_dir(files);
    if (files.at(i).is_directory == true) {
        return "    ";
    } else {
        return "         ";
    }
}