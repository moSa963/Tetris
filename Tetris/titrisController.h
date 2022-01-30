#pragma once
#include "drawable.h"
#include "appContext.h"
#include "titrisShape.h"
#include "direction.h"
#include "titrisBoard.h"
#include "titrisGenerator.h"

class TitrisController : public Drawable<AppContext>
{
private:
	TitrisBoard board;
	TitrisGenerator generator;
	bool inProcessing;
	Animation<TitrisBoard> deleteAnim;
	int score;
	std::function<void()> gameoverCallback;

private:
	//start the deleting animation
	void startDeletingRows(std::vector<int> index);

	bool isMovable(TitrisShape& shape, Direction direction);

	bool isRotateble(TitrisShape shape, Direction direction);

	void moveDown(std::vector<int> index);

	void checkCompletedRows();
public:

	TitrisController(AppContext* context);

	void draw() override;

	void process();

	TitrisGenerator& getGenerator();

	//move the current shape, if it can move
	bool move(Direction direction);

	//rotate the current shape, if it can rotate
	void rotate(Direction direction);

	//true if the game is over
	bool IsGameOver();

	//in processing "deleting or running animation"
	bool InProcessing();

	int getScore();

	void setGameoverCallback(std::function<void()> callback);
};