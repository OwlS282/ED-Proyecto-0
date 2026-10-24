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
	Descripcion...
*/

#pragma once

#include "SpiderGame.h"

// Cada accion guarda un puntero al juego para poder usar sus operaciones.
// El parametro Game& g de doAction / undoAction se exige por la clase Action, pero aqui no se usa.

class SpiderMoveAction : public Action {
private:
	SpiderGame* game;  // Puntero al juego principal Spider
	int from;          // Indice de la columna origen (0 a 9)
	int to;            // Indice de la columna destino (0 a 9)
	int count;         // Cantidad de cartas a mover
	bool flipped;      // Se volteo una carta al dejar la columna origen descubierta?
	bool completedSeq; // El movimiento completo una secuencia K..A en el destino?

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
	}

	// Ejecuta el movimiento, voltea la carta descubierta y retira la secuencia si se completa
	void doAction(Game& g) override {
		// TODO: mover las cartas con transfer, voltear la carta descubierta,
		// retirar la secuencia si se completa y sumar un movimiento

	}

	// Revierte el movimiento: restaura secuencia completada, reoculta la carta descubierta y regresa el bloque
	void undoAction(Game& g) override {
		// TODO: restaurar la secuencia retirada, voltear de nuevo la carta
		// descubierta, regresar las cartas y restar un movimiento

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
		// TODO: poner una carta del stock en cada columna, retirar las
		// secuencias que se completen y sumar un movimiento

	}

	// Deshace el reparto: restaura secuencias retiradas y regresa las cartas repartidas al mazo/stock
	void undoAction(Game& g) override {
		// TODO: regresar las cartas repartidas al stock, restaurar las
		// secuencias retiradas y restar un movimiento

	}
};

// Metodos de SpiderGame que crean acciones

// Valida las reglas de reparto e invoca la acción SpiderDealAction
void SpiderGame::drawFromStock() {
	// TODO: validar que haya stock y que ninguna columna este vacia,
	// y ejecutar un SpiderDealAction con executeAction

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