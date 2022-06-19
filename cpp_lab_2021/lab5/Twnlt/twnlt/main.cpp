#pragma once
#include "twnlt.h"
#include <QtWidgets/QApplication> 
#include <qdesktopwidget.h> 
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	twnlt w;
	w.show();
	return a.exec();
}
