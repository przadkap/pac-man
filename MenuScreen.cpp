#include "MenuScreen.h"
#include <QGraphicsRectItem>

MenuScreen::MenuScreen(QString message, int score, bool display_score) {
	QGraphicsRectItem * background = new QGraphicsRectItem(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	background->setBrush(Qt::darkGray);
	addItem(background);
	
	QGraphicsTextItem * game_over_text = new QGraphicsTextItem(message);
	game_over_text->setFont(QFont("Times", 40, QFont::Bold));
	game_over_text->setPos(WINDOW_WIDTH / 4 + 25 + (65 * !display_score) , WINDOW_HEIGHT / 8);
	
	if(display_score) {
		QString score_string = QString::number(score);
		QGraphicsTextItem * score_text = new QGraphicsTextItem("You scored " + score_string +" points.");
		score_text->setFont(QFont("Times", 30, QFont::Bold));
		score_text->setPos(WINDOW_WIDTH / 4 + 10, WINDOW_HEIGHT / 4.5);
		addItem(score_text);
	}

	Button * restart_button = new Button(QString("NEW GAME"), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
	Button * quit_button = new Button(QString("QUIT"), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
	restart_button->setPos(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 3);
	quit_button->setPos(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 1.5);

	connect(restart_button, SIGNAL(clicked()), this, SLOT(emitRestart()));
	connect(quit_button, SIGNAL(clicked()), this, SLOT(emitClose()));
	
	addItem(game_over_text);
	addItem(restart_button);
	addItem(quit_button);
	setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void MenuScreen::emitClose() {
	emit closeGame();
}

void MenuScreen::emitRestart() {
	emit restartGame();
}
