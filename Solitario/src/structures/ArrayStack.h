/*
Instituto Tecnologico de Costa Rica

Integrantes:	Owel Jafet Gutiérrez Ortiz,		2026800869
				Miranda Jiménez Alvarado,		2026XXXXXX
				Keishiro Gabriel Cubero Abe,	2026XXXXXX
				Eduardo Alfonso Moreno Pérez,	2026XXXXXX

Profesor : Mauricio Aviles Cisneros

Semana 13 : Proyecto 0 - Juegos de Solitario

Fecha de entrega : 26 / 10 / 2026

*/

/*
Clase ArrayStack:
	Implementacion de Stack con un arreglo dinamico. Cuando se llena,
	duplica su capacidad. Lanza una excepcion al desapilar o consultar el
	tope de una pila vacia.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::cout;
using std::runtime_error;
using std::underflow_error;

template <class E>
class ArrayStack : public Stack<E> {
private:
	E* elements;
	int max;
	int size;

public:
	ArrayStack(int max) {
		if (max < 1) {
			throw runtime_error("Error, Invalid max size. Must be bigger than 0.");
		}

		this->elements = new E[max];
		this->max = max;
		this->size = 0;
	}
	~ArrayStack() {
		delete[] this->elements;
	}

	void push(E newElement) override {
		if (this->size >= this->max) {
			int newMax = this->max * 2;
			E* temp = new E[newMax];
			for (int i = 0; i < this->size; i++) {
				temp[i] = this->elements[i];
			}
			delete[] this->elements;
			this->elements = temp;
			this->max = newMax;
		}

		this->elements[this->size] = newElement;
		this->size++;
	}

	E pop() override {
		if (this->isEmpty()) {
			throw underflow_error("Error, Cannot pop from an empty stack.");
		}
		this->size--;
		return this->elements[this->size];
	}

	E topValue() override {
		if (this->isEmpty()) {
			throw underflow_error("Error, Cannot peek from an empty stack.");
		}
		return this->elements[this->size - 1];
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

	void print() override {
		if (this->isEmpty()) {
			cout << "[]" << std::endl;
			return;
		}

		cout << "[";
		for (int i = 0; i < this->size - 1; i++) {
			cout << this->elements[i] << ", ";
		}
		cout << this->elements[this->size - 1] << "]" << std::endl;
	}
};