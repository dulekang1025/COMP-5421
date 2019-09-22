#include "stdafx.h"
#include "Quad.h"


//
// Created by Lekang Du on 2019-07-10.
//
#include <math.h>
#include <list>
#include <sstream>
#include "Quad.h"
long long int gcd(long long int x, long long int y);
Quad::Quad(long long int x1, long long int x2, long long int x3, long long int x4) {
	quad.push_back(x1);
	quad.push_back(x2);
	quad.push_back(x3);
	quad.push_back(x4);
	standardize();
}

Quad::Quad() {
	quad.push_back(0);
	quad.push_back(1);
	quad.push_back(0);
	quad.push_back(1);
	standardize();
}

Quad::Quad(long long int x1) {
	quad.push_back(x1);
	quad.push_back(1);
	quad.push_back(0);
	quad.push_back(1);
	standardize();
}

Quad::Quad(long long int x1, long long int x2) {
	quad.push_back(x1);
	quad.push_back(x2);
	quad.push_back(0);
	quad.push_back(1);
	standardize();
}

Quad::Quad(long long int x1, long long int x2, long long int x3) {
	quad.push_back(x1);
	quad.push_back(x2);
	quad.push_back(x3);
	quad.push_back(1);
	standardize();
}
// copy ctor
//Quad::Quad(const Quad &p) {
//    this->quad.push_back(p.quad[0]);
//    this->quad.push_back(p.quad[1]);
//    this->quad.push_back(p.quad[2]);
//    this->quad.push_back(p.quad[3]);
//}
// assign op
//Quad& Quad::operator=(const Quad &p) {
//    cout<<"YES"<<endl;
//    this->quad.push_back(p.quad[0]);
//    this->quad.push_back(p.quad[1]);
//    this->quad.push_back(p.quad[2]);
//    this->quad.push_back(p.quad[3]);
//}
// == operator
bool operator==(const Quad &p, const Quad &q) {
	if (p.quad[0] == q.quad[0] && p.quad[1] == q.quad[1] && p.quad[2] == q.quad[2] && p.quad[3] == q.quad[3]) {
		return true;
	}
	else {
		return false;
	}
}

// +
Quad operator+(const Quad &p, const Quad &q) {
	Quad temp;
	temp.quad[0] = p.quad[0] * q.quad[1] + p.quad[1] * q.quad[0];
	temp.quad[1] = p.quad[1] * q.quad[1];
	temp.quad[2] = p.quad[2] * q.quad[3] + p.quad[3] * q.quad[2];
	temp.quad[3] = p.quad[3] * q.quad[3];
	temp.standardize();
	return temp;
}

//*
Quad operator*(const Quad &x, const Quad &y) {
	Quad temp;
	temp.quad[0] = x.quad[0] * y.quad[0] * x.quad[3] * y.quad[3] + 2 * x.quad[2] * y.quad[2] * x.quad[1] * y.quad[1];
	temp.quad[1] = x.quad[1] * y.quad[1] * x.quad[3] * y.quad[3];
	temp.quad[2] = x.quad[0] * y.quad[2] * y.quad[1] * x.quad[3] + y.quad[0] * x.quad[2] * x.quad[1] * y.quad[3];
	temp.quad[3] = x.quad[1] * y.quad[1] * x.quad[3] * y.quad[3];
	temp.standardize();
	return temp;
}

// -
Quad operator-(const Quad &p, const Quad &q) {
	Quad temp;
	temp.quad[0] = p.quad[0] * q.quad[1] - p.quad[1] * q.quad[0];
	temp.quad[1] = p.quad[1] * q.quad[1];
	temp.quad[2] = p.quad[2] * q.quad[3] - p.quad[3] * q.quad[2];
	temp.quad[3] = p.quad[3] * q.quad[3];
	temp.standardize();
	return temp;
}

// is similar
bool Quad::isSimilar(const Quad &p) {
	if (quad[0] * p.quad[1] == p.quad[0] * quad[1] && quad[2] * p.quad[3] == p.quad[2] * quad[3]) {
		return true;
	}
	else {
		return false;
	}
}

// standardlize

void Quad::standardize() {
	// reduced
	long long int xr = gcd(quad[0], quad[1]);
	long long int yr = gcd(quad[2], quad[3]);
	if (quad[1] != 1) {
		quad[0] = quad[0] / xr;
		quad[1] = quad[1] / xr;
	}
	if (quad[3] != 1) {
		quad[2] = quad[2] / yr;
		quad[3] = quad[3] / yr;
	}
	// normalized
	if (quad[1] < 0) {
		quad[0] = quad[0] * -1;
		quad[1] = quad[1] * -1;
	}

	if (quad[3] < 0) {
		quad[2] = quad[2] * -1;
		quad[3] = quad[3] * -1;
	}



}
// gcd
long long int Quad::gcd(long long int x, long long int y) {
	long long int r = y;
	while (x % y != 0) {
		r = x % y;
		x = y;
		y = r;
	}
	return r;
}

// []
long long int& Quad::operator[](int i) {
	if (i - 1 > (quad.size())) {
		std::cout << "invalid argument(”index out of bounds”)";
		//return quad[3];
	}
	else {
		return quad[i - 1];
	}
}

// [] const
long long int Quad::operator [] (int i) const {
	if (i - 1 > (quad.size())) {
		std::cout << "invalid argument(”index out of bounds”)";
		//return quad[3];
	}
	else {
		return quad[i - 1];
	}
}

// another - (infront of quad num)
Quad operator-(const Quad &p) {
	Quad temp{ p };
	temp.quad[0] = -temp.quad[0];
	//temp.quad[1] = -temp.quad[1];
	temp.quad[2] = -temp.quad[2];
	//temp.quad[3] = -temp.quad[3];
	temp.standardize();
	return temp;
}

// op /
Quad operator / (const Quad &x, const Quad &y) {
	Quad yt{ y };
	Quad temp{ x * yt.Inversion() };
	temp.standardize();
	return temp;
}

// inversion
Quad Quad::Inversion() {
	Quad temp;
	long long int a = quad[0] * quad[0] * quad[3] * quad[3] - 2 * quad[1] * quad[1] * quad[2] * quad[2];
	if (a != 0) {
		temp.quad[0] = quad[0] * quad[1] * quad[3] * quad[3];
		temp.quad[1] = a;
		temp.quad[2] = (-1) * quad[1] * quad[1] * quad[2] * quad[3];
		temp.quad[3] = a;
	}
	else {
		cout << "Alpha is 0.";
	}
	temp.standardize();
	return temp;
}

// norm
float Quad::norm() {
	float r = ((float)quad[0] / (float)quad[1]) * ((float)quad[0] / (float)quad[1]) + ((float)quad[2] / (float)quad[3]) * ((float)quad[2] / (float)quad[3]);
	return r;
}

//conjugate
Quad Quad::conjugate() {
	Quad temp;
	temp.quad[0] = quad[0];
	temp.quad[1] = quad[1];
	temp.quad[2] = (-1) * quad[2];
	temp.quad[3] = quad[3];
	temp.standardize();
	return temp;
}

// inverse
Quad Quad::inverse() {
	Quad temp;
	long long int a = quad[0] * quad[0] * quad[3] * quad[3] - 2 * quad[1] * quad[1] * quad[2] * quad[2];
	if (a != 0) {
		temp.quad[0] = quad[0] * quad[1] * quad[3] * quad[3];
		temp.quad[1] = a;
		temp.quad[2] = (-1) * quad[1] * quad[1] * quad[2] * quad[3];
		temp.quad[3] = a;
	}
	else {
		cout << "Alpha is 0.";
	}
	temp.standardize();
	return temp;
}

//normalize

void Quad::normalize() {
	if (quad[1] < 0) {
		quad[0] = quad[0] * -1;
		quad[1] = quad[1] * -1;
	}

	if (quad[3] < 0) {
		quad[2] = quad[2] * -1;
		quad[3] = quad[3] * -1;
	}
}

void Quad::reduce() {
	// reduced
	long long int xr = gcd(quad[0], quad[1]);
	long long int yr = gcd(quad[2], quad[3]);
	if (xr < 0) xr *= (-1);
	if (yr < 0) yr *= (-1);
	if (quad[1] != 1) {
		quad[0] = quad[0] / xr;
		quad[1] = quad[1] / xr;
	}
	if (quad[3] != 1) {
		quad[2] = quad[2] / yr;
		quad[3] = quad[3] / yr;
	}
}

// + op
Quad operator+(Quad p, long long int k) {    //todo: long long int
	Quad temp;
	temp.quad[0] = p.quad[0] + k * p.quad[1];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// + op
Quad operator+(Quad p, int k) {    //todo: long long int
	Quad temp;
	temp.quad[0] = p.quad[0] + k * p.quad[1];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// - op
Quad operator-(Quad p, long long int k) {//todo: long long int
	Quad temp;
	temp.quad[0] = p.quad[0] - k * p.quad[1];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// - op
Quad operator-(Quad p, int k) {
	Quad temp;
	temp.quad[0] = p.quad[0] - k * p.quad[1];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// + op
Quad operator+=(Quad p, long long int k) {//todo: long long int
	p.quad[0] = p.quad[0] + k * p.quad[1];
	return p;
}

// - op
Quad operator-=(Quad p, long long int k) {//todo: long long int
	p.quad[0] = p.quad[0] - k * p.quad[1];
	return p;
}

//pre-increment
void Quad::operator++() {
	*this = *this + 1;

}

// post ++
Quad Quad::operator++(int) {
	Quad temp{ *this };
	*this = *this + 1;
	return temp;
}

//+=
Quad Quad::operator+=(const Quad &p) {
	*this = *this + p;
	return *this;
}

//pre-increment
void Quad::operator--() {
	*this = *this - 1;

}

// post ++
Quad Quad::operator--(int) {
	Quad temp{ *this };
	*this = *this - 1;
	return temp;
}
// *=
Quad Quad::operator*=(const Quad &p) {
	*this = *this * p;
	return *this;
}
// ^
Quad Quad::operator^(int i) {
	Quad temp{ *this };
	if (i > 0) {
		i--;
		while (i > 0) {
			temp.operator*=(*this);
			i--;
		}
	}
	else {
		Quad ttemp{ temp.operator^((-1)*i) };
		temp = ttemp.inverse();
	}
	temp.standardize();
	return temp;
}

// >>
istream & operator >>(istream & in, Quad & quad) {
	cout << "About to create the quad [a, b, c, d]" << endl;
	cout << "Enter four numbers a, b, c, d, in that order:" << endl;
	string  line;
	string num;
	getline(in, line);
	list<long long int> nlist;
	istringstream is(line);
	while (is >> num) {
		nlist.push_back(stoll(num));
	}
	auto it = nlist.begin();
	quad.quad[0] = *it;
	it++;
	quad.quad[1] = *it;
	it++;
	quad.quad[2] = *it;
	it++;
	quad.quad[3] = *it;
	it++;
	return in;
}

//double
Quad::operator double() {
	double r = absoluteValue();
	return r;
}

// absoluteValue
double Quad::absoluteValue() {
	double r = sqrt(norm());
	return r;
}

// int * quad
Quad operator * (long long int k, const Quad &p) {
	Quad temp;
	temp.quad[0] = k * p.quad[0];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = k * p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// quad * k
Quad operator * (const Quad &p, long long int k) {
	Quad temp;
	temp.quad[0] = k * p.quad[0];
	temp.quad[1] = p.quad[1];
	temp.quad[2] = k * p.quad[2];
	temp.quad[3] = p.quad[3];
	temp.standardize();
	return temp;
}

// quad / int
Quad operator / (const Quad &p, long long int k) {
	Quad temp;
	temp.quad[0] = p.quad[0];
	temp.quad[1] = k * p.quad[1];
	temp.quad[2] = p.quad[2];
	temp.quad[3] = k * p.quad[3];
	temp.standardize();
	return temp;
}

// isSimilar(k)
bool Quad::isSimilar(long long int k) {
	
	if (*this == Quad(k)) {
		return true;
	}
	else {
		return false;
	}
}

// op ()
double Quad::operator()() {
	this->standardize();
	return absoluteValue();
}

//// less than
//bool operator < (const Quad p, const Quad q) {
//	if (p.absoluteValue < q.absoluteValue) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//// <=
//bool operator <= (const Quad&p, const Quad&q) {
//	if (p.norm < q.norm || p.norm == q.norm) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//// greater than
//bool Quad::operator > (const Quad&p) {
//	if (this->norm > p.norm) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//// >=
//bool operator >= (const Quad&p, const Quad&q) {
//	if (p.norm > q.norm || p.norm == q.norm) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//// !=
//bool operator!=(const Quad &p, const Quad &q) {
//	if (p == q) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}