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



#ifndef	_LINK_H_
#define	_LINK_H_ 1

#include <tcl.h>
#include "DGeometry.h"
#include "DSystem.h"

#ifdef WIN32
#ifdef _EXPORTING_AR
#define DLLENTRY_AR __declspec(dllexport)
#else
#define DLLENTRY_AR __declspec(dllimport)
#endif
#else
#define DLLENTRY_AR
#endif

#define	DEF_MASS_DEN 1.0
#define MAX_BRANCHING 10 

typedef struct InCollision {
  char objectName[50] ;
  int linkNumber ;
} Incollision ;

class VCollide;
class DLLENTRY_AR Link : public DSystem {
friend class Joint ;
friend class ArticulatedObject ;
public:
	void DeleteChildren();
	void RemoveGlobalLink(Link *wlink);
	void RemoveChildJoint(Joint *wjoint);
	void Highlight(float r, float g, float b, float a);
	void displayAxes(void);
	static Link * GetGlobalLink(int collideID);
	void AddGlobalLink(Link *wlink);

	// VCOLLIDE collision routines.
    static VCollide *m_VCollideEngine;
	static Link **m_GlobalLinks;
	static int m_numGlobalLinks;
	myBOOL m_InCollision;

	int m_VCollideID;

    void setEndEffector(double pnt[3]);
    void displayMonitorPoints(void);
    BoundingBox	boundingBox;
	myBOOL m_DisplayBoundingBox;
    DGeometry *m_Geom ;
    double geomScale[3];
    int	geomFix;
	Vector m_childOffset ;         // used when reading a bvh file

    int	m_linkNumber ;		// holds the number of the links
    double m_transMat[4][4] ;	// the matrix that transforms a	point in link coordinates
    double m_invTransMat[4][4] ;	// the inverse of the above
    double m_prevWTransMat[4][4] ;  

    Link(int ln) ;
    ~Link() ;
    inline DGeometry *GetGeometry() { return(m_Geom); };
    inline int getNumber () { return m_linkNumber	;} ;
    inline int getNumChildLinks() { return m_numChildLinks ; } ;
    // inline int getNumChildJoints() { return m_numChildLinks ;} ;
    inline Link	**getChildLinks() { return &childLink[0] ; } ;
    inline Link	*getParentLink() { return parentLink ; } ;

    ArticulatedObject *	getAo(void) { return ao	;} ;

   
    void  getTransMat(double m[4][4]) ;
    void  getInvTransMat(double	m[4][4]) ;
    inline Joint *getParentJoint() { return parentJoint	; } ;
    inline void getEndEffector(double p[3]) {memcpy(p,endEffector,3*sizeof(double));};
    void getEndEffectorWC(double p[3]);
    void setEndEffectorWC(double p[3]);
   
    void getLocalCoord(double local[3], double world[3]);
    void getWorldCoord(double world[3], double local[3]);
    void getLocalCoordSim(double local[3], double world[3]);
    void getWorldNormal(double world[3], double local[3]);
    void getWorldVelocity(double worldvel[3], double local[3]);

  //void getWPrevPos(Vector pointLocal, Vector prevPos) ;
    void getWTransMatGeom(double transMat[4][4]) ;
    void getWTransMat(double tm[4][4]) ;
    void getWTransMat(float tm[4][4]) ;
    inline double getMass() {return m_Mass ; } ;
    void Display(int mode=0) ;
    void displayTree() ;
    void print(FILE *fptr) ;
    void changeToLocal() ;
    void changeToGlobal() ;
    void displayBoundingBox(float r=0.0, float g=1.0, float b=0.0, float a=1.0);
    BoundingBox	*calcBoundingBox(BoundingBox *)	;
    void getAxes(double	x[3], double y[3], double z[3]);
    void getCoordSystem(CoordSystem *cs);
    void setPosition(double p[3]) ;
    void getPosition(double p[3]) ;
    void getOrientation(float tm[4][4]);
    void getOrientation(double tm[4][4]);
    void setOrientation(int naxis, double v[3])	;
    void setOrientation(double tm[4][4]);
    void getRotation(double tm[3][3]);
    void getPoint(int index, int modifier, double *point);
    void setTransMat(double tm[4][4]) ;
    void setTransMat(CoordSystem cs);
   
    void setCenterMass(Vector p) { VecCopy(m_cm,p);} ;
    void getCenterMass(Vector p) { VecCopy(p,m_cm);} ;
    void setParentLink(Link *l)	{ parentLink = l ;} ;
    void setParentJoint(Joint *pj) { parentJoint = pj ;}
    void incNumChildLinks(Link *child) {
	      childLink[m_numChildLinks] = child;	m_numChildLinks++; } ;
   // void incNumChildJoints(void) { m_numChildJoints++; } ;
    int	writeSdFile(FILE *fp) ;
	void WriteBVHFile(FILE *fp, int depth) ;
    Link *readSdfast(FILE *fp) ;
    void FitGeometryToLink(int argc, char **argv) ;
    void AttachGeom(void) ;

    int	Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
    int	replaceGeometry(Tcl_Interp *interp, int	argc, char **argv);
    int rotateGeometry(int argc, char **argv) ;
    int	assignMonitorPoints(ClientData clientData, Tcl_Interp *interp,
			    int	argc, char **argv);
    void GetRapidTriangle(int n, Vector v1, Vector v2, Vector v3) ;
    int getChildren(Tcl_Interp *interp);
    int	getMonitorPoints(Vector	**pts);
    MonitorPoints *GetMonitorPoints(void){ return &m_MonitorPoints ;} ;
    inline int GetNumMonitorPoints(void) { return m_MonitorPoints.m_NumPoints; };

  InCollision m_inCollision ;
private:
    int getMonitorPointsFromGeom(void);
    void resetInbAndOutb(int flip = 0);

	// Mass properties.
    double m_Mass;				// mass of link
    double m_InerTensor[3][3] ;	// inertia tensor of link
	int m_InerTensorIsDiagonal;

	inline double *getInerTensor() { return &m_InerTensor[0][0] ;} ;
    inline void setMass(double m) { m_Mass = m ;} ;
	void setMoments(double moments[3]);

	float m_Transparency;
	myBOOL m_DisplayAxes;

	myBOOL m_DisplayNormals;
	myBOOL m_DisplayGeometry ;
    ArticulatedObject  *ao ;
    double endEffector[3];	 // end	effector for link
    MonitorPoints m_MonitorPoints; // Monitor points for link

    int	m_numChildLinks ;		// number of links attached to the end joint
    Link *parentLink ;		// pointer to the parent link (NULL if grounded	or free)
    Joint *parentJoint ;	// pointer to parent joint ( always not	null)
    Vector m_cm ;

    Link  *childLink[MAX_BRANCHING] ;		// holds the links that	follow this one
} ;

#endif
