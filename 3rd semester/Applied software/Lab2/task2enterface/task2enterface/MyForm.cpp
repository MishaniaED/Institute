#include "MyForm.h"


using namespace System;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(cli::array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    task2enterface::MyForm form;  //указать имя своего проекта
    Application::Run(% form);
}
