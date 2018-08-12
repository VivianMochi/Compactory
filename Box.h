#pragma once

#include <SFML/Graphics.hpp>

class FactoryState;

class Box : public sf::Drawable {
public:
	Box(FactoryState *state = nullptr, sf::Color color = sf::Color());
	~Box();

	void setPosition(sf::Vector2f screenPosition);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	FactoryState *factory;
	sf::Color color;

	sf::Sprite sprite;
};

