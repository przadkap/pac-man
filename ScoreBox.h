#pragma once
#include <QWidget>
#include <QLCDNumber>
#include <QHBoxLayout>
class ScoreBox : public QWidget {
	Q_OBJECT
	QLCDNumber * lcd;
public:
	ScoreBox(QWidget *parent = 0);

public slots:
	void setValue(int value);
};
