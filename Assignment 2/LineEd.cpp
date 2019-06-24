//
// Created by Lekang Du on 2019-06-22.
//

#include "LineEd.h"
#include "Command.h"
#include <iostream>
#include <string>

using namespace std;

LineEd::LineEd(string fileName) {
    cout<<"Entering command mode."<<endl;
}

void LineEd::run() {
    string command;
    getline(cin,command);
    Command com = Command(command);
}

