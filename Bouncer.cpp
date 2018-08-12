#include "Bouncer.h"

#include "FactoryState.h"

Bouncer::Bouncer(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	this->direction = direction;

	sprite.setTexture(factory->loadTexture("Resource/Image/Bouncer.png"));
	int spriteOffset = 0;
	if (direction == right) {
		spriteOffset = 12;
	}
	else if (direction == down) {
		spriteOffset = 24;
	}
	else if (direction == left) {
		spriteOffset = 36;
	}
	sprite.setTextureRect(sf::IntRect(0, spriteOffset, 16, 12));
}

Bouncer::~Bouncer() {

}

bool Bouncer::giveTick() {
	if (box && nextBox == box) {
		Cell *otherCell = factory->getCellAtGridPosition(gridPosition + directionToVector(direction) * 2);
		if (otherCell && otherCell->canReceiveFrom(flipDirection(direction))) {
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
