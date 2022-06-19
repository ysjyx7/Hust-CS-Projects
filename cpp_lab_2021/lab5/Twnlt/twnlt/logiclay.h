#pragma once
class STOP {                                                //����һ������վ��
	int numb;                                               //���й���վ����
	int x, y;                                               //����վ������
public:
	STOP(int n = 0, int x = 0, int y = 0);
	virtual int& X();
	virtual int& Y();
	virtual int& N();
};
class LINE {                                                //����һ��������·
	const int numb;                                         //������·��Ŵ�1��ʼ
	int* const stop;                                        //������·������վ����
	const int nofs;                                         //������·��վ������
public:
	LINE(int numb = 0, int nofs = 0, int* stop = nullptr);
	LINE(const LINE& r);
	LINE(LINE&& r)noexcept;
	LINE& operator=(const LINE& r);
	LINE& operator=(LINE&& r)noexcept;
	virtual int has(int s)const;                            //������վ����s���򷵻���·�е�վ����ţ�-1��ʾδ����
	virtual int cross(const LINE& b)const;                  //������������·�ཻ���򷵻�1
	virtual operator int()const;                            //ȡ������·���
	virtual int NOFS()const;                                //ȡ������·��վ������
	virtual double dist(int d, int a)const;                 //��·��վ��d��վ��a�ľ���
	virtual int& operator[](int x);                         //ȡ��·ĳ��վ�ε�վ����
	virtual ~LINE()noexcept;
};
class TRAN {                                                //����·from��վ����stopת����·to
	int from;                                               //�ֳ˵Ĺ�����·��
	int to;                                                 //��Ҫת�˵Ĺ�����·��
	int stop;                                               //��stops.txt�����վ����
public:
	TRAN(int from = 0, int to = 0, int stop = 0);
	int operator==(const TRAN& t)const;
	virtual int& F();                                       //�ֳ˵Ĺ�����·��
	virtual int& T();                                       //��Ҫת�˵Ĺ�����·��
	virtual int& S();                                       //ת�˵��վ����
};
class ROUTE {                                               //һ��ת��·��
	TRAN* const tran;                                       //ת��·���ϵ�����ת��վ��
	const int noft;                                         //ת��·���ϵ�ת�˴���
public:
	ROUTE(TRAN* tran = nullptr, int noft = 0);
	ROUTE(const TRAN& t);
	ROUTE(const ROUTE& r);
	ROUTE(ROUTE&& r)noexcept;
	virtual operator int()const;                            //�õ�ת�˴���
	virtual int operator==(const ROUTE& r)const;
	virtual ROUTE operator *()const;                        //Լ��ȥ���ظ��Ĺ���ת����·
	virtual TRAN& operator[](int);//һ��·���ϵ�����ת��վ�� 
	virtual ROUTE operator+(const ROUTE& r)const;// ת��·������ 
	virtual ROUTE& operator=(const ROUTE& r);
	virtual ROUTE& operator=(ROUTE&& r)noexcept;
	virtual ROUTE& operator+=(const ROUTE& r);
	virtual ~ROUTE()noexcept;
	virtual int print()const;
	//��ӡת��·�� 
};
class NODE {//����Ԫ�أ����ص�ת�˴�������· 
	ROUTE* const p;//����R*c��Ԫ�ص�ת��·������ 
	int n;//����r*c��Ԫ�ؼ��ص�ת��·�������� 
public:
	NODE(ROUTE* p, int n);
	NODE(int n = 0);
	NODE(const NODE& n);
	NODE(NODE&& n)noexcept;
	virtual NODE operator*()const;//����Ԫ��Լ��ȥ��ת���еĻ� 
	virtual NODE operator+(const ROUTE& n)const;//Ԫ������·�� 
	virtual NODE operator+(const NODE& n)const;//Ԫ��·������ 
	virtual NODE operator*(const NODE& n)const;//Ԫ��·��ת������ 
	virtual NODE& operator=(const NODE& n);
	virtual NODE& operator+=(const NODE& n);
	virtual NODE& operator+=(const ROUTE& n);
	virtual NODE& operator*=(const NODE& n);
	virtual NODE& operator=(NODE&& n)noexcept;
	virtual ROUTE& operator[](int x);//��õ�X��ת��·�� 
	virtual operator int& ();//���ؿ�ת��·����n 
	virtual ~NODE()noexcept;
	virtual void print()const;//��ӡת�˾���Ԫ�� 

};
class TMAP {//���й���ת��Ԫ�صġ��հ������� 
	NODE* const p;
	const int r, c;//���������� 
public:
	TMAP(int r = 0, int c = 0);
	TMAP(const TMAP& a);
	TMAP(TMAP&& a)noexcept;
	virtual ~TMAP();
	virtual int notZero()const;//�����ֲ��ɵ���վ�㣬�ͷ���0
	//���º�����������ת������·���������վ��Ϊb���յ�վ��Ϊe,r����10��·��
	virtual int miniTran(int b, int e, int& noft, ROUTE(&r)[100])const;
	//���º���������̾����·���������վ��Ϊb,�յ�վ��Ϊe,,r����ʮ��·��
	virtual int miniDist(int b, int e, double& dist, ROUTE(&r)[100])const;
	static double getDist(int b, int e, ROUTE& r);
	virtual NODE* operator[](int r);//�õ�����ĳ��rԪ�� ���׵�ַ
	virtual int& operator()(int r, int e);
	virtual TMAP operator*(const TMAP& a)const;//���հ������㣺�˷�
	virtual TMAP operator+(const TMAP& a)const;//"�հ������㣺�ӷ�
	virtual TMAP& operator=(const TMAP& a);
	virtual TMAP& operator= (TMAP&& a);
	virtual TMAP& operator+=(const TMAP& a);
	virtual TMAP& operator*=(const TMAP& a);
	virtual TMAP& operator()(int r, int c, const ROUTE& a);//��·��a�������Ԫ���� 
	virtual void print()const;//��ӡת�þ��� 
};
struct GIS {//����������Ϣϵͳ���� 
	static STOP* st;//���й���վ���� 
	static LINE* ls;//���й�����· 
	static int ns, nl;//����վ��ns,������·�� 
	static TMAP raw, tra;//ԭʼת�˾���raw,���հ���ת�˾��� 
	static int obs;//GIS�Ķ������� 
public:
	GIS();
	GIS(const char* flstop, const char* flline);//��վ�㼰��·�ļ����ص�ͼ 
	int miniTran(int fx, int fy, int tx, int ty, int& f, int& t, int& n, ROUTE(&r)[100]);
	int miniDist(int fx, int fy, int tx, int ty, int& f, int& t, double& d, ROUTE(&r)[100]);
	~GIS();
};
extern GIS* gis;