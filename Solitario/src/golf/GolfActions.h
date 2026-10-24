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
