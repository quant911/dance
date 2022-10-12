#ifdef __cplusplus
extern "C" {
#endif
/*
Generated 23-Nov-1999 14:32:48 by SD/FAST, Kane's formulation
Generated 23-Nov-1999 14:32:48 by SD/FAST, Kane's formulation
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

/* These routines are passed to skel18root. */

void skel18posfunc(double *vars, double *param, double *resid)
{
    int i;
    double pos[38],vel[37];

    for (i = 0; i < 37; i++) {
        vel[i] = 0.;
    }
    skel18ang2st(vars,pos);
    skel18state(param[0],pos,vel);
    skel18perr(resid);
}

void skel18velfunc(double *vars, double *param, double *resid)
{

    skel18state(param[38],param,vars);
    skel18verr(resid);
}

void skel18statfunc(double *vars, double *param, double *resid)
{
    double pos[38],qdotdum[38];

    skel18ang2st(vars,pos);
    skel18state(param[37],pos,param);
    skel18uforce(param[37],pos,param);
    skel18perr(resid);
    skel18deriv(qdotdum,&resid[0]);
}

void skel18stdyfunc(double *vars, double *param, double *resid)
{
    double pos[38],qdotdum[38];

    skel18ang2st(vars,pos);
    skel18state(param[0],pos,&vars[37]);
    skel18uforce(param[0],pos,&vars[37]);
    skel18perr(resid);
    skel18verr(&resid[0]);
    skel18deriv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

void skel18motfunc(double time, double *state, double *dstate, double *param, int *status)
{

    skel18state(time,state,&state[38]);
    skel18uforce(time,state,&state[38]);
    skel18deriv(dstate,&dstate[38]);
    *status = 0;
}

/* This routine performs assembly analysis. */

void skel18assemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err)
{
    double perrs[1],param[1];
    int i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(50,42);
    }
    param[0] = time;
    skel18st2ang(state,state);
    *err = 0;
    *fcnt = 0;
    skel18posfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    skel18ang2st(state,state);
}

/* This routine performs initial velocity analysis. */

void skel18initvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err)
{
    double verrs[1],param[39];
    int i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(51,42);
    }
    for (i = 0; i < 38; i++) {
        param[i] = state[i];
    }
    param[38] = time;
    *err = 0;
    *fcnt = 0;
    skel18velfunc(&state[38],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

void skel18static(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err)
{
    double resid[37],param[38],jw[1369],dw[10952],rw[592];
    int iw[296],rooterr,i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(52,42);
    }
    for (i = 0; i < 37; i++) {
        param[i] = state[38+i];
    }
    param[37] = time;
    skel18st2ang(state,state);
    skel18root(skel18statfunc,state,param,37,37,37,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    skel18statfunc(state,param,resid);
    *fcnt = *fcnt+1;
    skel18ang2st(state,state);
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

void skel18steady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err)
{
    double resid[37],param[1],vars[74];
    double jw[2738],dw[24642],rw[925];
    int iw[444],rooterr,i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(53,42);
    }
    param[0] = time;
    skel18st2ang(state,vars);
    for (i = 0; i < 37; i++) {
        vars[37+i] = state[38+i];
    }
    skel18root(skel18stdyfunc,vars,param,37,74,37,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    skel18stdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    skel18ang2st(vars,state);
    for (i = 0; i < 37; i++) {
        state[38+i] = vars[37+i];
    }
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

void skel18motion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err)
{
    static double step;
    double work[450],ttime,param[1];
    int vintgerr,which,ferr,i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        skel18motfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    skel18vinteg(skel18motfunc,&ttime,state,dstate,param,dt,&step,75,tol,work,&
      vintgerr,&which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void skel18fmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err)
{
    double work[300],ttime,param[1];
    int ferr,i;

    skel18gentime(&i);
    if (i != 143248) {
        skel18seterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        skel18motfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    skel18finteg(skel18motfunc,&ttime,state,dstate,param,dt,75,work,errest,&
      ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
#ifdef __cplusplus
}
#endif
