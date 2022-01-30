#pragma once
#include"drawable.h"
#include "appContext.h"
#include "titrisShape.h"
#include <queue>
#include "titrisGenerator.h"

class NextShapeView : public Drawable<AppContext>
{
private:
	sf::RectangleShape root;
	TitrisShape shape;
	sf::Texture background;

public:
	NextShapeView(AppContext* context, sf::Vector2f position, sf::Vector2f size);

	void update(TitrisGenerator& generator);

	void draw() override;   
};
