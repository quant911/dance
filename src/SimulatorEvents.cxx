#include "defs.h"
#include <tcl.h>
#include "danceTcl.h"
#include "SimulatorEvents.h"

static void appendMessage(Tcl_Interp *interp, char *s)
{
    Tcl_AppendResult(interp, s,	(char *) NULL) ;
}

void SimulatorEvent::process(Tcl_Interp *interp, double simtime)
{ 
    if( time <= simtime)
    {
	danceTcl::OutputMessage("Processing event: %s\n", command) ;
	Tcl_Eval(interp, command) ;
	// delete it
	time = -1 ;
	command[0] = '\0' ;
    }
}

void SimulatorEvent::print(FILE *fp) 
{ 
    fprintf(fp, "%lf %s\n", time, command) ; 
}
  
void SimulatorEvent::print(Tcl_Interp *interp)
{
    danceTcl::OutputMessage("%lf %s\n", time, command) ;
}

void SimulatorEvent::remove(void) 
{ 
    command[0] = '\0' ; time = -1 ;
} 

void SimulatorEvent::setEvent(double attime, char *s) 
{
    time = attime ; strcpy(command,s) ;
}

void SimulatorEvents::print(FILE *fp) 
{ 
    for( int i = 0 ; i < numEvents ; i++ ) 
    {
	printf("%d: ", i) ; event[i].print(fp) ;
    }
}

void SimulatorEvents::print(Tcl_Interp *interp) 
{ 
    for( int i = 0 ; i < numEvents ; i++ ) 
    {
	event[i].print(interp) ;
    }
}

void SimulatorEvents::process(Tcl_Interp *interp, double time)
{
    int i ;
    for( i = 0 ; i < numEvents ; i++ )
    {
	event[i].process(interp, time) ;
    }
    
    for( i = (numEvents -1) ; i > -1 ; i-- )
    {
	if( event[i].time == -1 ) removeEvent(interp, i) ;
    }
        
    return ;
}

void SimulatorEvents::addEvent(Tcl_Interp *interp, double attime, char *s)
{
    if( numEvents == MAX_EVENTS)
    {
	printf("Maximum number of events reached, cannot add!\n") ;
	return ;
    }
  
    int i ;
    for( i = 0 ; i < MAX_EVENTS; i++ )
	if( event[i].command[0] == '\0' ) 
	{
	    event[i].setEvent(attime, s) ;
	    numEvents++ ;
	    break ;
	}
    i = numEvents-1 ;
    printf("Added event %d time %lf command: %s\n", i, event[i].time, event[i].command) ;
}

void SimulatorEvents::removeEvent(Tcl_Interp *interp, int index)
{
    if ((index >( numEvents-1)) || (index < 0))
    {
	appendMessage(interp, "Index out of bounds!\n") ;
    }
    else
    {
	event[index].remove() ;
	if(index != (numEvents - 1))
	{
	    // move the events one place
	    for(int i = index ; i < numEvents - 1 ; i++ )
	    {
		event[i].copy(&event[i+1]) ;
	    }
	    event[numEvents - 1].remove() ;
	}
	numEvents-- ;
    }
}
