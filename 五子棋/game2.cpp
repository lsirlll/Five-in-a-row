#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

// ������Ŀ��ű���

// �ѱ����ŵ������ĵط�
static IMAGE bk; // ����ͼƬȫ�ֱ���

static int map[ROW][COL]; // ����װ������ 1�Ǻ��� 2�ǰ���

static struct Pos
{
	// ����λ��
	int row;
	int col;
	bool isShow; // �Ƿ��¼��ɫ�Ŀ�
	int player;
}pos;


void game2()
{
	// �����ھ���
	centerWindow(600, 500);

	loadResource();
	initializeGame();

	while (1)
	{
		// ˫�������
		BeginBatchDraw();
		drawBoard();
		EndBatchDraw();

		// ���������Ϣ
		ExMessage msg;

		// ������Ժ󣬻�ȡ��Ϣ
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
				// ����ƶ�
			case WM_MOUSEMOVE:
				mouseMoveMsg(&msg);

				// �����
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


//������Դ
static void loadResource()
{
	// ��������
	initgraph(600, 500); // 600,500�Ĵ���
	// ����ͼƬ
	loadimage(&bk, "Resource/image/bk.jpg"); // ����ͼ·����Resource��������Ŀ�µڶ��㣬��game.cppͬһ��
}


// ��ʼ�����Ϊ����
static void initializeGame()
{
	pos.player = Black; // ���õ�һ�����Ϊ����
}


// ������
static void drawBoard()
{
	// ��Ļ���ͼƬ
	putimage(-500, -100, &bk); // ������,��ͼƬ���Ͻǿ�ʼ,��㸺����ͼƬ�·���������ͼƬ�Ϸ�


	// ������
	// �ߵ���ɫ
	setlinecolor(BLACK); // ����Ϊ��ɫ
	// �ߵ���ʽ
	setlinestyle(BLACK); 
	
	// ��15����
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		// ����  ��һ�������ĺ����ꣻ�ڶ��������������ꣻ
			  // ���������յ�ĺ����ꣻ���ĸ����յ��������
			  
		// ������̶�ֵ���������ڱ䣬������,i��15������i-1��Ϊ�˲��������Ϊ��һ����û�д����
		line(X_SPACE, i * GRID_W + Y_SPACE, 14 * GRID_W + X_SPACE, i * GRID_W + Y_SPACE);
		// ������̶�ֵ���������ڱ䣬������
		line(i * GRID_W + X_SPACE, Y_SPACE, i * GRID_W + X_SPACE, 14 * GRID_W + Y_SPACE);
	}

	// �����ߵ���ʽ
	setlinestyle(PS_SOLID, 3); // ���þ�������ʽ�Ӵ�
	// ����һ�����Σ����Ͻǵ�����꣬���½ǵ������
	rectangle(X_SPACE, Y_SPACE, X_SPACE + 14 * GRID_W, Y_SPACE + 14 * GRID_W);

	// ���Բ��һ����ɫ
	setfillcolor(BLACK);
	// ����� Բ�ĵ�x���꣬Բ�ĵ�y���꣬Բ�İ뾶
	solidcircle(X_SPACE + 7 * GRID_W, Y_SPACE + 7 * GRID_W, 5); // ����
	solidcircle(X_SPACE + (7 - 4) * GRID_W, Y_SPACE + (7 - 4) * GRID_W, 5); // ����
	solidcircle(X_SPACE + 3 * GRID_W, Y_SPACE + 11 * GRID_W, 5); // ����
	solidcircle(X_SPACE + 11 * GRID_W, Y_SPACE + 3 * GRID_W, 5); // ����
	solidcircle(X_SPACE + 11 * GRID_W, Y_SPACE + 11 * GRID_W, 5); // ����
	
	// ��������
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			// ����
			if (map[i][k] == Black)
			{
				setfillcolor(BLACK); // ��ɫ
				// ����λ��
				solidcircle(k * GRID_W + X_SPACE, i * GRID_W + Y_SPACE, 10);
			}
			// ����
			else if (map[i][k] == White)
			{
				setfillcolor(WHITE); // ��ɫ
				// ����λ��
				solidcircle(k * GRID_W + X_SPACE, i * GRID_W + Y_SPACE, 10);
			}
		}
	}

	// ����ƶ�Ҫ��һ����ɫ�Ŀ�
	if (pos.isShow) // �������ʾ����һ������
	{
		setlinecolor(BLUE);
		// �ı���λ�� ����������������pos.row��pos.col  ��Ĵ�С
		rectangle((pos.col + 5) * GRID_W - 12, (pos.row + 3) * GRID_W - 12, (pos.col + 5) * GRID_W + 12, (pos.row + 3) * GRID_W + 12);
	}

}


// ����ƶ� ��Ҫ���������
static void mouseMoveMsg(ExMessage* msg)
{
	// ��ȡ��� �����±�
	pos.isShow = false;

	// ����ÿ������ �ж���ɫ�����Ƿ��������ڲ�
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			// ��������
			
			int gridx = k * GRID_W+X_SPACE;
			int gridy = i * GRID_W+Y_SPACE;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				// �������Ȼ�������ķ�Χ֮��
				pos.isShow = true;
				pos.row = i;
				pos.col = k;
			}
		}
	}
}


// �������
static void mousePressMsg(ExMessage* msg)
{
	// ��������Ҽ�
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (map[pos.row][pos.col] == NONE) // �ڿհ׵ĵط���������
		{
			map[pos.row][pos.col] = pos.player;
			// �ж���Ӯ
			if (isWin(pos.row, pos.col))
			{
				drawBoard(); // ȷ�����һ�����ӱ���ʾ
				MessageBox(GetHWnd(), "Your Win!", "hit", MB_OK);
				exit(0);
			}

			// �л�����
			pos.player = (pos.player == Black) ? White : Black;
		}
	}
}


// �ж���Ӯ
static int isWin(int r, int c)
{
	// ���ˮƽ����
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

	// ��鴹ֱ����
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

	// �����б����\��
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

	// �����б����/��
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