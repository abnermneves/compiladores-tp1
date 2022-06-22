#include <iostream>
#include <string>

std::string readNextLine() {
    // se a linha for vazia, retorna a próxima que não é vazia
    // separa a linha e identifica as partes
}

void initializeTables() {
    // ainda nao sei como vão ser as tabelas
    // talvez só map mesmo, mas acho que a
    // tabela de instruções vai precisar, 
    // além do código numérico, do length também
}

std::string removeComments(std::string line) {
    // retira ; e o que vier depois
    // se tiver
}

std::string checkForSymbols(std::string line) {
    // verifica se tem um label
    // se tiver, retorna o label
    // se não tiver, retorna ""
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
    int location_counter, length, value, type, numeric_code;
    int END_STATEMENT = -2; // provavelmente nao vai ser -2

    location_counter = 0;
    initializeTables();

    while (more_input) {
        length = 0;

        line = readNextLine();
        line = removeComments(line);

        symbol = checkForSymbols(line);
        if (symbol != "") {
            enterNewSymbol(symbol, location_counter);
        }

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
        }
    }
}

int main () {

    return 0;
}