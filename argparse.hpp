#include <iostream>
#include <string.h>
#include "./lib/utils.hpp"

namespace argparse{
    union undefined_type{
        int integer;
        const char* const_string;
        char* string;
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
                if(flags != NULL)
                    this->flags = (char*) malloc(sizeof(*flags) * (strlen(flags) + 1));
                else
                    this->flags = NULL;
                if(action != NULL)
                    this->action = (char*) malloc(sizeof(*action) * (strlen(action) + 1));
                else
                    this->action = NULL;
                if(type != NULL){
                    this->type = (char*) malloc(sizeof(*type) * (strlen(type) + 1));
                    if(strcmp(type, "int") == 0){
                        this->default_value.integer = default_value.integer;
                    }
                    else if(strcmp(type, "string") == 0){
                        if(default_value.const_string != NULL){
                            this->default_value.string = (char*) malloc(sizeof(*default_value.const_string) * (strlen(default_value.const_string) + 1));
                            strcpy(this->default_value.string, default_value.const_string);
                        }
                    }
                }
                else
                    this->type = NULL;
                this->nchoices = nchoices;
                // this->choices = (char**) malloc(sizeof(*choices) * nchoices);
                this->choices = choices;    // Won't work with a static input
                if(help != NULL)
                    this->help = (char*) malloc(sizeof(*help) * (strlen(help) + 1));
                else
                    this->help = NULL;
                if(metavar != NULL)
                    this->metavar = (char*) malloc(sizeof(*metavar) * (strlen(metavar) + 1));
                else
                    this->metavar = NULL;
                if(dest != NULL)
                    this->dest = (char*) malloc(sizeof(*dest) * (strlen(dest) + 1));
                else
                    this->dest = NULL;

                if(flags != NULL)
                    strcpy(this->flags, flags);
                if(action != NULL)
                    strcpy(this->action, action);
                this->nargs = nargs;
                this->constant = constant;
                // this->default_value_int = default_value;
                if(type != NULL)
                    strcpy(this->type, type);
                // this->nchoices = nchoices;
                // no choices management for now
                this->required = required;
                if(help != NULL)
                    strcpy(this->help, help);
                if(metavar != NULL)
                    strcpy(this->metavar, metavar);
                if(dest != NULL)
                    strcpy(this->dest, dest);
                this->deprecated = deprecated;

                this->previous = NULL;
                this->next = NULL;
            }
    };

    class ArgumentParser{
        // parser();
        private:
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

            int arg_flags_max_length;
            int arg_default_value_max_length;
            int arg_help_max_length;
            int arg_choices_max_length;

        public:
            // // not completed yet
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

            //     strcpy(this->prog, prog);
            //     strcpy(this->usage, usage);
            //     strcpy(this->description, description);
            //     strcpy(this->epilog, epilog);
            // }

            
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
                this->prog = (char*) malloc(sizeof(*prog) * (strlen(prog) + 1));
                this->usage = (char*) malloc(sizeof(*usage) * (strlen(usage) + 1));
                this->description = (char*) malloc(sizeof(*description) * (strlen(description) + 1));
                this->epilog = (char*) malloc(sizeof(*epilog) * (strlen(epilog) + 1));

                this->prefix_chars = (char*) malloc(sizeof(char)*2);

                strcpy(this->prog, prog);
                strcpy(this->usage, usage);
                strcpy(this->description, description);
                strcpy(this->epilog, epilog);
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
            
            int print_info(){
                printf("Prog : %s\nDesc : %s\nEpilog : %s\n", this->prog, this->description, this->epilog);
                printf("Prog : %d\nDesc : %d\nEpilog : %d\n", strlen(this->prog), strlen(this->description), strlen(this->epilog));

                return 0;
            }

            int help(){
                int arg_flags_max_length = strlen("FLAGS");
                int arg_default_value_max_length = strlen("DEFAULT");
                int arg_help_max_length = strlen("HELP");

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

                printf("\n%s\n\nUsage : %s\n\n%s\n\nArguments :\n", this->prog, this->usage, this->description);
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
                printf("\n%s\n\n", this->epilog);
                return 0;
            }

            int help_with_type(){
                printf("\n%s\n\nUsage : %s\n\n%s\n\nArguments :\n", this->prog, this->usage, this->description);
                for(Argument* argument = this->first_argument; argument != NULL; argument = argument->next){
                    printf("\t%s\ttype : %s\t%s", argument->flags, argument->type, argument->help);
                    if(strcmp(argument->type, "string") == 0)
                        printf("\tdefault : %s", argument->default_value.string);
                    else if(strcmp(argument->type, "int") == 0)
                        printf("\tdefault : %d", argument->default_value.integer);
                    printf("\n");
                }
                printf("\n%s\n\n", this->epilog);
                return 0;
            }
    };

    // struct ArgumentParserArgs{
    //     char* prog = "Program Name";
    //     char* description = "What the program does";
    //     char* epilog = "Text at the bottom of help";
    // };
}