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
Clase Game:
	Clase abstracta base de los juegos de solitario. Administra las columnas
	de cartas (listas enlazadas), el stock (mazo) y los historiales de
	deshacer y rehacer, que guardan acciones. Define las operaciones que cada
	juego debe implementar (init, play, end y drawFromStock) e imprime las
	columnas del tablero.
*/

#pragma once

#include <ostream>
#include <iostream>
#include <stdexcept>
#include "../core/Deck.h"
#include "../core/Card.h"
#include "../core/Action.h"
#include "../structures/LinkedList.h"
#include "../structures/ArrayList.h"
#include "../structures/ArrayStack.h"

using std::cout;
using std::runtime_error;

class Game {
protected:
	const static int limitHistory = 10;		// Capacidad por defecto del historial de deshacer

	LinkedList<Card>* columns = nullptr;	// Arreglo dinámico de listas enlazadas para las columnas
	int columnAmount = 0;					// Cantidad total de columnas en el tablero
	Deck stock;								// Mazo principal de cartas del juego
	int maxHistory;							// Límite máximo de acciones almacenadas en el historial
	ArrayList<Action*> undoHistory;			// Historial circular/limitado de deshacer (descarta lo más viejo al llenarse)
	ArrayStack<Action*> redoHistory;		// Pila de acciones para rehacer


	// Constructor protegido: Inicializa columnas, mazo e historiales
	Game(int amount, int columnAmount, int maxHistory = limitHistory)
		: columns(new LinkedList<Card>[columnAmount]),
		  columnAmount(columnAmount),
		  stock(amount),
		  maxHistory(maxHistory),
		  undoHistory(maxHistory),
		  redoHistory(maxHistory)
	{}

	// Agrega una acción al historial de deshacer; descarta la más antigua si supera 'maxHistory'
	void pushUndo(Action* a) {
		if (this->undoHistory.getSize() >= this->maxHistory) {
			this->undoHistory.goToStart();
			delete this->undoHistory.remove();
		}
		this->undoHistory.append(a);
	}

	// Extrae la última acción realizada del historial de deshacer
	Action* popUndo() {
		this->undoHistory.goToPos(this->undoHistory.getSize() - 1);
		return this->undoHistory.remove();
	}

public:
	// Destructor virtual: Libera la memoria dinámica de historiales y columnas
	virtual ~Game() {
		this->clearRedoHistory();
		this->clearUndoHistory();
		delete[] this->columns;
	}

	// Métodos abstractos que debe implementar cada solitario concreto
	virtual void init() = 0;
	virtual void play() = 0;
	virtual void end() = 0;
	virtual void drawFromStock() = 0;

	// Ejecuta una acción válida, borra el historial de rehacer y guarda la acción en 'undo'
	void executeAction(Action* action) {
		if (action == nullptr) {
			return;
		}
		this->clearRedoHistory();
		action->doAction(*this);
		this->pushUndo(action);
	}

	// Deshace la última acción realizada y la traslada al historial de rehacer
	void undo() {
		if (this->undoHistory.getSize() == 0) {
			cout << "Nada que deshacer.\n";
			return;
		}
		Action* a = this->popUndo();
		a->undoAction(*this);
		this->redoHistory.push(a);
	}

	// Rehace la última acción deshecha y la devuelve al historial de deshacer
	void redo() {
		if (this->redoHistory.isEmpty()) {
			cout << "Nada que rehacer.\n";
			return;
		}
		Action* a = this->redoHistory.pop();
		a->doAction(*this);
		this->pushUndo(a);
	}

	// Libera la memoria de todas las acciones guardadas en el historial de deshacer
	void clearUndoHistory() {
		while (this->undoHistory.getSize() > 0) {
			delete this->popUndo();
		}
	}

	// Libera la memoria de todas las acciones guardadas en la pila de rehacer
	void clearRedoHistory() {
		while (!this->redoHistory.isEmpty()) {
			delete this->redoHistory.pop();
		}
	}

	// Imprime visualmente las columnas de cartas en consola en formato de cuadrícula (matriz por filas)
	void printColumns() {
		if (this->columnAmount == 0) {
			throw runtime_error("Error, No columns initiated.");
		}

		int maxColumnHeight = 0;
		for (int i = 0; i < this->columnAmount; i++) {
			cout << "C" << (i + 1) << "\t";
			if (this->columns[i].getSize() > maxColumnHeight) {
				maxColumnHeight = this->columns[i].getSize();
			}
		}
		cout << "\n";

		for (int row = 0; row < maxColumnHeight; row++) {
			for (int col = 0; col < this->columnAmount; col++) {
				if (row < this->columns[col].getSize()) {
					this->columns[col].goToPos(row);
					Card c = this->columns[col].getElement();
					cout << c << "\t";
				}
				else {
					cout << "\t";
				}
			}
			cout << "\n";
		}
	}

	// Imprime el estado visual básico del tablero de juego
	virtual void printGameState() {
		this->printColumns();
	}
};
