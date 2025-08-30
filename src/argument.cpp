// #include <iostream>
#include <string.h>
#include "../include/utils.hpp"
#include "../include/argparse.hpp"

namespace argparse{
    Argument::Argument(ArgumentParser* parser,
                       const char* flags,
                       const char* action,
                       int nargs,
                       undefined_type constant,
                       undefined_type default_value,
                       type type_of_argument,
                       int nchoices,
                       undefined_type* choices,
                       bool required,
                       const char* help,
                       const char* metavar,
                       const char* dest,
                       bool deprecated){
        this->parent_parser = parser;
        bool store_true_false = false;
        char* char_ptr = NULL;
        void* address_ptr = NULL;
        if(flags == NULL){
            printf("Flags are necessary to declare a new argument");
            exit(1);
        }
        this->is_positional_argument = false;
        for(int i = 0; i < (int) strlen(flags); i++){ // look at wtf happens here
            if(strchr(parser->getPrefixChars(), flags[i]) == NULL){
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
        this->parent_parser->getGarbage()->throw_away(this->flags);
        if(action == NULL){
            this->action = alloc_and_copy_string("store");
            this->parent_parser->getGarbage()->throw_away(this->action);
        }
        else{
            this->action = alloc_and_copy_string(action);
            this->parent_parser->getGarbage()->throw_away(this->action);
        }
        if(strcmp(this->action, "store") == 0){
            
        }
        else if(strcmp(this->action, "store_const") == 0){
            this->nargs = 0;
            this->constant = constant;
            this->default_value = default_value;
            this->type_of_argument = type_of_argument;
            // this->parent_parser->getGarbage()->throw_away(this->type);
        }
        else if(strcmp(this->action, "store_true") == 0){
            address_ptr = this->action;
            free(this->action);
            this->action = alloc_and_copy_string("store_const");
            this->parent_parser->getGarbage()->recycle(address_ptr, this->action);
            // this->parent_parser->garbage->throw_away(this->action);
            this->nargs = 0;
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type_of_argument = _bool;
            // this->parent_parser->getGarbage()->throw_away(this->type);
        }
        else if(strcmp(this->action, "store_false") == 0){
            address_ptr = this->action;
            free(this->action);
            this->action = alloc_and_copy_string("store_const");
            this->parent_parser->getGarbage()->recycle(address_ptr, this->action);
            // this->parent_parser->garbage->throw_away(this->action);
            this->nargs = 0;
            this->default_value._bool = true;
            this->constant._bool = false;
            store_true_false = true;
            this->type_of_argument = _bool;
            // this->parent_parser->getGarbage()->throw_away(this->type);
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
            this->nargs = 0;
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type_of_argument = _bool;
            // this->parent_parser->getGarbage()->throw_away(this->type);
        }
        else if(strcmp(this->action, "version") == 0){
            this->nargs = 0;
            this->default_value._bool = false;
            this->constant._bool = true;
            store_true_false = true;
            this->type_of_argument = _bool;
            // this->parent_parser->getGarbage()->throw_away(this->type);
        }
        else{
            printf("The action argument value must be a correct value or none at all");
            exit(1);
        }
        if(!store_true_false && strcmp(this->action, "store_const") != 0){
            this->nargs = nargs;
            this->constant = constant;
            this->default_value = default_value;
            this->type_of_argument = type_of_argument;
            // this->parent_parser->getGarbage()->throw_away(this->type);
        }
        this->nchoices = nchoices;
        this->choices = choices;
        this->required = required;
        this->help = alloc_and_copy_string(help);
        this->parent_parser->getGarbage()->throw_away(this->help);
        this->metavar = alloc_and_copy_string(metavar);
        this->parent_parser->getGarbage()->throw_away(this->metavar);
        if(dest == NULL){
            char_ptr = this->flags;
            for(char_ptr = this->flags; strchr(char_ptr, ' ') != NULL; char_ptr = strchr(char_ptr, ' ') + 1);
            for(char_ptr = char_ptr; strchr(parser->getPrefixChars(), *char_ptr) != NULL; char_ptr++);
            this->dest = alloc_and_copy_string(char_ptr);
            this->parent_parser->getGarbage()->throw_away(this->dest);
        }
        else{
            this->dest = alloc_and_copy_string(dest);
            this->parent_parser->getGarbage()->throw_away(this->dest);
        }
        this->deprecated = deprecated;

        this->previous = NULL;
        this->next = NULL;
    }

    Argument* Argument::getPrevious(){
        return this->previous;
    }

    void Argument::setPrevious(Argument* previous){
        this->previous = previous;
    }

    Argument* Argument::getNext(){
        return this->next;
    }

    void Argument::setNext(Argument* next){
        this->next = next;
    }
    
    type Argument::getType(){
        return this->type_of_argument;
    }

    void Argument::setType(type type_of_argument){
        this->type_of_argument = type_of_argument;
    }

    char* Argument::getDest(){
        return this->dest;
    }

    void Argument::setDest(char* dest){
        this->dest = dest;
    }

    undefined_type Argument::getDefaultValue(){
        return this->default_value;
    }

    void Argument::setDefaultValue(undefined_type default_value){
        this->default_value = default_value;
    }
    
    char* Argument::getFlags(){
        return this->flags;
    }

    void Argument::setFlags(char* flags){
        this->flags = flags;
    }
    
    int Argument::getNargs(){
        return this->nargs;
    }

    void Argument::setNargs(int nargs){
        this->nargs = nargs;
    }

    char* Argument::getAction(){
        return this->action;
    }

    void Argument::setAction(char* action){
        this->action = action;
    }

    ArgumentParser* Argument::getParentParser(){
        return this->parent_parser;
    }

    void Argument::setParentParser(ArgumentParser* parent_parser){
        this->parent_parser = parent_parser;
    }

    undefined_type Argument::getConstant(){
        return this->constant;
    }

    void Argument::setConstant(undefined_type constant){
        this->constant = constant;
    }
    
    char* Argument::getHelp(){
        return this->help;
    }

    void Argument::setHelp(char* help){
        this->help = help;
    }

    int Argument::getNchoices(){
        return this->nchoices;
    }

    void Argument::setNchoices(int nchoices){
        this->nchoices = nchoices;
    }
    
    undefined_type* Argument::getChoices(){
        return this->choices;
    }

    void Argument::setChoices(undefined_type* choices){
        this->choices = choices;
    }
}