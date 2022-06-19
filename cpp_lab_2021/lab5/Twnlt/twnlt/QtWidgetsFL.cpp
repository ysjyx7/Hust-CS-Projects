#include <QFileDialog>
#include <QMessageBox>
#include "QtWidgetsFL.h"
#include "logiclayer.h"
#include "twnlt.h"

//�Զ����վ�㼰��·�������
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
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û������վ�㼰��·�ļ�·����")); //����fromLocal8Bit��ʾ����
		ui.textEditStop->setFocus();
		return;
	}
	if (fs.isEmpty()) {
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û������վ���ļ�·����"));
		ui.textEditStop->setFocus();
		return;
	}
	if (fl.isEmpty()) {
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û��������·�ļ�·����"));
		ui.textEditLine->setFocus();
		return;
	}
	if (forg.isEmpty())
	{
		ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û����������ļ�·����"));
		ui.textEditLine->setFocus();
		return;
	}
	//����վ���ļ�
	ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");	//���ò�����ʾ��Ϣ��ʾ��ɫ
	ui.labelHits->setText(QString::fromLocal8Bit("������ʾ�����ڴ���վ�����·�ļ�..."));
	try {//����վ�㼰��·�ļ�����ʼ��
		if (gis != nullptr) delete gis;
		std::string s1 = forg.toStdString();
		const char* ss = s1.c_str();
		gis = new GIS(fs.toStdString().c_str(), fl.toStdString().c_str(),ss);
		((MyScene*)(parnt->scene()))->stopLines(parnt); //�ڱ�����ͼ�ϻ���վ�㼰������·
	}
	catch (...) {//������ʼ��ʧ��
		gis = nullptr;
		close();
		QMessageBox::information(NULL, QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("����վ��򹫽���·�ļ����뼰��ʼ��ʧ�ܣ�"));
	}
	ui.labelHits->setText("");
	close();
}