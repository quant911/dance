#ifndef DSystem_h
#define DSystem_h 1

#include "defs.h"
#include "DanceObject.h"
#include "PlugIn.h"
#include "SimulatorEvents.h"
class BoundingBox ;
class DSimulator ;
class MonitorPoints ;

class DLLENTRY DSystem : public PlugIn {
public:
  DSystem() ;
  virtual ~DSystem() ;

  // If TRUE the system is begin simulated
  int IsSimul(void) { return isSimul ;} ;

  virtual DSystem *GetGroup(int index) { return NULL ; } ;
  virtual DSystem *GetGroup(char *id) { return NULL ;} ;
  virtual int GetNumGroups(void) { return 0 ; } ;
  virtual double GetGroupMass(int id) { return 0; } ;
  /** returns the index of the first controllable dof in the state vector */
  virtual int GetIndxFirstConDof(void) { return 0 ; } ;

  virtual void Interact(Event *event) {	return ; };
  virtual int InteractStart(Event *event) { return 0 ; };
  virtual int InteractEnd(Event *event) {return 0 ; };
  virtual int KeyboardCB( unsigned char key, int x, int y ) { return 0 ; } ;
  virtual int PassiveMotionCB(DView *view, int x, int y) { return 0 ;} ;

  /** returns a structure of monitor points */
  virtual MonitorPoints *GetMonitorPoints(void) { return NULL ;} ;
  /** Used to build and automatically link in an associated simulator */
  virtual void BuildAndLinkSimulator(void) { return ; } ;
  /** must be Called by the DSimulator::Start proc to initialize the system for simulation */
  void InitSimulationBase(double time, DSimulator *sim) { isSimul = TRUE ; InitSimulation(time, sim) ;} ;
  virtual int InitSimulation(double time, DSimulator *sim) { return TCL_OK ;} ;
  /** must be Called by the DSimulator::Step */
  void BeforeSimStepBase(double time, DSimulator *sim) 
		{ m_events.process(interpreter, time); BeforeSimStep(time, sim);} ;
  virtual int BeforeSimStep(double time, DSimulator *sim) { return TCL_OK; } ;
  /** must be Called by the DSimulator::Step */
  void AfterSimStepBase(double time, DSimulator *sim) { AfterSimStep(time, sim) ;} ;
  virtual int AfterSimStep(double time, DSimulator *sim) { return -1 ; } ;
  /** must be Called by the DSimulator::Step */
  void AtEndSimulBase(double time, DSimulator *sim) { isSimul = FALSE; AtEndSimul(time, sim);} ;
  virtual int AtEndSimul(double time, DSimulator *sim) { return TCL_OK ;} ;
  
  virtual BoundingBox *calcBoundingBox(BoundingBox *b) {return NULL ; } ;
  virtual int commandPlugIn(ClientData clientData, Tcl_Interp 
			    *interp, int argc, char **argv) { return TCL_OK;}; 
  
  DSimulator *simulator ;
  int	isSimul	;		// shows if the	object is under	simulation
  int	isPlayback ;		// shows if the	object is under	playback
  SimulatorEvents m_events ;

protected:

  int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
} ;

#endif
