#include "commands.h"
#include "errors.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <pwd.h>
#include <boost/algorithm/string.hpp>
#include <time.h>
#include <zip.h>
#include <errno.h>

constexpr size_t DATE_LENGTH = 32;
constexpr size_t STAT_SIZE = 256;
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
        std::cerr << "cd: " << ex.what() << std::endl;
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
    if (args.empty()) {
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
    if (args.empty()) {
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
    if (args.empty()) {
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

int vi_ls(const std::vector<std::string> &args, std::string &output, std::vector<file_data>* metadata){
    std::filesystem::path cur_path = std::filesystem::current_path();
//    std::vector<file_data> metadata;
    size_t max_user_len = 0;
    size_t max_size_len = 0;
    size_t max_name_len = 0;

    for (const auto & entry : std::filesystem::directory_iterator(cur_path)) {
        file_data file_meta;
        std::string path = entry.path();
        std::string file_name;

        std::vector<std::string> splitting;
        boost::split(splitting, path, boost::is_any_of("/"));
        file_name = splitting[splitting.size()-1];

        std::filesystem::file_status status = std::filesystem::symlink_status(path);
        std::filesystem::perms permissions = status.permissions();

        std::string perms_str;
        perms_str.reserve(9);

        (permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? perms_str += "r" : perms_str += "-";
        (permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? perms_str += "w" : perms_str += "-";
        (permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? perms_str += "x" : perms_str += "-";
        (permissions & std::filesystem::perms::group_read) != std::filesystem::perms::none ? perms_str += "r" : perms_str += "-";
        (permissions & std::filesystem::perms::group_write) != std::filesystem::perms::none ? perms_str += "w" : perms_str += "-";
        (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? perms_str += "x" : perms_str += "-";
        (permissions & std::filesystem::perms::others_read) != std::filesystem::perms::none ? perms_str += "r" : perms_str += "-";
        (permissions & std::filesystem::perms::others_write) != std::filesystem::perms::none ? perms_str += "w" : perms_str += "-";
        (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? perms_str += "x" : perms_str += "-";

        file_meta.rwx = perms_str;

        if (std::filesystem::is_directory(status)) {
            file_name = "\\" + file_name;
        }

        else if (std::filesystem::is_fifo(status)) {
            file_name = "|" + file_name;
        }
        else if (std::filesystem::is_socket(status)) {
            file_name = "=" + file_name;
        }
        else if (std::filesystem::is_symlink(status)) {
            file_name = "@" + file_name;
        }
        else if (((permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
                (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
                (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none)){
            file_name = "*" + file_name;
        }
        else if (!std::filesystem::is_regular_file(status)){
            file_name = "?" + file_name;
        }
        file_meta.name = file_name;
        if (file_name.length() > max_name_len){
            max_name_len = file_name.length();
        }

        struct stat sb{};
        std::string user_str;
        if (stat(path.c_str(), &sb) == -1) {
            std::cerr << "Could not obtain information about path" << std::endl;
            return INVALID_PATH;
        }
        auto pw = getpwuid(sb.st_uid);
        if (pw == nullptr) {
            user_str = "";
        }
        else{
            user_str =  pw->pw_name;
        }
        file_meta.user = user_str;
        if (user_str.length() > max_user_len){
            max_user_len = user_str.length();
        }

        auto file_size = sb.st_size;
        file_meta.size = std::to_string(file_size);
        if (file_meta.size.length() > max_size_len){
            max_size_len = file_meta.size.length();
        }

        auto mod_time = sb.st_mtime;
        std::tm * ptm = std::localtime(&mod_time);
        char time_mod_buf[DATE_LENGTH];
        std::strftime(time_mod_buf, DATE_LENGTH, "%Y-%m-%d %H:%M:%S", ptm);

        file_meta.date = std::string{time_mod_buf};
        metadata->emplace_back(file_meta);
    }

    output.reserve(33 + max_user_len + max_size_len + max_name_len);
    for (size_t i=0; i < metadata->size(); ++i){
        for (size_t j=0; j<9; ++j){
            output += metadata->at(i).rwx[j];
        }
        output += ' ';
        for (size_t j=0; j<max_user_len - metadata->at(i).user.length(); ++j){
            output += ' ';
        }
        for (size_t j=0; j<metadata->at(i).user.length(); ++j){
            output += metadata->at(i).user[j];
        }
        output += ' ';
        for (size_t j=0; j<max_size_len - metadata->at(i).size.length(); ++j){
            output += ' ';
        }
        for (size_t j=0; j<metadata->at(i).size.length(); ++j){
            output += metadata->at(i).size[j];
        }
        output += ' ';
        output += ' ';
        for (size_t j=0; j<metadata->at(i).date.length(); ++j){
            output += metadata->at(i).date[j];
        }
        output += ' ';
        output += ' ';
        for (size_t j=0; j<metadata->at(i).name.length(); ++j){
            output += metadata->at(i).name[j];
        }
        if (i != metadata->size()-1){
            output += '\n';
        }
    }
    return 0;
}

// Inspired by https://www.geeksforgeeks.org/c-program-to-read-and-print-all-files-from-a-zip-file/
int vi_archive(const std::vector<std::string> &args, const std::filesystem::path& path, std::vector<file_archive>* out){
    zip_t* archive = nullptr;
    archive = zip_open(path.c_str(), 0, nullptr);
    struct zip_stat* data = nullptr;
    data = static_cast<struct zip_stat*>(calloc(STAT_SIZE, sizeof(int)));
    zip_stat_init(data);
    zip_file_t* fd = nullptr;
    char* file = nullptr;
    int count = 0;

    while ((zip_stat_index(archive, count, 0, data)) == 0) {
        file = static_cast<char *>(calloc(data->size + 1, sizeof(char)));
        fd = zip_fopen_index(archive, count, 0);
        zip_fread(fd, file, data->size);
        file_archive file_arch;
        file_arch.name = data->name;
        file_arch.comp_size = std::to_string(data->comp_size);
        std::tm * ptm = std::localtime(&data->mtime);
        char time_mod_buf[DATE_LENGTH];
        std::strftime(time_mod_buf, DATE_LENGTH, "%Y-%m-%d %H:%M:%S", ptm);
        file_arch.date = std::string{time_mod_buf};
        file_arch.content = file;

        out->emplace_back(file_arch);

        free(file);
        count++;
    }
    return 0;
}

int vi_symlink(const std::vector<std::string> &args){
    if (args.size() != 2) {
        std::cerr << "symlink: too few or too many arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        std::filesystem::create_symlink(std::filesystem::u8path(args[0]), std::filesystem::u8path(args[1]));
    }
    catch(const  std::filesystem::filesystem_error& ex)
    {
        std::cerr << "symlink: link filename exists" << std::endl << ex.what() << std::endl;
        return ARGUMENTS_ERROR;
    }
    return 0;
}

int vi_hardlink(const std::vector<std::string> &args){
    if (args.size() != 2) {
        std::cerr << "hardlink: too few or too many arguments" << std::endl;
        return ARGUMENTS_ERROR;
    }
    try{
        std::filesystem::create_hard_link(std::filesystem::u8path(args[0]), std::filesystem::u8path(args[1]));
    }
    catch(const  std::filesystem::filesystem_error& ex)
    {
        std::cerr << "hardlink: link filename exists" << std::endl << ex.what() << std::endl;
        return ARGUMENTS_ERROR;
    }
    return 0;
}

int vi_chmod(const std::vector<std::string> &args){
    std::filesystem::perms params = std::filesystem::perms::none;
    if (args[1] == "r"){
        params |= std::filesystem::perms::owner_read;
    }
    if (args[2] == "w"){
        params |= std::filesystem::perms::owner_write;
    }
    if (args[3] == "x"){
        params |= std::filesystem::perms::owner_exec;
    }
    if (args[4] == "r"){
        params |= std::filesystem::perms::group_read;
    }
    if (args[5] == "w"){
        params |= std::filesystem::perms::group_write;
    }
    if (args[6] == "x"){
        params |= std::filesystem::perms::group_exec;
    }
    if (args[7] == "r"){
        params |= std::filesystem::perms::others_read;
    }
    if (args[8] == "w"){
        params |= std::filesystem::perms::others_write;
    }
    if (args[9] == "x"){
        params |= std::filesystem::perms::others_exec;
    }

    std::filesystem::permissions(std::filesystem::u8path(args[0]),
                    params,
                    std::filesystem::perm_options::replace);
}
