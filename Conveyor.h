#pragma once

#include "Cell.h"

class Conveyor : public Cell {
public:
	Conveyor(FactoryState *state = nullptr, int direction = 1);
	~Conveyor();

	// Inherited via Cell
	virtual void setGridPosition(sf::Vector2i gridPosition) override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

