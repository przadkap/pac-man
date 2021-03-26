#include "ScoreBox.h"
#include <QLabel>
ScoreBox::ScoreBox(QWidget *parent) : QWidget(parent) {
	lcd = new QLCDNumber(4);
	lcd->display(0);
	lcd->setSegmentStyle(QLCDNumber::Filled);
	lcd->setMinimumHeight(30);

	QLabel * score_label = new QLabel("Score: ");
	score_label->setAlignment(Qt::AlignCenter);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(score_label);
	layout->addWidget(lcd);
	setLayout(layout);
}

void ScoreBox::setValue(int new_score) {
	lcd->display(new_score);
}
