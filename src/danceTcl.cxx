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
#include "DanceObjectList.h"
#include "PlugInManager.h"
#include "DSimulatorManager.h"
#include "danceTcl.h"
#include "DSystem.h"
#include "ViewManager.h"
#include "Proximity.h"

#include <stdlib.h>
#include <assert.h>

int danceTcl::UsingTk =	FALSE;

Tcl_Interp *danceTcl::Interpreter = NULL;

SETVAR danceTcl::setlist[] = {
	"actuators", TCL_LINK_INT, (char *) &dance::m_DisplayActuators,
	"monitorpts",TCL_LINK_INT, (char *) &dance::Monitorpts,
	"updateAll",TCL_LINK_INT, (char	*) &dance::UpdateAllWindows,
	"fitviewAlways",TCL_LINK_INT,(char *) &dance::FitviewAlways,
	"simul_block", TCL_LINK_INT, (char *) &dance::m_SimulBlock,
	"",0,(char *) NULL };

// InitUserTclCommands:
//	Initializes user-defined Tcl Commands
void danceTcl::InitUserTclCommands(Tcl_Interp *interp)
{

	// DanceTcl.h
	Tcl_CreateCommand(interp, "actuator", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "geometry", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "system", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "light", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "view", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "simulator", danceTcl::Command, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);

	Tcl_CreateCommand(interp, "all", danceTcl::all,	(ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "active", danceTcl::active, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "interact", danceTcl::edit, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "instance", danceTcl::instance, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "plugin", danceTcl::Plugin, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "remove", danceTcl::remove, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "show", danceTcl::show, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "<", danceTcl::load, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "proximity", danceTcl::proximity, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *) NULL);
	Tcl_CreateCommand(interp, "quit", danceTcl::quit, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "save", danceTcl::save, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "simul", danceTcl::simul, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);
	Tcl_CreateCommand(interp, "queryOS",danceTcl::queryOS, (ClientData) NULL, 
					  (Tcl_CmdDeleteProc *) NULL);
}


DanceObjectList	*danceTcl::getList(char	*type)
{
	int number; DanceObjectList **lists;
	dance::getLists(&number, &lists);

	int i;
	for (i=0; i<number; i++)
	    if (strcmp(lists[i]->getType(),type) == 0)
		break;
	if (i == number)
		return NULL;
	return (lists[i]);
}

// checkEvents:
//	Processes both Tk and TCL events.
//
void danceTcl::checkEvents(void)
{
    if(	UsingTk	== FALSE)
	while(Tcl_DoOneEvent(TCL_DONT_WAIT) != 0) ;
    else
   	while(Tk_DoOneEvent(TK_DONT_WAIT) != 0) ;
}


// InitTclTk:
//	     does Tcl/Tk setup,
//	     hands over	control	to a TK	Mainloop,
//	     which hands control over to main3() after
//	     a timer interrupt
//
void danceTcl::InitTclTk(int argc, char	**argv)
{
    if (dance::m_NoDisplay == TRUE)
    {
	UsingTk	= FALSE	;
	Tcl_Main(argc, argv, Tcl_AppInit);
    }
    else
    {
	UsingTk	= TRUE ;
	Tk_Main(argc, argv, Tcl_AppInit);
    }
}

// Tcl_AppInit:
//	application-specific initialization
int danceTcl::Tcl_AppInit(Tcl_Interp *interp)
{
    if (Tcl_Init(interp) == TCL_ERROR) return TCL_ERROR;
    
    // Set the interpreter variable immediately
    // cause it is used in outputMessage()
    Interpreter = interp;

    LinkUserVariables(interp) ; 
    InitUserTclCommands(interp);

    if (UsingTk	== TRUE)
    {
	if (Tk_Init(interp) == TCL_ERROR) return TCL_ERROR;
	char filename[256];
	sprintf(filename,"%s/bin/danceshell.tcl",getenv("DANCE_DIR"));
	if (TCL_OK != Tcl_EvalFile(interp,filename))
		danceTcl::OutputMessage("Could not successfully parse file: %s",
		    filename);
	
    }
        
    return TCL_OK;
}

// LinkUserVariables:
//	Links user variables
void danceTcl::LinkUserVariables(Tcl_Interp *interp)
{
    int	count =	0;
    for(int i =	0 ; setlist[i].ptr ; i++ )
    {
	SETVAR *v = &setlist[i]	;

	if ( Tcl_LinkVar(interp,v->name, v->ptr,v->type) == TCL_ERROR) {
	    danceTcl::OutputMessage("ERROR: Cannot link	variables %s", v->name);
	}
	else
	    count++;
    }
    danceTcl::OutputMessage("Linked %d user Tcl	variables.\n",count);
	// link the variables for the simulator panel
	dance::AllSimulators->InitInterface(interp) ;

}

int danceTcl::edit(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
    if(	dance::m_NoDisplay == TRUE) return TCL_OK	;

    if(	argc !=	2) {
	danceTcl::OutputMessage("USAGE: edit [camera|light|actuator|"
		      "system|translate|scale|tumble|command]\n");
	return TCL_ERROR;
    }

    dance::SetMode(argv[1]) ;

	return(TCL_OK);
}

int danceTcl::remove(ClientData	clientData, Tcl_Interp *interp,	int argc, char **argv)
{
    if(	argc !=	3) {
	danceTcl::OutputMessage("USAGE: remove <type> <name>\n");
	return(TCL_ERROR);
    }

    DanceObjectList *list = getList(argv[1]);
    if (list ==	NULL) {
	danceTcl::OutputMessage("ERROR: Invalid type: %s", argv[1]);
	return(TCL_ERROR);
    }

    if (list->remove(argv[2]) == 0) {
	danceTcl::OutputMessage("ERROR: DANCE object with name %s not found.", argv[2]);
	return TCL_ERROR;
    }

    danceTcl::OutputMessage("OK");
    // update the interface structures
    danceTcl::ExecuteCommand("updateAll") ;
    
    return TCL_OK ;
}


int danceTcl::show(ClientData clientData,
		   Tcl_Interp *interp,int argc,	char **argv)
{
    if(	argc < 2) {
	danceTcl::OutputMessage("USAGE: show [actuator|geometry|system|light|view]	[active]\n");
	return TCL_ERROR;
    }

    DanceObjectList *list = getList(argv[1]);
    if (list ==	NULL) {
	danceTcl::OutputMessage("ERROR: Invalid type: %s", argv[1]);
	return TCL_ERROR;
    }

    DanceObject	*obj = NULL;
    if (argc ==	3) {
	if  (strcmp(argv[2],"active") == 0) {
	     obj = list->getActive();
	     if	(obj ==	NULL) {
		danceTcl::OutputMessage("ERROR: There is no active	object.\n");
		return TCL_ERROR;
	     }
	     Tcl_AppendResult(interp,obj->getName(),(char *)NULL);
	}
	else {
		 // Try and list items in list of given type in argv[2]
		int found = 0;
		for (int i = 0; i < list->size(); i++) {
			obj = list->get(i);
			if (strcmp(obj->getType(),argv[2]) == 0) {
				found = 1;
				Tcl_AppendElement(interp,obj->getName());
			}
		}
		if (found == 0) {
			danceTcl::OutputMessage("ERROR: Not a	valid modifier.\n");
			return TCL_ERROR;
		}
		return TCL_OK;
	}
    }
    else {
	for (int i = 0;	i < list->size(); i++) {
	    obj	= list->get(i);
	    Tcl_AppendElement(interp,obj->getName());
	}
    }

    return TCL_OK ;
}

// load:
//	Loads tcl scripts
int danceTcl::load(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
    if (argc < 2) {
	danceTcl::OutputMessage("USAGE: < <TclScript>\n");
	return TCL_ERROR;
    }

    Tcl_EvalFile(interp,argv[1]);
    // update the GUI structures
    danceTcl::ExecuteCommand("updateAll") ;
    return TCL_OK;
}

// all
//	Applies	a command to all members of a list.
//
int danceTcl::all(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
	if (argc <3) {
	   danceTcl::OutputMessage("USAGE:	all [actuator|constraint|view] <command>\n");
	   return TCL_ERROR;
	}

	// Determine type.
	DanceObjectList	*list =	getList(argv[1]);
	if (list == NULL) {
	   danceTcl::OutputMessage("ERROR:	Unrecognized type.\n");
	   return TCL_ERROR;
	}

	argc -=	2;
	argv +=	2;
	return(list->Command(clientData,interp,argc,argv));

}

// active
//	Sets the given object type with	the name active.
int danceTcl::active(ClientData	clientData, Tcl_Interp *interp,	int argc, char **argv)
{
	if (argc !=3) {
	   danceTcl::OutputMessage("USAGE:	active [actuator|system] <name>\n");
	   return TCL_ERROR;
	}

	// Determine type.
	DanceObjectList	*list =	getList(argv[1]);
	if (list)
		list->setActive(argv[2]);
	else {
	   danceTcl::OutputMessage("ERROR:	Unrecognized type.\n");
	   return TCL_ERROR;
	}

	danceTcl::OutputMessage("OK");
	return TCL_OK;
}

// instance
//	Create instances of the	desired	objects.
int danceTcl::instance(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
	if (argc < 3) {
	   danceTcl::OutputMessage("USAGE:	instance <type>	<name>\n");
	   return TCL_ERROR;
	}


	// Analyze type.
	char *listType = NULL;
	DanceObject *obj = NULL;
	PlugIn *plugin = NULL ;

	if( (strcmp(argv[1], "view") != 0 ) && (strcmp(argv[1], "light") != 0 ) )
	    plugin = dance::AllPlugIns->GetInstance(interp,
							    argv[1],argv[2],
							    argc-3,&argv[3]);
	
	if (plugin == NULL) {
	     //	Test for other types of	objects	(non-plugins)
	     DanceObjectList *list = getList(argv[1]);
	     if	(list == NULL) {
		 danceTcl::OutputMessage("ERROR: %s instance creation failed.", argv[1]) ;
		 return TCL_ERROR;
	     }
	     obj = dance::getInstance(interp, argv[1],argv[2],argc-3,&argv[3]);

	     //	getInstance may	perform	its own	list management.

	     if (obj == NULL) {
		 if ((strcmp(argv[1],"view") !=	0) && (strcmp(argv[2],"quadview") != 0)) {
		     danceTcl::OutputMessage("ERROR: Must use a specific plugin name.\n");
		     return TCL_ERROR;
		 }
		 return	TCL_OK;
	     }

	}
	else {
	     obj = plugin;

	     //	Initialize interface.
	     plugin->initInterface(interp) ;
	}


	// Now add this	instance to the	appropriate list.
	DanceObjectList	*list =	getList(obj->getBaseType());
	if (list) {
		// Check for duplicate.
		if (list->get(argv[2]) != NULL)	{
		    delete obj;
		    danceTcl::OutputMessage("ERROR: Name already exists for type. Deleting	object.\n");
		    return TCL_ERROR;
		}
		list->add(obj);
		list->setActive(argv[2]);
	}
	else {
	   danceTcl::OutputMessage("ERROR:	Unrecognized DANCE object type.\n");
	   return TCL_ERROR;
	}

	// update the interface structures
	danceTcl::ExecuteCommand("updateAll") ;
	danceTcl::OutputMessage("OK");
	return TCL_OK;
}

// quit
//	Quits the application.
//
int danceTcl::quit(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
	dance::DeleteAll();
	// Deallocate Tcl properly to close off GUI elements, otherwise on some
	// machines, we may get an invalid memory access error.
	ExecuteCommand("exit"); 
	exit(0);
	return(0);
}

// save
//	Saves all or individual	Dance objects.
//
int danceTcl::save(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
	if (argc < 3) {
	    danceTcl::OutputMessage("USAGE: save <filename> {<type> ...}\n");
	    return TCL_ERROR;
	}


	FILE *fptr = fopen(argv[1],"w");
	if (fptr == NULL) {
	    danceTcl::OutputMessage("ERROR: Cannot	open file to save.\n");
	    return TCL_ERROR;
	}

	// Save individual entries.
	// This third argument is a list.
	int size;
	char **items;
	Tcl_SplitList(interp,argv[2],&size,&items);
	for (int it=0; it < size; it++) {
	
		DanceObjectList	*list =	getList(items[it]);

		DanceObject *obj = NULL;
		if (list) {
			if (list->size() > 0)
				fprintf(fptr,"# BEGIN %s objects.\n\n",list->getType());
			for (int i = 0;	i < list->size(); i++) {
				obj = list->get(i);

				// Technical workaround:
				// It appears that file stream pointers cannot be
				// successfully passed into a plugin in Windows. In this case, we
				// pass in the filename instead and append to the file.
				if (dance::AllPlugIns->IsPlugin(obj->getType())) {
					fclose(fptr); // Close this file.
					PlugIn *plugin = (PlugIn *)obj;
					plugin->printFile(argv[1]);
					fptr = fopen(argv[1],"a"); // Re-open to append from 
											   // the end of the file.
				}
				else
					obj->print(fptr);
			}
			if (list->size() > 0)
				fprintf(fptr,"\n# END %s objects.\n\n",list->getType());
		}
	}

	// Append collision code.
	if (dance::m_AllVolumes) {
		fprintf(fptr,"\n# Add proximity checking volumes.\n");
		fprintf(fptr,"proximity add all\n");
	}
#ifdef WIN32
	if (*items) Tcl_Free((char *)*items); 
#else
	if (items) Tcl_Free((char *) items);
#endif

	fclose(fptr);
	return TCL_OK;
}


/** Handles	commands */
int danceTcl::Command(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv)
{
	 if (argc <= 2)	{
	     danceTcl::OutputMessage("USAGE:	%s <name> [<args> ...]\n",argv[0]);
	     return TCL_ERROR;
	 }

	 DanceObjectList *list = getList(argv[0]);
	 DanceObject *obj = NULL;
	 if (list == NULL) {
	     danceTcl::OutputMessage("ERROR: Non-recognizable or no active DANCE object.\n");
			return TCL_ERROR;
	 }
	 else {
		obj = list->get(argv[1]);

		if (obj	== NULL) {
			danceTcl::OutputMessage("ERROR: Invalid name.\n");
			return TCL_ERROR;
		}
		argc -=	2;
		argv +=	2;
	}

	return(obj->Command(clientData,interp,argc,argv));
}


/**
 * Adds the plugin into the PlugInManager registry list.
 *
 * A PlugIn is added into the PlugInManager registry list without creating an
 * instance of the specified PlugIn (ie., does not associate a name with it).
 * This is useful for cases where a PlugIn may be required by another PlugIn,
 * so that it must exist in the registry before the dependent PlugIn is instanced.
 *
 * @param ClientData clientData
 * @param Tcl_Interp *interp
 * @param int argc
 * @param char **argv
 * @return int 
 */
int danceTcl::Plugin(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
	if (argc != 2) {
		OutputMessage("plugin <plugin-type>");
		return TCL_ERROR;
	}
		
	PlugIn *proxy =	dance::AllPlugIns->AddProxy(argv[1]);
	if (proxy == NULL)
		return TCL_ERROR;
	return TCL_OK;
}
	
// proximity:
//	Commands for adjusting the proximity algorithm.
//
int danceTcl::proximity(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
	if (argc == 1) {
		OutputResult("USAGE: proximity clear|[add system <name> <linkname>|actuator <name>]\n");
		return TCL_OK;
	}

	if (strcmp(argv[1],"clear") == 0) 
		dance::m_Proximity->Clear();
	else if (strcmp(argv[1],"add") == 0) {
		if (argc >= 3) {
			if (strcmp(argv[2],"system") == 0) {
				DSystem *obj = (DSystem *) dance::AllSystems->get(argv[3]);
				if (argc == 5) {
					DanceObject *group = obj->GetGroup(argv[4]);
					if( group == NULL )
					{
						danceTcl::OutputMessage("No such group %s", argv[4]) ;
						return TCL_ERROR ;
					}
					dance::m_Proximity->AddItem(group);
				}
				else {
					OutputResult("Missing group name.\n");
					return TCL_ERROR;
				}
			}
			else if (strcmp(argv[2],"actuator") == 0) {
				DanceObject *act = dance::AllActuators->get(argv[3]);
				dance::m_Proximity->AddItem(act);
			}
			else if (strcmp(argv[2],"all") == 0) 
				dance::m_Proximity->InitializeAll();
			else {
				OutputResult("Invalid object type to add.\n");
				return TCL_ERROR;
			}

			dance::m_AllVolumes = dance::m_Proximity->m_Volumes;
		}
		else {
			OutputResult("Incomplete arguments.\n");
			return TCL_ERROR;
		}
	}
	else if (strcmp(argv[1],"get") == 0) {
		dance::m_Proximity->Reset(dance::m_AllVolumes);
		int num = atoi(argv[2]);
		if (dance::m_Proximity && dance::CursorPosn) {
			Volume *list = NULL;
			DanceObject *exclude = NULL;
			if (argc >= 5) {
				if (strcmp(argv[3],"actuator") == 0) {
					exclude = dance::AllActuators->get(argv[4]);
				}
				else if (strcmp(argv[3],"system") == 0) {
					DSystem *sys = (DSystem *) dance::AllSystems->get(argv[4]);
					exclude = sys->GetGroup(argv[5]);
				}
			}
			int count = dance::m_Proximity->GetClosestN(dance::CursorPosn,num,&list,exclude);
			Volume *wvol = list;
			for (int i = 0; i < count; i++) {
				OutputListElement("%s", wvol->m_DanceObject->getName());
				wvol = wvol->m_Next;
			}
			dance::m_Proximity->Deallocate(list);
		}
	}

	return TCL_OK;
}

// start stop or re-start the simulation for all objects
// Also	makes the shared object	using the system function
// when	a simulation starts.
// If running in no display mode then it calls idleCB for ever.
// LIMITATIONS: Can take only 20 arguments
int danceTcl::simul(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    dance::AllSimulators->Command(clientData, interp, argc, argv) ;
    
    return TCL_OK ;
}


int danceTcl::queryOS(ClientData clientData, Tcl_Interp *interp, int argc,
	char **argv)
{
#ifdef WIN32
	Tcl_AppendResult(interp,"WindowsNT",NULL);
#endif

#ifndef WIN32
#ifdef SGI
	Tcl_AppendResult(interp,"Irix",NULL);
#else // Linux
	Tcl_AppendResult(interp,"Linux",NULL);
#endif
#endif // WIN32 not defined
return TCL_OK;
}

void danceTcl::OutputResult(char *format, ...)
{
	va_list vl;

	//  format is the last argument specified; all
    //  others must be accessed using the variable-argument macros.
	va_start( vl, format);   
	static char message[1024];
	vsprintf(message,format,vl);
	va_end( vl );

	int len = strlen(message);
	assert( len < 1024); // Exceeded internal print buffer.
		
	Tcl_AppendResult(Interpreter,message,NULL);
	
}

void traceProc(ClientData clientDatat, Tcl_Interp *interp,
	int level, char *command, Tcl_CmdProc *cmdProc,
	ClientData cmdClientData, int argc, char *argv[]) 
{
	return ;
}

void danceTcl::OutputMessage(char *format, ...)
{
    va_list vl;   
    
    //  format is the last argument specified; all
    //  others must be accessed using the variable-argument macros.
    va_start( vl, format);   
    static char message[1024];
    vsprintf(message,format,vl);
    va_end( vl );
    
    int len = strlen(message);
    assert( len < 1024); // Exceeded internal print buffer.
    
    char command[1050]; 

    // use lists etc to prevent the interpreter from
    // substituting variables and interpreting special characters
    sprintf(command,"puts [lindex [list {%s}] 0]",message);

    //	 replace new lines with space
    char *s = &command[0] ;
    for( ; *s != '\0' ; s++ )
	if( *s == '\n' ) *s = 32 ;
    
    //	Tcl_Trace trace = Tcl_CreateTrace(Interpreter,3, traceProc, NULL ) ;
    Tcl_Eval(Interpreter, command) ;
    //	Tcl_DeleteTrace(Interpreter, trace) ;
}



// Function name	: danceTcl::ExecuteCommand
// Description	    : 
// Return type		: void 
// Argument         : char *command
void danceTcl::ExecuteCommand(char *command)
{
	Tcl_Eval(Interpreter,command);
}


// OutputListElement:
//	Adds an item to the result list.
void danceTcl::OutputListElement(char * format, ...)
{
	va_list vl;

	//  format is the last argument specified; all
    //  others must be accessed using the variable-argument macros.
    va_start( vl, format);   
	static char message[1024];
	vsprintf(message,format,vl);
	va_end( vl );

	int len = strlen(message);
	assert( len < 1024); // Exceeded internal print buffer.

	Tcl_AppendElement(Interpreter,message);
}
