#include "Conveyor.h"

#include "FactoryState.h"

Conveyor::Conveyor(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	giveTo.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Conveyor.png"));
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
