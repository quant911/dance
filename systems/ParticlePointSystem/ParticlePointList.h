#ifndef ParticlePointList_h
#define ParticlePointList_h

class ParticlePoint ;

class DLLEXPORT PListElement {
public:
  PListElement(ParticlePoint *p) ;
  ~PListElement() ;
  ParticlePoint *m_particle ;
  PListElement *m_next ;
  ParticlePoint *GetParticle(void) { return m_particle ; } ;
  void SetParticle(ParticlePoint *p) { m_particle = p ;} ;
} ;

class DLLEXPORT ParticlePointList {
public:
  ParticlePointList() ;
  ~ParticlePointList() ;

  int m_numElements ;
  PListElement *m_first ;
  PListElement *m_last ;
  int add(ParticlePoint *p);
  int remove(PListElement *p);
  int removeDead(double time, double lifeTime) ;
  inline int size() { return m_numElements ; };

  void output(int mode) ;

} ;


#endif
