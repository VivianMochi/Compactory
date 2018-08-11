#include "FactoryState.h"

FactoryState::FactoryState() : gridWidth(6), gridHeight(6), cellWidth(16), cellHeight(12), gridPosition(30, 30) {
	
}

FactoryState::~FactoryState() {
	for (Cell *cell : cells) {
		if (cell) {
			delete cell;
		}
	}
}

void FactoryState::init() {
	cells.resize(gridWidth * gridHeight, nullptr);
	gridPosition.x = 240 / 2 - gridWidth * cellWidth / 2;
	gridPosition.y = 135 / 2 - gridHeight * cellHeight / 2;
}

void FactoryState::gotEvent(sf::Event event) {

}

void FactoryState::update(sf::Time elapsed) {

}

void FactoryState::render(sf::RenderWindow &window) {
	sf::RectangleShape cellBG;
	cellBG.setSize(sf::Vector2f(cellWidth - 2, cellHeight - 2));
	size_t cellIndex = 0;
	for (size_t y = 0; y < gridHeight; y++) {
		for (size_t x = 0; x < gridWidth; x++) {
			cellBG.setPosition(gridPosition + sf::Vector2f(x * cellWidth + 1, y * cellHeight + 1));
			window.draw(cellBG);
			cellIndex++;
		}
	}
}
