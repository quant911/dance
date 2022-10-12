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

#include <assert.h>

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "defs.h"
#include "GLutilities.h"
#include "DanceObject.h"
#include "Joint.h"
#include "Link.h"
#include "dance.h"
#include "danceTcl.h"
#include "ViewManager.h"
#include "DView.h"
#include "ArticulatedObject.h"

// Default constructor and initializer for class Joint
Joint::Joint()
{
   
    setType("Joint");
    m_jointNumber = -1 ;
    m_jointType = J_BALL ;

    m_numAxis = 0;
    m_AuxFrame.set(0.0,0.0,0.0,1.0);

    inboardLink	= NULL ;
    outboardLink = NULL	;
    m_Frame.set(0.0,0.0,0.0,1.0) ;
    setVector(m_InbToJoint,0.0,0.0,0.0) ;
    setVector(m_BodyToJoint,0.0,0.0,0.0) ;

    for( int i = 0 ; i < 7 ; i++ )
    {
	m_OldState[i] = 0.0;
	m_State[i] = 0.0 ;

	stiffness[i] = 100.0 ;
	damping[i] = 1.0 ;
	maxDamping[i] = 100.0 ;
	maxStiffness[i] = 10.0 ;

	for( int j = 0 ; j < 3 ; j++) {
		if (i == j) 
			m_axis[i][j] = 1.0;
		else
			m_axis[i][j] = 0.0 ;
	}
    }

}

// Removes Joint and connections to links.
// Does not remove link, link must delete itself explicitly.
Joint::~Joint()
{

	// Unlink inboard link.
	if (inboardLink)
		inboardLink->RemoveChildJoint(this);

	// Unlink outboard link.
	if (outboardLink)
		outboardLink->parentJoint = NULL;

	

}

// create joint	number num of type t, between parent link p
// and link l
void Joint::create(int num, int t, Link *p, Link *l)
{

    //    sprintf(getName(),"joint%d",num);
    strcpy(getName(), l->getName()) ;
    m_jointNumber	= num ;
    m_jointType =	t ;
    inboardLink	= p ;
    outboardLink = l ;

    switch(t)
    {
	case J_PIN:
	    m_numAxis = 1 ;
	    setVector(m_axis[0],0.0,0.0,1.0) ;
	    setState(0, 0.0) ;
	    m_Limits[0][0] = -180.0; m_Limits[0][1] = 180.0;
	    break ;
	case J_PLANAR:
	    m_numAxis = 3 ;
	    setVector(m_axis[0],0.0,1.0,0.0) ;
	    setVector(m_axis[1],0.0,0.0,1.0) ;
	    setVector(m_axis[2],1.0,0.0,0.0) ;
	    setState(0, 0.0) ;
	    setState(1, 0.0) ;
	    setState(2, 0.0) ;
	    m_Limits[2][0] = -MINFLOAT; m_Limits[2][1] = MAXFLOAT;
	    break ;

    case J_UNIVERSAL:
		m_numAxis = 2 ;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setState(0, 0.0) ;
		setState(1, 0.0) ;
		m_Limits[0][0] = -180.0; m_Limits[0][1] = 180.0;
		m_Limits[1][0] = -180.0; m_Limits[1][1] = 180.0;
	break ;
    case J_GIMBAL:
    case J_FREE:
	{
		m_numAxis = 3 ;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setVector(m_axis[2],0.0,0.0,1.0) ;
		if (t == J_FREE) {
			m_Limits[0][0] = -10.0; m_Limits[0][1] = 10.0;
			m_Limits[1][0] = -10.0; m_Limits[1][1] = 10.0;
			m_Limits[2][0] = -10.0; m_Limits[2][1] = 10.0;
		}
		else {
			m_Limits[0][0] = -180.0; m_Limits[0][1] = 180.0;
			m_Limits[1][0] = -180.0; m_Limits[1][1] = 180.0;
			m_Limits[2][0] = -180.0; m_Limits[2][1] = 180.0;
		}

		double mat[4][4], cmat[4][4], pmat[4][4];
		if (inboardLink)
			inboardLink->getOrientation(pmat);
		else {
			for	(int i=0; i < 4; i++)
			for (int j=0; j	< 4; j++) {
				if (i==j) pmat[i][j] = 1.0;
				else pmat[i][j]	= 0.0;
			}
		}
		outboardLink->getOrientation(cmat);
		relativeToFrame(mat,cmat,pmat);
		m_Frame.fromMatrix(mat);
		CalcState();
		m_Limits[3][0] = 0.0; m_Limits[3][1] = 360.0;
		m_Limits[4][0] = 0.0; m_Limits[4][1] = 180.0;
		m_Limits[5][0] = 0.0; m_Limits[5][1] = 360.0;
	}
	break ;
    case J_BALL:
	{
		m_numAxis	= 0;
		// Determine frame of link l relative to link p
		// Convert to quaternion
		double mat[4][4], cmat[4][4], pmat[4][4];
		if (inboardLink)
			inboardLink->getOrientation(pmat);
		else {
			for	(int i=0; i < 4; i++)
			for (int j=0; j	< 4; j++) {
				if (i==j) pmat[i][j] = 1.0;
				else pmat[i][j]	= 0.0;
			}
		}
		l->getOrientation(cmat);
		relativeToFrame(mat,cmat,pmat);
		m_Frame.fromMatrix(mat);
		m_AuxFrame.set(0.0,0.0,0.0,1.0);
		CalcState();
		m_Limits[0][0] = 0.0; m_Limits[0][1] = 360.0;
		m_Limits[1][0] = 0.0; m_Limits[1][1] = 180.0;
		m_Limits[2][0] = 0.0; m_Limits[2][1] = 360.0;
	}
	break ;
    case J_SLIDER:
		m_numAxis	= 1;
		setState(0,0.0);
		setVector(m_axis[0],1.0,0.0,0.0) ;
		m_Limits[0][0] = -10.0; m_Limits[0][1] = 10.0;
	break;
    case J_WELD:
	 m_numAxis = 0 ;
	 break ;
    default:
		danceTcl::OutputMessage("Joint type %d\n", t) ;
		danceTcl::OutputMessage("ERROR:Joint::create: "
					"Not implemented yet.") ;
		break;
    }
}

// applyTransformation:
// Given the quaternion	or the angles that define
// the relative	orientation of the outboard link
// with	respect	to the inboard link
// calculate the matrix	that transforms	from child to parent
// assuming that the two coordinate systems are	currently
// aligned.
// The transformation matrix is:
// M = [ R 0 ]
//     [ T 1]
// where R is the rotation matrix defined by the m_Frame or the angles
// and T= Tinb -R*Toutb
void Joint::applyTransformation(void)
{
    int i,j ;
    double m[4][4], orient[4][4];

    getOutboardLink()->getOrientation(m) ;

    // apply the orientation corresponding to the joint.
    switch(m_jointType) {
	case J_PLANAR:
	case J_PIN:
	case J_UNIVERSAL:
	case J_SLIDER:
	case J_FREE:
	case J_BALL:
	case J_GIMBAL:
	    m_Frame.toMatrix(orient)	;
	    for (i=0;	i < 3; i++)
		for (j=0; j	< 3; j++)
		    m[i][j] = orient[i][j];
	    break;
	case J_WELD:
	    for (i=0; i < 3; i++)
		for (j=0; j	< 3; j++)
		    m[i][j] = 0 ;
	    m[0][0] = m[1][1] = m[2][2] = 1.0 ;
	    break ;
    }

    // now construct the translation part of the transformation	matrix
    Vector trans ;
    VecCopy(trans,m_BodyToJoint) ;
    rotPoint_mat4(trans,m) ;

    // Add in effects of slider	joints.
    if (m_jointType == J_FREE || m_jointType == J_SLIDER) {
	      double wtrans[3]={0.0,0.0,0.0};
		  for (int i=0; i <	m_numAxis; i++) {
			wtrans[0] += m_axis[i][0]*m_State[i];
			wtrans[1] += m_axis[i][1]*m_State[i];
			wtrans[2] += m_axis[i][2]*m_State[i];
		  }
		  VecSubtract(trans,trans,wtrans);
    }
	else if( m_jointType == J_PLANAR)
	{
		// first two axis are translational
		double wtrans[3] ;
		wtrans[0] = m_axis[0][0]*m_State[0] + m_axis[1][0]*m_State[1] ;
		wtrans[1] = m_axis[0][1]*m_State[0] + m_axis[1][1]*m_State[1] ;
		wtrans[2] = m_axis[0][2]*m_State[0] + m_axis[1][2]*m_State[1] ;
		VecSubtract(trans,trans,wtrans);
	}

    VecSubtract(m[3],m_InbToJoint,trans) ;
   
    getOutboardLink()->setTransMat(m) ;
    // caution:	it is set in local coordinates

}


// getStateSize:
//	returns	the number of items in the state vector
//
//	returns: size of state vector
int Joint::getStateSize()
{
	int num	= 0;
	switch(m_jointType)
	{
	    case J_PIN:
	    case J_SLIDER:
		num = 1;
		break;
	    case J_UNIVERSAL:
		num = 2	;
		break ;
	    case J_BALL:
		num = 4;
		break;
	    case J_GIMBAL:
		num = 3;
		break;
	    case J_FREE:
		num = 7;
		break;
	    case J_WELD:
		num = 0 ;
		break ;
	    case J_PLANAR:
		num = 3 ;
		break ;
	    default:
		num = 0;
	}
	return(num);
}

// getNumDof:
//	returns	the number of dofs
//
int Joint::getNumDof()
{
	int num	= 0;
	switch(m_jointType)
	{
	    case J_PIN:
	    case J_SLIDER:
		num = 1;
		break;
	    case J_UNIVERSAL:
		num = 2	;
		break ;
	    case J_BALL:
	    case J_GIMBAL:
		num = 3;
		break;
	    case J_FREE:
		num = 6;
		break;
	    case J_WELD:
		num = 0 ;
		break ;
	    case J_PLANAR:
		num = 3 ;
		break ;
	    default:
		num = 0;
	}
	return(num);
}

// setLastState:
//	copies the contents of m_State to m_OldState
void Joint::setLastState(void)
{
	memcpy(m_OldState,m_State,sizeof(double)*getStateSize());
	memcpy(m_OldInbToJoint,m_InbToJoint,3*sizeof(double));
	memcpy(m_OldBodyToJoint,m_BodyToJoint,3*sizeof(double));
}

// revertToLast:
//	Reverts to the last stored state.
void Joint::revertToLast(void)
{
	memcpy(m_InbToJoint,m_OldInbToJoint,3*sizeof(double));
	memcpy(m_BodyToJoint,m_OldBodyToJoint,3*sizeof(double));

	for (int i = 0; i < getStateSize(); i++) 
		setState(i,m_OldState[i]);

	// Make adjustments for joints involving quaternions
	switch(m_jointType) {
		case J_FREE:
			m_Frame.fromVector(&(m_State[3]));
			break;
		case J_BALL:
			m_Frame.fromVector(&(m_State[0]));
			break;
	}
	
}

// getState:
//	returns	the state of a joint with the given index
//
//	index  : index of state	to get
//	returns: state value
double Joint::getState(int index)
{
	double value = 0.0;
	switch(m_jointType) {
	    case J_GIMBAL:
	    case J_FREE:
		 if (index < 3)
			value =	m_State[index];
		 else
			value =	m_Frame.get(index-3);
		 break;
	    case J_BALL:
		 value = m_Frame.get(index);
		 break;
	    default:
		 value = m_State[index];
	}
	return(value);
}

// setState:
//	sets the state of a joint with the given index
//
//	index: index within the	state vector
//	state: new value to be put in this index position of the state vector
//
void Joint::setState(int index,	double state, int batch)
{
    switch (m_jointType) {
	case J_BALL:
	    m_Frame.set(index, state);
	    m_State[index] = state;
	    break;
	case J_FREE:
	    
	    if (index	>= 3) {
		m_Frame.set(index-3,state);
	    }
	    m_State[index] = state;
	    break;
	case J_PIN:
	    m_State[index] = state ;
	    m_Frame.set(state, m_axis[0]) ;
	    break;
	case J_PLANAR:
	    m_State[index] = state ;
	    if( index == 2 )	// rotational parameter
		m_Frame.set(state, m_axis[2]) ; // <------------- check it out
		break ;
	case J_GIMBAL:
	case J_UNIVERSAL: {
	    m_State[index] = state ;
	    
	    Quaternion q ;
	    if( batch	== FALSE )	// we want immediate update
	    {
		m_Frame.set(m_State[0], m_axis[0]) ;
		// multiply the three	rotations together
		// using quaternion multiplication
		for( int i = 1 ; i < getNumAxis() ; i++ )
		{
		    q.set(m_State[i], m_axis[i]) ;
		    m_Frame.multiply(&q)	;
		}
	    }
	    else // Optimized so we don't need to produce unnecessary multiplications.
	    {
		q.set(state, m_axis[index]) ;
		if( index == 0 ) m_Frame.copy(&q) ;
		else m_Frame.multiply(&q) ;
	    }
	    
	}
	break;
	default:
	    m_State[index] = state ;
    }
}

void Joint::setParam(int ax, double stif, double damp)
{
    if(	(ax >= 0) && (ax < getStateSize()))
    {
	stiffness[ax] =	stif ;
	damping[ax] = damp ;
    }
    else
    {
	danceTcl::OutputMessage("ERROR:Joint::setParam:Index out of bounds.")	;
    }
}


void Joint::print(FILE *fptr)
{
	fprintf(fptr,"\n     # Joint %s\n",getName());
	
	Link *wlink = getOutboardLink();
    ArticulatedObject *ao = wlink->getAo();

    int	ndof = getNumDof();
	for (int i = 0; i < ndof; i++) {
		fprintf(fptr,"     system %s joint %s dof %d limits %f %f\n",
			ao->getName(), getName(), i, m_Limits[i][0],m_Limits[i][1]);
	}

    return ;
}

// changeType:
//	Changes	the type of the	joint and resets its state, giving
//	default	parameters.
//
//	type: new joint	type
//
void Joint::changeType(int newtype)
{
	if (newtype == m_jointType) return; // No	need to	adjust type.
	m_jointType = newtype;

	switch(m_jointType)	{
	   case	J_SLIDER:
		m_numAxis	= 1;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setState(0,0.0);
		{
		double wangle =	0.0;
		double waxis[3]	= {0.0,0.0,1.0};
		m_Frame.set(wangle,waxis);
		}
		break;
	   case	J_FREE:
		m_numAxis	= 3;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setVector(m_axis[2],0.0,0.0,1.0) ;
		setState(0,0.0);
		setState(1,0.0);
		setState(2,0.0);
		{
		double wangle =	0.0;
		double waxis[3]	= {0.0,0.0,1.0};
		m_Frame.set(wangle,waxis);
		}
		break;
	   case	J_BALL:
		{
		m_numAxis	= 0;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setVector(m_axis[2],0.0,0.0,1.0) ;
		setState(0,0.0);
		setState(1,0.0);
		setState(2,0.0);
		setState(3,1.0);
		double wangle =	0.0;
		double waxis[3]	= {0.0,0.0,1.0};
		m_Frame.set(wangle,waxis);
		}
		break;
	   case	J_GIMBAL:
		{
		m_numAxis	= 3;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setVector(m_axis[2],0.0,0.0,1.0) ;
		setState(0,0.0);
		setState(1,0.0);
		setState(2,0.0);
		double wangle =	0.0;
		double waxis[3]	= {0.0,0.0,1.0};
		m_Frame.set(wangle,waxis);
		}
		break;
	   case	J_UNIVERSAL:
		{
		m_numAxis	= 2;
		setVector(m_axis[0],1.0,0.0,0.0) ;
		setVector(m_axis[1],0.0,1.0,0.0) ;
		setState(0,0.0);
		setState(1,0.0);
		double wangle =	0.0;
		double waxis[3]	= {0.0,1.0,0.0};
		m_Frame.set(wangle,waxis);
		}
		break;
	    case J_PLANAR:
		m_numAxis = 3 ;
		setVector(m_axis[0],0.0,1.0,0.0) ;
		setVector(m_axis[1],0.0,0.0,1.0) ;
		setVector(m_axis[1],1.0,0.0,0.0) ;
		setState(0,0.0);
		setState(1,0.0);
		setState(2,0.0) ;
		m_Frame.set(m_State[2],m_axis[2]);
	   case	J_PIN:
		{
			m_numAxis	= 1;
			setState(0,0.0);
			setVector(m_axis[0],0.0,0.0,1.0);
			m_Frame.set(m_State[0],m_axis[0]);
		}
		break;
	   default:
		danceTcl::OutputMessage("Change type to %d: not "
					"implemented yet.",newtype);
	}
}

//*******************************************
// PROC: Joint::getAxis()
// DOES: returns the axis associated with
//	 a Joint and their number
//*******************************************
int  Joint::getAxis(double a[3][3])
{
    int	i,j ;

    for( i = 0 ; i < 3 ; i++ )
	for( j = 0 ; j < 3 ; j++ )
	    a[i][j] = m_axis[i][j] ;
    return m_numAxis ;
}

// gets	the initial orientation	of the link given the information
// in angle and	 m_Frame fields
int Joint::getOrientation(double m[4][4])
{
    m_Frame.toMatrix(m) ;
    return OK ;
}





/**
 * Calculates the position of the joint in world coordinates
 *
 * Calculates the position of the joint in world coordinates
 * using the getWTransMat. So it works properly inpendendly of 
 * hierarchical or absolute structure.
 * @param double p[3] the position of the joint
 * @return void 
 */
void Joint::getPosition(double p[3])
{

	Vector outb ;
    getBodyToJoint(outb) ;
    double tm[4][4] ;
    outboardLink->getWTransMat(tm) ;
    transformPoint_mat(outb,tm);
    VecCopy(p,outb) ;
}

// displayArcBall:
//	Displays joint's arcball
//
void Joint::displayRefFrame(double length, double frame[4][4])
{
	const double x_axis[3] = {1.0,0.0,0.0};
	const double y_axis[3] = {0.0,1.0,0.0};
	const double z_axis[3] = {0.0,0.0,1.0};
	
	glPushMatrix();
	glMultMatrixd((double *)frame);

	// display quaternion axis.
	/*
	glPushAttrib(GL_CURRENT_BIT);
	const GLfloat axisColor[4] = {0.7f,0.0f,0.7f,1.0f};
	glColor4fv(axisColor); // violet color
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,axisColor) ;

	double rotaxis[3], angle;	
	m_Frame.getAxisAngle(rotaxis,&angle);
	
	// Labels
	char msgString[256];sprintf(msgString,"%f",angle);
	glRasterPos3d(0.0,0.0,0.0);
	GLlabel(msgString);
	
	displayAxis((double *)rotaxis,length);

	// Labels
	glRasterPos3d(rotaxis[0],rotaxis[1],rotaxis[2]);
	sprintf(msgString,"(%f,%f,%f)\n",rotaxis[0],rotaxis[1],rotaxis[2]);
	GLlabel(msgString);
	glPopAttrib();
    */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glLineWidth(2.0);

	// X-axis
	glPushName(3);
	glColor3f(0.7f,0.0f,0.0f);
	glPushMatrix();
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	GLdrawCircle(length,12); 
	glPopMatrix();
	glPopName();

	// Y-axis
	glPushName(4);
	glColor3f(0.0,0.9f,0.0f);
	glPushMatrix();
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	GLdrawCircle(length,12); 
	glPopMatrix();
	glPopName();

	// Z-axis
	glPushName(5);
	glColor3f(0.0f,0.0f,0.9f);
	GLdrawCircle(length,12); 
	glPopName();

	glLineWidth(1.0);

	glPopAttrib();

	glPopMatrix();


}

// displayAxis:
//	Displays joint axis.
//
//	axis:	Vector direction (length 1 is expected)
//	length:	Scaling	factor
//	type:	1 for translational, 0 for rotational
//
void Joint::displayAxis(double axis[3],	double length, int arrowtype)
{
    double point[3]; point[0] =	0.0; point[1] =	0.0; point[2] =	0.0;
    GLdrawVector(point,	axis, length);


    if (arrowtype) {
       for (int i =	0; i < 3; i++)
		axis[i]	*= -1.0;
       GLdrawVector(point,axis,length);
    }
}


// displayManipulators:
//	Displays the joint manipulators	based on type.
//
void Joint::displayManipulators(void)
{
    // Get frames of reference for each	link.
    double inb_tm[4][4], outb_tm[4][4];
    double inb[3];
    getInbToJoint(inb);
    if (inboardLink) {
		inboardLink->getWTransMat(inb_tm);
		transformPoint_mat(inb,inb_tm);
    }
    else // This is a root inboard
    {
	for (int i = 0;	i < 4; i ++)
	   for (int j =	0; j < 4; j++)
	     if	(i == j)
			inb_tm[i][j] = 1.0;
	     else
			inb_tm[i][j] = 0.0;
		 getInbToJoint(inb);
    }

    // Translate to inboard and outboard position
    memcpy(inb_tm[3],inb,3*sizeof(double));

    double outb[3]; getBodyToJoint(outb);
    outboardLink->getWTransMat(outb_tm);
    transformPoint_mat(outb,outb_tm);
    memcpy(outb_tm[3],outb,3*sizeof(double));

	// Calculate suitable arrow	lengths	for inboard and	outboard vectors.
	// Scale these arrows as a percentage of the View Volume dimensions.
	double arrowLength = 1.0;
	DView *wview = dance::AllViews->getViewFocus();
	if (wview) {
		double pos[3]; getPosition(pos);		
		double win[3]; wview->getWindowCoords(pos,win);
		double worldwidth = wview->getFrustumWidth(win[2]);
		arrowLength = 0.05*worldwidth;
	}

    double axis[3][3];
	double frameMat[4][4];
    int	numAxes	= getAxis(axis);

	const GLfloat sliderColor[] = {0.0f,0.0f,0.9f,1.0f};
	const GLfloat revoluteColor[] = {0.2f,0.2f,0.9f,1.0f};
    glColor4fv(revoluteColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,revoluteColor) ;
	
    // Draw any	axes that must be in the inboard frame.
    // Need to add glPushName
    glPushMatrix();
	switch(m_jointType) {
	   case	J_GIMBAL:
		glMultMatrixd((GLdouble *)inb_tm);
	
		glPushName(0);
		displayAxis(axis[0], arrowLength);
		glPopName();

		glRotated(m_State[0]*180.0/M_PI, axis[0][0],axis[0][1],axis[0][2]);
		glPushName(1);
		displayAxis(axis[1], arrowLength);
		glPopName();

		glRotated(m_State[1]*180.0/M_PI, axis[1][0],axis[1][1],axis[1][2]);
		glPushName(2);
		displayAxis(axis[2], arrowLength);
		glPopName();
		
		break;
	  case J_UNIVERSAL:
		glMultMatrixd((GLdouble	*)inb_tm);
		glPushName(0);
		displayAxis(axis[0], arrowLength);
		glPopName();

		glRotated(m_State[0]*180.0/M_PI, axis[0][0],axis[0][1],axis[0][2]);
		glPushName(1);
		displayAxis(axis[1], arrowLength);
		glPopName();

		break;
	   case	J_BALL:
		// displayRefFrame(arrowLength,outb_tm); // Show quaternion axes
		
		glMultMatrixd((GLdouble *)outb_tm);
		m_AuxFrame.toMatrix(frameMat);
	
		glPushName(0);
		glColor4f(1.0,0.0,0.0,1.0);
		displayAxis(frameMat[0],arrowLength);
		glPopName();
		glPushName(1);
		glColor4f(0.0,1.0,0.0,1.0);
		displayAxis(frameMat[1],arrowLength);
		glPopName();
		glPushName(2);
		glColor4f(0.0,0.0,1.0,1.0);
		displayAxis(frameMat[2],arrowLength);
		glPopName();

		break;
	   case	J_PIN:
		glMultMatrixd((GLdouble	*)inb_tm);
		glPushName(0);
		displayAxis(axis[0], arrowLength);
		glPopName();
		break;
	   case J_PLANAR:
		glMultMatrixd((GLdouble	*)inb_tm);
		glColor4fv(sliderColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,sliderColor) ;
		glPushName(0);
		displayAxis(axis[0], arrowLength,1);
		glPopName();
		glPushName(1);
		displayAxis(axis[1], arrowLength,1);
		glPopName();
		glColor4fv(revoluteColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,revoluteColor) ;
		glPushName(2);
		displayAxis(axis[2], arrowLength,1);
		glPopName();
		break ;
	   case	J_FREE:
		displayRefFrame(arrowLength,outb_tm);
		
		// Translate to outboard frame but don't rotate to match orientation
		glTranslated(outb_tm[3][0],outb_tm[3][1],outb_tm[3][2]);
		glColor4fv(sliderColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,sliderColor) ;
		glPushName(0);
		displayAxis(axis[0], arrowLength,1);
		glPopName();
		glPushName(1);
		displayAxis(axis[1], arrowLength,1);
		glPopName();
		glPushName(2);
		displayAxis(axis[2], arrowLength,1);
		glPopName();
		break;
	   case	J_SLIDER:   
		glMultMatrixd((GLdouble	*)inb_tm);
		glColor3fv(sliderColor);
		glPushName(0);
		displayAxis(axis[0], arrowLength, 1);
		glPopName();
		break;
	}
    glPopMatrix();

}

// display:
//	Displays a Joint as a sphere
//
// mode: JDISPLAY_CENTRES, Displays joint centres only.
//		 JDISPLAY_MANIPS , Joint manipulators, inboard and outboard vectors, joint centres
//
void Joint::display(int	mode)
{
	if (mode & LDISPLAY_SHADOW) return ;

	// glLoadName(m_jointNumber); //	For picking operations
	
	if ((mode & JDISPLAY_CENTRES) || (outboardLink->m_Geom == NULL) ) {
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING) ;
		glLineWidth(3.0);
		// Draw inboard and outboard vectors.
		if (inboardLink && mode != 0) { // Could be a NULL link (if root)
			glPushMatrix();
			glMultMatrixd((GLdouble *)inboardLink->m_transMat);

			glColor4f(1.0,0.0,1.0,1.0);
			glBegin(GL_LINES);
			glVertex3d(0.0,0.0,0.0);
			glVertex3dv(m_InbToJoint);
			glEnd();
			glPopMatrix();
		}

		glPushMatrix();
		glMultMatrixd((GLdouble	*)outboardLink->m_transMat);
		if (mode != 0) { 
 			glColor4f(1.0,0.0,0.0,1.0);
			glBegin(GL_LINES);
				glVertex3d(0.0,0.0,0.0);
				glVertex3dv(m_BodyToJoint);
			glEnd();
		}
		glLineWidth(1.0);
		// Joint centre.
		glColor4f((float)0.3,(float)0.3,(float)1.0,(float)1.0);
		glPointSize(7.0);
		glBegin(GL_POINTS);
			glVertex3dv(m_BodyToJoint);
		glEnd();
		glPointSize(1.0);
		glPopMatrix();
		glPopAttrib();
    }

    if (mode & JDISPLAY_MANIPS)
		displayManipulators();

}

// setPosition:
//	sets a single point which will coincide	with a common inboard
//	and outboard joint position for	each joint.
//
//	p:  Sets the position of the joint.
//
void Joint::setPosition(double p[3])
{
    assert(outboardLink);

    Vector inb,outb;
    Vector parentpos, childpos;
    if(	inboardLink != NULL)
    {
	inboardLink->getPosition(parentpos); //	world coordinates
	VecSubtract(inb,p, parentpos) ;	// world coordinates
	rotPoint_mat4(inb,inboardLink->m_invTransMat) ; // bring it to local coordinates
	setInbToJoint(inb);
    }
    else  // root link with respect to ground
	setInbToJoint(p) ;

    outboardLink->getPosition(childpos);

	// Make adjustments if translation involved due to slider or free joint.
	if (m_jointType == J_SLIDER || m_jointType == J_FREE)
	{
		// Convert translation into world.
		double wtrans[3] = {0.0,0.0,0.0};
		for (int i = 0; i < m_numAxis; i++) {
			wtrans[0] += m_axis[i][0]*m_State[0];
			wtrans[1] += m_axis[i][1]*m_State[1];
			wtrans[2] += m_axis[i][2]*m_State[2];
		}
		if (inboardLink) 
			transformPoint_mat(wtrans,inboardLink->m_transMat);
		VecAdd(p,p,wtrans);
	}


    VecSubtract(outb,p,childpos) ; // world coordinates

    rotPoint_mat4(outb,outboardLink->m_invTransMat) ; // local coordinates
    setBodyToJoint(outb);
}

// setInbToJoint:
//
void Joint::setInbToJoint(double p[3])
{
	VecCopy(m_InbToJoint,p);
	if (inboardLink) // will be NULL for first link
	    VecCopy(inboardLink->endEffector,p);
}

// setRelativePosition:
//	set the	relative position of the joints.
//
void Joint::setRelativePosition(double p[3])
{
    // Get inboard and outboard	in world coordinates
    Vector inb,	outb ;
    getInbToJoint(inb);
    if(	inboardLink != NULL)
	transformPoint_mat(inb,inboardLink->m_transMat);

    getBodyToJoint(outb);
    transformPoint_mat(outb,outboardLink->m_transMat);

    // Adjust both inboard and outboard	vectors.
    for	(int i=0; i < 3; i++) {
	inb[i] += p[i];
	outb[i]	+= p[i];
    }

    // Now bring back to local frame.
    Vector parentpos, childpos;
    if(	inboardLink != NULL)
    {
	inboardLink->getPosition(parentpos); //	world coordinates
	VecSubtract(inb,inb, parentpos)	; // world coordinates
	rotPoint_mat4(inb,inboardLink->m_invTransMat) ; // bring it to local coordinates
	setInbToJoint(inb);
    }
    else
	setInbToJoint(inb);

    // update body to joint
    outboardLink->getPosition(childpos);
    VecSubtract(outb,outb,childpos) ; // world coordinates
    rotPoint_mat4(outb,outboardLink->m_invTransMat) ; // local coordinates
    setBodyToJoint(outb);
}

int Joint::Command(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
	char dofString[MAX_LINE];

	int count = 0;
	// For compatibility
    if(	strcmp(argv[count],	"set") == 0 )
		count = 1;

    	if( strcmp(argv[count],"stiff_damp") == 0 )
	{
	    if( argc-1-count == 2 )
	    {
		double st =  atof(argv[count+1]) ;
		double damp = atof(argv[count+2]) ;
		double *iner = outboardLink->getInerTensor() ;
		for( int i = 0 ; i < getNumAxis() ; i++ )
		{
		    if( fabs(m_axis[i][0] - 1.0) <  0.00001 )
		    {
			stiffness[i] = st*iner[0] ;
			damping[i] = damp*iner[0] ;
		    }
		    else if( fabs(m_axis[i][1] - 1.0) <  0.00001 )
		    {
			stiffness[i] = st*iner[4] ;
			damping[i] = damp*iner[4] ;
		    }
		    else 
		    {
			stiffness[i] = st*iner[8] ;
			damping[i] = damp*iner[8] ;
		    }
		    maxStiffness[i] = stiffness[i] ;
		    maxDamping[i] = damping[i] ;
		    danceTcl::OutputResult("parameter: stiffness %lf damp %lf\n", 
					   stiffness[i], damping[i]) ;
		}
		return TCL_OK ;
	    }
	    if (argc-1-count != 3)
	    {
		danceTcl::OutputMessage("USAGE: stiff_damp <dof> <stiffness> <damping>\n");
		return TCL_ERROR ;
	    }
	    int	dof = atoi(argv[count+1]) ;
	    if(	(dof >= 0) && (dof < getStateSize()))
	    {
			stiffness[dof] = atof(argv[count+2]) ;
			damping[dof] = atof(argv[count+3]) ;
	    }
	    else
	    {
			danceTcl::OutputMessage("ERROR: Joint index out of bounds\n");
			return TCL_ERROR;
	    }
	}
	else if (strcmp(argv[count],"position") == 0)
	{
		double pos[3];
		if (argc-count-1 >= 3) { // Set position.
			pos[0] = atof(argv[count+1]);
			pos[1] = atof(argv[count+2]);
			pos[2] = atof(argv[count+3]);
		
			if (argc-count-1 == 4) {
				Link *wlink = getOutboardLink();
				
				ArticulatedObject *ao = wlink->getAo();
				if (strcmp(argv[count+4],"parents") == 0) 
					   ao->moveJointAndParents(m_jointNumber,pos);
				else if (strcmp(argv[count+4],"children") == 0) 
					   ao->moveJointAndChildren(m_jointNumber,pos);
				else 
					   setPosition(pos);

			}
			else 
				setPosition(pos);
			
		}
		else {
			getPosition(pos);
			danceTcl::OutputListElement("%f",pos[0]);
			danceTcl::OutputListElement("%f",pos[1]);
			danceTcl::OutputListElement("%f",pos[2]);
		}
		return TCL_OK;
	}
	else if (strcmp(argv[count],"ndof") == 0)
	{
		int num = getNumDof();
		danceTcl::OutputResult("%d", num) ;
	}
	else if (strcmp(argv[count],"dof") == 0)
	{
		if (argc-count-1 < 2) {
			danceTcl::OutputMessage("USAGE: dof <number> {value [<value>] | label}"); 
			return TCL_ERROR;
		}
		int num = atoi(argv[count+1]);
		if (num < 0 || num >= getNumDof()) {
			danceTcl::OutputMessage("ERROR: Dof index out of range.");
			return TCL_ERROR;
		}

		if (strcmp(argv[count+2],"value") == 0) {
			if (argc-count-1 == 3) {
				double val = atof(argv[count+3]);
				setDof(num,val);
			}
			else {
				sprintf(dofString,"%f",getDof(num));
				danceTcl::OutputResult("%f", getDof(num)) ;
			}
		}
		else if (strcmp(argv[count+2],"label") == 0) { 
			if (getLabel(num,dofString))
				danceTcl::OutputResult("%s", dofString);
			else
				danceTcl::OutputResult("%s", "");
		}
		else if (strcmp(argv[count+2],"limits") == 0) {
			if (argc-count-1 == 4) 
				setLimits(num,atof(argv[count+3]),atof(argv[count+4]));
			else {
			    danceTcl::OutputListElement("%lf", m_Limits[num][0]) ;
			    danceTcl::OutputListElement("%lf", m_Limits[num][1]) ;
			}
			return TCL_OK;
				
		}
		
	}
	else if (strcmp(argv[count],"types") == 0)
		return getAvailableTypes(interp);
	else if (strcmp(argv[count],"change") == 0) {
		if (argc-count-1 == 1) {
			int m_jointType = getJointType(argv[count+1]);
			changeType(m_jointType);
		}
		return TCL_OK;
	}
    return TCL_OK;
}

int Joint::getLabel(int dof, char *label)
{
	const char *coord[] = { "x","y","z","azim","elev","twist"};
	if (dof < 0 || dof > getNumDof() -1) return 0;

	switch(m_jointType)	{
	   case	J_SLIDER:
		sprintf(label,"axis%d",dof);
		break;
	   case	J_FREE:
		strcpy(label,coord[dof]);
		break;
	   case	J_BALL:
			strcpy(label,coord[dof+3]);
		break;
	   case	J_GIMBAL:
	   case J_UNIVERSAL:
	   case J_PIN:
		sprintf(label,"rot%d",dof);
		break;
	}
	return 1;
}

// Sets the dof of the joint. These are user-interpreted degrees of freedom
// opposed to the "true" representation of the joint which is stored in
// m_State and m_Frame. This method also changes the appropriate m_State vector.
// All angles assumed to be in degrees.
// This function checks for joint limits while the almost equivalent setState doesn't.
int Joint::setDof(int dof, double value)
{
    if (dof < 0 || dof > getNumDof()) {
		danceTcl::OutputMessage("ERROR: dof index out of range.\n");
		return 0;
    }
    if (value < m_Limits[dof][0]) value = m_Limits[dof][0];
    if (value > m_Limits[dof][1]) value = m_Limits[dof][1];

    double azim, elev, twist;
    switch (m_jointType) {
    case J_BALL:
	  m_Frame.toAzimElevTwist(&azim,&elev,&twist);
	  if (dof == 0) azim = value;
	  if (dof == 1) elev = value;
	  if (dof == 2) twist = value;
	  m_Frame.set(azim,elev,twist);
	  m_Frame.toVector(&(m_State[0]));
    break;
    case J_FREE:
	  if (dof >= 3) {
	      m_Frame.toAzimElevTwist(&azim,&elev,&twist);
	      if (dof == 3) azim = value;
	      if (dof == 4) elev = value;
	      if (dof == 5) twist = value;
	      m_Frame.set(azim,elev,twist);
	      m_Frame.toVector(&(m_State[3]));
	  }
 	  else
	      m_State[dof] = value;
    break;
    case J_PIN:
      m_State[dof] = value*M_PI/180.0;
      m_Frame.set(m_State[dof], m_axis[0]) ;
    break;
    case J_GIMBAL:
    case J_UNIVERSAL:
	{
      	  m_State[dof] = value*M_PI/180.0 ;

	  m_Frame.set(m_State[0], m_axis[0]) ;
	  // multiply the three	rotations together
	  // using quaternion multiplication
	  for( int i = 1 ; i < getNumAxis() ; i++ )
	  {
		  Quaternion q;
	      q.set(m_State[i], m_axis[i]) ;
	      m_Frame.multiply(&q)	;
	  }
	}
    break;
    case J_SLIDER:
      m_State[dof] = value ;
    break;
    }

    return 1;
}

/** Returns the degree of freedom in degrees */
double Joint::getDof(int dof)
{
    double azim, elev, twist;

    double result = 0.0;

    switch (m_jointType) {
    case J_BALL:
	  m_Frame.toAzimElevTwist(&azim,&elev,&twist);
	  if (dof == 0) result = azim;
	  if (dof == 1) result = elev;
	  if (dof == 2) result = twist;
      break;
    case J_FREE:
	  if (dof >= 3) {
	      m_Frame.toAzimElevTwist(&azim,&elev,&twist);
	      if (dof == 3) result =  azim;
	      if (dof == 4) result =  elev;
	      if (dof == 5) result =  twist;
	  }
 	  else
		  result = m_State[dof];
      break;
    case J_PIN:
		  result = m_State[dof]*180.0/M_PI;
      break;
    case J_GIMBAL:
    case J_UNIVERSAL:
		  result = m_State[dof]*180.0/M_PI;
      break;
	case J_PLANAR:
		if( dof == 2 )
			result = m_State[dof]*180.0/M_PI;
		else
			result = m_State[dof] ;
		break ;
    case J_SLIDER:
		  result = m_State[dof];
      break;
    }

    return  result;
}

void Joint::getLimits(int dof, double *low, double *high)
{
	*low = m_Limits[dof][0];
	*high = m_Limits[dof][1];
}

void Joint::setLimits(int dof, double low, double high)
{
	m_Limits[dof][0] = low; 
	m_Limits[dof][1] = high;
}

// Given the string, returns the type number.
int Joint::getJointType(char * typeString)
{
	if (strcmp(typeString,"Pin") == 0) return J_PIN;
	if (strcmp(typeString,"Ball") == 0) return J_BALL;
	if (strcmp(typeString,"Cylinder") == 0) return J_CYLINDER;
	if (strcmp(typeString,"Slider") == 0) return J_SLIDER;
	if (strcmp(typeString,"Free") == 0) return J_FREE;
	if (strcmp(typeString,"Gimbal") == 0) return J_GIMBAL;
	if (strcmp(typeString,"Weld") == 0) return J_WELD;
	if (strcmp(typeString,"Planar") == 0) return J_PLANAR;
	if (strcmp(typeString,"Bearing") == 0) return J_BEARING;
	if (strcmp(typeString,"Universal") == 0) return J_UNIVERSAL;
	if (strcmp(typeString,"Bushing") == 0) return J_BUSHING;

	return J_UNDEF;
}

// getAvailableJoints:
//	interp: Tcl interpreter
//
// Returns a list of available joints.
// NOTE: Commented out lines are not implemented yet.
int Joint::getAvailableTypes(Tcl_Interp * interp)
{
	danceTcl::OutputListElement("Pin");
	danceTcl::OutputListElement("Ball");
	// danceTcl::OutputListElement("Cylinder");
	danceTcl::OutputListElement("Slider");
	danceTcl::OutputListElement("Free");
	danceTcl::OutputListElement("Gimbal");
	// danceTcl::OutputListElement("Weld");
	danceTcl::OutputListElement("Planar");
	// danceTcl::OutputListElement("Bearing");
	danceTcl::OutputListElement("Universal");
	// danceTcl::OutputListElement("Bushing");

	return TCL_OK;
}

// addDof:
//		Adds the applicable delta to the joints state.
//
//		index:	index of degree of freedom
//	        deltaAngle: Delta to use for angles
//		deltaTrans: Delta to use for translations.
//              The use of setDof ensures that the joint limits
//              are preserved.
void Joint::addDof(int index, double deltaAngle, double deltaTrans)
{
	double stateValue	= 0.0;
        switch(m_jointType) {
		case J_PIN:
		     stateValue = deltaAngle+getState(0) ;
		     // convert to degrees which is what setDof takes
		     stateValue = stateValue*180.0 / (double) M_PI ;
		     setDof(0,stateValue);
		break;
	    case J_PLANAR:
		if( index == 2) 
		{
		    stateValue = deltaAngle+getState(index) ;
		    // convert to degrees which is what setDof takes
		    stateValue = stateValue*180.0 / (double) M_PI ;
		}
		else
		     stateValue = deltaTrans+getState(index) ;
		setDof(index,stateValue);
		    
		case J_BALL:
			switch(index) {
			  case  0:
			  case	1:
			  case	2: 
					 Quaternion q;
					 double auxMat[4][4]; m_AuxFrame.toMatrix(auxMat);
					 q.set(deltaAngle, auxMat[index]);

					 double newMat[4][4],new_rot[4][4];
					 q.toMatrix(new_rot);
					 
					 // If alt-key pressed, change joint rotation axes.
					 if (dance::m_ModifierKey == GLUT_ACTIVE_ALT) {
						 multArray((double *)newMat, (double *)auxMat, (double *)new_rot,4,4,4);
						 m_AuxFrame.fromMatrix(newMat);
					 }
					 else {
						 double mat[4][4]; getOrientation(mat);
						 multArray((double *)newMat,(double *)new_rot, (double *)mat,4,4,4);
						 m_Frame.fromMatrix(newMat);
						 m_Frame.toVector(&(m_State[0]));
					 }
		   	   break;
			   case	3: // red 
			   case	4: // green
			   case	5: // blue
				{
				double mat[4][4];
				getOrientation(mat);

				Quaternion q_rot;
				q_rot.set(deltaAngle,mat[index-3]);

				double	 rot[4][4], new_rot[4][4];
				q_rot.toMatrix(rot);
				multArray((double *)new_rot,(double *)mat,(double *)rot,4,4,4);
				m_Frame.fromMatrix(new_rot);
				m_Frame.toVector(&(m_State[0]));
				}
				break;
			}
		break;
		case J_SLIDER:
		case J_FREE:
		case J_GIMBAL:
		case J_UNIVERSAL:
		    switch(index) {
			   case	0:
			   case	1:
			   case	2:
				if (m_jointType == J_GIMBAL ||
				    m_jointType == J_UNIVERSAL)
				{
				    // convert the value from radians to degrees
				    stateValue	=  deltaAngle + getState(index);
				    stateValue = stateValue*180.0 / (double) M_PI ;
				}
				else  // Translation stuff for free, and slider	joints
				     stateValue	= deltaTrans + getState(index);
				
				setDof(index, stateValue);
				break;
			   // Ball and socket and quaternion part of Free joint
			   case	3: // red ,
			   case	4: // green
			   case	5: // blue
				{
				double mat[4][4];
				getOrientation(mat);

				Quaternion q_rot;
				q_rot.set(deltaAngle,mat[index-3]);

				double	 rot[4][4], new_rot[4][4];
				q_rot.toMatrix(rot);
				multArray((double *)new_rot,(double *)mat,(double *)rot,4,4,4);
				m_Frame.fromMatrix(new_rot);
				m_Frame.toVector(&(m_State[3]));
				}
				break;
		    }
		break;
		default:
		    danceTcl::OutputMessage("Not implemented: joint editing\n");
    }
}

void Joint::WriteBVHFile(FILE *fp, int depth)
{
	char prfx[MAX_LINE] = "" ;
	int i ;


	if( m_jointType == J_BALL )
	{
		danceTcl::OutputMessage("ERROR: writeBHVFile not "
					"implemented for ball joints yet.\n") ;
		return ;
	}

	for( i = 1 ; i < depth ; i++ )
		strcat(prfx, "\t") ;

	if( depth == 1 )
		fprintf(fp, "%s\tOFFSET 0.0000 0.0000 0.0000\n", prfx) ;
	else
	{
		Vector offset ;
		// get the parent joint of the inboard link
		Joint *inbJoint = inboardLink->getParentJoint() ;
		if( inbJoint == NULL ) 
		{
		       danceTcl::OutputMessage("ERROR: WriteBVHFile: missing joint!\n");
			return ;
		}
		Vector inbBtoJ ;
		inbJoint->getBodyToJoint(inbBtoJ) ;
		VecSubtract(offset, m_InbToJoint, inbBtoJ) ;
		fprintf(fp, "%s\tOFFSET %lf %lf %lf\n", prfx, offset[0], 
			offset[1], offset[2]) ;
	}
	
	// write the channels
	fprintf(fp, "%s\tCHANNELS %d", prfx, getNumDof()) ;
	switch (m_jointType)
	{
	case J_FREE:
		fprintf(fp, " Xposition Yposition Zposition") ;
		break ;
	case J_SLIDER:
		if( fabs(m_axis[0][0] - 1.0) < 0.00001 )
			fprintf(fp, " Xposition") ;
		else if( fabs(m_axis[0][1] - 1.0) < 0.00001 )
			fprintf(fp, " Yposition") ;
		else if( fabs(m_axis[0][2] - 1.0) < 0.00001 )
			fprintf(fp, " Zposition") ;
		else
		{
			danceTcl::OutputMessage("ERROR: WriteBVHFile: "
						"slide joint must be along "
						"one of the x,y,z axis!\n") ;
			return ;
		}
	}
	
	if( m_jointType != J_SLIDER )
	{
		for( i = 0 ; i < m_numAxis ; i++ )
		{
			if( fabs(m_axis[i][0] - 1.0) < 0.00001 )
				fprintf(fp, " Xrotation ") ;
			else if( fabs(m_axis[i][1] - 1.0) < 0.00001 )
				fprintf(fp, " Yrotation ") ;
			else if( fabs(m_axis[i][2] - 1.0) < 0.00001 )
				fprintf(fp, " Zrotation ") ;
			else
			{
				danceTcl::OutputMessage("ERROR: WriteBVHFile: "
							"axis must be along one "
							"of the x,y,z axis!\n") ;
				return ;
			}
		}
	}
	fprintf(fp, "\n") ;
}	

// Returns 1 if there has been a change in joint state.
//
int Joint::isChanged()
{
	int result = 0, i;
	double tol = 0.00001;
	for (i = 0; i < 3; i++) {
		if (fabs(m_InbToJoint[i] - m_OldInbToJoint[i]) > tol) {
			result = 1;
			break;
		}
		if (fabs(m_BodyToJoint[i] - m_OldBodyToJoint[i]) > tol) {
			result = 1;
			break;
		}
	}
	if (result) return(result);

	for (i = 0; i < getStateSize(); i++) 
		if (fabs(m_State[i] - m_OldState[i]) > tol) {
			result = 1;
			break;
		}
	return(result);
}


/**
 * Calculates the joint state variables from the joint's transformation matrix.
 *
 * @return void 
 */
void Joint::CalcState()
{
    switch (m_jointType) {
	case J_BALL:
	    m_Frame.toVector(&(m_State[0]));
	    break;
	case J_FREE:
	    // Assumes zero initial translation.
	    m_State[0] = 0.0;
	    m_State[1] = 0.0;
	    m_State[2] = 0.0;
	    m_Frame.toVector(&(m_State[3]));
	    break;
	case J_PLANAR:
	    break ;
	case J_PIN:
	    break;
	case J_GIMBAL:
	case J_UNIVERSAL:
	    break;
	case J_SLIDER:
	    break;
    }
}

void Joint::WriteMayaFile(FILE *fp)
{

    // set the parent first
    if( inboardLink != NULL )
    {
	fprintf(fp, "select -r %s ;\n", inboardLink->getParentJoint()->getName()) ;
    }
    Vector p ;
    getPosition(p) ;
    fprintf(fp, "joint -name %s -absolute -p %lf %lf %lf ", 
	    getName(), p[0], p[1], p[2]) ;
    fprintf(fp, "-dof ") ;
    char dof[4] = "" ;
    if( m_jointType == J_BALL )
	strcpy(dof, "xyz") ;
    else
    {
	int i ;
	for( i = 0 ; i < getNumAxis() ; i++ )
	{
	    if( m_axis[i][0] > 0.5 ) 
		dof[i] = 'x' ; 
	    else if( m_axis[i][1] > 0.5 )
		dof[i] = 'y' ;
	    else
	    dof[i] = 'z' ;
	}
        dof[i] = '\0' ;
    }
    fprintf(fp, "%s ", dof) ;
    if( getNumAxis() == 3 )
	fprintf(fp, "-roo %s", dof) ;
    fprintf(fp, " ;\n") ;
    
    // set end effectors for childless links
    if( outboardLink->getNumChildLinks() == 0 )
    {
	fprintf(fp,"select -r %s ;\n", getName()) ;
	outboardLink->getEndEffectorWC(p) ;
	fprintf(fp, "joint -name %sEndEffector -absolute -p %lf %lf %lf ;\n",
		getName(), p[0], p[1], p[2]) ;
    }
    return ;
}
	
