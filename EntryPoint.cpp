#include "EntryPoint.h"

EntryPoint::EntryPoint(FactoryState *state) : Cell(state) {

}

EntryPoint::~EntryPoint() {

}

bool EntryPoint::giveTick() {
	return false;
}

void EntryPoint::update(sf::Time elapsed) {

}

void EntryPoint::updateGraphics() {
	//sprite.setPosition(factory->gridToScreenPosition(gridPosition));
}
