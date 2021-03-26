#pragma once

#include "GameEntity.h"
#include "PathLine.h"
#include "PathPoint.h"
#include "Game.h"
// #include <QGraphicsRectItem>
// #include <QTimer>
#include <QPointF>
#include <QRectF>

#define PLAYER_SIZE 30
#define MOVE_STOP 0
// #define MOVE_LEFT 1
// #define MOVE_RIGHT 2
// #define MOVE_DOWN 3
// #define MOVE_UP 4
// #define STEP 1

class Player :  public GameEntity {
	Q_OBJECT

public:
	Player(PathLine * starting_line, QObject * parent = 0);
	void keyPressEvent(QKeyEvent *event);
public slots:
	void setDirection(QKeyEvent *event);
	void setNewTarget();
private slots:
	void advance();
signals:
	void nextTargetChanged(PathPoint * new_target, int new_move_direction);
	void previousTargetChanged(PathPoint * new_target, int new_move_direction);
	void positionChanged(QRectF pac_rect);
private:
	void move();
	void moveAlongCurrentDirection();
	bool stopped = false;
// 	void checkIfOnPathPoint();
// 	int move_direction;
	int next_move_direction;
// 	QPointF *origin;
	void stop();
// 	QTimer * move_timer;
	
// 	PathLine * current_pathline;
// 	PathPoint * current_pathpoint;
};
