#ifndef LEX_H
#define LEX_H

typedef enum {

    INSTRUCTION,
    REGISTER,
    BINARY,
    HEX,
    OPEN_SQUARE,
    CLOSE_SQUARE,
    LABEL,
    LABEL_CALL

} Token_Type;

typedef struct {

    Token_Type type;
    char* value;
    int length;

} Token;

int is_alpha(char c);
int is_digit(char c);
int is_register(const char* str);
int is_instruction(const char* str);

Token lex(const char* str);

#endif
