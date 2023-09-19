#include "./include/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int line_index;
unsigned int token_index = 0;

void parser_error() {
    printf("[ERROR] Invalid syntax on line %d\n", line_index);
    exit(1);
}

unsigned char instruction_to_binary(const char* str) {
    if (strcmp(str, "mov") == 0) {
        return 0b00000000;
    } else if (strcmp(str, "add") == 0) {
        return 0b00010000;
    } else if (strcmp(str, "sub") == 0) {
        return 0b00100000;
    } else if (strcmp(str, "and") == 0) {
        return 0b00110000;
    } else if (strcmp(str, "or") == 0) {
        return 0b01000000;
    } else if (strcmp(str, "xor") == 0) {
        return 0b01010000;
    } else if (strcmp(str, "push") == 0) {
        return 0b01100000;
    } else if (strcmp(str, "pop") == 0) {
        return 0b01110000;
    } else if (strcmp(str, "cmp") == 0) {
        return 0b10000000;
    } else if (strcmp(str, "j") == 0) {
        return 0b10010000;
    } else if (strcmp(str, "jz") == 0) {
        return 0b10100000;
    } else if (strcmp(str, "jnz") == 0) {
        return 0b10110000;
    }
    return 0b00000000;
}

unsigned char register_to_binary(const char* str) {
    if (strcmp(str, "ax") == 0) {
        return 0b00000000;
    } else if (strcmp(str, "bx") == 0) {
        return 0b00000001;
    } else if (strcmp(str, "cx") == 0) {
        return 0b00000010;
    } else if (strcmp(str, "dx") == 0) {
        return 0b00000011;
    }
    return 0b00000000;
}

unsigned char binary_str_to_binary(const char* str) {
    unsigned char buffer = 0b00;
    
    if (str[2] == '1') {
        buffer += 0b10;
    }

    if (str[3] == '1') {
        buffer += 0b01;
    }

    return buffer;
}

void assemble(FILE_TOKENS tokens) {

    parse(tokens);
    for (int i = 0; i < tokens.length; i++) {
        unsigned char buffer = 0b00000000;
        if (tokens.token_groups[i].tokens[0].token_type == INSTRUCTION) {

            buffer += instruction_to_binary(tokens.token_groups[i].tokens[0].value);
            if (tokens.token_groups[i].tokens[1].token_type == REGISTER) {
                buffer += register_to_binary(tokens.token_groups[i].tokens[1].value) << 2;

                if (tokens.token_groups[i].tokens[2].token_type == REGISTER) {
                    buffer += register_to_binary(tokens.token_groups[i].tokens[2].value);
                } else if (tokens.token_groups[i].tokens[2].token_type == BIN_IMMIDIATE) {
                    buffer += binary_str_to_binary(tokens.token_groups[i].tokens[2].value);
                }

            } else if (tokens.token_groups[i].tokens[1].token_type == LABEL_JUMP) {

            }

        } else if (tokens.token_groups[i].tokens[0].token_type == LABEL) {

            buffer += instruction_to_binary(tokens.token_groups[i].tokens[1].value);
            if (tokens.token_groups[i].tokens[2].token_type == REGISTER) {
                buffer += register_to_binary(tokens.token_groups[i].tokens[2].value) << 2;

                if (tokens.token_groups[i].tokens[3].token_type == REGISTER) {
                    buffer += register_to_binary(tokens.token_groups[i].tokens[3].value);
                } else if (tokens.token_groups[i].tokens[3].token_type == BIN_IMMIDIATE) {
                    buffer += binary_str_to_binary(tokens.token_groups[i].tokens[3].value);
                }

            } else if (tokens.token_groups[i].tokens[2].token_type == LABEL_JUMP) {

            }

        }

        printf("%b\n", buffer);
    }
}

void parse(FILE_TOKENS tokens) {
    for (int i = 0; i < tokens.length; i++) {
        token_index = 0;
        statement(tokens.token_groups[i]);
        line_index += 1;
    }
}

void statement(TOKEN_GROUP tokens) {
    if (tokens.tokens[token_index].token_type == LABEL) {
        token_index += 1;
        expression(tokens);
    } else {
        expression(tokens);
    }
}

void expression(TOKEN_GROUP tokens) {
    if (tokens.tokens[token_index].token_type == INSTRUCTION) {
        token_index += 1;
        if (tokens.tokens[token_index].token_type == REGISTER) {
            token_index += 1;
            if (tokens.tokens[token_index].token_type == REGISTER) {
                token_index += 1;
                if (token_index == tokens.length)
                    return;
            } else if (tokens.tokens[token_index].token_type == BIN_IMMIDIATE) {
                token_index += 1;
                if (token_index == tokens.length)
                    return;
            }
        } else if (tokens.tokens[token_index].token_type == LABEL_JUMP) {
            token_index += 1;
            if (token_index == tokens.length)
                return;
        } 
    }
    
    parser_error();
}

int main() {
    FILE_TOKENS tokens = make_tokens("./src/test.ebasm");
    assemble(tokens);
    return 0;
}