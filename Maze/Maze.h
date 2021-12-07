#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Player.h"

class Maze: public sf::Drawable
{
public:
	Maze();
	Maze(int W, int H);
	void genMaze();
	void setMapW(int W);
	void setMapH(int H);
	int getMapW();
	int getMapH();
	bool isSolved(Player &p);

	sf::Vector2f getStart();
	sf::Vector2f getExit();
	std::vector<sf::RectangleShape> getWalls();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::pair<int, int> getNabour(std::pair<int,int> cell);
	void findExit(int x,int y,int dist);
	void findStart();
	void genBFS();
	void genKruskle();

	int startX, startY, MAP_W, MAP_H, endX, endY, maxDist, tileH, tileW;
	std::vector <std::vector<Cell >> maze;
	std::vector<sf::RectangleShape> walls;
	sf::CircleShape start;
	sf::CircleShape end;
};

