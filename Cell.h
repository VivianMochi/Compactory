#pragma once

#include "Box.h"
#include "Directions.h"
#include <SFML/Graphics.hpp>

class FactoryState;

class Cell : public sf::Drawable {
public:
	Cell(FactoryState *state = nullptr, sf::Vector2i gridPosition = sf::Vector2i());
	virtual ~Cell();

	virtual void tick();
	virtual void update(sf::Time elapsed);

	virtual void setGridPosition(sf::Vector2i gridPosition);

protected:
	FactoryState *factory;
	sf::Vector2i gridPosition;

	Directions takeFrom;
	Directions canReceive;
	Directions giveTo;
	Box *box;
};

