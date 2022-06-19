#pragma once

#include <QWidget>
#include "ui_QtWidgetsFL.h"

class QtWidgetsFL : public QWidget
{
	Q_OBJECT
public:
	QtWidgetsFL(QWidget* parent = Q_NULLPTR);
	~QtWidgetsFL();
	QGraphicsView* parnt;
	void myShow(QGraphicsView* p);
private:
	Ui::QtWidgetsFL ui;
private slots:
	void inputStop();
	void inputLine();
	void checkFile();
	void inputOrg();
};
