#ifndef	DanceObject_h
#define	DanceObject_h

#include "defs.h"
#include "Event.h"

class BoundingBox ;
class DGeometry;

class DLLENTRY DanceObject {
public:
  virtual void Highlight(float r, float g, float b, float a) { return; };
  virtual void GetWorldFrame(double frame[3][3], double local[3]) {return;};
  virtual ~DanceObject() {return ;} ;

  inline char *getBaseType(void) { return &BaseType[0]; } ;
  inline char *getName(void) {	return &Name[0]	;} ;
  inline char *getFileName() {return &Filename[0];} ;
  inline char *getType(void) {	return &Type[0]	;} ;
	
  inline void setBaseType(char *type) { strcpy(BaseType,type); };
  inline void setFileName( char *filename) { strcpy(Filename,filename); };
  inline void setName(char *name) { strcpy(Name,name); };
  inline void setType(char *type) { strcpy(Type,type); };

  virtual void print(FILE *fptr) {return;};
  virtual void output(int mode=1) { return;};
  virtual int  Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) ;
  
  virtual void Interact(Event *event) {	return ; };
  virtual int InteractStart(Event *event) { return 0 ; };
  virtual int InteractEnd(Event *event) {return 0 ;};
  virtual int KeyboardCB( unsigned char key, int x, int y ) { return 0 ; } ;
  virtual int PassiveMotionCB(DView *view, int x, int y) { return 0 ;} ;

  virtual void getLocalCoord(double local[3], double world[3]) { return; };
  virtual void getWorldCoord(double world[3], double local[3]) { return; };
  virtual void getWorldVelocity(double worldvel[3], double local[3]) { return; };
  virtual void GetWorldVector(double worldve[3], double local[3]) { return; };
  virtual DGeometry *GetGeometry(void) { return NULL ;} ;
  virtual double GetState(int index) { return  MINFLOAT ;} ;

  virtual void GetState(double *state) { return ;} ;
  virtual int GetStateSize(void) { return 0 ;} ;
  virtual void GetVelocities(double *dstate) { return ;}
  virtual int GetVelocitiesSize(void) { return GetStateSize(); } ;
  virtual void UpdateState(double *state) { return ;} ;
  virtual void SetLastState(void) { return; };

  inline void Synchronize(double currentTime) { m_LocalTime = currentTime; };
  virtual int IdleCB() { return 0 ;} ;	// This routine is to be called in the
				        // dance::idleCB so that an object
					// can do something on each own  every time.
                                        // a value of 0 indicates that the object
                                        // hasn't done anything, so no need to redisplay
  virtual void AfterAllSimStep(double time, double dt) { return;} ;	// called in idleCB after all objects 
                                                        // take a step   
  virtual void BeforeAllSimStep(double time, double dt) { return ;} ;	// called in dance::idleCB before all objects take
                                                        // a simulation step
  virtual BoundingBox *calcBoundingBox(BoundingBox *) { return  NULL;} ;
protected:
  double m_LocalTime;
  	
private:
  char Filename[MAX_LINE];
  char Name[MAX_LINE] ;
  char Type[MAX_LINE] ;
  char BaseType[MAX_LINE];

} ;

#endif

