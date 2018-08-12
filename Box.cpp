#include "Box.h"

#include "FactoryState.h"

#include <iostream>

Box::Box(FactoryState *state, sf::Color color) : factory(state), color(color) {
	sprite.setTexture(factory->loadTexture("Resource/Image/Box.png"));
	sprite.setColor(color);
}

Box::~Box() {

}

void Box::setPosition(sf::Vector2f screenPosition) {
	sprite.setPosition(screenPosition);
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
