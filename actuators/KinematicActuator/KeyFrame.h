#ifndef KeyFrame_h
#define KeyFrame_h

static const int MAX_NUM_PARAM = 400 ;

class KeyFrame {
public:
  KeyFrame() ;
  KeyFrame(double time, int n, double *p) ;
  ~KeyFrame() ;
  int m_nparam ;
  double *m_param ;
  KeyFrame *m_next ;
  KeyFrame *m_previous ;
  double m_time ;

  double GetTime() { return m_time ;} ;
  void SetTime(double t) { m_time = t ;} ;
  void Save(FILE *fp) ;
  int Read(FILE *fp) ;
} ;

#endif
