#pragma once

#include <stdio.h>
#include <easyx.h>  //ͼ�ν���
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#include <windows.h>

// ͷ�ļ���Ŷ���

#define GRID_W 25  // �궨��15�����أ����15������
#define ROW 15  // ������Ϊ15
#define COL 15  // ������Ϊ15
#define X_SPACE (5 * GRID_W) // ��ߵļ��
#define Y_SPACE (3 * GRID_W) // �ϱߵļ��


// ��������
enum Chess
{
	NONE,   // û����
	Black,  // ����
	White   // ����
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