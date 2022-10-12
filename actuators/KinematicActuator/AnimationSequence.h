#ifndef AnimationSequence_h
#define AnimationSequence_h

#include "defs.h"

class KeyFrame ;

class Legend {
public:
  Legend() { index = 0 ; name[0] = '\0' ;} ;

  char name[MAX_LINE] ;
  int index ;
} ;

class AnimationSequence {
public:
  AnimationSequence() ;
  ~AnimationSequence() ;
  
  void Clear() ;
  int GetSize() { return m_nKeyFrames ;} ;
  int InsertKeyFrame(double time, int nparam, double *params) ;
  void InsertKeyFrame(KeyFrame *kf) ;
  void DeleteKeyFrame(double time) ;
  void DeleteKeyFrame(int index) ;
  void DeleteKeyFrame(KeyFrame *kf) ;
  void ReplaceKeyFrame(KeyFrame *kf_old, KeyFrame *kf_new) ;
  int Read(char *fname) ;
  int Read(FILE *fp) ;
  int Save(char *fname) ;
  int Save(FILE *fp) ;
  void print(void) { Save(stdout) ;} ;
  void DeleteKeyFrames(void) ;
  int ReadKeyFrames(FILE *fp) ;
  int ReadLegend(FILE *fp) ;
  void DeleteLegend(void) ;
  double GetStartTime(void) ;
  double GetEndTime(void) ;
  void InterpolateKeyFrames(KeyFrame *kf1, KeyFrame *kf2, double time,
					     double *paramInt) ;
  int GetKeyFrame(double time, double *params, int interpolation) ;
  KeyFrame *GetKeyFrame(double time) ;

  int m_nKeyFrames ;
  int m_nLegends ;
  KeyFrame *m_firstKeyFrame ;
  KeyFrame *m_lastKeyFrame ;

  Legend *m_legends ;
} ;



#endif
