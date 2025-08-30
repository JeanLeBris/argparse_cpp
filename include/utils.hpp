#ifndef UTILS_HPP
#define UTILS_HPP

int print_padding_characters(const char* string, int final_length, char padding_character);

int print_padding_characters(int string_len, int final_length, char padding_character);

char* alloc_and_copy_string(const char* input_string);

int print_title(const char* content, int length, char character);

#endif