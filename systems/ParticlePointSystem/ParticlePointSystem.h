#ifndef ParticlePointSystem_h
#define ParticlePointSystem_h 1

#include "defs.h"
#include "DSystem.h"
#include "ParticlePoint.h"
#include "ParticlePointList.h"

class BoundingBox ;


class DLLEXPORT ParticlePointSystem : public DSystem {
public:
  ParticlePointSystem() ;
  ~ParticlePointSystem() { return ;}  ;
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  BoundingBox *calcBoundingBox(BoundingBox *b) ;
  
  // These three overid methods in DanceObject
  void output(int mode);
  int GetStateSize(void) { return 0 ; } ;
  void GetState(double *state) { return ;} ;
  
  // Overides the on in PlugIn
  int commandPlugIn(ClientData clientData, Tcl_Interp 
		    *interp, int argc, char **argv) ;
  
  
  int BeforeSimStep(double time, DSimulator *sim) ; // overriding the on in DSystem

  // own stuff
  double m_lifeTime ;
  double m_birthRate ;		// particles per second
  ParticlePointList m_plist ;
  double m_posOffset[3] ;
  double m_initVel[3] ;
  double m_zMin ;
  double m_zMax ;
  double m_xMax ;
  double m_xMin ;
  double m_y ;
  double m_rotX ;
  double m_rotZ ;
  double m_length2 ;

  int ParticleGenerator(double time, double dt) ;

} ;


#endif
