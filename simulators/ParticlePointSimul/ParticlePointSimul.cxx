#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "DActuator.h"
#include "DSystem.h"
#include "ParticlePointSystem.h"
#include "ParticlePointSimul.h"


PlugIn *Proxy(void) { return (new ParticlePointSimul); } ;

double myRand(double low, double high) ;

PlugIn *ParticlePointSimul::create(Tcl_Interp *interp, int argc, char **argv)
{
    
    if( argc != 1  )
    {
	danceTcl::OutputMessage("usage: instance <simulator type> "
				"<simulator name> <object name>") ;
	return NULL ;
    }
    
    DSystem *ao = (DSystem *) dance::AllSystems->get(argv[0]) ;
    if( ao == NULL ) 
    {
	danceTcl::OutputMessage("No such object: %s", argv[0]) ;
	return NULL ;
    }
    ParticlePointSimul *f = new ParticlePointSimul(ao) ;
    
    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}

ParticlePointSimul::ParticlePointSimul()
{
    m_sys = NULL ;
    m_dt = 0.03 ;
    
    m_fadeFactor = 0.8 ;
    m_ythreshold = -4.0 ;
}

ParticlePointSimul::ParticlePointSimul(DSystem *sys)
{
    if( sys == NULL )
    {
	danceTcl::OutputMessage("ERROR: ParticlPointSimul() null system passed.") ;
	return ;
    }
	AddSystem(sys) ;
    m_sys =  sys ;
    m_sys->simulator = this ;
    m_dt = 0.01 ; 
    m_fadeFactor = 0.8 ;
    m_ythreshold = -4.0 ;
}

int ParticlePointSimul::Start(double time)
{
	m_ignoreBaseFlag = TRUE;
    int i ;
    m_time = time ;
    m_sys->InitSimulation (time, this) ;

    // Initialize the actuators and pass them the object that owns this simulator
    for	(i=0; i < dance::AllActuators->size(); i++)	{
	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
	wact->InitSimul(m_sys, m_time) ;
    }
    return OK ;
}

// clean up at end of simulation
int ParticlePointSimul::Stop(void)
{
    m_sys->AtEndSimul(m_time, this) ;
    for (int i = 0; i < dance::AllActuators->size(); i++)	{
	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
	wact->AtEndSimul(m_sys, m_time) ;
    }
	return TCL_OK ;
}

int ParticlePointSimul::Step(DSystem *sys, double destTime)
{
    while ( m_time < destTime )
    {
	m_sys->BeforeSimStepBase(m_time, m_sys->simulator) ;
	
	int i ;
	for (i = 0; i < dance::AllActuators->size(); i++) {
	    DActuator *act = (DActuator *)dance::AllActuators->get(i);
	    act->BeforeStep(m_sys, m_time) ;
	}
	
	step(destTime) ;
	
	m_sys->AfterSimStepBase(m_time, m_sys->simulator ) ;

	for (i = 0; i < dance::AllActuators->size(); i++) {
	    DActuator *act = (DActuator *)dance::AllActuators->get(i);
	    act->AfterStep(m_sys, m_time) ;
	}
	// Update all actuators.
	
    }
    return 1 ;
}

int ParticlePointSimul::step(double destTime)
{
    ParticlePointList *pl = &((ParticlePointSystem *) m_sys)->m_plist ;

    double dt = m_dt ;
    if( m_time + m_dt > destTime )
	dt = destTime - m_time ;

    m_time += dt ;
    for( PListElement *e = pl->m_first; e ; e = e->m_next )  
    {
	ParticlePoint *p = e->m_particle ;
	p->m_pos[0] += p->m_vel[0]*dt ;
	p->m_pos[1] += p->m_vel[1]*dt  -9.8 * dt*dt *0.5 ;
	p->m_pos[2] += p->m_vel[2]*dt ;
	
	p->m_vel[1] -= 9.8 * dt ;
	if( p->m_pos[1] <= m_ythreshold ) 
	{
	    p->m_pos[1] = m_ythreshold ;
	    p->m_vel[1] = -p->m_vel[1]*m_fadeFactor ;
	    p->m_pos[0] += myRand(-0.5, 0.5) ;
	    p->m_pos[2] += myRand(-0.5, 0.5) ;
	    
	}
    }
    return 1 ;
    
}


int ParticlePointSimul::commandPlugIn(ClientData clientData, Tcl_Interp 
				       *interp, int argc, char **argv)
{
    if( argc < 1 ) 
    {
	danceTcl::OutputMessage("usage: fade_factor <f> | "
				" y_threshold <y> | ") ;
	return TCL_OK ;
    }
    
    if( strcmp(argv[0],"fade_factor") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_fadeFactor) ;
	}
	else
	{
	    m_fadeFactor = atof(argv[1]) ;
	}
    }
    if( strcmp(argv[0],"y_threshold") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_ythreshold) ;
	}
	else
	{
	    m_ythreshold = atof(argv[1]) ;
	}
    }
    return TCL_OK ;
}

// returns a random number in [low, high)
double myRand(double low, double high)
{
    double a = high - low, x ;
#ifdef WIN32
    static double factor = 1.0 / (double) RAND_MAX ;
    x = (double) rand()*factor*a + low ;
#else
    x = drand48()*a + low ;
    //  printf(" x = %lf ", x) ;
#endif
    return x ;
}
