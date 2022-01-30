#pragma once
#include "nextShapeView.h"

NextShapeView::NextShapeView(AppContext* context, sf::Vector2f position, sf::Vector2f size)
	: Drawable(context), root(), shape()
{
	background = context->getTexture("background_view");
	root.setPosition(position);
	root.setSize(size);
	root.setTexture(&background);
	root.setFillColor(sf::Color(120, 120, 120));
}

void NextShapeView::update(TitrisGenerator& generator)
{
	shape = generator.getQueue().front();
	shape.setPosition(sf::Vector2f(root.getPosition().x + root.getSize().x / 2, root.getPosition().y + root.getSize().y / 2));
}

void NextShapeView::draw()
{
	context->getWindow().draw(root);

	for (auto& j : shape.getItems())
	{
		context->getWindow().draw(j);
	}
}
