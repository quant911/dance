#include <stdlib.h>
#include "dance.h"
#include "danceTcl.h"
#include "DSimulatorManager.h"
#include "DSimulator.h"
#include "DSystem.h"

/** Shows the last time we issued a redispay because of simulation */
static double gLastDisplayTime = MINFLOAT ;

DSimulatorManager::DSimulatorManager()
{
	m_CurrentTime = 0.0;
	m_DisplayTimeStep = 0.03; // approx. 1/30 second for 30 fps
	m_state = SM_NOT_RUNNING ;
	m_SimulationTimeStep = 0.01 ;
	m_EndTime = 100.0 ;
	m_autoMake = TRUE ;
}

DSimulatorManager::~DSimulatorManager()
{
		for (int i=0; i	< numDanceObjects; i++)
			if (DanceObjects[i]) {
				delete DanceObjects[i];
				DanceObjects[i] = NULL;
			}
		numDanceObjects = 0;
}


/** command parser */
int DSimulatorManager::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) 
{
    if (argc <= 0) 
    {
	danceTcl::OutputMessage("usage: simul") ;
	
	return TCL_OK ;
    }
    
    if( strcmp(argv[0],"simul") == 0 )
	return Simul(argc-1, &argv[1]) ;
    else
	danceTcl::OutputMessage("usage: simul") ;

    return TCL_OK ;
}

int DSimulatorManager::Simul(int argc, char **argv)
{

    if (argc <= 0) 
    {
	danceTcl::OutputMessage("usage: simul [-setDisplayTimeStep] "
				"[-setCurrentTime] "
				"[-setSimulationTimeStep]"
				"[-setEndTime] "
				"[-setAutoMake] "
				"[-block on|off] start|stop|pause|cont") ;
	return TCL_OK ;
    }
    int count = 0 ;
    while( (count < argc) && (argv[count][0] == '-') )
    {
	if (strcmp(argv[count],"-setDisplayTimeStep") == 0)
	{
	    count++;
	    if( count < argc )
	    {
		m_DisplayTimeStep = atof(argv[count]);		
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected number") ;
		return TCL_ERROR ;
	    }
		count++ ;
	}
	else if (strcmp(argv[count],"-setEndTime") == 0)
	{
	    count++ ;
	    if( count < argc )
	    {
		m_EndTime = atof(argv[count]);
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected number") ;
		return TCL_ERROR ;
	    }   
	    count++ ;
	}
	else if (strcmp(argv[count],"-setSimulationTimeStep") == 0)
	{
	    count++ ;
	    if( count < argc )
	    {
		m_SimulationTimeStep = atof(argv[count]);
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected number") ;
		return TCL_ERROR ;
	    }   
	    count++ ;
	}
	else if (strcmp(argv[count],"-setCurrentTime") == 0)
	{
	    
	    count++;
	    if( count < argc )
	    {
		m_CurrentTime = atof(argv[count]);
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected number") ;
		return TCL_ERROR ;
	    }   
		count++ ;
	}
	else if (strcmp(argv[count],"-block") == 0)
	{
	    count++;
	    if( count < argc )
	    {
		if( strcmp(argv[count], "on") == 0 )
		    dance::m_SimulBlock = TRUE;
		else if( strcmp(argv[count], "off") == 0 )
		    dance::m_SimulBlock = FALSE ;
		else
		{
			danceTcl::OutputMessage("error: expected on|off") ;
			return TCL_ERROR ;
		}
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected on|off") ;
		return TCL_ERROR ;
	    }
		count++ ;
	}
	else if (strcmp(argv[count],"-setAutoMake") == 0)
	{
	    count++;
	    if( count < argc )
	    {
		if( strcmp(argv[count], "on") == 0 )
		    m_autoMake = TRUE;
		else if( strcmp(argv[count], "off") == 0 )
		    m_autoMake = FALSE ;
		else
		{
			danceTcl::OutputMessage("error: expected on|off") ;
			return TCL_ERROR ;
		}
	    }
	    else
	    {
		danceTcl::OutputMessage("error: expected on|off") ;
		return TCL_ERROR ;
	    }
		count++ ;
	}
	else
	{
	    danceTcl::OutputMessage("Unknown argument %s", argv[count]) ;
	    return TCL_ERROR ;
	}

    }
    

    if( count < argc )
    {
	if( strcmp(argv[count], "start") == 0 )
	{
	    if( m_autoMake == TRUE )
	    {
		BuildSimulators() ;
	    }
	    dance::AllSimulators->Start() ;
	    if( dance::m_SimulBlock == TRUE )	// call the main loop code immediately
	    {				        // which will block on the simulation
			dance::IdleCB() ;
	    }
	}
	else if( strcmp(argv[count], "stop") == 0 )
	    dance::AllSimulators->Stop() ;
	else if( strcmp(argv[count], "pause") == 0 )
	    dance::AllSimulators->Pause() ;
	else if( strcmp(argv[count], "cont") == 0 )
	    dance::AllSimulators->Continue() ;
	else
	    danceTcl::OutputMessage("usage: simul [-setDisplayTimeStep] "
				    "[-setCurrentTime] "
				    "[-setSimulationTimeStep]"
				    "[-setEndTime] "
				    "[-block on|off] start|stop|pause|cont") ;
	
    }
    return TCL_OK ;
}

void DSimulatorManager::SetTime(double currTime, double displayTimeStep)
{
	m_CurrentTime = currTime;
	m_DisplayTimeStep = displayTimeStep;

	// Set the time for all Simulators
	for (int i = 0; i < numDanceObjects; i++) {
		DSimulator *sim = (DSimulator *)DanceObjects[i];
		sim->SetTime(currTime);
	}
}

// returns 0 if no step is taken otherwise 1
int DSimulatorManager::Step(void)
{
    int i ;


    int redisplay = 0 ;
    if( m_state != SM_RUNNING ) return 0 ;
   
    // stop if we have reached the end time
    if( m_CurrentTime > m_EndTime )
    {
	m_CurrentTime = m_EndTime ;
	danceTcl::OutputMessage("Reached end of simulation at time %lf.", 
				m_CurrentTime) ;
	Stop() ;
	return 0 ;		// no need to redisplay
    }
 
  
	m_CurrentTime += m_SimulationTimeStep ;
    
    // set the m_CurrentTime to m_EndTime plus an epsilon
    // so that the above comparison will not fail to detect
    // that we should finish at the next round.
    if( m_CurrentTime > m_EndTime ) 
    {
	m_CurrentTime = m_EndTime + 1e-10 ;
	redisplay = 1 ;
    }
	  
    // run the actuators before simulation function
    for( i = 0 ; i < dance::AllActuators->size() ; i++ )
	dance::AllActuators->get(i)->BeforeAllSimStep(m_CurrentTime,m_SimulationTimeStep) ;
    
    for ( i = 0; i < numDanceObjects; i++) {
	DSimulator *sim = (DSimulator *)DanceObjects[i];
	if (sim)
	    sim->StepBase(m_CurrentTime);
    }
    // run the actuators after simul function
    for( i = 0 ; i < dance::AllActuators->size() ; i++ )
	dance::AllActuators->get(i)->AfterAllSimStep(m_CurrentTime,m_SimulationTimeStep) ;
      
    //danceTcl::OutputMessage("Time %lf", m_CurrentTime) ;

    if( (m_CurrentTime - gLastDisplayTime) >= m_DisplayTimeStep )
    {
	gLastDisplayTime = m_CurrentTime ;
	return 1 ;
    }
    else
	{
		static char s[100] ;
		sprintf(s,"set SMCurrentTime %2.2lf", m_CurrentTime) ;
		danceTcl::ExecuteCommand(s) ;
		return redisplay ;
	}
    
}

void DSimulatorManager::Start(void)
{
   
    int i ;
    for( i = 0 ; i < numDanceObjects ; i++ )
    {
	// if simulators are running stop them in case they want to do clean up.
	DSimulator *sim = (DSimulator *) DanceObjects[i] ;
	if( m_state != SM_NOT_RUNNING)
	    sim->StopBase() ;
	if( sim->StartBase(m_CurrentTime) == -1 )
	{
	    danceTcl::OutputMessage("One or more simulators failed to start.") ;
	    return ;
	}
    }

    gLastDisplayTime = MINFLOAT ;

    // make sure the two time step parameters make sense
    if( m_DisplayTimeStep < m_SimulationTimeStep )
    {
	danceTcl::OutputMessage("Warning: Display time step less than"
				"simulation time step. The simulation time "
				"step will be used") ;
    }
    if( m_SimulationTimeStep < 1e-16 )
    {
	danceTcl::OutputMessage("Warning time step too small. Using 0.00001") ;
	m_SimulationTimeStep = 0.00001 ;
    }
    if( numDanceObjects > 0 ) 
	{
		m_state = SM_RUNNING ;
		danceTcl::OutputMessage("Starting simulation.") ;
	}
}


/**
 * <brief description>
 *
 * <full description>
 * @param void
 * @return void 
 */
void DSimulatorManager::Stop(void)
{
    danceTcl::OutputMessage("Stopping simulation.") ;
    m_state = SM_NOT_RUNNING ;
    int i ;
    for( i = 0 ; i < numDanceObjects ; i++ )
    {
	((DSimulator *) get(i))->StopBase() ;
    }
}


/**
 * <brief description>
 *
 * <full description>
 * @return void 
 */
void DSimulatorManager::Pause(void)
{
    if( m_state == SM_RUNNING )
    {
	m_state = SM_PAUSED ;
	danceTcl::OutputMessage("Simulation paused.") ;
    }
    else
	danceTcl::OutputMessage("No simulation running. Command ignored.") ;
}

int DSimulatorManager::IsSimulating(void)
{
	if (m_state == SM_RUNNING)
		return 1;
	return 0;
}

/**
 * <brief description>
 *
 * <full description>
 * @param void
 * @return void 
 */
void DSimulatorManager::Continue(void) 
{
    if( m_state == SM_PAUSED ) 
	m_state = SM_RUNNING ;
    else if( m_state == SM_NOT_RUNNING )
    {
	danceTcl::OutputMessage("Restarting simulation.") ;
	Start() ;
    }
}

/**
 * Loops through systems and calls their BuildAndLinkSimulator function
 *
 * Systems may implement the DSystem::BuildAndLinkSimulator function
 * that automatically instatiates the default simulator.
 * @param void
 * @return void
 */
void DSimulatorManager::BuildSimulators(void)
{
    DanceObjectList *allSystems = dance::getList("system") ;
    for( int i = 0 ; i < allSystems->size() ; i++ )
	((DSystem *)allSystems->get(i))->BuildAndLinkSimulator() ;
}

/** links the variables that the user can set about the all simulators */
void DSimulatorManager::InitInterface(Tcl_Interp *interp)
{
	if ( Tcl_LinkVar(interp,"SMSimulationTimeStep", 
		(char *) &m_SimulationTimeStep,TCL_LINK_DOUBLE) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMSimulationTimeStep");
	}
	if ( Tcl_LinkVar(interp,"SMDisplayTimeStep", 
		(char *) &m_DisplayTimeStep,TCL_LINK_DOUBLE) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMDisplayTimeStep");
	}
	if ( Tcl_LinkVar(interp,"SMEndTime", 
		(char *) &m_EndTime,TCL_LINK_DOUBLE) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMEndTime");
	}
	if ( Tcl_LinkVar(interp,"SMCurrentTime", 
		(char *) &m_CurrentTime,TCL_LINK_DOUBLE) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMCurrentTime");
	}
	if ( Tcl_LinkVar(interp,"SMAutoMake", 
		(char *) &m_autoMake,TCL_LINK_INT) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMAutoMake");
	}
	if ( Tcl_LinkVar(interp,"SMSimulBlock", 
		(char *) &dance::m_SimulBlock, TCL_LINK_INT) == TCL_ERROR) {
			danceTcl::OutputMessage("ERROR: Cannot link	variable %s", "SMSimulBlock");
	}
}



