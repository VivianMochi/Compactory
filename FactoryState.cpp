#include "FactoryState.h"

#include "Conveyor.h"
#include "Directions.h"
#include "Box.h"

#include <iostream>

FactoryState::FactoryState() : gridWidth(6), gridHeight(6), cellWidth(16), cellHeight(12), tickPeriod(.5) {
	
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
	gridPositionOnScreen.x = 240 / 2 - gridWidth * cellWidth / 2;
	gridPositionOnScreen.y = 135 / 2 - gridHeight * cellHeight / 2;
}

void FactoryState::gotEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				/*sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) / 4.f;
				Cell *cell = getCellAtGridPosition(screenToGridPosition(mousePosition));
				if (cell && cell->canReceiveFrom(left)) {
					std::cout << "Placing box\n";
					cell->setBox(new Box(this));
				}*/
			}
		}
	}
}

void FactoryState::update(sf::Time elapsed) {
	tickCounter -= elapsed.asSeconds();
	if (tickCounter <= 0) {
		tickCounter = tickPeriod;
		
		if (cells[0] && cells[0]->canReceiveFrom(left)) {
			cells[0]->nextBox = new Box(this, sf::Color(216, 176, 127));
		}

		// Todo: place "good" cells into their own vector. randomize order of vector to balance priority of give / take operations
		for (Cell *cell : cells) {
			if (cell) {
				cell->processTick();
			}
		}
		for (Cell *cell : cells) {
			if (cell) {
				cell->takeTick();
			}
		}
		for (Cell *cell : cells) {
			if (cell) {
				cell->giveTick();
			}
		}
	}

	for (Cell *cell : cells) {
		if (cell) {
			cell->update(elapsed);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) / 4.f;
		addCell(new Conveyor(this, right), screenToGridPosition(mousePosition));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) / 4.f;
		deleteCell(screenToGridPosition(mousePosition));
	}
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

void FactoryState::addCell(Cell * cell, int x, int y) {
	// Place cell into cells vector, deleting any existing cell
	if (validGridPosition(x, y)) {
		int cellIndex = y * gridWidth + x;
		if (cells[cellIndex]) {
			delete cells[cellIndex];
		}
		cells[cellIndex] = cell;

		// Do other setup
		cell->setGridPosition(x, y);
	}
	else {
		// Cell was placed outside grid, delete it
		delete cell;
	}
}

void FactoryState::addCell(Cell *cell, sf::Vector2i gridPosition) {
	addCell(cell, gridPosition.x, gridPosition.y);
}

void FactoryState::deleteCell(int x, int y) {
	if (validGridPosition(x, y)) {
		int cellIndex = y * gridWidth + x;
		if (cells[cellIndex]) {
			delete cells[cellIndex];
			cells[cellIndex] = nullptr;
		}
	}
}

void FactoryState::deleteCell(sf::Vector2i gridPosition) {
	deleteCell(gridPosition.x, gridPosition.y);
}

sf::Vector2f FactoryState::gridToScreenPosition(int x, int y) {
	return gridPositionOnScreen + sf::Vector2f(x * cellWidth, y * cellHeight);
}

sf::Vector2f FactoryState::gridToScreenPosition(sf::Vector2i gridPosition) {
	return gridToScreenPosition(gridPosition.x, gridPosition.y);
}

sf::Vector2i FactoryState::screenToGridPosition(int x, int y) {
	sf::Vector2i gridPosition;
	gridPosition.x = x - gridPositionOnScreen.x;
	if (gridPosition.x > 0) {
		gridPosition.x /= cellWidth;
	}
	gridPosition.y = y - gridPositionOnScreen.y;
	if (gridPosition.y > 0) {
		gridPosition.y /= cellHeight;
	}
	return gridPosition;
}

sf::Vector2i FactoryState::screenToGridPosition(sf::Vector2f screenPosition) {
	return screenToGridPosition(screenPosition.x, screenPosition.y);
}

Cell *FactoryState::getCellAtGridPosition(int x, int y) {
	if (validGridPosition(x, y)) {
		return cells[y * gridWidth + x];
	}
	else {
		return nullptr;
	}
}

Cell *FactoryState::getCellAtGridPosition(sf::Vector2i gridPosition) {
	return getCellAtGridPosition(gridPosition.x, gridPosition.y);
}

bool FactoryState::validGridPosition(int x, int y) {
	return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool FactoryState::validGridPosition(sf::Vector2i gridPosition) {
	return validGridPosition(gridPosition.x, gridPosition.y);
}
