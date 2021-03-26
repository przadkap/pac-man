#pragma once

#include "GameBoard.h"
#include "ScoreBox.h"
#include "PowerUpBox.h"
#include "MenuScreen.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QObject>

class GameBoard;

#define TILE_SIZE 28
#define WINDOW_WIDTH (27 * TILE_SIZE)
#define WINDOW_HEIGHT (30 * TILE_SIZE)

class Game : public QWidget {
	Q_OBJECT

	int score = 0;
public slots:
	void setNewScore(int add_amount);
	void setRestartScreen(QString message);
	void startNewGame();
signals:
	void updateScore(int);
public:
	Game(QWidget *parent = 0);
	GameBoard * game_board;
	QGraphicsView * view;
	QVBoxLayout * layout;
	ScoreBox * score_box;
	PowerUpBox * powerup_box;
};
