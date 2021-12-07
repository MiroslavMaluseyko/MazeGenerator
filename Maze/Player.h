#pragma once
#include <sfml/Graphics.hpp>
#include "Character.h"
#include <vector>
#include <iostream>
#include "Enemy.h"
class Player:public Character, public sf::Drawable
{
public:
	Player(float W, float H, int X, int Y);
	bool Interection(std::vector<Enemy> &enemys);
	void update(float &tick, std::vector<sf::RectangleShape> w, std::vector<Enemy> &enemys);

private:
	void controls() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

