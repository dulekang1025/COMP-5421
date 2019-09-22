#pragma once
#pragma once
//
// Created by Lekang Du on 2019-07-10.
//

#ifndef A3_QUAD_H
#define A3_QUAD_H


#include <array>
#include <iostream>
#include <vector>

using namespace std;
class Quad {
public:
	//std::array<long long int, 4> quad;
	long long int x1, x2, x3, x4;
	vector<long long int> quad;

	// ctor
	Quad(long long int, long long int, long long int, long long int);

	Quad();

	Quad(long long int);

	Quad(long long int, long long int);

	Quad(long long int, long long int, long long int);

	// copy ctor
	Quad(const Quad &p) = default;

	// assign op
	Quad &operator=(const Quad &) = default;

	// de ctor
	virtual ~Quad() = default;

	// << op
	friend std::ostream& operator<<(std::ostream &out, const Quad &p) {
		out << "[" << p.quad[0] << ", " << p.quad[1] << ", " << p.quad[2] << ", " << p.quad[3] << "]";
		return out;
	}
	// ==
	friend bool operator==(const Quad &, const Quad &);

	// +
	friend Quad operator + (const Quad &, const Quad &);

	// *
	friend Quad operator * (const Quad &, const Quad &);

	// k * quad
	friend Quad operator * (long long int, const Quad &);

	// quad * k
	friend Quad operator * (const Quad &, long long int);

	// -
	friend Quad operator - (const Quad &, const Quad &);

	// is similar
	bool isSimilar(const Quad &);

	// standardize
	void standardize();

	//double
	operator double();

	// absolute value
	double absoluteValue();

	// gcd
	long long int gcd(long long int x, long long int y);

	// []
	long long int& operator [] (int i);

	// [] const
	long long int operator [] (int i) const;

	// another - (infront of quad num)
	friend Quad operator - (const Quad &);

	// op / division
	friend Quad operator / (const Quad &, const Quad &);

	// op / division
	friend Quad operator / (const Quad &, long long int);

	// inversion
	Quad Inversion();

	// inverse
	Quad inverse();

	// norm
	float norm();

	//conjugate
	Quad conjugate();

	//normalize
	void normalize();

	//reduce
	void reduce();

	// + op
	friend Quad operator + (Quad, long long int);

	// + op
	friend Quad operator + (Quad, int);

	// - op
	friend Quad operator - (Quad, long long int);

	// - op
	friend Quad operator - (Quad, int);

	// += op
	friend Quad operator += (Quad, long long int);

	// -= op
	friend Quad operator -= (Quad, long long int);

	//pre-increment
	void operator ++();

	//post-increment
	Quad operator ++(int);

	// +=
	Quad operator +=(const Quad &);

	//pre-increment
	void operator --();

	//post-increment
	Quad operator --(int);

	// *=
	Quad operator*=(const Quad &);

	//^
	Quad operator ^(int);

	//>>
	friend istream & operator >>(istream & in, Quad & quad);

	// isSimilar(k)
	bool isSimilar(long long int k);

	//less than
	friend bool operator < (const Quad, const Quad);

	// <=
	friend bool operator <= (const Quad&, const Quad&);

	// greater than
	bool operator > (const Quad&);

	// >=
	friend bool operator >= (const Quad&, const Quad&);

	// !=
	friend bool operator!=(const Quad &, const Quad &);

	// op ()
	double operator()();
};
#endif //A3_QUAD_H


