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
Clase Card:
	Representa una carta de la baraja con un rango del 1 al 13 y un estado
	(boca arriba o boca abajo). Permite compararla con otra carta (mismo
	rango, rango adyacente o rango adyacente mayor), voltearla e imprimirla
	(A, J, Q, K, o ? si esta boca abajo). Lanza una excepcion si el rango
	no es valido.
*/

#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>

using std::cout;
using std::runtime_error;

class Card {
private:
	int rank;		// Rango de la carta (1 = As, 11 = J, 12 = Q, 13 = K)
	bool faceUp;	// Estado de visibilidad (true = boca arriba, false = boca abajo)
public:
	static const int maxRank = 13;	// Rango máximo permitido (Rey)

	// Constructor por defecto: As boca arriba
	Card() : rank(1), faceUp(true) {}

	// Constructor con validación de rango válido [1, 13]
	Card(int rank, bool faceUp = true) {
		if (rank < 1 || rank > 13) {
			throw std::runtime_error("Carta invalida.");
		}
		this->rank = rank;
		this->faceUp = faceUp;
	}

	// Compara si dos cartas tienen el mismo rango
	bool sameRank(const Card& other) const {
		return other.rank == this->rank;
	}

	// Compara si el rango es adyacente (diferencia de 1, o 12 para la secuencia circular K-A)
	bool isAdjacentRank(const Card& other) const {
		int diff = std::abs(this->rank - other.rank);
		return diff == 1 || diff == 12;  // K-A cuenta como adyacente
	}

	// Verifica si la carta 'other' es exactamente un rango superior (ej: esta 4, 'other' 5)
	bool isBiggerAdjacentRank(const Card& other) const {
		int diff = other.rank - this->rank;
		return diff == 1;
	}

	// Retorna true si la carta está boca arriba
	bool isFaceUp() const {
		return this->faceUp;
	}

	// Cambia explícitamente el estado de visibilidad
	void setFaceUp(bool v) {
		this->faceUp = v;
	}

	// Alterna la cara de la carta (boca arriba <-> boca abajo)
	void flip() {
		this->faceUp = !this->faceUp;
	}

	// Sobrecarga de operador de salida: imprime ?, A, J, Q, K o el número según su rango y visibilidad
	friend std::ostream& operator<<(std::ostream& os, const Card& c) {
		if (!c.faceUp) {
			return os << "?";
		}

		switch (c.rank) {

		case 1:
			return os << "A";
		case 11:
			return os << "J";
		case 12:
			return os << "Q";
		case 13:
			return os << "K";
		default:
			return os << c.rank;
		}
	}
};