#include "Maze.h"
#include <stack>
#include <iostream>

Maze::Maze():Maze(1,2){
}

Maze::Maze(int H, int W)
{
	this->MAP_W = W;
	this->MAP_H = H;

	start.setRadius(32);
	start.setFillColor(sf::Color::Red);
	end.setRadius(32);
	end.setFillColor(sf::Color::Blue);
}

void Maze::genKruskle() {

}

void Maze::genBFS() {
	std::stack < std::pair<int, int >> q;
	q.push({ startX,startY });
	while (!q.empty()) {
		std::pair <int, int> cell = q.top();
		maze[cell.first][cell.second].data |= 1;
		std::pair<int, int> nabour = getNabour(cell);
		if (nabour == cell) {
			q.pop();
			continue;
		}
		q.push(nabour);
	}
}

void Maze::genMaze()
{
	int i = 0,j = 0;
	maze.clear();
	maze.resize(MAP_H);
	for (int i = 0; i < MAP_H; i++)maze[i].resize(MAP_W);
	for (auto& mazeL : maze) {
		j = 0;
		for (auto& cell : mazeL) {
			cell.data = 30;//01111
			cell.x = j * 64;
			cell.y = i * 64;
			j++;
		}i++;
	}

	findStart();

	genBFS();
	findExit( startX, startY , 0);
	
	walls.clear();
	float wallTall = 5;
	for(auto& mazeL:maze)
		for (auto& cell : mazeL) {


			if (cell.data & 2) {
				walls.push_back(sf::RectangleShape({64,wallTall}));
				walls[walls.size() - 1].setPosition({ (float)cell.x,(float)cell.y});
				walls[walls.size() - 1].setFillColor(sf::Color::Black);
							}
			if (cell.data & 4) {
				walls.push_back(sf::RectangleShape({ 64,wallTall }));
				walls[walls.size() - 1].setPosition({ (float)cell.x,(float)cell.y + 64 - wallTall});
				walls[walls.size() - 1].setFillColor(sf::Color::Black);
			}
			if (cell.data & 8) {
				walls.push_back(sf::RectangleShape({ wallTall,64 }));
				walls[walls.size() - 1].setPosition({ (float)cell.x,(float)cell.y});
				walls[walls.size() - 1].setFillColor(sf::Color::Black);
			}
			if (cell.data & 16) {
				walls.push_back(sf::RectangleShape({ wallTall,64 }));
				walls[walls.size() - 1].setPosition({ (float)cell.x + 64 - wallTall,(float)cell.y});
				walls[walls.size() - 1].setFillColor(sf::Color::Black);
			}
		}
}

void Maze::setMapW(int W)
{
	this->MAP_W = W;
}

void Maze::setMapH(int H)
{
	this->MAP_H = H;
}

int Maze::getMapW()
{
	return MAP_W;
}

int Maze::getMapH()
{
	return MAP_H;
}

bool Maze::isSolved(Player &p)
{
	sf::CircleShape ex;
	ex.setPosition(getExit());
	ex.setRadius(32);
	if (p.getBox().getGlobalBounds().intersects(ex.getGlobalBounds()))return 1;
	return 0;
}

sf::Vector2f Maze::getStart()
{
	return start.getPosition();
}

sf::Vector2f Maze::getExit()
{
	return end.getPosition();
}

std::vector<sf::RectangleShape> Maze::getWalls()
{
	return walls;
}

void Maze::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(start);
	target.draw(end);
	for (auto& wall : walls)target.draw(wall);

}

std::pair<int, int> Maze::getNabour(std::pair<int, int> cell)
{
	int  x = cell.first;
	int y = cell.second;
	std::vector <std::pair<std::pair<int, int>, int>>l;
	if (x + 1 < MAP_H  && !(maze[x + 1][y].data & 1))l.push_back({ { x + 1,y },1 });
	if (x > 0 && !(maze[x - 1][y].data & 1))	l.push_back({ { x - 1,y },2 });
	if (y + 1 < MAP_W  && !(maze[x][y + 1].data & 1))	l.push_back({ { x,y + 1},3 });
	if (y > 0 && !(maze[x][y - 1].data & 1))	l.push_back({ { x,y - 1},4 });

	if (l.empty())return cell;

	std::pair<std::pair<int, int>, int> naub = l[rand() % l.size()];
	///Uudlr
	switch (naub.second) {
	case 1:
		maze[x][y].data &= 27;// 11011
		maze[x + 1][y].data &= 29; //10111
		break;
	case 2:
		maze[x][y].data &= 29;//10111
		maze[x - 1][y].data &= 27;//11011
		break;
	case 3:
		maze[x][y].data &= 15;//11110
		maze[x][y + 1].data &= 23;//11101
		break;
	case 4:
		maze[x][y].data &= 23;//11101
		maze[x][y - 1].data &= 15;//11110
		break;
	default:
		break;
	}

	return { naub.first.first, naub.first.second };
	
}

void Maze::findExit(int x, int y, int dist)
{

	if (!dist) {

		for (auto& mazeL : maze)
			for (auto& cell : mazeL)
				cell.data &= 30;//01111
		this->maxDist = 0;
	}
	maze[x][y].data |= 1;

	if (dist > maxDist) {
		this->maxDist = dist;
		this->endX = x;
		this->endY = y;
	}

	if (x < MAP_H && !(maze[x][y].data & 4) && !(maze[x + 1][y].data & 1))findExit(x + 1, y, dist + 1);
	if (x > 0 && !(maze[x][y].data & 2) && !(maze[x - 1][y].data & 1))findExit(x - 1, y, dist + 1);
	if (y < MAP_W && !(maze[x][y].data & 16) && !(maze[x][y + 1].data & 1))findExit(x, y + 1, dist + 1);
	if (y > 0 && !(maze[x][y].data & 8) && !(maze[x][y - 1].data & 1))findExit(x, y - 1, dist + 1);

	end.setPosition({ (float)endY * 64,(float)endX * 64 });
}

void Maze::findStart()
{
	this->startX = (rand() % MAP_H);
	this->startY = (rand() % MAP_W);
	start.setPosition({ (float)startY * 64,(float)startX * 64 });
}
