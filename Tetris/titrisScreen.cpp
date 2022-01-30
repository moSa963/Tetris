#pragma once
#include "titrisScreen.h"
#include "direction.h"

TitrisScreen::TitrisScreen(AppContext* context, std::map<std::string, std::string> params)
	: Screen(context, params), titris(context), clock(), speed(300),
	 nextView(context, sf::Vector2f(200, -300), sf::Vector2f(150, 150)), background(),
	backgroundTexture(context->getTexture("background")),
	score(context, sf::Vector2f(-350, 0), sf::Vector2f(150, 150))
{
	backgroundTexture.setRepeated(true);
	//set the background 
	background.setColor(sf::Color(150, 150, 150));
	background.setTexture(backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
	background.setPosition(sf::Vector2f(-1000, -1000));

	titris.setGameoverCallback([context=context, &score=score]() {
		std::map<std::string, std::string> params;
		params["score"] = score.getScore();
		context->setScreen("start", params);
	});

	clock.restart();
}

void TitrisScreen::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		//when the window resize, reset the view with the new size
		setView(event.size.width, event.size.height);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Right)
		{
			titris.move(Direction::RIGHT);
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			titris.move(Direction::LEFT);
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			titris.move(Direction::DOWN);
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			titris.rotate(Direction::RIGHT);
		}
	}
}

void TitrisScreen::process()
{
	titris.process();

	if (clock.getElapsedTime().asMilliseconds() >= speed)
	{
		//move the current shape down
		titris.move(Direction::DOWN);

		//update the view with the next shape in the queue
		nextView.update(titris.getGenerator());

		score.setScore(titris.getScore());

		clock.restart();
	}
}

void TitrisScreen::draw()
{
	context->getWindow().draw(background);
	titris.draw();
	nextView.draw();
	score.draw();
}

void TitrisScreen::setView(unsigned int width, unsigned int height)
{
	sf::View newView(sf::Vector2f(0.0, 0.0), sf::Vector2f((float)width, (float)height));
	newView.zoom((float)(1080 * 2) / (width + height));
	context->setView(newView);
}