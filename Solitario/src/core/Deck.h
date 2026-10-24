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
Clase Deck:
	Representa un mazo formado por una o mas barajas de 52 cartas, guardadas
	en un ArrayList. Permite barajar, robar una carta del final, devolver una
	carta (para deshacer jugadas) y reiniciar el mazo para una nueva ronda.
	Lanza una excepcion si la cantidad de barajas es invalida o si se roba de
	un mazo vacio.
*/

#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "../structures/ArrayList.h"
#include "../core/Card.h"


using std::runtime_error;

class Deck {
private:
	// Cantidad estándar de cartas por baraja
	static const int cardsInADeck = 52;

	ArrayList<Card> cards;	// Colección de cartas almacenadas en la lista
	int amount;				// Cantidad de barajas de 52 cartas que conforman el mazo

	// Valida que la cantidad de barajas sea mayor a 0 y retorna la capacidad total requerida
	static int validatedSize(int amount) {
		if (amount <= 0) {
			throw runtime_error("Error, Cantidad invalida de cartas.");
		}
		return cardsInADeck * amount;
	}

	// Vacía la lista y genera de nuevo las cartas ordenadas (4 palos por cada baraja)
	void fill() {
		this->cards.clear();
		for (int i = 0; i < this->amount; i++) {
			for (int suit = 0; suit < 4; suit++) {
				for (int rank = 1; rank <= Card::maxRank; rank++) {
					this->cards.append(Card(rank));
				}
			}
		}
	}

public:
	// Constructor: inicializa la capacidad interna y llena el mazo con la cantidad de barajas dada
	Deck(int amount) : cards(validatedSize(amount)), amount(amount) {
		this->fill();
	}

	// Rellena el mazo dejándolo completo nuevamente para una nueva partida
	void reset() {
		this->fill();
	}

	// MezcLA las cartas usando el algoritmo Fisher-Yates y reinicia el cursor al inicio
	void shuffle() {
		int size = this->cards.getSize();
		for (int i = size - 1; i > 0; i--) {
			int j = std::rand() % (i + 1);
			this->cards.swapElements(i, j);
		}
		this->cards.goToStart();
	}

	// Extrae y retorna la última carta del mazo en O(1)
	Card draw() {
		if (this->cards.getSize() == 0) {
			throw runtime_error("Error, Deck is empty.");
		}
		this->cards.goToPos(this->cards.getSize() - 1);
		return this->cards.remove();
	}

	// Inserta una carta de vuelta al final del mazo (utilizado para operaciones de Undo)
	void putBack(Card c) {
		this->cards.append(c);
	}

	// Retorna true si ya no quedan cartas en el mazo
	bool isEmpty() {
		return this->cards.getSize() == 0;
	}

	// Retorna la cantidad de cartas disponibles actualmente en el mazo
	int getSize() {
		return this->cards.getSize();
	}
};