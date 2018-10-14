HWND myhwnd;

LONG ThreadProc(LPVOID pParam)
{
	while(true)
	{
		Sleep(3000);
		MessageBox(myhwnd, "TEST", NULL, NULL);
	}
	return 0;
}


in hauptprozedur
     DWORD dwID;
     HANDLE threadHandle = CreateThread(NULL,NULL,
                           (LPTHREAD_START_ROUTINE)ThreadProc,
                           NULL, NULL, &dwID);						// in objekt 3. letztes parameter (LPVOID)this
     //TRACE("Started the thread %x\n",dwID);
