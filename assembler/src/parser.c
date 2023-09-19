#include "./include/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int line_index;
unsigned int token_index = 0;

char labels[1000][100];
int label_line[100];
int label_index = 0;

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
    } else if (strcmp(str, "not") == 0) {
        return 0b01100000;
    } else if (strcmp(str, "push") == 0) {
        return 0b01110000;
    } else if (strcmp(str, "pop") == 0) {
        return 0b10000000;
    } else if (strcmp(str, "cmp") == 0) {
        return 0b10010000;
    } else if (strcmp(str, "j") == 0) {
        return 0b10100000;
    } else if (strcmp(str, "jz") == 0) {
        return 0b10110000;
    } else if (strcmp(str, "jnz") == 0) {
        return 0b11000000;
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

unsigned char offset_to(const char* str) {
    for (int i = 0; i < label_index; i++) {
        if (strcmp(str, labels[i]) == 0) {
            if (line_index - label_line[i] < 8 && line_index - label_line[i] >= 0) {
                return 0b00001111 & (unsigned char) (label_line[i] - line_index);
            } else if (label_line[i] - line_index < 8) {
                return (unsigned char)(label_line[i] - line_index);
            }
        }
    }

    printf("[ERROR] Jump too large or does not exit on line %d\n", line_index);
    exit(1);

}

void assemble(FILE_TOKENS tokens) {

    parse(tokens);

    line_index = 0;
    for (int i = 0; i < tokens.length; i++) {
        TOKEN_TYPE type = tokens.token_groups[i].tokens[0].token_type;
        const char* value = tokens.token_groups[i].tokens[0].value;
        if (type == LABEL) {
            strcpy(labels[label_index], value);
            labels[label_index][strlen(labels[label_index]) - 1] = '\0';
            label_line[label_index] = line_index;
            label_index += 1;
        }
        if (tokens.token_groups[i].length > 1) {
            line_index += 1;
        }
    }

    line_index = 0;
    for (int i = 0; i < tokens.length; i++) {

        unsigned int register_shift = 2;
        unsigned char buffer = 0b00000000;
        for (int j = 0; j < tokens.token_groups[i].length; j++) {
            TOKEN_TYPE type = tokens.token_groups[i].tokens[j].token_type;
            const char* value = tokens.token_groups[i].tokens[j].value;
            if (type == INSTRUCTION) {
                buffer += instruction_to_binary(value);
            } else if (type == REGISTER) {
                buffer += register_to_binary(value) << register_shift;
                register_shift = 0;
            } else if (type == BIN_IMMIDIATE) {
                buffer += binary_str_to_binary(value);
            } else if (type == LABEL_JUMP) {
                buffer += offset_to(value);
            }  
        }
        if (tokens.token_groups[i].length > 1) {
            line_index += 1;
            printf("%b\n", buffer);
        }

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
        if (token_index == tokens.length) {
            return;
        }
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
            if (token_index == tokens.length) {
                return;
            } else if (tokens.tokens[token_index].token_type == REGISTER) {
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

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("[USAGE] ./ebasm <filepath>\n");
        return 1;
    }

    FILE_TOKENS tokens = make_tokens(argv[1]);
    assemble(tokens);
    return 0;
}