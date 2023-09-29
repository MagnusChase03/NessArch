#include "include/parser.h"

#include <stdlib.h>
#include <stdio.h>

int TOKEN_INDEX = 0;

void parse_error(const char* str) {
    printf("\33[1;31mUnexpected token <%s>\033[1;0m\n", str);
    exit(1);
}

void statement(TokenGroup tokens) {
    if (tokens.tokens[0].type == LABEL) {
        TOKEN_INDEX += 1;
        expression(tokens);
    } else {
        expression(tokens);
    }
}

void expression(TokenGroup tokens) {

    if (tokens.tokens[TOKEN_INDEX].type == INSTRUCTION) {
        TOKEN_INDEX += 1;
        if (tokens.tokens[TOKEN_INDEX].type == REGISTER || tokens.tokens[TOKEN_INDEX].type == LABEL_CALL) {
            TOKEN_INDEX += 1;
            if (tokens.tokens[TOKEN_INDEX].type == REGISTER || tokens.tokens[TOKEN_INDEX].type == LABEL_CALL) {
                TOKEN_INDEX += 1;
                if (TOKEN_INDEX == tokens.length) {
                    TOKEN_INDEX = 0;
                    return;
                } else if (tokens.tokens[TOKEN_INDEX].type == LABEL_CALL) {
                    TOKEN_INDEX += 1;
                    if (TOKEN_INDEX == tokens.length) {
                        TOKEN_INDEX = 0;
                        return;
                    }
                }
            }
        }

    } else if (tokens.tokens[TOKEN_INDEX].type == DATA) {
        TOKEN_INDEX += 1;
        if (tokens.tokens[TOKEN_INDEX].type == NUMBER) {
            TOKEN_INDEX += 1;
            if (TOKEN_INDEX == tokens.length) {
                TOKEN_INDEX = 0;
                return;
            }
        }
    }
    parse_error(tokens.tokens[TOKEN_INDEX].value);

}

void parse(FileTokens tokens) {
    for (int i = 0; i < tokens.length; i++) {
        statement(tokens.token_groups[i]);
    }
}

void parse_file(const char* filepath) {
    FileTokens tokens = lex_file(filepath);
    parse(tokens);
}
