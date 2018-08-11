#pragma once

#include "State.h"
#include "Cell.h"

class FactoryState : public State {
public:
	FactoryState();
	~FactoryState();

	// Inherited via State
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow & window) override;

private:
	int gridWidth;
	int gridHeight;
	int cellWidth;
	int cellHeight;

	sf::Vector2f gridPosition;
	std::vector<Cell*> cells;
};

