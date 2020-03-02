#pragma once
#include <iostream>
#include <string>

#include "exceptions.hpp"

class person {
	std::string name_;
	std::string surname_;
	std::string midname_;
	std::int8_t age_;
private:
	void ensure_field_bounds();
public:
	person();
	person(std::string_view name, std::string_view surname, std::string_view midname, std::int8_t age);
public: //setters
	void set_age(std::int8_t age);
	void set_name(std::string_view name);
	void set_surname(std::string_view surname);
	void set_midname(std::string_view midname);
public: //getters
	const std::int16_t& get_age() const { return this->age_; }
	const std::string& get_name() const { return this->name_; }
	const std::string& get_surname() const { return this->surname_; }
	const std::string& get_midname() const { return this->midname_; }
public: //print
	void print(std::ostream& os) const;
};

static std::ostream& operator<<(std::ostream& s, const person& p) {
	p.print(s);
	return s;
}