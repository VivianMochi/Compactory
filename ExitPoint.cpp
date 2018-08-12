#include "ExitPoint.h"

ExitPoint::ExitPoint(FactoryState *state) : Cell(state) {

}

ExitPoint::~ExitPoint() {

}

void ExitPoint::takeTick() {

}

void ExitPoint::update(sf::Time elapsed) {

}

void ExitPoint::setGridPosition(sf::Vector2i gridPosition) {
	Cell::setGridPosition(gridPosition);
	//sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}
