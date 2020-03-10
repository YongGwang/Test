#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawFace(int x, int y);
	void DrawPoo(int x, int y);
	void DrawGameOver(int x, int y);
	void DrawTitleScreen(int x, int y);
	int ClampScreenX(int x, int width);
	int ClampScreenY(int y, int height);
	int pooColRScreen(int x, int width, bool& pooColRCheck);
	int pooColBScreen(int y, int height, bool& pooColBCheck);
	bool IsColliding(int x0, int y0, int width0, int height0, 
		int x1, int y1,int width1, int height1);
	int pooMoveX(int pooPositionX, bool ColRIght);
	int pooMoveY(int pooPositionY, bool ColBottom);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	int dudeX = 500;
	int dudeY = 400;
	int dudeWidth = 20;
	int dudeHeight = 20;
	int poo0X = 300;
	int poo0Y = 100;
	bool poo0IsEaten = false;
	int poo1X = 600;
	int poo1Y = 300;
	bool poo1IsEaten = false;
	int poo2X = 50;
	int poo2Y = 500;
	bool poo2IsEaten = false;
	int pooWidth = 24;
	int pooHeight = 24;
	int pooMovex = 1;
	int pooMovey = 1;
	bool poo0colScreenRight = false;
	bool poo0colScreenBottom = true;
	bool poo1colScreenRight = true;
	bool poo1colScreenBottom = false;
	bool poo2colScreenRight = false;
	bool poo2colScreenBottom = false;
	bool isStarted = false;
	/********************************/
};
