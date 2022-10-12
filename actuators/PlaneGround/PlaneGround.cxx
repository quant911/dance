/**********************************************************
  This ground is just a	plane ground which is drawn as a
  checkered surface
  **********************************************************/
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "PlaneGround.h"
#include "DSimulator.h"
#include "MonitorPoints.h"
// #include "ArticulatedObject.h"

#ifndef	NO_GL
#include <GL/gl.h>
#endif

#define	Z_SPAN 500

PlugIn *Proxy(void) { return (new PlaneGround);	} ;

PlaneGround::PlaneGround()
{
    textureMode	= 0 ;
    color1[0] =	1.0 ;
    color1[1] =	1.0 ;
    color1[2] =	1.0 ;
    color1[3] =	1.0 ;
    color2[0] =	0.0 ;
    color2[1] =	0.0 ;
    color2[2] =	1.0 ;
    color2[3] =	1.0 ;

    setName("dummyGround") ;
    interpreter	= NULL ;
    npoints = 0	;
    m_stiffness = 100.0 ;
    m_damping = 1.0 ;
    m_friction = 0.0 ;

    am_dif[0] =	(float)1.0 ; am_dif[1] = (float)0.5 ; 
    am_dif[2] = (float)0.2 ; am_dif[3] = (float)1.0 ;
    stencil = FALSE ;
    return ;
}

PlaneGround::~PlaneGround()
{
    if(	interpreter != NULL )
	unLinkVariables(interpreter) ;
}


/************************************************************
  Ground::genGroundMesh2()
  DOES:	generates a quad mesh for the ground given a series
       of points with x*2 dimensions. Also calculates the normals.
**************************************************************/
void PlaneGround::genGroundMesh2(Vector2 *gpoints, int n)
{
    int	i ;
    npoints = n	;

    if(	n > MAX_QUAD_POINTS_X)
    {
	danceTcl::OutputMessage("Maximum number of points exceeded in x-dimension.") ;
	return ;
    }
    qm.nx = n ;
    qm.ny = 2 ;
    for( i = 0 ; i < n ; i++ )
    {
	qm.points[i][0][0] = gpoints[i][0] ;
	qm.points[i][0][1] = gpoints[i][1] ;
	qm.points[i][1][0] = gpoints[i][0] ;
	qm.points[i][1][1] = gpoints[i][1] ;

	qm.points[i][0][2] = (double) -Z_SPAN ;
	qm.points[i][1][2] = (double) Z_SPAN ;
	// calculate the slope of the ground
	if( i >	0)
	    slope[i-1] = (gpoints[i][1]	- gpoints[i-1][1]) /
		(double) (gpoints[i][0]	- gpoints[i-1][0]) ;
    }
    qm.calcNormals() ;		/* calculate normals */

    return ;
}
/************************************************************
  Ground::genGroundMesh()
  DOES:	generates a quad mesh for the ground given a series
       of points with nxm dimensions. Also calculates the normals.
**************************************************************/
void PlaneGround::genGroundMesh(Vector2	*gpoints, int n, int m)
{
    int	i,j ;
    npoints = n	;

    if(	n > MAX_QUAD_POINTS_X)
    {
	danceTcl::OutputMessage("Maximum number of points exceeded in x-dimension.") ;
	return ;
    }
    qm.nx = n ;
    qm.ny = m ;
    double z_inc = 2*Z_SPAN / (double) m ;

    for( i = 0 ; i < n ; i++ )
    {
	for( j = 0 ; j < m ; j++ )
	{
	    qm.points[i][j][0] = gpoints[i][0] ;
	    qm.points[i][j][1] = gpoints[i][1] ;
	    qm.points[i][j][2] = -Z_SPAN + j*z_inc ;
	}
	// calculate the slope of the ground
	if( i >	0)
	    slope[i-1] = (gpoints[i][1]	- gpoints[i-1][1]) /
		(double) (gpoints[i][0]	- gpoints[i-1][0]) ;
    }
    qm.calcNormals() ;		/* calculate normals */

    return ;
}

#ifndef	NO_GL

// it assumes that if a	light is found not to be active
// then	the rest are not active	too
// It can handle 3 different levels of overlapping shadows
// The ground if present it is allways displayed
void PlaneGround::output(int mode)
{
    double nl ;
    int	shadows	;

    if (mode & LDISPLAY_SHADOW)	shadows	= 1 ;
    else shadows = 0 ;

    if( shadows) 
    {
	/**
	if (glutGet((GLenum) GLUT_WINDOW_STENCIL_SIZE) <= 0)
	{
	    stencil = FALSE ;
	    danceTcl::OutputMessage("Cannot use stencil for the shadow!\n") ;
	}
	else
	{
	    stencil	= TRUE ;
	}
	**/
	stencil = FALSE ;
	
    }
    else
	stencil = FALSE ;
    
    /**
    if(	shadows	&& (stencil == TRUE) )
    {
	glClear(GL_STENCIL_BUFFER_BIT) ;
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 8, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    }
    **/
    // draw the	ground with a stencil value of 20

    qm.displayCheck(color1,color2, textureMode)	;

    // display all the shadows if needed
    if(	!shadows ) return ;

    glEnable(GL_BLEND) ;
    glDepthMask(GL_FALSE) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

    // level is	used to	allow the effect of multiple
    // shadows from multiple light sources.
    // Maximum is 8 different light Sources
    int	level =	7 ;
    DanceObjectList	*allLights = dance::getList("light");
    for( int i = 0 ; i < allLights->size() ; i++ )
    {
	DLight *l = (DLight *) allLights->get(i) ;
	if( l->IsOn() == FALSE)
	{
	    break ;
	}
	// check to see	if the light casts a casts a shadow on the ground
	GLfloat lpos[4] ;
	l->GetPosition(lpos) ;
	nl = plane.A * lpos[0] + plane.B * lpos[1] +
	  plane.C * lpos[2] +	 plane.D * lpos[3] ;
	if( nl > 0.0)
	{
	    /**
	    if(	(stencil == TRUE) && (level > -1) )
	    {
		glStencilFunc(GL_LESS, level--,	0xffffffff);  // draw if > 1 
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	    }
	    **/
	    calcShadowMatrices(l) ;
	    glPushMatrix() ;
	    glMultMatrixd(ShadowMatrix)	;
	    if( dance::AllSystems != NULL )
		dance::AllSystems->output(LDISPLAY_SOLID | LDISPLAY_SHADOW) ;
	    glPopMatrix() ;
	}

    }
    glDepthMask(GL_TRUE) ;
    glDisable(GL_BLEND)	;
    if( stencil	== TRUE	)
      glDisable(GL_STENCIL_TEST) ;

    return ;
}

#else
void PlaneGround::draw()
{
    return ;
}
#endif


int PlaneGround::linkVariables(Tcl_Interp *interp)
{
    char varName[256] ;
    sprintf(varName,"stiffness%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_stiffness,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable stiffness\n") ;
	return TCL_ERROR ;
    }
    // else // danceTcl::OutputMessage("Linked variable stiffness\n") ;

    sprintf(varName,"damping%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_damping,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable damping\n") ;
	return TCL_ERROR ;
    }
    // else // danceTcl::OutputMessage("Linked variable damping\n") ;

    sprintf(varName,"friction%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_friction,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable friction\n") ;
	return TCL_ERROR ;
    }
    //else // danceTcl::OutputMessage("Linked variable friction\n") ;

    return TCL_OK ;
}

void PlaneGround::unLinkVariables(Tcl_Interp *interp)
{
    char varName[256] ;

    sprintf(varName,"stiffness%s", getName()) ;
    danceTcl::OutputMessage("interp %p unlinking: %s", interp, varName) ;
    Tcl_UnlinkVar(interp, varName) ;
    sprintf(varName,"damping%s", getName()) ;
    Tcl_UnlinkVar(interp, varName) ;
    sprintf(varName,"friction%s", getName()) ;
    Tcl_UnlinkVar(interp, varName) ;

    return ;
}



// the user must ensure	that the ground	is flat!!
int PlaneGround::changeGeometry(double x1,double y1, double z1,	double x2, double y2, double z2,
				double x3,double y3, double z3,	double x4, double y4, double z4,
				int nx,	int nz)
{
    npoints = 0	;
    //stiffness	= 30.0 ;
    //damp = 2.0 ;
    //m	= 0.5 ;
    am_dif[0] =	(float)1.0 ; am_dif[1] = (float)0.5 ; am_dif[2]	= (float)0.2 ; am_dif[3] = (float)1.0 ;
    int	i,j ;

    if ((nx == 0) || (nz == 0))
    {
	danceTcl::OutputMessage("Cannot use 0 parameter ny or nz") ;
	qm.nx =	0 ;
	qm.ny =	0 ;
	return TCL_ERROR ;
    }

    qm.points[0][0][0] = x1 ;
    qm.points[0][0][1] = y1 ;
    qm.points[0][0][2] = z1 ;

    qm.points[nx-1][0][0] = x4 ;
    qm.points[nx-1][0][1] = y4 ;
    qm.points[nx-1][0][2] = z4 ;

    qm.points[0][nz-1][0] = x2 ;
    qm.points[0][nz-1][1] = y2 ;
    qm.points[0][nz-1][2] = z2 ;

    qm.points[nx-1][nz-1][0] = x3 ;
    qm.points[nx-1][nz-1][1] = y3 ;
    qm.points[nx-1][nz-1][2] = z3 ;

    qm.nx = nx ;
    qm.ny = nz ;
    for( i = 0 ; i < nx	; i++ )
	for( j = 0 ; j < 3 ; j++ )
	{
	    qm.points[i][0][j] = qm.points[0][0][j] +
	      i*(qm.points[nx-1][0][j] - qm.points[0][0][j]) / (double)	(nx-1) ;
	    qm.points[i][nz-1][j] =  qm.points[0][nz-1][j] +
	      i*(qm.points[nx-1][nz-1][j] - qm.points[0][nz-1][j]) / (double) (nx-1) ;
	}



    for( i = 0	; i < nx ; i++ )
	for( j = 0 ; j < nz ; j++)
	{
	    qm.points[i][j][0] = qm.points[i][0][0] +
	      j*(qm.points[i][nz-1][0] - qm.points[i][0][0])/ (double) (nz-1) ;
	    qm.points[i][j][1] = qm.points[i][0][1] +
	      j*(qm.points[i][nz-1][1] - qm.points[i][0][1])/ (double) (nz-1) ;
	    qm.points[i][j][2] = qm.points[i][0][2] +
	      j*(qm.points[i][nz-1][2] - qm.points[i][0][2])/ (double) (nz-1) ;
	}
    qm.calcNormals() ;		// calculate normals 

    // the normal is the first 3 plane coefficients
    plane.A = qm.normals[0][0][0] ;
    plane.B = qm.normals[0][0][1] ;
    plane.C = qm.normals[0][0][2] ;
    // Ax+By+cZ	+D = 0 ;
    plane.D = -VecDotProd(qm.normals[0][0],qm.points[0][0]) ;

    //calcShadowMatrices() ;  SHOULD BE	HERE IF	NOT ON THE FLY!!

    return TCL_OK ;
}

// calculate the bounding box for the ground plane.
BoundingBox *PlaneGround::calcBoundingBox(BoundingBox *box)
{
	qm.calcBoundingBox(box);
	return box;
}

// calculate the shadow	matrices of the	default	light
// for an arbitrary plane ground
void PlaneGround::calcShadowMatrices(DLight *l)
{
    GLfloat lpos[4] ;

    // init shadow Matrix
    for( int i = 0 ; i < 4 ; i++ )
	for( int j = 0 ; j < 4 ; j++)
	    if(	i == j)
		ShadowMatrix[j+4*i] = 1.0 ;
	    else
		ShadowMatrix[j+4*i] = 0.0 ;

   
   l->GetPosition(lpos) ;

   Vector n ;
    n[0] = plane.A ;
    n[1] = plane.B ;
    n[2] = plane.C ;
    // it is allready normalized
    VecNormalize(n) ;
    // check if	this light can cast shadows on this ground

    double nl =	plane.A	* lpos[0] + plane.B * lpos[1] +
	  plane.C * lpos[2] +	 plane.D * lpos[3] ;
    if(	nl <= 0.0)
    {
	danceTcl::OutputMessage("light cannot cast shadows on this ground.") ;
	danceTcl::OutputMessage("Cannot calculate matrices.") ;
	return ;
    }


    ShadowMatrix[0] = nl-n[0]*lpos[0] ;
    ShadowMatrix[1] = -n[0]*lpos[1] ;
    ShadowMatrix[2] = -n[0]*lpos[2] ;
    ShadowMatrix[3] = -n[0]*lpos[3];
    ShadowMatrix[4] = -n[1]*lpos[0] ;
    ShadowMatrix[5] = nl-n[1]*lpos[1] ;
    ShadowMatrix[6] = -n[1]*lpos[2] ;
    ShadowMatrix[7] =  -n[1]*lpos[3] ;
    ShadowMatrix[8] = -n[2]*lpos[0] ;
    ShadowMatrix[9] = -n[2]*lpos[1] ;
    ShadowMatrix[10] = nl-n[2]*lpos[2] ;
    ShadowMatrix[11] = -n[2]*lpos[3] ;
    ShadowMatrix[12] = -lpos[0]*plane.D + n[0]*0.001 ; // The is to make the shadow
    ShadowMatrix[13] = -lpos[1]*plane.D + n[1]*0.001 ; // come up the ground for the
    ShadowMatrix[14] = -lpos[2]*plane.D + n[2]*0.001 ; // the depth test
    ShadowMatrix[15] = nl - plane.D*lpos[3] ;

    // printArray(ShadowMatrix,4,4) ;
    return ;
}

PlugIn *PlaneGround::create(Tcl_Interp *interp,	int argc, char **argv)
{

    danceTcl::OutputResult("Allocating PlaneGround.") ;
    PlaneGround	*g = new PlaneGround ;

    if(	g == NULL )
    {
		danceTcl::OutputMessage("ERROR: out of memory.") ;
	return g ;
    }

    g->interpreter = interp ;


    // give some default geometry
    double dimX = 5.0 ;
    double dimZ = 5.0 ;
    double dimY = 2.0 ;
    g->changeGeometry(-dimX,-dimY,-dimZ, -dimX,-dimY,dimZ,
		      dimX,-dimY,dimZ, dimX,-dimY,-dimZ,
		      10,10) ;

    return g ;
}

int PlaneGround::save(char *name)
{
    FILE *fp ;

    if ( (fp = fopen(name,"w"))	== NULL	)
    {
	danceTcl::OutputMessage("ERROR: cannot open %s",name);
	return ERR ;
    }
    else
	save(fp) ;
    return OK ;
}

int PlaneGround::save(FILE *fp)
{

    fprintf(fp,"actuator %s set model %lf %lf %lf\n", getName(),
	    m_stiffness, m_damping, m_friction)	;
    fprintf(fp,"actuators %s set geometry ",	getName()) ;
    fprintf(fp,"%lf %lf	%lf ", qm.points[0][0][0], qm.points[0][0][1], qm.points[0][0][2]) ;
    fprintf(fp,"%lf %lf	%lf ", qm.points[0][qm.ny-1][0], qm.points[0][qm.ny-1][1],
	    qm.points[0][qm.ny-1][2]) ;
    fprintf(fp,"%lf %lf	%lf ", qm.points[qm.nx-1][qm.ny-1][0], qm.points[qm.nx-1][qm.ny-1][1],
	    qm.points[qm.nx-1][qm.ny-1][2]) ;
    fprintf(fp,"%lf %lf	%lf\n",	qm.points[qm.nx-1][0][0], qm.points[qm.nx-1][0][1],
	    qm.points[qm.nx-1][0][2]) ;
    if(	texture.im != NULL )
	fprintf(fp,"actuators %s set texture_file %s", getName(), texture.fname) ;
    return OK ;

}


int PlaneGround::initInterface(Tcl_Interp *interp)
{
   
    interpreter	= interp ;
    linkVariables(interp) ;
    return TCL_OK ;
}


int PlaneGround::commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{

    if(	argc < 1 )
    {
	// danceTcl::OutputMessage("Expected:  normal|set <param> value(s)...\n") ;
	return TCL_ERROR ;
    }


    if(	strcmp(argv[0],	"set") == 0 )
	return set(interp, argc-1, &argv[1]) ;
    else if( strcmp(argv[0], "texture_file") == 0 )
    {
	if( argc != 2)
	{
	    danceTcl::OutputMessage("usage: texture_file <fname>.") ;
	    return TCL_OK ;
	}
	if( texture.loadTexture(argv[1]) == TCL_ERROR )
	    textureMode = 0 ;
	return TCL_OK ;
    }
    else if (strcmp(argv[0], "texture_mode") == 0 )
    {
	if( argc != 2)
	{
	    danceTcl::OutputMessage("usage: texture_mode 0|1|2."
				    "0: no textrure, 1: apply on plane,"
				    "2: apply per quadrilateral") ;
	    return TCL_OK ;
	}
	textureMode = atoi(argv[1]) ;
	if( (textureMode > 2) || (textureMode < 0) )
	{
	    danceTcl::OutputMessage("usage: texture_mode 0|1|2|."
				    "0: no textrure, 1: apply on plane,"
				    "2: apply per quadrilateral") ;
	    return TCL_OK ;
	}
    }
    else if ( strcmp(argv[0], "normal") == 0 )
    {
	Vector n ;
	GetNormal(n) ;
	danceTcl::OutputListElement("%lf %lf %lf", n[0], n[1], n[2]) ;
    }
    else
    {
	// danceTcl::OutputMessage("Expected:  set <param> value(s)...\n") ;
	return TCL_OK ;
    }
    return TCL_OK ;

}


// sets	the various parameters of the ground actuator
// expects argv[0] = <param_name>
//	   argv[1] = <value 0> ...
int PlaneGround::set(Tcl_Interp	*interp, int argc, char	**argv)
{
    if(	argc < 1 )
    {
	danceTcl::OutputMessage("Expected:  <param> value(s)...\n") ;
	return TCL_ERROR ;
    }

    if(	strcmp(argv[0],"model")	== 0 )
    {
	if( argc < 4 )
	{
	    danceTcl::OutputMessage("ERROR: Expected: set model <stiff> <damp> <friction>\n") ;
	    return TCL_ERROR ;
	}

	m_stiffness = atof(argv[1]) ;
	m_damping = atof(argv[2]) ;
	m_friction = atof(argv[3])	;
    }
    else if( strcmp(argv[0], "stiffness") == 0 )
    {
	if( argc == 1 ) 
	    danceTcl::OutputResult("%lf", m_stiffness) ;
	else
	{
	    m_stiffness = atof(argv[1]) ;
	    danceTcl::OutputMessage("New stiffness: %lf", m_stiffness) ;
	}
    }
    else if( strcmp(argv[0], "damping") == 0 )
    {
	if( argc == 1 ) 
	    danceTcl::OutputResult("%lf", m_damping) ;
	else
	{
	    m_damping = atof(argv[1]) ;
	    danceTcl::OutputMessage("New damping: %lf", m_damping) ;
	}
    }
    else if( strcmp(argv[0], "friction") == 0 )
    {
	if( argc == 1 ) 
	    danceTcl::OutputResult("%lf", m_friction) ;
	else
	{
	    m_friction = atof(argv[1]) ;
	    danceTcl::OutputMessage("New friction: %lf", m_friction) ;
	}
    }
    else if( strcmp(argv[0], "geometry") == 0 )
    {
	if( argc != 15 ) 
	{
	    danceTcl::OutputMessage("Expected four points in counterclockwise order"
				    " along with subdivision on x,z axis :\n") ;
	    danceTcl::OutputMessage("\tx1 y1 z1 x2 y2 z2 x3 y3 z3 x4 y4 z4 nx nz\n") ;
	    return TCL_ERROR ;
	}
	changeGeometry(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]),
		       atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]),
		       atof(argv[9]), atof(argv[10]), atof(argv[11]), atof(argv[12]),
		       atoi(argv[13]), atoi(argv[14])) ;
    }
 
    else
    {
	danceTcl::OutputMessage("ERROR: unrecognized parameter!\n") ;
	danceTcl::OutputMessage("USAGE: set model|geometry|object\n") ;
	return TCL_ERROR ;
    }
    return TCL_OK ;
}

// PROC: PointInBoundary()
// DOES: returns TRUE if the point projected on the ground in the direction
//       of the y axis is in the boundary of the ground. 
//       The ground is assumed to be quadrilateral or bound by a
//       quadrilateral defined by pointe (0,0) (nx-1, 0) (nx-1, ny-1), (0, ny-1) 
// CAUTION: Works only for grounds that have less then 45 degrees of slope
//       It is not the full implementation of the function.

int PlaneGround::PointInBoundary(Vector point)
{
	int i ;

    if( qm.nx < 2) return FALSE ;
     if( qm.ny < 2) return FALSE ;

    int count[3] = {0, 0, 0} ;
    // The boundary of the ground is  the four corners
    for( i = 0 ; i < 3 ; i = i+2 )
    {
	if( qm.points[0][0][i] < point[i] ) count[i]++ ;
	if( qm.points[qm.nx-1][0][i] < point[i] ) count[i]++ ;
	if( qm.points[qm.nx-1][qm.ny-1][i] < point[i] ) count[i]++ ;
	if( qm.points[0][qm.ny-1][i] < point[i] ) count[i]++ ;
    }
    
    for( i = 0 ; i < 3 ; i = i+2 )
	if( count[i] != 2 ) return FALSE ;
    
    return TRUE ;
}

/** This is a generic exertLoad that works for any system that supports monitor points */
void PlaneGround::ExertLoad(DSystem *sys, double time, double dt, double *state, double *dstate)
{

	// check to see if the system in the list for this actuator
    if( IsInApplyList(sys) == FALSE ) return ;

	DSimulator *sim = sys->simulator ;
	if(	sim == NULL)
    {
		danceTcl::OutputMessage("ExertLoad: Simulator not present\n") ;
		return ;
    }

	// if the system has no groups then invoke the force routine on the system
	// otherwise do it per group
    int ngroup = sys->GetNumGroups() ;
    if( ngroup == 0 ) 
		ResolveForce(sys, sim) ;
    else
	{
		for( ngroup = 0 ; ngroup < sys->GetNumGroups() ; ngroup++ )
		{
			DSystem *group = sys->GetGroup(ngroup) ;
			if( group == NULL )
			{
				danceTcl::OutputMessage("PlaneGround: Got a null group!!") ;
				return ;
			}
			ResolveForce(group, sim) ;
		}
	}
}


/** Compute and apply the ground forces for the given system */
void PlaneGround::ResolveForce(DSystem *sys, DSimulator *sim)
{
   
    double planeOnPoint	;
    Vector tangVel, parVel, tangForce, dampForce, n ;
    MonitorPoints *mptsStruct = sys->GetMonitorPoints() ;
    
	if( mptsStruct == NULL ) return ;
	int nMonPts = mptsStruct->m_NumPoints ;
    if( nMonPts < 1 ) return ;
    
    Vector *mpts = mptsStruct->m_Point ;
    int *isUnderGround = mptsStruct->m_InCollision ;
    Vector *prevPos =  mptsStruct->m_PrevPos;
    int i ;
    Vector gforce,vel,point ;
    
    for( i = 0 ; i < nMonPts ; i++ )
    {
	// transform the point in world coordinates
	sim->GetPosition(sys,mpts[i],point) ;
	//printf("Monitor point (wcs) %d point %lf %lf %lf\n",
	// i, point[0],point[1],point[2]) ;
	planeOnPoint = plane.applyOn(point)	;
	// PointInBoundary works only for  grounds of no more
	// than 45 degrees of slope.
	if( (planeOnPoint < 0.0) && (PointInBoundary(point) == TRUE) ) //	 point underground
	{
	    
	    // form	the normal of the ground plane
	    n[0] = plane.A ;
	    n[1] = plane.B ;
	    n[2] = plane.C ;
	    
	    if( isUnderGround[i] == FALSE )
	    {
		// point under ground for first time
		// note that the point is underground
		isUnderGround[i] = TRUE ;
		
		// save its entry position
		prevPos[i][0] = point[0] - n[0]*planeOnPoint ;
		prevPos[i][1] = point[1] - n[1]*planeOnPoint ;
		prevPos[i][2] = point[2] - n[2]*planeOnPoint ;
		mptsStruct->m_PrevPosTimeStamp[i] = sim->GetTime() ;
	    }
	    
	    
	    // break the velocity into tangential and parallel parts
	    sim->GetVel(sys,mpts[i],vel) ;
	    //   printf("Vel:") ; printVector(vel) ;
	    VecNumMul(parVel, n,VecDotProd(n,vel)) ;
	    VecSubtract(tangVel, vel,parVel) ;
	    
	    
	    // calculate interpreteretration with respect to entry positions, which is
	    // point - prevPosition
	    Vector dx ;
	    
	    VecSubtract(dx, prevPos[i], point) ;
	    // break it into to components
	    Vector dxNormal, dxTang, dxTangUnit ;
	    double dxn = VecDotProd(dx,n) ;
	    VecNumMul( dxNormal, n, dxn) ;
	    VecSubtract(dxTang, dx, dxNormal) ;
	    VecCopy(dxTangUnit, dxTang) ;
	    VecNormalize(dxTangUnit) ;
	    
	    double normalForceMag = dxn*m_stiffness ;
	    VecNumMul(gforce,n, normalForceMag) ;
	    
	    // calculate the friction force using a friction cone model
	    
	    double dxtang = VecDotProd(dx, dxTangUnit) ;
	    double tangForceMag = dxtang*m_stiffness ;
	    double tangForceMaxMag = normalForceMag*m_friction ;
	    
	    if( fabs(tangForceMag) >= fabs(tangForceMaxMag) )
	    {
		VecNumMul(tangForce, dxTangUnit, tangForceMaxMag ) ;
		// move the point of entry to the one that satisfies the above limit
		// and record the current prevpos as the pprevpos
		mptsStruct->m_PrevPosTimeStamp[i] = sim->GetTime() ;
		Vector trans ;
		VecNumMul(trans, dxTangUnit, dxtang - 
			  m_friction * dxn) ;
		VecSubtract(prevPos[i], prevPos[i], trans) ;
	    }
	    else
	    {
		VecNumMul(tangForce, dxTangUnit, tangForceMag) ;
		//	danceTcl::OutputMessage("tangForceMag = %lf", tangForceMag) ;
		//  		    danceTcl::OutputMessage("tangForceNormal = %lf %lf %lf", tangNormal[0],
		//  					    tangNormal[1], tangNormal[2]) ;
		//  		    danceTcl::OutputMessage("stiffness = %lf", m_stiffness) ;
	    }
	    
	    //danceTcl::OutputMessage("tangForceMag = %lf", tangForceMag) ;
	    
	    VecNumMul(dampForce,parVel,-m_damping) ;
	    //printf("parvel ") ; printVector(parVel) ;
	    //printf("dampForce ") ; printVector(dampForce)	;
	    VecAdd(gforce,gforce,dampForce)	;

	    // correct sticky effect
	    if( VecDotProd(gforce,n) < (double) 0.0) 
	    {
		gforce[0] = gforce[1] = gforce[2] = 0.0 ;
	    }
	    
	    //		danceTcl::OutputMessage("tang force : %lf %lf %lf", 
	    //			tangForce[0], tangForce[1], tangForce[2]) ;
	    // add friction
	    VecAdd(gforce,gforce,tangForce)	;
	    
	    //printf("Inter	= %lf Force: \n", planeOnPoint)	; printVector(gforce) ;

	    
	    const int argc = 4 ;
	    char *argv[argc] ;
	    argv[0] = (char *) sys ;
	    argv[1] = (char *) &i ;
	    argv[2] = (char *) mpts[i] ;
	    argv[3] = (char *) &gforce[0] ;
	    //sim->PointForce(sys,mpts[i],force)	;
	    sim->PointForce(argc, argv) ;
	    
	} // end if point under ground
	else
	{
	    isUnderGround[i] = FALSE ;
	    mptsStruct->m_PrevPosTimeStamp[i] = MINFLOAT ;
	}
    } // end monitor point loop
}








