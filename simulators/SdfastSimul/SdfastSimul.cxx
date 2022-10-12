/***************************************************************************
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

#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include "windlfcn.h"
#else
#include <dlfcn.h>
#endif

#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "DActuator.h"
#include "DSystem.h"
#include "../systems/ArticulatedObject/ArticulatedObject.h"
#include "SdfastSimul.h"

// put here initializers for all global	variables
double DT = 0.001 ;
double CTol = 0.01;
double TOl = 0.1 ;

static int COllisions =	TRUE ;

PlugIn *Proxy(void) { return (new SdfastSimul); } ;

PlugIn *SdfastSimul::create(Tcl_Interp *interp, int argc, char **argv)
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
    SdfastSimul *f = new SdfastSimul(ao, interp) ;

    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}


DSystem *SdfastSimul::CurrentSimulObject = NULL ;

void SdfastSimul::Defaultuforce(double t, double *q, double *u)
{
    if(	!CurrentSimulObject) {
	printf("No articulated object for simulator.\n");
	return ;
    }
    SdfastSimul  *sim = (SdfastSimul *) CurrentSimulObject->simulator ;
    

    // t is the actual time when variable time step is used
    sim->m_time = t ;

    // Actuators can apply to more than	one articulated	object.
    for	(int i=0; i < dance::AllActuators->size(); i++)	{
	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
	if (wact->controlled ==	0)
	     wact->ExertLoad(CurrentSimulObject,sim->m_time,sim->m_dt,q,u);
    }

    return ;
}

void SdfastSimul::Defaultumotion(double t, double *q, double *u)
{
    return ;
}

// PosError:
//	Position error for point-to-point constraints.
//	perr = ((p1-p2)*(p1-p2)	- d*2)/2 where d = 0
//
void SdfastSimul::PosError(double t, double *q,	double *errs)
{
	return;
}

// VelError:
//	verr = (v1-v2)*(p1-p2)
//
void SdfastSimul::VelError(double t, double *q,	double *u, double *errs)
{
	return;
}

// AccError:
//	aerr = (a1-a2)*(p1-p2) + (v1-v2)*(v1-v2)
//
void SdfastSimul::AccError(double t, double *q,	double *u, double *udot, double	*errs)
{
	return;
}

// ConstraintForces:
//	Constraint forces for point to point constraint.
//	Velocity terms from VelError are:
//		v1*(p1-p2) and -v2*(p1-p2)
//	So constraint forces, calculated with multipliers are:
//	f1 = m*(p1-p2) and f2 =	-m*(p1-p2) = -f1
//	Forces are in the world	frame and must be converted into the body-local	frame.
//
void SdfastSimul::ConstraintForces(double t, double *q,	double *u, double *mults)
{
	return;
}

// dotDistance
//	Convenience function to	calculate the following	dot product.
//	dotprod	= (a1-a2)(b1-b2)
//
double SdfastSimul::dotDistance(double *a1, double *a2,	double *b1, double *b2)
{
	double dotprod = 0.0;
	for (int i = 0;	i < 3; i++)
	   dotprod += (a1[i]-a2[i])*(b1[i]-b2[i]);
	return(dotprod);
}



// called from sdfast code
extern "C" {
DLLEXPORT void (*sduforce)(double,  double *, double *)	= SdfastSimul::Defaultuforce ;
DLLEXPORT void (*sdumotion)(double,  double *, double *) = SdfastSimul::Defaultumotion ;
DLLEXPORT void (*sduperr)(double, double *, double *) =	SdfastSimul::PosError;
DLLEXPORT void (*sduverr)(double, double *, double *, double *)	= SdfastSimul::VelError;
DLLEXPORT void (*sduaerr)(double, double *, double *, double *,	double *) = SdfastSimul::AccError;
DLLEXPORT void (*sduconsfrc)(double, double *, double *, double	*) = SdfastSimul::ConstraintForces;
	   }

// end called from sdfast code

// called from lsodes
//DLLEXPORT void (*CalcDeriv)(double *y, double *dy,  double *t) = SdfastSimul::LsodesCalcDeriv ;

SdfastSimul::SdfastSimul()
{
    m_end	= MAXFLOAT ;
    m_dt = 0.001 ;
    m_lock = NULL;
    m_state = NULL ;
    m_dstate = NULL ;
    m_initVel = NULL ;
    m_isLoaded = FALSE ;
    handle = NULL ;
    m_time = 0.0 ;
    fixedStep =	TRUE ;		// fixed step integrator is the default
    m_integrator = 0 ;		// default sdfast integrator
   
    setType("SdfastSimul");
    setName("");
    interpreter = NULL ;
    ao = NULL ;

    m_iwork = NULL ;
    m_rwork = NULL ;
    m_liw = 0 ;
    m_lrw = 0 ;
    m_istate = 1 ;
}

SdfastSimul::SdfastSimul(DSystem *obj, Tcl_Interp *interp)
{
    tol	= 0.2 ;
    m_dt = 0.001 ;
    m_state = NULL ;
    m_dstate = NULL ;
    m_initVel = NULL ;
    m_lock = NULL ;   
    ao = obj ;
    AddSystem(ao) ;
    m_time = 0.0 ;
    m_isLoaded = FALSE ;
    handle = NULL ;
    setType("SdfastSimul") ;
    setName("");
    m_end	= 100.0 ;
    interpreter = interp ;
    fixedStep = TRUE ;
    m_integrator = 0 ;

    nbod = 0 ;
    njnt = 0 ;
    ndof = 0 ;
    nloop = 0 ;
    nldof = 0 ;
    nq = 0 ;
    nu = 0 ;
    nlq = 0 ;
    nlu = 0 ;
    nc = 0 ;
    nlc = 0 ;
    npresc = 0 ;
    nuserc = 0 ; 

    m_iwork = NULL ;
    m_rwork = NULL ;
    m_liw = 0 ;
    m_lrw = 0 ;
    m_istate = 1 ;

    if( Load() == ERR )
	danceTcl::OutputMessage("Cannot load!") ;

    danceTcl::OutputMessage("==========================================") ;
    danceTcl::OutputMessage("Dynamics provided by Symbolic Dynamics Inc.") ;
    danceTcl::OutputMessage("==========================================") ;
    
}

SdfastSimul::~SdfastSimul()
{
     if (m_initVel != NULL )
	 delete [] m_initVel ;
    if (m_state != NULL )
	delete [] m_state	;
    if (m_dstate != NULL )
	delete [] m_dstate ;
    if (m_lock != NULL)
	delete [] m_lock;
    if(	handle != NULL )
    {
	dlclose(handle)	;
	handle = NULL ;
    }
}


int SdfastSimul::Step(DSystem *sys, double destTime)
{
    CurrentSimulObject = (ArticulatedObject *) sys ;
    //danceTcl::OutputMessage("Step ========== %lf ============", m_time) ;

    //ao->m_events.process(interpreter, m_time) ;
    
    // for (i = 0; i < dance::AllActuators->size(); i++) {
    //	DActuator *act = (DActuator *)dance::AllActuators->get(i);
    //	act->BeforeStep(ao, m_time) ;
    //}
    double dt = m_dt ;

    if( m_time + m_dt > destTime )
	dt = destTime - m_time ;
    
    
    if( fixedStep == TRUE )	// fixed step integrator
    {
	(*sdfmotion)(&m_time,m_state,m_dstate,dt,ctol,&flag,&errest,&err) ;
    }
    else			// variable step integrator
	    (*sdmotion)(&m_time,m_state,m_dstate,dt,ctol,tol,&flag,&err) ;

    if (err == 0) {
	// moved the base class
	//for (i = 0; i < dance::AllActuators->size(); i++) {
	//	DActuator *act = (DActuator *)dance::AllActuators->get(i);
	//	act->AfterStep(ao, m_time) ;
	//}
	return 1;
    }
    if (err == 1) {
	printf("sdmotion: went over a step at time: %f\n",m_time);
	return 2;
    }
    if (err == 2)
	printf("sdmotion: can't	continue (lock-up), time: %f\n",m_time);
    if (err == 3)
	printf("sdmotion: can't	continue (constraint-violated),	time: %f\n",m_time);
    
    // Pause simulation if something went wrong
    if( err > 2 )
	ao->isSimul	= FALSE;
    
    //   else
//      {
//  	// the new stuff ------------------------------
//  	long int neq = nu+nq ;
//  	if( flag == 1)
//  	{
//  	    flag = 0 ;
	    
//  	    // myDeriv uses the c indexing
//  	    //myDeriv(time, m_state, m_dstate, &tol, &status) ;
//  	    LsodesCalcDeriv(m_state, m_dstate, &m_time) ;
	    
//  	    m_istate = 1 ;
//  	    m_lrw = 20*neq + 16 + 100*neq*neq ;
//  	    m_liw = 10*neq ;
//  	    if( m_rwork == NULL ) delete [] m_rwork ;
//  	    if( m_iwork == NULL ) delete [] m_iwork ;
//  	    m_rwork = new double [m_lrw] ;
//  	    m_iwork = new long int [m_liw] ;
//  	}
	
//  	double tout = m_time+m_dt ;
//  	//sdfinteg(myDeriv,&time, m_state, m_dstate, &tol, m_dt, neq, work, &errest, &err) ;
	
//  	//long mf = 212 ;
//  	long mf = m_integrator ;
//  	long itask = 1 ;
	
//  	long int itol = 1 ;
//  	long int iopt = 0 ;
	
//  	lsodes_(&neq, m_state,&m_time, &tout, &itol, &tol,&tol,&itask,&m_istate,&iopt,
//  		m_rwork,&m_lrw, m_iwork, &m_liw,&mf) ;
//  	if( m_istate < 0 ) 
//  	{
//  	    switch (m_istate) 
//  	    {
//  		case -1 : 
//  		    danceTcl::OutputMessage("Integration error: Excessive work!") ;
//  		    break ;
//  		case -2:
//  		    danceTcl::OutputMessage("Integration error: Too much accuracy!") ;
//  		    break ;
//  		case -3:
//  		    danceTcl::OutputMessage("Integration error: Input error!") ;
//  		    break ;
//  		case -4:
//  		    danceTcl::OutputMessage("Integration error: Repeated errors!") ;
//  		    break ;
//  		case -5:
//  		    danceTcl::OutputMessage("Integration error: Convergence errors!") ;
//  		    break ; 
//  		case -6:
//  		    danceTcl::OutputMessage("Integration error: Variable vanished!") ;
//  		    break ; 
//  		case -7:
//  		    danceTcl::OutputMessage("Integration error: Fatal error!") ;
//  		    break ;     
//  		default:
//  		    break ;
//  	    }
//  	    danceTcl::OutputMessage("It happened at time %lf", m_time) ;
//  	    // stop the simulation
//  	    ao->isSimul = FALSE ;
//  	}
//  	for (i = 0; i < dance::AllActuators->size(); i++) {
//  	    DActuator *act = (DActuator *)dance::AllActuators->get(i);
//  	    act->AfterStep(ao, m_time) ;
//  	}
//  	// Update all actuators.
//  	for (i = 0; i < dance::AllActuators->size(); i++) {
//  	    DActuator *act = (DActuator *)dance::AllActuators->get(i);
//  	    act->UpdateState(m_time,m_dt);
//  	}
//  	return;
//      }
    // end the new stuff -----------------------------

    // printf("Istate = %ld\n", istate) ;
    // fprintf(stderr,"==========\nTime: %f\n",time);
    //  danceTcl::OutputMessage("======= Time : %lf\n", time) ;
   return 1 ;
}

// does	the compilation	of the name.sd file to produce the shared object
int SdfastSimul::MakeCompile(char nameObj[])
{
#ifdef macintosh
    printf("No auto-make on Macintosh.\n");
#else
    char command[MAX_LINE] ;
    char precommand[MAX_LINE] ;
    sprintf(precommand,"cd %s/sdfastObjs",getenv("DANCE_DIR"));
#ifdef __sgi
    sprintf(command,"%s; make 'SYS=%s' -f Makefile_dyn_comp_no_rsh irix\n",precommand,nameObj)	;
#elif WIN32
	danceTcl::OutputMessage("No auto-make on windows.");
	return OK;
#else
    sprintf(command,"%s; make 'SYS=%s' -f Makefile_dyn_comp_no_rsh linux\n",precommand,nameObj) ;
#endif
    printf("Making the shared object:\n%s\n", command) ;
    system(command) ;
#endif
    return OK ;
}

// clean up at end of simulation
int SdfastSimul::Stop(void)
{
  //    ao->AtEndSimul(m_time, this) ;
//      for (int i = 0; i < dance::AllActuators->size(); i++)	{
//  	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
//  	wact->AtEndSimul(ao, m_time) ;
//      }
    return TCL_OK ;
}


// PROC:  Start() previously called init()
// DOES:  initializes the simulator to start from the begining.
// If the dynamically loaded quantities	are not	loaded
// then	it attempts to load them, allocate state vectors and bind some functions
int SdfastSimul::Start(double time)
{
    err	= 0 ;
    errest = 0.0 ;
    flag = 1 ;
    m_time = time ;
    if( ao == NULL ) return ERR ;
    
        
    if( m_isLoaded == FALSE )
    {
	if( Load() == ERR ) 
	    return ERR ;
    }
    else
    {
	sdinit() ;		  // initialize	sdfast
	danceTcl::OutputMessage("Parameters for simulation dt = %lf time = %lf tol = %lf\n",
				m_dt,
				m_time,
				tol) ;
	
	assemblyAnalysis();
	initVelocityAnalysis();
    }
    // initialize various quantities
    initSdState();

    // flag not to use the base code of StartBase, StepBase, StopBase.
    //    m_ignoreBase = TRUE ;

    //SetStateFromObjectState(ao);
    
    //ao->InitSimulation(time, this) ;
    
    // Initialize the actuators and pass them the object that owns this simulator
   //    for	(i=0; i < dance::AllActuators->size(); i++)	{
//    	DActuator *wact = (DActuator *)dance::AllActuators->get(i);
//    	wact->InitSimul(ao, m_time) ;
//        }

    return OK ;
}

int SdfastSimul::bindPointers(void)
{
    char fileName[MAX_LINE] ;
    char prefix[MAX_LINE] ;
    char routine[MAX_LINE] ;

    strcpy(prefix,ao->getName()) ;
    // construct the file name <name>.so
#ifdef macintosh
    sprintf(fileName,"%s.shlb\0", ao->getName()) ;
#elif WIN32
	sprintf(fileName,"%s/sdfastObjs/%s/%s.dll\0",getenv("DANCE_DIR"),ao->getName(),	ao->getName()) ;
#else
    sprintf(fileName,"%s/sdfastObjs/%s/%s.so\0",getenv("DANCE_DIR"),ao->getName(), ao->getName()) ;
#endif
    dlerror() ;	dlerror() ;	// clear the error messages
    if(	handle != NULL ) dlclose(handle) ;
    handle = dlopen(fileName, RTLD_NOW);
    if(	handle == NULL )
    {
	danceTcl::OutputMessage("Error opening |%s|!\n", fileName) ;
	danceTcl::OutputMessage("%s\n", dlerror()) ;
	return ERR ;
    }
    else
	danceTcl::OutputMessage("Successfully linked in %s\n",fileName);

    // ----------------------------------------------------
    // bind some of the	function pointers
    // ----------------------------------------------------
    sprintf(routine,"%sinit", prefix) ;
    if ((sdinit	= (void	(*) (void) ) dlsym(handle,routine)) == NULL)
    {
	  printf("Cannot load routine!\n") ;
	  printf("%s\n", dlerror()) ;
	  return ERR ;
    }

    sprintf(routine,"%sgrav",prefix);
    if ((sdgrav	= (void	(*) (double *) ) dlsym(handle,routine))	== NULL)
    {
	  printf("Cannot load routine!\n") ;
	  printf("%s\n", dlerror()) ;
	  return ERR ;
    }

    sprintf(routine,"%sprinterr",prefix);
    if ((sdprinterr = (void (*)	(FILE *) ) dlsym(handle,routine)) == NULL)
    {
	  fprintf(stderr,"Cannot load sdprinterr routine!\n") ;
	  danceTcl::OutputResult("%s\n", dlerror()) ;
	  return ERR ;
    }

    sprintf(routine,"%sstate", prefix) ;
    if((sdstate	= (void	(*) (double, double*, double *)) dlsym(handle,routine))	== NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%sderiv", prefix) ;
    if((sdderiv	= (void	(*) (double*, double *)) dlsym(handle,routine))	== NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%sstatic",	prefix)	;
    if((sdstatic = (int	(*) (double, double*, int *, double,
		double,	int, int *, int	*)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdstatic routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%ssteady",	prefix)	;
    if((sdsteady = (int	(*) (double, double*, int *, double,
		double,	int, int *, int	*)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdsteady routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }


    sprintf(routine,"%sang2st",	prefix)	;
    if((sdang2st = (void (*) (double*, double *)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sgetbtj",	prefix)	;
    if((sdgetbtj = (void (*) (int, double*)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sindx", prefix);
    if((sdindx = (int (*) (int,	int)) dlsym(handle,routine)) ==	NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sjnt", prefix);
    if((sdjnt =	(void (*) (int,	int *, int *)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sitj", prefix) ;
    if((sditj =	(void (*) (int,	double *)) dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sfmotion", prefix) ;
    if((sdfmotion = (int (*) (double *,	double *, double *, double, double, int	*,double *, int	*))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%smotion",	prefix)	;
    if((sdmotion = (int	(*) (double *, double *, double	*, double, double, double, int *, int *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdmotion routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sacc", prefix) ;
    if((sdacc =	(void (*) (int,	double *, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdacc routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%spos", prefix) ;
    if((sdpos =	(void (*) (int,	double *, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdpos routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%strans", prefix) ;
    if((sdtrans	= (void	(*) (int,  double *, int, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }


    sprintf(routine,"%sassemble", prefix) ;
    if((sdassemble = (int (*) (double,	double *, int *, double, int, int *, int *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdassemble routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sinitvel", prefix) ;
    if((sdinitvel = (int (*) (double,  double *, int *,	double,	int, int *, int	*))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdinitvel routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%spointf",	prefix)	;
    if((sdpointf = (void (*) (int,  double *, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%shinget",	prefix)	;
    if((sdhinget = (void (*) (int,  int, double))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sbodyt", prefix) ;
    if((sdbodyt	= (void	(*) (int, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%svel", prefix) ;
    if((sdvel =	(void (*) (int,	 double	*, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    sprintf(routine,"%sstab", prefix) ;
    if((sdstab = (void (*) (double , double ))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load sdstab routine!\n")	;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }



    sprintf(routine,"%spresvel", prefix) ;
    if((sdpresvel = (void (*) (int, int, double))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%sprespos", prefix) ;
    if((sdprespos = (void (*) (int, int, double))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%spresacc", prefix) ;
    if((sdpresacc = (void (*) (int, int, double))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%spres", prefix) ;
    if((sdpres = (void (*) (int, int, int))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%sfinteg", prefix) ;
    if((sdfinteg = (void (*)(void (*func) (double,double *,double *,double *,int *), 
			   double *time, double *st, double *dst, double *param, 
			   double step, int neq, double *work, double *errest, int *status))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%srel2cart", prefix) ;
    if((sdrel2cart = (void (*) (int, int, double *, double *, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }
    sprintf(routine,"%slsslv", prefix) ;
    if((sdlsslv	= (void	(*) (int, int, int, int, int,
			     int *, int	*, double, double *,
			     double *, int *, double *,	double *, double *))
	dlsym(handle,routine)) == NULL)
    {
	printf("Cannot load routine!\n") ;
	printf("%s\n", dlerror()) ;
	return ERR ;
    }

    //  sprintf(routine,"%sMyderiv", prefix) ;
//      if((myDeriv	= (void	(*)(double time, double *state, double *dstate, 
//  			    double *param, int *status))
//  	dlsym(handle,routine)) == NULL)
//      {
//  	printf("Cannot load routine!\n") ;
//  	printf("%s\n", dlerror()) ;
//  	return ERR ;
//      }
    
    return OK ;
}

// initialize to zero and normalize the	quaternions in the state
void SdfastSimul::initSdState(void)
{
    int i ;

    for( i = 0 ; i < (nq+nu) ; i++ )
	m_state[i] = m_dstate[i] = 0.0 ;
    for( i = 0 ; i < nu ; i++ )
    {
	  m_initVel[i] = 0.0 ;
    }
    (*sdang2st)(m_state,m_state) ;
}

// SetObjectStateFromState previously called setJointsFromStateVector:
//	Sets the joints	from the state vector.
//
int SdfastSimul::SetObjectStateFromState(DSystem *sys)
{
    // Loop through all	joints and set the state vector.
    
    ArticulatedObject *artObj = (ArticulatedObject *) sys ;
    Joint **joint =  artObj->getJoints();
    if (joint == NULL)
	printf("Could	not find joints	for object\n");
    
    int	i, dof, n;
    for	( i = 0; i < artObj->getNumJoints(); i++) {
	dof = joint[i]->getStateSize();
	
	
	for (n	= 0; n < dof; n++)
	    joint[i]->setState(n,m_state[(*sdindx)(i,n)], TRUE);
    }
    
    // Update all actuators
    for (i = 0; i < dance::AllActuators->size(); i++) {
	DActuator *act = (DActuator *)dance::AllActuators->get(i);
	act->afterObjectUpdate(sys);
    }
    return 1 ;
}

// SetStateFromObjectState: previously called  setStateVectorFromJoints:
//	Loads the state	vector with the	current	joint state configuration
//	from the articulated object.
int SdfastSimul::SetStateFromObjectState(DSystem *sys)
{
    ArticulatedObject *artObj = (ArticulatedObject *) ao ;
    // Loop through all	joints and set the state vector.
    Joint **joint =  artObj->getJoints();
    if (joint == NULL)
	  printf("Could	not find joints	for object\n");

    int	dof, n ;
    for	(int  i	= 0; i < artObj->getNumJoints(); i++) {
	 dof = joint[i]->getStateSize();

	 for ( n = 0; n	< dof; n++)
	    m_state[(*sdindx)(i,n)] = joint[i]->getState(n);
    }
    return 1 ;
}

void SdfastSimul::assemblyAnalysis()
{
	int fcnt, err;
	sdassemble(m_time,m_state,m_lock,ctol,MAXEVALS,&fcnt,&err);

	if (err	== 0)
	    printf("assembly: succeeded at constraint tolerance: %f\n",ctol);
	if (err	== 1)
	    printf("assembly: Local minimum reached in assembly.\n");
	if (err	== 2)
	    printf("assembly: Search stop prematurely due to MAXEVALS.\n");
       printf("assembly: Function Count: %d, MaxEval: %d\n",fcnt,MAXEVALS);
}

void SdfastSimul::initVelocityAnalysis()
{
	int fcnt, err;
	sdinitvel(m_time,m_state,m_lock,tol,MAXEVALS,&fcnt,&err);
	if (err	== 0)
		danceTcl::OutputMessage("initvel: All velocities within tolerance.\n");
	if (err	== 1)
		danceTcl::OutputMessage("initvel: No velocities exist that meet constraints.\n");
	if (err	== 2)
		danceTcl::OutputMessage("initvel: Search stop prematurely due to	MAXEVALS.\n");
       danceTcl::OutputMessage("initvel: Function Count: %d, MaxEval: %d\n",fcnt,MAXEVALS);
}

void SdfastSimul::staticAnalysis()
{
       int fcnt, err;
       sdstatic(m_time,m_state,m_lock,ctol,tol,MAXEVALS, &fcnt,&err);
       if (err == 0)
	    printf("static: succeeded at constraint tolerance: %f\n",ctol);
       if (err == 1)
	    printf("static: Local minimum reached in static analysis.\n");
       if (err == 2)
	    printf("static: Search stop	prematurely due	to MAXEVALS.\n");
       printf("static: Function	Count: %d, MaxEval: %d\n",fcnt,MAXEVALS);
}

void SdfastSimul::steadyStateAnalysis()
{
	int fcnt, err;
	sdsteady(m_time,m_state,m_lock,ctol,tol,MAXEVALS,&fcnt,&err);
       if (err == 0)
	    danceTcl::OutputMessage("steady: succeeded at given tolerance: %f\n",tol);
       if (err == 1)
	    danceTcl::OutputMessage("steady: Local minimum reached in static analysis.\n");
       if (err == 2)
	    danceTcl::OutputMessage("steady: Search stop prematurely due to MAXEVALS.\n");
       danceTcl::OutputMessage("steady: Function Count: %d, MaxEval: %d\n",fcnt,MAXEVALS);
}

void SdfastSimul::Savedstate(FILE *fp)
{
    for( int i = 0 ; i < (nu - 1)  ; i++ )
	fprintf(fp, "%lf ", m_dstate[i]) ;
    fprintf(fp, "%lf", m_dstate[nu-1]) ;
}

void SdfastSimul::LsodesCalcDeriv(double *y, double *dy, double *t)
{
    SdfastSimul *sim = (SdfastSimul *) CurrentSimulObject->simulator ;
    //    CurrentSimulObject->simulator->myDeriv(*t, y, dy, &tol, &status) ;

    int NQ = sim->nq ;
    int NC = sim->nc ;
    sim->sdstate(sim->m_time, &y[0], &y[NQ]) ;
    // penduforce(double t, double *q, double *u);
    Defaultuforce(sim->m_time, &y[0], &y[NQ]) ;
    Defaultumotion(sim->m_time, &y[0], &y[NQ]) ; // if we had prescribed motions
    sim->sdderiv(&dy[0], &dy[NQ]) ;

    // check the constraints
    //*status = 1 ;
   //   sim->sdverr(errs) ;
//      for( int i = 0 ; i < sim->nc ; i++ )
//      {
//      if ( fabs(errs[i]) > param[0] ) return ;
//      }
//      sim->sdperr(errs) ;
//      for( int i = 0 ; i < sim->nc ; i++ )
//      {
//      if ( fabs(errs[i]) > param[0] ) return ;
//      }

    //*status = 0 ;
    return ;

}

//  int SdfastSimul::Step(double destTime)
//  {
//      // used by the static functions such as Default force
//      CurrentSimulObject = ao ;
//      while ( m_time < destTime )
//      {
//  	ao->BeforeSimStepBase(m_time, this) ;
//  	step(destTime) ;
//  	ao->AfterSimStepBase(m_time, this) ;
//      }
//      return 1 ;
//  }


// load()
// loads the simulator and allocates state vectors etc
int SdfastSimul::Load(void)
{
    char fileName[MAX_LINE] ;
    char param[MAX_LINE] ;
    char line[MAX_LINE]	;
    FILE *fp = NULL ;

    int i ;

    err	= 0 ;
    errest = 0.0 ;
    flag = 1 ;
    ctol = CTol	;
    tol	= TOl ;
    m_dt = DT ;

    m_time = 0 ;
    if( ao == NULL ) return ERR ;
    if(	m_isLoaded != TRUE)
    {


	// make and compile
	MakeCompile(ao->getName()) ;
	// construct the file name <name>_info
#ifdef macintosh
	sprintf(fileName,"::sdfastObjs:%s:%s_info\0", ao->getName(), ao->getName())	;
#else
	sprintf(fileName,"%s/sdfastObjs/%s/%s_info\0", getenv("DANCE_DIR"),ao->getName(), ao->getName()) ;
#endif
	if((fp = fopen(fileName,"r")) == NULL)
	{
	    danceTcl::OutputMessage("Cannot open file %s\n", fileName) ;
	    return ERR ;
	}
	
	int	nfound = 0 ;
	do {
	    fgets(line,MAX_LINE,fp)	;
	    strcpy(param,""); // To	clear param
	    sscanf(line,"%s", param) ;
	    if( strcmp(param,"nbod") == 0)
	    {
		sscanf(line,"%s %d",param,&nbod) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"njnt") == 0)
	    {
		sscanf(line,"%s %d",param,&njnt) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"ndof") == 0)
	    {
		sscanf(line,"%s %d",param,&ndof) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nloop") == 0)
	    {
		sscanf(line,"%s %d",param,&nloop) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nldof") == 0)
	    {
		sscanf(line,"%s %d",param,&nldof) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nq") == 0)
	    {
		sscanf(line,"%s %d",param,&nq) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nu") == 0)
	    {
		sscanf(line,"%s %d",param,&nu) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nlq") ==	0)
	    {
		sscanf(line,"%s %d",param,&nlq) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nlu") ==	0)
	    {
		sscanf(line,"%s %d",param,&nlu) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nc") == 0)
	    {
		sscanf(line,"%s %d",param,&nc) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nlc") ==	0)
	    {
		sscanf(line,"%s %d",param,&nlc) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"npresc")	== 0)
	    {
		sscanf(line,"%s %d",param,&npresc) ;
		nfound++ ;
	    }
	    else if( strcmp(param,"nuserc")	== 0)
	    {
		sscanf(line,"%s %d",param,&nuserc) ;
		nfound++ ;
	    }
	    
	} while(!feof(fp) && (nfound < 13) ) ;
	
	if( fp ) fclose(fp) ;
	
	if (nfound != 13)
	{
	    danceTcl::OutputMessage("Less or more parameters than expected!\n") ;
	    danceTcl::OutputMessage("%d\n",nfound ) ;
	    return ERR ;
	}
	
	
	// bind the	function pointers to their proper functions
	if(	bindPointers() == ERR )
	{
	    danceTcl::OutputMessage("Cannot bind pointers!\n") ;
	    return ERR ;
	}
	
	// we now know the dimensions of our simulation so allocate the state vectors
	
	if( nu > 0 )
	{
	    m_lock = new int[nu];
	    if( m_lock == NULL )
	    {
		danceTcl::OutputMessage("No more memory!") ;
		return ERR ;
	    }
	    for( i=0; i < nu; i++)
		m_lock[i] = 0;
	}
	
	if( (nq+nu) > 0 )
	{
	    m_state = new double [nq+nu] ;
	    if( m_state == NULL )
	    {
		if( m_lock ) delete [] m_lock ;
		printf("Couldn't allocate memory!\n") ;
		return ERR ;
	    }
	}
    
	if( (nu) > 0 )
	{
	    m_dstate = new double [nq+nu] ;
	    if( m_dstate == NULL )
	    {
		danceTcl::OutputMessage("Couldn't allocate memory!\n") ;
		if ( m_lock ) delete [] m_lock ;
		if ( m_state ) delete [] m_state	;
		return ERR;
	    }
	}
	
	if( nu > 0 )
	{
	    m_initVel = new double [nu] ;
	    if( m_initVel == NULL )
	    {
		danceTcl::OutputMessage("Couldn't allocate memory!\n") ;
		if ( m_lock ) delete [] m_lock ;
		if ( m_state ) delete [] m_state ;
		if ( m_dstate ) delete [] m_dstate ;
		return ERR;
	    }
	}
    }

    
    sdinit() ;		  // initialize	sdfast
    danceTcl::OutputMessage("Parameters for simulation dt = %lf time = %lf tol = %lf\n",
			    m_dt,
			    m_time,
			    tol) ;
    
    assemblyAnalysis();
    initVelocityAnalysis();
    
    m_isLoaded = TRUE ;
    return OK ;
}

int SdfastSimul::commandPlugIn(ClientData clientData, Tcl_Interp *interp, 
				 int argc, char **argv)
{

    int new_vel = FALSE ;

    while(argc)
    {
	if( strcmp(argv[0], "dt") == 0)
	{
	    if(	argc < 2 )
	    {
		danceTcl::OutputMessage("ERROR: expected: dt <dt>\n");
		return TCL_ERROR ;
	    }
	    if(	!isdigit(argv[1][0]) )
	    {
		danceTcl::OutputMessage("ERROR: expected dt <dt>\n");
		continue ;
	    }
	    m_dt = atof(argv[1]) ;
	    argc -= 2 ;
	    argv += 2 ;
	}
	else if( strcmp(argv[0], "integ") == 0)
	{
	    if(	argc < 2 )
	    {
		danceTcl::OutputMessage("ERROR: expected: integ 0|<value>\n");
		return TCL_ERROR ;
	    }
	    m_integrator = atoi(argv[1]) ;
	    argc -= 2 ;
	    argv += 2 ;
	}
	else if( strcmp(argv[0], "tol") == 0)
	{
	    if(	argc < 2 )
	    {
		danceTcl::OutputMessage("ERROR: expected: tol <tol>\n");
		return TCL_ERROR ;
	    }
	    if(	!isdigit(argv[1][0]) )
	    {
		danceTcl::OutputMessage("ERROR: expected tol <tol>\n");
		continue ;
	    }
	    tol = atof(argv[1]) ;
	    argc -= 2 ;
	    argv += 2 ;
	}
	else if( strcmp(argv[0], "ctol") == 0)
	{
	    if(	argc < 2 )
	    {
		danceTcl::OutputMessage("ERROR: expected: ctol <ctol>\n");
		return TCL_ERROR ;
	    }
	    if(	!isdigit(argv[1][0]) )
	    {
		danceTcl::OutputMessage("ERROR: expected ctol <ctol>\n");
		argc -= 1 ;
		argv += 1 ;

		continue ;
	    }
	    ctol = atof(argv[1]) ;
	    argc -= 2 ;
	    argv += 2 ;
	}
	else if( strcmp(argv[0], "f") == 0 )
	{
	    danceTcl::OutputMessage("Using fixed time step\n") ;
	    fixedStep = TRUE	;
	    argc -= 1 ;
	    argv += 1 ;
	}
	else if( strcmp(argv[0], "v") == 0 )
	{
	    danceTcl::OutputMessage("Using variable time step\n") ;
	    fixedStep = FALSE ;
	    argc -= 1 ;
	    argv += 1 ;
	}
	else if( strcmp(argv[0], "end") == 0)
	{
	    if(	argc < 2 )
	    {
		danceTcl::OutputMessage("ERROR: expected: ctol <ctol>\n");
		return TCL_ERROR ;
	    }
	    if(	!isdigit(argv[1][0]) )
	    {
		danceTcl::OutputMessage("ERROR: expected ctol <ctol>\n");
		argc -= 1 ;
		argv += 1 ;
		
		continue ;
	    }
	    m_end = atof(argv[1]) ;
	    argc -= 2 ;
	    argv += 2 ;
	}
	else if( (strcmp(argv[0], "sstate") == 0 ) || (strcmp(argv[0], "dstate") == 0 ) )
	{
	    // read the velocities from the given file
	    if( argc > 1 )
	    {
		FILE *fp = fopen(argv[1], "r") ;
		if( fp == NULL )
		{
		    danceTcl::OutputMessage("Cannot open %s", argv[1]) ;
		    danceTcl::OutputMessage("Using 0 velocities") ;
		    argc -= 2 ;
		    argv += 2 ;
		    return TCL_ERROR ;
		}
		for( int i = 0 ; i < nu ; i++ )
		{
		    if( fscanf(fp, "%lf", &m_dstate[i]) != 1 )
		    {
			danceTcl::OutputMessage("Error reading velocity file.") ;
			fclose(fp) ;
			argc -= 2 ;
			argv += 2 ;
			fclose(fp) ;
			return TCL_ERROR ;
		    }
		    m_state[nq+i] = m_dstate[i] ;
		}
		danceTcl::OutputMessage("Read new velocities") ;
		new_vel = TRUE ;		
		fclose(fp) ;
	
	    }

	   
	    argc -= 2 ;
	    argv += 2 ;

	}
	else
	{
	    danceTcl::OutputMessage("Unknown parameter %s.", argv[0]) ;
	    return TCL_ERROR ;
	}
    }

    //  SetStateFromObjectState();
//      sdinit() ;		  // initialize	sdfast
//      danceTcl::OutputMessage("Parameters for simulation dt = %lf time = %lf tol = %lf\n",
//  			    m_dt,
//  			    m_time,
//  			    tol) ;
    
//      assemblyAnalysis();
//      initVelocityAnalysis();
    
    if( new_vel == TRUE ) 
	sdstate(m_time, m_state, m_dstate) ;
    return TCL_OK ;
}

void SdfastSimul::FieldForce(double *force)
{
	Vector localforce ;
    for (int i = 0; i < CurrentSimulObject->GetNumGroups(); i++)
    {
	GetOrientation(-1,force,i,localforce);
	double mass = CurrentSimulObject->GetGroupMass(i) ;
	localforce[0] *= mass ;
	localforce[1] *= mass ;
	localforce[2] *= mass ;
	Vector point = { 0.0, 0.0, 0.0} ;
	PointForce(i,point,localforce);
    }
    return ;
}

void SdfastSimul::PointForce(int argc, char *argv[])
{
    if( argc != 4 )
    {
	danceTcl::OutputMessage("PointForce: wrong number of arguments %d, "
				"expected 4", argc) ;
	return ;
    }
    Link *link = (Link *) argv[0] ;
    // not needed so commented out
    // int *npoint = (int *) argv[1] ;
    double *point = (double *) argv[2] ;
    double *force = (double *) argv[3] ;
    double lforce[3] ;
    // bring the force in local coordinates
    int nl = link->m_linkNumber ;
    GetOrientation(WORLDFRAME,force,nl,lforce) ;
    PointForce(nl, point, lforce) ;
}

int SdfastSimul::GetPosition(DSystem *sys, double *localPoint, double *position)
{
	Link *l = (Link *) sys ;
	sdpos(l->m_linkNumber, localPoint, position) ;
	return 1 ;
}
 
void SdfastSimul::GetVel(DSystem *sys, double *point, double *vel)
{
	Link *l = (Link *) sys ;
	sdvel(l->m_linkNumber, point, vel) ;
	return ;
}
