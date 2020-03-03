#pragma once
#include "linked_list.hpp"

template<class T>
class queue : private linked_list<T> {
	using parent = linked_list<T>;
public:
	queue() : parent(0) {}
	~queue() { /*parent::~linked_list();*/ }
	T pop() { auto t = parent::front(); parent::pop_front(); return t; }
	void push(T val) { parent::push_back(val); }
public:
	std::ostream& print(std::ostream& s) {
		bool first = false;
		s << "[" << parent::size_ << "]: ";
		parent::for_each([&](auto&& l) {
			if (first) s << " -> ";
			s << "|" << l << "|";
			first = true;
		});
		return s;
	}
public:
	using parent::empty;
	using parent::size;
	using parent::front;
};

template<class T>
static std::ostream& operator<<(std::ostream& s, queue<T>& l) {
	return l.print(s);
}


template<class T>
console& operator<<(console& l, queue<T>& r) {
	l.set_color(console::foreground_green | console::foreground_red | console::foreground_intensity);
	std::cout << r;
	l.reset_color();
	return l;
}