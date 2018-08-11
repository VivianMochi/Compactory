#pragma once

#include "State.h"

class FactoryState : public State {
public:
	FactoryState();
	~FactoryState();

	// Inherited via State
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow & window) override;
};

