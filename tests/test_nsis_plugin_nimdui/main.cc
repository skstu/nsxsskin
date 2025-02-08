#include "stdafx.h"

int main(int argc, char* argv[]) {
	HMODULE hDll = LoadLibraryW(LR"(C:\Users\k34ub\source\skstu\nsxsskin\bin\x86\Debug\nsxsskin.dll)");
	//HMODULE hDll = LoadLibraryW(LR"(C:\Users\k34ub\source\skstu\nsxsskin\bin\x86\Debug\xsnsskin.dll)");
	typedef void(*tfOpenUI)(void);
	typedef void(*tfCloseUI)(void);

	tfOpenUI openUI = (tfOpenUI)GetProcAddress(hDll, "OpenUI");
	tfCloseUI closeUI = (tfCloseUI)GetProcAddress(hDll, "CloseUI");

	openUI();
	std::string input;
	do {
		input.clear();
		std::getline(std::cin, input);
		if (input == "q" || std::cin.eof()) {
			closeUI();
			break;
		}
	} while (1);


	
	return 0;
}