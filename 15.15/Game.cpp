#include "Game.h"

Game::Game()
{
	font.loadFromFile("calibri.ttf");
	Init();
}

void Game::Init()
{
	for (int i = 0; i < ARRAY_SIZE - 1; i++)
		elements[i] = i + 1;

	emty_index = ARRAY_SIZE - 1;
	elements[emty_index] = 0;
	solved = true;
}

bool Game::Check()
{
	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
		if (elements[i] > 0 && elements[i] != i + 1)
			return false;

	return true;
}

void Game::Move(Direction direction)
{
	int col = emty_index % SIZE;
	int row = emty_index / SIZE;

	int move_index = -1;
	if (direction == Direction::left && col < SIZE - 1)
		move_index = emty_index + 1;
	if (direction == Direction::right && col > 0)
		move_index = emty_index - 1;
	if (direction == Direction::up && row < SIZE - 1)
		move_index = emty_index + SIZE;
	if (direction == Direction::down && row > 0)
		move_index = emty_index - SIZE;

	if (emty_index >= 0 && move_index >= 0)
	{
		int c = elements[emty_index];
		elements[emty_index] = elements[move_index];
		elements[move_index] = c;
		emty_index = move_index;
	}

	solved = Check();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// рисуем рамку игрового поля
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// подготавливаем рамку для отрисовки всех плашек
	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// отрисовка номеров плашек
	sf::Text text("", font, 52);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		
		if (solved)
		{
			shape.setOutlineColor(sf::Color::Yellow);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
			text.setFillColor(sf::Color::Green);

		// рисуем все плашки, кроме пустой
		if (elements[i] > 0)
		{
			// вычисление позиции плашки для отсортировки
			sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			
			// отрисовываем рамку плашки
			target.draw(shape, states);

			// отрисовываеи номер плашки
			target.draw(text, states);
		}
	}
}