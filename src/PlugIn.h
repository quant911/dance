
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



#ifndef	_PLUGIN_H_
#define	_PLUGIN_H_ 1

#include "defs.h"
#include "DanceObject.h"
#include <stdio.h>
#include <tcl.h>

class DLLENTRY PlugIn :	public DanceObject {
public:
	virtual	PlugIn *create(Tcl_Interp *interp, int argc, char **argv) {return NULL;};
        virtual int initInterface(Tcl_Interp *interp) {	return 1;} ;
        virtual int commandPlugIn(ClientData clientData, Tcl_Interp 
			    *interp, int argc, char **argv) { return TCL_OK;};
	// Appends contents to filename.
	virtual void printFile(char *filename) { return; };

protected:
	Tcl_Interp *interpreter;

};

// Factory function for	creating instances of plugins.
extern "C" DLLEXPORT PlugIn *Proxy(void);
#endif
