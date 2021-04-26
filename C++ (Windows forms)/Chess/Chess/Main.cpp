#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

#include "Main.h"

using namespace Chess;
using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Main);
	return 0;
}