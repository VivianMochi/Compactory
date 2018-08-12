#include "EntryPoint.h"

#include "FactoryState.h"

EntryPoint::EntryPoint(FactoryState *state, int x, int y, Direction direction, sf::Color color) : Cell(state, false), period(4), countdown(period) {
	giveTo.enable(direction);
	canReceive.disable(all);
	filter = color;

	sprite.setTexture(factory->loadTexture("Resource/Image/Arrows.png"));
	spritesheetPosition = 0;
	if (direction == right) {
		spritesheetPosition = 20;
	}
	else if (direction == down) {
		spritesheetPosition = 40;
	}
	else if (direction == left) {
		spritesheetPosition = 60;
	}
	sprite.setTextureRect(sf::IntRect(0, spritesheetPosition, 20, 20));
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
		stored++;
		sprite.setTextureRect(sf::IntRect(stored * 20, spritesheetPosition, 20, 20));
	}
	if (stored > 0 && !box && !nextBox) {
		box = new Box(factory, filter);
		nextBox = box;
		box->setPosition(factory->gridToScreenPosition(gridPosition));
	}
	else if (stored > 3) {
		factory->lose();
	}
}

bool EntryPoint::giveTick() {
	if (Cell::giveTick()) {
		stored--;
		sprite.setTextureRect(sf::IntRect(stored * 20, spritesheetPosition, 20, 20));
		return true;
	}
	else {
		return false;
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
