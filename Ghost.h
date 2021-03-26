#pragma once

#include "GameEntity.h"
#include <QBrush>

#define GHOST_SIZE 30

class Ghost : public GameEntity {
	Q_OBJECT

	virtual void findTarget() {};
	void move();
	void backToLair();
protected:
	PathPoint * target_pathpoint;
	PathPoint * flee_point;
	PathPoint * starting_point;
	PathPoint * true_target;
	bool fleeing = false;
	bool recovering = false;
	QTimer * recovery_timer;
	QTimer * flee_timer;
	QPixmap pixmap;
	PathPoint * calculateNextMovement();
	int distance_to_target;
	void changeMoveDirection();
private slots:
	void advance();
	void setFleeing();
	void checkPlayerCollision(QRectF pac_rect);
	void stopRecovering();
	void stopFleeing();
signals:
	void ghostEaten();
	void playerDamaged(QString message);
	void requestNewTarget();
};
