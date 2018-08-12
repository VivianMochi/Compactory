#pragma once

#include "Cell.h"

class EntryPoint : public Cell {
public:
	EntryPoint(FactoryState *state = nullptr);
	~EntryPoint();

	// Inherited via Cell
	virtual bool giveTick() override;
	virtual void update(sf::Time elapsed) override;
	virtual void updateGraphics() override;
};

