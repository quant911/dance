#ifdef __cplusplus
extern "C" {
#endif
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
#define skel18uforce (*sduforce)
extern  DLLIMPORT void skel18uforce(double t, double *q, double *u);
#define skel18umotion (*sdumotion)
extern  DLLIMPORT void skel18umotion(double t, double *q, double *u);
#define skel18uperr (*sduperr)
extern  DLLIMPORT void skel18uperr(double t, double *q, double *err);
#define skel18uverr (*sduverr)
extern  DLLIMPORT void skel18uverr(double t, double *q, double *u, double *err);
#define skel18uaerr (*sduaerr)
extern  DLLIMPORT void skel18uaerr(double t, double *q, double *u, double *udot, double *err);
#define skel18uconsfrc (*sduconsfrc)
extern  DLLIMPORT void skel18uconsfrc(double t, double *q, double *u, double *mults);
// BEGIN  function prototypes

DLLEXPORT void skel18init(void);
DLLEXPORT void skel18state(double timein, double *qin, double *uin);
DLLEXPORT void skel18qdot(double *oqdot);
DLLEXPORT void skel18u2qdot(double *uin, double *oqdot);
DLLEXPORT void skel18psstate(double *lqin);
DLLEXPORT void skel18dovpk(void);
DLLEXPORT void skel18doltau(void);
DLLEXPORT void skel18doiner(void);
DLLEXPORT void skel18dofs0(void);
DLLEXPORT void skel18domm(int routine);
DLLEXPORT void skel18dommldu(int routine);
DLLEXPORT void skel18lhs(int routine);
DLLEXPORT void skel18massmat(double (*mmat)[37]);
DLLEXPORT void skel18frcmat(double *fmat);
DLLEXPORT void skel18mfrc(double *imult);
DLLEXPORT void skel18equivht(double *tau);
DLLEXPORT void skel18fulltrq(double *udotin, double *multin, double *trqout);
DLLEXPORT void skel18comptrq(double *udotin, double *trqout);
DLLEXPORT void skel18multtrq(double *multin, double *trqout);
DLLEXPORT void skel18fs0(void);
DLLEXPORT void skel18fsmult(void);
DLLEXPORT void skel18fsfull(void);
DLLEXPORT void skel18fsgenmult(void);
DLLEXPORT void skel18fsgenfull(void);
DLLEXPORT void skel18rhs(void);
DLLEXPORT void skel18pseudo(double *lqout, double *luout);
DLLEXPORT void skel18psqdot(double *lqdout);
DLLEXPORT void skel18psudot(double *ludout);
DLLEXPORT void skel18perr(double *errs);
DLLEXPORT void skel18verr(double *errs);
DLLEXPORT void skel18aerr(double *errs);
DLLEXPORT int skel18indx(int joint, int axis);
DLLEXPORT void skel18presacc(int joint, int axis, double prval);
DLLEXPORT void skel18presvel(int joint, int axis, double prval);
DLLEXPORT void skel18prespos(int joint, int axis, double prval);
DLLEXPORT void skel18getht(int joint, int axis, double *torque);
DLLEXPORT void skel18hinget(int joint, int axis, double torque);
DLLEXPORT void skel18pointf(int body, double *point, double *force);
DLLEXPORT void skel18bodyt(int body, double *torque);
DLLEXPORT void skel18doww(int routine);
DLLEXPORT void skel18xudot0(int routine, double *oudot0);
DLLEXPORT void skel18udot0(double *oudot0);
DLLEXPORT void skel18setudot(double *iudot);
DLLEXPORT void skel18xudotm(int routine, double *imult, double *oudotm);
DLLEXPORT void skel18udotm(double *imult, double *oudotm);
DLLEXPORT void skel18deriv(double *oqdot, double *oudot);
DLLEXPORT void skel18resid(double *eqdot, double *eudot, double *emults, double *resid);
DLLEXPORT void skel18mult(double *omults, int *owrank, int *omultmap);
DLLEXPORT void skel18reac(double (*force)[3], double (*torque)[3]);
DLLEXPORT void skel18mom(double *lm, double *am, double *ke);
DLLEXPORT void skel18sys(double *mtoto, double *cm, double (*icm)[3]);
DLLEXPORT void skel18pos(int body, double *pt, double *loc);
DLLEXPORT void skel18vel(int body, double *pt, double *velo);
DLLEXPORT void skel18orient(int body, double (*dircos)[3]);
DLLEXPORT void skel18angvel(int body, double *avel);
DLLEXPORT void skel18trans(int frbod, double *ivec, int tobod, double *ovec);
DLLEXPORT void skel18rel2cart(int coord, int body, double *point, double *linchg, double *rotchg);
DLLEXPORT void skel18acc(int body, double *pt, double *accel);
DLLEXPORT void skel18angacc(int body, double *aacc);
DLLEXPORT void skel18grav(double *gravin);
DLLEXPORT void skel18mass(int body, double massin);
DLLEXPORT void skel18iner(int body, double (*inerin)[3]);
DLLEXPORT void skel18btj(int joint, double *btjin);
DLLEXPORT void skel18itj(int joint, double *itjin);
DLLEXPORT void skel18pin(int joint, int pinno, double *pinin);
DLLEXPORT void skel18pres(int joint, int axis, int presin);
DLLEXPORT void skel18stab(double velin, double posin);
DLLEXPORT void skel18getgrav(double *gravout);
DLLEXPORT void skel18getmass(int body, double *massout);
DLLEXPORT void skel18getiner(int body, double (*inerout)[3]);
DLLEXPORT void skel18getbtj(int joint, double *btjout);
DLLEXPORT void skel18getitj(int joint, double *itjout);
DLLEXPORT void skel18getpin(int joint, int pinno, double *pinout);
DLLEXPORT void skel18getpres(int joint, int axis, int *presout);
DLLEXPORT void skel18getstab(double *velout, double *posout);
DLLEXPORT void skel18info(int *info);
DLLEXPORT void skel18jnt(int joint, int *info, int *tran);
DLLEXPORT void skel18cons(int consno, int *info);
DLLEXPORT int skel18chkbnum(int routine, int bnum);
DLLEXPORT int skel18chkjnum(int routine, int jnum);
DLLEXPORT int skel18chkucnum(int routine, int ucnum);
DLLEXPORT int skel18chkjaxis(int routine, int jnum, int axnum);
DLLEXPORT int skel18chkjpin(int routine, int jnum, int pinno);
DLLEXPORT void skel18st2ang(double *st, double *stang);
DLLEXPORT void skel18ang2st(double *stang, double *st);
DLLEXPORT void skel18nrmsterr(double *st, double *normst, int routine);
DLLEXPORT void skel18normst(double *st, double *normst);
DLLEXPORT void skel18gentime(int *gentm);

// END of /homes/a/pfal/danceMulti/sdfastObjs/skel18/skel18_dyn.c function prototypes.

// BEGIN  function prototypes

DLLEXPORT void skel18posfunc(double *vars, double *param, double *resid);
DLLEXPORT void skel18velfunc(double *vars, double *param, double *resid);
DLLEXPORT void skel18statfunc(double *vars, double *param, double *resid);
DLLEXPORT void skel18stdyfunc(double *vars, double *param, double *resid);
DLLEXPORT void skel18motfunc(double time, double *state, double *dstate, double *param, int *status);
DLLEXPORT void skel18assemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void skel18initvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void skel18static(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void skel18steady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void skel18motion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err);
DLLEXPORT void skel18fmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err);

// END of /homes/a/pfal/danceMulti/sdfastObjs/skel18/skel18_sar.c function prototypes.

// BEGIN  function prototypes

DLLEXPORT void skel18error(int *routine, int *errnum);
DLLEXPORT void skel18printerr(FILE *fnum);
DLLEXPORT void skel18clearerr(void);
DLLEXPORT void skel18seterr(int routine, int errnum);
DLLEXPORT void skel18ldudcomp(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d);
DLLEXPORT void skel18ldubsl(int n, int na, int *map, double *l, double *b, double *x);
DLLEXPORT void skel18ldubsd(int n, int na, int *map, double *d, double *b, double *x);
DLLEXPORT void skel18ldubsu(int n, int na, int *map, double *l, double *b, double *x);
DLLEXPORT void skel18ldubslv(int n, int na, int *map, double *work, double *l, double *d, double *b, double *x);
DLLEXPORT void skel18lduslv(int n, int na, int *map, double tol, double *work1, double *work2, double *m, double *b, double *l, double *d, double *x);
DLLEXPORT void skel18qrdcomp(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w, double *qraux, int *jpvt);
DLLEXPORT void skel18qrsl(int nr, int nc, int nra, int nca, int *mapr, int *mapc, int k, double *work, double *w, double *qraux, double *b, double *x);
DLLEXPORT void skel18qrbslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, double *work, int *iwork, double *w, double *qraux, int *jpvt, double *b, double *x, int *rank);
DLLEXPORT void skel18qrslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, int *jpvt, double *qraux, double *work, int *iwork, double *w, double *b, double *x, int *rank);
DLLEXPORT void skel18lsslv(int nr, int nc, int nra, int nca, int ndes, int *mapr, int *mapc, double tol, double *dw, double *rw, int *iw, double *w, double *b, double *x);
DLLEXPORT void skel18calcerrs(double *fval, int nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm);
DLLEXPORT void skel18adjvars(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double tderr, double rtol, int *fcnt, double *newvars, double *newerrs);
DLLEXPORT void skel18calcjac(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int *lock, double delta, double *fval, double *ftmp, double *jw, int *fcnt, double *scale);
DLLEXPORT void skel18root(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol, int maxeval, double *jw, double *dw, double *rw, int *iw, double *fret, int *fcnt, int *err);
DLLEXPORT void skel18rk4m(void (*func) (double,double *,double *,double *,int *), double time, double *st, double *dst0, double *param, double step, double *nst, int neq, double *work, double *errs, double *maxerr, int *which);
DLLEXPORT void skel18finteg(void (*func) (double,double *,double *,double *,int *), double *time, double *st, double *dst, double *param, double step, int neq, double *work, double *errest, int *status);
DLLEXPORT void skel18vinteg(void (*func) (double,double *,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int neqin, double tol, double *work, int *err, int *which);
DLLEXPORT void skel18dc2ang(double (*dircos)[3], double *a1, double *a2, double *a3);
DLLEXPORT void skel18dc2quat(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4);
DLLEXPORT void skel18ang2dc(double a1, double a2, double a3, double (*dircos)[3]);
DLLEXPORT void skel18quat2dc(double ie1, double ie2, double ie3, double ie4, double (*dircos)[3]);
double skel18vdot(double *ivec1, double *ivec2);
double skel18vnorm(double *ivec);
DLLEXPORT void skel18vcopy(double *ivec, double *ovec);
DLLEXPORT void skel18vset(double sclr1, double sclr2, double sclr3, double *ovec);
DLLEXPORT void skel18vadd(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void skel18vsub(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void skel18vmul(double sclr, double *ivec, double *ovec);
DLLEXPORT void skel18vaxpy(double sclr, double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void skel18vcross(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void skel18vrot(double *ivec, double *rvec, double theta, double *ovec);
DLLEXPORT void skel18prerrmsg(FILE *fnum, int routine, int errnum);
DLLEXPORT void skel18serialno(int *serno);

// END of /homes/a/pfal/danceMulti/sdfastObjs/skel18/skel18lib.c function prototypes.

#ifdef __cplusplus
}
#endif
