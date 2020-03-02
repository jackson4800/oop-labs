#include "chain.hpp"

#include <array>
#include <chrono>
#include <random>
#include <cassert>

void chain::iterator_t::increment() {
	this->val = this->val->get_next();
}

void chain::iterator_t::decrement() {
	this->val = this->val->get_prev();
}

chain::iterator_t::iterator_t(wagon* val)
	: val(val) {}


bool chain::iterator_t::can_decrease() {
	return !!val->get_prev();
}

bool chain::iterator_t::is_end() {
	return !val->get_next();
}

chain::iterator_t& chain::iterator_t::operator++() {
	increment();
	return *this;
}

chain::iterator_t& chain::iterator_t::operator--() {
	assert(val->get_prev() && "can't decrement invalid next iterator");
	decrement();
	return *this;
}

chain::iterator_t chain::iterator_t::operator++(int) {
	increment();
	return *this;
}

chain::iterator_t chain::iterator_t::operator--(int) {
	assert(val->get_prev() && "can't decrement invalid next iterator");
	decrement();
	return *this;
}

wagon& chain::iterator_t::operator*() {
	assert(val && "can't dereference invalid iterator");
	return *val;
}

wagon* chain::iterator_t::operator->() {
	assert(val && "can't dereference invalid iterator");
	return val;
}

chain::iterator_t::operator bool() {
	return !is_end();
}

chain::iterator_t chain::begin() const {
	return begin_;
}

std::shared_ptr<chain> chain::create_random_train_chain(int length) {

	static std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
	static std::uniform_int_distribution<int> range(0, 4);

	static constexpr const std::array<wagon * (*)(wagon*), 5> fields = {
		&wagon::create_cisterna,
		&wagon::create_forest_wagon,
		&wagon::create_passanger_wagon,
		&wagon::create_restaurant,
		&wagon::create_car_wagon
	};

	std::shared_ptr<chain> new_chain = std::make_shared<chain>();
	
	auto begin = new_chain->begin();

	for (auto i = 0; i < length; i++) {
		auto ret = fields[range(rnd)](begin.val);

		if (!begin.val)
			new_chain->begin_.val = begin.val = ret;
		else
			++begin;
	}

	return new_chain;
}

std::uint32_t chain::get_total_weight() const {
	auto it = begin();
	std::uint32_t total = 0;
	while (it)
	{
		total += it->get_weight();
		it++;
	}
	return total;
}

std::ostream& chain::print_chain(std::ostream& ss) const {
	ss << "[Weight]: " << get_total_weight() << std::endl << "[Train]: ";

	auto it = begin();
	if(it)
		return ss << *it << std::endl;
}