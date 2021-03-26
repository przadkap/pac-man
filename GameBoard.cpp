#include "GameBoard.h"
#include <iostream>
#include <fstream>
//TODO 
//	player teleport naprawic DONE
//	dokonczyc mape rysowac DONE
//	punkty na mapie i jakis licznik DONE
//	kolizja z przeciwnikami i przegrana DONE
//	power-up i zjadanie duchow, duchy powinny uciekac w tym czasie DONE (naprawic Ambushera zeby nie wykrzaczal sie jak jest na flee_pointcie)
//	ogarnac ten wszechobecny syf i popakowac rzeczy w funkcje i zrobic jakas abstract klase GameEntity i Ghost, cos takiego DONE
//	wygrana i restart screen(po przegranej tez) DONE
// countdown do zakonczenia bonusu DONE
// grafiki dla duszkow i pacmana DONE
// jakis segmentation fault, czasem w findTarget od ambushera, a czasem w movealongcurrentdirection dla playera DONE
// random ghost moze tez niech ucieka? DONE
// enumy DONE
// bardziej popakowac wszystko w funkcje w duszkach DONE
// ogolny cleanup DONE
// no eeweentuuaalniee wracanie po zjedzeniu do domku i klapanie pacmana

void GameBoard::checkScore(QRectF pac_rect) {
	
	for(auto& powerup : powerups) {
		if(pac_rect.intersects(powerup->rect())) {
			powerup->setBrush(Qt::black);
			emit scored(25);
			emit powerupCollected();
			powerups.removeOne(powerup);
			return;
		}
	}
	
	for(auto& point : collectibles) {
		if(pac_rect.intersects(point->rect())) {
			point->setBrush(Qt::black);
			emit scored(5);
			collectibles.removeOne(point);

			return;
		}
	}
	if(collectibles.isEmpty() && powerups.isEmpty()) {
		setGameOver("YOU WON!!!");
	}
}

void GameBoard::setGameOver(QString message) {
	emit gameOver(message);
}

void GameBoard::addBonusPoints() {
	emit scored(100);
}

GameBoard::GameBoard() {
	
	generateGridline();
	
	QPixmap background = QPixmap("images/pacman_map.png");
	addPixmap(background);
	
	pacman = new Player(starting_line, this);
	pacman->setFlag(QGraphicsItem::ItemIsFocusable);
	pacman->setFocus();

	random = new RandomGhost(starting_line_ghost, corner_NE, this);
	chaser = new ChaserGhost(starting_line_chaser_ghost, corner_NW, this);
	ambusher = new AmbusherGhost(starting_line_ghost, corner_SE, this);
	scared = new ScaredGhost(starting_line_chaser_ghost, corner_SW, this);

	ghosts << random << chaser << ambusher << scared;
	for(auto& ghost : ghosts) {
		connect(pacman, SIGNAL(positionChanged(QRectF)), ghost, SLOT(checkPlayerCollision(QRectF)));
		connect(ghost, SIGNAL(requestNewTarget()), pacman, SLOT(setNewTarget()));
		connect(this, SIGNAL(powerupCollected()), ghost, SLOT(setFleeing()));
		connect(ghost, SIGNAL(playerDamaged(QString)), this, SLOT(setGameOver(QString)));
		connect(ghost, SIGNAL(ghostEaten()), this, SLOT(addBonusPoints()));
	}
	
	connect(pacman, SIGNAL(nextTargetChanged(PathPoint*, int)), chaser, SLOT(updateTarget(PathPoint*, int)));
	connect(pacman, SIGNAL(previousTargetChanged(PathPoint*, int)), ambusher, SLOT(updateTarget(PathPoint*, int)));
	connect(pacman, SIGNAL(nextTargetChanged(PathPoint*, int)), scared, SLOT(updateTarget(PathPoint*, int)));
	connect(pacman, SIGNAL(positionChanged(QRectF)), this, SLOT(checkScore(QRectF)));
	
	for(auto& point : collectibles) {
		point->setBrush(Qt::white);
		addItem(point);
	}
	
	for(auto& powerup : powerups) {
		powerup->setBrush(Qt::yellow);
		addItem(powerup);
	}
	
	addItem(pacman);
	addItem(random);
 	addItem(chaser);
 	addItem(ambusher);
 	addItem(scared);
	setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameBoard::generateGridline() {
	int offset = TILE_SIZE / 2;
	PathPoint * A0 = new PathPoint(offset, offset);
	PathPoint * A2 = new PathPoint(offset + TILE_SIZE * 5, offset);
	PathPoint * A4 = new PathPoint(offset + TILE_SIZE * 11, offset);
	PathPoint * A5 = new PathPoint(offset + TILE_SIZE * 14, offset);
	PathPoint * A7 = new PathPoint(offset + TILE_SIZE * 20, offset);
	PathPoint * A9 = new PathPoint(offset + TILE_SIZE * 25, offset);
	
	PathPoint * B0 = new PathPoint(offset, offset + TILE_SIZE * 4);
	PathPoint * B2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 4);
	PathPoint * B3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 4);
	PathPoint * B4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 4);
	PathPoint * B5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 4);
	PathPoint * B6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 4);
	PathPoint * B7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 4);
	PathPoint * B9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 4);
	
	PathPoint * C0 = new PathPoint(offset, offset + TILE_SIZE * 7);
	PathPoint * C2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 7);
	PathPoint * C3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 7);
	PathPoint * C4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 7);
	PathPoint * C5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 7);
	PathPoint * C6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 7);
	PathPoint * C7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 7);
	PathPoint * C9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 7);
	
	PathPoint * D3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 10);
	PathPoint * D4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 10);
	PathPoint * D5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 10);
	PathPoint * D6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 10);
	
	PathPoint * E2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 13);
	PathPoint * E3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 13);
	PathPoint * E6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 13);
	PathPoint * E7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 13);
	
	PathPoint * F3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 16);
	PathPoint * F6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 16);
	
	PathPoint * G0 = new PathPoint(offset, offset + TILE_SIZE * 19);
	PathPoint * G2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 19);
	PathPoint * G3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 19);
	PathPoint * G4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 19);
	PathPoint * G5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 19);
	PathPoint * G6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 19);
	PathPoint * G7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 19);
	PathPoint * G9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 19);
	
	PathPoint * H0 = new PathPoint(offset, offset + TILE_SIZE * 22);
	PathPoint * H1 = new PathPoint(offset + TILE_SIZE * 2, offset + TILE_SIZE * 22);
	PathPoint * H2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 22);
	PathPoint * H3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 22);
	PathPoint * H4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 22);
	PathPoint * H5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 22);
	PathPoint * H6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 22);
	PathPoint * H7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 22);
	PathPoint * H8 = new PathPoint(offset + TILE_SIZE * 23, offset + TILE_SIZE * 22);
	PathPoint * H9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 22);
	
	PathPoint * I0 = new PathPoint(offset, offset + TILE_SIZE * 25);
	PathPoint * I1 = new PathPoint(offset + TILE_SIZE * 2, offset + TILE_SIZE * 25);
	PathPoint * I2 = new PathPoint(offset + TILE_SIZE * 5, offset + TILE_SIZE * 25);
	PathPoint * I3 = new PathPoint(offset + TILE_SIZE * 8, offset + TILE_SIZE * 25);
	PathPoint * I4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 25);
	PathPoint * I5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 25);
	PathPoint * I6 = new PathPoint(offset + TILE_SIZE * 17, offset + TILE_SIZE * 25);
	PathPoint * I7 = new PathPoint(offset + TILE_SIZE * 20, offset + TILE_SIZE * 25);
	PathPoint * I8 = new PathPoint(offset + TILE_SIZE * 23, offset + TILE_SIZE * 25);
	PathPoint * I9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 25);
	
	PathPoint * J0 = new PathPoint(offset, offset + TILE_SIZE * 28);
	PathPoint * J4 = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 28);
	PathPoint * J5 = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 28);
	PathPoint * J9 = new PathPoint(offset + TILE_SIZE * 25, offset + TILE_SIZE * 28);
	
	PathPoint * E4_G = new PathPoint(offset + TILE_SIZE * 11, offset + TILE_SIZE * 13);
	PathPoint * E5_G = new PathPoint(offset + TILE_SIZE * 14, offset + TILE_SIZE * 13);
	
	PathLine * ghost_lair_path1 = new PathLine(D4, E4_G, VERTICAL, 10);
	PathLine * ghost_lair_path2 = new PathLine(D5, E5_G, VERTICAL, 10);
	PathLine * ghost_lair_path3 = new PathLine(E4_G, E5_G, HORIZONTAL, 10);
	
	D4->setDown(nullptr);
	D5->setDown(nullptr);
	
	PathLine * A0_A2 = new PathLine(A0, A2, HORIZONTAL, 20);
	PathLine * A2_A4 = new PathLine(A2, A4, HORIZONTAL, 25);
	PathLine * A5_A7 = new PathLine(A5, A7, HORIZONTAL, 25);
	PathLine * A7_A9 = new PathLine(A7, A9, HORIZONTAL, 20);
	
	PathLine * A0_B0 = new PathLine(A0, B0, VERTICAL, 15);
	PathLine * A2_B2 = new PathLine(A2, B2, VERTICAL, 15);
	PathLine * A4_B4 = new PathLine(A4, B4, VERTICAL, 15);
	PathLine * A5_B5 = new PathLine(A5, B5, VERTICAL, 15);
	PathLine * A7_B7 = new PathLine(A7, B7, VERTICAL, 15);
	PathLine * A9_B9 = new PathLine(A9, B9, VERTICAL, 15);
	
	PathLine * B0_B2 = new PathLine(B0, B2, HORIZONTAL, 20);
	PathLine * B2_B3 = new PathLine(B2, B3, HORIZONTAL, 10);
	PathLine * B3_B4 = new PathLine(B3, B4, HORIZONTAL, 10);
	PathLine * B4_B5 = new PathLine(B4, B5, HORIZONTAL, 10);
	PathLine * B5_B6 = new PathLine(B5, B6, HORIZONTAL, 10);
	PathLine * B6_B7 = new PathLine(B6, B7, HORIZONTAL, 10);
	PathLine * B7_B9 = new PathLine(B7, B9, HORIZONTAL, 20);
	
	PathLine * B0_C0 = new PathLine(B0, C0, VERTICAL, 10);
	PathLine * B2_C2 = new PathLine(B2, C2, VERTICAL, 10);
	PathLine * B3_C3 = new PathLine(B3, C3, VERTICAL, 10);
	PathLine * B6_C6 = new PathLine(B6, C6, VERTICAL, 10);
	PathLine * B7_C7 = new PathLine(B7, C7, VERTICAL, 10);
	PathLine * B9_C9 = new PathLine(B9, C9, VERTICAL, 10);
	
	PathLine * C0_C2 = new PathLine(C0, C2, HORIZONTAL, 20);
	PathLine * C3_C4 = new PathLine(C3, C4, HORIZONTAL, 10);
	PathLine * C5_C6 = new PathLine(C5, C6, HORIZONTAL, 10);
	PathLine * C7_C9 = new PathLine(C7, C9, HORIZONTAL, 20);
	
	PathLine * C2_E2 = new PathLine(C2, E2, VERTICAL, 25);
	PathLine * C4_D4 = new PathLine(C4, D4, VERTICAL, 10);
	PathLine * C5_D5 = new PathLine(C5, D5, VERTICAL, 10);
	PathLine * C7_E7 = new PathLine(C7, E7, VERTICAL, 25);
	
	PathLine * D3_D4 = new PathLine(D3, D4, HORIZONTAL, 10);
	PathLine * D4_D5 = new PathLine(D4, D5, HORIZONTAL, 10);
	PathLine * D5_D6 = new PathLine(D5, D6, HORIZONTAL, 10);
	
	PathLine * D3_E3 = new PathLine(D3, E3, VERTICAL, 10);
	PathLine * D6_E6 = new PathLine(D6, E6, VERTICAL, 10);
	
	PathLine * E2_E3 = new PathLine(E2, E3, HORIZONTAL, 10);
	PathLine * E6_E7 = new PathLine(E6, E7, HORIZONTAL, 10);
	PathLine * E7_E2 = new PathLine(E7, E2, HORIZONTAL, 50);
	
	PathLine * E2_G2 = new PathLine(E2, G2, VERTICAL, 25);
	PathLine * E3_F3 = new PathLine(E3, F3, VERTICAL, 10);
	PathLine * E6_F6 = new PathLine(E6, F6, VERTICAL, 10);
	PathLine * E7_G7 = new PathLine(E7, G7, VERTICAL, 25);
	
	PathLine * F3_F6 = new PathLine(F3, F6, HORIZONTAL, 40);
	
	PathLine * F3_G3 = new PathLine(F3, G3, VERTICAL, 10);
	PathLine * F6_G6 = new PathLine(F6, G6, VERTICAL, 10);
	
	PathLine * G0_G2 = new PathLine(G0, G2, HORIZONTAL, 20);
	PathLine * G2_G3 = new PathLine(G2, G3, HORIZONTAL, 10);
	PathLine * G3_G4 = new PathLine(G3, G4, HORIZONTAL, 10);
	PathLine * G5_G6 = new PathLine(G5, G6, HORIZONTAL, 10);
	PathLine * G6_G7 = new PathLine(G6, G7, HORIZONTAL, 10);
	PathLine * G7_G9 = new PathLine(G7, G9, HORIZONTAL, 20);
	
	PathLine * G0_H0 = new PathLine(G0, H0, VERTICAL, 10);
	PathLine * G2_H2 = new PathLine(G2, H2, VERTICAL, 10);
	PathLine * G4_H4 = new PathLine(G4, H4, VERTICAL, 10);
	PathLine * G5_H5 = new PathLine(G5, H5, VERTICAL, 10);
	PathLine * G7_H7 = new PathLine(G7, H7, VERTICAL, 10);
	PathLine * G9_H9 = new PathLine(G9, H9, VERTICAL, 10);
	
	PathLine * H0_H1 = new PathLine(H0, H1, HORIZONTAL, 5);
	PathLine * H2_H3 = new PathLine(H2, H3, HORIZONTAL, 10);
	PathLine * H3_H4 = new PathLine(H3, H4, HORIZONTAL, 10);
	PathLine * H4_H5 = new PathLine(H4, H5, HORIZONTAL, 10);
	PathLine * H5_H6 = new PathLine(H5, H6, HORIZONTAL, 10);
	PathLine * H6_H7 = new PathLine(H6, H7, HORIZONTAL, 10);
	PathLine * H8_H9 = new PathLine(H8, H9, HORIZONTAL, 5);
	
	PathLine * H1_I1 = new PathLine(H1, I1, VERTICAL, 10);
	PathLine * H2_I2 = new PathLine(H2, I2, VERTICAL, 10);
	PathLine * H3_I3 = new PathLine(H3, I3, VERTICAL, 10);
	PathLine * H6_I6 = new PathLine(H6, I6, VERTICAL, 10);
	PathLine * H7_I7 = new PathLine(H7, I7, VERTICAL, 10);
	PathLine * H8_I8 = new PathLine(H8, I8, VERTICAL, 10);
	
	PathLine * I0_I1 = new PathLine(I0, I1, HORIZONTAL, 5);
	PathLine * I1_I2 = new PathLine(I1, I2, HORIZONTAL, 10);
	PathLine * I3_I4 = new PathLine(I3, I4, HORIZONTAL, 10);
	PathLine * I5_I6 = new PathLine(I5, I6, HORIZONTAL, 10);
	PathLine * I7_I8 = new PathLine(I7, I8, HORIZONTAL, 10);
	PathLine * I8_I9 = new PathLine(I8, I9, HORIZONTAL, 5);
	
	PathLine * I0_J0 = new PathLine(I0, J0, VERTICAL, 10);
	PathLine * I4_J4 = new PathLine(I4, J4, VERTICAL, 10);
	PathLine * I5_J5 = new PathLine(I5, J5, VERTICAL, 10);
	PathLine * I9_J9 = new PathLine(I9, J9, VERTICAL, 10);
	
	PathLine * J0_J4 = new PathLine(J0, J4, HORIZONTAL, 50);
	PathLine * J4_J5 = new PathLine(J4, J5, HORIZONTAL, 10);
	PathLine * J5_J9 = new PathLine(J5, J9, HORIZONTAL, 50);
	
	gridline << A0_A2 << A2_A4 << A5_A7 << A7_A9
			 << A0_B0 << A2_B2 << A4_B4 << A5_B5 << A7_B7 << A9_B9
			 << B0_B2 << B2_B3 << B3_B4 << B4_B5 << B5_B6 << B6_B7 << B7_B9
			 << B0_C0 << B2_C2 << B3_C3 << B6_C6 << B7_C7 << B9_C9
			 << C0_C2 << C3_C4 << C5_C6 << C7_C9
			 << C2_E2 << C4_D4 << C5_D5 << C7_E7
			 << D3_D4 << D4_D5 << D5_D6
			 << D3_E3 << D6_E6
			 << E2_E3 << E6_E7 << E7_E2
			 << E2_G2 << E3_F3 << E6_F6 << E7_G7
			 << F3_F6
			 << F3_G3 << F6_G6
			 << G0_G2 << G2_G3 << G3_G4 << G5_G6 << G6_G7 << G7_G9
			 << G0_H0 << G2_H2 << G4_H4 << G5_H5 << G7_H7 << G9_H9
			 << H0_H1 << H2_H3 << H3_H4 << H4_H5 << H5_H6 << H6_H7 << H8_H9
			 << H1_I1 << H2_I2 << H3_I3 << H6_I6 << H7_I7 << H8_I8
			 << I0_I1 << I1_I2 << I3_I4 << I5_I6 << I7_I8 << I8_I9
			 << I0_J0 << I4_J4 << I5_J5 << I9_J9
			 << J0_J4 << J4_J5 << J5_J9
			 << ghost_lair_path1 << ghost_lair_path2 << ghost_lair_path3;
	
	std::ifstream point_file;
	point_file.open("points.txt");
	int point_y;
	int point_number;
	int point_x;

	while(point_file >> point_y) {
		point_file >> point_number;
		for(int i = 0; i < point_number; i++) {
			point_file >> point_x;
			collectibles.push_back(new QGraphicsEllipseItem(point_x, point_y, 10, 10));
		}
	}
	
	powerups.push_back(new QGraphicsEllipseItem(19, 75, 20, 20));
	powerups.push_back(new QGraphicsEllipseItem(719, 75, 20, 20));
	powerups.push_back(new QGraphicsEllipseItem(19, 635, 20, 20));
	powerups.push_back(new QGraphicsEllipseItem(719, 635, 20, 20));
	
	starting_line = H4_H5;
	starting_line_ghost = ghost_lair_path1;
	starting_line_chaser_ghost = ghost_lair_path2;
	corner_SW = J0;
	corner_NW = A0;
	corner_SE = J9;
	corner_NE = A9;
}
