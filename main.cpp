#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include "util.cpp"

const std::string CABECALHO = "MV1";
const int ENDERECO_INICIAL = 0;
const int PILHA_INICIAl = 999;
// Declarando estaticamente por conveni�ncia (para faer lookup em fun��es fora do escopo do main sem precisar redeclarar a tabela localmente)
InstructionTable table = InstructionTable();
// O tempFile, que vai ser usado no passo 2, vai ser declarado globalmente, assim como a tabela de s�mbolos, para facilitar o reuso
std::string tempFile;
std::map<std::string, int> symbolTable;
int programSize;

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
    int size = line.size();

    while (end != std::string::npos) {
        tokens.push_back(line.substr(start, (end - start)));
        start = end + delim.size();

        // Pula todos os espaços entre as palavras
        if(start + 1 < size && line[start+1] == ' ')
            start++;
        end = line.find(delim, start);
    }

    tokens.push_back(line.substr(start));

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
	
	return inst.getSize();
}

std::string labelRemover(std::string line){
	std::size_t pos = line.find(":");
	if(pos != std::string::npos)
		line = line.substr(pos+2);
	return line;
}

void writeTempFile(std::string *tempFile, std::string opcode, int length, std::string line) {
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

        instOperator = extractOperator(line);
        
        Instruction inst = table.getInstruction(instOperator);
        if(inst.getIsPseudo()){
        	//Realmente precisa fazer algo? N�o h� necessidade de verifica��o de tipo e a diferen�a de uso da mem�ria j� � indicada na tabela de instru��es
		}
		
		length = getInstructionLength(instOperator);
		writeTempFile(&tempFile, instOperator, length, line);
        location_counter += length;
        
        if (inst.getOpCode() == END_STATEMENT) {
            more_input = false;
        }
    }
}


// Retorna tamanho da instrucao e retira essa informacao do tempFile
int getSize() {
    int pos = tempFile.find(" ");
    std::string strSize = tempFile.substr(0, pos);
    tempFile = tempFile.substr(pos + 1);

    return std::stoi(strSize);
}

// Retorna e remove a primeira linha do tempFile
std::string getNextLine() {
    int pos = tempFile.find("\n");
    std::string line = tempFile.substr(0, pos);
    tempFile = tempFile.substr(pos + 1);

    // Retira espaços do inicio e final da linha
    int start, end;
    for(start = 0; start < line.size(); start++){
        if(line[start] != ' ')
            break;
    }
    
    for(end = line.size() - 1; end >= 0; end--){
        if(line[end] != ' ')
            break;
    }

    return line.substr(start, (end - start) + 1);
}

std::string passTwo(){
    bool more_input = true;         // flag that stops passTwo
    std::string line, output = "";
    int ilc;
    const int END_STATEMENT = -2;   // signals end of input

    ilc = 0; // assemble first instruction at 0

    while (more_input) { // more input set to false by END
        int size = getSize();
        line = getNextLine();
       
        std::vector<std::string> tokens = getTokens(line);
        std::string operador = tokens[0];
        Instruction instruction = table.getInstruction(operador);
        
        ilc += size; // update loc ctr
        
        if (instruction.getOpCode() != END_STATEMENT) {
            if (instruction.getIsPseudo()){
                if (size == 1)
                    output += tokens[1];
            } else {
                output += std::to_string(instruction.getOpCode());

                if (size > 1)
                    output += " " + std::to_string(symbolTable[tokens[1]] - ilc);
                    
            }
            output += " ";
        } else 
            more_input = false;

    }
    programSize = ilc;

    return output;
}

int main () {
    passOne();
    std::string program = passTwo();
    std::string output = CABECALHO + " " + std::to_string(ENDERECO_INICIAL) + " " + std::to_string(PILHA_INICIAl) + " " + std::to_string(programSize) + " " + program;
    std::cout << output;
    return 0;
}
