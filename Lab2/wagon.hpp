#pragma once
#include <iostream>
#include <string>


class wagon {

	wagon* next, *prev;
public:
	wagon* get_next() { return next; }
	wagon* get_prev() { return prev; }
public:
	wagon(wagon* prev = nullptr);
	virtual ~wagon();
	virtual std::string get_printable_name() const = 0;
	virtual std::uint32_t get_weight() const = 0;
	virtual std::uint8_t get_printable_color() const = 0;
public:
	std::ostream& print(std::ostream& ss) const;
public:
	static wagon* create_cisterna(wagon* prev = nullptr);
	static wagon* create_car_wagon(wagon* prev = nullptr);
	static wagon* create_forest_wagon(wagon* prev = nullptr);
	static wagon* create_passanger_wagon(wagon* prev = nullptr);
	static wagon* create_restaurant(wagon* prev = nullptr);
};

static std::ostream& operator<<(std::ostream& ss, const wagon& r) {
	return r.print(ss);
}