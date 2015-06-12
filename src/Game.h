#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //將x, y轉成 sturctor COORD
bool operator ==(const COORD& a, const COORD& b);

class Game
{
public:
	Game();
	void Interface();                                 //顯示遊戲介面
private:
	void reset();
	void setting();                                   //進入設定畫面
	void start();                                     //執行遊戲
	void exitGame();                                  //離開遊戲
	void playerControl();                             //進入玩家控制
	void makeAccess(Map& imap);                       //將每顆棋子能走的路徑push_back到棋子的vector中
	void setGamemode(int mode);

	int gamemode;//0=multiplayer, 1=singleplayer
	COORD cursorPos;
	Map GameMap;
	bool isWhosTurn;
	GUI gui;
};
#endif