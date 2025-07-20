#include <iostream>
#include "../../include/argparse.hpp"

using namespace std;


int main(int argc, char** argv){
    // auto parser = argparse::ArgumentParser(argv[0], NULL, NULL, NULL);

    // Declare new arguments parser
    auto parser = argparse::ArgumentParser(argv[0],
                                           NULL,
                                           "This program is an example of how to use the argparse_cpp library",
                                           "This is just a basic example of the library's usage, more content will be added later and feel free to experiment with it",
                                           NULL,
                                           "-",
                                           NULL,
                                           "0.1.0",
                                           true,
                                           true,
                                           true);

    // Declare 3 new arguments in the main arguments parser
    int choices1[2] = {1, 2};
    parser.add_argument("-a --argument-a", NULL, 1, 0, 2, "int", 2, choices1, false, "first argument", "metavar", NULL, 0);
    const char* choices2[2] = {"choice_1", "choice_2"};
    parser.add_argument("-b --argument-b", "store", 1, "cst", "def1", "string", 2, choices2, false, "second argument", "metavar", NULL, 0);
    parser.add_argument("-c --argument-c", "store", 1, (float) 2.1, (float) 1.9, "float", 0, NULL, false, "third argument", "metavar", NULL, 0);
    parser.add_argument("-d --argument-d", "store", 1, 2.1, 1.9, "double", 0, NULL, false, "fourth argument", "metavar", NULL, 0);
    
    // Declare a first sub-parser and 3 parsers under it
    argparse::Subparser* subparser_1 = parser.add_subparsers("tit1", NULL, NULL, NULL, NULL, true, "help of subparser 1", NULL);

    auto parser_1 = subparser_1->add_parser("a", NULL);
    auto parser_2 = subparser_1->add_parser("b", "help of b");
    auto parser_3 = subparser_1->add_parser("c", "help of c");
    

    
    argparse::ParsedArguments* parsed_args = parser.parse_args(argc, argv);
    
    parsed_args->print_keys_and_values();

    printf("Processing the arguments finished successfully\n");

    return 0;
}