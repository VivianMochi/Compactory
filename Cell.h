#pragma once

#include "Box.h"
#include "Directions.h"
#include <SFML/Graphics.hpp>

class FactoryState;

class Cell : sf::Drawable {
public:
	Cell(FactoryState *state = nullptr);
	virtual ~Cell();

	virtual void tick();
	virtual void update(sf::Time elapsed);

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	FactoryState *factory;
	sf::Vector2i position;

	Directions takeFrom;
	Directions canReceive;
	Directions giveTo;
	Box *box;
};

