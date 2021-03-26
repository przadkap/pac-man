#pragma once
#include <QPoint>

class PathLine;

class PathPoint : public QPoint {
	friend class GameBoard;
	friend class Player;
	friend class PathLine;
	friend class RandomGhost;
	friend class ChaserGhost;
	friend class AmbusherGhost;
	friend class ScaredGhost;
	friend class GameEntity;
	friend class Ghost;

public:
	PathPoint(int x, int y);
	void setLeft(PathLine* line);
	void setRight(PathLine* line);
	void setDown(PathLine* line);
	void setUp(PathLine* line);
	
private:
	PathLine * left = nullptr;
	PathLine * right = nullptr;
	PathLine * down = nullptr;
	PathLine * up = nullptr;
// 	PathPoint * previous = nullptr;
	static int count;
	int ordinal_no;
};
