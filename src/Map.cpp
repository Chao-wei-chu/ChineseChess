#include "Map.h"
#include "Game.h"

Chess* Map::bKingPointer() const
{
	return bKing;
}
Chess* Map::rKingPointer() const
{
	return rKing;
}
std::vector<chessStorage>* Map::chessStoragePointer()
{
	return &storage;
}
std::vector<chessStorage>* Map::chessStorageForRestorePointer()
{
	return &storageForRestore;
}
Map::Map()
{
	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < COLUMN_SIZE; j++)
			pChess[i][j] = NULL;

	bKing = new King("將", false, ComXY(4, 0));          pChess[4][0] = bKing;
	rKing = new King("帥", true, ComXY(4, 9));           pChess[4][9] = rKing;
	bAdviser1 = new Adviser("士", false, ComXY(5, 0));   pChess[5][0] = bAdviser1;
	bAdviser2 = new Adviser("士", false, ComXY(3, 0));   pChess[3][0] = bAdviser2;
	rAdviser1 = new Adviser("仕", true, ComXY(5, 9));    pChess[5][9] = rAdviser1;
	rAdviser2 = new Adviser("仕", true, ComXY(3, 9));    pChess[3][9] = rAdviser2;
	bElephant1 = new Elephant("象", false, ComXY(6, 0)); pChess[6][0] = bElephant1;
	bElephant2 = new Elephant("象", false, ComXY(2, 0)); pChess[2][0] = bElephant2;
	rElephant1 = new Elephant("相", true, ComXY(6, 9));  pChess[6][9] = rElephant1;
	rElephant2 = new Elephant("相", true, ComXY(2, 9));  pChess[2][9] = rElephant2;
	bHorse1 = new Horse("馬", false, ComXY(1, 0));       pChess[1][0] = bHorse1;
	bHorse2 = new Horse("馬", false, ComXY(7, 0));       pChess[7][0] = bHorse2;
	rHorse1 = new Horse("傌", true, ComXY(1, 9));        pChess[1][9] = rHorse1;
	rHorse2 = new Horse("傌", true, ComXY(7, 9));        pChess[7][9] = rHorse2;
	bChariot1 = new Chariot("車", false, ComXY(0, 0));   pChess[0][0] = bChariot1;
	bChariot2 = new Chariot("車", false, ComXY(8, 0));   pChess[8][0] = bChariot2;
	rChariot1 = new Chariot("車", true, ComXY(0, 9));    pChess[0][9] = rChariot1;
	rChariot2 = new Chariot("車", true, ComXY(8, 9));    pChess[8][9] = rChariot2;
	bPawn1 = new Pawn("卒", false, ComXY(0, 3));         pChess[0][3] = bPawn1;
	bPawn2 = new Pawn("卒", false, ComXY(2, 3));         pChess[2][3] = bPawn2;
	bPawn3 = new Pawn("卒", false, ComXY(4, 3));         pChess[4][3] = bPawn3;
	bPawn4 = new Pawn("卒", false, ComXY(6, 3));         pChess[6][3] = bPawn4;
	bPawn5 = new Pawn("卒", false, ComXY(8, 3));         pChess[8][3] = bPawn5;
	rPawn1 = new Pawn("兵", true, ComXY(0, 6));          pChess[0][6] = rPawn1;
	rPawn2 = new Pawn("兵", true, ComXY(2, 6));          pChess[2][6] = rPawn2;
	rPawn3 = new Pawn("兵", true, ComXY(4, 6));          pChess[4][6] = rPawn3;
	rPawn4 = new Pawn("兵", true, ComXY(6, 6));          pChess[6][6] = rPawn4;
	rPawn5 = new Pawn("兵", true, ComXY(8, 6));          pChess[8][6] = rPawn5;
	bCannon1 = new Cannon("包", false, ComXY(1, 2));     pChess[1][2] = bCannon1;
	bCannon2 = new Cannon("包", false, ComXY(7, 2));     pChess[7][2] = bCannon2;
	rCannon1 = new Cannon("炮", true, ComXY(1, 7));      pChess[1][7] = rCannon1;
	rCannon2 = new Cannon("炮", true, ComXY(7, 7));      pChess[7][7] = rCannon2;
}
Map::~Map()
{
	delete bKing;
	delete rKing;
	delete bAdviser1;
	delete bAdviser2;
	delete rAdviser1;
	delete rAdviser2;
	delete bElephant1;
	delete bElephant2;
	delete rElephant1;
	delete rElephant2;
	delete bHorse1;
	delete bHorse2;
	delete rHorse1;
	delete rHorse2;
	delete bChariot1;
	delete bChariot2;
	delete rChariot1;
	delete rChariot2;
	delete bPawn1;
	delete bPawn2;
	delete bPawn3;
	delete bPawn4;
	delete bPawn5;
	delete rPawn1;
	delete rPawn2;
	delete rPawn3;
	delete rPawn4;
	delete rPawn5;
	delete bCannon1;
	delete bCannon2;
	delete rCannon1;
	delete rCannon2;
}


short Map::checkKingToBeKilled(bool color)
{
	if ((color ? rKing : bKing)->enemy.size() != 0)
		return true;
	return false;
}

bool Map::regret()
{
	if (storage.size() >= 2) {
		for (int i = 0; i < 2; i++){
			chessStorage temp = storage.back();
			storageForRestore.push_back(temp);  //悔棋動作存入還原區
			storage.pop_back();   //刪除最後一筆資料
			pChess[temp.moved->getPos().X][temp.moved->getPos().Y] = NULL;
			temp.moved->setPos(temp.prePos);
			pChess[temp.prePos.X][temp.prePos.Y] = temp.moved;
			if (temp.dead != NULL)
			{
				temp.dead->setPos(temp.Pos);
				pChess[temp.Pos.X][temp.Pos.Y] = temp.dead;
				pChess[temp.Pos.X][temp.Pos.Y]->setAlive(true);
			}
		}
		return true;
	}
	return false;
}

bool Map::restore()
{
	if (storageForRestore.size() >= 2) {
		for (int i = 0; i < 2; i++) {
			chessStorage temp = storageForRestore.back();
			storage.push_back(temp);  //還原動作存入
			storageForRestore.pop_back();   //刪除還原區最後一筆資料
			temp.moved->setPos(temp.Pos);
			pChess[temp.prePos.X][temp.prePos.Y] = NULL;
			pChess[temp.Pos.X][temp.Pos.Y] = temp.moved;
			if (temp.dead != NULL)
				temp.dead->setAlive(false);
		}
		return true;
	}
	return false;
}

void Map::GameRestart() {
	delete bKing;
	delete rKing;
	delete bAdviser1;
	delete bAdviser2;
	delete rAdviser1;
	delete rAdviser2;
	delete bElephant1;
	delete bElephant2;
	delete rElephant1;
	delete rElephant2;
	delete bHorse1;
	delete bHorse2;
	delete rHorse1;
	delete rHorse2;
	delete bChariot1;
	delete bChariot2;
	delete rChariot1;
	delete rChariot2;
	delete bPawn1;
	delete bPawn2;
	delete bPawn3;
	delete bPawn4;
	delete bPawn5;
	delete rPawn1;
	delete rPawn2;
	delete rPawn3;
	delete rPawn4;
	delete rPawn5;
	delete bCannon1;
	delete bCannon2;
	delete rCannon1;
	delete rCannon2;

	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < COLUMN_SIZE; j++)
			pChess[i][j] = NULL;

	bKing = new King("將", false, ComXY(4, 0));          pChess[4][0] = bKing;
	rKing = new King("帥", true, ComXY(4, 9));           pChess[4][9] = rKing;
	bAdviser1 = new Adviser("士", false, ComXY(5, 0));   pChess[5][0] = bAdviser1;
	bAdviser2 = new Adviser("士", false, ComXY(3, 0));   pChess[3][0] = bAdviser2;
	rAdviser1 = new Adviser("仕", true, ComXY(5, 9));    pChess[5][9] = rAdviser1;
	rAdviser2 = new Adviser("仕", true, ComXY(3, 9));    pChess[3][9] = rAdviser2;
	bElephant1 = new Elephant("象", false, ComXY(6, 0)); pChess[6][0] = bElephant1;
	bElephant2 = new Elephant("象", false, ComXY(2, 0)); pChess[2][0] = bElephant2;
	rElephant1 = new Elephant("相", true, ComXY(6, 9));  pChess[6][9] = rElephant1;
	rElephant2 = new Elephant("相", true, ComXY(2, 9));  pChess[2][9] = rElephant2;
	bHorse1 = new Horse("馬", false, ComXY(1, 0));       pChess[1][0] = bHorse1;
	bHorse2 = new Horse("馬", false, ComXY(7, 0));       pChess[7][0] = bHorse2;
	rHorse1 = new Horse("傌", true, ComXY(1, 9));        pChess[1][9] = rHorse1;
	rHorse2 = new Horse("傌", true, ComXY(7, 9));        pChess[7][9] = rHorse2;
	bChariot1 = new Chariot("車", false, ComXY(0, 0));   pChess[0][0] = bChariot1;
	bChariot2 = new Chariot("車", false, ComXY(8, 0));   pChess[8][0] = bChariot2;
	rChariot1 = new Chariot("車", true, ComXY(0, 9));    pChess[0][9] = rChariot1;
	rChariot2 = new Chariot("車", true, ComXY(8, 9));    pChess[8][9] = rChariot2;
	bPawn1 = new Pawn("卒", false, ComXY(0, 3));         pChess[0][3] = bPawn1;
	bPawn2 = new Pawn("卒", false, ComXY(2, 3));         pChess[2][3] = bPawn2;
	bPawn3 = new Pawn("卒", false, ComXY(4, 3));         pChess[4][3] = bPawn3;
	bPawn4 = new Pawn("卒", false, ComXY(6, 3));         pChess[6][3] = bPawn4;
	bPawn5 = new Pawn("卒", false, ComXY(8, 3));         pChess[8][3] = bPawn5;
	rPawn1 = new Pawn("兵", true, ComXY(0, 6));          pChess[0][6] = rPawn1;
	rPawn2 = new Pawn("兵", true, ComXY(2, 6));          pChess[2][6] = rPawn2;
	rPawn3 = new Pawn("兵", true, ComXY(4, 6));          pChess[4][6] = rPawn3;
	rPawn4 = new Pawn("兵", true, ComXY(6, 6));          pChess[6][6] = rPawn4;
	rPawn5 = new Pawn("兵", true, ComXY(8, 6));          pChess[8][6] = rPawn5;
	bCannon1 = new Cannon("包", false, ComXY(1, 2));     pChess[1][2] = bCannon1;
	bCannon2 = new Cannon("包", false, ComXY(7, 2));     pChess[7][2] = bCannon2;
	rCannon1 = new Cannon("炮", true, ComXY(1, 7));      pChess[1][7] = rCannon1;
	rCannon2 = new Cannon("炮", true, ComXY(7, 7));      pChess[7][7] = rCannon2;

	storage.clear();
	storageForRestore.clear();
}