#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef WIN32
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#include "dance.h"
#include "danceTcl.h"
#include "ParticlePointSystem.h"
#include "DSimulator.h"
#include "BoundingBox.h"


void initRand(void) ;
double myRand(double low, double high) ;
void GetPosGrid(double xMin, double xMax, double zMin, 
		double zMax, double *x, double *z) ;

PlugIn *
Proxy(void) { return (new ParticlePointSystem) ;}


ParticlePointSystem::ParticlePointSystem()
{	 
    m_birthRate = 10 ;
    m_lifeTime = 10 ;
    m_posOffset[0] = 0 ;
    m_posOffset[1] = 0 ;
    m_posOffset[2] = 0 ;
    m_initVel[0] = 0 ;
    m_initVel[1] = -0.1 ;
    m_initVel[2] = 0 ;
    
    m_rotX = 0 ;
    m_rotZ = 0 ;

    m_zMin = -5 ;
    m_zMax = 5 ;
    m_xMin = -5 ;
    m_xMax = 5 ;
    m_y = 1 ;

    m_length2 = 0.5 ;

    // initialize the random number generator
    initRand() ;
}

int ParticlePointSystem::commandPlugIn(ClientData clientData, Tcl_Interp 
				       *interp, int argc, char **argv)
{
    if( argc < 1 ) 
    {
	danceTcl::OutputMessage("usage: pos_offset x y z | "
				"source xMin xMax zMin zMax y | "
				"birth_rate <b> | life_time <t> | "
				"vel x y z | "
				"rot_x <rad> | "
				"rox_z <rad> | "
				"length <l> | "
				"m_numParticles") ;
    }
    
    if( strcmp(argv[0],"pos_offset") == 0 ) 
    {
	if( argc != 4 )
	{
	    danceTcl::OutputMessage("%lf %lf %lf", m_posOffset[0], 
				    m_posOffset[1], m_posOffset[2]) ;
	}
	else
	{
	    m_posOffset[0] = atof(argv[1]) ;
	    m_posOffset[1] = atof(argv[2]) ;
	    m_posOffset[2] = atof(argv[3]) ;
	}
    }
    else if( strcmp(argv[0],"vel") == 0 ) 
    {
	if( argc != 4 )
	{
	    danceTcl::OutputMessage("%lf %lf %lf", m_initVel[0], 
				    m_initVel[1], m_initVel[2]) ;
	}
	else
	{
	    m_initVel[0] = atof(argv[1]) ;
	    m_initVel[1] = atof(argv[2]) ;
	    m_initVel[2] = atof(argv[3]) ;
	}
    }
    else if( strcmp(argv[0],"source") == 0 )
    {
	if( argc != 6 )
	{
	    danceTcl::OutputMessage("%lf %lf %lf %lf %lf", 
				    m_xMin, m_xMax, m_zMin, m_zMax, m_y) ;
	}
	else
	{
	    m_xMin = atof(argv[1]) ;
	    m_xMax = atof(argv[2]) ;
	    m_zMin = atof(argv[3]) ;
	    m_zMax = atof(argv[4]) ;
	    m_y = atof(argv[5]) ;
	}
    }
    else if( strcmp(argv[0],"birth_rate") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_birthRate) ;
	}
	else
	{
	    m_birthRate = atof(argv[1]) ;
	}
    }
    else if( strcmp(argv[0],"length") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_length2*2) ;
	}
	else
	{
	    m_length2 = atof(argv[1])*0.5 ;
	}
    }
    else if( strcmp(argv[0],"rot_x") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_rotX) ;
	}
	else
	{
	    m_rotX = atof(argv[1]) ;
	}
    }
    else if( strcmp(argv[0],"rot_z") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_rotZ) ;
	}
	else
	{
	    m_rotZ = atof(argv[1]) ;
	}
    }
    else if( strcmp(argv[0],"life_time") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("%lf", m_lifeTime) ;
	}
	else
	{
	    m_lifeTime = atof(argv[1]) ;
	}
    }
    return TCL_OK ;
}

PlugIn *ParticlePointSystem::create(Tcl_Interp *interp, int argc, char **argv)
{  
    ParticlePointSystem *f = new ParticlePointSystem ;

    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}

void ParticlePointSystem::output(int mode)
{
    m_plist.output(mode) ;
    return ;
} ;

// Generates random particles near the source
int ParticlePointSystem::ParticleGenerator(double time, double dt)
{
    int numNewPart = (int) (dt * m_birthRate) ;
    int i ;
    for( i = 0 ; i < numNewPart ; i++ )
    {
	ParticlePoint *p = new ParticlePoint(0.001, time) ;
	if( p == NULL )
	{
	    danceTcl::OutputMessage("ParticlePointSystem::ParticleGenerator:"
				    " out of memory") ;
	    return i - 1;
	}
	double pos[3] ;

	
		

	GetPosGrid(m_xMin, m_xMax, m_zMin, m_zMax, &pos[0], &pos[2]) ;
	pos[1] = m_y ;
	pos[0] += m_posOffset[0] ;
	pos[1] += m_posOffset[1] + myRand(-0.5, 0.5) ;
	pos[2] += m_posOffset[2] ;
	p->m_length2 = m_length2 ;
	p->UpdateState(pos) ;
	double vel[3] ;
	vel[0] = m_initVel[0] ;
	vel[1] = m_initVel[1] + myRand(-0.5, 0) ;
	vel[2] = m_initVel[2] ;
	p->SetVel(vel) ;


	// get the position of the last part of pend
	DSystem *pend = (DSystem *) dance::AllSystems->get("pend") ;
	if( pend != NULL )
	{
		double vef[3], endf[3] = {0, -0.5, 0} ;
		pend->simulator->GetVel(1,endf, vef) ;
		pend->simulator->GetOrientation(1,vel,WORLDFRAME,vel) ;
		vel[0] += vef[0] ;
		vel[1] += vef[1] ;
		vel[2] += vef[2] ;
		pos[1] = -0.5 ;
		pend->simulator->GetPosition (1, pos, pos) ;
		p->SetVel(vel) ;
		p->UpdateState(pos) ;
	}

	p->m_rotX = m_rotX ;
	p->m_rotZ = m_rotZ ;
	m_plist.add(p) ;
    }
    //    danceTcl::OutputMessage("Made %d particles", numNewPart) ;
    return numNewPart ;
    
}

int ParticlePointSystem::BeforeSimStep(double time, DSimulator *sim)
{
    static double prevTime = 0 ;

    m_plist.removeDead(time, m_lifeTime) ;
    
    if( time - prevTime > 0.1 ) 
    {
	ParticleGenerator(time, time - prevTime) ;
	prevTime = time ;
    }

    m_events.process(interpreter, time) ;
	return 1 ;
}

BoundingBox *ParticlePointSystem::calcBoundingBox(BoundingBox *b)
{
    b->xMin = m_xMin ;
    b->xMax = m_xMax ;
    b->zMin = m_zMin ;
    b->zMax = m_zMax ;
    b->yMin = 0.0 ;
    b->yMax = m_y ;
	return b ;
}


void initRand(void) 
{
#ifdef WIN32
	time_t ltime;
	time( &ltime );
	srand((long int) ltime) ;
#else
    struct timeval t ;
    struct timezone tzp ;
    
    gettimeofday( &t, &tzp) ;
    srand48(t.tv_sec) ;
#endif
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

// returns a random sampe point from the quadrilateral
// (xMin, zMin) (xMax, zMin) ( xMax, zMax) (xMin, zMax)
// using two independent random variables
void GetPosGrid(double xMin, double xMax, double zMin, double zMax, double *x, double *z)
{
    *x = myRand(xMin, xMax) ;
    *z = myRand(zMin, zMax) ;
}





