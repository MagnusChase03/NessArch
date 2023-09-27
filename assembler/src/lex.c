#include "include/lex.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int REGISTER_LENGTH = 6;
char REGISTERS[][3] = {"ax", "bx", "cx", "dx", "ds", "sp"};

int INSTRUCTION_LENGTH = 13;
char INSTRUCTIONS[][5] = {"mov", "add", "sub", 
                            "and", "or", "xor",
                            "not", "push", "pop",
                            "cmp", "j", "jnz", "jz"};

int is_alpha(char c) {
    int ascii = (int) c;
    return (ascii >= 97 && ascii <= 122) || (ascii >= 65 && ascii <= 90);
}

int is_digit(char c) {
    int ascii = (int) c;
    return (ascii >= 48 && ascii <= 57);
}

int is_register(const char* str) {
    for (int i = 0; i < REGISTER_LENGTH; i++) {
        if (strcmp(REGISTERS[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_instruction(const char* str) {
    for (int i = 0; i < INSTRUCTION_LENGTH; i++) {
        if (strcmp(INSTRUCTIONS[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

Token lex(const char* str) {
    Token token;
    token.length = strlen(str);
    token.value = (char*) malloc(token.length);
    strcpy(token.value, str);

    if (str[0] == '[' && token.length == 1) {
        token.type = OPEN_SQUARE;
    } else if (str[0] == ']' && token.length == 1) {
        token.type = CLOSE_SQUARE;
    } else if (is_register(str)) {
        token.type = REGISTER;
    } else if (is_instruction(str)) {
        token.type = INSTRUCTION;
    } else if (is_alpha(str[0])) {

        for (int i = 1; i < token.length; i++) {
            if (str[i] == ':' && token.length - 1 == i) {
                token.type = LABEL;
                return token;
            } else if (!is_alpha(str[i])) {
                printf("\033[1;31mUnknown token: %s\n\033[1;0m", str);
                exit(1);
            }
        }

        token.type = LABEL_CALL;

    } else {
        printf("\033[1;31mUnknown token: %s\n\033[1;0m", str);
        exit(1);
    }

    return token;
}
