#ifndef SimulatorEvents_h
#define SimulatorEvents_h

#include <stdio.h>
#include <string.h>
#include "defs.h"

const int MAX_EVENTS = 10 ;

class DLLENTRY SimulatorEvent {
public:
  char command[256] ;
  double time ;

  SimulatorEvent() { time = -1 ; command[0] = '\0' ;} ;
  void process(Tcl_Interp *interp, double simtime);
  void print(FILE *fp = stdout) ;
  void print(Tcl_Interp *interp) ;
  void remove(void) ;
  void setEvent(double attime, char *s)  ;
  void copy(SimulatorEvent *e) { time = e->time; strcpy(command, e->command) ;} ;
} ;

class DLLENTRY SimulatorEvents {
public:
  int numEvents ;
  SimulatorEvent event[MAX_EVENTS];

  SimulatorEvents() { numEvents = 0 ;} ;
  void process(Tcl_Interp *interp, double simtime) ;
  void addEvent(Tcl_Interp *interp, double attime, char *s) ;
  void removeEvent(Tcl_Interp *interp, int index) ; 
  void print(FILE *fp) ;
  void print(Tcl_Interp *interp) ;
} ;

#endif
