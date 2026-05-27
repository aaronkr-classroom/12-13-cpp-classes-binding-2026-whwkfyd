#pragma once
#ifndef GUARD_STR_H
#define GUARD_STR_H

#include <algorithm>
#include <iterator>
#include <cstring>
#include "Vec.h"

using namespace std;
class Str {
public:
	typedef Vec<char>::size_type size_type;
	typedef char* iterator;
	typedef const char* const_iterator;

	//생성자들
	Str() { }

	Str(size_type n, char c) : data(n,c) { }

	Str(const char* cp) {
		copy(
			cp, cp + strlen(cp),
			back_inserter(data)
		);
	}

	template<class In> Str(In b, In e) {
		copy(b, e, back_inserter(data));
	}

	size_type size() const { return data.size(); }
	char& operator[](size_type i) { return data[i]; }
const& operator
Str& operator+=(const Str& s) {
	copy(s.data.bgin(), s.data end()),
		(back_inserter(data));
	return *this;
}

iterator begin() { return data.begin(); }
iterator end() { return data.end(); }
iterator insert(iterator d, iterator b)
private:
	Vec<char> data;
};

#endif // !GUARD_STR_J

