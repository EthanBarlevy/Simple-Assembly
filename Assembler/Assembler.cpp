#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "MOVE.h"
#include "SingleDataProcessing.h"
#include "SingleDataTransfer.h"
#include "MultiDataTransfer.h"
#include "Branch.h"

// write to the file in a very inefficent way
void append_to_image_file(const std::string& filename, const std::bitset<8>& data) {
    std::ofstream imageFile(filename, std::ios::binary | std::ios::app);
    if (!imageFile.is_open()) {
        imageFile.open(filename, std::ios::binary);
        if (!imageFile.is_open()) {
            std::cerr << "Unable to create or open file: " << filename << std::endl;
            return;
        }
    }

    char byte = static_cast<char>(data.to_ulong());
    imageFile.write(&byte, 1);
    imageFile.close();
}

// break the command up into space separated strings
std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// check if a string contains another string
bool contains(std::string base, std::string substr)
{
    return base.find(substr) != std::string::npos;
}

// all of the possible condition codes
// it may break with more commands but i wont think about that
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

// all of the possible opperation codes for data processing
// again this might break with more commands but for now it works
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

// offset for functions
void ComputeOffsets(std::vector<std::string>& commands)
{
    for (int i = 0; i < commands.size(); i++)
    {
        std::vector<std::string> tokens = tokenize(commands[i]);
        if (contains(tokens[tokens.size() - 1], "<<"))
        {
            std::string function = tokens[tokens.size() - 1].substr(2);
            for (int j = 0; j < commands.size(); j++)
            {
                std::vector<std::string> tokens2 = tokenize(commands[j]);
                if (contains(tokens2[tokens2.size() - 1], ">>" + function))
                {
                    std::stringstream stream;
                    stream << std::hex << (j - i - 2);
                    commands[i] = commands[i].substr(0, commands[i].find("<<")) + stream.str();
                    break;
                }
            }
        }
    }
}

// where everything happens lol
Command* ProcessData(std::string line)
{
    std::vector<std::string> tokens = tokenize(line); // tokenize the command
    std::bitset<4> condition = GetCondCode(tokens[0]); // all commands have a condition code so find it

    if (contains(tokens[0], "MOV")) // this is the worst possible way of doing things but idk a better way
    {
        std::bitset<4> registry(std::stoul(tokens[1].substr(1,1), nullptr, 16));
        std::bitset<16> immediate(std::stoul(tokens[2], nullptr, 16));
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
    if (GetOppCode(tokens[0])) // this is for all data processing commands
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
        std::bitset<12> immediate(std::stoul(tokens[3], nullptr, 16));
        return new SingleDataProcessing(condition.to_string(), registry.to_string(), bitShift, usingImmediate, oppCode->to_string(), sBit, firstRegister.to_string(), immediate.to_string());
    }
    if (contains(tokens[0], "LDR") || contains(tokens[0], "STR")) // this is for load and store commands
    {
        std::string indexingBit = "0";
        std::string upBit = "0";
        std::string writeBit = "0";
        std::bitset<12> offset = 0;
        if (contains(tokens[0], "EA"))
        {
            indexingBit = contains(tokens[0], "LDR") ? "1" : "0";
            upBit = contains(tokens[0], "LDR") ? "0" : "1";
            if (contains(tokens[1], "!"))
            {
                writeBit = "1";
            }
            offset = std::stoul(tokens[3], nullptr, 16);
        }
        std::string bitShift = "01";
        std::string usingImmediate = "0";
        std::string wordBit = "0";
        std::string loadStoreBit = contains(tokens[0], "LDR") ? "1" : "0";
        std::bitset<4> registry(std::stoul(tokens[2].substr(2, 1), nullptr, 16));
        std::bitset<4> firstOpperand(std::stoul(tokens[1].substr(1,1), nullptr, 16));
        return new SingleDataTransfer(condition.to_string(), registry.to_string(), bitShift, usingImmediate, indexingBit, upBit, wordBit, writeBit, loadStoreBit, firstOpperand.to_string(), offset.to_string());
    }
    else if (contains(tokens[0], "LDM") || contains(tokens[0], "STM"))
    {
        std::string indexingBit = "0";
        std::string upBit = "0";
        std::string writeBit = "0";
        if (contains(tokens[0], "EA"))
        {
            indexingBit = contains(tokens[0], "LDR") ? "1" : "0";
            upBit = contains(tokens[0], "LDR") ? "0" : "1";
            if (contains(tokens[1], "!"))
            {
                writeBit = "1";
            }
        }
        std::string loadStoreBit = contains(tokens[0], "LDR") ? "1" : "0";
        std::bitset<4> registry(std::stoul(tokens[1].substr(1, 1), nullptr, 16));
        return new MultiDataTransfer(condition.to_string(), registry.to_string(), indexingBit, upBit, "0", writeBit, loadStoreBit, "0001111111111111");
    }
    if (contains(tokens[0], "B")) // branch commands
    {
        if (contains(tokens[0], "BX"))
        {
            std::bitset<4> registry(std::stoul(tokens[1].substr(1), nullptr, 16));
            return new Branch(condition.to_string(), registry.to_string());
        }
        std::string lbit = "0";
        if (contains(tokens[0], "BL"))
        {
            lbit = "1";
        }
        std::bitset<24> offset(std::stoul(tokens[1], nullptr, 16));
        return new Branch(condition.to_string(), "0000", lbit, offset.to_string());
    }
    return nullptr;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- MAIN -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int main()
{
    std::ifstream inputFile("Resources/test.txt"); // open the txt file
    std::vector<std::string> commandStrings;
    std::vector<Command*> commandList;

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        commandStrings.push_back(line);
    }

    ComputeOffsets(commandStrings); // convert <<[function_name] to the offset number

    for (auto string : commandStrings)
    {
        commandList.push_back(ProcessData(string)); // process each command line by line and add them to a list
    }
    
    std::string outputFile = "kernel7.img";

    for (auto command : commandList)
    {
        std::vector<std::bitset<8>>* bits = command->GetBits(); // format the bits 
        append_to_image_file(outputFile, bits->at(0)); // write it to a file
        append_to_image_file(outputFile, bits->at(1)); // dont question why i have 4
        append_to_image_file(outputFile, bits->at(2)); // i dont understand programming
        append_to_image_file(outputFile, bits->at(3)); // and a compiler is dumb
    }
    std::cout << "All data has been written to " << outputFile << std::endl;
}