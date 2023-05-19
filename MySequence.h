#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Sequence {        
public:              
    Sequence();
    void startWithStr(std::string userInput, std::string nazorSuboru);
    void containsStr(std::string userInput, std::string nazorSuboru);
    void searchMenuSequence();
};



