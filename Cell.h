#pragma once

#include "Box.h"
#include "Directions.h"
#include <SFML/Graphics.hpp>

class FactoryState;

class Cell : public sf::Drawable {
public:
	Cell(FactoryState *state = nullptr);
	virtual ~Cell();

	virtual void processTick();
	virtual void takeTick();
	virtual void giveTick();
	virtual void update(sf::Time elapsed);

	virtual void setGridPosition(sf::Vector2i gridPosition);
	void setGridPosition(int x, int y);

	bool canReceiveFrom(int directions) const;

protected:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	FactoryState *factory;
	sf::Vector2i gridPosition;

	Directions takeFrom;
	Directions canReceive;
	Directions giveTo;
public:
	Box *box;
	Box *nextBox;
};

