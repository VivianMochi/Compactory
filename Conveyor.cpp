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

void Conveyor::updateGraphics() {
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));

	// Find connections
	connections.disable(all);
	Cell *cellUp = factory->getCellAtGridPosition(gridPosition + directionToVector(up));
	Cell *cellRight = factory->getCellAtGridPosition(gridPosition + directionToVector(right));
	Cell *cellDown = factory->getCellAtGridPosition(gridPosition + directionToVector(down));
	Cell *cellLeft = factory->getCellAtGridPosition(gridPosition + directionToVector(left));
	if (cellUp && cellUp->giveTo.isEnabled(down)) {
		connections.enable(up);
	}
	if (cellRight && cellRight->giveTo.isEnabled(left)) {
		connections.enable(right);
	}
	if (cellDown && cellDown->giveTo.isEnabled(up)) {
		connections.enable(down);
	}
	if (cellLeft && cellLeft->giveTo.isEnabled(right)) {
		connections.enable(left);
	}
}

void Conveyor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Sprite connectingSprite;
	connectingSprite.setTexture(factory->loadTexture("Resource/Image/Connection.png"));
	connectingSprite.setPosition(factory->gridToScreenPosition(gridPosition));
	if (connections.isEnabled(up)) {
		connectingSprite.setTextureRect(sf::IntRect(0, 0, 16, 12));
		target.draw(connectingSprite);
	}
	if (connections.isEnabled(right)) {
		connectingSprite.setTextureRect(sf::IntRect(0, 12, 16, 12));
		target.draw(connectingSprite);
	}
	if (connections.isEnabled(down)) {
		connectingSprite.setTextureRect(sf::IntRect(0, 24, 16, 12));
		target.draw(connectingSprite);
	}
	if (connections.isEnabled(left)) {
		connectingSprite.setTextureRect(sf::IntRect(0, 36, 16, 12));
		target.draw(connectingSprite);
	}
	target.draw(sprite, states);
}
