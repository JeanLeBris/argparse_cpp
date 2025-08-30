#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include "../lib/deallocator/include/deallocator.hpp"
#include "../include/subparser.hpp"
#include "../include/argument.hpp"
#include "../include/parsed_arguments.hpp"

/**
 * The Argparse library, for C++
 */

namespace argparse{
    class Argument;
    class Subparser;
    class ArgumentParser;

    class ArgumentParser{
        private:
            char* prog;
            bool is_usage_auto;
            char* usage;
            char* description;
            char* epilog;
            ArgumentParser* parents;
            // no formatter class yet
            char* prefix_chars;
            char* fromfile_prefix_chars;
            char* version;
            // no argument_default yet
            // no conflict_handler yet
            bool add_help;
            bool allow_abbrev;
            bool exit_on_error;

            deallocator::Garbage* garbage;

            int n_arguments;
            int n_subparsers;

            Argument* first_argument;
            Argument* last_argument;

            Subparser* first_subparser;
            Subparser* last_subparser;

            int arg_flags_max_length;
            int arg_default_value_max_length;
            int arg_help_max_length;
            int arg_choices_max_length;

            void init(const char* prog, const char* usage, const char* description, const char* epilog, ArgumentParser* parents, const char* prefix_chars, const char* fromfile_prefix_chars, const char* version, bool add_help, bool allow_abbrev, bool exit_on_error); // no formatter_class, argument_default or conflict_handler yet

            int add_argument(const char* flags, const char* action, int nargs, undefined_type constant, undefined_type default_value, type type_of_argument, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            ParsedArguments* prepare_subparsers_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);
            ParsedArguments* parse_subparsers(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);
            ParsedArguments* prepare_arguments_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);
            ParsedArguments* parse_arguments(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            int print_help();
            int print_version();

        public:
            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog, ArgumentParser* parents, const char* prefix_chars, const char* fromfile_prefix_chars, const char* version, bool add_help, bool allow_abbrev, bool exit_on_error); // no formatter_class, argument_default or conflict_handler yet
            ArgumentParser(ArgumentParser* parser);
            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog);

            ~ArgumentParser();

            char* getPrefixChars();
            void setPrefixChars(char* prefix_chars);

            deallocator::Garbage* getGarbage();
            void setGarbage(deallocator::Garbage* garbage);

            int add_argument(const char* flags, const char* action, int nargs, int constant, int default_value, const char* type, int nchoices, int* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);
            int add_argument(const char* flags, const char* action, int nargs, float constant, float default_value, const char* type, int nchoices, float* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);
            int add_argument(const char* flags, const char* action, int nargs, double constant, double default_value, const char* type, int nchoices, double* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);
            int add_argument(const char* flags, const char* action, int nargs, const char* constant, const char* default_value, const char* type, int nchoices, const char* choices[], bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            Argument* get_Nth_argument(int n);

            Subparser* add_subparsers(const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet
            
            Subparser* get_Nth_subparser(int n);

            ParsedArguments* parse_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);
            ParsedArguments* parse_args(int argc, char** argv);
    };
}

#endif