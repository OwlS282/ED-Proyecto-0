#pragma once

class Game;

class Action
{
public:
	Action() {}
	Action(const Action& other) = delete;
	void operator=(const Action& other) = delete;

	virtual ~Action() = default;  // maybe?
	virtual void doAction(Game& g) = 0;
	virtual void undoAction(Game& g) = 0;
};

