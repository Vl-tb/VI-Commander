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
#include <fstream>
#include "errors.h"

int vi_cd(const std::vector<std::string> &args);
int vi_mv(const std::vector<std::string> &args);
int vi_mkdir(const std::vector<std::string> &args);
int vi_touch(const std::vector<std::string> &args);
int vi_cat(const std::vector<std::string> &args, std::vector<std::string>* output);
int vi_ls(const std::vector<std::string> &args, std::string &output);

struct file_data{
    std::string rwx;
    std::string user;
    std::string size;
    std::string date;
    std::string name;
};



#endif //VI_COMMANDER_COMMANDS_H
