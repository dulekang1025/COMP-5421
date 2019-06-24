//
// Created by Lekang Du on 2019-06-22.
//

#ifndef ASSIGNMENT_2_COMMAND_H
#define ASSIGNMENT_2_COMMAND_H
#include "LineEd.h"
#include <iostream>
#include <string>
using namespace std;

class Command {
private:
    std::string command_line;
    bool status;
    string symbol;
    string address1;
    string address2;
public:
    Command(const string& command_line);
    Command();
    void parse(const string& command_line);
    string getSymbol();
    void setSymbol(string symbol);
    string getAddress1();
    string getAddress2();
    bool getStatus();
    void setStatus(bool status);

    string getCommandLine();
    void remove_space(const string& command_line);
    void getInfo();
};


#endif //ASSIGNMENT_2_COMMAND_H
