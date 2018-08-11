#include "Cell.h"

#include "FactoryState.h"

Cell::Cell(FactoryState *state) : factory(state), canReceive(all) {

}

Cell::~Cell() {

}

void Cell::tick() {

}

void Cell::update(sf::Time elapsed) {

}

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

