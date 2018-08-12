#pragma once

#include "Cell.h"

class ExitPoint : public Cell {
public:
	ExitPoint(FactoryState *state = nullptr, int x = 0, int y = 0, Direction direction = none, sf::Color color = sf::Color(216, 176, 127));
	ExitPoint(FactoryState *state = nullptr, sf::Vector2i position = sf::Vector2i(), Direction direction = none, sf::Color color = sf::Color());
	~ExitPoint();

	// Inherited via Cell
	virtual void processTick() override;
	virtual bool takeTick() override;
	virtual void update(sf::Time elapsed) override;
	virtual void updateGraphics() override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
	sf::Color color;
};

