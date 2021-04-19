#include "Main_Form.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]


int main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BaseComputerSoftware::Main_Form form;
	Application::Run(%form);

	return 0;
}