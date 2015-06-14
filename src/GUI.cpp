#include "GUI.h"
#include <Windows.h>
#include <conio.h>

static CONSOLE_SCREEN_BUFFER_INFO srInfo;
static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_CURSOR_INFO crInfo;

GUI::GUI()
{
	system("chcp 950");
	system("mode con: cols=104 lines=24");
	SetConsoleTitle("¶H´Ñ¹CÀ¸");
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
	COORD bufferSize = { 34, 21 };
	COORD characterBufferSize = { 34, 21 };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { CHESS_BOARD_X, CHESS_BOARD_Y, CHESS_BOARD_X + 34 - 1, CHESS_BOARD_Y + 21 - 1 };
	CHAR_INFO consoleBuffer[34 * 21];
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

void GUI::displayGameInfo(bool isWhosTurn, const Map& map, const Chess *ch)
{
	/*
	if (isWhosTurn == true && map.checkKingToBeKilled(true)) { gotoxy(40, 6); showTextColor("¬õ¤è  ³Q±N­x", WD_RED_BG_BLACK); }
	if (isWhosTurn == false && map.checkKingToBeKilled(false)){ gotoxy(40, 7); showTextColor("¶Â¤è  ³Q±N­x", WD_GRAY_BG_BLACK); }
	*/
	const int cols = 38;
	const int lines = 22;
	COORD bufferSize = { cols, lines };
	COORD characterBufferSize = { cols, lines };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 64, 1, 64 + cols - 1, 1 + lines - 1 };
	CHAR_INFO consoleBuffer[cols * lines];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < lines; ++y)
		for (int x = 0; x < cols; ++x) {
			consoleBuffer[x + cols * y].Attributes = DEFAULT_COLOR;
			consoleBuffer[x + cols * y].Char.AsciiChar = gameInfoScreen[y][x];
		}
	for (int y = 2; y < 21; ++y) {
		for (int x = 2; x < 36; ++x) {
			if (y == 3) {   //  ²Ä3¦æ
				consoleBuffer[x + cols * y].Attributes = WD_OCEANBLUE_BG_BLACK;
				if (x >= 18 && x <= 23) {
					consoleBuffer[x + cols * y].Char.AsciiChar = string(isWhosTurn ? "¬õ¦â¤è" : "¶Â¦â¤è").at(x - 18);
					consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_RED_BG_BLACK : WD_GRAY_BG_BLACK;
				}
			}
			else if (y == 6 && ch != nullptr) {  //²Ä5¦æ
				consoleBuffer[x + cols * y].Attributes = WD_OCEANBLUE_BG_BLACK;
				if (x >= 12 && x <= 23) {
					consoleBuffer[x + cols * y].Char.AsciiChar = string(string("±z¿ï¾Ü¤F  ") + string(ch->getName())).at(x - 12);
					if (x == 22 || x == 23)
						consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_RED_BG_BLACK : WD_GRAY_BG_BLACK;
				}
			}
			else if (y == 9 && (map.checkKingToBeKilled(true) || map.checkKingToBeKilled(false))) {   //  ²Ä7¦æ
				if ((isWhosTurn && map.checkKingToBeKilled(true)) || ((!isWhosTurn) && map.checkKingToBeKilled(false))) {
					consoleBuffer[x + cols * 8].Attributes = 64;
					consoleBuffer[x + cols * 9].Attributes = 64;
					consoleBuffer[x + cols * 10].Attributes = 64;
				}
				if (x >= 9 && x <= 28) {
					consoleBuffer[x + cols * y].Attributes = DEFAULT_COLOR;
					if (isWhosTurn && map.checkKingToBeKilled(true))
						consoleBuffer[x + cols * y].Char.AsciiChar = string("¡I  ¬õ¤è  ³Q±N­x  ¡I").at(x - 9);
					else if ((!isWhosTurn) && map.checkKingToBeKilled(false))
						consoleBuffer[x + cols * y].Char.AsciiChar = string("¡I  ¶Â¤è  ³Q±N­x  ¡I").at(x - 9);
					if (x >= 13 && x <= 16)
						consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_RED_BG_BLACK : WD_GRAY_BG_BLACK;
				}
			}
		}
	}

	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

bool GUI::showConfirm(const string& info)
{
	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	/* Write our character buffer (a single character currently) to the console buffer */
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(false);
	bool point = false;
	setColor(12);
	gotoxy(MID_X - 10, MID_Y - 3);
	cout << "ùÝùùùùùùùùùùùùùùùùùùùùùùùß"; gotoxy(MID_X - 10, MID_Y - 2);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y - 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y);
	cout << "ùø"; showTextColor(info, DEFAULT_COLOR); setColor(12); cout << "ùø"; gotoxy(MID_X - 10, MID_Y + 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 2);
	cout << "ùø     ¬O        §_     ùø"; gotoxy(MID_X - 10, MID_Y + 3);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 4);
	cout << "ùãùùùùùùùùùùùùùùùùùùùùùùùå";
	char KB;
	while (true)
	{
		gotoxy(MID_X - 4, MID_Y + 2); 
		showTextColor("¬O", !point ? 15 : 240);
		gotoxy(MID_X + 6, MID_Y + 2);
		showTextColor("§_", point ? 15 : 240);
		KB = _getch();
		switch (KB)
		{
		case KB_LEFT:
		case KB_RIGHT:
			point = !point;
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

void GUI::displayBattleSituation(const Map& map)
{
	const int cols = 26;
	const int lines = BATTLE_SITUATION_LINES + 2;
	COORD bufferSize = { cols, lines };// col = 26, lines = 16
	COORD characterBufferSize = { cols, lines };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 2, 1, (78 + cols) - 1, (1 + lines) - 1 };
	CHAR_INFO consoleBuffer[cols * lines];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	string wall = "ùø";
	for (int y = 0; y < lines; ++y)
		for (int x = 0; x < cols; ++x) {
			consoleBuffer[y * cols + x].Char.AsciiChar = '\0';
			consoleBuffer[y * cols + x].Attributes = DEFAULT_COLOR;
			if (x == 0 || x == (cols-2)) {
				consoleBuffer[y * cols + x].Char.AsciiChar = wall.at(0);
				consoleBuffer[y * cols + x + 1].Char.AsciiChar = wall.at(1);
				consoleBuffer[y * cols + x + 1].Attributes = DEFAULT_COLOR;
				x++;
			}
		}

	string title = "ùÝùù  ¾Ô  ªp  Åã  ¥Ü  ùùùß";
	string bottom = "ùãùùùùùùùùùùùùùùùùùùùùùùùå";
	for (int x = 0; x < cols; ++x) {
		if (title[x] == '\0')break;
		consoleBuffer[x].Char.AsciiChar = title.at(x);
	}
	const std::string ChineseNum[9] = { "¤@", "¤G", "¤T", "¥|", "¤­", "¤»", "¤C", "¤K", "¤E" };
	const std::string ArabicNum[9] = { "¢°", "¢±", "¢²", "¢³", "¢´", "¢µ", "¢¶", "¢·", "¢¸" };
	int counter = 1;
	bool straight = false;
	int i = 0;
	const std::vector<chessStorage> *it = (map.chessStoragePointerConst());
	if (it->size() > BATTLE_SITUATION_LINES) {
		counter += it->size() - BATTLE_SITUATION_LINES;
		i += it->size() - BATTLE_SITUATION_LINES;
	}
	string line;
	int printer = 1;
	for (; i != map.chessStoragePointerConst()->size(); i++) {
		straight = false;
		bool color = it->at(i).moved->getColor();
		if (counter >= 100)line += " ";
		else if (counter >= 10)line += "  ";
		else if (counter < 10)line += "   ";
		line += std::to_string(counter);
		line += (color ? " ¬õ¡G" : " ¶Â¡G");
		line += it->at(i).moved->getName() + " ";
		line += (color ? ChineseNum[(8 - it->at(i).prePos.X)] : ArabicNum[(it->at(i).prePos.X)]);
		if ((color ? (it->at(i).prePos.Y - it->at(i).Pos.Y) : (it->at(i).Pos.Y - it->at(i).prePos.Y)) > 0) {
			line += " ¶i ";
			if ((it->at(i).prePos.X - it->at(i).Pos.X) == 0) {
				line += (color ? (ChineseNum[(it->at(i).prePos.Y - it->at(i).Pos.Y) - 1]) : (ArabicNum[(it->at(i).Pos.Y - it->at(i).prePos.Y) - 1]));
				straight = true;
			}
		}
		else if ((color ? (it->at(i).Pos.Y - it->at(i).prePos.Y) : -(it->at(i).prePos.Y - it->at(i).Pos.Y)) == 0)
			line += " ¥­ ";
		else {
			line += " °h ";
			if ((it->at(i).prePos.X - it->at(i).Pos.X) == 0) {
				line += (color ? (ChineseNum[(it->at(i).Pos.Y - it->at(i).prePos.Y) - 1]) : (ArabicNum[(it->at(i).prePos.Y - it->at(i).Pos.Y) - 1]));
				straight = true;
			}
		}
		if (!straight)
			line += (color ? (ChineseNum[(8 - it->at(i).Pos.X)]) : (ArabicNum[(it->at(i).Pos.X)]));
		for (int x = 0; x < 26; ++x) {
			if (x == (line.size()))break;
			consoleBuffer[26 * printer + x + 2].Char.AsciiChar = line.at(x);
		}
		consoleBuffer[26 * printer + 7].Attributes = (color ? WD_RED_BG_BLACK : WD_GRAY_BG_BLACK);
		consoleBuffer[26 * printer + 8].Attributes = (color ? WD_RED_BG_BLACK : WD_GRAY_BG_BLACK);
		printer++;
		line.clear();
		counter++;
	}
	for (int x = 0; x < cols; ++x) {
		if (title[x] == '\0')break;
		consoleBuffer[21*cols+x].Char.AsciiChar = bottom.at(x);
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::displayExitScreen()
{
	HWND hwnd = GetConsoleWindow();
	WINDOWINFO rr;
	GetWindowInfo(hwnd, &rr);
	COORD window{ rr.rcClient.right - rr.rcClient.left, rr.rcClient.bottom - rr.rcClient.top };
	HDC hdc = GetDC(hwnd);
	HDC memhdc = CreateCompatibleDC(hdc);
	HBITMAP cross = CreateCompatibleBitmap(hdc, window.X, window.Y);//106*8,24*16
	SelectObject(memhdc, cross);
	int x1 = 0;
	int y1 = 0;
	int x2 = window.X;
	int y2 = window.Y;
	int speed = 6;
	int density = 4;
	int color = 200;
	while (1) {
		DeleteObject(cross);
		cross = CreateCompatibleBitmap(hdc, window.X, window.Y);
		SelectObject(memhdc, cross);
		int y = 200;
		for (int x = x1; x < x2; x += density) {
			for (int y = y1; y < y2; y += density) {
				color = rand() % 256 + y1;
				
				if (color>255)color = 255;
				SetPixel(memhdc, x, y, RGB(color, color, color));
			}
		}
		x1 += 2 * speed, y1 += speed, x2 -= 2 * speed, y2 -= speed;
		BitBlt(hdc, 0, 0, window.X, window.Y, memhdc, 0, 0, SRCCOPY);
		if (x1 > (window.X / 2))break;
		else if (x1 > (window.X / 4)){ density = 2; }
		else if (x1 > (window.X / 3)){ density = 1; }
	}
}

short GUI::mainMenu()
{
	PlaySound("bgaudio.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);  //Play Sound;
	system("cls");
	class printMenu {
	private:
		COORD bufferSize;
		COORD characterBufferSize;
		COORD characterPosition;
		SMALL_RECT consoleWriteArea;
		CHAR_INFO *consoleBuffer;
	public:
		printMenu() {
			consoleBuffer = new CHAR_INFO[WINDOW_COLS * WINDOW_LINES];
			bufferSize = { WINDOW_COLS, WINDOW_LINES };
			characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
			characterPosition = { 0, 0 };
			consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
		}
		void print(int color,int option) {
			char* options[5] = { "Âù¤H¹CÀ¸", "¹q¸£¹ï¾Ô", "³]©wÃø«×", "¡@Ãö©ó¡@", "°h¥X¹CÀ¸" };
			SetConsoleScreenBufferSize(hConsole, bufferSize);
			for (int y = 0; y < WINDOW_LINES; ++y) {
				for (int x = 0; x < WINDOW_COLS; ++x) {
					consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = mainMenuScreen[y][x];
					consoleBuffer[x + WINDOW_COLS * y].Attributes = (((y / 2 + x + color) / 20) % 6 + 1);
			}}
			for (int y = 13; y <= 21; ++y) {
				if (y % 2 == 0)continue;
				for (int x = 53; x <= 60; ++x) {
					consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = options[(y - 13) / 2][x - 53];
					consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
					if (((y - 13) / 2) + 1 == option)
						consoleBuffer[x + WINDOW_COLS * y].Attributes = 112;
				}
			}
			WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		}
		~printMenu() {
			delete[] consoleBuffer;
		}
	};
	printMenu image;
	bool stop = false;
	static int option = 1;
	int const optionsNum = 5;
	std::thread t1([&]() {
		int color = 1, i = 0;
		while (!stop) {
			image.print(color, option);
			color++;
			if (color > 10000)
				color = 0;
			Sleep(150);
		}
	});
	//std::thread t2([&]() {
		setVisible(false);
		CHAR Input;
		bool end = false;
		while (!end) {
			Input = _getch();
			setVisible(false);
			switch (Input) {
			case KB_UP:
				if (option != 1)
					option--;
				else
					option = optionsNum;
				break;
			case KB_DOWN:
				if (option != optionsNum)
					option++;
				else
					option = 1;
				break;
			case KB_ENTER:
				end = true;
				stop = true;
				break;
			default:
				break;
			}
		}
	//});
	t1.join();
	//t2.join();
	//PlaySound(NULL, NULL, NULL);
	return option;
}

short GUI::MenuInGame()
{
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	bool decided = false;
	string options[4] = { "Ä~Äò¹CÀ¸", "­«·s¶}©l", "¦^¥D¿ï³æ", "Â÷¶}¹CÀ¸" };
	short option = 1;
	setColor(9);
	gotoxy(MID_X - 6, MID_Y - 5);
	cout << "ùÝùùùùùùùùùùùùùùùß"; gotoxy(MID_X - 6, MID_Y - 4);
	cout << "ùø              ùø"; gotoxy(MID_X - 6, MID_Y - 3);
	cout << "ùàùùùùùùùùùùùùùùùâ"; gotoxy(MID_X - 6, MID_Y - 2);
	cout << "ùø              ùø"; gotoxy(MID_X - 6, MID_Y - 1);
	cout << "ùàùùùùùùùùùùùùùùùâ"; gotoxy(MID_X - 6, MID_Y);
	cout << "ùø              ùø"; gotoxy(MID_X - 6, MID_Y + 1);
	cout << "ùàùùùùùùùùùùùùùùùâ"; gotoxy(MID_X - 6, MID_Y + 2);
	cout << "ùø              ùø"; gotoxy(MID_X - 6, MID_Y + 3);
	cout << "ùãùùùùùùùùùùùùùùùå";
	setColor(DEFAULT_COLOR);
	CHAR Input;
	while (!decided)
	{
		for (int i = 0; i < 4; i++) {
			gotoxy(MID_X - 1, MID_Y - 4 + 2 * i);
			if (option == (i + 1))
				showTextColor(options[i], 240);
			else
				cout << options[i];
		}
		setVisible(false);
		Input = _getch();
		switch (Input)
		{
		case KB_UP:
			if (option != 1)
				option--;
			else
				option = 4;
			break;
		case KB_DOWN:
			if (option != 4)
				option++;
			else
				option = 1;
			break;
		case KB_ENTER:
			decided = true;
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

void GUI::displayPossiblePath(Chess* ch, const Map& map)
{
	COORD bufferSize = { 34, 21 };
	COORD characterBufferSize = { 34, 21 };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { CHESS_BOARD_X, CHESS_BOARD_Y, CHESS_BOARD_X + 34 - 1, CHESS_BOARD_Y + 21 - 1 };
	CHAR_INFO consoleBuffer[34 * 21];
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
	for (unsigned int i = 0; i < ch->access.size(); i++)
	{
		int x = ch->access.at(i).X;
		int y = ch->access.at(i).Y;
		Chess *tempch = map.pChess[ch->access.at(i).X][ch->access.at(i).Y];
		consoleBuffer[(x * 4) + 34 * (y * 2 + 1)].Attributes = (tempch == NULL ? 120 : (tempch->getColor() ? 60 : 48));
		consoleBuffer[(x * 4) + 34 * (y * 2 + 1) + 1].Attributes = (tempch == NULL ? 120 : (tempch->getColor() ? 60 : 48));
		if (tempch != NULL) {
			consoleBuffer[(x * 4) + 34 * (y * 2 + 1)].Char.AsciiChar = tempch->getName().at(0);
			consoleBuffer[(x * 4) + 34 * (y * 2 + 1) + 1].Char.AsciiChar = tempch->getName().at(1);
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::showAlert(const string info, const short time)
{
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(false);
	setColor(12);
	gotoxy(MID_X - 10, MID_Y - 3);
	cout << "ùÝùùùùùùùùùùùùùùùùùùùùùùùß"; gotoxy(MID_X - 10, MID_Y - 2);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y - 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y);
	cout << "ùø"; showTextColor(info, DEFAULT_COLOR); setColor(12); cout << "ùø"; gotoxy(MID_X - 10, MID_Y + 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 2);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 3);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 4);
	cout << "ùãùùùùùùùùùùùùùùùùùùùùùùùå";
	setColor(DEFAULT_COLOR);
	Sleep(time);
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(true);
}

void GUI::displayGameScreen(const Map& map, bool isWhosTurn, const Chess* ch)
{
	COORD bufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition{ 0, 0 };
	SMALL_RECT consoleWriteArea{ 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = gameScreen[y][x];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = DEFAULT_COLOR;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	displayChessboard(map);
	displayBattleSituation(map);
	displayGameInfo(isWhosTurn, map, ch);
}

void GUI::displayAboutScreen()
{
	COORD bufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition{ 0, 0 };
	SMALL_RECT consoleWriteArea{ 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = aboutScreen[y][x];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = DEFAULT_COLOR;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	_getch();
}

int GUI::showDepthInput()
{
	int depth;
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(true);
	setColor(12);
	gotoxy(MID_X - 10, MID_Y - 3);
	cout << "ùÝùùùùùùùùùùùùùùùùùùùùùùùß"; gotoxy(MID_X - 10, MID_Y - 2);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y - 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y);
	cout << "ùø"; showTextColor(" ½Ð¿é¤J¹q¸£Ãø«× (1~9) ", DEFAULT_COLOR); setColor(12); cout << "ùø"; gotoxy(MID_X - 10, MID_Y + 1);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 2);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 3);
	cout << "ùø                      ùø"; gotoxy(MID_X - 10, MID_Y + 4);
	cout << "ùãùùùùùùùùùùùùùùùùùùùùùùùå";
	setColor(DEFAULT_COLOR);
	gotoxy(MID_X - 5, MID_Y + 2);
	depth = _getch();
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return depth - '0';
}