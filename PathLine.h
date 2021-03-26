#pragma once
#include <QLineF>
#include <QPoint>
#include <QGraphicsLineItem>

#define HORIZONTAL 0
#define VERTICAL 1

class PathPoint;

class PathLine : public QLineF {
	friend class Player;
	friend class PathPoint;
	friend class RandomGhost;
	friend class ChaserGhost;
	friend class AmbusherGhost;
	friend class ScaredGhost;
	friend class GameEntity;
	friend class Ghost;
	friend class GameBoard;
public:
	PathLine(PathPoint* begin, PathPoint* end, int direction, int length);
	QGraphicsLineItem * line_to_draw;
private:
	PathPoint * begin_point;
	PathPoint * end_point;
	int movement_cost;
};
