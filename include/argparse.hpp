#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include "../lib/deallocator/include/deallocator.hpp"

/**
 * The Argparse library, for C++
 */

namespace argparse{
    class Argument;
    class Subparser;
    class ArgumentParser;

    enum type{
        _int = 1,
        _float = 2,
        _double = 3,
        _bool = 4,
        _string = 5
    };

    union undefined_type{
        bool _bool;
        int _int;
        float _float;
        double _double;
        char* _string;
        undefined_type* _array;
    };

    struct SubparserElement{
        char* sub_command;
        char* help;
        ArgumentParser* parser;
        Subparser* parent_subparser;

        SubparserElement* previous;
        SubparserElement* next;
    };

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

            void print_keys();
            
            void print_keys_and_values();
    };

    class Argument{
        private:
            ArgumentParser* parent_parser;
            bool is_positional_argument;
            char* flags;
            char* action;
            int nargs;
            undefined_type constant;
            undefined_type default_value;
            type type_of_argument;
            int nchoices;
            undefined_type* choices;
            bool required;
            char* help;
            char* metavar;
            char* dest;
            bool deprecated;

            Argument* previous;
            Argument* next;

        public:
            Argument(ArgumentParser* parser, const char* flags, const char* action, int nargs, undefined_type constant, undefined_type default_value, type type_of_argument, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            Argument* getPrevious();
            void setPrevious(Argument* previous);

            Argument* getNext();
            void setNext(Argument* next);
            
            type getType();
            void setType(type type_of_argument);

            char* getDest();
            void setDest(char* dest);

            undefined_type getDefaultValue();
            void setDefaultValue(undefined_type default_value);
            
            char* getFlags();
            void setFlags(char* flags);
            
            int getNargs();
            void setNargs(int nargs);

            char* getAction();
            void setAction(char* action);

            ArgumentParser* getParentParser();
            void setParentParser(ArgumentParser* parent_parser);

            undefined_type getConstant();
            void setConstant(undefined_type constant);
            
            char* getHelp();
            void setHelp(char* help);
            
            int getNchoices();
            void setNchoices(int nchoices);
            
            undefined_type* getChoices();
            void setChoices(undefined_type* choices);
    };

    class Subparser{
        private:
            char* title;
            char* description;
            char* prog;
            // no parser_class yet
            char* action;
            char* dest;
            bool required;
            char* help;
            char* metavar;

            int n_parsers;

            ArgumentParser* parent_parser;

            SubparserElement* first_parser;
            SubparserElement* last_parser;

            Subparser* previous;
            Subparser* next;

        public:
            Subparser(ArgumentParser* parent_parser, const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet

            Subparser* getNext();
            void setNext(Subparser* next);

            Subparser* getPrevious();
            void setPrevious(Subparser* previous);

            char* getTitle();
            void setTitle(char* title);

            int getNparsers();
            void setNparsers(int n_parsers);

            bool getRequired();
            void setRequired(bool required);

            SubparserElement* getFirstParser();
            void setFirstParser(SubparserElement* first_parser);

            char* getHelp();
            void setHelp(char* help);

            ArgumentParser* add_parser(const char* sub_command, const char* help);

            SubparserElement* get_Nth_subparser_element(int n);
    };

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