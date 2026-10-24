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