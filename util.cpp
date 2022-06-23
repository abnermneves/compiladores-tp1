#ifndef UTIL
#define UTIL

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Instruction{
    int8_t opCode;
    uint8_t size;
    bool isPseudo;

    public:
        Instruction(){
            
        }

        Instruction(int8_t opCode, uint8_t size, bool isPseudo) {
            this->opCode = opCode;
            this->size = size;
            this->isPseudo = isPseudo;
        }

        int8_t getOpCode() {return opCode;}
        uint8_t getSize() {return size;}
        bool getIsPseudo() {return isPseudo;}

};

class InstructionTable {
    private:
        map<string, Instruction> instructionTable;
    
    public:
        InstructionTable() {
            instructionTable["LOAD"] = Instruction(1, 2, false);
            instructionTable["STORE"] = Instruction(2, 2, false);
            instructionTable["ADD"] = Instruction(3, 2, false);
            instructionTable["SUB"] = Instruction(4, 2, false);
            instructionTable["JMP"] = Instruction(5, 2, false);
            instructionTable["JPG"] = Instruction(6, 2, false);
            instructionTable["JPL"] = Instruction(7, 2, false);
            instructionTable["JPE"] = Instruction(8, 2, false);
            instructionTable["JPNE"] = Instruction(9, 2, false);
            instructionTable["PUSH"] = Instruction(10, 2, false);
            instructionTable["POP"] = Instruction(11, 2, false);
            instructionTable["READ"] = Instruction(12, 2, false);
            instructionTable["WRITE"] = Instruction(13, 2, false);
            instructionTable["CALL"] = Instruction(14, 2, false);
            instructionTable["RET"] = Instruction(15, 1, false);
            instructionTable["HALT"] = Instruction(16, 1, false);
            instructionTable["WORD"] = Instruction(-1, 1, true);
            instructionTable["END"] = Instruction(-2, 0, true);
        }

        Instruction getInstruction(string label){
            return instructionTable[label];
        }
};

#endif