#include "StdAfx.h"
#include "Form1.h"

using namespace NexusTor;
[STAThreadAttribute]

int Main()
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1()); //Form1 is the name of the form created. 
	//if named different replace Form1 With the right form name.
	return 0;
}