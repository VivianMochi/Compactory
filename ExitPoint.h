#pragma once

#include "Cell.h"

class ExitPoint : public Cell {
public:
	ExitPoint(FactoryState *state = nullptr);
	~ExitPoint();

	// Inherited via Cell
	virtual bool takeTick() override;
	virtual void update(sf::Time elapsed) override;
	virtual void setGridPosition(sf::Vector2i gridPosition) override;
};

