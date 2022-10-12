#include <stdio.h>

#ifdef WIN32

#ifndef DLLIMPORT
#define DLLIMPORT __declspec(dllimport)
#endif
#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif

#else
#ifndef DLLIMPORT
#define DLLIMPORT
#endif
#ifndef DLLEXPORT
#define DLLEXPORT
#endif

#endif

#define NBOD 16
#define NJNT 16
#define NDOF 37
#define NLOOP 0
#define NLDOF 0
#define NQ 38
#define NU 37
#define NLQ 0
#define NLU 0
#define NC 0
#define NLC 0
#define NPRESC 0
#define NUSERC 0

// User supplied sdfast functions.
extern  DLLIMPORT void skel18uforce(double t, double *q, double *u);
extern  DLLIMPORT void skel18umotion(double t, double *q, double *u);
extern  DLLIMPORT void skel18uperr(double t, double *q, double *err);
extern  DLLIMPORT void skel18uverr(double t, double *q, double *u, double *err);
extern  DLLIMPORT void skel18uaerr(double t, double *q, double *u, double *udot, double *err);
extern  DLLIMPORT void skel18uconsfrc(double t, double *q, double *u, double *mults);
