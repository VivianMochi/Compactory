#include "Directions.h"

sf::Vector2i directionToVector(Direction direction) {
	if (direction == up) {
		return sf::Vector2i(0, -1);
	}
	else if (direction == right) {
		return sf::Vector2i(1, 0);
	}
	else if (direction == down) {
		return sf::Vector2i(0, 1);
	}
	else if (direction == left) {
		return sf::Vector2i(-1, 0);
	}
	else {
		return sf::Vector2i();
	}
}

Direction flipDirection(Direction input) {
	if (input == up) {
		return down;
	}
	else if (input == right) {
		return left;
	}
	else if (input == down) {
		return up;
	}
	else if (input == left) {
		return right;
	}
	else {
		return none;
	}
}

Directions::Directions(int enabled) : enabled(enabled) {

}

Directions::~Directions() {

}

int Directions::getEnabled() const {
	return enabled;
}

bool Directions::isEnabled(int directions) const {
	return (directions & enabled) == directions;
}

void Directions::enable(int directions) {
	enabled = enabled | directions;
}

void Directions::disable(int directions) {
	enabled = enabled & !directions;
}

std::vector<Direction> Directions::listEnabled() {
	std::vector<Direction> list;
	if (isEnabled(up)) {
		list.push_back(up);
	}
	if (isEnabled(right)) {
		list.push_back(right);
	}
	if (isEnabled(down)) {
		list.push_back(down);
	}
	if (isEnabled(left)) {
		list.push_back(left);
	}
	return list;
}