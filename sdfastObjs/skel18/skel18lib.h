// BEGIN  function prototypes

void skel18error(int *routine, int *errnum);
void skel18printerr(FILE *fnum);
void skel18clearerr(void);
void skel18seterr(int routine, int errnum);
void skel18ldudcomp(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d);
void skel18ldubsl(int n, int na, int *map, double *l, double *b, double *x);
void skel18ldubsd(int n, int na, int *map, double *d, double *b, double *x);
void skel18ldubsu(int n, int na, int *map, double *l, double *b, double *x);
void skel18ldubslv(int n, int na, int *map, double *work, double *l, double *d, double *b, double *x);
void skel18lduslv(int n, int na, int *map, double tol, double *work1, double *work2, double *m, double *b, double *l, double *d, double *x);
void skel18qrdcomp(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w, double *qraux, int *jpvt);
void skel18qrsl(int nr, int nc, int nra, int nca, int *mapr, int *mapc, int k, double *work, double *w, double *qraux, double *b, double *x);
void skel18qrbslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, double *work, int *iwork, double *w, double *qraux, int *jpvt, double *b, double *x, int *rank);
void skel18qrslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, int *jpvt, double *qraux, double *work, int *iwork, double *w, double *b, double *x, int *rank);
void skel18lsslv(int nr, int nc, int nra, int nca, int ndes, int *mapr, int *mapc, double tol, double *dw, double *rw, int *iw, double *w, double *b, double *x);
void skel18calcerrs(double *fval, int nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm);
void skel18adjvars(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double tderr, double rtol, int *fcnt, double *newvars, double *newerrs);
void skel18calcjac(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int *lock, double delta, double *fval, double *ftmp, double *jw, int *fcnt, double *scale);
void skel18root(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol, int maxeval, double *jw, double *dw, double *rw, int *iw, double *fret, int *fcnt, int *err);
void skel18rk4m(void (*func) (double,double *,double *,double *,int *), double time, double *st, double *dst0, double *param, double step, double *nst, int neq, double *work, double *errs, double *maxerr, int *which);
void skel18finteg(void (*func) (double,double *,double *,double *,int *), double *time, double *st, double *dst, double *param, double step, int neq, double *work, double *errest, int *status);
void skel18vinteg(void (*func) (double,double *,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int neqin, double tol, double *work, int *err, int *which);
void skel18dc2ang(double (*dircos)[3], double *a1, double *a2, double *a3);
void skel18dc2quat(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4);
void skel18ang2dc(double a1, double a2, double a3, double (*dircos)[3]);
void skel18quat2dc(double ie1, double ie2, double ie3, double ie4, double (*dircos)[3]);
double skel18vdot(double *ivec1, double *ivec2);
double skel18vnorm(double *ivec);
void skel18vcopy(double *ivec, double *ovec);
void skel18vset(double sclr1, double sclr2, double sclr3, double *ovec);
void skel18vadd(double *ivec1, double *ivec2, double *ovec);
void skel18vsub(double *ivec1, double *ivec2, double *ovec);
void skel18vmul(double sclr, double *ivec, double *ovec);
void skel18vaxpy(double sclr, double *ivec1, double *ivec2, double *ovec);
void skel18vcross(double *ivec1, double *ivec2, double *ovec);
void skel18vrot(double *ivec, double *rvec, double theta, double *ovec);
void skel18prerrmsg(FILE *fnum, int routine, int errnum);
void skel18serialno(int *serno);

// END of /homes/a/pfal/danceMulti/sdfastObjs/skel18/skel18lib.c function prototypes.

