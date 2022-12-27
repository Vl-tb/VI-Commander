#ifndef VI_COMMANDER_COMMANDS_H
#define VI_COMMANDER_COMMANDS_H
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include "options_parser.h"
#include <sys/wait.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <readline/history.h>
#include <readline/readline.h>
#include <regex>
#include <zip.h>
#include <fstream>
#include "errors.h"

struct file_data{
    std::string rwx;
    std::string user;
    std::string size;
    std::string date;
    std::string name;
};

struct file_archive{
    std::string comp_size;
    std::string date;
    std::string name;
    std::string content;
};

int vi_cd(const std::vector<std::string> &args);
int vi_mv(const std::vector<std::string> &args);
int vi_mkdir(const std::vector<std::string> &args);
int vi_touch(const std::vector<std::string> &args);
int vi_cat(const std::vector<std::string> &args, std::vector<std::string>* output);
int vi_ls(const std::vector<std::string> &args, std::string &output, std::vector<file_data>* metadata);
int vi_archive(const std::vector<std::string> &args, const std::filesystem::path& path, std::vector<file_archive>* out);
int vi_symlink(const std::vector<std::string> &args);
int vi_hardlink(const std::vector<std::string> &args);
int vi_chmod(const std::vector<std::string> &args);



#endif //VI_COMMANDER_COMMANDS_H
