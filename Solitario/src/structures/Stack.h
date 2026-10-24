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
Clase Stack:
	Clase abstracta plantilla que define el TDA pila. Declara las
	operaciones de apilar, desapilar, consultar el tope, limpiar, saber si
	esta vacia y obtener su tamano. Es implementada por ArrayStack. No se
	puede copiar.
*/

#pragma once

template <class E>
class Stack {
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
};
