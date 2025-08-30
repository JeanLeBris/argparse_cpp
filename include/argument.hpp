#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

/**
 * The Argparse library, for C++
 */

namespace argparse{
    class Argument;
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
}

#endif