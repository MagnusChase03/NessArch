#ifndef LEX_H
#define LEX_H

typedef enum {

    INSTRUCTION,
    REGISTER,
    LABEL,
    LABEL_CALL,
    DATA,
    NUMBER

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

typedef struct {

    TokenGroup* token_groups;
    int length;

} FileTokens;

int is_alpha(char x);
int is_digit(char x);
int is_register(const char* str);

Token lex(const char* str);
TokenGroup lex_line(const char* str);
FileTokens lex_file(const char* filepath);

#endif
