#pragma once
#include "wagon.hpp"

class car_wagon : public wagon {
public:
	car_wagon(wagon* prev = nullptr) : wagon(prev) {}
	~car_wagon() override {
		wagon::~wagon();
	}
	std::string get_printable_name() const override {
		return "car wagon";
	}
	std::uint32_t get_weight() const override {
		return 228626;
	}
	std::uint8_t get_printable_color() const override {
		return 12;
	}
};