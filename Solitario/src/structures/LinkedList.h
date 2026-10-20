#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

template <class E>
class LinkedList : public List<E>
{
private:
	Node<E>* head;
	Node<E>* current;
	Node<E>* tail;
	int size;

	Node<E>*& ActualFront() {
		return this->head->next;
	}
	Node<E>*& ActualCurrent() {
		return this->current->next;
	}
	void ValidateList() {
		if (this->size == 0) {
			throw std::underflow_error("List is empty.");
		}
		if (this->current == this->tail) {
			throw std::runtime_error("No current element.");
		}
	}
public:
	LinkedList() {
		Node<E>* plhl = new Node<E>();
		this->head = plhl;
		this->tail = plhl;
		this->current = plhl;

		this->size = 0;
	}
	~LinkedList() {
		this->clear();
		delete this->head;
	}

	void insert(E elem) override {
		Node<E>* newNode = new Node<E>(elem, this->ActualCurrent());
		this->ActualCurrent() = newNode;

		if (this->current == this->tail) {
			this->tail = this->ActualCurrent();
		}
		this->size++;
	}

	void append(E elem) override {
		Node<E>* newNode = new Node<E>(elem);
		this->tail->next = newNode;
		this->tail = newNode;
		this->size++;
	}

	void setElement(E elem) override {
		this->ValidateList();

		this->ActualCurrent()->elem = elem;
	}

	E remove() override {
		this->ValidateList();

		Node<E>* tempCurr = this->ActualCurrent();
		E tempCurrElem = this->ActualCurrent()->elem;

		this->ActualCurrent() = this->ActualCurrent()->next;
		delete tempCurr;

		if (this->size == 1) {
			this->tail = this->head;
		}

		this->size--;
		return tempCurrElem;
	}

	void clear() override {
		while (this->ActualFront() != nullptr) {
			Node<E>* fr = this->ActualFront();
			this->ActualFront() = this->ActualFront()->next;
			delete fr;
		}

		this->tail = this->head;
		this->current = this->head;
		this->size = 0;
	}

	E getElement() override {
		this->ValidateList();

		return this->ActualCurrent()->elem;
	}

	void goToStart() override {
		this->current = this->head;
	}

	void goToEnd() override {
		this->current = this->tail;
	}

	void goToPos(int pos) override {
		if (pos > this->size || pos < 0) {
			throw std::out_of_range("Position out of bounds.");
		}

		this->current = this->head;
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}
	}

	void next() override {
		if (this->current != this->tail) {
			this->current = this->current->next;
		}
	}
	void previous() override {
		//this->ActualCurrent() = this->current;

		//for (Node<E>* temp = this->ActualFront(); temp != nullptr; temp = temp->next) {
		//	if (temp->next == this->current) {
		//		this->current = temp;
		//		return;
		//	}
		//}

		if (this->current != this->head) {
			Node<E>* temp = this->head;
			while (temp->next != this->current) {
				temp = temp->next;
			}
			this->current = temp;
		}
	}

	bool atEnd() override {
		return this->current == this->tail;
	}
	bool atStart() override {
		return this->current == this->head;
	}
	int getPos() override {
		int pos = 0;
		//for (Node<E>* temp = this->ActualFront(); temp == this->ActualCurrent(); temp = temp->next) {
		//	pos++;
		//}

		Node<E>* temp = this->head;
		while (temp->next != this->ActualCurrent()) {
			temp = temp->next;
			pos++;
		}

		return pos;
	}
	int getSize() override {
		return this->size;
	}

	void print() override {
		std::cout << "[";
		for (Node<E>* temp = this->ActualFront(); temp != nullptr; temp = temp->next) {
			std::cout << temp->elem;
			if (temp->next != nullptr) {
				std::cout << ", ";
			}
		}
		std::cout << "]" << std::endl;
	}
};

