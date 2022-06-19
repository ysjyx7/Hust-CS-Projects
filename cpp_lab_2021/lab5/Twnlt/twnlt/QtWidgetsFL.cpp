#include <QFileDialog>
#include <QMessageBox>
#include "QtWidgetsFL.h"
#include "logiclayer.h"
#include "twnlt.h"

//自定义的站点及线路输入界面
QtWidgetsFL::QtWidgetsFL(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonStop, SIGNAL(clicked()), this, SLOT(inputStop()), Qt::UniqueConnection);
	connect(ui.pushButtonLine, SIGNAL(clicked()), this, SLOT(inputLine()), Qt::UniqueConnection);
	connect(ui.pushButtonorg, SIGNAL(clicked()), this, SLOT(inputOrg()), Qt::UniqueConnection);
	connect(ui.pushButtonDone, SIGNAL(clicked()), this, SLOT(checkFile()), Qt::UniqueConnection);
	connect(ui.pushButtonDone, SIGNAL(clicked()),this,SLOT(close()),Qt::UniqueConnection);
}
void QtWidgetsFL::myShow(QGraphicsView* p) {
	parnt = p;
	show();
}
QtWidgetsFL::~QtWidgetsFL()
{
}
void QtWidgetsFL::inputStop() {
	ui.labelHits->setText("");
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*.txt"));
	ui.textEditStop->setText(fileName);
}
void QtWidgetsFL::inputLine() {
	ui.labelHits->setText("");
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "lines", tr("*.txt"));
	ui.textEditLine->setText(fileName);
}
void QtWidgetsFL::inputOrg()
{
	ui.labelHits->setText("");
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*.txt"));
	ui.textEditorg->setText(fileName);
}

void QtWidgetsFL::checkFile() {
	QString  fs = ui.textEditStop->toPlainText();
	QString  fl = ui.textEditLine->toPlainText();
	QString  forg = ui.textEditorg->toPlainText();
	if (fs.isEmpty() && fl.isEmpty()&&forg.isEmpty()) {
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入站点及线路文件路径！")); //不用fromLocal8Bit显示乱码
		ui.textEditStop->setFocus();
		return;
	}
	if (fs.isEmpty()) {
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入站点文件路径！"));
		ui.textEditStop->setFocus();
		return;
	}
	if (fl.isEmpty()) {
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入线路文件路径！"));
		ui.textEditLine->setFocus();
		return;
	}
	if (forg.isEmpty())
	{
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入地名文件路径！"));
		ui.textEditLine->setFocus();
		return;
	}
	//处理站点文件
	ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");	//设置操作提示信息显示颜色
	ui.labelHits->setText(QString::fromLocal8Bit("操作提示：正在处理站点和线路文件..."));
	try {//读入站点及线路文件并初始化
		if (gis != nullptr) delete gis;
		std::string s1 = forg.toStdString();
		const char* ss = s1.c_str();
		gis = new GIS(fs.toStdString().c_str(), fl.toStdString().c_str(),ss);
		((MyScene*)(parnt->scene()))->stopLines(parnt); //在背景地图上画出站点及公交线路
	}
	catch (...) {//读入或初始化失败
		gis = nullptr;
		close();
		QMessageBox::information(NULL, QString::fromLocal8Bit("操作提示"), QString::fromLocal8Bit("公交站点或公交线路文件读入及初始化失败！"));
	}
	ui.labelHits->setText("");
	close();
}