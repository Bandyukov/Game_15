#pragma once
#include <SFML/Graphics.hpp>

const int SIZE = 4; // размер поля в плашках
const int ARRAY_SIZE = SIZE * SIZE; // размер массива
const int FIELD_SIZE = 500; // размер игрового поля в пикселях
const int CELL_SIZE = 120; // размер плашки в пикселях

enum class Direction { left = 0, right = 1, up = 2, down = 3};

class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int elements[ARRAY_SIZE];
	int emty_index;
	bool solved;
	sf::Font font;

public:
	Game();
	void Init();
	bool Check();
	void Move(Direction direction);

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


