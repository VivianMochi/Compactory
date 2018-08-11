#include "FactoryState.h"

#include "Conveyor.h"

#include <iostream>

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

	addCell(new Conveyor(this, right), sf::Vector2i(1, 0));
	addCell(new Conveyor(this, down), sf::Vector2i(2, 0));
	addCell(new Conveyor(this, down), sf::Vector2i(2, 1));
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
			cellBG.setPosition(gridToScreenPosition(x, y) + sf::Vector2f(1, 1));
			window.draw(cellBG);
			if (cells[cellIndex]) {
				window.draw(*cells[cellIndex]);
			}
			cellIndex++;
		}
	}
}

void FactoryState::addCell(Cell *cell, sf::Vector2i position) {
	// Place cell into cells vector, deleting any existing cell
	if (position.x >= 0 && position.x < gridWidth && position.y >= 0 && position.y < gridHeight) {
		int cellIndex = position.y * gridWidth + position.x;
		if (cells[cellIndex]) {
			delete cells[cellIndex];
		}
		cells[cellIndex] = cell;

		// Do other setup
		cell->setGridPosition(position);
	}
	else {
		// Cell was placed outside grid, delete it
		delete cell;
	}
}

sf::Vector2f FactoryState::gridToScreenPosition(int x, int y) {
	return gridPosition + sf::Vector2f(x * cellWidth, y * cellHeight);
}

sf::Vector2f FactoryState::gridToScreenPosition(sf::Vector2i gridPosition) {
	return gridToScreenPosition(gridPosition.x, gridPosition.y);
}

sf::Vector2i FactoryState::screenToGridPosition(int x, int y) {
	return sf::Vector2i();
}

sf::Vector2i FactoryState::screenToGridPosition(sf::Vector2f screenPosition) {
	return sf::Vector2i();
}
