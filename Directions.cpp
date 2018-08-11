#include "Directions.h"

Directions::Directions(int enabled) : enabled(enabled) {

}

Directions::~Directions() {

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
