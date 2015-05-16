#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()
#define KB_UP 72     //鍵盤輸入數值 上
#define KB_DOWN 80   //鍵盤輸入數值 下
#define KB_LEFT 75   //鍵盤輸入數值 左
#define KB_RIGHT 77  //鍵盤輸入數值 右
#define KB_ENTER 13  //鍵盤輸入數值 Enter
#define KB_ESC 27    //鍵盤輸入數值 ESC
#define CHESSMAP_SIZE_ROW 17      //棋盤ROW    SIZE
#define CHESSMAP_SIZE_COLUMN 19   //棋盤column SIZE
#define OPTIONS_SIZE 3            //遊戲介面選項個數
#define WD_BLACK_BG_WHITE 240     //黑字白色背景
#define WD_RED_BG_WHITE 252       //紅字白色背景
#define CHESS_RED 124             //紅方旗子的顏色
#define CHESS_BLACK 112           //黑方棋子的顏色
#define WD_Purple_BG_WHITE 253    //紫色字白色背景
#define WD_RED_BG_BLACK 12        //紅字黑色背景
#define WD_OCEANBLUE_BG_BLACK 11  //水藍色字黑色背景
#define WD_GRAY_BG_BLACK 8        //灰色字黑色背景
#define DEFAULT_COLOR 7           //預設白字黑色背景
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //顯示你選取哪個棋子的座標
#define CHESS_BOARD_X 2           //棋盤基準點X
#define CHESS_BOARD_Y 1           //棋盤基準點Y
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"

COORD ComXY(SHORT x, SHORT y);    //將x, y轉成 sturctor COORD
bool operator ==(const COORD& a, const COORD& b);

class Game
{
public:
	Game();
	void Interface();                                 //顯示遊戲介面
private:
	void setting();                                   //進入設定畫面
	void start();                                     //執行遊戲
	void exitGame();                                  //離開遊戲
	void playerControl();                             //進入玩家控制
	void makeAccess(Map& imap);                       //將每顆棋子能走的路徑push_back到棋子的vector中

	COORD cursorPos;
	Map GameMap;
	bool isWhosTurn;
	GUI gui;
};
#endif