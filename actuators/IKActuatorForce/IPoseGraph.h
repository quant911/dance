#ifndef _IPoseGraph_
#define _IPoseGraph_

#include <stdio.h>
#include "IPose.h"

const int MAX_NPOSES = 50 ;

class DLLEXPORT IPoseGraph {
public:
  IPoseGraph() ;
  ~IPoseGraph() ;
  
  void DeletePoses(void) ;
  void Save(char *fname) ;
  void Save(FILE *fp) ;
  void Load(char *fname) ;
  void Load(FILE *fp) ;
  void SetStartTime(double time) ;
  CtrPrm *GetParams(double time) ;
  void Add(int nparam, CtrPrm *param, double transTime) ;
  void Add(int nparam, CtrPrm *param, double transTime, double currentTime) ;
  void Add(IPose *p) ;
  IPose *GetNext(double time) ;
  void InitSimul(double time) {m_lastTime = -1; m_current = m_first ;};
private:
  IPose *m_first ;
  IPose *m_last ;
  IPose *m_current ;
  double m_lastTime ; // last time we saved a pose while simulating
  int m_nposes ;
  IPose *m_poses[MAX_NPOSES] ;
} ;

#endif
