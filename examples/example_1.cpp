#include <iostream>
#include "../argparse.hpp"

using namespace std;
// using namespace argparse;

// argparse::parser(){

// }

// argparse::parser(char* prog, char* description, char* epilog){

// }

int main(){
    // argparse::ArgumentParserArgs parser_args;

    auto parser = argparse::ArgumentParser("Program name",
                                           "example_1.exe -a first_argument_value [-b second_argument_value] [-c third_argument_value]",
                                           "This program is an example of how to use the argparse_cpp library",
                                           "This is just a basic example of the library's usage, more content will be added later and feel free to experiment with it");
    // parser.add_argument("-a --argument-a", "action", 1, 0, (argparse::unknown_type) {.integer = 0}, "int", 0, NULL, true, "first argument", "metavar", NULL, 0);
    // parser.add_argument("-b --argument-b", "action", 1, 0, (argparse::unknown_type) {.const_string = "test"}, "string", 0, NULL, true, "second argument", "metavar", NULL, 0);
    // parser.add_argument("-c --argument-c", "action", 1, 0, (argparse::unknown_type) {.const_string = "test2"}, "string", 0, NULL, true, "third argument", "metavar", NULL, 0);
    argparse::undefined_type choices1[2] = {{.integer = 1}, {.integer = 2}};
    parser.add_argument("-a --argument-a",
                        "action",
                        1,
                        0,
                        (argparse::undefined_type) {.integer = 0},
                        "int",
                        2,
                        choices1,
                        true,
                        "first argument",
                        "metavar",
                        NULL,
                        0);
    argparse::undefined_type choices2[2] = {{.const_string = "choice_1"}, {.const_string = "choice_2"}};
    parser.add_argument("-b --argument-b", "action", 1, 0, (argparse::undefined_type) {.const_string = "def1"}, "string", 2, choices2, true, "second argument", "metavar", NULL, 0);
    parser.add_argument("-c --argument-c", "action", 1, 0, (argparse::undefined_type) {.const_string = "def2"}, "string", 0, NULL, true, "third argument", "metavar", NULL, 0);
    parser.help();

    return 0;
}