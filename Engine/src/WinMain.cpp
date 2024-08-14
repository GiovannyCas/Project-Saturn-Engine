#include <header/SystemClass.h>
#define MEMORY_LEAK_LINE -1
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR pScmdline, int iCmdshow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(MEMORY_LEAK_LINE); // DO NOT COMMENT OUT THIS LINE
	_CrtDumpMemoryLeaks();

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


