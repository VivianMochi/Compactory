#include "Splitter.h"

#include "FactoryState.h"

Splitter::Splitter(FactoryState *state, Direction direction) : Cell(state) {
	giveTo.enable(direction | flipDirection(direction));

	sprite.setTexture(factory->loadTexture("Resource/Image/Splitter.png"));
	int spriteOffset = 0;
	if (direction == right || direction == left) {
		spriteOffset = 12;
	}
	sprite.setTextureRect(sf::IntRect(0, spriteOffset, 16, 12));
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
