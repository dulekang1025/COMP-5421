/**
* The LineList.h defines members and functions of the LineList class
* Class LineList represents a doubly linked list with two dummy node at
* the begin and end.
* It has an inner class Node, Node repesents a node in the doubly linked list.
* @author  Lekang Du 40051703
*/

#ifndef ASSIGNMENT_1_LINELIST_H
#define ASSIGNMENT_1_LINELIST_H

#include "Line.h"

class LineList {
public:

	LineList();
	virtual ~LineList();
	LineList(const LineList& rhs);
	const LineList& operator = (const LineList& rhs);
	void push_front(const Line& line);
	void push_back(const Line& line);
	void pop_front();
	void pop_back();
	int size() const;
	bool empty() const;
	void insert(const Line& line, int k);
	void remove(int k);
	Line get(int k)const;
	void print();



private:
	/**
	* Class node, repesents a node in the doubly linked list.
	* This is a inner class of LineList
	*/
	class Node {
	public:
		Line data{ "" };
		Node* prev{ nullptr };
		Node* next{ nullptr };
		Node(const Line& in, Node* prv, Node* nxt);
	};
	int theSize;
	Node* head;
	Node* tail;

private:
	/**
	* New node method of node, calls class Node's ctor function
	*/
	Node* newNode(const Line &in) {
		Node *temp = new Node(in, nullptr, nullptr);
		temp->data = in;
		return temp;
	}
};


#endif //ASSIGNMENT_1_LINELIST_H


#pragma once
