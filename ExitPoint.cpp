#include "ExitPoint.h"

#include "FactoryState.h"

ExitPoint::ExitPoint(FactoryState *state, int x, int y, Direction direction, sf::Color color) : Cell(state, false), color(color) {
	takeFrom.enable(direction);
	canReceive.disable(all);
	canReceive.enable(direction);

	sprite.setTexture(factory->loadTexture("Resource/Image/Arrows.png"));
	Direction renderDirection = flipDirection(direction);
	int spriteOffset = 0;
	if (renderDirection == right) {
		spriteOffset = 20;
	}
	else if (renderDirection == down) {
		spriteOffset = 40;
	}
	else if (renderDirection == left) {
		spriteOffset = 60;
	}
	sprite.setTextureRect(sf::IntRect(0, spriteOffset, 20, 20));
	sprite.setOrigin(sf::Vector2f(2, 4));
	sprite.setColor(color);

	setGridPosition(x, y);
}

ExitPoint::~ExitPoint() {

}

void ExitPoint::processTick() {
	Cell::processTick();
	if (box && nextBox == box) {
		delete box;
		box = nullptr;
		nextBox = nullptr;
	}
}

void ExitPoint::update(sf::Time elapsed) {

}

void ExitPoint::updateGraphics() {
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void ExitPoint::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
