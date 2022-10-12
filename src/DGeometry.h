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


#ifndef	_DGeometry_h
#define	_DGeometry_h
#define	MAX_VER	40
#define	MAX_POINTS_IN_PL   1000	/* maximum number of points in a polygon list */
#define	MAX_ADJ_POL	     50	/* maximum number of polygons shared by	a single vertex	*/
#define	NOT_VALID	    -1

// These should	be moved to their respective subclasses	to hide	information

#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "vector.h"
#include "Ball.h"
#include "CoordSystem.h"
#include "BoundingBox.h"
#include "PlugIn.h"
#include "MonitorPoints.h"

class RAPID_model; // RAPID model for collision detection.

class DLLENTRY DGeometry: public PlugIn {
protected:
  static int m_NumGeometry;
  int m_ID;
  
  float m_Color[4];
  float m_Transparency;
  int	displayStyle;		// Style to draw in.
  BoundingBox	m_BoundingBox ;
  MonitorPoints m_MonitorPoints	;
  
  void DeleteMonitorPoints(void) ;
  int AllocateMonitorPoints(int n) ;
  int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
  
  virtual int createMonitorPoints(int numPoints) { return 0 ; } ;
public:
  RAPID_model *m_RAPIDmodel;
  virtual int GetRapidTriangle(int id, Vector v1, Vector v2, Vector v3) 
    { return -1 ;} ; // returns a triangle that corresponds to rapid
                                                          // id

    void getBounds(double dim[3]);
    virtual void displayNormals(void) { return; };
    void displayLocalAxes(void);
    inline void setTransparency(float transparency) {m_Transparency = transparency;};

	virtual ~DGeometry() {return;};
    DGeometry() ;
  
    virtual void display(int style=0) =	0 ;
    void displayBoundingBox(float r=0.0, float g=1.0, float b=0.0, float a=1.0);
    virtual BoundingBox	*calcBoundingBox(BoundingBox *box=NULL) { return NULL ;};
    virtual void calcInerTensor(double inerTensor[3][3], double	mass) =	0;
    virtual void computeMoments(double den, double *mass, double inerTensor[3][3])
      {	calcInerTensor(inerTensor, *mass) ; } ;
    virtual void getEndEffector(Vector p) { fprintf(stderr,"getEndEffector: Not	implemented for	this geometry type\n") ;};
	inline void setColor(float r, float g, float b, float a) { m_Color[0] = r; m_Color[1] = g; m_Color[2] = b; m_Color[3] = a; };
  // virtual functions
  // monitor points routines

 
  virtual int commandPlugIn(ClientData clientData, Tcl_Interp 
			  *interp, int argc, char **argv) { return TCL_OK;};

  virtual void Center(void) { return ;} ;
  virtual void Rotate(char *axis, double degrees, int center = 0) { return ;} ;
  virtual void Translate(double x, double y, double z) { return ;} ;
  virtual void Scale(double sx, double sy, double sz, int center = 0) { return ;} ;
  virtual void SetOrigin(Vector or) { printf("Not implemented for this geometry.\n") ;} ;
  virtual int PrepareCollision(void) { return TCL_ERROR ;} ;

  int assignMonitorPoints(int npoints) ;
  int assignMonitorPoints(int n, Vector	*p) ;
  void getMonitorPoints(double (*m)[4][4], Vector *pts)	;
  int getMonitorPoints(Vector **pts) ;
  int getMonitorPointsPrevPos(Vector **pts) ;
  int getNumMonitorPoints(void)	{  return m_MonitorPoints.m_NumPoints ; } ;
  void getMonitorPointsPrevPosition(double (*m)[4][4], Vector *pts) ;
   
  MonitorPoints * getMonitorStruct(void) { return &m_MonitorPoints ;} ;
} ;

#endif

