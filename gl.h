constexpr auto PI = 3.1415926535897932384626;
#define 创建窗口 initgraph			//需要easyx.h
#define 关闭窗口 closegraph			//需要easyx.h
#define 设置原点 setorigin			//需要easyx.h
#define 设置轴拉伸 setaspectratio	//需要easyx.h
#define 设置线条颜色 setlinecolor	//需要easyx.h
#define 设置背景颜色 setbkcolor		//需要easyx.h
#define 设置填充颜色 setfillcolor	//需要easyx.h
#define 刷新窗口 cleardevice		//需要easyx.h
#define 画点 putpixel				//需要easyx.h
#define 画圆 circle					//需要easyx.h
#define 填充圆 fillcircle			//需要easyx.h	/*fill带线，solid不带线*/
#define 画线 line					//需要easyx.h
#define 画矩形 rectangle			//需要easyx.h
#define 填充矩形 fillrectangle		//需要easyx.h	/*fill带线，solid不带线*/
#define 画椭圆 ellipse				//需要easyx.h
#define 填充椭圆 fillellipse		//需要easyx.h	/*fill带线，solid不带线*/
#define 画圆角矩形 roundrect		//需要easyx.h
#define 填充圆角矩形 fillroundrect	//需要easyx.h	/*fill带线，solid不带线*/
#define 画扇形 pie					//需要easyx.h
#define 画弧线 arc					//需要easyx.h
#define 画多边形 polygon			//需要easyx.h	/*fill带线，solid不带线*/
#define 填充多边形 fillpolygon		//需要easyx.h
#define 画多段线 polyline			//需要easyx.h
#define 加载图片 loadimage			//需要easyx.h
#define 显示图片 putimage			//需要easyx.h
#define 输出文字 outtextxy			//需要easyx.h
//outtextxy(TEXT("hello"));
#define 文字格式 settextstyle		//需要easyx.h
#define 文字颜色 settextcolor		//需要easyx.h
//settextcolor(RGB(0,0,0))||settextcolor(WHITE)
#define 输入 cin					//需要<iostream>
#define 输出 cout					//需要<iostream>
#define 换行 endl					//需要<iostream>
#define 主要 main
#define 字符串 string
#define 如果 if
#define 循环 for
#define 整数 int
#define 浮点 double
#define 获取输入 getchar
#define 输出字符 putchar
#define 随机数 rand()
#define 做 do
#define 当 while
#define 跳转 goto
#define 布尔 bool
#define 字符 char
#define 选择 switch
#define 事件 case
#define 默认 default
#define 声明 void
#define 类 class
#define 私有 private
#define 公有 public
#define 保护 protected
#define 此 this
#define 结构 struct
#define 命名 typedef
#define 返回 return
#define 使用命名空间 using namespace 
#define 标准标识符 std
#define 静态 static
#define 只读 const
#define 开启双重缓冲 BeginBatchDraw
#define 显示帧画面 FlushBatchDraw
#define 结束双重缓冲 EndBatchDraw
#define VK_W 0x57
#define VK_S 0x53
#define VK_D 0x44
#define VK_A 0x41
#include <easyx.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;


//计时器
int timer(int duration, int id)
{
	static int starttime[10];
	int endtime = clock();
	if (endtime - starttime[id] > duration)
	{
		starttime[id] = endtime;
		return 1;
	}
	return 0;
}

//小球类
class ball
{
public:
	ball();
	~ball();
	float getx();
	float gety();
	float getrotationx();
	float getrotationy();
	int getSpeed();
	void setx(float x);
	void sety(float y);
	void setrotationx(float rotationx);
	void setrotationy(float rotationy);
	void setSpeed(int s);
	void reset(float cx, float cy, float dx, float dy);
	void normalize();
	int r, speed;

private:
	float x, y;
	float rotationx, rotationy;
	float baseSpeed;
};

//线类
class line
{
public:
	line();
	~line();
	float getx();
	float gety();
	void setx(float x);
	void sety(float y);
private:
	float x, y;
}botline, myline;

//球类函数定义
ball::ball()
{
	x = 400.0f;
	y = 300.0f;
	rotationx = -1.0f;
	rotationy = 0.0f;
	r = 10;
	speed = 8;
	baseSpeed = 8.0f;
}
ball::~ball()
{
}
float ball::getx()
{
	return x;
}
float ball::gety()
{
	return y;
}
float ball::getrotationx()
{
	return rotationx;
}
float ball::getrotationy()
{
	return rotationy;
}
int ball::getSpeed()
{
	return speed;
}
void ball::setx(float x)
{
	this->x = x;
}
void ball::sety(float y)
{
	this->y = y;
}
void ball::setrotationx(float rotationx)
{
	this->rotationx = rotationx;
}
void ball::setrotationy(float rotationy)
{
	this->rotationy = rotationy;
}
void ball::setSpeed(int s)
{
	speed = s;
}
void ball::reset(float cx, float cy, float dx, float dy)
{
	x = cx;
	y = cy;
	rotationx = dx;
	rotationy = dy;
	speed = static_cast<int>(baseSpeed);
	normalize();
}
void ball::normalize()
{
	float len = sqrtf(rotationx * rotationx + rotationy * rotationy);
	if (len > 0.0001f)
	{
		rotationx /= len;
		rotationy /= len;
	}
}

//线类函数定义
line::line()
{
	x = y = 400.0f;
}
line::~line()
{
}
float line::getx()
{
	return this->x;
}
float line::gety()
{
	return this->y;
}
void line::setx(float x)
{
	this->x = x;
}
void line::sety(float y)
{
	this->y = y;
}

// ============================================================
// 砖块类型枚举
// ============================================================
enum BrickType
{
	BRICK_NORMAL = 0,      // 普通砖块：一击即碎
	BRICK_HARD,            // 坚硬砖块：需两次
	BRICK_SUPER,           // 超级砖块：需三次
	BRICK_EXPLOSIVE,       // 爆炸砖块：碎裂时波及四邻
	BRICK_INDESTRUCTIBLE   // 不可破坏：仅作障碍
};

// 砖块类
class Brick
{
public:
	Brick();
	Brick(float x, float y, float w, float h, BrickType t, COLORREF c);
	~Brick();
	bool isAlive();
	void hit();
	void destroy();
	BrickType getType();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	COLORREF getColor();
	int getHits();
	int getMaxHits();
	int getScore();

private:
	float m_x, m_y, m_w, m_h;
	BrickType m_type;
	int m_hits;        // 剩余耐久
	int m_maxHits;
	COLORREF m_color;
	bool m_alive;
};

Brick::Brick()
	: m_x(0), m_y(0), m_w(0), m_h(0), m_type(BRICK_NORMAL),
	m_hits(1), m_maxHits(1), m_color(WHITE), m_alive(false) {}

Brick::Brick(float x, float y, float w, float h, BrickType t, COLORREF c)
	: m_x(x), m_y(y), m_w(w), m_h(h), m_type(t), m_color(c), m_alive(true)
{
	switch (t)
	{
	case BRICK_NORMAL:      m_hits = 1; m_maxHits = 1; break;
	case BRICK_HARD:        m_hits = 2; m_maxHits = 2; break;
	case BRICK_SUPER:       m_hits = 3; m_maxHits = 3; break;
	case BRICK_EXPLOSIVE:   m_hits = 1; m_maxHits = 1; break;
	case BRICK_INDESTRUCTIBLE: m_hits = 999; m_maxHits = 999; break;
	default: m_hits = 1; m_maxHits = 1;
	}
}

Brick::~Brick() {}

bool Brick::isAlive() { return m_alive; }

void Brick::hit()
{
	if (m_type == BRICK_INDESTRUCTIBLE) return;
	m_hits--;
	if (m_hits <= 0) m_alive = false;
}

void Brick::destroy()
{
	if (m_type != BRICK_INDESTRUCTIBLE)
	{
		m_hits = 0;
		m_alive = false;
	}
}

BrickType Brick::getType() { return m_type; }
float Brick::getLeft() { return m_x; }
float Brick::getRight() { return m_x + m_w; }
float Brick::getTop() { return m_y + m_h; }
float Brick::getBottom() { return m_y; }
COLORREF Brick::getColor() { return m_color; }
int Brick::getHits() { return m_hits; }
int Brick::getMaxHits() { return m_maxHits; }

int Brick::getScore()
{
	switch (m_type)
	{
	case BRICK_NORMAL:    return 10;
	case BRICK_HARD:      return 25;
	case BRICK_SUPER:     return 50;
	case BRICK_EXPLOSIVE: return 15;
	default: return 0;
	}
}

// ============================================================
// 道具类型枚举
// ============================================================
enum PowerUpType
{
	POWERUP_WIDE = 0,     // 加宽挡板
	POWERUP_SLOW,         // 减速球
	POWERUP_LIFE,         // 额外生命
	POWERUP_MULTI         // 多球
};

class PowerUp
{
public:
	PowerUp(float x, float y, PowerUpType t);
	~PowerUp();
	void update(float dt);
	bool isAlive();
	void kill();
	float getX();
	float getY();
	float getR();
	PowerUpType getType();
	COLORREF getColor();

private:
	float m_x, m_y;
	float m_vy;
	float m_r;
	PowerUpType m_type;
	COLORREF m_color;
	bool m_alive;
};

PowerUp::PowerUp(float x, float y, PowerUpType t)
	: m_x(x), m_y(y), m_vy(-2.0f), m_r(10.0f), m_type(t), m_alive(true)
{
	switch (t)
	{
	case POWERUP_WIDE:  m_color = RGB(0, 220, 255); break;
	case POWERUP_SLOW:  m_color = RGB(180, 180, 255); break;
	case POWERUP_LIFE:  m_color = RGB(255, 80, 160); break;
	case POWERUP_MULTI: m_color = RGB(255, 220, 0); break;
	default: m_color = WHITE;
	}
}

PowerUp::~PowerUp() {}

void PowerUp::update(float dt)
{
	m_y += m_vy * dt;
	if (m_y < -20.0f) m_alive = false;
}

bool PowerUp::isAlive() { return m_alive; }
void PowerUp::kill() { m_alive = false; }
float PowerUp::getX() { return m_x; }
float PowerUp::getY() { return m_y; }
float PowerUp::getR() { return m_r; }
PowerUpType PowerUp::getType() { return m_type; }
COLORREF PowerUp::getColor() { return m_color; }

// ============================================================
// 粒子特效
// ============================================================
class Particle
{
public:
	Particle(float x, float y, float vx, float vy, COLORREF c, float life);
	~Particle();
	void update(float dt);
	bool isAlive();
	float getX();
	float getY();
	COLORREF getColor();

private:
	float m_x, m_y, m_vx, m_vy;
	COLORREF m_color;
	float m_life;
	float m_maxLife;
};

Particle::Particle(float x, float y, float vx, float vy, COLORREF c, float life)
	: m_x(x), m_y(y), m_vx(vx), m_vy(vy), m_color(c), m_life(life), m_maxLife(life) {}

Particle::~Particle() {}

void Particle::update(float dt)
{
	m_x += m_vx * dt;
	m_y += m_vy * dt;
	m_vy -= 0.15f * dt;  // 轻微重力
	m_life -= dt;
}

bool Particle::isAlive() { return m_life > 0; }
float Particle::getX() { return m_x; }
float Particle::getY() { return m_y; }

COLORREF Particle::getColor()
{
	float alpha = max(0.0f, m_life / m_maxLife);
	int r = GetRValue(m_color);
	int g = GetGValue(m_color);
	int b = GetBValue(m_color);
	return RGB(static_cast<BYTE>(r * alpha),
		static_cast<BYTE>(g * alpha),
		static_cast<BYTE>(b * alpha));
}






