#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()
#define KB_UP 72     //��L��J�ƭ� �W
#define KB_DOWN 80   //��L��J�ƭ� �U
#define KB_LEFT 75   //��L��J�ƭ� ��
#define KB_RIGHT 77  //��L��J�ƭ� �k
#define KB_ENTER 13  //��L��J�ƭ� Enter
#define KB_ESC 27    //��L��J�ƭ� ESC
#define CHESSMAP_SIZE_ROW 17      //�ѽLROW    SIZE
#define CHESSMAP_SIZE_COLUMN 19   //�ѽLcolumn SIZE
#define OPTIONS_SIZE 3            //�C�������ﶵ�Ӽ�
#define WD_BLACK_BG_WHITE 240     //�¦r�զ�I��
#define WD_RED_BG_WHITE 252       //���r�զ�I��
#define CHESS_RED 124             //����X�l���C��
#define CHESS_BLACK 112           //�¤�Ѥl���C��
#define WD_Purple_BG_WHITE 253    //����r�զ�I��
#define WD_RED_BG_BLACK 12        //���r�¦�I��
#define WD_OCEANBLUE_BG_BLACK 11  //���Ŧ�r�¦�I��
#define WD_GRAY_BG_BLACK 8        //�Ǧ�r�¦�I��
#define DEFAULT_COLOR 7           //�w�]�զr�¦�I��
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //��ܧA������ӴѤl���y��
#define CHESS_BOARD_X 2           //�ѽL����IX
#define CHESS_BOARD_Y 1           //�ѽL����IY
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"

COORD ComXY(SHORT x, SHORT y);    //�Nx, y�ন sturctor COORD
bool operator ==(const COORD& a, const COORD& b);

class Game
{
public:
	Game();
	void Interface();                                 //��ܹC������
private:
	void setting();                                   //�i�J�]�w�e��
	void start();                                     //����C��
	void exitGame();                                  //���}�C��
	void playerControl();                             //�i�J���a����
	void makeAccess(Map& imap);                       //�N�C���Ѥl�ਫ�����|push_back��Ѥl��vector��

	COORD cursorPos;
	Map GameMap;
	bool isWhosTurn;
	GUI gui;
};
#endif