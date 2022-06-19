#define _CRT_SECURE_NO_WARINGS
#include"logiclay.h"
#include<math.h>
#include<stdio.h>
STOP* GIS::st = 0;//公交站 
LINE* GIS::ls = 0;//公交线路 
int GIS::ns = 0;// 公交站数 
int GIS::nl = 0;//公交线路数 
int GIS::obs = 0;//GIS对象数量 
TMAP GIS::raw;//原始转移矩阵 
TMAP GIS::tra; //闭包转移矩阵 

STOP::STOP(int n, int x, int y) :numb(n), x(x), y(y) {}

int& STOP::X() {
	return x;
}
int& STOP::Y() {
	return y;
}
int& STOP::N() {
	return numb;
}
LINE::LINE(int n, int c, int* stop) :numb(n), stop(c ? new int[c] : nullptr), nofs(stop ? c : 0) {
	if (LINE::stop == nullptr && nofs != 0)throw "LINE类内存分配错误！";
	for (int x = 0; x < nofs; x++)LINE::stop[x] = stop[x];
}
LINE::LINE(const LINE& r) : numb(r.numb), stop(r.nofs ? new int[r.nofs] : nullptr), nofs(stop ? r.nofs : 0) {
	if (stop == nullptr && r.nofs != 0)throw"LINE类内存分配错误！";
	for (int x = 0; x < nofs; x++)stop[x] = r.stop[x];
}
LINE::LINE(LINE&& r)noexcept :numb(r.numb), stop(r.stop), nofs(r.nofs) {
	(int&)(r.numb) = (int&)(r.nofs) = 0;
	(int*&)(r.stop) = nullptr;
}
LINE& LINE::operator=(const LINE& r) {
	if (this == &r)return *this;
	if (stop) {
		delete[]stop;
	}
	(int&)numb = r.numb;
	(int*&)stop = new int[r.nofs];
	if (stop == nullptr)throw"Line类operator=操作错误！";
	(int&)nofs = stop ? r.nofs : 0;
	for (int x = 0; x < nofs; x++)stop[x] = r.stop[x];
	return *this;
}
LINE& LINE::operator=(LINE&& r)noexcept {
	if (this == &r)return *this;
	if (stop) {
		delete[] stop;
	}
	(int&)numb = r.numb;
	(int*&)stop = r.stop;
	(int&)nofs = r.nofs;
	(int&)(r.numb) = (int&)(r.nofs) = 0;
	(int*&)(r.stop) = nullptr;
	return *this;
}
int LINE::has(int s)const {
	for (int x = 0; x < nofs; x++)
		if (stop[x] == s)return x;
	return -1;
}
int LINE::cross(const LINE& b)const {//若线路相交，则返回1 
	if (this == &b)return 0;
	for (int x = 0; x < nofs; x++)if (b.has(stop[x]) != -1)return 1;
	return 0;
}
LINE::operator int()const {//取线路编号 
	return numb;
}
int LINE::NOFS()const {//取站点数目 
	return nofs;
}
double LINE::dist(int b, int e)const {//从站点b到站点e的距离 
	double d;
	int bi, ei;//两个站点编号b,e对应的站次 
	int x1, x2, y1, y2, w;
	if (bi = has(b) == -1)throw"计算站间距离没有找到站；";
	if (ei = has(e) == -1)throw"计算站间距离没有找到站！";
	if (bi > ei) {
		b = ei;
		ei = bi;
		bi = b;
	}
	for (d = 0, b = bi; b < ei; b++) {
		x1 = GIS::st[w = stop[b]].X();//由当前站点编号得到其位置坐标x,y 
		y1 = GIS::st[w].Y();
		x2 = GIS::st[e = stop[b + 1]].X() - x1;//到下一站点x,y轴的距离 
		y2 = GIS::st[e].Y() - y1;
		d += sqrt(double(x2 * x2 + y2 * y2));//到下一站的距离 
	}
	return d;
}
int& LINE::operator[](int x) {//到第x站的站点编号 
	return stop[x];
}
LINE::~LINE()noexcept {
	if (stop) {
		delete[] stop;
		(int*&)stop = 0;
		(int&)numb = (int&)nofs = 0;
	}
}
TRAN::TRAN(int from, int to, int stop) :from(from), to(to), stop(stop) {}
int TRAN::operator==(const TRAN& t)const {
	return from == t.from && to == t.to && stop == t.stop;
}

int& TRAN::F() {
	return from;
}

int& TRAN::T() {
	return to;
}

int& TRAN::S() {
	return stop;
}

ROUTE::ROUTE(TRAN* tran, int noft) :tran(noft ? new TRAN[noft] : nullptr), noft(tran ? noft : 0) {
	if (ROUTE::tran == nullptr && noft != 0)throw"ROUTR 构造分配内存错误！";
	for (int x = 0; x < noft; x++)ROUTE::tran[x] = tran[x];
}

ROUTE::ROUTE(const TRAN& t) : tran(new TRAN[1]), noft(tran ? 1 : 0) {
	if (tran == nullptr)throw"ROUTE 构造分配内存错误！";
	if (tran)*tran = t;
}

ROUTE::ROUTE(const ROUTE& r) : tran(r.noft ? new TRAN[r.noft] : nullptr), noft(tran ? r.noft : 0) {
	if (tran == nullptr && r.noft != 0)throw"ROUTE 构造分配内存错误！";
	for (int x = 0; x < noft; x++)tran[x] = r.tran[x];
}
ROUTE::ROUTE(ROUTE&& r)noexcept :tran(r.tran), noft(r.noft) {
	(TRAN*&)(r.tran) = nullptr;
	(int&)(r.noft) = 0;
}

ROUTE::~ROUTE()noexcept {
	if (tran) {
		delete[] tran;
		(TRAN*&)tran = nullptr;
		*(int*)&noft = 0;
	}
}
int ROUTE::print()const {
	for (int x = 0; x < noft; x++)
		if (tran[x].S() == -1)printf("\t乘坐公交%d直接到达\n", tran[x].F() + 1);
		else printf("\t公交%d转%d经站%d\n", tran[x].F() + 1, tran[x].T() + 1, tran[x].S() + 1);
	return noft;
}
ROUTE::operator int()const {
	return noft;
}
ROUTE ROUTE::operator*()const {//去掉重复转置 
	int nn = noft;
	TRAN* t = new TRAN[noft];
	if (t == nullptr)throw"ROUTE::operator*()分配内存错误！";
	for (int x = 0; x < nn; x++)t[x] = tran[x];
	for (int x = 0; x < nn - 1; x++)
		for (int y = x + 1; y < nn; y++) {
			if (t[x].S() == t[y].S() && t[x].F() == t[y].T()) {//转乘重复了 
				for (int m = x, n = y + 1; n < nn; n++, m++)t[m] = t[n];
				nn -= (y + 1 - x);
				y = x;
			}
		}
	ROUTE r(t, nn);
	delete[]t;
	return r;
}
int ROUTE::operator==(const ROUTE& r)const {
	int m = 1;
	if (noft != r.noft)return 0;
	for (int x = 0; x < noft; x++) {
		if (tran[x] == r.tran[x])continue;
		m = 0;
		break;
	}
	return m;
}
TRAN& ROUTE::operator[](int x) {//得到路径上的转乘x 
	if (x<0 || x>noft)throw"ROUTE类转乘下标越界！";
	return tran[x];
}

ROUTE ROUTE::operator+(const ROUTE& r)const {
	int x, y;
	ROUTE s;
	if (noft == 0)return *this;
	if (r.noft == 0)return r;
	if (tran[noft - 1].T() != r.tran[0].F())throw"Route can be concated!";
	try {
		(TRAN*&)(s.tran) = new TRAN[noft + r.noft];
	}

	/**********************************117*********************************/

	catch (...) {
		throw"ROUTE构造TRAN分配内存错误!";
	}
	(int&)(s.noft) = s.tran ? noft + r.noft : 0;
	for (x = 0; x < noft; x++) s.tran[x] = tran[x];
	for (y = 0; y < r.noft; y++) s.tran[x++] = r.tran[y];
	return *s;
}

ROUTE& ROUTE::operator=(const ROUTE& r) {
	if (this == &r) return *this;
	if (tran) delete[]tran;
	try { (TRAN*&)tran = new TRAN[r.noft]; }
	catch (...) {
		throw"Memory allocation for ROUTE construction error!";
	}
	(int&)noft = tran ? r.noft : 0;
	for (int x = 0; x < noft; x++) tran[x] = r.tran[x];
	return *this;
}

ROUTE& ROUTE::operator=(ROUTE&& r)noexcept {
	if (this == &r) return *this;
	if (tran) delete[]tran;
	(TRAN*&)tran = r.tran;
	(int&)noft = r.noft;
	(TRAN*&)(r.tran) = nullptr;
	(int&)(r.noft) = 0;
	return *this;
}

ROUTE& ROUTE::operator+=(const ROUTE& r) { return *this = *this + r; }
NODE::NODE(ROUTE* p, int n) :p(n ? new ROUTE[n] : nullptr) {
	if (NODE::p == nullptr && n != 0) throw"NODE类构造分配内存错误!";
	for (int x = 0; x < n; x++) NODE::p[x] = p[x];
}

NODE::NODE(int n) : p(n ? new ROUTE[n] : nullptr), n(p ? n : 0) {
	if (p == nullptr && n != 0) throw"NODE类构造分配内存错误!";
}

NODE::NODE(const NODE& n) : p(n.n ? new ROUTE[n.n] : nullptr), n(p ? n.n : 0) {
	if (p == nullptr && n.n != 0) throw"NODE类构造分配内存错误!";
	for (int x = 0; x < NODE::n; x++) p[x] = n.p[x];
}

NODE::NODE(NODE&& n)noexcept :p(n.p), n(n.n) {
	(ROUTE*&)(n.p) = nullptr;
	(int&)n.n = 0;
}

NODE NODE::operator*()const {
	int n = NODE::n;
	if (n == 0) return *this;
	ROUTE* t = new ROUTE[n];
	if (t == nullptr) throw"NODE::OPERATOR*()为ROUTE分配内存错误!";
	for (int x = 0; x < n; x++) t[x] = p[x];
	for (int x = 0; x < n + 1; x++)
		for (int y = x + 1; y < n; y++) {
			if (t[x] == t[y])
			{
	/*这里有问题*/			for (int m = x + 1, n = y + 1; n < NODE::n - 1; n++, m++) t[m] = t[n];
				n -= (y - x);
				y = x;
			}
		}
	NODE r(t, n);
	try {
		if (t != nullptr) delete[]t; t = nullptr;
	}


	/*********************118*********************************************/
	catch (...) {
		throw"initializing failed!";
	}
	return r;
}

NODE NODE::operator+(const ROUTE& n)const {
	NODE r(NODE::n + 1);
	for (int x = 0; x < NODE::n; x++) r.p[x] = *p[x];
	r.p[NODE::n] = n;
	return *r;
}

NODE NODE::operator+(const NODE& n)const {
	if (NODE::n == 0) return n;
	if (n.n == 0) return *this;
	NODE r(NODE::n + n.n);
	for (int x = 0; x < n.n; x++) r.p[x] = *p[x];
	for (int x = 0; x < n.n; x++) r.p[x + NODE::n] = *n.p[x];
	return *r;
}

NODE NODE::operator*(const NODE& n)const {
	if (NODE::n == 0) return *this;
	if (n.n == 0) return 0;
	NODE r(NODE::n * n.n);
	int m, f, h, k = 0;
	for (int x = 0; x < NODE::n; x++) //当前节点的x=4,y=0,k=4时异常
		for (int y = 0; y < n.n; y++) {
			if (p[x][-1 + p[x]].T() != n.p[y][0].F())
				throw"不满足转乘条件!";
			try {
				r.p[k] = p[x] + n.p[y]; //ROUTE的连接运算
			}
			catch (const char* e) {
				const char* p = e;
			}
			k++;
		}
	return *r;
}

NODE& NODE::operator=(const NODE& n) {
	if (this == &n) return *this;
	if (p) delete[]p;
	(ROUTE*&)p = new ROUTE[n.n];
	if (p == nullptr) throw"NODE赋值为ROUTE分配内存错误!";
	(int&)(NODE::n) = n.n;
	(ROUTE*&)(n.p) = nullptr;
	(int&)n.n = 0;
	return *this;
}

NODE& NODE::operator=(NODE&& n)noexcept {
	if (this == &n)return *this;
	if (p)delete[]p;
	(ROUTE*&)p = n.p;
	(int&)(NODE::n) = n.n;
	(ROUTE*&)(n.p) = nullptr;
	(int&)(n.n) = 0;
	return *this;
}

NODE& NODE::operator+=(const ROUTE& n) {
	return *this = *this + n;
}

NODE& NODE::operator+=(const NODE& n) {
	return *this = *this + n;
}

NODE& NODE::operator*=(const NODE& n) {

	/****************************119***********************************/
	return *this = *this * n;
}

ROUTE& NODE::operator[](int x) {
	if (x < 0 || x >= n) throw"NODE::operator[](int x)下标错误!";
	return p[x];
}

NODE::operator int& () { return n; }
NODE::~NODE()noexcept {
	if (p) {
		delete[]p;
		(ROUTE*&)p = nullptr;
		(int&)n = 0;
	}
}

void NODE::print()const { for (int m = 0; m < n; m++) p[m].print(); }

TMAP::TMAP(int r, int c) :p(r&& c ? new NODE[r * c] : nullptr), r(p ? r : 0), c(p ? c : 0) {
	if (TMAP::p == nullptr && r != 0 && c != 0)
		throw"TMAP分配内存错误!";
}

TMAP::TMAP(const TMAP& a) : p((a.r&& a.c) ? new NODE[a.r * a.c] : nullptr), r(p ? a.r : 0), c(p ? a.c : 0) {
	if (p == nullptr && a.r != 0 && a.c != 0)
		throw"TMAP分配内存错误!";
	for (int k = r * c - 1; k >= 0; k--) p[k] = a.p[k];
}

TMAP::TMAP(TMAP&& a)noexcept :p(a.p), c(a.c), r(a.r) {
	(NODE*&)(a.p) = nullptr;
	(int&)(a.r) = (int&)(a.c) = 0;
}

TMAP::~TMAP() {
	if (p)
		delete[]p;
	(NODE*&)p = nullptr;
	(int&)r = (int&)c = 0;
}

int TMAP::notZero()const {
	for (int x = r * c - 1; x >= 0; x--) if (p[x].operator int& () == 0) return 0;
	return 1;
}

int& TMAP::operator()(int x, int y) {
	if (x < 0 || x >= r) throw"TMAP行下表越界错误!";
	if (y < 0 || y >= c) throw"TMAP列下表越界错误!";
	return p[x * c + y];
}

NODE* TMAP::operator[](int r) {
	if (r<0 || r>TMAP::r) throw"TMAP行下标越界错误!";
	return p + r * c;
}

TMAP& TMAP::operator=(const TMAP& a) {
	if (this == &a) return *this;
	if (p) delete[]p;
	(NODE*&)p = new NODE[a.r * a.c];
	if (p == nullptr) throw"TMAP为NODE分配内存错误!";
	(int&)r = a.r;
	(int&)c = a.c;
	for (int k = r * c - 1; k >= 0; k--) p[k] = a.p[k];
	return *this;
}

TMAP& TMAP::operator=(TMAP&& a) {
	if (this == &a) return *this;
	if (p) delete[]p;
	(NODE*&)p = a.p;
	(int&)r = a.r;
	(int&)c = a.c;

	/*******************************120**********************************/
	(NODE*&)(a.p) = nullptr;
	(int&)(a.r) = (int&)(a.c) = 0;
	return *this;
}

TMAP TMAP::operator*(const TMAP& a)const {
	if (c != a.r) throw"TMAP矩阵不能相乘!";
	int t, m, u, v, w, x, y, z;
	TMAP s(r, a.c); //每个节点皆为空线路
	for (int h = 0; h < r; h++)
		for (int j = a.c - 1; j >= 0; j--) {
			if (h == j) continue;
			t = h * s.c + j;
			for (int k = 0; k < c; k++)
				if (k != h && k != j)
					s.p[t] += p[h * c + k] * a.p[k * a.c + j];
		}
	return s;
}
TMAP TMAP::operator+(const TMAP& a)const {
	if (r != a.r && c != a.c)throw"TMAP矩阵不能相加!";
	TMAP s(*this);
	for (int h = r * c - 1; h >= 0; h--) s.p[h] += a.p[h];
	return s;
}

TMAP& TMAP::operator+=(const TMAP& a) { return *this = *this + a; }

TMAP& TMAP::operator*=(const TMAP& a) { return *this = *this * a; }

TMAP& TMAP::operator()(int ro, int co, const ROUTE& a) {
	p[ro * c + co] += a;
	return *this;
}

//根据起点站s和终点站t找到最少转成次数noft的若干路线r，返回线路数
int TMAP::miniTran(int s, int t, int& notf, ROUTE(&r)[100])const {
	int k, u, v, w, x, y, z;      //z:返回实际最少转乘线路数
	int b = 0, e = 0;             //包含起点s的起始线路数b，包含终点t的线路数e
	int nott[100]{};              //对应规划路线r的转乘次数
	int bls[20], els[20];         //bls包含s的起始线路，els包含t的线路
	NODE rou;
	for (z = 0; z < GIS::nl; z++) {      //
		if (GIS::ls[z].has(s) != -1) if (b < 20) bls[b++] = z;
		if (GIS::ls[z].has(s) != -1) if (e < 20) els[e++] = z;
	}
	for (x = z = 0; x < b; x++)
		for (y = 0; y < e; y++) {
			rou = GIS::tra[bls[x]][els[y]];   //得到两路线的所有转乘线路
			w = GIS::tra(bls[x], els[y]);
			if (w == 0) continue;           //转成线路数==0
			for (v = 0; v < w; v++) {
				u = rou[v];          //线路得到转乘次数
				if (z == 0 || u < nott[0]) {  //若nott为空或转乘次数比nott[0]小
					nott[0] = u;
					r[0] = rou[v];
					z = 1;
				}
				if (u == nott[0]) {  //和已有的线路转乘次数相同时,插入
					if (z == 100) return z;
					nott[z] = u;
					r[z] = rou[v];
					z++;
				}


				/***********************************************************/
			}
		}
	notf = nott[0];                                       //nott[0]到nott[z-1]的转乘次数都相同
	return z;                                             //返回最少转乘线路数
}
//起站b,终站e，使用路线r的距离
double TMAP::getDist(int b, int e, ROUTE& r) {
	int x, y;
	double d = 0;
	if (1 == r && r[0].F() == r[0].T()) {                 //乘坐线路=转乘线路：不用转乘
		d = GIS::ls[r[0].F()].dist(b, e);
		return d;
	}
	d = GIS::ls[r[0].F()].dist(b, r[0].S());
	y = (int)r - 1;                                      //r的转乘次数-1
	for (x = 0; x < y; x++)
		d += GIS::ls[r[x].T()].dist(r[x].S(), r[x + 1].S());
	d += GIS::ls[r[y].T()].dist(r[y].S(), e);
	return d;
}
//根据起点站s和终点站t找到最短距离dist的若干线路r，返回实际线路数
int TMAP::miniDist(int s, int t, double& dist, ROUTE(&r)[100])const {
	int k, u, v, w, x, y, z;
	int b = 0, e = 0;                                    //s：包含站点s（数组下标）的起始线路数（存放于bls）
	double dot[100]{};                                   //对应r的转乘距离
	int bls[20], els[20];                                //e：包含站点t（站点数组下标）的起始线路数（存放于els）
	NODE rou;
	for (z = 0; z < GIS::nl; z++) {                      //寻找相关公交线路下标
		if (GIS::ls[z].has(s) != -1)if (b < 20)bls[b++] = z;
		if (GIS::ls[z].has(t) != -1)if (e < 20)els[e++] = z;
	}
	for (x = z = 0; x < b; x++)                          //b个起始站点
		for (y = 0; y < e; y++) {                        //e个到达站点
			rou = GIS::tra[bls[x]][els[y]];              //得到两条线路的所有转乘线路
			w = GIS::tra(bls[x], els[y]);                //得到两条线路的所有转乘线路数
			if (w == 0)continue;                         //本次起始站点的转乘线路数w==0
			for (v = 0; v < w; v++) {
				u = TMAP::getDist(s, t, rou[v]);         //得到转乘距离
				if (z == 0 || u < dot[0]) {              //若dot为空或转乘次数比dot[0]小
					dot[0] = u;
					r[0] = rou[v];
					z = 1;
				}
				if (u == dot[0]) {                       //和已有线路转成距离相同时，插入
					if (z == 100)return z;
					dot[z] = u;
					r[z] = rou[v];
					z++;
				}
			}
		}
	dist = dot[0];                                       //升序插入：dot[0]到dot[z-1]存储的距离相同
	return z;                                            //z个乘坐方案
}
void TMAP::print()const {
	for (int x = 0; x < r; x++)
		for (int y = 0; y < c; y++) {
			printf("Node(%d,%d)有 %d条路径：\n", x, y, (int)(p[x * c + y]));
			p[x * c + y].print();
		}
}
GIS::GIS() {
	obs++;
}
GIS::GIS(const char* flstop, const char* flline) {
	int m, n, p, q, r, * s, * t;
	FILE* fs, * fl;
	fs = fopen(flstop, "r");
	fl = fopen(flline, "r");
	if (fs == 0 || fl == 0)throw"File open error!";
	fscanf(fs, "%d", &ns);
	st = new STOP[ns];
	for (m = 0; m < ns; m++) {
		fscanf(fs, "%d%d", &st[m].X(), &st[m].Y());
		st[m].N() = m + 1;                              //公交线路编号从1开始
	}
	fclose(fs);
	fscanf(fl, "%d", &nl);
	s = new int[nl];                                     //每条线路的站点数
	t = new int[100];                                   //每条线路的站点数不超过100
	for (m = 0; m < nl; m++)fscanf(fl, "%d", &s[m]);
	*(LINE**)&ls = new LINE[nl];
	for (m = 0; m < nl; m++) {
		for (n = 0; n < s[m]; n++) {
			fscanf(fl, "%d", &t[n]);
			t[n]--;
		}
		ls[m] = LINE(m + 1, s[m], t);
	}
	fclose(fl);
	for (m = 0; m < nl; m++) {                          //构造raw
		for (p = n = 0; n < nl; n++)
			if (m != n)p += GIS::ls[m].cross(GIS::ls[n]);
		if (p == 0) {
			printf("公交%d没有和任何线路相交\n", m + 1);
			throw"有不相交的公交线路";
		}
	}
	TMAP ra(nl, nl);
	ROUTE a;
	TRAN* u = new TRAN[100];
	for (m = 0; m < nl; m++)
		for (n = 0; n < nl; n++) {
			if (m == n) {
				u[0] = TRAN(m, n, -1);                 //本线路自身可在任意一点转移
				a = ROUTE(&u[0], 1);                   //本线路只有一次转乘
				ra(m, n, a);
				continue;
			}
			p = 0;                                     //公交线路交点个数
			for (q = GIS::ls[m].NOFS() - 1; q >= 0; q--) {
				r = GIS::ls[m][q];
				if (GIS::ls[n].has(r) != -1) {         //每个交点产生一个转成方式：新路线
					u[p] = TRAN(m, n, r);
					a = ROUTE(&u[p++], 1);             //线路只有一次转乘
					ra(m, n, a);
				}
			}
		}
	tra = raw = ra;
	for (n = 2; n < nl; n++) {                         //构造闭包转乘矩阵
		raw *= ra;
		tra += raw;
	}
	raw = ra;                                          //保存原始转乘矩阵
	delete s;
	delete t;
	delete[]u;
	obs++;
}
GIS::~GIS() {
	obs--;
	if (obs) {
		return;
	}
	if (st) {
		delete[]st;
		*(STOP**)&st = nullptr;
	}
	if (ls) {
		delete[]ls;
		*(LINE**)&ls = nullptr;
	}
}
//根据步行起点和终点找到最少转乘次数n的若干路线r，返回路线数
int GIS::miniTran(int fx, int fy, int tx, int ty, int& f, int& t, int& n, ROUTE(&r)[100]) {
	int m;
	double df, tf, dt, tt;
	f = 0;                                           //设离步行起点最近的站点编号为f
	df = sqrt(st[0].X() - fx) * (st[0].X() - fx) + (st[0].Y() - fy) * (st[0].Y() - fy);
	t = 0;                                           //设离步行终点最近的站点编号为t
	dt = sqrt((st[0].X() - tx) * (st[0].X() - tx) + (st[0].Y() - ty) * (st[0].Y() - ty));
	for (m = 1; m < GIS::ns; m++) {                  //搜索离步行起点或者步行终点最近的站点编号
		tf = sqrt((st[m].X() - fx) * (st[m].X() - fx) + (st[m].Y() - fy) * (st[m].Y() - fy));
		if (df > tf) {                               //离步行起点最近的站点编号存在f中
			df = tf;
			f = m;
		}
		tt = sqrt((st[m].X() - tx) * (st[m].X() - tx) + (st[m].Y() - ty) * (st[m].Y() - ty));
		if (dt > tt) {                              //离步行终点最近的结点编号存在t中
			dt = tt;
			t = m;
		}
	}
	if (f == t) {                                   //步行起点编号和步行终点编号相同，不用乘车
		return 0;
	}
	return GIS::tra.miniTran(f, t, n, r);
}
//根据步行起点和步行终点找到最短距离d的若干线路r，返回线路数
int GIS::miniDist(int fx, int fy, int tx, int ty, int& f, int& t, double& d, ROUTE(&r)[100]) {
	int m;
	double df, tf, dt, tt;
	f = 0;                                          //设离步行起点最近的站点编号为f
	df = sqrt(st[0].X() - fx) * (st[0].X() - fx) + (st[0].Y() - fy) * (st[0].Y() - fy);
	t = 0;                                          //设离步行终点最近的站点编号为t
	dt = sqrt((st[0].X() - tx) * (st[0].X() - tx) + (st[0].Y() - ty) * (st[0].Y() - ty));
	for (m = 1; m < GIS::ns; m++) {
		tf = sqrt((st[m].X() - fx) * (st[m].X() - fx) + (st[m].Y() - fy) * (st[m].Y() - fy));
		if (df > tf) {                              //离步行起点最近的站点编号存在f中
			df = tf;
			f = m;
		}
		tt = sqrt((st[m].X() - tx) * (st[m].X() - tx) + (st[m].Y() - ty) * (st[m].Y() - ty));
		if (dt > tt) {                              //离步行终点最近的结点编号存在t中
			dt = tt;
			t = m;
		}
	}
	if (f == t) {                                   //步行起点编号和步行终点编号相同，不用乘车
		return 0;
	}
	return GIS::tra.miniDist(f, t, d, r);
}

