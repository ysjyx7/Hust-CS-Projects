#include "QtTipsDlgView.h"

QtTipsDlgView::QtTipsDlgView(const QString& msg, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);

	initFrame(msg);

	m_pTimer = new QTimer(this);
	m_pTimer->setSingleShot(true);	//定时器只执行一次
	connect(m_pTimer, &QTimer::timeout, this, [=]() {this->close(); });
}

QtTipsDlgView::~QtTipsDlgView()
{
	if (this->m_pTimer != Q_NULLPTR)
	{
		this->m_pTimer->deleteLater();
	}
}

void QtTipsDlgView::startTimer(int ms)
{
	this->m_pTimer->start(ms);
}
void QtTipsDlgView::initFrame(const QString& msg)
{
	ui.labelMsg->setText(msg);
}
