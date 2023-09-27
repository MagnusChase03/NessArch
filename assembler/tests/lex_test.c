#include "test.h"
#include "../src/include/lex.h"

int main() {

    TEST(is_alpha('a') == 1);
    TEST(is_alpha('z') == 1);
    TEST(is_alpha('A') == 1);
    TEST(is_alpha('Z') == 1);
    TEST(is_alpha('[') != 1);
    TEST(is_alpha('0') != 1);

    TEST(is_digit('0') == 1);
    TEST(is_digit('9') == 1);
    TEST(is_digit('A') != 1);
    TEST(is_digit('z') != 1);
    TEST(is_digit('[') != 1);

    TEST(is_register("ax") == 1);
    TEST(is_register("sp") == 1);
    TEST(is_register("help") != 1);
    TEST(is_register("pc") != 1);
    TEST(is_register("0x01") != 1);

    TEST(is_instruction("mov") == 1);
    TEST(is_instruction("and") == 1);
    TEST(is_instruction("jz") == 1);
    TEST(is_instruction("0x0b") != 1);
    TEST(is_instruction("help") != 1);
    TEST(is_instruction("ax") != 1);

    TEST(is_hex('0') == 1);
    TEST(is_hex('9') == 1);
    TEST(is_hex('F') == 1);
    TEST(is_hex('E') == 1);

    Token token = lex("ax");
    TEST(token.type == REGISTER);
    token = lex("ds");
    TEST(token.type == REGISTER);
    token = lex("[");
    TEST(token.type == OPEN_SQUARE);
    token = lex("]");
    TEST(token.type == CLOSE_SQUARE);
    token = lex("mov");
    TEST(token.type == INSTRUCTION);
    token = lex("jz");
    TEST(token.type == INSTRUCTION);
    token = lex("hello");
    TEST(token.type == LABEL_CALL);
    token = lex("hello:");
    TEST(token.type == LABEL);
    token = lex("0x0FEDBA15");
    TEST(token.type == HEX);
    token = lex("0b0101011");
    TEST(token.type == BINARY);
}
