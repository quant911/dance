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


#ifndef	NO_GL
#ifdef WIN32
#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"
#endif
#include "defs.h"
#include "DGeometry.h"
#include "GLutilities.h"
#include "RAPID.h"
#include "danceTcl.h"

int DGeometry::m_NumGeometry = 0;

DGeometry::DGeometry()
{
    setBaseType("geometry");

    m_Color[0] = 0.0 ;
    m_Color[1] = 1.0 ;
    m_Color[2] = 0.0 ;
    m_Color[3] = 1.0 ;
    
    m_RAPIDmodel = NULL;
    m_ID = m_NumGeometry++; // We will always have the first valid ID as 1 since ID 0 corresponds to the
    // proxy geometry.
    m_Transparency = 0.0;
}


void DGeometry::displayBoundingBox(float	r, float g, float b, float a)
{
	// Display Oriented-Bounding-Box if present.
	if (m_RAPIDmodel) {
		glColor4f(r,g,b,a);
		m_RAPIDmodel->Display();
	}
	else
		m_BoundingBox.display(r,g,b,a);
}

// monitor points functions

//		   getMonitorPoints()
// Accepts a transformation matrix or NULL and fills
// in the pre allocated	matrix pts with	the monitor
// points. THe monitor poins are returned in link
// coordinate system unless matrix m is	supplied
// in which case they are multiplied by	it.
// Matrices *m,
// [ R 0 ]
// [ T 1 ]

void DGeometry::getMonitorPoints(double (*m)[4][4], Vector *pts)
{
    int	i ;

    for( i = 0 ; i < m_MonitorPoints.m_NumPoints ; i++ )
	VecCopy(pts[i],	m_MonitorPoints.m_Point[i])	;

    if(	m != NULL )
	for( i = 0 ; i < m_MonitorPoints.m_NumPoints ; i++ )
		transformPoint_mat(pts[i],*m) ;
}

void DGeometry::getMonitorPointsPrevPosition(double (*m)[4][4], Vector *pts)
{
    int	i ;

    for( i = 0 ; i < m_MonitorPoints.m_NumPoints ; i++ )
	VecCopy(pts[i],	m_MonitorPoints.m_PrevPos[i])	;

    if(	m != NULL )
	for( i = 0 ; i < m_MonitorPoints.m_NumPoints ; i++ )
		transformPoint_mat(pts[i],*m) ;
}


int DGeometry::getMonitorPoints(Vector **pts)
{
    *pts = m_MonitorPoints.m_Point ;
    return  m_MonitorPoints.m_NumPoints ;
}


int DGeometry::getMonitorPointsPrevPos(Vector **pts)
{
    *pts = m_MonitorPoints.m_PrevPos ;
    return  m_MonitorPoints.m_NumPoints ;
}

void DGeometry::DeleteMonitorPoints(void)
{
    m_MonitorPoints.Deallocate() ;
}

int DGeometry::AllocateMonitorPoints(int n)
{
    return m_MonitorPoints.Allocate(n) ;
}


int DGeometry::assignMonitorPoints(int n)
{
    if( n < 1 )
    {
	printf("ERROR: assignMonitorPoints: number of points must be > 0!\n") ;
	return 0 ;
    }
    if( AllocateMonitorPoints(n) == n )
	return createMonitorPoints(n) ;
    else
	return 0 ;
}

int DGeometry::assignMonitorPoints(int n, Vector *p)
{
    if( n < 1 )
    {
	printf("ERROR: assignMonitorPoints: number of points must be > 0!\n") ;
	return 0 ;
    }
    if( AllocateMonitorPoints(n) != n ) return 0 ;
    for( int i = 0 ; i < n ; i++ )
	VecCopy(m_MonitorPoints.m_Point[i], p[i]) ;
    return n ;
}

int DGeometry::Command(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv)
{
    // call the DanceObject command
    if( DanceObject::Command(clientData, interp, argc, argv) == TCL_OK ) return TCL_OK ;

    // call the PlugIn command
    return commandPlugIn(clientData, interp, argc, argv) ;
}

void DGeometry::displayLocalAxes()
{
	// Draw origin.
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	double origin[3] = {0.0,0.0,0.0};
	glColor4f(1.0,1.0,0.0,1.0);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex3dv(origin);
	glEnd();
	glPointSize(1.0);

	// Draw axes.
	double xaxis[3] = { 1.0,0.0,0.0 };
	double yaxis[3] = { 0.0,1.0,0.0 };
	double zaxis[3] = { 0.0,0.0,1.0 };

	double dim[3];
	m_BoundingBox.getDimensions(dim);

	glColor4f(1.0,0.0,0.0,1.0);
	GLdrawVector(origin,xaxis,dim[0]*0.5);
	glColor4f(0.0,1.0,0.0,1.0);
	GLdrawVector(origin,yaxis,dim[1]*0.5);
	glColor4f(0.0,0.0,1.0,1.0);
	GLdrawVector(origin,zaxis,dim[2]*0.5);
	glPopAttrib();	
}

void DGeometry::getBounds(double dim [ 3 ])
{
	calcBoundingBox();
	m_BoundingBox.getDimensions(dim);
}
