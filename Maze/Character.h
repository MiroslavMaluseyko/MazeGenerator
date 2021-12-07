#pragma once
#include <sfml\Graphics.hpp>

class Character
{
public:

	Character(float W, float H, int X, int Y);

	void update(float &tick, std::vector<sf::RectangleShape> w);
	bool inWall(std::vector<sf::RectangleShape>& w);
	sf::RectangleShape& getBox();
	void setPosition(int x, int y);
	void kill();
	void rise();
	void setX(int X);
	void setY(int Y);

protected:

	virtual void controls() = 0;
	float w, h, x, y;
	float Dx, Dy;
	float speed;
	sf::RectangleShape box;
	bool alive;
};

