#include "Game.h"

Game::Game()
{
	lvl = 1;
}

void Game::start()
{
	std::cout << "Input '1' for load saving or any key for new game.\n";
	std::cin >> x;
	if (x == 1) {
		std::ifstream fin;
		fin.open("save.txt");
		if (!fin.is_open())std::cout << "FUCK";
		int w, h;
		fin >> w >> h >> lvl;
		fin.close();
		maze.setMapW(w);
		maze.setMapH(h);
		for (int i = 0; i < lvl / 2; i++)
			enemys.push_back(Enemy(10, 10, rand() % (maze.getMapH() - 1) * 64 + 32 - 5, rand() % (maze.getMapW() - 1) * 64 + 32 - 5));
	}

	maze.genMaze();


	sf::RenderWindow window(sf::VideoMode(), "MAZE");
	window.create(sf::VideoMode(maze.getMapW() * 64, maze.getMapH() * 64), "MAZE");

	Player player(10, 10, maze.getStart().x + 32 - 5, maze.getStart().y + 32 - 5);

	sf::Clock clock;
	sf::Clock timer;
	while (window.isOpen())
	{

		if (timer.getElapsedTime().asMilliseconds() > 30) {
			timer.restart();
			float tick = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			tick = tick / 3000;

			if (maze.isSolved(player)) {
				maze.setMapW(std::min(maze.getMapW() + 1, 25));
				maze.setMapH(std::min(maze.getMapH() + 1, 14));
				maze.genMaze();
				player.setPosition(maze.getStart().x + 22, maze.getStart().y + 22);

				lvl++;
				if (!(lvl & 1))
					enemys.push_back(Enemy(10, 10, rand() % (maze.getMapH() - 1) * 64 + 32 - 5, rand() % (maze.getMapW() - 1) * 64 + 32 - 5));

				for (auto& enemy : enemys)
					enemy.setPosition((rand() % (maze.getMapH() - 1) * 64) + 22, (rand() % (maze.getMapW() - 1) * 64) + 22);
				window.create(sf::VideoMode(maze.getMapW() * 64, maze.getMapH() * 64), "MAZE");
				std::ofstream fout;
				fout.open("save.txt");
				if (!fout.is_open())std::cout << "FUCK!!!";
				fout << maze.getMapW() << ' ' << maze.getMapH() << ' ' << lvl << '\n';
				fout.close();
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			player.update(tick, maze.getWalls(), enemys);
			for (auto& enemy : enemys)
				enemy.update(tick, maze.getWalls());

			window.clear(sf::Color(127, 127, 127));
			window.draw(maze);
			window.draw(player);
			for (auto& enemy : enemys)
				window.draw(enemy);
			window.display();
		}
	}
}
