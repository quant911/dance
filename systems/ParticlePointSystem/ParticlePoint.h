#ifndef ParticlePoint_h
#define ParticlePoint_h 1

#include "defs.h"

class DLLEXPORT ParticlePoint {
public:
  ParticlePoint() ;
  ParticlePoint(double mass, double time) ;

  double m_mass ;
  double m_pos[3] ;
  double m_vel[3] ;
  double m_birthTime ;
  double m_rotX ;			// not part of the state
  double m_rotZ ;			// not part of the state
  double m_length2 ;

  int GetStateSize(void) { return 3 ; } ;
  void GetState(double *p) { 
      p[0] = m_pos[0] ; p[1] = m_pos[1] ; p[2] = m_pos[2] ;
  } ;
  void GetVel(double *v) { 
      v[0] = m_vel[0] ; v[1] = m_vel[1] ; v[2] = m_vel[2] ;
  } ;
  void UpdateState(double *p) { 
      m_pos[0] = p[0] ; m_pos[1] = p[1] ; m_pos[2] = p[2] ;
  } ;
  void SetVel(double *v) {
      m_vel[0] = v[0] ; m_vel[1] = v[1] ; m_vel[2] = v[2] ;
  } ;

  inline void SetBirthTime(double t) { m_birthTime = t ;} ;
  inline double GetBirthTime(void) { return m_birthTime ; } ;
  
  void output(int mode) ;

} ;

#endif
