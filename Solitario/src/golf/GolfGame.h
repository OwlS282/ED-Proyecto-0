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
Clase GolfGame:S
	Descripcion...
*/

#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include "../core/Game.h"
#include "../structures/ArrayStack.h"
#include "../core/Card.h"

using std::cout;
using std::endl;
using std::cin;
using std::runtime_error;
using std::string;

class GolfGame : public Game {
private:
	int numRound = 0;
	int totalScore = 0;
	int roundScore = 0;
	int wonRounds = 0;
	int lostRounds = 0;
	bool abandoned = false;
	ArrayStack<Card> discardPile;



public:
	GolfGame() : Game(1,7,100), discardPile(52) {}
	void startRound()
	{
		for (int i = 0; i < columnAmount; i++)
		{
			columns[i].clear();
		}
		discardPile.clear();
		stock.reset();
		roundScore = 0;
		stock.shuffle();
		for (int i = 0; i < columnAmount; i++)
			for (int j = 0; j < 5; j++)
			{
				columns[i].append(stock.draw());
			}
		discardPile.push(stock.draw());
		clearRedoHistory();
		clearUndoHistory();
		numRound += 1;
		cout << "Se va a iniciar la ronda: " << numRound << endl;
		cout << "Su puntaje hasta el momento es: " << totalScore << endl;

	}
	void play();
		void endRound()
		{
			int waste = 0;
			for (int i = 0; i < columnAmount; i++)
				waste += columns[i].getSize();
			if (waste != 0)
			{
				roundScore = waste;
				cout << "Ronda Perdida." << endl;
				lostRounds += 1;
			}
			else
			{
				roundScore = -stock.getSize();
				cout << "Ronda Ganada." << endl;
				wonRounds += 1;
			}
			totalScore += roundScore;
			discardPile.clear();
		}
		void drawFromStock();
		Card getColumnTop(int numColumn)
		{
			columns[numColumn].goToPos(columns[numColumn].getSize() - 1);
			return columns[numColumn].getElement();
		}
		Card getDiscardPileTop()
		{
			return discardPile.topValue();
		}

		void ColumnToDiscard(int numColumn)
		{
			Card columnCard = getColumnTop(numColumn);
			discardPile.push(columnCard);
			columns[numColumn].remove();
		}
		void DiscardToColumn(int numColumn)
		{
			Card discardCard = discardPile.pop();
			columns[numColumn].append(discardCard);
		}
		void DeckToDiscard()
		{
			discardPile.push(stock.draw());
		}
		void DiscardToDeck()
		{
			stock.putBack(discardPile.pop());
		}
		bool isValidMove(int numColumn)
		{
			if (numColumn < 0 || numColumn >= columnAmount)
				return false;
			else if (columns[numColumn].getSize() == 0)
				return false;
			return getColumnTop(numColumn).isAdjacentRank(getDiscardPileTop());
		}
		bool isStockEmpty()
		{
			return stock.isEmpty();
		}

		void init()
		{	
			cout << "Golf Game" << endl;
			reset();
		}
		void end()
		{
			cout << "Juego finalizado." << endl;
			if (abandoned)
				cout << "Abandono el juego" << endl;
			else
			{
				cout << "Gano " << wonRounds << " rondas" << endl;
				cout << "Perdio " << lostRounds << " rondas" << endl;
			}
			cout << "El estado final de su juego es: " << Status() << endl;
			cout << "Su puntaje total fue:  " << totalScore << endl;
			cout << "Gracias por jugar" << endl;
		}
		int options()
		{
			cout << "1. Quitar de columna." << endl;
			cout << "2. Sacar del mazo." << endl;
			cout << "3. Deshacer." << endl;
			cout << "4. Rehacer." << endl;
			cout << "5. Abandonar." << endl;
			int option;
			cin >> option;
			if (option >= 1 && option <= 5)
				return option;
			cin.clear();
			cin.ignore(1000, '\n');
			return -1;
		}
		string Status()
		{
			string status;
			if (totalScore <= 0)
				status = "PERFECTO";
			else if (totalScore <= 45)
				status = "REGULAR";
			else
				status = "MALO";
			return status;
		}
		void reset()
		{
			numRound = 0;
			totalScore = 0;
			roundScore = 0;
			wonRounds = 0;
			lostRounds = 0;
			abandoned = false;
			discardPile.clear();
		}
		bool isRoundFinished()
		{
			int temp = 0;
			for (int i = 0; i < columnAmount; i++)
				temp += columns[i].getSize();
			if (temp == 0)
				return true;
			else if (stock.isEmpty() && !AreThereMoves())
				return true;
			return false;
		}
		bool AreThereMoves()
		{
			for (int i = 0; i < columnAmount; i++)
				if (isValidMove(i))
					return true;
			return false;
		}
		int setColumn()
		{
			cout << "Digite el numero de la columna donde se encuentra la carta que sea descartar" << endl;
			int column;
			cin >> column;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				return -1;
			}
			return column;

		}
		void abandon()
		{

			abandoned = true;
			totalScore += 35 * (9 - numRound);
			endRound();
		}
};	
#include "GolfActions.h"