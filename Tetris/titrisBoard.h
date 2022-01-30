#pragma once 
#include <vector>
#include "SFML/Graphics.hpp"
#include "appContext.h"
#include "titrisShape.h"
#include <iostream>
#include "animation.h"

class TitrisBoard : public Drawable<AppContext>
{
private:
	std::vector<sf::RectangleShape> grid;
	sf::RectangleShape root;
	float squareSize;
	const sf::Vector2i size;

private:
	void createGrid();

public:
	std::shared_ptr<sf::RectangleShape> settled[22][10];

	TitrisBoard(AppContext* context, sf::Vector2f position, sf::Vector2f size);

	void draw() override;

	sf::RectangleShape getCell(int x, int y);

	sf::Vector2i getSize();

	const sf::Vector2i getIndex(const sf::Vector2f& point) const;
	const sf::Vector2i getIndex(const sf::RectangleShape& shape) const;


	//add a shape to the settled shapes array
	void push(TitrisShape& shape);

	bool isOccupied(int x, int y);

	bool isOutOfBounds(int x, int y) const;

	bool isOutOfBounds(const sf::Vector2i& index) const;

	void setPosition(sf::RectangleShape& shape, sf::Vector2i index);
};