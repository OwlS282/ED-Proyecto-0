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
Clase SpiderMoveAction:
	Accion que mueve una secuencia de cartas de una columna a otra en
	Spider. Al ejecutarse voltea la carta que queda descubierta y retira la
	secuencia si se completa de la K a la A. Guarda lo ocurrido para poder
	deshacer el movimiento.
*/

#pragma once

#include "SpiderGame.h"

// Cada accion guarda un puntero al juego para poder usar sus operaciones.
// El parametro Game& g de doAction / undoAction se exige por la clase Action, pero aqui no se usa.

class SpiderMoveAction : public Action {
private:
	SpiderGame* game;			// Puntero al juego principal Spider
	int from;					// Indice de la columna origen (0 a 9)
	int to;						// Indice de la columna destino (0 a 9)
	int count;					// Cantidad de cartas a mover
	bool flipped;				// Se volteo una carta al dejar la columna origen descubierta?
	bool completedSeq;			// El movimiento completo una secuencia K..A en el destino?
	bool flippedDestination;	// Se agregó para lidiar con un edgecase en particular

	// Mueve 'n' cartas de la columna origen a la destino manteniendo el orden original usando una pila auxiliar
	void transfer(int src, int dst, int n) {
		ArrayStack<Card> tmp(13);
		for (int i = 0; i < n; i++) {
			tmp.push(this->game->takeFromColumn(src));
		}

		while (!tmp.isEmpty()) {
			this->game->returnToColumn(dst, tmp.pop());
		}
	}

public:
	// Constructor de la accion de movimiento
	SpiderMoveAction(SpiderGame* game, int from, int to, int count) {
		this->game = game;
		this->from = from;
		this->to = to;
		this->count = count;
		this->flipped = false;
		this->completedSeq = false;
		this->flippedDestination = false;
	}

	// Ejecuta el movimiento, voltea la carta descubierta y retira la secuencia si se completa
	void doAction(Game& g) override {
		this->flipped = false;
		this->completedSeq = false;
		this->flipped = false;
		this->completedSeq = false;
		this->flippedDestination = false;

		this->transfer(this->from, this->to, this->count);
		if (this->game->topIsFaceDown(this->from)) {
			this->game->flipTop(this->from);
			this->flipped = true;
		}

		if (this->game->hasCompleteSequence(this->to)) {
			this->game->removeSequence(this->to);
			this->completedSeq = true;

			if (this->game->topIsFaceDown(this->to)) {
				this->game->flipTop(this->to);
				this->flippedDestination = true;
			}
		}

		this->game->addMoves(1);
	}

	// Revierte el movimiento: restaura secuencia completada, reoculta la carta descubierta y regresa el bloque
	void undoAction(Game& g) override {
		if (this->completedSeq) {
			if (this->flippedDestination) {
				this->game->flipTop(this->to);
			}

			this->game->restoreSequence(this->to);
		}

		if (this->flipped) {
			this->game->flipTop(this->from);  // vuelve a quedar boca abajo
		}

		this->transfer(this->to, this->from, this->count);
		this->game->addMoves(-1);
	}

};

/*
Clase SpiderDealAction:
	Accion que reparte una carta del stock en cada columna de Spider. Guarda
	en que columnas se completo una secuencia para poder deshacer el reparto
	y devolver las cartas al stock.
*/

class SpiderDealAction : public Action {
private:
	SpiderGame* game;       // Puntero al juego principal Spider
	bool completedCol[10];  // En cuales columnas se completo una secuencia al repartir

public:
	// Constructor: inicializa el registro de secuencias completadas
	SpiderDealAction(SpiderGame* game) {
		this->game = game;
		for (int i = 0; i < 10; i++) {
			this->completedCol[i] = false;
		}
	}

	// Reparte una carta a cada columna y remueve las secuencias completadas
	void doAction(Game& g) override {
		for (int col = 0; col < 10; col++) {
			this->completedCol[col] = false;
			this->game->returnToColumn(col, this->game->takeFromStock());
			if (this->game->hasCompleteSequence(col)) {
				this->game->removeSequence(col);
				this->completedCol[col] = true;
			}
		}
		this->game->addMoves(1);
	}

	// Deshace el reparto: restaura secuencias retiradas y regresa las cartas repartidas al mazo/stock
	void undoAction(Game& g) override {
		for (int col = 9; col >= 0; col--) {
			if (this->completedCol[col]) {
				this->game->restoreSequence(col);
			}
			this->game->returnToStock(this->game->takeFromColumn(col));
		}
		this->game->addMoves(-1);
	}
};

// Metodos de SpiderGame que crean acciones

// Valida las reglas de reparto e invoca la acción SpiderDealAction
void SpiderGame::drawFromStock() {
	if (this->stock.getSize() < this->columnAmount) {
		cout << "Error, El stock esta vacio.\n";
		return;
	}

	for (int i = 0; i < this->columnAmount; i++) {
		if (this->columns[i].getSize() == 0) {
			cout << "Error, No puedes repartir con columnas vacias.\n";
			return;
		}
	}

	this->executeAction(new SpiderDealAction(this));
}

// Valida la legalidad de mover una secuencia entre columnas e invoca SpiderMoveAction
void SpiderGame::moveSequence(int from, int pos, int to) {
	if (from < 1 || from > this->columnAmount || to < 1 || to > this->columnAmount) {
		cout << "Error, Columna invalida (1-" << this->columnAmount << ").\n";
		return;
	}

	if (from == to) {
		cout << "Error, Origen y destino son la misma columna.\n";
		return;
	}

	int f = from - 1;
	int t = to - 1;
	int size = this->columns[f].getSize();

	if (pos < 1 || pos > size) {
		cout << "Error, Posicion invalida en la columna " << from << ".\n";
		return;
	}

	int idx = pos - 1;

	if (!this->isMovableSequence(f, idx)) {
		cout << "Error, Esas cartas no forman una secuencia descendente boca arriba.\n";
		return;
	}

	if (this->columns[t].getSize() > 0) {
		Card destTop = this->cardAt(t, this->columns[t].getSize() - 1);
		Card first = this->cardAt(f, idx);
		if (!first.isBiggerAdjacentRank(destTop)) {
			cout << "Error, Jugada ilegal: el destino debe tener una carta con rango uno mayor.\n";
			return;
		}
	}

	this->executeAction(new SpiderMoveAction(this, f, t, size - idx));
}