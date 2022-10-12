#include <math.h>
#include <GL/glutShared.h>
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "FieldActuator.h"
#include "DSystem.h"
#include "DSimulator.h"
#ifndef	NO_GL
#include <GL/gl.h>
#endif

#ifndef EPS
#define EPS 0.00000001
#endif

PlugIn *Proxy(void) { return (new FieldActuator); } ;

static void outputMessage(Tcl_Interp *interp, char *s)
{
    Tcl_AppendResult(interp, s,	(char *) NULL) ;
}


void displayVector(double point[3], double direction[3], double magnitude)
{
    double vector[3] ;
    for	(int i = 0; i <	3; i++)
	    vector[i] =	direction[i]*magnitude;

    // if a zero vector is given do not draw to avoid segmentation fault
    if( (fabs(vector[0]) < EPS) && (fabs(vector[1]) < EPS) && (fabs(vector[2]) < EPS))
	return ;

    glPushMatrix();
	      glTranslated(point[0],point[1],point[2]);
	      // Draw vector line.
	      glBegin(GL_LINES);
	      glVertex3d(0.0,0.0,0.0);
	      glVertex3dv(vector);
	      glEnd();

	      // Rotate	Z-axis of original cone	to line	up with	arrow
	      // compute dot product and angle between vectors.
	      double length = sqrt(vector[0]*vector[0] +
			vector[1]*vector[1] + vector[2]*vector[2]);
	      double angle = acos(vector[2]/length)*180.0/M_PI;

	      glTranslated(vector[0],vector[1],vector[2]);

	      // Calculate cross product of Z-axis and joint axis to
	      // produce axis of rotation.
	      glRotated(angle,-1.0*vector[1],vector[0],0.0);

	      // Draw arrow-head, translate apex of cone to origin.
	      glTranslated(0.0,0.0,-0.3*length);
	      glutWireCone(0.1*length,0.3*length, 3, 3);
    glPopMatrix();
}

FieldActuator::FieldActuator() {
	position[0] = position[1] = position[2]	= 0.0;
	direction[0] = direction[1] = direction[2] = 0.0;
	magnitude = 1.0;
	direction[1] = 1.0 ;
	arcball	= new BallData;
	Ball_Init(arcball);
	Quat qOne = {0, 0, 0, 1};
	Ball_Place(arcball,qOne, 0.25);
	setType("field");
}

FieldActuator::~FieldActuator()
{
	if (arcball) delete arcball;
}


void FieldActuator::output(int mode)
{
	if (mode) {
	    int	prevL =	glIsEnabled(GL_LIGHTING) ;
	    if(	prevL == TRUE )
		glDisable(GL_LIGHTING) ;
	    glColor4f(1.0,1.0,0.0,1.0);
	    displayVector(position,direction,magnitude*0.025);
	    if(prevL ==	TRUE) glEnable(GL_LIGHTING) ;
	}

}

void FieldActuator::Interact(Event *event)
{
    int	x,  y ;
    int	width, height, diffx, diffy ;

    diffx = event->winDiffX ;
    diffy = event->winDiffY ;
    width = event->winWidth ;
    height = event->winHeight ;
    x =	event->winX ;
    y =	event->winY ;


    if (interactionMode	== pDirection) {
	    HVect coords;
	    coords.x = 2.0*(float)x/(float)width-1.0;
	    coords.y = -2.0*(float)y/(float)height+1.0;

	    Ball_Mouse(arcball,coords);
	    Ball_Update(arcball);

	    HMatrix arcball_rot;
	    Ball_Value(arcball,arcball_rot);

	    // Transform startVector to	world coordinates
	    int	i;
	    double viewStart[3]={0.0,0.0,0.0};
	    for	(i = 0;	i < 3; i++) {
		viewStart[0] +=	event->winBasisX[i]*startVector[i];
		viewStart[1] +=	event->winBasisY[i]*startVector[i];
		viewStart[2] +=	event->winBasisZ[i]*startVector[i];
	    }

	    double viewDirection[3];
	    for	(i = 0;	i < 3; i++) {
		viewDirection[i] = arcball_rot[0][i] * viewStart[0]
			   + arcball_rot[1][i] * viewStart[1]
			   + arcball_rot[2][i] * viewStart[2];
	    }

	    // Back to original	world space.
	    for	(i = 0;	i < 3; i++) {
		direction[i] = event->winBasisX[i]*viewDirection[0]
			     + event->winBasisY[i]*viewDirection[1]
			     + event->winBasisZ[i]*viewDirection[2];
	    }
	}
	else if	(interactionMode == pPosition) {
	    for	(int i = 0 ; i < 3; i++)
		position[i] += event->winBasisX[i]*0.01*(double)diffx -
		  event->winBasisY[i]*0.01*(double)diffy;
	}
	else if	(interactionMode == pMagnitude)	{
	    if (diffx +	diffy >	0)
		magnitude *= 1.10;
	    else
		magnitude *= 0.90;
	}
}

int FieldActuator::InteractEnd(void)
{
	if (interactionMode == pDirection)
	    Ball_EndDrag(arcball);
	return 0 ;
}

int FieldActuator::InteractStart(Event	*event)
{
    switch(event->buttonID) {
	    case GLUT_LEFT_BUTTON:
		{
		interactionMode	= pDirection;
		memcpy(startVector,direction,3*sizeof(double));
		HVect coords;
		coords.x = 2.0*(float)event->winX/(float)event->winWidth-1.0;
		coords.y = -2.0*(float)event->winY/(float)event->winHeight+1.0;
		Ball_Mouse(arcball,coords);
		Ball_BeginDragReset(arcball);
		}
		break;
	    case GLUT_MIDDLE_BUTTON:
		interactionMode	= pPosition;
		break;
	    case GLUT_RIGHT_BUTTON:
		interactionMode	= pMagnitude;
		break;
	}
    return 1 ;
}

void FieldActuator::print(void)
{
	fprintf(stderr,"Field Position:	(%lf,%lf,%lf)\n",
		position[0],position[1],position[2]);

	fprintf(stderr,"Field Direction: (%lf,%lf,%lf)\n",
		direction[0],direction[1],direction[2]);
}

void FieldActuator::saveScript(char *name)
{
    char line[50] ;
    FILE *fp ;

    if ( (fp = fopen(name,"w"))	== NULL	)
    {
       sprintf(line,"ERROR: cannot open	%s\n", name) ;
       printf("%s", line) ;
       outputMessage(interpreter,line) ;
    }
    else
	saveScript(fp) ;
}

void FieldActuator::saveScript(FILE *fp)
{

    fprintf(fp,"actuator %s direction %lf %lf %lf\n", getName(),
	    direction[0], direction[1],	direction[2]) ;
    fprintf(fp,"actuator %s position %lf %lf %lf\n", getName(),
	    position[0], position[1], position[2]) ;
    fprintf(fp,"actuator %s magnitude %lf\n", getName(),
	    magnitude) ;
}

void FieldActuator::ExertLoad(DSystem *ao, double time, double dt,
double *state, double *dstate)
{

	DSimulator *sim = ao->simulator;
	if (sim	== NULL) {
		fprintf(stderr,"ExertLoad: Simulator not present.\n");
		return;
	}

	AppliedObject *wao = applyList;
	while (wao) {
		if (wao->ao == ao) break;
		wao = wao->next;
	}

	int apply = 0;
	if (wao) {
	   AppliedUnit *unitTest = wao->unitList;
	   if (unitTest==NULL) apply = 1;
	}

	//	printf("Applyall : %d apply %d\n", applyAllObjects, apply);


	if (applyAllObjects || apply) 
	{
	    // for (int i = 0; i	< ao->GetNumGroups(); i++)
	    //{
	    double force[3];
	    force[0] = magnitude*direction[0] ;
	    force[1] = magnitude*direction[1] ;
	    force[2] = magnitude*direction[2] ;
	    sim->FieldForce(force) ;
		// double point[3] = {0.0,0.0,0.0};
		//  sim->GetOrientation(-1,direction,i,force);
//  		double fmag = ao->GetGroupMass(i)*magnitude ;
//  		force[0] *= fmag ;
//  		force[1] *= fmag ;
//  		force[2] *= fmag ;
//  		sim->PointForce(i,point,force);
		//}
	    
	    return;
	}

	//  if (wao) { // On a per-group basis.
//  		Link **links = ao->getLinks();
//  		AppliedUnit *wunit = wao->unitList;
//  		while (wunit) {
//  		     int linkNo	= wunit->linkNo;
//  		     if	(linkNo	>= 0) {
//  			double point[3]	= {0.0,0.0,0.0};
//  			double force[3];
//  			sim->GetOrientation(-1,direction,linkNo,force);
//  			force[0] *= links[linkNo]->getMass()*magnitude;
//  			force[1] *= links[linkNo]->getMass()*magnitude;
//  			force[2] *= links[linkNo]->getMass()*magnitude;
//  			sim->PointForce(linkNo,point,force);
//  		     }
//  		     wunit = wunit->next ;
//  		}
//  	}

}

PlugIn *FieldActuator::create(Tcl_Interp *interp, int argc, char **argv)
{
    FieldActuator *f = new FieldActuator ;

    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}

int FieldActuator::commandPlugIn(ClientData clientData, Tcl_Interp *interp, 
				 int argc, char **argv)
{

    if(	argc < 2 )
    {
	danceTcl::OutputMessage("Expected:  set <param> value(s)...\n") ;
	return TCL_ERROR ;
    }

	if (strcmp(argv[0],"type") == 0) {
		Tcl_AppendResult(interp,getType(),NULL);
		return TCL_OK;
	}

    if(	strcmp(argv[0],	"set") == 0 )
		return set(interp, argc-1, &argv[1]) ;
    else
    {
		danceTcl::OutputMessage("Expected:  set <param> value(s)...\n") ;
		return TCL_ERROR ;
    }
}


// sets	the various parameters of the field actuator
// expects argv[0] = <param_name>
//	   argv[1] = <value 0> ...
int FieldActuator::set(Tcl_Interp *interp, int argc, char **argv)
{
    if(	argc < 1 )
    {
	danceTcl::OutputMessage( "Expected:  <param> value(s)...\n") ;
	return TCL_ERROR ;
    }

    if(	strcmp(argv[0],	"magnitude") ==	0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage( "Expected:  magnitude	<value>	...\n")	;
	    return TCL_ERROR ;
	}

	magnitude = atof(argv[1] ) ;

    }
    else if ( strcmp(argv[0], "direction") == 0	)
    {
	if( argc != 4 )
	{
	    danceTcl::OutputMessage( "Expected:  direction	<x> <y>	<z> ...\n") ;
	    return TCL_ERROR ;
	}
	direction[0] = atof(argv[1]) ;
	direction[1] = atof(argv[2]) ;
	direction[2] = atof(argv[3]) ;

	// normalize it
	double m = sqrt(direction[0]*direction[0] + direction[1]*direction[1]
		     + direction[2]*direction[2]) ;

	if( m >	0.000001 )
	{
	    direction[0] /= m ;
	    direction[1] /= m ;
	    direction[2] /= m ;
	}

    }
    else if( strcmp(argv[0], "field") == 0 )
    {
	if( argc != 4 )
	{
	    danceTcl::OutputMessage( "Expected:  field <x>	<y> <z>	...\n")	;
	    return TCL_ERROR ;
	}
	direction[0] = atof(argv[1]) ;
	direction[1] = atof(argv[2]) ;
	direction[2] = atof(argv[3]) ;

	// normalize it
	magnitude = sqrt(direction[0]*direction[0] + direction[1]*direction[1]
		     + direction[2]*direction[2]) ;

	if( magnitude >	0.000001 )
	{
	    direction[0] /= magnitude ;
	    direction[1] /= magnitude ;
	    direction[2] /= magnitude ;
	}

    }
    else if( strcmp(argv[0], "object") == 0 )
    {
	if ( argc != 2 )
	{
	    danceTcl::OutputMessage( "Expected: object <name>|all\n") ;
	    return TCL_ERROR ;
	}
	if( strcmp(argv[1], "all") == 0	)
	    setAppliedAllObjects() ;
	else
	{
		DanceObjectList	*allObjects = dance::getList("object");
	    DanceObject	*obj = allObjects->get(argv[1])	;
	    if(	obj == NULL )
	    {
		danceTcl::OutputMessage( "No such object!\n") ;
		return TCL_ERROR ;
	    }
	}
    }
    else
    {
	danceTcl::OutputMessage( "ERROR: unrecognized parameter!\n") ;
	danceTcl::OutputMessage( "USAGE: set magnitude|direction|field|object\n") ;
	return TCL_ERROR ;
    }
    return TCL_OK ;
}


