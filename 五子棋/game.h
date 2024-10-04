#pragma once

#include <stdio.h>
#include <easyx.h>  //图形界面
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#include <windows.h>

// 头文件里放定义

#define GRID_W 25  // 宏定义15个像素，间隔15个像素
#define ROW 15  // 定义行为15
#define COL 15  // 定义列为15
#define X_SPACE (5 * GRID_W) // 左边的间距
#define Y_SPACE (3 * GRID_W) // 上边的间距


// 定义棋子
enum Chess
{
	NONE,   // 没有棋
	Black,  // 黑棋
	White   // 白棋
};


void centerWindow(int width, int height);
void minimizeWindow();
void drawMenu();
void handleMenuSelection(int choice);
void game1();
void game2();
void initMap(int i);
void loadResource();
void initializeGame();
void drawBoard();
void mouseMoveMsg(ExMessage* msg);
void mousePressMsg(ExMessage* msg);
int isWin(int, int);
int evaluatePosition(int row, int col, int player);
void computerMove();