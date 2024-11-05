#ifndef LINKED_QUEUE
#define LINKED_QUEUE
#include <stdexcept>

template <typename T>
class LinkedQueue
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

	int n;		 // number of elements on queue
	Node *first; // beginning of queue
	Node *last;	 // end of queue

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T> &other);
	LinkedQueue<T> &operator=(const LinkedQueue<T> &other);
	~LinkedQueue();

private:
	void copyFrom(const LinkedQueue<T> &other);
	void free();

public:
	void enqueue(const T &el);
	T dequeue();
	const T &peek();
	bool isEmpty() const;
	int size() const;
};

template <typename T>
int LinkedQueue<T>::size() const
{
	return n;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T &el)
{
	Node *oldLast = last;
	last = new Node(el);

	if (isEmpty())
	{
		first = last;
	}
	else
	{
		oldLast->next = last;
	}

	n++;
}
template <typename T>
T LinkedQueue<T>::dequeue()
{
	if (!first)
	{
		throw std::length_error("Empty queue!");
	}

	Node *oldFirst = first;
	T item = first->data;
	first = first->next;
	delete oldFirst;
	n--;
	if (isEmpty())
	{
		last = nullptr;
	}
	return item;
}

template <typename T>
const T &LinkedQueue<T>::peek()
{
	if (!first)
	{
		throw std::length_error("Empty queue!");
	}

	return first->data;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return first == nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue() : first(nullptr), last(nullptr), n(0)
{
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &other) : LinkedQueue()
{
	copyFrom(other);
}

template <typename T>
LinkedQueue<T> &LinkedQueue<T>::operator=(const LinkedQueue<T> &other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	free();
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T> &other)
{
	Node *iter = other.first;

	while (iter)
	{
		enqueue(iter->data);
		iter = iter->next;
	}
}

template <typename T>
void LinkedQueue<T>::free()
{
	while (!isEmpty())
	{
		dequeue();
	}
}

#endif