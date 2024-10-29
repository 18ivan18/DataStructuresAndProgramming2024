#include "ArrayStack.h"
#include <iostream>

int main()
{
	ArrayStack<int> st1;
	st1.push(22);
	st1.push(2);
	st1.push(3);
	st1.push(33);

	st1.pop();
	st1.pop();
	st1.pop();

	ArrayStack<int> st2(st1);
	st2.push(23);
	st2.push(24);
	st2.push(25);

	st1.pop();
	std::cout << "st1 is empty: " << std::boolalpha << st1.isEmpty() << std::endl;
}