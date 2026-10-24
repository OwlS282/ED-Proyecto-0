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
Clase SpiderGame:
	Descripcion...
*/

#pragma once

#include <iostream>
#include "../core/Game.h"
#include "../structures/ArrayStack.h"
#include "../core/Card.h"

using std::cout;
using std::cin;


// Spider de un solo palo: 2 mazos (104 cartas), 10 columnas.
// Se reparten 54 cartas (4 columnas de 6 y 6 de 5), solo la ultima de cada columna boca arriba.
// El stock (50 cartas) se reparte de a 10: una carta por columna.
// Se mueven secuencias descendentes consecutivas (ej. 7-6-5) y al completar K..A se retiran.
class SpiderGame : public Game {
private:
	static const int numColumns = 10;		// Cantidad fija de columnas del tablero
	static const int totalSequences = 8;	// Secuencias K..A necesarias para ganar
	static const int sequenceLength = 13;	// Longitud de una secuencia completa

	int numRound = 0;	// Contador de rondas jugadas
	int completed = 0;	// Secuencias K..A completadas y retiradas
	int moves = 0;		// Movimientos realizados en la partida actual

	// Retorna la carta ubicada en un índice específico (0 a size - 1) dentro de una columna
	Card cardAt(int col, int idx) {
		this->columns[col].goToPos(idx);
		return this->columns[col].getElement();
	}

	// Valida que el bloque desde 'idx' al final de la columna sea una secuencia descendente continua y visible
	bool isMovableSequence(int col, int idx) {
		int size = this->columns[col].getSize();
		Card prev = this->cardAt(col, idx);
		if (!prev.isFaceUp()) {
			return false;
		}

		for (int i = idx + 1; i < size; i++) {
			Card c = this->cardAt(col, i);
			if (!c.isFaceUp() || !c.isBiggerAdjacentRank(prev)) {
				return false;
			}
			prev = c;
		}

		return true;
	}

public:
	// Constructor: inicializa el juego base con 2 mazos, 10 columnas y limite de 50 deshacer
	SpiderGame() : Game(2, numColumns, 50) {}

	void init() override;
	void play() override;
	void end() override;
	void drawFromStock() override;					// Reparte 10 cartas (definido en SpiderActions.h)
	void moveSequence(int from, int pos, int to);	// Ejecuta el movimiento (definido en SpiderActions.h)
	void printGameState() override;

	// Retorna true si se han completado las 8 secuencias necesarias para ganar
	bool isWon() {
		return this->completed >= totalSequences;
	}

	// Métodos auxiliares para uso de las Acciones (doAction / undoAction)

	// Retorna la cantidad de cartas en una columna dada 
	int colSize(int col) {
		return this->columns[col].getSize();
	}

	// Extrae y retorna la carta superior del mazo (stock)
	Card takeFromStock() {
		return this->stock.draw();
	}

	// Devuelve una carta al mazo/stock
	void returnToStock(Card c) {
		this->stock.putBack(c);
	}

	// Remueve y retorna la última carta (tope) de la columna especificada
	Card takeFromColumn(int col) {
		this->columns[col].goToEnd();
		this->columns[col].previous();
		return this->columns[col].remove();
	}

	// Inserta una carta al final de la columna especificada
	void returnToColumn(int col, Card c) {
		this->columns[col].append(c);
	}

	// Verifica si la carta superior de la columna está boca abajo
	bool topIsFaceDown(int col) {
		if (this->colSize(col) == 0) {
			return false;
		}
		Card c = this->cardAt(col, this->colSize(col) - 1);
		return !c.isFaceUp();
	}

	// Invierte la visibilidad (boca arriba/abajo) de la última carta de la columna
	void flipTop(int col) {
		this->columns[col].goToEnd();
		this->columns[col].previous();
		Card c = this->columns[col].getElement();
		c.flip();
		this->columns[col].setElement(c);
	}

	// Verifica si las últimas 13 cartas de una columna forman la secuencia completa K..A boca arriba
	bool hasCompleteSequence(int col) {
		// TODO: revisar si las ultimas 13 cartas son K, Q, J, ..., 2, A boca arriba
		return false;

	}

	// Elimina las últimas 13 cartas de la columna e incrementa el contador de secuencias
	void removeSequence(int col) {
		// TODO: sacar las ultimas 13 cartas de la columna y sumar 1 a completed

	}

	// Devuelve las 13 cartas K..A a la columna (utilizado al deshacer)
	void restoreSequence(int col) {
		// TODO: devolver las 13 cartas K..A a la columna y restar 1 a completed

	}

	// Ajusta la cantidad total de movimientos (+1 al realizar o -1 al deshacer)
	void addMoves(int n) {
		this->moves += n;
	}
};

// Metodos de SpiderGame

// Prepara el tablero para una nueva ronda
void SpiderGame::init() {
	this->clearUndoHistory();
	this->clearRedoHistory();
	for (int i = 0; i < this->columnAmount; i++) {
		this->columns[i].clear();
	}

	this->stock.reset();
	this->stock.shuffle();

	// Reparte 54 cartas iniciales (4 columnas de 6 y 6 columnas de 5)
	for (int row = 0; row < 6; row++) {
		for (int col = 0; col < this->columnAmount; col++) {
			int height;
			if (col < 4) {
				height = 6;
			}
			else {
				height = 5;
			}

			if (row < height) {
				Card c = this->stock.draw();
				c.setFaceUp(row == height - 1);  // solo la ultima boca arriba
				this->columns[col].append(c);
			}
		}
	}

	this->numRound++;
	this->completed = 0;
	this->moves = 0;
}

// Imprime las columnas del tablero, las reparticiones disponibles, secuencias y el puntaje
void SpiderGame::printGameState() {
	cout << "\n|    Spider - Ronda " << this->numRound << "    |\n";
	this->printColumns();
	cout << "\nReparticiones restantes: " << this->stock.getSize() / this->columnAmount
		<< "    Secuencias: " << this->completed << "/" << totalSequences
		<< "    Puntos: " << (500 - this->moves + 100 * this->completed) << "\n";
}

// TODO: bucle principal que lea los comandos (m, d, u, r, q)
void SpiderGame::play() {
	cout << "Spider aun no esta implementado.\n";
}

// TODO: mostrar mensaje final y puntaje
void SpiderGame::end() {
	cout << "\nPartida terminada.\n";
}

// Las acciones (y los metodos que las crean) van en SpiderActions.h.
// Este include va AL FINAL, cuando SpiderGame ya esta definida.
#include "SpiderActions.h"