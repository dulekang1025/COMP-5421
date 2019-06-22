/**
* The Line.h defines members and functions of the Line class
* Class Line represents a single line of text, which has length
* and capacity
* @author  Lekang Du 40051703
*/

#ifndef ASSIGNMENT_1_LINE_H
#define ASSIGNMENT_1_LINE_H

#include <iostream>
using namespace std;

class Line {

private:
	char *linePtr;
	int lineLength;
	int capacity;

public:
	Line(const char *text);
	Line(const Line&);
	const Line &operator = (const Line &rhs);
	virtual ~Line();
	char* cstr() const;
	int length() const;
	bool empty() const;
	bool full() const;
	int Capacity() const;
	void resize();
	void push_back(const char &ch);
	void pop_back();
	friend ostream& operator << (ostream &out, const Line &line);
	friend istream& operator >> (istream &in, Line &line);
	friend bool operator == (const Line &, const Line &);
	friend bool operator != (const Line &, const Line &);

};


#endif //ASSIGNMENT_1_LINE_H
#pragma once
