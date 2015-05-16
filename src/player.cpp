#include "Player.h"
#include "Game.h"

Player::Player(bool icolor) :color(icolor){}

SHORT Player::move(COORD cursorP, COORD movePos, Map& map)
{
	chessStorage tempStorage; //悔棋還原功能的struct暫存
	bool Valid = false;

	for (unsigned int i = 0; i < map.pChess[cursorP.X][cursorP.Y]->access.size(); i++) //
	{                                                                         //
		if (map.pChess[cursorP.X][cursorP.Y]->access.at(i) == movePos)        // >在access 中確定此路徑可行
			Valid = true;                                                     //
	}                                                                         //               

	if (map.pChess[movePos.X][movePos.Y] != NULL)
	{
		if (map.pChess[movePos.X][movePos.Y]->getColor() == map.pChess[cursorP.X][cursorP.Y]->getColor())//change the chess you chose !
			return -1;
		else
			if (Valid) //eat
			{
				tempStorage.dead = map.pChess[movePos.X][movePos.Y];  //
				tempStorage.moved = map.pChess[cursorP.X][cursorP.Y]; //
				tempStorage.prePos = ComXY(cursorP.X, cursorP.Y);     //  >儲存
				tempStorage.Pos = ComXY(movePos.X, movePos.Y);        //
				map.chessStoragePointer()->push_back(tempStorage);    //

				map.pChess[movePos.X][movePos.Y]->setAlive(false);
				map.pChess[movePos.X][movePos.Y] = map.pChess[cursorP.X][cursorP.Y];          //覆蓋pointer
				map.pChess[cursorP.X][cursorP.Y] = NULL;                                      //刪除棋子原本位置的pointer
				map.pChess[movePos.X][movePos.Y]->setPos(movePos);                            //更改Chess private裡的位置
				return 1;
			}
	}
	else if (Valid)                                           //move
	{

		tempStorage.dead = NULL;                              //
		tempStorage.moved = map.pChess[cursorP.X][cursorP.Y]; // 
		tempStorage.prePos = ComXY(cursorP.X, cursorP.Y);     //  >儲存
		tempStorage.Pos = ComXY(movePos.X, movePos.Y);        //
		map.chessStoragePointer()->push_back(tempStorage);    //

		map.pChess[movePos.X][movePos.Y] = map.pChess[cursorP.X][cursorP.Y];      //覆蓋pointer
		map.pChess[cursorP.X][cursorP.Y] = NULL;                                  //刪除棋子原本位置的pointer
		map.pChess[movePos.X][movePos.Y] ->setPos(movePos);                       //更改Chess private裡的位置
		return 1;
	}
	return 0;
}
COORD Player::chooseMovePos(COORD cursorPos, Map& map, bool& isMoveSuc, bool& reChoose, GUI& gui)
{
	CHAR InputKB = _getch();
	COORD originalCursorPos = cursorPos;
	bool isChooseSuccess = false;
	short moveVar;

	while (true)
	{
		switch (InputKB)
		{
		case KB_UP:
			if (cursorPos.Y > 0)
				--cursorPos.Y;
			break;
		case KB_DOWN:
			if (cursorPos.Y < 9)
				++cursorPos.Y;
			break;
		case KB_LEFT:
			if (cursorPos.X > 0)
				--cursorPos.X;
			break;
		case KB_RIGHT:
			if (cursorPos.X < 8)
				++cursorPos.X;
			break;
		case KB_ENTER:
			moveVar = move(originalCursorPos, ComXY(cursorPos.X, cursorPos.Y), map);
			if (moveVar == 1)       //move sucessfully
			{
				isChooseSuccess = true;
				isMoveSuc = true;
				return ComXY(cursorPos.X, cursorPos.Y);
			}
			else if (moveVar == -1) //change the chess you chose
				return ComXY(cursorPos.X, cursorPos.Y);
			else if (moveVar == 0)
			{
				reChoose = true;
				return ComXY(cursorPos.X, cursorPos.Y);
			}
			break;
		default:
			break;
		}
		gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
		InputKB = _getch();
	}
}