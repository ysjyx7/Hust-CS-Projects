#include "twnlt.h"
#include "logiclayer.h"
#include "QtWidgetsFL.h"
#include "MainWindow.h"
#include <QDialog>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include "QtTipsDlgView.h"
using namespace std;
GIS* gis = nullptr;     //地图信息
bool route = false;       //未显示查询路径时
bool depart = false;    //未选取步行起点
bool arrive = false;    //未选取步行终点
MyItem::MyItem(int x, int y, int f) : QGraphicsRectItem(x - 3, y - 3, 7, 7), cx(x), cy(y), cf(f), cs(0) {
    //以下根据鼠标左键点击步行起点和鼠标右键点击步行终点设置不同画笔颜色
    QBrush qbrush(f == 1 ? QColor(210, 105, 45) : QColor(255, 170, 00));   //根据f设置颜色
    QPen qpens(qbrush, 4, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //图元点的画笔
    QGraphicsRectItem* item = this;
    item->setPen(qpens);
    item->setBrush(qbrush);
    //item->setFlag(QGraphicsItem::ItemIsMovable); //不选中：因为没有移动图元点的操作
    checkAllStops(); //检测所有站点，找出最近的站点存于bs中
}
int& MyItem::x() { return cx; }
int& MyItem::y() { return cy; }
int& MyItem::f() { return cf; }
int& MyItem::c() { return cs; }
int& MyItem::operator[](int x) {
    if (x < 0 || x >= cs) throw "subscription overflow for stops around departure point!";
    return bs[x];   //返回已检测的编号为x的站点编号
}
int MyItem::operator()(int x, int y) {  //仅用于检测两点距离远近，不开方
    return (x - cx) * (x - cx) + (y - cy) * (y - cy);
}
MyItem& MyItem::operator<<(int s) {
    if (s < 0 || s >= GIS::ns) return *this;
    int d = (*this)(GIS::st[s].X(), GIS::st[s].Y()); //d为当前图元点到站点s的距离
    int m;          //m为当前图元点到先前已检测站点的距离
    if (cs == 0 || d < (m = (*this)(GIS::st[bs[0]].X(), GIS::st[bs[0]].Y()))) { //若bs没有元素即cs==0，或距离站点s更近
        bs[0] = s;
        cs = 1;
        return *this;
    }
    if (d == m) {   //和已检测站点比，到标号为s的站点的距离相同时
        if (cs == 6) return *this;
        bs[cs] = s; //只保存和最近距离相同的站点
        cs++;       //距离相同的站点个数增加
    }
    return *this;
}
int MyItem::checkAllStops() {//检测所有站点，找出最近的站点存于bs中
    for (int c = 0; c < GIS::ns; c++)
        operator<<(GIS::st[c].N());
    return cs;              //返回距离最近且相同的站点个数
}
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setSelected(true);      //当前图元被选中
    QGraphicsRectItem::mousePressEvent(event);
}
//定义自己的场景MyScene，以便能够捕获鼠标或键盘事件
MyScene::MyScene(QObject* parent) : QGraphicsScene(parent)
{
    clearFocus();
    qgv = Q_NULLPTR;        //没有加载地图文件时
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    //注意在其.ui界面文件中，mouseTracking必须勾选，否则不会出现此事件
    if (qgv == Q_NULLPTR) { //如果没有加载地图文件
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }
    QPointF qpointf = event->scenePos();		//获取鼠标移动时的坐标	
    for (int n = 0; n < gis->ns; n++) {
        if (fabs(gis->st[n].X() - qpointf.x()) < 8 && fabs(gis->st[n].Y() - qpointf.y()) < 8) {
            //以下提示信息必须使用fromLocal8Bit()，否则中文提示会显示乱码
            QtTipsDlgView dlg(QString::fromLocal8Bit("第") + QString::number(n + 1, 10, 0) + QString::fromLocal8Bit("个公交站点."));
            //dlg.setAttribute(Qt::WA_ShowModal,true); 若调用show()则需设置无边框,若调用dlg.exec()则不用此行，
            dlg.startTimer(1000);               //设置悬停显示时间为2秒，时间到自动关闭dlg
            QPointF m1 = qgv->mapToGlobal(QPoint(qpointf.x(), qpointf.y()));
            dlg.move(QPoint(m1.x(), m1.y()));
            dlg.exec();                         //显示站点提示信息
        }
    }
    for (int n = 0; n < gis->no; n++) {
        if (fabs(gis->org[n].X() - qpointf.x()) < 8 && fabs(gis->org[n].Y() - qpointf.y()) < 8) {
            QtTipsDlgView dlg(QString::fromLocal8Bit(gis->org[n].NAME()));
            dlg.startTimer(1000);
            QPointF m2 = qgv->mapToGlobal(QPoint(qpointf.x(), qpointf.y()));
            dlg.move(QPoint(m2.x(), m2.y()));
            dlg.exec();
        }
    }
    QGraphicsScene::mouseMoveEvent(event);		//回调基类鼠标事件
}
void MyScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //qDebug("*********MyScene::mousePressEvent***************");
    if (qgv == Q_NULLPTR || route == true) {      //未加载地图及显示查询结果时，不响应鼠标按下事件
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }
    QPointF qpointf = event->scenePos();	    //获取鼠标坐标	
    QList<QGraphicsItem*> listItem = items();
    int lb = 0;
    if (event->button() == Qt::LeftButton) { lb = 1; depart = true; }   //检查左键是否按下
    if (event->button() == Qt::RightButton) { lb = 2; arrive = true; }  //检查右键是否按下
    for (int i = listItem.length() - 1; i >= 0; i--) {
        MyItem* item = (MyItem*)listItem[i];
        if (item->f() == lb) {
            listItem.removeAt(i);
            delete item;
            break;
        }
    }
    addItem(new MyItem(qpointf.x(), qpointf.y(), lb));
    QGraphicsScene::mousePressEvent(event);		    //回调基类鼠标事件
}
void MyScene::stopLines(QGraphicsView* parnt) {     //加载地图站点和线路
        //按视图graphicsview大小设置scene显示区域大大小
    QSize viewsize = parnt->size();	            //取得graphicsview视图区域大小
    MyScene* scene;
    if (parnt->scene() != Q_NULLPTR)   delete parnt->scene();
    scene = new MyScene(parnt);                 //创建scene
    scene->setSceneRect(0, 0, viewsize.width(), viewsize.height());
    scene->qgv = parnt;
    //显示所有公交站点
    QBrush qbrush(QColor(255, 0, 0)); 
    QBrush qbrush1(QColor(0,255,0));//设置颜色
    QPen qpens(qbrush, 4, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //站点的笔
    for (int n = 0; n < gis->ns; n++) {
        scene->addEllipse(gis->st[n].X(), gis->st[n].Y(), 6, 6, qpens, qbrush);
    }
    //显示所有线路
    QPen qpenl(qbrush, 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //线路的笔
    for (int n = 0; n < gis->nl; n++) {
        LINE& line = gis->ls[n];
        int stops = line.NOFS();
        for (int m = 1; m < stops; m++) {
            STOP s = gis->st[line[m - 1]];
            STOP t = gis->st[line[m]];
            QLineF ql = QLineF(s.X(), s.Y(), t.X(), t.Y());
            scene->addLine(ql, qpenl);
        }
    }
    QPen qpenorg(qbrush1,5,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin);
    for (int n = 0; n < gis->numoforg; n++)
    {
        scene->addEllipse(gis->org[n].X(), gis->org[n].Y(), 6, 6, qpenorg, qbrush1);
    }
    parnt->setScene(scene);
    parnt->show();
}
/////////////////////////////////////////////////////////////////////////////////////
twnlt::twnlt(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    fl = Q_NULLPTR;
    gItem = Q_NULLPTR;
    win = Q_NULLPTR;
    m_Timer = new QTimer(this);
    m_Timer->setSingleShot(true);	                //定时器只执行一次
    connect(ui.action_open, SIGNAL(triggered(bool)), this, SLOT(loadmap()));
    connect(ui.action_exit, SIGNAL(triggered(bool)), this, SLOT(closewnd()));
    connect(ui.action_zszc, SIGNAL(triggered(bool)), this, SLOT(zszc()));
    connect(ui.action_zdjl, SIGNAL(triggered(bool)), this, SLOT(zdjl()));
    connect(ui.action_find, SIGNAL(triggered(bool)), this, SLOT(findinput()));
    //以下Lambda表达式可以用自动类型推导代替,或用非成员函数的地址代替
    connect(m_Timer, &QTimer::timeout, this, [=]() {
        QList<QGraphicsItem*> listItem = ui.graphicsView->scene()->items();
        deleteItems();      //查询结果显示时间一到，就删除场景的所有图元
        route = false;      //查询结果显示完毕，可以重新选取步行起点或终点      
        });
}
twnlt::~twnlt() {
    if (fl != Q_NULLPTR) {
        fl->hide();
        delete fl;
        fl = Q_NULLPTR;
        delete m_Timer;
        deleteItems();
        delete  gis;
    }
}
void twnlt::closewnd() {
    if (ui.action_exit->isChecked() == false) return; //鼠标点击一次触发两次，第二次触发直接返回
    ui.action_exit->setChecked(false);  //鼠标第一次触发设置状态为false,防止第2次触发进入
    if (fl != Q_NULLPTR) {
        fl->hide();
        delete fl;
        fl = Q_NULLPTR;
    }
    close();
}
void twnlt::closeEvent(QCloseEvent* event)
{
    if (fl != Q_NULLPTR) {
        fl->hide();
        delete fl;
        fl = Q_NULLPTR;
    }
}
void twnlt::loadmap() {

    if (ui.action_open->isChecked() == false) return; //鼠标点击触发两次，第二次触发直接返回
    ui.action_open->setChecked(false);  //鼠标第一次触发设置状态为false,防止第2次触发进入
    if (fl != Q_NULLPTR) {  //如果先前打开过站点及线路输入窗口
        fl->show();         //则直接显示该窗口
        return;
    }
    arrive = depart = false;  //此时未选取步行起点或终点
    fl = new QtWidgetsFL(); //如果以前没有打开过站点及线路输入窗口
    fl->setWindowFlags(Qt::WindowStaysOnTopHint); //设置最外层显示
    fl->myShow(ui.graphicsView);
}
void twnlt::findinput()
{
    if (ui.action_find->isChecked() == false) return;
    ui.action_find->setChecked(false);
    if (win != Q_NULLPTR)
    {
        win->show();
        return;
    }
    arrive = depart = false;
    QStringList q;
    for (int n = 0; n < gis->numoforg; n++)
    {
        const char* ch= gis->org[n].NAME();
        QString str = QString::fromLocal8Bit(ch);
        q << str;
    }
    win = new MainWindow(q);
    win->show();
}
void twnlt::deleteItems() { //删除场景的所有图元
    if (gItem == Q_NULLPTR) return;
    ui.graphicsView->scene()->removeItem(gItem);
    for (int i = gItem->childItems().size() - 1; i >= 0; i--) {
        QGraphicsItem* item = (gItem->childItems())[i];
        gItem->removeFromGroup(item);
        delete item;
    }
    delete gItem;
    gItem = Q_NULLPTR;
}
void twnlt::zszc() {
    //先计算最少转乘的路径,先获得起点坐标和终点坐标
    if (ui.action_zszc->isChecked() == false) return; //鼠标点击一次触发两次，第二次触发直接返回
    ui.action_zszc->setChecked(false);  //鼠标第一次触发设置状态为false,防止第2次触发进入
    QList<QGraphicsItem*> listItem;
    if ((depart && arrive) == false) return;//若没有选中步行起点和终点，则返回
    listItem = ui.graphicsView->scene()->items();
    MyItem* itemDepart = (MyItem*)listItem[0];
    MyItem* itemArrive = (MyItem*)listItem[1];
    if (itemDepart->f() != 1) {         //若不是步行起点，则交换
        itemDepart = (MyItem*)listItem[1];
        itemArrive = (MyItem*)listItem[0];
    }
    //开始组建图元组：用于显示转乘方案的路径
    QGraphicsEllipseItem* myEItem;
    QGraphicsLineItem* myLItem;
    MyScene* scene = (MyScene*)(ui.graphicsView->scene());
    QBrush qbrush(QColor(0, 0, 255));//设置颜色
    QPen qpens(qbrush, 4, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //站点的笔
    QPen qpenl(qbrush, 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //线路的笔
    route = true;               //进入查询路径显示期间，不响应步行起点与终点选取
    int c, n = 0;                //c为可行转乘方案数，n为最少转乘次数
    ROUTE r[100];               //一次查询，最多返回100条可行转乘方案
    for (int d = 0; d < itemDepart->c(); d++) {  //接近起点的所有公交站点
        int s = (*itemDepart)[d]; //获得起点站点编号s
        for (int a = 0; a < itemArrive->c(); a++) { //接近终点的所有公交站点
            int t = (*itemArrive)[a];               //获得终点站点编号t
            if (s == t) {                           //起点站和终点站相同不用转乘
                deleteItems();                      //删除先前的转乘方案路径显示
                gItem = new QGraphicsItemGroup();
                myEItem = new QGraphicsEllipseItem(itemDepart->x(), itemDepart->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(qbrush);
                gItem->addToGroup(myEItem);         //步行起点的位置
                myLItem = new QGraphicsLineItem(itemDepart->x(), itemDepart->y(), itemArrive->x(), itemArrive->y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);         //到步行终点的路径
                myEItem = new QGraphicsEllipseItem(itemArrive->x(), itemArrive->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(QBrush(QColor(255, 170, 00)));
                gItem->addToGroup(myEItem);         //步行终点的位置
                scene->addItem(gItem);
                ui.graphicsView->setScene(scene);
                continue;
            }
            c = GIS::tra.miniTran(s, t, n, r);        //得到的转乘方案数
            for (int m = 0; m < c; m++) {            //对于第m个转乘方案即route=r[m], 转乘次数都为n 
                deleteItems();
                gItem = new QGraphicsItemGroup();
                myEItem = new QGraphicsEllipseItem(itemDepart->x(), itemDepart->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(qbrush);
                gItem->addToGroup(myEItem);         //步行起点的位置
                int fr = s, to = t;                 //起始站fr与终点站to
                int fm, tm;                         //已乘线路fm与z转乘线路tm
                int bg, ed;                         //线路中的起始站点序号bg,终止站点序号ed
                myLItem = new QGraphicsLineItem(itemDepart->x(), itemDepart->y(), gis->st[s].X(), gis->st[s].Y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);         //到起点站
                if (n == 1 && r[m][0].S() == -1) {  //即从i路到i路(此时S()==-1)不用转乘
                    fm = r[m][0].F();               //已乘线路序号fm
                    bg = GIS::ls[fm].has(fr);       //起始站点在线路中的序号
                    ed = GIS::ls[fm].has(to);       //终止站点在线路中的序号
                    if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                    for (int y = bg; y < ed; y++)   //从起始站点下一序号到终止站点序号
                    {
                        fr = GIS::ls[fm][y];         //得到该站点序号对应的站点编号
                        to = GIS::ls[fm][y + 1];     //得到该站点序号对应的站点编号
                        myLItem = new QGraphicsLineItem(GIS::st[fr].X(), GIS::st[fr].Y(), GIS::st[to].X(), GIS::st[to].Y());
                        myLItem->setPen(qpenl);
                        gItem->addToGroup(myLItem); //到下一站的路径
                    }
                }
                else {
                    for (int y = 0; y < n; y++)     //对于每个转乘
                    {
                        fm = r[m][y].F();           //对于每个转乘的起始线路
                        bg = GIS::ls[fm].has(fr);
                        to = r[m][y].S();           //对于起始线路的转乘站点
                        ed = GIS::ls[fm].has(to);
                        if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                        for (int u = bg; u < ed; u++)  //从起始站点下一序号到终止站点序号
                        {
                            int ff = GIS::ls[fm][u];    //得到该站点序号对应的站点编号
                            int tt = GIS::ls[fm][u + 1];  //得到该站点序号对应的站点编号
                            myLItem = new QGraphicsLineItem(GIS::st[ff].X(), GIS::st[ff].Y(), GIS::st[tt].X(), GIS::st[tt].Y());
                            myLItem->setPen(qpenl);
                            gItem->addToGroup(myLItem); //到下一站的路径
                        }
                        fr = to;                        //作为下一起点
                    }
                    fm = r[m][n - 1].T();                 //对于最后乘坐的线路
                    bg = GIS::ls[fm].has(fr);
                    ed = GIS::ls[fm].has(t);
                    if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                    for (int u = bg; u < ed; u++)       //从起始站点下一序号到终止站点序号
                    {
                        int ff = GIS::ls[fm][u];        //得到该站点序号对应的站点编号
                        int tt = GIS::ls[fm][u + 1];    //得到该站点序号对应的站点编号
                        myLItem = new QGraphicsLineItem(GIS::st[ff].X(), GIS::st[ff].Y(), GIS::st[tt].X(), GIS::st[tt].Y());
                        myLItem->setPen(qpenl);
                        gItem->addToGroup(myLItem);     //到下一站的路径
                    }
                }
                myLItem = new QGraphicsLineItem(GIS::st[t].X(), GIS::st[t].Y(), itemArrive->x(), itemArrive->y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);             //到步行终点的路径
                myEItem = new QGraphicsEllipseItem(itemArrive->x(), itemArrive->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(QBrush(QColor(255, 170, 00)));
                gItem->addToGroup(myEItem);             //步行终点的位置
                scene->addItem(gItem);
                ui.graphicsView->setScene(scene);
            }
        }
    }
    this->m_Timer->start(5000);  //展示查询的路径结果5秒
}
void twnlt::zdjl() {
    //先计算最短距离的路径,先获得起点坐标和终点坐标
    if (ui.action_zdjl->isChecked() == false) return; //鼠标点击一次触发两次，第二次出发直接返回
    ui.action_zdjl->setChecked(false);  //鼠标第一次出发，设置状态为false,防止第2次出发进入
    QList<QGraphicsItem*> listItem;
    if ((depart && arrive) == false) return;
    listItem = ui.graphicsView->scene()->items();
    MyItem* itemDepart = (MyItem*)listItem[0];
    MyItem* itemArrive = (MyItem*)listItem[1];
    if (itemDepart->f() != 1) { //若不是起点，则交换
        itemDepart = (MyItem*)listItem[1];
        itemArrive = (MyItem*)listItem[0];
    }
    //开始组建图元组：用于显示转乘方案的路径
    QGraphicsEllipseItem* myEItem;
    QGraphicsLineItem* myLItem;
    MyScene* scene = (MyScene*)(ui.graphicsView->scene());
    QBrush qbrush(QColor(0, 0, 255));//设置颜色
    QPen qpens(qbrush, 4, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //站点的笔
    QPen qpenl(qbrush, 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin); //线路的笔
    route = true;                       //进入查询路径显示期间，不响应步行起点与终点选取
    int c = 0;                          //c为可行线路数
    double dist = 0;                    //dist为最短距离
    ROUTE r[100];
    for (int d = 0; d < itemDepart->c(); d++) {  //接近起点的所有公交站点
        int s = (*itemDepart)[d];       //获得起点站点编号s
        for (int a = 0; a < itemArrive->c(); a++) {  //接近终点的所有公交站点
            int t = (*itemArrive)[a];   //获得终点站点编号t
            if (s == t) {               //起点站和终点站相同不用转乘
                deleteItems();          //删除先前的转乘方案路径显示
                gItem = new QGraphicsItemGroup();
                myEItem = new QGraphicsEllipseItem(itemDepart->x(), itemDepart->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(qbrush);
                gItem->addToGroup(myEItem);//步行起点的位置显示
                myLItem = new QGraphicsLineItem(itemDepart->x(), itemDepart->y(), itemArrive->x(), itemArrive->y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);//到步行终点的路径
                myEItem = new QGraphicsEllipseItem(itemArrive->x(), itemArrive->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(QBrush(QColor(255, 170, 00)));
                gItem->addToGroup(myEItem);//步行终点的位置
                scene->addItem(gItem);
                ui.graphicsView->setScene(scene);
                continue;
            }
            c = GIS::tra.miniDist(s, t, dist, r);  //得到的转乘方案数c
            for (int m = 0; m < c; m++) {   //对于第m个转乘方案即route=r[m],最短距离都为dist 
                deleteItems();
                gItem = new QGraphicsItemGroup();
                myEItem = new QGraphicsEllipseItem(itemDepart->x(), itemDepart->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(qbrush);
                gItem->addToGroup(myEItem);     //步行起点的位置显示
                int fr = s, to = t;             //起始站fr与终点站to
                int fm, tm;                     //已乘线路fm与z转乘线路tm
                int bg, ed;                     //线路中的起始站点序号bg,终止站点序号ed
                myLItem = new QGraphicsLineItem(itemDepart->x(), itemDepart->y(), gis->st[s].X(), gis->st[s].Y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);     //到起点站的路径显示
                int n = r[m];                   //当前route中的转乘次数
                if (n == 1 && r[m][0].S() == -1) { //即从i路到i路(此时S()==-1)不用转乘
                    fm = r[m][0].F();           //已乘线路序号fm
                    bg = GIS::ls[fm].has(fr);   //起始站点在线路中的序号
                    ed = GIS::ls[fm].has(to);   //终止站点在线路中的序号
                    if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                    for (int y = bg; y < ed; y++) //从起始站点下一序号到终止站点序号
                    {
                        fr = GIS::ls[fm][y];    //得到该站点序号对应的站点编号
                        to = GIS::ls[fm][y + 1];//得到该站点序号对应的站点编号
                        myLItem = new QGraphicsLineItem(GIS::st[fr].X(), GIS::st[fr].Y(), GIS::st[to].X(), GIS::st[to].Y());
                        myLItem->setPen(qpenl);
                        gItem->addToGroup(myLItem);//到下一站
                    }
                }
                else {
                    for (int y = 0; y < n; y++) //对于每个转乘画出路径
                    {
                        fm = r[m][y].F();       //对于每个转乘的起始线路
                        bg = GIS::ls[fm].has(fr);
                        to = r[m][y].S();       //对于起始线路的转乘站点
                        ed = GIS::ls[fm].has(to);
                        if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                        for (int u = bg; u < ed; u++)   //从起始站点下一序号到终止站点序号
                        {
                            int ff = GIS::ls[fm][u];    //得到该站点序号对应的站点编号
                            int tt = GIS::ls[fm][u + 1];//得到该站点序号对应的站点编号
                            myLItem = new QGraphicsLineItem(GIS::st[ff].X(), GIS::st[ff].Y(), GIS::st[tt].X(), GIS::st[tt].Y());
                            myLItem->setPen(qpenl);
                            gItem->addToGroup(myLItem); //到下一站的路径
                        }
                        fr = to;                        //作为下一起点
                    }
                    fm = r[m][n - 1].T();               //对于最后乘坐的线路
                    bg = GIS::ls[fm].has(fr);
                    ed = GIS::ls[fm].has(t);
                    if (bg > ed) { tm = bg; bg = ed; ed = tm; }
                    for (int u = bg; u < ed; u++)       //从起始站点下一序号到终止站点序号
                    {
                        int ff = GIS::ls[fm][u];        //得到该站点序号对应的站点编号
                        int tt = GIS::ls[fm][u + 1];    //得到该站点序号对应的站点编号
                        myLItem = new QGraphicsLineItem(GIS::st[ff].X(), GIS::st[ff].Y(), GIS::st[tt].X(), GIS::st[tt].Y());
                        myLItem->setPen(qpenl);
                        gItem->addToGroup(myLItem);     //到下一站的路径
                    }
                }
                myLItem = new QGraphicsLineItem(GIS::st[t].X(), GIS::st[t].Y(), itemArrive->x(), itemArrive->y());
                myLItem->setPen(qpenl);
                gItem->addToGroup(myLItem);             //到步行终点的路径
                myEItem = new QGraphicsEllipseItem(itemArrive->x(), itemArrive->y(), 6, 6);
                myEItem->setPen(qpens);
                myEItem->setBrush(QBrush(QColor(255, 170, 00)));
                gItem->addToGroup(myEItem);             //步行终点的位置显示
                scene->addItem(gItem);
                ui.graphicsView->setScene(scene);
            }
        }
    }
    this->m_Timer->start(5000);  //展示查询的路径结果5秒
}