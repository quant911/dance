#include "DanceObject.h"

// Default Tcl commands for every object.

int DanceObject::Command(ClientData clientData, Tcl_Interp *interp, int argc, char	**argv)
{
	if (strcmp(argv[0],"type") == 0) 
	{
		Tcl_AppendResult(interp,getType(),NULL);
		return TCL_OK ;
	}
	else if (strcmp(argv[0],"name") == 0) {
		if (argc == 2) 
			setName(argv[1]);
		else 
			Tcl_AppendResult(interp,getName(),NULL);
		return TCL_OK ;
	}

	return TCL_ERROR;
}


