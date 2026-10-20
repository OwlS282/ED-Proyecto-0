#pragma once

#include <stdexcept>
#include <random>
#include <ctime>
#include "ArrayList.h"
#include "Card.h"

class Deck
{
private:
	ArrayList<Card> cards;
	static const int cardsInADeck = 52;

	void swap(Card* a, Card* b) {
		Card temp = *a;
		*a = *b;
		*b = temp;
	}
	static int validatedSize(int amount) {
		if (amount <= 0) {
			throw std::runtime_error("Cantidad invalida de cartas.");
		}

		return cardsInADeck * amount;
	}
public:
	Deck(int amount) : cards(validatedSize(amount)) {
		std::srand(std::time(nullptr));

		for (int i = 0; i < amount; i++) {
			for (int suit = 0; suit < 4; suit++) {
				for (int rank = 1; rank <= Card::maxRank; rank++) {
					Card c(rank);
					cards.append(c);
				}
			}
		}
	}

	void shuffle() {
		int size = this->cards.getSize();
		for (int i = size - 1; i > 0; i--) 
		{
			int j = std::rand() % (i + 1);
			this->cards.swapElements(i, j);
		}
		this->cards.goToStart();
	}
	Card draw() {
		if (this->cards.getSize() == 0) {
			throw std::runtime_error("Deck is empty.");
		}
		if (this->cards.getPos() == this->cards.getSize()) {
			throw std::runtime_error("Deck cursor is at end.");
		}
		return this->cards.remove();
	}
	int getSize() {
		return this->cards.getSize();
	}
};