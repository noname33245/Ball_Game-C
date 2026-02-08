#include "gl.h"
#define double float

using namespace std;
int main()
{
	srand(static_cast<unsigned>(time(0)));
	//绘制窗口
	initgraph(800, 600);
R:	setorigin(0, 600);
	setaspectratio(1, -1);
	//变量定义
	int score = 0;
	int abc = NULL;
	ball myball, myball_1;
	ExMessage mouse;
	//设置鼠标变量
	//绿球移动方向初始化
	myball_1.setrotationx(0);
	myball_1.setrotationy(-1);

	BeginBatchDraw();
	while (abc==NULL)
	{
		setbkcolor(BLACK);
		//读取鼠标
		peekmessage(&mouse);
		static float x;
		static float y;
		static bool setxy = true;
		//读取鼠标初始位置（一次）
		if (setxy)
		{
			y = mouse.y;
			x = mouse.x;
			setxy = false;
		}

		//Ball Red
		//边缘碰撞回弹
		if ((myball.gety() - myball.r) < 0 )
		{
			myball.setrotationy(1);
		}
		if (myball.gety() + myball.r > 600)
		{
			myball.setrotationy(-1);
		}

		if ((myball.getx() - myball.r) <= 10 )
		{
			myball.setrotationx(1);
			myball.setrotationy(-6+static_cast<float>(rand())/
				static_cast<float>(RAND_MAX/(6+6)));
		}
		if ((myball.getx() >= (790 - myball.r)
			&& (fabs(myball.gety() + mouse.y - 600) <= 50)))
		{
			myball.setrotationx(-1);
			myball.setrotationy(-4 + static_cast<float>(rand()) /
				static_cast<float>(RAND_MAX / (5 + 5)));
			if (timer(200,0))
			{
				score++;
			}
		}

		//使用计时器控制移动
		if (timer(20, 1))
		{
			myball.setx(myball.getx() + myball.getrotationx() * myball.speed);
			myball.sety(myball.gety() + myball.getrotationy() );
		}

		//绘制红色球
		setfillcolor(RED);
		solidcircle(myball.getx(), myball.gety(),myball.r);
		solidrectangle(790, 600 - mouse.y - 50, 800, 600 - mouse.y + 50);
		solidrectangle(0, myball.gety() - 50, 10,  myball.gety() + 50);

		//失败条件
		if (myball.getx() >= 800)
		{
			break;
		}
//================================================================================
//================================================================================

		//Ball Green
		static bool ball_1 = true;
		

		if ((myball_1.getx() - myball_1.r) < 0)
		{
			myball_1.setrotationx(1);
		}
		if (myball_1.getx() + myball_1.r > 800)
		{
			myball_1.setrotationx(-1);
		}

		if ((myball_1.gety() - myball_1.r) <= 10)
		{
			myball_1.setrotationy(1);
			myball_1.setrotationx(-6 + static_cast<float>(rand()) /
				static_cast<float>(RAND_MAX / (6 + 6)));
		}
		if ((myball_1.gety() >= (590 - myball_1.r)
			&& (fabs(myball_1.getx() - mouse.x) <= 50)))
		{
			myball_1.setrotationy(-1);
			myball_1.setrotationx(-4 + static_cast<float>(rand()) /
				static_cast<float>(RAND_MAX / (5 + 5)));
			if (timer(200, 2))
			{
				score++;
			}
		}

		if (timer(20, 3))
		{
			myball_1.sety(myball_1.gety() + myball_1.getrotationy() * myball_1.speed);
			myball_1.setx(myball_1.getx() + myball_1.getrotationx());
		}

		//绘制绿色球
		setfillcolor(GREEN);
		solidcircle(myball_1.getx(), myball_1.gety(), myball_1.r);
		solidrectangle(mouse.x - 50, 590, mouse.x + 50, 600);
		solidrectangle(myball_1.getx() - 50, 0, myball_1.getx() + 50, 10);

		FlushBatchDraw();
		cleardevice();

		//失败条件
		if (myball_1.gety() >= 600)
		{
			break;
		}


	}

	EndBatchDraw();
	cleardevice();
	setorigin(0, 0);
	setaspectratio(1, 1);

	//结束文字
	settextcolor(WHITE);
	settextstyle(40, 0, "楷体");
	char sco[100];
	sprintf_s(sco, "%d", score);
	outtextxy(380, 350, sco);
	outtextxy(200, 348, TEXT("分数:"));
	outtextxy(200, 250, TEXT("左键重开，右键退出"));

	//读取鼠标按键
	while (true)
	{
		while (peekmessage(&mouse))
		{
			switch (mouse.message)
			{
			case WM_LBUTTONDOWN:goto R;
				break;
			case WM_RBUTTONDOWN:closegraph(); return 0;
			default:
				break;
			}
		}
	}

}



//
//if (timer(20, 0))
//{
//	if (getasynckeystate(vk_up))
//		myball.sety(myball.gety() + 5);
//	if (getasynckeystate(vk_down))
//		myball.sety(myball.gety() - 5);
//	if (getasynckeystate(vk_right))
//		myball.setx(myball.getx() + 5);
//	if (getasynckeystate(vk_left))
//		myball.setx(myball.getx() - 5);
//
//	if (getasynckeystate(0x57))
//		myball.sety(myball.gety() + 5);
//	if (getasynckeystate(0x53))
//		myball.sety(myball.gety() - 5);
//	if (getasynckeystate(0x44))
//		myball.setx(myball.getx() + 5);
//	if (getasynckeystate(0x41))
//		myball.setx(myball.getx() - 5);
//}
//
//
