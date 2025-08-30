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
    if(string != NULL){
        for(int i = strlen(string); i < final_length; i++){
            printf("%c", padding_character);
        }
    }
    else{
        print_padding_characters("(null)", final_length, padding_character);
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

/**
 * Dynamically allocate a string and copy the input string in it, if input string is ```NULL```, the allocated string takes the value ```"\0"```
 * 
 * @param input_string String to copy
 * 
 * @return Copied string
 */
char* alloc_and_copy_string(const char* input_string){
    char* output_string = NULL;
    if(input_string != NULL){
        output_string = (char*) malloc(sizeof(*input_string) * (strlen(input_string) + 1));
        strcpy(output_string, input_string);
    }
    else{
        output_string = NULL;
        // output_string = (char*) malloc(sizeof(char) * 1);
        // output_string[0] = '\0';
    }
    
    return output_string;
}

int print_title(const char* content, int length, char character){
    char* content_and_first_char = (char*) malloc(sizeof(char) * (strlen(content) + 2));

    sprintf(content_and_first_char, "%c %s", character, content);
    print_padding_characters(0, length, character);
    printf("\n%s", content_and_first_char);
    print_padding_characters(content_and_first_char, length - 1, ' ');
    printf("%c\n", character);
    print_padding_characters(0, length, character);
    printf("\n");

    free(content_and_first_char);

    return 0;
}