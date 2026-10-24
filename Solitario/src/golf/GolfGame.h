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
Clase GolfGame:
	Descripcion...
*/

#pragma once
#include "../core/Game.h"
#include "../structures/ArrayStack.h"
#include "../core/Card.h"


class GolfGame : public Game {
private:
	int numRound = 0;
	int totalScore = 0;
	int roundScore = 0;
	int wonRounds = 0;
	int lostRounds = 0;
	ArrayStack<Card> discardPile;



public:
	GolfGame() : Game(1,7,100), discardPile(52) {}
	void init()
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


	}
	void play()
	{

	}
	void end()
	{
		int waste = 0;
		for (int i = 0; i < columnAmount; i++)
			waste += columns[i].getSize();
		if (waste != 0)
		{
			roundScore = waste;
			lostRounds += 1;
		}
		else
		{
			roundScore = -stock.getSize();
			wonRounds += 1;
		}
		totalScore += roundScore;

	}
	void drawFromStock()
	{
		if (!stock.isEmpty())
		{
			executeAction(new MovefromStock());
		}

	}
	Card getColumnTop(int numColumn)
	{
		columns[numColumn].goToPos(columns[numColumn].getSize() - 1);
		return columns[numColumn].getElement();
	}
	Card getDiscardPileTop()
	{
		return discardPile.topValue()
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
	bool isValideMove(int numColumn)
	{
		if (numColumn < 1 || numColumn > 7)
			return false;
		else if (columns[numColumn].getSize() == 0)
			return false;
		else if (getColumnTop(numColumn).isAdjacentRank(getDiscardPileTop()))
			return true;
	}
	bool isStockEmpty()
	{
		return stock.isEmpty();
	}
};