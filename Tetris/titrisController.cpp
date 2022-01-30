#pragma once
#include "titrisController.h"

TitrisController::TitrisController(AppContext* context)
	:Drawable(context), board(context, sf::Vector2f(-150, -300), sf::Vector2f(300, 660)),
		generator(context, board), deleteAnim(board, 250, 1, { 1, 0 }), inProcessing(), score(0)
{
}

void TitrisController::draw()
{
	board.draw();
	generator.draw();
}

void TitrisController::process()
{
	deleteAnim.process();
}

int TitrisController::getScore()
{
	return score;
}

bool TitrisController::move(Direction direction)
{
	if (inProcessing) return true;

	if (isMovable(generator.getCurrent(), direction))
	{
		generator.getCurrent().move(direction);
		return true;
	}

	if (direction == Direction::DOWN)
	{
		board.push(generator.getCurrent());
		checkCompletedRows();

		if (IsGameOver() && gameoverCallback)
		{
			gameoverCallback();
			return false;
		}

		generator.pop();
	}
	return false;
}

void TitrisController::rotate(Direction direction)
{
	if (inProcessing) return;

	if (isRotateble(generator.getCurrent(), direction))
	{
		generator.getCurrent().rotate(direction);
	}
}

bool TitrisController::isMovable(TitrisShape& shape, Direction direction)
{
	for (auto& i : shape.getItems())
	{
		sf::Vector2i index = board.getIndex(i);

		//if the destination cell is out of bounds or it is already occupied means the shape is not movable
		switch (direction)
		{
		case Direction::RIGHT:
			if (index.x >= board.getSize().x - 1 || board.isOccupied(index.x + 1, index.y)) return false;
			break;
		case Direction::LEFT:
			if (index.x <= 0 || board.isOccupied(index.x - 1, index.y)) return false;
			break;
		case Direction::DOWN:
			if (index.y >= board.getSize().y - 1 || board.isOccupied(index.x, index.y + 1)) return false;
			break;
		default: return false;
		}
	}

	return true;
}

bool TitrisController::isRotateble(TitrisShape shape, Direction direction)
{
	shape.rotate(direction);

	//after the shape got rotated
	for (auto& i : shape.getItems())
	{
		sf::Vector2i index = board.getIndex(i);

		//if the index out of the board bounds, or in the a cell that is already occupied, means it is not rotatable
		if (board.isOutOfBounds(index) || board.isOccupied(index.x, index.y)) return false;
	}

	return true;
}

bool TitrisController::IsGameOver()
{
	for (int x = 0; x < board.getSize().x; ++x)
	{
		//if there is an object in row 2, the game will be over
		if (board.isOccupied(x, 2))
		{
			return true;
		}
	}
	return false;
}

bool TitrisController::InProcessing()
{
	return inProcessing;
}

void TitrisController::checkCompletedRows()
{
	//contains y index of each completed row
	std::vector<int> indices;

	for (int y = board.getSize().y - 1; y >= 0; --y)
	{
		bool flag = true;

		//the row contains any empty cell, set flag to false and break
		for (int x = 0; x < board.getSize().x; ++x)
		{
			if (!board.isOccupied(x, y))
			{
				flag = false;
				break;
			}
		}

		//if there is no empty cell, add the index to the vector
		if (flag)
		{
			indices.push_back(y);
		}
	}

	//if there is completed rows, delete them
	if (indices.size() > 0)
	{
		startDeletingRows(indices);
	}
}

void TitrisController::startDeletingRows(std::vector<int> indices)
{
	inProcessing = true;

	score += (indices.size() * 5) + std::pow((float)indices.size(), 2.0f);

	//set the animation to scale down each cell
	deleteAnim.setCallBack([indices](TitrisBoard& board, float value) {
		for (int x = 0; x < board.getSize().x; ++x)
		{
			for (unsigned int i = 0; i < indices.size(); ++i)
			{
				if (board.isOccupied(x, indices[i]))
				{
					board.settled[indices[i]][x]->setScale(value, value);
				}
			}
		}
	});

	//when the scale animation is finished
	deleteAnim.setAnimationEndCallback([indices, this]() {
		//move down the cells
		this->moveDown(indices);
		this->inProcessing = false;
	});

	//start the animation
	deleteAnim.start();
}

void TitrisController::moveDown(std::vector<int> index)
{
	int counter = 0;

	//for each row starting from the bottom
	for (int y = board.getSize().y - 1; y >= 0; --y)
	{
		//if this row should be deleted delete it
		if (counter < index.size() && y == index[counter])
		{
			for (int x = 0; x < board.getSize().x; ++x)
			{
				board.settled[y][x] = nullptr;
			}

			++counter;
		}
		//eles if the counter not zero
		//means that there is a row "or more" deleted under this row so move them down 
		else if (counter != 0)
		{
			for (int x = 0; x < board.getSize().x; ++x)
			{
				if (!board.isOccupied(x, y)) continue;

				//if the cell not empty

				//move the position down depending on the counter
				//e.g. if the counter is 2 means there is two deleted rows under it so move it two cells down
				board.setPosition(*board.settled[y][x], sf::Vector2i(x, y + counter));
				board.settled[y + counter][x] = board.settled[y][x];
				board.settled[y][x] = nullptr;
			}
		}
	}
}


TitrisGenerator& TitrisController::getGenerator()
{
	return generator;
}


void TitrisController::setGameoverCallback(std::function<void()> callback)
{
	gameoverCallback = callback;
}