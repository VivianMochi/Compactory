#pragma once

#include "Box.h"
#include "Directions.h"
#include <SFML/Graphics.hpp>

class FactoryState;

class Cell : public sf::Drawable {
public:
	Cell(FactoryState *state = nullptr, bool useConnections = true);
	virtual ~Cell();

	virtual void preTick();
	virtual void processTick();
	// Returns true if a box is moved
	virtual bool takeTick();
	// Returns true if a box is moved
	virtual bool giveTick();
	virtual void update(sf::Time elapsed);

	void setGridPosition(sf::Vector2i gridPosition);
	void setGridPosition(int x, int y);
	virtual void updateGraphics();

	bool canReceiveFrom(int directions) const;

	virtual void drawBox(sf::RenderTarget &target) const;

	void destroy();
	bool shouldDie() const;

//private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	FactoryState *factory;
	sf::Vector2i gridPosition;
	bool dying = false;

	Directions takeFrom;
	Directions canReceive;
	Directions giveTo;
	Directions connections;
	bool useConnections;

	Box *box = nullptr;
	Box *nextBox = nullptr;

	bool filtered = false;
	sf::Color filter;
};

