#include "WinMain.h"
#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

int main(cli::array<System::String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Hadis::WinMain form;
	Application::Run(%form);
	return 0;
}