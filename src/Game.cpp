#include "Game.h"
#include "Chess.h"
#include "Map.h"
#include "Player.h"

using std::cout;
using namespace XQWLight;

Game::Game()
{
	isWhosTurn = true;
	cursorPos = ComXY(0, 0);
	gamemode = 1;
	init_engine(5);   //XQ
	init_game();      //XQ
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
	gui.displayGameScreen(GameMap, isWhosTurn);
	playerControl();
	reset();
}

void Game::setting()   //設定電腦難易度  可以不要
{
	int depth;
	depth = gui.showDepthInput();
	if (depth <= 0 || depth > 20) {
		gui.showAlert("  請輸入１～９的數字  ", 2000);
		depth = gui.showDepthInput();
	}
	string out;
	out += "   已設定難度為   ";
	out += (depth + '0');
	out += "   ";
	gui.showAlert(out, 2000);
	init_engine(depth * 2);
}
void Game::Interface() //開始介面
{
	while (true)
	{
		switch (gui.mainMenu()) {
		case 1:
			gamemode = 0;
			PlaySound(NULL, NULL, NULL);
			start();
			break;
		case 2:
			gamemode = 1;
			PlaySound(NULL, NULL, NULL);
			start();
			break;
		case 3:
			setting();
			break;
		case 4:
			gui.displayAboutScreen();
			break;
		case 5:
			exitGame();
			break;
		default:
			break;
		}
	}
}

void Game::exitGame()
{
	system("cls");
	gui.displayExitScreen();
	Sleep(200);//Delay 200ms
	exit(EXIT_SUCCESS);
}

void Game::playerControl()
{
	Player rPlayer(true);   //Red   Player
	Player bPlayer(false);  //Black Player
	isWhosTurn = true;      //Red 先開始
	bool isMoveSuccess = false;
	bool reChoose = false;
	bool go = true;  //control possible path
	makeAccess(GameMap);
	gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
	gui.displayGameScreen(GameMap, isWhosTurn);
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
				gui.displayGameInfo(isWhosTurn, GameMap, GameMap.pChess[cursorPos.X][cursorPos.Y]);

				gui.displayPossiblePath(GameMap.pChess[cursorPos.X][cursorPos.Y], GameMap); //顯示可以走的位置

				gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);
				COORD originalPos = cursorPos;
				cursorPos = (color ? rPlayer : bPlayer).chooseMovePos(ComXY(cursorPos.X, cursorPos.Y), GameMap, isMoveSuccess, reChoose, gui);
				
				if (reChoose) {
					gui.displayChessboard(GameMap);
					gui.displayGameInfo(isWhosTurn, GameMap);
				}
				if (!isMoveSuccess)
					continue;
				//---------------------------------------------------------
				//if (color == true) {
					string in;
					in += ((originalPos.X + '0'));
					in += ((originalPos.Y + '0'));
					in += ((cursorPos.X + '0'));
					in += ((cursorPos.Y + '0'));
					on_human_move(in);
				//}
				//--------------------------------------------------------------
				GameMap.chessStorageForRestorePointer()->clear();
				gui.displayChessboard(GameMap);
				gui.displayGameInfo(isWhosTurn, GameMap);

				isWhosTurn = !isWhosTurn;         //交換出棋方
				makeAccess(GameMap);

				gui.displayBattleSituation(GameMap);
				gui.displayGameInfo(isWhosTurn, GameMap);
				if (GameMap.bKingPointer()->isDeath()) { Sleep(1000); gui.showAlert("       紅方勝利       ", 5000); return; }
				if (GameMap.rKingPointer()->isDeath()){ Sleep(1000); gui.showAlert("       黑方勝利       ", 5000); return; }
			}
			break;
		case KB_ESC:
			switch (gui.MenuInGame()) {
			case 1://resume
				break;
			case 2://restart
				if (gui.showConfirm("    確定重新開始 ?    ")) { //22 chars
					reset();
					gui.displayGameScreen(GameMap, isWhosTurn);
				}
				break;
			case 3://back to main menu
				if (gui.showConfirm("  確定放棄目前戰局 ?  "))
					return;
				break;
			case 4://exit
				if (gui.showConfirm("      確定離開 ?      "))
					exitGame();
			default:
				break;
			}
			break;
		case KB_44:   //悔棋
			if (gamemode == 1) {
				gui.showAlert(" 電腦不想給你悔棋ㄏㄏ ", 2000);
				break;
			}
			if (gui.showConfirm("      確定悔棋 ?      "))
			{
				if (GameMap.regret())
				{
					makeAccess(GameMap);
					gui.displayGameScreen(GameMap, isWhosTurn);
				}
				else
					gui.showAlert(" 沒有步數可以悔棋了 ! ", 2500);
			}
			break;
		case KB_46:   //還原
			if (gamemode == 1) {
				gui.showAlert(" 電腦不想給你悔棋ㄏㄏ ", 2000);
				break;
			}
			if (gui.showConfirm("      確定還原 ?      "))
			{
				if (GameMap.restore())
				{
					makeAccess(GameMap);
					gui.displayGameScreen(GameMap, isWhosTurn);
				}
				else
					gui.showAlert(" 沒有步數可以還原了 ! ", 2500);
			}
			break;
		default:
			break;
		}
		if (gamemode == 1 && isWhosTurn == false) {
			if (GameMap.rKingPointer()->enemy.size() > 0) {
				bPlayer.move(GameMap.rKingPointer()->enemy.at(0)->getPos(), GameMap.rKingPointer()->getPos(), GameMap);
			}
			else {
				string out;
				out = generate_move();
				bPlayer.move(ComXY(out.at(0) - '0', out.at(1) - '0'), ComXY(out.at(2) - '0', out.at(3) - '0'), GameMap);
			}
			isWhosTurn = true;
			makeAccess(GameMap);
			gui.displayChessboard(GameMap);
			gui.displayBattleSituation(GameMap);
			gui.displayGameInfo(isWhosTurn, GameMap);
			if (GameMap.bKingPointer()->isDeath()) { Sleep(1000); gui.showAlert("       紅方勝利       ", 5000); return; }
			if (GameMap.rKingPointer()->isDeath()){ Sleep(1000); gui.showAlert("       黑方勝利       ", 5000); return; }
		}
		gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 4, CHESS_BOARD_Y + cursorPos.Y * 2 + 1);//回到游標原本的位置
		gui.setVisible(true);
		InputKB = _getch();
	}
}

void Game::reset()
{
	init_game();
	GameMap.reset();
	isWhosTurn = true;
	cursorPos = ComXY(0, 0);
	makeAccess(GameMap);
}

void Game::setGamemode(int mode)
{
	if (mode >= 0 && mode <= 1)
		gamemode = mode;
}