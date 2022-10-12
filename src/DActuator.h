#ifndef	_ACTUATOR_CLASS_
#define	_ACTUATOR_CLASS_

#include "defs.h"
#include "PlugIn.h"
#include "BoundingBox.h"
#include "DSystem.h"


class View ;

class DLLENTRY AppliedUnit {
    public:
	int linkNo;
	int jointNo;
	double pointOnObj[3]; // In object coordinates
	double forceOnObj[3]; // In object coordinates
	int index;
	int modifier;
	AppliedUnit *next;
};

class DLLENTRY AppliedObject {
      public:
	DanceObject *ao;
	AppliedUnit *unitList;
	AppliedObject *next;
};


#define	MAXAPPLIEDOBJS 256

class DLLENTRY DActuator: public PlugIn {
protected:
  int applyAllObjects;
  AppliedObject *applyList;
  int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);

public:
   virtual double GetDistance(double point[3], double closest[3]) { return -1.0; }

  int controlled;
  
  DActuator();
  virtual ~DActuator() { return ;} ;
  
  int IsInApplyList(DanceObject *sys) ;
  void removeAppliedObject(DanceObject *sys) ;
  virtual void setAppliedObject(DanceObject *sys, int linkNo, int jointNo);
  void setAppliedObject(DanceObject *sys, int linkNo,
  double pointOnObj[3], int index	= -1, int modifier = -1);
  inline void setAppliedObject(DanceObject *sys) {setAppliedObject(sys,-1,-1);};
  inline void setAppliedAllObjects(void) {applyAllObjects = 1;};
  virtual void BeforeStep(DSystem *sys, double time) { return; };
  virtual void AfterStep(DSystem *sys, double time) { return; };

  
  virtual void ExertLoad(DSystem *sys, double time, double dt,
			       double *state, double *dstate) { return; };
  virtual void InitSimul(DSystem *sys, double time) ;
  virtual void AtEndSimul(DSystem *sys, double time) { return ; };
  virtual void afterObjectUpdate(DanceObject *sys) {return;};
 
};
#endif
