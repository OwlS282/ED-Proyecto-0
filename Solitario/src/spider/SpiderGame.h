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

class SpiderGame : public Game {
private:
	static const int numColumns = 10;		// Cantidad fija de columnas del tablero
	static const int totalSequences = 8;	// Secuencias K..A necesarias para ganar
	static const int sequenceLength = 13;	// Longitud de una secuencia completa

	int numRound = 0;	// Contador de rondas jugadas
	int completed = 0;	// Secuencias K..A completadas y retiradas
	int moves = 0;		// Movimientos realizados en la partida actual

	// TODO: cardAt(int col, int idx)
	// TODO: isMovableSequence(int col, int idx)

public:
	// Constructor: inicializa el juego base con 2 mazos, 10 columnas y limite de 50 deshacer
	SpiderGame() : Game(2, numColumns, 50) {}

	void init() override;
	void play() override;
	void end() override;
	void drawFromStock() override;
	void moveSequence(int from, int pos, int to);
	void printGameState() override;

	// Retorna true si se han completado las 8 secuencias necesarias para ganar
	bool isWon() {
		return this->completed >= totalSequences;
	}

	// Retorna la cantidad de cartas en una columna dada
	int colSize(int col) {
		return this->columns[col].getSize();
	}

	// Ajusta la cantidad total de movimientos (+1 al realizar o -1 al deshacer)
	void addMoves(int n) {
		this->moves += n;
	}

	// TODO: takeFromStock, returnToStock
	// TODO: takeFromColumn, returnToColumn
	// TODO: topIsFaceDown, flipTop
	// TODO: hasCompleteSequence, removeSequence, restoreSequence
};

// Metodos de SpiderGame

// Prepara el tablero para una nueva ronda
void SpiderGame::init() {
	this->clearUndoHistory();
	this->clearRedoHistory();
	for (int i = 0; i < this->columnAmount; i++) {
		this->columns[i].clear();
	}

	// TODO: reiniciar el stock, mezclarlo y repartir las 54 cartas iniciales

	this->numRound++;
	this->completed = 0;
	this->moves = 0;
}

// TODO: imprimir columnas, reparticiones restantes, secuencias y puntos
void SpiderGame::printGameState() {
	cout << "\n|    Spider - Ronda " << this->numRound << "    |\n";
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