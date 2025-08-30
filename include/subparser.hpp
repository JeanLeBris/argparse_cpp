#ifndef SUBPARSER_HPP
#define SUBPARSER_HPP

/**
 * The Argparse library, for C++
 */

namespace argparse{
    class Subparser;
    class ArgumentParser;

    struct SubparserElement{
        char* sub_command;
        char* help;
        ArgumentParser* parser;
        Subparser* parent_subparser;

        SubparserElement* previous;
        SubparserElement* next;
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
}

#endif