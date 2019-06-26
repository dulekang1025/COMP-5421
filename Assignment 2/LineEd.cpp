//
// Created by Lekang Du on 2019-06-22.
//

#include "LineEd.h"
#include "Command.h"
#include <iostream>
#include <string>

using namespace std;

LineEd::LineEd(const string fileName) {
    LineEd::file_name = fileName;
    if(file_name == ""){
        curline = 0;
        state = false;
        buffer.clear();
        clipboard.clear();
        cout << "\"?\"" << " " << "[New File]" << endl;
        cout << "Entering command mode." << endl;
    } else{

    }
}

void LineEd::run() {
    string commandLine;
    cout<<"? ";
    getline(cin,commandLine);
    Command com;
    com.parse(commandLine,10,20);  //commandLine,curline,buffer.size()
    while(com.getSymbol() != "q"){
        carryOut(com);
        cout<<"? ";
        getline(cin,commandLine);
        com.parse(commandLine,curline,buffer.size());
    }
}

void LineEd::carryOut(Command &com) {
    if(com.getSymbol() == "a"){
        Appends();
        return;
    }

}

void LineEd::Appends() {
    int count{0};
    int size = buffer.size();
    string temp;
    cin.clear();
    getline(cin,temp);
    while(temp != "Q" && temp != "q"){
        buffer.push_back(temp);
        count++;
        cin.clear();
        getline(cin,temp);
    }
    curline = size + count;
}
