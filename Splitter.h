#pragma once

#include "Cell.h"

class Splitter : public Cell {
public:
	Splitter(FactoryState *state = nullptr, Direction direction = up);
	~Splitter();

	// Inherited via Cell
	virtual void updateGraphics() override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

