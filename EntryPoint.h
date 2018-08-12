#pragma once

#include "Cell.h"

class EntryPoint : public Cell {
public:
	EntryPoint(FactoryState *state = nullptr, int x = 0, int y = 0, Direction direction = none, sf::Color color = sf::Color(216, 176, 127));
	~EntryPoint();

	// Inherited via Cell
	virtual void processTick() override;
	virtual void update(sf::Time elapsed) override;
	virtual void updateGraphics() override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
	sf::Color color;
};

