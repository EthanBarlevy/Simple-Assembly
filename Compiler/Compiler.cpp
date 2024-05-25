#include <iostream>
#include <fstream>
#include "BlinkingLight.h"

int main()
{
    int blinks;
    std::cout << "How many times should the light blink?\n:: ";
    std::cin >> blinks;
    auto commands = MakeBlinking(blinks);
    std::ofstream outFile("Resources/output.txt");

    if (!outFile) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return 1;
    }

    for (const std::string& str : *commands) {
        outFile << str << std::endl;
    }

    outFile.close();
}