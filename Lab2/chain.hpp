#pragma once
#include <memory>

#include "wagon.hpp"


class chain {
	class iterator_t {
		friend class chain;
		wagon* val;
	private:
		void increment();
		void decrement();
	public:
		iterator_t(wagon* val = nullptr);
	public:
		wagon& operator*();
		wagon* operator->();
		bool is_end();
		bool can_decrease();
		iterator_t& operator++();
		iterator_t& operator--();
		iterator_t operator++(int);
		iterator_t operator--(int);
		operator bool();
	};
	iterator_t begin_;
public:
	chain() {}
public:
	iterator_t begin() const;
	std::uint32_t get_total_weight() const;
	std::ostream& print_chain(std::ostream& ss) const;
public:
	static std::shared_ptr<chain> create_random_train_chain(int length);
};

static std::ostream& operator<<(std::ostream& ss, chain* chain) {
	return chain->print_chain(ss);
}