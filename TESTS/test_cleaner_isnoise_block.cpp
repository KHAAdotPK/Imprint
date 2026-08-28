/*
    This file is a test file for the Cleaner class.
    It is used to test the isNoise block of cleanLine method of the Cleaner class.    
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "../lib/src/PunctuationSymbols.hh"
#include "../lib/src/Cleaner.hh"

void printBytes(const std::string& name, const std::string& s)
{
    std::cout << name << " (size=" << s.size() << "): ";
    for (unsigned char c : s)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }
    std::cout << std::dec << std::endl;
}

int main()
{
    Cleaner cleaner;
    std::string input = "François ░ ▒ ▓";
    printBytes("Input", input);
    
    std::string cleaned = cleaner.cleanLine(input);
    printBytes("Cleaned", cleaned);
    
    return 0;
}
