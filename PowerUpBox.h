#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QTimer>

class PowerUpBox : public QWidget {
	Q_OBJECT
	QProgressBar * powerup_bar;
	QTimer * progress_timer;
	int time_remaining = 0;
public:
	PowerUpBox(QWidget *parent = 0);

private slots:
	void updateBar();
public slots:
	void activate();
};
