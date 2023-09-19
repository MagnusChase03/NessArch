#include "./include/tokenizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char DIGITS[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char ALPHA[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char BIN_PREFIX[3] = "0b";
char LABEL_END = ':';

int NUM_REGISTERS = 4;
char REGISTERS[][3] = {"ax", "bx", "cx", "dx"};

int NUM_INSTRUCTIONS = 12;
char INSTRUCTIONS[][5] = {
    "mov",
    "add",
    "sub",
    "and",
    "or",
    "xor",
    "push",
    "pop",
    "cmp",
    "j",
    "jz",
    "jnz"
};

void lex_error(const char* str) {

    printf("[LEX ERROR] %s\n", str);
    exit(1);

}

int is_digit(char x) {
    for (int i = 0; i < sizeof(DIGITS); i++) {
        if (DIGITS[i] == x) {
            return 1;
        }
    }

    return 0;
}

int is_alpha(char x) {
    for (int i = 0; i < sizeof(ALPHA); i++) {
        if (ALPHA[i] == x) {
            return 1;
        }
    }

    return 0;
}

int is_register(const char* str) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        if (strcmp(str, REGISTERS[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int is_instruction(const char* str) {
    for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
        if (strcmp(str, INSTRUCTIONS[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

FILE_TOKENS make_tokens(const char* filename) {
    FILE_TOKENS tokens;
    FILE* file = fopen(filename, "r");

    TOKEN_GROUP token_groups[1000];
    char buffer[100];
    char* read = fgets(buffer, sizeof(buffer), file);
    while (read != NULL) {
        if (strlen(buffer) == 1 && buffer[strlen(buffer) - 1] == '\n') {
            read = fgets(buffer, sizeof(buffer), file);
            continue;
        } else if (buffer[strlen(buffer) - 1] == '\n') {
            token_groups[tokens.length] = tokenize(buffer, strlen(buffer) - 1);
        } else {
            token_groups[tokens.length] = tokenize(buffer, strlen(buffer));
        }
        tokens.length += 1;
        read = fgets(buffer, sizeof(buffer), file);
    }

    tokens.token_groups = (TOKEN_GROUP*) malloc(sizeof(TOKEN_GROUP) * tokens.length);
    for (int i = 0; i < tokens.length; i++) {
        tokens.token_groups[i] = token_groups[i];
    }

    return tokens;

}

TOKEN_GROUP tokenize(const char* str, unsigned int length) {
    TOKEN_GROUP tokens;

    unsigned int start = 0;
    while (str[start] == ' ') {
        start += 1;
    }

    unsigned int num_tokens = 1;
    for (int i = start; i < length; i++) {
        if (str[i] == ' ') {
            num_tokens += 1;
        }
    }
    tokens.length = num_tokens;
    tokens.tokens = (TOKEN*) malloc(sizeof(TOKEN) * num_tokens);

    char buffer[100];
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = '\0';
    }

    unsigned int token_index = 0;
    int buffer_index = 0;
    for (int i = start; i < length; i++, buffer_index++) {
        if (str[i] == ' ') {
            tokens.tokens[token_index] = lex(buffer, strlen(buffer));
            buffer_index = -1;
            token_index += 1;
            for (int i = 0; i < sizeof(buffer); i++) {
                buffer[i] = '\0';
            }
        } else {
            buffer[buffer_index] = str[i];
        }
    }
    tokens.tokens[token_index] = lex(buffer, strlen(buffer));

    return tokens;
}

TOKEN lex(const char* str, unsigned int length) {
    TOKEN token;
    token.length = length;
    strcpy(token.value, str);

    if (is_alpha(str[0])) {

        if (is_register(str)) {
            token.token_type = REGISTER;
            return token;
        } else if (is_instruction(str)) {
            token.token_type = INSTRUCTION;
            return token;
        } else {

            for (int i = 1; i < length; i++) {
                if (!is_alpha(str[i])) {
                    if (str[i] == LABEL_END && i == length - 1) {
                        token.token_type = LABEL;
                        return token;
                    } else {
                        lex_error(str);
                    }
                }
            }
            
            token.token_type = LABEL_JUMP;
            return token;
        }

    } else if (str[0] == '0' && length == 4) {

        if (str[1] == 'b') {

            for (int i = 2; i < length; i++) {
                if (str[i] != '0' && str[i] != '1') {
                    lex_error(str);
                }
            }

            token.token_type = BIN_IMMIDIATE;
            return token;

        }

    }

    lex_error(str);

}