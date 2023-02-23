#include "parser.h"

int main(int argc, char ** argv){
    ArgParser parser;
    parser.add_argument("type","","string","",false,"");
    parser.parse_args(argc,argv);
    return 0;
}