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
Clase Action:
	Clase abstracta base para las acciones del juego que se pueden deshacer
	y rehacer. Define los metodos doAction y undoAction, que cada accion
	concreta implementa. No se puede copiar.
*/

#pragma once

// Evita dependencias circulares con la clase del juego
class Game;

class Action {
public:
	Action() {}
	// Sin copia: cada acción debe ser única
	Action(const Action& other) = delete;
	void operator=(const Action& other) = delete;
	virtual ~Action() = default;
	virtual void doAction(Game& g) = 0;				// Aplica la acción sobre el juego
	virtual void undoAction(Game& g) = 0;			// Revierte la acción realizada
};