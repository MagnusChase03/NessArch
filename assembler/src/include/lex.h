#ifndef LEX_H
#define LEX_H

typedef enum {

    INSTRUCTION,
    REGISTER,
    LABEL,
    LABEL_CALL

} Token_Type;

typedef struct {

    Token_Type type;
    char* value;
    int length;

} Token;

typedef struct {

    Token* tokens;
    int length;

} TokenGroup;

int is_alpha(char x);
int is_register(const char* str);

Token lex(const char* str);
TokenGroup lex_line(const char* str);

#endif
