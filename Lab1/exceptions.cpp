#include "exceptions.hpp"

value_exception::value_exception(std::string_view message, int ex_code, int value)
	: message_(message), code_(ex_code), value_(value) {}

char const* value_exception::what() const {
	return message_.c_str();
}

int value_exception::code() const {
	return code_;
}

int value_exception::value() const {
	return value_;
}