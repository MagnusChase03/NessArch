#include "./include/parser.h"

#include <stdio.h>
#include <stdlib.h>

unsigned int line_index;
unsigned int token_index = 0;

void parser_error() {
    printf("[ERROR] Invalid syntax on line %d\n", line_index);
    exit(1);
}

void assemble(FILE_TOKENS tokens) {
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
            } else if (tokens.tokens[token_index].token_type == HEX_IMMIDIATE) {
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