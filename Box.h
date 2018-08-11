#pragma once

#include <SFML/Graphics.hpp>

class Box : sf::Drawable {
public:
	Box();
	~Box();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

