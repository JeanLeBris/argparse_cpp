#include <iostream>
#include "../argparse.hpp"

using namespace std;
// using namespace argparse;

// argparse::parser(){

// }

// argparse::parser(char* prog, char* description, char* epilog){

// }

// argparse::ArgumentParserArgs parser_args;

int main(){
    // Declare new arguments parser
    auto parser = argparse::ArgumentParser("Program name",
                                           "example_1.exe -a first_argument_value [-b second_argument_value] [-c third_argument_value]",
                                           "This program is an example of how to use the argparse_cpp library",
                                           "This is just a basic example of the library's usage, more content will be added later and feel free to experiment with it");
    
    // Declare 3 new arguments in the main arguments parser
    argparse::undefined_type choices1[2] = {{.integer = 1}, {.integer = 2}};
    parser.add_argument("-a --argument-a", "action", 1, 0, (argparse::undefined_type) {.integer = 0}, "int", 2, choices1, true, "first argument", "metavar", NULL, 0);
    argparse::undefined_type choices2[2] = {{.const_string = "choice_1"}, {.const_string = "choice_2"}};
    parser.add_argument("-b --argument-b", "action", 1, 0, (argparse::undefined_type) {.const_string = "def1"}, "string", 2, choices2, true, "second argument", "metavar", NULL, 0);
    parser.add_argument("-c --argument-c", "action", 1, 0, (argparse::undefined_type) {.const_string = "def2"}, "string", 0, NULL, true, "third argument", "metavar", NULL, 0);

    // Declare a first sub-parser and 3 parsers under it
    argparse::Subparser* subparser_1 = parser.add_subparsers(NULL, NULL, NULL, NULL, NULL, true, "help of subparser 1", NULL);

    auto parser_1 = subparser_1->add_parser("a", "help of a");
    auto parser_2 = subparser_1->add_parser("b", "help of b");
    auto parser_3 = subparser_1->add_parser("c", "help of c");
    
    // Declare a second sub-parser and 4 parsers under it
    argparse::Subparser* subparser_2 = parser.add_subparsers(NULL, NULL, NULL, NULL, NULL, true, "help of subparser 2", NULL);

    auto parser_4 = subparser_2->add_parser("d", "help of d");
    auto parser_5 = subparser_2->add_parser("e", "help of e");
    auto parser_6 = subparser_2->add_parser("f", "help of f");
    auto parser_7 = subparser_2->add_parser("g", "help of g");

    // Declare 2 new arguments under the third parser of the second sub-parser
    argparse::undefined_type choices3[3] = {{.const_string = "choice_3"}, {.const_string = "choice_4"}, {.const_string = "choice_5"}};
    parser_6->add_argument("-d --argument-d", "action", 1, 0, (argparse::undefined_type) {.const_string = "def1"}, "string", 3, choices3, true, "fourth argument", "metavar", NULL, 0);
    parser_6->add_argument("-e --argument-e", "action", 1, 0, (argparse::undefined_type) {.const_string = "def2"}, "string", 0, NULL, true, "fifth argument", "metavar", NULL, 0);

    // Display the main parser's help
    print_padding_characters(0, 80, '#');
    printf("\n# First parser's help");
    print_padding_characters("# First parser's help", 79, ' ');
    printf("#\n");
    print_padding_characters(0, 80, '#');
    printf("\n");
    parser.help();

    // Display the third parser of the second sub-parser' help
    print_padding_characters(0, 80, '#');
    printf("\n# Third parser of the second sub-parser' help");
    print_padding_characters("# Third parser of the second sub-parser' help", 79, ' ');
    printf("#\n");
    print_padding_characters(0, 80, '#');
    printf("\n");
    parser_6->help();

    return 0;
}