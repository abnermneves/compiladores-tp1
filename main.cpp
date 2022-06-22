#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include "util.cpp"

std::string removeComments(std::string line) {
    // se tiver, retira ; e o que vier depois
    std::regex re("\\s*;.*");
    return std::regex_replace(line, re, "");
}

std::string readNextLine() {
    // remove comentários e retorna a próxima linha que não é vazia
    std::string line;

    do {
        std::getline(std::cin, line);
        line = removeComments(line);
    } while(line.size() == 0);

    return line;
}

std::vector<std::string> getTokens(std::string line) {
    std::vector<std::string> tokens;
    std::string delim = " ";
    int start = 0;
    int end = line.find(delim);

    while (end != -1) {
        tokens.push_back(line.substr(start, end - start));
        start = end + delim.size();
        end = line.find(delim, start);
    }
    
    return tokens;
}

std::string checkForSymbol(std::string line) {
    // se tiver label, retorna o label
    // se não tiver, retorna ""
    std::string symbol;
    int colon_idx = line.find(":");

    if (colon_idx == std::string::npos) {
        return "";
    }

    symbol = line.substr(0, colon_idx);
    return symbol;
}

std::string checkForLiteral(std::string linha) {
    // procura literais na linha
    // se tiver, retorna o literal
    // se nao tiver, retorna ""
    // ou o quê? nullptr? NULL? não lembro a diferença
}

void enterNewSymbol(std::string symbol, int location_counter) {

}

void enterNewLiteral(std::string literal) {

}

std::string extractOpcode(std::string line) {

}

int getInstructionLength(std::string opcode) {

}

void writeTempFile(std::string opcode, int length, std::string line) {
    // acho que talvez nao precise desse método
    // vamo ve
}

void printSymbolTable(std::map<std::string, int> table) {
    for (auto it = table.begin(); it != table.end(); it++) {
        std:: cout << it->first << " -> " << it->second << std::endl;
    }
}

void passOne() {
    bool more_input = true;
    std::string line, symbol, literal, opcode; // provavelmente nao vai precisar do literal
    int location_counter, length, value, type; // por enquanto nao ta precisando de type
    int END_STATEMENT = -2; // provavelmente nao vai ser -2

    location_counter = 0;
    std::map<std::string, int> symbolTable;
    // inicializar instructionTable, acho que vai precisar do codigo numerico do opcode e do length

    while (more_input) {
        length = 0;
        line = readNextLine(); // próxima linha sem comentários não vazia

        symbol = checkForSymbol(line);
        if (symbol != "") {
            // adiciona símbolo na tabela de símbolos
            // ainda precisa da instruction table pra atualizar o location_counter
            // então por enquanto a localização tá tudo zerado
            std::pair<std::string, int> symbol_pair (symbol, location_counter);
            symbolTable.insert(symbol_pair);
        }
        /*

        literal = checkForLiteral(line);
        if (literal != "") {
            enterNewLiteral(literal);
        }

        opcode = extractOpcode(line);
        if (opcode == "WORD" || opcode == "END") {
            // verifica se é pseudoinstrução
            // com certeza dá pra melhorar essa verificação
            // para não ficar essas strings avulsas
            // mas isso é só temporário

            // como só tem word e end, acho que não vai precisar
            // de uma tabela de pseudoinstruções, nem da variável type
        }

        length = getInstructionLength(opcode);

        writeTempFile(opcode, length, line);

        location_counter += length;

        if (opcode == "END") {
            // mudar verificação pra tirar a string literal
            more_input = false;
        }*/

        if (line == "END") {
            more_input = false;
        }
    }
    // printSymbolTable(symbolTable);
}

std::string passTwo(std::string code, std::map<std::string, int> tabela){
    InstructionTable instTable = InstructionTable();
    bool more_input = true;         // flag that stops pass two
    std::string line, output = "";               // fields of the instruction
    int ilc;                        // misc. variables
    const int END_STATEMENT = -2;   // signals end of input

    ilc = 0; // assemble first instruction at 0

    while (more_input) { // more input set to false by END
        
        line = readNextLine();
        std::vector<std::string> tokens = getTokens(line); // TODO: Checar meio de separar os tokens
        std::string oper = tokens[0];
        Instruction instruction = instTable.getInstruction(oper);
        
        ilc += instruction.getSize(); // update loc ctr
        
        if (instruction.getOpCode() != END_STATEMENT) {
            if (instruction.getIsPseudo()){
                if (instruction.getSize() == 1)
                    output += tokens[1];
            } else {
                output += std::to_string(instruction.getOpCode());

                if (instruction.getSize() > 1)
                    output += " " + std::to_string(tabela[tokens[1]] - ilc); // TODO: Calcular endereço baseado na tabela gerada no passo 1
            }
            output += " ";
        } else 
            more_input = false;

    }
}

int main () {
    passOne();

    return 0;
}