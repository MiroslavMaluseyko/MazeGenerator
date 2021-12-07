#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int W, int H, int X, int Y):Character(W,H,X,Y)
{
	speed = 0.5;
	prevX = prevY = -1;
	prevDx = speed;
	prevDy = speed;
	box.setFillColor(sf::Color::Green);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box);
}

void Enemy::controls()
{
	Dx = prevDx;
	Dy = prevDy;
	if (prevX == x)Dx *= -1;
	if (prevY == y)Dy *= -1;
	prevX = x;
	prevY = y;
	prevDx = Dx;
	prevDy = Dy;

}
