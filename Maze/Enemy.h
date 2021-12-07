#pragma once
#include "Character.h"
class Enemy : public Character, public sf::Drawable
{
public:
	Enemy(int W,int H,int X,int Y);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void controls() override;
	float prevX, prevDx;
	float prevY, prevDy;
};

