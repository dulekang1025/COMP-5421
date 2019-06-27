//
// Created by Lekang Du on 2019-06-22.
//


#include "Command.h"
#include <iostream>
#include <string>
using namespace std;

Command::Command(const string &commandline, int curLine, int bufferSize) {
    Command::parse(commandline, curLine, bufferSize);
    //    Command::command_line = command_line;
    Command::setStatus(false);
}

Command::Command() {

}

void Command::parse(const string &cur_line, int curLine, int bufferSize) {
    Command::remove_space(cur_line);
    //cout<<command_line<<endl;
    Command::getSymbol(curLine, bufferSize);   //getInfo int curline, int bufferSize
    cout<<"In parse: "<<symbol<<endl;
    cout<<"In parse: "<<address1<<" "<<address2<<endl;

}

void Command::setSymbol(string sym) {
    symbol = sym;
}
string Command::getSymbol() {
    return symbol;
}

string Command::getAddress1() {
    return address1;
}

void Command::setAddress1(string address){
    Command::address1 = address;
}

void Command::setAddress2(string address){
    Command::address2 = address;
}

string Command::getAddress2() {
    return address2;
}

void Command::setStatus(bool stat) {
    status = stat;
}

string Command::getCommandLine() {
    return command_line;
}


bool Command::getStatus(){
    return status;
}

void Command::remove_space(const string &cur_line) {
    string temp = cur_line;
    string::iterator it = temp.begin();
    int count{0};
    command_line.clear();
    for(int i = 0; i < temp.length(); i++){
        if(*it != ' '){
//            cout<<count<<endl;
//            count++;
            command_line.push_back(*it);
        }
        it++;
    }
}

void Command::getSymbol(int curline, int bufferSize) {
    //[ command symbol ] [ line address 1 ] [, [ line address 2 ] ]

    // if null
    if(command_line.length() == 0){
        setSymbol("p");
        setAddress1(to_string(curline));
        setAddress2(to_string(curline));
        return;
    }
    // start from here
    string temp;
    temp.push_back(tolower((char)command_line.at(0)));  // ignore upper and lower case
    // bad command
    if(badcommandSet.find(temp) != string::npos){
        cout<<"bad command: "<<temp<<endl;
        setSymbol("");    // no symbol, default to p
        return;
    }
    if(symbolSet.find(temp) == string::npos){
        setSymbol("p");    // no symbol, default to p
        findAddress(command_line,curline,bufferSize);
    } else{
        setSymbol(temp);   // set symbol
        string tempRemovedSym = command_line.substr(1);  // remove symbol
        cout<<"After remove symbol: "<<tempRemovedSym<<endl;
        findAddress(tempRemovedSym,curline,bufferSize);
    }
}

void Command::findAddress(string commRemovedSym,int curline, int bufferSize){

    if(bufferSize == 0){
        if(getSymbol() != "i" && getSymbol() != "a" && getSymbol() != "q" && getSymbol() != "v"){
            cout<<"File empty. Must use one of I,A,Q commands."<<endl;
            return;
        }
    }

    size_t pos = commRemovedSym.find(',');
    int length = (int)commRemovedSym.length();
    string tempAddress1;
    string tempAddress2;
    if(pos != string::npos){   // there is a ','
        if(pos == length - 1 && length != 1){    // p 110, => p 110, 110
            cout<<"Mode: ' x, '"<<endl;
            tempAddress1 = commRemovedSym.substr(0,length - 1);
            tempAddress2 = tempAddress1;
        }
        else if(pos == length - 1 && length == 1){       // ,  => p . , .
            cout<<"Mode: ' , '"<<endl;
            tempAddress1 = to_string(curline);
            tempAddress2 = to_string(curline);
        }
        else if(pos == 0){   // ,y   // , -10  => p . , y
            cout<<"Mode: ' ,y '"<<endl;
            tempAddress1 = to_string(curline);
            tempAddress2 = commRemovedSym.substr(1,length - 1);
        }
        else{  //x,y    // -111，1111 //pos = 4 , x = -111, y = 1111
            cout<<"Mode: ' x,y '"<<endl;
            tempAddress1 = commRemovedSym.substr(0,pos);
            tempAddress2 = commRemovedSym.substr(pos+1);
        }



    } else{                                      // no ','
        if(length == 0){       // null => p ., .
            cout<<"Mode: ' null '"<<endl;
            return;
//            tempAddress1 = to_string(curline);
//            tempAddress2 = to_string(curline);
        } else{                // -100 => p -100, -100
            cout<<"Mode: ' x '"<<endl;
            tempAddress1 = commRemovedSym;
            tempAddress2 = tempAddress1;
        }
    }

    // validate address
    if(!validateAddress(tempAddress1) || !validateAddress(tempAddress2)){
        if(!validateAddress(tempAddress1)){
            cout<<"Bad address 1: "<<tempAddress1<<endl;
            setAddress1("BAD");
            return;
        }
        if(!validateAddress(tempAddress2)){
            cout<<"Bad address 2: "<<tempAddress2<<endl;
            setAddress2("BAD");
            return;
        }
        return;
    }

    // .
    if(tempAddress1 == "."){
        tempAddress1 = to_string(curline);
    }
    if(tempAddress2 == "."){
        tempAddress2 = to_string(curline);
    }

    // ?
    if(tempAddress1 == "$"){
        tempAddress1 = to_string(bufferSize);
        cout<<tempAddress1<<endl;
    }
    if(tempAddress2 == "$"){
        tempAddress2 = to_string(bufferSize);
        cout<<tempAddress2<<endl;
    }
    cout<<"Here luck."<<endl;

    // rules
    int tempA1 = stoi(tempAddress1);
    int tempA2 = stoi(tempAddress2);
    //If a line address is negative,
    // then LineED defaults to the ﬁrst line(0) in the buﬀer.
    if(tempA1 < 0){
        tempAddress1 = "0";
        tempA1 = 0;
    }
    if(tempA2 < 0){
        tempAddress2 = "0";
        tempA2 = 0;
    }
    //7. If a line address exceeds the buﬀer size,
    // then LineED defaults to the last line in the buﬀer.
    if(tempA1 > bufferSize){
        tempAddress1 = to_string(bufferSize);
        tempA1 = bufferSize;
    }
    if(tempA2 > bufferSize){
        tempAddress2 = to_string(bufferSize);
        tempA2 = bufferSize;
    }
    //8. Regardless of how a line range is determined,
    // the ﬁrst line address cannot exceed the second line address;
    // otherwise, LineEd will swap the two line addresses to ensure that
    // the ﬁrst line address is always less than
    // or equal to the second line address.
    if(tempA1 > tempA2){
        cout<<tempA1<<" "<<tempA2<<endl;
        int t = tempA2;
        tempA2 = tempA1;
        tempA1 = t;
        //cout<<tempA1<<" "<<t<<" "<<tempA2<<endl;
        tempAddress1 = to_string(tempA1);
        tempAddress2 = to_string(tempA2);
        //cout<<tempAddress1<<" "<<t<<" "<<tempAddress2<<endl;
    }

    // setAddress
    setAddress1(tempAddress1);
    setAddress2(tempAddress2);
}


bool Command::validateAddress(string address) {
    string characterSet = "qwertyuiopasdfghjklzxcvbnm";
    string numberSet = "0123456789";
    string symbolSet = ".$";

    // only symbol in the address and length must be 1
    if(address.find("$") != string::npos || address.find(".") != string::npos){
        cout<<"symbol check"<<endl;
        if(address.length() != 1) return false;
        if(characterSet.find(address) != string::npos || numberSet.find(address) != string::npos){
            return false;
        } else{
            return true;
        }
    }
    // only number
    if(numberSet.find(address) != string::npos){
        cout<<"number check"<<endl;
        if(address.find(symbolSet)!= string::npos || address.find(characterSet)!= string::npos){
            return false;
        } else{
            return true;
        }
    }
    // if there is characters in the address
    if(address.find(characterSet)!= string::npos){
        return false;
    } else{
        return true;
    }
    cout<<"Cannot reach here."<<endl;

}