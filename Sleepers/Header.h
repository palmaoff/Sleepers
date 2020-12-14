#ifndef SLEEPERS_H
#define SLEEPERS_H

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <list>

using namespace std;

struct Position
{
	float x;
	float y;
};

class Map
{
	int			MapWidth;
	int			MapHeight;
	int			ScreenWidth;
	int			ScreenHeight;
	int			nSleepers;
	int			nCarrots;
	wchar_t*	screen;
	HANDLE		Console;
	DWORD		dwBytesWritten;
	wstring		map;
public:
	Map();
	void	run();
};

class Player
{
	Position pos;
public:
	Player();
	Player(int x, int y);
	float	getX();
	float	getY();
	void	set_pos(int x, int y);
	void	change_pos(float x, float y, int H, int W, float time);
	int		get_keys(int MapWidth, int MapHeight, float fElapsedTime);
};

class Sleeper : public Player
{
	bool man;
	bool down;
public:
	Sleeper();
	bool	isDown();
	bool	isMale();
	void	move(int MapWidth, int MapHeight, float fElapsedTime, int i);
	void	changeDown();
};

struct Node
{
	Sleeper	curr;
	Node*	next;
};

class Carrot : public Player
{
public:
	Carrot();
};

class TSleeper
{
	Node* head;
public:
	TSleeper();
	~TSleeper();
	bool	isEmpty();
	int		count();
	Node*	getHead();
	void	add_end(Sleeper sleeper);
	void	add_end(TSleeper sleeper);
	void	add_start(Sleeper sleeper);
	void	moveAll(int MapWidth, int MapHeight, float fElapsedTime);
	void	displayAll(wchar_t* screen, int ScreenWidth);
	void	eat(Carrot*& carr, int nCarrots);
	void	kill(float x, float y);
	void	newSleeper();
	void	del_after(Node* todel);
};

#endif
