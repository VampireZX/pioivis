#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class PostMachine
{
public:
    PostMachine();
    ~PostMachine();

    void readTape();
    void readInputFile(string);
    void saveStateBefore();
    void saveStateAfter(string);
    string start();

private:
    string tape;
    vector<string> rules;
    unsigned long long tapeIndex;

};
