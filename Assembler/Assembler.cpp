#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "MOVE.h"
#include "SingleDataProcessing.h"
#include "SingleDataTransfer.h"
#include "Branch.h"

void append_to_image_file(const std::string& filename, const std::bitset<8>& data) {
    std::ofstream imageFile(filename, std::ios::binary | std::ios::app); // Open file in append mode
    if (!imageFile.is_open()) {
        // File does not exist, attempt to create it
        imageFile.open(filename, std::ios::binary);
        if (!imageFile.is_open()) {
            std::cerr << "Unable to create or open file: " << filename << std::endl;
            return;
        }
    }

    char byte = static_cast<char>(data.to_ulong());
    imageFile.write(&byte, 1);
    imageFile.close();
    std::cout << "Data appended to " << filename << " successfully." << std::endl;
}

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool contains(std::string base, std::string substr)
{
    return base.find(substr) != std::string::npos;
}

std::bitset<4> GetCondCode(std::string token)
{
    if (contains(token, "EQ")) return std::bitset<4>("0000");
    if (contains(token, "NE")) return std::bitset<4>("0001");
    if (contains(token, "CS")) return std::bitset<4>("0010");
    if (contains(token, "CC")) return std::bitset<4>("0011");
    if (contains(token, "MI")) return std::bitset<4>("0100");
    if (contains(token, "PL")) return std::bitset<4>("0101");
    if (contains(token, "VS")) return std::bitset<4>("0110");
    if (contains(token, "VC")) return std::bitset<4>("0111");
    if (contains(token, "HI")) return std::bitset<4>("1000");
    if (contains(token, "LS")) return std::bitset<4>("1001");
    if (contains(token, "GE")) return std::bitset<4>("1010");
    if (contains(token, "LT")) return std::bitset<4>("1011");
    if (contains(token, "GT")) return std::bitset<4>("1100");
    if (contains(token, "LE")) return std::bitset<4>("1101");
    if (contains(token, "AL")) return std::bitset<4>("1110");
    return std::bitset<4>("1110");
}

std::bitset<4>* GetOppCode(std::string token)
{
    if (contains(token, "AND")) return new std::bitset<4>("0000");
    if (contains(token, "EOR")) return new std::bitset<4>("0001");
    if (contains(token, "SUB")) return new std::bitset<4>("0010");
    if (contains(token, "RSB")) return new std::bitset<4>("0011");
    if (contains(token, "ADD")) return new std::bitset<4>("0100");
    if (contains(token, "ADC")) return new std::bitset<4>("0101");
    if (contains(token, "SBC")) return new std::bitset<4>("0110");
    if (contains(token, "RSC")) return new std::bitset<4>("0111");
    if (contains(token, "TST")) return new std::bitset<4>("1000");
    if (contains(token, "TEQ")) return new std::bitset<4>("1001");
    if (contains(token, "CMP")) return new std::bitset<4>("1010");
    if (contains(token, "CMN")) return new std::bitset<4>("1011");
    if (contains(token, "ORR")) return new std::bitset<4>("1100");
    if (contains(token, "MOV")) return new std::bitset<4>("1101");
    if (contains(token, "BIC")) return new std::bitset<4>("1110");
    if (contains(token, "MVN")) return new std::bitset<4>("1111");
    return nullptr;
}

Command* ProcessData(std::string line)
{
    std::vector<std::string> tokens = tokenize(line);
    std::bitset<4> condition = GetCondCode(tokens[0]);
    if (contains(tokens[0], "MOV"))
    {
        std::bitset<4> registry(tokens[1][1]);
        std::bitset<16> immediate(std::stoi(tokens[2]));
        std::string immediateString = immediate.to_string();
        if (contains(tokens[0], "W"))
        {
            return new MOVE(condition.to_string(), MOVE::FRONT, immediateString.substr(0, 4), registry.to_string(), immediateString.substr(4, 12));
        }
        else
        {
            return new MOVE(condition.to_string(), MOVE::BACK, immediateString.substr(0, 4), registry.to_string(), immediateString.substr(4, 12));
        }
    }
    if (GetOppCode(tokens[0]))
    {
        std::string bitShift = "00";
        std::string usingImmediate = "1";
        std::bitset<4>* oppCode = GetOppCode(tokens[0]);
        std::string sBit = "0";
        if (tokens[0].size() > 3)
        {
            sBit = tokens[0][3] == 'S' ? "1" : "0";
        }
        std::bitset<4> registry(tokens[2][1]);
        std::bitset<4> firstRegister(tokens[1][1]);
        std::bitset<12> immediate(std::stoi(tokens[3]));
        return new SingleDataProcessing(condition.to_string(), registry.to_string(), bitShift, usingImmediate, oppCode->to_string(), sBit, firstRegister.to_string(), immediate.to_string());
    }
    if (contains(tokens[0], "LDR") || contains(tokens[0], "STR"))
    {
        std::string bitShift = "01";
        std::string usingImmediate = "0";
        std::string indexingBit = "0";
        std::string upBit = "0";
        std::string wordBit = "0";
        std::string writeBit = "0";
        std::string loadStoreBit = contains(tokens[0], "LDR") ? "1" : "0";
        std::bitset<4> registry(tokens[2][2]);
        std::bitset<4> firstOpperand(tokens[1][1]);
        std::string offset = "000000000000";
        return new SingleDataTransfer(condition.to_string(), registry.to_string(), bitShift, usingImmediate, indexingBit, upBit, wordBit, writeBit, loadStoreBit, firstOpperand.to_string(), offset);
    }
    if (contains(tokens[0], "B"))
    {
        std::string lbit = "0";
        if (tokens[0].size() > 3 || tokens[0].size() == 2)
        {
            lbit = tokens[0][1] == 'L' ? "1" : "0";
        }
        std::bitset<24> offset(std::stoul(tokens[1], nullptr, 16));
        return new Branch(condition.to_string(), "0000", lbit, offset.to_string());
    }
    return nullptr;
}

int main()
{
    std::ifstream inputFile("Resources/blinking.txt");
    std::vector<Command*> commandList;

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        commandList.push_back(ProcessData(line));
    }
    
    for (auto command : commandList)
    {
        std::vector<std::bitset<8>>* bits = command->GetBits();
        append_to_image_file("kernel7.img", bits->at(0));
        append_to_image_file("kernel7.img", bits->at(1));
        append_to_image_file("kernel7.img", bits->at(2));
        append_to_image_file("kernel7.img", bits->at(3));
    }

}

