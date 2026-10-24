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
Clase Node:
	Nodo generico de una lista enlazada. Guarda un elemento y un puntero al
	siguiente nodo. Es utilizado por LinkedList.
*/

#pragma once

template <class E>
class Node {
public:
	E elem;
	Node<E>* next;

	Node() : elem(), next(nullptr) {}
	Node(E elem, Node<E>* next = nullptr) : elem(elem), next(next) {}
};
