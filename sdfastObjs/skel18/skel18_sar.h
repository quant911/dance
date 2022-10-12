// BEGIN  function prototypes

void skel18posfunc(double *vars, double *param, double *resid);
void skel18velfunc(double *vars, double *param, double *resid);
void skel18statfunc(double *vars, double *param, double *resid);
void skel18stdyfunc(double *vars, double *param, double *resid);
void skel18motfunc(double time, double *state, double *dstate, double *param, int *status);
void skel18assemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
void skel18initvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
void skel18static(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
void skel18steady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
void skel18motion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err);
void skel18fmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err);

// END of /homes/a/pfal/danceMulti/sdfastObjs/skel18/skel18_sar.c function prototypes.

