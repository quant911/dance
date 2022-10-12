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
#define penduforce (*sduforce)
extern  DLLIMPORT void penduforce(double t, double *q, double *u);
#define pendumotion (*sdumotion)
extern  DLLIMPORT void pendumotion(double t, double *q, double *u);
#define penduperr (*sduperr)
extern  DLLIMPORT void penduperr(double t, double *q, double *err);
#define penduverr (*sduverr)
extern  DLLIMPORT void penduverr(double t, double *q, double *u, double *err);
#define penduaerr (*sduaerr)
extern  DLLIMPORT void penduaerr(double t, double *q, double *u, double *udot, double *err);
#define penduconsfrc (*sduconsfrc)
extern  DLLIMPORT void penduconsfrc(double t, double *q, double *u, double *mults);
// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_dyn.c function prototypes

DLLEXPORT void pendinit(void);
DLLEXPORT void pendstate(double timein, double *qin, double *uin);
DLLEXPORT void pendqdot(double *oqdot);
DLLEXPORT void pendu2qdot(double *uin, double *oqdot);
DLLEXPORT void pendpsstate(double *lqin);
DLLEXPORT void penddovpk(void);
DLLEXPORT void penddoltau(void);
DLLEXPORT void penddoiner(void);
DLLEXPORT void penddofs0(void);
DLLEXPORT void penddomm(int routine);
DLLEXPORT void penddommldu(int routine);
DLLEXPORT void pendlhs(int routine);
DLLEXPORT void pendmassmat(double (*mmat)[2]);
DLLEXPORT void pendfrcmat(double *fmat);
DLLEXPORT void pendmfrc(double *imult);
DLLEXPORT void pendequivht(double *tau);
DLLEXPORT void pendfulltrq(double *udotin, double *multin, double *trqout);
DLLEXPORT void pendcomptrq(double *udotin, double *trqout);
DLLEXPORT void pendmulttrq(double *multin, double *trqout);
DLLEXPORT void pendfs0(void);
DLLEXPORT void pendfsmult(void);
DLLEXPORT void pendfsfull(void);
DLLEXPORT void pendfsgenmult(void);
DLLEXPORT void pendfsgenfull(void);
DLLEXPORT void pendrhs(void);
DLLEXPORT void pendpseudo(double *lqout, double *luout);
DLLEXPORT void pendpsqdot(double *lqdout);
DLLEXPORT void pendpsudot(double *ludout);
DLLEXPORT void pendperr(double *errs);
DLLEXPORT void pendverr(double *errs);
DLLEXPORT void pendaerr(double *errs);
DLLEXPORT int pendindx(int joint, int axis);
DLLEXPORT void pendpresacc(int joint, int axis, double prval);
DLLEXPORT void pendpresvel(int joint, int axis, double prval);
DLLEXPORT void pendprespos(int joint, int axis, double prval);
DLLEXPORT void pendgetht(int joint, int axis, double *torque);
DLLEXPORT void pendhinget(int joint, int axis, double torque);
DLLEXPORT void pendpointf(int body, double *point, double *force);
DLLEXPORT void pendbodyt(int body, double *torque);
DLLEXPORT void penddoww(int routine);
DLLEXPORT void pendxudot0(int routine, double *oudot0);
DLLEXPORT void pendudot0(double *oudot0);
DLLEXPORT void pendsetudot(double *iudot);
DLLEXPORT void pendxudotm(int routine, double *imult, double *oudotm);
DLLEXPORT void pendudotm(double *imult, double *oudotm);
DLLEXPORT void pendderiv(double *oqdot, double *oudot);
DLLEXPORT void pendresid(double *eqdot, double *eudot, double *emults, double *resid);
DLLEXPORT void pendmult(double *omults, int *owrank, int *omultmap);
DLLEXPORT void pendreac(double (*force)[3], double (*torque)[3]);
DLLEXPORT void pendmom(double *lm, double *am, double *ke);
DLLEXPORT void pendsys(double *mtoto, double *cm, double (*icm)[3]);
DLLEXPORT void pendpos(int body, double *pt, double *loc);
DLLEXPORT void pendvel(int body, double *pt, double *velo);
DLLEXPORT void pendorient(int body, double (*dircos)[3]);
DLLEXPORT void pendangvel(int body, double *avel);
DLLEXPORT void pendtrans(int frbod, double *ivec, int tobod, double *ovec);
DLLEXPORT void pendrel2cart(int coord, int body, double *point, double *linchg, double *rotchg);
DLLEXPORT void pendacc(int body, double *pt, double *accel);
DLLEXPORT void pendangacc(int body, double *aacc);
DLLEXPORT void pendgrav(double *gravin);
DLLEXPORT void pendmass(int body, double massin);
DLLEXPORT void pendiner(int body, double (*inerin)[3]);
DLLEXPORT void pendbtj(int joint, double *btjin);
DLLEXPORT void penditj(int joint, double *itjin);
DLLEXPORT void pendpin(int joint, int pinno, double *pinin);
DLLEXPORT void pendpres(int joint, int axis, int presin);
DLLEXPORT void pendstab(double velin, double posin);
DLLEXPORT void pendgetgrav(double *gravout);
DLLEXPORT void pendgetmass(int body, double *massout);
DLLEXPORT void pendgetiner(int body, double (*inerout)[3]);
DLLEXPORT void pendgetbtj(int joint, double *btjout);
DLLEXPORT void pendgetitj(int joint, double *itjout);
DLLEXPORT void pendgetpin(int joint, int pinno, double *pinout);
DLLEXPORT void pendgetpres(int joint, int axis, int *presout);
DLLEXPORT void pendgetstab(double *velout, double *posout);
DLLEXPORT void pendinfo(int *info);
DLLEXPORT void pendjnt(int joint, int *info, int *tran);
DLLEXPORT void pendcons(int consno, int *info);
DLLEXPORT int pendchkbnum(int routine, int bnum);
DLLEXPORT int pendchkjnum(int routine, int jnum);
DLLEXPORT int pendchkucnum(int routine, int ucnum);
DLLEXPORT int pendchkjaxis(int routine, int jnum, int axnum);
DLLEXPORT int pendchkjpin(int routine, int jnum, int pinno);
DLLEXPORT void pendst2ang(double *st, double *stang);
DLLEXPORT void pendang2st(double *stang, double *st);
DLLEXPORT void pendnrmsterr(double *st, double *normst, int routine);
DLLEXPORT void pendnormst(double *st, double *normst);
DLLEXPORT void pendgentime(int *gentm);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_dyn.c function prototypes.

// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_sar.c function prototypes

DLLEXPORT void pendposfunc(double *vars, double *param, double *resid);
DLLEXPORT void pendvelfunc(double *vars, double *param, double *resid);
DLLEXPORT void pendstatfunc(double *vars, double *param, double *resid);
DLLEXPORT void pendstdyfunc(double *vars, double *param, double *resid);
DLLEXPORT void pendmotfunc(double time, double *state, double *dstate, double *param, int *status);
DLLEXPORT void pendassemble(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void pendinitvel(double time, double *state, int *lock, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void pendstatic(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void pendsteady(double time, double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int *err);
DLLEXPORT void pendmotion(double *time, double *state, double *dstate, double dt, double ctol, double tol, int *flag, int *err);
DLLEXPORT void pendfmotion(double *time, double *state, double *dstate, double dt, double ctol, int *flag, double *errest, int *err);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_sar.c function prototypes.

// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pendlib.c function prototypes

DLLEXPORT void penderror(int *routine, int *errnum);
DLLEXPORT void pendprinterr(FILE *fnum);
DLLEXPORT void pendclearerr(void);
DLLEXPORT void pendseterr(int routine, int errnum);
DLLEXPORT void pendldudcomp(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d);
DLLEXPORT void pendldubsl(int n, int na, int *map, double *l, double *b, double *x);
DLLEXPORT void pendldubsd(int n, int na, int *map, double *d, double *b, double *x);
DLLEXPORT void pendldubsu(int n, int na, int *map, double *l, double *b, double *x);
DLLEXPORT void pendldubslv(int n, int na, int *map, double *work, double *l, double *d, double *b, double *x);
DLLEXPORT void pendlduslv(int n, int na, int *map, double tol, double *work1, double *work2, double *m, double *b, double *l, double *d, double *x);
DLLEXPORT void pendqrdcomp(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w, double *qraux, int *jpvt);
DLLEXPORT void pendqrsl(int nr, int nc, int nra, int nca, int *mapr, int *mapc, int k, double *work, double *w, double *qraux, double *b, double *x);
DLLEXPORT void pendqrbslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, double *work, int *iwork, double *w, double *qraux, int *jpvt, double *b, double *x, int *rank);
DLLEXPORT void pendqrslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, int *jpvt, double *qraux, double *work, int *iwork, double *w, double *b, double *x, int *rank);
DLLEXPORT void pendlsslv(int nr, int nc, int nra, int nca, int ndes, int *mapr, int *mapc, double tol, double *dw, double *rw, int *iw, double *w, double *b, double *x);
DLLEXPORT void pendcalcerrs(double *fval, int nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm);
DLLEXPORT void pendadjvars(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double tderr, double rtol, int *fcnt, double *newvars, double *newerrs);
DLLEXPORT void pendcalcjac(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int *lock, double delta, double *fval, double *ftmp, double *jw, int *fcnt, double *scale);
DLLEXPORT void pendroot(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol, int maxeval, double *jw, double *dw, double *rw, int *iw, double *fret, int *fcnt, int *err);
DLLEXPORT void pendrk4m(void (*func) (double,double *,double *,double *,int *), double time, double *st, double *dst0, double *param, double step, double *nst, int neq, double *work, double *errs, double *maxerr, int *which);
DLLEXPORT void pendfinteg(void (*func) (double,double *,double *,double *,int *), double *time, double *st, double *dst, double *param, double step, int neq, double *work, double *errest, int *status);
DLLEXPORT void pendvinteg(void (*func) (double,double *,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int neqin, double tol, double *work, int *err, int *which);
DLLEXPORT void penddc2ang(double (*dircos)[3], double *a1, double *a2, double *a3);
DLLEXPORT void penddc2quat(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4);
DLLEXPORT void pendang2dc(double a1, double a2, double a3, double (*dircos)[3]);
DLLEXPORT void pendquat2dc(double ie1, double ie2, double ie3, double ie4, double (*dircos)[3]);
double pendvdot(double *ivec1, double *ivec2);
double pendvnorm(double *ivec);
DLLEXPORT void pendvcopy(double *ivec, double *ovec);
DLLEXPORT void pendvset(double sclr1, double sclr2, double sclr3, double *ovec);
DLLEXPORT void pendvadd(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void pendvsub(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void pendvmul(double sclr, double *ivec, double *ovec);
DLLEXPORT void pendvaxpy(double sclr, double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void pendvcross(double *ivec1, double *ivec2, double *ovec);
DLLEXPORT void pendvrot(double *ivec, double *rvec, double theta, double *ovec);
DLLEXPORT void pendprerrmsg(FILE *fnum, int routine, int errnum);
DLLEXPORT void pendserialno(int *serno);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pendlib.c function prototypes.

#ifdef __cplusplus
}
#endif
