//
// Created by Lekang Du on 2019-06-22.
//

#include "LineEd.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <fstream>

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
        ifstream infile(fileName);
        if(!infile.is_open()){
            cout<<"Can not open file"<<endl;
        } else{
            string temp;
            while(!infile.eof()){
                getline(infile,temp);
                Appends(temp);
            }
            state = false;
            cout<<"\""<< file_name<<"\""<<buffer.size()<<" lines"<<endl;
            cout << "Entering command mode." << endl;
        }
    }
}

void LineEd::runCommand(string command) {
    Command com;
    com.parse(command,curline,buffer.size());  //commandLine,curline,buffer.size()
    if(com.getSymbol() != ""){
        carryOut(com);
    }

}

void LineEd::run() {
    string commandLine;
    cout<<"? ";
    getline(cin,commandLine);
    Command com;
    com.parse(commandLine,curline,buffer.size());  //commandLine,curline,buffer.size()
    while(com.getSymbol() != "q"){
        if(com.getSymbol() == ""){
            cout<<"? ";
            getline(cin,commandLine);
            com.parse(commandLine,curline,buffer.size());
            continue;
        }
        carryOut(com);
        cout<<"? ";
        getline(cin,commandLine);
        com.parse(commandLine,curline,buffer.size());
    }

    if(com.getSymbol() == "q"){
        carryOut(com);
    }
}

void LineEd::carryOut(Command &com) {
    if(com.getSymbol() == "a"){
        Appends();
        return;
    }

    if(com.getSymbol() == "p"){
        Prints(com.getAddress1(),com.getAddress2());
        return;
    }

    if(com.getSymbol() == "i"){
        Inserts(stoi(com.getAddress1()));
        return;
    }

    if(com.getSymbol() == "d"){
        Deletes(com.getAddress1(),com.getAddress2());
    }

    if(com.getSymbol() == "u"){
        Up();
    }

    if(com.getSymbol() == "n"){
        Down();
    }

    if(com.getSymbol() == "g"){
        Goes(com.getAddress1());
    }

    if(com.getSymbol() == "q"){
        Quit();
    }
}

void LineEd::Appends() {
    int count{0};
    int size = buffer.size();
    string temp;
    cin.clear();
    getline(cin,temp);
    while(temp != "."){
        buffer.push_back(temp);
        count++;
        cin.clear();
        getline(cin,temp);
    }
    curline = size + count;
    cout<<"Curline is "<<curline<<endl;
}

void LineEd::Prints(string address1,string address2) {
    if(buffer.size() == 0){
        return;
    }
    if(address1 == "BAD"){
        return;///////////////////////////////////////////
    }
    if(address2 == "BAD"){
        return;///////////////////////////////////////////
    }
    if(address1 == ""){
        address1 = to_string(curline);///////////////////////////////////////////
    }
    if(address2 == ""){
        address2 = to_string(curline);///////////////////////////////////////////
    }
    auto it = buffer.begin();
    advance(it,stoi(address1)-1);
    if(address1 == address2){
        cout<<address1<< ">  " << *it<<endl;
    } else{
        for(int curr = stoi(address1);curr <= stoi(address2);curr++,it++){
            if(curr != stoi(address2)){
                cout <<curr<< ":  " << *it << endl;
            } else{
                cout <<curr<< ">  " << *it << endl;
            }
        }
    }
}

void LineEd::Inserts(int line) {
    int count{0};
    if(buffer.size() == 0){
        cout<<"Buffer is empty, insert from line 1."<<endl;
        Appends();
    }else if(line > buffer.size()){
        cout<<"Insert line number is larger than buffer size, insert after the last line."<<endl;
        Inserts(buffer.size());
    } else{
        string temp;
        cin.clear();
        clipboard.clear();
        getline(cin,temp);
        while(temp != "."){
            clipboard.push_back(temp);
            getline(cin,temp);
        }
        auto it = buffer.begin();
        advance(it,line-1);
        buffer.insert(it, clipboard.begin(),clipboard.end());
        curline = line + clipboard.size() - 1;
    }
    cout<<"Curline is "<<curline<<endl;
}

void LineEd::Pastes(int line) {

}

void LineEd::Deletes(string address1, string address2) {
    if(buffer.size() == 0){
        cout<<"Buffer is empty, can not delete.";
    } else{
        auto it1 = buffer.begin();
        auto it2 = buffer.begin();
        advance(it1,stoi(address1) - 1);
        advance(it2,stoi(address2));
        buffer.erase(it1,it2);
        if(stoi(address2) < buffer.size()){
            curline = stoi(address1);
        }
        if(stoi(address2) == 1){
            curline = 1;
        }
        if(stoi(address2) == buffer.size()){
            curline = stoi(address1) - 1;
        }
        if(buffer.size() == 0){
            curline = 0;
        }
    }
    cout<<"Curline is "<<curline<<endl;
}

void LineEd::Up() {
    if(curline == 1){
        cout<<"BOF reached."<<endl;
    } else{
        curline = curline - 1;
    }
    auto it = buffer.begin();
    advance(it,curline-1);
    cout<<curline<<"> "<<*it<<endl;
}

void LineEd::Down() {
    if(curline == buffer.size()){
        cout<<"EOF reached."<<endl;
    } else{
        curline = curline + 1;
    }
    auto it1 = buffer.begin();
    advance(it1,curline-1);
    cout<<curline<<"> "<<*it1<<endl;
}

void LineEd::Goes(string address1) {
    if(address1 == "0"){
        curline = 1;
        auto it = buffer.begin();
        advance(it,curline-1);
        cout<<curline<<"> "<<*it<<endl;
    } else{
        curline = stoi(address1);
        auto it = buffer.begin();
        advance(it,curline-1);
        cout<<curline<<"> "<<*it<<endl;
    }
}

void LineEd::Writes(string fileName) {
    if(fileName.size() != 0){
        file_name = fileName;
        ofstream outfile ("Assignment 2/" + file_name);   //Assignment 2/as.txt
        auto it = buffer.begin();
        for(it;it != buffer.end();it++){
            outfile<<*it<<endl;
        }
    } else{
        ofstream outfile (file_name);
        auto it = buffer.begin();
        for(it;it != buffer.end();it++){
            outfile<<*it<<endl;
        }
    }
    cout<<buffer.size()<<" lines written to file "<<"\""<< file_name<<"\""<<endl;
    state = true;
}

void LineEd::Quit() {
    string tempYesNo;
    if (!state) {
        if (file_name.size() == 0) {
            cout << "There are unsaved changes.\nDo you wish to save the changes (y or n)?" << endl;
            cin.clear();
            getline(cin, tempYesNo);
            if (tempYesNo == "y" || tempYesNo == "Y") {
                string temp;
                cout << "Enter the name of a file to write to: " << endl;
                cin.clear();
                getline(cin, temp);
                Writes(temp);
            }
        } else {
            cout << "Save the changes to the file:" << file_name << " (y or n)?" << endl;
            cin.clear();
            getline(cin, tempYesNo);
            if (tempYesNo == "y" || tempYesNo == "Y") {
                Writes("");
            }
        }
        cout<<"bye"<<endl;
    }
}

void LineEd::Appends(string line) {
    int count{0};
    int size = buffer.size();
    buffer.push_back(line);
    count++;
    curline = size + count;
    cout<<"Curline is "<<curline<<endl;
}
