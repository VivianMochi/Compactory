#include "FactoryState.h"

#include "Conveyor.h"
#include "Directions.h"
#include "Box.h"

#include <iostream>

FactoryState::FactoryState() : gridWidth(6), gridHeight(6), cellWidth(16), cellHeight(12), tickPeriod(.5) {
	
}

FactoryState::~FactoryState() {
	for (Cell *cell : goodCells) {
		delete cell;
	}
}

void FactoryState::init() {
	cells.resize(gridWidth * gridHeight, nullptr);
	gridPositionOnScreen.x = 240 / 2 - gridWidth * cellWidth / 2;
	gridPositionOnScreen.y = 135 / 2 - gridHeight * cellHeight / 2;
}

void FactoryState::gotEvent(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q) {
			selection = conveyor;
		}
		/*else if (event.key.code == sf::Keyboard::W) {
			selection = bouncer;
		}*/
	}
}

void FactoryState::update(sf::Time elapsed) {
	tickCounter -= elapsed.asSeconds();
	if (tickCounter <= 0) {
		tick();
		tickCounter = tickPeriod;
		preTickDone = false;
	}
	else if (!preTickDone && tickCounter < tickPeriod / 2) {
		preTick();
		preTickDone = true;
	}

	int removed = 0;
	for (int i = 0; i < cells.size(); i++) {
		if (cells[i]) {
			cells[i]->update(elapsed);
			if (cells[i]->shouldDie()) {
				std::remove(goodCells.begin(), goodCells.end(), cells[i]);
				removed++;
				delete cells[i];
				cells[i] = nullptr;
			}
		}
	}
	if (removed) {
		goodCells.resize(goodCells.size() - removed);
	}

	sf::Vector2i selectedCell = screenToGridPosition(sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) / 4.f);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (selection == conveyor) {
			if (lastSelectedCell != selectedCell) {
				addCell(new Conveyor(this, vectorToDirection(selectedCell - lastSelectedCell)), lastSelectedCell);
			}
		}
		
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		deleteCell(selectedCell);
	}
	lastSelectedCell = selectedCell;
}

void FactoryState::render(sf::RenderWindow &window) {
	sf::RectangleShape cellBG;
	cellBG.setSize(sf::Vector2f(cellWidth - 2, cellHeight - 2));
	int cellIndex = 0;
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			cellBG.setPosition(gridToScreenPosition(x, y) + sf::Vector2f(1, 1));
			window.draw(cellBG);
			if (cells[cellIndex]) {
				window.draw(*cells[cellIndex]);
			}
			cellIndex++;
		}
	}
	for (Cell *cell : goodCells) {
		cell->drawBox(window);
	}
}

void FactoryState::addCell(Cell * cell, int x, int y) {
	// Place cell into cells vector
	if (validGridPosition(x, y)) {
		int cellIndex = y * gridWidth + x;
		if (!cells[cellIndex]) {
			cells[cellIndex] = cell;
			goodCells.push_back(cell);
			cell->setGridPosition(x, y);
		}
		else {
			// Cell was placed on another cell, delete it
			// Todo: make this place the new cell into a queue, and mark the overlapping cell for destruction
			delete cell;
		}
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
			cells[cellIndex]->destroy();
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
	if (gridPosition.x < 0) {
		gridPosition.x -= cellWidth;
	}
	gridPosition.x /= cellWidth;
	gridPosition.y = y - gridPositionOnScreen.y;
	if (gridPosition.y < 0) {
		gridPosition.y -= cellHeight;
	}
	gridPosition.y /= cellHeight;
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

void FactoryState::preTick() {
	for (Cell *cell : goodCells) {
		cell->preTick();
	}
}

void FactoryState::tick() {
	// Debug entrypoint
	if (cells[0] && cells[0]->canReceiveFrom(left)) {
		cells[0]->nextBox = new Box(this, sf::Color(216, 176, 127));
	}

	// Shuffle good cells to balance priority of box transfers
	std::random_shuffle(goodCells.begin(), goodCells.end());
	for (Cell *cell : goodCells) {
		cell->processTick();
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (Cell *cell : goodCells) {
			if (cell->takeTick()) {
				changed = true;
			}
		}
	}
	changed = true;
	while (changed) {
		changed = false;
		for (Cell *cell : goodCells) {
			if (cell->giveTick()) {
				changed = true;
			}
		}
	}
}

bool FactoryState::validGridPosition(int x, int y) {
	return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool FactoryState::validGridPosition(sf::Vector2i gridPosition) {
	return validGridPosition(gridPosition.x, gridPosition.y);
}
