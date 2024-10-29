#ifndef LINKED_STACK
#define LINKED_STACK
#include <stdexcept>

template <typename T>
class LinkedStack
{
private:
	struct Node
	{
		T data;
		Node *next;

		Node(const T &data) : data(data), next(nullptr)
		{
		}
	};

	Node *head; // top of stack
	int n;		// size of the stack

public:
	LinkedStack();
	LinkedStack(const LinkedStack<T> &other);
	LinkedStack<T> &operator=(const LinkedStack<T> &other);
	~LinkedStack();

private:
	void copyFrom(const LinkedStack<T> &other);
	void free();

public:
	void push(const T &el);
	T pop();
	const T &top();
	bool isEmpty() const;
	int size() const;
};

template <typename T>
int LinkedStack<T>::size() const
{
	return n;
}

template <typename T>
void LinkedStack<T>::push(const T &data)
{

	Node *oldfirst = head;
	head = new Node(data);
	head->next = oldfirst;
	n++;
}

template <typename T>
T LinkedStack<T>::pop()
{
	if (!head)
	{
		throw std::length_error("Empty stack!");
	}

	Node *oldHead = head;
	T item = oldHead->data; // save item to return
	head = head->next;		// delete first node
	delete oldHead;
	n--;
	return item;
}

template <typename T>
const T &LinkedStack<T>::top()
{
	if (!head)
	{
		throw std::length_error("Empty stack!");
	}

	return head->data;
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
	return head == nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack() : head(nullptr), n(0)
{
}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> &other)
{
	copyFrom(other);
}

template <typename T>
LinkedStack<T> &LinkedStack<T>::operator=(const LinkedStack<T> &other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
	free();
}

template <typename T>
void LinkedStack<T>::copyFrom(const LinkedStack<T> &other)
{
	if (other.isEmpty())
	{
		return;
	}

	Node *otherIter = other.head;
	head = new Node(otherIter->data);
	Node *thisIter = head;

	do
	{
		otherIter = otherIter->next;

		if (otherIter)
		{
			thisIter->next = new Node(otherIter->data);
			thisIter = thisIter->next;
		}
	} while (otherIter);
}

template <typename T>
void LinkedStack<T>::free()
{
	while (!isEmpty())
	{
		pop();
	}
}

#endif