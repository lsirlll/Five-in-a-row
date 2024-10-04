#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

// 函数项目里放变量

// 把变量放到用它的地方
static IMAGE bk; // 背景图片全局变量

static int map[ROW][COL]; // 棋子装到数组 1是黑棋 2是白棋

static struct Pos
{
	// 鼠标的位置
	int row;
	int col;
	bool isShow; // 是否记录蓝色的框
	int player;
}pos;


void game2()
{
	// 将窗口居中
	centerWindow(600, 500);

	loadResource();
	initializeGame();

	while (1)
	{
		// 双缓存机制
		BeginBatchDraw();
		drawBoard();
		EndBatchDraw();

		// 定义鼠标消息
		ExMessage msg;

		// 鼠标点击以后，获取消息
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
				// 鼠标移动
			case WM_MOUSEMOVE:
				mouseMoveMsg(&msg);

				// 鼠标点击
			case WM_LBUTTONDOWN:
				mousePressMsg(&msg);
			default:
				break;
			}
		}
	}
	system("pause");
	closegraph();
}


//加载资源
static void loadResource()
{
	// 背景界面
	initgraph(600, 500); // 600,500的窗口
	// 加载图片
	loadimage(&bk, "Resource/image/bk.jpg"); // 背景图路径，Resource在整个项目下第二层，和game.cpp同一层
}


// 初始化玩家为黑棋
static void initializeGame()
{
	pos.player = Black; // 设置第一个玩家为黑棋
}


// 画棋盘
static void drawBoard()
{
	// 屏幕输出图片
	putimage(-500, -100, &bk); // 输出起点,从图片左上角开始,起点负数在图片下方，正数在图片上方


	// 棋盘线
	// 线的颜色
	setlinecolor(BLACK); // 设置为黑色
	// 线的样式
	setlinestyle(BLACK); 
	
	// 画15条线
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		// 画线  第一个，起点的横坐标；第二个，起点的纵坐标；
			  // 第三个，终点的横坐标；第四个，终点的纵坐标
			  
		// 横坐标固定值，纵坐标在变，画横线,i画15条，改i-1是为了不溢出，因为第一条是没有穿插的
		line(X_SPACE, i * GRID_W + Y_SPACE, 14 * GRID_W + X_SPACE, i * GRID_W + Y_SPACE);
		// 纵坐标固定值，横坐标在变，画竖线
		line(i * GRID_W + X_SPACE, Y_SPACE, i * GRID_W + X_SPACE, 14 * GRID_W + Y_SPACE);
	}

	// 矩形线的样式
	setlinestyle(PS_SOLID, 3); // 设置矩形线样式加粗
	// 绘制一个矩形，左上角点的坐标，右下角点的坐标
	rectangle(X_SPACE, Y_SPACE, X_SPACE + 14 * GRID_W, Y_SPACE + 14 * GRID_W);

	// 填充圆的一个颜色
	setfillcolor(BLACK);
	// 五个点 圆心的x坐标，圆心的y坐标，圆的半径
	solidcircle(X_SPACE + 7 * GRID_W, Y_SPACE + 7 * GRID_W, 5); // 中心
	solidcircle(X_SPACE + (7 - 4) * GRID_W, Y_SPACE + (7 - 4) * GRID_W, 5); // 左上
	solidcircle(X_SPACE + 3 * GRID_W, Y_SPACE + 11 * GRID_W, 5); // 左下
	solidcircle(X_SPACE + 11 * GRID_W, Y_SPACE + 3 * GRID_W, 5); // 右上
	solidcircle(X_SPACE + 11 * GRID_W, Y_SPACE + 11 * GRID_W, 5); // 右下
	
	// 绘制棋子
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			// 黑棋
			if (map[i][k] == Black)
			{
				setfillcolor(BLACK); // 颜色
				// 坐标位置
				solidcircle(k * GRID_W + X_SPACE, i * GRID_W + Y_SPACE, 10);
			}
			// 白棋
			else if (map[i][k] == White)
			{
				setfillcolor(WHITE); // 颜色
				// 坐标位置
				solidcircle(k * GRID_W + X_SPACE, i * GRID_W + Y_SPACE, 10);
			}
		}
	}

	// 鼠标移动要有一个蓝色的框
	if (pos.isShow) // 如果框显示，则画一个矩形
	{
		setlinecolor(BLUE);
		// 改变框的位置 框的起点就是鼠标的起点pos.row和pos.col  框的大小
		rectangle((pos.col + 5) * GRID_W - 12, (pos.row + 3) * GRID_W - 12, (pos.col + 5) * GRID_W + 12, (pos.row + 3) * GRID_W + 12);
	}

}


// 鼠标移动 框要跟着鼠标走
static void mouseMoveMsg(ExMessage* msg)
{
	// 获取鼠标 鼠标的下标
	pos.isShow = false;

	// 遍历每个格子 判断蓝色格子是否在棋盘内部
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			// 左上坐标
			
			int gridx = k * GRID_W+X_SPACE;
			int gridy = i * GRID_W+Y_SPACE;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				// 在棋盘里，然后在鼠标的范围之内
				pos.isShow = true;
				pos.row = i;
				pos.col = k;
			}
		}
	}
}


// 按下鼠标
static void mousePressMsg(ExMessage* msg)
{
	// 左键还是右键
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (map[pos.row][pos.col] == NONE) // 在空白的地方才能下棋
		{
			map[pos.row][pos.col] = pos.player;
			// 判断输赢
			if (isWin(pos.row, pos.col))
			{
				drawBoard(); // 确保最后一个棋子被显示
				MessageBox(GetHWnd(), "Your Win!", "hit", MB_OK);
				exit(0);
			}

			// 切换棋手
			pos.player = (pos.player == Black) ? White : Black;
		}
	}
}


// 判断输赢
static int isWin(int r, int c)
{
	// 检查水平方向
	for (int i = c - 4; i <= c; i++)
	{
		if (i >= 0 && i <= c && i + 4 < COL &&
			map[r][i] == pos.player &&
			map[r][i + 1] == pos.player &&
			map[r][i + 2] == pos.player &&
			map[r][i + 3] == pos.player &&
			map[r][i + 4] == pos.player)
		{
			return 1;
		}
	}

	// 检查垂直方向
	for (int i = r - 4; i <= r; i++)
	{
		if (i >= 0 && i <= r && i + 4 < ROW &&
			map[i][c] == pos.player &&
			map[i + 1][c] == pos.player &&
			map[i + 2][c] == pos.player &&
			map[i + 3][c] == pos.player &&
			map[i + 4][c] == pos.player)
		{
			return 1;
		}
	}

	// 检查右斜方向（\）
	for (int i = -4; i <= 0; i++)
	{
		if (r + i >= 0 && r + i < ROW &&
			c + i >= 0 && c + i < COL &&
			r + i + 4 < ROW && c + i + 4 < COL &&
			map[r + i][c + i] == pos.player &&
			map[r + i + 1][c + i + 1] == pos.player &&
			map[r + i + 2][c + i + 2] == pos.player &&
			map[r + i + 3][c + i + 3] == pos.player &&
			map[r + i + 4][c + i + 4] == pos.player)
		{
			return 1;
		}
	}

	// 检查左斜方向（/）
	for (int i = -4; i <= 0; i++)
	{
		if (r + i >= 0 && r + i < ROW &&
			c - i >= 0 && c - i < COL &&
			r + i + 4 < ROW && c - i - 4 >= 0 &&
			map[r + i][c - i] == pos.player &&
			map[r + i + 1][c - i - 1] == pos.player &&
			map[r + i + 2][c - i - 2] == pos.player &&
			map[r + i + 3][c - i - 3] == pos.player &&
			map[r + i + 4][c - i - 4] == pos.player)
		{
			return 1;
		}
	}

	return 0;
}