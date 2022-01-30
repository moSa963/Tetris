#pragma once
#include "titrisGenerator.h"
#include <time.h>
#include <cstdlib>

TitrisGenerator::TitrisGenerator(AppContext* context, TitrisBoard& board)
	:Drawable(context), next(), shapeTexture(), board(board)
{
	std::srand(time(NULL));
	shapeTexture = context->getTexture("item");

	root = board.getCell(board.getSize().x / 2, 0);
	root.setFillColor(sf::Color::White);
	root.setTexture(&shapeTexture);

	root.setFillColor(getRandomColor());
	current = randomShape();

	for (int i = 0; i < 3; ++i)
	{
		pushShape();
	}
}

void TitrisGenerator::draw()
{
	for (auto& i : current.getItems())
	{
		context->getWindow().draw(i);
	}
}

TitrisShape TitrisGenerator::randomShape()
{
	TitrisShape shape;
	shape.init(root, (TitrisShape::Types)(std::rand() % 7));
	return shape;
}

void TitrisGenerator::pushShape()
{
	root.setFillColor(getRandomColor());
	next.push(randomShape());
}

TitrisShape& TitrisGenerator::getCurrent()
{
	return current;
}

void TitrisGenerator::pop()
{
	current = next.front();
	next.pop();
	pushShape();
}

sf::Color TitrisGenerator::getRandomColor()
{
	int id = rand() % 5;
	if (id == 0) return sf::Color::Blue;
	if (id == 1) return sf::Color::Red;
	if (id == 2) return sf::Color::Green;
	if (id == 3) return sf::Color::Yellow;
	return sf::Color::Magenta;
}

std::queue<TitrisShape>& TitrisGenerator::getQueue()
{
	return next;
}