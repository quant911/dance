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

#define NBOD 2
#define NJNT 2
#define NDOF 2
#define NLOOP 0
#define NLDOF 0
#define NQ 2
#define NU 2
#define NLQ 0
#define NLU 0
#define NC 2
#define NLC 0
#define NPRESC 2
#define NUSERC 0

// User supplied sdfast functions.
extern  DLLIMPORT void penduforce(double t, double *q, double *u);
extern  DLLIMPORT void pendumotion(double t, double *q, double *u);
extern  DLLIMPORT void penduperr(double t, double *q, double *err);
extern  DLLIMPORT void penduverr(double t, double *q, double *u, double *err);
extern  DLLIMPORT void penduaerr(double t, double *q, double *u, double *udot, double *err);
extern  DLLIMPORT void penduconsfrc(double t, double *q, double *u, double *mults);
