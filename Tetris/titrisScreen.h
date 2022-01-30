#pragma once
#include "screen.h"
#include "appContext.h"
#include "titrisController.h"
#include "nextShapeView.h"
#include "scoreView.h"

class TitrisScreen : public Screen<AppContext>
{
private:
	TitrisController titris;
	NextShapeView nextView;
	sf::Clock clock;
	int speed;
	sf::Sprite background;
	sf::Texture backgroundTexture;
	ScoreView score;

public:
	TitrisScreen(AppContext* context, std::map<std::string, std::string> params);

	void init() override {}

	void handleEvent(sf::Event& event) override;

	void process() override;

	void draw() override;

	void setView(unsigned int width, unsigned int height);
};