#pragma once
#include"drawable.h"
#include "appContext.h"
#include "titrisShape.h"
#include <queue>
#include "titrisGenerator.h"


class ScoreView : public Drawable<AppContext>
{
private:
	sf::RectangleShape root;
	sf::Texture background;
	sf::Text score;
	sf::Text title;
	sf::Font font;

public:
	ScoreView(AppContext* context, sf::Vector2f position, sf::Vector2f size)
		: Drawable(context), root(), background(), font(), score("0", font, 40), title("Score:", font, 30)
	{
		font = context->getFont("timesbd");
		background = context->getTexture("background_view");
		root.setPosition(position);
		root.setSize(size);
		root.setTexture(&background);
		root.setFillColor(sf::Color(120, 120, 120));

		score.setFillColor(sf::Color::Black);
		title.setFillColor(sf::Color::White);

		title.setPosition(sf::Vector2f(root.getPosition().x,
			root.getPosition().y - (root.getSize().y - score.getLocalBounds().height) / 2.0f));

		setTextPosition();
	}

	void setTextPosition()
	{
		score.setPosition(sf::Vector2f(root.getPosition().x + (root.getSize().x - score.getLocalBounds().width) / 2.0f,
			root.getPosition().y + (root.getSize().y - score.getLocalBounds().height) / 2.0f));
	}

	void setScore(int num)
	{
		score.setString(std::to_string(num));
		setTextPosition();
	}

	std::string getScore()
	{
		return score.getString().toAnsiString();
	}

	void draw() override
	{
		context->getWindow().draw(root);
		context->getWindow().draw(title);
		context->getWindow().draw(score);
	}
};