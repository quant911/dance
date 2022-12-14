/**************************************************************************
	----------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project


 ***************************************************************
 ******General License Agreement and Lack of Warranty ***********
 ****************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/

#include "dance.h"

#ifndef	WIN32

void main(int argc, char **argv)
{
    dance::initialize(argc,argv);
}
#else

#include <windows.h>

// _ANSI_ARGS_ defined in tcl.h
static void		setargv	_ANSI_ARGS_((int *argcPtr, char	***argvPtr));

int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
    char **argv, *p;
    int	argc;
    char buffer[MAX_PATH];

    setargv(&argc, &argv);

    /*
     * Replace argv[0] with full pathname of executable, and forward
     * slashes substituted for backslashes.
     */

    GetModuleFileName(NULL, buffer, sizeof(buffer));
    argv[0] = buffer;
    for	(p = buffer; *p	!= '\0'; p++) {
	if (*p == '\\')	{
	    *p = '/';
	}
    }

    dance::initialize(argc,argv);
    return 1;
}



/*
 *-------------------------------------------------------------------------
 *
 * setargv --
 *
 *	Parse the Windows command line string into argc/argv.  Done here
 *	because	we don't trust the builtin argument parser in crt0.
 *	Windows	applications are responsible for breaking their	command
 *	line into arguments.
 *
 *	2N backslashes + quote -> N backslashes	+ begin	quoted string
 *	2N + 1 backslashes + quote -> literal
 *	N backslashes +	non-quote -> literal
 *	quote +	quote in a quoted string -> single quote
 *	quote +	quote not in quoted string -> empty string
 *	quote -> begin quoted string
 *
 * Results:
 *	Fills argcPtr with the number of arguments and argvPtr with the
 *	array of arguments.
 *
 * Side	effects:
 *	Memory allocated.
 *
 *--------------------------------------------------------------------------
 */

static void
setargv(int *argcPtr, char ***argvPtr)
{
    char *cmdLine, *p, *arg, *argSpace;
    char **argv;
    int	argc, size, inquote, copy, slashes;

    cmdLine = GetCommandLine();

    /*
     * Precompute an overly pessimistic	guess at the number of arguments
     * in the command line by counting non-space spans.
     */

    size = 2;
    for	(p = cmdLine; *p != '\0'; p++) {
	if (isspace(*p)) {
	    size++;
	    while (isspace(*p))	{
		p++;
	    }
	    if (*p == '\0') {
		break;
	    }
	}
    }
    argSpace = (char *)	ckalloc((unsigned) (size * sizeof(char *)
	    + strlen(cmdLine) +	1));
    argv = (char **) argSpace;
    argSpace +=	size * sizeof(char *);
    size--;

    p =	cmdLine;
    for	(argc =	0; argc	< size;	argc++)	{
	argv[argc] = arg = argSpace;
	while (isspace(*p)) {
	    p++;
	}
	if (*p == '\0')	{
	    break;
	}

	inquote	= 0;
	slashes	= 0;
	while (1) {
	    copy = 1;
	    while (*p == '\\') {
		slashes++;
		p++;
	    }
	    if (*p == '"') {
		if ((slashes & 1) == 0)	{
		    copy = 0;
		    if ((inquote) && (p[1] == '"')) {
			p++;
			copy = 1;
		    } else {
			inquote	= !inquote;
		    }
		}
		slashes	>>= 1;
	    }

	    while (slashes) {
		*arg = '\\';
		arg++;
		slashes--;
	    }

	    if ((*p == '\0') ||	(!inquote && isspace(*p))) {
		break;
	    }
	    if (copy !=	0) {
		*arg = *p;
		arg++;
	    }
	    p++;
	}
	*arg = '\0';
	argSpace = arg + 1;
    }
    argv[argc] = NULL;

    *argcPtr = argc;
    *argvPtr = argv;
}

#endif

