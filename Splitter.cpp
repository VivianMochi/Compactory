#include "Splitter.h"

#include "FactoryState.h"

Splitter::Splitter(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	giveTo.enable(direction | flipDirection(direction));
	next = direction;

	sprite.setTexture(factory->loadTexture("Resource/Image/Splitter.png"));
	int spritesheetPosition = 0;
	if (next == right) {
		spritesheetPosition = 12;
	}
	else if (next == down) {
		spritesheetPosition = 24;
	}
	else if (next == left) {
		spritesheetPosition = 36;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 16, 12));
}

Splitter::~Splitter() {

}

void Splitter::updateGraphics() {
	Cell::updateGraphics();
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Splitter::preTick() {
	Cell::preTick();
	int spritesheetPosition = 0;
	if (next == right) {
		spritesheetPosition = 12;
	}
	else if (next == down) {
		spritesheetPosition = 24;
	}
	else if (next == left) {
		spritesheetPosition = 36;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 16, 12));
}

bool Splitter::giveTick() {
	if (box && nextBox == box) {
		Cell *otherCell = factory->getCellAtGridPosition(gridPosition + directionToVector(next));
		if (otherCell && otherCell->canReceiveFrom(flipDirection(next)) && (!otherCell->filtered || box->getColor() == otherCell->filter)) {
			otherCell->nextBox = box;
			nextBox = nullptr;
			next = flipDirection(next);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Splitter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Cell::draw(target, states);
	target.draw(sprite, states);
}
