#pragma once
#include "app.h"
#include <cstdlib>
#include "startScreen.h"
#include "titrisScreen.h"


App::App()
	: AppBase(1080, 720, "Tetris")
{
	context.getWindow().setFramerateLimit(120);
}

Screen<AppContext>* App::getScreen(std::string key, std::map<std::string, std::string> params)
{
	if (key == "start")
	{
		return new StartScreen(&context, params);
	}
	else if (key == "tetris")
	{
		return new TitrisScreen(&context, params);
	}
	return nullptr;
}

std::map<std::string, std::string> App::initTextures()
{
	std::map<std::string, std::string> map;

	map["item"] = "res/item.png";
	map["background"] = "res/background.png";
	map["background_view"] = "res/view.png";

	return map;
}


std::map<std::string, std::string> App::initFonts()
{
	std::map<std::string, std::string> map;

	map["timesbd"] = "res/timesbd.ttf";

	return map;
}

std::string App::firstScreenKey()
{
	return "start";
}