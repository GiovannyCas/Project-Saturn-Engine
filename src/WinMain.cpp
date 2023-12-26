#include "../src/header/SystemClass.h"


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* system;
	bool result;

	//Create the system object.
	system = new SystemClass();

	//Initialize and run the system object.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	//Shutdown and release teh system object.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;


}


