#ifndef __SLS_MAIN_H
#define __SLS_MAIN_H

#include <iostream>
#include <vector>
#include <string>

#define VERSION (std::string)"1.0.0v"

typedef struct SLS_FILE {
    std::string path;
    bool is_directory;
    int file_size;
} SLS_FILE;

int main(int argc, char** argv);

std::string type_of_file(bool is_dir);

std::string human_file_size(int file_size);

void print_filenames(std::vector<SLS_FILE> files);

int max_lenght_of_filenames(std::vector<SLS_FILE> files);

std::string print_spaces(int mxlen_of_filenames, std::string filepath);

void error(std::string desc);

bool is_path_exists(const std::string &s);

bool is_directory_in_actual_dir(std::vector<SLS_FILE> files);

std::string print_spaces_between_type(std::vector<SLS_FILE> files, int i);

#endif /* __SLS_MAIN_H */
