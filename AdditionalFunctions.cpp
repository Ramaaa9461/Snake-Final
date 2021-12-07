#include "AdditionalFunctions.h"


void initializeConsoleColors()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(console, &info);

	//Defino mi buffer de colores
	info.ColorTable[1] = RGB(255, 255, 255);//BLANCO = 1
	info.ColorTable[2] = RGB(255, 0, 0);	//ROJO = 2
	info.ColorTable[3] = RGB(255, 0, 255);	//MAGENTA = 3
	info.ColorTable[4] = RGB(255, 128, 0);	//NARANJA = 4
	info.ColorTable[5] = RGB(255, 255, 0);	//AMARILLO = 5
	info.ColorTable[6] = RGB(0, 255, 0);	//VERDE = 6
	info.ColorTable[7] = RGB(0, 255, 255);	//CIAN = 7
	info.ColorTable[8] = RGB(0, 0, 255);	//AZUL = 8
	info.ColorTable[9] = RGB(127, 0, 255);	//VIOLETA = 9
	

	SetConsoleScreenBufferInfoEx(console, &info);

	SetConsoleTextAttribute(console, 1);
}

void setCurrentColor(int color)
{
	SetConsoleTextAttribute(console, color);
}

void goToCoordinates(int x, int y)
{
	COORD coord = { x, y};


	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getKey(bool wait)
{
	int key;

	if (wait || _kbhit())
	{
		key = _getch();

		if (key == 0 || key == 224)
			key += 256;
	}
	else
	{
		key = 0;
	}

	return key;
}

void hideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

int getScreenWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	return (!GetConsoleScreenBufferInfo(console, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Right + 1;
}

int getScreenHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	

	return (!GetConsoleScreenBufferInfo(console, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Bottom + 1;
}



COORD GetConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}




