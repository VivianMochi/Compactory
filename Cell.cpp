#include "Cell.h"

#include "FactoryState.h"

Cell::Cell(FactoryState *state) : factory(state), canReceive(all) {

}

Cell::~Cell() {
	if (box) {
		delete box;
	}
}

void Cell::processTick() {
	box = nextBox;
	if (box) {
		box->setPosition(factory->gridToScreenPosition(gridPosition));
	}
}

void Cell::takeTick() {
	if (!box) {
		// Todo: take from random takeFrom direction
	}
}

void Cell::giveTick() {
	if (box) {
		for (Direction direction : giveTo.listEnabled()) {
			// Todo: randomly organize directions every time to balance load
			Cell *otherCell = factory->getCellAtGridPosition(gridPosition + directionToVector(direction));
			if (otherCell && otherCell->canReceiveFrom(flipDirection(direction))) {
				otherCell->nextBox = box;
				nextBox = nullptr;
				break;
			}
		}
	}
}

void Cell::update(sf::Time elapsed) {

}

void Cell::setGridPosition(sf::Vector2i gridPosition) {
	this->gridPosition = gridPosition;
}

void Cell::setGridPosition(int x, int y) {
	setGridPosition(sf::Vector2i(x, y));
}

bool Cell::canReceiveFrom(int directions) const {
	return !nextBox && canReceive.isEnabled(directions);
}

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (box) {
		target.draw(*box, states);
	}
}
