#pragma once 
#include "titrisBoard.h"

TitrisBoard::TitrisBoard(AppContext* context, sf::Vector2f position, sf::Vector2f size)
	: Drawable(context), size(sf::Vector2i(10, 22)), grid(), root(), squareSize(), settled()
{
	root.setPosition(position);
	root.setSize(size);
	createGrid();
}

void TitrisBoard::createGrid()
{
	squareSize = root.getSize().x / size.x;

	bool x = false;

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(squareSize, squareSize));
			rect.setFillColor(x ? sf::Color(50, 50, 50) : sf::Color(75, 75, 75));

			setPosition(rect, sf::Vector2i(i, j));

			grid.push_back(rect);
			x = !x;
		}
		x = !x;
	}
}

void TitrisBoard::draw()
{
	for (auto& i : grid)
	{
		context->getWindow().draw(i);
	}

	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			if (settled[y][x] != nullptr)
			{
				context->getWindow().draw(*settled[y][x]);
			}
		}
	}
}

sf::RectangleShape TitrisBoard::getCell(int x, int y)
{
	return grid[(size.x * y) + x];
}

sf::Vector2i TitrisBoard::getSize()
{
	return size;
}

const sf::Vector2i TitrisBoard::getIndex(const sf::Vector2f& point) const
{
	int x = (int)std::floor((point.x - root.getGlobalBounds().left) / squareSize);
	int y = (int)std::floor((point.y - root.getGlobalBounds().top) / squareSize);
	return sf::Vector2i(x, y);
}

const sf::Vector2i TitrisBoard::getIndex(const sf::RectangleShape& shape) const
{
	return getIndex(sf::Vector2f(shape.getGlobalBounds().left, shape.getGlobalBounds().top));
}

void TitrisBoard::push(TitrisShape& shape)
{
	for (auto& i : shape.getItems())
	{
		sf::Vector2i index = getIndex(i);
		
		if (index.x < 0 || index.y < 0) return;
		
		setPosition(i, index);
		settled[index.y][index.x].reset(new sf::RectangleShape(i));
	}
}

void TitrisBoard::setPosition(sf::RectangleShape& shape, sf::Vector2i index)
{
	shape.setOrigin(sf::Vector2f(squareSize / 2.0f, squareSize / 2.0f));
	shape.setPosition(sf::Vector2f((index.x * squareSize) + root.getGlobalBounds().left + (squareSize / 2.0f), (index.y * squareSize) + root.getGlobalBounds().top + (squareSize / 2.0f)));
}


bool TitrisBoard::isOccupied(int x, int y)
{
	return settled[y][x] != nullptr;
}


bool TitrisBoard::isOutOfBounds(int x, int y) const
{
	return x < 0 || y < 0 || x >= size.x || y >= size.y;
}

bool TitrisBoard::isOutOfBounds(const sf::Vector2i& index) const
{
	return isOutOfBounds(index.x, index.y);
}