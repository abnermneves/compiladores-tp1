#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>

std::string removeComments(std::string line) {
    // se tiver, retira ; e o que vier depois
    std::regex re("\\s*;.*");
    return std::regex_replace(line, re, "");
}

std::string readNextLine() {
    // retorna a próxima linha que não é vazia sem comentários
    std::string line;
    std::getline(std::cin, line);
    line = removeComments(line);

    while (line.size() == 0) {
        std::getline(std::cin, line);
        line = removeComments(line);
    }

    return line;
}

void initializeTables() {
    // ainda nao sei como vão ser as tabelas
    // talvez só map mesmo, mas acho que a
    // tabela de instruções vai precisar, 
    // além do código numérico, do length também
}

std::string checkForSymbols(std::string line) {
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

void passOne() {
    bool more_input = true;
    std::string line, symbol, literal, opcode; // provavelmente nao vai precisar do literal
    int location_counter, length, value, type; // por enquanto nao ta precisando de type
    int END_STATEMENT = -2; // provavelmente nao vai ser -2

    location_counter = 0;
    initializeTables();

    while (more_input) {
        length = 0;
        line = readNextLine();

        symbol = checkForSymbols(line);
        if (symbol != "") {
            // std::cout << symbol << std::endl;
            // enterNewSymbol(symbol, location_counter);
        }
        /*

        literal = checkForLiteral(line);
        if (literal != "") {
            enterNewLiteral(literal);
        }

        opcode = extractOpcode(line);
        if (opcode == "WORD" || opcode == "END") {
            // verifia se é pseudoinstrução
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
}

int main () {
    passOne();

    return 0;
}