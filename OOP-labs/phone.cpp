#include "phone.hpp"

#include <variant>
#include <array>
#include <map>

phone::phone() 
	: manufacturer_(phone::manufacturer_t::invalid_manufacturer), phone_number_("-1"), owner_(nullptr) {}

phone::phone(std::string_view phone_number, manufacturer_t manufacturer)
	: phone_number_(phone_number), manufacturer_(manufacturer) { }

void phone::update_owner(person* owner) {

	if (owner_ && owner_->get_age() > owner->get_age()) {
		throw invalid_owner_exception("[phone::update_owner] new owner is younger than previous", owner->get_age());
		return;
	}

	this->owner_ = owner;
}

std::string phone::get_manufacturer() const {

	static std::map<manufacturer_t, std::string> dict = {
		{appel, "appel"},
		{samsuk, "samsuk"},
		{xuomi, "xuomi"},
		{herowei, "herowei"},
		{moyzo, "moyzo"},
		{meh, "meh"},
		{invalid_manufacturer, "invalid"}
	};

	return dict[this->manufacturer_];
}

std::string phone::get_phone_number() const {
	return this->phone_number_;
}

person phone::get_owner() const {
	person ret = this->owner_ ? *this->owner_ : person();
	return ret;
}

void phone::print(std::ostream& os) const {
	using ref_field = std::pair<std::variant<std::string (phone::*)(void) const, person (phone::*)(void) const>, const std::string_view>;

	static constexpr const std::array<ref_field, 3> fields_ = {
		ref_field{ &phone::get_manufacturer, "manufacturer" },
		ref_field{ &phone::get_phone_number, "phone number" },
		ref_field{ &phone::get_owner, "owner" },
	};

	for (auto&& f : fields_)
		std::visit([&](auto&& ptr) {
			os << "[" << f.second << "]: " << std::endl << (this->*ptr)()  << std::endl;
		}, f.first);
}