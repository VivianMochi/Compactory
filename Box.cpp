#include "Box.h"

#include "FactoryState.h"

#include <iostream>

Box::Box(FactoryState *state, sf::Color color) : factory(state), color(color) {
	sprite.setTexture(factory->loadTexture("Resource/Image/Box.png"));
	sprite.setColor(color);
}

Box::~Box() {

}

void Box::update(sf::Time elapsed) {
	sprite.move((endPosition - sprite.getPosition()) * 10.f * elapsed.asSeconds());
}

void Box::slideTo(sf::Vector2f position) {
	endPosition = position;
}

void Box::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
	endPosition = position;
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
