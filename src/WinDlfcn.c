
#include "WinDlfcn.h"
#include <stdio.h>
#include "windows.h"

// Opens a shared object.
//
//	pathname: Path name of object to be opened.
//		  Can be absolute or relative path to current directory.
//	mode	: Governs when relocations take	place.
//
//	returns	: Handle which may be used by dlsym and	dlclose.
//
// Implementation:
//	Currently, mode	is ignored
void *dlopen(const char	*pathname, int mode)
{
	HINSTANCE mapaddress = LoadLibrary((LPCTSTR) pathname);
	return ((void *)mapaddress);
}

// Gets	the address of a symbol	in shared object.
//
//	handle	 : Value returned by call to dlopen
//	name	 : Symbol's name as a character	string
//
//	returns	 : Pointer to address where symbol is defined.
//
void *dlsym(void *handle, const	char *name)
{
	FARPROC	mapaddress = GetProcAddress((HMODULE)handle,(LPCSTR)name);
	return((void *)mapaddress);
}

// Close a shared object
//
//	handle	  : Handle of dynamically loaded object	to close.
//
//	returns	  : 0 on success, non-0	on failure.
//
int dlclose(void *handle)
{

	BOOL closed = FreeLibrary((HINSTANCE)handle);
	return((int)closed);

}


// Get diagnostic information
//
//	Returns: null-terminated character string with no newline.
//		 describes last	error occurred during dynamic linking
//		 process
//
char *dlerror(void)
{
	int error = GetLastError();
	static char errorMessage[256];
	sprintf(errorMessage,"Error returned: %d",error);
	return (errorMessage);
}

