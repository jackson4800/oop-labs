#pragma once
#include <exception>
#include <string>

enum exception_codes {
	INVALID_NAME_LENGTH,
	INVALID_SURNAME_LENGTH,
	INVALID_MIDNAME_LENGTH,
	INVALID_AGE_VALUE,
};

class value_exception : public std::exception {
protected:
	int code_, value_;
	std::string message_;
public:
	value_exception(std::string_view message, int ex_code, int value);
	char const* what() const override;
	virtual int code() const;
	virtual int value() const;
};


class invalid_length_exception : public value_exception {
public:
	invalid_length_exception(std::string_view message, int ex_code, int value = -1)
		: value_exception(message,ex_code, value) {}
};

class invalid_age_exception : public value_exception {
public:
	invalid_age_exception(std::string_view message, int ex_code, int value = -1)
		: value_exception(message, ex_code, value) {}
};

class invalid_owner_exception : public value_exception {
public:
	invalid_owner_exception(std::string_view message, int ex_code, int value = -1)
		: value_exception(message, ex_code, value) {}
};