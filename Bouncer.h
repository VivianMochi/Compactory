#pragma once
#include "Cell.h"
class Bouncer : public Cell {
public:
	Bouncer(FactoryState *state = nullptr, Direction direction = up);
	~Bouncer();

	// Inherited via Cell
	virtual bool giveTick() override;
	virtual void updateGraphics() override;

private:
	// Inherited via Cell
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	Direction direction;
	sf::Sprite sprite;
};

