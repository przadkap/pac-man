#pragma once

#include "Player.h"
#include "PathLine.h"
#include "PathPoint.h"
#include "RandomGhost.h"
#include "ChaserGhost.h"
#include "AmbusherGhost.h"
#include "ScaredGhost.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QObject>

class Player;

#define TILE_SIZE 28
#define WINDOW_WIDTH (27 * TILE_SIZE)
#define WINDOW_HEIGHT (30 * TILE_SIZE)

class GameBoard : public QGraphicsScene {
	Q_OBJECT
	void generateGridline();
	QVector<PathLine*> gridline;
	QVector<QGraphicsEllipseItem*> collectibles;
	QVector<QGraphicsEllipseItem*> powerups;
	QVector<Ghost *> ghosts;
	PathLine * starting_line;
	PathLine * starting_line_ghost;
	PathLine * starting_line_chaser_ghost;
	PathPoint * corner_NE;
	PathPoint * corner_NW;
	PathPoint * corner_SE;
	PathPoint * corner_SW;
	Player * pacman;
	AmbusherGhost * ambusher;
	ChaserGhost * chaser;
	RandomGhost * random;
	ScaredGhost * scared;
public slots:
	void checkScore(QRectF pac_rect);
	void addBonusPoints();
	void setGameOver(QString message);
signals:
	void scored(int);
	void powerupCollected();
	void gameOver(QString message);
public:
	GameBoard();
};
