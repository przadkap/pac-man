#pragma once

#include "Game.h"
#include "Button.h"
#include <string>
#include <QGraphicsScene>
#include <QString>

class MenuScreen : public QGraphicsScene {
	Q_OBJECT
public:
	MenuScreen(QString message, int score, bool display_score = true);
signals:
	void closeGame();
	void restartGame();
private slots:
	void emitClose();
	void emitRestart();
};
