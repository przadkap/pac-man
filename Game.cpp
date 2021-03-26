#include "Game.h"
#include <iostream>
#include <fstream>
#include <QFont>

void Game::setNewScore(int add_amount) {
	score += add_amount;
	emit updateScore(score);
}

void Game::setRestartScreen(QString message) {
	GameBoard * old_board = game_board;
	disconnect(old_board, SIGNAL(gameOver(QString)), this, SLOT(setRestartScreen(QString)));
	disconnect(old_board, SIGNAL(scored(int)), this, SLOT(setNewScore(int)));
	disconnect(old_board, SIGNAL(powerupCollected()), powerup_box, SLOT(activate()));

	delete old_board;
	
	MenuScreen * over_screen = new MenuScreen(message, score);
	
	connect(over_screen, SIGNAL(closeGame()), this, SLOT(close()));
	connect(over_screen, SIGNAL(restartGame()), this, SLOT(startNewGame()));

	view->setScene(over_screen);
}

void Game::startNewGame() {
	score = 0;
	emit updateScore(score);
	GameBoard * new_board = new GameBoard();
	connect(new_board, SIGNAL(gameOver(QString)), this, SLOT(setRestartScreen(QString)));
	connect(new_board, SIGNAL(scored(int)), this, SLOT(setNewScore(int)));
	connect(new_board, SIGNAL(powerupCollected()), powerup_box, SLOT(activate()));
	view->setScene(new_board);
	game_board = new_board;
}

Game::Game(QWidget *parent) : QWidget(parent) {

	view = new QGraphicsView();
	view->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	
	score_box = new ScoreBox();
	
	connect(this, SIGNAL(updateScore(int)), score_box, SLOT(setValue(int)));
	
	powerup_box = new PowerUpBox();
	
// 	startNewGame();
	
	MenuScreen * start_menu = new MenuScreen("Pac-man", score, false);
	
	connect(start_menu, SIGNAL(closeGame()), this, SLOT(close()));
	connect(start_menu, SIGNAL(restartGame()), this, SLOT(startNewGame()));
	
	view->setScene(start_menu);
	
	QHBoxLayout * up_bar = new QHBoxLayout();
	
	up_bar->addWidget(powerup_box);
	up_bar->addWidget(score_box);
	
	layout = new QVBoxLayout();
	layout->addLayout(up_bar);
	layout->addWidget(view);
	setLayout(layout);

}
