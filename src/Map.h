#ifndef MAP_H
#define MAP_H
#include "Chess.h"
#include <vector>
#define ROW_SIZE 9
#define COLUMN_SIZE 10

struct chessStorage
{
	COORD prePos;
	COORD Pos;
	Chess *moved;
	Chess *dead;
};

class Map
{
public:
	Map();
	~Map();
	short checkKingToBeKilled(bool color) const;
	bool regret();
	bool restore();
	void reset();
	Chess* bKingPointer() const;
	Chess* rKingPointer() const;
	const std::vector<chessStorage>* chessStoragePointerConst() const;
	const std::vector<chessStorage>* chessStorageForRestorePointerConst() const;
	std::vector<chessStorage>* chessStoragePointer();
	std::vector<chessStorage>* chessStorageForRestorePointer();
	
	Chess* pChess[ROW_SIZE][COLUMN_SIZE];
private:
	std::vector<chessStorage> storage;
	std::vector<chessStorage> storageForRestore;
	Chess* bKing;
	Chess* rKing;
	Chess* bAdviser1;
	Chess* bAdviser2;
	Chess* rAdviser1;
	Chess* rAdviser2;
	Chess* bElephant1;
	Chess* bElephant2;
	Chess* rElephant1;
	Chess* rElephant2;
	Chess* bHorse1;
	Chess* bHorse2;
	Chess* rHorse1;
	Chess* rHorse2;
	Chess* bChariot1;
	Chess* bChariot2;
	Chess* rChariot1;
	Chess* rChariot2;
	Chess* bPawn1;
	Chess* bPawn2;
	Chess* bPawn3;
	Chess* bPawn4;
	Chess* bPawn5;
	Chess* rPawn1;
	Chess* rPawn2;
	Chess* rPawn3;
	Chess* rPawn4;
	Chess* rPawn5;
	Chess* bCannon1;
	Chess* bCannon2;
	Chess* rCannon1;
	Chess* rCannon2;
};
#endif
