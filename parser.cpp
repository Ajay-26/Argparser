#include "parser.h"

ArgumentBlock::ArgumentBlock(std::string name, std::string shortname, std::string type, std::string value, bool required, std::string desc){
    this->name = name;
    this->short_name = shortname;
    this->type = type;
    this->value = value;
    this->required = required;
    this->desc = desc;
    this->found = false;
}
std::string ArgumentBlock::get_help_string(){
    return this->name + std::string(" or ") + this->short_name + std::string(":") + this->desc + std::string("\n");
}

ArgParser::ArgParser(){
    this->help_str = std::string("Usage: \n");
    this->valid = true;
}

void ArgParser::add_argument(std::string name, std::string short_name, std::string type, std::string value , bool required,std::string desc){
    if(name == EMPTY_STR && short_name == EMPTY_STR){
        std::cerr << "Invalid Argument" << std::endl;
        this->valid = false;
        return;
    }
    ArgumentBlock *new_block = new ArgumentBlock(name,short_name,type,value,required);
    if(name != EMPTY_STR){
        if(this->args_map.find(name) != this->args_map.end()){
            this->valid = false;
            std::cerr << "Repeated Argument" <<std::endl;
            return;
        }
        this->args_map[name] = new_block;
    }   
    if(short_name != EMPTY_STR){
        if(this->args_map.find(short_name) != this->args_map.end()){
            this->valid = false;
            std::cerr << "Repeated Argument" <<std::endl;
            return;
        }
        this->args_map[name] = new_block;
    }
    this->help_str += new_block->get_help_string(); 
    new_block->found = true;
    if(required){
        this->required_args.push_back(name);
    }
    return;   
}   
    
void ArgParser::parse_args(int argc, char **argv){
    if(!this->valid){
        std::cerr << this->help_str;
        return;
    }
    int i = 0;
    ArgumentBlock *temp;
    std::string input_str;
    while(i < argc){
        if(this->args_map.find(argv[i]) != this->args_map.end()){
            std::cerr << this->help_str;
            return;
        }
        if(argv[i][0] != '-'){
            std::cerr << this->help_str;
            return;
        }
        if(argv[i][1] == '-'){
            input_str = std::string(argv[i] + 2);
        }else{
            input_str = std::string(argv[i] + 1);
        }
        temp = this->args_map[input_str];
        i += 1;
        if(argv[i][0] != '-'){
            temp->value = std::string(argv[i]);
            i++;
        }
    }
    for(auto r : this->required_args){
        if(!this->args_map[r]->found){
            std::cerr << this->help_str;
            return;
        }
    }
}

void ArgParser::get_arg(std::string name, void* value){
    if(this->args_map.find(name) == this->args_map.end()){
        std::cerr << "Argument not entered" << std::endl;
        return;
    }
    ArgumentBlock *b = this->args_map[name];
    if(b->type == std::string("str")){
        *((std::string *)value) = b->value;
    }else if(b->type == std::string("float")){
        *((float *)value) = std::stof(b->value);
    }else if(b->type == std::string("int")){
        *((int *)value) = std::stoi(b->value);
    }else if(b->type == std::string("double")){
        *((double*)value) = std::stod(b->value);
    }
}
