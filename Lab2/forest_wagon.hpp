#pragma once
#include "wagon.hpp"

class forest_wagon : public wagon {
public:
	forest_wagon(wagon* prev = nullptr) : wagon(prev) {}
	~forest_wagon() override {
		wagon::~wagon();
	}
	std::string get_printable_name() const override {
		return "forest wagon";
	}
	std::uint32_t get_weight() const override {
		return 13370;
	}
};