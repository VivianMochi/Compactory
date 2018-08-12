#pragma once

#include "State.h"
#include "Cell.h"
#include <SFML/Graphics.hpp>

class FactoryState : public State {
public:
	FactoryState();
	~FactoryState();

	// Inherited via State
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow & window) override;

	void addCell(Cell *cell, int x, int y);
	void addCell(Cell *cell, sf::Vector2i gridPosition);
	void deleteCell(int x, int y);
	void deleteCell(sf::Vector2i gridPosition);

	sf::Vector2f gridToScreenPosition(int x, int y);
	sf::Vector2f gridToScreenPosition(sf::Vector2i gridPosition);
	sf::Vector2i screenToGridPosition(int x, int y);
	sf::Vector2i screenToGridPosition(sf::Vector2f screenPosition);

	Cell *getCellAtGridPosition(int x, int y);
	Cell *getCellAtGridPosition(sf::Vector2i gridPosition);

private:
	void preTick();
	void tick();
	// A difficulty tick adds new entry and exit points to the factory, and potentially a new rule
	void difficultyTick();
	int difficulty = 0;
	int difficultyCountdown = 2;

	bool validGridPosition(int x, int y);
	bool validGridPosition(sf::Vector2i gridPosition);
	
	void updateSurroundingGraphics(int x, int y);
	void updateSurroundingGraphics(sf::Vector2i gridPosition);

	int gridWidth;
	int gridHeight;
	int cellWidth = 16;
	int cellHeight = 12;

	sf::Vector2f gridPositionOnScreen;
	std::vector<Cell*> cells;
	std::vector<Cell*> goodCells;
	std::vector<Cell*> borderCells;
	std::vector<std::pair<sf::Vector2i, Direction>> emptyBorderPositions;

	enum cellType {
		conveyor,
		splitter,
		bouncer
	};
	cellType selection = conveyor;
	sf::Vector2i lastSelectedCell;

	float tickCounter = 0;
	float tickPeriod;
	bool preTickDone = false;

	std::vector<sf::Color> availableColors;
	std::vector<sf::Color> entryColors;
	std::vector<sf::Color> exitColors;
};

