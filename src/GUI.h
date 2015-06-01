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
#define KB_UP 72     //Áä½L¿é¤J¼Æ­È ¤W
#define KB_DOWN 80   //Áä½L¿é¤J¼Æ­È ¤U
#define KB_LEFT 75   //Áä½L¿é¤J¼Æ­È ¥ª
#define KB_RIGHT 77  //Áä½L¿é¤J¼Æ­È ¥k
#define KB_ENTER 13  //Áä½L¿é¤J¼Æ­È Enter
#define KB_ESC 27    //Áä½L¿é¤J¼Æ­È ESC
#define CHESSMAP_SIZE_ROW 17      //´Ñ½LROW    SIZE
#define CHESSMAP_SIZE_COLUMN 19   //´Ñ½Lcolumn SIZE
#define WD_BLACK_BG_WHITE 240     //¶Â¦r¥Õ¦â­I´º
#define WD_RED_BG_WHITE 252       //¬õ¦r¥Õ¦â­I´º
#define CHESS_RED 124             //¬õ¤èºX¤lªºÃC¦â
#define CHESS_BLACK 112           //¶Â¤è´Ñ¤lªºÃC¦â
#define WD_Purple_BG_WHITE 253    //µµ¦â¦r¥Õ¦â­I´º
#define WD_RED_BG_BLACK 12        //¬õ¦r¶Â¦â­I´º
#define WD_OCEANBLUE_BG_BLACK 11  //¤ôÂÅ¦â¦r¶Â¦â­I´º
#define WD_GRAY_BG_BLACK 8        //¦Ç¦â¦r¶Â¦â­I´º
#define DEFAULT_COLOR 7           //¹w³]¥Õ¦r¶Â¦â­I´º
#define SHOW_WHOS_TURN_POS ComXY(40,2)       //Åã¥Ü­þ¤@¤è¤U´Ñªº®y¼Ð
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //Åã¥Ü§A¿ï¨ú­þ­Ó´Ñ¤lªº®y¼Ð
#define CHESS_BOARD_X 2           //´Ñ½L°ò·ÇÂIX
#define CHESS_BOARD_Y 1           //´Ñ½L°ò·ÇÂIY
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"
#define MID_X srInfo.srWindow.Right/2
#define MID_Y srInfo.srWindow.Bottom/2

/**************´Ñ½L*****************/
const char ChessScreenChar[21][35] = {
	"¢°¡@¢±¡@¢²¡@¢³¡@¢´¡@¢µ¡@¢¶¡@¢·¡@¢¸",
	"ùÝùùùçùùùçùùùçùùùçùùùçùùùçùùùçùùùß",
	"ùø¡@¢x¡@¢x¡@¢x¢­¢x¢¬¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¢¬¢x¢­¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢w¢r¢wùø" ,
	"ùø¡@¡@·¡ªe¡@¡@¡@¡@¡@¡@º~¬É¡@¡@¡@ùø",
	"ùø¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¢­¢x¢¬¢x¡@¢x¡@¢x¡@ùø",
	"ùø¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢w¢q¢wùø",
	"ùø¡@¢x¡@¢x¡@¢x¢¬¢x¢­¢x¡@¢x¡@¢x¡@ùø",
	"ùãùùùíùùùíùùùíùùùíùùùíùùùíùùùíùùùå",
	"¤E¡@¤K¡@¤C¡@¤»¡@¤­¡@¥|¡@¤T¡@¤G¡@¤@" };

const string ChessScreen[CHESSMAP_SIZE_COLUMN][CHESSMAP_SIZE_ROW] =
{ { "ùÝ", "ùù", "ùç", "ùù", "ùç", "ùù", "ùç", "ùù", "ùç", "ùù", "ùç", "ùù", "ùç", "ùù", "ùç", "ùù", "ùß" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¢­", "¢x", "¢¬", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¢¬", "¢x", "¢­", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢r", "¢w", "¢r", "¢w", "¢r", "¢w", "¢r", "¢w", "¢r", "¢w", "¢r", "¢w", "¢r", "¢w", "ùø" },
{ "ùø", "¡@", "¡@", "·¡", "ªe", "¡@", "¡@", "¡@", "¡@", "¡@", "¡@", "º~", "¬É", "¡@", "¡@", "¡@", "ùø" },
{ "ùø", "¢w", "¢s", "¢w", "¢s", "¢w", "¢s", "¢w", "¢s", "¢w", "¢s", "¢w", "¢s", "¢w", "¢s", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¢­", "¢x", "¢¬", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùø", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "¢q", "¢w", "ùø" },
{ "ùø", "¡@", "¢x", "¡@", "¢x", "¡@", "¢x", "¢¬", "¢x", "¢­", "¢x", "¡@", "¢x", "¡@", "¢x", "¡@", "ùø" },
{ "ùã", "ùù", "ùí", "ùù", "ùí", "ùù", "ùí", "ùù", "ùí", "ùù", "ùí", "ùù", "ùí", "ùù", "ùí", "ùù", "ùå" } };

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
	"    ¢i¢i¢i¡@¢i¡@¡@¢i¡@¢i¡@¢i¡@¡@¡@¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¡@¡@¢i¡@¢i¡@¢i¢i¡@¡@¢i¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¢i¢i¢i¡@¢i¡@¢i¡@¢i¡@¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¡@¡@¢i¡@¢i¡@¢i¡@¡@¢i¢i¡@¢i¡@¡@¡@¡@¡@¡@¡@¢i¡@¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¡@¢i¢i¢i¡@¢i¡@¡@¢i¡@¢i¡@¢i¡@¡@¡@¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@<",
	"  ¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"    ¢i¢i¢i¡@¢i¡@¡@¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¡@¡@¢i¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¶H´Ñ¹CÀ¸¡@¡@¡@¡@¡@¡@<",
	"  ¢i¡@¡@¡@¡@¢i¡@¡@¢i¡@¢i¡@¡@¡@¡@¡@¡@¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<",
	"  ¡@¢i¢i¢i¡@¢i¡@¡@¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@<" };
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
	bool showConfirm(const string&);   //<==½Ð¶ñ­è¦n21¥b§Î¦r¤¸
	void showAlert(const string, const short);
	void displayExitScreen();
	void gotoxy(COORD);
	void gotoxy(short, short);
	void showTextColor(string, SHORT);
private:
	void setColor(INT);
};

#endif