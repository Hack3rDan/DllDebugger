#define WINDOWS_LEAN_AND_MEAN



#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void (WINAPI *DARKHELL)(PVOID, LPVOID)
int WINAPI GetUserInput ()
{

}
/**
*
**/
int WINAPI ParseCommandLine ( LPSTR NameOfDll )
{
	LPSTR sCommandLine		= NULL;
	INT index				= 0;
	INT iNumBytesToAlloc	= 0;

	sCommandLine = GetCommandLine ();
	strlen ( sCommandLine );

	while ( index < strlen ( sCommandLine ) )
	{
		// This is the delimiter
		if ( sCommandLine[index] == ' ' )
		{
			index++;
			break;
		}
		index++;
	}

	// We didn't find a space
	if ( index >= strlen )
	{
		return EXIT_FAILURE;
	}
	iNumBytesToAlloc = strlen ( sCommandLine - index ) + 1;
	if ( NameOfDll )
	{
		VirtualFree (	NameOfDll,
						0,
						MEM_RELEASE );
	}
	pNameOfDll = VirtualAlloc (	NULL,
								iNumBytesToAlloc,
								MEM_COMMIT,
								PAGE_READWRITE );

	strncpy (	NameOfDll,
				sCommandLine + index,
				iNumBytesToAlloc - 1 );
	return EXIT_SUCCESS;

}

int WINAPI PrintUsageStatement ()
{
	printf ( TEXT ( "DLL Loader is a debugging tool that can load the DLL of your choice, wait for a debugger to attach, and then execute the DLL function of your choice.\r\n" ) );
	printf ( TEXT ( "DLLLoader.exe <Path to DLL to load>\r\n" ) );
	return EXIT_SUCCESS;
}

int WINAPI wmain( int argc, char **argv )
{
	LPSTR pDllToLoad	= NULL;
	HMODULE hLoadedDll	= INVALID_HANDLE;
	DARKHELL DarkHell	= NULL;

	// Check command line
	switch ( argc )
	{
	case 2:
		ParseCommandLine ( pDllToLoad );
		break;
	default:
		PrintUsageStatement ();
		ExitProcess( EXIT_FAILURE );

	}
	// load dll
	LoadLibrary ( pDllToLoad );
	// TODO: Change this to be 
	// wait for debugger attach
	DarkHell = ( DARKHELL ) GetProcAddress ( hLoadedDll, "DarkHell" );
	printf( " Attach with debugger now\r\n" );
	getch();
	printf ( "Executing now\r\n" );
	DarkHell ( 0, 0 );
	// continue

}