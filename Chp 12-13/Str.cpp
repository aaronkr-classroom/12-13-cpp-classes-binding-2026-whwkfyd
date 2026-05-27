#include <iostream>
#include <iterator>
#include <cstring>

#include "Str.h"

using namespace std;

istream& operator>>(istream& is, Str& s) {
	s.data.clear();

	//띄워쓰기까지 문자 읽기
	char c;
	while (is.get(c) && isspace(c))
		;

	if (is) {
		do s.data.push_back(c);
		while (is.get(c) && !isspace(c))
			;

		//띄어쓰기 있으면 다시 스트림으로 보내기
		if (is) {
			do s.data push_back(c);
			while (is.get(c) && )
		}
	}
}


ostream& operator<<(ostream& os, const Str& s) {
	for (Str::size_type i = 0; i != s.size(); ++i) {
		os << s[i];
	}
}

Str operator+(const Str & s, const Str & t) {
	Str r = s;
	r += t;
	return r;
}
