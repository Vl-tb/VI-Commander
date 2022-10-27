#include "commands.h"
#include "errors.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

int vi_cd(const std::vector<std::string> &args) {
    if (args.size() > 1) {
        std::cerr << "cd: too many arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        const std::filesystem::path path = std::filesystem::u8path(args[0]);
//    int cd = chdir(args[0].c_str());
        std::filesystem::current_path(path);
    }
    catch(const  std::filesystem::filesystem_error& ex)
    {
        std::cerr << "cr: " << ex.what() << std::endl;
        return DIRECTORY_ERROR;
    }
    catch(const  std::bad_alloc& ex)
    {
        std::cerr << "cd: " << ex.what() << std::endl;
        return MEMORY_ERROR;
    }
    catch(...){
        std::cerr << "Unknown cd error" << std::endl;
        return UNKNOWN_ERROR;
    }
    return 0;
}

int vi_mv(const std::vector<std::string> &args) {
    if (args.size() > 2) {
        std::cerr << "mv: too much arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    if (args.size() < 2) {
        std::cerr << "mv: too many arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        const std::filesystem::path old_p = std::filesystem::u8path(args[0]);
        const std::filesystem::path new_p = std::filesystem::u8path(args[1]);
        rename(old_p,new_p );
    }
    catch(const  std::filesystem::filesystem_error& ex)
    {
        std::cerr << "mv: " << ex.what() << std::endl;
        return DIRECTORY_ERROR;
    }
    catch(const  std::bad_alloc& ex)
    {
        std::cerr << "mv: " << ex.what() << std::endl;
        return MEMORY_ERROR;
    }
    catch(...){
        std::cerr << "Unknown mv error" << std::endl;
        return UNKNOWN_ERROR;
    }
    return 0;
}

int vi_mkdir(const std::vector<std::string> &args){
    if (args.size() < 1) {
        std::cerr << "mkdir: too few arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        for (auto &arg: args){
            const std::filesystem::path dir = std::filesystem::u8path(arg);
            bool status = std::filesystem::create_directory(dir);
            if (!status) {
                std::cerr << "mkdir: creation of directory failed" << std::endl;
                return DIRECTORY_ERROR;
            }
        }
    }
    catch(const  std::filesystem::filesystem_error& ex)
    {
        std::cerr << "mkdir: " << ex.what() << std::endl;
        return DIRECTORY_ERROR;
    }
    catch(const  std::bad_alloc& ex)
    {
        std::cerr << "mkdir: " << ex.what() << std::endl;
        return MEMORY_ERROR;
    }
    catch(...){
        std::cerr << "Unknown mkdir error" << std::endl;
        return UNKNOWN_ERROR;
    }
    return 0;
}

int vi_touch(const std::vector<std::string> &args){
    if (args.size() < 1) {
        std::cerr << "touch: too few arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        for (auto &file : args){
            std::ofstream new_file(file);
            new_file.close();
        }
    }
    catch(...){
        std::cerr << "touch: file creation error" << std::endl;
        return UNKNOWN_ERROR;
    }
    return 0;
}

int vi_cat(const std::vector<std::string> &args, std::vector<std::string>* output){
    if (args.size() < 1) {
        std::cerr << "cat: too few arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        for (auto &arg: args){
            std::ifstream ifs(arg);
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                 (std::istreambuf_iterator<char>()) );
            output->push_back(content);
        }
    }
    catch(...){
        std::cerr << "cat: unknown error" << std::endl;
        return UNKNOWN_ERROR;
    }
    return 0;
}

std::string replace_str(std::string str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
