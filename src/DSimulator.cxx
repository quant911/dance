#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "DSimulator.h"
#include "DActuator.h"


void DSimulator::NotImpl(char *func) 
{
    danceTcl::OutputMessage("Function %s not implemented for %s.", func, getName()) ;
    return ;
}

DSimulator::DSimulator()
{
    setBaseType("simulator") ;
    m_ignoreBaseFlag = FALSE ;
    m_initActuatorsFlag = TRUE ;
    m_initSystemsFlag = TRUE ;
}

DSimulator::~DSimulator()
{
	for (int i = 0 ; i < m_systems.size() ; i++ )
		m_systems.remove(i) ;
}

int DSimulator::StartBase(double time)
{
    // first Initialize the plugin simulator
	SetTime(time) ;
    int res = Start(time) ;

    if( m_ignoreBaseFlag == TRUE ) return res ;

    for( int s = 0 ; s < m_systems.size() ; s++ )
    {
	DSystem *sys = (DSystem *) m_systems.get(s) ;

	// Initialize the system for simulation
	if( m_initSystemsFlag == TRUE ) sys->InitSimulationBase(time, this) ;
	// Set the internal simulator state from the current state of the object
	SetStateFromObjectState(sys) ;
	// Initialize the actuators and pass them the current system 
	if( m_initActuatorsFlag == TRUE )
	{
	    for (int i=0; i < dance::AllActuators->size(); i++) {
		DActuator *wact = (DActuator *)dance::AllActuators->get(i);
		wact->InitSimul(sys, time) ;
	    }
	}
    }
    
    return res ;
}

int DSimulator::StopBase(void)
{
    // call the plugin Stop
    int res = Stop() ;
    
    if( m_ignoreBaseFlag == TRUE )  return res ;
	

    // Call the AtEndSimul method of every object controller by this
    // simulator
    for( int s = 0 ; s < m_systems.size() ; s++ )
    {
	DSystem *sys = (DSystem *) m_systems.get(s) ;
	sys->AtEndSimul(GetTime(), this) ;
    }
    return res ;

}

void DSimulator::StepBase(double destTime)
{
    int i ;
    double t = GetTime() ;
		
    if( m_ignoreBaseFlag == TRUE )
    {
	for( int s = 0 ; s < m_systems.size() ; s++ )
	    Step((DSystem *) m_systems.get(s), destTime) ;
	return ;
    }
    
    while(GetTime() < destTime )
    {
	for( int s = 0 ; s < m_systems.size() ; s++ )
	{
	    DSystem *sys = (DSystem *) m_systems.get(s) ;
	    sys->BeforeSimStepBase(t, this) ;
	    for (i = 0; i < dance::AllActuators->size(); i++) {
		DActuator *act = (DActuator *)dance::AllActuators->get(i);
		act->BeforeStep(sys, t) ;
	    }
	    Step(sys, destTime) ;
	    // update the system's state if applicable
	    SetObjectStateFromState(sys) ;
	    sys->AfterSimStepBase(t, this) ;
	    for (i = 0; i < dance::AllActuators->size(); i++) {
		DActuator *act = (DActuator *)dance::AllActuators->get(i);
		act->AfterStep(sys, t) ;
	    }
	}
    }
    return ;
}

void DSimulator::AddSystem(DSystem *sys)
{
    if( !sys )
	{
		danceTcl::OutputMessage("Cannot add system") ;
			return ;
	}
    if( m_systems.add((DanceObject *) sys) == 1 )
   	sys->simulator = this ;
    else
	danceTcl::OutputMessage("Cannot add system.") ;
    return ;
}

int DSimulator::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{

    if( DanceObject::Command(clientData, interp, argc, argv) == TCL_OK ) return TCL_OK ;

    DSystem *sys ;
    // check simulator base class commands
    if (strcmp(argv[0],"apply") == 0) {
	if (argc != 2) {
	    danceTcl::OutputMessage("USAGE: apply <system name>") ;
	    return TCL_ERROR;
	}
	sys = (DSystem *) dance::AllSystems->get(argv[1]);
	if( sys ) AddSystem(sys) ;
	return TCL_OK ;
    }
    else if( strcmp(argv[0], "remove") == 0	)
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("Expected: remove <system name>") ;
	    return TCL_ERROR;
	}
	sys = (DSystem *) dance::AllSystems->get(argv[1]);
	return TCL_OK ;
    }
    return commandPlugIn(clientData, interp, argc, argv) ;
}

/** Apply the actuator forces */
void DSimulator::ApplyActuatorForces(DSystem *sys, double time, double dt, double *state, 
			   double *dstate)
{
    for	(int i=0; i < dance::AllActuators->size(); i++)	{
	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
	if (wact->controlled ==	0)
	    wact->ExertLoad(sys, time,dt,state,dstate);
    }
}
