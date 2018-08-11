#pragma once

#include <SFML/Graphics.hpp>

enum {
	up = 1,
	right = 2,
	down = 4,
	left = 8,
	all = 15
};

class Directions {
public:
	Directions(int enabled = 0);
	~Directions();

	bool isEnabled(int directions);
	void enable(int directions);
	void disable(int directions);

private:
	int enabled;
};

