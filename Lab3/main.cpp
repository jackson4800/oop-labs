#include "stack.hpp"
#include "queue.hpp"

int main(int argc, char** argv) {
	console output{};
	output << "Hellow, stranger, do u wanna see my stuff? \n\n";
	output << "Here's some listos: \n";
	try {
		linked_list<int> p;
		output << p << "\n";
		p.push_front(1);
		output << p << "\n";
		p.push_front(2);
		output << p << "\n";
		p.push_back(3);
		output << p << "\n";
		p.pop_front();
		output << p << "\n";
		p.pop_back();
		output << p << "\n";
	}
	catch (std::exception & e)
	{
		output << e.what() << "\n";
	}
	output << "Here's some stacks: \n";
	try {
		stack<int> p;
		output << p << "\n";
		p.push(1);
		output << p << "\n";
		p.push(2);
		output << p << "\n";
		p.push(3);
		output << p << "\n";
		p.pop();
		output << p << "\n";
	}
	catch (std::exception & e)
	{
		output << e.what() << "\n";
	}
	output << "\nHere's some queues: \n";
	try {
		queue<int> p;
		output << p << "\n";
		p.push(1);
		output << p << "\n";
		p.push(2);
		output << p << "\n";
		p.push(3);
		output << p << "\n";
		p.pop();
		output << p << "\n";
		p.pop();
		output << p << "\n";
		p.pop();
		output << p << "\n";
		p.pop();
	}
	catch (std::exception & e)
	{
		output << e.what() << "\n";
	}
	return 0;
}