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

char DIGITS[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char ALPHA[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char HEX_PREFIX[3] = "0x";
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

FILE_TOKENS make_tokens(const char* filename);
TOKEN_GROUP tokenize(const char* str, unsigned int length);
TOKEN lex(const char* str, unsigned int length);

#endif
