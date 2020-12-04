
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "15");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	// текст с обозначением клавиш
	sf::Text text("F2 - new game / Ecs - exit / Arrow keys - move tile", font, 23);
	text.setFillColor(sf::Color::White);
	text.setPosition(5.f, 5.f);

	//создаём объект игры
	Game game;
	game.setPosition(50.f, 50.f);

	sf::Music music;
	music.openFromFile("from_Bass_with_love.ogg");
	music.play();

	sf::Event event;
	int move_counter = 0;	// Счетчик случайных ходов для перемешивания головоломки

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) game.Move(Direction::left);
				if (event.key.code == sf::Keyboard::Right) game.Move(Direction::right);
				if (event.key.code == sf::Keyboard::Up) game.Move(Direction::up);
				if (event.key.code == sf::Keyboard::Down) game.Move(Direction::down);
				// Новая игра
				if (event.key.code == sf::Keyboard::F2)
				{
					game.Init();
					move_counter = 400;
				}
			}
		}

		// Если счетчик ходов больше нуля, продолжаем перемешивать головоломку
		if (move_counter-- > 0) game.Move((Direction)(rand() % 4));

		// Выполняем необходимые действия по отрисовке
		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}

	return 0;
}
