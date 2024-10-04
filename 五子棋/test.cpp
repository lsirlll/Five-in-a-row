#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

void drawMainMenu();
void drawCenteredText(int x, int y, int width, int height, const char* text);
void mousePressMsg(ExMessage* msg);


// ��������Ŀ��ź���
IMAGE bk;
ExMessage msg;


// ����ˮƽ����
void centerWindow(int width, int height)
{
	// ��ȡ��Ļ�ߴ�
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	int screenWidth = desktop.right;
	int screenHeight = desktop.bottom;

	// ���㴰�����Ͻ�����
	int x = (screenWidth - width) / 2;
	int y = (screenHeight - height) / 2;

	// ���ô���λ��
	HWND hwnd = GetConsoleWindow(); // ��ȡ����̨���ھ��
	MoveWindow(hwnd, x, y, width, height, TRUE);
}


// ��С���������
void minimizeWindow()
{
	HWND hWnd = GetHWnd(); // ��ȡ��ǰ���ھ��
	ShowWindow(hWnd, SW_MINIMIZE); // ��С������
}


void drawMainMenu()
{
	// ��������
	initgraph(600, 500); // 600,500�Ĵ���
	// ����ͼƬ
	loadimage(&bk, "Resource/image/bk.jpg"); // ����ͼ·����Resource��������Ŀ�µڶ��㣬��game.cppͬһ��
	// ��Ļ���ͼƬ
	putimage(-500, -100, &bk); // ������,��ͼƬ���Ͻǿ�ʼ,��㸺����ͼƬ�·���������ͼƬ�Ϸ�

	setlinestyle(PS_SOLID, 3); // ���þ�������ʽ�Ӵ�
	// ��һ������
	setfillcolor(BLACK);
	fillrectangle(150, 80, 450, 180); // ������
	rectangle(150, 80, 450, 180);
	// �ڶ�������
	setfillcolor(BLACK);
	fillrectangle(150, 200, 450, 300); // ������
	rectangle(150, 200, 450, 300);
	// ����������
	setfillcolor(BLACK);
	fillrectangle(150, 320, 450, 420); // ������
	rectangle(150, 320, 450, 420);


	// �����ı�
	drawCenteredText(150, 80, 300, 100, "1.Computer Play");
	drawCenteredText(150, 200, 300, 100, "2.Player Play");
	drawCenteredText(150, 320, 300, 100, "0.Exit");

	//system("pause"); // ���ڳ�פ
}


void drawCenteredText(int x, int y, int width, int height, const char* text)
{
	// ����������ɫΪ��ɫ
	settextcolor(WHITE);

	// ����������ʽ�����Ը�����Ҫ������
	settextstyle(20, 0, "΢���ź�");

	// �����ı���Ⱥ͸߶�
	int textWidth = textwidth(text);
	int textHeight = textheight(text);

	// �������λ��
	int textX = x + (width - textWidth) / 2;
	int textY = y + (height - textHeight) / 2;

	// �����ı�
	outtextxy(textX, textY, text);
}


// ���ú���
void mousePressMsg(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		int mouseX = msg->x;
		int mouseY = msg->y;

		// ����Ƿ��ڵ�һ��������
		if (mouseX >= 150 && mouseX <= 450 && mouseY >= 80 && mouseY <= 180)
		{
			// �����˻���ս�ĺ���
			game1();
			exit(0); 
		}
		else if (mouseX >= 150 && mouseX <= 450 && mouseY >= 200 && mouseY <= 300)
		{
			// ������Ҷ�ս�ĺ���
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
	// �����ھ���
	centerWindow(600, 500); 
	minimizeWindow();
	Sleep(1);
	minimizeWindow(); // ���������С��


	while (true)
	{
		drawMainMenu(); // �������˵�

		while (true)
		{
			if (peekmessage(&msg, EM_MOUSE)) // �������¼�
			{
				mousePressMsg(&msg);
			}
		}
	}

	system("pause");
	closegraph();

	return 0;
}