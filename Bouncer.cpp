#include "Bouncer.h"

#include "FactoryState.h"

Bouncer::Bouncer(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	this->direction = direction;

	sprite.setTexture(factory->loadTexture("Resource/Image/Bouncer.png"));
	int spritesheetPosition = 0;
	if (direction == right) {
		spritesheetPosition = 12;
	}
	else if (direction == down) {
		spritesheetPosition = 24;
	}
	else if (direction == left) {
		spritesheetPosition = 36;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 16, 12));
}

Bouncer::~Bouncer() {

}

bool Bouncer::giveTick() {
	if (box && nextBox == box) {
		Cell *otherCell = factory->getCellAtGridPosition(gridPosition + directionToVector(direction) * 2);
		if (otherCell && otherCell->canReceiveFrom(flipDirection(direction)) && (!otherCell->filtered || box->getColor() == otherCell->filter)) {
			otherCell->nextBox = box;
			nextBox = nullptr;
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

void Bouncer::updateGraphics() {
	Cell::updateGraphics();
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Bouncer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Cell::draw(target, states);
	target.draw(sprite, states);
}
