#ifdef __cplusplus
extern "C" {
#endif
/*
Generated 27-Apr-2000 15:42:50 by SD/FAST, Kane's formulation
Generated 27-Apr-2000 15:42:50 by SD/FAST, Kane's formulation
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
#include <stdio.h>

typedef struct {
    int lasterr_,lastrou_;
} pendgerror_t;
#define lasterr (pendgerror.lasterr_)
#define lastrou (pendgerror.lastrou_)

pendgerror_t pendgerror = {
/* Error parameters
*/
    /* lasterr */ 0,
    /* lastrou */ 0,
};


void penderror(int *routine, int *errnum)
{

    *errnum = lasterr;
    *routine = lastrou;
}

void pendprinterr(FILE *fnum)
{

    pendprerrmsg(fnum,lastrou,lasterr);
}

void pendclearerr(void)
{

    lasterr = 0;
    lastrou = 0;
}

void pendseterr(int routine, int errnum)
{

    if (lasterr == 0) {
        lasterr = errnum;
        lastrou = routine;
    }
}

/*
===========================================================
LDU decomposition scheme for solving Mx=b
  M: na X na symmetric, pos. definite, upper rt triangle filled
  b: na X 1
  x: na X 1 (returned)
Actual dimensions (n) may be larger, map says where to find
the na interesting elements.
===========================================================
*/

void pendldudcomp(int n, int na, int *map, double tol, double *ld, double *sum, double *m, double *l, double *d)
{
    int r,c,row,col,cm1,j,mj;
    double dtemp,dtempi,ldtemp,tsum;

    for (c = 0; c <= na-1; c++) {
        col = map[c];
        cm1 = c-1;

        for (r = c; r <= na-1; r++) {
            row = map[r];
            tsum = m[col*n+row];
            for (j = 0; j <= cm1; j++) {
                mj = map[j];
                tsum = tsum-ld[r*na+j]*l[col*n+mj];
            }
            sum[r] = tsum;
        }
        dtemp = sum[c];
        dtempi = 0.;
        if (fabs(dtemp) > tol)
            dtempi = 1./dtemp;
        d[col] = dtempi;
        for (r = c; r <= na-1; r++) {
            row = map[r];
            ldtemp = sum[r];
            ld[r*na+c] = ldtemp;
            l[row*n+col] = ldtemp*dtempi;
        }
    }
}

void pendldubsl(int n, int na, int *map, double *l, double *b, double *x)
{
    int i,j,im1,mi,mj;
    double sum;

    mi = map[0];
    x[mi] = b[mi];
    for (i = 1; i <= na-1; i++) {
        mi = map[i];
        im1 = i-1;
        sum = b[mi];
        for (j = 0; j <= im1; j++) {
            mj = map[j];
            sum = sum-l[mi*n+mj]*x[mj];
        }
        x[mi] = sum;
    }
}

void pendldubsd(int n, int na, int *map, double *d, double *b, double *x)
{
    int i,mi;

    for (i = 0; i <= na-1; i++) {
        mi = map[i];
        x[mi] = b[mi]*d[mi];
    }
}

void pendldubsu(int n, int na, int *map, double *l, double *b, double *x)
{
    int i,j,ip1,mi,mj;
    double sum;

    mi = map[na-1];
    x[mi] = b[mi];
    i = na-2;
    while (i  >=  0) {
        mi = map[i];
        ip1 = i+1;
        sum = b[mi];
        for (j = ip1; j <= na-1; j++) {
            mj = map[j];
            sum = sum-l[mj*n+mi]*x[mj];
        }
        x[mi] = sum;
        i = i-1;
    }
}

void pendldubslv(int n, int na, int *map, double *work, double *l, double *d, double *b, double *x)
{

    pendldubsl(n,na,map,l,b,work);
    pendldubsd(n,na,map,d,work,work);
    pendldubsu(n,na,map,l,work,x);
}

void pendlduslv(int n, int na, int *map, double tol, double *work1, double *work2, double *m, double *b, double *l, double *d, double *x)
{

    pendldudcomp(n,na,map,tol,work1,work2,m,l,d);
    pendldubslv(n,na,map,work2,l,d,b,x);
}

/*
===========================================================
QR decomposition scheme for solving Wx=b
  W is nra by nca
  b is nra by 1
  x (returned) is nca by 1
Actual dimensions (nr,nc) may be larger, mapr (mapc) says where
to find the nra (nca) interesting rows (columns).  On return, W is
overwritten by the Q and R matrices in compact form.  Solution yields
least squares residual for overdetermined systems.  Underdetermined
systems give a solution in which elements corresponding to redundant
or missing equations are set to 0. (Not necessarily the LS solution.)
===========================================================
*/

void pendqrdcomp(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double *w, double *qraux, int *jpvt)
{
    int i,j,l,lp1,maxj,mi,mj,mlr,mlc,mmaxj,minrca;
    double maxnrm,nrmxl,t;

    for (j = 0; j <= nca-1; j++) {
        mj = mapc[j];
        jpvt[j] = j;
        t = 0.;
        for (l = 0; l <= nra-1; l++) {
            mlr = mapr[l];
            t = t+w[mlr*nc+mj]*w[mlr*nc+mj];
        }
        qraux[j] = sqrt(t);
    }
    if (nca  <  nra) {
        minrca = nca;
    } else {
        minrca = nra;
    }
    for (l = 0; l <= minrca-1; l++) {
        mlr = mapr[l];
        mlc = mapc[l];
        maxnrm = 0.;
        maxj = l;
        for (j = l; j <= nca-1; j++) {
            if (qraux[j]  >  maxnrm) {
                maxnrm = qraux[j];
                maxj = j;
            }
        }
        if (maxj  !=  l) {
            mmaxj = mapc[maxj];
            for (i = 0; i <= nra-1; i++) {
                mi = mapr[i];
                t = w[mi*nc+mlc];
                w[mi*nc+mlc] = w[mi*nc+mmaxj];
                w[mi*nc+mmaxj] = t;
            }
            qraux[maxj] = qraux[l];
            i = jpvt[maxj];
            jpvt[maxj] = jpvt[l];
            jpvt[l] = i;
        }
        qraux[l] = 0.;
        if (l  !=  nra-1) {
            t = 0.;
            for (i = l; i <= nra-1; i++) {
                mi = mapr[i];
                t = t+w[mi*nc+mlc]*w[mi*nc+mlc];
            }
            nrmxl = sqrt(t);
            if (nrmxl  !=  0.) {
                if (w[mlr*nc+mlc]  <  0.) {
                    nrmxl =  -nrmxl;
                }
                t = 1./nrmxl;
                for (i = l; i <= nra-1; i++) {
                    mi = mapr[i];
                    w[mi*nc+mlc] = t*w[mi*nc+mlc];
                }
                w[mlr*nc+mlc] = 1.+w[mlr*nc+mlc];
                lp1 = l+1;
                for (j = lp1; j <= nca-1; j++) {
                    mj = mapc[j];
                    t = 0.;
                    for (i = l; i <= nra-1; i++) {
                        mi = mapr[i];
                        t = t-w[mi*nc+mlc]*w[mi*nc+mj];
                    }
                    t = t/w[mlr*nc+mlc];
                    for (i = l; i <= nra-1; i++) {
                        mi = mapr[i];
                        w[mi*nc+mj] = w[mi*nc+mj]+t*w[mi*nc+mlc];
                    }
                    t = 0.;
                    for (i = lp1; i <= nra-1; i++) {
                        mi = mapr[i];
                        t = t+w[mi*nc+mj]*w[mi*nc+mj];
                    }
                    qraux[j] = sqrt(t);
                }
                qraux[l] = w[mlr*nc+mlc];
                w[mlr*nc+mlc] =  -nrmxl;
            }
        }
    }
}

void pendqrsl(int nr, int nc, int nra, int nca, int *mapr, int *mapc, int k, double *work, double *w, double *qraux, double *b, double *x)
{
    int i,j,jj,jm1,mir,mic,mjr,mjc,minrk;
    double t,tt;

    for (i = 0; i <= nra-1; i++) {
        mir = mapr[i];
        work[i] = b[mir];
    }
    minrk = nra-1;
    if (k  <  minrk) {
        minrk = k;
    }
    for (j = 0; j <= minrk-1; j++) {
        mjr = mapr[j];
        mjc = mapc[j];
        if (qraux[j]  !=  0.) {
            tt = w[mjr*nc+mjc];
            w[mjr*nc+mjc] = qraux[j];
            t = 0.;
            for (i = j; i <= nra-1; i++) {
                mir = mapr[i];
                t = t-w[mir*nc+mjc]*work[i];
            }
            t = t/w[mjr*nc+mjc];
            for (i = j; i <= nra-1; i++) {
                mir = mapr[i];
                work[i] = work[i]+t*w[mir*nc+mjc];
            }
            w[mjr*nc+mjc] = tt;
        }
    }
    for (j = 0; j <= k-1; j++) {
        mjc = mapc[j];
        x[mjc] = work[j];
    }
    for (jj = 0; jj <= k-1; jj++) {
        j = k-jj-1;
        jm1 = j-1;
        mjr = mapr[j];
        mjc = mapc[j];
        x[mjc] = x[mjc]/w[mjr*nc+mjc];
        t =  -x[mjc];
        for (i = 0; i <= jm1; i++) {
            mir = mapr[i];
            mic = mapc[i];
            x[mic] = x[mic]+t*w[mir*nc+mjc];
        }
    }
}

void pendqrbslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, double *work, int *iwork, double *w, double *qraux, int *jpvt, double *b, double *x, int *rank)
{
    int j,k,kk,mjc,mkkr,mkkc,minrca;
    double t;

    for (j = 0; j < nca; j++) {
        iwork[j] = jpvt[j];
    }
    if (nca  <  nra) {
        minrca = nca;
    } else {
        minrca = nra;
    }
    k = 0;
    mkkr = mapr[0];
    mkkc = mapc[0];
    t = tol*fabs(w[mkkr*nc+mkkc]);
    if (t < .1*tol) {
        t = .1*tol;
    }
    for (kk = 0; kk <= minrca-1; kk++) {
        mkkr = mapr[kk];
        mkkc = mapc[kk];
        if (fabs(w[mkkr*nc+mkkc])  <=  t) {
            break;
        } else {
            k = k+1;
        }
    }
    if (k  !=  0) {
        pendqrsl(nr,nc,nra,nca,mapr,mapc,k,work,w,qraux,b,x);
    }
    for (j = k; j <= nca-1; j++) {
        x[mapc[j]] = 0.;
    }
    for (j = 0; j <= nca-1; j++) {
        kk = iwork[j];
        while (kk  !=  j) {
            mjc = mapc[j];
            mkkc = mapc[kk];
            t = x[mjc];
            x[mjc] = x[mkkc];
            x[mkkc] = t;
            iwork[j] = iwork[kk];
            iwork[kk] = kk;
            kk = iwork[j];
        }
    }
    *rank = k;
}

void pendqrslv(int nr, int nc, int nra, int nca, int *mapr, int *mapc, double tol, int *jpvt, double *qraux, double *work, int *iwork, double *w, double *b, double *x, int *rank)
{

    pendqrdcomp(nr,nc,nra,nca,mapr,mapc,w,qraux,jpvt);
    pendqrbslv(nr,nc,nra,nca,mapr,mapc,tol,work,iwork,w,qraux,jpvt,b,x,rank);
}

/*
===========================================================
Linear equation solver for Wx=b
  W is nra by nca
  b is nra by 1
  x (returned) is nca by 1
Actual dimensions (nr,nc) may be larger, mapr (mapc) says where
to find the nra (nca) interesting rows (columns).  On return, W and
b are unchanged.  Solution yields least squares residual for
overdetermined systems and a least squares solution vector for
underdetermined systems.  If ndes > 0, the first nra-ndes rows
are `required' while the remaining ndes rows are `desired'.  The
returned solution minimizes the residual for the required rows,
then does the best it can on the desired rows.

The performance and numerical properties of this routine are
considerably worse than those of the qrslv routine.  However, it
works very well as a guide to the root finding routine.

Work arrays should be dimensioned as follows:
  dw is 2*(nra+nca)**2
  rw is 4*(nra+nca)
  iw is 3*(nra+nca)
===========================================================
*/

void pendlsslv(int nr, int nc, int nra, int nca, int ndes, int *mapr, int *mapc, double tol, double *dw, double *rw, int *iw, double *w, double *b, double *x)
{
    int i,j,k,nreq,dsiz,rank,mapi,mapj,mapk;
    int ix,wwt,dloc,ddt,qraux,work,rhs,soln,map,jpvt,iwork;

    nreq = nra-ndes;
    dsiz = nca+nreq;
    wwt = 0;
    dloc = 0;
    ddt = dloc+dsiz*dsiz;
    qraux = 0;
    work = qraux+nca+nra;
    rhs = work+nca+nra;
    soln = rhs+nca+nra;
    map = 0;
    jpvt = map+nca+nra;
    iwork = jpvt+nca+nra;
    if (ndes  ==  0) {
        for (i = 0; i <= nra-1; i++) {
            mapi = mapr[i];
            rw[rhs+i] = b[mapi];
            for (j = i; j <= nra-1; j++) {
                mapj = mapr[j];
                ix = wwt+i*nra+j;
                dw[ix] = 0.;
                for (k = 0; k <= nca-1; k++) {
                    mapk = mapc[k];
                    dw[ix] = dw[ix]+w[mapi*nc+mapk]*w[mapj*nc+mapk];
                }
                dw[wwt+j*nra+i] = dw[ix];
            }
            iw[map+i] = i;
        }
        pendqrslv(nra,nra,nra,nra,&iw[map],&iw[map],tol,&iw[jpvt],&rw[qraux],&rw
          [work],&iw[iwork],&dw[wwt],&rw[rhs],&rw[soln],&rank);
        for (i = 0; i <= nca-1; i++) {
            mapi = mapc[i];
            x[mapi] = 0.;
            for (j = 0; j <= nra-1; j++) {
                mapj = mapr[j];
                x[mapi] = x[mapi]+w[mapj*nc+mapi]*rw[soln+j];
            }
        }
    } else {
        for (i = 0; i <= nca-1; i++) {
            mapi = mapc[i];
            for (j = i; j <= nca-1; j++) {
                mapj = mapc[j];
                ix = dloc+i*dsiz+j;
                dw[ix] = 0.;
                for (k = 0; k <= ndes-1; k++) {
                    mapk = mapr[nreq+k];
                    dw[ix] = dw[ix]+w[mapk*nc+mapi]*w[mapk*nc+mapj];
                }
                dw[dloc+j*dsiz+i] = dw[ix];
            }
            for (j = 0; j <= nreq-1; j++) {
                mapj = mapr[j];
                ix = dloc+i*dsiz+(j+nca);
                dw[ix] = w[mapj*nc+mapi];
                dw[dloc+(j+nca)*dsiz+i] = dw[ix];
            }
            rw[rhs+i] = 0.;
            for (j = 0; j <= ndes-1; j++) {
                mapj = mapr[nreq+j];
                rw[rhs+i] = rw[rhs+i]+w[mapj*nc+mapi]*b[mapj];
            }
        }
        for (i = 0; i <= nreq-1; i++) {
            for (j = 0; j <= nreq-1; j++) {
                dw[dloc+(i+nca)*dsiz+(j+nca)] = 0.;
            }
            rw[rhs+(i+nca)] = b[mapr[i]];
        }
        for (i = 0; i <= dsiz-1; i++) {
            iw[map+i] = i;
            for (j = i; j <= dsiz-1; j++) {
                ix = ddt+i*dsiz+j;
                dw[ix] = 0.;
                for (k = 0; k <= dsiz-1; k++) {
                    dw[ix] = dw[ix]+dw[dloc+i*dsiz+k]*dw[dloc+j*dsiz+k];
                }
                dw[ddt+j*dsiz+i] = dw[ix];
            }
        }
        pendqrslv(dsiz,dsiz,dsiz,dsiz,&iw[map],&iw[map],tol,&iw[jpvt],&rw[qraux]
          ,&rw[work],&iw[iwork],&dw[ddt],&rw[rhs],&rw[soln],&rank);
        for (i = 0; i <= nca-1; i++) {
            mapi = mapc[i];
            x[mapi] = 0.;
            for (j = 0; j <= dsiz-1; j++) {
                x[mapi] = x[mapi]+dw[dloc+j*dsiz+i]*rw[soln+j];
            }
        }
    }
}

/* Utility routines for use with pendroot. */


void pendcalcerrs(double *fval, int nfunc, int ndes, int dnorm, double *maxderr, double *maxrerr, double *derrnorm)
{
    int i,nreq;
    double tmp;

    nreq = nfunc-ndes;
    *maxderr = 0.;
    *maxrerr = 0.;
    *derrnorm = 0.;
    for (i = 0; i < nreq; i++) {
        tmp = fabs(fval[i]);
        if (tmp > *maxrerr) {
            *maxrerr = tmp;
        }
    }
    for (i = 0; i < ndes; i++) {
        tmp = fabs(fval[nreq+i]);
        if (tmp > *maxderr) {
            *maxderr = tmp;
        }
        *derrnorm = *derrnorm+tmp;
    }
    if (dnorm == 1) {
        *derrnorm = *maxderr;
    }
}

void pendadjvars(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int ndes, int dnorm, int nvar, double *deltas, double step, double rerr, double tderr, double rtol, int *fcnt, double *newvars, double *newerrs)
{
    int i,cnt,alldone;
    double impr,maxchg,pmaxfact,maxfact,pmaxrerr,pderrnorm,maxderr,maxrerr,
      derrnorm,mag;

    maxfact = 1.;
    for (i = 0; i < nvar; i++) {
        impr = fabs(deltas[i]*step);
        maxchg = .1*fabs(vars[i])+1.;
        if (impr/maxchg > maxfact) {
            maxfact = impr/maxchg;
        }
    }
    maxfact = 1./maxfact;
    pmaxrerr = rerr;
    pderrnorm = tderr;
    pmaxfact = maxfact;
    cnt = 0;
    alldone = 0;
    retry: ;
    cnt = cnt+1;
    for (i = 0; i < nvar; i++) {
        impr = deltas[i]*step;
        newvars[i] = vars[i] - impr*maxfact;
    }
    func(newvars,param,newerrs);
    *fcnt = *fcnt+1;
    if (alldone != 0) {
        return;
    }
    pendcalcerrs(newerrs,nfunc,ndes,dnorm,&maxderr,&maxrerr,&derrnorm);
    if ((pmaxrerr <= rtol) && (maxrerr <= rtol)) {
        impr = pderrnorm-derrnorm;
    } else {
        impr = pmaxrerr-maxrerr;
    }
    pmaxrerr = maxrerr;
    pderrnorm = derrnorm;
    if (impr <= 0.) {
        if (maxfact != pmaxfact) {
            maxfact = pmaxfact;
            alldone = 1;
            goto retry;
        }
    } else {
        if (maxfact < .5) {
            if (cnt < 5) {
                mag = 1.25;
            } else {
                if (cnt < 10) {
                    mag = 2.;
                } else {
                    mag = 10.;
                }
            }
            pmaxfact = maxfact;
            maxfact = mag*maxfact;
            if (maxfact > 1.) {
                maxfact = 1.;
            }
            goto retry;
        }
    }
}

void pendcalcjac(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int *lock, double delta, double *fval, double *ftmp, double *jw, int *fcnt, double *scale)
{
    int i,j;
    double save,chg,vchg,maxelt;

    for (j = 0; j < nvar; j++) {
        if (lock[j] != 0) {
            for (i = 0; i < nfunc; i++) {
                jw[i*nvar+j] = 0.;
            }
        } else {
            save = vars[j];
            vchg = delta*(fabs(save)+1.);
            vars[j] = vars[j]+vchg;
            func(vars,param,ftmp);
            *fcnt = *fcnt+1;
            vars[j] = save;
            for (i = 0; i < nfunc; i++) {
                chg = ftmp[i]-fval[i];
                if (fabs(chg) < 1e-13) {
                    jw[i*nvar+j] = 0.;
                } else {
                    jw[i*nvar+j] = chg/vchg;
                }
            }
        }
    }
    for (i = 0; i < nfunc; i++) {
        maxelt = 0.;
        for (j = 0; j < nvar; j++) {
            if (fabs(jw[i*nvar+j]) > maxelt) {
                maxelt = fabs(jw[i*nvar+j]);
            }
        }
        if (maxelt > 0.) {
            scale[i] = 1./maxelt;
            for (j = 0; j < nvar; j++) {
                jw[i*nvar+j] = jw[i*nvar+j]*scale[i];
            }
        } else {
            scale[i] = 1.;
        }
    }
}

/*
====================================================================
Root-finding scheme for solving a set of nfunc=nreq+ndes nonlinear
equations in nvar unknowns:
  r (v) = r (v) = ... = r (v) = 0    (actually |r | <= rtol)
   1       2             nreq                    i

  d (v) = d (v) = ... = d (v) = 0    (actually |d | <= dtol)
   1       2             ndes                    i
The r's are "required" functions while the d's are only "desired".
That is, we adjust the nvar variables v to find a solution which keeps
each of the r's below rtol, and keeps the d's as small as possible
without violating any of the r's.  Least squares residuals are attempted
if the equations cannot be solved.  No guarantees can be made that
this routine will find a solution even if there is one.  The better
the initial values for the v's, the more likely it is to succeed and
the more quickly it will converge.

A single function func is provided which calculates all of the
r's and d's for the current v and returns the residuals.  A parameter
param is passed through unchanged to the function. 

The array lock has an element corresponding to each variable.  Any
variable which may be modified should have its corresponding lock
element set to 0.  If non-zero, the variable will not be altered here.

Maxeval sets an upper limit on the number of calls to func which may
be made.  The root finder only returns after complete iterations, so
it may make somewhat more than maxeval calls.  On return, the actual
number of calls made is returned in fcnt.  Err is returned 0 if we
successfully reduce all the r's to below rtol and all the d's to below
dtol.  If the r's are met but not the d's, we return with err=1, and if
the r's are not met we return err=2.

Work arrays should be dimensioned as follows:
  jw is nf*nv
  dw is 2*(nf+nv)**2
  rw is 7*nf+9*nv
  iw is 4*(nf+nv)
====================================================================
*/

void pendroot(void (*func) (double *,double *,double *), double *vars, double *param, int nfunc, int nvar, int ndesin, int *lock, double rtol, double dtol, int maxeval, double *jw, double *dw, double *rw, int *iw, double *fret, int *fcnt, int *err)
{
    int i,slowcnt,tooslow,ntrys,nreq,fixits,ndes,dnorm;
    int f1,f2,scale,deltav,guess,rvars,rdeltav,rguess,morerw,mapf,mapv,moreiw;
    double qrtol,maxderr,maxrerr,derrnorm,pmaxderr,pmaxrerr,pderrnorm,step,crude
      ,impr,rstep,preverr;

    if (ndesin < 0) {
        ndes = -ndesin;
        dnorm = 1;
    } else {
        ndes = ndesin;
        dnorm = 0;
    }
    nreq = nfunc-ndes;
    qrtol = 1e-13;
    *fcnt = 0;
    *err = 0;
    f1 = 0;
    f2 = f1+nfunc;
    scale = f2+nfunc;
    deltav = scale+nfunc;
    guess = deltav+nvar;
    rvars = guess+nvar;
    rdeltav = rvars+nvar;
    rguess = rdeltav+nvar;
    morerw = rguess+nvar;
    mapf = 0;
    mapv = mapf+nfunc;
    moreiw = mapv+nvar;
    for (i = 0; i < nfunc; i++) {
        iw[mapf+i] = i;
    }
    for (i = 0; i < nvar; i++) {
        iw[mapv+i] = i;
    }
    func(vars,param,fret);
    *fcnt = *fcnt+1;
    pendcalcerrs(fret,nfunc,ndes,dnorm,&pmaxderr,&pmaxrerr,&pderrnorm);
    crude = 1e-6;
    for (ntrys = 0; ntrys < 2; ntrys++) {
        slowcnt = 0;
        step = 1.;
        for (;;) {
            if ((pmaxrerr <= rtol) && (pmaxderr <= dtol)) {
                return;
            }
            if (*fcnt >= maxeval) {
                goto givingUp;
            }
            pendcalcjac(func,vars,param,nfunc,nvar,lock,crude,fret,&rw[f1]
              ,jw,fcnt,&rw[scale]);
            for (i = 0; i < nfunc; i++) {
                rw[f1+i] = fret[i]*rw[scale+i];
            }
            pendlsslv(nfunc,nvar,nfunc,nvar,ndes,&iw[mapf],&iw[mapv],qrtol,dw,&
              rw[morerw],&iw[moreiw],jw,&rw[f1],&rw[deltav]);
            for (;;) {
                pendadjvars(func,vars,param,nfunc,ndes,dnorm,nvar,&rw[deltav]
                  ,step,pmaxrerr,pderrnorm,rtol,fcnt,&rw[guess],&rw[f1]);
                pendcalcerrs(&rw[f1],nfunc,ndes,dnorm,&maxderr,&maxrerr,&
                  derrnorm);
                if ((pderrnorm > derrnorm) && (pmaxrerr <= rtol) && (maxrerr > 
                  rtol) && (maxrerr <= .05)) {
                    for (i = 0; i < nvar; i++) {
                        rw[rvars+i] = rw[guess+i];
                    }
                    rstep = 1.;
                    preverr = maxrerr;
                    for (fixits = 0; fixits < 5; fixits++) {
                        pendcalcjac(func,&rw[rvars],param,nreq,nvar,lock,crude,&
                          rw[f1],&rw[f2],jw,fcnt,&rw[scale]);
                        for (i = 0; i < nreq; i++) {
                            rw[f2+i] = rw[f1+i]*rw[scale+i];
                        }
                        pendlsslv(nreq,nvar,nreq,nvar,0,&iw[mapf],&iw[mapv]
                          ,qrtol,dw,&rw[morerw],&iw[moreiw],jw,&rw[f2],&rw[
                          rdeltav]);
                        for (;;) {
                            pendadjvars(func,&rw[rvars]
                              ,param,nfunc,ndes,dnorm,nvar,&rw[rdeltav]
                              ,rstep,preverr,pderrnorm,rtol,fcnt,&rw[rguess],&rw
                              [f2]);
                            pendcalcerrs(&rw[f2],nfunc,ndes,dnorm,&maxderr,&
                              maxrerr,&derrnorm);
                            if (preverr-maxrerr >= rtol) {
                                break;
                            } else {
                                rstep = rstep*.5;
                                if (rstep < .01) {
                                    goto couldntFixReqs;
                                }
                            }
                        }
                        if (derrnorm > pderrnorm) {
                            goto couldntFixReqs;
                        }
                        for (i = 0; i < nfunc; i++) {
                            rw[f1+i] = rw[f2+i];
                        }
                        for (i = 0; i < nvar; i++) {
                            rw[rvars+i] = rw[rguess+i];
                        }
                        preverr = maxrerr;
                        if (maxrerr <= rtol) {
                            goto fixUpSucceeded;
                        }
                        rstep = rstep*2.;
                        if (rstep > 1.) {
                            rstep = 1.;
                        }
                    }
                    goto couldntFixReqs;
                    fixUpSucceeded: ;
                    for (i = 0; i < nvar; i++) {
                        rw[guess+i] = rw[rvars+i];
                    }
                }
                if ((pmaxrerr <= rtol) && (maxrerr <= rtol)) {
                    impr = pderrnorm-derrnorm;
                    if (impr < .1*dtol+.01*derrnorm) {
                        tooslow = 1;
                    } else {
                        tooslow = 0;
                    }
                } else {
                    impr = pmaxrerr-maxrerr;
                    if (impr < .01*rtol+.01*maxrerr) {
                        tooslow = 1;
                    } else {
                        tooslow = 0;
                    }
                }
                if (impr >= 0.) {
                    break;
                }
                couldntFixReqs: ;
                step = step*.5;
                if (ntrys == 1) {
                    if (step < 1e-5) {
                        goto nextcrude;
                    }
                } else {
                    if (step < .01) {
                        goto nextcrude;
                    }
                }
            }
            for (i = 0; i < nfunc; i++) {
                fret[i] = rw[f1+i];
            }
            for (i = 0; i < nvar; i++) {
                vars[i] = rw[guess+i];
            }
            pmaxderr = maxderr;
            pmaxrerr = maxrerr;
            pderrnorm = derrnorm;
            if (tooslow != 0) {
                slowcnt = slowcnt+1;
                if (slowcnt >= 3) {
                    goto nextcrude;
                }
            } else {
                slowcnt = 0;
            }
            step = step*2.;
            if (step > 1.) {
                step = 1.;
            }
        }
        nextcrude: ;
        crude = crude*.001;
    }
    givingUp: ;
    if (pmaxrerr > rtol) {
        *err = 2;
    } else {
        if (pmaxderr > dtol) {
            *err = 1;
        }
    }
}

/* Utility routine for use with pendfinteg and pendvinteg.  Work is 2*neq. */


void pendrk4m(void (*func) (double,double *,double *,double *,int *), double time, double *st, double *dst0, double *param, double step, double *nst, int neq, double *work, double *errs, double *maxerr, int *which)
{
    int i,dst1,dst2,errf;
    double step2,step3,step6,step8,err,old,ast;

    dst1 = 0;
    dst2 = dst1+neq;
    step2 = step/2.;
    step3 = step/3.;
    step6 = step/6.;
    step8 = step/8.;
    for (i = 0; i < neq; i++) {
        nst[i] = st[i]+dst0[i]*step3;
    }
    func(time+step3,nst,&work[dst1],param,&errf);
    for (i = 0; i < neq; i++) {
        nst[i] = st[i]+(dst0[i]+work[dst1+i])*step6;
    }
    func(time+step3,nst,&work[dst1],param,&errf);
    for (i = 0; i < neq; i++) {
        nst[i] = st[i]+(dst0[i]+3.*work[dst1+i])*step8;
    }
    func(time+step2,nst,&work[dst2],param,&errf);
    for (i = 0; i < neq; i++) {
        nst[i] = st[i]+(dst0[i]-3.*work[dst1+i]+4.*work[dst2+i])*step2;
    }
    func(time+step,nst,&work[dst1],param,&errf);
    *maxerr = 0.;
    *which = 0;
    for (i = 0; i < neq; i++) {
        old = nst[i];
        nst[i] = st[i]+(dst0[i]+4.*work[dst2+i]+work[dst1+i])*step6;
        err = fabs(.2*(old-nst[i]));
        ast = fabs(nst[i]);
        if (ast > .1) {
            errs[i] = err/(ast+1e-20);
        } else {
            errs[i] = 10.*err;
        }
        if (errs[i] > *maxerr) {
            *maxerr = errs[i];
            *which = i;
        }
    }
}

/* A fixed-step integrator.  Work should be dimensioned 4*neq. */


void pendfinteg(void (*func) (double,double *,double *,double *,int *), double *time, double *st, double *dst, double *param, double step, int neq, double *work, double *errest, int *status)
{
    int i,which,nst,errs,morework;
    double ttime;

    nst = 0;
    errs = nst+neq;
    morework = errs+neq;
    ttime = *time;
    if (step > 0.) {
        pendrk4m(func,ttime,st,dst,param,step,&work[nst],neq,&work[morework],&
          work[errs],errest,&which);
        for (i = 0; i < neq; i++) {
            st[i] = work[nst+i];
        }
        ttime = ttime+step;
    } else {
        *errest = 0.;
    }
    *status = 0;
    func(ttime,st,dst,param,status);
    *time = ttime;
}

/* A variable-step integrator.  Work should be dimensioned 6*neq. */

void pendvinteg(void (*func) (double,double *,double *,double *, int *), double *time, double *st, double *dst, double *param, double dt, double *step, int neqin, double tol, double *work, int *err, int *which)
{
    int i,wh,wh2,xst,xst2,xdst,errs,morework,errf,neq,earlyret;
    double ttime,ntime,xtime,tfin,stp,stp2,nstp,maxerr,minstep;

    if (neqin < 0) {
        neq = -neqin;
        earlyret = 1;
    } else {
        neq = neqin;
        earlyret = 0;
    }
    xst = 0;
    xst2 = xst+neq;
    xdst = xst2+neq;
    errs = xdst+neq;
    morework = errs+neq;
    minstep = 1e-10;
    ttime = *time;
    tfin = ttime+dt;
    stp = *step;
    if (stp < minstep) {
        stp = minstep;
    }
    *err = 0;
    if (dt <= 0.) {
        errf = 0;
        func(ttime,st,dst,param,&errf);
        if (errf != 0) {
            *err = 3;
            *which = errf;
        }
        return;
    }
    while (ttime  <  tfin) {
        if (ttime+1.25*stp >= tfin) {
            stp = tfin-ttime;
        }
        nstp = stp;
        for (;;) {
            pendrk4m(func,ttime,st,dst,param,nstp,&work[xst],neq,&work[morework]
              ,&work[errs],&maxerr,&wh);
            xtime = ttime+nstp;
            if (maxerr <= tol) {
                errf = 0;
                func(xtime,&work[xst],&work[xdst],param,&errf);
                if (errf == 0) {
                    stp2 = 2.*nstp;
                    if ((maxerr*64. <= tol) && (stp2 <= dt)) {
                        stp = stp2;
                    } else {
                        stp = nstp;
                    }
                    break;
                }
            }
            stp2 = nstp/2.;
            if (stp2 < minstep) {
                errf = 0;
                func(xtime,&work[xst],&work[xdst],param,&errf);
                if (errf != 0) {
                    *err = 3;
                    *which = errf;
                    *time = ttime;
                    *step = nstp;
                    func(ttime,st,dst,param,&errf);
                    return;
                }
                if (*err == 0) {
                    *err = 1;
                    *which = wh;
                }
                if (xtime+nstp > tfin) {
                    stp2 = tfin-xtime;
                } else {
                    stp2 = nstp;
                }
                ntime = xtime+stp2;
                if (ntime == xtime) {
                    stp = nstp;
                    break;
                }
                pendrk4m(func,xtime,&work[xst],&work[xdst],param,stp2,&work[xst2
                  ],neq,&work[morework],&work[errs],&maxerr,&wh2);
                if (work[errs+wh] <= tol) {
                    func(xtime,&work[xst],&work[xdst],param,&errf);
                    stp = nstp;
                    break;
                }
                *err = 2;
                *which = wh;
                *time = ttime;
                *step = nstp;
                func(ttime,st,dst,param,&errf);
                return;
            } else {
                nstp = stp2;
            }
        }
        ttime = xtime;
        for (i = 0; i < neq; i++) {
            st[i] = work[xst+i];
            dst[i] = work[xdst+i];
        }
        if (stp >= minstep) {
            *step = stp;
        }
        ntime = ttime+stp;
        if (ntime == ttime) {
            ttime = tfin;
        }
        if (earlyret != 0) {
            *time = ttime;
            return;
        }
    }
    *time = tfin;
}

void penddc2ang(double (*dircos)[3], double *a1, double *a2, double *a3)
{
    double quot,angle,th1,th2,th3,costh2,temp[10];

    if ((fabs((fabs(dircos[0][2])-1.)) <= 1e-10)  ) {
        if ((dircos[0][2] > 0.)  ) {
            temp[0] = 1.5707963267949;
        } else {
            temp[0] = -1.5707963267949;
        }
        th2 = temp[0];
        if ((dircos[2][1] > 1.)  ) {
            temp[0] = 1.;
        } else {
            if ((dircos[2][1] < -1.)  ) {
                temp[1] = -1.;
            } else {
                temp[1] = dircos[2][1];
            }
            temp[0] = temp[1];
        }
        angle = asin(temp[0]);
        if ((dircos[1][1] >= 0.)  ) {
            temp[0] = angle;
        } else {
            temp[0] = (3.14159265358979-angle);
        }
        th1 = temp[0];
        th3 = 0.;
    } else {
        if ((dircos[0][2] > 1.)  ) {
            temp[0] = 1.;
        } else {
            if ((dircos[0][2] < -1.)  ) {
                temp[1] = -1.;
            } else {
                temp[1] = dircos[0][2];
            }
            temp[0] = temp[1];
        }
        th2 = asin(temp[0]);
        costh2 = cos(th2);
        quot = ((-dircos[1][2])/costh2);
        if ((quot > 1.)  ) {
            temp[0] = 1.;
        } else {
            if ((quot < -1.)  ) {
                temp[1] = -1.;
            } else {
                temp[1] = quot;
            }
            temp[0] = temp[1];
        }
        angle = asin(temp[0]);
        if ((dircos[2][2] >= 0.)  ) {
            temp[0] = angle;
        } else {
            temp[0] = (3.14159265358979-angle);
        }
        th1 = temp[0];
        quot = ((-dircos[0][1])/costh2);
        if ((quot > 1.)  ) {
            temp[0] = 1.;
        } else {
            if ((quot < -1.)  ) {
                temp[1] = -1.;
            } else {
                temp[1] = quot;
            }
            temp[0] = temp[1];
        }
        angle = asin(temp[0]);
        if ((dircos[0][0] >= 0.)  ) {
            temp[0] = angle;
        } else {
            temp[0] = (3.14159265358979-angle);
        }
        th3 = temp[0];
    }
    if ((th1 > 3.14159265358979)  ) {
        temp[0] = (th1-6.28318530717959);
    } else {
        temp[0] = th1;
    }
    *a1 = temp[0];
    *a2 = th2;
    if ((th3 > 3.14159265358979)  ) {
        temp[0] = (th3-6.28318530717959);
    } else {
        temp[0] = th3;
    }
    *a3 = temp[0];
}

void penddc2quat(double (*dircos)[3], double *e1, double *e2, double *e3, double *e4)
{
    double tmp,tmp1,tmp2,tmp3,tmp4,temp[10];

    tmp = (.25*(1.-(dircos[0][0]+(dircos[1][1]+dircos[2][2]))));
    tmp4 = (.5-tmp);
    if ((tmp4 <= 0.)  ) {
        temp[0] = 0.;
    } else {
        temp[0] = sqrt(tmp4);
    }
    tmp4 = temp[0];
    tmp1 = (tmp+(.5*dircos[0][0]));
    if ((tmp1 <= 0.)  ) {
        temp[0] = 0.;
    } else {
        temp[0] = sqrt(tmp1);
    }
    tmp1 = temp[0];
    tmp2 = (tmp+(.5*dircos[1][1]));
    if ((tmp2 <= 0.)  ) {
        temp[0] = 0.;
    } else {
        temp[0] = sqrt(tmp2);
    }
    tmp2 = temp[0];
    tmp3 = (tmp+(.5*dircos[2][2]));
    if ((tmp3 <= 0.)  ) {
        temp[0] = 0.;
    } else {
        temp[0] = sqrt(tmp3);
    }
    tmp3 = temp[0];
    if (((tmp1 >= tmp2) && (tmp1 >= tmp3))  ) {
        if ((dircos[2][1] < dircos[1][2])  ) {
            temp[0] = -1.;
        } else {
            temp[0] = 1.;
        }
        tmp1 = (tmp1*temp[0]);
        if (((tmp1*(dircos[0][1]+dircos[1][0])) < 0.)  ) {
            temp[0] = -1.;
        } else {
            temp[0] = 1.;
        }
        tmp2 = (tmp2*temp[0]);
        if (((tmp1*(dircos[0][2]+dircos[2][0])) < 0.)  ) {
            temp[0] = -1.;
        } else {
            temp[0] = 1.;
        }
        tmp3 = (tmp3*temp[0]);
    } else {
        if (((tmp2 >= tmp1) && (tmp2 >= tmp3))  ) {
            if ((dircos[0][2] < dircos[2][0])  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp2 = (tmp2*temp[0]);
            if (((tmp2*(dircos[1][2]+dircos[2][1])) < 0.)  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp3 = (tmp3*temp[0]);
            if (((tmp2*(dircos[0][1]+dircos[1][0])) < 0.)  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp1 = (tmp1*temp[0]);
        } else {
            if ((dircos[1][0] < dircos[0][1])  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp3 = (tmp3*temp[0]);
            if (((tmp3*(dircos[0][2]+dircos[2][0])) < 0.)  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp1 = (tmp1*temp[0]);
            if (((tmp3*(dircos[1][2]+dircos[2][1])) < 0.)  ) {
                temp[0] = -1.;
            } else {
                temp[0] = 1.;
            }
            tmp2 = (tmp2*temp[0]);
        }
    }
    tmp = (1./sqrt(((tmp1*tmp1)+((tmp2*tmp2)+((tmp3*tmp3)+(tmp4*tmp4))))));
    *e1 = (tmp*tmp1);
    *e2 = (tmp*tmp2);
    *e3 = (tmp*tmp3);
    *e4 = (tmp*tmp4);
}

void pendang2dc(double a1, double a2, double a3, double (*dircos)[3])
{
    double cos1,cos2,cos3,sin1,sin2,sin3;

    cos1 = cos(a1);
    cos2 = cos(a2);
    cos3 = cos(a3);
    sin1 = sin(a1);
    sin2 = sin(a2);
    sin3 = sin(a3);
    dircos[0][0] = (cos2*cos3);
    dircos[0][1] = -(cos2*sin3);
    dircos[0][2] = sin2;
    dircos[1][0] = ((cos1*sin3)+(sin1*(cos3*sin2)));
    dircos[1][1] = ((cos1*cos3)-(sin1*(sin2*sin3)));
    dircos[1][2] = -(cos2*sin1);
    dircos[2][0] = ((sin1*sin3)-(cos1*(cos3*sin2)));
    dircos[2][1] = ((cos1*(sin2*sin3))+(cos3*sin1));
    dircos[2][2] = (cos1*cos2);
}

void pendquat2dc(double ie1, double ie2, double ie3, double ie4, double (*dircos)[3])
{
    double e1,e2,e3,e4,e11,e22,e33,e44,norm;

    e11 = ie1*ie1;
    e22 = ie2*ie2;
    e33 = ie3*ie3;
    e44 = ie4*ie4;
    norm = sqrt(e11+e22+e33+e44);
    if (norm == 0.) {
        e4 = 1.;
        norm = 1.;
    } else {
        e4 = ie4;
    }
    norm = 1./norm;
    e1 = ie1*norm;
    e2 = ie2*norm;
    e3 = ie3*norm;
    e4 = e4*norm;
    e11 = e1*e1;
    e22 = e2*e2;
    e33 = e3*e3;
    dircos[0][0] = 1.-(2.*(e22+e33));
    dircos[0][1] = 2.*(e1*e2-e3*e4);
    dircos[0][2] = 2.*(e1*e3+e2*e4);
    dircos[1][0] = 2.*(e1*e2+e3*e4);
    dircos[1][1] = 1.-(2.*(e11+e33));
    dircos[1][2] = 2.*(e2*e3-e1*e4);
    dircos[2][0] = 2.*(e1*e3-e2*e4);
    dircos[2][1] = 2.*(e2*e3+e1*e4);
    dircos[2][2] = 1.-(2.*(e11+e22));
}

double pendvdot(double *ivec1, double *ivec2)
{
    double dprod;

/* Compute the dot product of two vectors
*/
    dprod = ivec1[0]*ivec2[0]+ivec1[1]*ivec2[1]+ivec1[2]*ivec2[2];
    return dprod;
}

double pendvnorm(double *ivec)
{
    double norm;

/* Compute the length (norm) of a vector
*/
    norm = sqrt(pendvdot(ivec,ivec));
    return norm;
}

void pendvcopy(double *ivec, double *ovec)
{

/* Copy vector ivec to vector ovec
*/
    ovec[0] = ivec[0];
    ovec[1] = ivec[1];
    ovec[2] = ivec[2];
}

void pendvset(double sclr1, double sclr2, double sclr3, double *ovec)
{

/* Set ovec to [sclr1,sclr2,sclr3]
*/
    ovec[0] = sclr1;
    ovec[1] = sclr2;
    ovec[2] = sclr3;
}

void pendvadd(double *ivec1, double *ivec2, double *ovec)
{

/* Add two vectors
*/
    ovec[0] = ivec1[0]+ivec2[0];
    ovec[1] = ivec1[1]+ivec2[1];
    ovec[2] = ivec1[2]+ivec2[2];
}

void pendvsub(double *ivec1, double *ivec2, double *ovec)
{

/* Subtract two vectors
*/
    ovec[0] = ivec1[0]-ivec2[0];
    ovec[1] = ivec1[1]-ivec2[1];
    ovec[2] = ivec1[2]-ivec2[2];
}

void pendvmul(double sclr, double *ivec, double *ovec)
{

/* Multiply a vector by a scalar
*/
    ovec[0] = sclr*ivec[0];
    ovec[1] = sclr*ivec[1];
    ovec[2] = sclr*ivec[2];
}

void pendvaxpy(double sclr, double *ivec1, double *ivec2, double *ovec)
{

/* Multiply a vector by a scalar and add in another vector
*/
    ovec[0] = sclr*ivec1[0]+ivec2[0];
    ovec[1] = sclr*ivec1[1]+ivec2[1];
    ovec[2] = sclr*ivec1[2]+ivec2[2];
}

void pendvcross(double *ivec1, double *ivec2, double *ovec)
{
    double tempout[3];

/* Compute the cross product of two vectors
*/
    tempout[0] = ivec1[1]*ivec2[2]-ivec1[2]*ivec2[1];
    tempout[1] = ivec1[2]*ivec2[0]-ivec1[0]*ivec2[2];
    tempout[2] = ivec1[0]*ivec2[1]-ivec1[1]*ivec2[0];
    ovec[0] = tempout[0];
    ovec[1] = tempout[1];
    ovec[2] = tempout[2];
}

void pendvrot(double *ivec, double *rvec, double theta, double *ovec)
{
    double norm,idotu,ctheta,stheta,dotcos,uvec[3],icosvec[3],isinvec[3],uxisin[
      3];

/* Rotate a vector ivec around vector rvec by angle theta
*/
    norm = pendvnorm(rvec);
    if (norm == 0.) {
        ovec[0] = ivec[0];
        ovec[1] = ivec[1];
        ovec[2] = ivec[2];
        pendseterr(62,46);
        return;
    }
    stheta = sin(theta);
    ctheta = cos(theta);
    pendvmul(stheta,ivec,isinvec);
    pendvmul(ctheta,ivec,icosvec);
    norm = 1./norm;
    pendvmul(norm,rvec,uvec);
    idotu = pendvdot(ivec,uvec);
    pendvcross(uvec,isinvec,uxisin);
    dotcos = idotu*(1.-ctheta);
    pendvaxpy(dotcos,uvec,icosvec,ovec);
    pendvadd(ovec,uxisin,ovec);
}

void pendprerrmsg(FILE *fnum, int routine, int errnum)
{

    if (errnum == 0) {
        return;
    }
    fprintf(fnum,"\n");
    if (routine == 1) {
        fprintf(fnum,"pendgrav:\n");
    }
    if (routine == 2) {
        fprintf(fnum,"pendmass:\n");
    }
    if (routine == 3) {
        fprintf(fnum,"pendiner:\n");
    }
    if (routine == 4) {
        fprintf(fnum,"pendbtj:\n");
    }
    if (routine == 5) {
        fprintf(fnum,"penditj:\n");
    }
    if (routine == 6) {
        fprintf(fnum,"pendpin:\n");
    }
    if (routine == 7) {
        fprintf(fnum,"pendinit:\n");
    }
    if (routine == 8) {
        fprintf(fnum,"pendstate:\n");
    }
    if (routine == 9) {
        fprintf(fnum,"pendpsstate:\n");
    }
    if (routine == 13) {
        fprintf(fnum,"pendpresacc:\n");
    }
    if (routine == 14) {
        fprintf(fnum,"pendpresvel:\n");
    }
    if (routine == 15) {
        fprintf(fnum,"pendprespos:\n");
    }
    if (routine == 10) {
        fprintf(fnum,"pendhinget:\n");
    }
    if (routine == 11) {
        fprintf(fnum,"pendpointf:\n");
    }
    if (routine == 12) {
        fprintf(fnum,"pendbodyt:\n");
    }
    if (routine == 17) {
        fprintf(fnum,"pendderiv:\n");
    }
    if (routine == 16) {
        fprintf(fnum,"pendresid:\n");
    }
    if (routine == 18) {
        fprintf(fnum,"pendpseudo:\n");
    }
    if (routine == 19) {
        fprintf(fnum,"pendmom:\n");
    }
    if (routine == 20) {
        fprintf(fnum,"pendsys:\n");
    }
    if (routine == 21) {
        fprintf(fnum,"pendpos:\n");
    }
    if (routine == 22) {
        fprintf(fnum,"pendvel:\n");
    }
    if (routine == 23) {
        fprintf(fnum,"pendorient:\n");
    }
    if (routine == 24) {
        fprintf(fnum,"pendangvel:\n");
    }
    if (routine == 25) {
        fprintf(fnum,"pendtrans:\n");
    }
    if (routine == 26) {
        fprintf(fnum,"pendperr:\n");
    }
    if (routine == 27) {
        fprintf(fnum,"pendverr:\n");
    }
    if (routine == 28) {
        fprintf(fnum,"pendpsqdot:\n");
    }
    if (routine == 29) {
        fprintf(fnum,"pendpsudot:\n");
    }
    if (routine == 30) {
        fprintf(fnum,"pendgetht:\n");
    }
    if (routine == 31) {
        fprintf(fnum,"pendreac:\n");
    }
    if (routine == 32) {
        fprintf(fnum,"pendacc:\n");
    }
    if (routine == 33) {
        fprintf(fnum,"pendangacc:\n");
    }
    if (routine == 34) {
        fprintf(fnum,"pendmult:\n");
    }
    if (routine == 35) {
        fprintf(fnum,"pendaerr:\n");
    }
    if (routine == 36) {
        fprintf(fnum,"pendindx:\n");
    }
    if (routine == 37) {
        fprintf(fnum,"pendpres:\n");
    }
    if (routine == 38) {
        fprintf(fnum,"pendstab:\n");
    }
    if (routine == 39) {
        fprintf(fnum,"pendgetgrav:\n");
    }
    if (routine == 40) {
        fprintf(fnum,"pendgetmass:\n");
    }
    if (routine == 41) {
        fprintf(fnum,"pendgetiner:\n");
    }
    if (routine == 42) {
        fprintf(fnum,"pendgetbtj:\n");
    }
    if (routine == 43) {
        fprintf(fnum,"pendgetitj:\n");
    }
    if (routine == 44) {
        fprintf(fnum,"pendgetpin:\n");
    }
    if (routine == 45) {
        fprintf(fnum,"pendgetpres:\n");
    }
    if (routine == 46) {
        fprintf(fnum,"pendgetstab:\n");
    }
    if (routine == 47) {
        fprintf(fnum,"pendinfo:\n");
    }
    if (routine == 48) {
        fprintf(fnum,"pendjnt:\n");
    }
    if (routine == 49) {
        fprintf(fnum,"pendcons:\n");
    }
    if (routine == 50) {
        fprintf(fnum,"pendassemble:\n");
    }
    if (routine == 51) {
        fprintf(fnum,"pendinitvel:\n");
    }
    if (routine == 52) {
        fprintf(fnum,"pendstatic:\n");
    }
    if (routine == 53) {
        fprintf(fnum,"pendsteady:\n");
    }
    if (routine == 54) {
        fprintf(fnum,"pendmotion:\n");
    }
    if (routine == 55) {
        fprintf(fnum,"pendfmotion:\n");
    }
    if (routine == 56) {
        fprintf(fnum,"pendequivht:\n");
    }
    if (routine == 57) {
        fprintf(fnum,"pendmassmat:\n");
    }
    if (routine == 58) {
        fprintf(fnum,"pendfrcmat:\n");
    }
    if (routine == 59) {
        fprintf(fnum,"pendrel2cart:\n");
    }
    if (routine == 60) {
        fprintf(fnum,"pendcomptrq:\n");
    }
    if (routine == 61) {
        fprintf(fnum,"pendfulltrq:\n");
    }
    if (routine == 62) {
        fprintf(fnum,"pendvrot:\n");
    }
    if (errnum == 1) {
        fprintf(fnum,"a tree joint pin axis was zero\n");
    }
    if (errnum == 2) {
        fprintf(fnum,"the 1st inboard pin for a loop joint was zero\n");
    }
    if (errnum == 3) {
        fprintf(fnum,"the 2nd inboard pin for a loop joint was zero\n");
    }
    if (errnum == 4) {
        fprintf(fnum,"the 3rd inboard pin for a loop joint was zero\n");
    }
    if (errnum == 5) {
        fprintf(fnum,"an inboard reference line was zero\n");
    }
    if (errnum == 6) {
        fprintf(fnum,"a set of loop joint axes was not right handed\n");
    }
    if (errnum == 7) {
        fprintf(fnum,"a loop joint bodypin was zero\n");
    }
    if (errnum == 8) {
        fprintf(fnum,"a loop joint body reference line was zero\n");
    }
    if (errnum == 9) {
        fprintf(fnum,"1st/2nd pins in a loop joint not perpendicular\n");
    }
    if (errnum == 10) {
        fprintf(fnum,"2nd/3rd pins in a loop joint not perpendicular\n");
    }
    if (errnum == 11) {
        fprintf(fnum,"1st/3rd pins in a loop joint not perpendicular\n");
    }
    if (errnum == 12) {
        fprintf(fnum,"a loop jt pin and inbref were not perpendicular\n");
    }
    if (errnum == 13) {
        fprintf(fnum,"a bodypin and bodyref were not perpendicular\n");
    }
    if (errnum == 14) {
        fprintf(fnum,"Euler parameters were far from normalized\n");
    }
    if (errnum == 15) {
        fprintf(fnum,"illegal body number\n");
    }
    if (errnum == 16) {
        fprintf(fnum,"illegal joint number\n");
    }
    if (errnum == 17) {
        fprintf(fnum,"illegal axis number\n");
    }
    if (errnum == 18) {
        fprintf(fnum,"illegal axis number for this joint\n");
    }
    if (errnum == 19) {
        fprintf(fnum,"tried to set non-variable (i.e., non-?) parameter\n");
    }
    if (errnum == 20) {
        fprintf(fnum,"prescribed motion was neither 0 (off) or 1 (on)\n");
    }
    if (errnum == 21) {
        fprintf(fnum,"illegal user constraint number\n");
    }
    if (errnum == 22) {
        fprintf(fnum,"pendinit must be called first\n");
    }
    if (errnum == 23) {
        fprintf(fnum,"pendstate must be called first\n");
    }
    if (errnum == 24) {
        fprintf(fnum,"pendderiv must be called first\n");
    }
    if (errnum == 25) {
        fprintf(fnum,"a gravity ? parameter is unspecified\n");
    }
    if (errnum == 26) {
        fprintf(fnum,"a ? mass is unspecified\n");
    }
    if (errnum == 27) {
        fprintf(fnum,"a ? inertia is unspecified\n");
    }
    if (errnum == 28) {
        fprintf(fnum,"a ? tree jt pin is unspecified\n");
    }
    if (errnum == 29) {
        fprintf(fnum,"a ? tree bodyToJoint vector is unspecified\n");
    }
    if (errnum == 30) {
        fprintf(fnum,"a ? tree inbToJoint vector is unspecified\n");
    }
    if (errnum == 31) {
        fprintf(fnum,"a ? prescribed tree jt axis is unspecified\n");
    }
    if (errnum == 32) {
        fprintf(fnum,"the stabvel ? parameter is unspecified\n");
    }
    if (errnum == 33) {
        fprintf(fnum,"the stabpos ? parameter is unspecified\n");
    }
    if (errnum == 34) {
        fprintf(fnum,"a ? loop jt inboard pin is unspecified\n");
    }
    if (errnum == 35) {
        fprintf(fnum,"a ? loop jt inbref is unspecified\n");
    }
    if (errnum == 36) {
        fprintf(fnum,"a ? loop jt bodypin is unspecified\n");
    }
    if (errnum == 37) {
        fprintf(fnum,"a ? loop jt bodyref is unspecified\n");
    }
    if (errnum == 38) {
        fprintf(fnum,"a ? loop jt bodyToJoint vector is unspecified\n");
    }
    if (errnum == 39) {
        fprintf(fnum,"a ? loop jt inbToJoint vector is unspecified\n");
    }
    if (errnum == 40) {
        fprintf(fnum,"a ? prescribed loop jt axis is unspecified\n");
    }
    if (errnum == 41) {
        fprintf(fnum,"Dynamics & Library File serial nos. differ\n");
    }
    if (errnum == 42) {
        fprintf(fnum,"Dynamics & Analysis File gen. times differ\n");
    }
    if (errnum == 43) {
        fprintf(fnum,"A tree gimbal joint is in gimbal lock\n");
    }
    if (errnum == 44) {
        fprintf(fnum,"A loop gimbal joint is in gimbal lock\n");
    }
    if (errnum == 45) {
        fprintf(fnum,"Bad relative coordinate number\n");
    }
    if (errnum == 46) {
        fprintf(fnum,"The vector about which to rotate was zero\n");
    }
    if (errnum == 47) {
        fprintf(fnum,"Singular mass matrix - bad inertialess body?\n");
    }
}

void pendserialno(int *serno)
{

    *serno = 70405;
}
#ifdef __cplusplus
}
#endif
