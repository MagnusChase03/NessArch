#include "test.h"
#include "../src/include/lex.h"

int main() {
    
    TEST(is_register("ax") == 1);
    TEST(is_register("dx") == 1);
    TEST(is_register("blah") != 1);

    TEST(is_alpha('a') == 1);
    TEST(is_alpha('z') == 1);
    TEST(is_alpha('0') != 1);

    TEST(is_digit('9') == 1);
    TEST(is_digit('0') == 1);

    Token token = lex("ax");
    TEST(token.type == REGISTER);
    token = lex("sub");
    TEST(token.type == INSTRUCTION);
    token = lex("label:");
    TEST(token.type == LABEL);
    token = lex("label");
    TEST(token.type == LABEL_CALL);
    token = lex(".data");
    TEST(token.type == DATA);
    token = lex("256");
    TEST(token.type == NUMBER);

    TokenGroup tokens = lex_line("loop: sub ax bx loop");
    TEST(tokens.length == 5);
    TEST(tokens.tokens[0].type == LABEL);
    TEST(tokens.tokens[1].type == INSTRUCTION);
    TEST(tokens.tokens[2].type == REGISTER);
    TEST(tokens.tokens[3].type == REGISTER);
    TEST(tokens.tokens[4].type == LABEL_CALL);

    tokens = lex_line("loop: .data 0");
    TEST(tokens.length == 3);
    TEST(tokens.tokens[0].type == LABEL);
    TEST(tokens.tokens[1].type == DATA);
    TEST(tokens.tokens[2].type == NUMBER);

}
