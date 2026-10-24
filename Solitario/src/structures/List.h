/*
Instituto Tecnologico de Costa Rica

Integrantes:	Owel Jafet Gutiérrez Ortiz,		2026800869
				Miranda Jiménez Alvarado,		2026008616
				Keishiro Gabriel Cubero Abe,	2026091245
				Eduardo Alfonso Moreno Pérez,	2025080891

Profesor : Mauricio Aviles Cisneros

Semana 13 : Proyecto 0 - Juegos de Solitario

Fecha de entrega : 26 / 10 / 2026

*/

/*
Clase List:
	Clase abstracta plantilla que define el TDA lista con una posicion
	actual (cursor). Declara las operaciones de insertar, agregar, eliminar,
	consultar y moverse por la lista. Es implementada por ArrayList y
	LinkedList. No se puede copiar.
*/

#pragma once

template <class E>
class List {
public:
	List(const List<E>& other) = delete;
	void operator =(const List<E>& other) = delete;

	List() {};
	virtual ~List() {};
	virtual void insert(E elem) = 0;
	virtual void append(E elem) = 0;
	virtual void setElement(E elem) = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual E getElement() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atEnd() = 0;
	virtual bool atStart() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};