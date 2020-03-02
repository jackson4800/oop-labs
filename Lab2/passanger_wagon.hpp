#pragma once
#include "wagon.hpp"

class passenger_wagon : public wagon {
public:
	passenger_wagon(wagon* prev = nullptr) : wagon(prev) {}
	~passenger_wagon() override {
		wagon::~wagon();
	}
	std::string get_printable_name() const override {
		return "passenger wagon";
	}
	std::uint32_t get_weight() const override {
		return 10000;
	}
	std::uint8_t get_printable_color() const override {
		return 13;
	}
};