#include "PowerUpBox.h"
#include <QLabel>

PowerUpBox::PowerUpBox(QWidget *parent) : QWidget(parent) {
	
	powerup_bar = new QProgressBar();
	
	powerup_bar->setTextVisible(false);
	powerup_bar->setMaximum(100);
	powerup_bar->setValue(0);
	
	progress_timer = new QTimer();
	connect(progress_timer, SIGNAL(timeout()), this, SLOT(updateBar()));
	
	QLabel * powerup_label = new QLabel("Remaining power-up time: ");
	powerup_label->setAlignment(Qt::AlignCenter);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(powerup_label);
	layout->addWidget(powerup_bar);
	setLayout(layout);
}

void PowerUpBox::activate() {
	time_remaining = 100;
	progress_timer->start(100);
	updateBar();
}

void PowerUpBox::updateBar() {
	powerup_bar->setValue(time_remaining);
	if(time_remaining == 0) {
		progress_timer->stop();
	}
	--time_remaining;
}
