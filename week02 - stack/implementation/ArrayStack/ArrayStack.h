#ifndef ARRAY_STACK
#define ARRAY_STACK
#include <stdexcept>

template <typename T>
class ArrayStack
{
private:
	static const int INIT_CAPACITY = 8;

	int n; // number of elements on stack
	int capacity;

	T *arr; // array of items

public:
	ArrayStack();
	ArrayStack(const ArrayStack<T> &other);
	ArrayStack<T> &operator=(const ArrayStack<T> &other);
	~ArrayStack();

private:
	void copyFrom(const ArrayStack<T> &other);
	void free();

	void resize(int capacity);

public:
	void push(const T &element);
	T pop();
	const T &top();
	bool isEmpty() const;
};

template <typename T>
void ArrayStack<T>::push(const T &element)
{
	if (n >= capacity)
	{
		resize(capacity * 2);
	}

	arr[n++] = element;
}

template <typename T>
T ArrayStack<T>::pop()
{
	if (isEmpty())
	{
		throw std::length_error("Empty ArrayStack!");
	}

	T item = arr[n - 1];

	// why /4?
	if (--n == capacity / 4 && n > 0)
	{
		resize(capacity / 2);
	}
	return item;
}

template <typename T>
const T &ArrayStack<T>::top()
{
	if (isEmpty())
	{
		throw std::length_error("Empty ArrayStack!");
	}

	return arr[n - 1];
}

template <typename T>
bool ArrayStack<T>::isEmpty() const
{
	return n == 0;
}

template <typename T>
ArrayStack<T>::ArrayStack() : n(0), capacity(INIT_CAPACITY), arr(new T[capacity])
{
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &other)
{
	copyFrom(other);
}

template <typename T>
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack<T> &other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
	free();
}

template <typename T>
void ArrayStack<T>::copyFrom(const ArrayStack<T> &other)
{
	arr = new T[other.capacity];

	n = other.n;
	capacity = other.capacity;

	for (size_t i = 0; i < n; i++)
	{
		arr[i] = other.arr[i];
	}
}

template <typename T>
void ArrayStack<T>::free()
{
	delete[] arr;
}

template <typename T>
void ArrayStack<T>::resize(int capacity)
{
	this->capacity = capacity;
	T *temp = new T[capacity];

	for (size_t i = 0; i < n; i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;
}

#endif