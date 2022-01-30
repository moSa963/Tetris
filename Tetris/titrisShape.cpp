#pragma once 
#include "titrisShape.h"

TitrisShape::TitrisShape()
	:items(), id(Types::NONE)
{
}

std::vector<sf::RectangleShape>& TitrisShape::getItems()
{
	return items;
}

void TitrisShape::rotate(Direction direction)
{
	for (auto& shape : items)
	{
		shape.rotate(direction == Direction::RIGHT ? 90 : -90);
	}
}

void TitrisShape::move(Direction direction)
{
	for (auto& shape : items)
	{
		shiftPosition(shape, direction);
	}
}

TitrisShape::Types TitrisShape::getId()
{
	return id;
}

void TitrisShape::setPosition(sf::Vector2f position)
{
	for (auto& shape : items)
	{
		shape.setPosition(position);
	}
}

void TitrisShape::init(const sf::RectangleShape& root, Types type)
{
	id = type;
	sf::RectangleShape s1 = root;
	sf::RectangleShape s2;
	sf::RectangleShape s3;
	sf::RectangleShape s4;

	if (type == Types::O)
	{
		s2 = shiftOrigin(s1, Direction::UP);
		s3 = shiftOrigin(s1, Direction::LEFT);
		s4 = shiftOrigin(s3, Direction::UP);
	}
	else if (type == Types::I)
	{
		s2 = shiftOrigin(s1, Direction::UP);
		s3 = shiftOrigin(s1, Direction::DOWN);
		s4 = shiftOrigin(s3, Direction::DOWN);
	}
	else if (type == Types::T)
	{
		s2 = shiftOrigin(s1, Direction::RIGHT);
		s3 = shiftOrigin(s1, Direction::LEFT);
		s4 = shiftOrigin(s1, Direction::UP);
	}
	else if (type == Types::S)
	{
		s2 = shiftOrigin(s1, Direction::UP);
		s3 = shiftOrigin(s1, Direction::LEFT);
		s4 = shiftOrigin(s2, Direction::RIGHT);
	}
	else if (type == Types::Z)
	{
		s2 = shiftOrigin(s1, Direction::LEFT);
		s3 = shiftOrigin(s1, Direction::DOWN);
		s4 = shiftOrigin(s3, Direction::RIGHT);
	}
	else if (type == Types::L || type == Types::J)
	{
		s2 = shiftOrigin(s1, Direction::LEFT);
		s3 = shiftOrigin(s1, Direction::RIGHT);
		s4 = shiftOrigin(s3, type == Types::J ? Direction::UP : Direction::DOWN);
	}

	items.push_back(s1);
	items.push_back(s2);
	items.push_back(s3);
	items.push_back(s4);
}


sf::RectangleShape TitrisShape::shiftOrigin(const sf::RectangleShape& from, Direction direction)
{
	sf::RectangleShape newShap = from;
	sf::Vector2f origin = newShap.getOrigin();
	sf::Vector2f size = newShap.getSize();

	switch (direction)
	{
	case Direction::RIGHT: newShap.setOrigin(origin.x - size.x, origin.y);
		break;
	case Direction::DOWN: newShap.setOrigin(origin.x, origin.y - size.y);
		break;
	case Direction::LEFT: newShap.setOrigin(origin.x + size.x, origin.y);
		break;
	case Direction::UP: newShap.setOrigin(origin.x, origin.y + size.y);
		break;
	}

	return newShap;
}


void TitrisShape::shiftPosition(sf::RectangleShape& from, Direction direction)
{
	sf::Vector2f position = from.getPosition();
	sf::Vector2f size = from.getSize();

	switch (direction)
	{
	case Direction::LEFT: return from.setPosition(position.x - size.x, position.y);
	case Direction::DOWN: return from.setPosition(position.x, position.y + size.y);
	case Direction::UP: return from.setPosition(position.x, position.y - size.y);
	default: return from.setPosition(position.x + size.x, position.y);
	}
}