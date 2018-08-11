#include "Cell.h"

#include "FactoryState.h"

Cell::Cell(FactoryState *state, sf::Vector2i gridPosition) : factory(state), gridPosition(gridPosition), canReceive(all) {

}

Cell::~Cell() {

}

void Cell::tick() {

}

void Cell::update(sf::Time elapsed) {

}

void Cell::setGridPosition(sf::Vector2i gridPosition) {
	this->gridPosition = gridPosition;
}

