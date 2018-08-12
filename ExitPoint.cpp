#include "ExitPoint.h"

#include "FactoryState.h"

ExitPoint::ExitPoint(FactoryState *state, int x, int y, Direction direction, sf::Color color) : Cell(state, false), consumeTime(3), color(color) {
	takeFrom.enable(direction);
	canReceive.disable(all);
	canReceive.enable(direction);
	filtered = true;
	filter = color;

	sprite.setTexture(factory->loadTexture("Resource/Image/Arrows.png"));
	Direction renderDirection = flipDirection(direction);
	spritesheetPosition = 0;
	if (renderDirection == right) {
		spritesheetPosition = 20;
	}
	else if (renderDirection == down) {
		spritesheetPosition = 40;
	}
	else if (renderDirection == left) {
		spritesheetPosition = 60;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 20, 20));
	sprite.setOrigin(sf::Vector2f(2, 4));
	sprite.setColor(color);

	setGridPosition(x, y);
}

ExitPoint::ExitPoint(FactoryState *state, sf::Vector2i position, Direction direction, sf::Color color) : ExitPoint(state, position.x, position.y, direction, color) {

}

ExitPoint::~ExitPoint() {

}

void ExitPoint::processTick() {
	Cell::processTick();
	if (stored > 0 && consuming > 0) {
		consuming--;
	}
	else if (stored > 0) {
		consuming = consumeTime;
		stored--;
	}

	if (stored >= 3) {
		// This is a fairly hacky solution, but temporarily change the color filter to stop accepting boxes
		filter = sf::Color();
	}
	else {
		filter = color;
	}

	if (box && nextBox == box) {
		delete box;
		box = nullptr;
		nextBox = nullptr;
		stored++;
		factory->score();
	}
}

void ExitPoint::update(sf::Time elapsed) {
	sprite.setTextureRect(sf::IntRect(stored * 20, spritesheetPosition, 20, 20));
}

void ExitPoint::updateGraphics() {
	sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}

void ExitPoint::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
