#include <iostream>
#include "../argparse.hpp"

using namespace std;


int main(int argc, char** argv){
    auto parser = argparse::ArgumentParser(argv[0], NULL, NULL, NULL);
    
    // Display the main parser's help
    print_padding_characters(0, 80, '#');
    printf("\n# First parser's help");
    print_padding_characters("# First parser's help", 79, ' ');
    printf("#\n");
    print_padding_characters(0, 80, '#');
    printf("\n");
    parser.print_help();
}