#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "direction.h"

class TitrisShape
{
public:
	enum class Types
	{
		I, O, S, Z, J, L, T, NONE
	};

private:
	std::vector<sf::RectangleShape> items;
	Types id;

	static sf::RectangleShape shiftOrigin(const sf::RectangleShape& from, Direction direction);

public:
	TitrisShape();

	void init(const sf::RectangleShape& root, Types type);

	void rotate(Direction direction);

	void move(Direction direction);

	void setPosition(sf::Vector2f position);

	Types getId();

	static void shiftPosition(sf::RectangleShape& from, Direction direction);

	std::vector<sf::RectangleShape>& getItems();
};