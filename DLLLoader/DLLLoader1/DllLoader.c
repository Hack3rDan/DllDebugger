#define WINDOWS_LEAN_AND_MEAN



#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void (WINAPI *DARKHELL)(LPVOID, LPVOID);
extern _getch ();
/**
* Function that will get input from the user
**/
int WINAPI GetUserInput ()
{
	return EXIT_SUCCESS;
}

/**
* Function to parse the command line arugments to grab the name of the DLL to debug.
**/
int WINAPI ParseCommandLine ( LPSTR NameOfDll )
{
	LPSTR	sCommandLine		= NULL;
	UINT	index				= 0;
	UINT	iNumBytesToAlloc	= 0;
	PCHAR	pNameOfDll			= NULL;

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
	if ( index >= strlen ( sCommandLine ) )
	{
		return EXIT_FAILURE;
	}
	iNumBytesToAlloc = (UINT)strlen ( sCommandLine - index ) + 1;
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

/**
* Function used to print usage statement to user
**/
int WINAPI PrintUsageStatement ()
{
	printf ( TEXT ( "DLL Loader is a debugging tool that can load the DLL of your choice, wait for a debugger to attach, and then execute the DLL function of your choice.\r\n" ) );
	printf ( TEXT ( "DLLLoader.exe <Path to DLL to load>\r\n" ) );
	return EXIT_SUCCESS;
}


/**
* Main function
**/
INT main( INT argc, TCHAR **argv )
{
	LPSTR pDllToLoad	= NULL;
	HMODULE hLoadedDll	= INVALID_HANDLE_VALUE;
	DARKHELL DarkHell	= NULL;

	// Check command line
	switch ( argc )
	{
	case 2:
		ParseCommandLine ( pDllToLoad );
		break;
	case 1:
		break;
	default:
		PrintUsageStatement ();
		ExitProcess( EXIT_FAILURE );

	}
	// load dll
	hLoadedDll = LoadLibrary ( "malware.dll" );
	// TODO: Change this to be 
	// wait for debugger attach
	DarkHell = ( DARKHELL ) GetProcAddress ( hLoadedDll, "DarkHell" );
	printf( " Attach with debugger now\r\n" );
	_getch();
	printf ( "Executing now\r\n" );
	DarkHell ( 0, 0 );
	// continue
	return EXIT_SUCCESS;

}