#pragma once
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include "PathPoint.h"
#include "PathLine.h"
#define STEP 1

enum directions {
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_UP
};

class GameEntity : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
protected:
	virtual void move() {};
	int move_direction;
	int move_interval;
	void checkIfOnPathPoint();
	QTimer * move_timer;
	PathLine * current_pathline;
	PathPoint * current_pathpoint;
private slots:
	virtual void advance() {};
};
