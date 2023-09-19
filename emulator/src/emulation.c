#include "./include/emulation.h"

#include <stdio.h>

unsigned char PC = 0b00000000;
unsigned char SP = 0b11111111;

unsigned char AX;
unsigned char BX;
unsigned char CX;
unsigned char DX;

unsigned char MEMORY[255];

void run(const char* filepath) {
    for (int i = 0; i < sizeof(MEMORY); i++) {
        MEMORY[i] = '\0';
    }

    FILE* file = fopen(filepath, "r");
    
    unsigned char index = 0;
    char buffer = fgetc(file);
    while (buffer != EOF) {
        MEMORY[index] = buffer;
        buffer = fgetc(file);
        index += 1;
    }

    while (PC < (unsigned char) 255) {
        handle_instruction(MEMORY[PC]);
        PC += 1;
    }
}

void handle_instruction(unsigned char instruction) {

    unsigned char op_code = 0b11110000 & instruction;
    unsigned char reg0 = 0b00001100 & instruction >> 2;
    unsigned char reg1 = 0b00000011 & instruction;
    unsigned char label_jump = 0b00001111 & instruction;
    if (op_code == 0b00000000) {
    }

}

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("[USAGE] ./bin/emulation <filepath>\n");
        return 1;
    }

    run(argv[1]);

}
