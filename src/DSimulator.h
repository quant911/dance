#ifndef DSimulator_h
#define DSimulator_h

#include "defs.h"
#include "vector.h"
#include "PlugIn.h"
#include "DanceObjectRefList.h"
#include "DSystem.h"


#define WORLDFRAME -1


/**
 * This is the DSimulator class that serves as the base class API for simulators
 * @author Victor Ng-Thow-Hing
 * @author Petros Faloutsos
 * @version $Id: DSimulator.h,v 1.22 2000/08/23 03:25:51 pfal Exp $
 * @see PlugIn
 */
class DLLENTRY DSimulator: public PlugIn {
public:
    DSimulator () ;
    virtual ~DSimulator()  ;

    // Initialization functions
    virtual void SetTime(double currentTime) = 0 ;
    virtual double GetTime(void) = 0 ; 
    // Advance state function
    void StepBase(double destinationTime) ;
    virtual int Step(DSystem *sys, double destinationTime) = 0 ; 

    int StartBase(double time) ;
    // initialization function for every run of the simulation
    virtual int Start(double time) { NotImpl("Start(time)") ; return 0 ; } ; 
  
    int StopBase(void) ;
    // clean up after simulation is stopped
    virtual int Stop(void) { NotImpl("Stop") ; return 0 ; } ;
    
    // State functions
    virtual int GetStateSize(void) { NotImpl("GetStateSize") ; return 0 ; } ;
    // returns -1 on error else non zero
    virtual int SetState(int index, double value) { NotImpl("SetState") ; return 0 ; } ;  
    virtual int SetState(int startIndex, int size, double *q) 
                { NotImpl("SetState") ; return 0 ;} ;
    virtual int SetStateFromObjectState(DSystem *sys) { return 0; } ;
    virtual int SetObjectStateFromState(DSystem *sys) { return 0; } ;
    virtual double GetState(int index) { NotImpl("GetState") ; return MINFLOAT ; } ;
    // fast access, returns the pointer
    virtual double *GetState(void) { NotImpl("GetState") ; return NULL ; } ;
    virtual double *GetState(int startIndex, int size, double *q)  // q must be allocated
                   { NotImpl("GetState") ; return NULL ; } ;       // by the calller
    virtual int GetVelSize(void) { NotImpl("GetVelSize") ; return 0 ; } ;
    // returns -1 on error else non zero
    virtual int SetVel(int index, double value) { NotImpl("SetVel") ; return 0 ; } ;   
  
    virtual int SetVel(int startIndex, int size, double *q) { NotImpl("SetVel") ; return 0 ; } ;
    virtual double GetVel(int index) { NotImpl("GetVel") ; return MINFLOAT ; } ; 
    // fast access, returns the pointer
    virtual double *GetVel(void) { NotImpl("GetVel") ; return NULL ; } ;
    // q must be allocated by the calller
    virtual double *GetVel(int startIndex, int size, double *q) 
                   { NotImpl("GetVel") ; return NULL ; } ;
  

    virtual double GetAcc(int index) { NotImpl("GetAcc") ; return MINFLOAT ; } ;
    // fast access, returns the pointer
    virtual double *GetAcc(void) { NotImpl("GetAcc") ; return NULL ; } ;	
    // q must be allocated by the calller
    virtual double *GetAcc(int startIndex, int size, double *q) 
                   { NotImpl("GetAcc") ; return NULL ; } ; 
    virtual int GetIndex(int group, int subgroup) { NotImpl("GetIndex") ; return 0; };
    virtual int GetIndex(int argc, char **argv) { NotImpl("GetIndex") ; return 0; } ; // generic
    
   // Force functions
  
    virtual void FieldForce(double *force) {NotImpl("FieldForce") ; } ;
    // force vector and point relative to the given part of the object
    virtual void PointForce(int group, double *point, double *force) 
                 { NotImpl("PointForce") ; };
  // point and force in world coordinates
    virtual void PointForce(DSystem *sys, double *pointWorldCoord, double *force){ NotImpl("PointForce") ;} ;
  // the most general form of point force
    virtual void PointForce(int argc, char *argv[]){ NotImpl("PointForce") ;} ;  
     
    virtual void BodyTorque(int group, double *torque) { NotImpl("BodyTorque") ; } ;
    virtual void GeneralizedForce(int coord, double force) 
            { NotImpl("GeneralizedForce(int coord, double force") ; } ;
    virtual void GeneralizedForce(int *index, double *force, int size) 
            { NotImpl("GeneralizedForce(int *index, double *force, int size)") ; };
    virtual void GeneralizedForce(double *Q) { NotImpl("GeneralizedForce(double *Q)") ; } ;
    virtual void GeneralizedForce(int group, int subgroup, double force) 
            { NotImpl("GeneralizedForce") ;};

    // transformation utilities
   virtual void GetVel(DSystem *sys, double *localPoint, double *vel) 
         { NotImpl("GetVel") ; return ; } ;
    virtual void GetVel(int group, double *point, double *vel) 
                 { NotImpl("GetVel") ; } ;
    virtual void GetAcc(int group, double *point, double *acc)
                 { NotImpl("GetAcc")  ; } ;
    virtual int GetAcc(DSystem *sys, double *localPoint, double *acc) 
          { NotImpl("GetAcc") ; return 0 ; } ;
    
    virtual int GetPosition(DSystem *sys, double *localPoint, double *position)
       { NotImpl("GetPosition") ; return 0 ; } ;
    virtual int GetPosition(int group, double *localPoint, double *position) 
                { NotImpl("GetPosition") ; return 0 ; } ;
    virtual int GetOrientation(DSystem *sourceSystem, double *sourceVec, 
			       DSystem *targetSystem, double *targetVec) 
    { NotImpl("GetOrientation") ; return 0;};
    virtual int GetOrientation(int sourceGroup, double *localVec, int targetGroup, 
			       double *rotated)
                { NotImpl("GetOrientation") ; return 0 ; } ;
    virtual int Transform(int argc, char **argv) // generic
                { NotImpl("Tranform") ; return 0; } ;

    virtual int  commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
          { NotImpl("commandPlugIn") ; return TCL_OK ; } ;
  /** adds as system in the list of simulated systems */
  void AddSystem(DSystem *sys) ;
  /** remove a system from the list of simulated systems */
  void RemoveSystem(DSystem *sys) { if( sys ) m_systems.remove(sys->getName()) ;} ;
protected:
  int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) ;
  void ApplyActuatorForces(DSystem *sys, double time, double dt, double *state, 
			   double *dstate) ;
  void NotImpl(char *funcName) ;
  DanceObjectRefList m_systems ;
  /** if true the base code the function xxxxBase is ignored and corresponding
      virtual functions are called immediately */
  int m_ignoreBaseFlag ;
  int m_initSystemsFlag ;
  int m_initActuatorsFlag ;
} ;
    
#endif
