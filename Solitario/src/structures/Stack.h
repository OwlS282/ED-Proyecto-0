#pragma once

template <class E>
class Stack
{
public:
	Stack() {}
	virtual ~Stack() {}
	Stack(const Stack<E>& otherStack) = delete;
	void operator =(const Stack<E>& otherStack) = delete;

	virtual void push(E newElement) = 0;
	virtual E pop() = 0;
	virtual E topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
	//virtual void copy(Stack<E>& other) = 0;
};

