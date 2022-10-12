#include "defs.h"
#include "danceTcl.h"
#include "PlugIn.h"
#include "DSystem.h"
#include "DanceObject.h"
#include "DSimulator.h"
#include "SimulatorEvents.h"

DSystem::DSystem()
{
    isSimul = FALSE ;
    isPlayback = FALSE ;
    setBaseType("system") ;
}

DSystem::~DSystem()
{
	return ;
}

int DSystem::Command(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv)
{
    if( DanceObject::Command(clientData, interp, argc, argv) == TCL_OK ) return TCL_OK ;

    if( strcmp(argv[0], "simul_event") == 0 )
    {
	if( argc < 2)
	{
	    danceTcl::OutputMessage("Usage: simul_event print|add <time> "
				    "<string>|remove <index>\n") ;
	    danceTcl::OutputMessage("Caution: maximum number of events %d\n", MAX_EVENTS) ;
	    return TCL_OK ; 
	}
	
	if (strcmp(argv[1], "print") == 0)
	{
	    m_events.print(interp) ;
	    return TCL_OK ;
	}
	if( strcmp(argv[1], "add") == 0)
	{
	    if( argc < 4 ) 
	    {
		danceTcl::OutputMessage("Expected: simul_event add <time> <string>\n") ;
		return TCL_ERROR ;
	    }
	    double time = atof(argv[2]) ;
	    if( simulator != NULL )
	    {
		time = time + simulator->GetTime() ;
	    }
	    // if the event is added during simulation
	    // take the given time as being relative
	    // to the current time
	    m_events.addEvent(interp, time, argv[3]) ;
	    return TCL_OK ;
	}
	else if( strcmp(argv[1], "remove") == 0)
	{
	    if( argc < 3) 
	    {
		danceTcl::OutputMessage("Expected: simul_event remove <index>\n") ;
		return TCL_ERROR ;
	    }
	    m_events.removeEvent(interp, atoi(argv[2])) ;
	    return TCL_OK ;
	}
	else
	{
	    danceTcl::OutputMessage("Expected: simul_event print|add <time> "
				    "<string>|remove <index>\n") ;
	    return TCL_ERROR ; 
	}
	
    }
    
    return commandPlugIn(clientData, interp, argc, argv) ;
}


