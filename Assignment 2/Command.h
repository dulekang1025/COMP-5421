//
// Created by Lekang Du on 2019-06-22.
//

#ifndef ASSIGNMENT_2_COMMAND_H
#define ASSIGNMENT_2_COMMAND_H
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
    string symbolSet = "aivdxjpcungwq";
public:
    Command(const string &commandline, int curLine, int bufferSize);
    Command();
    void parse(const string &cur_line, int curLine, int bufferSize);
    string getSymbol();
    void setSymbol(string symbol);
    string getAddress1();
    string getAddress2();
    bool getStatus();
    void setStatus(bool status);
    void setAddress1(string address1);
    void setAddress2(string address2);
    string getCommandLine();
    void remove_space(const string& command_line);
    void getSymbol(int curline, int bufferSize);
    void findAddress(string commRemovedSym,int curline, int bufferSize);
};


#endif //ASSIGNMENT_2_COMMAND_H
