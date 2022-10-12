// BEGIN /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_dyn.c function prototypes

void pendinit(void);
void pendstate(double timein, double *qin, double *uin);
void pendqdot(double *oqdot);
void pendu2qdot(double *uin, double *oqdot);
void pendpsstate(double *lqin);
void penddovpk(void);
void penddoltau(void);
void penddoiner(void);
void penddofs0(void);
void penddomm(int routine);
void penddommldu(int routine);
void pendlhs(int routine);
void pendmassmat(double (*mmat)[2]);
void pendfrcmat(double *fmat);
void pendmfrc(double *imult);
void pendequivht(double *tau);
void pendfulltrq(double *udotin, double *multin, double *trqout);
void pendcomptrq(double *udotin, double *trqout);
void pendmulttrq(double *multin, double *trqout);
void pendfs0(void);
void pendfsmult(void);
void pendfsfull(void);
void pendfsgenmult(void);
void pendfsgenfull(void);
void pendrhs(void);
void pendpseudo(double *lqout, double *luout);
void pendpsqdot(double *lqdout);
void pendpsudot(double *ludout);
void pendperr(double *errs);
void pendverr(double *errs);
void pendaerr(double *errs);
int pendindx(int joint, int axis);
void pendpresacc(int joint, int axis, double prval);
void pendpresvel(int joint, int axis, double prval);
void pendprespos(int joint, int axis, double prval);
void pendgetht(int joint, int axis, double *torque);
void pendhinget(int joint, int axis, double torque);
void pendpointf(int body, double *point, double *force);
void pendbodyt(int body, double *torque);
void penddoww(int routine);
void pendxudot0(int routine, double *oudot0);
void pendudot0(double *oudot0);
void pendsetudot(double *iudot);
void pendxudotm(int routine, double *imult, double *oudotm);
void pendudotm(double *imult, double *oudotm);
void pendderiv(double *oqdot, double *oudot);
void pendresid(double *eqdot, double *eudot, double *emults, double *resid);
void pendmult(double *omults, int *owrank, int *omultmap);
void pendreac(double (*force)[3], double (*torque)[3]);
void pendmom(double *lm, double *am, double *ke);
void pendsys(double *mtoto, double *cm, double (*icm)[3]);
void pendpos(int body, double *pt, double *loc);
void pendvel(int body, double *pt, double *velo);
void pendorient(int body, double (*dircos)[3]);
void pendangvel(int body, double *avel);
void pendtrans(int frbod, double *ivec, int tobod, double *ovec);
void pendrel2cart(int coord, int body, double *point, double *linchg, double *rotchg);
void pendacc(int body, double *pt, double *accel);
void pendangacc(int body, double *aacc);
void pendgrav(double *gravin);
void pendmass(int body, double massin);
void pendiner(int body, double (*inerin)[3]);
void pendbtj(int joint, double *btjin);
void penditj(int joint, double *itjin);
void pendpin(int joint, int pinno, double *pinin);
void pendpres(int joint, int axis, int presin);
void pendstab(double velin, double posin);
void pendgetgrav(double *gravout);
void pendgetmass(int body, double *massout);
void pendgetiner(int body, double (*inerout)[3]);
void pendgetbtj(int joint, double *btjout);
void pendgetitj(int joint, double *itjout);
void pendgetpin(int joint, int pinno, double *pinout);
void pendgetpres(int joint, int axis, int *presout);
void pendgetstab(double *velout, double *posout);
void pendinfo(int *info);
void pendjnt(int joint, int *info, int *tran);
void pendcons(int consno, int *info);
int pendchkbnum(int routine, int bnum);
int pendchkjnum(int routine, int jnum);
int pendchkucnum(int routine, int ucnum);
int pendchkjaxis(int routine, int jnum, int axnum);
int pendchkjpin(int routine, int jnum, int pinno);
void pendst2ang(double *st, double *stang);
void pendang2st(double *stang, double *st);
void pendnrmsterr(double *st, double *normst, int routine);
void pendnormst(double *st, double *normst);
void pendgentime(int *gentm);

// END of /homes/a/pfal/danceMulti/sdfastObjs/pend/pend_dyn.c function prototypes.
