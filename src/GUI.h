#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <string>
#include <iomanip> //setw()
#include "Map.h"
using std::cout;
using std::string;

#define WINDOW_COLS 120
#define WINDOW_LINES 34
#define BATTLE_SITUATION_LINES 15
#define KB_UP 72     //��L��J�ƭ� �W
#define KB_DOWN 80   //��L��J�ƭ� �U
#define KB_LEFT 75   //��L��J�ƭ� ��
#define KB_RIGHT 77  //��L��J�ƭ� �k
#define KB_ENTER 13  //��L��J�ƭ� Enter
#define KB_ESC 27    //��L��J�ƭ� ESC
#define CHESSMAP_SIZE_ROW 17      //�ѽLROW    SIZE
#define CHESSMAP_SIZE_COLUMN 19   //�ѽLcolumn SIZE
#define WD_BLACK_BG_WHITE 240     //�¦r�զ�I��
#define WD_RED_BG_WHITE 252       //���r�զ�I��
#define CHESS_RED 124             //����X�l���C��
#define CHESS_BLACK 112           //�¤�Ѥl���C��
#define WD_Purple_BG_WHITE 253    //����r�զ�I��
#define WD_RED_BG_BLACK 12        //���r�¦�I��
#define WD_OCEANBLUE_BG_BLACK 11  //���Ŧ�r�¦�I��
#define WD_GRAY_BG_BLACK 8        //�Ǧ�r�¦�I��
#define DEFAULT_COLOR 7           //�w�]�զr�¦�I��
#define SHOW_WHOS_TURN_POS ComXY(40,2)       //��ܭ��@��U�Ѫ��y��
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //��ܧA������ӴѤl���y��
#define CHESS_BOARD_X 2           //�ѽL����IX
#define CHESS_BOARD_Y 1           //�ѽL����IY
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"
#define MID_X srInfo.srWindow.Right/2
#define MID_Y srInfo.srWindow.Bottom/2

/**************�ѽL*****************/
const char ChessScreenChar[21][35] = {
	"���@���@���@���@���@���@���@���@��",
	"����������������������������������",
	"���@�x�@�x�@�x���x���x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x���x���x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x�@�x�@�x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x�@�x�@�x�@�x�@�x�@��",
	"���w�r�w�r�w�r�w�r�w�r�w�r�w�r�w��" ,
	"���@�@���e�@�@�@�@�@�@�~�ɡ@�@�@��",
	"���w�s�w�s�w�s�w�s�w�s�w�s�w�s�w��",
	"���@�x�@�x�@�x�@�x�@�x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x�@�x�@�x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x���x���x�@�x�@�x�@��",
	"���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��",
	"���@�x�@�x�@�x���x���x�@�x�@�x�@��",
	"����������������������������������",
	"�E�@�K�@�C�@���@���@�|�@�T�@�G�@�@" };

const string ChessScreen[CHESSMAP_SIZE_COLUMN][CHESSMAP_SIZE_ROW] =
{ { "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "��", "�x", "��", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "��", "�x", "��", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�r", "�w", "�r", "�w", "�r", "�w", "�r", "�w", "�r", "�w", "�r", "�w", "�r", "�w", "��" },
{ "��", "�@", "�@", "��", "�e", "�@", "�@", "�@", "�@", "�@", "�@", "�~", "��", "�@", "�@", "�@", "��" },
{ "��", "�w", "�s", "�w", "�s", "�w", "�s", "�w", "�s", "�w", "�s", "�w", "�s", "�w", "�s", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "��", "�x", "��", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "�q", "�w", "��" },
{ "��", "�@", "�x", "�@", "�x", "�@", "�x", "��", "�x", "��", "�x", "�@", "�x", "�@", "�x", "�@", "��" },
{ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" } };

const char exitScreen[14][52] = { 
	"    _____                                          ",
	"   /  ___|                                         ",
	"   \\ `--.  ___  ___   _   _  ___  _   _            ",
	"    `--. \\/ _ \\/ _ \\ | | | |/ _ \\| | | |           ",
	"   /\\__/ /  __/  __/ | |_| | (_) | |_| |           ",
	"   \\____/ \\___|\\___|  \\__, |\\___/ \\__,_|           ",
	"                       __/ |                       ",
	"                      |___/                        ",
	"                       _     _   _                 ",
	"                      | |   | | (_)                ",
	"       _ __   _____  _| |_  | |_ _ _ __ ___   ___  ",
	"      | '_ \\ / _ \\ \\/ / __| | __| | '_ ` _ \\ / _ \\ ",
	"      | | | |  __/>  <| |_  | |_| | | | | | |  __/ ",
	"      |_| |_|\\___/_/\\_\\\\__|  \\__|_|_| |_| |_|\\___| "};

const char mainMenuScreen[12][80] = {
	"    �i�i�i�@�i�@�@�i�@�i�@�i�@�@�@�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�@�@�i�@�i�@�i�i�@�@�i�@�i�@�@�@�@�i�@�@�@�@�i�@�@�@�@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�i�i�i�@�i�@�i�@�i�@�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�@�@�i�@�i�@�i�@�@�i�i�@�i�@�@�@�@�@�@�@�i�@�i�@�@�@�@�@�@�@�@�@<",
	"  �@�i�i�i�@�i�@�@�i�@�i�@�i�@�@�@�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�@�@<",
	"  �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@<",
	"  �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@<",
	"    �i�i�i�@�i�@�@�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�@�@�@�@�@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�@�@�i�@�i�@�@�@�@�i�@�@�@�@�i�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�H�ѹC���@�@�@�@�@�@<",
	"  �i�@�@�@�@�i�@�@�i�@�i�@�@�@�@�@�@�@�i�@�@�@�@�i�@�@�@�@�@�@�@�@�@�@�@�@�@�@<",
	"  �@�i�i�i�@�i�@�@�i�@�i�i�i�i�@�i�i�i�i�@�i�i�i�i�@�@�@�@�@�@�@�@�@�@�@�@�@�@<" };
class GUI {
public:
	GUI();
	~GUI();
	short mainMenu();    //  1=start ; 2=setting ; 3=exit
	short MenuInGame();  //  1=resume ; 2=restart ; 3=exit
	void setVisible(bool);
	void dwSize(int);
	void displayChessboard(const Map&);
	void displayGameInfo(bool, Map&);
	void displayBattleSituation(Map& map);
	void displayWhatChessYouChose(const Chess&);
	void displayPossiblePath(Chess* ch, Map& map);
	void clearWhatChessYouChose();
	bool showConfirm(const string&);   //<==�ж��n21�b�Φr��
	void showAlert(const string, const short);
	void displayExitScreen();
	void gotoxy(COORD);
	void gotoxy(short, short);
	void showTextColor(string, SHORT);
private:
	void setColor(INT);
};

#endif