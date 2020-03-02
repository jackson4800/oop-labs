#include "wagon.hpp"

class restaurant : public wagon {
public:
	restaurant(wagon* prev = nullptr) : wagon(prev) {}
	~restaurant() override {
		wagon::~wagon();
	}
	std::string get_printable_name() const override {
		return "restaurant";
	}
	std::uint32_t get_weight() const override {
		return 25000;
	}
	std::uint8_t get_printable_color() const override {
		return 11;
	}
};