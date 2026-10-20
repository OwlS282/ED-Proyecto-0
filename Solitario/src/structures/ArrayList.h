#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"

template <class E>
class ArrayList : public List<E>
{
private:
	E* elements;
	int max;
	int size;
	int pos;

	void ValidatePos() {
		if (this->size == 0) {
			throw std::underflow_error("List is empty.");
		}
		if (this->pos >= this->size) {
			throw std::range_error("No current element at pos.");
		}
	}
	bool ValidateIdx(int idx) {
		if (idx < 0 || idx >= this->getSize()) {
			throw std::runtime_error("Index out of bounds.");
		}
	}
public:
	ArrayList(int max) {
		if (max < 1) {
			throw std::length_error("Invalid max size. Must be bigger than 0.");
		}

		this->elements = new E[max];
		this->max = max;
		this->size = 0;
		this->pos = 0;
	}
	~ArrayList() override {
		delete[] elements;
	}

	void insert(E elem) override {
		if (this->size >= this->max) {
			throw std::overflow_error("Cannot insert into a full list.");
		}

		if (this->pos >= 0 && this->pos <= this->size) {
			for (int i = this->size - 1; i >= this->pos; i--) {
				E elemToMove = this->elements[i];
				this->elements[i + 1] = elemToMove;
			}

			this->elements[this->pos] = elem;
			this->size++;
		}
		else {
			throw std::range_error("Insertion out of range.");
		}
	}

	void append(E elem) override {
		if (this->size >= this->max) {
			throw std::overflow_error("Cannot append into a full list.");
		}
		this->elements[this->size] = elem;
		this->size++;
	}

	void setElement(E elem) override {
		ValidatePos();
		this->elements[this->pos] = elem;
	}

	E remove() override {  // pop
		ValidatePos();
		E elemToReturn = this->elements[this->pos];

		for (int i = this->pos; i < this->size - 1; i++) {
			this->elements[i] = this->elements[i + 1];
		}
		this->size--;
		return elemToReturn;
	}

	void clear() override {
		this->size = 0;
		this->pos = 0;
	}

	E getElement() override {  // peek
		ValidatePos();

		return this->elements[this->pos];
	}

	void swapElements(int i, int j) {
		ValidateIdx(i);
		ValidateIdx(j);

		E temp = this->elements[i];
		this->elements[i] = this->elements[j];
		this->elements[j] = temp;
	}

	void goToStart() override {
		this->pos = 0;
	}
	void goToEnd() override {
		this->pos = this->size;  // -1?
	}
	void goToPos(int pos) override {
		if (pos < 0 || pos > this->size) {  // >= this->size?
			throw std::range_error("Pos out of current list range.");
		}
		this->pos = pos;
	}
	void next() override {
		if (this->pos < this->size) {
			this->pos++;
		}
	}
	void previous() override {
		if (this->pos > 0) {
			this->pos--;
		}
	}
	bool atEnd() override {
		return this->pos == this->size;
	}
	bool atStart() override {
		return this->pos == 0;
	}
	int getPos() override {
		return this->pos;
	}
	int getSize() override {
		return this->size;
	}

	void print() override {
		std::cout << "[";
		for (int i = 0; i < this->size; i++) {
			std::cout << this->elements[i];
			if (i < this->size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]" << std::endl;
	}
};