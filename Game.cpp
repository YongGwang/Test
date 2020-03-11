#include "MainWindow.h"
#include "Game.h"
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> xDist(0, 770);
	std::uniform_int_distribution<int> yDist(0, 570);
	poo0X = xDist(rng);
	poo0Y = yDist(rng);
	poo1X = xDist(rng);
	poo1Y = yDist(rng);
	poo2X = xDist(rng);
	poo2Y = yDist(rng);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			dudeX = dudeX + 1;
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			dudeX = dudeX - 1;
		}
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			dudeY = dudeY - 1;
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			dudeY = dudeY + 1;
		}

		dudeX = ClampScreenX(dudeX, dudeWidth);
		dudeY = ClampScreenY(dudeY, dudeHeight);

		//poo0
		poo0X = pooMoveX(poo0X, poo0colScreenRight);
		poo0Y = pooMoveY(poo0Y, poo0colScreenBottom);
		//POO1
		poo1X = pooMoveX(poo1X, poo1colScreenRight);
		poo1Y = pooMoveY(poo1Y, poo1colScreenBottom);
		//POO2
		poo2X = pooMoveX(poo2X, poo2colScreenRight);
		poo2Y = pooMoveY(poo2Y, poo2colScreenBottom);

		poo0X = pooColRScreen(poo0X, pooWidth, poo0colScreenRight);
		poo0Y = pooColBScreen(poo0Y, pooHeight, poo0colScreenBottom);
		poo1X = pooColRScreen(poo1X, pooWidth, poo1colScreenRight);
		poo1Y = pooColBScreen(poo1Y, pooHeight, poo1colScreenBottom);
		poo2X = pooColRScreen(poo2X, pooWidth, poo2colScreenRight);
		poo2Y = pooColBScreen(poo2Y, pooHeight, poo2colScreenBottom);
		
		if (IsColliding(dudeX, dudeY, dudeWidth, dudeHeight, poo0X, poo0Y, pooWidth, pooHeight))
		{
			poo0IsEaten = true;
		}
		if (IsColliding(dudeX, dudeY, dudeWidth, dudeHeight, poo1X, poo1Y, pooWidth, pooHeight))
		{
			poo1IsEaten = true;
		}
		if (IsColliding(dudeX, dudeY, dudeWidth, dudeHeight, poo2X, poo2Y, pooWidth, pooHeight))
		{
			poo2IsEaten = true;
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isStarted = true;
		}
	}
}

void Game::DrawFace(int x, int y)
{...}

void Game::DrawPoo(int x, int y)
{...}

void Game::DrawGameOver(int x, int y)
{...}

void Game::DrawTitleScreen(int x, int y)
{...}

int Game::ClampScreenX(int x, int width)
{
	const int right = x + width;

	if (x < 0)
	{
		return 0;
	}
	else if (right >= gfx.ScreenWidth)
	{
		return (gfx.ScreenWidth - 1) - width;
	}
	else
	{
		return x;
	}
}

int Game::ClampScreenY(int y, int height)
{
	const int bottom = y + height;

	if (y < 0)
	{

		return 0;
	}
	else if (bottom >= gfx.ScreenHeight)
	{

		return (gfx.ScreenHeight - 1) - height;
	}
	else
	{
		return y;
	}
}

int Game::pooColRScreen(int x, int width, bool& pooColRCheck)
{
	const int right = x + width;

	if (x < 0)
	{
		pooColRCheck = false;
		return 0;
	}
	else if (right >= gfx.ScreenWidth)
	{
		pooColRCheck = true;
		return (gfx.ScreenWidth - 1) - width;
	}
	else
	{
		return x;
	}
}

int Game::pooColBScreen(int y, int height, bool& pooColBCheck)
{
	const int bottom = y + height;

	if (y < 0)
	{
		pooColBCheck = false;
		return 0;
	}
	else if (bottom >= gfx.ScreenHeight)
	{
		pooColBCheck = true;
		return (gfx.ScreenHeight - 1) - height;
	}
	else
	{
		return y;
	}
}

bool Game::IsColliding(int x0, int y0, int width0, int height0, 
	int x1, int y1,int width1, int height1)
{
	const int right0 = x0 + width0;
	const int bottom0 = y0 + height0;
	const int right1 = x1 + width1;
	const int bottom1 = y1 + height1;

	return
		right0 >= x1 &&
		x0 <= right1 &&
		bottom0 >= y1 &&
		y0 <= bottom1;
}

int Game::pooMoveX(int pooPositionX, bool ColRIght)
{
	if (ColRIght)
	{
		return pooPositionX - 1;
	}
	else
	{
		return pooPositionX + 1;
	}
}

int Game::pooMoveY(int pooPositionY, bool ColBottom)
{
	if (ColBottom)
	{
		return pooPositionY - 1;
	}
	else
	{
		return pooPositionY + 1;
	}
}

void Game::ComposeFrame()
{
	if (!isStarted)
	{
		DrawTitleScreen(325, 211);
	}

	if (poo0IsEaten && poo1IsEaten && poo2IsEaten)
	{
		DrawGameOver(358, 268);
	}

	DrawFace(dudeX, dudeY);

	if (!poo0IsEaten)
	{
		DrawPoo(poo0X, poo0Y);
	}
	if (!poo1IsEaten)
	{
		DrawPoo(poo1X, poo1Y);
	}
	if (!poo2IsEaten)
	{
		DrawPoo(poo2X, poo2Y);
	}
}
