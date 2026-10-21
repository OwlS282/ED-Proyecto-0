#pragma once

#include <ostream>
#include <iostream>
#include <stdexcept>
#include "Deck.h"
#include "Card.h"
#include "Action.h"
#include "LinkedList.h"
#include "ArrayStack.h"

class Game
{
protected:
	const static int limitHistory = 10;

	LinkedList<Card>* columns = nullptr;
	ArrayStack<Action*> undoHistory;
	ArrayStack<Action*> redoHistory;
	Deck stock;
	int columnAmount = 0;

	Game(int amount, int columnAmount, int maxHistory = limitHistory) : undoHistory(maxHistory), redoHistory(maxHistory), stock(amount), columnAmount(columnAmount) 
	{
		columns = new LinkedList<Card>[columnAmount];
	}

public:
	virtual ~Game() {
		this->clearRedoHistory();
		this->clearUndoHistory();
		delete[] this->columns;
	}
	virtual void init() = 0;
	virtual void play() = 0;
	virtual void end() = 0;
	//virtual void drawFromColumn(int column, int cardPos) = 0;  // cardPos is irrelevant for Golf
	virtual void drawFromStock() = 0;

	void executeAction(Action* action) {
		if (action == nullptr) {
			return;
		}
		this->clearRedoHistory();
		action->doAction(*this);
		undoHistory.push(action);  // NOOOPE!!! (If history is full we should remove the last one and THEN push; Stack by itself can't do this. Dequeue or CircularStack could do this)
		// we also don't check if action is legal in this specific Game.h instance (AKA Golf or Spider). void methods in Golf/Spider that then create an action to pass it in here solve this.
	}

	void undo() {
		if (undoHistory.getSize() == 0) {
			return;
		}

		Action* a = undoHistory.pop();
		a->undoAction(*this);
		redoHistory.push(a);
	}
	void redo() {
		if (redoHistory.getSize() == 0) {
			return;
		}

		Action* a = redoHistory.pop();
		a->doAction(*this);
		undoHistory.push(a);
	}
	void clearUndoHistory() {
		while (!this->undoHistory.isEmpty()) {
			Action* a = this->undoHistory.pop();
			delete a;
		}
	}
	void clearRedoHistory() {
		while (!this->redoHistory.isEmpty()) {
			Action* a = this->redoHistory.pop();
			delete a;
		}
	}

	void printColumns() {
		if (this->columnAmount == 0) {
			throw std::runtime_error("No columns initiated.");
		}

		int maxColumnHeight = 0;
		for (int i = 0; i < this->columnAmount; i++) {
			std::cout << "C" << (i + 1) << "\t";
			if (this->columns[i].getSize() > maxColumnHeight) {
				maxColumnHeight = this->columns[i].getSize();
			}
		}
		std::cout << "\n";

		for (int row = 0; row < maxColumnHeight; row++) {
			for (int col = 0; col < this->columnAmount; col++) {
				if (row < this->columns[col].getSize()) {
					this->columns[col].goToPos(row);
					Card c = this->columns[col].getElement();
					std::cout << c << "\t";
				}
				else {
					std::cout << "\t";
				}
			}
			std::cout << "\n";
		}
	}

	void printGameState() {
		// differences in golf and spider; golf has the current card, spider dont
		this->printColumns();
		// and the stock
	}
};

