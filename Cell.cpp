#include "Cell.h"

#include "FactoryState.h"

Cell::Cell(FactoryState *state) : factory(state), canReceive(all) {

}

Cell::~Cell() {
	if (box) {
		delete box;
	}
}

void Cell::preTick() {
	if (nextBox) {
		nextBox->slideTo(factory->gridToScreenPosition(gridPosition));
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
	if (box) {
		box->update(elapsed);
	}
}

void Cell::setGridPosition(sf::Vector2i gridPosition) {
	this->gridPosition = gridPosition;
}

void Cell::setGridPosition(int x, int y) {
	setGridPosition(sf::Vector2i(x, y));
}

bool Cell::canReceiveFrom(int directions) const {
	return !dying && !nextBox && canReceive.isEnabled(directions);
}

void Cell::drawBox(sf::RenderTarget &target) const {
	if (box) {
		target.draw(*box);
	}
}

void Cell::destroy() {
	dying = true;
}

bool Cell::shouldDie() const {
	return dying && !box && !nextBox;
}
