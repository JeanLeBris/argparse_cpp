// #include <iostream>
#include <string.h>
#include "../include/utils.hpp"
#include "../include/argparse.hpp"

namespace argparse{
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
        this->parent_parser->getGarbage()->throw_away(this->title);
        this->description = alloc_and_copy_string(description);
        this->parent_parser->getGarbage()->throw_away(this->description);
        this->prog = alloc_and_copy_string(prog);
        this->parent_parser->getGarbage()->throw_away(this->prog);
        this->action = alloc_and_copy_string(action);
        this->parent_parser->getGarbage()->throw_away(this->action);
        this->dest = alloc_and_copy_string(dest);
        this->parent_parser->getGarbage()->throw_away(this->dest);
        this->required = required;
        this->help = alloc_and_copy_string(help);
        this->parent_parser->getGarbage()->throw_away(this->help);
        this->metavar = alloc_and_copy_string(metavar);
        this->parent_parser->getGarbage()->throw_away(this->metavar);

        this->n_parsers = 0;
        
        this->first_parser = NULL;
        this->last_parser = NULL;

        this->previous = NULL;
        this->next = NULL;
    }
    
    Subparser* Subparser::getNext(){
        return this->next;
    }

    void Subparser::setNext(Subparser* next){
        this->next = next;
    }

    Subparser* Subparser::getPrevious(){
        return this->previous;
    }

    void Subparser::setPrevious(Subparser* previous){
        this->previous = previous;
    }

    char* Subparser::getTitle(){
        return this->title;
    }

    void Subparser::setTitle(char* title){
        this->title = title;
    }

    int Subparser::getNparsers(){
        return this->n_parsers;
    }

    void Subparser::setNparsers(int n_parsers){
        this->n_parsers = n_parsers;
    }

    bool Subparser::getRequired(){
        return this->required;
    }

    void Subparser::setRequired(bool required){
        this->required = required;
    }

    SubparserElement* Subparser::getFirstParser(){
        return this->first_parser;
    }

    void Subparser::setFirstParser(SubparserElement* first_parser){
        this->first_parser = first_parser;
    }

    char* Subparser::getHelp(){
        return this->help;
    }

    void Subparser::setHelp(char* help){
        this->help = help;
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
        SubparserElement* subparser_element = new SubparserElement();
        this->parent_parser->getGarbage()->throw_away(subparser_element);
        subparser_element->parser = new ArgumentParser(this->parent_parser);
        this->parent_parser->getGarbage()->throw_away(subparser_element->parser);
        subparser_element->parent_subparser = this;
        // subparser_element->sub_command = NULL;
        if(sub_command == NULL){
            printf("To add a parser to a sub-parser, a sub-command is necessary");
            exit(1);
        }
        subparser_element->sub_command = alloc_and_copy_string(sub_command);
        this->parent_parser->getGarbage()->throw_away(subparser_element->sub_command);
        // subparser_element->help = NULL;
        subparser_element->help = alloc_and_copy_string(help);
        this->parent_parser->getGarbage()->throw_away(subparser_element->help);
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
}