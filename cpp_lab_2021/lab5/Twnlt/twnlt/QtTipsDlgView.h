#pragma once
#include<QTimer>
#include <QDialog>
#include "ui_QtTipsDlgView.h"

class QtTipsDlgView : public QDialog
{
	Q_OBJECT

public:
	QtTipsDlgView(const QString& msg, QWidget* parent = Q_NULLPTR);
	~QtTipsDlgView();
	void startTimer(int);
private:
	Ui::QtTipsDlgView ui;
	QTimer* m_pTimer;
	void initFrame(const QString& msg);
};
