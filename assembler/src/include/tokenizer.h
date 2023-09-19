#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {

    BIN_IMMIDIATE,
    HEX_IMMIDIATE,
    REGISTER,
    INSTRUCTION,
    LABEL,
    LABEL_JUMP

} TOKEN_TYPE;

typedef struct {

    TOKEN_TYPE token_type;
    unsigned int length;

} TOKEN;

typedef struct {

    TOKEN* tokens;
    unsigned int length;

} TOKEN_GROUP;

typedef struct {

    TOKEN_GROUP* token_groups;
    unsigned int length;

} FILE_TOKENS;

FILE_TOKENS make_tokens(const char* filename);
TOKEN_GROUP tokenize(const char* str, unsigned int length);
TOKEN lex(const char* str, unsigned int length);

#endif
