#ifndef	_KinematicActuator
#define	_KinematicActuator

#include "DActuator.h"

class AnimationSequence ;

class KinematicActuator : public DActuator {
private:
  int m_show_time ;
  int m_PingPong;
  int m_direction;
  int m_interpolation ;
  int m_isPlaying ;
  int m_isOffsetted ;

  double *m_objectState ;
  Vector m_offset ;
  Vector m_labelPos ;
  GLfloat m_labelCol[3] ;
  int m_labelSize ;
  DanceObject *danceObj ;
  // void applyState(double *qpos, SdfastSimul *sim) ;
  
public:
  KinematicActuator();
  ~KinematicActuator();

  int InsertKeyFrame(void) ;
  int InsertKeyFrameSdfast(int stateSize, double *state) ;
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  void output(int mode);
  void ExertLoad(DSystem *ao, double time, double dt,
		 double *state, double *dstate);
  void print(void);
  void saveScript(char *)	;
  void saveScript(FILE *)	;
  int commandPlugIn(ClientData clientData, Tcl_Interp *interp,
		    int argc, char	**argv)	;
  int set(Tcl_Interp *interp, int argc, char **argv) ;
  int initInterface(Tcl_Interp *interp)	;
  int linkVariables(Tcl_Interp *interp)	;
  void unLinkVariables(Tcl_Interp *interp) ;
  void ShowNextKeyFrame(void) ;
  int Record(Tcl_Interp *interp, int argc, char **argv) ;
  int Delete(Tcl_Interp *interp, int argc, char **argv) ;
  int ShowKeyFrame(Tcl_Interp *interp, int argc, char **argv) ;
  void ShowKeyFrame(void) ;

  void Play(int argc, char *argv[]) ;
  
  int IdleCB(void) ;		// inherited from DanceObject

  char m_animFileName[MAX_LINE] ;
  int m_recording ;
  AnimationSequence m_animSeq ;
  double m_time ;
  double m_recordTimeStep ;
  double m_playTimeStep ;
  double m_last_record_time ;
 };


#endif

