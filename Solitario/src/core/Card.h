#pragma once

#include <ostream>
#include <stdexcept>
#include <cstdlib>

class Card
{
private:
	int rank;
	bool faceUp;
public:
	static const int maxRank = 13;

	Card() {}
	Card(int rank, bool faceUp = true) {
		if (rank < 1 || rank > 13) {
			throw std::runtime_error("Carta invalida.");
		}
		this->rank = rank;
		this->faceUp = faceUp;
	}

	bool sameRank(const Card& other) const {
		return other.rank == this->rank;
	}
	bool isAdjacentRank(const Card& other) const {
		int diff = std::abs(this->rank - other.rank);
		return diff == 1 || diff == 12;
	}
	bool isBiggerAdjacentRank(const Card& other) const {
		int diff = other.rank - this->rank;
		return diff == 1;
	}
	bool isFaceUp() const {
		return this->faceUp;
	}
	void setFaceUp(bool v) {
		this->faceUp = v;
	}
	void flip() {
		this->faceUp = !this->faceUp;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Card& c) {
		if (!c.faceUp) {
			return os << "?";
		}
		switch (c.rank) {
		case 1:
			return os << "A";
		case 11:
			return os << "J";
		case 12:
			return os << "Q";
		case 13:
			return os << "K";
		default:
			return os << c.rank;
		}
	}
};

