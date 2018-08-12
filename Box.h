#pragma once

#include <SFML/Graphics.hpp>

class FactoryState;

class Box : public sf::Drawable {
public:
	Box(FactoryState *state = nullptr, sf::Color color = sf::Color());
	~Box();

	void update(sf::Time elapsed);

	void slideTo(sf::Vector2f position);
	void setPosition(sf::Vector2f position);

	sf::Color getColor() const;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	FactoryState *factory;
	sf::Color color;

	sf::Sprite sprite;
	sf::Vector2f endPosition;
};

