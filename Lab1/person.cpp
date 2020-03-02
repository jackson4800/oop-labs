#include <variant>
#include <array>

#include "person.hpp"

void person::ensure_field_bounds() {
	if (name_.size() > 20)
		throw invalid_length_exception("[person::ensure_field_bounds] name length is greater than 20", INVALID_NAME_LENGTH, name_.size());
	if (surname_.size() > 20)
		throw invalid_length_exception("[person::ensure_field_bounds] surname length is greater than 20", INVALID_SURNAME_LENGTH, surname_.size());
	if (midname_.size() > 20)
		throw invalid_length_exception("[person::ensure_field_bounds] midname length is greater than 20", INVALID_MIDNAME_LENGTH, midname_.size());
	if (age_ < 0)
		throw invalid_age_exception("[person::ensure_field_bounds] age value is negative", INVALID_AGE_VALUE, age_);
}

person::person()
	: age_(-1), name_(""), surname_(""), midname_("") {}

person::person(std::string_view name, std::string_view surname, std::string_view midname, std::int8_t age)
	: name_(name), surname_(surname), midname_(midname), age_(age) {

	this->ensure_field_bounds();
}

void person::set_age(std::int8_t age) {

	if(age < 0)
		throw invalid_age_exception("[person::set_age] age value is negative", INVALID_AGE_VALUE, age);

	this->age_ = age;
}

void person::set_name(std::string_view name) {

	if(name.size() > 20)
		throw invalid_length_exception("[person::set_name] name length is greater than 20", INVALID_NAME_LENGTH, name.size());

	this->name_ = name;
}

void person::set_surname(std::string_view surname) {

	if (surname.size() > 20)
		throw invalid_length_exception("[person::set_surname] name length is greater than 20", INVALID_NAME_LENGTH, surname.size());

	this->surname_ = surname;
}

void person::set_midname(std::string_view midname) {

	if (midname.size() > 20)
		throw invalid_length_exception("[person::set_midname] name length is greater than 20", INVALID_NAME_LENGTH, midname.size());

	this->midname_ = midname;
}

void person::print(std::ostream& os) const {

	using ref_field = std::pair<std::variant<const std::string&(person::*)(void) const, const std::int16_t&(person::*)(void) const>, const std::string_view>;

	static constexpr const std::array<ref_field, 4> fields_ = {
		ref_field{ &person::get_age, "age" },
		ref_field{ &person::get_name, "name" },
		ref_field{ &person::get_surname, "surname" },
		ref_field{ &person::get_midname, "midname" }
	};

	for (auto&& f : fields_)
		std::visit([&](auto&& ptr) {
			os << "[" << f.second << "]: " << (this->*ptr)() << std::endl;
		}, f.first);
}