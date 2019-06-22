/**
* The Line.cpp implements methods of class Line
* @author  Lekang Du
*/
#include<string>
#include<iostream>
#include<vector>
#include "stdafx.h"
#include"Line.h"
using namespace std;

/**
* Ctor of class Line
* @param text this is a c-string type text
*/
Line::Line(const char *text) {
	lineLength = 0;
	capacity = 1;
	linePtr = new char[2]; // capacity set to 2 to store '/0'
	memset(linePtr, 0, 2);
	for (; text != nullptr && *text != NULL; text++) {
		char temp2 = *text;
		linePtr[length()] = temp2;
		lineLength++;
		if (full()) {
			resize();
		}
	}
}

/**
* Destructor of class Line
*/
Line::~Line() {
	if (linePtr == nullptr) return;
	capacity = 0;
	lineLength = 0;
	delete[] linePtr;   // delete lineptr
}

/**
* Copy ctor of Class Line
* @param Line& l is a variable of type line
*/
Line::Line(const Line &l) {
	linePtr = new char[l.capacity + 1];// capacity need +1 to store '/0'
	strcpy(linePtr, l.linePtr);
	lineLength = l.lineLength;
	capacity = l.capacity;
}

/**
* Overload opeartor = , assign Line rhs to Line lhs
* @param Line& rhs , an object of class Line
*/
const Line& Line::operator=(const Line &rhs) {
	if (this != &rhs) {
		while (capacity < rhs.capacity) {
			resize();
		}
		strcpy(linePtr, rhs.linePtr);
	}
	lineLength = rhs.lineLength;
	capacity = rhs.capacity;
	return *this;
}

/**
* this function returns C-style text of Line
* @return linePtr text of class Line
*/
char* Line::cstr() const {
	return linePtr;
}

/**
* This function returns length of the line
* @return lineLength length of Line
*/
int Line::length() const {
	return lineLength;
}
/**
* This function returns whether this line is empty
* @return true empty; false: not empty
*/
bool Line::empty() const {
	if (lineLength == 0) return true;
	else return false;
}
/**
* This function returns whether this line is full
* @return true: full; false: not full
*/
bool Line::full() const {
	if (lineLength == capacity) return true;
	else return false;
}

/**
* This function returns this line's capacity
* @return capacity capacity of this line
*/
int Line::Capacity() const {
	return capacity;
}

/**
* This function doubles the line's capacity
* if the line is full and re-assign it
*/
void Line::resize() {
	capacity = capacity * 2;
	char *temPtr = new char[capacity + 1];
	memset(temPtr, 0, capacity + 1);   // capacity need +1 to store '/0'
	strcpy(temPtr, linePtr);
	delete[] linePtr;
	linePtr = new char[capacity + 1];
	memset(linePtr, 0, capacity + 1); // capacity need +1 to store '/0'
	strcpy(linePtr, temPtr);
	delete[] temPtr;
	temPtr = nullptr;
}

/**
* This function adds character at the end of the line
*/
void Line::push_back(const char& ch) {
	if (full()) {
		resize();
	}
	linePtr[strlen(linePtr)] = ch;
	lineLength++;
}

/**
* This function removes the last character of the line
*/
void Line::pop_back() {
	linePtr[strlen(linePtr)] = NULL;
	lineLength--;
}

/**
* Op overload <<
* @param out return result
* @param line line which need to be operated
* @return out ostream& type out
*/
ostream& operator << (ostream& out, const Line& line) {
	for (int i = 0; i < line.length(); i++) {
		out << line.cstr()[i];
	}
	return out;
}
/**
* Op overload >>
* @param in return result
* @param line line which need to be operated
* @return out istream& type in
*/
istream& operator >> (istream& in, Line& line) {
	for (int i = 0; i < line.lineLength; i++) {
		in >> line.linePtr[i];
	}
	return in;
}
/**
* Op overload == , compare two line if they are equal
* @param a line at right which will be compared with
* @param b line at right which will be compared with
*/
bool operator == (const Line &a, const Line &b) {
	if (a.length() == b.length()) {
		if (strcmp(a.cstr(), b.cstr()) == 0) {
			return true;
		}
	}
	else {
		return false;
	}
}
/**
* Op overload == , compare two line if they are not equal
* @param a line at right which will be compared with
* @param b line at right which will be compared with
*/
bool operator != (const Line &a, const Line &b) {	// no need to refac
	return !(a == b);
}