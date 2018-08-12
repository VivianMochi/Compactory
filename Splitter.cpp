#include "Splitter.h"

#include "FactoryState.h"

Splitter::Splitter(FactoryState *state, Direction direction) : Cell(state) {
	if (direction == none || direction == all) {
		direction = up;
	}
	giveTo.enable(direction | flipDirection(direction));

	sprite.setTexture(factory->loadTexture("Resource/Image/Splitter.png"));
	int spritesheetPosition = 0;
	if (direction == right || direction == left) {
		spritesheetPosition = 12;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 16, 12));
}

Splitter::~Splitter() {

}

void Splitter::updateGraphics() {
	Cell::updateGraphics();
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Splitter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Cell::draw(target, states);
	target.draw(sprite, states);
}
