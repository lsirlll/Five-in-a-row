#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

// 函数项目里放变量

static IMAGE bk; // 背景图片全局变量

static int map[ROW][COL]; // 棋子装到数组，NONE表示没有棋子

static struct Pos
{
    int row;
    int col;
    bool isShow; // 是否记录蓝色的框
    int player;  // 当前玩家
} pos;


void game1()
{
    // 将窗口居中
    centerWindow(600, 500);
    
    srand((unsigned int)time(NULL));
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


// 加载资源
static void loadResource()
{
    initgraph(600, 500); // 窗口大小
    loadimage(&bk, "Resource/image/bk.jpg"); // 加载背景图
    int i = rand() % 4;
    initMap(i);
}


// 初始化游戏
static void initializeGame()
{
    pos.player = Black; // 玩家为黑棋
    memset(map, NONE, sizeof(map)); // 初始化棋盘为空
    // 电脑下棋
    map[7 + rand() % 2][7 + rand() % 2] = White;
}


// 画棋盘
static void drawBoard()
{
    putimage(-500, -100, &bk); // 绘制背景

    // 绘制棋盘线
    setlinecolor(BLACK);
    setlinestyle(BLACK);

    for (int i = 0; i < ROW; i++)
    {
        line(X_SPACE, i * GRID_W + Y_SPACE, 14 * GRID_W + X_SPACE, i * GRID_W + Y_SPACE);
        line(i * GRID_W + X_SPACE, Y_SPACE, i * GRID_W + X_SPACE, 14 * GRID_W + Y_SPACE);
    }

    setlinestyle(PS_SOLID, 3);
    rectangle(X_SPACE, Y_SPACE, X_SPACE + 14 * GRID_W, Y_SPACE + 14 * GRID_W);

    // 绘制棋子
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

    // 绘制鼠标框
    if (pos.isShow)
    {
        setlinecolor(BLUE);
        rectangle((pos.col + 5) * GRID_W - 12, (pos.row + 3) * GRID_W - 12, (pos.col + 5) * GRID_W + 12, (pos.row + 3) * GRID_W + 12);
    }
}


// 鼠标移动
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


// 鼠标按下
static void mousePressMsg(ExMessage* msg)
{
    if (msg->message == WM_LBUTTONDOWN)
    {
       if (map[pos.row][pos.col] == NONE) // 确保位置为空
       {
            map[pos.row][pos.col] = pos.player; // 玩家下棋

            // 判断胜负
            if (isWin(pos.row, pos.col) == 1)
            {
                drawBoard();
                MessageBox(GetHWnd(), "Your Win!", "hit", MB_OK);
                exit(0);
            }

            // 切换到电脑
            pos.player = White;
            computerMove();

            // 检查电脑是否胜利
            if (isWin(pos.row, pos.col) == 1)
            {
                drawBoard();
                MessageBox(GetHWnd(), "Computer Wins!", "hit", MB_OK);
                exit(0);
            }

            // 切换回玩家
            pos.player = Black;
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


// 评分函数
static int evaluatePosition(int row, int col, int player)
{
    int score = 0;

    // 假设我们使用一些简单的评分规则：
    // 检查该位置周围的棋子，给不同数量的棋子赋予不同的分值

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r == 0 && c == 0) continue; // 跳过自身位置

            int count = 0;
            int emptyCount = 0;

            // 检查该方向上的棋子
            for (int step = 1; step < 5; step++) {
                int newRow = row + r * step;
                int newCol = col + c * step;

                // 边界检查
                if (newRow < 0 || newRow >= ROW || newCol < 0 || newCol >= COL) break;

                if (map[newRow][newCol] == player) {
                    count++;
                }
                else if (map[newRow][newCol] == NONE) {
                    emptyCount++;
                    break; // 遇到空位就停止
                }
                else {
                    break; // 遇到对手棋子停止
                }
            }

            // 评分逻辑，可以根据实际需求调整
            if (count > 0) {
                score += (int)pow(10, count); // 连续棋子越多，分数越高
            }
        }
    }

    return score;
}


 // 电脑下棋
static void computerMove()
{
    int bestScore = -1;
    int bestRow = -1;
    int bestCol = -1;


    // 阻止玩家的胜利
    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j <= 15; j++)
        {
            if (map[i][j] == NONE)
            {
                // 临时下棋以评估
                map[i][j] = Black; // 假设玩家是黑棋
                if (isWin(i, j) == 1 || isWin(i, j) == 2 || isWin(i, j) == 3) // 检查是否能赢
                {
                    map[i][j] = White; // 阻止玩家的棋
                    pos.row = i;
                    pos.col = j;
                    return; // 电脑下完棋后立即返回
                }
                map[i][j] = NONE; // 撤销临时下棋
            }
        }
    }

    // 评分函数选择最佳位置
    for (int i = 5; i <= 19; i++)
    {
        for (int j = 3; j <= 17; j++)
        {
            if (map[i][j] == NONE) // 只考虑空位置
            {
                // 评估该位置的分值
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

    // 在最佳位置下棋
    if (bestRow != -1 && bestCol != -1)
    {
        map[bestRow][bestCol] = White;
        pos.row = bestRow;
        pos.col = bestCol;
    }
}