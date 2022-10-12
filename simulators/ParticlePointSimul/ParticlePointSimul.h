#ifndef	ParticlePointSimul_h
#define	ParticlePointSimul_h 1

#include <stdio.h>
#include "defs.h"
#include "DSimulator.h"

class DSystem ;

class DLLEXPORT ParticlePointSimul : public DSimulator	{
public:
  ParticlePointSimul() ;
  ParticlePointSimul(DSystem *) ;
  ~ParticlePointSimul() { return ; }  ;
  
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  
  int Start(double time) ;
  int Step(DSystem *sys, double destTime) ; 
  int Stop(void) ;
  
  int step(double destTime) ; 
  int commandPlugIn(ClientData clientData, Tcl_Interp 
		    *interp, int argc, char **argv) ;
 
  void SetTime(double t) { m_time = t ;} ;
  double GetTime(void) { return m_time ;} ;
private:
  DSystem *m_sys ;
  double m_dt ;
  double m_time ;

  double m_ythreshold ;
  double m_fadeFactor ;
} ;

#endif
