// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "commands.h"
#include <chrono>
#include <thread>
int main(int argc, char *argv[]) {
//    command_line_options_t command_line_options{argc, argv};
//    std::cout << "A flag value: " << command_line_options.get_A_flag() << std::endl;

// Testing cd:
//    std::vector<std::string> input = {".."};
//    std::cout << std::filesystem::current_path() << std::endl;
//    vi_cd(input);
//    std::cout << std::filesystem::current_path() << std::endl;

// Testing mv:
//    std::vector<std::string> input2 = {"hello.txt", "helloe.txt"};
//    std::vector<std::string> input3 = {"prikol", "data"};
//    vi_mv(input2);
//    vi_mv(input3);

// Testing mkdir:
//    std::vector<std::string> input4 = {"new dir", "yomayo", "gg"};
//    vi_mkdir(input4);

// Testing touch:
//    std::vector<std::string> input5 = {"touch.txt", "yoma.yaml", "gg.py"};
//    vi_touch(input5);

//  Testing cat:
//    std::vector<std::string> output;
//    std::vector<std::string> input6 = {"hello2.txt", "helloe.txt"};
//    vi_cat(input6, &output);
//    for (auto &el: output){
//        std::cout << el << std::endl;
//    }

//  Testing ls:
//    std::vector<std::string> input7 = {};
//    std::string ls{};
//    std::vector<file_data> info;
//    std::vector<file_data>* info_ptr = &info;
//    vi_ls(input7, ls, info_ptr);
//    std::cout << ls << std::endl;
//    for (auto el:info){
//        std::cout << el.name << "   " << el.rwx << "    " << el.user << "    " << el.size << "    " << el.date << std::endl;
//    }
//  Testing archive:
//    std::vector<file_archive> inside_zip;
//    std::vector<file_archive>* inside_zip_ptr = &inside_zip;
//    vi_archive(input7, "../data/data.zip", inside_zip_ptr);
//    for (auto el:inside_zip){
//        std::cout << el.name << "   " << el.comp_size << "    " << el.date << "    " << el.content << std::endl;
//    }
//  Testing symlink:
//    std::vector<std::string> args = {"../data/joj.txt", "sym_joj.txt"};
//    vi_symlink(args);
//    std::vector<std::string> input7 = {};
//    std::string ls{};
//    std::vector<file_data> info;
//    std::vector<file_data>* info_ptr = &info;
//    vi_ls(input7, ls, info_ptr);
//    std::cout << ls << std::endl;

//  Testing hardlink:
//    std::vector<std::string> args = {"../data/hard_joj.txt", "hard_joj.txt"};
//    vi_hardlink(args);
//    std::vector<std::string> input7 = {};
//    std::string ls{};
//    std::vector<file_data> info;
//    std::vector<file_data>* info_ptr = &info;
//    vi_ls(input7, ls, info_ptr);
//    std::cout << ls << std::endl;

// Testing chmod:
//    std::vector<std::string> input7 = {};
//    std::string ls{};
//    std::vector<file_data> info;
//    std::vector<file_data>* info_ptr = &info;
//    vi_ls(input7, ls, info_ptr);
//    std::cout << ls << std::endl;
//    std::vector<std::string> inputn = {"opapa.txt", "r", "w", "x", "", "w", "x", "-", "-", "-"};
//    vi_chmod(inputn);
//    ls = {};
//    info = {};
//    info_ptr = &info;
//    vi_ls(input7, ls, info_ptr);
//    std::cout << std::endl;
//    std::cout << ls << std::endl;
    return 0;
}
