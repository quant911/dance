#ifndef	PLANEGROUND_H
#define	PLANEGROUND_H

#include "GL/glutShared.h"
#include "DLight.h"
#include "DActuator.h"
#include "QuadMesh.h"
#include "Texture.h"

#define	MAX_GROUND_POINTS 60	// maximum number of grounds points

#ifdef WIN32
#ifdef _EXPORTING_GR
#define DLLENTRY_GR __declspec(dllexport)
#else
#define DLLENTRY_GR __declspec(dllimport)
#endif
#else
#define DLLENTRY_GR
#endif

typedef	double Vector2[2] ;


enum pgroundActuatorParms
{
	pDynamic,
	pGeometry,
	pLight,
	pColor1,
	pColor2,
	pTexture
};

class DSystem;

class DLLENTRY_GR myPlane {
public:
  double A ;
  double B ;
  double C ;
  double D ;

  double applyOn(Vector	p) { return (A*p[0]+B*p[1]+C*p[2]+D ) ;	};
} ;

class DLLENTRY_GR PlaneGround : public DActuator {
public:
  myPlane plane	;
  int npoints ;
  double m_stiffness  ;	// stiffness ;
  double m_damping  ;	// damping ;
  double m_friction ;
  float	am_dif[4] ;
  GLfloat	color1[4] ;
  GLfloat	color2[4] ;
  double ShadowMatrix[16] ;
  int stencil ;
  Texture texture ;
  int textureMode ;

  Vector2 points[MAX_GROUND_POINTS][2] ;
  double slope[MAX_GROUND_POINTS] ;
  QuadMesh qm ;

  PlaneGround()	;
  ~PlaneGround() ;
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  PlaneGround(double x1, double	y1, double z1, double x2, double y2, double z2,	int nx,	int nz)	;
 
  void ResolveForce(DSystem *sys, DSimulator *sim) ;
  void output(int mode)	;
  void bindCommands(Tcl_Interp *interp,	ClientData data, int noDisplay=0) { return ;} ;
  void genGroundMesh(Vector2 *gpoints, int n, int m);
  void genGroundMesh2(Vector2 *gpoints,	int n);
  int linkVariables(Tcl_Interp *interp)	;
  void unLinkVariables(Tcl_Interp *interp) ;
  BoundingBox *calcBoundingBox(BoundingBox *box);
  void calcShadowMatrices(DLight	*l) ;
  int changeGeometry(double x1,double y1, double z1, double x2,	double y2, double z2,
		     double x3,double y3, double z3, double x4,	double y4, double z4,
		     int nx, int nz) ;
  void ExertLoad(DSystem *ao,	double time, double dt,	double *state, double *dstate) ;
  //  void ExertLoadGen(DSystem *sys, DSimulator *sim)  ;
  // void ExertLoadBackTime(DSystem *ao,	double time, double dt,	double *state, double *dstate) ;
  //void ExertLoadOld(DSystem *ao,	double time, double dt,	double *state, double *dstate) ;
  int commandPlugIn(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv)	;
  int set(Tcl_Interp *interp, int argc,	char **argv);

  int initInterface(Tcl_Interp *interp)	;
  int save(char	*) ;
  int save(FILE	*) ;
  int PointInBoundary(Vector point) ;
  double *GetNormal(Vector v) { 
      v[0] = plane.A ; v[1] = plane.B ;
      v[2] = plane.C ;
      return &v[0]; 
  } ;
} ;



#endif





