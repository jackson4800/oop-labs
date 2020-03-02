#pragma once
#include "person.hpp"

class person;

/*
открытые члены класса:
Метод для вывода информации о телефоне: марка, номер, ФИО владельца.

Для иллюстрации работы с классами в методе Main()

Создать 2 экземпляра класса Person с разным значением возраста.
Вывести о них информацию на экран.
Создать экземпляр класса телефон.
Установить владельца телефона.
Вывести информацию о телефоне.
*/

class phone {
public:
	enum manufacturer_t {
		invalid_manufacturer = -1,
		appel,
		samsuk,
		xuomi,
		herowei,
		moyzo,
		meh,
	};
private:
	person* owner_;
	manufacturer_t manufacturer_;
	std::string phone_number_;
public:
	phone();
	phone(std::string_view phone_number, manufacturer_t manufacturer);
	void update_owner(person* owner);
public:
	std::string get_manufacturer() const;
	std::string get_phone_number() const;
	person get_owner() const;
public: //print
	void print(std::ostream& os) const;
};

static std::ostream& operator<<(std::ostream& s, const phone& p) {
	p.print(s);
	return s;
}