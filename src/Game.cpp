#include "Game.h"
#include "Chess.h"
#include "Map.h"
#include "Player.h"
using std::cout;

Game::Game()
{
	isWhosTurn = true;
	cursorPos = ComXY(0, 0);
}

bool operator ==(const COORD& a, const COORD& b)
{
	if (a.X == b.X&&a.Y == b.Y)
		return true;
	return false;
}

void Game::makeAccess(Map& imap)
{
	imap.rKingPointer()->enemy.clear();
	imap.bKingPointer()->enemy.clear();
	for (int i = 0; i < ROW_SIZE; i++)   //尋找每個棋子
		for (int j = 0; j < COLUMN_SIZE; j++)  //
			if (imap.pChess[i][j] != NULL)
			{
				imap.pChess[i][j]->access.clear();
				for (int k = 0; k < ROW_SIZE; k++)     //針對每個棋子做預測路徑
					for (int l = 0; l < COLUMN_SIZE; l++)    //
						if (imap.pChess[i][j]->isValid(ComXY(k, l), imap))
						{
							imap.pChess[i][j]->access.push_back(ComXY(k, l)); //輸入所有能移動的位置
							if (k == imap.rKingPointer()->getPos().X &&      //被將軍與否
								l == imap.rKingPointer()->getPos().Y &&
								imap.pChess[i][j]->getColor()==false)
								imap.rKingPointer()->enemy.push_back(imap.pChess[i][j]);
							else if (k == imap.bKingPointer()->getPos().X && 
									 l == imap.bKingPointer()->getPos().Y &&
									 imap.pChess[i][j]->getColor()==true)
								imap.bKingPointer()->enemy.push_back(imap.pChess[i][j]);
						}
			}
}

COORD ComXY(SHORT x, SHORT y)
{
	return COORD{ x, y };
}

void Game::start()
{
	system("cls");      //清除開始介面畫面

	gui.setVisible(true);
	gui.dwSize(25);
	gui.displayChessboard(GameMap);
	playerControl();
}

void Game::setting()   //設定電腦難易度  可以不要
{

}
void Game::Interface() //開始介面
{
	switch (gui.mainMenu()) {
	case 1:
		start();
		break;
	case 2:
		//setting();
		break;
	case 3:
		exitGame();
		break;
	default:
		break;
	}
}

void Game::exitGame()
{
	system("cls");
	gui.displayExitScreen();
	Sleep(2000);	                //延遲2秒
	exit(EXIT_SUCCESS);
}

void Game::playerControl()
{
	Player rPlayer(true);   //Red   Player
	Player bPlayer(false);  //Black Player
	isWhosTurn = true;      //Red 先開始
	bool isMoveSuccess = false;
	bool reChoose = false;
	gui.displayGameInfo(isWhosTurn, GameMap);
	makeAccess(GameMap);
	gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
	CHAR InputKB = _getch();
	while (true)
	{
		isMoveSuccess = false;
		reChoose = false;
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
			if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL)
			{
				bool color = GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor();
				if (color != isWhosTurn)break;
				gui.displayWhatChessYouChose(*GameMap.pChess[cursorPos.X][cursorPos.Y]);    //顯示你選擇的棋子
				gui.displayPossiblePath(GameMap.pChess[cursorPos.X][cursorPos.Y], GameMap); //顯示可以走的位置
				gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
				cursorPos = (color ? rPlayer : bPlayer).chooseMovePos(ComXY(cursorPos.X, cursorPos.Y), GameMap, isMoveSuccess, reChoose, gui);
				if (reChoose) {
					gui.displayChessboard(GameMap);
					gui.displayGameInfo(isWhosTurn, GameMap);
					gui.clearWhatChessYouChose();
				}
				if (!isMoveSuccess)
					continue;

				gui.clearWhatChessYouChose();
				gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
				gui.showTextColor(GameMap.pChess[cursorPos.X][cursorPos.Y]->getName(), (color ? CHESS_RED : CHESS_BLACK));
				gui.displayChessboard(GameMap);
				isWhosTurn = !isWhosTurn;         //交換出棋方
				gui.displayGameInfo(isWhosTurn, GameMap);  //顯示換哪方

				makeAccess(GameMap);

				gui.gotoxy(40, 6); cout << "\t\t";
				gui.gotoxy(40, 7); cout << "\t\t";
				gui.displayBattleSituation(GameMap);//--------------->戰況
				
				if (GameMap.bKingPointer()->isDeath()) { gui.showAlert("      紅方勝利      ", 5000); exit(EXIT_SUCCESS); }
				if (GameMap.rKingPointer()->isDeath()){ gui.showAlert("      黑方勝利      ", 5000); exit(EXIT_SUCCESS); }

			}
			break;
		case KB_ESC:
			switch (gui.MenuInGame()) {
			case 1://resume
				break;
			case 2://restart
				if (gui.showConfirm("    確定重新開始 ?   "))
					restart();
				break;
			case 3://exit
				exitGame();
			default:
				break;
			}
			break;
		case KB_44:   //悔棋
			if (gui.showConfirm("     確定悔棋 ?     "))
			{
				if (GameMap.regret())
				{
					makeAccess(GameMap);
					gui.displayChessboard(GameMap);
					gui.displayBattleSituation(GameMap);
				}
				else
					gui.showAlert("沒有步數可以悔棋了 !", 2500);
			}
			break;
		case KB_46:   //還原
			if (gui.showConfirm("     確定還原 ?     "))
			{
				if (GameMap.restore())
				{
					makeAccess(GameMap);
					gui.displayChessboard(GameMap);
					gui.displayBattleSituation(GameMap);
				}
				else
					gui.showAlert("沒有步數可以還原了 !", 2500);
			}
			break;
		default:
			break;
		}
		gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);//回到游標原本的位置
		gui.setVisible(true);
		InputKB = _getch();
	}
}

void Game::restart()
{
	GameMap.GameRestart();
	isWhosTurn = true;
	cursorPos = ComXY(0, 0);
	makeAccess(GameMap);
	gui.displayChessboard(GameMap);
	gui.displayBattleSituation(GameMap);
	gui.displayGameInfo(isWhosTurn, GameMap);
}