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
Clase MovefromColumns:
	Descripcion...
*/

#pragma once

#include "GolfGame.h"

class MovefromColumns : public Action
{
private:
	int column;
public:
	MovefromColumns(int column)
	{
		this->column = column;
	}
	void doAction(Game& g)
	{
		GolfGame& game = static_cast<GolfGame&>(g);
		game.ColumnToDiscard(column);
	}
	void undoAction(Game& g)
	{
		GolfGame& game = static_cast<GolfGame&>(g);
		game.DiscardToColumn(column);
	}
};

class MovefromStock : public Action
{
public:
	MovefromStock() {}
	void doAction(Game& g)
	{
		GolfGame& game = static_cast<GolfGame&>(g);
		game.DeckToDiscard();
	}
	void undoAction(Game& g)
	{
		GolfGame& game = static_cast<GolfGame&>(g);
		game.DiscardToDeck();
	}

};
inline void GolfGame::drawFromStock()
{
	if (!stock.isEmpty())
	{
		executeAction(new MovefromStock());
	}
}
inline void GolfGame::play()
{
	while (numRound < 9 && !abandoned)
	{
		startRound();
		while (!isRoundFinished() && !abandoned)
		{
			cout << "Quedan " << stock.getSize() << " en el mazo" << endl;
			cout << "La carta en el tope de descarte es: " << discardPile.topValue() << endl;
			printColumns();
			if (!AreThereMoves())
				cout << "Se le recomienda sacar una carta del mazo" << endl;
			int move = options();
			if (move == 1)
			{
				int column = setColumn() - 1;
				if (isValidMove(column))
					executeAction(new MovefromColumns(column));
				else
					cout << "Movimiento Invalido" << endl;
			}
			else if (move == 2)
			{
				if (!isStockEmpty())
					drawFromStock();
				else
					cout << "Movimiento Invalido" << endl;
			}
			else if (move == 3)
				undo();
			else if (move == 4)
				redo();
			else if (move == 5)
				abandon();
			else
				cout << "Movimiento Invalido" << endl;
		}
		if (!abandoned)
			endRound();


	}
}
