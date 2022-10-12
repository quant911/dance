// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pendlib.c function prototypes

void penderror(int *routine, int *errnum);
void pendprinterr(FILE *fnum);
void pendclearerr(void);
void pendseterr(int routine, int errnum);
void pendldudcomp(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d);
void pendldubsl(int n, int na, int *map, double *l, double *b, double *x);
void pendldubsd(int n, int na, int *map, double *d, double *b, double *x);
void pendldubsu(int n, int na, int *map, double *l, double *b, double *x);
void pendldubslv(int n, int na, int *map, double *work, double *l, double *d, double *b, double *x);
void pendlduslv(int n, int na, int *map, double tol, double *work1, double *work2, double *m, double *b, double *l, double *d, double *x);
void pendqrdcomp(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w, double *qraux, int *jpvt);
void pendqrsl(int nr, int nc, int nra, int nca, int *mapr, int *mapc, int k, double *work, double *w, double *qraux, double *b, double *x);
void pendqrbslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, double *work, int *iwork, double *w, double *qraux, int *jpvt, double *b, double *x, int *rank);
void pendqrslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, int *jpvt, double *qraux, double *work, int *iwork, double *w, double *b, double *x, int *rank);
void pendlsslv(int nr, int nc, int nra, int nca, int ndes, int *mapr, int *mapc, double tol, double *dw, double *rw, int *iw, double *w, double *b, double *x);
void pendcalcerrs(double *fval, int nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm);
void pendadjvars(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double tderr, double rtol, int *fcnt, double *newvars, double *newerrs);
void pendcalcjac(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int *lock, double delta, double *fval, double *ftmp, double *jw, int *fcnt, double *scale);
void pendroot(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol, int maxeval, double *jw, double *dw, double *rw, int *iw, double *fret, int *fcnt, int *err);
void pendrk4m(void (*func) (double,double *,double *,double *,int *), double time, double *st, double *dst0, double *param, double step, double *nst, int neq, double *work, double *errs, double *maxerr, int *which);
void pendfinteg(void (*func) (double,double *,double *,double *,int *), double *time, double *st, double *dst, double *param, double step, int neq, double *work, double *errest, int *status);
void pendvinteg(void (*func) (double,double *,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int neqin, double tol, double *work, int *err, int *which);
void penddc2ang(double (*dircos)[3], double *a1, double *a2, double *a3);
void penddc2quat(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4);
void pendang2dc(double a1, double a2, double a3, double (*dircos)[3]);
void pendquat2dc(double ie1, double ie2, double ie3, double ie4, double (*dircos)[3]);
double pendvdot(double *ivec1, double *ivec2);
double pendvnorm(double *ivec);
void pendvcopy(double *ivec, double *ovec);
void pendvset(double sclr1, double sclr2, double sclr3, double *ovec);
void pendvadd(double *ivec1, double *ivec2, double *ovec);
void pendvsub(double *ivec1, double *ivec2, double *ovec);
void pendvmul(double sclr, double *ivec, double *ovec);
void pendvaxpy(double sclr, double *ivec1, double *ivec2, double *ovec);
void pendvcross(double *ivec1, double *ivec2, double *ovec);
void pendvrot(double *ivec, double *rvec, double theta, double *ovec);
void pendprerrmsg(FILE *fnum, int routine, int errnum);
void pendserialno(int *serno);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pendlib.c function prototypes.

