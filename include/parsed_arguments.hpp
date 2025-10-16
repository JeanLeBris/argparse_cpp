#ifndef PARSED_ARGUMENTS_HPP
#define PARSED_ARGUMENTS_HPP

#include "../lib/deallocator/include/deallocator.hpp"
// #include "../include/subparser.hpp"
#include "../include/argument.hpp"

/**
 * The Argparse library, for C++
 */

namespace argparse{
    class ParsedArguments{
        private:
            char** keys;
            undefined_type* values;
            int* number_of_values;
            type* type_of_value;
            int length;
            deallocator::Garbage* garbage;

        public:
            ParsedArguments(deallocator::Garbage* garbage);

            int add_argument(char* key, int number_of_values, undefined_type values, type type_of_value);

            int change_argument(char* key, int number_of_values, undefined_type values, type type_of_value);

            int change_argument_array_value(char* key, int id_of_value, undefined_type value);

            bool is_key(const char* key);

            argparse::undefined_type get_value_by_key(const char* key);

            void print_keys();
            
            void print_keys_and_values();
    };
}

#endif