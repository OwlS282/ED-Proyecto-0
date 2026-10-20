#pragma once

#include <stdexcept>
#include "Stack.h"

template <class E>
class ArrayStack : public Stack<E>
{
private:
	E* elements;
	int max;
	int size;

public:
	ArrayStack(int max) {
		if (max < 1) {
			throw std::runtime_error("Invalid max size. Must be bigger than 0.");
		}

		this->elements = new E[max];
		this->max = max;
		this->size = 0;
	}
	~ArrayStack() {
		this->clear();
		delete[] this->elements;
	}

	void push(E newElement) override {
		if (this->size >= this->max) {
			this->max *= 2;
			E* temp = new E[this->max];
			for (int i = 0; i < this->max; i++) {
				temp[i] = this->elements[i];
			}
			delete[] elements;
			elements = temp;
			return;
			//throw std::overflow_error("Cannot push to a full stack.");
		}

		this->elements[this->size] = newElement;
		this->size++;
	}
	E pop() override {
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot pop from an empty stack.");
		}
		this->size--;
		return this->elements[this->size];
	}
	E topValue() override {
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot peek from an empty stack.");
		}
		return this->elements[this->size-1];
	}
	void clear() override {
		this->size = 0;
	}
	bool isEmpty() override {
		return this->size == 0;
	}
	int getSize() override {
		return this->size;
	}
	//void copy(Stack<E>& other) override {
	//	int amount = other->getSize() < this->getSize() ? this->getSize() : other->getSize();
	//	for (int i = 0; i < amount; i++) {
	//		this->elements[i] = other->  // other E*. However, we only have pop() to expose the next element...
	//	}
	//}
	void print() override {
		if (this->isEmpty()) {
			std::cout << "[]" << std::endl;
			return;
		}

		std::cout << "[";
		for (int i = 0; i < this->size-1; i++) {
			std::cout << this->elements[i] << ", ";
		}
		std::cout << this->elements[this->size-1] << "]" << std::endl;
	}
};

