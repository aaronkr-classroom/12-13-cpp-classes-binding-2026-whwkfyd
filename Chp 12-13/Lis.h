#pragma once

#ifndef GUARD_LIS_H
#define GUARD_LIS_H

#include <memory>

template <class T> class Node {
public:
	T value; //값 주기
	Node<T>* next;
	Node<T>* prev;

	//생성자
	Node() : value(0), next(0), prev(0) { } //초기화
	Node(T t) : value(t), next(0), prev(0) { } //값 있으면

};

template <class T> class NodeItr {
public:
	NodeItr& operator++(); //증가 연산자
	NodeItr& operator--(); //감소 연산자
	NodeItr operator++(int);
	NodeItr operator--(int);
	T& operator*() const { return node->value;  } //포인터
	bool operator !=(const Nodeltr& rhs) const {
		return node != rhs.node;
	}

	//생성자
	NodeItr(Node<T>* n) : node(n) { }

private:
	Node<T>* node;
};

template <class T> NodeItr<T>& NodeItr<T>::operator++() {
	node = node->next;
	return *this;
}

template <class T> NodeItr<T>& NodeItr<T>::operator--() {
	node = node->prev;
	return *this;
}

template <class T> NodeItr<T>& NodeItr<T>::operator++(int) {
	node = node->next;
	return *this;
}

template <class T> NodeItr<T>& NodeItr<T>::operator--(int) {
	node = node->prev;
	return *this;
}

template <class T> class Lis {
public:
	typedef NodeItr<T> iterator;
	typedef const NodeItr<T> const_iterator;
	typedef size_t size_type;

	//생성하고 초기화
	Lis() : b(0), e(0), s(0) { }
	explict Lis(size_type n, const T& t = T()) { create(n, t); }
	Lis(const Lis& v) { create(v.begin(), v.end()); }
	Lis& operator=(const Lis&);
	~Lis() { uncreate();  }

	void push_back(const T& t);
	size_type size() const { return s;  }

	iterator begin() { return b;  }
	const_iterator begin() const { return b;  }

	iterator end() { return e; }
	const_iterator end() const { return e; }

	void clear() { uncreate(); }
	bool empty() const { return s == 0; }

private:
	Node<T>* b; //시작하는 포인터
	Node<T>* e;//끝 포인터
	size_type s;

	//메모리 할당하고 Lis 배열 초기화
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	//Lis 배열 소멸하고 메모리 해제
	void uncreate();
};

template <class T>
void Lis<T>::push_back(const T& t) {
	Node<T>* node = new Node<T>(t);

	if (s == 0)
		b = e = node;
	else {
		e->next = node;
		node->prev = e;
		e = node;
	}
	s++; //사이즈증가
}

template <class T>
void Lis<T>::create(size_type s, const T& t) {
	for (size_type i = 0; i < s; i++)
		push_back(t);
}

//b와 e 반복자를 사용하여 사본 만드는 crate()
template <class T>
void Lis<T>::create(iterator b, iterator e) {
	while (b != e)
		push_back(*b++);
}

//소멸
template <class T>
void Lis<T>::uncreate() {
	Node<T>* node = e;

	while (node != b) { //역방향 삭제, 소멸, 메모리 해제 
		Node<T>* node_delete = node;
		node = node->prev; //이전 노드를 가르키
		delete node_delete; //포인터 없는 노드 삭제
	}

	//b에 있으니까
	b = e = 0;
	s = 0;
}
#endif
