//
// Created by Lekang Du on 2019-06-22.
//


#include "Command.h"
#include "LineEd.h"
#include <iostream>
#include <string>

using namespace std;

Command::Command(const string &cur_line) {
    Command::parse(cur_line);
    //    Command::command_line = command_line;
    Command::setStatus(false);
}

void Command::parse(const string &cur_line) {
    Command::remove_space(cur_line);
    cout<<command_line<<endl;
    Command::getInfo();
    cout<<symbol<<endl;

}

void Command::setSymbol(string sym) {
    symbol = sym;
}
string Command::getSymbol() {
    return symbol;
}

string Command::getAddress1() {

}

string Command::getAddress2() {

}

void Command::setStatus(bool status) {

}

string Command::getCommandLine() {
    return command_line;
}


bool Command::getStatus(){

}

void Command::remove_space(const string &cur_line) {
    string temp = cur_line;
    string::iterator it = temp.begin();
    int count{0};
    //command_line.clear();
    for(int i = 0; i < temp.length(); i++){
        if(*it != ' '){
//            cout<<count<<endl;
//            count++;
            command_line.push_back(*it);
        }
        it++;
    }
}

void Command::getInfo() {
    //[ command symbol ] [ line address 1 ] [, [ line address 2 ] ]
    string temp;
    temp.push_back(command_line.at(0));
    setSymbol(temp);

}
