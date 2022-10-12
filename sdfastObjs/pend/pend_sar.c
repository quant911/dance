#ifdef __cplusplus
extern "C" {
#endif
/*
Generated 27-Apr-2000 15:43:58 by SD/FAST, Kane's formulation
Generated 27-Apr-2000 15:43:58 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
#include <math.h>
#include "sdfast.h"

/* These routines are passed to pendroot. */

void pendposfunc(double *vars, double *param, double *resid)
{
    int i;
    double pos[2],vel[2];

    for (i = 0; i < 2; i++) {
        vel[i] = 0.;
    }
    pendang2st(vars,pos);
    pendstate(param[0],pos,vel);
    pendumotion(param[0],pos,vel);
    pendperr(resid);
}

void pendvelfunc(double *vars, double *param, double *resid)
{

    pendstate(param[2],param,vars);
    pendumotion(param[2],param,vars);
    pendverr(resid);
}

void pendstatfunc(double *vars, double *param, double *resid)
{
    double pos[2],qdotdum[2];

    pendang2st(vars,pos);
    pendstate(param[2],pos,param);
    pendumotion(param[2],pos,param);
    penduforce(param[2],pos,param);
    pendperr(resid);
    pendderiv(qdotdum,&resid[2]);
}

void pendstdyfunc(double *vars, double *param, double *resid)
{
    double pos[2],qdotdum[2];

    pendang2st(vars,pos);
    pendstate(param[0],pos,&vars[2]);
    pendumotion(param[0],pos,&vars[2]);
    penduforce(param[0],pos,&vars[2]);
    pendperr(resid);
    pendverr(&resid[2]);
    pendderiv(qdotdum,&resid[4]);
}

/* This routine is passed to the integrator. */

void pendmotfunc(double time, double *state, double *dstate, double *param, int *status)
{
    double err[2];
    int i;

    pendstate(time,state,&state[2]);
    pendumotion(time,state,&state[2]);
    penduforce(time,state,&state[2]);
    pendderiv(dstate,&dstate[2]);
    *status = 1;
    pendverr(err);
    for (i = 0; i < 2; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    pendperr(err);
    for (i = 0; i < 2; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

void pendassemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err)
{
    double perrs[2],param[1];
    int i;
    double jw[4],dw[32],rw[32];
    int iw[16],rooterr;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(50,42);
    }
    param[0] = time;
    pendroot(pendposfunc,state,param,2,2,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,perrs,fcnt,&rooterr);
    pendposfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs initial velocity analysis. */

void pendinitvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err)
{
    double verrs[2],param[3];
    int i;
    double jw[4],dw[32],rw[32];
    int iw[16],rooterr;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(51,42);
    }
    for (i = 0; i < 2; i++) {
        param[i] = state[i];
    }
    param[2] = time;
    pendroot(pendvelfunc,&state[2],param,2,2,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    pendvelfunc(&state[2],param,verrs);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs static analysis. */

void pendstatic(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err)
{
    double resid[4],param[3],jw[8],dw[72],rw[46];
    int iw[24],rooterr,i;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(52,42);
    }
    for (i = 0; i < 2; i++) {
        param[i] = state[2+i];
    }
    param[2] = time;
    pendroot(pendstatfunc,state,param,4,2,2,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    pendstatfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs steady motion analysis. */

void pendsteady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err)
{
    double resid[6],param[1];
    double jw[24],dw[200],rw[78];
    int iw[40],rooterr,i;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(53,42);
    }
    param[0] = time;
    pendroot(pendstdyfunc,state,param,6,4,2,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    pendstdyfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs state integration. */

void pendmotion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err)
{
    static double step;
    double work[24],ttime,param[1];
    int vintgerr,which,ferr,i;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        pendmotfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    pendvinteg(pendmotfunc,&ttime,state,dstate,param,dt,&step,4,tol,work,&
      vintgerr,&which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void pendfmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err)
{
    double work[16],ttime,param[1];
    int ferr,i;

    pendgentime(&i);
    if (i != 154358) {
        pendseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        pendmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    pendfinteg(pendmotfunc,&ttime,state,dstate,param,dt,4,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
#ifdef __cplusplus
}
#endif
