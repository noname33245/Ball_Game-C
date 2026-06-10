#include "gl.h"

// ============================================================
// 游戏常量
// ============================================================
const int WINDOW_W = 800;
const int WINDOW_H = 600;

const int PADDLE_HALF = 60;      // 挡板半长
const int PADDLE_HALF_MAX = 100; // 道具加宽后最大
const int WALL_THICK = 10;       // 墙壁厚度

const float BALL_SPEED_MIN = 6.0f;
const float BALL_SPEED_MAX = 14.0f;

// 砖块布局
const int BRICK_COLS = 10;
const int BRICK_ROWS = 6;
const float BRICK_W = 50.0f;
const float BRICK_H = 22.0f;
const float BRICK_START_X = 110.0f;
const float BRICK_START_Y = 380.0f;  // 顶部砖块 Y（在 setorigin(0,600)+setaspectratio(1,-1) 的数学坐标系下）

// 游戏状态
enum GameState
{
	STATE_MENU = 0,
	STATE_PLAYING,
	STATE_PAUSED,
	STATE_LEVEL_CLEAR,
	STATE_GAME_OVER,
	STATE_WIN
};

// ============================================================
// 全局游戏数据
// ============================================================
static int g_score = 0;
static int g_lives = 3;
static int g_level = 1;
static int g_highScore = 0;

static GameState g_state = STATE_MENU;

// 挡板尺寸（可被道具修改）
static int g_paddleHalf = PADDLE_HALF;
static int g_slowTimer = 0;       // 减速剩余帧数

// 砖块与道具与粒子
static vector<Brick> g_bricks;
static vector<PowerUp> g_powerups;
static vector<Particle> g_particles;

// 活动中的球
static vector<ball> g_balls;

// 鼠标坐标（经过坐标系转换）
static int g_mouseX = 400;
static int g_mouseY = 300;
static bool g_mouseLeftPressed = false;
static bool g_mouseRightPressed = false;
static bool g_spacePressed = false;

// 菜单选中项
static int g_menuIndex = 0;

// ============================================================
// 工具函数
// ============================================================
float clampf(float v, float lo, float hi)
{
	if (v < lo) return lo;
	if (v > hi) return hi;
	return v;
}

void spawnParticles(float x, float y, COLORREF color, int count)
{
	for (int i = 0; i < count; i++)
	{
		float ang = static_cast<float>(rand()) / RAND_MAX * 2.0f * PI;
		float sp = 1.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f;
		float life = 20.0f + static_cast<float>(rand()) / RAND_MAX * 25.0f;
		g_particles.push_back(Particle(x, y, cosf(ang) * sp, sinf(ang) * sp, color, life));
	}
}

// ============================================================
// 关卡生成
// ============================================================
void buildLevel(int level)
{
	g_bricks.clear();

	// 基础颜色随关卡变化
	COLORREF colors[] = {
		RGB(255, 90, 90),
		RGB(255, 180, 70),
		RGB(80, 220, 120),
		RGB(90, 160, 255),
		RGB(220, 120, 255),
		RGB(255, 240, 100)
	};

	// 关卡难度参数
	int hardChance = min(45, 10 + level * 5);      // 硬砖块概率
	int superChance = min(25, level * 3);           // 超级砖块概率
	int explosiveChance = min(20, 5 + level * 2);   // 爆炸砖块概率
	int indestructChance = min(15, (level - 1) * 3); // 不可破坏概率

	int rows = min(BRICK_ROWS + (level - 1), 8);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < BRICK_COLS; c++)
		{
			float x = BRICK_START_X + c * BRICK_W;
			float y = BRICK_START_Y - r * BRICK_H;

			// 顶部两行留空，避免堵死发球区
			if (y > 540.0f) continue;

			int roll = rand() % 100;
			BrickType type = BRICK_NORMAL;

			// 根据概率决定砖块类型
			if (roll < indestructChance)
				type = BRICK_INDESTRUCTIBLE;
			else if (roll < indestructChance + explosiveChance)
				type = BRICK_EXPLOSIVE;
			else if (roll < indestructChance + explosiveChance + superChance)
				type = BRICK_SUPER;
			else if (roll < indestructChance + explosiveChance + superChance + hardChance)
				type = BRICK_HARD;
			else
				type = BRICK_NORMAL;

			COLORREF col;
			if (type == BRICK_INDESTRUCTIBLE)
				col = RGB(120, 120, 120);
			else if (type == BRICK_EXPLOSIVE)
				col = RGB(255, 120, 0);
			else
				col = colors[(r + level) % 6];

			g_bricks.push_back(Brick(x, y, BRICK_W, BRICK_H, type, col));
		}
	}

	// 保证至少有可破坏砖块
	bool hasBreakable = false;
	for (auto& b : g_bricks)
	{
		if (b.getType() != BRICK_INDESTRUCTIBLE) { hasBreakable = true; break; }
	}
	if (!hasBreakable && !g_bricks.empty())
	{
		g_bricks[0] = Brick(BRICK_START_X, BRICK_START_Y, BRICK_W, BRICK_H, BRICK_NORMAL, RGB(255, 90, 90));
	}
}

// ============================================================
// 初始化一关
// ============================================================
void startLevel(bool resetScoreAndLives)
{
	if (resetScoreAndLives)
	{
		g_score = 0;
		g_lives = 3;
		g_level = 1;
	}

	g_paddleHalf = PADDLE_HALF;
	g_slowTimer = 0;
	g_powerups.clear();
	g_particles.clear();
	g_balls.clear();
	g_mouseLeftPressed = false;
	g_mouseRightPressed = false;
	g_spacePressed = false;

	buildLevel(g_level);

	// 添加两个初始球
	ball b1, b2;
	b1.reset(300.0f, 300.0f, -0.7f, 0.5f);
	b2.reset(500.0f, 250.0f, 0.6f, -0.6f);
	g_balls.push_back(b1);
	g_balls.push_back(b2);

	g_state = STATE_PLAYING;
}

// ============================================================
// 检查球与矩形的碰撞，返回是否命中以及需要翻转的轴
// ============================================================
bool ballVsRect(ball& b, float rx, float ry, float rw, float rh,
	bool& flipX, bool& flipY, float& hitX, float& hitY)
{
	float bx = b.getx();
	float by = b.gety();
	float r = static_cast<float>(b.r);

	// 最近点
	float closestX = clampf(bx, rx, rx + rw);
	float closestY = clampf(by, ry, ry + rh);

	float dx = bx - closestX;
	float dy = by - closestY;
	float distSq = dx * dx + dy * dy;

	if (distSq > r * r) return false;

	// 决定从哪条边进入
	float overlapX = r - fabsf(dx);
	float overlapY = r - fabsf(dy);

	flipX = false;
	flipY = false;

	// 若球心在矩形内部
	if (distSq < 0.0001f)
	{
		flipX = true;
		flipY = true;
		hitX = bx;
		hitY = by;
		return true;
	}

	// 选择较小的重叠量来推出与反弹
	if (overlapX < overlapY)
	{
		flipX = true;
		if (dx < 0) b.setx(rx - r - 0.5f);
		else b.setx(rx + rw + r + 0.5f);
	}
	else
	{
		flipY = true;
		if (dy < 0) b.sety(ry - r - 0.5f);
		else b.sety(ry + rh + r + 0.5f);
	}

	hitX = closestX;
	hitY = closestY;
	return true;
}

// ============================================================
// 处理砖块被命中后的连锁效果（爆炸砖块）
// ============================================================
void onBrickDestroyed(size_t idx)
{
	if (idx >= g_bricks.size()) return;
	Brick& b = g_bricks[idx];

	float cx = (b.getLeft() + b.getRight()) * 0.5f;
	float cy = (b.getTop() + b.getBottom()) * 0.5f;

	spawnParticles(cx, cy, b.getColor(), 18);
	g_score += b.getScore();

	// 一定概率掉落道具
	if (b.getType() != BRICK_INDESTRUCTIBLE && rand() % 100 < 18)
	{
		PowerUpType t;
		int r = rand() % 100;
		if (r < 35) t = POWERUP_WIDE;
		else if (r < 65) t = POWERUP_SLOW;
		else if (r < 85) t = POWERUP_MULTI;
		else t = POWERUP_LIFE;
		g_powerups.push_back(PowerUp(cx, cy, t));
	}

	// 爆炸砖块：连锁销毁相邻
	if (b.getType() == BRICK_EXPLOSIVE)
	{
		spawnParticles(cx, cy, RGB(255, 220, 80), 40);
		for (size_t i = 0; i < g_bricks.size(); i++)
		{
			if (i == idx || !g_bricks[i].isAlive()) continue;
			Brick& nb = g_bricks[i];
			float dx = fabsf((nb.getLeft() + nb.getRight()) * 0.5f - cx);
			float dy = fabsf((nb.getTop() + nb.getBottom()) * 0.5f - cy);
			if (dx < BRICK_W * 1.5f && dy < BRICK_H * 1.5f)
			{
				if (nb.getType() != BRICK_INDESTRUCTIBLE)
				{
					nb.destroy();
					float ccx = (nb.getLeft() + nb.getRight()) * 0.5f;
					float ccy = (nb.getTop() + nb.getBottom()) * 0.5f;
					spawnParticles(ccx, ccy, nb.getColor(), 10);
					g_score += nb.getScore();
				}
			}
		}
	}
}

// ============================================================
// 应用道具
// ============================================================
void applyPowerUp(PowerUpType t)
{
	switch (t)
	{
	case POWERUP_WIDE:
		g_paddleHalf = PADDLE_HALF_MAX;
		break;
	case POWERUP_SLOW:
		g_slowTimer = 360;  // ~6秒
		for (auto& b : g_balls) b.setSpeed(max(5, b.getSpeed() - 2));
		break;
	case POWERUP_LIFE:
		g_lives++;
		break;
	case POWERUP_MULTI:
	{
		// 克隆现有球
		if (!g_balls.empty())
		{
			size_t n = g_balls.size();
			for (size_t i = 0; i < n; i++)
			{
				ball nb = g_balls[i];
				nb.setrotationx(-g_balls[i].getrotationx());
				nb.setrotationy(g_balls[i].getrotationy() + 0.3f);
				nb.normalize();
				g_balls.push_back(nb);
			}
		}
		break;
	}
	default: break;
	}
}

// ============================================================
// 更新单个球
// ============================================================
void updateBall(ball& b)
{
	float speedFactor = 1.0f;
	if (g_slowTimer > 0) speedFactor = 0.7f;

	float s = static_cast<float>(b.getSpeed()) * speedFactor;
	b.setx(b.getx() + b.getrotationx() * s);
	b.sety(b.gety() + b.getrotationy() * s);

	float r = static_cast<float>(b.r);

	// 顶部墙
	if (b.gety() + r > WINDOW_H - WALL_THICK)
	{
		b.sety(WINDOW_H - WALL_THICK - r);
		b.setrotationy(-fabsf(b.getrotationy()));
	}
	// 左侧墙
	if (b.getx() - r < WALL_THICK)
	{
		b.setx(WALL_THICK + r);
		b.setrotationx(fabsf(b.getrotationx()));
	}

	// ===== 底部挡板（水平方向，由鼠标 X 控制）=====
	float paddleBottomY = 0.0f;
	float paddleBottomTop = WALL_THICK;
	float paddleBottomLeft = g_mouseX - g_paddleHalf;
	float paddleBottomRight = g_mouseX + g_paddleHalf;

	bool flipX, flipY;
	float hx, hy;
	if (b.gety() - r < paddleBottomTop && b.getrotationy() < 0 &&
		b.getx() > paddleBottomLeft && b.getx() < paddleBottomRight)
	{
		b.sety(paddleBottomTop + r);
		// 根据击中位置调整角度
		float rel = (b.getx() - g_mouseX) / static_cast<float>(g_paddleHalf);
		rel = clampf(rel, -0.9f, 0.9f);
		float angle = rel * (PI * 0.35f);  // 最多 ±63°
		b.setrotationx(sinf(angle));
		b.setrotationy(fabsf(cosf(angle)));
		b.normalize();
		spawnParticles(b.getx(), b.gety(), RGB(120, 220, 255), 6);
		g_score += 1;
	}

	// ===== 右侧挡板（垂直方向，由鼠标 Y 控制）=====
	float paddleRightX = WINDOW_W - WALL_THICK;
	float paddleRightLeft = WINDOW_W - WALL_THICK * 2;
	float paddleRightBottom = g_mouseY - g_paddleHalf;
	float paddleRightTop = g_mouseY + g_paddleHalf;

	if (b.getx() + r > paddleRightLeft && b.getrotationx() > 0 &&
		b.gety() > paddleRightBottom && b.gety() < paddleRightTop)
	{
		b.setx(paddleRightLeft - r);
		float rel = (b.gety() - g_mouseY) / static_cast<float>(g_paddleHalf);
		rel = clampf(rel, -0.9f, 0.9f);
		float angle = rel * (PI * 0.35f);
		b.setrotationx(-fabsf(cosf(angle)));
		b.setrotationy(sinf(angle));
		b.normalize();
		spawnParticles(b.getx(), b.gety(), RGB(255, 150, 200), 6);
		g_score += 1;
	}

	// ===== 砖块碰撞 =====
	for (size_t i = 0; i < g_bricks.size(); i++)
	{
		if (!g_bricks[i].isAlive()) continue;
		bool didFlipX, didFlipY;
		float hitPX, hitPY;
		if (ballVsRect(b, g_bricks[i].getLeft(), g_bricks[i].getBottom(),
			BRICK_W, BRICK_H, didFlipX, didFlipY, hitPX, hitPY))
		{
			if (didFlipX) b.setrotationx(-b.getrotationx());
			if (didFlipY) b.setrotationy(-b.getrotationy());

			bool wasAlive = g_bricks[i].isAlive();
			g_bricks[i].hit();
			if (wasAlive && !g_bricks[i].isAlive())
			{
				onBrickDestroyed(i);
			}
			else if (g_bricks[i].isAlive())
			{
				// 未摧毁：小粒子 + 变色反馈
				spawnParticles(hitPX, hitPY, g_bricks[i].getColor(), 4);
			}
			break;  // 一帧只处理一个砖块
		}
	}

	// 稍微加速（让游戏逐渐变难）
	if (rand() % 200 == 0 && b.getSpeed() < static_cast<int>(BALL_SPEED_MAX))
	{
		b.setSpeed(b.getSpeed() + 1);
	}
}

// ============================================================
// 主游戏循环
// ============================================================
void updateGame()
{
	if (g_slowTimer > 0) g_slowTimer--;

	// 更新所有球
	for (size_t i = 0; i < g_balls.size(); )
	{
		updateBall(g_balls[i]);
		// 丢失球
		if (g_balls[i].gety() < -20.0f || g_balls[i].getx() > WINDOW_W + 20.0f)
		{
			g_balls.erase(g_balls.begin() + i);
		}
		else
		{
			i++;
		}
	}

	// 道具更新 + 挡板拾取
	for (size_t i = 0; i < g_powerups.size(); )
	{
		g_powerups[i].update(1.0f);

		float px = g_powerups[i].getX();
		float py = g_powerups[i].getY();
		float pr = g_powerups[i].getR();

		// 底部挡板拾取
		bool picked = false;
		if (py - pr < WALL_THICK && px > g_mouseX - g_paddleHalf && px < g_mouseX + g_paddleHalf)
		{
			applyPowerUp(g_powerups[i].getType());
			spawnParticles(px, py, g_powerups[i].getColor(), 20);
			picked = true;
		}
		// 右侧挡板拾取
		if (!picked && px + pr > WINDOW_W - WALL_THICK * 2 &&
			py > g_mouseY - g_paddleHalf && py < g_mouseY + g_paddleHalf)
		{
			applyPowerUp(g_powerups[i].getType());
			spawnParticles(px, py, g_powerups[i].getColor(), 20);
			picked = true;
		}

		if (!g_powerups[i].isAlive() || picked)
			g_powerups.erase(g_powerups.begin() + i);
		else
			i++;
	}

	// 粒子
	for (size_t i = 0; i < g_particles.size(); )
	{
		g_particles[i].update(1.0f);
		if (!g_particles[i].isAlive())
			g_particles.erase(g_particles.begin() + i);
		else
			i++;
	}

	// 若所有球丢失
	if (g_balls.empty())
	{
		g_lives--;
		if (g_lives <= 0)
		{
			if (g_score > g_highScore) g_highScore = g_score;
			g_state = STATE_GAME_OVER;
		}
		else
		{
			// 重新发球
			g_slowTimer = 0;
			ball b1, b2;
			b1.reset(250.0f, 300.0f, -0.7f, 0.5f);
			b2.reset(550.0f, 280.0f, 0.7f, -0.5f);
			g_balls.push_back(b1);
			g_balls.push_back(b2);
		}
	}

	// 检查关卡是否清空（所有可破坏砖块被清除）
	bool hasBreakable = false;
	for (auto& br : g_bricks)
	{
		if (br.isAlive() && br.getType() != BRICK_INDESTRUCTIBLE)
		{
			hasBreakable = true;
			break;
		}
	}
	if (!hasBreakable && g_state == STATE_PLAYING)
	{
		if (g_level >= 8)
		{
			if (g_score > g_highScore) g_highScore = g_score;
			g_state = STATE_WIN;
		}
		else
		{
			g_state = STATE_LEVEL_CLEAR;
		}
	}
}

// ============================================================
// 绘制辅助
// ============================================================
void drawBrick(Brick& b)
{
	COLORREF col = b.getColor();
	float x = b.getLeft();
	float yBot = b.getBottom();
	float yTop = b.getTop();
	float xR = b.getRight();

	// 填充
	setfillcolor(col);
	solidrectangle(static_cast<int>(x + 1), static_cast<int>(yBot + 1),
		static_cast<int>(xR - 1), static_cast<int>(yTop - 1));

	// 耐久度显示（半行高亮）
	if (b.getType() == BRICK_HARD || b.getType() == BRICK_SUPER)
	{
		int remaining = b.getHits();
		int total = b.getMaxHits();
		float ratio = static_cast<float>(remaining) / total;
		setfillcolor(RGB(255, 255, 255));
		int hlW = static_cast<int>((xR - x) * ratio * 0.5f);
		solidrectangle(static_cast<int>(x + 3), static_cast<int>(yBot + 3),
			static_cast<int>(x + 3 + hlW), static_cast<int>(yBot + 6));
	}

	if (b.getType() == BRICK_EXPLOSIVE)
	{
		setfillcolor(RGB(255, 255, 200));
		int cx = static_cast<int>((x + xR) * 0.5f);
		int cy = static_cast<int>((yTop + yBot) * 0.5f);
		solidcircle(cx, cy, 4);
	}
	if (b.getType() == BRICK_INDESTRUCTIBLE)
	{
		// 画交叉斜线
		setlinecolor(RGB(80, 80, 80));
		line(static_cast<int>(x + 2), static_cast<int>(yBot + 2),
			static_cast<int>(xR - 2), static_cast<int>(yTop - 2));
		line(static_cast<int>(xR - 2), static_cast<int>(yBot + 2),
			static_cast<int>(x + 2), static_cast<int>(yTop - 2));
	}
}

void drawPaddles()
{
	// 底部水平挡板
	setfillcolor(RGB(120, 220, 255));
	solidrectangle(g_mouseX - g_paddleHalf, 0, g_mouseX + g_paddleHalf, WALL_THICK);
	setfillcolor(RGB(220, 245, 255));
	solidrectangle(g_mouseX - g_paddleHalf + 4, 3, g_mouseX + g_paddleHalf - 4, WALL_THICK - 3);

	// 右侧垂直挡板
	setfillcolor(RGB(255, 150, 200));
	solidrectangle(WINDOW_W - WALL_THICK, g_mouseY - g_paddleHalf,
		WINDOW_W, g_mouseY + g_paddleHalf);
	setfillcolor(RGB(255, 225, 240));
	solidrectangle(WINDOW_W - WALL_THICK + 3, g_mouseY - g_paddleHalf + 4,
		WINDOW_W - 3, g_mouseY + g_paddleHalf - 4);
}

void drawWalls()
{
	setfillcolor(RGB(70, 80, 100));
	// 顶部墙
	solidrectangle(0, WINDOW_H - WALL_THICK, WINDOW_W, WINDOW_H);
	// 左侧墙
	solidrectangle(0, 0, WALL_THICK, WINDOW_H);

	// 底出口与右出口标记为危险区（红色边框）
	setlinecolor(RGB(255, 60, 60));
	linestyle(PS_DASH, 2);
	line(WALL_THICK, 2, WINDOW_W - WALL_THICK, 2);
	line(WINDOW_W - 2, WALL_THICK, WINDOW_W - 2, WINDOW_H - WALL_THICK);
	linestyle(PS_SOLID, 1);
}

void drawBalls()
{
	for (auto& b : g_balls)
	{
		setfillcolor(RGB(255, 240, 200));
		solidcircle(static_cast<int>(b.getx()), static_cast<int>(b.gety()), b.r);
		setfillcolor(RGB(255, 255, 255));
		solidcircle(static_cast<int>(b.getx()) - 3, static_cast<int>(b.gety()) + 3, 2);
	}
}

void drawParticles()
{
	for (auto& p : g_particles)
	{
		setfillcolor(p.getColor());
		solidcircle(static_cast<int>(p.getX()), static_cast<int>(p.getY()), 2);
	}
}

void drawPowerUps()
{
	for (auto& pu : g_powerups)
	{
		setfillcolor(pu.getColor());
		solidcircle(static_cast<int>(pu.getX()), static_cast<int>(pu.getY()), static_cast<int>(pu.getR()));

		// 符号
		settextcolor(BLACK);
		settextstyle(14, 0, _T("Arial"));
		TCHAR ch;
		switch (pu.getType())
		{
		case POWERUP_WIDE:  ch = _T('W'); break;
		case POWERUP_SLOW:  ch = _T('S'); break;
		case POWERUP_LIFE:  ch = _T('+'); break;
		case POWERUP_MULTI: ch = _T('M'); break;
		default: ch = _T('?');
		}
		TCHAR str[2] = { ch, 0 };
		outtextxy(static_cast<int>(pu.getX()) - 4, static_cast<int>(pu.getY()) - 7, str);
	}
}

void drawHUD()
{
	settextcolor(RGB(255, 255, 255));
	settextstyle(18, 0, _T("Arial"));

	TCHAR buf[120];
	_stprintf_s(buf, _T("分数: %d   最高: %d   关卡: %d"), g_score, g_highScore, g_level);
	outtextxy(20, 20, buf);

	// 生命：心形
	settextstyle(16, 0, _T("Arial"));
	_stprintf_s(buf, _T("生命: %d"), g_lives);
	outtextxy(20, 45, buf);

	_stprintf_s(buf, _T("球数: %zu"), g_balls.size());
	outtextxy(WINDOW_W - 110, 20, buf);

	if (g_slowTimer > 0)
	{
		settextcolor(RGB(180, 180, 255));
		outtextxy(WINDOW_W - 150, 45, _T("减速中"));
	}
	if (g_paddleHalf >= PADDLE_HALF_MAX)
	{
		settextcolor(RGB(0, 220, 255));
		outtextxy(WINDOW_W - 150, 65, _T("加宽中"));
	}

	settextcolor(RGB(180, 180, 180));
	settextstyle(12, 0, _T("Arial"));
	outtextxy(20, WINDOW_H - 40, _T("鼠标控制两个挡板 | 空格暂停 | 右键菜单"));
}

// ============================================================
// 菜单与状态界面
// ============================================================
void drawMenu()
{
	TCHAR buf[120];
	setbkcolor(BLACK);
	cleardevice();

	settextcolor(RGB(255, 240, 180));
	settextstyle(56, 0, _T("Arial Black"));
	outtextxy(170, 460, _T("双 挡 板 挑 战"));

	settextcolor(RGB(200, 200, 200));
	settextstyle(20, 0, _T("Arial"));
	outtextxy(180, 410, _T("Duet Paddle Breakout"));

	settextcolor(RGB(120, 220, 255));
	settextstyle(18, 0, _T("Arial"));
	outtextxy(200, 340, _T("鼠标 X 轴控制底部挡板（水平）"));
	outtextxy(200, 315, _T("鼠标 Y 轴控制右侧挡板（垂直）"));
	outtextxy(200, 290, _T("两个球同时在场，同时堵住两个出口！"));

	// 菜单 Y 坐标（在翻转坐标系中）：开始=230, 说明=190, 退出=150
	// 根据鼠标 Y 动态高亮
	int mouseMenuIdx = g_menuIndex;
	if (g_mouseY > 215 && g_mouseY < 245) mouseMenuIdx = 0;
	else if (g_mouseY > 175 && g_mouseY <= 215) mouseMenuIdx = 1;
	else if (g_mouseY > 135 && g_mouseY <= 175) mouseMenuIdx = 2;
	g_menuIndex = mouseMenuIdx;

	settextcolor(g_menuIndex == 0 ? RGB(255, 255, 100) : RGB(180, 180, 180));
	settextstyle(24, 0, _T("Arial"));
	outtextxy(330, 230, (g_menuIndex == 0 ? _T("> 开始游戏") : _T("  开始游戏")));

	settextcolor(g_menuIndex == 1 ? RGB(255, 255, 100) : RGB(180, 180, 180));
	outtextxy(330, 190, (g_menuIndex == 1 ? _T("> 操作说明") : _T("  操作说明")));

	settextcolor(g_menuIndex == 2 ? RGB(255, 255, 100) : RGB(180, 180, 180));
	outtextxy(330, 150, (g_menuIndex == 2 ? _T("> 退出游戏") : _T("  退出游戏")));

	settextcolor(RGB(120, 120, 120));
	settextstyle(14, 0, _T("Arial"));
	outtextxy(260, 100, _T("移动鼠标选择，左键确认，右键退出"));

	_stprintf_s(buf, _T("最高分: %d"), g_highScore);
	settextcolor(RGB(255, 220, 120));
	outtextxy(330, 70, buf);
}

void drawHelp()
{
	setbkcolor(BLACK);
	cleardevice();

	settextcolor(RGB(255, 240, 180));
	settextstyle(40, 0, _T("Arial Black"));
	outtextxy(270, 500, _T("操作说明"));

	settextcolor(RGB(220, 220, 220));
	settextstyle(18, 0, _T("Arial"));

	outtextxy(80, 450, _T("◆ 鼠标 X 轴 — 控制底部水平挡板（蓝色）"));
	outtextxy(80, 420, _T("◆ 鼠标 Y 轴 — 控制右侧垂直挡板（粉色）"));
	outtextxy(80, 390, _T("◆ 两个球在场内同时运动"));
	outtextxy(80, 360, _T("◆ 从底部或右侧漏出即损失一条生命"));

	outtextxy(80, 320, _T("砖块类型："));
	settextcolor(RGB(255, 90, 90));
	outtextxy(120, 295, _T("■ 普通 — 一击即碎"));
	settextcolor(RGB(255, 180, 70));
	outtextxy(120, 270, _T("■ 坚硬 — 需两次击打"));
	settextcolor(RGB(80, 220, 120));
	outtextxy(120, 245, _T("■ 超级 — 需三次击打"));
	settextcolor(RGB(255, 120, 0));
	outtextxy(120, 220, _T("■ 爆炸 — 摧毁相邻砖块"));
	settextcolor(RGB(120, 120, 120));
	outtextxy(120, 195, _T("■ 不可破坏 — 障碍"));

	settextcolor(RGB(120, 220, 255));
	outtextxy(80, 160, _T("道具：W=加宽挡板  S=减速  +=生命  M=多球"));

	settextcolor(RGB(255, 255, 100));
	settextstyle(22, 0, _T("Arial"));
	outtextxy(280, 100, _T("左键单击 返回菜单"));
}

void drawPauseOverlay()
{
	// 用半透明感的横线叠加
	setlinecolor(RGB(0, 0, 0));
	for (int y = 0; y < WINDOW_H; y += 3)
	{
		line(0, y, WINDOW_W, y);
	}

	settextcolor(RGB(255, 255, 255));
	settextstyle(60, 0, _T("Arial Black"));
	outtextxy(260, 330, _T("已 暂 停"));

	settextstyle(22, 0, _T("Arial"));
	outtextxy(200, 260, _T("按 空格 继续  |  右键 返回菜单"));
}

void drawLevelClear()
{
	setfillcolor(RGB(0, 0, 0));
	cleardevice();

	settextcolor(RGB(120, 255, 180));
	settextstyle(50, 0, _T("Arial Black"));
	outtextxy(220, 380, _T("关卡通过！"));

	TCHAR buf[120];
	settextcolor(RGB(255, 240, 180));
	settextstyle(26, 0, _T("Arial"));
	_stprintf_s(buf, _T("当前分数：%d"), g_score);
	outtextxy(280, 320, buf);
	_stprintf_s(buf, _T("即将进入第 %d 关"), g_level + 1);
	outtextxy(260, 280, buf);

	settextcolor(RGB(220, 220, 220));
	settextstyle(20, 0, _T("Arial"));
	outtextxy(240, 220, _T("左键单击 继续下一关"));
}

void drawGameOver()
{
	setbkcolor(BLACK);
	cleardevice();

	settextcolor(RGB(255, 80, 80));
	settextstyle(64, 0, _T("Arial Black"));
	outtextxy(200, 380, _T("游戏结束"));

	TCHAR buf[120];
	settextcolor(RGB(255, 240, 180));
	settextstyle(28, 0, _T("Arial"));
	_stprintf_s(buf, _T("最终分数：%d"), g_score);
	outtextxy(270, 310, buf);
	_stprintf_s(buf, _T("到达关卡：%d"), g_level);
	outtextxy(290, 270, buf);
	_stprintf_s(buf, _T("历史最高：%d"), g_highScore);
	outtextxy(290, 230, buf);

	settextcolor(RGB(220, 220, 220));
	settextstyle(20, 0, _T("Arial"));
	outtextxy(230, 170, _T("左键 重新开始   |   右键 返回主菜单"));
}

void drawWin()
{
	setbkcolor(BLACK);
	cleardevice();

	settextcolor(RGB(255, 230, 100));
	settextstyle(64, 0, _T("Arial Black"));
	outtextxy(180, 380, _T("通关胜利！"));

	TCHAR buf[120];
	settextcolor(RGB(255, 255, 255));
	settextstyle(28, 0, _T("Arial"));
	_stprintf_s(buf, _T("最终分数：%d"), g_score);
	outtextxy(270, 310, buf);
	_stprintf_s(buf, _T("历史最高：%d"), g_highScore);
	outtextxy(290, 270, buf);

	settextcolor(RGB(220, 220, 220));
	settextstyle(20, 0, _T("Arial"));
	outtextxy(230, 200, _T("左键 重新开始   |   右键 返回主菜单"));
}

// ============================================================
// 主函数
// ============================================================
int main()
{
	srand(static_cast<unsigned>(time(NULL)));
	initgraph(WINDOW_W, WINDOW_H);
	setorigin(0, WINDOW_H);
	setaspectratio(1, -1);
	setbkcolor(BLACK);
	cleardevice();

	// 读取最高分（简易文件）
	FILE* fp = NULL;
	_fopen_s(&fp, "highscore.txt", "r");
	if (fp)
	{
		if (fscanf_s(fp, "%d", &g_highScore) != 1) g_highScore = 0;
		fclose(fp);
	}

	ExMessage mouse;
	bool showingHelp = false;

	BeginBatchDraw();
	while (true)
	{
		// 输入处理
		while (peekmessage(&mouse, EM_MOUSE | EM_KEY))
		{
			// 鼠标坐标转换到数学坐标系（Y 翻转）
			if (mouse.message == WM_MOUSEMOVE || mouse.message == WM_LBUTTONDOWN ||
				mouse.message == WM_RBUTTONDOWN || mouse.message == WM_MOUSEWHEEL)
			{
				g_mouseX = mouse.x;
				g_mouseY = WINDOW_H - mouse.y;
				g_mouseX = max(WALL_THICK + g_paddleHalf, min(WINDOW_W - WALL_THICK - g_paddleHalf, g_mouseX));
				g_mouseY = max(WALL_THICK + g_paddleHalf, min(WINDOW_H - WALL_THICK - g_paddleHalf, g_mouseY));
			}

			if (mouse.message == WM_LBUTTONDOWN)
			{
				g_mouseLeftPressed = true;
			}
			if (mouse.message == WM_RBUTTONDOWN)
			{
				g_mouseRightPressed = true;
			}
			if (mouse.message == WM_MOUSEWHEEL)
			{
				short delta = GET_WHEEL_DELTA_WPARAM(mouse.wparam);
				if (g_state == STATE_MENU && !showingHelp)
				{
					if (delta > 0) g_menuIndex = (g_menuIndex + 2) % 3;
					else g_menuIndex = (g_menuIndex + 1) % 3;
				}
			}
			if (mouse.message == WM_KEYDOWN)
			{
				if (mouse.vkcode == VK_SPACE) g_spacePressed = true;
				if (mouse.vkcode == VK_UP && g_state == STATE_MENU && !showingHelp)
					g_menuIndex = (g_menuIndex + 2) % 3;
				if (mouse.vkcode == VK_DOWN && g_state == STATE_MENU && !showingHelp)
					g_menuIndex = (g_menuIndex + 1) % 3;
				if (mouse.vkcode == VK_RETURN && g_state == STATE_MENU && !showingHelp)
					g_mouseLeftPressed = true;
				if (mouse.vkcode == VK_ESCAPE)
					g_mouseRightPressed = true;
			}
		}

		// 状态逻辑
		switch (g_state)
		{
		case STATE_MENU:
		{
			if (showingHelp)
			{
				drawHelp();
				if (g_mouseLeftPressed || g_mouseRightPressed)
				{
					showingHelp = false;
					g_mouseLeftPressed = false;
					g_mouseRightPressed = false;
				}
			}
			else
			{
				drawMenu();
				if (g_mouseLeftPressed)
				{
					if (g_menuIndex == 0) startLevel(true);
					else if (g_menuIndex == 1) showingHelp = true;
					else if (g_menuIndex == 2) { EndBatchDraw(); closegraph(); return 0; }
				}
				if (g_mouseRightPressed)
				{
					EndBatchDraw(); closegraph(); return 0;
				}
			}
			break;
		}
		case STATE_PLAYING:
		{
			if (g_spacePressed)
			{
				g_state = STATE_PAUSED;
				g_spacePressed = false;
			}
			else
			{
				updateGame();
				setbkcolor(BLACK);
				cleardevice();
				drawWalls();
				for (auto& br : g_bricks) if (br.isAlive()) drawBrick(br);
				drawPowerUps();
				drawBalls();
				drawParticles();
				drawPaddles();
				drawHUD();
			}
			if (g_mouseRightPressed)
			{
				g_state = STATE_MENU;
				g_mouseRightPressed = false;
			}
			break;
		}
		case STATE_PAUSED:
		{
			// 先画场景再画遮罩
			setbkcolor(BLACK);
			cleardevice();
			drawWalls();
			for (auto& br : g_bricks) if (br.isAlive()) drawBrick(br);
			drawPowerUps();
			drawBalls();
			drawParticles();
			drawPaddles();
			drawHUD();
			drawPauseOverlay();

			if (g_spacePressed)
			{
				g_state = STATE_PLAYING;
				g_spacePressed = false;
			}
			if (g_mouseRightPressed)
			{
				g_state = STATE_MENU;
				g_mouseRightPressed = false;
			}
			break;
		}
		case STATE_LEVEL_CLEAR:
		{
			drawLevelClear();
			if (g_mouseLeftPressed)
			{
				g_level++;
				startLevel(false);
				g_mouseLeftPressed = false;
			}
			break;
		}
		case STATE_GAME_OVER:
		{
			drawGameOver();
			if (g_mouseLeftPressed)
			{
				startLevel(true);
				g_mouseLeftPressed = false;
			}
			if (g_mouseRightPressed)
			{
				g_state = STATE_MENU;
				g_mouseRightPressed = false;
			}
			break;
		}
		case STATE_WIN:
		{
			drawWin();
			if (g_mouseLeftPressed)
			{
				startLevel(true);
				g_mouseLeftPressed = false;
			}
			if (g_mouseRightPressed)
			{
				g_state = STATE_MENU;
				g_mouseRightPressed = false;
			}
			break;
		}
		default:
			g_state = STATE_MENU;
			break;
		}

		FlushBatchDraw();
		Sleep(16);  // ~60 FPS
	}

	EndBatchDraw();

	// 保存最高分
	_fopen_s(&fp, "highscore.txt", "w");
	if (fp)
	{
		fprintf(fp, "%d", g_highScore);
		fclose(fp);
	}

	closegraph();
	return 0;
}
