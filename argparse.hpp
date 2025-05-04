#include <iostream>
#include <string.h>
#include "./lib/utils.hpp"

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
        undefined_type* undefined_object;
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

        public:
            char** keys;
            undefined_type* values;
            int* number_of_values;
            type* type_of_value;
            int length;

            ParsedArguments();

            int add_argument(char* key, int number_of_values, undefined_type values, type type_of_value);

            int change_argument(char* key, int number_of_values, undefined_type values, type type_of_value);

            bool is_key(const char* key);

            void print_keys();
            
            void print_keys_and_values();
    };

    class Argument{
        private:

        public:
            bool is_positional_argument;
            char* flags;
            char* action;
            int nargs;
            undefined_type constant;
            undefined_type default_value;
            char* type;
            int nchoices;
            undefined_type* choices;
            bool required;
            char* help;
            char* metavar;
            char* dest;
            bool deprecated;

            Argument* previous;
            Argument* next;

            Argument(ArgumentParser* parser, const char* flags, const char* action, int nargs, undefined_type constant, undefined_type default_value, const char* type, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);
    };

    class Subparser{
        private:
        
        public:
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

            Subparser(ArgumentParser* parent_parser, const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet

            ArgumentParser* add_parser(const char* sub_command, const char* help);

            SubparserElement* get_Nth_subparser_element(int n);
    };

    class ArgumentParser{
        // parser();
        private:

        public:
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
            
            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog, ArgumentParser* parents, const char* prefix_chars, const char* fromfile_prefix_chars, const char* version, bool add_help, bool allow_abbrev, bool exit_on_error); // no formatter_class, argument_default or conflict_handler yet

            ArgumentParser(ArgumentParser* parser);

            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog);

            int add_argument(const char* flags, const char* action, int nargs, undefined_type constant, undefined_type default_value, const char* type, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            int add_argument(const char* flags, const char* action, int nargs, int constant, int default_value, const char* type, int nchoices, int* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            int add_argument(const char* flags, const char* action, int nargs, const char* constant, const char* default_value, const char* type, int nchoices, const char* choices[], bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            Argument* get_Nth_argument(int n);

            Subparser* add_subparsers(const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet
            
            Subparser* get_Nth_subparser(int n);

            ParsedArguments* prepare_subparsers_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            ParsedArguments* parse_subparsers(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            ParsedArguments* prepare_arguments_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            ParsedArguments* parse_arguments(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            ParsedArguments* parse_args(int argc, char** argv, ParsedArguments* parsed_arguments, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array);

            int print_help();

            int print_version();
    };

    // struct ArgumentParserArgs{
    //     char* prog = "Program Name";
    //     char* description = "What the program does";
    //     char* epilog = "Text at the bottom of help";
    // };

    ParsedArguments::ParsedArguments(){
        this->keys = NULL;
        this->values = NULL;
        this->number_of_values = NULL;
        this->type_of_value = NULL;
        this->length = 0;
    }

    void ParsedArguments::print_keys(){
        for(int i = 0; i < this->length; i++){
            printf("%s\n", this->keys[i]);
        }
    }

    void ParsedArguments::print_keys_and_values(){
        for(int i = 0; i < this->length; i++){
            printf("%s\t", this->keys[i]);

            if(this->number_of_values[i] == 0){
                printf("None");
            }
            else if(this->number_of_values[i] == 1){
                switch(this->type_of_value[i]){
                    case _int:
                        printf("%d", this->values[i]._int);
                        break;
                    case _float:
                        printf("%f", this->values[i]._float);
                        break;
                    case _double:
                        printf("%f", this->values[i]._double);
                        break;
                    case _bool:
                        printf(this->values[i]._bool == true ? "true" : "false");
                        break;
                    case _string:
                        printf("%s", this->values[i]._string);
                        break;
                }
            }
            else{
                for(int j = 0; j < this->number_of_values[i]; j++){
                    switch(this->type_of_value[i]){
                        case _int:
                            printf("%d", this->values[i].undefined_object[j]._int);
                            break;
                        case _float:
                            printf("%f", this->values[i].undefined_object[j]._float);
                            break;
                        case _double:
                            printf("%f", this->values[i].undefined_object[j]._double);
                            break;
                        case _bool:
                            printf(this->values[i].undefined_object[j]._bool == true ? "true" : "false");
                            break;
                        case _string:
                            printf("%s", this->values[i].undefined_object[j]._string);
                            break;
                    }
                }
            }
            printf("\n");
        }
    }

    int ParsedArguments::add_argument(char* key, int number_of_values, undefined_type values, type type_of_value){
        if(this->keys == NULL){
            this->keys = (char**) malloc(sizeof(char*) * 1);
        }
        else{
            this->keys = (char**) realloc(this->keys, sizeof(char*) * (this->length + 1));
        }

        if(this->number_of_values == NULL){
            this->number_of_values = (int*) malloc(sizeof(int) * 1);
        }
        else{
            this->number_of_values = (int*) realloc(this->number_of_values, sizeof(int) * (this->length + 1));
        }

        if(this->type_of_value == NULL){
            this->type_of_value = (type*) malloc(sizeof(type) * 1);
        }
        else{
            this->type_of_value = (type*) realloc(this->type_of_value, sizeof(type) * (this->length + 1));
        }

        if(this->values == NULL){
            this->values = (undefined_type*) malloc(sizeof(undefined_type) * 1);
        }
        else{
            this->values = (undefined_type*) realloc(this->values, sizeof(undefined_type) * (this->length + 1));
        }

        this->keys[this->length] = key;
        this->number_of_values[this->length] = number_of_values;
        this->type_of_value[this->length] = type_of_value;
        this->values[this->length] = values;
        this->length++;

        return 0;
    }

    int ParsedArguments::change_argument(char* key, int number_of_values, undefined_type values, type type_of_value){
        int id = -1;

        for(int i = 0; i < this->length; i++){
            if(strcmp(this->keys[i], key) == 0){
                id = i;
            }
        }

        if(id == -1){
            return 1;
        }

        if(this->number_of_values[id] > 1){
            free(this->values[id].undefined_object);
        }

        this->number_of_values[id] = number_of_values;

        this->type_of_value[id] = type_of_value;

        this->values[id] = values;

        return 0;
    }

    bool ParsedArguments::is_key(const char* key){
        for(int i = 0; i < this->length; i++){
            if(strcmp(this->keys[i], key) == 0){
                return true;
            }
        }

        return false;
    }

    Argument::Argument(ArgumentParser* parser,
                       const char* flags,
                       const char* action,
                       int nargs,
                       undefined_type constant,
                       undefined_type default_value,
                       const char* type,
                       int nchoices,
                       undefined_type* choices,
                       bool required,
                       const char* help,
                       const char* metavar,
                       const char* dest,
                       bool deprecated){
        bool store_true_false = false;
        char* char_ptr = NULL;
        char* string_copy = NULL;
        if(flags == NULL){
            printf("Flags are necessary to declare a new argument");
            exit(1);
        }
        this->is_positional_argument = false;
        for(int i = 0; i < strlen(flags); i++){ // look at wtf happens here
            if(strchr(parser->prefix_chars, flags[i]) == NULL){
                this->is_positional_argument = true;
            }
            while(flags[i] != ' ' && flags[i] != '\0'){
                i++;
            }
        }
        if(this->is_positional_argument && strchr(flags, ' ') != NULL){
            printf("A positional argument can only have one flag\n");
            exit(1);
        }
        this->flags = alloc_and_copy_string(flags);
        this->action = alloc_and_copy_string(action);
        if(this->action == NULL){
            this->action = alloc_and_copy_string("store");
        }
        if(strcmp(this->action, "store") == 0){
            
        }
        else if(strcmp(this->action, "store_const") == 0){
            
        }
        else if(strcmp(this->action, "store_true") == 0){
            free(this->action);
            this->action = alloc_and_copy_string("store_const");
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type = alloc_and_copy_string("bool");
        }
        else if(strcmp(this->action, "store_false") == 0){
            free(this->action);
            this->action = alloc_and_copy_string("store_const");
            this->default_value._bool = true;
            this->constant._bool = false;
            store_true_false = true;
            this->type = alloc_and_copy_string("bool");
        }
        // else if(strcmp(this->action, "append") == 0){
            
        // }
        // else if(strcmp(this->action, "append_const") == 0){
            
        // }
        // else if(strcmp(this->action, "extend") == 0){
            
        // }
        // else if(strcmp(this->action, "count") == 0){
            
        // }
        else if(strcmp(this->action, "help") == 0){
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type = alloc_and_copy_string("bool");
        }
        else if(strcmp(this->action, "version") == 0){
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type = alloc_and_copy_string("bool");
        }
        else{
            printf("The action argument value must be a correct value or none at all");
            exit(1);
        }
        this->nargs = nargs;
        if(!store_true_false){
            this->constant = constant;
            this->default_value = default_value;
            this->type = alloc_and_copy_string(type);
        }
        // this->nchoices = nchoices;
        // no choices management for now
        this->nchoices = nchoices;
        this->choices = choices;
        this->required = required;
        this->help = alloc_and_copy_string(help);
        this->metavar = alloc_and_copy_string(metavar);
        if(dest == NULL){
            char_ptr = this->flags;
            for(char_ptr = this->flags; strchr(char_ptr, ' ') != NULL; char_ptr = strchr(char_ptr, ' ') + 1);
            for(char_ptr = char_ptr; strchr(parser->prefix_chars, *char_ptr) != NULL; char_ptr++);
            this->dest = alloc_and_copy_string(char_ptr);
        }
        else{
            this->dest = alloc_and_copy_string(dest);
        }
        this->deprecated = deprecated;

        this->previous = NULL;
        this->next = NULL;
    }
    
    Subparser::Subparser(ArgumentParser* parent_parser,
                         const char* title,
                         const char* description,
                         const char* prog,
                         // no parser_class yet
                         const char* action,
                         const char* dest,
                         bool required,
                         const char* help,
                         const char* metavar){
        this->parent_parser = parent_parser;
        this->title = alloc_and_copy_string(title);
        this->description = alloc_and_copy_string(description);
        this->prog = alloc_and_copy_string(prog);
        this->action = alloc_and_copy_string(action);
        this->dest = alloc_and_copy_string(dest);
        this->required = required;
        this->help = alloc_and_copy_string(help);
        this->metavar = alloc_and_copy_string(metavar);

        this->n_parsers = 0;
        
        this->first_parser = NULL;
        this->last_parser = NULL;

        this->previous = NULL;
        this->next = NULL;
    }
    
    /**
    * Add a parser to the subparser
    * 
    * @param sub_command Sub-command of the new parser
    * @param help Help to display for the new parser
    * 
    * @return ArgumentParser
    */
    ArgumentParser* Subparser::add_parser(const char* sub_command, const char* help){
        SubparserElement* subparser_element = new SubparserElement;
        subparser_element->parser = new ArgumentParser(this->parent_parser);
        subparser_element->parent_subparser = this;
        // subparser_element->sub_command = NULL;
        if(sub_command == NULL){
            printf("To add a parser to a sub-parser, a sub-command is necessary");
            exit(1);
        }
        subparser_element->sub_command = alloc_and_copy_string(sub_command);
        // subparser_element->help = NULL;
        subparser_element->help = alloc_and_copy_string(help);
        subparser_element->previous = NULL;
        subparser_element->next = NULL;
        
        if(this->first_parser == NULL){
            this->first_parser = subparser_element;
            this->last_parser = subparser_element;
        }
        else{
            this->last_parser->next = subparser_element;
            subparser_element->previous = this->last_parser;
            this->last_parser = subparser_element;
        }

        this->n_parsers++;

        return subparser_element->parser;
    }

    SubparserElement* Subparser::get_Nth_subparser_element(int n){
        SubparserElement* parser = this->first_parser;
        for(int i = 0; i < (n < this->n_parsers - 1 ? n : this->n_parsers - 1); i++){
            parser = parser->next;
        }

        return parser;
    }
    
    void ArgumentParser::init(const char* prog,
                              const char* usage,
                              const char* description,
                              const char* epilog,
                              ArgumentParser* parents,
                              // formatter_class,
                              const char* prefix_chars,
                              const char* fromfile_prefix_chars,
                              const char* version,
                              // unknown_type argument_default,
                              // conflict_handler,
                              bool add_help,
                              bool allow_abbrev,
                              bool exit_on_error){
        const char* prog_reformatted = NULL;
        if(prog == NULL){
            printf("A program name is necessary to produce an argument parser");
            exit(1);
        }
        for(prog_reformatted = prog + (strlen(prog) - 1); prog_reformatted != prog-1 && *prog_reformatted != '/'; prog_reformatted--);
        prog = prog_reformatted+1;
        for(prog_reformatted = prog + (strlen(prog) - 1); prog_reformatted != prog-1 && *prog_reformatted != '\\'; prog_reformatted--);
        prog = prog_reformatted+1;
        this->prog = alloc_and_copy_string(prog);
        this->usage = alloc_and_copy_string(usage); // auto build to make
        if(usage == NULL){
            this->is_usage_auto = true;
            this->usage = (char*) malloc(sizeof(char) * (strlen(this->prog) + 1));
            strcpy(this->usage, this->prog);
        }
        else{
            this->is_usage_auto = false;
        }
        this->description = alloc_and_copy_string(description);
        this->epilog = alloc_and_copy_string(epilog);

        // this->prefix_chars = (char*) malloc(sizeof(char)*2);

        this->parents = parents;
        this->prefix_chars = alloc_and_copy_string(prefix_chars);
        this->fromfile_prefix_chars = alloc_and_copy_string(fromfile_prefix_chars);
        this->version = alloc_and_copy_string(version);
        // unknown_type argument_default = {NULL};
        // this->argument_default = argument_default;
        this->add_help = add_help;
        this->allow_abbrev = allow_abbrev;
        this->exit_on_error = exit_on_error;

        this->n_arguments = 0;
        this->n_subparsers = 0;

        this->first_argument = NULL;
        this->last_argument = NULL;

        this->first_subparser = NULL;
        this->last_subparser = NULL;

        char help_flags[20] = "";
        sprintf(help_flags, "%ch %c%chelp", this->prefix_chars[0], this->prefix_chars[0], this->prefix_chars[0]);
        if(this->add_help){
            this->add_argument(help_flags, "help", 1, 0, 0, "int", 0, NULL, false, "display the help of the program", "metavar", NULL, 0);
        }
    }

    /**
     * Declares a new arguments parser
     * 
     * @param prog Name of the program
     * @param usage Describes the usage of the program's arguments
     * @param description Describes what the program does
     * @param epilog Message displayed at the end of the help
     * @param parents not done
     * @param prefix_chars not done
     * @param fromfile_prefix_chars not done
     * @param version Version of the program
     * @param add_help not done
     * @param allow_abbrev not done
     * @param exit_on_error not done
     * 
     * @return Argument parser
     */
    ArgumentParser::ArgumentParser(const char* prog,
                                   const char* usage,
                                   const char* description,
                                   const char* epilog,
                                   ArgumentParser* parents,
                                   // formatter_class,
                                   const char* prefix_chars,
                                   const char* fromfile_prefix_chars,
                                   const char* version,
                                   // unknown_type argument_default,
                                   // conflict_handler,
                                   bool add_help,
                                   bool allow_abbrev,
                                   bool exit_on_error){
        init(prog, usage, description, epilog, parents, prefix_chars, fromfile_prefix_chars, version, add_help, allow_abbrev, exit_on_error);
    }

    /**
     * Declares a new arguments parser
     * 
     * @param parser Input parser to copy
     * 
     * @return Argument parser
     */
    ArgumentParser::ArgumentParser(ArgumentParser* parser){
        if(parser->is_usage_auto){
            init(parser->prog, NULL, parser->description, parser->epilog, parser, parser->prefix_chars, parser->fromfile_prefix_chars, parser->version, parser->add_help, parser->allow_abbrev, parser->exit_on_error);
        }
        else{
            init(parser->prog, parser->usage, parser->description, parser->epilog, parser, parser->prefix_chars, parser->fromfile_prefix_chars, parser->version, parser->add_help, parser->allow_abbrev, parser->exit_on_error);
        }
    }

    /**
     * Declares a new arguments parser
     * 
     * @param prog Name of the program
     * @param usage Describes the usage of the program's arguments
     * @param description Describes what the program does
     * @param epilog Message displayed at the end of the help
     * 
     * @return Argument parser
     */
    ArgumentParser::ArgumentParser(const char* prog,
                                   const char* usage,
                                   const char* description,
                                   const char* epilog){
        init(prog, usage, description, epilog, NULL, "-", NULL, "0.0.0", true, true, true);
    }

    /**
     * Add a new argument to the argument parser
     * 
     * @param flags The flags of the argument, separated by spaces
     * @param action The basic of action to be taken when this argument is encountered at the command line
     * @param nargs The number of command-line arguments that should be consumed
     * @param constant A constant value required by some ```action``` and ```nargs``` selections
     * @param default_value The value produced if the argument is absent from the command line and if it is absent from the namespace object
     * @param type The type to which the command-line argument should be converted
     * @param choices A sequence of the allowable values for the argument
     * @param required Whether or not the command-line option may be omitted
     * @param help A brief description of what the argument does
     * @param metavar A name for the argument in usage messages
     * @param dest The name of the attribute to be added to the object returned by ```parse_args()```
     * @param deprecated Whether or not use of the argument is deprecated
     * 
     * @return 0 if all goes well
     */
    int ArgumentParser::add_argument(const char* flags,
                                     const char* action,
                                     int nargs,
                                     undefined_type constant,
                                     undefined_type default_value,
                                     const char* type,
                                     int nchoices,
                                     undefined_type* choices,
                                     bool required,
                                     const char* help,
                                     const char* metavar,
                                     const char* dest,
                                     bool deprecated){
        Argument* argument = new Argument(this, flags, action, nargs, constant, default_value, type, nchoices, choices,
                                            required, help, metavar, dest, deprecated);
        
        if(this->first_argument == NULL){
            this->first_argument = argument;
            this->last_argument = argument;
        }
        else{
            this->last_argument->next = argument;
            argument->previous = this->last_argument;
            this->last_argument = argument;
        }

        // TODO Update the usage modifier to make it ok (not really ok rn)
        char* usage_buffer = NULL;
        char* flag = NULL;
        int flag_size = 0;
        if(this->is_usage_auto){
            usage_buffer = this->usage;
            for(flag_size = 0; flag_size < strlen(flags) && flags[flag_size] != ' '; flag_size++);
            flag = (char*) malloc(sizeof(char) * (flag_size + 1));
            for(flag_size = 0; flag_size < strlen(flags) && flags[flag_size] != ' '; flag_size++){
                flag[flag_size] = flags[flag_size];
            }
            flag[flag_size] = '\0';
            // strcpy_s(flag, flag_size, usage_buffer);
            if(required){
                this->usage = (char*) malloc(sizeof(char) * (strlen(usage_buffer) + flag_size + 1));
                sprintf(this->usage, "%s %s", usage_buffer, flag);
            }
            else{
                this->usage = (char*) malloc(sizeof(char) * (strlen(usage_buffer) + flag_size + 3));
                sprintf(this->usage, "%s [%s]", usage_buffer, flag);
            }
            free(usage_buffer);
            free(flag);
        }

        this->n_arguments++;

        return 0;
    }

    /**
     * Add a new argument to the argument parser
     * 
     * @param flags The flags of the argument, separated by spaces
     * @param action The basic of action to be taken when this argument is encountered at the command line
     * @param nargs The number of command-line arguments that should be consumed
     * @param constant A constant value required by some ```action``` and ```nargs``` selections
     * @param default_value The value produced if the argument is absent from the command line and if it is absent from the namespace object
     * @param type The type to which the command-line argument should be converted
     * @param choices A sequence of the allowable values for the argument
     * @param required Whether or not the command-line option may be omitted
     * @param help A brief description of what the argument does
     * @param metavar A name for the argument in usage messages
     * @param dest The name of the attribute to be added to the object returned by ```parse_args()```
     * @param deprecated Whether or not use of the argument is deprecated
     * 
     * @return 0 if all goes well
     */
    int ArgumentParser::add_argument(const char* flags,
                                     const char* action,
                                     int nargs,
                                     int constant,
                                     int default_value,
                                     const char* type,
                                     int nchoices,
                                     int* choices,
                                     bool required,
                                     const char* help,
                                     const char* metavar,
                                     const char* dest,
                                     bool deprecated){
        undefined_type casted_constant = {._int = constant};
        undefined_type casted_default_value = {._int = default_value};
        undefined_type* casted_choices = NULL;
        if(nchoices > 0){
            casted_choices = (undefined_type*) malloc(sizeof(undefined_type) * nchoices);
            for(int i = 0; i < nchoices; i++){
                casted_choices[i] = {._int = choices[i]};
            }
        }
        int result = this->add_argument(flags, action, nargs, casted_constant, casted_default_value, type, nchoices, casted_choices, required, help, metavar, dest, deprecated);
        
        return result;
    }
    
    /**
     * Add a new argument to the argument parser
     * 
     * @param flags The flags of the argument, separated by spaces
     * @param action The basic of action to be taken when this argument is encountered at the command line
     * @param nargs The number of command-line arguments that should be consumed
     * @param constant A constant value required by some ```action``` and ```nargs``` selections
     * @param default_value The value produced if the argument is absent from the command line and if it is absent from the namespace object
     * @param type The type to which the command-line argument should be converted
     * @param choices A sequence of the allowable values for the argument
     * @param required Whether or not the command-line option may be omitted
     * @param help A brief description of what the argument does
     * @param metavar A name for the argument in usage messages
     * @param dest The name of the attribute to be added to the object returned by ```parse_args()```
     * @param deprecated Whether or not use of the argument is deprecated
     * 
     * @return 0 if all goes well
     */
    int ArgumentParser::add_argument(const char* flags,
                                     const char* action,
                                     int nargs,
                                     const char* constant,
                                     const char* default_value,
                                     const char* type,
                                     int nchoices,
                                     const char* choices[],
                                     bool required,
                                     const char* help,
                                     const char* metavar,
                                     const char* dest,
                                     bool deprecated){
        undefined_type casted_constant = {._string = alloc_and_copy_string(constant)};
        undefined_type casted_default_value = {._string = alloc_and_copy_string(default_value)};
        undefined_type* casted_choices = NULL;
        if(nchoices > 0){
            casted_choices = (undefined_type*) malloc(sizeof(undefined_type) * nchoices);
            for(int i = 0; i < nchoices; i++){
                casted_choices[i] = {._string = alloc_and_copy_string(choices[i])};
            }
        }
        int result = this->add_argument(flags, action, nargs, casted_constant, casted_default_value, type, nchoices, casted_choices, required, help, metavar, dest, deprecated);
        
        return result;
    }

    Argument* ArgumentParser::get_Nth_argument(int n){
        Argument* argument = this->first_argument;
        for(int i = 0; i < (n < this->n_arguments - 1 ? n : this->n_arguments - 1); i++){
            argument = argument->next;
        }

        return argument;
    }
    
    /**
     * Adds a new subparser to the argument parser
     * 
     * @param title Title for the sub-parser group in help output
     * @param description Description for the sub-parser group in help output
     * @param prog Usage information that will be displayed with sub-command help
     * @param action The basic type of action to be taken when this argument is encountered at the command line
     * @param dest Name of the attribute under which sub-command name will be stored
     * @param required Whether or not a subcommand must be provided
     * @param help Help for sub-parser group in help output
     * @param metavar String presenting available subcommands in help
     * 
     * @return Subparser
     */
    Subparser* ArgumentParser::add_subparsers(const char* title,
                                              const char* description,
                                              const char* prog,
                                              // no parser_class yet
                                              const char* action,
                                              const char* dest,
                                              bool required,
                                              const char* help,
                                              const char* metavar){
        Subparser* subparser = new Subparser(this, title, description, prog, action, dest, required, help, metavar);
        if(this->first_subparser == NULL){
            this->first_subparser = subparser;
            this->last_subparser = this->first_subparser;
        }
        else{
            this->last_subparser->next = subparser;
            subparser->previous = this->last_subparser;
            this->last_subparser = subparser;
        }

        this->n_subparsers++;

        return subparser;
    }

    Subparser* ArgumentParser::get_Nth_subparser(int n){
        Subparser* subparser = this->first_subparser;
        for(int i = 0; i < (n < this->n_subparsers - 1 ? n : this->n_subparsers - 1); i++){
            subparser = subparser->next;
        }

        return subparser;
    }

    ParsedArguments* ArgumentParser::prepare_subparsers_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_args, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array){
        Subparser* subparser_ptr = NULL;
        SubparserElement* subparser_element_ptr = NULL;

        for(int j = 0; j < this->n_subparsers; j++){ // read in each subparsers
            subparser_ptr = this->get_Nth_subparser(j);
            parsed_args->add_argument(subparser_ptr->title, 0, (undefined_type) {._string = NULL}, _string);
            for(int k = 0; k < subparser_ptr->n_parsers; k++){ // read in each subparsers' parsers
                subparser_element_ptr = subparser_ptr->get_Nth_subparser_element(k);
                parsed_args = subparser_element_ptr->parser->prepare_subparsers_in_parsed_args(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);
            }
        }

        return parsed_args;
    }

    ParsedArguments* ArgumentParser::parse_subparsers(int argc, char** argv, ParsedArguments* parsed_args = NULL, bool* args_processed = NULL, int* subparser_element_array_length = NULL, SubparserElement*** subparser_element_array = NULL){
        if(parsed_args == NULL){
            parsed_args = (ParsedArguments*) malloc(sizeof(ParsedArguments));
        }
        if(args_processed == NULL){
            args_processed = (bool*) malloc(sizeof(bool) * argc);
            for(int i = 0; i < argc; i++){
                args_processed[i] = false;
            }
        }
        char* char_ptr = NULL;
        Subparser* subparser_ptr = NULL;
        if(subparser_element_array == NULL){
            subparser_element_array_length = (int*) malloc(sizeof(int) * 1);
            *subparser_element_array_length = 0;
            subparser_element_array = (SubparserElement***) malloc(sizeof(SubparserElement**) * 1);
            *subparser_element_array = (SubparserElement**) malloc(sizeof(SubparserElement*) * 0);
        }
        SubparserElement* subparser_element_ptr = NULL;
        bool required = false;
        bool found = false;
        bool stopping = false;
        char* instance_ptr = NULL;
        char* key = NULL;
        char* value = NULL;
        undefined_type* values = NULL;

        for(int i = 1; i < argc && !stopping; i++){ // read every arguments
            if(!args_processed[i]){
                found = false;
                char_ptr = argv[i];
                for(int j = 0; j < this->n_subparsers; j++){ // read in each subparsers
                    subparser_ptr = this->get_Nth_subparser(j);
                    required = subparser_ptr->required;
                    for(int k = 0; k < subparser_ptr->n_parsers; k++){ // read in each subparsers' parsers
                        subparser_element_ptr = subparser_ptr->get_Nth_subparser_element(k);
                        if((instance_ptr = strstr(subparser_element_ptr->sub_command, char_ptr)) != NULL){
                            if(instance_ptr == subparser_element_ptr->sub_command && instance_ptr[strlen(char_ptr)] == '\0'){ // if the command is of the subparser's parser
                                for(int x = 0; x < *subparser_element_array_length; x++){
                                    if(subparser_element_ptr->parent_subparser == (*subparser_element_array)[x]->parent_subparser){
                                        printf("A subparser can only be referenced one time");
                                        exit(1);
                                    }
                                }
                                found = true;
                                (*subparser_element_array_length)++;
                                *subparser_element_array = (SubparserElement**) realloc(*subparser_element_array, sizeof(SubparserElement*) * (*subparser_element_array_length));
                                (*subparser_element_array)[*subparser_element_array_length-1] = subparser_element_ptr;
                                args_processed[i] = true;

                                parsed_args->change_argument(subparser_element_ptr->parent_subparser->title, 1, (undefined_type) {._string = subparser_element_ptr->sub_command}, _string);

                                parsed_args = subparser_element_ptr->parser->parse_subparsers(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);
                            }
                        }
                    }
                }
                if(!found){
                    stopping = true;
                }
            }
        }

        return parsed_args;
    }

    ParsedArguments* ArgumentParser::prepare_arguments_in_parsed_args(int argc, char** argv, ParsedArguments* parsed_args, bool* args_processed, int* subparser_element_array_length, SubparserElement*** subparser_element_array){
        Argument* argument_ptr = NULL;
        SubparserElement* subparser_element_ptr = NULL;
        char* char_ptr = NULL;

        for(int i = *subparser_element_array_length - 1; i >= 0; i--){ // read in each subparsers' parsers
            subparser_element_ptr = (*subparser_element_array)[i];

            for(int j = 0; j < subparser_element_ptr->parser->n_arguments; j++){
                argument_ptr = subparser_element_ptr->parser->get_Nth_argument(j);

                if(!parsed_args->is_key(argument_ptr->dest)){
                    if(strcmp(argument_ptr->type, "string") == 0){
                        parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._string = argument_ptr->default_value._string}, _string);
                    }
                    else if(strcmp(argument_ptr->type, "int") == 0){
                        parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._int = argument_ptr->default_value._int}, _int);
                    }
                    else if(strcmp(argument_ptr->type, "bool") == 0){
                        parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._bool = argument_ptr->default_value._bool}, _bool);
                    }
                }
            }
        }

        for(int j = 0; j < this->n_arguments; j++){
            argument_ptr = this->get_Nth_argument(j);
            if(!parsed_args->is_key(argument_ptr->dest)){
                if(strcmp(argument_ptr->type, "string") == 0){
                    parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._string = argument_ptr->default_value._string}, _string);
                }
                else if(strcmp(argument_ptr->type, "int") == 0){
                    parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._int = argument_ptr->default_value._int}, _int);
                }
                else if(strcmp(argument_ptr->type, "bool") == 0){
                    parsed_args->add_argument(argument_ptr->dest, 1, (undefined_type) {._bool = argument_ptr->default_value._bool}, _bool);
                }
            }
        }

        return parsed_args;
    }

    // ParsedArguments* ArgumentParser::parse_arguments(int argc, char** argv, ParsedArguments* parsed_args = NULL, bool* args_processed = NULL, int* subparser_element_array_length = NULL, SubparserElement*** subparser_element_array = NULL){
    //     if(parsed_args == NULL){
    //         parsed_args = (ParsedArguments*) malloc(sizeof(ParsedArguments));
    //     }
    //     if(args_processed == NULL){
    //         args_processed = (bool*) malloc(sizeof(bool) * argc);
    //         for(int i = 0; i < argc; i++){
    //             args_processed[i] = false;
    //         }
    //     }
    //     char* char_ptr = NULL;
    //     Subparser* subparser_ptr = NULL;
    //     if(subparser_element_array == NULL){
    //         subparser_element_array_length = (int*) malloc(sizeof(int) * 1);
    //         *subparser_element_array_length = 0;
    //         subparser_element_array = (SubparserElement***) malloc(sizeof(SubparserElement**) * 1);
    //         *subparser_element_array = (SubparserElement**) malloc(sizeof(SubparserElement*) * 0);
    //     }
    //     SubparserElement* subparser_element_ptr = NULL;
    //     bool required = false;
    //     bool found = false;
    //     bool stopping = false;
    //     char* instance_ptr = NULL;
    //     char* key = NULL;
    //     char* value = NULL;
    //     undefined_type* values = NULL;

    //     for(int i = 1; i < argc && !stopping; i++){ // read every arguments
    //         if(!args_processed[i]){
    //             found = false;
    //             char_ptr = argv[i];
    //             for(int j = 0; j < this->n_subparsers; j++){ // read in each subparsers
    //                 subparser_ptr = this->get_Nth_subparser(j);
    //                 required = subparser_ptr->required;
    //                 for(int k = 0; k < subparser_ptr->n_parsers; k++){ // read in each subparsers' parsers
    //                     subparser_element_ptr = subparser_ptr->get_Nth_subparser_element(k);
    //                     if((instance_ptr = strstr(subparser_element_ptr->sub_command, char_ptr)) != NULL){
    //                         if(instance_ptr == subparser_element_ptr->sub_command && instance_ptr[strlen(char_ptr)] == '\0'){ // if the command is of the subparser's parser
    //                             for(int x = 0; x < *subparser_element_array_length; x++){
    //                                 if(subparser_element_ptr->parent_subparser == (*subparser_element_array)[x]->parent_subparser){
    //                                     printf("A subparser can only be referenced one time");
    //                                     exit(1);
    //                                 }
    //                             }
    //                             found = true;
    //                             (*subparser_element_array_length)++;
    //                             *subparser_element_array = (SubparserElement**) realloc(*subparser_element_array, sizeof(SubparserElement*) * (*subparser_element_array_length));
    //                             (*subparser_element_array)[*subparser_element_array_length-1] = subparser_element_ptr;
    //                             args_processed[i] = true;

    //                             parsed_args->change_argument(subparser_element_ptr->parent_subparser->title, 1, (undefined_type) {._string = subparser_element_ptr->sub_command}, _string);

    //                             parsed_args = subparser_element_ptr->parser->parse_subparsers(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);
    //                         }
    //                     }
    //                 }
    //             }
    //             if(!found){
    //                 stopping = true;
    //             }
    //         }
    //     }

    //     return parsed_args;
    // }

    /**
     * Parse arguments
     * 
     * @param argc The amount of arguments
     * @param argv The arguments
     * 
     * @return The parsed arguments
     */
    ParsedArguments* ArgumentParser::parse_args(int argc, char** argv, ParsedArguments* parsed_args = NULL, bool* args_processed = NULL, int* subparser_element_array_length = NULL, SubparserElement*** subparser_element_array = NULL){
        if(parsed_args == NULL){
            parsed_args = (ParsedArguments*) malloc(sizeof(ParsedArguments));
        }
        if(args_processed == NULL){
            args_processed = (bool*) malloc(sizeof(bool) * argc);
            for(int i = 0; i < argc; i++){
                args_processed[i] = false;
            }
        }
        char* char_ptr = NULL;
        Subparser* subparser_ptr = NULL;
        if(subparser_element_array == NULL){
            subparser_element_array_length = (int*) malloc(sizeof(int) * 1);
            *subparser_element_array_length = 0;
            subparser_element_array = (SubparserElement***) malloc(sizeof(SubparserElement**) * 1);
            *subparser_element_array = (SubparserElement**) malloc(sizeof(SubparserElement*) * 0);
        }
        SubparserElement* subparser_element_ptr = NULL;
        bool required = false;
        bool found = false;
        bool stopping = false;
        char* instance_ptr = NULL;
        char* key = NULL;
        char* value = NULL;

        parsed_args = this->prepare_subparsers_in_parsed_args(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);

        parsed_args = this->parse_subparsers(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);

        // printf("%d\n", *subparser_element_array_length);
        // for(int i = 0; i < *subparser_element_array_length; i++){
        //     printf("%d\n", (*subparser_element_array)[i]);
        // }

        parsed_args = this->prepare_arguments_in_parsed_args(argc, argv, parsed_args, args_processed, subparser_element_array_length, subparser_element_array);

        return parsed_args;
    }

    /**
     * Display the argument parser's help
     */
    int ArgumentParser::print_help(){
        int arg_flags_max_length = strlen("FLAGS");
        int arg_default_value_max_length = strlen("DEFAULT");
        int arg_help_max_length = strlen("HELP");

        int sub_flags_max_length = strlen("FLAGS");
        int sum = 0;
        // int sub_help_max_length = strlen("HELP");

        char string_buffer[20] = "";

        for(Argument* argument = this->first_argument; argument != NULL; argument = argument->next){
            if(strlen(argument->flags) > arg_flags_max_length){
                arg_flags_max_length = strlen(argument->flags);
            }
            if(strcmp(argument->type, "string") == 0){
                if(argument->default_value._string != NULL && strlen(argument->default_value._string) > arg_default_value_max_length){
                    arg_default_value_max_length = strlen(argument->default_value._string);
                }
            }
            else if(strcmp(argument->type, "int") == 0){
                itoa(argument->default_value._int, string_buffer, 10);
                if(strlen(string_buffer) > arg_default_value_max_length){
                    arg_default_value_max_length = strlen(string_buffer);
                }
            }
            else if(strcmp(argument->type, "bool") == 0){
                if(strlen(argument->default_value._bool ? "True" : "False") > arg_default_value_max_length){
                    arg_default_value_max_length = strlen(argument->default_value._bool ? "True" : "False");
                }
            }
            if(strlen(argument->help) > arg_help_max_length){
                arg_help_max_length = strlen(argument->help);
            }
        }

        printf("\nusage : %s\n\n", this->usage);

        if(this->description != NULL){
            printf("%s\n\n", this->description);
        }

        if(this->first_argument != NULL){
            printf("options :\n");
            printf("\tFLAGS");
            print_padding_characters("FLAGS", arg_flags_max_length+5, ' ');
            printf("DEFAULT");
            print_padding_characters("DEFAULT", arg_default_value_max_length+5, ' ');
            printf("HELP");
            print_padding_characters("HELP", arg_help_max_length+5, ' ');
            printf("CHOICES");
            printf("\n");
            for(Argument* argument = this->first_argument; argument != NULL; argument = argument->next){
                printf("\t%s", argument->flags);
                print_padding_characters(argument->flags, arg_flags_max_length+5, ' ');
                
                if(strcmp(argument->type, "string") == 0){
                    printf("%s", argument->default_value._string);
                    print_padding_characters(argument->default_value._string, arg_default_value_max_length+5, ' ');
                }
                else if(strcmp(argument->type, "int") == 0){
                    printf("%d", argument->default_value._int);
                    itoa(argument->default_value._int, string_buffer, 10);
                    print_padding_characters(string_buffer, arg_default_value_max_length+5, ' ');
                }
                else if(strcmp(argument->type, "bool") == 0){
                    printf(argument->default_value._bool ? "True" : "False");
                    print_padding_characters(argument->default_value._bool ? "True" : "False", arg_default_value_max_length+5, ' ');
                }
                // printf("\t%d", sizeof(argument->choices));
                printf("%s", argument->help);
                print_padding_characters(argument->help, arg_help_max_length+5, ' ');
                if(argument->choices != NULL && strcmp(argument->type, "string") == 0){
                    // printf("");
                    for(int i = 0; i < argument->nchoices; i++){
                        printf("%s ", argument->choices[i]);
                    }
                }
                else if(argument->choices != NULL && strcmp(argument->type, "int") == 0){
                    // printf("");
                    for(int i = 0; i < argument->nchoices; i++){
                        printf("%d ", argument->choices[i]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }

        for(Subparser* subparser = this->first_subparser; subparser != NULL; subparser = subparser->next){
            sum = 2;
            for(SubparserElement* subparser_element = subparser->first_parser; subparser_element != NULL; subparser_element = subparser_element->next){
                sum += strlen(subparser_element->sub_command)+1;
            }
            if(sum != 2){
                sum--;
            }

            if(sum > sub_flags_max_length){
                sub_flags_max_length = sum;
            }
        }

        if(this->first_subparser != NULL){
            printf("positional arguments:\n");
            printf("\tFLAGS");
            print_padding_characters("FLAGS", sub_flags_max_length+5, ' ');
            printf("HELP");
            printf("\n");
            for(Subparser* subparser = this->first_subparser; subparser != NULL; subparser = subparser->next){
                sum = 2;
                printf("\t{");
                for(SubparserElement* subparser_element = subparser->first_parser; subparser_element != NULL; subparser_element = subparser_element->next){
                    printf("%s", subparser_element->sub_command);
                    sum += strlen(subparser_element->sub_command);
                    if(subparser_element->next != NULL){
                        printf(",");
                        sum++;
                    }
                }
                printf("}");
                print_padding_characters(sum, sub_flags_max_length+5, ' ');
                printf("%s\n", subparser->help != NULL ? subparser->help : "      ");

                for(SubparserElement* subparser_element = subparser->first_parser; subparser_element != NULL; subparser_element = subparser_element->next){
                    printf("\t%s", subparser_element->sub_command);
                    print_padding_characters(subparser_element->sub_command, sub_flags_max_length+5, ' ');
                    printf("%s", subparser_element->help != NULL ? subparser_element->help : "      ");
                    printf("\n");
                }
            }
            printf("\n");
        }

        if(this->epilog != NULL){
            printf("%s\n\n", this->epilog);
        }

        return 0;
    }

    int ArgumentParser::print_version(){
        printf("%s %s\n", this->prog, this->version);
        return 0;
    }

}