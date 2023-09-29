#ifndef PARSER_H
#define PARSER_H

#include "include/lex.h"

void statement(TokenGroup tokens);
void expression(TokenGroup tokens);

void parse(FileTokens tokens);
void parse_file(const char* filepath);

#endif
