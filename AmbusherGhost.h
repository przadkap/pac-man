#pragma once

#include "Ghost.h"

class AmbusherGhost : public Ghost {
	Q_OBJECT
public:
	AmbusherGhost(PathLine * staring_line, PathPoint * i_flee_point, QObject * parent);
public slots:
	void updateTarget(PathPoint * new_target_point, int new_player_move_direction);
private:
	void findTarget();
	int player_move_direction;
};
