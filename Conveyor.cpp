#include "Conveyor.h"

#include "FactoryState.h"

Conveyor::Conveyor(FactoryState *state, int direction) : Cell(state) {
	giveTo.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Conveyor.png"));
	sprite.setTextureRect(sf::IntRect(0, (giveTo.isEnabled(up) || giveTo.isEnabled(down) ? 0 : 12), 16, 12));
}

Conveyor::~Conveyor() {

}

void Conveyor::setGridPosition(sf::Vector2i gridPosition) {
	Cell::setGridPosition(gridPosition);
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void Conveyor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
