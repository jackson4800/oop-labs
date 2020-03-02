#include "chain.hpp"

int main(int argc, char** argv) {
	auto c = chain::create_random_train_chain(9);
	std::cout << c.get();
	return 0;
}