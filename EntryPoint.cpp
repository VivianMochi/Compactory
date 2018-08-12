#include "EntryPoint.h"

EntryPoint::EntryPoint(FactoryState *state) : Cell(state) {

}

EntryPoint::~EntryPoint() {

}

void EntryPoint::giveTick() {

}

void EntryPoint::update(sf::Time elapsed) {

}

void EntryPoint::setGridPosition(sf::Vector2i gridPosition) {
	Cell::setGridPosition(gridPosition);
	//sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}
