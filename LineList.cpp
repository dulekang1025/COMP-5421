/**
* The LineList.cpp implements methods of class LineList
* @author  Lekang Du
*/

//#include <curses.h>
#include "stdafx.h"
#include "LineList.h"

/**
* Constructor of class LineList
*/
LineList::LineList() {
	this->theSize = 0;
	this->head = new Node("", nullptr, nullptr);
	this->tail = new Node("", nullptr, nullptr);
	head->next = tail;
	tail->prev = head;
}

/**
* Destructor of class LineList
*/
LineList::~LineList() {
	while (!empty()) {
		pop_front();
	}
}

/**
* Copy constructor of class linelist
* @param rhs right side linelist
*/
LineList::LineList(const LineList &rhs) {
	theSize = rhs.size();
	head = new Node("", nullptr, nullptr);
	tail = new Node("", nullptr, nullptr);
	Node *a = head;
	Node *b = rhs.head;
	head->next = tail;
	tail->prev = head;
	for (int i = 0; i<rhs.theSize; i++) {
		b = b->next;
		a->next = new Node("", nullptr, nullptr);
		a->next->data = b->data;
		a->next->prev = a;
		a = a->next;
	}
	tail->prev = a;  // tail.prev -> a(last node)
	a->next = tail;  // last node

}


/**
* Op overload =
* @param rhs List at right side
* @return return copied List
*/
const LineList& LineList::operator = (const LineList &rhs) {
	if (this != &rhs) {
		Node *p = rhs.head;
		while (p) {
			push_back(p->data);
			p = p->next;
		}
	}
	return *this;
}

/**
* This function inserts line at the front of list
* @param line line which need to be added at front
*/
void LineList::push_front(const Line &line) {
	if (head->next == tail) {
		Node *p = newNode(line);
		p->prev = head;
		p->next = tail;
		head->next = p;
		tail->prev = p;
	}
	else {
		Node *p3 = newNode(line);
		p3->prev = head;
		p3->next = head->next;
		head->next->prev = p3;
		head->next = p3;
	}
	this->theSize++;
}

/**
* This function inserts line at the end of list
* @param line line which need to be added at back
*/
void LineList::push_back(const Line &line) {
	if (head->next == tail) {
		Node *p = newNode(line);
		p->prev = head;
		p->next = tail;
		head->next = p;
		tail->prev = p;
	}
	else {
		Node *p1 = newNode(line);
		p1->prev = tail->prev;
		p1->next = tail;
		tail->prev->next = p1;
		tail->prev = p1;
	}
	this->theSize++;
}

/**
* This function remove line at the front of list
*/
void LineList::pop_front() {
	if (head->next == tail) {
		return;
	}
	else {
		Node *p4;
		p4 = head->next;
		head->next = head->next->next;
		p4->next->prev = head;
		delete p4;
	}
	theSize--;
}

/**
* This function remove line at the end of list
*/
void LineList::pop_back() {
	if (head->next == tail) {
		return;
	}
	else {
		Node *p5;
		p5 = tail->prev;
		tail->prev = tail->prev->prev;
		p5->prev->next = tail;
		delete p5;
	}
	theSize--;
}

/**
* This function returns size of the list
* @return theSize size of this list( head and tail not included)
*/
int LineList::size() const {
	return theSize;
}

/**
* This function returns whether the list is empty
* @return true: empty; false: not empty
*/
bool LineList::empty() const {
	if (theSize == 0) return true;
	else return false;
}

/**
* This function inserts a line at position k
* @param line line which need to be inserted
* @param k position which to be instered
*/
void LineList::insert(const Line &line, int k) {
	if (k == 0) {
		return;
	}
	else if (head->next == tail) {
		push_back(line);
	}
	else {
		Node *p5 = newNode(line);
		Node *p6 = head;
		int i = 0;
		while (i<k) {
			p6 = p6->next;
			i++;
		}
		p5->prev = p6->prev;
		p5->next = p6;
		p6->prev->next = p5;
		p6->prev = p5;
	}
	theSize++;
}

/**
* This function removes node at position k
* @param k position which need to remove a node
*/
void LineList::remove(int k) {
	if (k == 0) {
		return;
	}
	else if (head->next == tail) {
		return;
	}
	else {
		Node *p7 = head;
		int i = 0;
		while (i<k) {
			p7 = p7->next;
			i++;
		}
		p7->prev->next = p7->next;
		p7->next->prev = p7->prev;
		delete p7;
	}
	theSize--;
}

/**
* This function returns the kth line of the list
* @param k position
* @return node at position k
*/
Line LineList::get(int k) const {
	if (k < 1 || k > size()) {
		return nullptr;
	}
	else if (head->next == tail) {
		return nullptr;
	}
	else {

		Node *p8;
		p8 = head;
		int i = 0;
		while (i<k) {
			p8 = p8->next;
			i++;
		}
		Line temp = p8->data;
		return p8->data;

	}
}

/**
* This function print the list
*/
void LineList::print() {
	Node *p = head->next;

	for (int i = 0; i < theSize; ++i) {
		if (i >= 10 - 1) {
			cout << "(" << i + 1 << ") ";
		}
		else {
			cout << "( " << i + 1 << ") ";
		}
		cout << p->data << endl;
		p = p->next;
	}
}

/**
* Cotr of Node
*/
LineList::Node::Node(const Line &in, LineList::Node *prv, LineList::Node *nxt) {
	data = in;
	prev = prv;
	next = nxt;
}