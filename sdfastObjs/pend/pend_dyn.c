/*
Generated 27-Apr-2000 15:43:26 by SD/FAST, Kane's formulation
Generated 27-Apr-2000 15:43:26 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041



Bodies        Inb
No  Name      body Joint type  Coords q         Multipliers
--- --------- ---- ----------- ---------------- -----------------------
 -1 $ground                                    |
  0 link0      -1  Pin           0?            |  0p
  1 link1       0  Pin           1?            |  1p

*/
#include <math.h>
#include "sdfast.h"
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[2],inb_[2],outb_[2],njntdof_[2],njntc_[2],njntp_[2],firstq_[2],
      ballq_[2],firstm_[2],firstp_[2];
    int trans_[2];
} pendgtopo_t;
#define ground (pendgtopo.ground_)
#define nbod (pendgtopo.nbod_)
#define ndof (pendgtopo.ndof_)
#define ncons (pendgtopo.ncons_)
#define nloop (pendgtopo.nloop_)
#define nldof (pendgtopo.nldof_)
#define nloopc (pendgtopo.nloopc_)
#define nball (pendgtopo.nball_)
#define nlball (pendgtopo.nlball_)
#define npres (pendgtopo.npres_)
#define nuser (pendgtopo.nuser_)
#define jtype (pendgtopo.jtype_)
#define inb (pendgtopo.inb_)
#define outb (pendgtopo.outb_)
#define njntdof (pendgtopo.njntdof_)
#define njntc (pendgtopo.njntc_)
#define njntp (pendgtopo.njntp_)
#define firstq (pendgtopo.firstq_)
#define ballq (pendgtopo.ballq_)
#define firstm (pendgtopo.firstm_)
#define firstp (pendgtopo.firstp_)
#define trans (pendgtopo.trans_)

typedef struct {
    double grav_[3],mk_[2],ik_[2][3][3],pin_[2][3];
    double rk_[2][3],ri_[2][3],pres_[2],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[2];
    int gravq_[3],mkq_[2],ikq_[2][3][3],pinq_[2][3],rkq_[2][3],riq_[2][3],presq_
      [2],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[2][3],rcom_[2][3],mkrcomt_[2][3][3],psikg_[3][3],
      psrcomg_[3],psrkg_[3],psrig_[3],psmk_[2],psik_[2][3][3],psrcom_[2][3],
      psrk_[2][3],psri_[2][3];
} pendginput_t;
#define grav (pendginput.grav_)
#define mk (pendginput.mk_)
#define ik (pendginput.ik_)
#define pin (pendginput.pin_)
#define rk (pendginput.rk_)
#define ri (pendginput.ri_)
#define pres (pendginput.pres_)
#define stabvel (pendginput.stabvel_)
#define stabpos (pendginput.stabpos_)
#define rhead (pendginput.rhead_)
#define rcom (pendginput.rcom_)
#define psrcomg (pendginput.psrcomg_)
#define psrcom (pendginput.psrcom_)
#define mkrcomt (pendginput.mkrcomt_)
#define psmk (pendginput.psmk_)
#define psik (pendginput.psik_)
#define psrk (pendginput.psrk_)
#define psri (pendginput.psri_)
#define psmkg (pendginput.psmkg_)
#define psikg (pendginput.psikg_)
#define psrkg (pendginput.psrkg_)
#define psrig (pendginput.psrig_)
#define mtot (pendginput.mtot_)
#define mfrcflg (pendginput.mfrcflg_)
#define roustate (pendginput.roustate_)
#define vpkflg (pendginput.vpkflg_)
#define inerflg (pendginput.inerflg_)
#define mmflg (pendginput.mmflg_)
#define mmlduflg (pendginput.mmlduflg_)
#define wwflg (pendginput.wwflg_)
#define ltauflg (pendginput.ltauflg_)
#define fs0flg (pendginput.fs0flg_)
#define ii (pendginput.ii_)
#define mmap (pendginput.mmap_)
#define gravq (pendginput.gravq_)
#define mkq (pendginput.mkq_)
#define ikq (pendginput.ikq_)
#define pinq (pendginput.pinq_)
#define rkq (pendginput.rkq_)
#define riq (pendginput.riq_)
#define presq (pendginput.presq_)
#define stabvelq (pendginput.stabvelq_)
#define stabposq (pendginput.stabposq_)

typedef struct {
    double curtim_,q_[2],qn_[2],u_[2],cnk_[2][3][3],cnb_[2][3][3];
    double rnk_[2][3],vnk_[2][3],wk_[2][3],rnb_[2][3],vnb_[2][3],wb_[2][3],
      wbrcom_[2][3],com_[3],rnkg_[3];
    double Cik_[2][3][3],rikt_[2][3][3],Iko_[2][3][3],mkrk_[2][3][3],Cib_[2][3][
      3];
    double Wkk_[2][3],Vkk_[2][3],dik_[2][3],rpp_[2][3],rpk_[2][3],rik_[2][3],
      rik2_[2][3];
    double rpri_[2][3],Wik_[2][3],Vik_[2][3],Wirk_[2][3],rkWkk_[2][3],Wkrpk_[2][
      3],VikWkr_[2][3];
    double perr_[2],verr_[2],aerr_[2],mult_[2],ufk_[2][3],utk_[2][3],mfk_[2][3],
      mtk_[2][3];
    double utau_[2],mtau_[2],uacc_[2],uvel_[2],upos_[2];
    double s0_,c0_,s1_,c1_;
} pendgstate_t;
#define curtim (pendgstate.curtim_)
#define q (pendgstate.q_)
#define qn (pendgstate.qn_)
#define u (pendgstate.u_)
#define cnk (pendgstate.cnk_)
#define cnb (pendgstate.cnb_)
#define rnkg (pendgstate.rnkg_)
#define rnk (pendgstate.rnk_)
#define rnb (pendgstate.rnb_)
#define vnk (pendgstate.vnk_)
#define vnb (pendgstate.vnb_)
#define wk (pendgstate.wk_)
#define wb (pendgstate.wb_)
#define com (pendgstate.com_)
#define Cik (pendgstate.Cik_)
#define Cib (pendgstate.Cib_)
#define rikt (pendgstate.rikt_)
#define Iko (pendgstate.Iko_)
#define mkrk (pendgstate.mkrk_)
#define Wkk (pendgstate.Wkk_)
#define Vkk (pendgstate.Vkk_)
#define dik (pendgstate.dik_)
#define rpp (pendgstate.rpp_)
#define rpk (pendgstate.rpk_)
#define rik (pendgstate.rik_)
#define rik2 (pendgstate.rik2_)
#define rpri (pendgstate.rpri_)
#define Wik (pendgstate.Wik_)
#define Vik (pendgstate.Vik_)
#define Wirk (pendgstate.Wirk_)
#define rkWkk (pendgstate.rkWkk_)
#define Wkrpk (pendgstate.Wkrpk_)
#define VikWkr (pendgstate.VikWkr_)
#define wbrcom (pendgstate.wbrcom_)
#define perr (pendgstate.perr_)
#define verr (pendgstate.verr_)
#define aerr (pendgstate.aerr_)
#define mult (pendgstate.mult_)
#define ufk (pendgstate.ufk_)
#define utk (pendgstate.utk_)
#define utau (pendgstate.utau_)
#define mfk (pendgstate.mfk_)
#define mtk (pendgstate.mtk_)
#define mtau (pendgstate.mtau_)
#define uacc (pendgstate.uacc_)
#define uvel (pendgstate.uvel_)
#define upos (pendgstate.upos_)
#define s0 (pendgstate.s0_)
#define c0 (pendgstate.c0_)
#define s1 (pendgstate.s1_)
#define c1 (pendgstate.c1_)

typedef struct {
    double fs0_[2],qdot_[2],Otk_[2][3],Atk_[2][3],AiOiWi_[2][3],Fstar_[2][3];
    double Tstar_[2][3],Fstark_[2][3],Tstark_[2][3],IkWk_[2][3],WkIkWk_[2][3],
      gk_[2][3],IkbWk_[2][3],WkIkbWk_[2][3];
    double w0w0_[2],w1w1_[2],w2w2_[2],w0w1_[2],w0w2_[2],w1w2_[2];
    double w00w11_[2],w00w22_[2],w11w22_[2],ww_[2][2],qraux_[2];
    double mm_[2][2],mlo_[2][2],mdi_[2],IkWpk_[2][2][3],works_[2],workss_[2][2];
    double Wpk_[2][2][3],Vpk_[2][2][3],VWri_[2][2][3];
    int wmap_[2],multmap_[2],jpvt_[2],wsiz_,wrank_;
} pendglhs_t;
#define qdot (pendglhs.qdot_)
#define Otk (pendglhs.Otk_)
#define Atk (pendglhs.Atk_)
#define AiOiWi (pendglhs.AiOiWi_)
#define Fstar (pendglhs.Fstar_)
#define Tstar (pendglhs.Tstar_)
#define fs0 (pendglhs.fs0_)
#define Fstark (pendglhs.Fstark_)
#define Tstark (pendglhs.Tstark_)
#define IkWk (pendglhs.IkWk_)
#define IkbWk (pendglhs.IkbWk_)
#define WkIkWk (pendglhs.WkIkWk_)
#define WkIkbWk (pendglhs.WkIkbWk_)
#define gk (pendglhs.gk_)
#define w0w0 (pendglhs.w0w0_)
#define w1w1 (pendglhs.w1w1_)
#define w2w2 (pendglhs.w2w2_)
#define w0w1 (pendglhs.w0w1_)
#define w0w2 (pendglhs.w0w2_)
#define w1w2 (pendglhs.w1w2_)
#define w00w11 (pendglhs.w00w11_)
#define w00w22 (pendglhs.w00w22_)
#define w11w22 (pendglhs.w11w22_)
#define ww (pendglhs.ww_)
#define qraux (pendglhs.qraux_)
#define mm (pendglhs.mm_)
#define mlo (pendglhs.mlo_)
#define mdi (pendglhs.mdi_)
#define IkWpk (pendglhs.IkWpk_)
#define works (pendglhs.works_)
#define workss (pendglhs.workss_)
#define Wpk (pendglhs.Wpk_)
#define Vpk (pendglhs.Vpk_)
#define VWri (pendglhs.VWri_)
#define wmap (pendglhs.wmap_)
#define multmap (pendglhs.multmap_)
#define jpvt (pendglhs.jpvt_)
#define wsiz (pendglhs.wsiz_)
#define wrank (pendglhs.wrank_)

typedef struct {
    double fs_[2],udot_[2],tauc_[2],dyad_[2][3][3],fc_[2][3],tc_[2][3];
    double ank_[2][3],onk_[2][3],Onkb_[2][3],AOnkri_[2][3],Ankb_[2][3],AnkAtk_[2
      ][3],anb_[2][3],onb_[2][3],dyrcom_[2][3];
    double ffk_[2][3],ttk_[2][3],fccikt_[2][3],ffkb_[2][3],ttkb_[2][3];
} pendgrhs_t;
#define fs (pendgrhs.fs_)
#define udot (pendgrhs.udot_)
#define ank (pendgrhs.ank_)
#define anb (pendgrhs.anb_)
#define onk (pendgrhs.onk_)
#define onb (pendgrhs.onb_)
#define Onkb (pendgrhs.Onkb_)
#define AOnkri (pendgrhs.AOnkri_)
#define Ankb (pendgrhs.Ankb_)
#define AnkAtk (pendgrhs.AnkAtk_)
#define dyrcom (pendgrhs.dyrcom_)
#define ffk (pendgrhs.ffk_)
#define ttk (pendgrhs.ttk_)
#define fccikt (pendgrhs.fccikt_)
#define ffkb (pendgrhs.ffkb_)
#define ttkb (pendgrhs.ttkb_)
#define dyad (pendgrhs.dyad_)
#define fc (pendgrhs.fc_)
#define tc (pendgrhs.tc_)
#define tauc (pendgrhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} pendgtemp_t;
#define temp (pendgtemp.temp_)
#define tmat1 (pendgtemp.tmat1_)
#define tmat2 (pendgtemp.tmat2_)
#define tvec1 (pendgtemp.tvec1_)
#define tvec2 (pendgtemp.tvec2_)
#define tvec3 (pendgtemp.tvec3_)
#define tvec4 (pendgtemp.tvec4_)
#define tvec5 (pendgtemp.tvec5_)
#define tsc1 (pendgtemp.tsc1_)
#define tsc2 (pendgtemp.tsc2_)
#define tsc3 (pendgtemp.tsc3_)

pendgtopo_t pendgtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 2,
    /* ndof */ 2,
    /* ncons */ 2,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 2,
    /* nuser */ 0,
    /* jtype[0] */ 1,
    /* jtype[1] */ 1,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* njntdof[0] */ 1,
    /* njntdof[1] */ 1,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntp[0] */ 1,
    /* njntp[1] */ 1,
    /* firstq[0] */ 0,
    /* firstq[1] */ 1,
    /* ballq[0] */ -104,
    /* ballq[1] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstp[0] */ 0,
    /* firstp[1] */ 1,
    /* trans[0] */ 0,
    /* trans[1] */ 0,
};
pendginput_t pendginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 1.,
    /* mk[1] */ 1.,

/* inertia */
    /* ik[0][0][0] */ .083333,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .083333,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ .0833333,
    /* ik[1][0][0] */ .083333,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ .083333,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ .0833333,

/* tree hinge axis vectors */
    /* pin[0][0] */ 0.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 1.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 0.,
    /* pin[1][2] */ 1.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ .5,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ .5,
    /* rk[1][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ -.5,
    /* ri[1][2] */ 0.,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 3,
    /* gravq[1] */ 3,
    /* gravq[2] */ 3,
    /* mkq[0] */ 0,
    /* mkq[1] */ 0,
    /* ikq[0][0][0] */ 0,
    /* ikq[0][0][1] */ 0,
    /* ikq[0][0][2] */ 0,
    /* ikq[0][1][0] */ 0,
    /* ikq[0][1][1] */ 0,
    /* ikq[0][1][2] */ 0,
    /* ikq[0][2][0] */ 0,
    /* ikq[0][2][1] */ 0,
    /* ikq[0][2][2] */ 0,
    /* ikq[1][0][0] */ 0,
    /* ikq[1][0][1] */ 0,
    /* ikq[1][0][2] */ 0,
    /* ikq[1][1][0] */ 0,
    /* ikq[1][1][1] */ 0,
    /* ikq[1][1][2] */ 0,
    /* ikq[1][2][0] */ 0,
    /* ikq[1][2][1] */ 0,
    /* ikq[1][2][2] */ 0,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* rkq[0][0] */ 0,
    /* rkq[0][1] */ 0,
    /* rkq[0][2] */ 0,
    /* rkq[1][0] */ 0,
    /* rkq[1][1] */ 0,
    /* rkq[1][2] */ 0,
    /* riq[0][0] */ 3,
    /* riq[0][1] */ 3,
    /* riq[0][2] */ 3,
    /* riq[1][0] */ 0,
    /* riq[1][1] */ 0,
    /* riq[1][2] */ 0,
    /* presq[0] */ 3,
    /* presq[1] */ 3,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
pendgstate_t pendgstate;
pendglhs_t pendglhs;
pendgrhs_t pendgrhs;
pendgtemp_t pendgtemp;


void pendinit(void)
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            pendseterr(7,25);
        }
    }
    for (k = 0; k < 2; k++) {
        if (mkq[k] == 1) {
            pendseterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                pendseterr(7,29);
            }
            if (riq[k][i] == 1) {
                pendseterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    pendseterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                pendseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 2; i++) {
        for (j = i; j <= 1; j++) {
            for (k = 0; k < 3; k++) {
                Vpk[i][j][k] = 0.;
                Wpk[i][j][k] = 0.;
            }
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = 0.;
    rcom[0][1] = 0.;
    rcom[0][2] = 0.;
    rcom[1][0] = 0.;
    rcom[1][1] = 0.;
    rcom[1][2] = 0.;

/* Compute mass properties-related constants */

    mtot = 2.;
    pendserialno(&i);
    if (i != 70405) {
        pendseterr(7,41);
    }
    roustate = 1;
}

void pendstate(double timein, double *qin, double *uin)
{
/*
Compute kinematic information and store it in sdgstate.

Generated 27-Apr-2000 15:43:26 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        pendseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 2; i++) {
            if (presq[i] == 1) {
                pendseterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 2; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 2; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 2; i++) {
        q[i] = qin[i];
    }
/*
Compute sines and cosines of q
*/
    s0 = sin(q[0]);
    c0 = cos(q[0]);
    s1 = sin(q[1]);
    c1 = cos(q[1]);
/*
Compute across-axis direction cosines Cik
*/
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
    gk[0][0] = ((grav[0]*c0)+(grav[1]*s0));
    gk[0][1] = ((grav[1]*c0)-(grav[0]*s0));
    gk[1][0] = ((gk[0][0]*c1)+(gk[0][1]*s1));
    gk[1][1] = ((gk[0][1]*c1)-(gk[0][0]*s1));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[1][0][0] = ((c0*c1)-(s0*s1));
    cnk[1][0][1] = -((s0*c1)+(s1*c0));
    cnk[1][1][0] = ((s0*c1)+(s1*c0));
    cnk[1][1][1] = ((c0*c1)-(s0*s1));
    cnb[0][0][0] = c0;
    cnb[0][0][1] = -s0;
    cnb[0][0][2] = 0.;
    cnb[0][1][0] = s0;
    cnb[0][1][1] = c0;
    cnb[0][1][2] = 0.;
    cnb[0][2][0] = 0.;
    cnb[0][2][1] = 0.;
    cnb[0][2][2] = 1.;
    cnb[1][0][0] = cnk[1][0][0];
    cnb[1][0][1] = cnk[1][0][1];
    cnb[1][0][2] = 0.;
    cnb[1][1][0] = cnk[1][1][0];
    cnb[1][1][1] = cnk[1][1][1];
    cnb[1][1][2] = 0.;
    cnb[1][2][0] = 0.;
    cnb[1][2][1] = 0.;
    cnb[1][2][2] = 1.;
/*
Compute q-related auxiliary variables
*/
    rik[0][0] = ((ri[0][0]*c0)+(ri[0][1]*s0));
    rik[0][1] = (((ri[0][1]*c0)-(ri[0][0]*s0))-.5);
    rik[1][1] = -(.5+(.5*c1));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[0][0] = (ri[0][0]+(.5*s0));
    rnk[0][1] = (ri[0][1]-(.5*c0));
    rnk[1][0] = ((rnk[0][0]+(.5*s0))-(.5*cnk[1][0][1]));
    rnk[1][1] = ((rnk[0][1]-(.5*c0))-(.5*cnk[1][1][1]));
    rnb[0][0] = rnk[0][0];
    rnb[0][1] = rnk[0][1];
    rnb[0][2] = ri[0][2];
    rnb[1][0] = rnk[1][0];
    rnb[1][1] = rnk[1][1];
    rnb[1][2] = ri[0][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = (.5*(rnk[0][0]+rnk[1][0]));
    com[1] = (.5*(rnk[0][1]+rnk[1][1]));
    com[2] = ri[0][2];
/*
Compute constraint position errors
*/
    skipqs: ;
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 2; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[1][2] = (u[0]+u[1]);
    wb[0][0] = 0.;
    wb[0][1] = 0.;
    wb[0][2] = u[0];
    wb[1][0] = 0.;
    wb[1][1] = 0.;
    wb[1][2] = wk[1][2];
/*
Compute auxiliary variables involving wk
*/
/*
Compute temporaries for use in SDRHS
*/
    w2w2[0] = (u[0]*u[0]);
    w2w2[1] = (wk[1][2]*wk[1][2]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[0][0] = (.5*(u[0]*c0));
    vnk[0][1] = (.5*(u[0]*s0));
    vnk[1][0] = ((.5*(cnk[1][0][0]*wk[1][2]))+(vnk[0][0]+(.5*(u[0]*c0))));
    vnk[1][1] = ((.5*(cnk[1][1][0]*wk[1][2]))+(vnk[0][1]+(.5*(u[0]*s0))));
    vnb[0][0] = vnk[0][0];
    vnb[0][1] = vnk[0][1];
    vnb[0][2] = 0.;
    vnb[1][0] = vnk[1][0];
    vnb[1][1] = vnk[1][1];
    vnb[1][2] = 0.;
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
/*
Compute constraint velocity errors
*/
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 2; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
Initialize prescribed motions
*/
    uacc[0] = 0.;
    uvel[0] = u[0];
    upos[0] = q[0];
    uacc[1] = 0.;
    uvel[1] = u[1];
    upos[1] = q[1];
/*
 Used 0.13 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   28 adds/subtracts/negates
                     43 multiplies
                      0 divides
                     87 assignments
*/
}

void pendqdot(double *oqdot)
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(63,23);
        return;
    }
    for (i = 0; i <= 1; i++) {
        oqdot[i] = qdot[i];
    }
}

void pendu2qdot(double *uin, double *oqdot)
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(64,23);
        return;
    }
    for (i = 0; i <= 1; i++) {
        oqdot[i] = uin[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendpsstate(double *lqin)
{

    if (roustate != 2) {
        pendseterr(9,23);
        return;
    }
}

void penddovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[0][0][2] = 1.;
        Wpk[0][1][2] = 1.;
        Wpk[1][1][2] = 1.;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = .5;
        Vpk[0][1][0] = (.5+c1);
        Vpk[0][1][1] = -s1;
        Vpk[1][1][0] = .5;
        vpkflg = 1;
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    2 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      7 assignments
*/
}

void penddoltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void penddoiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[0][1] = (.5*(u[0]*u[0]));
        AiOiWi[1][1] = (Atk[0][1]+(.5*(u[0]*u[0])));
        Atk[1][0] = (AiOiWi[1][1]*s1);
        Atk[1][1] = ((.5*(wk[1][2]*wk[1][2]))+(AiOiWi[1][1]*c1));
        inerflg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    2 adds/subtracts/negates
                      8 multiplies
                      0 divides
                      4 assignments
*/
}

void penddofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        penddoltau();
        penddoiner();
/*
Compute Fstar (forces)
*/
        Fstar[0][0] = -(gk[0][0]+ufk[0][0]);
        Fstar[0][1] = ((Atk[0][1]-gk[0][1])-ufk[0][1]);
        Fstar[0][2] = -(grav[2]+ufk[0][2]);
        Fstar[1][0] = ((Atk[1][0]-gk[1][0])-ufk[1][0]);
        Fstar[1][1] = ((Atk[1][1]-gk[1][1])-ufk[1][1]);
        Fstar[1][2] = -(grav[2]+ufk[1][2]);
/*
Compute Tstar (torques)
*/
/*
Compute fs0 (RHS ignoring constraints)
*/
        penddovpk();
        fs0[0] = (utau[0]-(((.5*Fstar[0][0])-utk[0][2])+(((Fstar[1][0]*
          Vpk[0][1][0])-(Fstar[1][1]*s1))-utk[1][2])));
        fs0[1] = (utau[1]-((.5*Fstar[1][0])-utk[1][2]));
        fs0flg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   19 adds/subtracts/negates
                      4 multiplies
                      0 divides
                      8 assignments
*/
}

void penddomm(int routine)
{
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        penddovpk();
        mm[0][0] = (.4166666+((Vpk[0][1][0]*Vpk[0][1][0])+(s1*s1)));
        mm[0][1] = (.0833333+(.5*Vpk[0][1][0]));
        mm[1][1] = .3333333;
/*
Check for singular mass matrix
*/
        for (i = 0; i < 2; i++) {
            if (mm[i][i] < 1e-13) {
                pendseterr(routine,47);
            }
        }
        mmflg = 1;
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    3 adds/subtracts/negates
                      3 multiplies
                      0 divides
                      3 assignments
*/
}

void penddommldu(int routine)
{
    int i;

    if (mmlduflg == 0) {
        penddomm(routine);
/*
Numerically decompose the mass matrix
*/
        pendldudcomp(2,2,mmap,1e-13,(double *) workss,works,(double *) mm,(double *) (double *) mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 2; i++) {
            if (mdi[i] <= 1e-13) {
                pendseterr(routine,47);
            }
        }
        mmlduflg = 1;
    }
}

void pendlhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    penddommldu(routine);
    penddofs0();
}

void pendmassmat(double (*mmat)[2])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(57,23);
        return;
    }
    penddomm(57);
    for (i = 0; i < 2; i++) {
        for (j = i; j <= 1; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void pendfrcmat(double *fmat)
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(58,23);
        return;
    }
    penddofs0();
    for (i = 0; i < 2; i++) {
        fmat[i] = fs0[i];
    }
}

void pendmfrc(double *imult)
{
/*
Calculate forces due to constraint multipliers.

*/

    if (pres[0]  !=  0.) {
        mtau[0] = imult[0];
    } else {
        mtau[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        mtau[1] = imult[1];
    } else {
        mtau[1] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      4 assignments
*/
}

void pendequivht(double *tau)
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[2][3],tstareq[2][3];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[0][0] = -(gk[0][0]+ufk[0][0]);
    fstareq[0][1] = -(gk[0][1]+ufk[0][1]);
    fstareq[0][2] = -(grav[2]+ufk[0][2]);
    fstareq[1][0] = -(gk[1][0]+ufk[1][0]);
    fstareq[1][1] = -(gk[1][1]+ufk[1][1]);
    fstareq[1][2] = -(grav[2]+ufk[1][2]);
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    penddovpk();
    tau[0] = (utau[0]-(((.5*fstareq[0][0])-utk[0][2])+(((fstareq[1][0]*
      Vpk[0][1][0])-(fstareq[1][1]*s1))-utk[1][2])));
    tau[1] = (utau[1]-((.5*fstareq[1][0])-utk[1][2]));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   19 adds/subtracts/negates
                      4 multiplies
                      0 divides
                      8 assignments
*/
}

void pendfulltrq(double *udotin, double *multin, double *trqout)
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[2][3],tstarr[2][3],Otkr[2][3],Atir[2][3],Atkr[2][3];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(61,23);
        return;
    }
/*
Compute multiplier-generated forces
*/
    pendmfrc(multin);
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[1][2] = (udotin[0]+udotin[1]);
    Atkr[0][1] = (.5*(u[0]*u[0]));
    Atir[1][1] = (Atkr[0][1]+(.5*(u[0]*u[0])));
    Atkr[1][0] = ((.5*Otkr[1][2])+((Atir[1][1]*s1)+(udotin[0]*c1)));
    Atkr[1][1] = ((.5*(wk[1][2]*wk[1][2]))+((Atir[1][1]*c1)-(udotin[0]*s1)));
/*
Accumulate all forces and torques
*/
    fstarr[0][0] = (ufk[0][0]+(gk[0][0]-(.5*udotin[0])));
    fstarr[0][1] = (ufk[0][1]+(gk[0][1]-Atkr[0][1]));
    fstarr[0][2] = (grav[2]+ufk[0][2]);
    fstarr[1][0] = (ufk[1][0]+(gk[1][0]-Atkr[1][0]));
    fstarr[1][1] = (ufk[1][1]+(gk[1][1]-Atkr[1][1]));
    fstarr[1][2] = (grav[2]+ufk[1][2]);
    tstarr[0][2] = (utk[0][2]-(.0833333*udotin[0]));
    tstarr[1][2] = (utk[1][2]-(.0833333*Otkr[1][2]));
/*
Now calculate the torques
*/
    penddovpk();
    trqout[0] = -((mtau[0]+utau[0])+((tstarr[0][2]+(.5*fstarr[0][0]))+(
      tstarr[1][2]+((fstarr[1][0]*Vpk[0][1][0])-(fstarr[1][1]*s1)))));
    trqout[1] = -((mtau[1]+utau[1])+(tstarr[1][2]+(.5*fstarr[1][0])));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.05 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   29 adds/subtracts/negates
                     18 multiplies
                      0 divides
                     15 assignments
*/
}

void pendcomptrq(double *udotin, double *trqout)
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    int i;
    double multin[2];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(60,23);
        return;
    }
    for (i = 0; i < 2; i++) {
        multin[i] = 0.;
    }
    pendfulltrq(udotin,multin,trqout);
}

void pendmulttrq(double *multin, double *trqout)
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(65,23);
        return;
    }
    pendmfrc(multin);
    pendfsmult();
    for (i = 0; i < 2; i++) {
        trqout[i] = fs[i];
    }
}

void pendfs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendfsmult(void)
{

/*
Compute Fs (multiplier-generated forces only)
*/
    penddovpk();
    fs[0] = mtau[0];
    fs[1] = mtau[1];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendfsfull(void)
{

/*
Compute Fs (including all forces)
*/
    pendfsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    2 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendfsgenmult(void)
{

/*
Compute Fs (generic multiplier-generated forces)
*/
    penddovpk();
    fs[0] = (mtau[0]-((((mfk[1][1]*s1)-(mfk[1][0]*Vpk[0][1][0]))-mtk[1][2])-(
      mtk[0][2]+(.5*mfk[0][0]))));
    fs[1] = (mtau[1]+(mtk[1][2]+(.5*mfk[1][0])));
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    7 adds/subtracts/negates
                      4 multiplies
                      0 divides
                      2 assignments
*/
}

void pendfsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    pendfsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    2 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendrhs(void)
{
/*
Generated 27-Apr-2000 15:43:27 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = (mtau[0]+utau[0]);
    tauc[1] = (mtau[1]+utau[1]);
    penddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[1][2] = (udot[0]+udot[1]);
    onb[0][0] = 0.;
    onb[0][1] = 0.;
    onb[0][2] = udot[0];
    onb[1][0] = 0.;
    onb[1][1] = 0.;
    onb[1][2] = Onkb[1][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = -w2w2[0];
    dyad[0][0][1] = -udot[0];
    dyad[0][0][2] = 0.;
    dyad[0][1][0] = udot[0];
    dyad[0][1][1] = -w2w2[0];
    dyad[0][1][2] = 0.;
    dyad[0][2][0] = 0.;
    dyad[0][2][1] = 0.;
    dyad[0][2][2] = 0.;
    dyad[1][0][0] = -w2w2[1];
    dyad[1][0][1] = -Onkb[1][2];
    dyad[1][0][2] = 0.;
    dyad[1][1][0] = Onkb[1][2];
    dyad[1][1][1] = -w2w2[1];
    dyad[1][1][2] = 0.;
    dyad[1][2][0] = 0.;
    dyad[1][2][1] = 0.;
    dyad[1][2][2] = 0.;
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[1][0] = ((.5*Onkb[1][2])+(udot[0]*c1));
    Ankb[1][1] = -(udot[0]*s1);
    ank[0][0] = ((.5*(udot[0]*c0))-(Atk[0][1]*s0));
    ank[0][1] = ((.5*(udot[0]*s0))+(Atk[0][1]*c0));
    AnkAtk[1][0] = (Ankb[1][0]+Atk[1][0]);
    AnkAtk[1][1] = (Ankb[1][1]+Atk[1][1]);
    ank[1][0] = ((AnkAtk[1][0]*cnk[1][0][0])+(AnkAtk[1][1]*cnk[1][0][1]));
    ank[1][1] = ((AnkAtk[1][0]*cnk[1][1][0])+(AnkAtk[1][1]*cnk[1][1][1]));
    anb[0][0] = ank[0][0];
    anb[0][1] = ank[0][1];
    anb[0][2] = 0.;
    anb[1][0] = ank[1][0];
    anb[1][1] = ank[1][1];
    anb[1][2] = 0.;
/*
Compute constraint acceleration errors
*/
    roustate = 3;
/*
 Used 0.04 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   17 adds/subtracts/negates
                     13 multiplies
                      0 divides
                     41 assignments
*/
}

void pendpseudo(double *lqout, double *luout)
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void pendpsqdot(double *lqdout)
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void pendpsudot(double *ludout)
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void pendperr(double *errs)
{
/*
Return position constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(26,23);
        return;
    }
    if (pres[0]  !=  0.) {
        perr[0] = (q[0]-upos[0]);
    } else {
        perr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        perr[1] = (q[1]-upos[1]);
    } else {
        perr[1] = 0.;
    }
    errs[0] = perr[0];
    errs[1] = perr[1];
}

void pendverr(double *errs)
{
/*
Return velocity constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(27,23);
        return;
    }
    if (pres[0]  !=  0.) {
        verr[0] = (u[0]-uvel[0]);
    } else {
        verr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        verr[1] = (u[1]-uvel[1]);
    } else {
        verr[1] = 0.;
    }
    errs[0] = verr[0];
    errs[1] = verr[1];
}

void pendaerr(double *errs)
{
/*
Return acceleration constraint errors.

*/

    if (roustate != 3) {
        pendseterr(35,24);
        return;
    }
    if (pres[0]  !=  0.) {
        aerr[0] = (udot[0]-uacc[0]);
    } else {
        aerr[0] = 0.;
    }
    if (pres[1]  !=  0.) {
        aerr[1] = (udot[1]-uacc[1]);
    } else {
        aerr[1] = 0.;
    }
    errs[0] = aerr[0];
    errs[1] = aerr[1];
}

int pendindx(int joint, int axis)
{
    int offs,gotit;

    if (pendchkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

void pendpresacc(int joint, int axis, double prval)
{

    if (pendchkjaxis(13,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(13,23);
        return;
    }
    if (pres[pendindx(joint,axis)]  !=  0.) {
        uacc[pendindx(joint,axis)] = prval;
    }
}

void pendpresvel(int joint, int axis, double prval)
{

    if (pendchkjaxis(14,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(14,23);
        return;
    }
    if (pres[pendindx(joint,axis)]  !=  0.) {
        uvel[pendindx(joint,axis)] = prval;
    }
}

void pendprespos(int joint, int axis, double prval)
{

    if (pendchkjaxis(15,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(15,23);
        return;
    }
    if (pres[pendindx(joint,axis)]  !=  0.) {
        upos[pendindx(joint,axis)] = prval;
    }
}

void pendgetht(int joint, int axis, double *torque)
{

    if (pendchkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        pendseterr(30,24);
        return;
    }
    *torque = tauc[pendindx(joint,axis)];
}

void pendhinget(int joint, int axis, double torque)
{

    if (pendchkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[pendindx(joint,axis)] = mtau[pendindx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[pendindx(joint,axis)] = utau[pendindx(joint,axis)]+torque;
    }
}

void pendpointf(int body, double *point, double *force)
{
    double torque[3];

    if (pendchkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void pendbodyt(int body, double *torque)
{

    if (pendchkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        pendseterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void penddoww(int routine)
{
    double pp[2][2],dpp[2][2];
    int i,j,c;
    double sum;
    double dfk[2][3],dtk[2][3],dtau[2],dltci[1][3],dltc[1][3],dlfci[1][3],dlfc[1
      ][3];
    double dTinb[1][3],dToutb[1][3],dltaufi[1][3],dltaufo[1][3],dltauti[1][3],
      dltauto[1][3];
    double dfs[2],row[2],dinvrow[2];

    roustate = 2;
    if (wwflg == 0) {
/*
Compute constraint effects
*/
        penddovpk();
        penddommldu(routine);
/*
Constraint 0 (prescribed motion)
*/
        if (pres[0]  !=  0.) {
            dtau[0] = 1.;
        } else {
            dtau[0] = 0.;
        }
        dfs[0] = dtau[0];
        dfs[1] = 0.;
        pendldubsl(2,2,mmap,(double *) mlo,dfs,row);
        pendldubsd(2,2,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 1; i++) {
            pp[0][i] = row[i];
            dpp[i][0] = dinvrow[i];
        }
        wmap[0] = 0;
/*
Constraint 1 (prescribed motion)
*/
        if (pres[1]  !=  0.) {
            dtau[1] = 1.;
        } else {
            dtau[1] = 0.;
        }
        dfs[1] = dtau[1];
        dfs[0] = 0.;
        pendldubsl(2,2,mmap,(double *) mlo,dfs,row);
        pendldubsd(2,2,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 1; i++) {
            pp[1][i] = row[i];
            dpp[i][1] = dinvrow[i];
        }
        wmap[1] = 1;
/*
Produce constraint coefficient matrix WW
*/
        for (c = 0; c <= 1; c++) {
            for (i = c; i <= 1; i++) {
                sum = 0.;
                for (j = 0; j <= 1; j++) {
                    sum = sum+pp[wmap[c]][j]*dpp[j][wmap[i]];
                }
                ww[wmap[c]][wmap[i]] = sum;
                ww[wmap[i]][wmap[c]] = sum;
            }
        }
/*
Form QR decomposition of WW
*/
        pendqrdcomp(2,2,2,2,wmap,wmap,(double *) ww,qraux,jpvt);
        wwflg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    6 adds/subtracts/negates
                      6 multiplies
                      0 divides
                     31 assignments
*/
}

void pendxudot0(int routine, double *oudot0)
{
/*
Compute unconstrained equations
*/
    int i;

    pendlhs(routine);
/*
Solve equations ignoring constraints
*/
    pendfs0();
    pendldubslv(2,2,mmap,works,(double *) mlo,mdi,fs,udot);
    for (i = 0; i <= 1; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendudot0(double *oudot0)
{

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(66,23);
        return;
    }
    pendxudot0(66,oudot0);
}

void pendsetudot(double *iudot)
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(68,23);
        return;
    }
    for (i = 0; i <= 1; i++) {
        udot[i] = iudot[i];
    }
    pendrhs();
}

void pendxudotm(int routine, double *imult, double *oudotm)
{
/*
Compute udots due only to multipliers
*/
    int i;

    pendlhs(routine);
    pendmfrc(imult);
    pendfsmult();
    pendldubslv(2,2,mmap,works,(double *) mlo,mdi,fs,udot);
    for (i = 0; i <= 1; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      2 assignments
*/
}

void pendudotm(double *imult, double *oudotm)
{

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(67,23);
        return;
    }
    pendxudotm(67,imult,oudotm);
}

void pendderiv(double *oqdot, double *oudot)
{
/*
This is the derivative section for a 2-body ground-based
system with 2 hinge degree(s) of freedom.
2 of the degrees of freedom may follow prescribed motion.
There are 2 constraints.
*/
    double workr[2],bb[2],b0[2],v0[2],p0[2];
    int iwork[2];
    int i,j;
    double udot0[2],udot1[2];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        pendseterr(17,32);
    }
    if (stabposq == 1) {
        pendseterr(17,33);
    }
    wsiz = 2;
/*
Compute unconstrained equations
*/
    pendxudot0(17,udot0);
    pendrhs();
    pendaerr(b0);
    if (stabvel  !=  0.) {
        pendverr(v0);
    }
    if (stabpos  !=  0.) {
        pendperr(p0);
    }
/*
Stabilize constraints using Baumgarte's method
*/
    for (i = 0; i <= 1; i++) {
        bb[i] = -b0[i];
    }
    if (stabvel  !=  0.) {
        for (i = 0; i <= 1; i++) {
            bb[i] = bb[i]-stabvel*v0[i];
        }
    }
    if (stabpos  !=  0.) {
        for (i = 0; i <= 1; i++) {
            bb[i] = bb[i]-stabpos*p0[i];
        }
    }
/*
Compute and decompose constraint matrix WW
*/
    penddoww(17);
/*
Numerically solve for constraint multipliers
*/
    pendqrbslv(2,2,2,2,wmap,wmap,1e-13,workr,iwork,(double *) ww,qraux,jpvt,bb,mult,&wrank)
      ;
    for (i = 0; i <= 1; i++) {
        multmap[i] = 0;
    }
    for (i = 0; i < wrank; i++) {
        multmap[jpvt[i]] = 1;
    }
    j = 0;
    for (i = 0; i <= 1; i++) {
        if (multmap[i] != 0) {
            multmap[j] = wmap[i];
            j = j+1;
        }
    }
/*
Compute final udots
*/
    pendxudotm(17,mult,udot1);
    for (i = 0; i <= 1; i++) {
        udot[i] = udot0[i]+udot1[i];
    }
    pendrhs();
    for (i = 0; i <= 1; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 1; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    8 adds/subtracts/negates
                      4 multiplies
                      0 divides
                     12 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void pendresid(double *eqdot, double *eudot, double *emults, double *resid)
{
    int i;
    double uderrs[2],p0[2];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        pendseterr(16,33);
    }
    pendfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 2; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 2; i++) {
        resid[2+i] = uderrs[i];
    }
    pendverr(&resid[4]);
    if (stabpos  !=  0.) {
        pendperr(p0);
        for (i = 0; i < 2; i++) {
            resid[4+i] = resid[4+i]+stabpos*p0[i];
        }
    }
    for (i = 0; i < 2; i++) {
        udot[i] = eudot[i];
    }
    for (i = 0; i < 2; i++) {
        mult[i] = emults[i];
    }
    pendrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    4 adds/subtracts/negates
                      2 multiplies
                      0 divides
                     10 assignments
*/
}

void pendmult(double *omults, int *owrank, int *omultmap)
{
    int i;

    if (roustate != 3) {
        pendseterr(34,24);
        return;
    }
    for (i = 0; i < 2; i++) {
        omults[i] = mult[i];
        if (i <= wrank-1) {
            omultmap[i] = multmap[i];
        } else {
            omultmap[i] = -1;
        }
    }
    *owrank = wrank;
}

void pendreac(double (*force)[3], double (*torque)[3])
{
/*
Generated 27-Apr-2000 15:43:28 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

    if (roustate != 3) {
        pendseterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[1][0] = ((AnkAtk[1][0]-gk[1][0])-ufk[1][0]);
    fc[1][1] = ((AnkAtk[1][1]-gk[1][1])-ufk[1][1]);
    fc[1][2] = -(grav[2]+ufk[1][2]);
    tc[1][0] = -(utk[1][0]+(.5*fc[1][2]));
    tc[1][1] = -utk[1][1];
    tc[1][2] = ((.0833333*Onkb[1][2])-(utk[1][2]-(.5*fc[1][0])));
    fccikt[1][0] = ((fc[1][0]*c1)-(fc[1][1]*s1));
    fccikt[1][1] = ((fc[1][0]*s1)+(fc[1][1]*c1));
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = (ufk[0][0]-fccikt[1][0]);
    ffk[0][1] = (ufk[0][1]-fccikt[1][1]);
    ffk[0][2] = (ufk[0][2]-fccikt[1][2]);
    ttk[0][0] = (utk[0][0]-(((tc[1][0]*c1)-(tc[1][1]*s1))-(.5*fccikt[1][2])));
    ttk[0][1] = (utk[0][1]-((tc[1][0]*s1)+(tc[1][1]*c1)));
    ttk[0][2] = (utk[0][2]-(tc[1][2]+(.5*fccikt[1][0])));
    fc[0][0] = (((.5*udot[0])-gk[0][0])-ffk[0][0]);
    fc[0][1] = ((Atk[0][1]-gk[0][1])-ffk[0][1]);
    fc[0][2] = -(ffk[0][2]+grav[2]);
    tc[0][0] = -(ttk[0][0]+(.5*fc[0][2]));
    tc[0][1] = -ttk[0][1];
    tc[0][2] = ((.0833333*udot[0])-(ttk[0][2]-(.5*fc[0][0])));
    force[0][0] = fc[0][0];
    torque[0][0] = tc[0][0];
    force[0][1] = fc[0][1];
    torque[0][1] = tc[0][1];
    force[0][2] = fc[0][2];
    torque[0][2] = tc[0][2];
    force[1][0] = fc[1][0];
    torque[1][0] = tc[1][0];
    force[1][1] = fc[1][1];
    torque[1][1] = tc[1][1];
    force[1][2] = fc[1][2];
    torque[1][2] = tc[1][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.05 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   34 adds/subtracts/negates
                     17 multiplies
                      0 divides
                     33 assignments
*/
}

void pendmom(double *lm, double *am, double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 27-Apr-2000 15:43:28 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[2][3],hnk[2][3];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(19,23);
        return;
    }
    lm[0] = (vnk[0][0]+vnk[1][0]);
    lm[1] = (vnk[0][1]+vnk[1][1]);
    lm[2] = 0.;
    am[0] = ((lm[1]*ri[0][2])-((ri[0][2]*vnk[0][1])+(ri[0][2]*vnk[1][1])));
    am[1] = (((ri[0][2]*vnk[0][0])+(ri[0][2]*vnk[1][0]))-(lm[0]*ri[0][2]));
    am[2] = ((((.0833333*u[0])+((rnk[0][0]*vnk[0][1])-(rnk[0][1]*vnk[0][0])))+((
      .0833333*wk[1][2])+((rnk[1][0]*vnk[1][1])-(rnk[1][1]*vnk[1][0]))))-((
      com[0]*lm[1])-(com[1]*lm[0])));
    *ke = (.5*(((.0833333*(u[0]*u[0]))+((vnk[0][0]*vnk[0][0])+(vnk[0][1]*
      vnk[0][1])))+((.0833333*(wk[1][2]*wk[1][2]))+((vnk[1][0]*vnk[1][0])+(
      vnk[1][1]*vnk[1][1])))));
/*
 Used 0.03 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain   18 adds/subtracts/negates
                     23 multiplies
                      0 divides
                      7 assignments
*/
}

void pendsys(double *mtoto, double *cm, double (*icm)[3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 27-Apr-2000 15:43:28 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[2][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(20,23);
        return;
    }
    *mtoto = 2.;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = ri[0][2];
    icm[0][0] = (.083333+((((.083333*((cnk[1][0][0]*cnk[1][0][0])+(cnk[1][0][1]*
      cnk[1][0][1])))+((ri[0][2]*ri[0][2])+(rnk[1][1]*rnk[1][1])))+((ri[0][2]*
      ri[0][2])+(rnk[0][1]*rnk[0][1])))-(2.*((com[1]*com[1])+(ri[0][2]*ri[0][2])
      ))));
    icm[0][1] = ((2.*(com[0]*com[1]))+(((.083333*((cnk[1][0][0]*cnk[1][1][0])+(
      cnk[1][0][1]*cnk[1][1][1])))-(rnk[1][0]*rnk[1][1]))-(rnk[0][0]*rnk[0][1]))
      );
    icm[0][2] = ((2.*(com[0]*ri[0][2]))-((ri[0][2]*rnk[0][0])+(ri[0][2]*
      rnk[1][0])));
    icm[1][0] = icm[0][1];
    icm[1][1] = (.083333+((((.083333*((cnk[1][1][0]*cnk[1][1][0])+(cnk[1][1][1]*
      cnk[1][1][1])))+((ri[0][2]*ri[0][2])+(rnk[1][0]*rnk[1][0])))+((ri[0][2]*
      ri[0][2])+(rnk[0][0]*rnk[0][0])))-(2.*((com[0]*com[0])+(ri[0][2]*ri[0][2])
      ))));
    icm[1][2] = ((2.*(com[1]*ri[0][2]))-((ri[0][2]*rnk[0][1])+(ri[0][2]*
      rnk[1][1])));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    icm[2][2] = (.1666666+((((rnk[0][0]*rnk[0][0])+(rnk[0][1]*rnk[0][1]))+((
      rnk[1][0]*rnk[1][0])+(rnk[1][1]*rnk[1][1])))-(2.*((com[0]*com[0])+(com[1]*
      com[1])))));
/*
 Used 0.07 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   30 adds/subtracts/negates
                     42 multiplies
                      0 divides
                     13 assignments
*/
}

void pendpos(int body, double *pt, double *loc)
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (pendchkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

void pendvel(int body, double *pt, double *velo)
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (pendchkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

void pendorient(int body, double (*dircos)[3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (pendchkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

void pendangvel(int body, double *avel)
{
/*
Return angular velocity of the body.

*/

    if (pendchkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

void pendtrans(int frbod, double *ivec, int tobod, double *ovec)
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (pendchkbnum(25,frbod) != 0) {
        return;
    }
    if (pendchkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(25,23);
        return;
    }
    if (frbod == tobod) {
        pendvcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        pendvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        pendvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

void pendrel2cart(int coord, int body, double *point, double *linchg, double *rotchg)
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 1)) {
        pendseterr(59,45);
        return;
    }
    if (pendchkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        pendseterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        pendvset(0.,0.,0.,linchg);
        pendvset(0.,0.,0.,rotchg);
        return;
    }
    penddovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        pendvcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    pendvcross(rotchg,pv,linchg);
    pendvadd(linchg,lin,linchg);
}

void pendacc(int body, double *pt, double *accel)
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (pendchkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        pendseterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

void pendangacc(int body, double *aacc)
{
/*
Return angular acceleration of the body.

*/

    if (pendchkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        pendseterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

void pendgrav(double *gravin)
{

    grav[0] = gravin[0];
    gravq[0] = 3;
    grav[1] = gravin[1];
    gravq[1] = 3;
    grav[2] = gravin[2];
    gravq[2] = 3;
    roustate = 0;
}

void pendmass(int body, double massin)
{

    if (pendchkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        pendseterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        pendseterr(2,19);
    }
    roustate = 0;
}

void pendiner(int body, double (*inerin)[3])
{
    int anyques;

    if (pendchkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        pendseterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        pendseterr(3,19);
    }
    roustate = 0;
}

void pendbtj(int joint, double *btjin)
{
    int anyques;

    if (pendchkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        pendseterr(4,19);
    }
    roustate = 0;
}

void penditj(int joint, double *itjin)
{
    int anyques;

    if (pendchkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        pendseterr(5,19);
    }
    roustate = 0;
}

void pendpin(int joint, int pinno, double *pinin)
{
    int anyques,offs;

    if (pendchkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        pendseterr(6,19);
    }
    roustate = 0;
}

void pendpres(int joint, int axis, int presin)
{
    int anyques;

    if (pendchkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        pendseterr(37,20);
    }
    anyques = 0;
    if (presq[pendindx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[pendindx(joint,axis)] = 1.;
        } else {
            pres[pendindx(joint,axis)] = 0.;
        }
        presq[pendindx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        pendseterr(37,19);
    }
    wwflg = 0;
}

void pendstab(double velin, double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void pendgetgrav(double *gravout)
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void pendgetmass(int body, double *massout)
{

    if (pendchkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        pendseterr(40,15);
        return;
    }
    *massout = mk[body];
}

void pendgetiner(int body, double (*inerout)[3])
{

    if (pendchkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        pendseterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

void pendgetbtj(int joint, double *btjout)
{

    if (pendchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void pendgetitj(int joint, double *itjout)
{

    if (pendchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void pendgetpin(int joint, int pinno, double *pinout)
{
    int offs;

    if (pendchkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

void pendgetpres(int joint, int axis, int *presout)
{

    if (pendchkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[pendindx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void pendgetstab(double *velout, double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void pendinfo(int *info)
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 2;
/* info entries from 12-49 are reserved */
}

void pendjnt(int joint, int *info, int *tran)
{
    int i,offs;

    if (pendchkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

void pendcons(int consno, int *info)
{

    if (pendchkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

int pendchkbnum(int routine, int bnum)
{

    if ((bnum < -1) || (bnum > 1)) {
        pendseterr(routine,15);
        return 1;
    }
    return 0;
}

int pendchkjnum(int routine, int jnum)
{

    if ((jnum < 0) || (jnum > 1)) {
        pendseterr(routine,16);
        return 1;
    }
    return 0;
}

int pendchkucnum(int routine, int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        pendseterr(routine,21);
        return 1;
    }
    return 0;
}

int pendchkjaxis(int routine, int jnum, int axnum)
{
    int maxax;

    if (pendchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        pendseterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        pendseterr(routine,18);
        return 1;
    }
    return 0;
}

int pendchkjpin(int routine, int jnum, int pinno)
{
    int maxax,pinok;

    if (pendchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        pendseterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        pendseterr(routine,18);
        return 1;
    }
    return 0;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void pendst2ang(double *st, double *stang)
{
    int i;

    for (i = 0; i < 2; i++) {
        stang[i] = st[i];
    }
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void pendang2st(double *stang, double *st)
{
    int i;

    for (i = 0; i < 2; i++) {
        st[i] = stang[i];
    }
}

/* Normalize Euler parameters in state. */

void pendnrmsterr(double *st, double *normst, int routine)
{
    int i;

    for (i = 0; i < 2; i++) {
        normst[i] = st[i];
    }
}

void pendnormst(double *st, double *normst)
{

    pendnrmsterr(st,normst,0);
}

void pendgentime(int *gentm)
{

    *gentm = 154326;
}
/*
Done. CPU seconds used: 0.78  Memory used: 901120 bytes.
Equation complexity:
  sdstate:    28 adds    43 multiplies     0 divides    87 assignments
  sdderiv:   109 adds    92 multiplies    11 divides   271 assignments
  sdresid:    52 adds    33 multiplies     0 divides    77 assignments
  sdreac:     34 adds    17 multiplies     0 divides    33 assignments
  sdmom:      18 adds    23 multiplies     0 divides     7 assignments
  sdsys:      30 adds    42 multiplies     0 divides    13 assignments
*/
