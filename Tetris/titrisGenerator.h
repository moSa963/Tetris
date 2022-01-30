#pragma once
#include "drawable.h"
#include "appContext.h"
#include "titrisBoard.h"
#include "titrisShape.h"
#include <queue>


class TitrisGenerator : public Drawable<AppContext>
{
private:
	std::queue<TitrisShape> next;
	TitrisShape current;
	sf::Texture shapeTexture;
	TitrisBoard& board;
	sf::RectangleShape root;

private:
	sf::Color getRandomColor();
	void pushShape();
	TitrisShape randomShape();

public:
	TitrisGenerator(AppContext* context, TitrisBoard& board);

	
	TitrisShape& getCurrent();

	//set the first shape in the queue as current and push a new shape to the queue
	void pop();
	
	std::queue<TitrisShape>& getQueue();

	void draw() override;
};
