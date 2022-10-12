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


#ifndef	_DANCETCL_H_
#define	_DANCETCL_H_ 1

#include <tcl.h>
#include "DanceObjectList.h"

#include <stdarg.h>

typedef	struct {
		char name[MAX_LINE];
		int type;
		char *ptr;
} SETVAR;






class DLLENTRY danceTcl {
	private:
	
	static Tcl_Interp * Interpreter;
    static int UsingTk;
	static SETVAR setlist[];

	static DanceObjectList *getList(char *type);
	static void appendMessage(Tcl_Interp *interp, char *message);

	public:

	// Utility routines
	static void checkEvents(void);
        static void ExecuteCommand(char *command) ;
	static void OutputMessage(char *format, ...);
	static void OutputResult(char *format, ...);
	static void OutputListElement(char *format, ...);


	// Initialization routines
	static void InitTclTk(int argc,	char **argv);
	static int Tcl_AppInit(Tcl_Interp *interp);
	static void InitUserTclCommands(Tcl_Interp *interp);
	static void LinkUserVariables(Tcl_Interp *interp);

	// Generic commands
	static int active(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int all(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int Command(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv);
	static int edit(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int instance(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int show(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int load(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int Plugin(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int proximity(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int quit(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int remove(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	static int save(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
    static int simul(ClientData	clientData, Tcl_Interp *interp,	int argc, char **argv);
    static int queryOS(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);

};
#endif



