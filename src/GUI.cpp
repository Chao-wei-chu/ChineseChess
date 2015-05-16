#include "GUI.h"
#include <Windows.h>
#include <conio.h>

static CONSOLE_SCREEN_BUFFER_INFO srInfo;
static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_CURSOR_INFO crInfo;

GUI::GUI()
{
	system("chcp 950");
	system("mode con: cols=120 lines=34");
	SetConsoleTitle("象棋遊戲");
	GetConsoleScreenBufferInfo(hConsole, &srInfo);
	GetConsoleCursorInfo(hConsole, &crInfo);
	if (hConsole == INVALID_HANDLE_VALUE)
		exit(EXIT_FAILURE);
}
GUI::~GUI(){}

void GUI::gotoxy(SHORT x, SHORT y)
{
	COORD hwCursorPosition{ x, y };
	SetConsoleCursorPosition(hConsole, hwCursorPosition);
}
void GUI::gotoxy(COORD cd)
{
	SetConsoleCursorPosition(hConsole, cd);
}

void GUI::setVisible(bool op)
{
	crInfo.bVisible = op;
	SetConsoleCursorInfo(hConsole, &crInfo);
}

void GUI::dwSize(int size)
{
	crInfo.dwSize = size;
	SetConsoleCursorInfo(hConsole, &crInfo);
}

void GUI::showTextColor(std::string word, SHORT color)
{
	SetConsoleTextAttribute(hConsole, color);
	cout << word;
	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

void GUI::setColor(INT color)
{
	SetConsoleTextAttribute(hConsole, color);
}

void GUI::displayChessboard(const Map& map)
{
	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { 34, 21 };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { 34, 21 };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { CHESS_BOARD_X, CHESS_BOARD_Y, CHESS_BOARD_X + 34 - 1, CHESS_BOARD_Y + 21 - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[34 * 21];

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < (21); ++y) {
		for (int x = 0; x < 34; ++x) {
			consoleBuffer[x + 34 * y].Attributes = ((y == 0 || y == 20) ? WD_Purple_BG_WHITE : WD_BLACK_BG_WHITE);
			consoleBuffer[x + 34 * y].Char.AsciiChar = ChessScreenChar[y][x];
			
		}
	}

	for (int x = 0; x < ROW_SIZE; x++)
		for (int y = 0; y < COLUMN_SIZE; y++)
			if (map.pChess[x][y] != NULL) {
				consoleBuffer[(x * 4) + 34 * (y * 2 + 1)].Attributes = ((map.pChess[x][y]->getColor() == true) ? CHESS_RED : CHESS_BLACK);
				consoleBuffer[(x * 4) + 34 * (y * 2 + 1) + 1].Attributes = ((map.pChess[x][y]->getColor() == true) ? CHESS_RED : CHESS_BLACK);
				consoleBuffer[(x * 4) + 34 * (y * 2 + 1)].Char.AsciiChar = map.pChess[x][y]->getName().at(0);
				consoleBuffer[(x * 4) + 34 * (y * 2 + 1) + 1].Char.AsciiChar = map.pChess[x][y]->getName().at(1);
			}
	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::displayGameInfo(bool isWhosTurn, Map& map)
{
	gotoxy(40, 0);
	cout << "選單 Esc    悔棋 <    還原 > ";
	gotoxy(40, 2);
	showTextColor("現在輪到  ", WD_OCEANBLUE_BG_BLACK);
	if (isWhosTurn)
		showTextColor("紅色方", WD_RED_BG_BLACK);
	else
		showTextColor("黑色方", WD_GRAY_BG_BLACK);
	showTextColor("  下棋", WD_OCEANBLUE_BG_BLACK);
	if (map.checkKingToBeKilled(true) && isWhosTurn == true) { gotoxy(40, 6); showTextColor("紅方  被將軍", WD_RED_BG_BLACK); }
	if (map.checkKingToBeKilled(false) && isWhosTurn == false){ gotoxy(40, 7); showTextColor("黑方  被將軍", WD_GRAY_BG_BLACK); }
}

bool GUI::showConfirm(const string& info)
{
	SMALL_RECT windowSize = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { 120, 34 };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the window size */
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	/* Write our character buffer (a single character currently) to the console buffer */
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(false);
	bool point = false;
	gotoxy(MID_X - 10, MID_Y - 3);
	showTextColor("=========================", 12); gotoxy(MID_X - 10, MID_Y - 2);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y - 1);
	showTextColor("=", 12); cout << " " << info << " "; gotoxy(MID_X - 10 + 24, MID_Y - 1); showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 1);
	showTextColor("=", 12); cout << "          YES          "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 2);
	showTextColor("=", 12); cout << "       -> NO           "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 3);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 4);
	showTextColor("=========================", 12);
	char KB;
	gotoxy(MID_X, MID_Y + 2);
	while (true)
	{
		KB = _getch();
		switch (KB)
		{
		case KB_UP:
		case KB_DOWN:
			point = !point;
			cout << "\b\b  ";
			gotoxy(MID_X - 2, MID_Y + 2 - point); cout << "->";
			break;
		case KB_ENTER:
			WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
			return point;
			break;
		default:
			break;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return point;
}

void GUI::displayWhatChessYouChose(const Chess& youChose)
{
	gotoxy(40, 4);
	showTextColor("您選擇了  ", WD_OCEANBLUE_BG_BLACK);
	if (youChose.getColor() == true)
		showTextColor(youChose.getName(), WD_RED_BG_BLACK);
	else
		showTextColor(youChose.getName(), WD_GRAY_BG_BLACK);
	gotoxy(CHESS_BOARD_X + youChose.getPos().X * 4 + 1, CHESS_BOARD_Y + youChose.getPos().Y * 2 + 1);
}

void GUI::clearWhatChessYouChose()
{
	gotoxy(40, 4);
	cout << "\t\t";
}

void GUI::displayBattleSituation(Map& map)
{
	gotoxy(80, 1);
	cout << "----------戰  況  顯  示----------\n";
	const std::string ChineseNum[9] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
	const std::string ArabicNum[9] = { "１", "２", "３", "４", "５", "６", "７", "８", "９" };
	int counter = 1;
	bool straight = false;
	std::vector<chessStorage>::iterator it = map.chessStoragePointer()->begin();
	if (map.chessStoragePointer()->size() > BATTLE_SITUATION_LINES) {
		counter += map.chessStoragePointer()->size() - BATTLE_SITUATION_LINES;
		it += map.chessStoragePointer()->size() - BATTLE_SITUATION_LINES;
	}
	for (; it != map.chessStoragePointer()->end(); it++) {
		straight = false;
		gotoxy(80, 2 + map.chessStoragePointer()->size() - counter);
		cout << "  " << counter;
		((counter % 2) ? showTextColor(" 紅：", WD_RED_BG_BLACK) : showTextColor(" 黑：", WD_GRAY_BG_BLACK));
		cout << (*it).moved->getName() << " ";
		(counter % 2) ? (cout << ChineseNum[(8 - (*it).prePos.X)]) : (cout << ArabicNum[((*it).prePos.X)]);
		if (((counter % 2) ? ((*it).prePos.Y - (*it).Pos.Y) : ((*it).Pos.Y - (*it).prePos.Y)) > 0) {
			cout << " 進 ";
			if (((*it).prePos.X - (*it).Pos.X) == 0) {
				(counter % 2) ? (cout << ChineseNum[((*it).prePos.Y - (*it).Pos.Y) - 1]) : (cout << ArabicNum[((*it).Pos.Y - (*it).prePos.Y) - 1]);
				straight = true;
			}
		}
		else if ((counter % 2 ? ((*it).Pos.Y - (*it).prePos.Y) : -((*it).prePos.Y - (*it).Pos.Y)) == 0)
			cout << " 平 ";
		else {
			cout << " 退 ";
			if (((*it).prePos.X - (*it).Pos.X) == 0) {
				(counter % 2) ? (cout << ChineseNum[((*it).Pos.Y - (*it).prePos.Y) - 1]) : (cout << ArabicNum[((*it).prePos.Y - (*it).Pos.Y) - 1]);
				straight = true;
			}
		}
		if (!straight)
			(counter % 2) ? (cout << ChineseNum[(8 - (*it).Pos.X)]) : (cout << ArabicNum[((*it).Pos.X)]);
		cout << std::endl;
		counter++;
	}
	gotoxy(0, 0);
}

void GUI::displayExitScreen()
{
	/* Window size coordinates, be sure to start index at zero! */
	SMALL_RECT windowSize = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the window size */
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = ' ';
			consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
		}
	}

	for (int y = 2; y < WINDOW_LINES; ++y) {
		for (int x = 4; x < WINDOW_COLS; ++x) {
			if (exitScreen[y - 2][x - 4] == '\0')
				break;
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = exitScreen[y - 2][x - 4];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
		}
		if (y == 15)break;
	}

	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

short GUI::mainMenu()
{
	//PlaySound("bgaudio.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);  //Play Sound;
	/* Window size coordinates, be sure to start index at zero! */
	SMALL_RECT windowSize = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the window size */
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = ' ';
			consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
		}
	}

	for (int y = 2; y < WINDOW_LINES; ++y) {
		for (int x = 4; x < WINDOW_COLS; ++x) {
			if (mainMenuScreen[y - 2][x - 4] == '\0')
				break;
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = mainMenuScreen[y - 2][x - 4];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
		}
		if (y == 14)break;
	}

	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	bool reload = true;
	while (reload){
		reload = false;
		WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		setVisible(false);

		char* options[OPTIONS_SIZE] = { "開始遊戲", "設定難度", "退出遊戲" };
		int option = 1;
		for (int i = 0; i < OPTIONS_SIZE; i++) { //秀出選項
			gotoxy(MID_X - 4, MID_Y + 2 * (i + 1));
			cout << options[i];
		}
		gotoxy(MID_X - 6, MID_Y + 2);cout << "->";
		CHAR op = _getch();
		while (!reload)
		{
			setVisible(false);
			switch (op)
			{
			case KB_UP:
				if (option != 1) {
					cout << "\b\b  ";
					option--;
					gotoxy(MID_X - 6, MID_Y + option * 2); cout << "->";
				}
				else {
					cout << "\b\b  ";
					option = 3;
					gotoxy(MID_X - 6, MID_Y + option * 2); cout << "->";
				}
				break;
			case KB_DOWN:
				if (option != 3) {
					cout << "\b\b  ";
					option++;
					gotoxy(MID_X - 6, MID_Y + option * 2); cout << "->";
				}
				else {
					cout << "\b\b  ";
					option = 1;
					gotoxy(MID_X - 6, MID_Y + option * 2); cout << "->";
				}
				break;
			case KB_ENTER:
				if (option == 1)        //選項: 開始遊戲
				{
					//PlaySound(NULL, NULL, NULL);
					return 1;
				}
				else if (option == 2)  //選項: 設定難度
					return 2;
				else if (option == 3)   //選項: 離開遊戲
				{
					if (showConfirm("     確定離開 ?     "))
						return 3;
					reload = true;
				}
			default:
				break;
			}
			op = _getch();
		}
	}
	return 3;
}

short GUI::MenuInGame()
{
	SMALL_RECT windowSize = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { 120, 34 };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the window size */
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	/* Write our character buffer (a single character currently) to the console buffer */
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	bool decided = false;
	short option = 1;
	gotoxy(MID_X - 7, MID_Y - 1);
	cout << "=============="; gotoxy(MID_X - 7, MID_Y);
	cout << " ->繼續遊戲   "; gotoxy(MID_X - 7, MID_Y + 1);
	cout << "              "; gotoxy(MID_X - 7, MID_Y + 2);
	cout << "   重新開始   "; gotoxy(MID_X - 7, MID_Y + 3);
	cout << "              "; gotoxy(MID_X - 7, MID_Y + 4);
	cout << "   離開遊戲   "; gotoxy(MID_X - 7, MID_Y + 5);
	cout << "==============";
	CHAR op;
	while (!decided)
	{
		gotoxy(MID_X - 4, MID_Y - 2 + option * 2);
		setVisible(false);
		op = _getch();
		switch (op)
		{
		case KB_UP:
			if (option != 1)
				option--;
			else
				option = 3;
			cout << "\b\b  ";
			gotoxy(MID_X - 6, MID_Y - 2 + option * 2); cout << "->";
			break;
		case KB_DOWN:
			if (option != 3)
				option++;
			else
				option = 1;
			cout << "\b\b  ";
			gotoxy(MID_X - 6, MID_Y - 2 + option * 2); cout << "->";
			break;
		case KB_ENTER:
			decided = true;
			if (option == 3)
				if (!showConfirm("     確定離開 ?     "))
					decided = false;
			break;
		case KB_ESC:
			option = 1;
			decided = true;
		default:
			break;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return option;
}

void GUI::displayPossiblePath(Chess* ch, Map& map)
{
	displayChessboard(map);
	for (unsigned int i = 0; i < ch->access.size(); i++)
	{
		gotoxy(CHESS_BOARD_X + ch->access.at(i).X * 4, CHESS_BOARD_Y + ch->access.at(i).Y * 2 + 1); //
		if (map.pChess[ch->access.at(i).X][ch->access.at(i).Y] != NULL)
		{
			showTextColor(map.pChess[ch->access.at(i).X][ch->access.at(i).Y]->getName(), map.pChess[ch->access.at(i).X][ch->access.at(i).Y]->getColor() ? 60 : 48);
		}
		else
			showTextColor(ChessScreen[ch->access.at(i).Y * 2][ch->access.at(i).X * 2], 120);
	}
}

void GUI::showAlert(const string info, const short time)
{
	SMALL_RECT windowSize = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the window size */
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	/* Write our character buffer (a single character currently) to the console buffer */
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(false);
	bool point = false;
	gotoxy(MID_X - 10, MID_Y - 3);
	showTextColor("=========================", 12); gotoxy(MID_X - 10, MID_Y - 2);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y - 1);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y);
	showTextColor("=", 12); cout << " " << info << " "; gotoxy(MID_X - 10 + 24, MID_Y); showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 1);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 2);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 3);
	showTextColor("=", 12); cout << "                       "; showTextColor("=", 12); gotoxy(MID_X - 10, MID_Y + 4);
	showTextColor("=========================", 12);
	Sleep(time);
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(true);
}