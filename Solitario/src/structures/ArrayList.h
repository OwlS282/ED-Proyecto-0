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
Clase ArrayList:
	Implementacion de List con un arreglo dinamico de tamano maximo fijo.
	Mantiene una posicion actual y desplaza elementos al insertar y eliminar.
	Lanza excepciones si la lista esta llena, vacia o si la posicion o el
	indice no son validos. Ademas permite intercambiar dos elementos.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::cout;
using std::runtime_error;
using std::underflow_error;
using std::range_error;
using std::length_error;
using std::overflow_error;

template <class E>
class ArrayList : public List<E> {
private:
	E* elements;
	int max;
	int size;
	int pos;

	void ValidatePos() {
		if (this->size == 0) {
			throw underflow_error("Error, List is empty.");
		}
		if (this->pos >= this->size) {
			throw range_error("Error, No current element at pos.");
		}
	}

	void ValidateIdx(int idx) {
		if (idx < 0 || idx >= this->getSize()) {
			throw runtime_error("Error, Index out of bounds.");
		}
	}

public:
	ArrayList(int max) {
		if (max < 1) {
			throw length_error("Error, Invalid max size. Must be bigger than 0.");
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
			throw overflow_error("Error, Cannot insert into a full list.");
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
			throw range_error("Error, Insertion out of range.");
		}
	}

	void append(E elem) override {
		if (this->size >= this->max) {
			throw overflow_error("Error, Cannot append into a full list.");
		}
		this->elements[this->size] = elem;
		this->size++;
	}

	void setElement(E elem) override {
		ValidatePos();
		this->elements[this->pos] = elem;
	}

	E remove() override {
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

	E getElement() override {
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
		this->pos = this->size;
	}

	void goToPos(int pos) override {
		if (pos < 0 || pos > this->size) {
			throw range_error("Error, Pos out of current list range.");
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
		cout << "[";
		for (int i = 0; i < this->size; i++) {
			cout << this->elements[i];
			if (i < this->size - 1) {
				cout << ", ";
			}
		}
		cout << "]" << std::endl;
	}
};