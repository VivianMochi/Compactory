#pragma once

#include "Cell.h"

class EntryPoint : public Cell {
public:
	EntryPoint(FactoryState *state = nullptr, int x = 0, int y = 0, Direction direction = none, sf::Color color = sf::Color());
	EntryPoint(FactoryState *state = nullptr, sf::Vector2i position = sf::Vector2i(), Direction direction = none, sf::Color color = sf::Color());
	~EntryPoint();

	// Inherited via Cell
	virtual void processTick() override;
	virtual bool giveTick() override;
	virtual void update(sf::Time elapsed) override;
	virtual void updateGraphics() override;

	void speedUp();

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Sprite sprite;
	int spritesheetPosition;

	int period;
	int countdown;
	int stored;
};

