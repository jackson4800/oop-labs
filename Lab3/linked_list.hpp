#pragma once
#include <algorithm>
#include <iostream>
#include <functional>

#include "console.hpp"

#include "exceptions.hpp"

template <class  T>
class linked_list {
public:
	class iterator_t {
		linked_list<T>* owner;
		friend class linked_list;
		class node_t {
			friend class linked_list;
			node_t* next_, *prev_;
			T value_;
			bool valid_;
		public:
			node_t* prev() {
				return prev_;
			}
			node_t* next() {
				return next_;
			}
			bool is_valid() {
				return valid_;
			}
			operator T& () {
				return value_;
			}
		public:
			node_t(T v, node_t* prev = nullptr, bool valid = false) 
			: value_(v), prev_(prev), valid_(valid) {
				if (this->prev_)
					this->prev_->next_ = this;
			}
			~node_t() { }
		};
		node_t* value_;
		static node_t get_dummy() { return node_t(0); }
	private:
		void decrement() {
			if (!value_ || !value_->is_valid())
				throw iterator_exception("Can't dereference invalid iterator");
			if (!value_->prev_)
				throw iterator_exception("Can't decrement begin iterator");
			value_ = value_->prev();
		}
		void increment() {
			if (!value_ || !value_->is_valid())
				throw iterator_exception("Can't dereference invalid iterator");
			if (!value_->next_)
				throw iterator_exception("Can't decrement end iterator");
			value_ = value_->next();
		}
	public:
		iterator_t(linked_list<T>* owner) : value_(new node_t(0)), owner(owner) {

		}
	public:
		T& operator*() {
			if (!value_ || !value_->is_valid())
				throw iterator_exception("Can't dereference invalid iterator");
			return static_cast<T&>(*value_);
		}
		T* operator->() {
			if (!value_ || !value_->is_valid())
				throw iterator_exception("Can't dereference invalid iterator");
			return &static_cast<T&>(*value_);
		}
		iterator_t& operator--() {
			decrement();
			return *this;
		}
		iterator_t operator--(int) {
			decrement();
			return *this;
		}
		iterator_t& operator++() {
			increment();
			return *this;
		}
		iterator_t operator++(int) {
			increment();
			return *this;
		}
		operator bool() {
			return value_ && value_->is_valid();
		}
	};
	using node = decltype(iterator_t::get_dummy());
protected:
	std::uint32_t size_;
	iterator_t begin_, end_;
public:
	linked_list(std::uint32_t size = 0) 
	: size_(0), begin_(iterator_t(this)), end_(iterator_t(this)) {
		end_.value_->prev_ =(begin_.value_);
		begin_.value_->next_ = (end_.value_);
		resize(size);
	}
	linked_list(std::uint32_t size, T filler)
		: linked_list(0) {
		resize(size, filler);
	}
	~linked_list() {
		clear();
		delete end_.value_;
		delete begin_.value_;
	}
	std::size_t size() { return size_; }
	bool empty() { return size_ == 0; }
	iterator_t begin() { return begin_; }
	iterator_t end() { return end_; }
	T& front() { return *begin(); }
	T& back() { return *(--end()); }
	void clear() {
		auto memory = begin_.value_->next_;
		while (memory) {
			delete begin_.value_;
			begin_.value_ = memory;
			memory = begin_.value_->next_;
		}
		begin_ = iterator_t(this);
		end_ = iterator_t(this);
		end_.value_->prev_ = (begin_.value_);
		begin_.value_->next_ = (end_.value_);
	}
	void resize(std::uint32_t size) {
		resize(size, T{});
	}
	void resize(std::uint32_t size, T filler) {
		if (size > ((2 << 31) - 1))
			throw invalid_size_exception("resize called with invalid size");

		auto it = begin();

		if (size < size_) {
			auto offset = size_ - size;
			while (offset--) pop_back();
			return;
		}

		auto offset = size_;

		while (offset > 0) {
			it++;
			offset--;
		}

		size -= offset;

		while (size--)
			it = insert(it, filler);
	}
	void pop_back() {
		if (!size())
			throw empty_access_exception("pop_back called with empty list");
		erase(--end());
	}
	void pop_front() {
		if (!size())
			throw empty_access_exception("pop_front called with empty list");
		erase(begin());
	}
	void push_front(T value) {
		insert(begin_, value);
	}
	void push_back(T value) {
		insert(end_, value);
	}
	iterator_t erase(iterator_t where) {
		if (where.owner != this)
			throw iterator_exception("foreign iterator given to erase");

		if (size_ == 0)
			throw empty_access_exception("erase called with empty list");

		size_--;
		if (where.value_->prev_)
			where.value_->prev_->next_ = where.value_->next_;
		if (where.value_->next_)
			where.value_->next_->prev_ = where.value_->prev_;
		if (where.value_ == begin_.value_)
			begin_++;
		delete where.value_;
		where++;
		return where;
	}
	iterator_t insert(iterator_t where, T value) {
		if (where.owner != this)
			throw iterator_exception("foreign iterator given to insert");

		size_++;

		if (size_ > ((2 << 31) - 1))
			throw invalid_size_exception("insert overflowed list size");

		if (where.value_->next() == begin_.value_->next()) {
			if (begin_) {
				begin_.value_->prev_ = new node(value, nullptr, true);
				begin_.value_->prev_->next_ = (begin_.value_);
				auto it = begin_;
				begin_--;
				return it;
			}
			else {
				begin_.value_->value_ = value;
				begin_.value_->valid_ = true;
				return end_;
			}
		}
		else if (!where) {
			if (begin_) {
				where.value_->value_ = value;
				where.value_->valid_ = true;
				where.value_->next_ = new node(0);
				where.value_->next_->prev_ = (where.value_);
				end_++;
			}
			else {
				begin_.value_->value_ = value;
				begin_.value_->valid_ = true;
			}
			return end_;
		}
		else {
			node* p = new node(value, where.value_, true);
			where.value_->next_->prev_ = p;
			p->next_ = where.value_->next_;
			where.value_->next_ = p;
		}
		return ++where;
	}
	void for_each(std::function<void(T&)> fn) {
		for (auto& val : *this) fn(val);
	}
	void for_each_r(std::function<void(T&)> fn) {
		auto it = --end();
		while (it) {
			fn(*it);
			it--;
		}
	}
public:
	std::ostream& print(std::ostream& s) {
		bool first = false;
		s << "[" << size_ << "]: ";
		for_each([&](auto&& l) {
			if (first)
				s << " -> ";
			s << l;
			first = true;
		});
		return s;
	}
};

template<class T>
static std::ostream& operator<<(std::ostream& s, linked_list<T>& l) {
	return l.print(s);
}

template<class T>
console& operator<<(console& l, linked_list<T>& r) {
	l.set_color(console::foreground_red | console::foreground_intensity);
	std::cout << r;
	l.reset_color();
	return l;
}