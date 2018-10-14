#include "Engine.h"
#include <vector>


LPDIRECT3DDEVICE9* landev::Engine::parentRenderingDevice=NULL;


std::vector<landev::artObject*> landev::Engine::children;

HWND myhwnd;

HANDLE mutex;					//für jedes objekt ein eigenes mutex

landev::artObject* object;

DWORD WINAPI GlobalModelThread(LPVOID *param)
{
	while(true)
	{
		//WaitForSingleObject (mutex, 1000);
		
		for(unsigned int i=0; i<landev::Engine::children.size(); i++)
		{
			object = landev::Engine::children[i];
			object->Calculate();

		}

		//ReleaseMutex (mutex);
		//Sleep(10);

	}
	return 0;
}





landev::Engine::Engine(LPDIRECT3DDEVICE9* parentDevice)
{
	if (parentRenderingDevice!=NULL) parentRenderingDevice = parentDevice;
	init=true;
	landev::Engine::modelStartTime=GetTickCount();	

	mutex = CreateMutex (NULL, false, NULL);

	DWORD dwID;
	HANDLE threadHandle = CreateThread(	NULL,							// default security attributes 
										0x1000,							// 0 : use default stack size
										(LPTHREAD_START_ROUTINE)GlobalModelThread,	// thread function 
										NULL,							// argument to thread function
										NULL,							// 0 : use default creation flags or CREATE_SUSPENDED
										&dwID );						// returns the thread identifier
																			// in objekt 3. letztes parameter (LPVOID)this


		// -----------------------------------

		for(int i=0; i<50; i++) HookChild(new artObject(parentDevice, i));

		// NUR TEMPORäR für das erste testen, danach eigner steuerungsthread der children hinzufügt

}


landev::Engine::~Engine()
{
	//CloseHandle(mutex);
}



HRESULT landev::Engine::HookChild(landev::artObject* child)
{
	children.push_back(child);
	//childrenCount++;

	return S_OK; //allenfalls noch schauen ob es wirklich auch funktioniert hat, vs. rechenaufwand...
}


HRESULT landev::Engine::Draw()
{
	return Draw(0, 0, 640, 480);
}

HRESULT landev::Engine::Draw(int x, int y, int width, int height)
{
	//Hier die Szenen hinzufügen

	WaitForSingleObject (mutex, 1000);		// Handle, wartezeit
	
	for(unsigned int i=0; i<children.size(); i++)
	{
		object = children[i];
		object->Draw();

	}
	
	ReleaseMutex (mutex);					// Das Mutex freigeben
	
	init=false;
	return S_OK;
}




