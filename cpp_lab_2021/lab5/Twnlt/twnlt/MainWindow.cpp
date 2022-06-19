#include "MainWindow.h"

MainWindow::MainWindow(QStringList qstr,QWidget *parent)
	: QMainWindow(parent)
{
    this->qstr = qstr;
	ui.setupUi(this);
    FuzzySearch();
}

MainWindow::~MainWindow()
{
}
void MainWindow::FuzzySearch()
{

    ui.comboBox->addItems(qstr);
    ui.comboBox_2->addItems(qstr);
    ui.comboBox->setView(new QListView());
    ui.comboBox->setEditable(true);
    ui.comboBox->setLineEdit(ui.lineEdit);
    ui.comboBox->setMaxVisibleItems(5);//下拉列表显示item数
    ui.comboBox_2->setView(new QListView());
    ui.comboBox_2->setEditable(true);
    ui.comboBox_2->setMaxVisibleItems(5);
    ui.comboBox_2->setLineEdit(ui.lineEdit_2);
//    QString arrowImagePath = ":/res/combox.png";
//    ui->comboBox->setStyleSheet("QComboBox {font-family: \"Arial\"; font-size: 13px; padding: 3px 0x 3px 5px;}"
//        "QComboBox::drop-down {subcontrol-origin: padding; subcontrol-position: top right; width: 30 px; border: 0px;}"
//        "QComboBox::down-arrow {image: url("+ arrowImagePath +");}");

    ui.comboBox->view()->setStyleSheet("QListView {font-family: \"Arial\"; font-size: 13px; outline: 0px;}"
        "QListView::item {padding: 3px 0x 3px 5px; border-width: 0px;}"
        "QListView::item:selected {background-color: rgb(74, 144, 226);}");
    QCompleter* pCompleter = new QCompleter(qstr, this);
    ui.lineEdit->setCompleter(pCompleter);
    pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui.comboBox->setCompleter(pCompleter);
    ui.lineEdit->clear();
    ui.comboBox_2->view()->setStyleSheet("QListView {font-family: \"Arial\"; font-size: 13px; outline: 0px;}"
        "QListView::item {padding: 3px 0x 3px 5px; border-width: 0px;}"
        "QListView::item:selected {background-color: rgb(74, 144, 226);}");
    QCompleter* pCompleter2 = new QCompleter(qstr, this);
    ui.lineEdit_2->setCompleter(pCompleter2);
    pCompleter2->setCaseSensitivity(Qt::CaseInsensitive);
    ui.comboBox_2->setCompleter(pCompleter2);
    ui.lineEdit_2->clear();
}
void MainWindow::checkinput()
{
    QString start = ui.lineEdit->text();
    int flag1 = 0, flag2 = 0;
    QString end = ui.lineEdit_2->text();
    //if (start.isEmpty() || start.isEmpty())
    //{
    //    ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");
    //    ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入站点及线路文件路径！")); //不用fromLocal8Bit显示乱码
    //    ui.textEditStop->setFocus();
    //    return;
    //}
    int i = 0;
    int pos1=0, pos2=0;
    QList<QString>::Iterator it=qstr.begin();
    for (; it != qstr.end(); it++)
    {
        if (*it == start)
        {
            pos1 = i;
        }
        else if (*it == end)
        {
            pos2 = i;
        }
        i++;
    }
    if (pos1 && pos2)
    {
        gis->end = pos1;
        gis->start = pos2;
        gis->flag = true;
    }
    else
    {

    }
}
