#include "include/lex.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int REGISTER_LENGTH = 4;
char REGISTERS[][3] = {"ax", "bx", "cx", "dx"};

void lex_error(const char* str) {
    printf("\033[1;31mUnknown token: %s\033[1;0m\n", str);
    exit(1);
}

int is_alpha(char x) {
    int tmp = (int) x;
    return tmp >= 97 && tmp <=122;
}

int is_digit(char x) {
    int tmp = (int) x;
    return tmp >= 48 && tmp <=57;
}

int is_register(const char* str) {

    for (int i = 0; i < REGISTER_LENGTH; i++) {
        if (strcmp(str, REGISTERS[i]) == 0) {
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

    if (is_register(str)) {
        token.type = REGISTER;
    } else if (strcmp(str, "sub") == 0) {
        token.type = INSTRUCTION;
    } else if (strcmp(str, ".data") == 0) {
        token.type = DATA;
    } else if (is_alpha(str[0])) {
        for (int i = 0; i < token.length; i++) {
            if (i > 0 && i == token.length - 1 && str[i] == ':') {
                token.type = LABEL;
                return token;
            } else if (!is_alpha(str[i])) {
                lex_error(str);
            }
        }
        token.type = LABEL_CALL;
    } else {
        for (int i = 0; i < token.length; i++) {
            if (!is_digit(str[i])) {
                lex_error(str);
            }
        }
        token.type = NUMBER;
    }

    return token;

}

TokenGroup lex_line(const char* str) {

    int str_len = strlen(str);
    TokenGroup tokens;
    tokens.length = 0;

    int start = 0;
    while (str[start] == ' ') {
        start += 1;
    }

    tokens.length += 1;
    for (int i = start; i < str_len; i++) {
        if (str[i] == ' ') {
            tokens.length += 1;
        }
    }
    tokens.tokens = (Token*) malloc(sizeof(Token) * tokens.length);

    int token_index = 0;
    int buffer_index = 0;
    char buffer[100];
    for (int i = 0; i < 100; i ++) {buffer[i] = '\0';}
    for (int i = start; i < str_len; i++) {
        if (str[i] == ' ') {
            Token token = lex(buffer); 
            tokens.tokens[token_index] = token; 
            buffer_index = 0;
            token_index += 1;
            for (int i = 0; i < 100; i ++) {buffer[i] = '\0';}
        } else {
           buffer[buffer_index] = str[i];
           buffer_index += 1;
        }
    }
    Token token = lex(buffer); 
    tokens.tokens[token_index] = token; 

    return tokens;

}
