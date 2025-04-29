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

            Argument(const char* flags,
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

            Subparser(ArgumentParser* parent_parser,
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

            ArgumentParser* add_parser(const char* sub_command, const char* help){
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
    };

    class ArgumentParser{
        // parser();
        private:

        public:
            char* prog;
            char* usage;
            char* description;
            char* epilog;
            ArgumentParser* parents;
            // no formatter class yet
            char* prefix_chars;
            char* fromfile_prefix_chars;
            // no argument_default yet
            // unknown_type argument_default;
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

            // not completed yet
            
            // /**
            //  * Declares a new arguments parser
            //  * 
            //  * @param prog Name of the program
            //  * @param usage Describes the usage of the program's arguments
            //  * @param description Describes what the program does
            //  * @param epilog Message displayed at the end of the help
            //  * @param parents not done
            //  * @param prefix_chars not done
            //  * @param fromfile_prefix_chars not done
            //  * @param add_help not done
            //  * @param allow_abbrev not done
            //  * @param exit_on_error not done
            //  * 
            //  * @return Argument parser
            //  */
            // ArgumentParser(const char* prog,
            //                const char* usage,
            //                const char* description,
            //                const char* epilog,
            //                ArgumentParser* parents,
            //                // formatter_class,
            //                const char* prefix_chars,
            //                const char* fromfile_prefix_chars,
            //                // unknown_type argument_default,
            //                // conflict_handler,
            //                bool add_help,
            //                bool allow_abbrev,
            //                bool exit_on_error){
            //     this->prog = (char*) malloc(sizeof(*prog) * (strlen(prog) + 1));
            //     this->usage = (char*) malloc(sizeof(*usage) * (strlen(usage) + 1));
            //     this->description = (char*) malloc(sizeof(*description) * (strlen(description) + 1));
            //     this->epilog = (char*) malloc(sizeof(*epilog) * (strlen(epilog) + 1));

            //     this->prefix_chars = (char*) malloc(sizeof(*prefix_chars) * (strlen(prefix_chars) + 1));
            //     this->fromfile_prefix_chars = (char*) malloc(sizeof(*fromfile_prefix_chars) * (strlen(fromfile_prefix_chars) + 1));

            //     strcpy(this->prog, prog);
            //     strcpy(this->usage, usage);
            //     strcpy(this->description, description);
            //     strcpy(this->epilog, epilog);

            //     strcpy(this->prefix_chars, prefix_chars);
            //     strcpy(this->fromfile_prefix_chars, fromfile_prefix_chars);

            //     this->parents = parents;
            //     // unknown_type argument_default = {NULL};
            //     // this->argument_default = argument_default;
            //     this->add_help = add_help;
            //     this->allow_abbrev = allow_abbrev;
            //     this->exit_on_error = exit_on_error;

            //     this->first_argument = NULL;
            //     this->last_argument = NULL;

            //     this->subparser = NULL;

            //     // this->add_argument("-h --help", "action", 1, 0, (argparse::unknown_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
            //     this->add_argument("-h --help", "action", 1, 0, (argparse::undefined_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
            // }

            /**
             * Declares a new arguments parser
             * 
             * @param parser Input parser to copy
             * 
             * @return Argument parser
             */
            ArgumentParser(ArgumentParser* parser){
                this->prog = alloc_and_copy_string(parser->prog);
                this->usage = alloc_and_copy_string(parser->usage);
                this->description = alloc_and_copy_string(parser->description);
                this->epilog = alloc_and_copy_string(parser->epilog);

                this->prefix_chars = alloc_and_copy_string(parser->prefix_chars);

                this->parents = parents;
                // this->fromfile_prefix_chars = NULL;
                this->fromfile_prefix_chars = alloc_and_copy_string(parser->fromfile_prefix_chars);
                // unknown_type argument_default = {NULL};
                // this->argument_default = argument_default;
                this->add_help = parser->add_help;
                this->allow_abbrev = parser->allow_abbrev;
                this->exit_on_error = parser->exit_on_error;

                this->first_argument = NULL;
                this->last_argument = NULL;

                this->first_subparser = NULL;
                this->last_subparser = NULL;

                // this->add_argument("-h --help", "action", 1, 0, (argparse::unknown_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
                this->add_argument("-h --help", "action", 1, 0, (argparse::undefined_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
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
            ArgumentParser(const char* prog,
                const char* usage,
                const char* description,
                const char* epilog){
                this->prog = alloc_and_copy_string(prog);
                this->usage = alloc_and_copy_string(usage);
                this->description = alloc_and_copy_string(description);
                this->epilog = alloc_and_copy_string(epilog);

                this->prefix_chars = (char*) malloc(sizeof(char)*2);

                this->parents = NULL;
                this->prefix_chars[0] = '-';
                this->prefix_chars[1] = '\0';
                this->fromfile_prefix_chars = NULL;
                // unknown_type argument_default = {NULL};
                // this->argument_default = argument_default;
                this->add_help = true;
                this->allow_abbrev = true;
                this->exit_on_error = true;

                this->first_argument = NULL;
                this->last_argument = NULL;

                this->first_subparser = NULL;
                this->last_subparser = NULL;

                // this->add_argument("-h --help", "action", 1, 0, (argparse::unknown_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
                this->add_argument("-h --help", "action", 1, 0, (argparse::undefined_type) {.integer = 0}, "int", 0, NULL, true, "display the help of the program", "metavar", NULL, 0);
            }

            /**
             * Add a new argument at the argument parser
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
            int add_argument(const char* flags,
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
                // Argument* argument = new Argument(flags, action, nargs, constant, default_value, type, nchoices, choices,
                //                                   required, help, metavar, dest, deprecated);
                // printf("%d\n", sizeof(choices));
                Argument* argument = new Argument(flags, action, nargs, constant, default_value, type, nchoices, choices,
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
                return 0;
            }

            Subparser* add_subparsers(const char* title,
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
            
            int print_info(){
                printf("Prog : %s\nDesc : %s\nEpilog : %s\n", this->prog, this->description, this->epilog);
                printf("Prog : %d\nDesc : %d\nEpilog : %d\n", strlen(this->prog), strlen(this->description), strlen(this->epilog));

                return 0;
            }

            int help(){
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

                printf("\n%s\n\nUsage : %s\n\n%s\n\n", this->prog, this->usage, this->description);

                if(this->first_argument != NULL){
                    printf("Arguments :\n");
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
                // printf("%s\n\n", this->epilog);
                return 0;
            }

            // int help_with_type(){
            //     printf("\n%s\n\nUsage : %s\n\n%s\n\nArguments :\n", this->prog, this->usage, this->description);
            //     for(Argument* argument = this->first_argument; argument != NULL; argument = argument->next){
            //         printf("\t%s\ttype : %s\t%s", argument->flags, argument->type, argument->help);
            //         if(strcmp(argument->type, "string") == 0)
            //             printf("\tdefault : %s", argument->default_value.string);
            //         else if(strcmp(argument->type, "int") == 0)
            //             printf("\tdefault : %d", argument->default_value.integer);
            //         printf("\n");
            //     }
            //     printf("\n%s\n\n", this->epilog);
            //     return 0;
            // }
    };

    ArgumentParser* declare_new_argument_parser(ArgumentParser* parser){
        return new ArgumentParser(parser);
    }

    // struct ArgumentParserArgs{
    //     char* prog = "Program Name";
    //     char* description = "What the program does";
    //     char* epilog = "Text at the bottom of help";
    // };
}