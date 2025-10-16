// #include <iostream>
#include <string.h>
// #include "../include/utils.hpp"
#include "../include/argparse.hpp"

namespace argparse{
    ParsedArguments::ParsedArguments(deallocator::Garbage* garbage){
        this->keys = NULL;
        this->values = NULL;
        this->number_of_values = NULL;
        this->type_of_value = NULL;
        this->length = 0;
        this->garbage = garbage;
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
                            printf("%d", this->values[i]._array[j]._int);
                            break;
                        case _float:
                            printf("%f", this->values[i]._array[j]._float);
                            break;
                        case _double:
                            printf("%f", this->values[i]._array[j]._double);
                            break;
                        case _bool:
                            printf(this->values[i]._array[j]._bool == true ? "true" : "false");
                            break;
                        case _string:
                            printf("%s", this->values[i]._array[j]._string);
                            break;
                    }
                    printf("\t");
                }
            }
            printf("\n");
        }
    }

    int ParsedArguments::add_argument(char* key, int number_of_values, undefined_type values, type type_of_value){
        void* address_ptr = NULL;
        if(this->keys == NULL){
            this->keys = (char**) malloc(sizeof(char*) * 1);
            this->garbage->throw_away(this->keys);
        }
        else{
            address_ptr = this->keys;
            this->keys = (char**) realloc(this->keys, sizeof(char*) * (this->length + 1));
            this->garbage->recycle(address_ptr, this->keys);
        }

        if(this->number_of_values == NULL){
            this->number_of_values = (int*) malloc(sizeof(int) * 1);
            this->garbage->throw_away(this->number_of_values);
        }
        else{
            address_ptr = this->number_of_values;
            this->number_of_values = (int*) realloc(this->number_of_values, sizeof(int) * (this->length + 1));
            this->garbage->recycle(address_ptr, this->number_of_values);
        }

        if(this->type_of_value == NULL){
            this->type_of_value = (type*) malloc(sizeof(type) * 1);
            this->garbage->throw_away(this->type_of_value);
        }
        else{
            address_ptr = this->type_of_value;
            this->type_of_value = (type*) realloc(this->type_of_value, sizeof(type) * (this->length + 1));
            this->garbage->recycle(address_ptr, this->type_of_value);
        }

        if(this->values == NULL){
            this->values = (undefined_type*) malloc(sizeof(undefined_type) * 1);
            this->garbage->throw_away(this->values);
        }
        else{
            address_ptr = this->values;
            this->values = (undefined_type*) realloc(this->values, sizeof(undefined_type) * (this->length + 1));
            this->garbage->recycle(address_ptr, this->values);
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
            this->garbage->recycle(this->values[id]._array, NULL);
            free(this->values[id]._array);
        }

        this->number_of_values[id] = number_of_values;

        this->type_of_value[id] = type_of_value;

        this->values[id] = values;

        return 0;
    }

    int ParsedArguments::change_argument_array_value(char* key, int id_of_value, undefined_type value){
        int id = -1;

        for(int i = 0; i < this->length; i++){
            if(strcmp(this->keys[i], key) == 0){
                id = i;
            }
        }

        if(id == -1){
            return 1;
        }

        this->values[id]._array[id_of_value] = value;

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

    argparse::undefined_type ParsedArguments::get_value_by_key(const char* key){
        for(int i = 0; i < this->length; i++){
            if(strcmp(this->keys[i], key) == 0){
                return this->values[i];
            }
        }

        return this->values[0];
    }
}