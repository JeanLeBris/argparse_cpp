#include <iostream>
#include "../argparse.hpp"

using namespace std;
// using namespace argparse;

// argparse::parser(){

// }

// argparse::parser(char* prog, char* description, char* epilog){

// }

// argparse::ArgumentParserArgs parser_args;

int main(int argc, char** argv){
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
    parser.add_argument("-c --argument-c", "store_true", 1, "cst", "def2", "string", 0, NULL, false, "third argument", "metavar", NULL, 0);

    // Declare a first sub-parser and 3 parsers under it
    argparse::Subparser* subparser_1 = parser.add_subparsers("tit1", NULL, NULL, NULL, NULL, true, "help of subparser 1", NULL);

    auto parser_1 = subparser_1->add_parser("a", NULL);
    auto parser_2 = subparser_1->add_parser("b", "help of b");
    auto parser_3 = subparser_1->add_parser("c", "help of c");
    
    // Declare a second sub-parser and 4 parsers under it
    argparse::Subparser* subparser_2 = parser.add_subparsers("tit2", NULL, NULL, NULL, NULL, true, NULL, NULL);

    auto parser_4 = subparser_2->add_parser("d", "help of d");
    auto parser_5 = subparser_2->add_parser("e", "help of e");
    auto parser_6 = subparser_2->add_parser("f", "help of f");
    auto parser_7 = subparser_2->add_parser("g", "help of g");

    // Declare 2 new arguments under the third parser of the second sub-parser
    const char* choices3[3] = {"choice_3", "choice_4", "choice_5"};
    parser_6->add_argument("-d --argument-d", "store", 1, NULL, NULL, "string", 3, choices3, false, "fourth argument", "metavar", NULL, 0);
    parser_6->add_argument("-e --argument-e", "store", 1, "cst", "def2", "string", 0, NULL, false, "fifth argument", "metavar", NULL, 0);



    subparser_2 = parser_6->add_subparsers("tit3", NULL, NULL, NULL, NULL, true, NULL, NULL);
    subparser_2->add_parser("1", "help of d");
    subparser_2->add_parser("2", "help of e");
    subparser_2->add_parser("3", "help of f");
    subparser_2->add_parser("4", "help of g");




    // // Display the main parser's help
    // print_padding_characters(0, 80, '#');
    // printf("\n# First parser's help");
    // print_padding_characters("# First parser's help", 79, ' ');
    // printf("#\n");
    // print_padding_characters(0, 80, '#');
    // printf("\n");
    // parser.print_help();

    // // Display the third parser of the second sub-parser' help
    // print_padding_characters(0, 80, '#');
    // printf("\n# Third parser of the second sub-parser' help");
    // print_padding_characters("# Third parser of the second sub-parser' help", 79, ' ');
    // printf("#\n");
    // print_padding_characters(0, 80, '#');
    // printf("\n");
    // parser_6->print_help();

    // parser_6->print_version();

    argparse::ParsedArguments* parsed_args = parser.parse_args(argc, argv);

    parsed_args->print_keys_and_values();

    return 0;
}