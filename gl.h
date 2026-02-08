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
	int getx();
	int gety();
	float getrotationx();
	float getrotationy();
	void setx(int x);
	void sety(int y);
	void setrotationx(float rotationx);
	void setrotationy(float rotationy);
	int r, speed;

private:
	int x, y;
	float rotationx, rotationy;

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
	x = 400;
	y = 300;
	rotationx = -1;
	rotationy = 0;
	r = 10;
	speed = 8;
}
ball::~ball()
{
	speed = r = x = y = rotationx = rotationy = NULL;
}
int ball::getx()
{
	return x;
}
int ball::gety()
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
void ball::setx(int x)
{
	this->x = x;
}
void ball::sety(int y)
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

//线类函数定义
line::line()
{
	x = y = 400;
}
line::~line()
{
	x = y = NULL;
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






