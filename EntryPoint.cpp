#include "EntryPoint.h"

#include "FactoryState.h"

EntryPoint::EntryPoint(FactoryState *state, int x, int y, Direction direction, sf::Color color) : Cell(state, false), color(color), period(4), countdown(period) {
	giveTo.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Arrows.png"));
	int spriteOffset = 0;
	if (direction == right) {
		spriteOffset = 20;
	}
	else if (direction == down) {
		spriteOffset = 40;
	}
	else if (direction == left) {
		spriteOffset = 60;
	}
	sprite.setTextureRect(sf::IntRect(0, spriteOffset, 20, 20));
	sprite.setOrigin(sf::Vector2f(2, 4));
	sprite.setColor(color);

	setGridPosition(x, y);
}

EntryPoint::EntryPoint(FactoryState *state, sf::Vector2i position, Direction direction, sf::Color color) : EntryPoint(state, position.x, position.y, direction, color) {

}

EntryPoint::~EntryPoint() {

}

void EntryPoint::processTick() {
	Cell::processTick();
	countdown--;
	if (countdown <= 0) {
		countdown = period;
		if (!box && !nextBox) {
			box = new Box(factory, color);
			nextBox = box;
			box->setPosition(factory->gridToScreenPosition(gridPosition));
		}
	}
}

void EntryPoint::update(sf::Time elapsed) {

}

void EntryPoint::updateGraphics() {
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void EntryPoint::speedUp() {
	period /= 2;
}

void EntryPoint::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
