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
	while (abc!=NULL)
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
#include#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, W#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W /#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peek#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
		#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore =#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H -#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HAL#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX >#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.get#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >=#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
				#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddle#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(red#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			//#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			//#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rs#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotation#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// =====#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.get#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.getrotationx();
			float gvy = greenBall.getrotationy();
			float gspeed#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.getrotationx();
			float gvy = greenBall.getrotationy();
			float gspeed = static_cast<float>(greenBall.getSpeed());
			int gr = greenBall.r;

#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.getrotationx();
			float gvy = greenBall.getrotationy();
			float gspeed = static_cast<float>(greenBall.getSpeed());
			int gr = greenBall.r;

			// 左/右边界反弹
			if (gx - gr <= 0)#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.getrotationx();
			float gvy = greenBall.getrotationy();
			float gspeed = static_cast<float>(greenBall.getSpeed());
			int gr = greenBall.r;

			// 左/右边界反弹
			if (gx - gr <= 0) { gx = static_cast<float>(gr); gvx = fabsf(gvx); }#include "gl.h"
#define double float

using namespace std;

const int WND_W = 800;
const int WND_H = 600;
const int PADDLE_HALF = 50;
const int WALL_PAD = 10;

enum GameState { MENU, PLAYING, PAUSED, GAMEOVER };

int main()
{
	srand(static_cast<unsigned>(time(0)));
	initgraph(WND_W, WND_H);

R:
	setorigin(0, WND_H);
	setaspectratio(1, -1);

	// 游戏对象
	ball redBall;		// 水平方向球：玩家1用鼠标Y控制右侧挡板
	ball greenBall;		// 垂直方向球：玩家2用鼠标X控制底部挡板
	ExMessage mouse;
	int mouseX = WND_W / 2;
	int mouseY = WND_H / 2;

	int score = 0;
	int hiScore = 0;
	int hits = 0;
	GameState state = MENU;
	bool running = true;

	// 两球独立计分
	int redScore = 0;
	int greenScore = 0;

	BeginBatchDraw();
	while (running)
	{
		setbkcolor(BLACK);
		cleardevice();

		// ===== 消息处理 =====
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标：EasyX 默认原点在左上角，y 向下
			// 我们翻转了坐标系，所以 y 需要转换
			mouseX = mouse.x;
			mouseY = mouse.y;

			if (mouse.message == WM_LBUTTONDOWN)
			{
				if (state == MENU || state == GAMEOVER)
				{
					// 初始化/重置游戏
					redBall.reset(100.0f, 300.0f, 1.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f));
					greenBall.reset(400.0f, 500.0f,
						-1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f),
						-1.0f);
					redBall.setSpeed(6);
					greenBall.setSpeed(6);
					score = 0;
					hits = 0;
					redScore = 0;
					greenScore = 0;
					state = PLAYING;
				}
				else if (state == PLAYING)
				{
					state = PAUSED;
				}
				else if (state == PAUSED)
				{
					state = PLAYING;
				}
			}
			else if (mouse.message == WM_RBUTTONDOWN)
			{
				if (state == PLAYING || state == PAUSED || state == MENU || state == GAMEOVER)
				{
					running = false;
					break;
				}
			}
			else if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
				else if (mouse.vkcode == VK_SPACE)
				{
					if (state == PLAYING) state = PAUSED;
					else if (state == PAUSED) state = PLAYING;
				}
			}
		}
		if (!running) break;

		// ===== 游戏逻辑 =====
		if (state == PLAYING)
		{
			// 挡板的"显示"y 值在翻转坐标系中 = WND_H - mouseY
			float paddleY = static_cast<float>(WND_H - mouseY);
			float paddleX = static_cast<float>(mouseX);

			// 限制鼠标挡板在合理范围
			if (paddleY < PADDLE_HALF) paddleY = static_cast<float>(PADDLE_HALF);
			if (paddleY > WND_H - PADDLE_HALF) paddleY = static_cast<float>(WND_H - PADDLE_HALF);
			if (paddleX < PADDLE_HALF) paddleX = static_cast<float>(PADDLE_HALF);
			if (paddleX > WND_W - PADDLE_HALF) paddleX = static_cast<float>(WND_W - PADDLE_HALF);

			// ===== 红球逻辑（水平左右飞行） =====
			float rx = redBall.getx();
			float ry = redBall.gety();
			float rvx = redBall.getrotationx();
			float rvy = redBall.getrotationy();
			float rspeed = static_cast<float>(redBall.getSpeed());
			int rr = redBall.r;

			// 上/下边界反弹
			if (ry - rr <= 0) { ry = static_cast<float>(rr); rvy = fabsf(rvy); }
			if (ry + rr >= WND_H) { ry = static_cast<float>(WND_H - rr); rvy = -fabsf(rvy); }

			// 左墙（AI/静态挡板）反弹
			if (rx - rr <= WALL_PAD)
			{
				rx = static_cast<float>(WALL_PAD + rr);
				rvx = fabsf(rvx);
				// 随机偏移 y 方向
				rvy += -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f);
			}

			// 右侧玩家挡板碰撞（在翻转坐标系中挡板 y = paddleY）
			if (rx + rr >= WND_W - WALL_PAD && rvx > 0)
			{
				if (fabsf(ry - paddleY) <= static_cast<float>(PADDLE_HALF))
				{
					rx = static_cast<float>(WND_W - WALL_PAD - rr);
					rvx = -fabsf(rvx);
					// 根据击中位置改变角度：击中越靠上/下，角度越大
					float hitOffset = (ry - paddleY) / static_cast<float>(PADDLE_HALF); // -1 ~ 1
					rvy = hitOffset * 2.0f;
					redScore++;
					hits++;
					// 加速
					if (hits % 3 == 0 && rspeed < 16)
						redBall.setSpeed(redBall.getSpeed() + 1);
				}
			}

			// 红球出界（右侧无挡板拦截）
			if (rx >= WND_W)
			{
				state = GAMEOVER;
			}

			// 更新红球位置
			redBall.normalize();
			rx += rvx * rspeed;
			ry += rvy * rspeed;
			redBall.setx(rx);
			redBall.sety(ry);
			redBall.setrotationx(rvx);
			redBall.setrotationy(rvy);

			// ===== 绿球逻辑（垂直上下飞行） =====
			float gx = greenBall.getx();
			float gy = greenBall.gety();
			float gvx = greenBall.getrotationx();
			float gvy = greenBall.getrotationy();
			float gspeed = static_cast<float>(greenBall.getSpeed());
			int gr = greenBall.r;

			// 左/右边界反弹
			if (gx - gr <= 0) { gx = static_cast<float>(gr); gvx = fabsf(gvx); }
			if (gx + gr >= WND_W) { gx = static_cast<float>(