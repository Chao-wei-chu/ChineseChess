#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include <string>
#include <Windows.h>

using std::string;

class Map;

class Chess
{
public:
	Chess() = delete;
	~Chess();
	Chess(string iName, bool icolor, COORD iPos);
	void setName();
	void setColor();
	void setPos(COORD p);
	void setAlive(bool t);
	string getName() const { return Name; }
	bool getColor() const { return Color; }
	COORD getPos() const { return Pos; }
	virtual bool isValid(COORD moveP, const Map& map)const;                //���k�O�_�X�k
	bool isDeath();
	std::vector<COORD>access;
	std::vector<Chess*>enemy;
private:
	string Name;
	bool Color;    //����true �¬�false
	COORD Pos;     //size 9,10
	bool alive;
};
class King :public Chess  // �N
{
public:
	King() = delete;
	~King();
	King(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD move, const Map& map)const;
};
class Chariot :public Chess // ��
{
public:
	Chariot() = delete;
	~Chariot();
	Chariot(string iName, bool icolo, COORD iPos);
	virtual bool isValid(COORD move, const Map& map)const;
};
class Horse : public Chess // ��
{
public:
	Horse() = delete;
	~Horse();
	Horse(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD moveP, const Map& map)const;
};
class Cannon :public Chess // ��
{
public:
	Cannon() = delete;
	~Cannon();
	Cannon(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD move, const Map& map)const;
};
class Elephant :public Chess //�H
{
public:
	Elephant() = delete;
	~Elephant();
	Elephant(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD move, const Map& map)const;
};
class Adviser :public Chess  //�h 
{
public:
	Adviser() = delete;
	~Adviser();
	Adviser(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD moveP, const Map& map)const;
};
class Pawn :public Chess    //�L
{
public:
	Pawn() = delete;
	~Pawn();
	Pawn(string iName, bool icolor, COORD iPos);
	virtual bool isValid(COORD move, const Map& map)const;
};
#endif