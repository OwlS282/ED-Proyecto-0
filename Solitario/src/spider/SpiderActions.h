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

	// TODO: transfer(int src, int dst, int n)
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

	// TODO: mover las cartas, voltear la descubierta y retirar la secuencia si se completa
	void doAction(Game& g) override {
	}

	// TODO: revertir el movimiento
	void undoAction(Game& g) override {
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

	// TODO: repartir una carta a cada columna y retirar las secuencias completas
	void doAction(Game& g) override {
	}

	// TODO: deshacer el reparto
	void undoAction(Game& g) override {
	}
};

// Metodos de SpiderGame que crean acciones

// TODO: validar el reparto y ejecutar SpiderDealAction
void SpiderGame::drawFromStock() {
}

// TODO: validar el movimiento y ejecutar SpiderMoveAction
void SpiderGame::moveSequence(int from, int pos, int to) {
}