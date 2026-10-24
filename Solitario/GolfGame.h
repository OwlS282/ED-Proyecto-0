#pragma once
#include "Game.h"
#include "ArrayStack.h"
#include "Card.h"
#include "Deck.h"
#include "LinkedList.h"



class GolfGame : public Game
{
private:
	int numRound = 0;
	int totalScore = 0;
	int roundScore = 0;
	ArrayStack<Card> discardPile;

	public:
		GolfGame() : Game(1,7), discardPile(52) {}
		void init()
		{
			for (int i = 0; i < columnAmount; i++)
				columns[i].clear();
			discardPile.clear();
			stock.reset();
			clearRedoHistory();
			clearUndoHistory();
			roundScore = 0;
			stock.shuffle();
			for (int i = 0; i < columnAmount; i++)
				for (int j = 0; j < 5; j++)
				{
					columns[i].append(stock.draw());
				}
			discardPile.push(stock.draw());
			numRound += 1;
		}

		void end()
		{

		}
		void play()
		{

		}
		void drawFromStock()
		{
			b  
		}

};