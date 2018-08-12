#pragma once

#include "Box.h"
#include "Directions.h"
#include <SFML/Graphics.hpp>

class FactoryState;

class Cell : public sf::Drawable {
public:
	Cell(FactoryState *state = nullptr);
	virtual ~Cell();

	virtual void preTick();
	virtual void processTick();
	virtual void takeTick();
	virtual void giveTick();
	virtual void update(sf::Time elapsed);

	virtual void setGridPosition(sf::Vector2i gridPosition);
	void setGridPosition(int x, int y);

	bool canReceiveFrom(int directions) const;

	virtual void drawBox(sf::RenderTarget &target) const;

	void destroy();
	bool shouldDie() const;

protected:
	FactoryState *factory;
	sf::Vector2i gridPosition;
	bool dying = false;

	Directions takeFrom;
	Directions canReceive;
	Directions giveTo;
public:
	Box *box = nullptr;
	Box *nextBox = nullptr;
};

