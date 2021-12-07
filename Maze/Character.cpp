#include "Character.h"

Character::Character(float W, float H, int X, int Y)
{
	box.setSize({ W,H });
	box.setFillColor(sf::Color::White);
	box.setPosition(X, Y);
	w = W;
	h = H;
	x = X;
	y = Y;
	Dx = Dy = 0;
	alive = 1;
}

void Character::update(float &tick, std::vector<sf::RectangleShape> w)
{
	controls();
	if (!alive)return;
	x += Dx * tick;
	if (inWall(w))x -= Dx * tick;
	y += Dy * tick;
	if (inWall(w))y -= Dy * tick;

	box.setPosition({ (float)x,(float)y });

	Dx = Dy = 0;
}

bool Character::inWall(std::vector<sf::RectangleShape>& w)
{
	for (auto wall : w) {
		if (wall.getGlobalBounds().intersects(sf::FloatRect({ x,y }, box.getSize())))return 1;
	}
	return 0;
}


sf::RectangleShape& Character::getBox()
{
	return box;
}

void Character::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Character::kill()
{
	alive = 0;
	box.setFillColor(sf::Color::Red);
}

void Character::rise()
{
	alive = 1;
	box.setFillColor(sf::Color::White);
}

void Character::setX(int X)
{ 
	x = X;
}
void Character::setY(int Y)
{
	y = Y;
}
