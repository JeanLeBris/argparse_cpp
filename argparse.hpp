#include <iostream>
#include <string.h>
#include "./lib/utils.hpp"

namespace argparse{
    class Argument;
    class Subparser;
    class ArgumentParser;

    ArgumentParser* declare_new_argument_parser(ArgumentParser* parser);

    union undefined_type{
        int integer;
        float float_value;
        double double_value;
        const char* const_string;
        char* string;
    };

    struct SubparserElement{
        char* sub_command;
        char* help;
        ArgumentParser* parser;

        SubparserElement* previous;
        SubparserElement* next;
    };

    class Argument{
        private:

        public:
            bool is_positional_argument;
            char* flags;
            char* action;
            int nargs;
            int constant;
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

            Argument(ArgumentParser* parser, const char* flags, const char* action, int nargs, int constant, undefined_type default_value, const char* type, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);
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

            ArgumentParser* parent_parser;

            SubparserElement* first_parser;
            SubparserElement* last_parser;

            Subparser* previous;
            Subparser* next;

            Subparser(ArgumentParser* parent_parser, const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet

            ArgumentParser* add_parser(const char* sub_command, const char* help);
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
            // no argument_default yet
            // no conflict_handler yet
            bool add_help;
            bool allow_abbrev;
            bool exit_on_error;

            Argument* first_argument;
            Argument* last_argument;

            Subparser* first_subparser;
            Subparser* last_subparser;

            int arg_flags_max_length;
            int arg_default_value_max_length;
            int arg_help_max_length;
            int arg_choices_max_length;

            void init(const char* prog, const char* usage, const char* description, const char* epilog, ArgumentParser* parents, const char* prefix_chars, const char* fromfile_prefix_chars, bool add_help, bool allow_abbrev, bool exit_on_error); // no formatter_class, argument_default or conflict_handler yet
            
            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog, ArgumentParser* parents, const char* prefix_chars, const char* fromfile_prefix_chars, bool add_help, bool allow_abbrev, bool exit_on_error); // no formatter_class, argument_default or conflict_handler yet

            ArgumentParser(ArgumentParser* parser);

            ArgumentParser(const char* prog, const char* usage, const char* description, const char* epilog);

            int add_argument(const char* flags, const char* action, int nargs, int constant, undefined_type default_value, const char* type, int nchoices, undefined_type* choices, bool required, const char* help, const char* metavar, const char* dest, bool deprecated);

            Subparser* add_subparsers(const char* title, const char* description, const char* prog, const char* action, const char* dest, bool required, const char* help, const char* metavar); // no parser_class yet
            
            int help();
    };

    ArgumentParser* declare_new_argument_parser(ArgumentParser* parser){
        return new ArgumentParser(parser);
    }

    // struct ArgumentParserArgs{
    //     char* prog = "Program Name";
    //     char* description = "What the program does";
    //     char* epilog = "Text at the bottom of help";
    // };

    Argument::Argument(ArgumentParser* parser,
                       const char* flags,
                       const char* action,
                       int nargs,
                       int constant,
                       undefined_type default_value,
                       const char* type,
                       int nchoices,
                       undefined_type* choices,
                       bool required,
                       const char* help,
                       const char* metavar,
                       const char* dest,
                       bool deprecated){
        // const char* flags_ptr = NULL;
        if(flags == NULL){
            printf("Flags are necessary to declare a new argument");
            exit(1);
        }
        // flags_ptr == flags;
        // while(*flags_ptr != '\0'){
        //     if(strchr(parser->prefix_chars, *flags_ptr) == NULL){
        //         printf("test");
        //     }
        //     while(*flags_ptr != ' ' && *flags_ptr != '\0'){
        //         flags_ptr++;
        //     }
        // }
        this->flags = alloc_and_copy_string(flags);
        this->action = alloc_and_copy_string(action);
        this->type = alloc_and_copy_string(type);
        if(type != NULL){
            if(strcmp(type, "int") == 0){
                this->default_value.integer = default_value.integer;
            }
            else if(strcmp(type, "string") == 0){
                if(default_value.const_string != NULL){
                    // this->default_value.string = (char*) malloc(sizeof(*default_value.const_string) * (strlen(default_value.const_string) + 1));
                    // strcpy(this->default_value.string, default_value.const_string);
                    this->default_value.string = alloc_and_copy_string(default_value.const_string);
                }
            }
        }
        else
            this->type = NULL;
        this->nchoices = nchoices;
        // this->choices = (char**) malloc(sizeof(*choices) * nchoices);
        this->choices = choices;    // Won't work with a static input
        this->help = alloc_and_copy_string(help);
        this->metavar = alloc_and_copy_string(metavar);
        this->dest = alloc_and_copy_string(dest);

        this->nargs = nargs;
        this->constant = constant;
        // this->nchoices = nchoices;
        // no choices management for now
        this->required = required;
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
        // subparser_element->parser = new ArgumentParser(this->parent_parser);
        subparser_element->parser = declare_new_argument_parser(this->parent_parser);
        // subparser_element->sub_command = NULL;
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

        return subparser_element->parser;
    }
    
    void ArgumentParser::init(const char* prog,
                              const char* usage,
                              const char* description,
                              const char* epilog,
                              ArgumentParser* parents,
                              // formatter_class,
                              const char* prefix_chars,
                              const char* fromfile_prefix_chars,
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
        // unknown_type argument_default = {NULL};
        // this->argument_default = argument_default;
        this->add_help = add_help;
        this->allow_abbrev = allow_abbrev;
        this->exit_on_error = exit_on_error;

        this->first_argument = NULL;
        this->last_argument = NULL;

        this->first_subparser = NULL;
        this->last_subparser = NULL;

        char help_flags[20] = "";
        sprintf(help_flags, "%ch %c%chelp", this->prefix_chars[0], this->prefix_chars[0], this->prefix_chars[0]);
        if(this->add_help){
            this->add_argument(help_flags, "action", 1, 0, (argparse::undefined_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
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
                                   // unknown_type argument_default,
                                   // conflict_handler,
                                   bool add_help,
                                   bool allow_abbrev,
                                   bool exit_on_error){
        init(prog, usage, description, epilog, parents, prefix_chars, fromfile_prefix_chars, add_help, allow_abbrev, exit_on_error);
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
            init(parser->prog, NULL, parser->description, parser->epilog, parser, parser->prefix_chars, parser->fromfile_prefix_chars, parser->add_help, parser->allow_abbrev, parser->exit_on_error);
        }
        else{
            init(parser->prog, parser->usage, parser->description, parser->epilog, parser, parser->prefix_chars, parser->fromfile_prefix_chars, parser->add_help, parser->allow_abbrev, parser->exit_on_error);
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
        init(prog, usage, description, epilog, NULL, "-", NULL, true, true, true);
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

        return 0;
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

        return subparser;
    }

    /**
     * Display the argument parser's help
     */
    int ArgumentParser::help(){
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
                if(strlen(argument->default_value.string) > arg_default_value_max_length){
                    arg_default_value_max_length = strlen(argument->default_value.string);
                }
            }
            else if(strcmp(argument->type, "int") == 0){
                itoa(argument->default_value.integer, string_buffer, 10);
                if(strlen(string_buffer) > arg_default_value_max_length){
                    arg_default_value_max_length = strlen(string_buffer);
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
                    printf("%s", argument->default_value.string);
                    print_padding_characters(argument->default_value.string, arg_default_value_max_length+5, ' ');
                }
                else if(strcmp(argument->type, "int") == 0){
                    printf("%d", argument->default_value.integer);
                    itoa(argument->default_value.integer, string_buffer, 10);
                    print_padding_characters(string_buffer, arg_default_value_max_length+5, ' ');
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
                printf("%s\n", subparser->help);

                for(SubparserElement* subparser_element = subparser->first_parser; subparser_element != NULL; subparser_element = subparser_element->next){
                    printf("\t%s", subparser_element->sub_command);
                    print_padding_characters(subparser_element->sub_command, sub_flags_max_length+5, ' ');
                    printf("%s", subparser_element->help);
                    printf("\n");
                }
            }
            printf("\n");
        }
        // if(this->subparser != NULL && this->subparser->first_parser != NULL){
        //     // printf("%d\n", this->subparser);
        //     // printf("%d\n", this->subparser->first_parser);
        //     for(SubparserElement* subparser_element = this->subparser->first_parser; subparser_element != NULL; subparser_element = subparser_element->next){
        //         printf("\t%s", subparser_element->sub_command);
        //         print_padding_characters(subparser_element->sub_command, 10, ' ');
        //         printf("%s", subparser_element->help);
        //         printf("\n");
        //     }
        //     printf("\n");
        // }

        if(this->epilog != NULL){
            printf("%s\n\n", this->epilog);
        }

        return 0;
    }

}