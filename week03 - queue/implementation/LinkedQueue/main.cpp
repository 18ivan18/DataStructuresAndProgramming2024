#include "LinkedQueue.h"
#include <iostream>

int main()
{
	LinkedQueue<int> q1;
	q1.enqueue(22);
	q1.enqueue(2);
	q1.enqueue(3);
	q1.enqueue(33);

	q1.dequeue();
	q1.dequeue();
	q1.dequeue();

	LinkedQueue<int> q2(q1);
	q2.enqueue(23);
	q2.enqueue(24);
	q2.enqueue(25);

	q1.dequeue();
	std::cout << "q1 is empty: " << std::boolalpha << q1.isEmpty() << std::endl;
}