#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

// ������Ŀ��ű���

static IMAGE bk; // ����ͼƬȫ�ֱ���

static int map[ROW][COL]; // ����װ�����飬NONE��ʾû������

static struct Pos
{
    int row;
    int col;
    bool isShow; // �Ƿ��¼��ɫ�Ŀ�
    int player;  // ��ǰ���
} pos;


void game1()
{
    // �����ھ���
    centerWindow(600, 500);
    
    srand((unsigned int)time(NULL));
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


static void initMap(int i)
{
    switch (i)
    {
    case 0:
        map[7 + rand() % 4][7 + rand() % 4] = White;
        break;
    case 1:
        map[7 - rand() % 4][7 + rand() % 4] = White;
        break;
    case 2:
        map[7 - rand() % 4][7 - rand() % 4] = White;
        break;
    case 3:
        map[7 + rand() % 4][7 - rand() % 4] = White;
        break;
    default:
        break;
    }
}


// ������Դ
static void loadResource()
{
    initgraph(600, 500); // ���ڴ�С
    loadimage(&bk, "Resource/image/bk.jpg"); // ���ر���ͼ
    int i = rand() % 4;
    initMap(i);
}


// ��ʼ����Ϸ
static void initializeGame()
{
    pos.player = Black; // ���Ϊ����
    memset(map, NONE, sizeof(map)); // ��ʼ������Ϊ��
    // ��������
    map[7 + rand() % 2][7 + rand() % 2] = White;
}


// ������
static void drawBoard()
{
    putimage(-500, -100, &bk); // ���Ʊ���

    // ����������
    setlinecolor(BLACK);
    setlinestyle(BLACK);

    for (int i = 0; i < ROW; i++)
    {
        line(X_SPACE, i * GRID_W + Y_SPACE, 14 * GRID_W + X_SPACE, i * GRID_W + Y_SPACE);
        line(i * GRID_W + X_SPACE, Y_SPACE, i * GRID_W + X_SPACE, 14 * GRID_W + Y_SPACE);
    }

    setlinestyle(PS_SOLID, 3);
    rectangle(X_SPACE, Y_SPACE, X_SPACE + 14 * GRID_W, Y_SPACE + 14 * GRID_W);

    // ��������
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COL; k++)
        {
            if (map[i][k] == Black)
            {
                setfillcolor(BLACK);
                solidcircle((k + 5) * GRID_W, (i + 3) * GRID_W, 10);
            }
            else if (map[i][k] == White)
            {
                setfillcolor(WHITE);
                solidcircle((k + 5) * GRID_W, (i + 3) * GRID_W, 10);
            }
        }
    }

    // ��������
    if (pos.isShow)
    {
        setlinecolor(BLUE);
        rectangle((pos.col + 5) * GRID_W - 12, (pos.row + 3) * GRID_W - 12, (pos.col + 5) * GRID_W + 12, (pos.row + 3) * GRID_W + 12);
    }
}


// ����ƶ�
static void mouseMoveMsg(ExMessage* msg)
{
    pos.isShow = false;

    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COL; k++)
        {
            int gridx = (k + 5) * GRID_W;
            int gridy = (i + 3) * GRID_W;
            if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
            {
                pos.isShow = true;
                pos.row = i;
                pos.col = k;
            }
        }
    }
}


// ��갴��
static void mousePressMsg(ExMessage* msg)
{
    if (msg->message == WM_LBUTTONDOWN)
    {
       if (map[pos.row][pos.col] == NONE) // ȷ��λ��Ϊ��
       {
            map[pos.row][pos.col] = pos.player; // �������

            // �ж�ʤ��
            if (isWin(pos.row, pos.col) == 1)
            {
                drawBoard();
                MessageBox(GetHWnd(), "Your Win!", "hit", MB_OK);
                exit(0);
            }

            // �л�������
            pos.player = White;
            computerMove();

            // �������Ƿ�ʤ��
            if (isWin(pos.row, pos.col) == 1)
            {
                drawBoard();
                MessageBox(GetHWnd(), "Computer Wins!", "hit", MB_OK);
                exit(0);
            }

            // �л������
            pos.player = Black;
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


// ���ֺ���
static int evaluatePosition(int row, int col, int player)
{
    int score = 0;

    // ��������ʹ��һЩ�򵥵����ֹ���
    // ����λ����Χ�����ӣ�����ͬ���������Ӹ��費ͬ�ķ�ֵ

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r == 0 && c == 0) continue; // ��������λ��

            int count = 0;
            int emptyCount = 0;

            // ���÷����ϵ�����
            for (int step = 1; step < 5; step++) {
                int newRow = row + r * step;
                int newCol = col + c * step;

                // �߽���
                if (newRow < 0 || newRow >= ROW || newCol < 0 || newCol >= COL) break;

                if (map[newRow][newCol] == player) {
                    count++;
                }
                else if (map[newRow][newCol] == NONE) {
                    emptyCount++;
                    break; // ������λ��ֹͣ
                }
                else {
                    break; // ������������ֹͣ
                }
            }

            // �����߼������Ը���ʵ���������
            if (count > 0) {
                score += (int)pow(10, count); // ��������Խ�࣬����Խ��
            }
        }
    }

    return score;
}


 // ��������
static void computerMove()
{
    int bestScore = -1;
    int bestRow = -1;
    int bestCol = -1;


    // ��ֹ��ҵ�ʤ��
    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j <= 15; j++)
        {
            if (map[i][j] == NONE)
            {
                // ��ʱ����������
                map[i][j] = Black; // ��������Ǻ���
                if (isWin(i, j) == 1 || isWin(i, j) == 2 || isWin(i, j) == 3) // ����Ƿ���Ӯ
                {
                    map[i][j] = White; // ��ֹ��ҵ���
                    pos.row = i;
                    pos.col = j;
                    return; // �������������������
                }
                map[i][j] = NONE; // ������ʱ����
            }
        }
    }

    // ���ֺ���ѡ�����λ��
    for (int i = 5; i <= 19; i++)
    {
        for (int j = 3; j <= 17; j++)
        {
            if (map[i][j] == NONE) // ֻ���ǿ�λ��
            {
                // ������λ�õķ�ֵ
                int score = evaluatePosition(i, j, White);
                if (score > bestScore)
                {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    // �����λ������
    if (bestRow != -1 && bestCol != -1)
    {
        map[bestRow][bestCol] = White;
        pos.row = bestRow;
        pos.col = bestCol;
    }
}