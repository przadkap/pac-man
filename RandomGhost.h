#pragma once

#include "Ghost.h"

class Ghost;

class RandomGhost : public Ghost {
	Q_OBJECT
public:
	RandomGhost(PathLine * staring_line, PathPoint * i_flee_point, QObject * parent);
private:
	void findTarget();
};
