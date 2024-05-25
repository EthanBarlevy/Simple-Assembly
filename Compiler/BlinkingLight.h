#pragma once
#include <vector>
#include <iostream>

std::vector<std::string>* MakeBlinking(int numOfBlinks);
void AddCommands(std::vector<std::string>* mainList, std::vector<std::string>* secondaryList);
std::vector<std::string>* PutValueInRegister(int registerNumber, std::string value);
std::vector<std::string>* CallFunctionWithStorage(std::string functionName);
std::vector<std::string>* MakeFunction(std::string functionName, std::vector<std::string>* commands);
std::vector<std::string>* DecrementRegisterCallFunctionIfNegative(int registerNumber, std::string functionName);
std::vector<std::string>* StoreValueOnStack(int registerNumber);
std::vector<std::string>* CallFunctionWithoutStorage(std::string functionName, bool withLink = true);
std::vector<std::string>* LoadValueFromStack(int registerNumber);
std::vector<std::string>* InitializeGPIOPin();
std::vector<std::string>* CreateBlinkFunction(int delay);