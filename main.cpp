// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "commands.h"

int main(int argc, char *argv[]) {
//    command_line_options_t command_line_options{argc, argv};
//    std::cout << "A flag value: " << command_line_options.get_A_flag() << std::endl;

// Testing cd:
    std::vector<std::string> input = {".."};
//    std::cout << std::filesystem::current_path() << std::endl;
    vi_cd(input);
//    std::cout << std::filesystem::current_path() << std::endl;

// Testing mv:
    std::vector<std::string> input2 = {"hello.txt", "helloe.txt"};
    std::vector<std::string> input3 = {"prikol", "data"};
//    vi_mv(input2);
//    vi_mv(input3);

// Testing mkdir:
    std::vector<std::string> input4 = {"new dir", "yomayo", "gg"};
//    vi_mkdir(input4);

// Testing touch:
    std::vector<std::string> input5 = {"touch.txt", "yoma.yaml", "gg.py"};
//    vi_touch(input5);

//  Testing cat:
    std::vector<std::string> output;
    std::vector<std::string> input6 = {"hello2.txt", "helloe.txt"};
    vi_cat(input6, &output);
//    for (auto &el: output){
//        std::cout << el << std::endl;
//    }

//  Testing ls:
    std::vector<std::string> input7 = {};
    std::string ls{};
    vi_ls(input7, ls);
    std::cout << ls << std::endl;
    return 0;
}
