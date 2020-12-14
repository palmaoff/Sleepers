#include "Header.h"

Map::Map()
{
	// init W & H of the map
	MapWidth = 16;
	MapHeight = 16;

	// W & H of the Screen
	ScreenWidth = 120;
	ScreenHeight = 40;

	// number of Sleepers & Carrots
	nSleepers = 10;
	nCarrots = 10;

	// Create Screen Buffer
	screen = new wchar_t[ScreenWidth * ScreenHeight];
	Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(Console);
	dwBytesWritten = 0;

	// Create Map of world space
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
	map += L"................";
}

void	Map::run()
{
	bool		run = TRUE;
	Player		player(MapWidth - 1, MapHeight - 1);
	TSleeper	sleepers;
	Sleeper		sleeper;
	Carrot		*carr = new Carrot[nCarrots];
	float		t = 0;

	// time
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	srand(time(NULL));

	// init sleepers
	for (int i = 0; i < nSleepers; i++)
	{
		sleeper.set_pos(0, i);
		sleepers.add_end(sleeper);
	}

	// init carrots
	for (int i = 0; i < nCarrots; i++)
		carr[i].set_pos(rand() % MapWidth, rand() % MapHeight);

	// base loop
	while (run)
	{
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
			run = 0;
		
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		// Init with ' '
		for (int x = 0; x < ScreenWidth; x++)
			for (int y = 0; y < ScreenHeight; y++)
				screen[y * ScreenWidth + x] = ' ';

		// Display information
		swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f Sleepers=%d ", player.getX(), player.getY(), sleepers.count());

		// Display Map
		for (int nx = 0; nx < MapWidth; nx++)
			for (int ny = 0; ny < MapWidth; ny++)
				screen[(ny + 1) * ScreenWidth + nx] = map[ny * MapWidth + nx];

		// keys for moving
		if (player.get_keys(MapWidth, MapHeight, fElapsedTime))
		{
			// Move sleepers
			sleepers.moveAll(MapWidth, MapHeight, fElapsedTime);

			// eating Carrot
			sleepers.eat(carr, nCarrots);

			// kill sleepers
			sleepers.kill(player.getX(), player.getY());

			// new sleeper
			t += fElapsedTime;
			if (t > 5)
			{
				sleepers.newSleeper();
				t = 0;
			}
		}

		// Display sleepers
		sleepers.displayAll(screen, ScreenWidth);

		// Display Carrot
		bool b = FALSE;
		for (int i = 0; i < nCarrots; i++)
			if (carr[i].getX() > 0 && carr[i].getY() > 0)
			{
				screen[((int)carr[i].getX() + 1) * ScreenWidth + (int)carr[i].getY()] = 'C';
				b = TRUE;
			}

		if (!b)
			run = FALSE;

		// Display Player
		screen[((int)player.getX() + 1) * ScreenWidth + (int)player.getY()] = 'P';

		// Display Frame
		screen[ScreenWidth * ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(Console, screen, ScreenWidth * ScreenHeight, { 0, 0 }, &dwBytesWritten);

		if (sleepers.isEmpty())
			run = FALSE;
	}
}
