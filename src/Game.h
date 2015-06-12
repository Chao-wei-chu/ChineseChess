#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //�Nx, y�ন sturctor COORD
bool operator ==(const COORD& a, const COORD& b);

class Game
{
public:
	Game();
	void Interface();                                 //��ܹC������
private:
	void reset();
	void setting();                                   //�i�J�]�w�e��
	void start();                                     //����C��
	void exitGame();                                  //���}�C��
	void playerControl();                             //�i�J���a����
	void makeAccess(Map& imap);                       //�N�C���Ѥl�ਫ�����|push_back��Ѥl��vector��
	void setGamemode(int mode);

	int gamemode;//0=multiplayer, 1=singleplayer
	COORD cursorPos;
	Map GameMap;
	bool isWhosTurn;
	GUI gui;
};
#endif