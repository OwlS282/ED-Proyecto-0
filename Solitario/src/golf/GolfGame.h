/*
Instituto Tecnologico de Costa Rica

Integrantes:	Owel Jafet Gutiérrez Ortiz,		2026800869
				Miranda Jiménez Alvarado,		2026008618
				Keishiro Gabriel Cubero Abe,	2026091245
				Eduardo Alfonso Moreno Pérez,	2025080891

Profesor : Mauricio Aviles Cisneros

Semana 13 : Proyecto 0 - Juegos de Solitario

Fecha de entrega : 26 / 10 / 2026

*/

/*
Clase GolfGame:
	El juego Solitario Golf se juego con 52 cartas 
	35 cartas de ellas repartidas en siete columnas de cinco elementos
	cada una, 16 de las cartas restantes se mantienen en el mazo y la ultima 
	carta restante se mantiene boca arriba.
	El juego consiste en utilizar la carta boca arriba para ir descartando 
	poco a poco las cartas de las columnas; esto es posible si las cartas al 
	final de las columnas es mayor o menos por uno que la carta boca arriba, 
	una vez se desarta una carta esta pasa a ser la carta boca arriba que se
	usa para comparar en la siguiente jugada.
	El juego funciona por 9 rondas en las que se acumulan puntos. 
	-Una ronda se considera ganada sí ya no quedan cartas en las columnas, 
	además se dan -1 punto por cada carta que quede en el mazo.
	-Una ronda ronda se considera perdida si aún queda cartas en las 
	columnas y ya no quedan cartas en el mazo o movimientos válidos. 
	Entre menor sea el puntaje total de las 9 rondas se considera ganado
	o perdido el juego. 

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
	void startRound() //Reinicia los valores que se deben utilizar en cada ronda. 
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

		void endRound() //Actualiza los puntajes con la información de la ronda. 
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
		Card getColumnTop(int numColumn) //Busca el elemento en el tope de una columna especifica.
		{
			columns[numColumn].goToPos(columns[numColumn].getSize() - 1);
			return columns[numColumn].getElement();
		}
		Card getDiscardPileTop()
		{
			return discardPile.topValue(); //Busca el elemtno en el tope de la columna de descarte.
		}

		void ColumnToDiscard(int numColumn) //Mueve un elemento de la columna a la pila de descarte.
		{
			Card columnCard = getColumnTop(numColumn);
			discardPile.push(columnCard);
			columns[numColumn].remove();
		}
		void DiscardToColumn(int numColumn) //Mueve un elemento de la pila de descarte a la columna donde estaba.
		{
			Card discardCard = discardPile.pop();
			columns[numColumn].append(discardCard);
		}
		void DeckToDiscard() //Mueve un elemnto del mazo a la pila de descarte 
		{
			discardPile.push(stock.draw());
		}
		void DiscardToDeck() //Mueve un elemento de la pila de descarte de regreso al mazo.
		{
			stock.putBack(discardPile.pop());
		}
		bool isValidMove(int numColumn) //Comprueba si un elemento es válido o no.
		{
			if (numColumn < 0 || numColumn >= columnAmount)
				return false;
			else if (columns[numColumn].getSize() == 0)
				return false;
			return getColumnTop(numColumn).isAdjacentRank(getDiscardPileTop());
		}
		bool isStockEmpty() //Revisa si el mazo está vacío. 
		{
			return stock.isEmpty();
		}

		void init() //Empieza un nuevo juego.
		{	
			cout << "Golf Game" << endl;
			reset();
		}
		void end() //Finaliza un juego e imprime sus resultados.
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
		int options() //Imprime las jugadas disponibles y recoje la opción escogida.
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
		string Status() //Calcula el estado final del juego.
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
		void reset() //Reinicia los valorres necesarios para un nuevo juego.
		{
			numRound = 0;
			totalScore = 0;
			roundScore = 0;
			wonRounds = 0;
			lostRounds = 0;
			abandoned = false;
			discardPile.clear();
		}
		bool isRoundFinished() //Comprueba si una ronda terminó o uno.
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
		bool AreThereMoves() //Comprueba si hay movimientos disponibles.
		{
			for (int i = 0; i < columnAmount; i++)
				if (isValidMove(i))
					return true;
			return false;
		}
		int setColumn() // Recibe la columna a utilizar en una jugada y la devuelve.
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
		void abandon() //Agrega los resultados de abandonar una ronda. 
		{

			abandoned = true;
			totalScore += 35 * (9 - numRound);
			endRound();
		}
};	
#include "GolfActions.h"