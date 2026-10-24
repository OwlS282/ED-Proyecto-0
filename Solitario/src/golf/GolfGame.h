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
	GolfGame() : Game(1,7), discardPile(52) {}
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
			discardPile.push(stock.draw());

	}

};