#pragma once
#include "Game.h"
#include "ArrayStack.h"
#include "Card.h"



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

		}
		void play()
		{

		}
		void end()
		{

		}
		void drawFromStock()
		{

		}

};