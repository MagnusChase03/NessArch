#ifndef PARSER_H
#define PARSER_H

#include "./tokenizer.h"

void assemble(FILE_TOKENS tokens);
void parse(FILE_TOKENS tokens);
void statement(TOKEN_GROUP tokens);
void expression(TOKEN_GROUP tokens);

#endif