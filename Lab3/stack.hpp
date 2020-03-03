#pragma once
#include "linked_list.hpp"

template<class T>
class stack : private linked_list<T> {
	using parent = linked_list<T>;
public:
	stack() : parent(0) {}
	~stack() { /*parent::~linked_list();*/ }
	T& top() { return parent::front(); }
	T pop() { auto t = parent::front(); parent::pop_front(); return t; }
	void push(T val) { parent::push_front(val); }
public:
	std::ostream& print(std::ostream& s) {
		bool first = false;
		parent::for_each([&](auto&& l) {
			s << "|" << l << "|\n";
			first = true;
		});
		s << "[" << parent::size_ << "]\n";
		return s;
	}
public:
	using parent::empty;
	using parent::size;
};

template<class T>
static std::ostream& operator<<(std::ostream& s, stack<T>& l) {
	return l.print(s);
}

template<class T>
console& operator<<(console& l, stack<T>& r) {
	l.set_color(console::foreground_green | console::foreground_blue | console::foreground_intensity);
	std::cout << r;
	l.reset_color();
	return l;
}