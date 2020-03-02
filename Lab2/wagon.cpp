#include <Windows.h>

#include "restaurant.hpp"
#include "cisterna.hpp"
#include "car_wagon.hpp"
#include "forest_wagon.hpp"
#include "passanger_wagon.hpp"



wagon::wagon(wagon* prev)
	: prev(prev), next(nullptr) {

	if (this->prev)
		this->prev->next = this;
}

wagon::~wagon() {
	if (this->prev)
		this->prev->next = this->next;
	if (this->next)
		this->next->prev = this->prev;
}

wagon* wagon::create_cisterna(wagon* prev) {
	return new cisterna(prev);
}

wagon* wagon::create_car_wagon(wagon* prev) {
	return new car_wagon(prev);
}

wagon* wagon::create_forest_wagon(wagon* prev) {
	return new forest_wagon(prev);
}

wagon* wagon::create_passanger_wagon(wagon* prev) {
	return new passenger_wagon(prev);
}

wagon* wagon::create_restaurant(wagon* prev) {
	return new restaurant(prev);
}

std::ostream& wagon::print(std::ostream& ss) const {
	static HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console_handle, get_printable_color());

	if (!prev)
		ss << "_";

	ss << "[" << get_printable_name() << "]_";

	SetConsoleTextAttribute(console_handle, 7);
	return next ? next->print(ss) : ss;
}