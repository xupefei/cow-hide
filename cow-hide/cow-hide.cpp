// cow-hide.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "cow-hide.h"
#include "windows.h"
#include "Shlwapi.h"

#pragma comment(lib, "Shlwapi.lib")

BOOL RemoveFileName(LPTSTR path)
{
	LPTSTR newPath = PathFindFileName(path);
	if(newPath && (newPath != path))
	{
		newPath[0] = TEXT('\0');
		return 1;
	}
	return 0;
}

LPTSTR GetStartupDir()
{
	TCHAR lpFileName[MAX_PATH];
	GetModuleFileName(NULL, lpFileName, MAX_PATH);

	RemoveFileName(lpFileName);

	return lpFileName;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	LPTSTR commandLine = GetStartupDir();	
	_tcscat(commandLine,TEXT("cow.exe"));

	INT ExitCode;

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	// if CreateProcess fails, exit with GetLastError, otherwise exit with (process ID * -1)
	ExitCode = CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) \
		? pi.dwProcessId : GetLastError() * -1;

	printf("%d\n", ExitCode);
	exit(ExitCode);
}
