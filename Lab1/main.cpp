#include "person.hpp"
#include "phone.hpp"

int main(int argc, char** argv) {
	try {
		person p("Vladislav", "Drokin", "Vitalyevich", 19);
		std::cout << p;
		person p2("Kr", "Lr", "Pe", 18);
		phone smartphone("79829936054", phone::manufacturer_t::appel);
		smartphone.update_owner(&p);
		std::cout << smartphone;
		smartphone.update_owner(&p2);
	}
	catch (value_exception& ex) {
		std::cout << "[" << ex.code() << "]: " << ex.what() << ", value: " << ex.value() << std::endl;
	}

	return 0;
}