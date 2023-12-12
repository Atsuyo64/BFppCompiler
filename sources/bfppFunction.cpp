#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "bfppFunction.h"

std::string tabGen(int numberOfTabs)
{
    std::string rtn = "";
    for (size_t i = 0; i < numberOfTabs; i++)
    {
        rtn += TAB;
    }
    return rtn;
}

/* FUNCTION GENERATOR */

bfppFunction::bfppFunction(std::string functionName) : name(functionName)
{
}

bfppFunction::~bfppFunction()
{
}

std::string bfppFunction::toStr()
{
    std::string rtn = "";
    if (name == "main")
    {
        rtn += name + "int main()\n{\n";
        rtn += TAB + "std::vector<uchar> memory;\n";
        rtn += TAB + "memory.emplace_back(0);\n";
        rtn += TAB + "int cursor(0);\n";
    }
    else
    {
        rtn += "void " + name + "()\n{\n";
    }

    rtn += content;
    rtn += "}\n\n";
    return rtn;
}

void bfppFunction::addOB()
{
    content += tabGen(height) + "while (memory[cursor] > 0)\n{\n";
    height++;
}

bool bfppFunction::addCB()
{
    if (height > 1)
    {
        height--;
        content += tabGen(height) + "}\n";
        return false;
    }
    return true;
}

void bfppFunction::addPlus()
{
    content += tabGen(height) + "memory[cursor]++;\n";
}

void bfppFunction::addMinus()
{
    content += tabGen(height) + "memory[cursor]--;\n";
}

void bfppFunction::addLeft()
{
    content += tabGen(height) + "if (moveLeft(cursor)) {\n";
    content += tabGen(height+1) + "std::cout << 'FATAL ERROR: Cursor can not go before position 0!\\n';\n";
    content += tabGen(height) + "}\n";
}

void bfppFunction::addRight()
{
    content += tabGen(height) + "moveRight(memory, cursor);\n";
}

void bfppFunction::addCin()
{
    content += tabGen(height) + "\n";
}

void bfppFunction::addCout()
{
    content += tabGen(height) + "\n";
}


bool bfppFunction::validFinalHeight()
{
    return height == 1;
}