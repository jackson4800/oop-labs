#pragma once
#include "person.hpp"

class person;

/*
�������� ����� ������:
����� ��� ������ ���������� � ��������: �����, �����, ��� ���������.

��� ����������� ������ � �������� � ������ Main()

������� 2 ���������� ������ Person � ������ ��������� ��������.
������� � ��� ���������� �� �����.
������� ��������� ������ �������.
���������� ��������� ��������.
������� ���������� � ��������.
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