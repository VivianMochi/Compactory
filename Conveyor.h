#pragma once

#include "Cell.h"

class Conveyor : public Cell {
public:
	Conveyor(FactoryState *state = nullptr, Direction direction = up);
	~Conveyor();

	// Inherited via Cell
	virtual void updateGraphics() override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

