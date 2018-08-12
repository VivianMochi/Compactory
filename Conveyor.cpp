#include "Conveyor.h"

#include "FactoryState.h"

Conveyor::Conveyor(FactoryState *state, int direction) : Cell(state) {
	giveTo.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Conveyor.png"));
	int spriteOffset = 0;
	if (giveTo.isEnabled(right)) {
		spriteOffset = 12;
	}
	else if (giveTo.isEnabled(down)) {
		spriteOffset = 24;
	}
	else if (giveTo.isEnabled(left)) {
		spriteOffset = 36;
	}
	sprite.setTextureRect(sf::IntRect(0, spriteOffset, 16, 12));
}

Conveyor::~Conveyor() {

}

void Conveyor::setGridPosition(sf::Vector2i gridPosition) {
	Cell::setGridPosition(gridPosition);
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Conveyor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
