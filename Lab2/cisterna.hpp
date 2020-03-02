#pragma once
#include "wagon.hpp"


class cisterna : public wagon {
public:
	cisterna(wagon* prev = nullptr) : wagon(prev) {}
	~cisterna() override {
		wagon::~wagon();
	}
	std::string get_printable_name() const override {
		return "cisterna";
	}
	std::uint32_t get_weight() const override {
		return 14880;
	}
};

