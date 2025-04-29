#include <iostream>
#include <string.h>

/**
 * Print padding characters after the input string until the total length reaches the end value
 * 
 * @param string String after which printing padding characters
 * @param final_length Total length of the printed string after padding added
 * @param padding_character Padding cahracter to use
 * 
 * @return 0 if the function worked as intended
 */
int print_padding_characters(const char* string, int final_length, char padding_character){
    for(int i = strlen(string); i < final_length; i++){
        printf("%c", padding_character);
    }

    return 0;
}

/**
 * Print padding characters after the input string until the total length reaches the end value
 * 
 * @param string_len String after which printing padding characters
 * @param final_length Total length of the printed string after padding added
 * @param padding_character Padding cahracter to use
 * 
 * @return 0 if the function worked as intended
 */
int print_padding_characters(int string_len, int final_length, char padding_character){
    for(int i = string_len; i < final_length; i++){
        printf("%c", padding_character);
    }

    return 0;
}