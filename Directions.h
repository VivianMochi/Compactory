#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
	none = 0,
	up = 1,
	right = 2,
	down = 4,
	left = 8,
	all = 15
};

sf::Vector2i directionToVector(Direction direction);
Direction vectorToDirection(sf::Vector2i vector);
Direction flipDirection(Direction input);

class Directions {
public:
	Directions(int enabled = 0);
	~Directions();

	int getEnabled() const;
	bool isEnabled(int directions) const;
	void enable(int directions);
	void disable(int directions);
	std::vector<Direction> listEnabled();

private:
	int enabled;
};

