#pragma once

#ifndef GUARD_VEC_H
#define GUARD_VEC_H
#include <memory>
#include <algorithm>
#include <cstddef>

using namespace std;
class Str {

};
template <class T> class Vec {
public:
	//속성
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	/*
	Vec<int> grades;
	Vec<int> pass;
	pass = grades;
	1. operator= 필요
	2. Vec() 사본 만든 생성자
	*/
	
	//생산자
	
	//빈 객체
    Vec() { create(); };
	explicit Vec(size_type n, const T& val = T()) { create(n, val); }
	Vec(const Vec& v) { create(v.begin(), v.end()); };

	//벡터 크기와 인덱스에 관한 새로운 함수들
	size_type size() const { return avail - data;  }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) { return data[i]; }

	Vec& operator=(const Vec&);

	//반복자를 반환하는 새로운 함수
	iterator begin() { return data; }
	const_iterator begin() const { return data; }
	iterator end() { return avail;  }
	const_iterator end() const { return avail; }

	template<class In> iterator insert(iterator, In, In);
	void asssign(iterator iterator;)
	//인터페이스
	void push_back(const T& val) {
		if (avail == limit) // 필요하다면 저장 공간 확보
			grow();

		unchecked_append(val); //새로운 요소 추가
	}
	//11-9를 위해 추가
	
	void push_back_grow_once(const T& t) {
		grow_once();
		unchecked_append();
	}
	//소멸자
	~Vec(); { uncreate(); }
	void clear() { uncreate(); };
	bool empty() const { return data == avail; } // 0 == 0? True
private:
	iterator data;//
	iterator avail;//vec 마지막 요소 다음을 가리키는 포인터
	iterator limit; //사용할 수 있는 마지막 요소의 다음을 가르키는 포인처

	allocator<T> alloc; //메모리 할당 위해 관리하는 객체

	//멤버 함수
	//생성자: 메모리 할당 + 값 초기화 함수
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	//소멸자: 메모리 삭제
	void uncrate();
	//유틸리티 함수들 push_back의 지원 함수
	void grow();
	void grow_once();
	void unchecked_append(const T&);
};

template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	// int i = 0
	// lhs = 변수
	// rhs = 값
	//자가 할당 여부 확인
	if (&rhs != this) {
		//좌변이 지닌 배열이 점유하는 메모리를 해제
		uncreate();

		//우변이 지닌 요소를 좌변으로 복사
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

template <class T> void Vec<T>::create() {
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val) {
	data = alloc.allocate(); //#include <memory>
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

template <class T>
void Vec<T>::uncrate() {
	if (data) {
		//역순서대로 모든 요소를 소멸하고 메모리 해제
		iterator it = avail;//마지막 요소 다음에 가리키는 포인터
		while (it != data) //촛본째 요소를 가리키는 포인터까지
			alloc.destroy(--it);

		//할당한 메모리 공간을 해제 (비우기)
		alloc.deallocate(data, limit - data);
	}
	//모든 포인터를 재정의 (재설정)
	data = limit = avail = 0;
}

template <class T>
void Vec<T>::unchecked_append(const T& val) {
	// avail = 할당되지 않은 사용 가능 공간
	alloc.construct(avail++, val);
}

// 사용 가능한 공간은 다 채우면 
// 벡터 크기를 2배로 증가하는 함수
template <class T>
void Vec<T>::grow() {
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

	//새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	//전에 있던 공간을 소멸
	uncreate();

	//모든 포인터를 새로운 공간에서 가리킴
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

// 11-9
template <class T>
void Vec<T>::grow_once() {
	size_type new_size = limit - data + ptrdiff_t(1);

	//새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	//전에 있던 공간을 소멸
	uncreate();

	//모든 포인터를 새로운 공간에서 가리킴
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

template <class T>
template <class In>
typename Vec<T>::iterator Vec<T>::insert(iterator d, In b, In e)
Vec<T>end(d, avail);
ptrdiff_t diff = d - data;

if (d) {
	while (avail)


}

while (b != e) {
push_back(*b++);

for (Vec<T>::const_iterator it = end.begin();
	it !+ end.end(); it++)
	push_back(*it);

return data + diff;
}

template <class T> 
void Vec<T>::assign(iterator b, iterator e) {

}
istream& operator>>(istream&, Str&);
ostream& operator<<(ostream&, const Str&);
Str operator+(const Str&, const Str&);
#endif
