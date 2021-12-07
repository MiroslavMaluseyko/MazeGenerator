#include "Player.h"
Player::Player(float W, float H, int X, int Y) :Character(W, H, X, Y)
{
	speed = 1;
}

bool Player::Interection(std::vector<Enemy>& enemys)
{
	for (auto& enemy : enemys) {
		if (box.getGlobalBounds().intersects(enemy.getBox().getGlobalBounds()))return 1;
	}
	return 0;
}

void Player::update(float& tick, std::vector<sf::RectangleShape> w, std::vector<Enemy>& enemys)
{
	Character::update(tick, w);
	if (Interection(enemys))kill();
}

	void Player::controls()
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))rise();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))Dy = speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))Dy = -speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))Dx = speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))Dx = -speed;

	}


	void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(box);
	}
