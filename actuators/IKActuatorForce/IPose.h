#ifndef	_IPose_h_
#define	_IPose_h_ 1

#define	QDIMM 100

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct CtrPrm {
  double v ;
  double ks ;
  double kd ;
} CtrPrm ;

class DLLEXPORT IPose {
public:
  IPose(void);
  IPose(int id, int nparam, CtrPrm *q, double transTime) ;
   void Save(FILE *fp) ;

  
 void SetStartTime(double time) { m_startTime = time ;} ;
  double GetStartTime(void) { return m_startTime ;} ;
  double GetTransTime(void) { return m_transTime ; } ;
  void SetTransTime(double t) { m_transTime = t ;} ;
  IPose *GetNext(void) { return m_next ;} ;
  int GetNextID(void) { return m_nextID ;} ;
  int GetID(void) { return m_id ;} ;
  CtrPrm *GetParams(void) { return m_q ;} ;
  void SetID(int id) { m_id = id;} ;
  void SetNextID(int id) { m_nextID = id ;} ;
  void SetNext(IPose *p) { m_next = p ;} ;
  int Load(FILE *fp) ;
  
private:
  int	m_nparams ;
  int	m_id ;		// simpler counter for now
  
  CtrPrm m_q[QDIMM] ;
  double m_transTime ;
  double m_startTime ;		// when	the pose started to be the current one
  IPose *m_next ;	// next	pose to	move to
  int m_nextID ;
} ;

#endif

