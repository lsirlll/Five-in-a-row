#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

void drawMainMenu();
void drawCenteredText(int x, int y, int width, int height, const char* text);
void mousePressMsg(ExMessage* msg);


// 主函数项目里放函数
IMAGE bk;
ExMessage msg;


// 窗口水平居中
void centerWindow(int width, int height)
{
	// 获取屏幕尺寸
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	int screenWidth = desktop.right;
	int screenHeight = desktop.bottom;

	// 计算窗口左上角坐标
	int x = (screenWidth - width) / 2;
	int y = (screenHeight - height) / 2;

	// 设置窗口位置
	HWND hwnd = GetConsoleWindow(); // 获取控制台窗口句柄
	MoveWindow(hwnd, x, y, width, height, TRUE);
}


// 最小化输出窗口
void minimizeWindow()
{
	HWND hWnd = GetHWnd(); // 获取当前窗口句柄
	ShowWindow(hWnd, SW_MINIMIZE); // 最小化窗口
}


void drawMainMenu()
{
	// 背景界面
	initgraph(600, 500); // 600,500的窗口
	// 加载图片
	loadimage(&bk, "Resource/image/bk.jpg"); // 背景图路径，Resource在整个项目下第二层，和game.cpp同一层
	// 屏幕输出图片
	putimage(-500, -100, &bk); // 输出起点,从图片左上角开始,起点负数在图片下方，正数在图片上方

	setlinestyle(PS_SOLID, 3); // 设置矩形线样式加粗
	// 第一个矩形
	setfillcolor(BLACK);
	fillrectangle(150, 80, 450, 180); // 填充矩形
	rectangle(150, 80, 450, 180);
	// 第二个矩形
	setfillcolor(BLACK);
	fillrectangle(150, 200, 450, 300); // 填充矩形
	rectangle(150, 200, 450, 300);
	// 第三个矩形
	setfillcolor(BLACK);
	fillrectangle(150, 320, 450, 420); // 填充矩形
	rectangle(150, 320, 450, 420);


	// 绘制文本
	drawCenteredText(150, 80, 300, 100, "1.Computer Play");
	drawCenteredText(150, 200, 300, 100, "2.Player Play");
	drawCenteredText(150, 320, 300, 100, "0.Exit");

	//system("pause"); // 窗口常驻
}


void drawCenteredText(int x, int y, int width, int height, const char* text)
{
	// 设置文字颜色为白色
	settextcolor(WHITE);

	// 设置文字样式（可以根据需要调整）
	settextstyle(20, 0, "微软雅黑");

	// 计算文本宽度和高度
	int textWidth = textwidth(text);
	int textHeight = textheight(text);

	// 计算居中位置
	int textX = x + (width - textWidth) / 2;
	int textY = y + (height - textHeight) / 2;

	// 绘制文本
	outtextxy(textX, textY, text);
}


// 调用函数
void mousePressMsg(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		int mouseX = msg->x;
		int mouseY = msg->y;

		// 检查是否在第一个矩形内
		if (mouseX >= 150 && mouseX <= 450 && mouseY >= 80 && mouseY <= 180)
		{
			// 调用人机对战的函数
			game1();
			exit(0); 
		}
		else if (mouseX >= 150 && mouseX <= 450 && mouseY >= 200 && mouseY <= 300)
		{
			// 调用玩家对战的函数
			game2();
			exit(0);
		}
		else if (mouseX >= 150 && mouseX <= 450 && mouseY >= 320 && mouseY <= 420)
		{
			exit(0);
		}
	}
}


int main()
{
	// 将窗口居中
	centerWindow(600, 500); 
	minimizeWindow();
	Sleep(1);
	minimizeWindow(); // 输出窗口最小化


	while (true)
	{
		drawMainMenu(); // 绘制主菜单

		while (true)
		{
			if (peekmessage(&msg, EM_MOUSE)) // 检测鼠标事件
			{
				mousePressMsg(&msg);
			}
		}
	}

	system("pause");
	closegraph();

	return 0;
}