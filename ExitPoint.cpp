#include "ExitPoint.h"

ExitPoint::ExitPoint(FactoryState *state) : Cell(state) {

}

ExitPoint::~ExitPoint() {

}

bool ExitPoint::takeTick() {
	return false;
}

void ExitPoint::update(sf::Time elapsed) {

}

void ExitPoint::updateGraphics() {
	//sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}
