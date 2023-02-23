#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

#define EMPTY_STR std::string("")

class ArgumentBlock{
public:
    std::string name;
    std::string short_name;
    std::string type;
    std::string value;
    std::string desc;
    bool required;
    bool found;
    ArgumentBlock(std::string name = EMPTY_STR, std::string shortname = EMPTY_STR, std::string type = EMPTY_STR, std::string value = EMPTY_STR, bool required = false,std::string desc = EMPTY_STR);
    std::string get_help_string();
};

class ArgParser{
public:
    std::unordered_map<std::string,ArgumentBlock *>  args_map;
    std::string help_str;
    bool valid;
    std::vector<std::string> required_args;
    void add_argument(std::string name = EMPTY_STR, std::string short_name= EMPTY_STR, std::string type = std::string("string"), std::string value = EMPTY_STR, bool required = false,std::string desc = EMPTY_STR);
    void parse_args(int argc, char ** argv);
    void get_arg(std::string name, void* value);
    ArgParser();
};