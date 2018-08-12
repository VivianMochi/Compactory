#include "FactoryState.h"

#include "Conveyor.h"
#include "Splitter.h"
#include "Directions.h"
#include "Box.h"
#include "EntryPoint.h"
#include "ExitPoint.h"

#include <iostream>

FactoryState::FactoryState() : gridWidth(6), gridHeight(6), tickPeriod(.5) {
	
}

FactoryState::~FactoryState() {
	for (Cell *cell : goodCells) {
		delete cell;
	}
	for (Cell *cell : borderCells) {
		delete cell;
	}
}

void FactoryState::init() {
	cells.resize(gridWidth * gridHeight, nullptr);
	gridPositionOnScreen.x = 240 / 2 - gridWidth * cellWidth / 2;
	gridPositionOnScreen.y = 135 / 2 - gridHeight * cellHeight / 2;

	availableColors.emplace_back(216, 176, 127); // Brown-yellow
	availableColors.emplace_back(101, 176, 127); // Green
	availableColors.emplace_back(84, 167, 183); // Light blue
	availableColors.emplace_back(151, 147, 151); // Gray
	availableColors.emplace_back(150, 76, 77); // Red
	availableColors.emplace_back(36, 68, 104); // Dark Blue

	// Add all border positons to a vector
	for (int x = 0; x < gridWidth; x++) {
		emptyBorderPositions.emplace_back(sf::Vector2i(x, -1), down);
		emptyBorderPositions.emplace_back(sf::Vector2i(x, gridHeight), up);
	}
	for (int y = 0; y < gridHeight; y++) {
		emptyBorderPositions.emplace_back(sf::Vector2i(-1, y), right);
		emptyBorderPositions.emplace_back(sf::Vector2i(gridWidth, y), left);
	}
	// Shuffle it to randomize what comes out
	std::random_shuffle(emptyBorderPositions.begin(), emptyBorderPositions.end());
}

void FactoryState::gotEvent(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q) {
			selection = conveyor;
		}
		else if (event.key.code == sf::Keyboard::W) {
			selection = splitter;
		}
		else if (event.key.code == sf::Keyboard::E) {
			selection = bouncer;
		}
		else if (event.key.code == sf::Keyboard::Z) {
			game->changeState(new FactoryState());
		}
	}
}

void FactoryState::update(sf::Time elapsed) {
	tickCounter -= elapsed.asSeconds();
	if (tickCounter <= 0) {
		tick();
		tickCounter = tickPeriod;
		preTickDone = false;

		difficultyCountdown--;
		if (difficultyCountdown <= 0) {
			difficultyTick();
			difficultyCountdown = 5 + difficulty * 5;
		}
	}
	else if (!preTickDone && tickCounter < tickPeriod * 4 / 5) {
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
				updateSurroundingGraphics(i % gridWidth, i / gridWidth);
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
		else if (selection == splitter) {
			if (lastSelectedCell != selectedCell) {
				addCell(new Splitter(this, vectorToDirection(selectedCell - lastSelectedCell)), lastSelectedCell);
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
	for (Cell *cell : borderCells) {
		window.draw(*cell);
		cell->drawBox(window);
	}
}

void FactoryState::addCell(Cell *cell, int x, int y) {
	// Place cell into cells vector
	if (validGridPosition(x, y)) {
		int cellIndex = y * gridWidth + x;
		if (!cells[cellIndex]) {
			cells[cellIndex] = cell;
			goodCells.push_back(cell);
			cell->setGridPosition(x, y);
			updateSurroundingGraphics(x, y);
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
		for (Cell *cell : borderCells) {
			if (cell->gridPosition == sf::Vector2i(x, y)) {
				return cell;
			}
		}
		return nullptr;
	}
}

Cell *FactoryState::getCellAtGridPosition(sf::Vector2i gridPosition) {
	return getCellAtGridPosition(gridPosition.x, gridPosition.y);
}

void FactoryState::preTick() {
	// Move all boxes towards their next cell
	for (Cell *cell : goodCells) {
		cell->preTick();
	}
	for (Cell *cell : borderCells) {
		cell->preTick();
	}
}

void FactoryState::tick() {
	// Shuffle cells to balance priority of box transfers
	std::random_shuffle(goodCells.begin(), goodCells.end());
	std::random_shuffle(borderCells.begin(), borderCells.end());

	// Allow all cells to process their contents
	for (Cell *cell : goodCells) {
		cell->processTick();
	}
	for (Cell *cell : borderCells) {
		cell->processTick();
	}

	// Allow any cells that take boxes to do so
	bool changed = true;
	while (changed) {
		changed = false;
		for (Cell *cell : goodCells) {
			if (cell->takeTick()) {
				changed = true;
			}
		}
		for (Cell *cell : borderCells) {
			if (cell->takeTick()) {
				changed = true;
			}
		}
	}

	// Allow cells that give boxes to do so
	changed = true;
	while (changed) {
		changed = false;
		for (Cell *cell : goodCells) {
			if (cell->giveTick()) {
				changed = true;
			}
		}
		for (Cell *cell : borderCells) {
			if (cell->giveTick()) {
				changed = true;
			}
		}
	}
}

void FactoryState::difficultyTick() {
	sf::Color entryColor;
	sf::Color exitColor;
	if (difficulty == 0) {
		entryColor = availableColors[0];
		exitColor = entryColor;
	}
	else {
		entryColor = availableColors[std::rand() % availableColors.size()];
		if (std::rand() % 3 == 0) {
			exitColor = availableColors[std::rand() % availableColors.size()];
			// Todo: add new rule to change colors from entry to exit
		}
		else {
			exitColor = entryColor;
		}
	}
	
	// Take the last position from the (shuffled) empty border position vector and place the entry there
	sf::Vector2i entryPosition = emptyBorderPositions.back().first;
	Direction entryDirection = emptyBorderPositions.back().second;
	emptyBorderPositions.pop_back();
	borderCells.push_back(new EntryPoint(this, entryPosition, entryDirection, entryColor));
	updateSurroundingGraphics(entryPosition);

	// Do the same for the exit
	sf::Vector2i exitPosition = emptyBorderPositions.back().first;
	Direction exitDirection = emptyBorderPositions.back().second;
	emptyBorderPositions.pop_back();
	borderCells.push_back(new ExitPoint(this, exitPosition, exitDirection, exitColor));
	updateSurroundingGraphics(exitPosition);

	difficulty++;
}

bool FactoryState::validGridPosition(int x, int y) {
	return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool FactoryState::validGridPosition(sf::Vector2i gridPosition) {
	return validGridPosition(gridPosition.x, gridPosition.y);
}

void FactoryState::updateSurroundingGraphics(int x, int y) {
	Cell *cellUp = getCellAtGridPosition(x, y - 1);
	Cell *cellRight = getCellAtGridPosition(x + 1, y);
	Cell *cellDown = getCellAtGridPosition(x, y + 1);
	Cell *cellLeft = getCellAtGridPosition(x - 1, y);
	if (cellUp) {
		cellUp->updateGraphics();
	}
	if (cellRight) {
		cellRight->updateGraphics();
	}
	if (cellDown) {
		cellDown->updateGraphics();
	}
	if (cellLeft) {
		cellLeft->updateGraphics();
	}
}

void FactoryState::updateSurroundingGraphics(sf::Vector2i gridPosition) {
	updateSurroundingGraphics(gridPosition.x, gridPosition.y);
}
