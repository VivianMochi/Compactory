#include "Conveyor.h"

#include "FactoryState.h"

Conveyor::Conveyor(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	giveTo.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Conveyor.png"));
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

Conveyor::~Conveyor() {

}

void Conveyor::updateGraphics() {
	Cell::updateGraphics();
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Conveyor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Cell::draw(target, states);
	target.draw(sprite, states);
}
