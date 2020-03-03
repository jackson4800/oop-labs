#pragma once
#include <exception>
#include <string>

class _abstract_exception : public std::exception {
	std::string message;
public:
	explicit _abstract_exception(std::string_view msg) : message(msg) {}
	virtual ~_abstract_exception() {};
	char const* what() const override {
		return message.c_str();
	}
};

class empty_access_exception : public _abstract_exception {
	using parent = _abstract_exception;
public:
	empty_access_exception(std::string_view msg) : parent(msg) {};
};


class invalid_size_exception : public _abstract_exception {
	using parent = _abstract_exception;
public:
	invalid_size_exception(std::string_view msg) : parent(msg) {};
};

class iterator_exception : public _abstract_exception {
	using parent = _abstract_exception;
public:
	iterator_exception(std::string_view msg) : parent(msg) {};
};