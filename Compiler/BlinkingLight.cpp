#include "BlinkingLight.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
std::vector<std::string>* MakeBlinking(int numOfBlinks)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    AddCommands(commands, PutValueInRegister(13, "0"));
    AddCommands(commands, CallFunctionWithStorage("initializePin"));
    AddCommands(commands, MakeFunction("start", PutValueInRegister(9, std::to_string(numOfBlinks - 1))));
    AddCommands(commands, MakeFunction("short", CallFunctionWithStorage("blink")));
    AddCommands(commands, DecrementRegisterCallFunctionIfNegative(9, "short"));
    AddCommands(commands, PutValueInRegister(0, "3D0900"));
    AddCommands(commands, StoreValueOnStack(0)); 
    AddCommands(commands, CallFunctionWithoutStorage("delay"));
    AddCommands(commands, CallFunctionWithoutStorage("start", false));
    AddCommands(commands, MakeFunction("delay", LoadValueFromStack(6)));
    AddCommands(commands, MakeFunction("sub", DecrementRegisterCallFunctionIfNegative(6, "sub")));
    commands->push_back("BX RE");
    AddCommands(commands, MakeFunction("initializePin", InitializeGPIOPin()));
    AddCommands(commands, MakeFunction("blink", CreateBlinkFunction(1000000)));
    return commands;
}

void AddCommands(std::vector<std::string>* mainList, std::vector<std::string>* secondaryList)
{
    for (auto command : *secondaryList)
    {
        mainList->push_back(command);
    }
    delete(secondaryList);
}

std::vector<std::string>* PutValueInRegister(int registerNumber, std::string value)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::stringstream stream;
    stream << std::hex << registerNumber;
    std::string registernum = stream.str();
    std::string fixedValue(8 - value.size(), '0');
    std::string total = fixedValue + value;
    commands->push_back("MOVW R" + registernum + ", " + total.substr(4, 4));
    commands->push_back("MOVT R" + registernum + ", " + total.substr(0, 4));
    return commands;
}

std::vector<std::string>* CallFunctionWithStorage(std::string functionName)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    commands->push_back("STMEA RD!");
    commands->push_back("BL <<" + functionName);
    commands->push_back("LDMEA RD!");
    return commands;
}

std::vector<std::string>* MakeFunction(std::string functionName, std::vector<std::string>* commands)
{
    commands->at(0).append(" >>" + functionName);
    return commands;
}

std::vector<std::string>* DecrementRegisterCallFunctionIfNegative(int registerNumber, std::string functionName)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::string registernum = std::to_string(std::stoul(std::to_string(registerNumber), nullptr, 16));
    commands->push_back("SUBS R" + registernum +", R" + registernum + ", 01");
    commands->push_back("BPL <<" + functionName);
    return commands;
}

std::vector<std::string>* StoreValueOnStack(int registerNumber)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::string registernum = std::to_string(std::stoul(std::to_string(registerNumber), nullptr, 16));
    commands->push_back("STREA R" + registernum + ", (RD!), 4");
    return commands;
}

std::vector<std::string>* CallFunctionWithoutStorage(std::string functionName, bool withLink)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::string link = withLink ? "L " : " ";
    commands->push_back("B" + link + "<<" + functionName);
    return commands;
}

std::vector<std::string>* LoadValueFromStack(int registerNumber)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::string registernum = std::to_string(std::stoul(std::to_string(registerNumber), nullptr, 16));
    commands->push_back("LDREA R" + registernum + ", (RD!), 4");
    return commands;
}

std::vector<std::string>* InitializeGPIOPin()
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    AddCommands(commands, PutValueInRegister(4, "3F200000"));
    commands->push_back("ADD R2, R4, 08");
    commands->push_back("LDR R3, (R2)");
    commands->push_back("ORR R3, R33, 008");
    commands->push_back("STR R3, (R2)");
    commands->push_back("BX RE");
    return commands;
}

std::vector<std::string>* CreateBlinkFunction(int delay)
{
    std::vector<std::string>* commands = new std::vector<std::string>;
    std::stringstream stream;
    stream << std::hex << delay;
    std::string delayAmount = stream.str();
    commands->push_back("ADD R3, R4, 1c");
    AddCommands(commands, PutValueInRegister(2, "200000"));
    commands->push_back("STR R2, (R3)");
    commands->push_back("STMEA RD!");
    AddCommands(commands, PutValueInRegister(0, delayAmount));
    commands->push_back("STREA RE, (RD!), 4");
    commands->push_back("STREA R0, (RD!), 4");
    commands->push_back("BL <<delay");
    commands->push_back("LDREA RE, (RD!), 4");
    commands->push_back("LDMEA RD!");
    commands->push_back("ADD R3, R4, 28");
    AddCommands(commands, PutValueInRegister(2, "200000"));
    commands->push_back("STR R2, (R3)");
    commands->push_back("STMEA RD!");
    AddCommands(commands, PutValueInRegister(0, delayAmount));
    commands->push_back("STREA RE, (RD!), 4");
    commands->push_back("STREA R0, (RD!), 4");
    commands->push_back("BL <<delay");
    commands->push_back("LDREA RE, (RD!), 4");
    commands->push_back("LDMEA RD!");
    commands->push_back("BX RE");
    return commands;
}
