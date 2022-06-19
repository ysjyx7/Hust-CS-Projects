#pragma once
#include <QtWidgets/QMainWindow>
#include<QGraphicsRectItem>
#include "ui_twnlt.h"
class QtWidgetsFL;
class MainWindow;
class twnlt : public QMainWindow
{
    Q_OBJECT

public:
    twnlt(QWidget* parent = Q_NULLPTR);
    ~twnlt();
private:
    Ui::twnltClass ui;
    QtWidgetsFL* fl;
    MainWindow* win;
    QTimer* m_Timer;
    QGraphicsItemGroup* gItem;
    void deleteItems();
protected:
    void closeEvent(QCloseEvent* event);
private slots:
    void loadmap();
    void closewnd();
    void zszc();
    void zdjl();
    void findinput();
};
class MyScene :public QGraphicsScene
{
public:
    explicit MyScene(QObject* parent = 0);
    void stopLines(QGraphicsView*);
protected:
    QGraphicsView* qgv;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
public slots:
};
class MyItem :public QGraphicsRectItem {
    int cx, cy;//��ǰͼԪ������
    int cf;//�����������Ҽ������Ϊ1���Ҽ�Ϊ2
    int cs;//��¼bs��洢��վ����Ŀ
    int bs[6];//��¼�뵱ǰͼԪ���������վ����
public:
    MyItem(int x, int y, int f);
    MyItem& operator<<(int s);
    int operator()(int x, int y);
    int& x();
    int& y();
    int& f();
    int& c();
    int& operator[](int);
    int checkAllStops();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};
