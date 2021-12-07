#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <thread>
#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
class Game
{
public:
	Game();
	void start();
	void draw();
private:
	int lvl, x;
	Maze maze;
	std::vector<Enemy> enemys;
};

