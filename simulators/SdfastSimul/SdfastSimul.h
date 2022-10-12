/**************************************************************************
	----------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project


 ***************************************************************
 ******General License Agreement and Lack of Warranty ***********
 ****************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/



#ifndef	SdfastSimul_h
#define	SdfastSimul_h 1

#define	SD_GROUND -1 //	index for ground body acording to sdfast
#define	MAXUSERCONSTRAINTS 5 //	Max constraints	per object
#define	MAXEVALS	 500 //	Used in	assembly analysis

#include <stdio.h>
#include "defs.h"
#include "DSimulator.h"

class DSystem ;

class DLLEXPORT SdfastSimul : public DSimulator	{
public:
  SdfastSimul()	;
  SdfastSimul(DSystem *, Tcl_Interp *interp) ;
  ~SdfastSimul() ;

  //-----------	starting modules that should be	loaded from sdfast --------------
  int nbod ;
  int njnt ;
  int ndof ;
  int nloop ;
  int nldof ;
  int nq ;
  int nu ;
  int nlq ;
  int nlu ;
  int nc ;
  int nlc ;
  int npresc ;
  int nuserc ;

  void (* sdinit)(void);
  void (* sdstate)(double timein, double *qin, double *uin);
  void (* sdqdot)(double *oqdot);
  void (* sdu2qdot)(double *uin, double	*oqdot);
  void (* sdpsstate)(double *lqin);
  void (* sddovpk)(void);
  void (* sddoltau)(void);
  void (* sddoiner)(void);
  void (* sddofs0)(void);
  void (* sddomm)(int routine);
  void (* sddommldu)(int routine);
  void (* sdlhs)(int routine);
  void (* sdmassmat)(double (*mmat)[7]);
  void (* sdfrcmat)(double *fmat);
  void (* sdmfrc)(double *imult);
  void (* sdequivht)(double *tau);
  void (* sdfulltrq)(double *udotin, double *multin, double *trqout);
  void (* sdcomptrq)(double *udotin, double *trqout);
  void (* sdmulttrq)(double *multin, double *trqout);
  void (* sdfs0)(void);
  void (* sdfsmult)(void);
  void (* sdfsfull)(void);
  void (* sdfsgenmult)(void);
  void (* sdfsgenfull)(void);
  void (* sdrhs)(void);
  void (* sdpseudo)(double *lqout, double *luout);
  void (* sdpsqdot)(double *lqdout);
  void (* sdpsudot)(double *ludout);
  void (* sdperr)(double *errs);
  void (* sdverr)(double *errs);
  void (* sdaerr)(double *errs);
  int (* sdindx)(int joint, int	axis);
  void (* sdpresacc)(int joint,	int axis, double prval);
  void (* sdpresvel)(int joint,	int axis, double prval);
  void (* sdprespos)(int joint,	int axis, double prval);
  void (* sdgetht)(int joint, int axis,	double *torque);
  void (* sdhinget)(int	joint, int axis, double	torque);
  void (* sdpointf)(int	body, double *point, double *force);
  void (* sdbodyt)(int body, double *torque);
  void (* sddoww)(int routine);
  void (* sdxudot0)(int	routine, double	*oudot0);
  void (* sdudot0)(double *oudot0);
  void (* sdsetudot)(double *iudot);
  void (* sdxudotm)(int	routine, double	*imult,	double *oudotm);
  void (* sdudotm)(double *imult, double *oudotm);
  void (* sdderiv)(double *oqdot, double *oudot);
  void (* sdresid)(double *eqdot, double *eudot, double	*emults, double	*resid);
  void (* sdmult)(double *omults, int *owrank, int *omultmap);
  void (* sdreac)(double (*force)[3], double (*torque)[3]);
  void (* sdmom)(double	*lm, double *am, double	*ke);
  void (* sdsys)(double	*mtoto,	double *cm, double (*icm)[3]);
  void (* sdpos)(int body, double *pt, double *loc);
  void (* sdvel)(int body, double *pt, double *velo);
  void (* sdorient)(int	body, double (*dircos)[3]);
  void (* sdangvel)(int	body, double *avel);
  void (* sdtrans)(int frbod, double *ivec, int	tobod, double *ovec);
  void (* sdrel2cart)(int coord, int body, double *point, double *linchg, double *rotchg);
  void (* sdacc)(int body, double *pt, double *accel);
  void (* sdangacc)(int	body, double *aacc);
  void (* sdgrav)(double *gravin);
  void (* sdmass)(int body, double massin);
  void (* sdiner)(int body, double (*inerin)[3]);
  void (* sdbtj)(int joint, double *btjin);
  void (* sditj)(int joint, double *itjin);
  void (* sdpin)(int joint, int	pinno, double *pinin);
  void (* sdpres)(int joint, int axis, int presin);
  void (* sdstab)(double velin,	double posin);
  void (* sdgetgrav)(double *gravout);
  void (* sdgetmass)(int body, double *massout);
  void (* sdgetiner)(int body, double (*inerout)[3]);
  void (* sdgetbtj)(int	joint, double *btjout);
  void (* sdgetitj)(int	joint, double *itjout);
  void (* sdgetpin)(int	joint, int pinno, double *pinout);
  void (* sdgetpres)(int joint,	int axis, int *presout);
  void (* sdgetstab)(double *velout, double *posout);
  void (* sdinfo)(int *info);
  void (* sdjnt)(int joint, int	*info, int *tran);
  void (* sdcons)(int consno, int *info);
  int (* sdchkbnum)(int	routine, int bnum);
  int (* sdchkjnum)(int	routine, int jnum);
  int (* sdchkucnum)(int routine, int ucnum);
  int (* sdchkjaxis)(int routine, int jnum, int	axnum);
  int (* sdchkjpin)(int	routine, int jnum, int pinno);
  void (* sdst2ang)(double *st,	double *stang);
  void (* sdang2st)(double *stang, double *st);
  void (* sdnrmsterr)(double *st, double *normst, int routine);
  void (* sdnormst)(double *st,	double *normst);
  void (* sdgentime)(int *gentm);
  int (* sdposfunc)(double *vars, double *param, double	*resid)	;
  int (* sdvelfunc)(double *vars, double *param, double	*resid)	;
  int (* sdstatfunc)(double *vars, double *param, double *resid) ;
  int (* sdstdyfunc)(double *vars, double *param, double *resid) ;
  int (* sdmotfunc)(double time, double	*state,	double *dstate,	double *param, int *status) ;
  int (* sdassemble)(double time, double *state, int *lock, double tol,	int maxevals, int *fcnt, int *err) ;
  int (* sdinitvel)(double time, double	*state,	int *lock, double tol, int maxevals, int *fcnt,	int *err) ;
  int (* sdstatic)(double time,	double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int	*err) ;
  int (* sdsteady)(double time,	double *state, int *lock, double ctol, double tol, int maxevals, int *fcnt, int	*err) ;
  int (* sdmotion)(double *time, double	*state,	double *dstate,	double dt, double ctol,	double tol, int	*flag, int *err) ;
  int (* sdfmotion)(double *time, double *state, double	*dstate, double	dt, double ctol, int *flag, double *errest, int	*err) ;
  void (* sderror)(int *routine, int *errnum);
  void (* sdprinterr)(FILE *fnum);
  void (* sdclearerr)(void);
  void (* sdseterr)(int	routine, int errnum);
  void (* sdldudcomp)(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d);
  void (* sdldubsl)(int	n, int na, int *map, double *l,	double *b, double *x);
  void (* sdldubsd)(int	n, int na, int *map, double *d,	double *b, double *x);
  void (* sdldubsu)(int	n, int na, int *map, double *l,	double *b, double *x);
  void (* sdldubslv)(int n, int	na, int	*map, double *work, double *l, double *d, double *b, double *x);
  void (* sdlduslv)(int	n, int na, int *map, double tol, double	*work1,	double *work2, double *m, double *b, double *l,	double *d, double *x);
  void (* sdqrdcomp)(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w,	double *qraux, int *jpvt);
  void (* sdqrsl)(int nr, int nc, int nra, int nca, int	*mapr, int *mapc, int k, double	*work, double *w, double *qraux, double	*b, double *x);
  void (* sdqrbslv)(int	nr, int	nc, int	nra, int nca, int *mapr, int *mapc, double tol,	double *work, int *iwork, double *w, double *qraux, int	*jpvt, double *b, double *x, int *rank);
  void (* sdqrslv)(int nr, int nc, int nra, int	nca, int *mapr,	int *mapc, double tol, int *jpvt, double *qraux, double	*work, int *iwork, double *w, double *b, double	*x, int	*rank);
  void (* sdlsslv)(int nr, int nc, int nra, int	nca, int ndes, int *mapr, int *mapc, double tol, double	*dw, double *rw, int *iw, double *w, double *b,	double *x);
  void (* sdcalcerrs)(double *fval, int	nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm);
  void (* sdadjvars)(void (*func) (double *,double *,double *),	double *vars, double *param, int nfunc,	int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double	tderr, double rtol, int	*fcnt, double *newvars,	double *newerrs);
  void (* sdcalcjac)(void (*func) (double *,double *,double *),	double *vars, double *param, int nfunc,	int nvar, int *lock, double delta, double *fval, double	*ftmp, double *jw, int *fcnt, double *scale);
  void (* sdroot)(void (*func) (double *,double	*,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol,	int maxeval, double *jw, double	*dw, double *rw, int *iw, double *fret,	int *fcnt, int *err);
  void (* sdrk4m)(void (*func) (double,double *,double *,double	*,int *), double time, double *st, double *dst0, double	*param,	double step, double *nst, int neq, double *work, double	*errs, double *maxerr, int *which);
  void (* sdfinteg)(void (*func) (double,double	*,double *,double *,int	*), double *time, double *st, double *dst, double *param, double step, int neq,	double *work, double *errest, int *status);
  void (* sdvinteg)(void (*func) (double,double	*,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int	neqin, double tol, double *work, int *err, int *which);
  void (* sddc2ang)(double (*dircos)[3], double	*a1, double *a2, double	*a3);
  void (* sddc2quat)(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4);
  void (* sdang2dc)(double a1, double a2, double a3, double (*dircos)[3]);
  void (* sdquat2dc)(double ie1, double	ie2, double ie3, double	ie4, double (*dircos)[3]);
  double (* sdvdot)(double *ivec1, double *ivec2);
  double (* sdvnorm)(double *ivec);
  void (* sdvcopy)(double *ivec, double	*ovec);
  void (* sdvset)(double sclr1,	double sclr2, double sclr3, double *ovec);
  void (* sdvadd)(double *ivec1, double	*ivec2,	double *ovec);
  void (* sdvsub)(double *ivec1, double	*ivec2,	double *ovec);
  void (* sdvmul)(double sclr, double *ivec, double *ovec);
  void (* sdvaxpy)(double sclr,	double *ivec1, double *ivec2, double *ovec);
  void (* sdvcross)(double *ivec1, double *ivec2, double *ovec);
  void (* sdvrot)(double *ivec,	double *rvec, double theta, double *ovec);
  void (* sdprerrmsg)(FILE *fnum, int routine, int errnum);
  void (* sdserialno)(int *serno);
  // void (*myDeriv) (double time, double *state, double *dstate, 
  //		   double *param, int *status) ;


  //---------------------- end of sdfast functions and parameters ----------------

  
  DSystem *ao	;
  static DSystem *CurrentSimulObject ;
  int m_isLoaded ;
  Tcl_Interp *interpreter ;

  int flag ;
  int *m_lock;
  double tol ;
  double ctol ;	// Position error tolerance for	constraints
  double errest	;
  int err ;

  double *m_state	;
  double *m_dstate ;
	double *m_initVel ;
  double m_dt ;
  double m_time ;
  void *handle ;
  double m_end ;
  int fixedStep	;
  int m_integrator ;		// shows which intergrator to use

  long int m_liw ;
  long int m_lrw ;
  double *m_rwork ;
  long int *m_iwork ;
  long int m_istate ;

  void initSdState(void) ;
  // void setJointsFromStateVector(void);
  // void setStateVectorFromJoints(void);
  static int MakeCompile(char nameObj[]) ;
  void assemblyAnalysis();
  void initVelocityAnalysis();
  void staticAnalysis();
  void steadyStateAnalysis();
  void step(double destTime) ;

  int bindPointers() ;
  void getState(double *s) { memcpy(s, m_state, nq*sizeof(double)) ;} ;
  static double	dotDistance(double *a1,	double *a2, double *b1,	double *b2);
  static void Defaultuforce(double t, double *q, double	*u) ;
  static void Defaultumotion(double t, double *q, double *u) ;
  static void PosError(double t, double	*q, double *errs);
  static void VelError(double t, double	*q, double *u, double *errs);
  static void AccError(double t, double	*q, double *u, double *udot, double *errs);
  static void ConstraintForces(double t, double	*q, double *u, double *mults);
  static void LsodesCalcDeriv(double *y, double *dy,  double *t) ;
  void Savedstate(FILE *fp) ;


  int Load(void) ;
  // new functions (after simulators became plugins)
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;

  void SetTime(double t) { m_time = t ;} ;
  double GetTime(void) { return m_time ;} ;
  int Stop(void) ;
  int Start(double time) ;
  int Step(DSystem *sys, double destTime) ;

  // wrapper functions
  void GetVel(DSystem *sys, double *point, double *vel) ;
  void GetVel(int group, double *point, double *vel) { sdvel(group, point, vel) ; };
  void GetAcc(int group, double *point, double *acc) { sdacc(group, point, acc) ; };
  int GetPosition(DSystem *sys, double *localPoint, double *position) ;
  int GetPosition(int group, double *localPoint, double *position) 
    { sdpos(group, localPoint, position) ; return 1;} ;
  int GetOrientation(int sourceGroup, double *localVec, int targetGroup, 
		     double *rotated) 
    { sdtrans(sourceGroup, localVec, targetGroup, rotated) ; return 1;} ;
  void FieldForce(double *force);
  void PointForce(int argc, char *argv[]) ;
  void PointForce(int group, double *point, double *force) 
    { sdpointf(group, point, force) ;} ;
  void BodyTorque(int group, double *torque) { sdbodyt(group, torque); } ;
  void GeneralizedForce(int coord, double force) { NotImpl("GeneralizedForce") ; };
  void GeneralizedForce(int *index, double *force, int size) 
    { NotImpl("GeneralizedForce") ; };
  void GeneralizedForce(int group, int subgroup, double force) 
		{ sdhinget(group, subgroup, force) ; };
  void GeneralizedForce(double *Q) { NotImpl("GeneralizedForce") ; } ;
  int GetIndex(int group, int subgroup) { return sdindx(group, subgroup) ; };
  
  
  int SetStateFromObjectState(DSystem *sys) ;
  int SetObjectStateFromState(DSystem *sys) ;

  int commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) ;
  
} ;

#endif

