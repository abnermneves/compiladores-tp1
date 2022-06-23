#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include "util.cpp"

// Declarando estaticamente por conveni�ncia (para faer lookup em fun��es fora do escopo do main sem precisar redeclarar a tabela localmente)
InstructionTable table = InstructionTable();
// O tempFile, que vai ser usado no passo 2, vai ser declarado globalmente, assim como a tabela de s�mbolos, para facilitar o reuso
std::string tempFile;
std::map<std::string, int> symbolTable;

std::string removeComments(std::string line) {
    // se tiver, retira ; e o que vier depois
    std::regex re("\\s*;.*");
    return std::regex_replace(line, re, "");
}

std::string readNextLine() {
    // remove coment�rios e retorna a pr�xima linha que n�o � vazia
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
    // se n�o tiver, retorna ""
    std::string symbol;
    int colon_idx = line.find(":");

    if (colon_idx == std::string::npos) {
        return "";
    }

    symbol = line.substr(0, colon_idx);
    return symbol;
}

/*std::string checkForLiteral(std::string linha) {
    // procura literais na linha
    // se tiver, retorna o literal
    // se nao tiver, retorna ""
    // ou o qu�? nullptr? NULL? n�o lembro a diferen�a
}

void enterNewLiteral(std::string literal) {

}*/

std::string extractOperator(std::string line) {
    int colon_idx, start, end;
    colon_idx = line.find(":");

    start = 0;
    if (colon_idx != std::string::npos) {
        start = colon_idx + 1;

    }

    // ignora espa�os antes do operador
    for (int i = start; line[i] == ' '; i++) {
        start++;
    }

    end = line.find(" ", start);
    if (end == std::string::npos) {
        end = line.size();
    }

    return line.substr(start, end - start);
}

int getInstructionLength(std::string opcode) {
	Instruction inst = table.getInstruction(opcode);
	//std::cout << inst.getSize();
	return inst.getSize();
}

std::string labelRemover(std::string line){
	std::size_t pos = line.find(":");
	if(pos != std::string::npos)
		line = line.substr(pos+2);
	return line;
}

void writeTempFile(std::string *tempFile, std::string opcode, int length, std::string line) {
    // acho que talvez nao precise desse m�todo
    // vamo ve
    line = labelRemover(line);
    *tempFile = *tempFile + std::to_string(length) + " " + line + "\n";
}

void printSymbolTable(std::map<std::string, int> table) {
    for (auto it = table.begin(); it != table.end(); it++) {
        std:: cout << it->first << " -> " << it->second << std::endl;
    }
}

void passOne() {
    bool more_input = true;
    std::string line, symbol, literal, instOperator; // provavelmente nao vai precisar do literal
    int location_counter, length, value, type; // por enquanto nao ta precisando de type
    int END_STATEMENT = -2;
    location_counter = 0;
    std::map<std::string, int> symbolTable;
    // Instruction table j� inicializada globalmente

    while (more_input) {
        length = 0;
        line = readNextLine(); // pr�xima linha sem coment�rios n�o vazia

        symbol = checkForSymbol(line);
        if (symbol != "") {
            // adiciona s�mbolo na tabela de s�mbolos
            std::pair<std::string, int> symbol_pair (symbol, location_counter);
            symbolTable.insert(symbol_pair);
        }
        /*
        literal = checkForLiteral(line);
        if (literal != "") {
            enterNewLiteral(literal);
        }
        */

        instOperator = extractOperator(line);
        // std::cout << line << std::endl << instOperator << '$' << std::endl;
        
        Instruction inst = table.getInstruction(instOperator);
        if(inst.getIsPseudo()){
        	//Realmente precisa fazer algo? N�o h� necessidade de verifica��o de tipo e a diferen�a de uso da mem�ria j� � indicada na tabela de instru��es
		}
		
		length = getInstructionLength(instOperator);
		writeTempFile(&tempFile, instOperator, length, line);
        location_counter += length;
        if (instOperator == "END") {
            // mudar verifica��o pra tirar a string literal
            more_input = false;
        }
    }
    
    std::cout << "Symbol table:" << std::endl;
	printSymbolTable(symbolTable);
    std::cout << "tempFile:" << std::endl;
    std::cout << tempFile;
}

// std::string passTwo(std::string code, std::map<std::string, int> tabela){
//     InstructionTable instTable = InstructionTable();
//     bool more_input = true;         // flag that stops pass two
//     std::string line, output = "";               // fields of the instruction
//     int ilc;                        // misc. variables
//     const int END_STATEMENT = -2;   // signals end of input

//     ilc = 0; // assemble first instruction at 0

//     while (more_input) { // more input set to false by END
        
//         line = readNextLine();
//         std::vector<std::string> tokens = getTokens(line); // TODO: Checar meio de separar os tokens
//         std::string oper = tokens[0];
//         Instruction instruction = instTable.getInstruction(oper);
        
//         ilc += instruction.getSize(); // update loc ctr
        
//         if (instruction.getOpCode() != END_STATEMENT) {
//             if (instruction.getIsPseudo()){
//                 if (instruction.getSize() == 1)
//                     output += tokens[1];
//             } else {
//                 output += std::to_string(instruction.getOpCode());

//                 if (instruction.getSize() > 1)
//                     output += " " + std::to_string(tabela[tokens[1]] - ilc); // TODO: Calcular endere�o baseado na tabela gerada no passo 1
//             }
//             output += " ";
//         } else 
//             more_input = false;

//     }
// }

int main () {
    passOne();

    return 0;
}
