// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_sar.c function prototypes

void pendposfunc(double *vars, double *param, double *resid);
void pendvelfunc(double *vars, double *param, double *resid);
void pendstatfunc(double *vars, double *param, double *resid);
void pendstdyfunc(double *vars, double *param, double *resid);
void pendmotfunc(double time, double *state, double *dstate, double *param, int *status);
void pendassemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
void pendinitvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
void pendstatic(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
void pendsteady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
void pendmotion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err);
void pendfmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_sar.c function prototypes.

