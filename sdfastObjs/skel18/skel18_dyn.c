/*
Generated 23-Nov-1999 14:30:31 by SD/FAST, Kane's formulation
Generated 23-Nov-1999 14:30:31 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041



Bodies             Inb
No  Name           body Joint type  Coords q
--- -------------- ---- ----------- ----------------
 -1 $ground                                         
  0 Hip             -1  Sixdof        0   1   2 
                        ...           3   4   5  37 
  1 Trunk_comp       0  Gimbal        6   7   8     
  2 Neck             1  Gimbal        9  10  11     
  3 Head_comp        2  Pin          12             
  4 Left_Shoulder    1  U-joint      13  14         
  5 Left_Forearm     4  U-joint      15  16         
  6 Left_Hand        5  U-joint      17  18         
  7 Right_Shoulder   1  U-joint      19  20         
  8 Right_Forearm    7  U-joint      21  22         
  9 Right_Hand       8  U-joint      23  24         
 10 Left_Thigh       0  Gimbal       25  26  27     
 11 Left_Shin       10  Pin          28             
 12 Left_Foot       11  U-joint      29  30         
 13 Right_Thigh      0  Gimbal       31  32  33     
 14 Right_Shin      13  Pin          34             
 15 Right_Foot      14  U-joint      35  36         

*/
#include <math.h>
#include "sdfast.h"
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[16],inb_[16],outb_[16],njntdof_[16],njntc_[16],njntp_[16],firstq_
      [16],ballq_[16],firstm_[16],firstp_[16];
    int trans_[37];
} skel18gtopo_t;
#define ground (skel18gtopo.ground_)
#define nbod (skel18gtopo.nbod_)
#define ndof (skel18gtopo.ndof_)
#define ncons (skel18gtopo.ncons_)
#define nloop (skel18gtopo.nloop_)
#define nldof (skel18gtopo.nldof_)
#define nloopc (skel18gtopo.nloopc_)
#define nball (skel18gtopo.nball_)
#define nlball (skel18gtopo.nlball_)
#define npres (skel18gtopo.npres_)
#define nuser (skel18gtopo.nuser_)
#define jtype (skel18gtopo.jtype_)
#define inb (skel18gtopo.inb_)
#define outb (skel18gtopo.outb_)
#define njntdof (skel18gtopo.njntdof_)
#define njntc (skel18gtopo.njntc_)
#define njntp (skel18gtopo.njntp_)
#define firstq (skel18gtopo.firstq_)
#define ballq (skel18gtopo.ballq_)
#define firstm (skel18gtopo.firstm_)
#define firstp (skel18gtopo.firstp_)
#define trans (skel18gtopo.trans_)

typedef struct {
    double grav_[3],mk_[16],ik_[16][3][3],pin_[37][3];
    double rk_[16][3],ri_[16][3],pres_[37],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[37];
    int gravq_[3],mkq_[16],ikq_[16][3][3],pinq_[37][3],rkq_[16][3],riq_[16][3],
      presq_[37],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[16][3],rcom_[16][3],mkrcomt_[16][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[37],psik_[37][3][3],psrcom_[37][3
      ],psrk_[37][3],psri_[37][3];
} skel18ginput_t;
#define grav (skel18ginput.grav_)
#define mk (skel18ginput.mk_)
#define ik (skel18ginput.ik_)
#define pin (skel18ginput.pin_)
#define rk (skel18ginput.rk_)
#define ri (skel18ginput.ri_)
#define pres (skel18ginput.pres_)
#define stabvel (skel18ginput.stabvel_)
#define stabpos (skel18ginput.stabpos_)
#define rhead (skel18ginput.rhead_)
#define rcom (skel18ginput.rcom_)
#define psrcomg (skel18ginput.psrcomg_)
#define psrcom (skel18ginput.psrcom_)
#define mkrcomt (skel18ginput.mkrcomt_)
#define psmk (skel18ginput.psmk_)
#define psik (skel18ginput.psik_)
#define psrk (skel18ginput.psrk_)
#define psri (skel18ginput.psri_)
#define psmkg (skel18ginput.psmkg_)
#define psikg (skel18ginput.psikg_)
#define psrkg (skel18ginput.psrkg_)
#define psrig (skel18ginput.psrig_)
#define mtot (skel18ginput.mtot_)
#define mfrcflg (skel18ginput.mfrcflg_)
#define roustate (skel18ginput.roustate_)
#define vpkflg (skel18ginput.vpkflg_)
#define inerflg (skel18ginput.inerflg_)
#define mmflg (skel18ginput.mmflg_)
#define mmlduflg (skel18ginput.mmlduflg_)
#define wwflg (skel18ginput.wwflg_)
#define ltauflg (skel18ginput.ltauflg_)
#define fs0flg (skel18ginput.fs0flg_)
#define ii (skel18ginput.ii_)
#define mmap (skel18ginput.mmap_)
#define gravq (skel18ginput.gravq_)
#define mkq (skel18ginput.mkq_)
#define ikq (skel18ginput.ikq_)
#define pinq (skel18ginput.pinq_)
#define rkq (skel18ginput.rkq_)
#define riq (skel18ginput.riq_)
#define presq (skel18ginput.presq_)
#define stabvelq (skel18ginput.stabvelq_)
#define stabposq (skel18ginput.stabposq_)

typedef struct {
    double curtim_,q_[38],qn_[38],u_[37],cnk_[37][3][3],cnb_[16][3][3];
    double rnk_[37][3],vnk_[37][3],wk_[37][3],rnb_[16][3],vnb_[16][3],wb_[16][3]
      ,wbrcom_[16][3],com_[3],rnkg_[3];
    double Cik_[37][3][3],rikt_[37][3][3],Iko_[37][3][3],mkrk_[37][3][3],Cib_[16
      ][3][3];
    double Wkk_[37][3],Vkk_[37][3],dik_[37][3],rpp_[37][3],rpk_[37][3],rik_[37][
      3],rik2_[37][3];
    double rpri_[37][3],Wik_[37][3],Vik_[37][3],Wirk_[37][3],rkWkk_[37][3],
      Wkrpk_[37][3],VikWkr_[37][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[16][3],utk_[16][3],mfk_[16][
      3],mtk_[16][3];
    double utau_[37],mtau_[37],uacc_[37],uvel_[37],upos_[38];
    double s6_,c6_,s7_,c7_,s8_,c8_,s9_,c9_,s10_,c10_,s11_,c11_,s12_,c12_,s13_,
      c13_,s14_,c14_,s15_,c15_,s16_,c16_,s17_,c17_,s18_,c18_,s19_,c19_,s20_,c20_
      ,s21_,c21_,s22_,c22_,s23_,c23_,s24_,c24_,s25_,c25_,s26_,c26_,s27_,c27_,
      s28_,c28_,s29_,c29_,s30_,c30_,s31_,c31_,s32_,c32_,s33_,c33_,s34_,c34_,s35_
      ,c35_,s36_,c36_;
} skel18gstate_t;
#define curtim (skel18gstate.curtim_)
#define q (skel18gstate.q_)
#define qn (skel18gstate.qn_)
#define u (skel18gstate.u_)
#define cnk (skel18gstate.cnk_)
#define cnb (skel18gstate.cnb_)
#define rnkg (skel18gstate.rnkg_)
#define rnk (skel18gstate.rnk_)
#define rnb (skel18gstate.rnb_)
#define vnk (skel18gstate.vnk_)
#define vnb (skel18gstate.vnb_)
#define wk (skel18gstate.wk_)
#define wb (skel18gstate.wb_)
#define com (skel18gstate.com_)
#define Cik (skel18gstate.Cik_)
#define Cib (skel18gstate.Cib_)
#define rikt (skel18gstate.rikt_)
#define Iko (skel18gstate.Iko_)
#define mkrk (skel18gstate.mkrk_)
#define Wkk (skel18gstate.Wkk_)
#define Vkk (skel18gstate.Vkk_)
#define dik (skel18gstate.dik_)
#define rpp (skel18gstate.rpp_)
#define rpk (skel18gstate.rpk_)
#define rik (skel18gstate.rik_)
#define rik2 (skel18gstate.rik2_)
#define rpri (skel18gstate.rpri_)
#define Wik (skel18gstate.Wik_)
#define Vik (skel18gstate.Vik_)
#define Wirk (skel18gstate.Wirk_)
#define rkWkk (skel18gstate.rkWkk_)
#define Wkrpk (skel18gstate.Wkrpk_)
#define VikWkr (skel18gstate.VikWkr_)
#define wbrcom (skel18gstate.wbrcom_)
#define perr (skel18gstate.perr_)
#define verr (skel18gstate.verr_)
#define aerr (skel18gstate.aerr_)
#define mult (skel18gstate.mult_)
#define ufk (skel18gstate.ufk_)
#define utk (skel18gstate.utk_)
#define utau (skel18gstate.utau_)
#define mfk (skel18gstate.mfk_)
#define mtk (skel18gstate.mtk_)
#define mtau (skel18gstate.mtau_)
#define uacc (skel18gstate.uacc_)
#define uvel (skel18gstate.uvel_)
#define upos (skel18gstate.upos_)
#define s6 (skel18gstate.s6_)
#define c6 (skel18gstate.c6_)
#define s7 (skel18gstate.s7_)
#define c7 (skel18gstate.c7_)
#define s8 (skel18gstate.s8_)
#define c8 (skel18gstate.c8_)
#define s9 (skel18gstate.s9_)
#define c9 (skel18gstate.c9_)
#define s10 (skel18gstate.s10_)
#define c10 (skel18gstate.c10_)
#define s11 (skel18gstate.s11_)
#define c11 (skel18gstate.c11_)
#define s12 (skel18gstate.s12_)
#define c12 (skel18gstate.c12_)
#define s13 (skel18gstate.s13_)
#define c13 (skel18gstate.c13_)
#define s14 (skel18gstate.s14_)
#define c14 (skel18gstate.c14_)
#define s15 (skel18gstate.s15_)
#define c15 (skel18gstate.c15_)
#define s16 (skel18gstate.s16_)
#define c16 (skel18gstate.c16_)
#define s17 (skel18gstate.s17_)
#define c17 (skel18gstate.c17_)
#define s18 (skel18gstate.s18_)
#define c18 (skel18gstate.c18_)
#define s19 (skel18gstate.s19_)
#define c19 (skel18gstate.c19_)
#define s20 (skel18gstate.s20_)
#define c20 (skel18gstate.c20_)
#define s21 (skel18gstate.s21_)
#define c21 (skel18gstate.c21_)
#define s22 (skel18gstate.s22_)
#define c22 (skel18gstate.c22_)
#define s23 (skel18gstate.s23_)
#define c23 (skel18gstate.c23_)
#define s24 (skel18gstate.s24_)
#define c24 (skel18gstate.c24_)
#define s25 (skel18gstate.s25_)
#define c25 (skel18gstate.c25_)
#define s26 (skel18gstate.s26_)
#define c26 (skel18gstate.c26_)
#define s27 (skel18gstate.s27_)
#define c27 (skel18gstate.c27_)
#define s28 (skel18gstate.s28_)
#define c28 (skel18gstate.c28_)
#define s29 (skel18gstate.s29_)
#define c29 (skel18gstate.c29_)
#define s30 (skel18gstate.s30_)
#define c30 (skel18gstate.c30_)
#define s31 (skel18gstate.s31_)
#define c31 (skel18gstate.c31_)
#define s32 (skel18gstate.s32_)
#define c32 (skel18gstate.c32_)
#define s33 (skel18gstate.s33_)
#define c33 (skel18gstate.c33_)
#define s34 (skel18gstate.s34_)
#define c34 (skel18gstate.c34_)
#define s35 (skel18gstate.s35_)
#define c35 (skel18gstate.c35_)
#define s36 (skel18gstate.s36_)
#define c36 (skel18gstate.c36_)

typedef struct {
    double fs0_[37],qdot_[38],Otk_[37][3],Atk_[37][3],AiOiWi_[37][3],Fstar_[37][
      3];
    double Tstar_[37][3],Fstark_[37][3],Tstark_[37][3],IkWk_[37][3],WkIkWk_[37][
      3],gk_[37][3],IkbWk_[16][3],WkIkbWk_[16][3];
    double w0w0_[16],w1w1_[16],w2w2_[16],w0w1_[16],w0w2_[16],w1w2_[16];
    double w00w11_[16],w00w22_[16],w11w22_[16],ww_[1][1],qraux_[1];
    double mm_[37][37],mlo_[37][37],mdi_[37],IkWpk_[37][37][3],works_[37],
      workss_[37][37];
    double Wpk_[37][37][3],Vpk_[37][37][3],VWri_[37][37][3];
    int wmap_[1],multmap_[1],jpvt_[1],wsiz_,wrank_;
} skel18glhs_t;
#define qdot (skel18glhs.qdot_)
#define Otk (skel18glhs.Otk_)
#define Atk (skel18glhs.Atk_)
#define AiOiWi (skel18glhs.AiOiWi_)
#define Fstar (skel18glhs.Fstar_)
#define Tstar (skel18glhs.Tstar_)
#define fs0 (skel18glhs.fs0_)
#define Fstark (skel18glhs.Fstark_)
#define Tstark (skel18glhs.Tstark_)
#define IkWk (skel18glhs.IkWk_)
#define IkbWk (skel18glhs.IkbWk_)
#define WkIkWk (skel18glhs.WkIkWk_)
#define WkIkbWk (skel18glhs.WkIkbWk_)
#define gk (skel18glhs.gk_)
#define w0w0 (skel18glhs.w0w0_)
#define w1w1 (skel18glhs.w1w1_)
#define w2w2 (skel18glhs.w2w2_)
#define w0w1 (skel18glhs.w0w1_)
#define w0w2 (skel18glhs.w0w2_)
#define w1w2 (skel18glhs.w1w2_)
#define w00w11 (skel18glhs.w00w11_)
#define w00w22 (skel18glhs.w00w22_)
#define w11w22 (skel18glhs.w11w22_)
#define ww (skel18glhs.ww_)
#define qraux (skel18glhs.qraux_)
#define mm (skel18glhs.mm_)
#define mlo (skel18glhs.mlo_)
#define mdi (skel18glhs.mdi_)
#define IkWpk (skel18glhs.IkWpk_)
#define works (skel18glhs.works_)
#define workss (skel18glhs.workss_)
#define Wpk (skel18glhs.Wpk_)
#define Vpk (skel18glhs.Vpk_)
#define VWri (skel18glhs.VWri_)
#define wmap (skel18glhs.wmap_)
#define multmap (skel18glhs.multmap_)
#define jpvt (skel18glhs.jpvt_)
#define wsiz (skel18glhs.wsiz_)
#define wrank (skel18glhs.wrank_)

typedef struct {
    double fs_[37],udot_[37],tauc_[37],dyad_[16][3][3],fc_[37][3],tc_[37][3];
    double ank_[37][3],onk_[37][3],Onkb_[37][3],AOnkri_[37][3],Ankb_[37][3],
      AnkAtk_[37][3],anb_[16][3],onb_[16][3],dyrcom_[16][3];
    double ffk_[37][3],ttk_[37][3],fccikt_[37][3],ffkb_[16][3],ttkb_[16][3];
} skel18grhs_t;
#define fs (skel18grhs.fs_)
#define udot (skel18grhs.udot_)
#define ank (skel18grhs.ank_)
#define anb (skel18grhs.anb_)
#define onk (skel18grhs.onk_)
#define onb (skel18grhs.onb_)
#define Onkb (skel18grhs.Onkb_)
#define AOnkri (skel18grhs.AOnkri_)
#define Ankb (skel18grhs.Ankb_)
#define AnkAtk (skel18grhs.AnkAtk_)
#define dyrcom (skel18grhs.dyrcom_)
#define ffk (skel18grhs.ffk_)
#define ttk (skel18grhs.ttk_)
#define fccikt (skel18grhs.fccikt_)
#define ffkb (skel18grhs.ffkb_)
#define ttkb (skel18grhs.ttkb_)
#define dyad (skel18grhs.dyad_)
#define fc (skel18grhs.fc_)
#define tc (skel18grhs.tc_)
#define tauc (skel18grhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} skel18gtemp_t;
#define temp (skel18gtemp.temp_)
#define tmat1 (skel18gtemp.tmat1_)
#define tmat2 (skel18gtemp.tmat2_)
#define tvec1 (skel18gtemp.tvec1_)
#define tvec2 (skel18gtemp.tvec2_)
#define tvec3 (skel18gtemp.tvec3_)
#define tvec4 (skel18gtemp.tvec4_)
#define tvec5 (skel18gtemp.tvec5_)
#define tsc1 (skel18gtemp.tsc1_)
#define tsc2 (skel18gtemp.tsc2_)
#define tsc3 (skel18gtemp.tsc3_)

skel18gtopo_t skel18gtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 16,
    /* ndof */ 37,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 1,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 6,
    /* jtype[1] */ 3,
    /* jtype[2] */ 3,
    /* jtype[3] */ 1,
    /* jtype[4] */ 2,
    /* jtype[5] */ 2,
    /* jtype[6] */ 2,
    /* jtype[7] */ 2,
    /* jtype[8] */ 2,
    /* jtype[9] */ 2,
    /* jtype[10] */ 3,
    /* jtype[11] */ 1,
    /* jtype[12] */ 2,
    /* jtype[13] */ 3,
    /* jtype[14] */ 1,
    /* jtype[15] */ 2,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 1,
    /* inb[3] */ 2,
    /* inb[4] */ 1,
    /* inb[5] */ 4,
    /* inb[6] */ 5,
    /* inb[7] */ 1,
    /* inb[8] */ 7,
    /* inb[9] */ 8,
    /* inb[10] */ 0,
    /* inb[11] */ 10,
    /* inb[12] */ 11,
    /* inb[13] */ 0,
    /* inb[14] */ 13,
    /* inb[15] */ 14,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* outb[3] */ 3,
    /* outb[4] */ 4,
    /* outb[5] */ 5,
    /* outb[6] */ 6,
    /* outb[7] */ 7,
    /* outb[8] */ 8,
    /* outb[9] */ 9,
    /* outb[10] */ 10,
    /* outb[11] */ 11,
    /* outb[12] */ 12,
    /* outb[13] */ 13,
    /* outb[14] */ 14,
    /* outb[15] */ 15,
    /* njntdof[0] */ 6,
    /* njntdof[1] */ 3,
    /* njntdof[2] */ 3,
    /* njntdof[3] */ 1,
    /* njntdof[4] */ 2,
    /* njntdof[5] */ 2,
    /* njntdof[6] */ 2,
    /* njntdof[7] */ 2,
    /* njntdof[8] */ 2,
    /* njntdof[9] */ 2,
    /* njntdof[10] */ 3,
    /* njntdof[11] */ 1,
    /* njntdof[12] */ 2,
    /* njntdof[13] */ 3,
    /* njntdof[14] */ 1,
    /* njntdof[15] */ 2,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntc[3] */ 0,
    /* njntc[4] */ 0,
    /* njntc[5] */ 0,
    /* njntc[6] */ 0,
    /* njntc[7] */ 0,
    /* njntc[8] */ 0,
    /* njntc[9] */ 0,
    /* njntc[10] */ 0,
    /* njntc[11] */ 0,
    /* njntc[12] */ 0,
    /* njntc[13] */ 0,
    /* njntc[14] */ 0,
    /* njntc[15] */ 0,
    /* njntp[0] */ 0,
    /* njntp[1] */ 0,
    /* njntp[2] */ 0,
    /* njntp[3] */ 0,
    /* njntp[4] */ 0,
    /* njntp[5] */ 0,
    /* njntp[6] */ 0,
    /* njntp[7] */ 0,
    /* njntp[8] */ 0,
    /* njntp[9] */ 0,
    /* njntp[10] */ 0,
    /* njntp[11] */ 0,
    /* njntp[12] */ 0,
    /* njntp[13] */ 0,
    /* njntp[14] */ 0,
    /* njntp[15] */ 0,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 9,
    /* firstq[3] */ 12,
    /* firstq[4] */ 13,
    /* firstq[5] */ 15,
    /* firstq[6] */ 17,
    /* firstq[7] */ 19,
    /* firstq[8] */ 21,
    /* firstq[9] */ 23,
    /* firstq[10] */ 25,
    /* firstq[11] */ 28,
    /* firstq[12] */ 29,
    /* firstq[13] */ 31,
    /* firstq[14] */ 34,
    /* firstq[15] */ 35,
    /* ballq[0] */ 37,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* ballq[7] */ -104,
    /* ballq[8] */ -104,
    /* ballq[9] */ -104,
    /* ballq[10] */ -104,
    /* ballq[11] */ -104,
    /* ballq[12] */ -104,
    /* ballq[13] */ -104,
    /* ballq[14] */ -104,
    /* ballq[15] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstm[3] */ -1,
    /* firstm[4] */ -1,
    /* firstm[5] */ -1,
    /* firstm[6] */ -1,
    /* firstm[7] */ -1,
    /* firstm[8] */ -1,
    /* firstm[9] */ -1,
    /* firstm[10] */ -1,
    /* firstm[11] */ -1,
    /* firstm[12] */ -1,
    /* firstm[13] */ -1,
    /* firstm[14] */ -1,
    /* firstm[15] */ -1,
    /* firstp[0] */ -1,
    /* firstp[1] */ -1,
    /* firstp[2] */ -1,
    /* firstp[3] */ -1,
    /* firstp[4] */ -1,
    /* firstp[5] */ -1,
    /* firstp[6] */ -1,
    /* firstp[7] */ -1,
    /* firstp[8] */ -1,
    /* firstp[9] */ -1,
    /* firstp[10] */ -1,
    /* firstp[11] */ -1,
    /* firstp[12] */ -1,
    /* firstp[13] */ -1,
    /* firstp[14] */ -1,
    /* firstp[15] */ -1,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* trans[8] */ 0,
    /* trans[9] */ 0,
    /* trans[10] */ 0,
    /* trans[11] */ 0,
    /* trans[12] */ 0,
    /* trans[13] */ 0,
    /* trans[14] */ 0,
    /* trans[15] */ 0,
    /* trans[16] */ 0,
    /* trans[17] */ 0,
    /* trans[18] */ 0,
    /* trans[19] */ 0,
    /* trans[20] */ 0,
    /* trans[21] */ 0,
    /* trans[22] */ 0,
    /* trans[23] */ 0,
    /* trans[24] */ 0,
    /* trans[25] */ 0,
    /* trans[26] */ 0,
    /* trans[27] */ 0,
    /* trans[28] */ 0,
    /* trans[29] */ 0,
    /* trans[30] */ 0,
    /* trans[31] */ 0,
    /* trans[32] */ 0,
    /* trans[33] */ 0,
    /* trans[34] */ 0,
    /* trans[35] */ 0,
    /* trans[36] */ 0,
};
skel18ginput_t skel18ginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 16.61,
    /* mk[1] */ 29.27,
    /* mk[2] */ 1.,
    /* mk[3] */ 5.89,
    /* mk[4] */ 2.79,
    /* mk[5] */ 1.21,
    /* mk[6] */ .55,
    /* mk[7] */ 2.79,
    /* mk[8] */ 1.21,
    /* mk[9] */ .55,
    /* mk[10] */ 8.35,
    /* mk[11] */ 4.16,
    /* mk[12] */ 1.34,
    /* mk[13] */ 8.35,
    /* mk[14] */ 4.16,
    /* mk[15] */ 1.34,

/* inertia */
    /* ik[0][0][0] */ .18,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .16,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ .23,
    /* ik[1][0][0] */ .63,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ .32,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ .73,
    /* ik[2][0][0] */ .006,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ .001,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ .006,
    /* ik[3][0][0] */ .033,
    /* ik[3][0][1] */ 0.,
    /* ik[3][0][2] */ 0.,
    /* ik[3][1][0] */ 0.,
    /* ik[3][1][1] */ .023,
    /* ik[3][1][2] */ 0.,
    /* ik[3][2][0] */ 0.,
    /* ik[3][2][1] */ 0.,
    /* ik[3][2][2] */ .03,
    /* ik[4][0][0] */ .005,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ .025,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ .025,
    /* ik[5][0][0] */ .0012,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ .0054,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ .005,
    /* ik[6][0][0] */ .0005,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ .002,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ .0016,
    /* ik[7][0][0] */ .005,
    /* ik[7][0][1] */ 0.,
    /* ik[7][0][2] */ 0.,
    /* ik[7][1][0] */ 0.,
    /* ik[7][1][1] */ .025,
    /* ik[7][1][2] */ 0.,
    /* ik[7][2][0] */ 0.,
    /* ik[7][2][1] */ 0.,
    /* ik[7][2][2] */ .025,
    /* ik[8][0][0] */ .0012,
    /* ik[8][0][1] */ 0.,
    /* ik[8][0][2] */ 0.,
    /* ik[8][1][0] */ 0.,
    /* ik[8][1][1] */ .0054,
    /* ik[8][1][2] */ 0.,
    /* ik[8][2][0] */ 0.,
    /* ik[8][2][1] */ 0.,
    /* ik[8][2][2] */ .005,
    /* ik[9][0][0] */ .0005,
    /* ik[9][0][1] */ 0.,
    /* ik[9][0][2] */ 0.,
    /* ik[9][1][0] */ 0.,
    /* ik[9][1][1] */ .002,
    /* ik[9][1][2] */ 0.,
    /* ik[9][2][0] */ 0.,
    /* ik[9][2][1] */ 0.,
    /* ik[9][2][2] */ .0016,
    /* ik[10][0][0] */ .16,
    /* ik[10][0][1] */ 0.,
    /* ik[10][0][2] */ 0.,
    /* ik[10][1][0] */ 0.,
    /* ik[10][1][1] */ .025,
    /* ik[10][1][2] */ 0.,
    /* ik[10][2][0] */ 0.,
    /* ik[10][2][1] */ 0.,
    /* ik[10][2][2] */ .15,
    /* ik[11][0][0] */ .056,
    /* ik[11][0][1] */ 0.,
    /* ik[11][0][2] */ 0.,
    /* ik[11][1][0] */ 0.,
    /* ik[11][1][1] */ .007,
    /* ik[11][1][2] */ 0.,
    /* ik[11][2][0] */ 0.,
    /* ik[11][2][1] */ 0.,
    /* ik[11][2][2] */ .055,
    /* ik[12][0][0] */ .0075,
    /* ik[12][0][1] */ 0.,
    /* ik[12][0][2] */ 0.,
    /* ik[12][1][0] */ 0.,
    /* ik[12][1][1] */ .007,
    /* ik[12][1][2] */ 0.,
    /* ik[12][2][0] */ 0.,
    /* ik[12][2][1] */ 0.,
    /* ik[12][2][2] */ .0018,
    /* ik[13][0][0] */ .16,
    /* ik[13][0][1] */ 0.,
    /* ik[13][0][2] */ 0.,
    /* ik[13][1][0] */ 0.,
    /* ik[13][1][1] */ .025,
    /* ik[13][1][2] */ 0.,
    /* ik[13][2][0] */ 0.,
    /* ik[13][2][1] */ 0.,
    /* ik[13][2][2] */ .15,
    /* ik[14][0][0] */ .056,
    /* ik[14][0][1] */ 0.,
    /* ik[14][0][2] */ 0.,
    /* ik[14][1][0] */ 0.,
    /* ik[14][1][1] */ .007,
    /* ik[14][1][2] */ 0.,
    /* ik[14][2][0] */ 0.,
    /* ik[14][2][1] */ 0.,
    /* ik[14][2][2] */ .055,
    /* ik[15][0][0] */ .0075,
    /* ik[15][0][1] */ 0.,
    /* ik[15][0][2] */ 0.,
    /* ik[15][1][0] */ 0.,
    /* ik[15][1][1] */ .007,
    /* ik[15][1][2] */ 0.,
    /* ik[15][2][0] */ 0.,
    /* ik[15][2][1] */ 0.,
    /* ik[15][2][2] */ .0018,

/* tree hinge axis vectors */
    /* pin[0][0] */ 1.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 0.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 1.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 0.,
    /* pin[2][2] */ 1.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 0.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 0.,
    /* pin[6][0] */ 1.,
    /* pin[6][1] */ 0.,
    /* pin[6][2] */ 0.,
    /* pin[7][0] */ 0.,
    /* pin[7][1] */ 0.,
    /* pin[7][2] */ 1.,
    /* pin[8][0] */ 0.,
    /* pin[8][1] */ 1.,
    /* pin[8][2] */ 0.,
    /* pin[9][0] */ 1.,
    /* pin[9][1] */ 0.,
    /* pin[9][2] */ 0.,
    /* pin[10][0] */ 0.,
    /* pin[10][1] */ 0.,
    /* pin[10][2] */ 1.,
    /* pin[11][0] */ 0.,
    /* pin[11][1] */ 1.,
    /* pin[11][2] */ 0.,
    /* pin[12][0] */ 1.,
    /* pin[12][1] */ 0.,
    /* pin[12][2] */ 0.,
    /* pin[13][0] */ 0.,
    /* pin[13][1] */ 0.,
    /* pin[13][2] */ 1.,
    /* pin[14][0] */ 0.,
    /* pin[14][1] */ 1.,
    /* pin[14][2] */ 0.,
    /* pin[15][0] */ 0.,
    /* pin[15][1] */ 1.,
    /* pin[15][2] */ 0.,
    /* pin[16][0] */ 1.,
    /* pin[16][1] */ 0.,
    /* pin[16][2] */ 0.,
    /* pin[17][0] */ 0.,
    /* pin[17][1] */ 0.,
    /* pin[17][2] */ 1.,
    /* pin[18][0] */ 0.,
    /* pin[18][1] */ 1.,
    /* pin[18][2] */ 0.,
    /* pin[19][0] */ 0.,
    /* pin[19][1] */ 0.,
    /* pin[19][2] */ 1.,
    /* pin[20][0] */ 0.,
    /* pin[20][1] */ 1.,
    /* pin[20][2] */ 0.,
    /* pin[21][0] */ 0.,
    /* pin[21][1] */ 1.,
    /* pin[21][2] */ 0.,
    /* pin[22][0] */ 1.,
    /* pin[22][1] */ 0.,
    /* pin[22][2] */ 0.,
    /* pin[23][0] */ 0.,
    /* pin[23][1] */ 0.,
    /* pin[23][2] */ 1.,
    /* pin[24][0] */ 0.,
    /* pin[24][1] */ 1.,
    /* pin[24][2] */ 0.,
    /* pin[25][0] */ 1.,
    /* pin[25][1] */ 0.,
    /* pin[25][2] */ 0.,
    /* pin[26][0] */ 0.,
    /* pin[26][1] */ 0.,
    /* pin[26][2] */ 1.,
    /* pin[27][0] */ 0.,
    /* pin[27][1] */ 1.,
    /* pin[27][2] */ 0.,
    /* pin[28][0] */ 1.,
    /* pin[28][1] */ 0.,
    /* pin[28][2] */ 0.,
    /* pin[29][0] */ 1.,
    /* pin[29][1] */ 0.,
    /* pin[29][2] */ 0.,
    /* pin[30][0] */ 0.,
    /* pin[30][1] */ 0.,
    /* pin[30][2] */ 1.,
    /* pin[31][0] */ 1.,
    /* pin[31][1] */ 0.,
    /* pin[31][2] */ 0.,
    /* pin[32][0] */ 0.,
    /* pin[32][1] */ 0.,
    /* pin[32][2] */ 1.,
    /* pin[33][0] */ 0.,
    /* pin[33][1] */ 1.,
    /* pin[33][2] */ 0.,
    /* pin[34][0] */ 1.,
    /* pin[34][1] */ 0.,
    /* pin[34][2] */ 0.,
    /* pin[35][0] */ 1.,
    /* pin[35][1] */ 0.,
    /* pin[35][2] */ 0.,
    /* pin[36][0] */ 0.,
    /* pin[36][1] */ 0.,
    /* pin[36][2] */ 1.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ .1206,
    /* rk[0][2] */ .05,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ -.14625,
    /* rk[1][2] */ .0351,
    /* rk[2][0] */ 0.,
    /* rk[2][1] */ -.0442,
    /* rk[2][2] */ -.0065,
    /* rk[3][0] */ 0.,
    /* rk[3][1] */ -.078,
    /* rk[3][2] */ -.0312,
    /* rk[4][0] */ -.1326,
    /* rk[4][1] */ 0.,
    /* rk[4][2] */ -.0013,
    /* rk[5][0] */ -.1378,
    /* rk[5][1] */ -.0039,
    /* rk[5][2] */ 0.,
    /* rk[6][0] */ -.065,
    /* rk[6][1] */ 0.,
    /* rk[6][2] */ 0.,
    /* rk[7][0] */ .1326,
    /* rk[7][1] */ 0.,
    /* rk[7][2] */ -.0013,
    /* rk[8][0] */ .1378,
    /* rk[8][1] */ -.0039,
    /* rk[8][2] */ 0.,
    /* rk[9][0] */ .065,
    /* rk[9][1] */ 0.,
    /* rk[9][2] */ 0.,
    /* rk[10][0] */ .0169,
    /* rk[10][1] */ .2379,
    /* rk[10][2] */ -.0143,
    /* rk[11][0] */ .0078,
    /* rk[11][1] */ .2158,
    /* rk[11][2] */ .0039,
    /* rk[12][0] */ 0.,
    /* rk[12][1] */ .0442,
    /* rk[12][2] */ -.039,
    /* rk[13][0] */ -.0169,
    /* rk[13][1] */ .2379,
    /* rk[13][2] */ -.0143,
    /* rk[14][0] */ -.0078,
    /* rk[14][1] */ .2158,
    /* rk[14][2] */ .0039,
    /* rk[15][0] */ 0.,
    /* rk[15][1] */ .0442,
    /* rk[15][2] */ -.039,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 1.131,
    /* ri[0][2] */ .0052,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ .1206,
    /* ri[1][2] */ .05,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ .24635,
    /* ri[2][2] */ -.0013,
    /* ri[3][0] */ 0.,
    /* ri[3][1] */ .0442,
    /* ri[3][2] */ .0065,
    /* ri[4][0] */ .1768,
    /* ri[4][1] */ .18915,
    /* ri[4][2] */ .0013,
    /* ri[5][0] */ .1326,
    /* ri[5][1] */ 0.,
    /* ri[5][2] */ .0013,
    /* ri[6][0] */ .1378,
    /* ri[6][1] */ .0039,
    /* ri[6][2] */ 0.,
    /* ri[7][0] */ -.1768,
    /* ri[7][1] */ .18915,
    /* ri[7][2] */ .0013,
    /* ri[8][0] */ -.1326,
    /* ri[8][1] */ 0.,
    /* ri[8][2] */ .0013,
    /* ri[9][0] */ -.1378,
    /* ri[9][1] */ .0039,
    /* ri[9][2] */ 0.,
    /* ri[10][0] */ .1118,
    /* ri[10][1] */ -.0406,
    /* ri[10][2] */ .0058,
    /* ri[11][0] */ -.0169,
    /* ri[11][1] */ -.2379,
    /* ri[11][2] */ .0143,
    /* ri[12][0] */ -.0078,
    /* ri[12][1] */ -.2158,
    /* ri[12][2] */ -.0039,
    /* ri[13][0] */ -.1118,
    /* ri[13][1] */ -.0406,
    /* ri[13][2] */ .0058,
    /* ri[14][0] */ .0169,
    /* ri[14][1] */ -.2379,
    /* ri[14][2] */ .0143,
    /* ri[15][0] */ .0078,
    /* ri[15][1] */ -.2158,
    /* ri[15][2] */ -.0039,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,
    /* pres[5] */ 0.,
    /* pres[6] */ 0.,
    /* pres[7] */ 0.,
    /* pres[8] */ 0.,
    /* pres[9] */ 0.,
    /* pres[10] */ 0.,
    /* pres[11] */ 0.,
    /* pres[12] */ 0.,
    /* pres[13] */ 0.,
    /* pres[14] */ 0.,
    /* pres[15] */ 0.,
    /* pres[16] */ 0.,
    /* pres[17] */ 0.,
    /* pres[18] */ 0.,
    /* pres[19] */ 0.,
    /* pres[20] */ 0.,
    /* pres[21] */ 0.,
    /* pres[22] */ 0.,
    /* pres[23] */ 0.,
    /* pres[24] */ 0.,
    /* pres[25] */ 0.,
    /* pres[26] */ 0.,
    /* pres[27] */ 0.,
    /* pres[28] */ 0.,
    /* pres[29] */ 0.,
    /* pres[30] */ 0.,
    /* pres[31] */ 0.,
    /* pres[32] */ 0.,
    /* pres[33] */ 0.,
    /* pres[34] */ 0.,
    /* pres[35] */ 0.,
    /* pres[36] */ 0.,

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
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,
    /* mmap[5] */ 5,
    /* mmap[6] */ 6,
    /* mmap[7] */ 7,
    /* mmap[8] */ 8,
    /* mmap[9] */ 9,
    /* mmap[10] */ 10,
    /* mmap[11] */ 11,
    /* mmap[12] */ 12,
    /* mmap[13] */ 13,
    /* mmap[14] */ 14,
    /* mmap[15] */ 15,
    /* mmap[16] */ 16,
    /* mmap[17] */ 17,
    /* mmap[18] */ 18,
    /* mmap[19] */ 19,
    /* mmap[20] */ 20,
    /* mmap[21] */ 21,
    /* mmap[22] */ 22,
    /* mmap[23] */ 23,
    /* mmap[24] */ 24,
    /* mmap[25] */ 25,
    /* mmap[26] */ 26,
    /* mmap[27] */ 27,
    /* mmap[28] */ 28,
    /* mmap[29] */ 29,
    /* mmap[30] */ 30,
    /* mmap[31] */ 31,
    /* mmap[32] */ 32,
    /* mmap[33] */ 33,
    /* mmap[34] */ 34,
    /* mmap[35] */ 35,
    /* mmap[36] */ 36,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 0,
    /* gravq[1] */ 0,
    /* gravq[2] */ 0,
    /* mkq[0] */ 0,
    /* mkq[1] */ 0,
    /* mkq[2] */ 0,
    /* mkq[3] */ 0,
    /* mkq[4] */ 0,
    /* mkq[5] */ 0,
    /* mkq[6] */ 0,
    /* mkq[7] */ 0,
    /* mkq[8] */ 0,
    /* mkq[9] */ 0,
    /* mkq[10] */ 0,
    /* mkq[11] */ 0,
    /* mkq[12] */ 0,
    /* mkq[13] */ 0,
    /* mkq[14] */ 0,
    /* mkq[15] */ 0,
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
    /* ikq[2][0][0] */ 0,
    /* ikq[2][0][1] */ 0,
    /* ikq[2][0][2] */ 0,
    /* ikq[2][1][0] */ 0,
    /* ikq[2][1][1] */ 0,
    /* ikq[2][1][2] */ 0,
    /* ikq[2][2][0] */ 0,
    /* ikq[2][2][1] */ 0,
    /* ikq[2][2][2] */ 0,
    /* ikq[3][0][0] */ 0,
    /* ikq[3][0][1] */ 0,
    /* ikq[3][0][2] */ 0,
    /* ikq[3][1][0] */ 0,
    /* ikq[3][1][1] */ 0,
    /* ikq[3][1][2] */ 0,
    /* ikq[3][2][0] */ 0,
    /* ikq[3][2][1] */ 0,
    /* ikq[3][2][2] */ 0,
    /* ikq[4][0][0] */ 0,
    /* ikq[4][0][1] */ 0,
    /* ikq[4][0][2] */ 0,
    /* ikq[4][1][0] */ 0,
    /* ikq[4][1][1] */ 0,
    /* ikq[4][1][2] */ 0,
    /* ikq[4][2][0] */ 0,
    /* ikq[4][2][1] */ 0,
    /* ikq[4][2][2] */ 0,
    /* ikq[5][0][0] */ 0,
    /* ikq[5][0][1] */ 0,
    /* ikq[5][0][2] */ 0,
    /* ikq[5][1][0] */ 0,
    /* ikq[5][1][1] */ 0,
    /* ikq[5][1][2] */ 0,
    /* ikq[5][2][0] */ 0,
    /* ikq[5][2][1] */ 0,
    /* ikq[5][2][2] */ 0,
    /* ikq[6][0][0] */ 0,
    /* ikq[6][0][1] */ 0,
    /* ikq[6][0][2] */ 0,
    /* ikq[6][1][0] */ 0,
    /* ikq[6][1][1] */ 0,
    /* ikq[6][1][2] */ 0,
    /* ikq[6][2][0] */ 0,
    /* ikq[6][2][1] */ 0,
    /* ikq[6][2][2] */ 0,
    /* ikq[7][0][0] */ 0,
    /* ikq[7][0][1] */ 0,
    /* ikq[7][0][2] */ 0,
    /* ikq[7][1][0] */ 0,
    /* ikq[7][1][1] */ 0,
    /* ikq[7][1][2] */ 0,
    /* ikq[7][2][0] */ 0,
    /* ikq[7][2][1] */ 0,
    /* ikq[7][2][2] */ 0,
    /* ikq[8][0][0] */ 0,
    /* ikq[8][0][1] */ 0,
    /* ikq[8][0][2] */ 0,
    /* ikq[8][1][0] */ 0,
    /* ikq[8][1][1] */ 0,
    /* ikq[8][1][2] */ 0,
    /* ikq[8][2][0] */ 0,
    /* ikq[8][2][1] */ 0,
    /* ikq[8][2][2] */ 0,
    /* ikq[9][0][0] */ 0,
    /* ikq[9][0][1] */ 0,
    /* ikq[9][0][2] */ 0,
    /* ikq[9][1][0] */ 0,
    /* ikq[9][1][1] */ 0,
    /* ikq[9][1][2] */ 0,
    /* ikq[9][2][0] */ 0,
    /* ikq[9][2][1] */ 0,
    /* ikq[9][2][2] */ 0,
    /* ikq[10][0][0] */ 0,
    /* ikq[10][0][1] */ 0,
    /* ikq[10][0][2] */ 0,
    /* ikq[10][1][0] */ 0,
    /* ikq[10][1][1] */ 0,
    /* ikq[10][1][2] */ 0,
    /* ikq[10][2][0] */ 0,
    /* ikq[10][2][1] */ 0,
    /* ikq[10][2][2] */ 0,
    /* ikq[11][0][0] */ 0,
    /* ikq[11][0][1] */ 0,
    /* ikq[11][0][2] */ 0,
    /* ikq[11][1][0] */ 0,
    /* ikq[11][1][1] */ 0,
    /* ikq[11][1][2] */ 0,
    /* ikq[11][2][0] */ 0,
    /* ikq[11][2][1] */ 0,
    /* ikq[11][2][2] */ 0,
    /* ikq[12][0][0] */ 0,
    /* ikq[12][0][1] */ 0,
    /* ikq[12][0][2] */ 0,
    /* ikq[12][1][0] */ 0,
    /* ikq[12][1][1] */ 0,
    /* ikq[12][1][2] */ 0,
    /* ikq[12][2][0] */ 0,
    /* ikq[12][2][1] */ 0,
    /* ikq[12][2][2] */ 0,
    /* ikq[13][0][0] */ 0,
    /* ikq[13][0][1] */ 0,
    /* ikq[13][0][2] */ 0,
    /* ikq[13][1][0] */ 0,
    /* ikq[13][1][1] */ 0,
    /* ikq[13][1][2] */ 0,
    /* ikq[13][2][0] */ 0,
    /* ikq[13][2][1] */ 0,
    /* ikq[13][2][2] */ 0,
    /* ikq[14][0][0] */ 0,
    /* ikq[14][0][1] */ 0,
    /* ikq[14][0][2] */ 0,
    /* ikq[14][1][0] */ 0,
    /* ikq[14][1][1] */ 0,
    /* ikq[14][1][2] */ 0,
    /* ikq[14][2][0] */ 0,
    /* ikq[14][2][1] */ 0,
    /* ikq[14][2][2] */ 0,
    /* ikq[15][0][0] */ 0,
    /* ikq[15][0][1] */ 0,
    /* ikq[15][0][2] */ 0,
    /* ikq[15][1][0] */ 0,
    /* ikq[15][1][1] */ 0,
    /* ikq[15][1][2] */ 0,
    /* ikq[15][2][0] */ 0,
    /* ikq[15][2][1] */ 0,
    /* ikq[15][2][2] */ 0,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* pinq[2][0] */ 0,
    /* pinq[2][1] */ 0,
    /* pinq[2][2] */ 0,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* pinq[6][0] */ 0,
    /* pinq[6][1] */ 0,
    /* pinq[6][2] */ 0,
    /* pinq[7][0] */ 0,
    /* pinq[7][1] */ 0,
    /* pinq[7][2] */ 0,
    /* pinq[8][0] */ 0,
    /* pinq[8][1] */ 0,
    /* pinq[8][2] */ 0,
    /* pinq[9][0] */ 0,
    /* pinq[9][1] */ 0,
    /* pinq[9][2] */ 0,
    /* pinq[10][0] */ 0,
    /* pinq[10][1] */ 0,
    /* pinq[10][2] */ 0,
    /* pinq[11][0] */ 0,
    /* pinq[11][1] */ 0,
    /* pinq[11][2] */ 0,
    /* pinq[12][0] */ 0,
    /* pinq[12][1] */ 0,
    /* pinq[12][2] */ 0,
    /* pinq[13][0] */ 0,
    /* pinq[13][1] */ 0,
    /* pinq[13][2] */ 0,
    /* pinq[14][0] */ 0,
    /* pinq[14][1] */ 0,
    /* pinq[14][2] */ 0,
    /* pinq[15][0] */ 0,
    /* pinq[15][1] */ 0,
    /* pinq[15][2] */ 0,
    /* pinq[16][0] */ 0,
    /* pinq[16][1] */ 0,
    /* pinq[16][2] */ 0,
    /* pinq[17][0] */ 0,
    /* pinq[17][1] */ 0,
    /* pinq[17][2] */ 0,
    /* pinq[18][0] */ 0,
    /* pinq[18][1] */ 0,
    /* pinq[18][2] */ 0,
    /* pinq[19][0] */ 0,
    /* pinq[19][1] */ 0,
    /* pinq[19][2] */ 0,
    /* pinq[20][0] */ 0,
    /* pinq[20][1] */ 0,
    /* pinq[20][2] */ 0,
    /* pinq[21][0] */ 0,
    /* pinq[21][1] */ 0,
    /* pinq[21][2] */ 0,
    /* pinq[22][0] */ 0,
    /* pinq[22][1] */ 0,
    /* pinq[22][2] */ 0,
    /* pinq[23][0] */ 0,
    /* pinq[23][1] */ 0,
    /* pinq[23][2] */ 0,
    /* pinq[24][0] */ 0,
    /* pinq[24][1] */ 0,
    /* pinq[24][2] */ 0,
    /* pinq[25][0] */ 0,
    /* pinq[25][1] */ 0,
    /* pinq[25][2] */ 0,
    /* pinq[26][0] */ 0,
    /* pinq[26][1] */ 0,
    /* pinq[26][2] */ 0,
    /* pinq[27][0] */ 0,
    /* pinq[27][1] */ 0,
    /* pinq[27][2] */ 0,
    /* pinq[28][0] */ 0,
    /* pinq[28][1] */ 0,
    /* pinq[28][2] */ 0,
    /* pinq[29][0] */ 0,
    /* pinq[29][1] */ 0,
    /* pinq[29][2] */ 0,
    /* pinq[30][0] */ 0,
    /* pinq[30][1] */ 0,
    /* pinq[30][2] */ 0,
    /* pinq[31][0] */ 0,
    /* pinq[31][1] */ 0,
    /* pinq[31][2] */ 0,
    /* pinq[32][0] */ 0,
    /* pinq[32][1] */ 0,
    /* pinq[32][2] */ 0,
    /* pinq[33][0] */ 0,
    /* pinq[33][1] */ 0,
    /* pinq[33][2] */ 0,
    /* pinq[34][0] */ 0,
    /* pinq[34][1] */ 0,
    /* pinq[34][2] */ 0,
    /* pinq[35][0] */ 0,
    /* pinq[35][1] */ 0,
    /* pinq[35][2] */ 0,
    /* pinq[36][0] */ 0,
    /* pinq[36][1] */ 0,
    /* pinq[36][2] */ 0,
    /* rkq[0][0] */ 0,
    /* rkq[0][1] */ 0,
    /* rkq[0][2] */ 0,
    /* rkq[1][0] */ 0,
    /* rkq[1][1] */ 0,
    /* rkq[1][2] */ 0,
    /* rkq[2][0] */ 0,
    /* rkq[2][1] */ 0,
    /* rkq[2][2] */ 0,
    /* rkq[3][0] */ 0,
    /* rkq[3][1] */ 0,
    /* rkq[3][2] */ 0,
    /* rkq[4][0] */ 0,
    /* rkq[4][1] */ 0,
    /* rkq[4][2] */ 0,
    /* rkq[5][0] */ 0,
    /* rkq[5][1] */ 0,
    /* rkq[5][2] */ 0,
    /* rkq[6][0] */ 0,
    /* rkq[6][1] */ 0,
    /* rkq[6][2] */ 0,
    /* rkq[7][0] */ 0,
    /* rkq[7][1] */ 0,
    /* rkq[7][2] */ 0,
    /* rkq[8][0] */ 0,
    /* rkq[8][1] */ 0,
    /* rkq[8][2] */ 0,
    /* rkq[9][0] */ 0,
    /* rkq[9][1] */ 0,
    /* rkq[9][2] */ 0,
    /* rkq[10][0] */ 0,
    /* rkq[10][1] */ 0,
    /* rkq[10][2] */ 0,
    /* rkq[11][0] */ 0,
    /* rkq[11][1] */ 0,
    /* rkq[11][2] */ 0,
    /* rkq[12][0] */ 0,
    /* rkq[12][1] */ 0,
    /* rkq[12][2] */ 0,
    /* rkq[13][0] */ 0,
    /* rkq[13][1] */ 0,
    /* rkq[13][2] */ 0,
    /* rkq[14][0] */ 0,
    /* rkq[14][1] */ 0,
    /* rkq[14][2] */ 0,
    /* rkq[15][0] */ 0,
    /* rkq[15][1] */ 0,
    /* rkq[15][2] */ 0,
    /* riq[0][0] */ 0,
    /* riq[0][1] */ 0,
    /* riq[0][2] */ 0,
    /* riq[1][0] */ 0,
    /* riq[1][1] */ 0,
    /* riq[1][2] */ 0,
    /* riq[2][0] */ 0,
    /* riq[2][1] */ 0,
    /* riq[2][2] */ 0,
    /* riq[3][0] */ 0,
    /* riq[3][1] */ 0,
    /* riq[3][2] */ 0,
    /* riq[4][0] */ 0,
    /* riq[4][1] */ 0,
    /* riq[4][2] */ 0,
    /* riq[5][0] */ 0,
    /* riq[5][1] */ 0,
    /* riq[5][2] */ 0,
    /* riq[6][0] */ 0,
    /* riq[6][1] */ 0,
    /* riq[6][2] */ 0,
    /* riq[7][0] */ 0,
    /* riq[7][1] */ 0,
    /* riq[7][2] */ 0,
    /* riq[8][0] */ 0,
    /* riq[8][1] */ 0,
    /* riq[8][2] */ 0,
    /* riq[9][0] */ 0,
    /* riq[9][1] */ 0,
    /* riq[9][2] */ 0,
    /* riq[10][0] */ 0,
    /* riq[10][1] */ 0,
    /* riq[10][2] */ 0,
    /* riq[11][0] */ 0,
    /* riq[11][1] */ 0,
    /* riq[11][2] */ 0,
    /* riq[12][0] */ 0,
    /* riq[12][1] */ 0,
    /* riq[12][2] */ 0,
    /* riq[13][0] */ 0,
    /* riq[13][1] */ 0,
    /* riq[13][2] */ 0,
    /* riq[14][0] */ 0,
    /* riq[14][1] */ 0,
    /* riq[14][2] */ 0,
    /* riq[15][0] */ 0,
    /* riq[15][1] */ 0,
    /* riq[15][2] */ 0,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* presq[6] */ 0,
    /* presq[7] */ 0,
    /* presq[8] */ 0,
    /* presq[9] */ 0,
    /* presq[10] */ 0,
    /* presq[11] */ 0,
    /* presq[12] */ 0,
    /* presq[13] */ 0,
    /* presq[14] */ 0,
    /* presq[15] */ 0,
    /* presq[16] */ 0,
    /* presq[17] */ 0,
    /* presq[18] */ 0,
    /* presq[19] */ 0,
    /* presq[20] */ 0,
    /* presq[21] */ 0,
    /* presq[22] */ 0,
    /* presq[23] */ 0,
    /* presq[24] */ 0,
    /* presq[25] */ 0,
    /* presq[26] */ 0,
    /* presq[27] */ 0,
    /* presq[28] */ 0,
    /* presq[29] */ 0,
    /* presq[30] */ 0,
    /* presq[31] */ 0,
    /* presq[32] */ 0,
    /* presq[33] */ 0,
    /* presq[34] */ 0,
    /* presq[35] */ 0,
    /* presq[36] */ 0,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
skel18gstate_t skel18gstate;
skel18glhs_t skel18glhs;
skel18grhs_t skel18grhs;
skel18gtemp_t skel18gtemp;


void skel18init(void)
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
            skel18seterr(7,25);
        }
    }
    for (k = 0; k < 16; k++) {
        if (mkq[k] == 1) {
            skel18seterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                skel18seterr(7,29);
            }
            if (riq[k][i] == 1) {
                skel18seterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    skel18seterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 37; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                skel18seterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 37; i++) {
        for (j = i; j <= 36; j++) {
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
    rcom[2][0] = 0.;
    rcom[2][1] = 0.;
    rcom[2][2] = 0.;
    rcom[3][0] = 0.;
    rcom[3][1] = 0.;
    rcom[3][2] = 0.;
    rcom[4][0] = 0.;
    rcom[4][1] = 0.;
    rcom[4][2] = 0.;
    rcom[5][0] = 0.;
    rcom[5][1] = 0.;
    rcom[5][2] = 0.;
    rcom[6][0] = 0.;
    rcom[6][1] = 0.;
    rcom[6][2] = 0.;
    rcom[7][0] = 0.;
    rcom[7][1] = 0.;
    rcom[7][2] = 0.;
    rcom[8][0] = 0.;
    rcom[8][1] = 0.;
    rcom[8][2] = 0.;
    rcom[9][0] = 0.;
    rcom[9][1] = 0.;
    rcom[9][2] = 0.;
    rcom[10][0] = 0.;
    rcom[10][1] = 0.;
    rcom[10][2] = 0.;
    rcom[11][0] = 0.;
    rcom[11][1] = 0.;
    rcom[11][2] = 0.;
    rcom[12][0] = 0.;
    rcom[12][1] = 0.;
    rcom[12][2] = 0.;
    rcom[13][0] = 0.;
    rcom[13][1] = 0.;
    rcom[13][2] = 0.;
    rcom[14][0] = 0.;
    rcom[14][1] = 0.;
    rcom[14][2] = 0.;
    rcom[15][0] = 0.;
    rcom[15][1] = 0.;
    rcom[15][2] = 0.;

/* Compute mass properties-related constants */

    mtot = 89.57;
    skel18serialno(&i);
    if (i != 70405) {
        skel18seterr(7,41);
    }
    roustate = 1;
}

void skel18state(double timein, double *qin, double *uin)
{
/*
Compute kinematic information and store it in sdgstate.

Generated 23-Nov-1999 14:30:32 by SD/FAST, Kane's formulation
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
    double ee,stab;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        skel18seterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 37; i++) {
            if (presq[i] == 1) {
                skel18seterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 38; i++) {
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
        for (i = 0; i < 37; i++) {
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
    for (i = 0; i < 38; i++) {
        q[i] = qin[i];
    }
/*
Normalize Euler parameters in state
*/
    skel18nrmsterr(q,qn,8);
/*
Compute sines and cosines of q
*/
    s6 = sin(q[6]);
    c6 = cos(q[6]);
    s7 = sin(q[7]);
    c7 = cos(q[7]);
    s8 = sin(q[8]);
    c8 = cos(q[8]);
    s9 = sin(q[9]);
    c9 = cos(q[9]);
    s10 = sin(q[10]);
    c10 = cos(q[10]);
    s11 = sin(q[11]);
    c11 = cos(q[11]);
    s12 = sin(q[12]);
    c12 = cos(q[12]);
    s13 = sin(q[13]);
    c13 = cos(q[13]);
    s14 = sin(q[14]);
    c14 = cos(q[14]);
    s15 = sin(q[15]);
    c15 = cos(q[15]);
    s16 = sin(q[16]);
    c16 = cos(q[16]);
    s17 = sin(q[17]);
    c17 = cos(q[17]);
    s18 = sin(q[18]);
    c18 = cos(q[18]);
    s19 = sin(q[19]);
    c19 = cos(q[19]);
    s20 = sin(q[20]);
    c20 = cos(q[20]);
    s21 = sin(q[21]);
    c21 = cos(q[21]);
    s22 = sin(q[22]);
    c22 = cos(q[22]);
    s23 = sin(q[23]);
    c23 = cos(q[23]);
    s24 = sin(q[24]);
    c24 = cos(q[24]);
    s25 = sin(q[25]);
    c25 = cos(q[25]);
    s26 = sin(q[26]);
    c26 = cos(q[26]);
    s27 = sin(q[27]);
    c27 = cos(q[27]);
    s28 = sin(q[28]);
    c28 = cos(q[28]);
    s29 = sin(q[29]);
    c29 = cos(q[29]);
    s30 = sin(q[30]);
    c30 = cos(q[30]);
    s31 = sin(q[31]);
    c31 = cos(q[31]);
    s32 = sin(q[32]);
    c32 = cos(q[32]);
    s33 = sin(q[33]);
    c33 = cos(q[33]);
    s34 = sin(q[34]);
    c34 = cos(q[34]);
    s35 = sin(q[35]);
    c35 = cos(q[35]);
    s36 = sin(q[36]);
    c36 = cos(q[36]);
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (1.-(2.*((qn[4]*qn[4])+(qn[5]*qn[5]))));
    Cik[3][0][1] = (2.*((qn[3]*qn[4])-(qn[5]*qn[37])));
    Cik[3][0][2] = (2.*((qn[3]*qn[5])+(qn[4]*qn[37])));
    Cik[3][1][0] = (2.*((qn[3]*qn[4])+(qn[5]*qn[37])));
    Cik[3][1][1] = (1.-(2.*((qn[3]*qn[3])+(qn[5]*qn[5]))));
    Cik[3][1][2] = (2.*((qn[4]*qn[5])-(qn[3]*qn[37])));
    Cik[3][2][0] = (2.*((qn[3]*qn[5])-(qn[4]*qn[37])));
    Cik[3][2][1] = (2.*((qn[3]*qn[37])+(qn[4]*qn[5])));
    Cik[3][2][2] = (1.-(2.*((qn[3]*qn[3])+(qn[4]*qn[4]))));
/*
Compute across-joint direction cosines Cib
*/
    Cib[1][0][0] = (c7*c8);
    Cib[1][0][2] = (s8*c7);
    Cib[1][1][0] = ((s6*s8)+(c8*(s7*c6)));
    Cib[1][1][1] = (c6*c7);
    Cib[1][1][2] = ((s8*(s7*c6))-(s6*c8));
    Cib[1][2][0] = ((c8*(s6*s7))-(s8*c6));
    Cib[1][2][1] = (s6*c7);
    Cib[1][2][2] = ((s8*(s6*s7))+(c6*c8));
    Cib[2][0][0] = (c10*c11);
    Cib[2][0][2] = (s11*c10);
    Cib[2][1][0] = ((s9*s11)+(c11*(s10*c9)));
    Cib[2][1][1] = (c9*c10);
    Cib[2][1][2] = ((s11*(s10*c9))-(s9*c11));
    Cib[2][2][0] = ((c11*(s9*s10))-(s11*c9));
    Cib[2][2][1] = (s9*c10);
    Cib[2][2][2] = ((s11*(s9*s10))+(c9*c11));
    Cib[4][0][0] = (c13*c14);
    Cib[4][0][2] = (s14*c13);
    Cib[4][1][0] = (s13*c14);
    Cib[4][1][2] = (s13*s14);
    Cib[5][0][1] = (s15*s16);
    Cib[5][0][2] = (s15*c16);
    Cib[5][2][1] = (s16*c15);
    Cib[5][2][2] = (c15*c16);
    Cib[6][0][0] = (c17*c18);
    Cib[6][0][2] = (s18*c17);
    Cib[6][1][0] = (s17*c18);
    Cib[6][1][2] = (s17*s18);
    Cib[7][0][0] = (c19*c20);
    Cib[7][0][2] = (s20*c19);
    Cib[7][1][0] = (s19*c20);
    Cib[7][1][2] = (s19*s20);
    Cib[8][0][1] = (s21*s22);
    Cib[8][0][2] = (s21*c22);
    Cib[8][2][1] = (s22*c21);
    Cib[8][2][2] = (c21*c22);
    Cib[9][0][0] = (c23*c24);
    Cib[9][0][2] = (s24*c23);
    Cib[9][1][0] = (s23*c24);
    Cib[9][1][2] = (s23*s24);
    Cib[10][0][0] = (c26*c27);
    Cib[10][0][2] = (s27*c26);
    Cib[10][1][0] = ((s25*s27)+(c27*(s26*c25)));
    Cib[10][1][1] = (c25*c26);
    Cib[10][1][2] = ((s27*(s26*c25))-(s25*c27));
    Cib[10][2][0] = ((c27*(s25*s26))-(s27*c25));
    Cib[10][2][1] = (s25*c26);
    Cib[10][2][2] = ((s27*(s25*s26))+(c25*c27));
    Cib[12][1][0] = (s30*c29);
    Cib[12][1][1] = (c29*c30);
    Cib[12][2][0] = (s29*s30);
    Cib[12][2][1] = (s29*c30);
    Cib[13][0][0] = (c32*c33);
    Cib[13][0][2] = (s33*c32);
    Cib[13][1][0] = ((s31*s33)+(c33*(s32*c31)));
    Cib[13][1][1] = (c31*c32);
    Cib[13][1][2] = ((s33*(s32*c31))-(s31*c33));
    Cib[13][2][0] = ((c33*(s31*s32))-(s33*c31));
    Cib[13][2][1] = (s31*c32);
    Cib[13][2][2] = ((s33*(s31*s32))+(c31*c33));
    Cib[15][1][0] = (s36*c35);
    Cib[15][1][1] = (c35*c36);
    Cib[15][2][0] = (s35*s36);
    Cib[15][2][1] = (s35*c36);
/*
Compute gravity
*/
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[6][0][1] = ((Cik[3][0][1]*c6)+(Cik[3][0][2]*s6));
    cnk[6][0][2] = ((Cik[3][0][2]*c6)-(Cik[3][0][1]*s6));
    cnk[6][1][1] = ((Cik[3][1][1]*c6)+(Cik[3][1][2]*s6));
    cnk[6][1][2] = ((Cik[3][1][2]*c6)-(Cik[3][1][1]*s6));
    cnk[6][2][1] = ((Cik[3][2][1]*c6)+(Cik[3][2][2]*s6));
    cnk[6][2][2] = ((Cik[3][2][2]*c6)-(Cik[3][2][1]*s6));
    cnk[7][0][0] = ((Cik[3][0][0]*c7)+(cnk[6][0][1]*s7));
    cnk[7][0][1] = ((cnk[6][0][1]*c7)-(Cik[3][0][0]*s7));
    cnk[7][1][0] = ((Cik[3][1][0]*c7)+(cnk[6][1][1]*s7));
    cnk[7][1][1] = ((cnk[6][1][1]*c7)-(Cik[3][1][0]*s7));
    cnk[7][2][0] = ((Cik[3][2][0]*c7)+(cnk[6][2][1]*s7));
    cnk[7][2][1] = ((cnk[6][2][1]*c7)-(Cik[3][2][0]*s7));
    cnk[8][0][0] = ((cnk[7][0][0]*c8)-(cnk[6][0][2]*s8));
    cnk[8][0][2] = ((cnk[6][0][2]*c8)+(cnk[7][0][0]*s8));
    cnk[8][1][0] = ((cnk[7][1][0]*c8)-(cnk[6][1][2]*s8));
    cnk[8][1][2] = ((cnk[6][1][2]*c8)+(cnk[7][1][0]*s8));
    cnk[8][2][0] = ((cnk[7][2][0]*c8)-(cnk[6][2][2]*s8));
    cnk[8][2][2] = ((cnk[6][2][2]*c8)+(cnk[7][2][0]*s8));
    cnk[9][0][1] = ((cnk[7][0][1]*c9)+(cnk[8][0][2]*s9));
    cnk[9][0][2] = ((cnk[8][0][2]*c9)-(cnk[7][0][1]*s9));
    cnk[9][1][1] = ((cnk[7][1][1]*c9)+(cnk[8][1][2]*s9));
    cnk[9][1][2] = ((cnk[8][1][2]*c9)-(cnk[7][1][1]*s9));
    cnk[9][2][1] = ((cnk[7][2][1]*c9)+(cnk[8][2][2]*s9));
    cnk[9][2][2] = ((cnk[8][2][2]*c9)-(cnk[7][2][1]*s9));
    cnk[10][0][0] = ((cnk[8][0][0]*c10)+(cnk[9][0][1]*s10));
    cnk[10][0][1] = ((cnk[9][0][1]*c10)-(cnk[8][0][0]*s10));
    cnk[10][1][0] = ((cnk[8][1][0]*c10)+(cnk[9][1][1]*s10));
    cnk[10][1][1] = ((cnk[9][1][1]*c10)-(cnk[8][1][0]*s10));
    cnk[10][2][0] = ((cnk[8][2][0]*c10)+(cnk[9][2][1]*s10));
    cnk[10][2][1] = ((cnk[9][2][1]*c10)-(cnk[8][2][0]*s10));
    cnk[11][0][0] = ((cnk[10][0][0]*c11)-(cnk[9][0][2]*s11));
    cnk[11][0][2] = ((cnk[9][0][2]*c11)+(cnk[10][0][0]*s11));
    cnk[11][1][0] = ((cnk[10][1][0]*c11)-(cnk[9][1][2]*s11));
    cnk[11][1][2] = ((cnk[9][1][2]*c11)+(cnk[10][1][0]*s11));
    cnk[11][2][0] = ((cnk[10][2][0]*c11)-(cnk[9][2][2]*s11));
    cnk[11][2][2] = ((cnk[9][2][2]*c11)+(cnk[10][2][0]*s11));
    cnk[12][0][1] = ((cnk[10][0][1]*c12)+(cnk[11][0][2]*s12));
    cnk[12][0][2] = ((cnk[11][0][2]*c12)-(cnk[10][0][1]*s12));
    cnk[12][1][1] = ((cnk[10][1][1]*c12)+(cnk[11][1][2]*s12));
    cnk[12][1][2] = ((cnk[11][1][2]*c12)-(cnk[10][1][1]*s12));
    cnk[12][2][1] = ((cnk[10][2][1]*c12)+(cnk[11][2][2]*s12));
    cnk[12][2][2] = ((cnk[11][2][2]*c12)-(cnk[10][2][1]*s12));
    cnk[13][0][0] = ((cnk[7][0][1]*s13)+(cnk[8][0][0]*c13));
    cnk[13][0][1] = ((cnk[7][0][1]*c13)-(cnk[8][0][0]*s13));
    cnk[13][1][0] = ((cnk[7][1][1]*s13)+(cnk[8][1][0]*c13));
    cnk[13][1][1] = ((cnk[7][1][1]*c13)-(cnk[8][1][0]*s13));
    cnk[13][2][0] = ((cnk[7][2][1]*s13)+(cnk[8][2][0]*c13));
    cnk[13][2][1] = ((cnk[7][2][1]*c13)-(cnk[8][2][0]*s13));
    cnk[14][0][0] = ((cnk[13][0][0]*c14)-(cnk[8][0][2]*s14));
    cnk[14][0][2] = ((cnk[8][0][2]*c14)+(cnk[13][0][0]*s14));
    cnk[14][1][0] = ((cnk[13][1][0]*c14)-(cnk[8][1][2]*s14));
    cnk[14][1][2] = ((cnk[8][1][2]*c14)+(cnk[13][1][0]*s14));
    cnk[14][2][0] = ((cnk[13][2][0]*c14)-(cnk[8][2][2]*s14));
    cnk[14][2][2] = ((cnk[8][2][2]*c14)+(cnk[13][2][0]*s14));
    cnk[15][0][0] = ((cnk[14][0][0]*c15)-(cnk[14][0][2]*s15));
    cnk[15][0][2] = ((cnk[14][0][0]*s15)+(cnk[14][0][2]*c15));
    cnk[15][1][0] = ((cnk[14][1][0]*c15)-(cnk[14][1][2]*s15));
    cnk[15][1][2] = ((cnk[14][1][0]*s15)+(cnk[14][1][2]*c15));
    cnk[15][2][0] = ((cnk[14][2][0]*c15)-(cnk[14][2][2]*s15));
    cnk[15][2][2] = ((cnk[14][2][0]*s15)+(cnk[14][2][2]*c15));
    cnk[16][0][1] = ((cnk[13][0][1]*c16)+(cnk[15][0][2]*s16));
    cnk[16][0][2] = ((cnk[15][0][2]*c16)-(cnk[13][0][1]*s16));
    cnk[16][1][1] = ((cnk[13][1][1]*c16)+(cnk[15][1][2]*s16));
    cnk[16][1][2] = ((cnk[15][1][2]*c16)-(cnk[13][1][1]*s16));
    cnk[16][2][1] = ((cnk[13][2][1]*c16)+(cnk[15][2][2]*s16));
    cnk[16][2][2] = ((cnk[15][2][2]*c16)-(cnk[13][2][1]*s16));
    cnk[17][0][0] = ((cnk[15][0][0]*c17)+(cnk[16][0][1]*s17));
    cnk[17][0][1] = ((cnk[16][0][1]*c17)-(cnk[15][0][0]*s17));
    cnk[17][1][0] = ((cnk[15][1][0]*c17)+(cnk[16][1][1]*s17));
    cnk[17][1][1] = ((cnk[16][1][1]*c17)-(cnk[15][1][0]*s17));
    cnk[17][2][0] = ((cnk[15][2][0]*c17)+(cnk[16][2][1]*s17));
    cnk[17][2][1] = ((cnk[16][2][1]*c17)-(cnk[15][2][0]*s17));
    cnk[18][0][0] = ((cnk[17][0][0]*c18)-(cnk[16][0][2]*s18));
    cnk[18][0][2] = ((cnk[16][0][2]*c18)+(cnk[17][0][0]*s18));
    cnk[18][1][0] = ((cnk[17][1][0]*c18)-(cnk[16][1][2]*s18));
    cnk[18][1][2] = ((cnk[16][1][2]*c18)+(cnk[17][1][0]*s18));
    cnk[18][2][0] = ((cnk[17][2][0]*c18)-(cnk[16][2][2]*s18));
    cnk[18][2][2] = ((cnk[16][2][2]*c18)+(cnk[17][2][0]*s18));
    cnk[19][0][0] = ((cnk[7][0][1]*s19)+(cnk[8][0][0]*c19));
    cnk[19][0][1] = ((cnk[7][0][1]*c19)-(cnk[8][0][0]*s19));
    cnk[19][1][0] = ((cnk[7][1][1]*s19)+(cnk[8][1][0]*c19));
    cnk[19][1][1] = ((cnk[7][1][1]*c19)-(cnk[8][1][0]*s19));
    cnk[19][2][0] = ((cnk[7][2][1]*s19)+(cnk[8][2][0]*c19));
    cnk[19][2][1] = ((cnk[7][2][1]*c19)-(cnk[8][2][0]*s19));
    cnk[20][0][0] = ((cnk[19][0][0]*c20)-(cnk[8][0][2]*s20));
    cnk[20][0][2] = ((cnk[8][0][2]*c20)+(cnk[19][0][0]*s20));
    cnk[20][1][0] = ((cnk[19][1][0]*c20)-(cnk[8][1][2]*s20));
    cnk[20][1][2] = ((cnk[8][1][2]*c20)+(cnk[19][1][0]*s20));
    cnk[20][2][0] = ((cnk[19][2][0]*c20)-(cnk[8][2][2]*s20));
    cnk[20][2][2] = ((cnk[8][2][2]*c20)+(cnk[19][2][0]*s20));
    cnk[21][0][0] = ((cnk[20][0][0]*c21)-(cnk[20][0][2]*s21));
    cnk[21][0][2] = ((cnk[20][0][0]*s21)+(cnk[20][0][2]*c21));
    cnk[21][1][0] = ((cnk[20][1][0]*c21)-(cnk[20][1][2]*s21));
    cnk[21][1][2] = ((cnk[20][1][0]*s21)+(cnk[20][1][2]*c21));
    cnk[21][2][0] = ((cnk[20][2][0]*c21)-(cnk[20][2][2]*s21));
    cnk[21][2][2] = ((cnk[20][2][0]*s21)+(cnk[20][2][2]*c21));
    cnk[22][0][1] = ((cnk[19][0][1]*c22)+(cnk[21][0][2]*s22));
    cnk[22][0][2] = ((cnk[21][0][2]*c22)-(cnk[19][0][1]*s22));
    cnk[22][1][1] = ((cnk[19][1][1]*c22)+(cnk[21][1][2]*s22));
    cnk[22][1][2] = ((cnk[21][1][2]*c22)-(cnk[19][1][1]*s22));
    cnk[22][2][1] = ((cnk[19][2][1]*c22)+(cnk[21][2][2]*s22));
    cnk[22][2][2] = ((cnk[21][2][2]*c22)-(cnk[19][2][1]*s22));
    cnk[23][0][0] = ((cnk[21][0][0]*c23)+(cnk[22][0][1]*s23));
    cnk[23][0][1] = ((cnk[22][0][1]*c23)-(cnk[21][0][0]*s23));
    cnk[23][1][0] = ((cnk[21][1][0]*c23)+(cnk[22][1][1]*s23));
    cnk[23][1][1] = ((cnk[22][1][1]*c23)-(cnk[21][1][0]*s23));
    cnk[23][2][0] = ((cnk[21][2][0]*c23)+(cnk[22][2][1]*s23));
    cnk[23][2][1] = ((cnk[22][2][1]*c23)-(cnk[21][2][0]*s23));
    cnk[24][0][0] = ((cnk[23][0][0]*c24)-(cnk[22][0][2]*s24));
    cnk[24][0][2] = ((cnk[22][0][2]*c24)+(cnk[23][0][0]*s24));
    cnk[24][1][0] = ((cnk[23][1][0]*c24)-(cnk[22][1][2]*s24));
    cnk[24][1][2] = ((cnk[22][1][2]*c24)+(cnk[23][1][0]*s24));
    cnk[24][2][0] = ((cnk[23][2][0]*c24)-(cnk[22][2][2]*s24));
    cnk[24][2][2] = ((cnk[22][2][2]*c24)+(cnk[23][2][0]*s24));
    cnk[25][0][1] = ((Cik[3][0][1]*c25)+(Cik[3][0][2]*s25));
    cnk[25][0][2] = ((Cik[3][0][2]*c25)-(Cik[3][0][1]*s25));
    cnk[25][1][1] = ((Cik[3][1][1]*c25)+(Cik[3][1][2]*s25));
    cnk[25][1][2] = ((Cik[3][1][2]*c25)-(Cik[3][1][1]*s25));
    cnk[25][2][1] = ((Cik[3][2][1]*c25)+(Cik[3][2][2]*s25));
    cnk[25][2][2] = ((Cik[3][2][2]*c25)-(Cik[3][2][1]*s25));
    cnk[26][0][0] = ((Cik[3][0][0]*c26)+(cnk[25][0][1]*s26));
    cnk[26][0][1] = ((cnk[25][0][1]*c26)-(Cik[3][0][0]*s26));
    cnk[26][1][0] = ((Cik[3][1][0]*c26)+(cnk[25][1][1]*s26));
    cnk[26][1][1] = ((cnk[25][1][1]*c26)-(Cik[3][1][0]*s26));
    cnk[26][2][0] = ((Cik[3][2][0]*c26)+(cnk[25][2][1]*s26));
    cnk[26][2][1] = ((cnk[25][2][1]*c26)-(Cik[3][2][0]*s26));
    cnk[27][0][0] = ((cnk[26][0][0]*c27)-(cnk[25][0][2]*s27));
    cnk[27][0][2] = ((cnk[25][0][2]*c27)+(cnk[26][0][0]*s27));
    cnk[27][1][0] = ((cnk[26][1][0]*c27)-(cnk[25][1][2]*s27));
    cnk[27][1][2] = ((cnk[25][1][2]*c27)+(cnk[26][1][0]*s27));
    cnk[27][2][0] = ((cnk[26][2][0]*c27)-(cnk[25][2][2]*s27));
    cnk[27][2][2] = ((cnk[25][2][2]*c27)+(cnk[26][2][0]*s27));
    cnk[28][0][1] = ((cnk[26][0][1]*c28)+(cnk[27][0][2]*s28));
    cnk[28][0][2] = ((cnk[27][0][2]*c28)-(cnk[26][0][1]*s28));
    cnk[28][1][1] = ((cnk[26][1][1]*c28)+(cnk[27][1][2]*s28));
    cnk[28][1][2] = ((cnk[27][1][2]*c28)-(cnk[26][1][1]*s28));
    cnk[28][2][1] = ((cnk[26][2][1]*c28)+(cnk[27][2][2]*s28));
    cnk[28][2][2] = ((cnk[27][2][2]*c28)-(cnk[26][2][1]*s28));
    cnk[29][0][1] = ((cnk[28][0][1]*c29)+(cnk[28][0][2]*s29));
    cnk[29][0][2] = ((cnk[28][0][2]*c29)-(cnk[28][0][1]*s29));
    cnk[29][1][1] = ((cnk[28][1][1]*c29)+(cnk[28][1][2]*s29));
    cnk[29][1][2] = ((cnk[28][1][2]*c29)-(cnk[28][1][1]*s29));
    cnk[29][2][1] = ((cnk[28][2][1]*c29)+(cnk[28][2][2]*s29));
    cnk[29][2][2] = ((cnk[28][2][2]*c29)-(cnk[28][2][1]*s29));
    cnk[30][0][0] = ((cnk[27][0][0]*c30)+(cnk[29][0][1]*s30));
    cnk[30][0][1] = ((cnk[29][0][1]*c30)-(cnk[27][0][0]*s30));
    cnk[30][1][0] = ((cnk[27][1][0]*c30)+(cnk[29][1][1]*s30));
    cnk[30][1][1] = ((cnk[29][1][1]*c30)-(cnk[27][1][0]*s30));
    cnk[30][2][0] = ((cnk[27][2][0]*c30)+(cnk[29][2][1]*s30));
    cnk[30][2][1] = ((cnk[29][2][1]*c30)-(cnk[27][2][0]*s30));
    cnk[31][0][1] = ((Cik[3][0][1]*c31)+(Cik[3][0][2]*s31));
    cnk[31][0][2] = ((Cik[3][0][2]*c31)-(Cik[3][0][1]*s31));
    cnk[31][1][1] = ((Cik[3][1][1]*c31)+(Cik[3][1][2]*s31));
    cnk[31][1][2] = ((Cik[3][1][2]*c31)-(Cik[3][1][1]*s31));
    cnk[31][2][1] = ((Cik[3][2][1]*c31)+(Cik[3][2][2]*s31));
    cnk[31][2][2] = ((Cik[3][2][2]*c31)-(Cik[3][2][1]*s31));
    cnk[32][0][0] = ((Cik[3][0][0]*c32)+(cnk[31][0][1]*s32));
    cnk[32][0][1] = ((cnk[31][0][1]*c32)-(Cik[3][0][0]*s32));
    cnk[32][1][0] = ((Cik[3][1][0]*c32)+(cnk[31][1][1]*s32));
    cnk[32][1][1] = ((cnk[31][1][1]*c32)-(Cik[3][1][0]*s32));
    cnk[32][2][0] = ((Cik[3][2][0]*c32)+(cnk[31][2][1]*s32));
    cnk[32][2][1] = ((cnk[31][2][1]*c32)-(Cik[3][2][0]*s32));
    cnk[33][0][0] = ((cnk[32][0][0]*c33)-(cnk[31][0][2]*s33));
    cnk[33][0][2] = ((cnk[31][0][2]*c33)+(cnk[32][0][0]*s33));
    cnk[33][1][0] = ((cnk[32][1][0]*c33)-(cnk[31][1][2]*s33));
    cnk[33][1][2] = ((cnk[31][1][2]*c33)+(cnk[32][1][0]*s33));
    cnk[33][2][0] = ((cnk[32][2][0]*c33)-(cnk[31][2][2]*s33));
    cnk[33][2][2] = ((cnk[31][2][2]*c33)+(cnk[32][2][0]*s33));
    cnk[34][0][1] = ((cnk[32][0][1]*c34)+(cnk[33][0][2]*s34));
    cnk[34][0][2] = ((cnk[33][0][2]*c34)-(cnk[32][0][1]*s34));
    cnk[34][1][1] = ((cnk[32][1][1]*c34)+(cnk[33][1][2]*s34));
    cnk[34][1][2] = ((cnk[33][1][2]*c34)-(cnk[32][1][1]*s34));
    cnk[34][2][1] = ((cnk[32][2][1]*c34)+(cnk[33][2][2]*s34));
    cnk[34][2][2] = ((cnk[33][2][2]*c34)-(cnk[32][2][1]*s34));
    cnk[35][0][1] = ((cnk[34][0][1]*c35)+(cnk[34][0][2]*s35));
    cnk[35][0][2] = ((cnk[34][0][2]*c35)-(cnk[34][0][1]*s35));
    cnk[35][1][1] = ((cnk[34][1][1]*c35)+(cnk[34][1][2]*s35));
    cnk[35][1][2] = ((cnk[34][1][2]*c35)-(cnk[34][1][1]*s35));
    cnk[35][2][1] = ((cnk[34][2][1]*c35)+(cnk[34][2][2]*s35));
    cnk[35][2][2] = ((cnk[34][2][2]*c35)-(cnk[34][2][1]*s35));
    cnk[36][0][0] = ((cnk[33][0][0]*c36)+(cnk[35][0][1]*s36));
    cnk[36][0][1] = ((cnk[35][0][1]*c36)-(cnk[33][0][0]*s36));
    cnk[36][1][0] = ((cnk[33][1][0]*c36)+(cnk[35][1][1]*s36));
    cnk[36][1][1] = ((cnk[35][1][1]*c36)-(cnk[33][1][0]*s36));
    cnk[36][2][0] = ((cnk[33][2][0]*c36)+(cnk[35][2][1]*s36));
    cnk[36][2][1] = ((cnk[35][2][1]*c36)-(cnk[33][2][0]*s36));
    cnb[0][0][0] = Cik[3][0][0];
    cnb[0][0][1] = Cik[3][0][1];
    cnb[0][0][2] = Cik[3][0][2];
    cnb[0][1][0] = Cik[3][1][0];
    cnb[0][1][1] = Cik[3][1][1];
    cnb[0][1][2] = Cik[3][1][2];
    cnb[0][2][0] = Cik[3][2][0];
    cnb[0][2][1] = Cik[3][2][1];
    cnb[0][2][2] = Cik[3][2][2];
    cnb[1][0][0] = cnk[8][0][0];
    cnb[1][0][1] = cnk[7][0][1];
    cnb[1][0][2] = cnk[8][0][2];
    cnb[1][1][0] = cnk[8][1][0];
    cnb[1][1][1] = cnk[7][1][1];
    cnb[1][1][2] = cnk[8][1][2];
    cnb[1][2][0] = cnk[8][2][0];
    cnb[1][2][1] = cnk[7][2][1];
    cnb[1][2][2] = cnk[8][2][2];
    cnb[2][0][0] = cnk[11][0][0];
    cnb[2][0][1] = cnk[10][0][1];
    cnb[2][0][2] = cnk[11][0][2];
    cnb[2][1][0] = cnk[11][1][0];
    cnb[2][1][1] = cnk[10][1][1];
    cnb[2][1][2] = cnk[11][1][2];
    cnb[2][2][0] = cnk[11][2][0];
    cnb[2][2][1] = cnk[10][2][1];
    cnb[2][2][2] = cnk[11][2][2];
    cnb[3][0][0] = cnk[11][0][0];
    cnb[3][0][1] = cnk[12][0][1];
    cnb[3][0][2] = cnk[12][0][2];
    cnb[3][1][0] = cnk[11][1][0];
    cnb[3][1][1] = cnk[12][1][1];
    cnb[3][1][2] = cnk[12][1][2];
    cnb[3][2][0] = cnk[11][2][0];
    cnb[3][2][1] = cnk[12][2][1];
    cnb[3][2][2] = cnk[12][2][2];
    cnb[4][0][0] = cnk[14][0][0];
    cnb[4][0][1] = cnk[13][0][1];
    cnb[4][0][2] = cnk[14][0][2];
    cnb[4][1][0] = cnk[14][1][0];
    cnb[4][1][1] = cnk[13][1][1];
    cnb[4][1][2] = cnk[14][1][2];
    cnb[4][2][0] = cnk[14][2][0];
    cnb[4][2][1] = cnk[13][2][1];
    cnb[4][2][2] = cnk[14][2][2];
    cnb[5][0][0] = cnk[15][0][0];
    cnb[5][0][1] = cnk[16][0][1];
    cnb[5][0][2] = cnk[16][0][2];
    cnb[5][1][0] = cnk[15][1][0];
    cnb[5][1][1] = cnk[16][1][1];
    cnb[5][1][2] = cnk[16][1][2];
    cnb[5][2][0] = cnk[15][2][0];
    cnb[5][2][1] = cnk[16][2][1];
    cnb[5][2][2] = cnk[16][2][2];
    cnb[6][0][0] = cnk[18][0][0];
    cnb[6][0][1] = cnk[17][0][1];
    cnb[6][0][2] = cnk[18][0][2];
    cnb[6][1][0] = cnk[18][1][0];
    cnb[6][1][1] = cnk[17][1][1];
    cnb[6][1][2] = cnk[18][1][2];
    cnb[6][2][0] = cnk[18][2][0];
    cnb[6][2][1] = cnk[17][2][1];
    cnb[6][2][2] = cnk[18][2][2];
    cnb[7][0][0] = cnk[20][0][0];
    cnb[7][0][1] = cnk[19][0][1];
    cnb[7][0][2] = cnk[20][0][2];
    cnb[7][1][0] = cnk[20][1][0];
    cnb[7][1][1] = cnk[19][1][1];
    cnb[7][1][2] = cnk[20][1][2];
    cnb[7][2][0] = cnk[20][2][0];
    cnb[7][2][1] = cnk[19][2][1];
    cnb[7][2][2] = cnk[20][2][2];
    cnb[8][0][0] = cnk[21][0][0];
    cnb[8][0][1] = cnk[22][0][1];
    cnb[8][0][2] = cnk[22][0][2];
    cnb[8][1][0] = cnk[21][1][0];
    cnb[8][1][1] = cnk[22][1][1];
    cnb[8][1][2] = cnk[22][1][2];
    cnb[8][2][0] = cnk[21][2][0];
    cnb[8][2][1] = cnk[22][2][1];
    cnb[8][2][2] = cnk[22][2][2];
    cnb[9][0][0] = cnk[24][0][0];
    cnb[9][0][1] = cnk[23][0][1];
    cnb[9][0][2] = cnk[24][0][2];
    cnb[9][1][0] = cnk[24][1][0];
    cnb[9][1][1] = cnk[23][1][1];
    cnb[9][1][2] = cnk[24][1][2];
    cnb[9][2][0] = cnk[24][2][0];
    cnb[9][2][1] = cnk[23][2][1];
    cnb[9][2][2] = cnk[24][2][2];
    cnb[10][0][0] = cnk[27][0][0];
    cnb[10][0][1] = cnk[26][0][1];
    cnb[10][0][2] = cnk[27][0][2];
    cnb[10][1][0] = cnk[27][1][0];
    cnb[10][1][1] = cnk[26][1][1];
    cnb[10][1][2] = cnk[27][1][2];
    cnb[10][2][0] = cnk[27][2][0];
    cnb[10][2][1] = cnk[26][2][1];
    cnb[10][2][2] = cnk[27][2][2];
    cnb[11][0][0] = cnk[27][0][0];
    cnb[11][0][1] = cnk[28][0][1];
    cnb[11][0][2] = cnk[28][0][2];
    cnb[11][1][0] = cnk[27][1][0];
    cnb[11][1][1] = cnk[28][1][1];
    cnb[11][1][2] = cnk[28][1][2];
    cnb[11][2][0] = cnk[27][2][0];
    cnb[11][2][1] = cnk[28][2][1];
    cnb[11][2][2] = cnk[28][2][2];
    cnb[12][0][0] = cnk[30][0][0];
    cnb[12][0][1] = cnk[30][0][1];
    cnb[12][0][2] = cnk[29][0][2];
    cnb[12][1][0] = cnk[30][1][0];
    cnb[12][1][1] = cnk[30][1][1];
    cnb[12][1][2] = cnk[29][1][2];
    cnb[12][2][0] = cnk[30][2][0];
    cnb[12][2][1] = cnk[30][2][1];
    cnb[12][2][2] = cnk[29][2][2];
    cnb[13][0][0] = cnk[33][0][0];
    cnb[13][0][1] = cnk[32][0][1];
    cnb[13][0][2] = cnk[33][0][2];
    cnb[13][1][0] = cnk[33][1][0];
    cnb[13][1][1] = cnk[32][1][1];
    cnb[13][1][2] = cnk[33][1][2];
    cnb[13][2][0] = cnk[33][2][0];
    cnb[13][2][1] = cnk[32][2][1];
    cnb[13][2][2] = cnk[33][2][2];
    cnb[14][0][0] = cnk[33][0][0];
    cnb[14][0][1] = cnk[34][0][1];
    cnb[14][0][2] = cnk[34][0][2];
    cnb[14][1][0] = cnk[33][1][0];
    cnb[14][1][1] = cnk[34][1][1];
    cnb[14][1][2] = cnk[34][1][2];
    cnb[14][2][0] = cnk[33][2][0];
    cnb[14][2][1] = cnk[34][2][1];
    cnb[14][2][2] = cnk[34][2][2];
    cnb[15][0][0] = cnk[36][0][0];
    cnb[15][0][1] = cnk[36][0][1];
    cnb[15][0][2] = cnk[35][0][2];
    cnb[15][1][0] = cnk[36][1][0];
    cnb[15][1][1] = cnk[36][1][1];
    cnb[15][1][2] = cnk[35][1][2];
    cnb[15][2][0] = cnk[36][2][0];
    cnb[15][2][1] = cnk[36][2][1];
    cnb[15][2][2] = cnk[35][2][2];
/*
Compute q-related auxiliary variables
*/
    rik[6][1] = ((.05*s6)+(.1206*c6));
    rik[6][2] = ((.05*c6)-(.1206*s6));
    rik[9][1] = ((.24635*c9)-(.0013*s9));
    rik[9][2] = -((.0013*c9)+(.24635*s9));
    rik[12][1] = (.078+((.0065*s12)+(.0442*c12)));
    rik[12][2] = (.0312+((.0065*c12)-(.0442*s12)));
    rik[13][0] = ((.1768*c13)+(.18915*s13));
    rik[13][1] = ((.18915*c13)-(.1768*s13));
    rik[15][0] = ((.1326*c15)-(.0013*s15));
    rik[15][2] = ((.0013*c15)+(.1326*s15));
    rik[17][0] = ((.0039*s17)+(.1378*c17));
    rik[17][1] = ((.0039*c17)-(.1378*s17));
    rik[19][0] = ((.18915*s19)-(.1768*c19));
    rik[19][1] = ((.1768*s19)+(.18915*c19));
    rik[21][0] = -((.0013*s21)+(.1326*c21));
    rik[21][2] = ((.0013*c21)-(.1326*s21));
    rik[23][0] = ((.0039*s23)-(.1378*c23));
    rik[23][1] = ((.0039*c23)+(.1378*s23));
    rik[25][1] = ((.0058*s25)-(.0406*c25));
    rik[25][2] = ((.0058*c25)+(.0406*s25));
    rik[28][1] = (((.0143*s28)-(.2379*c28))-.2158);
    rik[28][2] = (((.0143*c28)+(.2379*s28))-.0039);
    rik[29][1] = -((.0039*s29)+(.2158*c29));
    rik[29][2] = ((.2158*s29)-(.0039*c29));
    rik[31][1] = ((.0058*s31)-(.0406*c31));
    rik[31][2] = ((.0058*c31)+(.0406*s31));
    rik[34][1] = (((.0143*s34)-(.2379*c34))-.2158);
    rik[34][2] = (((.0143*c34)+(.2379*s34))-.0039);
    rik[35][1] = -((.0039*s35)+(.2158*c35));
    rik[35][2] = ((.2158*s35)-(.0039*c35));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[1][1] = (1.131+q[1]);
    rnk[2][2] = (.0052+q[2]);
    rnk[5][0] = (q[0]-((.05*Cik[3][0][2])+(.1206*Cik[3][0][1])));
    rnk[5][1] = (rnk[1][1]-((.05*Cik[3][1][2])+(.1206*Cik[3][1][1])));
    rnk[5][2] = (rnk[2][2]-((.05*Cik[3][2][2])+(.1206*Cik[3][2][1])));
    rnk[6][0] = (rnk[5][0]+((.05*Cik[3][0][2])+(.1206*Cik[3][0][1])));
    rnk[6][1] = (rnk[5][1]+((.05*Cik[3][1][2])+(.1206*Cik[3][1][1])));
    rnk[6][2] = (rnk[5][2]+((.05*Cik[3][2][2])+(.1206*Cik[3][2][1])));
    rnk[8][0] = (rnk[6][0]+((.14625*cnk[7][0][1])-(.0351*cnk[8][0][2])));
    rnk[8][1] = (rnk[6][1]+((.14625*cnk[7][1][1])-(.0351*cnk[8][1][2])));
    rnk[8][2] = (rnk[6][2]+((.14625*cnk[7][2][1])-(.0351*cnk[8][2][2])));
    rnk[9][0] = (rnk[8][0]+((.24635*cnk[7][0][1])-(.0013*cnk[8][0][2])));
    rnk[9][1] = (rnk[8][1]+((.24635*cnk[7][1][1])-(.0013*cnk[8][1][2])));
    rnk[9][2] = (rnk[8][2]+((.24635*cnk[7][2][1])-(.0013*cnk[8][2][2])));
    rnk[11][0] = (rnk[9][0]+((.0065*cnk[11][0][2])+(.0442*cnk[10][0][1])));
    rnk[11][1] = (rnk[9][1]+((.0065*cnk[11][1][2])+(.0442*cnk[10][1][1])));
    rnk[11][2] = (rnk[9][2]+((.0065*cnk[11][2][2])+(.0442*cnk[10][2][1])));
    rnk[12][0] = ((rnk[11][0]+((.0065*cnk[11][0][2])+(.0442*cnk[10][0][1])))+((
      .0312*cnk[12][0][2])+(.078*cnk[12][0][1])));
    rnk[12][1] = ((rnk[11][1]+((.0065*cnk[11][1][2])+(.0442*cnk[10][1][1])))+((
      .0312*cnk[12][1][2])+(.078*cnk[12][1][1])));
    rnk[12][2] = ((rnk[11][2]+((.0065*cnk[11][2][2])+(.0442*cnk[10][2][1])))+((
      .0312*cnk[12][2][2])+(.078*cnk[12][2][1])));
    rnk[13][0] = (rnk[8][0]+((.0013*cnk[8][0][2])+((.1768*cnk[8][0][0])+(.18915*
      cnk[7][0][1]))));
    rnk[13][1] = (rnk[8][1]+((.0013*cnk[8][1][2])+((.1768*cnk[8][1][0])+(.18915*
      cnk[7][1][1]))));
    rnk[13][2] = (rnk[8][2]+((.0013*cnk[8][2][2])+((.1768*cnk[8][2][0])+(.18915*
      cnk[7][2][1]))));
    rnk[14][0] = (rnk[13][0]+((.0013*cnk[14][0][2])+(.1326*cnk[14][0][0])));
    rnk[14][1] = (rnk[13][1]+((.0013*cnk[14][1][2])+(.1326*cnk[14][1][0])));
    rnk[14][2] = (rnk[13][2]+((.0013*cnk[14][2][2])+(.1326*cnk[14][2][0])));
    rnk[15][0] = (rnk[14][0]+((.0013*cnk[14][0][2])+(.1326*cnk[14][0][0])));
    rnk[15][1] = (rnk[14][1]+((.0013*cnk[14][1][2])+(.1326*cnk[14][1][0])));
    rnk[15][2] = (rnk[14][2]+((.0013*cnk[14][2][2])+(.1326*cnk[14][2][0])));
    rnk[16][0] = (rnk[15][0]+((.0039*cnk[16][0][1])+(.1378*cnk[15][0][0])));
    rnk[16][1] = (rnk[15][1]+((.0039*cnk[16][1][1])+(.1378*cnk[15][1][0])));
    rnk[16][2] = (rnk[15][2]+((.0039*cnk[16][2][1])+(.1378*cnk[15][2][0])));
    rnk[17][0] = (rnk[16][0]+((.0039*cnk[16][0][1])+(.1378*cnk[15][0][0])));
    rnk[17][1] = (rnk[16][1]+((.0039*cnk[16][1][1])+(.1378*cnk[15][1][0])));
    rnk[17][2] = (rnk[16][2]+((.0039*cnk[16][2][1])+(.1378*cnk[15][2][0])));
    rnk[18][0] = (rnk[17][0]+(.065*cnk[18][0][0]));
    rnk[18][1] = (rnk[17][1]+(.065*cnk[18][1][0]));
    rnk[18][2] = (rnk[17][2]+(.065*cnk[18][2][0]));
    rnk[19][0] = (rnk[8][0]+((.0013*cnk[8][0][2])+((.18915*cnk[7][0][1])-(.1768*
      cnk[8][0][0]))));
    rnk[19][1] = (rnk[8][1]+((.0013*cnk[8][1][2])+((.18915*cnk[7][1][1])-(.1768*
      cnk[8][1][0]))));
    rnk[19][2] = (rnk[8][2]+((.0013*cnk[8][2][2])+((.18915*cnk[7][2][1])-(.1768*
      cnk[8][2][0]))));
    rnk[20][0] = (rnk[19][0]+((.0013*cnk[20][0][2])-(.1326*cnk[20][0][0])));
    rnk[20][1] = (rnk[19][1]+((.0013*cnk[20][1][2])-(.1326*cnk[20][1][0])));
    rnk[20][2] = (rnk[19][2]+((.0013*cnk[20][2][2])-(.1326*cnk[20][2][0])));
    rnk[21][0] = (rnk[20][0]+((.0013*cnk[20][0][2])-(.1326*cnk[20][0][0])));
    rnk[21][1] = (rnk[20][1]+((.0013*cnk[20][1][2])-(.1326*cnk[20][1][0])));
    rnk[21][2] = (rnk[20][2]+((.0013*cnk[20][2][2])-(.1326*cnk[20][2][0])));
    rnk[22][0] = (rnk[21][0]+((.0039*cnk[22][0][1])-(.1378*cnk[21][0][0])));
    rnk[22][1] = (rnk[21][1]+((.0039*cnk[22][1][1])-(.1378*cnk[21][1][0])));
    rnk[22][2] = (rnk[21][2]+((.0039*cnk[22][2][1])-(.1378*cnk[21][2][0])));
    rnk[23][0] = (rnk[22][0]+((.0039*cnk[22][0][1])-(.1378*cnk[21][0][0])));
    rnk[23][1] = (rnk[22][1]+((.0039*cnk[22][1][1])-(.1378*cnk[21][1][0])));
    rnk[23][2] = (rnk[22][2]+((.0039*cnk[22][2][1])-(.1378*cnk[21][2][0])));
    rnk[24][0] = (rnk[23][0]-(.065*cnk[24][0][0]));
    rnk[24][1] = (rnk[23][1]-(.065*cnk[24][1][0]));
    rnk[24][2] = (rnk[23][2]-(.065*cnk[24][2][0]));
    rnk[25][0] = (rnk[5][0]+((.0058*Cik[3][0][2])+((.1118*Cik[3][0][0])-(.0406*
      Cik[3][0][1]))));
    rnk[25][1] = (rnk[5][1]+((.0058*Cik[3][1][2])+((.1118*Cik[3][1][0])-(.0406*
      Cik[3][1][1]))));
    rnk[25][2] = (rnk[5][2]+((.0058*Cik[3][2][2])+((.1118*Cik[3][2][0])-(.0406*
      Cik[3][2][1]))));
    rnk[27][0] = (rnk[25][0]+((.0143*cnk[27][0][2])-((.0169*cnk[27][0][0])+(
      .2379*cnk[26][0][1]))));
    rnk[27][1] = (rnk[25][1]+((.0143*cnk[27][1][2])-((.0169*cnk[27][1][0])+(
      .2379*cnk[26][1][1]))));
    rnk[27][2] = (rnk[25][2]+((.0143*cnk[27][2][2])-((.0169*cnk[27][2][0])+(
      .2379*cnk[26][2][1]))));
    rnk[28][0] = ((rnk[27][0]+((.0143*cnk[27][0][2])-((.0169*cnk[27][0][0])+(
      .2379*cnk[26][0][1]))))-((.0039*cnk[28][0][2])+((.0078*cnk[27][0][0])+(
      .2158*cnk[28][0][1]))));
    rnk[28][1] = ((rnk[27][1]+((.0143*cnk[27][1][2])-((.0169*cnk[27][1][0])+(
      .2379*cnk[26][1][1]))))-((.0039*cnk[28][1][2])+((.0078*cnk[27][1][0])+(
      .2158*cnk[28][1][1]))));
    rnk[28][2] = ((rnk[27][2]+((.0143*cnk[27][2][2])-((.0169*cnk[27][2][0])+(
      .2379*cnk[26][2][1]))))-((.0039*cnk[28][2][2])+((.0078*cnk[27][2][0])+(
      .2158*cnk[28][2][1]))));
    rnk[29][0] = (rnk[28][0]-((.0039*cnk[28][0][2])+((.0078*cnk[27][0][0])+(
      .2158*cnk[28][0][1]))));
    rnk[29][1] = (rnk[28][1]-((.0039*cnk[28][1][2])+((.0078*cnk[27][1][0])+(
      .2158*cnk[28][1][1]))));
    rnk[29][2] = (rnk[28][2]-((.0039*cnk[28][2][2])+((.0078*cnk[27][2][0])+(
      .2158*cnk[28][2][1]))));
    rnk[30][0] = (rnk[29][0]+((.039*cnk[29][0][2])-(.0442*cnk[30][0][1])));
    rnk[30][1] = (rnk[29][1]+((.039*cnk[29][1][2])-(.0442*cnk[30][1][1])));
    rnk[30][2] = (rnk[29][2]+((.039*cnk[29][2][2])-(.0442*cnk[30][2][1])));
    rnk[31][0] = (rnk[5][0]+((.0058*Cik[3][0][2])-((.0406*Cik[3][0][1])+(.1118*
      Cik[3][0][0]))));
    rnk[31][1] = (rnk[5][1]+((.0058*Cik[3][1][2])-((.0406*Cik[3][1][1])+(.1118*
      Cik[3][1][0]))));
    rnk[31][2] = (rnk[5][2]+((.0058*Cik[3][2][2])-((.0406*Cik[3][2][1])+(.1118*
      Cik[3][2][0]))));
    rnk[33][0] = (rnk[31][0]+((.0143*cnk[33][0][2])+((.0169*cnk[33][0][0])-(
      .2379*cnk[32][0][1]))));
    rnk[33][1] = (rnk[31][1]+((.0143*cnk[33][1][2])+((.0169*cnk[33][1][0])-(
      .2379*cnk[32][1][1]))));
    rnk[33][2] = (rnk[31][2]+((.0143*cnk[33][2][2])+((.0169*cnk[33][2][0])-(
      .2379*cnk[32][2][1]))));
    rnk[34][0] = ((rnk[33][0]+((.0143*cnk[33][0][2])+((.0169*cnk[33][0][0])-(
      .2379*cnk[32][0][1]))))+(((.0078*cnk[33][0][0])-(.2158*cnk[34][0][1]))-(
      .0039*cnk[34][0][2])));
    rnk[34][1] = ((rnk[33][1]+((.0143*cnk[33][1][2])+((.0169*cnk[33][1][0])-(
      .2379*cnk[32][1][1]))))+(((.0078*cnk[33][1][0])-(.2158*cnk[34][1][1]))-(
      .0039*cnk[34][1][2])));
    rnk[34][2] = ((rnk[33][2]+((.0143*cnk[33][2][2])+((.0169*cnk[33][2][0])-(
      .2379*cnk[32][2][1]))))+(((.0078*cnk[33][2][0])-(.2158*cnk[34][2][1]))-(
      .0039*cnk[34][2][2])));
    rnk[35][0] = (rnk[34][0]+(((.0078*cnk[33][0][0])-(.2158*cnk[34][0][1]))-(
      .0039*cnk[34][0][2])));
    rnk[35][1] = (rnk[34][1]+(((.0078*cnk[33][1][0])-(.2158*cnk[34][1][1]))-(
      .0039*cnk[34][1][2])));
    rnk[35][2] = (rnk[34][2]+(((.0078*cnk[33][2][0])-(.2158*cnk[34][2][1]))-(
      .0039*cnk[34][2][2])));
    rnk[36][0] = (rnk[35][0]+((.039*cnk[35][0][2])-(.0442*cnk[36][0][1])));
    rnk[36][1] = (rnk[35][1]+((.039*cnk[35][1][2])-(.0442*cnk[36][1][1])));
    rnk[36][2] = (rnk[35][2]+((.039*cnk[35][2][2])-(.0442*cnk[36][2][1])));
    rnb[0][0] = rnk[5][0];
    rnb[0][1] = rnk[5][1];
    rnb[0][2] = rnk[5][2];
    rnb[1][0] = rnk[8][0];
    rnb[1][1] = rnk[8][1];
    rnb[1][2] = rnk[8][2];
    rnb[2][0] = rnk[11][0];
    rnb[2][1] = rnk[11][1];
    rnb[2][2] = rnk[11][2];
    rnb[3][0] = rnk[12][0];
    rnb[3][1] = rnk[12][1];
    rnb[3][2] = rnk[12][2];
    rnb[4][0] = rnk[14][0];
    rnb[4][1] = rnk[14][1];
    rnb[4][2] = rnk[14][2];
    rnb[5][0] = rnk[16][0];
    rnb[5][1] = rnk[16][1];
    rnb[5][2] = rnk[16][2];
    rnb[6][0] = rnk[18][0];
    rnb[6][1] = rnk[18][1];
    rnb[6][2] = rnk[18][2];
    rnb[7][0] = rnk[20][0];
    rnb[7][1] = rnk[20][1];
    rnb[7][2] = rnk[20][2];
    rnb[8][0] = rnk[22][0];
    rnb[8][1] = rnk[22][1];
    rnb[8][2] = rnk[22][2];
    rnb[9][0] = rnk[24][0];
    rnb[9][1] = rnk[24][1];
    rnb[9][2] = rnk[24][2];
    rnb[10][0] = rnk[27][0];
    rnb[10][1] = rnk[27][1];
    rnb[10][2] = rnk[27][2];
    rnb[11][0] = rnk[28][0];
    rnb[11][1] = rnk[28][1];
    rnb[11][2] = rnk[28][2];
    rnb[12][0] = rnk[30][0];
    rnb[12][1] = rnk[30][1];
    rnb[12][2] = rnk[30][2];
    rnb[13][0] = rnk[33][0];
    rnb[13][1] = rnk[33][1];
    rnb[13][2] = rnk[33][2];
    rnb[14][0] = rnk[34][0];
    rnb[14][1] = rnk[34][1];
    rnb[14][2] = rnk[34][2];
    rnb[15][0] = rnk[36][0];
    rnb[15][1] = rnk[36][1];
    rnb[15][2] = rnk[36][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = (.0111644523836106*((1.34*rnk[36][0])+((4.16*rnk[34][0])+((8.35*
      rnk[33][0])+((1.34*rnk[30][0])+((4.16*rnk[28][0])+((8.35*rnk[27][0])+((.55
      *rnk[24][0])+((1.21*rnk[22][0])+((2.79*rnk[20][0])+((.55*rnk[18][0])+((
      1.21*rnk[16][0])+((2.79*rnk[14][0])+((5.89*rnk[12][0])+(rnk[11][0]+((16.61
      *rnk[5][0])+(29.27*rnk[8][0])))))))))))))))));
    com[1] = (.0111644523836106*((1.34*rnk[36][1])+((4.16*rnk[34][1])+((8.35*
      rnk[33][1])+((1.34*rnk[30][1])+((4.16*rnk[28][1])+((8.35*rnk[27][1])+((.55
      *rnk[24][1])+((1.21*rnk[22][1])+((2.79*rnk[20][1])+((.55*rnk[18][1])+((
      1.21*rnk[16][1])+((2.79*rnk[14][1])+((5.89*rnk[12][1])+(rnk[11][1]+((16.61
      *rnk[5][1])+(29.27*rnk[8][1])))))))))))))))));
    com[2] = (.0111644523836106*((1.34*rnk[36][2])+((4.16*rnk[34][2])+((8.35*
      rnk[33][2])+((1.34*rnk[30][2])+((4.16*rnk[28][2])+((8.35*rnk[27][2])+((.55
      *rnk[24][2])+((1.21*rnk[22][2])+((2.79*rnk[20][2])+((.55*rnk[18][2])+((
      1.21*rnk[16][2])+((2.79*rnk[14][2])+((5.89*rnk[12][2])+(rnk[11][2]+((16.61
      *rnk[5][2])+(29.27*rnk[8][2])))))))))))))))));
    skipqs: ;
/*
Check for locked gimbal tree joint
*/
    if ((fabs((fabs(((Cik[3][2][0]*cnk[7][2][1])+((Cik[3][0][0]*cnk[7][0][1])+(
      Cik[3][1][0]*cnk[7][1][1]))))-1.)) <= .00380530190825445)  ) {
        skel18seterr(8,43);
    }
    if ((fabs((fabs(((cnk[8][2][0]*cnk[10][2][1])+((cnk[8][0][0]*cnk[10][0][1])+
      (cnk[8][1][0]*cnk[10][1][1]))))-1.)) <= .00380530190825445)  ) {
        skel18seterr(8,43);
    }
    if ((fabs((fabs(((Cik[3][2][0]*cnk[26][2][1])+((Cik[3][0][0]*cnk[26][0][1])+
      (Cik[3][1][0]*cnk[26][1][1]))))-1.)) <= .00380530190825445)  ) {
        skel18seterr(8,43);
    }
    if ((fabs((fabs(((Cik[3][2][0]*cnk[32][2][1])+((Cik[3][0][0]*cnk[32][0][1])+
      (Cik[3][1][0]*cnk[32][1][1]))))-1.)) <= .00380530190825445)  ) {
        skel18seterr(8,43);
    }
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 37; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[6][0] = (u[3]+u[6]);
    wk[6][1] = ((u[4]*c6)+(u[5]*s6));
    wk[6][2] = ((u[5]*c6)-(u[4]*s6));
    wk[7][0] = ((wk[6][0]*c7)+(wk[6][1]*s7));
    wk[7][1] = ((wk[6][1]*c7)-(wk[6][0]*s7));
    wk[7][2] = (u[7]+wk[6][2]);
    wk[8][0] = ((wk[7][0]*c8)-(wk[7][2]*s8));
    wk[8][1] = (u[8]+wk[7][1]);
    wk[8][2] = ((wk[7][0]*s8)+(wk[7][2]*c8));
    wk[9][0] = (u[9]+wk[8][0]);
    wk[9][1] = ((wk[8][1]*c9)+(wk[8][2]*s9));
    wk[9][2] = ((wk[8][2]*c9)-(wk[8][1]*s9));
    wk[10][0] = ((wk[9][0]*c10)+(wk[9][1]*s10));
    wk[10][1] = ((wk[9][1]*c10)-(wk[9][0]*s10));
    wk[10][2] = (u[10]+wk[9][2]);
    wk[11][0] = ((wk[10][0]*c11)-(wk[10][2]*s11));
    wk[11][1] = (u[11]+wk[10][1]);
    wk[11][2] = ((wk[10][0]*s11)+(wk[10][2]*c11));
    wk[12][0] = (u[12]+wk[11][0]);
    wk[12][1] = ((wk[11][1]*c12)+(wk[11][2]*s12));
    wk[12][2] = ((wk[11][2]*c12)-(wk[11][1]*s12));
    wk[13][0] = ((wk[8][0]*c13)+(wk[8][1]*s13));
    wk[13][1] = ((wk[8][1]*c13)-(wk[8][0]*s13));
    wk[13][2] = (u[13]+wk[8][2]);
    wk[14][0] = ((wk[13][0]*c14)-(wk[13][2]*s14));
    wk[14][1] = (u[14]+wk[13][1]);
    wk[14][2] = ((wk[13][0]*s14)+(wk[13][2]*c14));
    wk[15][0] = ((wk[14][0]*c15)-(wk[14][2]*s15));
    wk[15][1] = (u[15]+wk[14][1]);
    wk[15][2] = ((wk[14][0]*s15)+(wk[14][2]*c15));
    wk[16][0] = (u[16]+wk[15][0]);
    wk[16][1] = ((wk[15][1]*c16)+(wk[15][2]*s16));
    wk[16][2] = ((wk[15][2]*c16)-(wk[15][1]*s16));
    wk[17][0] = ((wk[16][0]*c17)+(wk[16][1]*s17));
    wk[17][1] = ((wk[16][1]*c17)-(wk[16][0]*s17));
    wk[17][2] = (u[17]+wk[16][2]);
    wk[18][0] = ((wk[17][0]*c18)-(wk[17][2]*s18));
    wk[18][1] = (u[18]+wk[17][1]);
    wk[18][2] = ((wk[17][0]*s18)+(wk[17][2]*c18));
    wk[19][0] = ((wk[8][0]*c19)+(wk[8][1]*s19));
    wk[19][1] = ((wk[8][1]*c19)-(wk[8][0]*s19));
    wk[19][2] = (u[19]+wk[8][2]);
    wk[20][0] = ((wk[19][0]*c20)-(wk[19][2]*s20));
    wk[20][1] = (u[20]+wk[19][1]);
    wk[20][2] = ((wk[19][0]*s20)+(wk[19][2]*c20));
    wk[21][0] = ((wk[20][0]*c21)-(wk[20][2]*s21));
    wk[21][1] = (u[21]+wk[20][1]);
    wk[21][2] = ((wk[20][0]*s21)+(wk[20][2]*c21));
    wk[22][0] = (u[22]+wk[21][0]);
    wk[22][1] = ((wk[21][1]*c22)+(wk[21][2]*s22));
    wk[22][2] = ((wk[21][2]*c22)-(wk[21][1]*s22));
    wk[23][0] = ((wk[22][0]*c23)+(wk[22][1]*s23));
    wk[23][1] = ((wk[22][1]*c23)-(wk[22][0]*s23));
    wk[23][2] = (u[23]+wk[22][2]);
    wk[24][0] = ((wk[23][0]*c24)-(wk[23][2]*s24));
    wk[24][1] = (u[24]+wk[23][1]);
    wk[24][2] = ((wk[23][0]*s24)+(wk[23][2]*c24));
    wk[25][0] = (u[3]+u[25]);
    wk[25][1] = ((u[4]*c25)+(u[5]*s25));
    wk[25][2] = ((u[5]*c25)-(u[4]*s25));
    wk[26][0] = ((wk[25][0]*c26)+(wk[25][1]*s26));
    wk[26][1] = ((wk[25][1]*c26)-(wk[25][0]*s26));
    wk[26][2] = (u[26]+wk[25][2]);
    wk[27][0] = ((wk[26][0]*c27)-(wk[26][2]*s27));
    wk[27][1] = (u[27]+wk[26][1]);
    wk[27][2] = ((wk[26][0]*s27)+(wk[26][2]*c27));
    wk[28][0] = (u[28]+wk[27][0]);
    wk[28][1] = ((wk[27][1]*c28)+(wk[27][2]*s28));
    wk[28][2] = ((wk[27][2]*c28)-(wk[27][1]*s28));
    wk[29][0] = (u[29]+wk[28][0]);
    wk[29][1] = ((wk[28][1]*c29)+(wk[28][2]*s29));
    wk[29][2] = ((wk[28][2]*c29)-(wk[28][1]*s29));
    wk[30][0] = ((wk[29][0]*c30)+(wk[29][1]*s30));
    wk[30][1] = ((wk[29][1]*c30)-(wk[29][0]*s30));
    wk[30][2] = (u[30]+wk[29][2]);
    wk[31][0] = (u[3]+u[31]);
    wk[31][1] = ((u[4]*c31)+(u[5]*s31));
    wk[31][2] = ((u[5]*c31)-(u[4]*s31));
    wk[32][0] = ((wk[31][0]*c32)+(wk[31][1]*s32));
    wk[32][1] = ((wk[31][1]*c32)-(wk[31][0]*s32));
    wk[32][2] = (u[32]+wk[31][2]);
    wk[33][0] = ((wk[32][0]*c33)-(wk[32][2]*s33));
    wk[33][1] = (u[33]+wk[32][1]);
    wk[33][2] = ((wk[32][0]*s33)+(wk[32][2]*c33));
    wk[34][0] = (u[34]+wk[33][0]);
    wk[34][1] = ((wk[33][1]*c34)+(wk[33][2]*s34));
    wk[34][2] = ((wk[33][2]*c34)-(wk[33][1]*s34));
    wk[35][0] = (u[35]+wk[34][0]);
    wk[35][1] = ((wk[34][1]*c35)+(wk[34][2]*s35));
    wk[35][2] = ((wk[34][2]*c35)-(wk[34][1]*s35));
    wk[36][0] = ((wk[35][0]*c36)+(wk[35][1]*s36));
    wk[36][1] = ((wk[35][1]*c36)-(wk[35][0]*s36));
    wk[36][2] = (u[36]+wk[35][2]);
    wb[0][0] = u[3];
    wb[0][1] = u[4];
    wb[0][2] = u[5];
    wb[1][0] = wk[8][0];
    wb[1][1] = wk[8][1];
    wb[1][2] = wk[8][2];
    wb[2][0] = wk[11][0];
    wb[2][1] = wk[11][1];
    wb[2][2] = wk[11][2];
    wb[3][0] = wk[12][0];
    wb[3][1] = wk[12][1];
    wb[3][2] = wk[12][2];
    wb[4][0] = wk[14][0];
    wb[4][1] = wk[14][1];
    wb[4][2] = wk[14][2];
    wb[5][0] = wk[16][0];
    wb[5][1] = wk[16][1];
    wb[5][2] = wk[16][2];
    wb[6][0] = wk[18][0];
    wb[6][1] = wk[18][1];
    wb[6][2] = wk[18][2];
    wb[7][0] = wk[20][0];
    wb[7][1] = wk[20][1];
    wb[7][2] = wk[20][2];
    wb[8][0] = wk[22][0];
    wb[8][1] = wk[22][1];
    wb[8][2] = wk[22][2];
    wb[9][0] = wk[24][0];
    wb[9][1] = wk[24][1];
    wb[9][2] = wk[24][2];
    wb[10][0] = wk[27][0];
    wb[10][1] = wk[27][1];
    wb[10][2] = wk[27][2];
    wb[11][0] = wk[28][0];
    wb[11][1] = wk[28][1];
    wb[11][2] = wk[28][2];
    wb[12][0] = wk[30][0];
    wb[12][1] = wk[30][1];
    wb[12][2] = wk[30][2];
    wb[13][0] = wk[33][0];
    wb[13][1] = wk[33][1];
    wb[13][2] = wk[33][2];
    wb[14][0] = wk[34][0];
    wb[14][1] = wk[34][1];
    wb[14][2] = wk[34][2];
    wb[15][0] = wk[36][0];
    wb[15][1] = wk[36][1];
    wb[15][2] = wk[36][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[6][0] = ((.05*u[4])-(.1206*u[5]));
    Wirk[9][0] = -((.0013*wk[8][1])+(.24635*wk[8][2]));
    Wirk[12][0] = ((.0065*wk[11][1])-(.0442*wk[11][2]));
    Wirk[13][0] = ((.0013*wk[8][1])-(.18915*wk[8][2]));
    Wirk[13][1] = ((.1768*wk[8][2])-(.0013*wk[8][0]));
    Wirk[13][2] = ((.18915*wk[8][0])-(.1768*wk[8][1]));
    Wirk[15][1] = ((.1326*wk[14][2])-(.0013*wk[14][0]));
    Wirk[17][2] = ((.0039*wk[16][0])-(.1378*wk[16][1]));
    Wirk[19][0] = ((.0013*wk[8][1])-(.18915*wk[8][2]));
    Wirk[19][1] = -((.0013*wk[8][0])+(.1768*wk[8][2]));
    Wirk[19][2] = ((.1768*wk[8][1])+(.18915*wk[8][0]));
    Wirk[21][1] = -((.0013*wk[20][0])+(.1326*wk[20][2]));
    Wirk[23][2] = ((.0039*wk[22][0])+(.1378*wk[22][1]));
    Wirk[25][0] = ((.0058*u[4])+(.0406*u[5]));
    Wirk[25][1] = ((.1118*u[5])-(.0058*u[3]));
    Wirk[25][2] = -((.0406*u[3])+(.1118*u[4]));
    Wirk[28][0] = ((.0143*wk[27][1])+(.2379*wk[27][2]));
    Wirk[28][1] = -((.0143*wk[27][0])+(.0169*wk[27][2]));
    Wirk[28][2] = ((.0169*wk[27][1])-(.2379*wk[27][0]));
    Wirk[29][0] = ((.2158*wk[28][2])-(.0039*wk[28][1]));
    Wirk[29][1] = ((.0039*wk[28][0])-(.0078*wk[28][2]));
    Wirk[29][2] = ((.0078*wk[28][1])-(.2158*wk[28][0]));
    Wirk[31][0] = ((.0058*u[4])+(.0406*u[5]));
    Wirk[31][1] = -((.0058*u[3])+(.1118*u[5]));
    Wirk[31][2] = ((.1118*u[4])-(.0406*u[3]));
    Wirk[34][0] = ((.0143*wk[33][1])+(.2379*wk[33][2]));
    Wirk[34][1] = ((.0169*wk[33][2])-(.0143*wk[33][0]));
    Wirk[34][2] = -((.0169*wk[33][1])+(.2379*wk[33][0]));
    Wirk[35][0] = ((.2158*wk[34][2])-(.0039*wk[34][1]));
    Wirk[35][1] = ((.0039*wk[34][0])+(.0078*wk[34][2]));
    Wirk[35][2] = -((.0078*wk[34][1])+(.2158*wk[34][0]));
    Wkrpk[5][0] = ((.1206*u[5])-(.05*u[4]));
    Wkrpk[8][0] = -((.0351*wk[8][1])+(.14625*wk[8][2]));
    Wkrpk[11][0] = ((.0065*wk[11][1])-(.0442*wk[11][2]));
    Wkrpk[12][0] = ((.0312*wk[12][1])-(.078*wk[12][2]));
    Wkrpk[14][1] = ((.1326*wk[14][2])-(.0013*wk[14][0]));
    Wkrpk[16][2] = ((.0039*wk[16][0])-(.1378*wk[16][1]));
    Wkrpk[20][1] = -((.0013*wk[20][0])+(.1326*wk[20][2]));
    Wkrpk[22][2] = ((.0039*wk[22][0])+(.1378*wk[22][1]));
    Wkrpk[27][0] = ((.0143*wk[27][1])+(.2379*wk[27][2]));
    Wkrpk[27][1] = -((.0143*wk[27][0])+(.0169*wk[27][2]));
    Wkrpk[27][2] = ((.0169*wk[27][1])-(.2379*wk[27][0]));
    Wkrpk[28][0] = ((.2158*wk[28][2])-(.0039*wk[28][1]));
    Wkrpk[28][1] = ((.0039*wk[28][0])-(.0078*wk[28][2]));
    Wkrpk[28][2] = ((.0078*wk[28][1])-(.2158*wk[28][0]));
    Wkrpk[30][0] = ((.039*wk[30][1])+(.0442*wk[30][2]));
    Wkrpk[33][0] = ((.0143*wk[33][1])+(.2379*wk[33][2]));
    Wkrpk[33][1] = ((.0169*wk[33][2])-(.0143*wk[33][0]));
    Wkrpk[33][2] = -((.0169*wk[33][1])+(.2379*wk[33][0]));
    Wkrpk[34][0] = ((.2158*wk[34][2])-(.0039*wk[34][1]));
    Wkrpk[34][1] = ((.0039*wk[34][0])+(.0078*wk[34][2]));
    Wkrpk[34][2] = -((.0078*wk[34][1])+(.2158*wk[34][0]));
    Wkrpk[36][0] = ((.039*wk[36][1])+(.0442*wk[36][2]));
    WkIkWk[5][0] = (.07*(u[4]*u[5]));
    WkIkWk[5][1] = -(.05*(u[3]*u[5]));
    WkIkWk[5][2] = -(.02*(u[3]*u[4]));
    WkIkWk[8][0] = (.41*(wk[8][1]*wk[8][2]));
    WkIkWk[8][1] = -(.1*(wk[8][0]*wk[8][2]));
    WkIkWk[8][2] = -(.31*(wk[8][0]*wk[8][1]));
    WkIkWk[11][0] = (.005*(wk[11][1]*wk[11][2]));
    WkIkWk[11][2] = -(.005*(wk[11][0]*wk[11][1]));
    WkIkWk[12][0] = (.007*(wk[12][1]*wk[12][2]));
    WkIkWk[12][1] = (.003*(wk[12][0]*wk[12][2]));
    WkIkWk[12][2] = -(.01*(wk[12][0]*wk[12][1]));
    WkIkWk[14][1] = -(.02*(wk[14][0]*wk[14][2]));
    WkIkWk[14][2] = (.02*(wk[14][0]*wk[14][1]));
    WkIkWk[16][0] = -(.0004*(wk[16][1]*wk[16][2]));
    WkIkWk[16][1] = -(.0038*(wk[16][0]*wk[16][2]));
    WkIkWk[16][2] = (.0042*(wk[16][0]*wk[16][1]));
    WkIkWk[18][0] = -(.0004*(wk[18][1]*wk[18][2]));
    WkIkWk[18][1] = -(.0011*(wk[18][0]*wk[18][2]));
    WkIkWk[18][2] = (.0015*(wk[18][0]*wk[18][1]));
    WkIkWk[20][1] = -(.02*(wk[20][0]*wk[20][2]));
    WkIkWk[20][2] = (.02*(wk[20][0]*wk[20][1]));
    WkIkWk[22][0] = -(.0004*(wk[22][1]*wk[22][2]));
    WkIkWk[22][1] = -(.0038*(wk[22][0]*wk[22][2]));
    WkIkWk[22][2] = (.0042*(wk[22][0]*wk[22][1]));
    WkIkWk[24][0] = -(.0004*(wk[24][1]*wk[24][2]));
    WkIkWk[24][1] = -(.0011*(wk[24][0]*wk[24][2]));
    WkIkWk[24][2] = (.0015*(wk[24][0]*wk[24][1]));
    WkIkWk[27][0] = (.125*(wk[27][1]*wk[27][2]));
    WkIkWk[27][1] = (.01*(wk[27][0]*wk[27][2]));
    WkIkWk[27][2] = -(.135*(wk[27][0]*wk[27][1]));
    WkIkWk[28][0] = (.048*(wk[28][1]*wk[28][2]));
    WkIkWk[28][1] = (.001*(wk[28][0]*wk[28][2]));
    WkIkWk[28][2] = -(.049*(wk[28][0]*wk[28][1]));
    WkIkWk[30][0] = -(.0052*(wk[30][1]*wk[30][2]));
    WkIkWk[30][1] = (.0057*(wk[30][0]*wk[30][2]));
    WkIkWk[30][2] = -(.0005*(wk[30][0]*wk[30][1]));
    WkIkWk[33][0] = (.125*(wk[33][1]*wk[33][2]));
    WkIkWk[33][1] = (.01*(wk[33][0]*wk[33][2]));
    WkIkWk[33][2] = -(.135*(wk[33][0]*wk[33][1]));
    WkIkWk[34][0] = (.048*(wk[34][1]*wk[34][2]));
    WkIkWk[34][1] = (.001*(wk[34][0]*wk[34][2]));
    WkIkWk[34][2] = -(.049*(wk[34][0]*wk[34][1]));
    WkIkWk[36][0] = -(.0052*(wk[36][1]*wk[36][2]));
    WkIkWk[36][1] = (.0057*(wk[36][0]*wk[36][2]));
    WkIkWk[36][2] = -(.0005*(wk[36][0]*wk[36][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (u[3]*u[3]);
    w0w0[1] = (wk[8][0]*wk[8][0]);
    w0w0[2] = (wk[11][0]*wk[11][0]);
    w0w0[3] = (wk[12][0]*wk[12][0]);
    w0w0[4] = (wk[14][0]*wk[14][0]);
    w0w0[5] = (wk[16][0]*wk[16][0]);
    w0w0[6] = (wk[18][0]*wk[18][0]);
    w0w0[7] = (wk[20][0]*wk[20][0]);
    w0w0[8] = (wk[22][0]*wk[22][0]);
    w0w0[9] = (wk[24][0]*wk[24][0]);
    w0w0[10] = (wk[27][0]*wk[27][0]);
    w0w0[11] = (wk[28][0]*wk[28][0]);
    w0w0[12] = (wk[30][0]*wk[30][0]);
    w0w0[13] = (wk[33][0]*wk[33][0]);
    w0w0[14] = (wk[34][0]*wk[34][0]);
    w0w0[15] = (wk[36][0]*wk[36][0]);
    w1w1[0] = (u[4]*u[4]);
    w1w1[1] = (wk[8][1]*wk[8][1]);
    w1w1[2] = (wk[11][1]*wk[11][1]);
    w1w1[3] = (wk[12][1]*wk[12][1]);
    w1w1[4] = (wk[14][1]*wk[14][1]);
    w1w1[5] = (wk[16][1]*wk[16][1]);
    w1w1[6] = (wk[18][1]*wk[18][1]);
    w1w1[7] = (wk[20][1]*wk[20][1]);
    w1w1[8] = (wk[22][1]*wk[22][1]);
    w1w1[9] = (wk[24][1]*wk[24][1]);
    w1w1[10] = (wk[27][1]*wk[27][1]);
    w1w1[11] = (wk[28][1]*wk[28][1]);
    w1w1[12] = (wk[30][1]*wk[30][1]);
    w1w1[13] = (wk[33][1]*wk[33][1]);
    w1w1[14] = (wk[34][1]*wk[34][1]);
    w1w1[15] = (wk[36][1]*wk[36][1]);
    w2w2[0] = (u[5]*u[5]);
    w2w2[1] = (wk[8][2]*wk[8][2]);
    w2w2[2] = (wk[11][2]*wk[11][2]);
    w2w2[3] = (wk[12][2]*wk[12][2]);
    w2w2[4] = (wk[14][2]*wk[14][2]);
    w2w2[5] = (wk[16][2]*wk[16][2]);
    w2w2[6] = (wk[18][2]*wk[18][2]);
    w2w2[7] = (wk[20][2]*wk[20][2]);
    w2w2[8] = (wk[22][2]*wk[22][2]);
    w2w2[9] = (wk[24][2]*wk[24][2]);
    w2w2[10] = (wk[27][2]*wk[27][2]);
    w2w2[11] = (wk[28][2]*wk[28][2]);
    w2w2[12] = (wk[30][2]*wk[30][2]);
    w2w2[13] = (wk[33][2]*wk[33][2]);
    w2w2[14] = (wk[34][2]*wk[34][2]);
    w2w2[15] = (wk[36][2]*wk[36][2]);
    w0w1[0] = (u[3]*u[4]);
    w0w1[1] = (wk[8][0]*wk[8][1]);
    w0w1[2] = (wk[11][0]*wk[11][1]);
    w0w1[3] = (wk[12][0]*wk[12][1]);
    w0w1[4] = (wk[14][0]*wk[14][1]);
    w0w1[5] = (wk[16][0]*wk[16][1]);
    w0w1[6] = (wk[18][0]*wk[18][1]);
    w0w1[7] = (wk[20][0]*wk[20][1]);
    w0w1[8] = (wk[22][0]*wk[22][1]);
    w0w1[9] = (wk[24][0]*wk[24][1]);
    w0w1[10] = (wk[27][0]*wk[27][1]);
    w0w1[11] = (wk[28][0]*wk[28][1]);
    w0w1[12] = (wk[30][0]*wk[30][1]);
    w0w1[13] = (wk[33][0]*wk[33][1]);
    w0w1[14] = (wk[34][0]*wk[34][1]);
    w0w1[15] = (wk[36][0]*wk[36][1]);
    w0w2[0] = (u[3]*u[5]);
    w0w2[1] = (wk[8][0]*wk[8][2]);
    w0w2[2] = (wk[11][0]*wk[11][2]);
    w0w2[3] = (wk[12][0]*wk[12][2]);
    w0w2[4] = (wk[14][0]*wk[14][2]);
    w0w2[5] = (wk[16][0]*wk[16][2]);
    w0w2[6] = (wk[18][0]*wk[18][2]);
    w0w2[7] = (wk[20][0]*wk[20][2]);
    w0w2[8] = (wk[22][0]*wk[22][2]);
    w0w2[9] = (wk[24][0]*wk[24][2]);
    w0w2[10] = (wk[27][0]*wk[27][2]);
    w0w2[11] = (wk[28][0]*wk[28][2]);
    w0w2[12] = (wk[30][0]*wk[30][2]);
    w0w2[13] = (wk[33][0]*wk[33][2]);
    w0w2[14] = (wk[34][0]*wk[34][2]);
    w0w2[15] = (wk[36][0]*wk[36][2]);
    w1w2[0] = (u[4]*u[5]);
    w1w2[1] = (wk[8][1]*wk[8][2]);
    w1w2[2] = (wk[11][1]*wk[11][2]);
    w1w2[3] = (wk[12][1]*wk[12][2]);
    w1w2[4] = (wk[14][1]*wk[14][2]);
    w1w2[5] = (wk[16][1]*wk[16][2]);
    w1w2[6] = (wk[18][1]*wk[18][2]);
    w1w2[7] = (wk[20][1]*wk[20][2]);
    w1w2[8] = (wk[22][1]*wk[22][2]);
    w1w2[9] = (wk[24][1]*wk[24][2]);
    w1w2[10] = (wk[27][1]*wk[27][2]);
    w1w2[11] = (wk[28][1]*wk[28][2]);
    w1w2[12] = (wk[30][1]*wk[30][2]);
    w1w2[13] = (wk[33][1]*wk[33][2]);
    w1w2[14] = (wk[34][1]*wk[34][2]);
    w1w2[15] = (wk[36][1]*wk[36][2]);
    w00w11[0] = -(w0w0[0]+w1w1[0]);
    w00w11[1] = -(w0w0[1]+w1w1[1]);
    w00w11[2] = -(w0w0[2]+w1w1[2]);
    w00w11[3] = -(w0w0[3]+w1w1[3]);
    w00w11[4] = -(w0w0[4]+w1w1[4]);
    w00w11[5] = -(w0w0[5]+w1w1[5]);
    w00w11[6] = -(w0w0[6]+w1w1[6]);
    w00w11[7] = -(w0w0[7]+w1w1[7]);
    w00w11[8] = -(w0w0[8]+w1w1[8]);
    w00w11[9] = -(w0w0[9]+w1w1[9]);
    w00w11[10] = -(w0w0[10]+w1w1[10]);
    w00w11[11] = -(w0w0[11]+w1w1[11]);
    w00w11[12] = -(w0w0[12]+w1w1[12]);
    w00w11[13] = -(w0w0[13]+w1w1[13]);
    w00w11[14] = -(w0w0[14]+w1w1[14]);
    w00w11[15] = -(w0w0[15]+w1w1[15]);
    w00w22[0] = -(w0w0[0]+w2w2[0]);
    w00w22[1] = -(w0w0[1]+w2w2[1]);
    w00w22[2] = -(w0w0[2]+w2w2[2]);
    w00w22[3] = -(w0w0[3]+w2w2[3]);
    w00w22[4] = -(w0w0[4]+w2w2[4]);
    w00w22[5] = -(w0w0[5]+w2w2[5]);
    w00w22[6] = -(w0w0[6]+w2w2[6]);
    w00w22[7] = -(w0w0[7]+w2w2[7]);
    w00w22[8] = -(w0w0[8]+w2w2[8]);
    w00w22[9] = -(w0w0[9]+w2w2[9]);
    w00w22[10] = -(w0w0[10]+w2w2[10]);
    w00w22[11] = -(w0w0[11]+w2w2[11]);
    w00w22[12] = -(w0w0[12]+w2w2[12]);
    w00w22[13] = -(w0w0[13]+w2w2[13]);
    w00w22[14] = -(w0w0[14]+w2w2[14]);
    w00w22[15] = -(w0w0[15]+w2w2[15]);
    w11w22[0] = -(w1w1[0]+w2w2[0]);
    w11w22[1] = -(w1w1[1]+w2w2[1]);
    w11w22[2] = -(w1w1[2]+w2w2[2]);
    w11w22[3] = -(w1w1[3]+w2w2[3]);
    w11w22[4] = -(w1w1[4]+w2w2[4]);
    w11w22[5] = -(w1w1[5]+w2w2[5]);
    w11w22[6] = -(w1w1[6]+w2w2[6]);
    w11w22[7] = -(w1w1[7]+w2w2[7]);
    w11w22[8] = -(w1w1[8]+w2w2[8]);
    w11w22[9] = -(w1w1[9]+w2w2[9]);
    w11w22[10] = -(w1w1[10]+w2w2[10]);
    w11w22[11] = -(w1w1[11]+w2w2[11]);
    w11w22[12] = -(w1w1[12]+w2w2[12]);
    w11w22[13] = -(w1w1[13]+w2w2[13]);
    w11w22[14] = -(w1w1[14]+w2w2[14]);
    w11w22[15] = -(w1w1[15]+w2w2[15]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[5][0] = (u[0]+(((.05*(Cik[3][0][1]*u[3]))+(Cik[3][0][0]*Wkrpk[5][0]))-(
      .1206*(Cik[3][0][2]*u[3]))));
    vnk[5][1] = (u[1]+(((.05*(Cik[3][1][1]*u[3]))+(Cik[3][1][0]*Wkrpk[5][0]))-(
      .1206*(Cik[3][1][2]*u[3]))));
    vnk[5][2] = (u[2]+(((.05*(Cik[3][2][1]*u[3]))+(Cik[3][2][0]*Wkrpk[5][0]))-(
      .1206*(Cik[3][2][2]*u[3]))));
    vnk[6][0] = (vnk[5][0]+((.1206*(Cik[3][0][2]*u[3]))+((Cik[3][0][0]*
      Wirk[6][0])-(.05*(Cik[3][0][1]*u[3])))));
    vnk[6][1] = (vnk[5][1]+((.1206*(Cik[3][1][2]*u[3]))+((Cik[3][1][0]*
      Wirk[6][0])-(.05*(Cik[3][1][1]*u[3])))));
    vnk[6][2] = (vnk[5][2]+((.1206*(Cik[3][2][2]*u[3]))+((Cik[3][2][0]*
      Wirk[6][0])-(.05*(Cik[3][2][1]*u[3])))));
    vnk[8][0] = (vnk[6][0]+((.14625*(cnk[8][0][2]*wk[8][0]))+((.0351*(
      cnk[7][0][1]*wk[8][0]))+(cnk[8][0][0]*Wkrpk[8][0]))));
    vnk[8][1] = (vnk[6][1]+((.14625*(cnk[8][1][2]*wk[8][0]))+((.0351*(
      cnk[7][1][1]*wk[8][0]))+(cnk[8][1][0]*Wkrpk[8][0]))));
    vnk[8][2] = (vnk[6][2]+((.14625*(cnk[8][2][2]*wk[8][0]))+((.0351*(
      cnk[7][2][1]*wk[8][0]))+(cnk[8][2][0]*Wkrpk[8][0]))));
    vnk[9][0] = (vnk[8][0]+((.24635*(cnk[8][0][2]*wk[8][0]))+((.0013*(
      cnk[7][0][1]*wk[8][0]))+(cnk[8][0][0]*Wirk[9][0]))));
    vnk[9][1] = (vnk[8][1]+((.24635*(cnk[8][1][2]*wk[8][0]))+((.0013*(
      cnk[7][1][1]*wk[8][0]))+(cnk[8][1][0]*Wirk[9][0]))));
    vnk[9][2] = (vnk[8][2]+((.24635*(cnk[8][2][2]*wk[8][0]))+((.0013*(
      cnk[7][2][1]*wk[8][0]))+(cnk[8][2][0]*Wirk[9][0]))));
    vnk[11][0] = (vnk[9][0]+((.0442*(cnk[11][0][2]*wk[11][0]))+((cnk[11][0][0]*
      Wkrpk[11][0])-(.0065*(cnk[10][0][1]*wk[11][0])))));
    vnk[11][1] = (vnk[9][1]+((.0442*(cnk[11][1][2]*wk[11][0]))+((cnk[11][1][0]*
      Wkrpk[11][0])-(.0065*(cnk[10][1][1]*wk[11][0])))));
    vnk[11][2] = (vnk[9][2]+((.0442*(cnk[11][2][2]*wk[11][0]))+((cnk[11][2][0]*
      Wkrpk[11][0])-(.0065*(cnk[10][2][1]*wk[11][0])))));
    vnk[12][0] = ((vnk[11][0]+((.0442*(cnk[11][0][2]*wk[11][0]))+((cnk[11][0][0]
      *Wirk[12][0])-(.0065*(cnk[10][0][1]*wk[11][0])))))+((.078*(cnk[12][0][2]*
      wk[12][0]))+((cnk[11][0][0]*Wkrpk[12][0])-(.0312*(cnk[12][0][1]*wk[12][0])
      ))));
    vnk[12][1] = ((vnk[11][1]+((.0442*(cnk[11][1][2]*wk[11][0]))+((cnk[11][1][0]
      *Wirk[12][0])-(.0065*(cnk[10][1][1]*wk[11][0])))))+((.078*(cnk[12][1][2]*
      wk[12][0]))+((cnk[11][1][0]*Wkrpk[12][0])-(.0312*(cnk[12][1][1]*wk[12][0])
      ))));
    vnk[12][2] = ((vnk[11][2]+((.0442*(cnk[11][2][2]*wk[11][0]))+((cnk[11][2][0]
      *Wirk[12][0])-(.0065*(cnk[10][2][1]*wk[11][0])))))+((.078*(cnk[12][2][2]*
      wk[12][0]))+((cnk[11][2][0]*Wkrpk[12][0])-(.0312*(cnk[12][2][1]*wk[12][0])
      ))));
    vnk[13][0] = (vnk[8][0]+((cnk[8][0][2]*Wirk[13][2])+((cnk[7][0][1]*
      Wirk[13][1])+(cnk[8][0][0]*Wirk[13][0]))));
    vnk[13][1] = (vnk[8][1]+((cnk[8][1][2]*Wirk[13][2])+((cnk[7][1][1]*
      Wirk[13][1])+(cnk[8][1][0]*Wirk[13][0]))));
    vnk[13][2] = (vnk[8][2]+((cnk[8][2][2]*Wirk[13][2])+((cnk[7][2][1]*
      Wirk[13][1])+(cnk[8][2][0]*Wirk[13][0]))));
    vnk[14][0] = (vnk[13][0]+(((.0013*(cnk[14][0][0]*wk[14][1]))+(cnk[13][0][1]*
      Wkrpk[14][1]))-(.1326*(cnk[14][0][2]*wk[14][1]))));
    vnk[14][1] = (vnk[13][1]+(((.0013*(cnk[14][1][0]*wk[14][1]))+(cnk[13][1][1]*
      Wkrpk[14][1]))-(.1326*(cnk[14][1][2]*wk[14][1]))));
    vnk[14][2] = (vnk[13][2]+(((.0013*(cnk[14][2][0]*wk[14][1]))+(cnk[13][2][1]*
      Wkrpk[14][1]))-(.1326*(cnk[14][2][2]*wk[14][1]))));
    vnk[15][0] = (vnk[14][0]+(((.0013*(cnk[14][0][0]*wk[14][1]))+(cnk[13][0][1]*
      Wirk[15][1]))-(.1326*(cnk[14][0][2]*wk[14][1]))));
    vnk[15][1] = (vnk[14][1]+(((.0013*(cnk[14][1][0]*wk[14][1]))+(cnk[13][1][1]*
      Wirk[15][1]))-(.1326*(cnk[14][1][2]*wk[14][1]))));
    vnk[15][2] = (vnk[14][2]+(((.0013*(cnk[14][2][0]*wk[14][1]))+(cnk[13][2][1]*
      Wirk[15][1]))-(.1326*(cnk[14][2][2]*wk[14][1]))));
    vnk[16][0] = (vnk[15][0]+((cnk[16][0][2]*Wkrpk[16][2])+((.1378*(
      cnk[16][0][1]*wk[16][2]))-(.0039*(cnk[15][0][0]*wk[16][2])))));
    vnk[16][1] = (vnk[15][1]+((cnk[16][1][2]*Wkrpk[16][2])+((.1378*(
      cnk[16][1][1]*wk[16][2]))-(.0039*(cnk[15][1][0]*wk[16][2])))));
    vnk[16][2] = (vnk[15][2]+((cnk[16][2][2]*Wkrpk[16][2])+((.1378*(
      cnk[16][2][1]*wk[16][2]))-(.0039*(cnk[15][2][0]*wk[16][2])))));
    vnk[17][0] = (vnk[16][0]+((cnk[16][0][2]*Wirk[17][2])+((.1378*(cnk[16][0][1]
      *wk[16][2]))-(.0039*(cnk[15][0][0]*wk[16][2])))));
    vnk[17][1] = (vnk[16][1]+((cnk[16][1][2]*Wirk[17][2])+((.1378*(cnk[16][1][1]
      *wk[16][2]))-(.0039*(cnk[15][1][0]*wk[16][2])))));
    vnk[17][2] = (vnk[16][2]+((cnk[16][2][2]*Wirk[17][2])+((.1378*(cnk[16][2][1]
      *wk[16][2]))-(.0039*(cnk[15][2][0]*wk[16][2])))));
    vnk[18][0] = (vnk[17][0]+(.065*((cnk[17][0][1]*wk[18][2])-(cnk[18][0][2]*
      wk[18][1]))));
    vnk[18][1] = (vnk[17][1]+(.065*((cnk[17][1][1]*wk[18][2])-(cnk[18][1][2]*
      wk[18][1]))));
    vnk[18][2] = (vnk[17][2]+(.065*((cnk[17][2][1]*wk[18][2])-(cnk[18][2][2]*
      wk[18][1]))));
    vnk[19][0] = (vnk[8][0]+((cnk[8][0][2]*Wirk[19][2])+((cnk[7][0][1]*
      Wirk[19][1])+(cnk[8][0][0]*Wirk[19][0]))));
    vnk[19][1] = (vnk[8][1]+((cnk[8][1][2]*Wirk[19][2])+((cnk[7][1][1]*
      Wirk[19][1])+(cnk[8][1][0]*Wirk[19][0]))));
    vnk[19][2] = (vnk[8][2]+((cnk[8][2][2]*Wirk[19][2])+((cnk[7][2][1]*
      Wirk[19][1])+(cnk[8][2][0]*Wirk[19][0]))));
    vnk[20][0] = (vnk[19][0]+((.1326*(cnk[20][0][2]*wk[20][1]))+((.0013*(
      cnk[20][0][0]*wk[20][1]))+(cnk[19][0][1]*Wkrpk[20][1]))));
    vnk[20][1] = (vnk[19][1]+((.1326*(cnk[20][1][2]*wk[20][1]))+((.0013*(
      cnk[20][1][0]*wk[20][1]))+(cnk[19][1][1]*Wkrpk[20][1]))));
    vnk[20][2] = (vnk[19][2]+((.1326*(cnk[20][2][2]*wk[20][1]))+((.0013*(
      cnk[20][2][0]*wk[20][1]))+(cnk[19][2][1]*Wkrpk[20][1]))));
    vnk[21][0] = (vnk[20][0]+((.1326*(cnk[20][0][2]*wk[20][1]))+((.0013*(
      cnk[20][0][0]*wk[20][1]))+(cnk[19][0][1]*Wirk[21][1]))));
    vnk[21][1] = (vnk[20][1]+((.1326*(cnk[20][1][2]*wk[20][1]))+((.0013*(
      cnk[20][1][0]*wk[20][1]))+(cnk[19][1][1]*Wirk[21][1]))));
    vnk[21][2] = (vnk[20][2]+((.1326*(cnk[20][2][2]*wk[20][1]))+((.0013*(
      cnk[20][2][0]*wk[20][1]))+(cnk[19][2][1]*Wirk[21][1]))));
    vnk[22][0] = (vnk[21][0]+((cnk[22][0][2]*Wkrpk[22][2])-((.0039*(
      cnk[21][0][0]*wk[22][2]))+(.1378*(cnk[22][0][1]*wk[22][2])))));
    vnk[22][1] = (vnk[21][1]+((cnk[22][1][2]*Wkrpk[22][2])-((.0039*(
      cnk[21][1][0]*wk[22][2]))+(.1378*(cnk[22][1][1]*wk[22][2])))));
    vnk[22][2] = (vnk[21][2]+((cnk[22][2][2]*Wkrpk[22][2])-((.0039*(
      cnk[21][2][0]*wk[22][2]))+(.1378*(cnk[22][2][1]*wk[22][2])))));
    vnk[23][0] = (vnk[22][0]+((cnk[22][0][2]*Wirk[23][2])-((.0039*(cnk[21][0][0]
      *wk[22][2]))+(.1378*(cnk[22][0][1]*wk[22][2])))));
    vnk[23][1] = (vnk[22][1]+((cnk[22][1][2]*Wirk[23][2])-((.0039*(cnk[21][1][0]
      *wk[22][2]))+(.1378*(cnk[22][1][1]*wk[22][2])))));
    vnk[23][2] = (vnk[22][2]+((cnk[22][2][2]*Wirk[23][2])-((.0039*(cnk[21][2][0]
      *wk[22][2]))+(.1378*(cnk[22][2][1]*wk[22][2])))));
    vnk[24][0] = (vnk[23][0]+(.065*((cnk[24][0][2]*wk[24][1])-(cnk[23][0][1]*
      wk[24][2]))));
    vnk[24][1] = (vnk[23][1]+(.065*((cnk[24][1][2]*wk[24][1])-(cnk[23][1][1]*
      wk[24][2]))));
    vnk[24][2] = (vnk[23][2]+(.065*((cnk[24][2][2]*wk[24][1])-(cnk[23][2][1]*
      wk[24][2]))));
    vnk[25][0] = (vnk[5][0]+((Cik[3][0][2]*Wirk[25][2])+((Cik[3][0][0]*
      Wirk[25][0])+(Cik[3][0][1]*Wirk[25][1]))));
    vnk[25][1] = (vnk[5][1]+((Cik[3][1][2]*Wirk[25][2])+((Cik[3][1][0]*
      Wirk[25][0])+(Cik[3][1][1]*Wirk[25][1]))));
    vnk[25][2] = (vnk[5][2]+((Cik[3][2][2]*Wirk[25][2])+((Cik[3][2][0]*
      Wirk[25][0])+(Cik[3][2][1]*Wirk[25][1]))));
    vnk[27][0] = (vnk[25][0]+((cnk[27][0][2]*Wkrpk[27][2])+((cnk[26][0][1]*
      Wkrpk[27][1])+(cnk[27][0][0]*Wkrpk[27][0]))));
    vnk[27][1] = (vnk[25][1]+((cnk[27][1][2]*Wkrpk[27][2])+((cnk[26][1][1]*
      Wkrpk[27][1])+(cnk[27][1][0]*Wkrpk[27][0]))));
    vnk[27][2] = (vnk[25][2]+((cnk[27][2][2]*Wkrpk[27][2])+((cnk[26][2][1]*
      Wkrpk[27][1])+(cnk[27][2][0]*Wkrpk[27][0]))));
    vnk[28][0] = ((vnk[27][0]+((cnk[27][0][2]*Wirk[28][2])+((cnk[26][0][1]*
      Wirk[28][1])+(cnk[27][0][0]*Wirk[28][0]))))+((cnk[28][0][2]*Wkrpk[28][2])+
      ((cnk[27][0][0]*Wkrpk[28][0])+(cnk[28][0][1]*Wkrpk[28][1]))));
    vnk[28][1] = ((vnk[27][1]+((cnk[27][1][2]*Wirk[28][2])+((cnk[26][1][1]*
      Wirk[28][1])+(cnk[27][1][0]*Wirk[28][0]))))+((cnk[28][1][2]*Wkrpk[28][2])+
      ((cnk[27][1][0]*Wkrpk[28][0])+(cnk[28][1][1]*Wkrpk[28][1]))));
    vnk[28][2] = ((vnk[27][2]+((cnk[27][2][2]*Wirk[28][2])+((cnk[26][2][1]*
      Wirk[28][1])+(cnk[27][2][0]*Wirk[28][0]))))+((cnk[28][2][2]*Wkrpk[28][2])+
      ((cnk[27][2][0]*Wkrpk[28][0])+(cnk[28][2][1]*Wkrpk[28][1]))));
    vnk[29][0] = (vnk[28][0]+((cnk[28][0][2]*Wirk[29][2])+((cnk[27][0][0]*
      Wirk[29][0])+(cnk[28][0][1]*Wirk[29][1]))));
    vnk[29][1] = (vnk[28][1]+((cnk[28][1][2]*Wirk[29][2])+((cnk[27][1][0]*
      Wirk[29][0])+(cnk[28][1][1]*Wirk[29][1]))));
    vnk[29][2] = (vnk[28][2]+((cnk[28][2][2]*Wirk[29][2])+((cnk[27][2][0]*
      Wirk[29][0])+(cnk[28][2][1]*Wirk[29][1]))));
    vnk[30][0] = (vnk[29][0]+(((cnk[30][0][0]*Wkrpk[30][0])-(.039*(cnk[30][0][1]
      *wk[30][0])))-(.0442*(cnk[29][0][2]*wk[30][0]))));
    vnk[30][1] = (vnk[29][1]+(((cnk[30][1][0]*Wkrpk[30][0])-(.039*(cnk[30][1][1]
      *wk[30][0])))-(.0442*(cnk[29][1][2]*wk[30][0]))));
    vnk[30][2] = (vnk[29][2]+(((cnk[30][2][0]*Wkrpk[30][0])-(.039*(cnk[30][2][1]
      *wk[30][0])))-(.0442*(cnk[29][2][2]*wk[30][0]))));
    vnk[31][0] = (vnk[5][0]+((Cik[3][0][2]*Wirk[31][2])+((Cik[3][0][0]*
      Wirk[31][0])+(Cik[3][0][1]*Wirk[31][1]))));
    vnk[31][1] = (vnk[5][1]+((Cik[3][1][2]*Wirk[31][2])+((Cik[3][1][0]*
      Wirk[31][0])+(Cik[3][1][1]*Wirk[31][1]))));
    vnk[31][2] = (vnk[5][2]+((Cik[3][2][2]*Wirk[31][2])+((Cik[3][2][0]*
      Wirk[31][0])+(Cik[3][2][1]*Wirk[31][1]))));
    vnk[33][0] = (vnk[31][0]+((cnk[33][0][2]*Wkrpk[33][2])+((cnk[32][0][1]*
      Wkrpk[33][1])+(cnk[33][0][0]*Wkrpk[33][0]))));
    vnk[33][1] = (vnk[31][1]+((cnk[33][1][2]*Wkrpk[33][2])+((cnk[32][1][1]*
      Wkrpk[33][1])+(cnk[33][1][0]*Wkrpk[33][0]))));
    vnk[33][2] = (vnk[31][2]+((cnk[33][2][2]*Wkrpk[33][2])+((cnk[32][2][1]*
      Wkrpk[33][1])+(cnk[33][2][0]*Wkrpk[33][0]))));
    vnk[34][0] = ((vnk[33][0]+((cnk[33][0][2]*Wirk[34][2])+((cnk[32][0][1]*
      Wirk[34][1])+(cnk[33][0][0]*Wirk[34][0]))))+((cnk[34][0][2]*Wkrpk[34][2])+
      ((cnk[33][0][0]*Wkrpk[34][0])+(cnk[34][0][1]*Wkrpk[34][1]))));
    vnk[34][1] = ((vnk[33][1]+((cnk[33][1][2]*Wirk[34][2])+((cnk[32][1][1]*
      Wirk[34][1])+(cnk[33][1][0]*Wirk[34][0]))))+((cnk[34][1][2]*Wkrpk[34][2])+
      ((cnk[33][1][0]*Wkrpk[34][0])+(cnk[34][1][1]*Wkrpk[34][1]))));
    vnk[34][2] = ((vnk[33][2]+((cnk[33][2][2]*Wirk[34][2])+((cnk[32][2][1]*
      Wirk[34][1])+(cnk[33][2][0]*Wirk[34][0]))))+((cnk[34][2][2]*Wkrpk[34][2])+
      ((cnk[33][2][0]*Wkrpk[34][0])+(cnk[34][2][1]*Wkrpk[34][1]))));
    vnk[35][0] = (vnk[34][0]+((cnk[34][0][2]*Wirk[35][2])+((cnk[33][0][0]*
      Wirk[35][0])+(cnk[34][0][1]*Wirk[35][1]))));
    vnk[35][1] = (vnk[34][1]+((cnk[34][1][2]*Wirk[35][2])+((cnk[33][1][0]*
      Wirk[35][0])+(cnk[34][1][1]*Wirk[35][1]))));
    vnk[35][2] = (vnk[34][2]+((cnk[34][2][2]*Wirk[35][2])+((cnk[33][2][0]*
      Wirk[35][0])+(cnk[34][2][1]*Wirk[35][1]))));
    vnk[36][0] = (vnk[35][0]+(((cnk[36][0][0]*Wkrpk[36][0])-(.039*(cnk[36][0][1]
      *wk[36][0])))-(.0442*(cnk[35][0][2]*wk[36][0]))));
    vnk[36][1] = (vnk[35][1]+(((cnk[36][1][0]*Wkrpk[36][0])-(.039*(cnk[36][1][1]
      *wk[36][0])))-(.0442*(cnk[35][1][2]*wk[36][0]))));
    vnk[36][2] = (vnk[35][2]+(((cnk[36][2][0]*Wkrpk[36][0])-(.039*(cnk[36][2][1]
      *wk[36][0])))-(.0442*(cnk[35][2][2]*wk[36][0]))));
    vnb[0][0] = vnk[5][0];
    vnb[0][1] = vnk[5][1];
    vnb[0][2] = vnk[5][2];
    vnb[1][0] = vnk[8][0];
    vnb[1][1] = vnk[8][1];
    vnb[1][2] = vnk[8][2];
    vnb[2][0] = vnk[11][0];
    vnb[2][1] = vnk[11][1];
    vnb[2][2] = vnk[11][2];
    vnb[3][0] = vnk[12][0];
    vnb[3][1] = vnk[12][1];
    vnb[3][2] = vnk[12][2];
    vnb[4][0] = vnk[14][0];
    vnb[4][1] = vnk[14][1];
    vnb[4][2] = vnk[14][2];
    vnb[5][0] = vnk[16][0];
    vnb[5][1] = vnk[16][1];
    vnb[5][2] = vnk[16][2];
    vnb[6][0] = vnk[18][0];
    vnb[6][1] = vnk[18][1];
    vnb[6][2] = vnk[18][2];
    vnb[7][0] = vnk[20][0];
    vnb[7][1] = vnk[20][1];
    vnb[7][2] = vnk[20][2];
    vnb[8][0] = vnk[22][0];
    vnb[8][1] = vnk[22][1];
    vnb[8][2] = vnk[22][2];
    vnb[9][0] = vnk[24][0];
    vnb[9][1] = vnk[24][1];
    vnb[9][2] = vnk[24][2];
    vnb[10][0] = vnk[27][0];
    vnb[10][1] = vnk[27][1];
    vnb[10][2] = vnk[27][2];
    vnb[11][0] = vnk[28][0];
    vnb[11][1] = vnk[28][1];
    vnb[11][2] = vnk[28][2];
    vnb[12][0] = vnk[30][0];
    vnb[12][1] = vnk[30][1];
    vnb[12][2] = vnk[30][2];
    vnb[13][0] = vnk[33][0];
    vnb[13][1] = vnk[33][1];
    vnb[13][2] = vnk[33][2];
    vnb[14][0] = vnk[34][0];
    vnb[14][1] = vnk[34][1];
    vnb[14][2] = vnk[34][2];
    vnb[15][0] = vnk[36][0];
    vnb[15][1] = vnk[36][1];
    vnb[15][2] = vnk[36][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = (.5*((q[37]*u[3])+((q[4]*u[5])-(q[5]*u[4]))));
    qdot[4] = (.5*((q[5]*u[3])+((q[37]*u[4])-(q[3]*u[5]))));
    qdot[5] = (.5*(((q[3]*u[4])+(q[37]*u[5]))-(q[4]*u[3])));
    qdot[37] = -(.5*((q[3]*u[3])+((q[4]*u[4])+(q[5]*u[5]))));
    if (stabvel  !=  0.) {
        ee = ((q[37]*q[37])+((q[5]*q[5])+((q[3]*q[3])+(q[4]*q[4]))));
        stab = ((stabvel*(1.-ee))/ee);
        qdot[3] = (qdot[3]+(q[3]*stab));
        qdot[4] = (qdot[4]+(q[4]*stab));
        qdot[5] = (qdot[5]+(q[5]*stab));
        qdot[37] = (qdot[37]+(q[37]*stab));
    }
    qdot[6] = u[6];
    qdot[7] = u[7];
    qdot[8] = u[8];
    qdot[9] = u[9];
    qdot[10] = u[10];
    qdot[11] = u[11];
    qdot[12] = u[12];
    qdot[13] = u[13];
    qdot[14] = u[14];
    qdot[15] = u[15];
    qdot[16] = u[16];
    qdot[17] = u[17];
    qdot[18] = u[18];
    qdot[19] = u[19];
    qdot[20] = u[20];
    qdot[21] = u[21];
    qdot[22] = u[22];
    qdot[23] = u[23];
    qdot[24] = u[24];
    qdot[25] = u[25];
    qdot[26] = u[26];
    qdot[27] = u[27];
    qdot[28] = u[28];
    qdot[29] = u[29];
    qdot[30] = u[30];
    qdot[31] = u[31];
    qdot[32] = u[32];
    qdot[33] = u[33];
    qdot[34] = u[34];
    qdot[35] = u[35];
    qdot[36] = u[36];
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 37; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 3.00 seconds CPU time,
 122880 additional bytes of memory.
 Equations contain 1098 adds/subtracts/negates
                   1653 multiplies
                      1 divides
                   1337 assignments
*/
}

void skel18qdot(double *oqdot)
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(63,23);
        return;
    }
    for (i = 0; i <= 37; i++) {
        oqdot[i] = qdot[i];
    }
}

void skel18u2qdot(double *uin, double *oqdot)
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(64,23);
        return;
    }
    for (i = 0; i <= 36; i++) {
        oqdot[i] = uin[i];
    }
    oqdot[3] = (.5*((q[37]*uin[3])+((q[4]*uin[5])-(q[5]*uin[4]))));
    oqdot[4] = (.5*((q[5]*uin[3])+((q[37]*uin[4])-(q[3]*uin[5]))));
    oqdot[5] = (.5*(((q[3]*uin[4])+(q[37]*uin[5]))-(q[4]*uin[3])));
    oqdot[37] = -(.5*((q[3]*uin[3])+((q[4]*uin[4])+(q[5]*uin[5]))));
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                     16 multiplies
                      0 divides
                     41 assignments
*/
}

void skel18psstate(double *lqin)
{

    if (roustate != 2) {
        skel18seterr(9,23);
        return;
    }
}

void skel18dovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[3][3][0] = 1.;
        Wpk[3][4][0] = 1.;
        Wpk[3][5][0] = 1.;
        Wpk[3][6][0] = 1.;
        Wpk[3][7][0] = c7;
        Wpk[3][7][1] = -s7;
        Wpk[3][8][0] = (c7*c8);
        Wpk[3][8][1] = -s7;
        Wpk[3][8][2] = (s8*c7);
        Wpk[3][9][0] = Wpk[3][8][0];
        Wpk[3][9][1] = ((Wpk[3][8][2]*s9)-(s7*c9));
        Wpk[3][9][2] = ((Wpk[3][8][2]*c9)+(s7*s9));
        Wpk[3][10][0] = ((Wpk[3][8][0]*c10)+(Wpk[3][9][1]*s10));
        Wpk[3][10][1] = ((Wpk[3][9][1]*c10)-(Wpk[3][8][0]*s10));
        Wpk[3][10][2] = Wpk[3][9][2];
        Wpk[3][11][0] = ((Wpk[3][10][0]*c11)-(Wpk[3][9][2]*s11));
        Wpk[3][11][1] = Wpk[3][10][1];
        Wpk[3][11][2] = ((Wpk[3][9][2]*c11)+(Wpk[3][10][0]*s11));
        Wpk[3][12][0] = Wpk[3][11][0];
        Wpk[3][12][1] = ((Wpk[3][10][1]*c12)+(Wpk[3][11][2]*s12));
        Wpk[3][12][2] = ((Wpk[3][11][2]*c12)-(Wpk[3][10][1]*s12));
        Wpk[3][13][0] = ((Wpk[3][8][0]*c13)-(s7*s13));
        Wpk[3][13][1] = -((Wpk[3][8][0]*s13)+(s7*c13));
        Wpk[3][13][2] = Wpk[3][8][2];
        Wpk[3][14][0] = ((Wpk[3][13][0]*c14)-(Wpk[3][8][2]*s14));
        Wpk[3][14][1] = Wpk[3][13][1];
        Wpk[3][14][2] = ((Wpk[3][8][2]*c14)+(Wpk[3][13][0]*s14));
        Wpk[3][15][0] = ((Wpk[3][14][0]*c15)-(Wpk[3][14][2]*s15));
        Wpk[3][15][1] = Wpk[3][13][1];
        Wpk[3][15][2] = ((Wpk[3][14][0]*s15)+(Wpk[3][14][2]*c15));
        Wpk[3][16][0] = Wpk[3][15][0];
        Wpk[3][16][1] = ((Wpk[3][13][1]*c16)+(Wpk[3][15][2]*s16));
        Wpk[3][16][2] = ((Wpk[3][15][2]*c16)-(Wpk[3][13][1]*s16));
        Wpk[3][17][0] = ((Wpk[3][15][0]*c17)+(Wpk[3][16][1]*s17));
        Wpk[3][17][1] = ((Wpk[3][16][1]*c17)-(Wpk[3][15][0]*s17));
        Wpk[3][17][2] = Wpk[3][16][2];
        Wpk[3][18][0] = ((Wpk[3][17][0]*c18)-(Wpk[3][16][2]*s18));
        Wpk[3][18][1] = Wpk[3][17][1];
        Wpk[3][18][2] = ((Wpk[3][16][2]*c18)+(Wpk[3][17][0]*s18));
        Wpk[3][19][0] = ((Wpk[3][8][0]*c19)-(s7*s19));
        Wpk[3][19][1] = -((Wpk[3][8][0]*s19)+(s7*c19));
        Wpk[3][19][2] = Wpk[3][8][2];
        Wpk[3][20][0] = ((Wpk[3][19][0]*c20)-(Wpk[3][8][2]*s20));
        Wpk[3][20][1] = Wpk[3][19][1];
        Wpk[3][20][2] = ((Wpk[3][8][2]*c20)+(Wpk[3][19][0]*s20));
        Wpk[3][21][0] = ((Wpk[3][20][0]*c21)-(Wpk[3][20][2]*s21));
        Wpk[3][21][1] = Wpk[3][19][1];
        Wpk[3][21][2] = ((Wpk[3][20][0]*s21)+(Wpk[3][20][2]*c21));
        Wpk[3][22][0] = Wpk[3][21][0];
        Wpk[3][22][1] = ((Wpk[3][19][1]*c22)+(Wpk[3][21][2]*s22));
        Wpk[3][22][2] = ((Wpk[3][21][2]*c22)-(Wpk[3][19][1]*s22));
        Wpk[3][23][0] = ((Wpk[3][21][0]*c23)+(Wpk[3][22][1]*s23));
        Wpk[3][23][1] = ((Wpk[3][22][1]*c23)-(Wpk[3][21][0]*s23));
        Wpk[3][23][2] = Wpk[3][22][2];
        Wpk[3][24][0] = ((Wpk[3][23][0]*c24)-(Wpk[3][22][2]*s24));
        Wpk[3][24][1] = Wpk[3][23][1];
        Wpk[3][24][2] = ((Wpk[3][22][2]*c24)+(Wpk[3][23][0]*s24));
        Wpk[3][25][0] = 1.;
        Wpk[3][26][0] = c26;
        Wpk[3][26][1] = -s26;
        Wpk[3][27][0] = (c26*c27);
        Wpk[3][27][1] = -s26;
        Wpk[3][27][2] = (s27*c26);
        Wpk[3][28][0] = Wpk[3][27][0];
        Wpk[3][28][1] = ((Wpk[3][27][2]*s28)-(s26*c28));
        Wpk[3][28][2] = ((Wpk[3][27][2]*c28)+(s26*s28));
        Wpk[3][29][0] = Wpk[3][27][0];
        Wpk[3][29][1] = ((Wpk[3][28][1]*c29)+(Wpk[3][28][2]*s29));
        Wpk[3][29][2] = ((Wpk[3][28][2]*c29)-(Wpk[3][28][1]*s29));
        Wpk[3][30][0] = ((Wpk[3][27][0]*c30)+(Wpk[3][29][1]*s30));
        Wpk[3][30][1] = ((Wpk[3][29][1]*c30)-(Wpk[3][27][0]*s30));
        Wpk[3][30][2] = Wpk[3][29][2];
        Wpk[3][31][0] = 1.;
        Wpk[3][32][0] = c32;
        Wpk[3][32][1] = -s32;
        Wpk[3][33][0] = (c32*c33);
        Wpk[3][33][1] = -s32;
        Wpk[3][33][2] = (s33*c32);
        Wpk[3][34][0] = Wpk[3][33][0];
        Wpk[3][34][1] = ((Wpk[3][33][2]*s34)-(s32*c34));
        Wpk[3][34][2] = ((Wpk[3][33][2]*c34)+(s32*s34));
        Wpk[3][35][0] = Wpk[3][33][0];
        Wpk[3][35][1] = ((Wpk[3][34][1]*c35)+(Wpk[3][34][2]*s35));
        Wpk[3][35][2] = ((Wpk[3][34][2]*c35)-(Wpk[3][34][1]*s35));
        Wpk[3][36][0] = ((Wpk[3][33][0]*c36)+(Wpk[3][35][1]*s36));
        Wpk[3][36][1] = ((Wpk[3][35][1]*c36)-(Wpk[3][33][0]*s36));
        Wpk[3][36][2] = Wpk[3][35][2];
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = 1.;
        Wpk[4][6][1] = c6;
        Wpk[4][6][2] = -s6;
        Wpk[4][7][0] = (s7*c6);
        Wpk[4][7][1] = (c6*c7);
        Wpk[4][7][2] = -s6;
        Wpk[4][8][0] = ((Wpk[4][7][0]*c8)+(s6*s8));
        Wpk[4][8][1] = Wpk[4][7][1];
        Wpk[4][8][2] = ((Wpk[4][7][0]*s8)-(s6*c8));
        Wpk[4][9][0] = Wpk[4][8][0];
        Wpk[4][9][1] = ((Wpk[4][7][1]*c9)+(Wpk[4][8][2]*s9));
        Wpk[4][9][2] = ((Wpk[4][8][2]*c9)-(Wpk[4][7][1]*s9));
        Wpk[4][10][0] = ((Wpk[4][8][0]*c10)+(Wpk[4][9][1]*s10));
        Wpk[4][10][1] = ((Wpk[4][9][1]*c10)-(Wpk[4][8][0]*s10));
        Wpk[4][10][2] = Wpk[4][9][2];
        Wpk[4][11][0] = ((Wpk[4][10][0]*c11)-(Wpk[4][9][2]*s11));
        Wpk[4][11][1] = Wpk[4][10][1];
        Wpk[4][11][2] = ((Wpk[4][9][2]*c11)+(Wpk[4][10][0]*s11));
        Wpk[4][12][0] = Wpk[4][11][0];
        Wpk[4][12][1] = ((Wpk[4][10][1]*c12)+(Wpk[4][11][2]*s12));
        Wpk[4][12][2] = ((Wpk[4][11][2]*c12)-(Wpk[4][10][1]*s12));
        Wpk[4][13][0] = ((Wpk[4][7][1]*s13)+(Wpk[4][8][0]*c13));
        Wpk[4][13][1] = ((Wpk[4][7][1]*c13)-(Wpk[4][8][0]*s13));
        Wpk[4][13][2] = Wpk[4][8][2];
        Wpk[4][14][0] = ((Wpk[4][13][0]*c14)-(Wpk[4][8][2]*s14));
        Wpk[4][14][1] = Wpk[4][13][1];
        Wpk[4][14][2] = ((Wpk[4][8][2]*c14)+(Wpk[4][13][0]*s14));
        Wpk[4][15][0] = ((Wpk[4][14][0]*c15)-(Wpk[4][14][2]*s15));
        Wpk[4][15][1] = Wpk[4][13][1];
        Wpk[4][15][2] = ((Wpk[4][14][0]*s15)+(Wpk[4][14][2]*c15));
        Wpk[4][16][0] = Wpk[4][15][0];
        Wpk[4][16][1] = ((Wpk[4][13][1]*c16)+(Wpk[4][15][2]*s16));
        Wpk[4][16][2] = ((Wpk[4][15][2]*c16)-(Wpk[4][13][1]*s16));
        Wpk[4][17][0] = ((Wpk[4][15][0]*c17)+(Wpk[4][16][1]*s17));
        Wpk[4][17][1] = ((Wpk[4][16][1]*c17)-(Wpk[4][15][0]*s17));
        Wpk[4][17][2] = Wpk[4][16][2];
        Wpk[4][18][0] = ((Wpk[4][17][0]*c18)-(Wpk[4][16][2]*s18));
        Wpk[4][18][1] = Wpk[4][17][1];
        Wpk[4][18][2] = ((Wpk[4][16][2]*c18)+(Wpk[4][17][0]*s18));
        Wpk[4][19][0] = ((Wpk[4][7][1]*s19)+(Wpk[4][8][0]*c19));
        Wpk[4][19][1] = ((Wpk[4][7][1]*c19)-(Wpk[4][8][0]*s19));
        Wpk[4][19][2] = Wpk[4][8][2];
        Wpk[4][20][0] = ((Wpk[4][19][0]*c20)-(Wpk[4][8][2]*s20));
        Wpk[4][20][1] = Wpk[4][19][1];
        Wpk[4][20][2] = ((Wpk[4][8][2]*c20)+(Wpk[4][19][0]*s20));
        Wpk[4][21][0] = ((Wpk[4][20][0]*c21)-(Wpk[4][20][2]*s21));
        Wpk[4][21][1] = Wpk[4][19][1];
        Wpk[4][21][2] = ((Wpk[4][20][0]*s21)+(Wpk[4][20][2]*c21));
        Wpk[4][22][0] = Wpk[4][21][0];
        Wpk[4][22][1] = ((Wpk[4][19][1]*c22)+(Wpk[4][21][2]*s22));
        Wpk[4][22][2] = ((Wpk[4][21][2]*c22)-(Wpk[4][19][1]*s22));
        Wpk[4][23][0] = ((Wpk[4][21][0]*c23)+(Wpk[4][22][1]*s23));
        Wpk[4][23][1] = ((Wpk[4][22][1]*c23)-(Wpk[4][21][0]*s23));
        Wpk[4][23][2] = Wpk[4][22][2];
        Wpk[4][24][0] = ((Wpk[4][23][0]*c24)-(Wpk[4][22][2]*s24));
        Wpk[4][24][1] = Wpk[4][23][1];
        Wpk[4][24][2] = ((Wpk[4][22][2]*c24)+(Wpk[4][23][0]*s24));
        Wpk[4][25][1] = c25;
        Wpk[4][25][2] = -s25;
        Wpk[4][26][0] = (s26*c25);
        Wpk[4][26][1] = (c25*c26);
        Wpk[4][26][2] = -s25;
        Wpk[4][27][0] = ((Wpk[4][26][0]*c27)+(s25*s27));
        Wpk[4][27][1] = Wpk[4][26][1];
        Wpk[4][27][2] = ((Wpk[4][26][0]*s27)-(s25*c27));
        Wpk[4][28][0] = Wpk[4][27][0];
        Wpk[4][28][1] = ((Wpk[4][26][1]*c28)+(Wpk[4][27][2]*s28));
        Wpk[4][28][2] = ((Wpk[4][27][2]*c28)-(Wpk[4][26][1]*s28));
        Wpk[4][29][0] = Wpk[4][27][0];
        Wpk[4][29][1] = ((Wpk[4][28][1]*c29)+(Wpk[4][28][2]*s29));
        Wpk[4][29][2] = ((Wpk[4][28][2]*c29)-(Wpk[4][28][1]*s29));
        Wpk[4][30][0] = ((Wpk[4][27][0]*c30)+(Wpk[4][29][1]*s30));
        Wpk[4][30][1] = ((Wpk[4][29][1]*c30)-(Wpk[4][27][0]*s30));
        Wpk[4][30][2] = Wpk[4][29][2];
        Wpk[4][31][1] = c31;
        Wpk[4][31][2] = -s31;
        Wpk[4][32][0] = (s32*c31);
        Wpk[4][32][1] = (c31*c32);
        Wpk[4][32][2] = -s31;
        Wpk[4][33][0] = ((Wpk[4][32][0]*c33)+(s31*s33));
        Wpk[4][33][1] = Wpk[4][32][1];
        Wpk[4][33][2] = ((Wpk[4][32][0]*s33)-(s31*c33));
        Wpk[4][34][0] = Wpk[4][33][0];
        Wpk[4][34][1] = ((Wpk[4][32][1]*c34)+(Wpk[4][33][2]*s34));
        Wpk[4][34][2] = ((Wpk[4][33][2]*c34)-(Wpk[4][32][1]*s34));
        Wpk[4][35][0] = Wpk[4][33][0];
        Wpk[4][35][1] = ((Wpk[4][34][1]*c35)+(Wpk[4][34][2]*s35));
        Wpk[4][35][2] = ((Wpk[4][34][2]*c35)-(Wpk[4][34][1]*s35));
        Wpk[4][36][0] = ((Wpk[4][33][0]*c36)+(Wpk[4][35][1]*s36));
        Wpk[4][36][1] = ((Wpk[4][35][1]*c36)-(Wpk[4][33][0]*s36));
        Wpk[4][36][2] = Wpk[4][35][2];
        Wpk[5][5][2] = 1.;
        Wpk[5][6][1] = s6;
        Wpk[5][6][2] = c6;
        Wpk[5][7][0] = (s6*s7);
        Wpk[5][7][1] = (s6*c7);
        Wpk[5][7][2] = c6;
        Wpk[5][8][0] = ((Wpk[5][7][0]*c8)-(s8*c6));
        Wpk[5][8][1] = Wpk[5][7][1];
        Wpk[5][8][2] = ((Wpk[5][7][0]*s8)+(c6*c8));
        Wpk[5][9][0] = Wpk[5][8][0];
        Wpk[5][9][1] = ((Wpk[5][7][1]*c9)+(Wpk[5][8][2]*s9));
        Wpk[5][9][2] = ((Wpk[5][8][2]*c9)-(Wpk[5][7][1]*s9));
        Wpk[5][10][0] = ((Wpk[5][8][0]*c10)+(Wpk[5][9][1]*s10));
        Wpk[5][10][1] = ((Wpk[5][9][1]*c10)-(Wpk[5][8][0]*s10));
        Wpk[5][10][2] = Wpk[5][9][2];
        Wpk[5][11][0] = ((Wpk[5][10][0]*c11)-(Wpk[5][9][2]*s11));
        Wpk[5][11][1] = Wpk[5][10][1];
        Wpk[5][11][2] = ((Wpk[5][9][2]*c11)+(Wpk[5][10][0]*s11));
        Wpk[5][12][0] = Wpk[5][11][0];
        Wpk[5][12][1] = ((Wpk[5][10][1]*c12)+(Wpk[5][11][2]*s12));
        Wpk[5][12][2] = ((Wpk[5][11][2]*c12)-(Wpk[5][10][1]*s12));
        Wpk[5][13][0] = ((Wpk[5][7][1]*s13)+(Wpk[5][8][0]*c13));
        Wpk[5][13][1] = ((Wpk[5][7][1]*c13)-(Wpk[5][8][0]*s13));
        Wpk[5][13][2] = Wpk[5][8][2];
        Wpk[5][14][0] = ((Wpk[5][13][0]*c14)-(Wpk[5][8][2]*s14));
        Wpk[5][14][1] = Wpk[5][13][1];
        Wpk[5][14][2] = ((Wpk[5][8][2]*c14)+(Wpk[5][13][0]*s14));
        Wpk[5][15][0] = ((Wpk[5][14][0]*c15)-(Wpk[5][14][2]*s15));
        Wpk[5][15][1] = Wpk[5][13][1];
        Wpk[5][15][2] = ((Wpk[5][14][0]*s15)+(Wpk[5][14][2]*c15));
        Wpk[5][16][0] = Wpk[5][15][0];
        Wpk[5][16][1] = ((Wpk[5][13][1]*c16)+(Wpk[5][15][2]*s16));
        Wpk[5][16][2] = ((Wpk[5][15][2]*c16)-(Wpk[5][13][1]*s16));
        Wpk[5][17][0] = ((Wpk[5][15][0]*c17)+(Wpk[5][16][1]*s17));
        Wpk[5][17][1] = ((Wpk[5][16][1]*c17)-(Wpk[5][15][0]*s17));
        Wpk[5][17][2] = Wpk[5][16][2];
        Wpk[5][18][0] = ((Wpk[5][17][0]*c18)-(Wpk[5][16][2]*s18));
        Wpk[5][18][1] = Wpk[5][17][1];
        Wpk[5][18][2] = ((Wpk[5][16][2]*c18)+(Wpk[5][17][0]*s18));
        Wpk[5][19][0] = ((Wpk[5][7][1]*s19)+(Wpk[5][8][0]*c19));
        Wpk[5][19][1] = ((Wpk[5][7][1]*c19)-(Wpk[5][8][0]*s19));
        Wpk[5][19][2] = Wpk[5][8][2];
        Wpk[5][20][0] = ((Wpk[5][19][0]*c20)-(Wpk[5][8][2]*s20));
        Wpk[5][20][1] = Wpk[5][19][1];
        Wpk[5][20][2] = ((Wpk[5][8][2]*c20)+(Wpk[5][19][0]*s20));
        Wpk[5][21][0] = ((Wpk[5][20][0]*c21)-(Wpk[5][20][2]*s21));
        Wpk[5][21][1] = Wpk[5][19][1];
        Wpk[5][21][2] = ((Wpk[5][20][0]*s21)+(Wpk[5][20][2]*c21));
        Wpk[5][22][0] = Wpk[5][21][0];
        Wpk[5][22][1] = ((Wpk[5][19][1]*c22)+(Wpk[5][21][2]*s22));
        Wpk[5][22][2] = ((Wpk[5][21][2]*c22)-(Wpk[5][19][1]*s22));
        Wpk[5][23][0] = ((Wpk[5][21][0]*c23)+(Wpk[5][22][1]*s23));
        Wpk[5][23][1] = ((Wpk[5][22][1]*c23)-(Wpk[5][21][0]*s23));
        Wpk[5][23][2] = Wpk[5][22][2];
        Wpk[5][24][0] = ((Wpk[5][23][0]*c24)-(Wpk[5][22][2]*s24));
        Wpk[5][24][1] = Wpk[5][23][1];
        Wpk[5][24][2] = ((Wpk[5][22][2]*c24)+(Wpk[5][23][0]*s24));
        Wpk[5][25][1] = s25;
        Wpk[5][25][2] = c25;
        Wpk[5][26][0] = (s25*s26);
        Wpk[5][26][1] = (s25*c26);
        Wpk[5][26][2] = c25;
        Wpk[5][27][0] = ((Wpk[5][26][0]*c27)-(s27*c25));
        Wpk[5][27][1] = Wpk[5][26][1];
        Wpk[5][27][2] = ((Wpk[5][26][0]*s27)+(c25*c27));
        Wpk[5][28][0] = Wpk[5][27][0];
        Wpk[5][28][1] = ((Wpk[5][26][1]*c28)+(Wpk[5][27][2]*s28));
        Wpk[5][28][2] = ((Wpk[5][27][2]*c28)-(Wpk[5][26][1]*s28));
        Wpk[5][29][0] = Wpk[5][27][0];
        Wpk[5][29][1] = ((Wpk[5][28][1]*c29)+(Wpk[5][28][2]*s29));
        Wpk[5][29][2] = ((Wpk[5][28][2]*c29)-(Wpk[5][28][1]*s29));
        Wpk[5][30][0] = ((Wpk[5][27][0]*c30)+(Wpk[5][29][1]*s30));
        Wpk[5][30][1] = ((Wpk[5][29][1]*c30)-(Wpk[5][27][0]*s30));
        Wpk[5][30][2] = Wpk[5][29][2];
        Wpk[5][31][1] = s31;
        Wpk[5][31][2] = c31;
        Wpk[5][32][0] = (s31*s32);
        Wpk[5][32][1] = (s31*c32);
        Wpk[5][32][2] = c31;
        Wpk[5][33][0] = ((Wpk[5][32][0]*c33)-(s33*c31));
        Wpk[5][33][1] = Wpk[5][32][1];
        Wpk[5][33][2] = ((Wpk[5][32][0]*s33)+(c31*c33));
        Wpk[5][34][0] = Wpk[5][33][0];
        Wpk[5][34][1] = ((Wpk[5][32][1]*c34)+(Wpk[5][33][2]*s34));
        Wpk[5][34][2] = ((Wpk[5][33][2]*c34)-(Wpk[5][32][1]*s34));
        Wpk[5][35][0] = Wpk[5][33][0];
        Wpk[5][35][1] = ((Wpk[5][34][1]*c35)+(Wpk[5][34][2]*s35));
        Wpk[5][35][2] = ((Wpk[5][34][2]*c35)-(Wpk[5][34][1]*s35));
        Wpk[5][36][0] = ((Wpk[5][33][0]*c36)+(Wpk[5][35][1]*s36));
        Wpk[5][36][1] = ((Wpk[5][35][1]*c36)-(Wpk[5][33][0]*s36));
        Wpk[5][36][2] = Wpk[5][35][2];
        Wpk[6][6][0] = 1.;
        Wpk[6][7][0] = c7;
        Wpk[6][7][1] = -s7;
        Wpk[6][8][0] = (c7*c8);
        Wpk[6][8][1] = -s7;
        Wpk[6][8][2] = (s8*c7);
        Wpk[6][9][0] = Wpk[6][8][0];
        Wpk[6][9][1] = ((Wpk[6][8][2]*s9)-(s7*c9));
        Wpk[6][9][2] = ((Wpk[6][8][2]*c9)+(s7*s9));
        Wpk[6][10][0] = ((Wpk[6][8][0]*c10)+(Wpk[6][9][1]*s10));
        Wpk[6][10][1] = ((Wpk[6][9][1]*c10)-(Wpk[6][8][0]*s10));
        Wpk[6][10][2] = Wpk[6][9][2];
        Wpk[6][11][0] = ((Wpk[6][10][0]*c11)-(Wpk[6][9][2]*s11));
        Wpk[6][11][1] = Wpk[6][10][1];
        Wpk[6][11][2] = ((Wpk[6][9][2]*c11)+(Wpk[6][10][0]*s11));
        Wpk[6][12][0] = Wpk[6][11][0];
        Wpk[6][12][1] = ((Wpk[6][10][1]*c12)+(Wpk[6][11][2]*s12));
        Wpk[6][12][2] = ((Wpk[6][11][2]*c12)-(Wpk[6][10][1]*s12));
        Wpk[6][13][0] = ((Wpk[6][8][0]*c13)-(s7*s13));
        Wpk[6][13][1] = -((Wpk[6][8][0]*s13)+(s7*c13));
        Wpk[6][13][2] = Wpk[6][8][2];
        Wpk[6][14][0] = ((Wpk[6][13][0]*c14)-(Wpk[6][8][2]*s14));
        Wpk[6][14][1] = Wpk[6][13][1];
        Wpk[6][14][2] = ((Wpk[6][8][2]*c14)+(Wpk[6][13][0]*s14));
        Wpk[6][15][0] = ((Wpk[6][14][0]*c15)-(Wpk[6][14][2]*s15));
        Wpk[6][15][1] = Wpk[6][13][1];
        Wpk[6][15][2] = ((Wpk[6][14][0]*s15)+(Wpk[6][14][2]*c15));
        Wpk[6][16][0] = Wpk[6][15][0];
        Wpk[6][16][1] = ((Wpk[6][13][1]*c16)+(Wpk[6][15][2]*s16));
        Wpk[6][16][2] = ((Wpk[6][15][2]*c16)-(Wpk[6][13][1]*s16));
        Wpk[6][17][0] = ((Wpk[6][15][0]*c17)+(Wpk[6][16][1]*s17));
        Wpk[6][17][1] = ((Wpk[6][16][1]*c17)-(Wpk[6][15][0]*s17));
        Wpk[6][17][2] = Wpk[6][16][2];
        Wpk[6][18][0] = ((Wpk[6][17][0]*c18)-(Wpk[6][16][2]*s18));
        Wpk[6][18][1] = Wpk[6][17][1];
        Wpk[6][18][2] = ((Wpk[6][16][2]*c18)+(Wpk[6][17][0]*s18));
        Wpk[6][19][0] = ((Wpk[6][8][0]*c19)-(s7*s19));
        Wpk[6][19][1] = -((Wpk[6][8][0]*s19)+(s7*c19));
        Wpk[6][19][2] = Wpk[6][8][2];
        Wpk[6][20][0] = ((Wpk[6][19][0]*c20)-(Wpk[6][8][2]*s20));
        Wpk[6][20][1] = Wpk[6][19][1];
        Wpk[6][20][2] = ((Wpk[6][8][2]*c20)+(Wpk[6][19][0]*s20));
        Wpk[6][21][0] = ((Wpk[6][20][0]*c21)-(Wpk[6][20][2]*s21));
        Wpk[6][21][1] = Wpk[6][19][1];
        Wpk[6][21][2] = ((Wpk[6][20][0]*s21)+(Wpk[6][20][2]*c21));
        Wpk[6][22][0] = Wpk[6][21][0];
        Wpk[6][22][1] = ((Wpk[6][19][1]*c22)+(Wpk[6][21][2]*s22));
        Wpk[6][22][2] = ((Wpk[6][21][2]*c22)-(Wpk[6][19][1]*s22));
        Wpk[6][23][0] = ((Wpk[6][21][0]*c23)+(Wpk[6][22][1]*s23));
        Wpk[6][23][1] = ((Wpk[6][22][1]*c23)-(Wpk[6][21][0]*s23));
        Wpk[6][23][2] = Wpk[6][22][2];
        Wpk[6][24][0] = ((Wpk[6][23][0]*c24)-(Wpk[6][22][2]*s24));
        Wpk[6][24][1] = Wpk[6][23][1];
        Wpk[6][24][2] = ((Wpk[6][22][2]*c24)+(Wpk[6][23][0]*s24));
        Wpk[7][7][2] = 1.;
        Wpk[7][8][0] = -s8;
        Wpk[7][8][2] = c8;
        Wpk[7][9][0] = -s8;
        Wpk[7][9][1] = (s9*c8);
        Wpk[7][9][2] = (c8*c9);
        Wpk[7][10][0] = ((Wpk[7][9][1]*s10)-(s8*c10));
        Wpk[7][10][1] = ((Wpk[7][9][1]*c10)+(s8*s10));
        Wpk[7][10][2] = Wpk[7][9][2];
        Wpk[7][11][0] = ((Wpk[7][10][0]*c11)-(Wpk[7][9][2]*s11));
        Wpk[7][11][1] = Wpk[7][10][1];
        Wpk[7][11][2] = ((Wpk[7][9][2]*c11)+(Wpk[7][10][0]*s11));
        Wpk[7][12][0] = Wpk[7][11][0];
        Wpk[7][12][1] = ((Wpk[7][10][1]*c12)+(Wpk[7][11][2]*s12));
        Wpk[7][12][2] = ((Wpk[7][11][2]*c12)-(Wpk[7][10][1]*s12));
        Wpk[7][13][0] = -(s8*c13);
        Wpk[7][13][1] = (s8*s13);
        Wpk[7][13][2] = c8;
        Wpk[7][14][0] = ((Wpk[7][13][0]*c14)-(s14*c8));
        Wpk[7][14][1] = Wpk[7][13][1];
        Wpk[7][14][2] = ((Wpk[7][13][0]*s14)+(c8*c14));
        Wpk[7][15][0] = ((Wpk[7][14][0]*c15)-(Wpk[7][14][2]*s15));
        Wpk[7][15][1] = Wpk[7][13][1];
        Wpk[7][15][2] = ((Wpk[7][14][0]*s15)+(Wpk[7][14][2]*c15));
        Wpk[7][16][0] = Wpk[7][15][0];
        Wpk[7][16][1] = ((Wpk[7][13][1]*c16)+(Wpk[7][15][2]*s16));
        Wpk[7][16][2] = ((Wpk[7][15][2]*c16)-(Wpk[7][13][1]*s16));
        Wpk[7][17][0] = ((Wpk[7][15][0]*c17)+(Wpk[7][16][1]*s17));
        Wpk[7][17][1] = ((Wpk[7][16][1]*c17)-(Wpk[7][15][0]*s17));
        Wpk[7][17][2] = Wpk[7][16][2];
        Wpk[7][18][0] = ((Wpk[7][17][0]*c18)-(Wpk[7][16][2]*s18));
        Wpk[7][18][1] = Wpk[7][17][1];
        Wpk[7][18][2] = ((Wpk[7][16][2]*c18)+(Wpk[7][17][0]*s18));
        Wpk[7][19][0] = -(s8*c19);
        Wpk[7][19][1] = (s8*s19);
        Wpk[7][19][2] = c8;
        Wpk[7][20][0] = ((Wpk[7][19][0]*c20)-(s20*c8));
        Wpk[7][20][1] = Wpk[7][19][1];
        Wpk[7][20][2] = ((Wpk[7][19][0]*s20)+(c8*c20));
        Wpk[7][21][0] = ((Wpk[7][20][0]*c21)-(Wpk[7][20][2]*s21));
        Wpk[7][21][1] = Wpk[7][19][1];
        Wpk[7][21][2] = ((Wpk[7][20][0]*s21)+(Wpk[7][20][2]*c21));
        Wpk[7][22][0] = Wpk[7][21][0];
        Wpk[7][22][1] = ((Wpk[7][19][1]*c22)+(Wpk[7][21][2]*s22));
        Wpk[7][22][2] = ((Wpk[7][21][2]*c22)-(Wpk[7][19][1]*s22));
        Wpk[7][23][0] = ((Wpk[7][21][0]*c23)+(Wpk[7][22][1]*s23));
        Wpk[7][23][1] = ((Wpk[7][22][1]*c23)-(Wpk[7][21][0]*s23));
        Wpk[7][23][2] = Wpk[7][22][2];
        Wpk[7][24][0] = ((Wpk[7][23][0]*c24)-(Wpk[7][22][2]*s24));
        Wpk[7][24][1] = Wpk[7][23][1];
        Wpk[7][24][2] = ((Wpk[7][22][2]*c24)+(Wpk[7][23][0]*s24));
        Wpk[8][8][1] = 1.;
        Wpk[8][9][1] = c9;
        Wpk[8][9][2] = -s9;
        Wpk[8][10][0] = (s10*c9);
        Wpk[8][10][1] = (c9*c10);
        Wpk[8][10][2] = -s9;
        Wpk[8][11][0] = ((Wpk[8][10][0]*c11)+(s9*s11));
        Wpk[8][11][1] = Wpk[8][10][1];
        Wpk[8][11][2] = ((Wpk[8][10][0]*s11)-(s9*c11));
        Wpk[8][12][0] = Wpk[8][11][0];
        Wpk[8][12][1] = ((Wpk[8][10][1]*c12)+(Wpk[8][11][2]*s12));
        Wpk[8][12][2] = ((Wpk[8][11][2]*c12)-(Wpk[8][10][1]*s12));
        Wpk[8][13][0] = s13;
        Wpk[8][13][1] = c13;
        Wpk[8][14][0] = (s13*c14);
        Wpk[8][14][1] = c13;
        Wpk[8][14][2] = (s13*s14);
        Wpk[8][15][0] = ((Wpk[8][14][0]*c15)-(Wpk[8][14][2]*s15));
        Wpk[8][15][1] = c13;
        Wpk[8][15][2] = ((Wpk[8][14][0]*s15)+(Wpk[8][14][2]*c15));
        Wpk[8][16][0] = Wpk[8][15][0];
        Wpk[8][16][1] = ((Wpk[8][15][2]*s16)+(c13*c16));
        Wpk[8][16][2] = ((Wpk[8][15][2]*c16)-(s16*c13));
        Wpk[8][17][0] = ((Wpk[8][15][0]*c17)+(Wpk[8][16][1]*s17));
        Wpk[8][17][1] = ((Wpk[8][16][1]*c17)-(Wpk[8][15][0]*s17));
        Wpk[8][17][2] = Wpk[8][16][2];
        Wpk[8][18][0] = ((Wpk[8][17][0]*c18)-(Wpk[8][16][2]*s18));
        Wpk[8][18][1] = Wpk[8][17][1];
        Wpk[8][18][2] = ((Wpk[8][16][2]*c18)+(Wpk[8][17][0]*s18));
        Wpk[8][19][0] = s19;
        Wpk[8][19][1] = c19;
        Wpk[8][20][0] = (s19*c20);
        Wpk[8][20][1] = c19;
        Wpk[8][20][2] = (s19*s20);
        Wpk[8][21][0] = ((Wpk[8][20][0]*c21)-(Wpk[8][20][2]*s21));
        Wpk[8][21][1] = c19;
        Wpk[8][21][2] = ((Wpk[8][20][0]*s21)+(Wpk[8][20][2]*c21));
        Wpk[8][22][0] = Wpk[8][21][0];
        Wpk[8][22][1] = ((Wpk[8][21][2]*s22)+(c19*c22));
        Wpk[8][22][2] = ((Wpk[8][21][2]*c22)-(s22*c19));
        Wpk[8][23][0] = ((Wpk[8][21][0]*c23)+(Wpk[8][22][1]*s23));
        Wpk[8][23][1] = ((Wpk[8][22][1]*c23)-(Wpk[8][21][0]*s23));
        Wpk[8][23][2] = Wpk[8][22][2];
        Wpk[8][24][0] = ((Wpk[8][23][0]*c24)-(Wpk[8][22][2]*s24));
        Wpk[8][24][1] = Wpk[8][23][1];
        Wpk[8][24][2] = ((Wpk[8][22][2]*c24)+(Wpk[8][23][0]*s24));
        Wpk[9][9][0] = 1.;
        Wpk[9][10][0] = c10;
        Wpk[9][10][1] = -s10;
        Wpk[9][11][0] = (c10*c11);
        Wpk[9][11][1] = -s10;
        Wpk[9][11][2] = (s11*c10);
        Wpk[9][12][0] = Wpk[9][11][0];
        Wpk[9][12][1] = ((Wpk[9][11][2]*s12)-(s10*c12));
        Wpk[9][12][2] = ((Wpk[9][11][2]*c12)+(s10*s12));
        Wpk[10][10][2] = 1.;
        Wpk[10][11][0] = -s11;
        Wpk[10][11][2] = c11;
        Wpk[10][12][0] = -s11;
        Wpk[10][12][1] = (s12*c11);
        Wpk[10][12][2] = (c11*c12);
        Wpk[11][11][1] = 1.;
        Wpk[11][12][1] = c12;
        Wpk[11][12][2] = -s12;
        Wpk[12][12][0] = 1.;
        Wpk[13][13][2] = 1.;
        Wpk[13][14][0] = -s14;
        Wpk[13][14][2] = c14;
        Wpk[13][15][0] = -((s14*c15)+(s15*c14));
        Wpk[13][15][2] = ((c14*c15)-(s14*s15));
        Wpk[13][16][0] = Wpk[13][15][0];
        Wpk[13][16][1] = (Wpk[13][15][2]*s16);
        Wpk[13][16][2] = (Wpk[13][15][2]*c16);
        Wpk[13][17][0] = ((Wpk[13][15][0]*c17)+(Wpk[13][16][1]*s17));
        Wpk[13][17][1] = ((Wpk[13][16][1]*c17)-(Wpk[13][15][0]*s17));
        Wpk[13][17][2] = Wpk[13][16][2];
        Wpk[13][18][0] = ((Wpk[13][17][0]*c18)-(Wpk[13][16][2]*s18));
        Wpk[13][18][1] = Wpk[13][17][1];
        Wpk[13][18][2] = ((Wpk[13][16][2]*c18)+(Wpk[13][17][0]*s18));
        Wpk[14][14][1] = 1.;
        Wpk[14][15][1] = 1.;
        Wpk[14][16][1] = c16;
        Wpk[14][16][2] = -s16;
        Wpk[14][17][0] = (s17*c16);
        Wpk[14][17][1] = (c16*c17);
        Wpk[14][17][2] = -s16;
        Wpk[14][18][0] = ((Wpk[14][17][0]*c18)+(s16*s18));
        Wpk[14][18][1] = Wpk[14][17][1];
        Wpk[14][18][2] = ((Wpk[14][17][0]*s18)-(s16*c18));
        Wpk[15][15][1] = 1.;
        Wpk[15][16][1] = c16;
        Wpk[15][16][2] = -s16;
        Wpk[15][17][0] = (s17*c16);
        Wpk[15][17][1] = (c16*c17);
        Wpk[15][17][2] = -s16;
        Wpk[15][18][0] = ((Wpk[15][17][0]*c18)+(s16*s18));
        Wpk[15][18][1] = Wpk[15][17][1];
        Wpk[15][18][2] = ((Wpk[15][17][0]*s18)-(s16*c18));
        Wpk[16][16][0] = 1.;
        Wpk[16][17][0] = c17;
        Wpk[16][17][1] = -s17;
        Wpk[16][18][0] = (c17*c18);
        Wpk[16][18][1] = -s17;
        Wpk[16][18][2] = (s18*c17);
        Wpk[17][17][2] = 1.;
        Wpk[17][18][0] = -s18;
        Wpk[17][18][2] = c18;
        Wpk[18][18][1] = 1.;
        Wpk[19][19][2] = 1.;
        Wpk[19][20][0] = -s20;
        Wpk[19][20][2] = c20;
        Wpk[19][21][0] = -((s20*c21)+(s21*c20));
        Wpk[19][21][2] = ((c20*c21)-(s20*s21));
        Wpk[19][22][0] = Wpk[19][21][0];
        Wpk[19][22][1] = (Wpk[19][21][2]*s22);
        Wpk[19][22][2] = (Wpk[19][21][2]*c22);
        Wpk[19][23][0] = ((Wpk[19][21][0]*c23)+(Wpk[19][22][1]*s23));
        Wpk[19][23][1] = ((Wpk[19][22][1]*c23)-(Wpk[19][21][0]*s23));
        Wpk[19][23][2] = Wpk[19][22][2];
        Wpk[19][24][0] = ((Wpk[19][23][0]*c24)-(Wpk[19][22][2]*s24));
        Wpk[19][24][1] = Wpk[19][23][1];
        Wpk[19][24][2] = ((Wpk[19][22][2]*c24)+(Wpk[19][23][0]*s24));
        Wpk[20][20][1] = 1.;
        Wpk[20][21][1] = 1.;
        Wpk[20][22][1] = c22;
        Wpk[20][22][2] = -s22;
        Wpk[20][23][0] = (s23*c22);
        Wpk[20][23][1] = (c22*c23);
        Wpk[20][23][2] = -s22;
        Wpk[20][24][0] = ((Wpk[20][23][0]*c24)+(s22*s24));
        Wpk[20][24][1] = Wpk[20][23][1];
        Wpk[20][24][2] = ((Wpk[20][23][0]*s24)-(s22*c24));
        Wpk[21][21][1] = 1.;
        Wpk[21][22][1] = c22;
        Wpk[21][22][2] = -s22;
        Wpk[21][23][0] = (s23*c22);
        Wpk[21][23][1] = (c22*c23);
        Wpk[21][23][2] = -s22;
        Wpk[21][24][0] = ((Wpk[21][23][0]*c24)+(s22*s24));
        Wpk[21][24][1] = Wpk[21][23][1];
        Wpk[21][24][2] = ((Wpk[21][23][0]*s24)-(s22*c24));
        Wpk[22][22][0] = 1.;
        Wpk[22][23][0] = c23;
        Wpk[22][23][1] = -s23;
        Wpk[22][24][0] = (c23*c24);
        Wpk[22][24][1] = -s23;
        Wpk[22][24][2] = (s24*c23);
        Wpk[23][23][2] = 1.;
        Wpk[23][24][0] = -s24;
        Wpk[23][24][2] = c24;
        Wpk[24][24][1] = 1.;
        Wpk[25][25][0] = 1.;
        Wpk[25][26][0] = c26;
        Wpk[25][26][1] = -s26;
        Wpk[25][27][0] = (c26*c27);
        Wpk[25][27][1] = -s26;
        Wpk[25][27][2] = (s27*c26);
        Wpk[25][28][0] = Wpk[25][27][0];
        Wpk[25][28][1] = ((Wpk[25][27][2]*s28)-(s26*c28));
        Wpk[25][28][2] = ((Wpk[25][27][2]*c28)+(s26*s28));
        Wpk[25][29][0] = Wpk[25][27][0];
        Wpk[25][29][1] = ((Wpk[25][28][1]*c29)+(Wpk[25][28][2]*s29));
        Wpk[25][29][2] = ((Wpk[25][28][2]*c29)-(Wpk[25][28][1]*s29));
        Wpk[25][30][0] = ((Wpk[25][27][0]*c30)+(Wpk[25][29][1]*s30));
        Wpk[25][30][1] = ((Wpk[25][29][1]*c30)-(Wpk[25][27][0]*s30));
        Wpk[25][30][2] = Wpk[25][29][2];
        Wpk[26][26][2] = 1.;
        Wpk[26][27][0] = -s27;
        Wpk[26][27][2] = c27;
        Wpk[26][28][0] = -s27;
        Wpk[26][28][1] = (s28*c27);
        Wpk[26][28][2] = (c27*c28);
        Wpk[26][29][0] = -s27;
        Wpk[26][29][1] = ((Wpk[26][28][1]*c29)+(Wpk[26][28][2]*s29));
        Wpk[26][29][2] = ((Wpk[26][28][2]*c29)-(Wpk[26][28][1]*s29));
        Wpk[26][30][0] = ((Wpk[26][29][1]*s30)-(s27*c30));
        Wpk[26][30][1] = ((Wpk[26][29][1]*c30)+(s27*s30));
        Wpk[26][30][2] = Wpk[26][29][2];
        Wpk[27][27][1] = 1.;
        Wpk[27][28][1] = c28;
        Wpk[27][28][2] = -s28;
        Wpk[27][29][1] = ((c28*c29)-(s28*s29));
        Wpk[27][29][2] = -((s28*c29)+(s29*c28));
        Wpk[27][30][0] = (Wpk[27][29][1]*s30);
        Wpk[27][30][1] = (Wpk[27][29][1]*c30);
        Wpk[27][30][2] = Wpk[27][29][2];
        Wpk[28][28][0] = 1.;
        Wpk[28][29][0] = 1.;
        Wpk[28][30][0] = c30;
        Wpk[28][30][1] = -s30;
        Wpk[29][29][0] = 1.;
        Wpk[29][30][0] = c30;
        Wpk[29][30][1] = -s30;
        Wpk[30][30][2] = 1.;
        Wpk[31][31][0] = 1.;
        Wpk[31][32][0] = c32;
        Wpk[31][32][1] = -s32;
        Wpk[31][33][0] = (c32*c33);
        Wpk[31][33][1] = -s32;
        Wpk[31][33][2] = (s33*c32);
        Wpk[31][34][0] = Wpk[31][33][0];
        Wpk[31][34][1] = ((Wpk[31][33][2]*s34)-(s32*c34));
        Wpk[31][34][2] = ((Wpk[31][33][2]*c34)+(s32*s34));
        Wpk[31][35][0] = Wpk[31][33][0];
        Wpk[31][35][1] = ((Wpk[31][34][1]*c35)+(Wpk[31][34][2]*s35));
        Wpk[31][35][2] = ((Wpk[31][34][2]*c35)-(Wpk[31][34][1]*s35));
        Wpk[31][36][0] = ((Wpk[31][33][0]*c36)+(Wpk[31][35][1]*s36));
        Wpk[31][36][1] = ((Wpk[31][35][1]*c36)-(Wpk[31][33][0]*s36));
        Wpk[31][36][2] = Wpk[31][35][2];
        Wpk[32][32][2] = 1.;
        Wpk[32][33][0] = -s33;
        Wpk[32][33][2] = c33;
        Wpk[32][34][0] = -s33;
        Wpk[32][34][1] = (s34*c33);
        Wpk[32][34][2] = (c33*c34);
        Wpk[32][35][0] = -s33;
        Wpk[32][35][1] = ((Wpk[32][34][1]*c35)+(Wpk[32][34][2]*s35));
        Wpk[32][35][2] = ((Wpk[32][34][2]*c35)-(Wpk[32][34][1]*s35));
        Wpk[32][36][0] = ((Wpk[32][35][1]*s36)-(s33*c36));
        Wpk[32][36][1] = ((Wpk[32][35][1]*c36)+(s33*s36));
        Wpk[32][36][2] = Wpk[32][35][2];
        Wpk[33][33][1] = 1.;
        Wpk[33][34][1] = c34;
        Wpk[33][34][2] = -s34;
        Wpk[33][35][1] = ((c34*c35)-(s34*s35));
        Wpk[33][35][2] = -((s34*c35)+(s35*c34));
        Wpk[33][36][0] = (Wpk[33][35][1]*s36);
        Wpk[33][36][1] = (Wpk[33][35][1]*c36);
        Wpk[33][36][2] = Wpk[33][35][2];
        Wpk[34][34][0] = 1.;
        Wpk[34][35][0] = 1.;
        Wpk[34][36][0] = c36;
        Wpk[34][36][1] = -s36;
        Wpk[35][35][0] = 1.;
        Wpk[35][36][0] = c36;
        Wpk[35][36][1] = -s36;
        Wpk[36][36][2] = 1.;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = 1.;
        Vpk[0][1][0] = 1.;
        Vpk[0][2][0] = 1.;
        Vpk[0][3][0] = Cik[3][0][0];
        Vpk[0][3][1] = Cik[3][0][1];
        Vpk[0][3][2] = Cik[3][0][2];
        Vpk[0][4][0] = Cik[3][0][0];
        Vpk[0][4][1] = Cik[3][0][1];
        Vpk[0][4][2] = Cik[3][0][2];
        Vpk[0][5][0] = Cik[3][0][0];
        Vpk[0][5][1] = Cik[3][0][1];
        Vpk[0][5][2] = Cik[3][0][2];
        Vpk[0][6][0] = Cik[3][0][0];
        Vpk[0][6][1] = ((Cik[3][0][1]*c6)+(Cik[3][0][2]*s6));
        Vpk[0][6][2] = ((Cik[3][0][2]*c6)-(Cik[3][0][1]*s6));
        Vpk[0][7][0] = ((Cik[3][0][0]*c7)+(Vpk[0][6][1]*s7));
        Vpk[0][7][1] = ((Vpk[0][6][1]*c7)-(Cik[3][0][0]*s7));
        Vpk[0][7][2] = Vpk[0][6][2];
        Vpk[0][8][0] = ((Vpk[0][7][0]*c8)-(Vpk[0][6][2]*s8));
        Vpk[0][8][1] = Vpk[0][7][1];
        Vpk[0][8][2] = ((Vpk[0][6][2]*c8)+(Vpk[0][7][0]*s8));
        Vpk[0][9][0] = Vpk[0][8][0];
        Vpk[0][9][1] = ((Vpk[0][7][1]*c9)+(Vpk[0][8][2]*s9));
        Vpk[0][9][2] = ((Vpk[0][8][2]*c9)-(Vpk[0][7][1]*s9));
        Vpk[0][10][0] = ((Vpk[0][8][0]*c10)+(Vpk[0][9][1]*s10));
        Vpk[0][10][1] = ((Vpk[0][9][1]*c10)-(Vpk[0][8][0]*s10));
        Vpk[0][10][2] = Vpk[0][9][2];
        Vpk[0][11][0] = ((Vpk[0][10][0]*c11)-(Vpk[0][9][2]*s11));
        Vpk[0][11][1] = Vpk[0][10][1];
        Vpk[0][11][2] = ((Vpk[0][9][2]*c11)+(Vpk[0][10][0]*s11));
        Vpk[0][12][0] = Vpk[0][11][0];
        Vpk[0][12][1] = ((Vpk[0][10][1]*c12)+(Vpk[0][11][2]*s12));
        Vpk[0][12][2] = ((Vpk[0][11][2]*c12)-(Vpk[0][10][1]*s12));
        Vpk[0][13][0] = ((Vpk[0][7][1]*s13)+(Vpk[0][8][0]*c13));
        Vpk[0][13][1] = ((Vpk[0][7][1]*c13)-(Vpk[0][8][0]*s13));
        Vpk[0][13][2] = Vpk[0][8][2];
        Vpk[0][14][0] = ((Vpk[0][13][0]*c14)-(Vpk[0][8][2]*s14));
        Vpk[0][14][1] = Vpk[0][13][1];
        Vpk[0][14][2] = ((Vpk[0][8][2]*c14)+(Vpk[0][13][0]*s14));
        Vpk[0][15][0] = ((Vpk[0][14][0]*c15)-(Vpk[0][14][2]*s15));
        Vpk[0][15][1] = Vpk[0][13][1];
        Vpk[0][15][2] = ((Vpk[0][14][0]*s15)+(Vpk[0][14][2]*c15));
        Vpk[0][16][0] = Vpk[0][15][0];
        Vpk[0][16][1] = ((Vpk[0][13][1]*c16)+(Vpk[0][15][2]*s16));
        Vpk[0][16][2] = ((Vpk[0][15][2]*c16)-(Vpk[0][13][1]*s16));
        Vpk[0][17][0] = ((Vpk[0][15][0]*c17)+(Vpk[0][16][1]*s17));
        Vpk[0][17][1] = ((Vpk[0][16][1]*c17)-(Vpk[0][15][0]*s17));
        Vpk[0][17][2] = Vpk[0][16][2];
        Vpk[0][18][0] = ((Vpk[0][17][0]*c18)-(Vpk[0][16][2]*s18));
        Vpk[0][18][1] = Vpk[0][17][1];
        Vpk[0][18][2] = ((Vpk[0][16][2]*c18)+(Vpk[0][17][0]*s18));
        Vpk[0][19][0] = ((Vpk[0][7][1]*s19)+(Vpk[0][8][0]*c19));
        Vpk[0][19][1] = ((Vpk[0][7][1]*c19)-(Vpk[0][8][0]*s19));
        Vpk[0][19][2] = Vpk[0][8][2];
        Vpk[0][20][0] = ((Vpk[0][19][0]*c20)-(Vpk[0][8][2]*s20));
        Vpk[0][20][1] = Vpk[0][19][1];
        Vpk[0][20][2] = ((Vpk[0][8][2]*c20)+(Vpk[0][19][0]*s20));
        Vpk[0][21][0] = ((Vpk[0][20][0]*c21)-(Vpk[0][20][2]*s21));
        Vpk[0][21][1] = Vpk[0][19][1];
        Vpk[0][21][2] = ((Vpk[0][20][0]*s21)+(Vpk[0][20][2]*c21));
        Vpk[0][22][0] = Vpk[0][21][0];
        Vpk[0][22][1] = ((Vpk[0][19][1]*c22)+(Vpk[0][21][2]*s22));
        Vpk[0][22][2] = ((Vpk[0][21][2]*c22)-(Vpk[0][19][1]*s22));
        Vpk[0][23][0] = ((Vpk[0][21][0]*c23)+(Vpk[0][22][1]*s23));
        Vpk[0][23][1] = ((Vpk[0][22][1]*c23)-(Vpk[0][21][0]*s23));
        Vpk[0][23][2] = Vpk[0][22][2];
        Vpk[0][24][0] = ((Vpk[0][23][0]*c24)-(Vpk[0][22][2]*s24));
        Vpk[0][24][1] = Vpk[0][23][1];
        Vpk[0][24][2] = ((Vpk[0][22][2]*c24)+(Vpk[0][23][0]*s24));
        Vpk[0][25][0] = Cik[3][0][0];
        Vpk[0][25][1] = ((Cik[3][0][1]*c25)+(Cik[3][0][2]*s25));
        Vpk[0][25][2] = ((Cik[3][0][2]*c25)-(Cik[3][0][1]*s25));
        Vpk[0][26][0] = ((Cik[3][0][0]*c26)+(Vpk[0][25][1]*s26));
        Vpk[0][26][1] = ((Vpk[0][25][1]*c26)-(Cik[3][0][0]*s26));
        Vpk[0][26][2] = Vpk[0][25][2];
        Vpk[0][27][0] = ((Vpk[0][26][0]*c27)-(Vpk[0][25][2]*s27));
        Vpk[0][27][1] = Vpk[0][26][1];
        Vpk[0][27][2] = ((Vpk[0][25][2]*c27)+(Vpk[0][26][0]*s27));
        Vpk[0][28][0] = Vpk[0][27][0];
        Vpk[0][28][1] = ((Vpk[0][26][1]*c28)+(Vpk[0][27][2]*s28));
        Vpk[0][28][2] = ((Vpk[0][27][2]*c28)-(Vpk[0][26][1]*s28));
        Vpk[0][29][0] = Vpk[0][27][0];
        Vpk[0][29][1] = ((Vpk[0][28][1]*c29)+(Vpk[0][28][2]*s29));
        Vpk[0][29][2] = ((Vpk[0][28][2]*c29)-(Vpk[0][28][1]*s29));
        Vpk[0][30][0] = ((Vpk[0][27][0]*c30)+(Vpk[0][29][1]*s30));
        Vpk[0][30][1] = ((Vpk[0][29][1]*c30)-(Vpk[0][27][0]*s30));
        Vpk[0][30][2] = Vpk[0][29][2];
        Vpk[0][31][0] = Cik[3][0][0];
        Vpk[0][31][1] = ((Cik[3][0][1]*c31)+(Cik[3][0][2]*s31));
        Vpk[0][31][2] = ((Cik[3][0][2]*c31)-(Cik[3][0][1]*s31));
        Vpk[0][32][0] = ((Cik[3][0][0]*c32)+(Vpk[0][31][1]*s32));
        Vpk[0][32][1] = ((Vpk[0][31][1]*c32)-(Cik[3][0][0]*s32));
        Vpk[0][32][2] = Vpk[0][31][2];
        Vpk[0][33][0] = ((Vpk[0][32][0]*c33)-(Vpk[0][31][2]*s33));
        Vpk[0][33][1] = Vpk[0][32][1];
        Vpk[0][33][2] = ((Vpk[0][31][2]*c33)+(Vpk[0][32][0]*s33));
        Vpk[0][34][0] = Vpk[0][33][0];
        Vpk[0][34][1] = ((Vpk[0][32][1]*c34)+(Vpk[0][33][2]*s34));
        Vpk[0][34][2] = ((Vpk[0][33][2]*c34)-(Vpk[0][32][1]*s34));
        Vpk[0][35][0] = Vpk[0][33][0];
        Vpk[0][35][1] = ((Vpk[0][34][1]*c35)+(Vpk[0][34][2]*s35));
        Vpk[0][35][2] = ((Vpk[0][34][2]*c35)-(Vpk[0][34][1]*s35));
        Vpk[0][36][0] = ((Vpk[0][33][0]*c36)+(Vpk[0][35][1]*s36));
        Vpk[0][36][1] = ((Vpk[0][35][1]*c36)-(Vpk[0][33][0]*s36));
        Vpk[0][36][2] = Vpk[0][35][2];
        Vpk[1][1][1] = 1.;
        Vpk[1][2][1] = 1.;
        Vpk[1][3][0] = Cik[3][1][0];
        Vpk[1][3][1] = Cik[3][1][1];
        Vpk[1][3][2] = Cik[3][1][2];
        Vpk[1][4][0] = Cik[3][1][0];
        Vpk[1][4][1] = Cik[3][1][1];
        Vpk[1][4][2] = Cik[3][1][2];
        Vpk[1][5][0] = Cik[3][1][0];
        Vpk[1][5][1] = Cik[3][1][1];
        Vpk[1][5][2] = Cik[3][1][2];
        Vpk[1][6][0] = Cik[3][1][0];
        Vpk[1][6][1] = ((Cik[3][1][1]*c6)+(Cik[3][1][2]*s6));
        Vpk[1][6][2] = ((Cik[3][1][2]*c6)-(Cik[3][1][1]*s6));
        Vpk[1][7][0] = ((Cik[3][1][0]*c7)+(Vpk[1][6][1]*s7));
        Vpk[1][7][1] = ((Vpk[1][6][1]*c7)-(Cik[3][1][0]*s7));
        Vpk[1][7][2] = Vpk[1][6][2];
        Vpk[1][8][0] = ((Vpk[1][7][0]*c8)-(Vpk[1][6][2]*s8));
        Vpk[1][8][1] = Vpk[1][7][1];
        Vpk[1][8][2] = ((Vpk[1][6][2]*c8)+(Vpk[1][7][0]*s8));
        Vpk[1][9][0] = Vpk[1][8][0];
        Vpk[1][9][1] = ((Vpk[1][7][1]*c9)+(Vpk[1][8][2]*s9));
        Vpk[1][9][2] = ((Vpk[1][8][2]*c9)-(Vpk[1][7][1]*s9));
        Vpk[1][10][0] = ((Vpk[1][8][0]*c10)+(Vpk[1][9][1]*s10));
        Vpk[1][10][1] = ((Vpk[1][9][1]*c10)-(Vpk[1][8][0]*s10));
        Vpk[1][10][2] = Vpk[1][9][2];
        Vpk[1][11][0] = ((Vpk[1][10][0]*c11)-(Vpk[1][9][2]*s11));
        Vpk[1][11][1] = Vpk[1][10][1];
        Vpk[1][11][2] = ((Vpk[1][9][2]*c11)+(Vpk[1][10][0]*s11));
        Vpk[1][12][0] = Vpk[1][11][0];
        Vpk[1][12][1] = ((Vpk[1][10][1]*c12)+(Vpk[1][11][2]*s12));
        Vpk[1][12][2] = ((Vpk[1][11][2]*c12)-(Vpk[1][10][1]*s12));
        Vpk[1][13][0] = ((Vpk[1][7][1]*s13)+(Vpk[1][8][0]*c13));
        Vpk[1][13][1] = ((Vpk[1][7][1]*c13)-(Vpk[1][8][0]*s13));
        Vpk[1][13][2] = Vpk[1][8][2];
        Vpk[1][14][0] = ((Vpk[1][13][0]*c14)-(Vpk[1][8][2]*s14));
        Vpk[1][14][1] = Vpk[1][13][1];
        Vpk[1][14][2] = ((Vpk[1][8][2]*c14)+(Vpk[1][13][0]*s14));
        Vpk[1][15][0] = ((Vpk[1][14][0]*c15)-(Vpk[1][14][2]*s15));
        Vpk[1][15][1] = Vpk[1][13][1];
        Vpk[1][15][2] = ((Vpk[1][14][0]*s15)+(Vpk[1][14][2]*c15));
        Vpk[1][16][0] = Vpk[1][15][0];
        Vpk[1][16][1] = ((Vpk[1][13][1]*c16)+(Vpk[1][15][2]*s16));
        Vpk[1][16][2] = ((Vpk[1][15][2]*c16)-(Vpk[1][13][1]*s16));
        Vpk[1][17][0] = ((Vpk[1][15][0]*c17)+(Vpk[1][16][1]*s17));
        Vpk[1][17][1] = ((Vpk[1][16][1]*c17)-(Vpk[1][15][0]*s17));
        Vpk[1][17][2] = Vpk[1][16][2];
        Vpk[1][18][0] = ((Vpk[1][17][0]*c18)-(Vpk[1][16][2]*s18));
        Vpk[1][18][1] = Vpk[1][17][1];
        Vpk[1][18][2] = ((Vpk[1][16][2]*c18)+(Vpk[1][17][0]*s18));
        Vpk[1][19][0] = ((Vpk[1][7][1]*s19)+(Vpk[1][8][0]*c19));
        Vpk[1][19][1] = ((Vpk[1][7][1]*c19)-(Vpk[1][8][0]*s19));
        Vpk[1][19][2] = Vpk[1][8][2];
        Vpk[1][20][0] = ((Vpk[1][19][0]*c20)-(Vpk[1][8][2]*s20));
        Vpk[1][20][1] = Vpk[1][19][1];
        Vpk[1][20][2] = ((Vpk[1][8][2]*c20)+(Vpk[1][19][0]*s20));
        Vpk[1][21][0] = ((Vpk[1][20][0]*c21)-(Vpk[1][20][2]*s21));
        Vpk[1][21][1] = Vpk[1][19][1];
        Vpk[1][21][2] = ((Vpk[1][20][0]*s21)+(Vpk[1][20][2]*c21));
        Vpk[1][22][0] = Vpk[1][21][0];
        Vpk[1][22][1] = ((Vpk[1][19][1]*c22)+(Vpk[1][21][2]*s22));
        Vpk[1][22][2] = ((Vpk[1][21][2]*c22)-(Vpk[1][19][1]*s22));
        Vpk[1][23][0] = ((Vpk[1][21][0]*c23)+(Vpk[1][22][1]*s23));
        Vpk[1][23][1] = ((Vpk[1][22][1]*c23)-(Vpk[1][21][0]*s23));
        Vpk[1][23][2] = Vpk[1][22][2];
        Vpk[1][24][0] = ((Vpk[1][23][0]*c24)-(Vpk[1][22][2]*s24));
        Vpk[1][24][1] = Vpk[1][23][1];
        Vpk[1][24][2] = ((Vpk[1][22][2]*c24)+(Vpk[1][23][0]*s24));
        Vpk[1][25][0] = Cik[3][1][0];
        Vpk[1][25][1] = ((Cik[3][1][1]*c25)+(Cik[3][1][2]*s25));
        Vpk[1][25][2] = ((Cik[3][1][2]*c25)-(Cik[3][1][1]*s25));
        Vpk[1][26][0] = ((Cik[3][1][0]*c26)+(Vpk[1][25][1]*s26));
        Vpk[1][26][1] = ((Vpk[1][25][1]*c26)-(Cik[3][1][0]*s26));
        Vpk[1][26][2] = Vpk[1][25][2];
        Vpk[1][27][0] = ((Vpk[1][26][0]*c27)-(Vpk[1][25][2]*s27));
        Vpk[1][27][1] = Vpk[1][26][1];
        Vpk[1][27][2] = ((Vpk[1][25][2]*c27)+(Vpk[1][26][0]*s27));
        Vpk[1][28][0] = Vpk[1][27][0];
        Vpk[1][28][1] = ((Vpk[1][26][1]*c28)+(Vpk[1][27][2]*s28));
        Vpk[1][28][2] = ((Vpk[1][27][2]*c28)-(Vpk[1][26][1]*s28));
        Vpk[1][29][0] = Vpk[1][27][0];
        Vpk[1][29][1] = ((Vpk[1][28][1]*c29)+(Vpk[1][28][2]*s29));
        Vpk[1][29][2] = ((Vpk[1][28][2]*c29)-(Vpk[1][28][1]*s29));
        Vpk[1][30][0] = ((Vpk[1][27][0]*c30)+(Vpk[1][29][1]*s30));
        Vpk[1][30][1] = ((Vpk[1][29][1]*c30)-(Vpk[1][27][0]*s30));
        Vpk[1][30][2] = Vpk[1][29][2];
        Vpk[1][31][0] = Cik[3][1][0];
        Vpk[1][31][1] = ((Cik[3][1][1]*c31)+(Cik[3][1][2]*s31));
        Vpk[1][31][2] = ((Cik[3][1][2]*c31)-(Cik[3][1][1]*s31));
        Vpk[1][32][0] = ((Cik[3][1][0]*c32)+(Vpk[1][31][1]*s32));
        Vpk[1][32][1] = ((Vpk[1][31][1]*c32)-(Cik[3][1][0]*s32));
        Vpk[1][32][2] = Vpk[1][31][2];
        Vpk[1][33][0] = ((Vpk[1][32][0]*c33)-(Vpk[1][31][2]*s33));
        Vpk[1][33][1] = Vpk[1][32][1];
        Vpk[1][33][2] = ((Vpk[1][31][2]*c33)+(Vpk[1][32][0]*s33));
        Vpk[1][34][0] = Vpk[1][33][0];
        Vpk[1][34][1] = ((Vpk[1][32][1]*c34)+(Vpk[1][33][2]*s34));
        Vpk[1][34][2] = ((Vpk[1][33][2]*c34)-(Vpk[1][32][1]*s34));
        Vpk[1][35][0] = Vpk[1][33][0];
        Vpk[1][35][1] = ((Vpk[1][34][1]*c35)+(Vpk[1][34][2]*s35));
        Vpk[1][35][2] = ((Vpk[1][34][2]*c35)-(Vpk[1][34][1]*s35));
        Vpk[1][36][0] = ((Vpk[1][33][0]*c36)+(Vpk[1][35][1]*s36));
        Vpk[1][36][1] = ((Vpk[1][35][1]*c36)-(Vpk[1][33][0]*s36));
        Vpk[1][36][2] = Vpk[1][35][2];
        Vpk[2][2][2] = 1.;
        Vpk[2][3][0] = Cik[3][2][0];
        Vpk[2][3][1] = Cik[3][2][1];
        Vpk[2][3][2] = Cik[3][2][2];
        Vpk[2][4][0] = Cik[3][2][0];
        Vpk[2][4][1] = Cik[3][2][1];
        Vpk[2][4][2] = Cik[3][2][2];
        Vpk[2][5][0] = Cik[3][2][0];
        Vpk[2][5][1] = Cik[3][2][1];
        Vpk[2][5][2] = Cik[3][2][2];
        Vpk[2][6][0] = Cik[3][2][0];
        Vpk[2][6][1] = ((Cik[3][2][1]*c6)+(Cik[3][2][2]*s6));
        Vpk[2][6][2] = ((Cik[3][2][2]*c6)-(Cik[3][2][1]*s6));
        Vpk[2][7][0] = ((Cik[3][2][0]*c7)+(Vpk[2][6][1]*s7));
        Vpk[2][7][1] = ((Vpk[2][6][1]*c7)-(Cik[3][2][0]*s7));
        Vpk[2][7][2] = Vpk[2][6][2];
        Vpk[2][8][0] = ((Vpk[2][7][0]*c8)-(Vpk[2][6][2]*s8));
        Vpk[2][8][1] = Vpk[2][7][1];
        Vpk[2][8][2] = ((Vpk[2][6][2]*c8)+(Vpk[2][7][0]*s8));
        Vpk[2][9][0] = Vpk[2][8][0];
        Vpk[2][9][1] = ((Vpk[2][7][1]*c9)+(Vpk[2][8][2]*s9));
        Vpk[2][9][2] = ((Vpk[2][8][2]*c9)-(Vpk[2][7][1]*s9));
        Vpk[2][10][0] = ((Vpk[2][8][0]*c10)+(Vpk[2][9][1]*s10));
        Vpk[2][10][1] = ((Vpk[2][9][1]*c10)-(Vpk[2][8][0]*s10));
        Vpk[2][10][2] = Vpk[2][9][2];
        Vpk[2][11][0] = ((Vpk[2][10][0]*c11)-(Vpk[2][9][2]*s11));
        Vpk[2][11][1] = Vpk[2][10][1];
        Vpk[2][11][2] = ((Vpk[2][9][2]*c11)+(Vpk[2][10][0]*s11));
        Vpk[2][12][0] = Vpk[2][11][0];
        Vpk[2][12][1] = ((Vpk[2][10][1]*c12)+(Vpk[2][11][2]*s12));
        Vpk[2][12][2] = ((Vpk[2][11][2]*c12)-(Vpk[2][10][1]*s12));
        Vpk[2][13][0] = ((Vpk[2][7][1]*s13)+(Vpk[2][8][0]*c13));
        Vpk[2][13][1] = ((Vpk[2][7][1]*c13)-(Vpk[2][8][0]*s13));
        Vpk[2][13][2] = Vpk[2][8][2];
        Vpk[2][14][0] = ((Vpk[2][13][0]*c14)-(Vpk[2][8][2]*s14));
        Vpk[2][14][1] = Vpk[2][13][1];
        Vpk[2][14][2] = ((Vpk[2][8][2]*c14)+(Vpk[2][13][0]*s14));
        Vpk[2][15][0] = ((Vpk[2][14][0]*c15)-(Vpk[2][14][2]*s15));
        Vpk[2][15][1] = Vpk[2][13][1];
        Vpk[2][15][2] = ((Vpk[2][14][0]*s15)+(Vpk[2][14][2]*c15));
        Vpk[2][16][0] = Vpk[2][15][0];
        Vpk[2][16][1] = ((Vpk[2][13][1]*c16)+(Vpk[2][15][2]*s16));
        Vpk[2][16][2] = ((Vpk[2][15][2]*c16)-(Vpk[2][13][1]*s16));
        Vpk[2][17][0] = ((Vpk[2][15][0]*c17)+(Vpk[2][16][1]*s17));
        Vpk[2][17][1] = ((Vpk[2][16][1]*c17)-(Vpk[2][15][0]*s17));
        Vpk[2][17][2] = Vpk[2][16][2];
        Vpk[2][18][0] = ((Vpk[2][17][0]*c18)-(Vpk[2][16][2]*s18));
        Vpk[2][18][1] = Vpk[2][17][1];
        Vpk[2][18][2] = ((Vpk[2][16][2]*c18)+(Vpk[2][17][0]*s18));
        Vpk[2][19][0] = ((Vpk[2][7][1]*s19)+(Vpk[2][8][0]*c19));
        Vpk[2][19][1] = ((Vpk[2][7][1]*c19)-(Vpk[2][8][0]*s19));
        Vpk[2][19][2] = Vpk[2][8][2];
        Vpk[2][20][0] = ((Vpk[2][19][0]*c20)-(Vpk[2][8][2]*s20));
        Vpk[2][20][1] = Vpk[2][19][1];
        Vpk[2][20][2] = ((Vpk[2][8][2]*c20)+(Vpk[2][19][0]*s20));
        Vpk[2][21][0] = ((Vpk[2][20][0]*c21)-(Vpk[2][20][2]*s21));
        Vpk[2][21][1] = Vpk[2][19][1];
        Vpk[2][21][2] = ((Vpk[2][20][0]*s21)+(Vpk[2][20][2]*c21));
        Vpk[2][22][0] = Vpk[2][21][0];
        Vpk[2][22][1] = ((Vpk[2][19][1]*c22)+(Vpk[2][21][2]*s22));
        Vpk[2][22][2] = ((Vpk[2][21][2]*c22)-(Vpk[2][19][1]*s22));
        Vpk[2][23][0] = ((Vpk[2][21][0]*c23)+(Vpk[2][22][1]*s23));
        Vpk[2][23][1] = ((Vpk[2][22][1]*c23)-(Vpk[2][21][0]*s23));
        Vpk[2][23][2] = Vpk[2][22][2];
        Vpk[2][24][0] = ((Vpk[2][23][0]*c24)-(Vpk[2][22][2]*s24));
        Vpk[2][24][1] = Vpk[2][23][1];
        Vpk[2][24][2] = ((Vpk[2][22][2]*c24)+(Vpk[2][23][0]*s24));
        Vpk[2][25][0] = Cik[3][2][0];
        Vpk[2][25][1] = ((Cik[3][2][1]*c25)+(Cik[3][2][2]*s25));
        Vpk[2][25][2] = ((Cik[3][2][2]*c25)-(Cik[3][2][1]*s25));
        Vpk[2][26][0] = ((Cik[3][2][0]*c26)+(Vpk[2][25][1]*s26));
        Vpk[2][26][1] = ((Vpk[2][25][1]*c26)-(Cik[3][2][0]*s26));
        Vpk[2][26][2] = Vpk[2][25][2];
        Vpk[2][27][0] = ((Vpk[2][26][0]*c27)-(Vpk[2][25][2]*s27));
        Vpk[2][27][1] = Vpk[2][26][1];
        Vpk[2][27][2] = ((Vpk[2][25][2]*c27)+(Vpk[2][26][0]*s27));
        Vpk[2][28][0] = Vpk[2][27][0];
        Vpk[2][28][1] = ((Vpk[2][26][1]*c28)+(Vpk[2][27][2]*s28));
        Vpk[2][28][2] = ((Vpk[2][27][2]*c28)-(Vpk[2][26][1]*s28));
        Vpk[2][29][0] = Vpk[2][27][0];
        Vpk[2][29][1] = ((Vpk[2][28][1]*c29)+(Vpk[2][28][2]*s29));
        Vpk[2][29][2] = ((Vpk[2][28][2]*c29)-(Vpk[2][28][1]*s29));
        Vpk[2][30][0] = ((Vpk[2][27][0]*c30)+(Vpk[2][29][1]*s30));
        Vpk[2][30][1] = ((Vpk[2][29][1]*c30)-(Vpk[2][27][0]*s30));
        Vpk[2][30][2] = Vpk[2][29][2];
        Vpk[2][31][0] = Cik[3][2][0];
        Vpk[2][31][1] = ((Cik[3][2][1]*c31)+(Cik[3][2][2]*s31));
        Vpk[2][31][2] = ((Cik[3][2][2]*c31)-(Cik[3][2][1]*s31));
        Vpk[2][32][0] = ((Cik[3][2][0]*c32)+(Vpk[2][31][1]*s32));
        Vpk[2][32][1] = ((Vpk[2][31][1]*c32)-(Cik[3][2][0]*s32));
        Vpk[2][32][2] = Vpk[2][31][2];
        Vpk[2][33][0] = ((Vpk[2][32][0]*c33)-(Vpk[2][31][2]*s33));
        Vpk[2][33][1] = Vpk[2][32][1];
        Vpk[2][33][2] = ((Vpk[2][31][2]*c33)+(Vpk[2][32][0]*s33));
        Vpk[2][34][0] = Vpk[2][33][0];
        Vpk[2][34][1] = ((Vpk[2][32][1]*c34)+(Vpk[2][33][2]*s34));
        Vpk[2][34][2] = ((Vpk[2][33][2]*c34)-(Vpk[2][32][1]*s34));
        Vpk[2][35][0] = Vpk[2][33][0];
        Vpk[2][35][1] = ((Vpk[2][34][1]*c35)+(Vpk[2][34][2]*s35));
        Vpk[2][35][2] = ((Vpk[2][34][2]*c35)-(Vpk[2][34][1]*s35));
        Vpk[2][36][0] = ((Vpk[2][33][0]*c36)+(Vpk[2][35][1]*s36));
        Vpk[2][36][1] = ((Vpk[2][35][1]*c36)-(Vpk[2][33][0]*s36));
        Vpk[2][36][2] = Vpk[2][35][2];
        Vpk[3][5][1] = .05;
        Vpk[3][5][2] = -.1206;
        Vpk[3][8][0] = ((.0351*s7)-(.14625*Wpk[3][8][2]));
        Vpk[3][8][1] = (.0351*Wpk[3][8][0]);
        Vpk[3][8][2] = (.14625*Wpk[3][8][0]);
        VWri[3][9][0] = (Vpk[3][8][0]+((.0013*s7)-(.24635*Wpk[3][8][2])));
        Vpk[3][9][0] = VWri[3][9][0];
        Vpk[3][9][1] = ((.0364*(Wpk[3][8][0]*c9))+(.3926*(Wpk[3][8][0]*s9)));
        Vpk[3][9][2] = ((.3926*(Wpk[3][8][0]*c9))-(.0364*(Wpk[3][8][0]*s9)));
        Vpk[3][10][0] = ((Vpk[3][9][1]*s10)+(VWri[3][9][0]*c10));
        Vpk[3][10][1] = ((Vpk[3][9][1]*c10)-(VWri[3][9][0]*s10));
        Vpk[3][10][2] = Vpk[3][9][2];
        Vpk[3][11][0] = (((.0065*Wpk[3][10][1])-(.0442*Wpk[3][11][2]))+((
          Vpk[3][10][0]*c11)-(Vpk[3][9][2]*s11)));
        Vpk[3][11][1] = (Vpk[3][10][1]-(.0065*Wpk[3][11][0]));
        Vpk[3][11][2] = ((.0442*Wpk[3][11][0])+((Vpk[3][9][2]*c11)+(
          Vpk[3][10][0]*s11)));
        VWri[3][12][0] = (Vpk[3][11][0]+((.0065*Wpk[3][10][1])-(.0442*
          Wpk[3][11][2])));
        VWri[3][12][1] = (Vpk[3][11][1]-(.0065*Wpk[3][11][0]));
        VWri[3][12][2] = (Vpk[3][11][2]+(.0442*Wpk[3][11][0]));
        Vpk[3][12][0] = (VWri[3][12][0]+((.0312*Wpk[3][12][1])-(.078*
          Wpk[3][12][2])));
        Vpk[3][12][1] = (((VWri[3][12][1]*c12)+(VWri[3][12][2]*s12))-(.0312*
          Wpk[3][11][0]));
        Vpk[3][12][2] = ((.078*Wpk[3][11][0])+((VWri[3][12][2]*c12)-(
          VWri[3][12][1]*s12)));
        VWri[3][13][0] = (Vpk[3][8][0]-((.0013*s7)+(.18915*Wpk[3][8][2])));
        VWri[3][13][1] = ((.0351*Wpk[3][8][0])+((.1768*Wpk[3][8][2])-(.0013*
          Wpk[3][8][0])));
        VWri[3][13][2] = ((.14625*Wpk[3][8][0])+((.1768*s7)+(.18915*Wpk[3][8][0]
          )));
        Vpk[3][13][0] = ((VWri[3][13][0]*c13)+(VWri[3][13][1]*s13));
        Vpk[3][13][1] = ((VWri[3][13][1]*c13)-(VWri[3][13][0]*s13));
        Vpk[3][13][2] = VWri[3][13][2];
        Vpk[3][14][0] = ((.0013*Wpk[3][13][1])+((Vpk[3][13][0]*c14)-(
          VWri[3][13][2]*s14)));
        Vpk[3][14][1] = (Vpk[3][13][1]+((.1326*Wpk[3][14][2])-(.0013*
          Wpk[3][14][0])));
        Vpk[3][14][2] = (((Vpk[3][13][0]*s14)+(VWri[3][13][2]*c14))-(.1326*
          Wpk[3][13][1]));
        VWri[3][15][0] = (Vpk[3][14][0]+(.0013*Wpk[3][13][1]));
        VWri[3][15][1] = (Vpk[3][14][1]+((.1326*Wpk[3][14][2])-(.0013*
          Wpk[3][14][0])));
        VWri[3][15][2] = (Vpk[3][14][2]-(.1326*Wpk[3][13][1]));
        Vpk[3][15][0] = ((VWri[3][15][0]*c15)-(VWri[3][15][2]*s15));
        Vpk[3][15][1] = VWri[3][15][1];
        Vpk[3][15][2] = ((VWri[3][15][0]*s15)+(VWri[3][15][2]*c15));
        Vpk[3][16][0] = (Vpk[3][15][0]-(.0039*Wpk[3][16][2]));
        Vpk[3][16][1] = ((.1378*Wpk[3][16][2])+((Vpk[3][15][2]*s16)+(
          VWri[3][15][1]*c16)));
        Vpk[3][16][2] = (((.0039*Wpk[3][15][0])-(.1378*Wpk[3][16][1]))+((
          Vpk[3][15][2]*c16)-(VWri[3][15][1]*s16)));
        VWri[3][17][0] = (Vpk[3][16][0]-(.0039*Wpk[3][16][2]));
        VWri[3][17][1] = (Vpk[3][16][1]+(.1378*Wpk[3][16][2]));
        VWri[3][17][2] = (Vpk[3][16][2]+((.0039*Wpk[3][15][0])-(.1378*
          Wpk[3][16][1])));
        Vpk[3][17][0] = ((VWri[3][17][0]*c17)+(VWri[3][17][1]*s17));
        Vpk[3][17][1] = ((VWri[3][17][1]*c17)-(VWri[3][17][0]*s17));
        Vpk[3][17][2] = VWri[3][17][2];
        Vpk[3][18][0] = ((Vpk[3][17][0]*c18)-(VWri[3][17][2]*s18));
        Vpk[3][18][1] = (Vpk[3][17][1]+(.065*Wpk[3][18][2]));
        Vpk[3][18][2] = (((Vpk[3][17][0]*s18)+(VWri[3][17][2]*c18))-(.065*
          Wpk[3][17][1]));
        VWri[3][19][0] = (Vpk[3][8][0]-((.0013*s7)+(.18915*Wpk[3][8][2])));
        VWri[3][19][1] = ((.0351*Wpk[3][8][0])-((.0013*Wpk[3][8][0])+(.1768*
          Wpk[3][8][2])));
        VWri[3][19][2] = ((.14625*Wpk[3][8][0])+((.18915*Wpk[3][8][0])-(.1768*s7
          )));
        Vpk[3][19][0] = ((VWri[3][19][0]*c19)+(VWri[3][19][1]*s19));
        Vpk[3][19][1] = ((VWri[3][19][1]*c19)-(VWri[3][19][0]*s19));
        Vpk[3][19][2] = VWri[3][19][2];
        Vpk[3][20][0] = ((.0013*Wpk[3][19][1])+((Vpk[3][19][0]*c20)-(
          VWri[3][19][2]*s20)));
        Vpk[3][20][1] = (Vpk[3][19][1]-((.0013*Wpk[3][20][0])+(.1326*
          Wpk[3][20][2])));
        Vpk[3][20][2] = ((.1326*Wpk[3][19][1])+((Vpk[3][19][0]*s20)+(
          VWri[3][19][2]*c20)));
        VWri[3][21][0] = (Vpk[3][20][0]+(.0013*Wpk[3][19][1]));
        VWri[3][21][1] = (Vpk[3][20][1]-((.0013*Wpk[3][20][0])+(.1326*
          Wpk[3][20][2])));
        VWri[3][21][2] = (Vpk[3][20][2]+(.1326*Wpk[3][19][1]));
        Vpk[3][21][0] = ((VWri[3][21][0]*c21)-(VWri[3][21][2]*s21));
        Vpk[3][21][1] = VWri[3][21][1];
        Vpk[3][21][2] = ((VWri[3][21][0]*s21)+(VWri[3][21][2]*c21));
        Vpk[3][22][0] = (Vpk[3][21][0]-(.0039*Wpk[3][22][2]));
        Vpk[3][22][1] = (((Vpk[3][21][2]*s22)+(VWri[3][21][1]*c22))-(.1378*
          Wpk[3][22][2]));
        Vpk[3][22][2] = (((.0039*Wpk[3][21][0])+(.1378*Wpk[3][22][1]))+((
          Vpk[3][21][2]*c22)-(VWri[3][21][1]*s22)));
        VWri[3][23][0] = (Vpk[3][22][0]-(.0039*Wpk[3][22][2]));
        VWri[3][23][1] = (Vpk[3][22][1]-(.1378*Wpk[3][22][2]));
        VWri[3][23][2] = (Vpk[3][22][2]+((.0039*Wpk[3][21][0])+(.1378*
          Wpk[3][22][1])));
        Vpk[3][23][0] = ((VWri[3][23][0]*c23)+(VWri[3][23][1]*s23));
        Vpk[3][23][1] = ((VWri[3][23][1]*c23)-(VWri[3][23][0]*s23));
        Vpk[3][23][2] = VWri[3][23][2];
        Vpk[3][24][0] = ((Vpk[3][23][0]*c24)-(VWri[3][23][2]*s24));
        Vpk[3][24][1] = (Vpk[3][23][1]-(.065*Wpk[3][24][2]));
        Vpk[3][24][2] = ((.065*Wpk[3][23][1])+((Vpk[3][23][0]*s24)+(
          VWri[3][23][2]*c24)));
        Vpk[3][25][1] = ((.0442*c25)-(.1612*s25));
        Vpk[3][25][2] = -((.0442*s25)+(.1612*c25));
        Vpk[3][26][0] = (Vpk[3][25][1]*s26);
        Vpk[3][26][1] = (Vpk[3][25][1]*c26);
        Vpk[3][26][2] = Vpk[3][25][2];
        Vpk[3][27][0] = (((.2379*Wpk[3][27][2])-(.0143*s26))+((Vpk[3][26][0]*c27
          )-(Vpk[3][25][2]*s27)));
        Vpk[3][27][1] = (Vpk[3][26][1]-((.0143*Wpk[3][27][0])+(.0169*
          Wpk[3][27][2])));
        Vpk[3][27][2] = (((Vpk[3][25][2]*c27)+(Vpk[3][26][0]*s27))-((.0169*s26)+
          (.2379*Wpk[3][27][0])));
        VWri[3][28][0] = (Vpk[3][27][0]+((.2379*Wpk[3][27][2])-(.0143*s26)));
        VWri[3][28][1] = (Vpk[3][27][1]-((.0143*Wpk[3][27][0])+(.0169*
          Wpk[3][27][2])));
        VWri[3][28][2] = (Vpk[3][27][2]-((.0169*s26)+(.2379*Wpk[3][27][0])));
        Vpk[3][28][0] = (VWri[3][28][0]+((.2158*Wpk[3][28][2])-(.0039*
          Wpk[3][28][1])));
        Vpk[3][28][1] = (((.0039*Wpk[3][27][0])-(.0078*Wpk[3][28][2]))+((
          VWri[3][28][1]*c28)+(VWri[3][28][2]*s28)));
        Vpk[3][28][2] = (((.0078*Wpk[3][28][1])-(.2158*Wpk[3][27][0]))+((
          VWri[3][28][2]*c28)-(VWri[3][28][1]*s28)));
        VWri[3][29][0] = (Vpk[3][28][0]+((.2158*Wpk[3][28][2])-(.0039*
          Wpk[3][28][1])));
        VWri[3][29][1] = (Vpk[3][28][1]+((.0039*Wpk[3][27][0])-(.0078*
          Wpk[3][28][2])));
        VWri[3][29][2] = (Vpk[3][28][2]+((.0078*Wpk[3][28][1])-(.2158*
          Wpk[3][27][0])));
        Vpk[3][29][0] = VWri[3][29][0];
        Vpk[3][29][1] = ((VWri[3][29][1]*c29)+(VWri[3][29][2]*s29));
        Vpk[3][29][2] = ((VWri[3][29][2]*c29)-(VWri[3][29][1]*s29));
        Vpk[3][30][0] = (((.039*Wpk[3][30][1])+(.0442*Wpk[3][29][2]))+((
          Vpk[3][29][1]*s30)+(VWri[3][29][0]*c30)));
        Vpk[3][30][1] = (((Vpk[3][29][1]*c30)-(VWri[3][29][0]*s30))-(.039*
          Wpk[3][30][0]));
        Vpk[3][30][2] = (Vpk[3][29][2]-(.0442*Wpk[3][30][0]));
        Vpk[3][31][1] = ((.0442*c31)-(.1612*s31));
        Vpk[3][31][2] = -((.0442*s31)+(.1612*c31));
        Vpk[3][32][0] = (Vpk[3][31][1]*s32);
        Vpk[3][32][1] = (Vpk[3][31][1]*c32);
        Vpk[3][32][2] = Vpk[3][31][2];
        Vpk[3][33][0] = (((.2379*Wpk[3][33][2])-(.0143*s32))+((Vpk[3][32][0]*c33
          )-(Vpk[3][31][2]*s33)));
        Vpk[3][33][1] = (Vpk[3][32][1]+((.0169*Wpk[3][33][2])-(.0143*
          Wpk[3][33][0])));
        Vpk[3][33][2] = (((.0169*s32)-(.2379*Wpk[3][33][0]))+((Vpk[3][31][2]*c33
          )+(Vpk[3][32][0]*s33)));
        VWri[3][34][0] = (Vpk[3][33][0]+((.2379*Wpk[3][33][2])-(.0143*s32)));
        VWri[3][34][1] = (Vpk[3][33][1]+((.0169*Wpk[3][33][2])-(.0143*
          Wpk[3][33][0])));
        VWri[3][34][2] = (Vpk[3][33][2]+((.0169*s32)-(.2379*Wpk[3][33][0])));
        Vpk[3][34][0] = (VWri[3][34][0]+((.2158*Wpk[3][34][2])-(.0039*
          Wpk[3][34][1])));
        Vpk[3][34][1] = (((.0039*Wpk[3][33][0])+(.0078*Wpk[3][34][2]))+((
          VWri[3][34][1]*c34)+(VWri[3][34][2]*s34)));
        Vpk[3][34][2] = (((VWri[3][34][2]*c34)-(VWri[3][34][1]*s34))-((.0078*
          Wpk[3][34][1])+(.2158*Wpk[3][33][0])));
        VWri[3][35][0] = (Vpk[3][34][0]+((.2158*Wpk[3][34][2])-(.0039*
          Wpk[3][34][1])));
        VWri[3][35][1] = (Vpk[3][34][1]+((.0039*Wpk[3][33][0])+(.0078*
          Wpk[3][34][2])));
        VWri[3][35][2] = (Vpk[3][34][2]-((.0078*Wpk[3][34][1])+(.2158*
          Wpk[3][33][0])));
        Vpk[3][35][0] = VWri[3][35][0];
        Vpk[3][35][1] = ((VWri[3][35][1]*c35)+(VWri[3][35][2]*s35));
        Vpk[3][35][2] = ((VWri[3][35][2]*c35)-(VWri[3][35][1]*s35));
        Vpk[3][36][0] = (((.039*Wpk[3][36][1])+(.0442*Wpk[3][35][2]))+((
          Vpk[3][35][1]*s36)+(VWri[3][35][0]*c36)));
        Vpk[3][36][1] = (((Vpk[3][35][1]*c36)-(VWri[3][35][0]*s36))-(.039*
          Wpk[3][36][0]));
        Vpk[3][36][2] = (Vpk[3][35][2]-(.0442*Wpk[3][36][0]));
        Vpk[4][5][0] = -.05;
        Vpk[4][8][0] = -((.0351*Wpk[4][7][1])+(.14625*Wpk[4][8][2]));
        Vpk[4][8][1] = (.0351*Wpk[4][8][0]);
        Vpk[4][8][2] = (.14625*Wpk[4][8][0]);
        VWri[4][9][0] = (Vpk[4][8][0]-((.0013*Wpk[4][7][1])+(.24635*Wpk[4][8][2]
          )));
        Vpk[4][9][0] = VWri[4][9][0];
        Vpk[4][9][1] = ((.0364*(Wpk[4][8][0]*c9))+(.3926*(Wpk[4][8][0]*s9)));
        Vpk[4][9][2] = ((.3926*(Wpk[4][8][0]*c9))-(.0364*(Wpk[4][8][0]*s9)));
        Vpk[4][10][0] = ((Vpk[4][9][1]*s10)+(VWri[4][9][0]*c10));
        Vpk[4][10][1] = ((Vpk[4][9][1]*c10)-(VWri[4][9][0]*s10));
        Vpk[4][10][2] = Vpk[4][9][2];
        Vpk[4][11][0] = (((.0065*Wpk[4][10][1])-(.0442*Wpk[4][11][2]))+((
          Vpk[4][10][0]*c11)-(Vpk[4][9][2]*s11)));
        Vpk[4][11][1] = (Vpk[4][10][1]-(.0065*Wpk[4][11][0]));
        Vpk[4][11][2] = ((.0442*Wpk[4][11][0])+((Vpk[4][9][2]*c11)+(
          Vpk[4][10][0]*s11)));
        VWri[4][12][0] = (Vpk[4][11][0]+((.0065*Wpk[4][10][1])-(.0442*
          Wpk[4][11][2])));
        VWri[4][12][1] = (Vpk[4][11][1]-(.0065*Wpk[4][11][0]));
        VWri[4][12][2] = (Vpk[4][11][2]+(.0442*Wpk[4][11][0]));
        Vpk[4][12][0] = (VWri[4][12][0]+((.0312*Wpk[4][12][1])-(.078*
          Wpk[4][12][2])));
        Vpk[4][12][1] = (((VWri[4][12][1]*c12)+(VWri[4][12][2]*s12))-(.0312*
          Wpk[4][11][0]));
        Vpk[4][12][2] = ((.078*Wpk[4][11][0])+((VWri[4][12][2]*c12)-(
          VWri[4][12][1]*s12)));
        VWri[4][13][0] = (Vpk[4][8][0]+((.0013*Wpk[4][7][1])-(.18915*
          Wpk[4][8][2])));
        VWri[4][13][1] = ((.0351*Wpk[4][8][0])+((.1768*Wpk[4][8][2])-(.0013*
          Wpk[4][8][0])));
        VWri[4][13][2] = ((.14625*Wpk[4][8][0])+((.18915*Wpk[4][8][0])-(.1768*
          Wpk[4][7][1])));
        Vpk[4][13][0] = ((VWri[4][13][0]*c13)+(VWri[4][13][1]*s13));
        Vpk[4][13][1] = ((VWri[4][13][1]*c13)-(VWri[4][13][0]*s13));
        Vpk[4][13][2] = VWri[4][13][2];
        Vpk[4][14][0] = ((.0013*Wpk[4][13][1])+((Vpk[4][13][0]*c14)-(
          VWri[4][13][2]*s14)));
        Vpk[4][14][1] = (Vpk[4][13][1]+((.1326*Wpk[4][14][2])-(.0013*
          Wpk[4][14][0])));
        Vpk[4][14][2] = (((Vpk[4][13][0]*s14)+(VWri[4][13][2]*c14))-(.1326*
          Wpk[4][13][1]));
        VWri[4][15][0] = (Vpk[4][14][0]+(.0013*Wpk[4][13][1]));
        VWri[4][15][1] = (Vpk[4][14][1]+((.1326*Wpk[4][14][2])-(.0013*
          Wpk[4][14][0])));
        VWri[4][15][2] = (Vpk[4][14][2]-(.1326*Wpk[4][13][1]));
        Vpk[4][15][0] = ((VWri[4][15][0]*c15)-(VWri[4][15][2]*s15));
        Vpk[4][15][1] = VWri[4][15][1];
        Vpk[4][15][2] = ((VWri[4][15][0]*s15)+(VWri[4][15][2]*c15));
        Vpk[4][16][0] = (Vpk[4][15][0]-(.0039*Wpk[4][16][2]));
        Vpk[4][16][1] = ((.1378*Wpk[4][16][2])+((Vpk[4][15][2]*s16)+(
          VWri[4][15][1]*c16)));
        Vpk[4][16][2] = (((.0039*Wpk[4][15][0])-(.1378*Wpk[4][16][1]))+((
          Vpk[4][15][2]*c16)-(VWri[4][15][1]*s16)));
        VWri[4][17][0] = (Vpk[4][16][0]-(.0039*Wpk[4][16][2]));
        VWri[4][17][1] = (Vpk[4][16][1]+(.1378*Wpk[4][16][2]));
        VWri[4][17][2] = (Vpk[4][16][2]+((.0039*Wpk[4][15][0])-(.1378*
          Wpk[4][16][1])));
        Vpk[4][17][0] = ((VWri[4][17][0]*c17)+(VWri[4][17][1]*s17));
        Vpk[4][17][1] = ((VWri[4][17][1]*c17)-(VWri[4][17][0]*s17));
        Vpk[4][17][2] = VWri[4][17][2];
        Vpk[4][18][0] = ((Vpk[4][17][0]*c18)-(VWri[4][17][2]*s18));
        Vpk[4][18][1] = (Vpk[4][17][1]+(.065*Wpk[4][18][2]));
        Vpk[4][18][2] = (((Vpk[4][17][0]*s18)+(VWri[4][17][2]*c18))-(.065*
          Wpk[4][17][1]));
        VWri[4][19][0] = (Vpk[4][8][0]+((.0013*Wpk[4][7][1])-(.18915*
          Wpk[4][8][2])));
        VWri[4][19][1] = ((.0351*Wpk[4][8][0])-((.0013*Wpk[4][8][0])+(.1768*
          Wpk[4][8][2])));
        VWri[4][19][2] = ((.14625*Wpk[4][8][0])+((.1768*Wpk[4][7][1])+(.18915*
          Wpk[4][8][0])));
        Vpk[4][19][0] = ((VWri[4][19][0]*c19)+(VWri[4][19][1]*s19));
        Vpk[4][19][1] = ((VWri[4][19][1]*c19)-(VWri[4][19][0]*s19));
        Vpk[4][19][2] = VWri[4][19][2];
        Vpk[4][20][0] = ((.0013*Wpk[4][19][1])+((Vpk[4][19][0]*c20)-(
          VWri[4][19][2]*s20)));
        Vpk[4][20][1] = (Vpk[4][19][1]-((.0013*Wpk[4][20][0])+(.1326*
          Wpk[4][20][2])));
        Vpk[4][20][2] = ((.1326*Wpk[4][19][1])+((Vpk[4][19][0]*s20)+(
          VWri[4][19][2]*c20)));
        VWri[4][21][0] = (Vpk[4][20][0]+(.0013*Wpk[4][19][1]));
        VWri[4][21][1] = (Vpk[4][20][1]-((.0013*Wpk[4][20][0])+(.1326*
          Wpk[4][20][2])));
        VWri[4][21][2] = (Vpk[4][20][2]+(.1326*Wpk[4][19][1]));
        Vpk[4][21][0] = ((VWri[4][21][0]*c21)-(VWri[4][21][2]*s21));
        Vpk[4][21][1] = VWri[4][21][1];
        Vpk[4][21][2] = ((VWri[4][21][0]*s21)+(VWri[4][21][2]*c21));
        Vpk[4][22][0] = (Vpk[4][21][0]-(.0039*Wpk[4][22][2]));
        Vpk[4][22][1] = (((Vpk[4][21][2]*s22)+(VWri[4][21][1]*c22))-(.1378*
          Wpk[4][22][2]));
        Vpk[4][22][2] = (((.0039*Wpk[4][21][0])+(.1378*Wpk[4][22][1]))+((
          Vpk[4][21][2]*c22)-(VWri[4][21][1]*s22)));
        VWri[4][23][0] = (Vpk[4][22][0]-(.0039*Wpk[4][22][2]));
        VWri[4][23][1] = (Vpk[4][22][1]-(.1378*Wpk[4][22][2]));
        VWri[4][23][2] = (Vpk[4][22][2]+((.0039*Wpk[4][21][0])+(.1378*
          Wpk[4][22][1])));
        Vpk[4][23][0] = ((VWri[4][23][0]*c23)+(VWri[4][23][1]*s23));
        Vpk[4][23][1] = ((VWri[4][23][1]*c23)-(VWri[4][23][0]*s23));
        Vpk[4][23][2] = VWri[4][23][2];
        Vpk[4][24][0] = ((Vpk[4][23][0]*c24)-(VWri[4][23][2]*s24));
        Vpk[4][24][1] = (Vpk[4][23][1]-(.065*Wpk[4][24][2]));
        Vpk[4][24][2] = ((.065*Wpk[4][23][1])+((Vpk[4][23][0]*s24)+(
          VWri[4][23][2]*c24)));
        Vpk[4][25][0] = -.0442;
        Vpk[4][25][1] = -(.1118*s25);
        Vpk[4][25][2] = -(.1118*c25);
        Vpk[4][26][0] = -((.0442*c26)+(.1118*(s25*s26)));
        Vpk[4][26][1] = ((.0442*s26)-(.1118*(s25*c26)));
        Vpk[4][26][2] = -(.1118*c25);
        Vpk[4][27][0] = (((.0143*Wpk[4][26][1])+(.2379*Wpk[4][27][2]))+((.1118*(
          s27*c25))+(Vpk[4][26][0]*c27)));
        Vpk[4][27][1] = (Vpk[4][26][1]-((.0143*Wpk[4][27][0])+(.0169*
          Wpk[4][27][2])));
        Vpk[4][27][2] = (((.0169*Wpk[4][26][1])-(.2379*Wpk[4][27][0]))+((
          Vpk[4][26][0]*s27)-(.1118*(c25*c27))));
        VWri[4][28][0] = (Vpk[4][27][0]+((.0143*Wpk[4][26][1])+(.2379*
          Wpk[4][27][2])));
        VWri[4][28][1] = (Vpk[4][27][1]-((.0143*Wpk[4][27][0])+(.0169*
          Wpk[4][27][2])));
        VWri[4][28][2] = (Vpk[4][27][2]+((.0169*Wpk[4][26][1])-(.2379*
          Wpk[4][27][0])));
        Vpk[4][28][0] = (VWri[4][28][0]+((.2158*Wpk[4][28][2])-(.0039*
          Wpk[4][28][1])));
        Vpk[4][28][1] = (((.0039*Wpk[4][27][0])-(.0078*Wpk[4][28][2]))+((
          VWri[4][28][1]*c28)+(VWri[4][28][2]*s28)));
        Vpk[4][28][2] = (((.0078*Wpk[4][28][1])-(.2158*Wpk[4][27][0]))+((
          VWri[4][28][2]*c28)-(VWri[4][28][1]*s28)));
        VWri[4][29][0] = (Vpk[4][28][0]+((.2158*Wpk[4][28][2])-(.0039*
          Wpk[4][28][1])));
        VWri[4][29][1] = (Vpk[4][28][1]+((.0039*Wpk[4][27][0])-(.0078*
          Wpk[4][28][2])));
        VWri[4][29][2] = (Vpk[4][28][2]+((.0078*Wpk[4][28][1])-(.2158*
          Wpk[4][27][0])));
        Vpk[4][29][0] = VWri[4][29][0];
        Vpk[4][29][1] = ((VWri[4][29][1]*c29)+(VWri[4][29][2]*s29));
        Vpk[4][29][2] = ((VWri[4][29][2]*c29)-(VWri[4][29][1]*s29));
        Vpk[4][30][0] = (((.039*Wpk[4][30][1])+(.0442*Wpk[4][29][2]))+((
          Vpk[4][29][1]*s30)+(VWri[4][29][0]*c30)));
        Vpk[4][30][1] = (((Vpk[4][29][1]*c30)-(VWri[4][29][0]*s30))-(.039*
          Wpk[4][30][0]));
        Vpk[4][30][2] = (Vpk[4][29][2]-(.0442*Wpk[4][30][0]));
        Vpk[4][31][0] = -.0442;
        Vpk[4][31][1] = (.1118*s31);
        Vpk[4][31][2] = (.1118*c31);
        Vpk[4][32][0] = ((.1118*(s31*s32))-(.0442*c32));
        Vpk[4][32][1] = ((.0442*s32)+(.1118*(s31*c32)));
        Vpk[4][32][2] = (.1118*c31);
        Vpk[4][33][0] = (((.0143*Wpk[4][32][1])+(.2379*Wpk[4][33][2]))+((
          Vpk[4][32][0]*c33)-(.1118*(s33*c31))));
        Vpk[4][33][1] = (Vpk[4][32][1]+((.0169*Wpk[4][33][2])-(.0143*
          Wpk[4][33][0])));
        Vpk[4][33][2] = (((.1118*(c31*c33))+(Vpk[4][32][0]*s33))-((.0169*
          Wpk[4][32][1])+(.2379*Wpk[4][33][0])));
        VWri[4][34][0] = (Vpk[4][33][0]+((.0143*Wpk[4][32][1])+(.2379*
          Wpk[4][33][2])));
        VWri[4][34][1] = (Vpk[4][33][1]+((.0169*Wpk[4][33][2])-(.0143*
          Wpk[4][33][0])));
        VWri[4][34][2] = (Vpk[4][33][2]-((.0169*Wpk[4][32][1])+(.2379*
          Wpk[4][33][0])));
        Vpk[4][34][0] = (VWri[4][34][0]+((.2158*Wpk[4][34][2])-(.0039*
          Wpk[4][34][1])));
        Vpk[4][34][1] = (((.0039*Wpk[4][33][0])+(.0078*Wpk[4][34][2]))+((
          VWri[4][34][1]*c34)+(VWri[4][34][2]*s34)));
        Vpk[4][34][2] = (((VWri[4][34][2]*c34)-(VWri[4][34][1]*s34))-((.0078*
          Wpk[4][34][1])+(.2158*Wpk[4][33][0])));
        VWri[4][35][0] = (Vpk[4][34][0]+((.2158*Wpk[4][34][2])-(.0039*
          Wpk[4][34][1])));
        VWri[4][35][1] = (Vpk[4][34][1]+((.0039*Wpk[4][33][0])+(.0078*
          Wpk[4][34][2])));
        VWri[4][35][2] = (Vpk[4][34][2]-((.0078*Wpk[4][34][1])+(.2158*
          Wpk[4][33][0])));
        Vpk[4][35][0] = VWri[4][35][0];
        Vpk[4][35][1] = ((VWri[4][35][1]*c35)+(VWri[4][35][2]*s35));
        Vpk[4][35][2] = ((VWri[4][35][2]*c35)-(VWri[4][35][1]*s35));
        Vpk[4][36][0] = (((.039*Wpk[4][36][1])+(.0442*Wpk[4][35][2]))+((
          Vpk[4][35][1]*s36)+(VWri[4][35][0]*c36)));
        Vpk[4][36][1] = (((Vpk[4][35][1]*c36)-(VWri[4][35][0]*s36))-(.039*
          Wpk[4][36][0]));
        Vpk[4][36][2] = (Vpk[4][35][2]-(.0442*Wpk[4][36][0]));
        Vpk[5][5][0] = .1206;
        Vpk[5][8][0] = -((.0351*Wpk[5][7][1])+(.14625*Wpk[5][8][2]));
        Vpk[5][8][1] = (.0351*Wpk[5][8][0]);
        Vpk[5][8][2] = (.14625*Wpk[5][8][0]);
        VWri[5][9][0] = (Vpk[5][8][0]-((.0013*Wpk[5][7][1])+(.24635*Wpk[5][8][2]
          )));
        Vpk[5][9][0] = VWri[5][9][0];
        Vpk[5][9][1] = ((.0364*(Wpk[5][8][0]*c9))+(.3926*(Wpk[5][8][0]*s9)));
        Vpk[5][9][2] = ((.3926*(Wpk[5][8][0]*c9))-(.0364*(Wpk[5][8][0]*s9)));
        Vpk[5][10][0] = ((Vpk[5][9][1]*s10)+(VWri[5][9][0]*c10));
        Vpk[5][10][1] = ((Vpk[5][9][1]*c10)-(VWri[5][9][0]*s10));
        Vpk[5][10][2] = Vpk[5][9][2];
        Vpk[5][11][0] = (((.0065*Wpk[5][10][1])-(.0442*Wpk[5][11][2]))+((
          Vpk[5][10][0]*c11)-(Vpk[5][9][2]*s11)));
        Vpk[5][11][1] = (Vpk[5][10][1]-(.0065*Wpk[5][11][0]));
        Vpk[5][11][2] = ((.0442*Wpk[5][11][0])+((Vpk[5][9][2]*c11)+(
          Vpk[5][10][0]*s11)));
        VWri[5][12][0] = (Vpk[5][11][0]+((.0065*Wpk[5][10][1])-(.0442*
          Wpk[5][11][2])));
        VWri[5][12][1] = (Vpk[5][11][1]-(.0065*Wpk[5][11][0]));
        VWri[5][12][2] = (Vpk[5][11][2]+(.0442*Wpk[5][11][0]));
        Vpk[5][12][0] = (VWri[5][12][0]+((.0312*Wpk[5][12][1])-(.078*
          Wpk[5][12][2])));
        Vpk[5][12][1] = (((VWri[5][12][1]*c12)+(VWri[5][12][2]*s12))-(.0312*
          Wpk[5][11][0]));
        Vpk[5][12][2] = ((.078*Wpk[5][11][0])+((VWri[5][12][2]*c12)-(
          VWri[5][12][1]*s12)));
        VWri[5][13][0] = (Vpk[5][8][0]+((.0013*Wpk[5][7][1])-(.18915*
          Wpk[5][8][2])));
        VWri[5][13][1] = ((.0351*Wpk[5][8][0])+((.1768*Wpk[5][8][2])-(.0013*
          Wpk[5][8][0])));
        VWri[5][13][2] = ((.14625*Wpk[5][8][0])+((.18915*Wpk[5][8][0])-(.1768*
          Wpk[5][7][1])));
        Vpk[5][13][0] = ((VWri[5][13][0]*c13)+(VWri[5][13][1]*s13));
        Vpk[5][13][1] = ((VWri[5][13][1]*c13)-(VWri[5][13][0]*s13));
        Vpk[5][13][2] = VWri[5][13][2];
        Vpk[5][14][0] = ((.0013*Wpk[5][13][1])+((Vpk[5][13][0]*c14)-(
          VWri[5][13][2]*s14)));
        Vpk[5][14][1] = (Vpk[5][13][1]+((.1326*Wpk[5][14][2])-(.0013*
          Wpk[5][14][0])));
        Vpk[5][14][2] = (((Vpk[5][13][0]*s14)+(VWri[5][13][2]*c14))-(.1326*
          Wpk[5][13][1]));
        VWri[5][15][0] = (Vpk[5][14][0]+(.0013*Wpk[5][13][1]));
        VWri[5][15][1] = (Vpk[5][14][1]+((.1326*Wpk[5][14][2])-(.0013*
          Wpk[5][14][0])));
        VWri[5][15][2] = (Vpk[5][14][2]-(.1326*Wpk[5][13][1]));
        Vpk[5][15][0] = ((VWri[5][15][0]*c15)-(VWri[5][15][2]*s15));
        Vpk[5][15][1] = VWri[5][15][1];
        Vpk[5][15][2] = ((VWri[5][15][0]*s15)+(VWri[5][15][2]*c15));
        Vpk[5][16][0] = (Vpk[5][15][0]-(.0039*Wpk[5][16][2]));
        Vpk[5][16][1] = ((.1378*Wpk[5][16][2])+((Vpk[5][15][2]*s16)+(
          VWri[5][15][1]*c16)));
        Vpk[5][16][2] = (((.0039*Wpk[5][15][0])-(.1378*Wpk[5][16][1]))+((
          Vpk[5][15][2]*c16)-(VWri[5][15][1]*s16)));
        VWri[5][17][0] = (Vpk[5][16][0]-(.0039*Wpk[5][16][2]));
        VWri[5][17][1] = (Vpk[5][16][1]+(.1378*Wpk[5][16][2]));
        VWri[5][17][2] = (Vpk[5][16][2]+((.0039*Wpk[5][15][0])-(.1378*
          Wpk[5][16][1])));
        Vpk[5][17][0] = ((VWri[5][17][0]*c17)+(VWri[5][17][1]*s17));
        Vpk[5][17][1] = ((VWri[5][17][1]*c17)-(VWri[5][17][0]*s17));
        Vpk[5][17][2] = VWri[5][17][2];
        Vpk[5][18][0] = ((Vpk[5][17][0]*c18)-(VWri[5][17][2]*s18));
        Vpk[5][18][1] = (Vpk[5][17][1]+(.065*Wpk[5][18][2]));
        Vpk[5][18][2] = (((Vpk[5][17][0]*s18)+(VWri[5][17][2]*c18))-(.065*
          Wpk[5][17][1]));
        VWri[5][19][0] = (Vpk[5][8][0]+((.0013*Wpk[5][7][1])-(.18915*
          Wpk[5][8][2])));
        VWri[5][19][1] = ((.0351*Wpk[5][8][0])-((.0013*Wpk[5][8][0])+(.1768*
          Wpk[5][8][2])));
        VWri[5][19][2] = ((.14625*Wpk[5][8][0])+((.1768*Wpk[5][7][1])+(.18915*
          Wpk[5][8][0])));
        Vpk[5][19][0] = ((VWri[5][19][0]*c19)+(VWri[5][19][1]*s19));
        Vpk[5][19][1] = ((VWri[5][19][1]*c19)-(VWri[5][19][0]*s19));
        Vpk[5][19][2] = VWri[5][19][2];
        Vpk[5][20][0] = ((.0013*Wpk[5][19][1])+((Vpk[5][19][0]*c20)-(
          VWri[5][19][2]*s20)));
        Vpk[5][20][1] = (Vpk[5][19][1]-((.0013*Wpk[5][20][0])+(.1326*
          Wpk[5][20][2])));
        Vpk[5][20][2] = ((.1326*Wpk[5][19][1])+((Vpk[5][19][0]*s20)+(
          VWri[5][19][2]*c20)));
        VWri[5][21][0] = (Vpk[5][20][0]+(.0013*Wpk[5][19][1]));
        VWri[5][21][1] = (Vpk[5][20][1]-((.0013*Wpk[5][20][0])+(.1326*
          Wpk[5][20][2])));
        VWri[5][21][2] = (Vpk[5][20][2]+(.1326*Wpk[5][19][1]));
        Vpk[5][21][0] = ((VWri[5][21][0]*c21)-(VWri[5][21][2]*s21));
        Vpk[5][21][1] = VWri[5][21][1];
        Vpk[5][21][2] = ((VWri[5][21][0]*s21)+(VWri[5][21][2]*c21));
        Vpk[5][22][0] = (Vpk[5][21][0]-(.0039*Wpk[5][22][2]));
        Vpk[5][22][1] = (((Vpk[5][21][2]*s22)+(VWri[5][21][1]*c22))-(.1378*
          Wpk[5][22][2]));
        Vpk[5][22][2] = (((.0039*Wpk[5][21][0])+(.1378*Wpk[5][22][1]))+((
          Vpk[5][21][2]*c22)-(VWri[5][21][1]*s22)));
        VWri[5][23][0] = (Vpk[5][22][0]-(.0039*Wpk[5][22][2]));
        VWri[5][23][1] = (Vpk[5][22][1]-(.1378*Wpk[5][22][2]));
        VWri[5][23][2] = (Vpk[5][22][2]+((.0039*Wpk[5][21][0])+(.1378*
          Wpk[5][22][1])));
        Vpk[5][23][0] = ((VWri[5][23][0]*c23)+(VWri[5][23][1]*s23));
        Vpk[5][23][1] = ((VWri[5][23][1]*c23)-(VWri[5][23][0]*s23));
        Vpk[5][23][2] = VWri[5][23][2];
        Vpk[5][24][0] = ((Vpk[5][23][0]*c24)-(VWri[5][23][2]*s24));
        Vpk[5][24][1] = (Vpk[5][23][1]-(.065*Wpk[5][24][2]));
        Vpk[5][24][2] = ((.065*Wpk[5][23][1])+((Vpk[5][23][0]*s24)+(
          VWri[5][23][2]*c24)));
        Vpk[5][25][0] = .1612;
        Vpk[5][25][1] = (.1118*c25);
        Vpk[5][25][2] = -(.1118*s25);
        Vpk[5][26][0] = ((.1118*(s26*c25))+(.1612*c26));
        Vpk[5][26][1] = ((.1118*(c25*c26))-(.1612*s26));
        Vpk[5][26][2] = -(.1118*s25);
        Vpk[5][27][0] = (((.0143*Wpk[5][26][1])+(.2379*Wpk[5][27][2]))+((.1118*(
          s25*s27))+(Vpk[5][26][0]*c27)));
        Vpk[5][27][1] = (Vpk[5][26][1]-((.0143*Wpk[5][27][0])+(.0169*
          Wpk[5][27][2])));
        Vpk[5][27][2] = (((.0169*Wpk[5][26][1])-(.2379*Wpk[5][27][0]))+((
          Vpk[5][26][0]*s27)-(.1118*(s25*c27))));
        VWri[5][28][0] = (Vpk[5][27][0]+((.0143*Wpk[5][26][1])+(.2379*
          Wpk[5][27][2])));
        VWri[5][28][1] = (Vpk[5][27][1]-((.0143*Wpk[5][27][0])+(.0169*
          Wpk[5][27][2])));
        VWri[5][28][2] = (Vpk[5][27][2]+((.0169*Wpk[5][26][1])-(.2379*
          Wpk[5][27][0])));
        Vpk[5][28][0] = (VWri[5][28][0]+((.2158*Wpk[5][28][2])-(.0039*
          Wpk[5][28][1])));
        Vpk[5][28][1] = (((.0039*Wpk[5][27][0])-(.0078*Wpk[5][28][2]))+((
          VWri[5][28][1]*c28)+(VWri[5][28][2]*s28)));
        Vpk[5][28][2] = (((.0078*Wpk[5][28][1])-(.2158*Wpk[5][27][0]))+((
          VWri[5][28][2]*c28)-(VWri[5][28][1]*s28)));
        VWri[5][29][0] = (Vpk[5][28][0]+((.2158*Wpk[5][28][2])-(.0039*
          Wpk[5][28][1])));
        VWri[5][29][1] = (Vpk[5][28][1]+((.0039*Wpk[5][27][0])-(.0078*
          Wpk[5][28][2])));
        VWri[5][29][2] = (Vpk[5][28][2]+((.0078*Wpk[5][28][1])-(.2158*
          Wpk[5][27][0])));
        Vpk[5][29][0] = VWri[5][29][0];
        Vpk[5][29][1] = ((VWri[5][29][1]*c29)+(VWri[5][29][2]*s29));
        Vpk[5][29][2] = ((VWri[5][29][2]*c29)-(VWri[5][29][1]*s29));
        Vpk[5][30][0] = (((.039*Wpk[5][30][1])+(.0442*Wpk[5][29][2]))+((
          Vpk[5][29][1]*s30)+(VWri[5][29][0]*c30)));
        Vpk[5][30][1] = (((Vpk[5][29][1]*c30)-(VWri[5][29][0]*s30))-(.039*
          Wpk[5][30][0]));
        Vpk[5][30][2] = (Vpk[5][29][2]-(.0442*Wpk[5][30][0]));
        Vpk[5][31][0] = .1612;
        Vpk[5][31][1] = -(.1118*c31);
        Vpk[5][31][2] = (.1118*s31);
        Vpk[5][32][0] = ((.1612*c32)-(.1118*(s32*c31)));
        Vpk[5][32][1] = -((.1118*(c31*c32))+(.1612*s32));
        Vpk[5][32][2] = (.1118*s31);
        Vpk[5][33][0] = (((.0143*Wpk[5][32][1])+(.2379*Wpk[5][33][2]))+((
          Vpk[5][32][0]*c33)-(.1118*(s31*s33))));
        Vpk[5][33][1] = (Vpk[5][32][1]+((.0169*Wpk[5][33][2])-(.0143*
          Wpk[5][33][0])));
        Vpk[5][33][2] = (((.1118*(s31*c33))+(Vpk[5][32][0]*s33))-((.0169*
          Wpk[5][32][1])+(.2379*Wpk[5][33][0])));
        VWri[5][34][0] = (Vpk[5][33][0]+((.0143*Wpk[5][32][1])+(.2379*
          Wpk[5][33][2])));
        VWri[5][34][1] = (Vpk[5][33][1]+((.0169*Wpk[5][33][2])-(.0143*
          Wpk[5][33][0])));
        VWri[5][34][2] = (Vpk[5][33][2]-((.0169*Wpk[5][32][1])+(.2379*
          Wpk[5][33][0])));
        Vpk[5][34][0] = (VWri[5][34][0]+((.2158*Wpk[5][34][2])-(.0039*
          Wpk[5][34][1])));
        Vpk[5][34][1] = (((.0039*Wpk[5][33][0])+(.0078*Wpk[5][34][2]))+((
          VWri[5][34][1]*c34)+(VWri[5][34][2]*s34)));
        Vpk[5][34][2] = (((VWri[5][34][2]*c34)-(VWri[5][34][1]*s34))-((.0078*
          Wpk[5][34][1])+(.2158*Wpk[5][33][0])));
        VWri[5][35][0] = (Vpk[5][34][0]+((.2158*Wpk[5][34][2])-(.0039*
          Wpk[5][34][1])));
        VWri[5][35][1] = (Vpk[5][34][1]+((.0039*Wpk[5][33][0])+(.0078*
          Wpk[5][34][2])));
        VWri[5][35][2] = (Vpk[5][34][2]-((.0078*Wpk[5][34][1])+(.2158*
          Wpk[5][33][0])));
        Vpk[5][35][0] = VWri[5][35][0];
        Vpk[5][35][1] = ((VWri[5][35][1]*c35)+(VWri[5][35][2]*s35));
        Vpk[5][35][2] = ((VWri[5][35][2]*c35)-(VWri[5][35][1]*s35));
        Vpk[5][36][0] = (((.039*Wpk[5][36][1])+(.0442*Wpk[5][35][2]))+((
          Vpk[5][35][1]*s36)+(VWri[5][35][0]*c36)));
        Vpk[5][36][1] = (((Vpk[5][35][1]*c36)-(VWri[5][35][0]*s36))-(.039*
          Wpk[5][36][0]));
        Vpk[5][36][2] = (Vpk[5][35][2]-(.0442*Wpk[5][36][0]));
        Vpk[6][8][0] = ((.0351*s7)-(.14625*Wpk[6][8][2]));
        Vpk[6][8][1] = (.0351*Wpk[6][8][0]);
        Vpk[6][8][2] = (.14625*Wpk[6][8][0]);
        VWri[6][9][0] = (Vpk[6][8][0]+((.0013*s7)-(.24635*Wpk[6][8][2])));
        Vpk[6][9][0] = VWri[6][9][0];
        Vpk[6][9][1] = ((.0364*(Wpk[6][8][0]*c9))+(.3926*(Wpk[6][8][0]*s9)));
        Vpk[6][9][2] = ((.3926*(Wpk[6][8][0]*c9))-(.0364*(Wpk[6][8][0]*s9)));
        Vpk[6][10][0] = ((Vpk[6][9][1]*s10)+(VWri[6][9][0]*c10));
        Vpk[6][10][1] = ((Vpk[6][9][1]*c10)-(VWri[6][9][0]*s10));
        Vpk[6][10][2] = Vpk[6][9][2];
        Vpk[6][11][0] = (((.0065*Wpk[6][10][1])-(.0442*Wpk[6][11][2]))+((
          Vpk[6][10][0]*c11)-(Vpk[6][9][2]*s11)));
        Vpk[6][11][1] = (Vpk[6][10][1]-(.0065*Wpk[6][11][0]));
        Vpk[6][11][2] = ((.0442*Wpk[6][11][0])+((Vpk[6][9][2]*c11)+(
          Vpk[6][10][0]*s11)));
        VWri[6][12][0] = (Vpk[6][11][0]+((.0065*Wpk[6][10][1])-(.0442*
          Wpk[6][11][2])));
        VWri[6][12][1] = (Vpk[6][11][1]-(.0065*Wpk[6][11][0]));
        VWri[6][12][2] = (Vpk[6][11][2]+(.0442*Wpk[6][11][0]));
        Vpk[6][12][0] = (VWri[6][12][0]+((.0312*Wpk[6][12][1])-(.078*
          Wpk[6][12][2])));
        Vpk[6][12][1] = (((VWri[6][12][1]*c12)+(VWri[6][12][2]*s12))-(.0312*
          Wpk[6][11][0]));
        Vpk[6][12][2] = ((.078*Wpk[6][11][0])+((VWri[6][12][2]*c12)-(
          VWri[6][12][1]*s12)));
        VWri[6][13][0] = (Vpk[6][8][0]-((.0013*s7)+(.18915*Wpk[6][8][2])));
        VWri[6][13][1] = ((.0351*Wpk[6][8][0])+((.1768*Wpk[6][8][2])-(.0013*
          Wpk[6][8][0])));
        VWri[6][13][2] = ((.14625*Wpk[6][8][0])+((.1768*s7)+(.18915*Wpk[6][8][0]
          )));
        Vpk[6][13][0] = ((VWri[6][13][0]*c13)+(VWri[6][13][1]*s13));
        Vpk[6][13][1] = ((VWri[6][13][1]*c13)-(VWri[6][13][0]*s13));
        Vpk[6][13][2] = VWri[6][13][2];
        Vpk[6][14][0] = ((.0013*Wpk[6][13][1])+((Vpk[6][13][0]*c14)-(
          VWri[6][13][2]*s14)));
        Vpk[6][14][1] = (Vpk[6][13][1]+((.1326*Wpk[6][14][2])-(.0013*
          Wpk[6][14][0])));
        Vpk[6][14][2] = (((Vpk[6][13][0]*s14)+(VWri[6][13][2]*c14))-(.1326*
          Wpk[6][13][1]));
        VWri[6][15][0] = (Vpk[6][14][0]+(.0013*Wpk[6][13][1]));
        VWri[6][15][1] = (Vpk[6][14][1]+((.1326*Wpk[6][14][2])-(.0013*
          Wpk[6][14][0])));
        VWri[6][15][2] = (Vpk[6][14][2]-(.1326*Wpk[6][13][1]));
        Vpk[6][15][0] = ((VWri[6][15][0]*c15)-(VWri[6][15][2]*s15));
        Vpk[6][15][1] = VWri[6][15][1];
        Vpk[6][15][2] = ((VWri[6][15][0]*s15)+(VWri[6][15][2]*c15));
        Vpk[6][16][0] = (Vpk[6][15][0]-(.0039*Wpk[6][16][2]));
        Vpk[6][16][1] = ((.1378*Wpk[6][16][2])+((Vpk[6][15][2]*s16)+(
          VWri[6][15][1]*c16)));
        Vpk[6][16][2] = (((.0039*Wpk[6][15][0])-(.1378*Wpk[6][16][1]))+((
          Vpk[6][15][2]*c16)-(VWri[6][15][1]*s16)));
        VWri[6][17][0] = (Vpk[6][16][0]-(.0039*Wpk[6][16][2]));
        VWri[6][17][1] = (Vpk[6][16][1]+(.1378*Wpk[6][16][2]));
        VWri[6][17][2] = (Vpk[6][16][2]+((.0039*Wpk[6][15][0])-(.1378*
          Wpk[6][16][1])));
        Vpk[6][17][0] = ((VWri[6][17][0]*c17)+(VWri[6][17][1]*s17));
        Vpk[6][17][1] = ((VWri[6][17][1]*c17)-(VWri[6][17][0]*s17));
        Vpk[6][17][2] = VWri[6][17][2];
        Vpk[6][18][0] = ((Vpk[6][17][0]*c18)-(VWri[6][17][2]*s18));
        Vpk[6][18][1] = (Vpk[6][17][1]+(.065*Wpk[6][18][2]));
        Vpk[6][18][2] = (((Vpk[6][17][0]*s18)+(VWri[6][17][2]*c18))-(.065*
          Wpk[6][17][1]));
        VWri[6][19][0] = (Vpk[6][8][0]-((.0013*s7)+(.18915*Wpk[6][8][2])));
        VWri[6][19][1] = ((.0351*Wpk[6][8][0])-((.0013*Wpk[6][8][0])+(.1768*
          Wpk[6][8][2])));
        VWri[6][19][2] = ((.14625*Wpk[6][8][0])+((.18915*Wpk[6][8][0])-(.1768*s7
          )));
        Vpk[6][19][0] = ((VWri[6][19][0]*c19)+(VWri[6][19][1]*s19));
        Vpk[6][19][1] = ((VWri[6][19][1]*c19)-(VWri[6][19][0]*s19));
        Vpk[6][19][2] = VWri[6][19][2];
        Vpk[6][20][0] = ((.0013*Wpk[6][19][1])+((Vpk[6][19][0]*c20)-(
          VWri[6][19][2]*s20)));
        Vpk[6][20][1] = (Vpk[6][19][1]-((.0013*Wpk[6][20][0])+(.1326*
          Wpk[6][20][2])));
        Vpk[6][20][2] = ((.1326*Wpk[6][19][1])+((Vpk[6][19][0]*s20)+(
          VWri[6][19][2]*c20)));
        VWri[6][21][0] = (Vpk[6][20][0]+(.0013*Wpk[6][19][1]));
        VWri[6][21][1] = (Vpk[6][20][1]-((.0013*Wpk[6][20][0])+(.1326*
          Wpk[6][20][2])));
        VWri[6][21][2] = (Vpk[6][20][2]+(.1326*Wpk[6][19][1]));
        Vpk[6][21][0] = ((VWri[6][21][0]*c21)-(VWri[6][21][2]*s21));
        Vpk[6][21][1] = VWri[6][21][1];
        Vpk[6][21][2] = ((VWri[6][21][0]*s21)+(VWri[6][21][2]*c21));
        Vpk[6][22][0] = (Vpk[6][21][0]-(.0039*Wpk[6][22][2]));
        Vpk[6][22][1] = (((Vpk[6][21][2]*s22)+(VWri[6][21][1]*c22))-(.1378*
          Wpk[6][22][2]));
        Vpk[6][22][2] = (((.0039*Wpk[6][21][0])+(.1378*Wpk[6][22][1]))+((
          Vpk[6][21][2]*c22)-(VWri[6][21][1]*s22)));
        VWri[6][23][0] = (Vpk[6][22][0]-(.0039*Wpk[6][22][2]));
        VWri[6][23][1] = (Vpk[6][22][1]-(.1378*Wpk[6][22][2]));
        VWri[6][23][2] = (Vpk[6][22][2]+((.0039*Wpk[6][21][0])+(.1378*
          Wpk[6][22][1])));
        Vpk[6][23][0] = ((VWri[6][23][0]*c23)+(VWri[6][23][1]*s23));
        Vpk[6][23][1] = ((VWri[6][23][1]*c23)-(VWri[6][23][0]*s23));
        Vpk[6][23][2] = VWri[6][23][2];
        Vpk[6][24][0] = ((Vpk[6][23][0]*c24)-(VWri[6][23][2]*s24));
        Vpk[6][24][1] = (Vpk[6][23][1]-(.065*Wpk[6][24][2]));
        Vpk[6][24][2] = ((.065*Wpk[6][23][1])+((Vpk[6][23][0]*s24)+(
          VWri[6][23][2]*c24)));
        Vpk[7][8][0] = -(.14625*c8);
        Vpk[7][8][1] = -(.0351*s8);
        Vpk[7][8][2] = -(.14625*s8);
        Vpk[7][9][0] = -(.3926*c8);
        Vpk[7][9][1] = -((.0364*(s8*c9))+(.3926*(s8*s9)));
        Vpk[7][9][2] = ((.0364*(s8*s9))-(.3926*(s8*c9)));
        Vpk[7][10][0] = ((Vpk[7][9][1]*s10)-(.3926*(c8*c10)));
        Vpk[7][10][1] = ((.3926*(s10*c8))+(Vpk[7][9][1]*c10));
        Vpk[7][10][2] = Vpk[7][9][2];
        Vpk[7][11][0] = (((.0065*Wpk[7][10][1])-(.0442*Wpk[7][11][2]))+((
          Vpk[7][10][0]*c11)-(Vpk[7][9][2]*s11)));
        Vpk[7][11][1] = (Vpk[7][10][1]-(.0065*Wpk[7][11][0]));
        Vpk[7][11][2] = ((.0442*Wpk[7][11][0])+((Vpk[7][9][2]*c11)+(
          Vpk[7][10][0]*s11)));
        VWri[7][12][0] = (Vpk[7][11][0]+((.0065*Wpk[7][10][1])-(.0442*
          Wpk[7][11][2])));
        VWri[7][12][1] = (Vpk[7][11][1]-(.0065*Wpk[7][11][0]));
        VWri[7][12][2] = (Vpk[7][11][2]+(.0442*Wpk[7][11][0]));
        Vpk[7][12][0] = (VWri[7][12][0]+((.0312*Wpk[7][12][1])-(.078*
          Wpk[7][12][2])));
        Vpk[7][12][1] = (((VWri[7][12][1]*c12)+(VWri[7][12][2]*s12))-(.0312*
          Wpk[7][11][0]));
        Vpk[7][12][2] = ((.078*Wpk[7][11][0])+((VWri[7][12][2]*c12)-(
          VWri[7][12][1]*s12)));
        VWri[7][13][1] = (((.0013*s8)+(.1768*c8))-(.0351*s8));
        Vpk[7][13][0] = ((VWri[7][13][1]*s13)-(.3354*(c8*c13)));
        Vpk[7][13][1] = ((.3354*(s13*c8))+(VWri[7][13][1]*c13));
        Vpk[7][13][2] = -(.3354*s8);
        Vpk[7][14][0] = ((.0013*Wpk[7][13][1])+((.3354*(s8*s14))+(Vpk[7][13][0]*
          c14)));
        Vpk[7][14][1] = (Vpk[7][13][1]+((.1326*Wpk[7][14][2])-(.0013*
          Wpk[7][14][0])));
        Vpk[7][14][2] = (((Vpk[7][13][0]*s14)-(.3354*(s8*c14)))-(.1326*
          Wpk[7][13][1]));
        VWri[7][15][0] = (Vpk[7][14][0]+(.0013*Wpk[7][13][1]));
        VWri[7][15][1] = (Vpk[7][14][1]+((.1326*Wpk[7][14][2])-(.0013*
          Wpk[7][14][0])));
        VWri[7][15][2] = (Vpk[7][14][2]-(.1326*Wpk[7][13][1]));
        Vpk[7][15][0] = ((VWri[7][15][0]*c15)-(VWri[7][15][2]*s15));
        Vpk[7][15][1] = VWri[7][15][1];
        Vpk[7][15][2] = ((VWri[7][15][0]*s15)+(VWri[7][15][2]*c15));
        Vpk[7][16][0] = (Vpk[7][15][0]-(.0039*Wpk[7][16][2]));
        Vpk[7][16][1] = ((.1378*Wpk[7][16][2])+((Vpk[7][15][2]*s16)+(
          VWri[7][15][1]*c16)));
        Vpk[7][16][2] = (((.0039*Wpk[7][15][0])-(.1378*Wpk[7][16][1]))+((
          Vpk[7][15][2]*c16)-(VWri[7][15][1]*s16)));
        VWri[7][17][0] = (Vpk[7][16][0]-(.0039*Wpk[7][16][2]));
        VWri[7][17][1] = (Vpk[7][16][1]+(.1378*Wpk[7][16][2]));
        VWri[7][17][2] = (Vpk[7][16][2]+((.0039*Wpk[7][15][0])-(.1378*
          Wpk[7][16][1])));
        Vpk[7][17][0] = ((VWri[7][17][0]*c17)+(VWri[7][17][1]*s17));
        Vpk[7][17][1] = ((VWri[7][17][1]*c17)-(VWri[7][17][0]*s17));
        Vpk[7][17][2] = VWri[7][17][2];
        Vpk[7][18][0] = ((Vpk[7][17][0]*c18)-(VWri[7][17][2]*s18));
        Vpk[7][18][1] = (Vpk[7][17][1]+(.065*Wpk[7][18][2]));
        Vpk[7][18][2] = (((Vpk[7][17][0]*s18)+(VWri[7][17][2]*c18))-(.065*
          Wpk[7][17][1]));
        VWri[7][19][1] = (((.0013*s8)-(.1768*c8))-(.0351*s8));
        Vpk[7][19][0] = ((VWri[7][19][1]*s19)-(.3354*(c8*c19)));
        Vpk[7][19][1] = ((.3354*(s19*c8))+(VWri[7][19][1]*c19));
        Vpk[7][19][2] = -(.3354*s8);
        Vpk[7][20][0] = ((.0013*Wpk[7][19][1])+((.3354*(s8*s20))+(Vpk[7][19][0]*
          c20)));
        Vpk[7][20][1] = (Vpk[7][19][1]-((.0013*Wpk[7][20][0])+(.1326*
          Wpk[7][20][2])));
        Vpk[7][20][2] = ((.1326*Wpk[7][19][1])+((Vpk[7][19][0]*s20)-(.3354*(s8*
          c20))));
        VWri[7][21][0] = (Vpk[7][20][0]+(.0013*Wpk[7][19][1]));
        VWri[7][21][1] = (Vpk[7][20][1]-((.0013*Wpk[7][20][0])+(.1326*
          Wpk[7][20][2])));
        VWri[7][21][2] = (Vpk[7][20][2]+(.1326*Wpk[7][19][1]));
        Vpk[7][21][0] = ((VWri[7][21][0]*c21)-(VWri[7][21][2]*s21));
        Vpk[7][21][1] = VWri[7][21][1];
        Vpk[7][21][2] = ((VWri[7][21][0]*s21)+(VWri[7][21][2]*c21));
        Vpk[7][22][0] = (Vpk[7][21][0]-(.0039*Wpk[7][22][2]));
        Vpk[7][22][1] = (((Vpk[7][21][2]*s22)+(VWri[7][21][1]*c22))-(.1378*
          Wpk[7][22][2]));
        Vpk[7][22][2] = (((.0039*Wpk[7][21][0])+(.1378*Wpk[7][22][1]))+((
          Vpk[7][21][2]*c22)-(VWri[7][21][1]*s22)));
        VWri[7][23][0] = (Vpk[7][22][0]-(.0039*Wpk[7][22][2]));
        VWri[7][23][1] = (Vpk[7][22][1]-(.1378*Wpk[7][22][2]));
        VWri[7][23][2] = (Vpk[7][22][2]+((.0039*Wpk[7][21][0])+(.1378*
          Wpk[7][22][1])));
        Vpk[7][23][0] = ((VWri[7][23][0]*c23)+(VWri[7][23][1]*s23));
        Vpk[7][23][1] = ((VWri[7][23][1]*c23)-(VWri[7][23][0]*s23));
        Vpk[7][23][2] = VWri[7][23][2];
        Vpk[7][24][0] = ((Vpk[7][23][0]*c24)-(VWri[7][23][2]*s24));
        Vpk[7][24][1] = (Vpk[7][23][1]-(.065*Wpk[7][24][2]));
        Vpk[7][24][2] = ((.065*Wpk[7][23][1])+((Vpk[7][23][0]*s24)+(
          VWri[7][23][2]*c24)));
        Vpk[8][8][0] = -.0351;
        Vpk[8][9][0] = -.0364;
        Vpk[8][10][0] = -(.0364*c10);
        Vpk[8][10][1] = (.0364*s10);
        Vpk[8][11][0] = (((.0065*Wpk[8][10][1])-(.0442*Wpk[8][11][2]))-(.0364*(
          c10*c11)));
        Vpk[8][11][1] = ((.0364*s10)-(.0065*Wpk[8][11][0]));
        Vpk[8][11][2] = ((.0442*Wpk[8][11][0])-(.0364*(s11*c10)));
        VWri[8][12][0] = (Vpk[8][11][0]+((.0065*Wpk[8][10][1])-(.0442*
          Wpk[8][11][2])));
        VWri[8][12][1] = (Vpk[8][11][1]-(.0065*Wpk[8][11][0]));
        VWri[8][12][2] = (Vpk[8][11][2]+(.0442*Wpk[8][11][0]));
        Vpk[8][12][0] = (VWri[8][12][0]+((.0312*Wpk[8][12][1])-(.078*
          Wpk[8][12][2])));
        Vpk[8][12][1] = (((VWri[8][12][1]*c12)+(VWri[8][12][2]*s12))-(.0312*
          Wpk[8][11][0]));
        Vpk[8][12][2] = ((.078*Wpk[8][11][0])+((VWri[8][12][2]*c12)-(
          VWri[8][12][1]*s12)));
        Vpk[8][13][0] = -(.0338*c13);
        Vpk[8][13][1] = (.0338*s13);
        Vpk[8][13][2] = -.1768;
        Vpk[8][14][0] = ((.0013*c13)+((.1768*s14)-(.0338*(c13*c14))));
        Vpk[8][14][1] = ((.0338*s13)+((.1326*Wpk[8][14][2])-(.0013*Wpk[8][14][0]
          )));
        Vpk[8][14][2] = -((.1326*c13)+((.0338*(s14*c13))+(.1768*c14)));
        VWri[8][15][0] = (Vpk[8][14][0]+(.0013*c13));
        VWri[8][15][1] = (Vpk[8][14][1]+((.1326*Wpk[8][14][2])-(.0013*
          Wpk[8][14][0])));
        VWri[8][15][2] = (Vpk[8][14][2]-(.1326*c13));
        Vpk[8][15][0] = ((VWri[8][15][0]*c15)-(VWri[8][15][2]*s15));
        Vpk[8][15][1] = VWri[8][15][1];
        Vpk[8][15][2] = ((VWri[8][15][0]*s15)+(VWri[8][15][2]*c15));
        Vpk[8][16][0] = (Vpk[8][15][0]-(.0039*Wpk[8][16][2]));
        Vpk[8][16][1] = ((.1378*Wpk[8][16][2])+((Vpk[8][15][2]*s16)+(
          VWri[8][15][1]*c16)));
        Vpk[8][16][2] = (((.0039*Wpk[8][15][0])-(.1378*Wpk[8][16][1]))+((
          Vpk[8][15][2]*c16)-(VWri[8][15][1]*s16)));
        VWri[8][17][0] = (Vpk[8][16][0]-(.0039*Wpk[8][16][2]));
        VWri[8][17][1] = (Vpk[8][16][1]+(.1378*Wpk[8][16][2]));
        VWri[8][17][2] = (Vpk[8][16][2]+((.0039*Wpk[8][15][0])-(.1378*
          Wpk[8][16][1])));
        Vpk[8][17][0] = ((VWri[8][17][0]*c17)+(VWri[8][17][1]*s17));
        Vpk[8][17][1] = ((VWri[8][17][1]*c17)-(VWri[8][17][0]*s17));
        Vpk[8][17][2] = VWri[8][17][2];
        Vpk[8][18][0] = ((Vpk[8][17][0]*c18)-(VWri[8][17][2]*s18));
        Vpk[8][18][1] = (Vpk[8][17][1]+(.065*Wpk[8][18][2]));
        Vpk[8][18][2] = (((Vpk[8][17][0]*s18)+(VWri[8][17][2]*c18))-(.065*
          Wpk[8][17][1]));
        Vpk[8][19][0] = -(.0338*c19);
        Vpk[8][19][1] = (.0338*s19);
        Vpk[8][19][2] = .1768;
        Vpk[8][20][0] = ((.0013*c19)-((.0338*(c19*c20))+(.1768*s20)));
        Vpk[8][20][1] = ((.0338*s19)-((.0013*Wpk[8][20][0])+(.1326*Wpk[8][20][2]
          )));
        Vpk[8][20][2] = ((.1326*c19)+((.1768*c20)-(.0338*(s20*c19))));
        VWri[8][21][0] = (Vpk[8][20][0]+(.0013*c19));
        VWri[8][21][1] = (Vpk[8][20][1]-((.0013*Wpk[8][20][0])+(.1326*
          Wpk[8][20][2])));
        VWri[8][21][2] = (Vpk[8][20][2]+(.1326*c19));
        Vpk[8][21][0] = ((VWri[8][21][0]*c21)-(VWri[8][21][2]*s21));
        Vpk[8][21][1] = VWri[8][21][1];
        Vpk[8][21][2] = ((VWri[8][21][0]*s21)+(VWri[8][21][2]*c21));
        Vpk[8][22][0] = (Vpk[8][21][0]-(.0039*Wpk[8][22][2]));
        Vpk[8][22][1] = (((Vpk[8][21][2]*s22)+(VWri[8][21][1]*c22))-(.1378*
          Wpk[8][22][2]));
        Vpk[8][22][2] = (((.0039*Wpk[8][21][0])+(.1378*Wpk[8][22][1]))+((
          Vpk[8][21][2]*c22)-(VWri[8][21][1]*s22)));
        VWri[8][23][0] = (Vpk[8][22][0]-(.0039*Wpk[8][22][2]));
        VWri[8][23][1] = (Vpk[8][22][1]-(.1378*Wpk[8][22][2]));
        VWri[8][23][2] = (Vpk[8][22][2]+((.0039*Wpk[8][21][0])+(.1378*
          Wpk[8][22][1])));
        Vpk[8][23][0] = ((VWri[8][23][0]*c23)+(VWri[8][23][1]*s23));
        Vpk[8][23][1] = ((VWri[8][23][1]*c23)-(VWri[8][23][0]*s23));
        Vpk[8][23][2] = VWri[8][23][2];
        Vpk[8][24][0] = ((Vpk[8][23][0]*c24)-(VWri[8][23][2]*s24));
        Vpk[8][24][1] = (Vpk[8][23][1]-(.065*Wpk[8][24][2]));
        Vpk[8][24][2] = ((.065*Wpk[8][23][1])+((Vpk[8][23][0]*s24)+(
          VWri[8][23][2]*c24)));
        Vpk[9][11][0] = -((.0065*s10)+(.0442*Wpk[9][11][2]));
        Vpk[9][11][1] = -(.0065*Wpk[9][11][0]);
        Vpk[9][11][2] = (.0442*Wpk[9][11][0]);
        VWri[9][12][0] = (Vpk[9][11][0]-((.0065*s10)+(.0442*Wpk[9][11][2])));
        Vpk[9][12][0] = (VWri[9][12][0]+((.0312*Wpk[9][12][1])-(.078*
          Wpk[9][12][2])));
        Vpk[9][12][1] = (((.0884*(Wpk[9][11][0]*s12))-(.013*(Wpk[9][11][0]*c12))
          )-(.0312*Wpk[9][11][0]));
        Vpk[9][12][2] = ((.078*Wpk[9][11][0])+((.013*(Wpk[9][11][0]*s12))+(.0884
          *(Wpk[9][11][0]*c12))));
        Vpk[10][11][0] = -(.0442*c11);
        Vpk[10][11][1] = (.0065*s11);
        Vpk[10][11][2] = -(.0442*s11);
        Vpk[10][12][0] = (((.0312*Wpk[10][12][1])-(.078*Wpk[10][12][2]))-(.0884*
          c11));
        Vpk[10][12][1] = ((.0312*s11)+((.013*(s11*c12))-(.0884*(s11*s12))));
        Vpk[10][12][2] = -((.078*s11)+((.013*(s11*s12))+(.0884*(s11*c12))));
        Vpk[11][11][0] = .0065;
        Vpk[11][12][0] = (.013+((.0312*c12)+(.078*s12)));
        Vpk[12][12][1] = -.0312;
        Vpk[12][12][2] = .078;
        Vpk[13][14][1] = ((.0013*s14)+(.1326*c14));
        VWri[13][15][1] = (Vpk[13][14][1]+((.0013*s14)+(.1326*c14)));
        Vpk[13][15][1] = VWri[13][15][1];
        Vpk[13][16][0] = -(.0039*Wpk[13][16][2]);
        Vpk[13][16][1] = ((.1378*Wpk[13][16][2])+(VWri[13][15][1]*c16));
        Vpk[13][16][2] = (((.0039*Wpk[13][15][0])-(.1378*Wpk[13][16][1]))-(
          VWri[13][15][1]*s16));
        VWri[13][17][1] = (Vpk[13][16][1]+(.1378*Wpk[13][16][2]));
        VWri[13][17][2] = (Vpk[13][16][2]+((.0039*Wpk[13][15][0])-(.1378*
          Wpk[13][16][1])));
        Vpk[13][17][0] = ((VWri[13][17][1]*s17)-(.0078*(Wpk[13][16][2]*c17)));
        Vpk[13][17][1] = ((.0078*(Wpk[13][16][2]*s17))+(VWri[13][17][1]*c17));
        Vpk[13][17][2] = VWri[13][17][2];
        Vpk[13][18][0] = ((Vpk[13][17][0]*c18)-(VWri[13][17][2]*s18));
        Vpk[13][18][1] = (Vpk[13][17][1]+(.065*Wpk[13][18][2]));
        Vpk[13][18][2] = (((Vpk[13][17][0]*s18)+(VWri[13][17][2]*c18))-(.065*
          Wpk[13][17][1]));
        Vpk[14][14][0] = .0013;
        Vpk[14][14][2] = -.1326;
        Vpk[14][15][0] = ((.0026*c15)+(.2652*s15));
        Vpk[14][15][2] = ((.0026*s15)-(.2652*c15));
        Vpk[14][16][0] = (Vpk[14][15][0]+(.0039*s16));
        Vpk[14][16][1] = ((Vpk[14][15][2]*s16)-(.1378*s16));
        Vpk[14][16][2] = ((Vpk[14][15][2]*c16)-(.1378*c16));
        VWri[14][17][0] = (Vpk[14][16][0]+(.0039*s16));
        VWri[14][17][1] = (Vpk[14][16][1]-(.1378*s16));
        VWri[14][17][2] = (Vpk[14][16][2]-(.1378*c16));
        Vpk[14][17][0] = ((VWri[14][17][0]*c17)+(VWri[14][17][1]*s17));
        Vpk[14][17][1] = ((VWri[14][17][1]*c17)-(VWri[14][17][0]*s17));
        Vpk[14][17][2] = VWri[14][17][2];
        Vpk[14][18][0] = ((Vpk[14][17][0]*c18)-(VWri[14][17][2]*s18));
        Vpk[14][18][1] = (Vpk[14][17][1]+(.065*Wpk[14][18][2]));
        Vpk[14][18][2] = (((Vpk[14][17][0]*s18)+(VWri[14][17][2]*c18))-(.065*
          Wpk[14][17][1]));
        Vpk[15][16][0] = (.0039*s16);
        Vpk[15][16][1] = -(.1378*s16);
        Vpk[15][16][2] = -(.1378*c16);
        Vpk[15][17][0] = ((.0078*(s16*c17))-(.2756*(s16*s17)));
        Vpk[15][17][1] = -((.0078*(s16*s17))+(.2756*(s16*c17)));
        Vpk[15][17][2] = -(.2756*c16);
        Vpk[15][18][0] = ((.2756*(s18*c16))+(Vpk[15][17][0]*c18));
        Vpk[15][18][1] = (Vpk[15][17][1]+(.065*Wpk[15][18][2]));
        Vpk[15][18][2] = (((Vpk[15][17][0]*s18)-(.2756*(c16*c18)))-(.065*
          Wpk[15][17][1]));
        Vpk[16][16][2] = .0039;
        Vpk[16][17][2] = .0078;
        Vpk[16][18][0] = -(.0078*s18);
        Vpk[16][18][1] = (.065*Wpk[16][18][2]);
        Vpk[16][18][2] = ((.0078*c18)+(.065*s17));
        Vpk[17][18][1] = (.065*c18);
        Vpk[18][18][2] = -.065;
        Vpk[19][20][1] = ((.0013*s20)-(.1326*c20));
        VWri[19][21][1] = (Vpk[19][20][1]+((.0013*s20)-(.1326*c20)));
        Vpk[19][21][1] = VWri[19][21][1];
        Vpk[19][22][0] = -(.0039*Wpk[19][22][2]);
        Vpk[19][22][1] = ((VWri[19][21][1]*c22)-(.1378*Wpk[19][22][2]));
        Vpk[19][22][2] = (((.0039*Wpk[19][21][0])+(.1378*Wpk[19][22][1]))-(
          VWri[19][21][1]*s22));
        VWri[19][23][1] = (Vpk[19][22][1]-(.1378*Wpk[19][22][2]));
        VWri[19][23][2] = (Vpk[19][22][2]+((.0039*Wpk[19][21][0])+(.1378*
          Wpk[19][22][1])));
        Vpk[19][23][0] = ((VWri[19][23][1]*s23)-(.0078*(Wpk[19][22][2]*c23)));
        Vpk[19][23][1] = ((.0078*(Wpk[19][22][2]*s23))+(VWri[19][23][1]*c23));
        Vpk[19][23][2] = VWri[19][23][2];
        Vpk[19][24][0] = ((Vpk[19][23][0]*c24)-(VWri[19][23][2]*s24));
        Vpk[19][24][1] = (Vpk[19][23][1]-(.065*Wpk[19][24][2]));
        Vpk[19][24][2] = ((.065*Wpk[19][23][1])+((Vpk[19][23][0]*s24)+(
          VWri[19][23][2]*c24)));
        Vpk[20][20][0] = .0013;
        Vpk[20][20][2] = .1326;
        Vpk[20][21][0] = ((.0026*c21)-(.2652*s21));
        Vpk[20][21][2] = ((.0026*s21)+(.2652*c21));
        Vpk[20][22][0] = (Vpk[20][21][0]+(.0039*s22));
        Vpk[20][22][1] = ((.1378*s22)+(Vpk[20][21][2]*s22));
        Vpk[20][22][2] = ((.1378*c22)+(Vpk[20][21][2]*c22));
        VWri[20][23][0] = (Vpk[20][22][0]+(.0039*s22));
        VWri[20][23][1] = (Vpk[20][22][1]+(.1378*s22));
        VWri[20][23][2] = (Vpk[20][22][2]+(.1378*c22));
        Vpk[20][23][0] = ((VWri[20][23][0]*c23)+(VWri[20][23][1]*s23));
        Vpk[20][23][1] = ((VWri[20][23][1]*c23)-(VWri[20][23][0]*s23));
        Vpk[20][23][2] = VWri[20][23][2];
        Vpk[20][24][0] = ((Vpk[20][23][0]*c24)-(VWri[20][23][2]*s24));
        Vpk[20][24][1] = (Vpk[20][23][1]-(.065*Wpk[20][24][2]));
        Vpk[20][24][2] = ((.065*Wpk[20][23][1])+((Vpk[20][23][0]*s24)+(
          VWri[20][23][2]*c24)));
        Vpk[21][22][0] = (.0039*s22);
        Vpk[21][22][1] = (.1378*s22);
        Vpk[21][22][2] = (.1378*c22);
        Vpk[21][23][0] = ((.0078*(s22*c23))+(.2756*(s22*s23)));
        Vpk[21][23][1] = ((.2756*(s22*c23))-(.0078*(s22*s23)));
        Vpk[21][23][2] = (.2756*c22);
        Vpk[21][24][0] = ((Vpk[21][23][0]*c24)-(.2756*(s24*c22)));
        Vpk[21][24][1] = (Vpk[21][23][1]-(.065*Wpk[21][24][2]));
        Vpk[21][24][2] = ((.065*Wpk[21][23][1])+((.2756*(c22*c24))+(
          Vpk[21][23][0]*s24)));
        Vpk[22][22][2] = .0039;
        Vpk[22][23][2] = .0078;
        Vpk[22][24][0] = -(.0078*s24);
        Vpk[22][24][1] = -(.065*Wpk[22][24][2]);
        Vpk[22][24][2] = ((.0078*c24)-(.065*s23));
        Vpk[23][24][1] = -(.065*c24);
        Vpk[24][24][2] = .065;
        Vpk[25][27][0] = ((.2379*Wpk[25][27][2])-(.0143*s26));
        Vpk[25][27][1] = -((.0143*Wpk[25][27][0])+(.0169*Wpk[25][27][2]));
        Vpk[25][27][2] = -((.0169*s26)+(.2379*Wpk[25][27][0]));
        VWri[25][28][0] = (Vpk[25][27][0]+((.2379*Wpk[25][27][2])-(.0143*s26)));
        VWri[25][28][1] = (Vpk[25][27][1]-((.0143*Wpk[25][27][0])+(.0169*
          Wpk[25][27][2])));
        VWri[25][28][2] = (Vpk[25][27][2]-((.0169*s26)+(.2379*Wpk[25][27][0])));
        Vpk[25][28][0] = (VWri[25][28][0]+((.2158*Wpk[25][28][2])-(.0039*
          Wpk[25][28][1])));
        Vpk[25][28][1] = (((.0039*Wpk[25][27][0])-(.0078*Wpk[25][28][2]))+((
          VWri[25][28][1]*c28)+(VWri[25][28][2]*s28)));
        Vpk[25][28][2] = (((.0078*Wpk[25][28][1])-(.2158*Wpk[25][27][0]))+((
          VWri[25][28][2]*c28)-(VWri[25][28][1]*s28)));
        VWri[25][29][0] = (Vpk[25][28][0]+((.2158*Wpk[25][28][2])-(.0039*
          Wpk[25][28][1])));
        VWri[25][29][1] = (Vpk[25][28][1]+((.0039*Wpk[25][27][0])-(.0078*
          Wpk[25][28][2])));
        VWri[25][29][2] = (Vpk[25][28][2]+((.0078*Wpk[25][28][1])-(.2158*
          Wpk[25][27][0])));
        Vpk[25][29][0] = VWri[25][29][0];
        Vpk[25][29][1] = ((VWri[25][29][1]*c29)+(VWri[25][29][2]*s29));
        Vpk[25][29][2] = ((VWri[25][29][2]*c29)-(VWri[25][29][1]*s29));
        Vpk[25][30][0] = (((.039*Wpk[25][30][1])+(.0442*Wpk[25][29][2]))+((
          Vpk[25][29][1]*s30)+(VWri[25][29][0]*c30)));
        Vpk[25][30][1] = (((Vpk[25][29][1]*c30)-(VWri[25][29][0]*s30))-(.039*
          Wpk[25][30][0]));
        Vpk[25][30][2] = (Vpk[25][29][2]-(.0442*Wpk[25][30][0]));
        Vpk[26][27][0] = (.2379*c27);
        Vpk[26][27][1] = ((.0143*s27)-(.0169*c27));
        Vpk[26][27][2] = (.2379*s27);
        VWri[26][28][1] = (Vpk[26][27][1]+((.0143*s27)-(.0169*c27)));
        Vpk[26][28][0] = ((.4758*c27)+((.2158*Wpk[26][28][2])-(.0039*
          Wpk[26][28][1])));
        Vpk[26][28][1] = (((.4758*(s27*s28))+(VWri[26][28][1]*c28))-((.0039*s27)
          +(.0078*Wpk[26][28][2])));
        Vpk[26][28][2] = (((.0078*Wpk[26][28][1])+(.2158*s27))+((.4758*(s27*c28)
          )-(VWri[26][28][1]*s28)));
        VWri[26][29][0] = (Vpk[26][28][0]+((.2158*Wpk[26][28][2])-(.0039*
          Wpk[26][28][1])));
        VWri[26][29][1] = (Vpk[26][28][1]-((.0039*s27)+(.0078*Wpk[26][28][2])));
        VWri[26][29][2] = (Vpk[26][28][2]+((.0078*Wpk[26][28][1])+(.2158*s27)));
        Vpk[26][29][0] = VWri[26][29][0];
        Vpk[26][29][1] = ((VWri[26][29][1]*c29)+(VWri[26][29][2]*s29));
        Vpk[26][29][2] = ((VWri[26][29][2]*c29)-(VWri[26][29][1]*s29));
        Vpk[26][30][0] = (((.039*Wpk[26][30][1])+(.0442*Wpk[26][29][2]))+((
          Vpk[26][29][1]*s30)+(VWri[26][29][0]*c30)));
        Vpk[26][30][1] = (((Vpk[26][29][1]*c30)-(VWri[26][29][0]*s30))-(.039*
          Wpk[26][30][0]));
        Vpk[26][30][2] = (Vpk[26][29][2]-(.0442*Wpk[26][30][0]));
        Vpk[27][27][0] = .0143;
        Vpk[27][27][2] = .0169;
        Vpk[27][28][0] = (.0286-((.0039*c28)+(.2158*s28)));
        Vpk[27][28][1] = (.0416*s28);
        Vpk[27][28][2] = (.0416*c28);
        VWri[27][29][0] = (Vpk[27][28][0]-((.0039*c28)+(.2158*s28)));
        Vpk[27][29][0] = VWri[27][29][0];
        Vpk[27][29][1] = (.0494*((s28*c29)+(s29*c28)));
        Vpk[27][29][2] = (.0494*((c28*c29)-(s28*s29)));
        Vpk[27][30][0] = (((.039*Wpk[27][30][1])+(.0442*Wpk[27][29][2]))+((
          Vpk[27][29][1]*s30)+(VWri[27][29][0]*c30)));
        Vpk[27][30][1] = (((Vpk[27][29][1]*c30)-(VWri[27][29][0]*s30))-(.039*
          Wpk[27][30][0]));
        Vpk[27][30][2] = (Vpk[27][29][2]-(.0442*Wpk[27][30][0]));
        Vpk[28][28][1] = .0039;
        Vpk[28][28][2] = -.2158;
        Vpk[28][29][1] = ((.0078*c29)-(.4316*s29));
        Vpk[28][29][2] = -((.0078*s29)+(.4316*c29));
        Vpk[28][30][0] = ((Vpk[28][29][1]*s30)-(.039*s30));
        Vpk[28][30][1] = ((Vpk[28][29][1]*c30)-(.039*c30));
        Vpk[28][30][2] = (Vpk[28][29][2]-(.0442*c30));
        Vpk[29][30][0] = -(.039*s30);
        Vpk[29][30][1] = -(.039*c30);
        Vpk[29][30][2] = -(.0442*c30);
        Vpk[30][30][0] = .0442;
        Vpk[31][33][0] = ((.2379*Wpk[31][33][2])-(.0143*s32));
        Vpk[31][33][1] = ((.0169*Wpk[31][33][2])-(.0143*Wpk[31][33][0]));
        Vpk[31][33][2] = ((.0169*s32)-(.2379*Wpk[31][33][0]));
        VWri[31][34][0] = (Vpk[31][33][0]+((.2379*Wpk[31][33][2])-(.0143*s32)));
        VWri[31][34][1] = (Vpk[31][33][1]+((.0169*Wpk[31][33][2])-(.0143*
          Wpk[31][33][0])));
        VWri[31][34][2] = (Vpk[31][33][2]+((.0169*s32)-(.2379*Wpk[31][33][0])));
        Vpk[31][34][0] = (VWri[31][34][0]+((.2158*Wpk[31][34][2])-(.0039*
          Wpk[31][34][1])));
        Vpk[31][34][1] = (((.0039*Wpk[31][33][0])+(.0078*Wpk[31][34][2]))+((
          VWri[31][34][1]*c34)+(VWri[31][34][2]*s34)));
        Vpk[31][34][2] = (((VWri[31][34][2]*c34)-(VWri[31][34][1]*s34))-((.0078*
          Wpk[31][34][1])+(.2158*Wpk[31][33][0])));
        VWri[31][35][0] = (Vpk[31][34][0]+((.2158*Wpk[31][34][2])-(.0039*
          Wpk[31][34][1])));
        VWri[31][35][1] = (Vpk[31][34][1]+((.0039*Wpk[31][33][0])+(.0078*
          Wpk[31][34][2])));
        VWri[31][35][2] = (Vpk[31][34][2]-((.0078*Wpk[31][34][1])+(.2158*
          Wpk[31][33][0])));
        Vpk[31][35][0] = VWri[31][35][0];
        Vpk[31][35][1] = ((VWri[31][35][1]*c35)+(VWri[31][35][2]*s35));
        Vpk[31][35][2] = ((VWri[31][35][2]*c35)-(VWri[31][35][1]*s35));
        Vpk[31][36][0] = (((.039*Wpk[31][36][1])+(.0442*Wpk[31][35][2]))+((
          Vpk[31][35][1]*s36)+(VWri[31][35][0]*c36)));
        Vpk[31][36][1] = (((Vpk[31][35][1]*c36)-(VWri[31][35][0]*s36))-(.039*
          Wpk[31][36][0]));
        Vpk[31][36][2] = (Vpk[31][35][2]-(.0442*Wpk[31][36][0]));
        Vpk[32][33][0] = (.2379*c33);
        Vpk[32][33][1] = ((.0143*s33)+(.0169*c33));
        Vpk[32][33][2] = (.2379*s33);
        VWri[32][34][1] = (Vpk[32][33][1]+((.0143*s33)+(.0169*c33)));
        Vpk[32][34][0] = ((.4758*c33)+((.2158*Wpk[32][34][2])-(.0039*
          Wpk[32][34][1])));
        Vpk[32][34][1] = (((.0078*Wpk[32][34][2])-(.0039*s33))+((.4758*(s33*s34)
          )+(VWri[32][34][1]*c34)));
        Vpk[32][34][2] = (((.2158*s33)-(.0078*Wpk[32][34][1]))+((.4758*(s33*c34)
          )-(VWri[32][34][1]*s34)));
        VWri[32][35][0] = (Vpk[32][34][0]+((.2158*Wpk[32][34][2])-(.0039*
          Wpk[32][34][1])));
        VWri[32][35][1] = (Vpk[32][34][1]+((.0078*Wpk[32][34][2])-(.0039*s33)));
        VWri[32][35][2] = (Vpk[32][34][2]+((.2158*s33)-(.0078*Wpk[32][34][1])));
        Vpk[32][35][0] = VWri[32][35][0];
        Vpk[32][35][1] = ((VWri[32][35][1]*c35)+(VWri[32][35][2]*s35));
        Vpk[32][35][2] = ((VWri[32][35][2]*c35)-(VWri[32][35][1]*s35));
        Vpk[32][36][0] = (((.039*Wpk[32][36][1])+(.0442*Wpk[32][35][2]))+((
          Vpk[32][35][1]*s36)+(VWri[32][35][0]*c36)));
        Vpk[32][36][1] = (((Vpk[32][35][1]*c36)-(VWri[32][35][0]*s36))-(.039*
          Wpk[32][36][0]));
        Vpk[32][36][2] = (Vpk[32][35][2]-(.0442*Wpk[32][36][0]));
        Vpk[33][33][0] = .0143;
        Vpk[33][33][2] = -.0169;
        Vpk[33][34][0] = (.0286-((.0039*c34)+(.2158*s34)));
        Vpk[33][34][1] = -(.0416*s34);
        Vpk[33][34][2] = -(.0416*c34);
        VWri[33][35][0] = (Vpk[33][34][0]-((.0039*c34)+(.2158*s34)));
        Vpk[33][35][0] = VWri[33][35][0];
        Vpk[33][35][1] = -(.0494*((s34*c35)+(s35*c34)));
        Vpk[33][35][2] = (.0494*((s34*s35)-(c34*c35)));
        Vpk[33][36][0] = (((.039*Wpk[33][36][1])+(.0442*Wpk[33][35][2]))+((
          Vpk[33][35][1]*s36)+(VWri[33][35][0]*c36)));
        Vpk[33][36][1] = (((Vpk[33][35][1]*c36)-(VWri[33][35][0]*s36))-(.039*
          Wpk[33][36][0]));
        Vpk[33][36][2] = (Vpk[33][35][2]-(.0442*Wpk[33][36][0]));
        Vpk[34][34][1] = .0039;
        Vpk[34][34][2] = -.2158;
        Vpk[34][35][1] = ((.0078*c35)-(.4316*s35));
        Vpk[34][35][2] = -((.0078*s35)+(.4316*c35));
        Vpk[34][36][0] = ((Vpk[34][35][1]*s36)-(.039*s36));
        Vpk[34][36][1] = ((Vpk[34][35][1]*c36)-(.039*c36));
        Vpk[34][36][2] = (Vpk[34][35][2]-(.0442*c36));
        Vpk[35][36][0] = -(.039*s36);
        Vpk[35][36][1] = -(.039*c36);
        Vpk[35][36][2] = -(.0442*c36);
        Vpk[36][36][0] = .0442;
        vpkflg = 1;
    }
/*
 Used 6.86 seconds CPU time,
 212992 additional bytes of memory.
 Equations contain 1567 adds/subtracts/negates
                   2489 multiplies
                      0 divides
                   1714 assignments
*/
}

void skel18doltau(void)
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

void skel18doiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
        Otk[6][1] = (u[6]*wk[6][2]);
        Otk[6][2] = -(u[6]*wk[6][1]);
        Otk[7][0] = ((Otk[6][1]*s7)+(u[7]*wk[7][1]));
        Otk[7][1] = ((Otk[6][1]*c7)-(u[7]*wk[7][0]));
        Otk[8][0] = (((Otk[7][0]*c8)-(Otk[6][2]*s8))-(u[8]*wk[8][2]));
        Otk[8][2] = ((u[8]*wk[8][0])+((Otk[6][2]*c8)+(Otk[7][0]*s8)));
        Otk[9][1] = ((u[9]*wk[9][2])+((Otk[7][1]*c9)+(Otk[8][2]*s9)));
        Otk[9][2] = (((Otk[8][2]*c9)-(Otk[7][1]*s9))-(u[9]*wk[9][1]));
        Otk[10][0] = ((u[10]*wk[10][1])+((Otk[8][0]*c10)+(Otk[9][1]*s10)));
        Otk[10][1] = (((Otk[9][1]*c10)-(Otk[8][0]*s10))-(u[10]*wk[10][0]));
        Otk[11][0] = (((Otk[10][0]*c11)-(Otk[9][2]*s11))-(u[11]*wk[11][2]));
        Otk[11][2] = ((u[11]*wk[11][0])+((Otk[9][2]*c11)+(Otk[10][0]*s11)));
        Otk[12][1] = ((u[12]*wk[12][2])+((Otk[10][1]*c12)+(Otk[11][2]*s12)));
        Otk[12][2] = (((Otk[11][2]*c12)-(Otk[10][1]*s12))-(u[12]*wk[12][1]));
        Otk[13][0] = ((u[13]*wk[13][1])+((Otk[7][1]*s13)+(Otk[8][0]*c13)));
        Otk[13][1] = (((Otk[7][1]*c13)-(Otk[8][0]*s13))-(u[13]*wk[13][0]));
        Otk[14][0] = (((Otk[13][0]*c14)-(Otk[8][2]*s14))-(u[14]*wk[14][2]));
        Otk[14][2] = ((u[14]*wk[14][0])+((Otk[8][2]*c14)+(Otk[13][0]*s14)));
        Otk[15][0] = (((Otk[14][0]*c15)-(Otk[14][2]*s15))-(u[15]*wk[15][2]));
        Otk[15][2] = ((u[15]*wk[15][0])+((Otk[14][0]*s15)+(Otk[14][2]*c15)));
        Otk[16][1] = ((u[16]*wk[16][2])+((Otk[13][1]*c16)+(Otk[15][2]*s16)));
        Otk[16][2] = (((Otk[15][2]*c16)-(Otk[13][1]*s16))-(u[16]*wk[16][1]));
        Otk[17][0] = ((u[17]*wk[17][1])+((Otk[15][0]*c17)+(Otk[16][1]*s17)));
        Otk[17][1] = (((Otk[16][1]*c17)-(Otk[15][0]*s17))-(u[17]*wk[17][0]));
        Otk[18][0] = (((Otk[17][0]*c18)-(Otk[16][2]*s18))-(u[18]*wk[18][2]));
        Otk[18][2] = ((u[18]*wk[18][0])+((Otk[16][2]*c18)+(Otk[17][0]*s18)));
        Otk[19][0] = ((u[19]*wk[19][1])+((Otk[7][1]*s19)+(Otk[8][0]*c19)));
        Otk[19][1] = (((Otk[7][1]*c19)-(Otk[8][0]*s19))-(u[19]*wk[19][0]));
        Otk[20][0] = (((Otk[19][0]*c20)-(Otk[8][2]*s20))-(u[20]*wk[20][2]));
        Otk[20][2] = ((u[20]*wk[20][0])+((Otk[8][2]*c20)+(Otk[19][0]*s20)));
        Otk[21][0] = (((Otk[20][0]*c21)-(Otk[20][2]*s21))-(u[21]*wk[21][2]));
        Otk[21][2] = ((u[21]*wk[21][0])+((Otk[20][0]*s21)+(Otk[20][2]*c21)));
        Otk[22][1] = ((u[22]*wk[22][2])+((Otk[19][1]*c22)+(Otk[21][2]*s22)));
        Otk[22][2] = (((Otk[21][2]*c22)-(Otk[19][1]*s22))-(u[22]*wk[22][1]));
        Otk[23][0] = ((u[23]*wk[23][1])+((Otk[21][0]*c23)+(Otk[22][1]*s23)));
        Otk[23][1] = (((Otk[22][1]*c23)-(Otk[21][0]*s23))-(u[23]*wk[23][0]));
        Otk[24][0] = (((Otk[23][0]*c24)-(Otk[22][2]*s24))-(u[24]*wk[24][2]));
        Otk[24][2] = ((u[24]*wk[24][0])+((Otk[22][2]*c24)+(Otk[23][0]*s24)));
        Otk[25][1] = (u[25]*wk[25][2]);
        Otk[25][2] = -(u[25]*wk[25][1]);
        Otk[26][0] = ((Otk[25][1]*s26)+(u[26]*wk[26][1]));
        Otk[26][1] = ((Otk[25][1]*c26)-(u[26]*wk[26][0]));
        Otk[27][0] = (((Otk[26][0]*c27)-(Otk[25][2]*s27))-(u[27]*wk[27][2]));
        Otk[27][2] = ((u[27]*wk[27][0])+((Otk[25][2]*c27)+(Otk[26][0]*s27)));
        Otk[28][1] = ((u[28]*wk[28][2])+((Otk[26][1]*c28)+(Otk[27][2]*s28)));
        Otk[28][2] = (((Otk[27][2]*c28)-(Otk[26][1]*s28))-(u[28]*wk[28][1]));
        Otk[29][1] = ((u[29]*wk[29][2])+((Otk[28][1]*c29)+(Otk[28][2]*s29)));
        Otk[29][2] = (((Otk[28][2]*c29)-(Otk[28][1]*s29))-(u[29]*wk[29][1]));
        Otk[30][0] = ((u[30]*wk[30][1])+((Otk[27][0]*c30)+(Otk[29][1]*s30)));
        Otk[30][1] = (((Otk[29][1]*c30)-(Otk[27][0]*s30))-(u[30]*wk[30][0]));
        Otk[31][1] = (u[31]*wk[31][2]);
        Otk[31][2] = -(u[31]*wk[31][1]);
        Otk[32][0] = ((Otk[31][1]*s32)+(u[32]*wk[32][1]));
        Otk[32][1] = ((Otk[31][1]*c32)-(u[32]*wk[32][0]));
        Otk[33][0] = (((Otk[32][0]*c33)-(Otk[31][2]*s33))-(u[33]*wk[33][2]));
        Otk[33][2] = ((u[33]*wk[33][0])+((Otk[31][2]*c33)+(Otk[32][0]*s33)));
        Otk[34][1] = ((u[34]*wk[34][2])+((Otk[32][1]*c34)+(Otk[33][2]*s34)));
        Otk[34][2] = (((Otk[33][2]*c34)-(Otk[32][1]*s34))-(u[34]*wk[34][1]));
        Otk[35][1] = ((u[35]*wk[35][2])+((Otk[34][1]*c35)+(Otk[34][2]*s35)));
        Otk[35][2] = (((Otk[34][2]*c35)-(Otk[34][1]*s35))-(u[35]*wk[35][1]));
        Otk[36][0] = ((u[36]*wk[36][1])+((Otk[33][0]*c36)+(Otk[35][1]*s36)));
        Otk[36][1] = (((Otk[35][1]*c36)-(Otk[33][0]*s36))-(u[36]*wk[36][0]));
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[5][0] = -((.05*(u[3]*u[5]))+(.1206*(u[3]*u[4])));
        Atk[5][1] = ((.1206*(u[3]*u[3]))+(u[5]*Wkrpk[5][0]));
        Atk[5][2] = ((.05*(u[3]*u[3]))-(u[4]*Wkrpk[5][0]));
        AiOiWi[6][0] = (Atk[5][0]+((.05*(u[3]*u[5]))+(.1206*(u[3]*u[4]))));
        AiOiWi[6][1] = (Atk[5][1]+((u[5]*Wirk[6][0])-(.1206*(u[3]*u[3]))));
        AiOiWi[6][2] = (Atk[5][2]-((.05*(u[3]*u[3]))+(u[4]*Wirk[6][0])));
        Atk[6][1] = ((AiOiWi[6][1]*c6)+(AiOiWi[6][2]*s6));
        Atk[6][2] = ((AiOiWi[6][2]*c6)-(AiOiWi[6][1]*s6));
        Atk[7][0] = ((AiOiWi[6][0]*c7)+(Atk[6][1]*s7));
        Atk[7][1] = ((Atk[6][1]*c7)-(AiOiWi[6][0]*s7));
        Atk[8][0] = (((Atk[7][0]*c8)-(Atk[6][2]*s8))+(((.14625*(wk[8][0]*
          wk[8][1]))-(.0351*(wk[8][0]*wk[8][2])))-((.0351*Otk[7][1])+(.14625*
          Otk[8][2]))));
        Atk[8][1] = (Atk[7][1]+((.0351*Otk[8][0])+((wk[8][2]*Wkrpk[8][0])-(
          .14625*(wk[8][0]*wk[8][0])))));
        Atk[8][2] = (((.14625*Otk[8][0])+((.0351*(wk[8][0]*wk[8][0]))-(wk[8][1]*
          Wkrpk[8][0])))+((Atk[6][2]*c8)+(Atk[7][0]*s8)));
        AiOiWi[9][0] = (Atk[8][0]+(((.24635*(wk[8][0]*wk[8][1]))-(.0013*(
          wk[8][0]*wk[8][2])))-((.0013*Otk[7][1])+(.24635*Otk[8][2]))));
        AiOiWi[9][1] = (Atk[8][1]+((.0013*Otk[8][0])+((Wirk[9][0]*wk[8][2])-(
          .24635*(wk[8][0]*wk[8][0])))));
        AiOiWi[9][2] = (Atk[8][2]+((.24635*Otk[8][0])+((.0013*(wk[8][0]*wk[8][0]
          ))-(Wirk[9][0]*wk[8][1]))));
        Atk[9][1] = ((AiOiWi[9][1]*c9)+(AiOiWi[9][2]*s9));
        Atk[9][2] = ((AiOiWi[9][2]*c9)-(AiOiWi[9][1]*s9));
        Atk[10][0] = ((AiOiWi[9][0]*c10)+(Atk[9][1]*s10));
        Atk[10][1] = ((Atk[9][1]*c10)-(AiOiWi[9][0]*s10));
        Atk[11][0] = (((Atk[10][0]*c11)-(Atk[9][2]*s11))+(((.0065*Otk[10][1])-(
          .0442*Otk[11][2]))+((.0065*(wk[11][0]*wk[11][2]))+(.0442*(wk[11][0]*
          wk[11][1])))));
        Atk[11][1] = (Atk[10][1]+(((wk[11][2]*Wkrpk[11][0])-(.0442*(wk[11][0]*
          wk[11][0])))-(.0065*Otk[11][0])));
        Atk[11][2] = (((.0442*Otk[11][0])-((.0065*(wk[11][0]*wk[11][0]))+(
          wk[11][1]*Wkrpk[11][0])))+((Atk[9][2]*c11)+(Atk[10][0]*s11)));
        AiOiWi[12][0] = (Atk[11][0]+(((.0065*Otk[10][1])-(.0442*Otk[11][2]))+((
          .0065*(wk[11][0]*wk[11][2]))+(.0442*(wk[11][0]*wk[11][1])))));
        AiOiWi[12][1] = (Atk[11][1]+(((Wirk[12][0]*wk[11][2])-(.0442*(wk[11][0]*
          wk[11][0])))-(.0065*Otk[11][0])));
        AiOiWi[12][2] = (Atk[11][2]+((.0442*Otk[11][0])-((.0065*(wk[11][0]*
          wk[11][0]))+(Wirk[12][0]*wk[11][1]))));
        Atk[12][0] = (AiOiWi[12][0]+(((.0312*Otk[12][1])-(.078*Otk[12][2]))+((
          .0312*(wk[12][0]*wk[12][2]))+(.078*(wk[12][0]*wk[12][1])))));
        Atk[12][1] = (((AiOiWi[12][1]*c12)+(AiOiWi[12][2]*s12))+(((wk[12][2]*
          Wkrpk[12][0])-(.078*(wk[12][0]*wk[12][0])))-(.0312*Otk[11][0])));
        Atk[12][2] = (((.078*Otk[11][0])-((.0312*(wk[12][0]*wk[12][0]))+(
          wk[12][1]*Wkrpk[12][0])))+((AiOiWi[12][2]*c12)-(AiOiWi[12][1]*s12)));
        AiOiWi[13][0] = (Atk[8][0]+(((.0013*Otk[7][1])-(.18915*Otk[8][2]))+((
          Wirk[13][2]*wk[8][1])-(Wirk[13][1]*wk[8][2]))));
        AiOiWi[13][1] = (Atk[8][1]+(((.1768*Otk[8][2])-(.0013*Otk[8][0]))+((
          Wirk[13][0]*wk[8][2])-(Wirk[13][2]*wk[8][0]))));
        AiOiWi[13][2] = (Atk[8][2]+(((.18915*Otk[8][0])-(.1768*Otk[7][1]))+((
          Wirk[13][1]*wk[8][0])-(Wirk[13][0]*wk[8][1]))));
        Atk[13][0] = ((AiOiWi[13][0]*c13)+(AiOiWi[13][1]*s13));
        Atk[13][1] = ((AiOiWi[13][1]*c13)-(AiOiWi[13][0]*s13));
        Atk[14][0] = (((.0013*Otk[13][1])-((.1326*(wk[14][1]*wk[14][1]))+(
          wk[14][2]*Wkrpk[14][1])))+((Atk[13][0]*c14)-(AiOiWi[13][2]*s14)));
        Atk[14][1] = (Atk[13][1]+(((.0013*(wk[14][1]*wk[14][2]))+(.1326*(
          wk[14][0]*wk[14][1])))+((.1326*Otk[14][2])-(.0013*Otk[14][0]))));
        Atk[14][2] = (((AiOiWi[13][2]*c14)+(Atk[13][0]*s14))+(((wk[14][0]*
          Wkrpk[14][1])-(.0013*(wk[14][1]*wk[14][1])))-(.1326*Otk[13][1])));
        AiOiWi[15][0] = (Atk[14][0]+((.0013*Otk[13][1])-((.1326*(wk[14][1]*
          wk[14][1]))+(Wirk[15][1]*wk[14][2]))));
        AiOiWi[15][1] = (Atk[14][1]+(((.0013*(wk[14][1]*wk[14][2]))+(.1326*(
          wk[14][0]*wk[14][1])))+((.1326*Otk[14][2])-(.0013*Otk[14][0]))));
        AiOiWi[15][2] = (Atk[14][2]+(((Wirk[15][1]*wk[14][0])-(.0013*(wk[14][1]*
          wk[14][1])))-(.1326*Otk[13][1])));
        Atk[15][0] = ((AiOiWi[15][0]*c15)-(AiOiWi[15][2]*s15));
        Atk[15][2] = ((AiOiWi[15][0]*s15)+(AiOiWi[15][2]*c15));
        Atk[16][0] = (Atk[15][0]+(((wk[16][1]*Wkrpk[16][2])-(.1378*(wk[16][2]*
          wk[16][2])))-(.0039*Otk[16][2])));
        Atk[16][1] = (((.1378*Otk[16][2])-((.0039*(wk[16][2]*wk[16][2]))+(
          wk[16][0]*Wkrpk[16][2])))+((AiOiWi[15][1]*c16)+(Atk[15][2]*s16)));
        Atk[16][2] = (((Atk[15][2]*c16)-(AiOiWi[15][1]*s16))+(((.0039*Otk[15][0]
          )-(.1378*Otk[16][1]))+((.0039*(wk[16][1]*wk[16][2]))+(.1378*(wk[16][0]
          *wk[16][2])))));
        AiOiWi[17][0] = (Atk[16][0]+(((Wirk[17][2]*wk[16][1])-(.1378*(wk[16][2]*
          wk[16][2])))-(.0039*Otk[16][2])));
        AiOiWi[17][1] = (Atk[16][1]+((.1378*Otk[16][2])-((.0039*(wk[16][2]*
          wk[16][2]))+(Wirk[17][2]*wk[16][0]))));
        AiOiWi[17][2] = (Atk[16][2]+(((.0039*Otk[15][0])-(.1378*Otk[16][1]))+((
          .0039*(wk[16][1]*wk[16][2]))+(.1378*(wk[16][0]*wk[16][2])))));
        Atk[17][0] = ((AiOiWi[17][0]*c17)+(AiOiWi[17][1]*s17));
        Atk[17][1] = ((AiOiWi[17][1]*c17)-(AiOiWi[17][0]*s17));
        Atk[18][0] = (((Atk[17][0]*c18)-(AiOiWi[17][2]*s18))-(.065*((wk[18][1]*
          wk[18][1])+(wk[18][2]*wk[18][2]))));
        Atk[18][1] = (Atk[17][1]+(.065*(Otk[18][2]+(wk[18][0]*wk[18][1]))));
        Atk[18][2] = ((.065*((wk[18][0]*wk[18][2])-Otk[17][1]))+((AiOiWi[17][2]*
          c18)+(Atk[17][0]*s18)));
        AiOiWi[19][0] = (Atk[8][0]+(((.0013*Otk[7][1])-(.18915*Otk[8][2]))+((
          Wirk[19][2]*wk[8][1])-(Wirk[19][1]*wk[8][2]))));
        AiOiWi[19][1] = (Atk[8][1]+(((Wirk[19][0]*wk[8][2])-(Wirk[19][2]*
          wk[8][0]))-((.0013*Otk[8][0])+(.1768*Otk[8][2]))));
        AiOiWi[19][2] = (Atk[8][2]+(((.1768*Otk[7][1])+(.18915*Otk[8][0]))+((
          Wirk[19][1]*wk[8][0])-(Wirk[19][0]*wk[8][1]))));
        Atk[19][0] = ((AiOiWi[19][0]*c19)+(AiOiWi[19][1]*s19));
        Atk[19][1] = ((AiOiWi[19][1]*c19)-(AiOiWi[19][0]*s19));
        Atk[20][0] = (((.0013*Otk[19][1])+((.1326*(wk[20][1]*wk[20][1]))-(
          wk[20][2]*Wkrpk[20][1])))+((Atk[19][0]*c20)-(AiOiWi[19][2]*s20)));
        Atk[20][1] = (Atk[19][1]+(((.0013*(wk[20][1]*wk[20][2]))-(.1326*(
          wk[20][0]*wk[20][1])))-((.0013*Otk[20][0])+(.1326*Otk[20][2]))));
        Atk[20][2] = (((.1326*Otk[19][1])+((wk[20][0]*Wkrpk[20][1])-(.0013*(
          wk[20][1]*wk[20][1]))))+((AiOiWi[19][2]*c20)+(Atk[19][0]*s20)));
        AiOiWi[21][0] = (Atk[20][0]+((.0013*Otk[19][1])+((.1326*(wk[20][1]*
          wk[20][1]))-(Wirk[21][1]*wk[20][2]))));
        AiOiWi[21][1] = (Atk[20][1]+(((.0013*(wk[20][1]*wk[20][2]))-(.1326*(
          wk[20][0]*wk[20][1])))-((.0013*Otk[20][0])+(.1326*Otk[20][2]))));
        AiOiWi[21][2] = (Atk[20][2]+((.1326*Otk[19][1])+((Wirk[21][1]*wk[20][0])
          -(.0013*(wk[20][1]*wk[20][1])))));
        Atk[21][0] = ((AiOiWi[21][0]*c21)-(AiOiWi[21][2]*s21));
        Atk[21][2] = ((AiOiWi[21][0]*s21)+(AiOiWi[21][2]*c21));
        Atk[22][0] = (Atk[21][0]+(((.1378*(wk[22][2]*wk[22][2]))+(wk[22][1]*
          Wkrpk[22][2]))-(.0039*Otk[22][2])));
        Atk[22][1] = (((AiOiWi[21][1]*c22)+(Atk[21][2]*s22))-((.1378*Otk[22][2])
          +((.0039*(wk[22][2]*wk[22][2]))+(wk[22][0]*Wkrpk[22][2]))));
        Atk[22][2] = (((Atk[21][2]*c22)-(AiOiWi[21][1]*s22))+(((.0039*Otk[21][0]
          )+(.1378*Otk[22][1]))+((.0039*(wk[22][1]*wk[22][2]))-(.1378*(wk[22][0]
          *wk[22][2])))));
        AiOiWi[23][0] = (Atk[22][0]+(((.1378*(wk[22][2]*wk[22][2]))+(Wirk[23][2]
          *wk[22][1]))-(.0039*Otk[22][2])));
        AiOiWi[23][1] = (Atk[22][1]-((.1378*Otk[22][2])+((.0039*(wk[22][2]*
          wk[22][2]))+(Wirk[23][2]*wk[22][0]))));
        AiOiWi[23][2] = (Atk[22][2]+(((.0039*Otk[21][0])+(.1378*Otk[22][1]))+((
          .0039*(wk[22][1]*wk[22][2]))-(.1378*(wk[22][0]*wk[22][2])))));
        Atk[23][0] = ((AiOiWi[23][0]*c23)+(AiOiWi[23][1]*s23));
        Atk[23][1] = ((AiOiWi[23][1]*c23)-(AiOiWi[23][0]*s23));
        Atk[24][0] = ((.065*((wk[24][1]*wk[24][1])+(wk[24][2]*wk[24][2])))+((
          Atk[23][0]*c24)-(AiOiWi[23][2]*s24)));
        Atk[24][1] = (Atk[23][1]-(.065*(Otk[24][2]+(wk[24][0]*wk[24][1]))));
        Atk[24][2] = ((.065*(Otk[23][1]-(wk[24][0]*wk[24][2])))+((AiOiWi[23][2]*
          c24)+(Atk[23][0]*s24)));
        AiOiWi[25][0] = (Atk[5][0]+((u[4]*Wirk[25][2])-(u[5]*Wirk[25][1])));
        AiOiWi[25][1] = (Atk[5][1]+((u[5]*Wirk[25][0])-(u[3]*Wirk[25][2])));
        AiOiWi[25][2] = (Atk[5][2]+((u[3]*Wirk[25][1])-(u[4]*Wirk[25][0])));
        Atk[25][1] = ((AiOiWi[25][1]*c25)+(AiOiWi[25][2]*s25));
        Atk[25][2] = ((AiOiWi[25][2]*c25)-(AiOiWi[25][1]*s25));
        Atk[26][0] = ((AiOiWi[25][0]*c26)+(Atk[25][1]*s26));
        Atk[26][1] = ((Atk[25][1]*c26)-(AiOiWi[25][0]*s26));
        Atk[27][0] = (((Atk[26][0]*c27)-(Atk[25][2]*s27))+(((.0143*Otk[26][1])+(
          .2379*Otk[27][2]))+((wk[27][1]*Wkrpk[27][2])-(wk[27][2]*Wkrpk[27][1]))
          ));
        Atk[27][1] = (Atk[26][1]+(((wk[27][2]*Wkrpk[27][0])-(wk[27][0]*
          Wkrpk[27][2]))-((.0143*Otk[27][0])+(.0169*Otk[27][2]))));
        Atk[27][2] = (((Atk[25][2]*c27)+(Atk[26][0]*s27))+(((.0169*Otk[26][1])-(
          .2379*Otk[27][0]))+((wk[27][0]*Wkrpk[27][1])-(wk[27][1]*Wkrpk[27][0]))
          ));
        AiOiWi[28][0] = (Atk[27][0]+(((.0143*Otk[26][1])+(.2379*Otk[27][2]))+((
          Wirk[28][2]*wk[27][1])-(Wirk[28][1]*wk[27][2]))));
        AiOiWi[28][1] = (Atk[27][1]+(((Wirk[28][0]*wk[27][2])-(Wirk[28][2]*
          wk[27][0]))-((.0143*Otk[27][0])+(.0169*Otk[27][2]))));
        AiOiWi[28][2] = (Atk[27][2]+(((.0169*Otk[26][1])-(.2379*Otk[27][0]))+((
          Wirk[28][1]*wk[27][0])-(Wirk[28][0]*wk[27][1]))));
        Atk[28][0] = (AiOiWi[28][0]+(((.2158*Otk[28][2])-(.0039*Otk[28][1]))+((
          wk[28][1]*Wkrpk[28][2])-(wk[28][2]*Wkrpk[28][1]))));
        Atk[28][1] = (((AiOiWi[28][1]*c28)+(AiOiWi[28][2]*s28))+(((.0039*
          Otk[27][0])-(.0078*Otk[28][2]))+((wk[28][2]*Wkrpk[28][0])-(wk[28][0]*
          Wkrpk[28][2]))));
        Atk[28][2] = (((AiOiWi[28][2]*c28)-(AiOiWi[28][1]*s28))+(((.0078*
          Otk[28][1])-(.2158*Otk[27][0]))+((wk[28][0]*Wkrpk[28][1])-(wk[28][1]*
          Wkrpk[28][0]))));
        AiOiWi[29][0] = (Atk[28][0]+(((.2158*Otk[28][2])-(.0039*Otk[28][1]))+((
          Wirk[29][2]*wk[28][1])-(Wirk[29][1]*wk[28][2]))));
        AiOiWi[29][1] = (Atk[28][1]+(((.0039*Otk[27][0])-(.0078*Otk[28][2]))+((
          Wirk[29][0]*wk[28][2])-(Wirk[29][2]*wk[28][0]))));
        AiOiWi[29][2] = (Atk[28][2]+(((.0078*Otk[28][1])-(.2158*Otk[27][0]))+((
          Wirk[29][1]*wk[28][0])-(Wirk[29][0]*wk[28][1]))));
        Atk[29][1] = ((AiOiWi[29][1]*c29)+(AiOiWi[29][2]*s29));
        Atk[29][2] = ((AiOiWi[29][2]*c29)-(AiOiWi[29][1]*s29));
        Atk[30][0] = (((AiOiWi[29][0]*c30)+(Atk[29][1]*s30))+(((.039*Otk[30][1])
          +(.0442*Otk[29][2]))+((.039*(wk[30][0]*wk[30][2]))-(.0442*(wk[30][0]*
          wk[30][1])))));
        Atk[30][1] = (((Atk[29][1]*c30)-(AiOiWi[29][0]*s30))+(((.0442*(wk[30][0]
          *wk[30][0]))+(wk[30][2]*Wkrpk[30][0]))-(.039*Otk[30][0])));
        Atk[30][2] = (Atk[29][2]-((.0442*Otk[30][0])+((.039*(wk[30][0]*wk[30][0]
          ))+(wk[30][1]*Wkrpk[30][0]))));
        AiOiWi[31][0] = (Atk[5][0]+((u[4]*Wirk[31][2])-(u[5]*Wirk[31][1])));
        AiOiWi[31][1] = (Atk[5][1]+((u[5]*Wirk[31][0])-(u[3]*Wirk[31][2])));
        AiOiWi[31][2] = (Atk[5][2]+((u[3]*Wirk[31][1])-(u[4]*Wirk[31][0])));
        Atk[31][1] = ((AiOiWi[31][1]*c31)+(AiOiWi[31][2]*s31));
        Atk[31][2] = ((AiOiWi[31][2]*c31)-(AiOiWi[31][1]*s31));
        Atk[32][0] = ((AiOiWi[31][0]*c32)+(Atk[31][1]*s32));
        Atk[32][1] = ((Atk[31][1]*c32)-(AiOiWi[31][0]*s32));
        Atk[33][0] = (((Atk[32][0]*c33)-(Atk[31][2]*s33))+(((.0143*Otk[32][1])+(
          .2379*Otk[33][2]))+((wk[33][1]*Wkrpk[33][2])-(wk[33][2]*Wkrpk[33][1]))
          ));
        Atk[33][1] = (Atk[32][1]+(((.0169*Otk[33][2])-(.0143*Otk[33][0]))+((
          wk[33][2]*Wkrpk[33][0])-(wk[33][0]*Wkrpk[33][2]))));
        Atk[33][2] = (((Atk[31][2]*c33)+(Atk[32][0]*s33))+(((wk[33][0]*
          Wkrpk[33][1])-(wk[33][1]*Wkrpk[33][0]))-((.0169*Otk[32][1])+(.2379*
          Otk[33][0]))));
        AiOiWi[34][0] = (Atk[33][0]+(((.0143*Otk[32][1])+(.2379*Otk[33][2]))+((
          Wirk[34][2]*wk[33][1])-(Wirk[34][1]*wk[33][2]))));
        AiOiWi[34][1] = (Atk[33][1]+(((.0169*Otk[33][2])-(.0143*Otk[33][0]))+((
          Wirk[34][0]*wk[33][2])-(Wirk[34][2]*wk[33][0]))));
        AiOiWi[34][2] = (Atk[33][2]+(((Wirk[34][1]*wk[33][0])-(Wirk[34][0]*
          wk[33][1]))-((.0169*Otk[32][1])+(.2379*Otk[33][0]))));
        Atk[34][0] = (AiOiWi[34][0]+(((.2158*Otk[34][2])-(.0039*Otk[34][1]))+((
          wk[34][1]*Wkrpk[34][2])-(wk[34][2]*Wkrpk[34][1]))));
        Atk[34][1] = (((AiOiWi[34][1]*c34)+(AiOiWi[34][2]*s34))+(((.0039*
          Otk[33][0])+(.0078*Otk[34][2]))+((wk[34][2]*Wkrpk[34][0])-(wk[34][0]*
          Wkrpk[34][2]))));
        Atk[34][2] = (((AiOiWi[34][2]*c34)-(AiOiWi[34][1]*s34))+(((wk[34][0]*
          Wkrpk[34][1])-(wk[34][1]*Wkrpk[34][0]))-((.0078*Otk[34][1])+(.2158*
          Otk[33][0]))));
        AiOiWi[35][0] = (Atk[34][0]+(((.2158*Otk[34][2])-(.0039*Otk[34][1]))+((
          Wirk[35][2]*wk[34][1])-(Wirk[35][1]*wk[34][2]))));
        AiOiWi[35][1] = (Atk[34][1]+(((.0039*Otk[33][0])+(.0078*Otk[34][2]))+((
          Wirk[35][0]*wk[34][2])-(Wirk[35][2]*wk[34][0]))));
        AiOiWi[35][2] = (Atk[34][2]+(((Wirk[35][1]*wk[34][0])-(Wirk[35][0]*
          wk[34][1]))-((.0078*Otk[34][1])+(.2158*Otk[33][0]))));
        Atk[35][1] = ((AiOiWi[35][1]*c35)+(AiOiWi[35][2]*s35));
        Atk[35][2] = ((AiOiWi[35][2]*c35)-(AiOiWi[35][1]*s35));
        Atk[36][0] = (((AiOiWi[35][0]*c36)+(Atk[35][1]*s36))+(((.039*Otk[36][1])
          +(.0442*Otk[35][2]))+((.039*(wk[36][0]*wk[36][2]))-(.0442*(wk[36][0]*
          wk[36][1])))));
        Atk[36][1] = (((Atk[35][1]*c36)-(AiOiWi[35][0]*s36))+(((.0442*(wk[36][0]
          *wk[36][0]))+(wk[36][2]*Wkrpk[36][0]))-(.039*Otk[36][0])));
        Atk[36][2] = (Atk[35][2]-((.0442*Otk[36][0])+((.039*(wk[36][0]*wk[36][0]
          ))+(wk[36][1]*Wkrpk[36][0]))));
        inerflg = 1;
    }
/*
 Used 0.91 seconds CPU time,
 16384 additional bytes of memory.
 Equations contain  475 adds/subtracts/negates
                    668 multiplies
                      0 divides
                    187 assignments
*/
}

void skel18dofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        skel18doltau();
        skel18doiner();
/*
Compute Fstar (forces)
*/
        Fstar[5][0] = ((16.61*Atk[5][0])-ufk[0][0]);
        Fstar[5][1] = ((16.61*Atk[5][1])-ufk[0][1]);
        Fstar[5][2] = ((16.61*Atk[5][2])-ufk[0][2]);
        Fstar[8][0] = ((29.27*Atk[8][0])-ufk[1][0]);
        Fstar[8][1] = ((29.27*Atk[8][1])-ufk[1][1]);
        Fstar[8][2] = ((29.27*Atk[8][2])-ufk[1][2]);
        Fstar[11][0] = (Atk[11][0]-ufk[2][0]);
        Fstar[11][1] = (Atk[11][1]-ufk[2][1]);
        Fstar[11][2] = (Atk[11][2]-ufk[2][2]);
        Fstar[12][0] = ((5.89*Atk[12][0])-ufk[3][0]);
        Fstar[12][1] = ((5.89*Atk[12][1])-ufk[3][1]);
        Fstar[12][2] = ((5.89*Atk[12][2])-ufk[3][2]);
        Fstar[14][0] = ((2.79*Atk[14][0])-ufk[4][0]);
        Fstar[14][1] = ((2.79*Atk[14][1])-ufk[4][1]);
        Fstar[14][2] = ((2.79*Atk[14][2])-ufk[4][2]);
        Fstar[16][0] = ((1.21*Atk[16][0])-ufk[5][0]);
        Fstar[16][1] = ((1.21*Atk[16][1])-ufk[5][1]);
        Fstar[16][2] = ((1.21*Atk[16][2])-ufk[5][2]);
        Fstar[18][0] = ((.55*Atk[18][0])-ufk[6][0]);
        Fstar[18][1] = ((.55*Atk[18][1])-ufk[6][1]);
        Fstar[18][2] = ((.55*Atk[18][2])-ufk[6][2]);
        Fstar[20][0] = ((2.79*Atk[20][0])-ufk[7][0]);
        Fstar[20][1] = ((2.79*Atk[20][1])-ufk[7][1]);
        Fstar[20][2] = ((2.79*Atk[20][2])-ufk[7][2]);
        Fstar[22][0] = ((1.21*Atk[22][0])-ufk[8][0]);
        Fstar[22][1] = ((1.21*Atk[22][1])-ufk[8][1]);
        Fstar[22][2] = ((1.21*Atk[22][2])-ufk[8][2]);
        Fstar[24][0] = ((.55*Atk[24][0])-ufk[9][0]);
        Fstar[24][1] = ((.55*Atk[24][1])-ufk[9][1]);
        Fstar[24][2] = ((.55*Atk[24][2])-ufk[9][2]);
        Fstar[27][0] = ((8.35*Atk[27][0])-ufk[10][0]);
        Fstar[27][1] = ((8.35*Atk[27][1])-ufk[10][1]);
        Fstar[27][2] = ((8.35*Atk[27][2])-ufk[10][2]);
        Fstar[28][0] = ((4.16*Atk[28][0])-ufk[11][0]);
        Fstar[28][1] = ((4.16*Atk[28][1])-ufk[11][1]);
        Fstar[28][2] = ((4.16*Atk[28][2])-ufk[11][2]);
        Fstar[30][0] = ((1.34*Atk[30][0])-ufk[12][0]);
        Fstar[30][1] = ((1.34*Atk[30][1])-ufk[12][1]);
        Fstar[30][2] = ((1.34*Atk[30][2])-ufk[12][2]);
        Fstar[33][0] = ((8.35*Atk[33][0])-ufk[13][0]);
        Fstar[33][1] = ((8.35*Atk[33][1])-ufk[13][1]);
        Fstar[33][2] = ((8.35*Atk[33][2])-ufk[13][2]);
        Fstar[34][0] = ((4.16*Atk[34][0])-ufk[14][0]);
        Fstar[34][1] = ((4.16*Atk[34][1])-ufk[14][1]);
        Fstar[34][2] = ((4.16*Atk[34][2])-ufk[14][2]);
        Fstar[36][0] = ((1.34*Atk[36][0])-ufk[15][0]);
        Fstar[36][1] = ((1.34*Atk[36][1])-ufk[15][1]);
        Fstar[36][2] = ((1.34*Atk[36][2])-ufk[15][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = (WkIkWk[5][0]-utk[0][0]);
        Tstar[5][1] = (WkIkWk[5][1]-utk[0][1]);
        Tstar[5][2] = (WkIkWk[5][2]-utk[0][2]);
        Tstar[8][0] = ((WkIkWk[8][0]+(.63*Otk[8][0]))-utk[1][0]);
        Tstar[8][1] = ((WkIkWk[8][1]+(.32*Otk[7][1]))-utk[1][1]);
        Tstar[8][2] = ((WkIkWk[8][2]+(.73*Otk[8][2]))-utk[1][2]);
        Tstar[11][0] = ((WkIkWk[11][0]+(.006*Otk[11][0]))-utk[2][0]);
        Tstar[11][1] = ((.001*Otk[10][1])-utk[2][1]);
        Tstar[11][2] = ((WkIkWk[11][2]+(.006*Otk[11][2]))-utk[2][2]);
        Tstar[12][0] = ((WkIkWk[12][0]+(.033*Otk[11][0]))-utk[3][0]);
        Tstar[12][1] = ((WkIkWk[12][1]+(.023*Otk[12][1]))-utk[3][1]);
        Tstar[12][2] = ((WkIkWk[12][2]+(.03*Otk[12][2]))-utk[3][2]);
        Tstar[14][0] = ((.005*Otk[14][0])-utk[4][0]);
        Tstar[14][1] = ((WkIkWk[14][1]+(.025*Otk[13][1]))-utk[4][1]);
        Tstar[14][2] = ((WkIkWk[14][2]+(.025*Otk[14][2]))-utk[4][2]);
        Tstar[16][0] = ((WkIkWk[16][0]+(.0012*Otk[15][0]))-utk[5][0]);
        Tstar[16][1] = ((WkIkWk[16][1]+(.0054*Otk[16][1]))-utk[5][1]);
        Tstar[16][2] = ((WkIkWk[16][2]+(.005*Otk[16][2]))-utk[5][2]);
        Tstar[18][0] = ((WkIkWk[18][0]+(.0005*Otk[18][0]))-utk[6][0]);
        Tstar[18][1] = ((WkIkWk[18][1]+(.002*Otk[17][1]))-utk[6][1]);
        Tstar[18][2] = ((WkIkWk[18][2]+(.0016*Otk[18][2]))-utk[6][2]);
        Tstar[20][0] = ((.005*Otk[20][0])-utk[7][0]);
        Tstar[20][1] = ((WkIkWk[20][1]+(.025*Otk[19][1]))-utk[7][1]);
        Tstar[20][2] = ((WkIkWk[20][2]+(.025*Otk[20][2]))-utk[7][2]);
        Tstar[22][0] = ((WkIkWk[22][0]+(.0012*Otk[21][0]))-utk[8][0]);
        Tstar[22][1] = ((WkIkWk[22][1]+(.0054*Otk[22][1]))-utk[8][1]);
        Tstar[22][2] = ((WkIkWk[22][2]+(.005*Otk[22][2]))-utk[8][2]);
        Tstar[24][0] = ((WkIkWk[24][0]+(.0005*Otk[24][0]))-utk[9][0]);
        Tstar[24][1] = ((WkIkWk[24][1]+(.002*Otk[23][1]))-utk[9][1]);
        Tstar[24][2] = ((WkIkWk[24][2]+(.0016*Otk[24][2]))-utk[9][2]);
        Tstar[27][0] = ((WkIkWk[27][0]+(.16*Otk[27][0]))-utk[10][0]);
        Tstar[27][1] = ((WkIkWk[27][1]+(.025*Otk[26][1]))-utk[10][1]);
        Tstar[27][2] = ((WkIkWk[27][2]+(.15*Otk[27][2]))-utk[10][2]);
        Tstar[28][0] = ((WkIkWk[28][0]+(.056*Otk[27][0]))-utk[11][0]);
        Tstar[28][1] = ((WkIkWk[28][1]+(.007*Otk[28][1]))-utk[11][1]);
        Tstar[28][2] = ((WkIkWk[28][2]+(.055*Otk[28][2]))-utk[11][2]);
        Tstar[30][0] = ((WkIkWk[30][0]+(.0075*Otk[30][0]))-utk[12][0]);
        Tstar[30][1] = ((WkIkWk[30][1]+(.007*Otk[30][1]))-utk[12][1]);
        Tstar[30][2] = ((WkIkWk[30][2]+(.0018*Otk[29][2]))-utk[12][2]);
        Tstar[33][0] = ((WkIkWk[33][0]+(.16*Otk[33][0]))-utk[13][0]);
        Tstar[33][1] = ((WkIkWk[33][1]+(.025*Otk[32][1]))-utk[13][1]);
        Tstar[33][2] = ((WkIkWk[33][2]+(.15*Otk[33][2]))-utk[13][2]);
        Tstar[34][0] = ((WkIkWk[34][0]+(.056*Otk[33][0]))-utk[14][0]);
        Tstar[34][1] = ((WkIkWk[34][1]+(.007*Otk[34][1]))-utk[14][1]);
        Tstar[34][2] = ((WkIkWk[34][2]+(.055*Otk[34][2]))-utk[14][2]);
        Tstar[36][0] = ((WkIkWk[36][0]+(.0075*Otk[36][0]))-utk[15][0]);
        Tstar[36][1] = ((WkIkWk[36][1]+(.007*Otk[36][1]))-utk[15][1]);
        Tstar[36][2] = ((WkIkWk[36][2]+(.0018*Otk[35][2]))-utk[15][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        skel18dovpk();
        temp[0] = (((Fstar[12][2]*Vpk[0][12][2])+((Fstar[12][0]*Vpk[0][11][0])+(
          Fstar[12][1]*Vpk[0][12][1])))+(((Fstar[11][2]*Vpk[0][11][2])+((
          Fstar[11][0]*Vpk[0][11][0])+(Fstar[11][1]*Vpk[0][10][1])))+(((
          Cik[3][0][2]*Fstar[5][2])+((Cik[3][0][0]*Fstar[5][0])+(Cik[3][0][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[0][8][2])+((Fstar[8][0]*Vpk[0][8][0])
          +(Fstar[8][1]*Vpk[0][7][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[0][20][2])+((Fstar[20][0]*Vpk[0][20][0])+(
          Fstar[20][1]*Vpk[0][19][1])))+(((Fstar[18][2]*Vpk[0][18][2])+((
          Fstar[18][0]*Vpk[0][18][0])+(Fstar[18][1]*Vpk[0][17][1])))+(((
          Fstar[16][2]*Vpk[0][16][2])+((Fstar[16][0]*Vpk[0][15][0])+(
          Fstar[16][1]*Vpk[0][16][1])))+(((Fstar[14][2]*Vpk[0][14][2])+((
          Fstar[14][0]*Vpk[0][14][0])+(Fstar[14][1]*Vpk[0][13][1])))+temp[0]))))
          ;
        temp[2] = (((Fstar[28][2]*Vpk[0][28][2])+((Fstar[28][0]*Vpk[0][27][0])+(
          Fstar[28][1]*Vpk[0][28][1])))+(((Fstar[27][2]*Vpk[0][27][2])+((
          Fstar[27][0]*Vpk[0][27][0])+(Fstar[27][1]*Vpk[0][26][1])))+(((
          Fstar[24][2]*Vpk[0][24][2])+((Fstar[24][0]*Vpk[0][24][0])+(
          Fstar[24][1]*Vpk[0][23][1])))+(((Fstar[22][2]*Vpk[0][22][2])+((
          Fstar[22][0]*Vpk[0][21][0])+(Fstar[22][1]*Vpk[0][22][1])))+temp[1]))))
          ;
        fs0[0] = (utau[0]-(((Fstar[36][2]*Vpk[0][35][2])+((Fstar[36][0]*
          Vpk[0][36][0])+(Fstar[36][1]*Vpk[0][36][1])))+(((Fstar[34][2]*
          Vpk[0][34][2])+((Fstar[34][0]*Vpk[0][33][0])+(Fstar[34][1]*
          Vpk[0][34][1])))+(((Fstar[33][2]*Vpk[0][33][2])+((Fstar[33][0]*
          Vpk[0][33][0])+(Fstar[33][1]*Vpk[0][32][1])))+(((Fstar[30][2]*
          Vpk[0][29][2])+((Fstar[30][0]*Vpk[0][30][0])+(Fstar[30][1]*
          Vpk[0][30][1])))+temp[2])))));
        temp[0] = (((Fstar[12][2]*Vpk[1][12][2])+((Fstar[12][0]*Vpk[1][11][0])+(
          Fstar[12][1]*Vpk[1][12][1])))+(((Fstar[11][2]*Vpk[1][11][2])+((
          Fstar[11][0]*Vpk[1][11][0])+(Fstar[11][1]*Vpk[1][10][1])))+(((
          Cik[3][1][2]*Fstar[5][2])+((Cik[3][1][0]*Fstar[5][0])+(Cik[3][1][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[1][8][2])+((Fstar[8][0]*Vpk[1][8][0])
          +(Fstar[8][1]*Vpk[1][7][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[1][20][2])+((Fstar[20][0]*Vpk[1][20][0])+(
          Fstar[20][1]*Vpk[1][19][1])))+(((Fstar[18][2]*Vpk[1][18][2])+((
          Fstar[18][0]*Vpk[1][18][0])+(Fstar[18][1]*Vpk[1][17][1])))+(((
          Fstar[16][2]*Vpk[1][16][2])+((Fstar[16][0]*Vpk[1][15][0])+(
          Fstar[16][1]*Vpk[1][16][1])))+(((Fstar[14][2]*Vpk[1][14][2])+((
          Fstar[14][0]*Vpk[1][14][0])+(Fstar[14][1]*Vpk[1][13][1])))+temp[0]))))
          ;
        temp[2] = (((Fstar[28][2]*Vpk[1][28][2])+((Fstar[28][0]*Vpk[1][27][0])+(
          Fstar[28][1]*Vpk[1][28][1])))+(((Fstar[27][2]*Vpk[1][27][2])+((
          Fstar[27][0]*Vpk[1][27][0])+(Fstar[27][1]*Vpk[1][26][1])))+(((
          Fstar[24][2]*Vpk[1][24][2])+((Fstar[24][0]*Vpk[1][24][0])+(
          Fstar[24][1]*Vpk[1][23][1])))+(((Fstar[22][2]*Vpk[1][22][2])+((
          Fstar[22][0]*Vpk[1][21][0])+(Fstar[22][1]*Vpk[1][22][1])))+temp[1]))))
          ;
        fs0[1] = (utau[1]-(((Fstar[36][2]*Vpk[1][35][2])+((Fstar[36][0]*
          Vpk[1][36][0])+(Fstar[36][1]*Vpk[1][36][1])))+(((Fstar[34][2]*
          Vpk[1][34][2])+((Fstar[34][0]*Vpk[1][33][0])+(Fstar[34][1]*
          Vpk[1][34][1])))+(((Fstar[33][2]*Vpk[1][33][2])+((Fstar[33][0]*
          Vpk[1][33][0])+(Fstar[33][1]*Vpk[1][32][1])))+(((Fstar[30][2]*
          Vpk[1][29][2])+((Fstar[30][0]*Vpk[1][30][0])+(Fstar[30][1]*
          Vpk[1][30][1])))+temp[2])))));
        temp[0] = (((Fstar[12][2]*Vpk[2][12][2])+((Fstar[12][0]*Vpk[2][11][0])+(
          Fstar[12][1]*Vpk[2][12][1])))+(((Fstar[11][2]*Vpk[2][11][2])+((
          Fstar[11][0]*Vpk[2][11][0])+(Fstar[11][1]*Vpk[2][10][1])))+(((
          Cik[3][2][2]*Fstar[5][2])+((Cik[3][2][0]*Fstar[5][0])+(Cik[3][2][1]*
          Fstar[5][1])))+((Fstar[8][2]*Vpk[2][8][2])+((Fstar[8][0]*Vpk[2][8][0])
          +(Fstar[8][1]*Vpk[2][7][1]))))));
        temp[1] = (((Fstar[20][2]*Vpk[2][20][2])+((Fstar[20][0]*Vpk[2][20][0])+(
          Fstar[20][1]*Vpk[2][19][1])))+(((Fstar[18][2]*Vpk[2][18][2])+((
          Fstar[18][0]*Vpk[2][18][0])+(Fstar[18][1]*Vpk[2][17][1])))+(((
          Fstar[16][2]*Vpk[2][16][2])+((Fstar[16][0]*Vpk[2][15][0])+(
          Fstar[16][1]*Vpk[2][16][1])))+(((Fstar[14][2]*Vpk[2][14][2])+((
          Fstar[14][0]*Vpk[2][14][0])+(Fstar[14][1]*Vpk[2][13][1])))+temp[0]))))
          ;
        temp[2] = (((Fstar[28][2]*Vpk[2][28][2])+((Fstar[28][0]*Vpk[2][27][0])+(
          Fstar[28][1]*Vpk[2][28][1])))+(((Fstar[27][2]*Vpk[2][27][2])+((
          Fstar[27][0]*Vpk[2][27][0])+(Fstar[27][1]*Vpk[2][26][1])))+(((
          Fstar[24][2]*Vpk[2][24][2])+((Fstar[24][0]*Vpk[2][24][0])+(
          Fstar[24][1]*Vpk[2][23][1])))+(((Fstar[22][2]*Vpk[2][22][2])+((
          Fstar[22][0]*Vpk[2][21][0])+(Fstar[22][1]*Vpk[2][22][1])))+temp[1]))))
          ;
        fs0[2] = (utau[2]-(((Fstar[36][2]*Vpk[2][35][2])+((Fstar[36][0]*
          Vpk[2][36][0])+(Fstar[36][1]*Vpk[2][36][1])))+(((Fstar[34][2]*
          Vpk[2][34][2])+((Fstar[34][0]*Vpk[2][33][0])+(Fstar[34][1]*
          Vpk[2][34][1])))+(((Fstar[33][2]*Vpk[2][33][2])+((Fstar[33][0]*
          Vpk[2][33][0])+(Fstar[33][1]*Vpk[2][32][1])))+(((Fstar[30][2]*
          Vpk[2][29][2])+((Fstar[30][0]*Vpk[2][30][0])+(Fstar[30][1]*
          Vpk[2][30][1])))+temp[2])))));
        temp[0] = (((Tstar[5][0]+((.05*Fstar[5][1])-(.1206*Fstar[5][2])))+(((
          .14625*(Fstar[8][2]*Wpk[3][8][0]))+((.0351*(Fstar[8][1]*Wpk[3][8][0]))
          +(Fstar[8][0]*Vpk[3][8][0])))+((Tstar[8][2]*Wpk[3][8][2])+((
          Tstar[8][0]*Wpk[3][8][0])-(Tstar[8][1]*s7)))))+(((Fstar[11][2]*
          Vpk[3][11][2])+((Fstar[11][0]*Vpk[3][11][0])+(Fstar[11][1]*
          Vpk[3][11][1])))+((Tstar[11][2]*Wpk[3][11][2])+((Tstar[11][0]*
          Wpk[3][11][0])+(Tstar[11][1]*Wpk[3][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[3][14][2])+((Fstar[14][0]*Vpk[3][14][0])+
          (Fstar[14][1]*Vpk[3][14][1])))+((Tstar[14][2]*Wpk[3][14][2])+((
          Tstar[14][0]*Wpk[3][14][0])+(Tstar[14][1]*Wpk[3][13][1]))))+((((
          Fstar[12][2]*Vpk[3][12][2])+((Fstar[12][0]*Vpk[3][12][0])+(
          Fstar[12][1]*Vpk[3][12][1])))+((Tstar[12][2]*Wpk[3][12][2])+((
          Tstar[12][0]*Wpk[3][11][0])+(Tstar[12][1]*Wpk[3][12][1]))))+temp[0]));
        temp[2] = ((((Fstar[18][2]*Vpk[3][18][2])+((Fstar[18][0]*Vpk[3][18][0])+
          (Fstar[18][1]*Vpk[3][18][1])))+((Tstar[18][2]*Wpk[3][18][2])+((
          Tstar[18][0]*Wpk[3][18][0])+(Tstar[18][1]*Wpk[3][17][1]))))+((((
          Fstar[16][2]*Vpk[3][16][2])+((Fstar[16][0]*Vpk[3][16][0])+(
          Fstar[16][1]*Vpk[3][16][1])))+((Tstar[16][2]*Wpk[3][16][2])+((
          Tstar[16][0]*Wpk[3][15][0])+(Tstar[16][1]*Wpk[3][16][1]))))+temp[1]));
        temp[3] = ((((Fstar[22][2]*Vpk[3][22][2])+((Fstar[22][0]*Vpk[3][22][0])+
          (Fstar[22][1]*Vpk[3][22][1])))+((Tstar[22][2]*Wpk[3][22][2])+((
          Tstar[22][0]*Wpk[3][21][0])+(Tstar[22][1]*Wpk[3][22][1]))))+((((
          Fstar[20][2]*Vpk[3][20][2])+((Fstar[20][0]*Vpk[3][20][0])+(
          Fstar[20][1]*Vpk[3][20][1])))+((Tstar[20][2]*Wpk[3][20][2])+((
          Tstar[20][0]*Wpk[3][20][0])+(Tstar[20][1]*Wpk[3][19][1]))))+temp[2]));
        temp[4] = ((((Fstar[27][2]*Vpk[3][27][2])+((Fstar[27][0]*Vpk[3][27][0])+
          (Fstar[27][1]*Vpk[3][27][1])))+((Tstar[27][2]*Wpk[3][27][2])+((
          Tstar[27][0]*Wpk[3][27][0])-(Tstar[27][1]*s26))))+((((Fstar[24][2]*
          Vpk[3][24][2])+((Fstar[24][0]*Vpk[3][24][0])+(Fstar[24][1]*
          Vpk[3][24][1])))+((Tstar[24][2]*Wpk[3][24][2])+((Tstar[24][0]*
          Wpk[3][24][0])+(Tstar[24][1]*Wpk[3][23][1]))))+temp[3]));
        temp[5] = ((((Fstar[30][2]*Vpk[3][30][2])+((Fstar[30][0]*Vpk[3][30][0])+
          (Fstar[30][1]*Vpk[3][30][1])))+((Tstar[30][2]*Wpk[3][29][2])+((
          Tstar[30][0]*Wpk[3][30][0])+(Tstar[30][1]*Wpk[3][30][1]))))+((((
          Fstar[28][2]*Vpk[3][28][2])+((Fstar[28][0]*Vpk[3][28][0])+(
          Fstar[28][1]*Vpk[3][28][1])))+((Tstar[28][2]*Wpk[3][28][2])+((
          Tstar[28][0]*Wpk[3][27][0])+(Tstar[28][1]*Wpk[3][28][1]))))+temp[4]));
        temp[6] = ((((Fstar[34][2]*Vpk[3][34][2])+((Fstar[34][0]*Vpk[3][34][0])+
          (Fstar[34][1]*Vpk[3][34][1])))+((Tstar[34][2]*Wpk[3][34][2])+((
          Tstar[34][0]*Wpk[3][33][0])+(Tstar[34][1]*Wpk[3][34][1]))))+((((
          Fstar[33][2]*Vpk[3][33][2])+((Fstar[33][0]*Vpk[3][33][0])+(
          Fstar[33][1]*Vpk[3][33][1])))+((Tstar[33][2]*Wpk[3][33][2])+((
          Tstar[33][0]*Wpk[3][33][0])-(Tstar[33][1]*s32))))+temp[5]));
        fs0[3] = (utau[3]-((((Fstar[36][2]*Vpk[3][36][2])+((Fstar[36][0]*
          Vpk[3][36][0])+(Fstar[36][1]*Vpk[3][36][1])))+((Tstar[36][2]*
          Wpk[3][35][2])+((Tstar[36][0]*Wpk[3][36][0])+(Tstar[36][1]*
          Wpk[3][36][1]))))+temp[6]));
        temp[0] = (((Tstar[5][1]-(.05*Fstar[5][0]))+(((.14625*(Fstar[8][2]*
          Wpk[4][8][0]))+((.0351*(Fstar[8][1]*Wpk[4][8][0]))+(Fstar[8][0]*
          Vpk[4][8][0])))+((Tstar[8][2]*Wpk[4][8][2])+((Tstar[8][0]*Wpk[4][8][0]
          )+(Tstar[8][1]*Wpk[4][7][1])))))+(((Fstar[11][2]*Vpk[4][11][2])+((
          Fstar[11][0]*Vpk[4][11][0])+(Fstar[11][1]*Vpk[4][11][1])))+((
          Tstar[11][2]*Wpk[4][11][2])+((Tstar[11][0]*Wpk[4][11][0])+(
          Tstar[11][1]*Wpk[4][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[4][14][2])+((Fstar[14][0]*Vpk[4][14][0])+
          (Fstar[14][1]*Vpk[4][14][1])))+((Tstar[14][2]*Wpk[4][14][2])+((
          Tstar[14][0]*Wpk[4][14][0])+(Tstar[14][1]*Wpk[4][13][1]))))+((((
          Fstar[12][2]*Vpk[4][12][2])+((Fstar[12][0]*Vpk[4][12][0])+(
          Fstar[12][1]*Vpk[4][12][1])))+((Tstar[12][2]*Wpk[4][12][2])+((
          Tstar[12][0]*Wpk[4][11][0])+(Tstar[12][1]*Wpk[4][12][1]))))+temp[0]));
        temp[2] = ((((Fstar[18][2]*Vpk[4][18][2])+((Fstar[18][0]*Vpk[4][18][0])+
          (Fstar[18][1]*Vpk[4][18][1])))+((Tstar[18][2]*Wpk[4][18][2])+((
          Tstar[18][0]*Wpk[4][18][0])+(Tstar[18][1]*Wpk[4][17][1]))))+((((
          Fstar[16][2]*Vpk[4][16][2])+((Fstar[16][0]*Vpk[4][16][0])+(
          Fstar[16][1]*Vpk[4][16][1])))+((Tstar[16][2]*Wpk[4][16][2])+((
          Tstar[16][0]*Wpk[4][15][0])+(Tstar[16][1]*Wpk[4][16][1]))))+temp[1]));
        temp[3] = ((((Fstar[22][2]*Vpk[4][22][2])+((Fstar[22][0]*Vpk[4][22][0])+
          (Fstar[22][1]*Vpk[4][22][1])))+((Tstar[22][2]*Wpk[4][22][2])+((
          Tstar[22][0]*Wpk[4][21][0])+(Tstar[22][1]*Wpk[4][22][1]))))+((((
          Fstar[20][2]*Vpk[4][20][2])+((Fstar[20][0]*Vpk[4][20][0])+(
          Fstar[20][1]*Vpk[4][20][1])))+((Tstar[20][2]*Wpk[4][20][2])+((
          Tstar[20][0]*Wpk[4][20][0])+(Tstar[20][1]*Wpk[4][19][1]))))+temp[2]));
        temp[4] = ((((Fstar[27][2]*Vpk[4][27][2])+((Fstar[27][0]*Vpk[4][27][0])+
          (Fstar[27][1]*Vpk[4][27][1])))+((Tstar[27][2]*Wpk[4][27][2])+((
          Tstar[27][0]*Wpk[4][27][0])+(Tstar[27][1]*Wpk[4][26][1]))))+((((
          Fstar[24][2]*Vpk[4][24][2])+((Fstar[24][0]*Vpk[4][24][0])+(
          Fstar[24][1]*Vpk[4][24][1])))+((Tstar[24][2]*Wpk[4][24][2])+((
          Tstar[24][0]*Wpk[4][24][0])+(Tstar[24][1]*Wpk[4][23][1]))))+temp[3]));
        temp[5] = ((((Fstar[30][2]*Vpk[4][30][2])+((Fstar[30][0]*Vpk[4][30][0])+
          (Fstar[30][1]*Vpk[4][30][1])))+((Tstar[30][2]*Wpk[4][29][2])+((
          Tstar[30][0]*Wpk[4][30][0])+(Tstar[30][1]*Wpk[4][30][1]))))+((((
          Fstar[28][2]*Vpk[4][28][2])+((Fstar[28][0]*Vpk[4][28][0])+(
          Fstar[28][1]*Vpk[4][28][1])))+((Tstar[28][2]*Wpk[4][28][2])+((
          Tstar[28][0]*Wpk[4][27][0])+(Tstar[28][1]*Wpk[4][28][1]))))+temp[4]));
        temp[6] = ((((Fstar[34][2]*Vpk[4][34][2])+((Fstar[34][0]*Vpk[4][34][0])+
          (Fstar[34][1]*Vpk[4][34][1])))+((Tstar[34][2]*Wpk[4][34][2])+((
          Tstar[34][0]*Wpk[4][33][0])+(Tstar[34][1]*Wpk[4][34][1]))))+((((
          Fstar[33][2]*Vpk[4][33][2])+((Fstar[33][0]*Vpk[4][33][0])+(
          Fstar[33][1]*Vpk[4][33][1])))+((Tstar[33][2]*Wpk[4][33][2])+((
          Tstar[33][0]*Wpk[4][33][0])+(Tstar[33][1]*Wpk[4][32][1]))))+temp[5]));
        fs0[4] = (utau[4]-((((Fstar[36][2]*Vpk[4][36][2])+((Fstar[36][0]*
          Vpk[4][36][0])+(Fstar[36][1]*Vpk[4][36][1])))+((Tstar[36][2]*
          Wpk[4][35][2])+((Tstar[36][0]*Wpk[4][36][0])+(Tstar[36][1]*
          Wpk[4][36][1]))))+temp[6]));
        temp[0] = (((Tstar[5][2]+(.1206*Fstar[5][0]))+(((.14625*(Fstar[8][2]*
          Wpk[5][8][0]))+((.0351*(Fstar[8][1]*Wpk[5][8][0]))+(Fstar[8][0]*
          Vpk[5][8][0])))+((Tstar[8][2]*Wpk[5][8][2])+((Tstar[8][0]*Wpk[5][8][0]
          )+(Tstar[8][1]*Wpk[5][7][1])))))+(((Fstar[11][2]*Vpk[5][11][2])+((
          Fstar[11][0]*Vpk[5][11][0])+(Fstar[11][1]*Vpk[5][11][1])))+((
          Tstar[11][2]*Wpk[5][11][2])+((Tstar[11][0]*Wpk[5][11][0])+(
          Tstar[11][1]*Wpk[5][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[5][14][2])+((Fstar[14][0]*Vpk[5][14][0])+
          (Fstar[14][1]*Vpk[5][14][1])))+((Tstar[14][2]*Wpk[5][14][2])+((
          Tstar[14][0]*Wpk[5][14][0])+(Tstar[14][1]*Wpk[5][13][1]))))+((((
          Fstar[12][2]*Vpk[5][12][2])+((Fstar[12][0]*Vpk[5][12][0])+(
          Fstar[12][1]*Vpk[5][12][1])))+((Tstar[12][2]*Wpk[5][12][2])+((
          Tstar[12][0]*Wpk[5][11][0])+(Tstar[12][1]*Wpk[5][12][1]))))+temp[0]));
        temp[2] = ((((Fstar[18][2]*Vpk[5][18][2])+((Fstar[18][0]*Vpk[5][18][0])+
          (Fstar[18][1]*Vpk[5][18][1])))+((Tstar[18][2]*Wpk[5][18][2])+((
          Tstar[18][0]*Wpk[5][18][0])+(Tstar[18][1]*Wpk[5][17][1]))))+((((
          Fstar[16][2]*Vpk[5][16][2])+((Fstar[16][0]*Vpk[5][16][0])+(
          Fstar[16][1]*Vpk[5][16][1])))+((Tstar[16][2]*Wpk[5][16][2])+((
          Tstar[16][0]*Wpk[5][15][0])+(Tstar[16][1]*Wpk[5][16][1]))))+temp[1]));
        temp[3] = ((((Fstar[22][2]*Vpk[5][22][2])+((Fstar[22][0]*Vpk[5][22][0])+
          (Fstar[22][1]*Vpk[5][22][1])))+((Tstar[22][2]*Wpk[5][22][2])+((
          Tstar[22][0]*Wpk[5][21][0])+(Tstar[22][1]*Wpk[5][22][1]))))+((((
          Fstar[20][2]*Vpk[5][20][2])+((Fstar[20][0]*Vpk[5][20][0])+(
          Fstar[20][1]*Vpk[5][20][1])))+((Tstar[20][2]*Wpk[5][20][2])+((
          Tstar[20][0]*Wpk[5][20][0])+(Tstar[20][1]*Wpk[5][19][1]))))+temp[2]));
        temp[4] = ((((Fstar[27][2]*Vpk[5][27][2])+((Fstar[27][0]*Vpk[5][27][0])+
          (Fstar[27][1]*Vpk[5][27][1])))+((Tstar[27][2]*Wpk[5][27][2])+((
          Tstar[27][0]*Wpk[5][27][0])+(Tstar[27][1]*Wpk[5][26][1]))))+((((
          Fstar[24][2]*Vpk[5][24][2])+((Fstar[24][0]*Vpk[5][24][0])+(
          Fstar[24][1]*Vpk[5][24][1])))+((Tstar[24][2]*Wpk[5][24][2])+((
          Tstar[24][0]*Wpk[5][24][0])+(Tstar[24][1]*Wpk[5][23][1]))))+temp[3]));
        temp[5] = ((((Fstar[30][2]*Vpk[5][30][2])+((Fstar[30][0]*Vpk[5][30][0])+
          (Fstar[30][1]*Vpk[5][30][1])))+((Tstar[30][2]*Wpk[5][29][2])+((
          Tstar[30][0]*Wpk[5][30][0])+(Tstar[30][1]*Wpk[5][30][1]))))+((((
          Fstar[28][2]*Vpk[5][28][2])+((Fstar[28][0]*Vpk[5][28][0])+(
          Fstar[28][1]*Vpk[5][28][1])))+((Tstar[28][2]*Wpk[5][28][2])+((
          Tstar[28][0]*Wpk[5][27][0])+(Tstar[28][1]*Wpk[5][28][1]))))+temp[4]));
        temp[6] = ((((Fstar[34][2]*Vpk[5][34][2])+((Fstar[34][0]*Vpk[5][34][0])+
          (Fstar[34][1]*Vpk[5][34][1])))+((Tstar[34][2]*Wpk[5][34][2])+((
          Tstar[34][0]*Wpk[5][33][0])+(Tstar[34][1]*Wpk[5][34][1]))))+((((
          Fstar[33][2]*Vpk[5][33][2])+((Fstar[33][0]*Vpk[5][33][0])+(
          Fstar[33][1]*Vpk[5][33][1])))+((Tstar[33][2]*Wpk[5][33][2])+((
          Tstar[33][0]*Wpk[5][33][0])+(Tstar[33][1]*Wpk[5][32][1]))))+temp[5]));
        fs0[5] = (utau[5]-((((Fstar[36][2]*Vpk[5][36][2])+((Fstar[36][0]*
          Vpk[5][36][0])+(Fstar[36][1]*Vpk[5][36][1])))+((Tstar[36][2]*
          Wpk[5][35][2])+((Tstar[36][0]*Wpk[5][36][0])+(Tstar[36][1]*
          Wpk[5][36][1]))))+temp[6]));
        temp[0] = ((((.14625*(Fstar[8][2]*Wpk[6][8][0]))+((.0351*(Fstar[8][1]*
          Wpk[6][8][0]))+(Fstar[8][0]*Vpk[6][8][0])))+((Tstar[8][2]*Wpk[6][8][2]
          )+((Tstar[8][0]*Wpk[6][8][0])-(Tstar[8][1]*s7))))+(((Fstar[11][2]*
          Vpk[6][11][2])+((Fstar[11][0]*Vpk[6][11][0])+(Fstar[11][1]*
          Vpk[6][11][1])))+((Tstar[11][2]*Wpk[6][11][2])+((Tstar[11][0]*
          Wpk[6][11][0])+(Tstar[11][1]*Wpk[6][10][1])))));
        temp[1] = ((((Fstar[14][2]*Vpk[6][14][2])+((Fstar[14][0]*Vpk[6][14][0])+
          (Fstar[14][1]*Vpk[6][14][1])))+((Tstar[14][2]*Wpk[6][14][2])+((
          Tstar[14][0]*Wpk[6][14][0])+(Tstar[14][1]*Wpk[6][13][1]))))+((((
          Fstar[12][2]*Vpk[6][12][2])+((Fstar[12][0]*Vpk[6][12][0])+(
          Fstar[12][1]*Vpk[6][12][1])))+((Tstar[12][2]*Wpk[6][12][2])+((
          Tstar[12][0]*Wpk[6][11][0])+(Tstar[12][1]*Wpk[6][12][1]))))+temp[0]));
        temp[2] = ((((Fstar[18][2]*Vpk[6][18][2])+((Fstar[18][0]*Vpk[6][18][0])+
          (Fstar[18][1]*Vpk[6][18][1])))+((Tstar[18][2]*Wpk[6][18][2])+((
          Tstar[18][0]*Wpk[6][18][0])+(Tstar[18][1]*Wpk[6][17][1]))))+((((
          Fstar[16][2]*Vpk[6][16][2])+((Fstar[16][0]*Vpk[6][16][0])+(
          Fstar[16][1]*Vpk[6][16][1])))+((Tstar[16][2]*Wpk[6][16][2])+((
          Tstar[16][0]*Wpk[6][15][0])+(Tstar[16][1]*Wpk[6][16][1]))))+temp[1]));
        temp[3] = ((((Fstar[22][2]*Vpk[6][22][2])+((Fstar[22][0]*Vpk[6][22][0])+
          (Fstar[22][1]*Vpk[6][22][1])))+((Tstar[22][2]*Wpk[6][22][2])+((
          Tstar[22][0]*Wpk[6][21][0])+(Tstar[22][1]*Wpk[6][22][1]))))+((((
          Fstar[20][2]*Vpk[6][20][2])+((Fstar[20][0]*Vpk[6][20][0])+(
          Fstar[20][1]*Vpk[6][20][1])))+((Tstar[20][2]*Wpk[6][20][2])+((
          Tstar[20][0]*Wpk[6][20][0])+(Tstar[20][1]*Wpk[6][19][1]))))+temp[2]));
        fs0[6] = (utau[6]-((((Fstar[24][2]*Vpk[6][24][2])+((Fstar[24][0]*
          Vpk[6][24][0])+(Fstar[24][1]*Vpk[6][24][1])))+((Tstar[24][2]*
          Wpk[6][24][2])+((Tstar[24][0]*Wpk[6][24][0])+(Tstar[24][1]*
          Wpk[6][23][1]))))+temp[3]));
        temp[0] = ((((Fstar[11][2]*Vpk[7][11][2])+((Fstar[11][0]*Vpk[7][11][0])+
          (Fstar[11][1]*Vpk[7][11][1])))+((Tstar[11][2]*Wpk[7][11][2])+((
          Tstar[11][0]*Wpk[7][11][0])+(Tstar[11][1]*Wpk[7][10][1]))))+(((
          Tstar[8][2]*c8)-(Tstar[8][0]*s8))-((.14625*(Fstar[8][2]*s8))+((.0351*(
          Fstar[8][1]*s8))+(.14625*(Fstar[8][0]*c8))))));
        temp[1] = ((((Fstar[14][2]*Vpk[7][14][2])+((Fstar[14][0]*Vpk[7][14][0])+
          (Fstar[14][1]*Vpk[7][14][1])))+((Tstar[14][2]*Wpk[7][14][2])+((
          Tstar[14][0]*Wpk[7][14][0])+(Tstar[14][1]*Wpk[7][13][1]))))+((((
          Fstar[12][2]*Vpk[7][12][2])+((Fstar[12][0]*Vpk[7][12][0])+(
          Fstar[12][1]*Vpk[7][12][1])))+((Tstar[12][2]*Wpk[7][12][2])+((
          Tstar[12][0]*Wpk[7][11][0])+(Tstar[12][1]*Wpk[7][12][1]))))+temp[0]));
        temp[2] = ((((Fstar[18][2]*Vpk[7][18][2])+((Fstar[18][0]*Vpk[7][18][0])+
          (Fstar[18][1]*Vpk[7][18][1])))+((Tstar[18][2]*Wpk[7][18][2])+((
          Tstar[18][0]*Wpk[7][18][0])+(Tstar[18][1]*Wpk[7][17][1]))))+((((
          Fstar[16][2]*Vpk[7][16][2])+((Fstar[16][0]*Vpk[7][16][0])+(
          Fstar[16][1]*Vpk[7][16][1])))+((Tstar[16][2]*Wpk[7][16][2])+((
          Tstar[16][0]*Wpk[7][15][0])+(Tstar[16][1]*Wpk[7][16][1]))))+temp[1]));
        temp[3] = ((((Fstar[22][2]*Vpk[7][22][2])+((Fstar[22][0]*Vpk[7][22][0])+
          (Fstar[22][1]*Vpk[7][22][1])))+((Tstar[22][2]*Wpk[7][22][2])+((
          Tstar[22][0]*Wpk[7][21][0])+(Tstar[22][1]*Wpk[7][22][1]))))+((((
          Fstar[20][2]*Vpk[7][20][2])+((Fstar[20][0]*Vpk[7][20][0])+(
          Fstar[20][1]*Vpk[7][20][1])))+((Tstar[20][2]*Wpk[7][20][2])+((
          Tstar[20][0]*Wpk[7][20][0])+(Tstar[20][1]*Wpk[7][19][1]))))+temp[2]));
        fs0[7] = (utau[7]-((((Fstar[24][2]*Vpk[7][24][2])+((Fstar[24][0]*
          Vpk[7][24][0])+(Fstar[24][1]*Vpk[7][24][1])))+((Tstar[24][2]*
          Wpk[7][24][2])+((Tstar[24][0]*Wpk[7][24][0])+(Tstar[24][1]*
          Wpk[7][23][1]))))+temp[3]));
        temp[0] = (((Tstar[8][1]-(.0351*Fstar[8][0]))+(((Fstar[11][2]*
          Vpk[8][11][2])+((Fstar[11][0]*Vpk[8][11][0])+(Fstar[11][1]*
          Vpk[8][11][1])))+((Tstar[11][2]*Wpk[8][11][2])+((Tstar[11][0]*
          Wpk[8][11][0])+(Tstar[11][1]*Wpk[8][10][1])))))+(((Fstar[12][2]*
          Vpk[8][12][2])+((Fstar[12][0]*Vpk[8][12][0])+(Fstar[12][1]*
          Vpk[8][12][1])))+((Tstar[12][2]*Wpk[8][12][2])+((Tstar[12][0]*
          Wpk[8][11][0])+(Tstar[12][1]*Wpk[8][12][1])))));
        temp[1] = ((((Fstar[16][2]*Vpk[8][16][2])+((Fstar[16][0]*Vpk[8][16][0])+
          (Fstar[16][1]*Vpk[8][16][1])))+((Tstar[16][2]*Wpk[8][16][2])+((
          Tstar[16][0]*Wpk[8][15][0])+(Tstar[16][1]*Wpk[8][16][1]))))+((((
          Fstar[14][2]*Vpk[8][14][2])+((Fstar[14][0]*Vpk[8][14][0])+(
          Fstar[14][1]*Vpk[8][14][1])))+((Tstar[14][2]*Wpk[8][14][2])+((
          Tstar[14][0]*Wpk[8][14][0])+(Tstar[14][1]*c13))))+temp[0]));
        temp[2] = ((((Fstar[20][2]*Vpk[8][20][2])+((Fstar[20][0]*Vpk[8][20][0])+
          (Fstar[20][1]*Vpk[8][20][1])))+((Tstar[20][2]*Wpk[8][20][2])+((
          Tstar[20][0]*Wpk[8][20][0])+(Tstar[20][1]*c19))))+((((Fstar[18][2]*
          Vpk[8][18][2])+((Fstar[18][0]*Vpk[8][18][0])+(Fstar[18][1]*
          Vpk[8][18][1])))+((Tstar[18][2]*Wpk[8][18][2])+((Tstar[18][0]*
          Wpk[8][18][0])+(Tstar[18][1]*Wpk[8][17][1]))))+temp[1]));
        fs0[8] = (utau[8]-((((Fstar[24][2]*Vpk[8][24][2])+((Fstar[24][0]*
          Vpk[8][24][0])+(Fstar[24][1]*Vpk[8][24][1])))+((Tstar[24][2]*
          Wpk[8][24][2])+((Tstar[24][0]*Wpk[8][24][0])+(Tstar[24][1]*
          Wpk[8][23][1]))))+((((Fstar[22][2]*Vpk[8][22][2])+((Fstar[22][0]*
          Vpk[8][22][0])+(Fstar[22][1]*Vpk[8][22][1])))+((Tstar[22][2]*
          Wpk[8][22][2])+((Tstar[22][0]*Wpk[8][21][0])+(Tstar[22][1]*
          Wpk[8][22][1]))))+temp[2])));
        fs0[9] = (utau[9]-((((.0442*(Fstar[11][2]*Wpk[9][11][0]))+((Fstar[11][0]
          *Vpk[9][11][0])-(.0065*(Fstar[11][1]*Wpk[9][11][0]))))+((Tstar[11][2]*
          Wpk[9][11][2])+((Tstar[11][0]*Wpk[9][11][0])-(Tstar[11][1]*s10))))+(((
          Fstar[12][2]*Vpk[9][12][2])+((Fstar[12][0]*Vpk[9][12][0])+(
          Fstar[12][1]*Vpk[9][12][1])))+((Tstar[12][2]*Wpk[9][12][2])+((
          Tstar[12][0]*Wpk[9][11][0])+(Tstar[12][1]*Wpk[9][12][1]))))));
        fs0[10] = (utau[10]-((((Fstar[12][2]*Vpk[10][12][2])+((Fstar[12][0]*
          Vpk[10][12][0])+(Fstar[12][1]*Vpk[10][12][1])))+((Tstar[12][2]*
          Wpk[10][12][2])+((Tstar[12][1]*Wpk[10][12][1])-(Tstar[12][0]*s11))))+(
          ((Tstar[11][2]*c11)-(Tstar[11][0]*s11))+(((.0065*(Fstar[11][1]*s11))-(
          .0442*(Fstar[11][0]*c11)))-(.0442*(Fstar[11][2]*s11))))));
        fs0[11] = (utau[11]-((Tstar[11][1]+(.0065*Fstar[11][0]))+((Fstar[12][0]*
          Vpk[11][12][0])+((Tstar[12][1]*c12)-(Tstar[12][2]*s12)))));
        fs0[12] = (utau[12]-(Tstar[12][0]+((.078*Fstar[12][2])-(.0312*
          Fstar[12][1]))));
        temp[0] = (((Fstar[14][1]*Vpk[13][14][1])+((Tstar[14][2]*c14)-(
          Tstar[14][0]*s14)))+(((Fstar[16][2]*Vpk[13][16][2])+((Fstar[16][1]*
          Vpk[13][16][1])-(.0039*(Fstar[16][0]*Wpk[13][16][2]))))+((Tstar[16][2]
          *Wpk[13][16][2])+((Tstar[16][0]*Wpk[13][15][0])+(Tstar[16][1]*
          Wpk[13][16][1])))));
        fs0[13] = (utau[13]-(temp[0]+(((Fstar[18][2]*Vpk[13][18][2])+((
          Fstar[18][0]*Vpk[13][18][0])+(Fstar[18][1]*Vpk[13][18][1])))+((
          Tstar[18][2]*Wpk[13][18][2])+((Tstar[18][0]*Wpk[13][18][0])+(
          Tstar[18][1]*Wpk[13][17][1]))))));
        fs0[14] = (utau[14]-(((Tstar[14][1]+((.0013*Fstar[14][0])-(.1326*
          Fstar[14][2])))+(((Fstar[16][2]*Vpk[14][16][2])+((Fstar[16][0]*
          Vpk[14][16][0])+(Fstar[16][1]*Vpk[14][16][1])))+((Tstar[16][1]*c16)-(
          Tstar[16][2]*s16))))+(((Fstar[18][2]*Vpk[14][18][2])+((Fstar[18][0]*
          Vpk[14][18][0])+(Fstar[18][1]*Vpk[14][18][1])))+((Tstar[18][2]*
          Wpk[14][18][2])+((Tstar[18][0]*Wpk[14][18][0])+(Tstar[18][1]*
          Wpk[14][17][1]))))));
        fs0[15] = (utau[15]-((((Fstar[18][2]*Vpk[15][18][2])+((Fstar[18][0]*
          Vpk[15][18][0])+(Fstar[18][1]*Vpk[15][18][1])))+((Tstar[18][2]*
          Wpk[15][18][2])+((Tstar[18][0]*Wpk[15][18][0])+(Tstar[18][1]*
          Wpk[15][17][1]))))+(((Tstar[16][1]*c16)-(Tstar[16][2]*s16))+(((.0039*(
          Fstar[16][0]*s16))-(.1378*(Fstar[16][1]*s16)))-(.1378*(Fstar[16][2]*
          c16))))));
        fs0[16] = (utau[16]-((Tstar[16][0]+(.0039*Fstar[16][2]))+(((Fstar[18][2]
          *Vpk[16][18][2])+((.065*(Fstar[18][1]*Wpk[16][18][2]))-(.0078*(
          Fstar[18][0]*s18))))+((Tstar[18][2]*Wpk[16][18][2])+((Tstar[18][0]*
          Wpk[16][18][0])-(Tstar[18][1]*s17))))));
        fs0[17] = (utau[17]-((.065*(Fstar[18][1]*c18))+((Tstar[18][2]*c18)-(
          Tstar[18][0]*s18))));
        fs0[18] = (utau[18]-(Tstar[18][1]-(.065*Fstar[18][2])));
        temp[0] = (((Fstar[20][1]*Vpk[19][20][1])+((Tstar[20][2]*c20)-(
          Tstar[20][0]*s20)))+(((Fstar[22][2]*Vpk[19][22][2])+((Fstar[22][1]*
          Vpk[19][22][1])-(.0039*(Fstar[22][0]*Wpk[19][22][2]))))+((Tstar[22][2]
          *Wpk[19][22][2])+((Tstar[22][0]*Wpk[19][21][0])+(Tstar[22][1]*
          Wpk[19][22][1])))));
        fs0[19] = (utau[19]-(temp[0]+(((Fstar[24][2]*Vpk[19][24][2])+((
          Fstar[24][0]*Vpk[19][24][0])+(Fstar[24][1]*Vpk[19][24][1])))+((
          Tstar[24][2]*Wpk[19][24][2])+((Tstar[24][0]*Wpk[19][24][0])+(
          Tstar[24][1]*Wpk[19][23][1]))))));
        fs0[20] = (utau[20]-(((Tstar[20][1]+((.0013*Fstar[20][0])+(.1326*
          Fstar[20][2])))+(((Fstar[22][2]*Vpk[20][22][2])+((Fstar[22][0]*
          Vpk[20][22][0])+(Fstar[22][1]*Vpk[20][22][1])))+((Tstar[22][1]*c22)-(
          Tstar[22][2]*s22))))+(((Fstar[24][2]*Vpk[20][24][2])+((Fstar[24][0]*
          Vpk[20][24][0])+(Fstar[24][1]*Vpk[20][24][1])))+((Tstar[24][2]*
          Wpk[20][24][2])+((Tstar[24][0]*Wpk[20][24][0])+(Tstar[24][1]*
          Wpk[20][23][1]))))));
        fs0[21] = (utau[21]-((((.1378*(Fstar[22][2]*c22))+((.0039*(Fstar[22][0]*
          s22))+(.1378*(Fstar[22][1]*s22))))+((Tstar[22][1]*c22)-(Tstar[22][2]*
          s22)))+(((Fstar[24][2]*Vpk[21][24][2])+((Fstar[24][0]*Vpk[21][24][0])+
          (Fstar[24][1]*Vpk[21][24][1])))+((Tstar[24][2]*Wpk[21][24][2])+((
          Tstar[24][0]*Wpk[21][24][0])+(Tstar[24][1]*Wpk[21][23][1]))))));
        fs0[22] = (utau[22]-((Tstar[22][0]+(.0039*Fstar[22][2]))+(((Fstar[24][2]
          *Vpk[22][24][2])-((.0078*(Fstar[24][0]*s24))+(.065*(Fstar[24][1]*
          Wpk[22][24][2]))))+((Tstar[24][2]*Wpk[22][24][2])+((Tstar[24][0]*
          Wpk[22][24][0])-(Tstar[24][1]*s23))))));
        fs0[23] = (utau[23]-(((Tstar[24][2]*c24)-(Tstar[24][0]*s24))-(.065*(
          Fstar[24][1]*c24))));
        fs0[24] = (utau[24]-(Tstar[24][1]+(.065*Fstar[24][2])));
        temp[0] = ((((Fstar[27][2]*Vpk[25][27][2])+((Fstar[27][0]*Vpk[25][27][0]
          )+(Fstar[27][1]*Vpk[25][27][1])))+((Tstar[27][2]*Wpk[25][27][2])+((
          Tstar[27][0]*Wpk[25][27][0])-(Tstar[27][1]*s26))))+(((Fstar[28][2]*
          Vpk[25][28][2])+((Fstar[28][0]*Vpk[25][28][0])+(Fstar[28][1]*
          Vpk[25][28][1])))+((Tstar[28][2]*Wpk[25][28][2])+((Tstar[28][0]*
          Wpk[25][27][0])+(Tstar[28][1]*Wpk[25][28][1])))));
        fs0[25] = (utau[25]-((((Fstar[30][2]*Vpk[25][30][2])+((Fstar[30][0]*
          Vpk[25][30][0])+(Fstar[30][1]*Vpk[25][30][1])))+((Tstar[30][2]*
          Wpk[25][29][2])+((Tstar[30][0]*Wpk[25][30][0])+(Tstar[30][1]*
          Wpk[25][30][1]))))+temp[0]));
        temp[0] = ((((.2379*(Fstar[27][2]*s27))+((.2379*(Fstar[27][0]*c27))+(
          Fstar[27][1]*Vpk[26][27][1])))+((Tstar[27][2]*c27)-(Tstar[27][0]*s27))
          )+(((Fstar[28][2]*Vpk[26][28][2])+((Fstar[28][0]*Vpk[26][28][0])+(
          Fstar[28][1]*Vpk[26][28][1])))+((Tstar[28][2]*Wpk[26][28][2])+((
          Tstar[28][1]*Wpk[26][28][1])-(Tstar[28][0]*s27)))));
        fs0[26] = (utau[26]-((((Fstar[30][2]*Vpk[26][30][2])+((Fstar[30][0]*
          Vpk[26][30][0])+(Fstar[30][1]*Vpk[26][30][1])))+((Tstar[30][2]*
          Wpk[26][29][2])+((Tstar[30][0]*Wpk[26][30][0])+(Tstar[30][1]*
          Wpk[26][30][1]))))+temp[0]));
        fs0[27] = (utau[27]-(((Tstar[27][1]+((.0143*Fstar[27][0])+(.0169*
          Fstar[27][2])))+(((.0416*(Fstar[28][2]*c28))+((.0416*(Fstar[28][1]*s28
          ))+(Fstar[28][0]*Vpk[27][28][0])))+((Tstar[28][1]*c28)-(Tstar[28][2]*
          s28))))+(((Fstar[30][2]*Vpk[27][30][2])+((Fstar[30][0]*Vpk[27][30][0])
          +(Fstar[30][1]*Vpk[27][30][1])))+((Tstar[30][2]*Wpk[27][29][2])+((
          Tstar[30][0]*Wpk[27][30][0])+(Tstar[30][1]*Wpk[27][30][1]))))));
        fs0[28] = (utau[28]-((Tstar[28][0]+((.0039*Fstar[28][1])-(.2158*
          Fstar[28][2])))+(((Fstar[30][2]*Vpk[28][30][2])+((Fstar[30][0]*
          Vpk[28][30][0])+(Fstar[30][1]*Vpk[28][30][1])))+((Tstar[30][0]*c30)-(
          Tstar[30][1]*s30)))));
        fs0[29] = (utau[29]-(((Tstar[30][0]*c30)-(Tstar[30][1]*s30))-((.039*((
          Fstar[30][0]*s30)+(Fstar[30][1]*c30)))+(.0442*(Fstar[30][2]*c30)))));
        fs0[30] = (utau[30]-(Tstar[30][2]+(.0442*Fstar[30][0])));
        temp[0] = ((((Fstar[33][2]*Vpk[31][33][2])+((Fstar[33][0]*Vpk[31][33][0]
          )+(Fstar[33][1]*Vpk[31][33][1])))+((Tstar[33][2]*Wpk[31][33][2])+((
          Tstar[33][0]*Wpk[31][33][0])-(Tstar[33][1]*s32))))+(((Fstar[34][2]*
          Vpk[31][34][2])+((Fstar[34][0]*Vpk[31][34][0])+(Fstar[34][1]*
          Vpk[31][34][1])))+((Tstar[34][2]*Wpk[31][34][2])+((Tstar[34][0]*
          Wpk[31][33][0])+(Tstar[34][1]*Wpk[31][34][1])))));
        fs0[31] = (utau[31]-((((Fstar[36][2]*Vpk[31][36][2])+((Fstar[36][0]*
          Vpk[31][36][0])+(Fstar[36][1]*Vpk[31][36][1])))+((Tstar[36][2]*
          Wpk[31][35][2])+((Tstar[36][0]*Wpk[31][36][0])+(Tstar[36][1]*
          Wpk[31][36][1]))))+temp[0]));
        temp[0] = ((((.2379*(Fstar[33][2]*s33))+((.2379*(Fstar[33][0]*c33))+(
          Fstar[33][1]*Vpk[32][33][1])))+((Tstar[33][2]*c33)-(Tstar[33][0]*s33))
          )+(((Fstar[34][2]*Vpk[32][34][2])+((Fstar[34][0]*Vpk[32][34][0])+(
          Fstar[34][1]*Vpk[32][34][1])))+((Tstar[34][2]*Wpk[32][34][2])+((
          Tstar[34][1]*Wpk[32][34][1])-(Tstar[34][0]*s33)))));
        fs0[32] = (utau[32]-((((Fstar[36][2]*Vpk[32][36][2])+((Fstar[36][0]*
          Vpk[32][36][0])+(Fstar[36][1]*Vpk[32][36][1])))+((Tstar[36][2]*
          Wpk[32][35][2])+((Tstar[36][0]*Wpk[32][36][0])+(Tstar[36][1]*
          Wpk[32][36][1]))))+temp[0]));
        fs0[33] = (utau[33]-(((Tstar[33][1]+((.0143*Fstar[33][0])-(.0169*
          Fstar[33][2])))+(((Tstar[34][1]*c34)-(Tstar[34][2]*s34))+(((
          Fstar[34][0]*Vpk[33][34][0])-(.0416*(Fstar[34][1]*s34)))-(.0416*(
          Fstar[34][2]*c34)))))+(((Fstar[36][2]*Vpk[33][36][2])+((Fstar[36][0]*
          Vpk[33][36][0])+(Fstar[36][1]*Vpk[33][36][1])))+((Tstar[36][2]*
          Wpk[33][35][2])+((Tstar[36][0]*Wpk[33][36][0])+(Tstar[36][1]*
          Wpk[33][36][1]))))));
        fs0[34] = (utau[34]-((Tstar[34][0]+((.0039*Fstar[34][1])-(.2158*
          Fstar[34][2])))+(((Fstar[36][2]*Vpk[34][36][2])+((Fstar[36][0]*
          Vpk[34][36][0])+(Fstar[36][1]*Vpk[34][36][1])))+((Tstar[36][0]*c36)-(
          Tstar[36][1]*s36)))));
        fs0[35] = (utau[35]-(((Tstar[36][0]*c36)-(Tstar[36][1]*s36))-((.039*((
          Fstar[36][0]*s36)+(Fstar[36][1]*c36)))+(.0442*(Fstar[36][2]*c36)))));
        fs0[36] = (utau[36]-(Tstar[36][2]+(.0442*Fstar[36][0])));
        fs0flg = 1;
    }
/*
 Used 2.00 seconds CPU time,
 40960 additional bytes of memory.
 Equations contain  981 adds/subtracts/negates
                    957 multiplies
                      0 divides
                    180 assignments
*/
}

void skel18domm(int routine)
{
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        skel18dovpk();
        temp[0] = (((16.61*((Cik[3][0][2]*Cik[3][0][2])+((Cik[3][0][0]*
          Cik[3][0][0])+(Cik[3][0][1]*Cik[3][0][1]))))+(29.27*((Vpk[0][8][2]*
          Vpk[0][8][2])+((Vpk[0][7][1]*Vpk[0][7][1])+(Vpk[0][8][0]*Vpk[0][8][0])
          ))))+((Vpk[0][11][2]*Vpk[0][11][2])+((Vpk[0][10][1]*Vpk[0][10][1])+(
          Vpk[0][11][0]*Vpk[0][11][0]))));
        temp[1] = ((1.21*((Vpk[0][16][2]*Vpk[0][16][2])+((Vpk[0][15][0]*
          Vpk[0][15][0])+(Vpk[0][16][1]*Vpk[0][16][1]))))+((2.79*((Vpk[0][14][2]
          *Vpk[0][14][2])+((Vpk[0][13][1]*Vpk[0][13][1])+(Vpk[0][14][0]*
          Vpk[0][14][0]))))+((5.89*((Vpk[0][12][2]*Vpk[0][12][2])+((
          Vpk[0][11][0]*Vpk[0][11][0])+(Vpk[0][12][1]*Vpk[0][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[0][22][2]*Vpk[0][22][2])+((Vpk[0][21][0]*
          Vpk[0][21][0])+(Vpk[0][22][1]*Vpk[0][22][1]))))+((2.79*((Vpk[0][20][2]
          *Vpk[0][20][2])+((Vpk[0][19][1]*Vpk[0][19][1])+(Vpk[0][20][0]*
          Vpk[0][20][0]))))+((.55*((Vpk[0][18][2]*Vpk[0][18][2])+((Vpk[0][17][1]
          *Vpk[0][17][1])+(Vpk[0][18][0]*Vpk[0][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[0][28][2]*Vpk[0][28][2])+((Vpk[0][27][0]*
          Vpk[0][27][0])+(Vpk[0][28][1]*Vpk[0][28][1]))))+((8.35*((Vpk[0][27][2]
          *Vpk[0][27][2])+((Vpk[0][26][1]*Vpk[0][26][1])+(Vpk[0][27][0]*
          Vpk[0][27][0]))))+((.55*((Vpk[0][24][2]*Vpk[0][24][2])+((Vpk[0][23][1]
          *Vpk[0][23][1])+(Vpk[0][24][0]*Vpk[0][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[0][34][2]*Vpk[0][34][2])+((Vpk[0][33][0]*
          Vpk[0][33][0])+(Vpk[0][34][1]*Vpk[0][34][1]))))+((8.35*((Vpk[0][33][2]
          *Vpk[0][33][2])+((Vpk[0][32][1]*Vpk[0][32][1])+(Vpk[0][33][0]*
          Vpk[0][33][0]))))+((1.34*((Vpk[0][29][2]*Vpk[0][29][2])+((
          Vpk[0][30][0]*Vpk[0][30][0])+(Vpk[0][30][1]*Vpk[0][30][1]))))+temp[3])
          ));
        mm[0][0] = ((1.34*((Vpk[0][35][2]*Vpk[0][35][2])+((Vpk[0][36][0]*
          Vpk[0][36][0])+(Vpk[0][36][1]*Vpk[0][36][1]))))+temp[4]);
        temp[0] = (((16.61*((Cik[3][0][2]*Cik[3][1][2])+((Cik[3][0][0]*
          Cik[3][1][0])+(Cik[3][0][1]*Cik[3][1][1]))))+(29.27*((Vpk[0][8][2]*
          Vpk[1][8][2])+((Vpk[0][7][1]*Vpk[1][7][1])+(Vpk[0][8][0]*Vpk[1][8][0])
          ))))+((Vpk[0][11][2]*Vpk[1][11][2])+((Vpk[0][10][1]*Vpk[1][10][1])+(
          Vpk[0][11][0]*Vpk[1][11][0]))));
        temp[1] = ((1.21*((Vpk[0][16][2]*Vpk[1][16][2])+((Vpk[0][15][0]*
          Vpk[1][15][0])+(Vpk[0][16][1]*Vpk[1][16][1]))))+((2.79*((Vpk[0][14][2]
          *Vpk[1][14][2])+((Vpk[0][13][1]*Vpk[1][13][1])+(Vpk[0][14][0]*
          Vpk[1][14][0]))))+((5.89*((Vpk[0][12][2]*Vpk[1][12][2])+((
          Vpk[0][11][0]*Vpk[1][11][0])+(Vpk[0][12][1]*Vpk[1][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[0][22][2]*Vpk[1][22][2])+((Vpk[0][21][0]*
          Vpk[1][21][0])+(Vpk[0][22][1]*Vpk[1][22][1]))))+((2.79*((Vpk[0][20][2]
          *Vpk[1][20][2])+((Vpk[0][19][1]*Vpk[1][19][1])+(Vpk[0][20][0]*
          Vpk[1][20][0]))))+((.55*((Vpk[0][18][2]*Vpk[1][18][2])+((Vpk[0][17][1]
          *Vpk[1][17][1])+(Vpk[0][18][0]*Vpk[1][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[0][28][2]*Vpk[1][28][2])+((Vpk[0][27][0]*
          Vpk[1][27][0])+(Vpk[0][28][1]*Vpk[1][28][1]))))+((8.35*((Vpk[0][27][2]
          *Vpk[1][27][2])+((Vpk[0][26][1]*Vpk[1][26][1])+(Vpk[0][27][0]*
          Vpk[1][27][0]))))+((.55*((Vpk[0][24][2]*Vpk[1][24][2])+((Vpk[0][23][1]
          *Vpk[1][23][1])+(Vpk[0][24][0]*Vpk[1][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[0][34][2]*Vpk[1][34][2])+((Vpk[0][33][0]*
          Vpk[1][33][0])+(Vpk[0][34][1]*Vpk[1][34][1]))))+((8.35*((Vpk[0][33][2]
          *Vpk[1][33][2])+((Vpk[0][32][1]*Vpk[1][32][1])+(Vpk[0][33][0]*
          Vpk[1][33][0]))))+((1.34*((Vpk[0][29][2]*Vpk[1][29][2])+((
          Vpk[0][30][0]*Vpk[1][30][0])+(Vpk[0][30][1]*Vpk[1][30][1]))))+temp[3])
          ));
        mm[0][1] = ((1.34*((Vpk[0][35][2]*Vpk[1][35][2])+((Vpk[0][36][0]*
          Vpk[1][36][0])+(Vpk[0][36][1]*Vpk[1][36][1]))))+temp[4]);
        temp[0] = (((16.61*((Cik[3][0][2]*Cik[3][2][2])+((Cik[3][0][0]*
          Cik[3][2][0])+(Cik[3][0][1]*Cik[3][2][1]))))+(29.27*((Vpk[0][8][2]*
          Vpk[2][8][2])+((Vpk[0][7][1]*Vpk[2][7][1])+(Vpk[0][8][0]*Vpk[2][8][0])
          ))))+((Vpk[0][11][2]*Vpk[2][11][2])+((Vpk[0][10][1]*Vpk[2][10][1])+(
          Vpk[0][11][0]*Vpk[2][11][0]))));
        temp[1] = ((1.21*((Vpk[0][16][2]*Vpk[2][16][2])+((Vpk[0][15][0]*
          Vpk[2][15][0])+(Vpk[0][16][1]*Vpk[2][16][1]))))+((2.79*((Vpk[0][14][2]
          *Vpk[2][14][2])+((Vpk[0][13][1]*Vpk[2][13][1])+(Vpk[0][14][0]*
          Vpk[2][14][0]))))+((5.89*((Vpk[0][12][2]*Vpk[2][12][2])+((
          Vpk[0][11][0]*Vpk[2][11][0])+(Vpk[0][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[0][22][2]*Vpk[2][22][2])+((Vpk[0][21][0]*
          Vpk[2][21][0])+(Vpk[0][22][1]*Vpk[2][22][1]))))+((2.79*((Vpk[0][20][2]
          *Vpk[2][20][2])+((Vpk[0][19][1]*Vpk[2][19][1])+(Vpk[0][20][0]*
          Vpk[2][20][0]))))+((.55*((Vpk[0][18][2]*Vpk[2][18][2])+((Vpk[0][17][1]
          *Vpk[2][17][1])+(Vpk[0][18][0]*Vpk[2][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[0][28][2]*Vpk[2][28][2])+((Vpk[0][27][0]*
          Vpk[2][27][0])+(Vpk[0][28][1]*Vpk[2][28][1]))))+((8.35*((Vpk[0][27][2]
          *Vpk[2][27][2])+((Vpk[0][26][1]*Vpk[2][26][1])+(Vpk[0][27][0]*
          Vpk[2][27][0]))))+((.55*((Vpk[0][24][2]*Vpk[2][24][2])+((Vpk[0][23][1]
          *Vpk[2][23][1])+(Vpk[0][24][0]*Vpk[2][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[0][34][2]*Vpk[2][34][2])+((Vpk[0][33][0]*
          Vpk[2][33][0])+(Vpk[0][34][1]*Vpk[2][34][1]))))+((8.35*((Vpk[0][33][2]
          *Vpk[2][33][2])+((Vpk[0][32][1]*Vpk[2][32][1])+(Vpk[0][33][0]*
          Vpk[2][33][0]))))+((1.34*((Vpk[0][29][2]*Vpk[2][29][2])+((
          Vpk[0][30][0]*Vpk[2][30][0])+(Vpk[0][30][1]*Vpk[2][30][1]))))+temp[3])
          ));
        mm[0][2] = ((1.34*((Vpk[0][35][2]*Vpk[2][35][2])+((Vpk[0][36][0]*
          Vpk[2][36][0])+(Vpk[0][36][1]*Vpk[2][36][1]))))+temp[4]);
        temp[0] = ((5.89*((Vpk[0][12][2]*Vpk[3][12][2])+((Vpk[0][11][0]*
          Vpk[3][12][0])+(Vpk[0][12][1]*Vpk[3][12][1]))))+(((16.61*((.05*
          Cik[3][0][1])-(.1206*Cik[3][0][2])))+(29.27*((.14625*(Vpk[0][8][2]*
          Wpk[3][8][0]))+((.0351*(Vpk[0][7][1]*Wpk[3][8][0]))+(Vpk[0][8][0]*
          Vpk[3][8][0])))))+((Vpk[0][11][2]*Vpk[3][11][2])+((Vpk[0][10][1]*
          Vpk[3][11][1])+(Vpk[0][11][0]*Vpk[3][11][0])))));
        temp[1] = ((.55*((Vpk[0][18][2]*Vpk[3][18][2])+((Vpk[0][17][1]*
          Vpk[3][18][1])+(Vpk[0][18][0]*Vpk[3][18][0]))))+((1.21*((Vpk[0][16][2]
          *Vpk[3][16][2])+((Vpk[0][15][0]*Vpk[3][16][0])+(Vpk[0][16][1]*
          Vpk[3][16][1]))))+((2.79*((Vpk[0][14][2]*Vpk[3][14][2])+((
          Vpk[0][13][1]*Vpk[3][14][1])+(Vpk[0][14][0]*Vpk[3][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[0][24][2]*Vpk[3][24][2])+((Vpk[0][23][1]*
          Vpk[3][24][1])+(Vpk[0][24][0]*Vpk[3][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[3][22][2])+((Vpk[0][21][0]*Vpk[3][22][0])+(Vpk[0][22][1]*
          Vpk[3][22][1]))))+((2.79*((Vpk[0][20][2]*Vpk[3][20][2])+((
          Vpk[0][19][1]*Vpk[3][20][1])+(Vpk[0][20][0]*Vpk[3][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[0][29][2]*Vpk[3][30][2])+((Vpk[0][30][0]*
          Vpk[3][30][0])+(Vpk[0][30][1]*Vpk[3][30][1]))))+((4.16*((Vpk[0][28][2]
          *Vpk[3][28][2])+((Vpk[0][27][0]*Vpk[3][28][0])+(Vpk[0][28][1]*
          Vpk[3][28][1]))))+((8.35*((Vpk[0][27][2]*Vpk[3][27][2])+((
          Vpk[0][26][1]*Vpk[3][27][1])+(Vpk[0][27][0]*Vpk[3][27][0]))))+temp[2])
          ));
        mm[0][3] = ((1.34*((Vpk[0][35][2]*Vpk[3][36][2])+((Vpk[0][36][0]*
          Vpk[3][36][0])+(Vpk[0][36][1]*Vpk[3][36][1]))))+((4.16*((Vpk[0][34][2]
          *Vpk[3][34][2])+((Vpk[0][33][0]*Vpk[3][34][0])+(Vpk[0][34][1]*
          Vpk[3][34][1]))))+((8.35*((Vpk[0][33][2]*Vpk[3][33][2])+((
          Vpk[0][32][1]*Vpk[3][33][1])+(Vpk[0][33][0]*Vpk[3][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[0][12][2]*Vpk[4][12][2])+((Vpk[0][11][0]*
          Vpk[4][12][0])+(Vpk[0][12][1]*Vpk[4][12][1]))))+(((29.27*((.14625*(
          Vpk[0][8][2]*Wpk[4][8][0]))+((.0351*(Vpk[0][7][1]*Wpk[4][8][0]))+(
          Vpk[0][8][0]*Vpk[4][8][0]))))-(.8305*Cik[3][0][0]))+((Vpk[0][11][2]*
          Vpk[4][11][2])+((Vpk[0][10][1]*Vpk[4][11][1])+(Vpk[0][11][0]*
          Vpk[4][11][0])))));
        temp[1] = ((.55*((Vpk[0][18][2]*Vpk[4][18][2])+((Vpk[0][17][1]*
          Vpk[4][18][1])+(Vpk[0][18][0]*Vpk[4][18][0]))))+((1.21*((Vpk[0][16][2]
          *Vpk[4][16][2])+((Vpk[0][15][0]*Vpk[4][16][0])+(Vpk[0][16][1]*
          Vpk[4][16][1]))))+((2.79*((Vpk[0][14][2]*Vpk[4][14][2])+((
          Vpk[0][13][1]*Vpk[4][14][1])+(Vpk[0][14][0]*Vpk[4][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[0][24][2]*Vpk[4][24][2])+((Vpk[0][23][1]*
          Vpk[4][24][1])+(Vpk[0][24][0]*Vpk[4][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[4][22][2])+((Vpk[0][21][0]*Vpk[4][22][0])+(Vpk[0][22][1]*
          Vpk[4][22][1]))))+((2.79*((Vpk[0][20][2]*Vpk[4][20][2])+((
          Vpk[0][19][1]*Vpk[4][20][1])+(Vpk[0][20][0]*Vpk[4][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[0][29][2]*Vpk[4][30][2])+((Vpk[0][30][0]*
          Vpk[4][30][0])+(Vpk[0][30][1]*Vpk[4][30][1]))))+((4.16*((Vpk[0][28][2]
          *Vpk[4][28][2])+((Vpk[0][27][0]*Vpk[4][28][0])+(Vpk[0][28][1]*
          Vpk[4][28][1]))))+((8.35*((Vpk[0][27][2]*Vpk[4][27][2])+((
          Vpk[0][26][1]*Vpk[4][27][1])+(Vpk[0][27][0]*Vpk[4][27][0]))))+temp[2])
          ));
        mm[0][4] = ((1.34*((Vpk[0][35][2]*Vpk[4][36][2])+((Vpk[0][36][0]*
          Vpk[4][36][0])+(Vpk[0][36][1]*Vpk[4][36][1]))))+((4.16*((Vpk[0][34][2]
          *Vpk[4][34][2])+((Vpk[0][33][0]*Vpk[4][34][0])+(Vpk[0][34][1]*
          Vpk[4][34][1]))))+((8.35*((Vpk[0][33][2]*Vpk[4][33][2])+((
          Vpk[0][32][1]*Vpk[4][33][1])+(Vpk[0][33][0]*Vpk[4][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[0][12][2]*Vpk[5][12][2])+((Vpk[0][11][0]*
          Vpk[5][12][0])+(Vpk[0][12][1]*Vpk[5][12][1]))))+(((2.003166*
          Cik[3][0][0])+(29.27*((.14625*(Vpk[0][8][2]*Wpk[5][8][0]))+((.0351*(
          Vpk[0][7][1]*Wpk[5][8][0]))+(Vpk[0][8][0]*Vpk[5][8][0])))))+((
          Vpk[0][11][2]*Vpk[5][11][2])+((Vpk[0][10][1]*Vpk[5][11][1])+(
          Vpk[0][11][0]*Vpk[5][11][0])))));
        temp[1] = ((.55*((Vpk[0][18][2]*Vpk[5][18][2])+((Vpk[0][17][1]*
          Vpk[5][18][1])+(Vpk[0][18][0]*Vpk[5][18][0]))))+((1.21*((Vpk[0][16][2]
          *Vpk[5][16][2])+((Vpk[0][15][0]*Vpk[5][16][0])+(Vpk[0][16][1]*
          Vpk[5][16][1]))))+((2.79*((Vpk[0][14][2]*Vpk[5][14][2])+((
          Vpk[0][13][1]*Vpk[5][14][1])+(Vpk[0][14][0]*Vpk[5][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[0][24][2]*Vpk[5][24][2])+((Vpk[0][23][1]*
          Vpk[5][24][1])+(Vpk[0][24][0]*Vpk[5][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[5][22][2])+((Vpk[0][21][0]*Vpk[5][22][0])+(Vpk[0][22][1]*
          Vpk[5][22][1]))))+((2.79*((Vpk[0][20][2]*Vpk[5][20][2])+((
          Vpk[0][19][1]*Vpk[5][20][1])+(Vpk[0][20][0]*Vpk[5][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[0][29][2]*Vpk[5][30][2])+((Vpk[0][30][0]*
          Vpk[5][30][0])+(Vpk[0][30][1]*Vpk[5][30][1]))))+((4.16*((Vpk[0][28][2]
          *Vpk[5][28][2])+((Vpk[0][27][0]*Vpk[5][28][0])+(Vpk[0][28][1]*
          Vpk[5][28][1]))))+((8.35*((Vpk[0][27][2]*Vpk[5][27][2])+((
          Vpk[0][26][1]*Vpk[5][27][1])+(Vpk[0][27][0]*Vpk[5][27][0]))))+temp[2])
          ));
        mm[0][5] = ((1.34*((Vpk[0][35][2]*Vpk[5][36][2])+((Vpk[0][36][0]*
          Vpk[5][36][0])+(Vpk[0][36][1]*Vpk[5][36][1]))))+((4.16*((Vpk[0][34][2]
          *Vpk[5][34][2])+((Vpk[0][33][0]*Vpk[5][34][0])+(Vpk[0][34][1]*
          Vpk[5][34][1]))))+((8.35*((Vpk[0][33][2]*Vpk[5][33][2])+((
          Vpk[0][32][1]*Vpk[5][33][1])+(Vpk[0][33][0]*Vpk[5][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[0][12][2]*Vpk[6][12][2])+((Vpk[0][11][0]*
          Vpk[6][12][0])+(Vpk[0][12][1]*Vpk[6][12][1]))))+((29.27*((.14625*(
          Vpk[0][8][2]*Wpk[6][8][0]))+((.0351*(Vpk[0][7][1]*Wpk[6][8][0]))+(
          Vpk[0][8][0]*Vpk[6][8][0]))))+((Vpk[0][11][2]*Vpk[6][11][2])+((
          Vpk[0][10][1]*Vpk[6][11][1])+(Vpk[0][11][0]*Vpk[6][11][0])))));
        temp[1] = ((.55*((Vpk[0][18][2]*Vpk[6][18][2])+((Vpk[0][17][1]*
          Vpk[6][18][1])+(Vpk[0][18][0]*Vpk[6][18][0]))))+((1.21*((Vpk[0][16][2]
          *Vpk[6][16][2])+((Vpk[0][15][0]*Vpk[6][16][0])+(Vpk[0][16][1]*
          Vpk[6][16][1]))))+((2.79*((Vpk[0][14][2]*Vpk[6][14][2])+((
          Vpk[0][13][1]*Vpk[6][14][1])+(Vpk[0][14][0]*Vpk[6][14][0]))))+temp[0])
          ));
        mm[0][6] = ((.55*((Vpk[0][24][2]*Vpk[6][24][2])+((Vpk[0][23][1]*
          Vpk[6][24][1])+(Vpk[0][24][0]*Vpk[6][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[6][22][2])+((Vpk[0][21][0]*Vpk[6][22][0])+(Vpk[0][22][1]*
          Vpk[6][22][1]))))+((2.79*((Vpk[0][20][2]*Vpk[6][20][2])+((
          Vpk[0][19][1]*Vpk[6][20][1])+(Vpk[0][20][0]*Vpk[6][20][0]))))+temp[1])
          ));
        temp[0] = ((2.79*((Vpk[0][14][2]*Vpk[7][14][2])+((Vpk[0][13][1]*
          Vpk[7][14][1])+(Vpk[0][14][0]*Vpk[7][14][0]))))+((5.89*((Vpk[0][12][2]
          *Vpk[7][12][2])+((Vpk[0][11][0]*Vpk[7][12][0])+(Vpk[0][12][1]*
          Vpk[7][12][1]))))+(((Vpk[0][11][2]*Vpk[7][11][2])+((Vpk[0][10][1]*
          Vpk[7][11][1])+(Vpk[0][11][0]*Vpk[7][11][0])))-(29.27*((.14625*(
          Vpk[0][8][2]*s8))+((.0351*(Vpk[0][7][1]*s8))+(.14625*(Vpk[0][8][0]*c8)
          )))))));
        temp[1] = ((2.79*((Vpk[0][20][2]*Vpk[7][20][2])+((Vpk[0][19][1]*
          Vpk[7][20][1])+(Vpk[0][20][0]*Vpk[7][20][0]))))+((.55*((Vpk[0][18][2]*
          Vpk[7][18][2])+((Vpk[0][17][1]*Vpk[7][18][1])+(Vpk[0][18][0]*
          Vpk[7][18][0]))))+((1.21*((Vpk[0][16][2]*Vpk[7][16][2])+((
          Vpk[0][15][0]*Vpk[7][16][0])+(Vpk[0][16][1]*Vpk[7][16][1]))))+temp[0])
          ));
        mm[0][7] = ((.55*((Vpk[0][24][2]*Vpk[7][24][2])+((Vpk[0][23][1]*
          Vpk[7][24][1])+(Vpk[0][24][0]*Vpk[7][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[7][22][2])+((Vpk[0][21][0]*Vpk[7][22][0])+(Vpk[0][22][1]*
          Vpk[7][22][1]))))+temp[1]));
        temp[0] = ((2.79*((Vpk[0][14][2]*Vpk[8][14][2])+((Vpk[0][13][1]*
          Vpk[8][14][1])+(Vpk[0][14][0]*Vpk[8][14][0]))))+((5.89*((Vpk[0][12][2]
          *Vpk[8][12][2])+((Vpk[0][11][0]*Vpk[8][12][0])+(Vpk[0][12][1]*
          Vpk[8][12][1]))))+(((Vpk[0][11][2]*Vpk[8][11][2])+((Vpk[0][10][1]*
          Vpk[8][11][1])+(Vpk[0][11][0]*Vpk[8][11][0])))-(1.027377*Vpk[0][8][0])
          )));
        temp[1] = ((2.79*((Vpk[0][20][2]*Vpk[8][20][2])+((Vpk[0][19][1]*
          Vpk[8][20][1])+(Vpk[0][20][0]*Vpk[8][20][0]))))+((.55*((Vpk[0][18][2]*
          Vpk[8][18][2])+((Vpk[0][17][1]*Vpk[8][18][1])+(Vpk[0][18][0]*
          Vpk[8][18][0]))))+((1.21*((Vpk[0][16][2]*Vpk[8][16][2])+((
          Vpk[0][15][0]*Vpk[8][16][0])+(Vpk[0][16][1]*Vpk[8][16][1]))))+temp[0])
          ));
        mm[0][8] = ((.55*((Vpk[0][24][2]*Vpk[8][24][2])+((Vpk[0][23][1]*
          Vpk[8][24][1])+(Vpk[0][24][0]*Vpk[8][24][0]))))+((1.21*((Vpk[0][22][2]
          *Vpk[8][22][2])+((Vpk[0][21][0]*Vpk[8][22][0])+(Vpk[0][22][1]*
          Vpk[8][22][1]))))+temp[1]));
        mm[0][9] = ((5.89*((Vpk[0][12][2]*Vpk[9][12][2])+((Vpk[0][11][0]*
          Vpk[9][12][0])+(Vpk[0][12][1]*Vpk[9][12][1]))))+((.0442*(Vpk[0][11][2]
          *Wpk[9][11][0]))+((Vpk[0][11][0]*Vpk[9][11][0])-(.0065*(Vpk[0][10][1]*
          Wpk[9][11][0])))));
        mm[0][10] = ((5.89*((Vpk[0][12][2]*Vpk[10][12][2])+((Vpk[0][11][0]*
          Vpk[10][12][0])+(Vpk[0][12][1]*Vpk[10][12][1]))))+(((.0065*(
          Vpk[0][10][1]*s11))-(.0442*(Vpk[0][11][0]*c11)))-(.0442*(Vpk[0][11][2]
          *s11))));
        mm[0][11] = ((.0065*Vpk[0][11][0])+(5.89*(Vpk[0][11][0]*Vpk[11][12][0]))
          );
        mm[0][12] = (5.89*((.078*Vpk[0][12][2])-(.0312*Vpk[0][12][1])));
        mm[0][13] = ((.55*((Vpk[0][18][2]*Vpk[13][18][2])+((Vpk[0][17][1]*
          Vpk[13][18][1])+(Vpk[0][18][0]*Vpk[13][18][0]))))+((1.21*((
          Vpk[0][16][2]*Vpk[13][16][2])+((Vpk[0][16][1]*Vpk[13][16][1])-(.0039*(
          Vpk[0][15][0]*Wpk[13][16][2])))))+(2.79*(Vpk[0][13][1]*Vpk[13][14][1])
          )));
        mm[0][14] = ((.55*((Vpk[0][18][2]*Vpk[14][18][2])+((Vpk[0][17][1]*
          Vpk[14][18][1])+(Vpk[0][18][0]*Vpk[14][18][0]))))+((1.21*((
          Vpk[0][16][2]*Vpk[14][16][2])+((Vpk[0][15][0]*Vpk[14][16][0])+(
          Vpk[0][16][1]*Vpk[14][16][1]))))+(2.79*((.0013*Vpk[0][14][0])-(.1326*
          Vpk[0][14][2])))));
        mm[0][15] = ((.55*((Vpk[0][18][2]*Vpk[15][18][2])+((Vpk[0][17][1]*
          Vpk[15][18][1])+(Vpk[0][18][0]*Vpk[15][18][0]))))+(1.21*(((.0039*(
          Vpk[0][15][0]*s16))-(.1378*(Vpk[0][16][1]*s16)))-(.1378*(Vpk[0][16][2]
          *c16)))));
        mm[0][16] = ((.004719*Vpk[0][16][2])+(.55*((Vpk[0][18][2]*Vpk[16][18][2]
          )+((.065*(Vpk[0][17][1]*Wpk[16][18][2]))-(.0078*(Vpk[0][18][0]*s18))))
          ));
        mm[0][17] = (.03575*(Vpk[0][17][1]*c18));
        mm[0][18] = -(.03575*Vpk[0][18][2]);
        mm[0][19] = ((.55*((Vpk[0][24][2]*Vpk[19][24][2])+((Vpk[0][23][1]*
          Vpk[19][24][1])+(Vpk[0][24][0]*Vpk[19][24][0]))))+((1.21*((
          Vpk[0][22][2]*Vpk[19][22][2])+((Vpk[0][22][1]*Vpk[19][22][1])-(.0039*(
          Vpk[0][21][0]*Wpk[19][22][2])))))+(2.79*(Vpk[0][19][1]*Vpk[19][20][1])
          )));
        mm[0][20] = ((.55*((Vpk[0][24][2]*Vpk[20][24][2])+((Vpk[0][23][1]*
          Vpk[20][24][1])+(Vpk[0][24][0]*Vpk[20][24][0]))))+((1.21*((
          Vpk[0][22][2]*Vpk[20][22][2])+((Vpk[0][21][0]*Vpk[20][22][0])+(
          Vpk[0][22][1]*Vpk[20][22][1]))))+(2.79*((.0013*Vpk[0][20][0])+(.1326*
          Vpk[0][20][2])))));
        mm[0][21] = ((.55*((Vpk[0][24][2]*Vpk[21][24][2])+((Vpk[0][23][1]*
          Vpk[21][24][1])+(Vpk[0][24][0]*Vpk[21][24][0]))))+(1.21*((.1378*(
          Vpk[0][22][2]*c22))+((.0039*(Vpk[0][21][0]*s22))+(.1378*(Vpk[0][22][1]
          *s22))))));
        mm[0][22] = ((.004719*Vpk[0][22][2])+(.55*((Vpk[0][24][2]*Vpk[22][24][2]
          )-((.0078*(Vpk[0][24][0]*s24))+(.065*(Vpk[0][23][1]*Wpk[22][24][2]))))
          ));
        mm[0][23] = -(.03575*(Vpk[0][23][1]*c24));
        mm[0][24] = (.03575*Vpk[0][24][2]);
        mm[0][25] = ((1.34*((Vpk[0][29][2]*Vpk[25][30][2])+((Vpk[0][30][0]*
          Vpk[25][30][0])+(Vpk[0][30][1]*Vpk[25][30][1]))))+((4.16*((
          Vpk[0][28][2]*Vpk[25][28][2])+((Vpk[0][27][0]*Vpk[25][28][0])+(
          Vpk[0][28][1]*Vpk[25][28][1]))))+(8.35*((Vpk[0][27][2]*Vpk[25][27][2])
          +((Vpk[0][26][1]*Vpk[25][27][1])+(Vpk[0][27][0]*Vpk[25][27][0]))))));
        mm[0][26] = ((1.34*((Vpk[0][29][2]*Vpk[26][30][2])+((Vpk[0][30][0]*
          Vpk[26][30][0])+(Vpk[0][30][1]*Vpk[26][30][1]))))+((4.16*((
          Vpk[0][28][2]*Vpk[26][28][2])+((Vpk[0][27][0]*Vpk[26][28][0])+(
          Vpk[0][28][1]*Vpk[26][28][1]))))+(8.35*((.2379*(Vpk[0][27][2]*s27))+((
          .2379*(Vpk[0][27][0]*c27))+(Vpk[0][26][1]*Vpk[26][27][1]))))));
        mm[0][27] = ((1.34*((Vpk[0][29][2]*Vpk[27][30][2])+((Vpk[0][30][0]*
          Vpk[27][30][0])+(Vpk[0][30][1]*Vpk[27][30][1]))))+((4.16*((.0416*(
          Vpk[0][28][2]*c28))+((.0416*(Vpk[0][28][1]*s28))+(Vpk[0][27][0]*
          Vpk[27][28][0]))))+(8.35*((.0143*Vpk[0][27][0])+(.0169*Vpk[0][27][2]))
          )));
        mm[0][28] = ((1.34*((Vpk[0][29][2]*Vpk[28][30][2])+((Vpk[0][30][0]*
          Vpk[28][30][0])+(Vpk[0][30][1]*Vpk[28][30][1]))))+(4.16*((.0039*
          Vpk[0][28][1])-(.2158*Vpk[0][28][2]))));
        mm[0][29] = -(1.34*((.039*((Vpk[0][30][0]*s30)+(Vpk[0][30][1]*c30)))+(
          .0442*(Vpk[0][29][2]*c30))));
        mm[0][30] = (.059228*Vpk[0][30][0]);
        mm[0][31] = ((1.34*((Vpk[0][35][2]*Vpk[31][36][2])+((Vpk[0][36][0]*
          Vpk[31][36][0])+(Vpk[0][36][1]*Vpk[31][36][1]))))+((4.16*((
          Vpk[0][34][2]*Vpk[31][34][2])+((Vpk[0][33][0]*Vpk[31][34][0])+(
          Vpk[0][34][1]*Vpk[31][34][1]))))+(8.35*((Vpk[0][33][2]*Vpk[31][33][2])
          +((Vpk[0][32][1]*Vpk[31][33][1])+(Vpk[0][33][0]*Vpk[31][33][0]))))));
        mm[0][32] = ((1.34*((Vpk[0][35][2]*Vpk[32][36][2])+((Vpk[0][36][0]*
          Vpk[32][36][0])+(Vpk[0][36][1]*Vpk[32][36][1]))))+((4.16*((
          Vpk[0][34][2]*Vpk[32][34][2])+((Vpk[0][33][0]*Vpk[32][34][0])+(
          Vpk[0][34][1]*Vpk[32][34][1]))))+(8.35*((.2379*(Vpk[0][33][2]*s33))+((
          .2379*(Vpk[0][33][0]*c33))+(Vpk[0][32][1]*Vpk[32][33][1]))))));
        mm[0][33] = ((1.34*((Vpk[0][35][2]*Vpk[33][36][2])+((Vpk[0][36][0]*
          Vpk[33][36][0])+(Vpk[0][36][1]*Vpk[33][36][1]))))+((4.16*(((
          Vpk[0][33][0]*Vpk[33][34][0])-(.0416*(Vpk[0][34][1]*s34)))-(.0416*(
          Vpk[0][34][2]*c34))))+(8.35*((.0143*Vpk[0][33][0])-(.0169*
          Vpk[0][33][2])))));
        mm[0][34] = ((1.34*((Vpk[0][35][2]*Vpk[34][36][2])+((Vpk[0][36][0]*
          Vpk[34][36][0])+(Vpk[0][36][1]*Vpk[34][36][1]))))+(4.16*((.0039*
          Vpk[0][34][1])-(.2158*Vpk[0][34][2]))));
        mm[0][35] = -(1.34*((.039*((Vpk[0][36][0]*s36)+(Vpk[0][36][1]*c36)))+(
          .0442*(Vpk[0][35][2]*c36))));
        mm[0][36] = (.059228*Vpk[0][36][0]);
        temp[0] = (((16.61*((Cik[3][1][2]*Cik[3][1][2])+((Cik[3][1][0]*
          Cik[3][1][0])+(Cik[3][1][1]*Cik[3][1][1]))))+(29.27*((Vpk[1][8][2]*
          Vpk[1][8][2])+((Vpk[1][7][1]*Vpk[1][7][1])+(Vpk[1][8][0]*Vpk[1][8][0])
          ))))+((Vpk[1][11][2]*Vpk[1][11][2])+((Vpk[1][10][1]*Vpk[1][10][1])+(
          Vpk[1][11][0]*Vpk[1][11][0]))));
        temp[1] = ((1.21*((Vpk[1][16][2]*Vpk[1][16][2])+((Vpk[1][15][0]*
          Vpk[1][15][0])+(Vpk[1][16][1]*Vpk[1][16][1]))))+((2.79*((Vpk[1][14][2]
          *Vpk[1][14][2])+((Vpk[1][13][1]*Vpk[1][13][1])+(Vpk[1][14][0]*
          Vpk[1][14][0]))))+((5.89*((Vpk[1][12][2]*Vpk[1][12][2])+((
          Vpk[1][11][0]*Vpk[1][11][0])+(Vpk[1][12][1]*Vpk[1][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[1][22][2]*Vpk[1][22][2])+((Vpk[1][21][0]*
          Vpk[1][21][0])+(Vpk[1][22][1]*Vpk[1][22][1]))))+((2.79*((Vpk[1][20][2]
          *Vpk[1][20][2])+((Vpk[1][19][1]*Vpk[1][19][1])+(Vpk[1][20][0]*
          Vpk[1][20][0]))))+((.55*((Vpk[1][18][2]*Vpk[1][18][2])+((Vpk[1][17][1]
          *Vpk[1][17][1])+(Vpk[1][18][0]*Vpk[1][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[1][28][2]*Vpk[1][28][2])+((Vpk[1][27][0]*
          Vpk[1][27][0])+(Vpk[1][28][1]*Vpk[1][28][1]))))+((8.35*((Vpk[1][27][2]
          *Vpk[1][27][2])+((Vpk[1][26][1]*Vpk[1][26][1])+(Vpk[1][27][0]*
          Vpk[1][27][0]))))+((.55*((Vpk[1][24][2]*Vpk[1][24][2])+((Vpk[1][23][1]
          *Vpk[1][23][1])+(Vpk[1][24][0]*Vpk[1][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[1][34][2]*Vpk[1][34][2])+((Vpk[1][33][0]*
          Vpk[1][33][0])+(Vpk[1][34][1]*Vpk[1][34][1]))))+((8.35*((Vpk[1][33][2]
          *Vpk[1][33][2])+((Vpk[1][32][1]*Vpk[1][32][1])+(Vpk[1][33][0]*
          Vpk[1][33][0]))))+((1.34*((Vpk[1][29][2]*Vpk[1][29][2])+((
          Vpk[1][30][0]*Vpk[1][30][0])+(Vpk[1][30][1]*Vpk[1][30][1]))))+temp[3])
          ));
        mm[1][1] = ((1.34*((Vpk[1][35][2]*Vpk[1][35][2])+((Vpk[1][36][0]*
          Vpk[1][36][0])+(Vpk[1][36][1]*Vpk[1][36][1]))))+temp[4]);
        temp[0] = (((16.61*((Cik[3][1][2]*Cik[3][2][2])+((Cik[3][1][0]*
          Cik[3][2][0])+(Cik[3][1][1]*Cik[3][2][1]))))+(29.27*((Vpk[1][8][2]*
          Vpk[2][8][2])+((Vpk[1][7][1]*Vpk[2][7][1])+(Vpk[1][8][0]*Vpk[2][8][0])
          ))))+((Vpk[1][11][2]*Vpk[2][11][2])+((Vpk[1][10][1]*Vpk[2][10][1])+(
          Vpk[1][11][0]*Vpk[2][11][0]))));
        temp[1] = ((1.21*((Vpk[1][16][2]*Vpk[2][16][2])+((Vpk[1][15][0]*
          Vpk[2][15][0])+(Vpk[1][16][1]*Vpk[2][16][1]))))+((2.79*((Vpk[1][14][2]
          *Vpk[2][14][2])+((Vpk[1][13][1]*Vpk[2][13][1])+(Vpk[1][14][0]*
          Vpk[2][14][0]))))+((5.89*((Vpk[1][12][2]*Vpk[2][12][2])+((
          Vpk[1][11][0]*Vpk[2][11][0])+(Vpk[1][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[1][22][2]*Vpk[2][22][2])+((Vpk[1][21][0]*
          Vpk[2][21][0])+(Vpk[1][22][1]*Vpk[2][22][1]))))+((2.79*((Vpk[1][20][2]
          *Vpk[2][20][2])+((Vpk[1][19][1]*Vpk[2][19][1])+(Vpk[1][20][0]*
          Vpk[2][20][0]))))+((.55*((Vpk[1][18][2]*Vpk[2][18][2])+((Vpk[1][17][1]
          *Vpk[2][17][1])+(Vpk[1][18][0]*Vpk[2][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[1][28][2]*Vpk[2][28][2])+((Vpk[1][27][0]*
          Vpk[2][27][0])+(Vpk[1][28][1]*Vpk[2][28][1]))))+((8.35*((Vpk[1][27][2]
          *Vpk[2][27][2])+((Vpk[1][26][1]*Vpk[2][26][1])+(Vpk[1][27][0]*
          Vpk[2][27][0]))))+((.55*((Vpk[1][24][2]*Vpk[2][24][2])+((Vpk[1][23][1]
          *Vpk[2][23][1])+(Vpk[1][24][0]*Vpk[2][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[1][34][2]*Vpk[2][34][2])+((Vpk[1][33][0]*
          Vpk[2][33][0])+(Vpk[1][34][1]*Vpk[2][34][1]))))+((8.35*((Vpk[1][33][2]
          *Vpk[2][33][2])+((Vpk[1][32][1]*Vpk[2][32][1])+(Vpk[1][33][0]*
          Vpk[2][33][0]))))+((1.34*((Vpk[1][29][2]*Vpk[2][29][2])+((
          Vpk[1][30][0]*Vpk[2][30][0])+(Vpk[1][30][1]*Vpk[2][30][1]))))+temp[3])
          ));
        mm[1][2] = ((1.34*((Vpk[1][35][2]*Vpk[2][35][2])+((Vpk[1][36][0]*
          Vpk[2][36][0])+(Vpk[1][36][1]*Vpk[2][36][1]))))+temp[4]);
        temp[0] = ((5.89*((Vpk[1][12][2]*Vpk[3][12][2])+((Vpk[1][11][0]*
          Vpk[3][12][0])+(Vpk[1][12][1]*Vpk[3][12][1]))))+(((16.61*((.05*
          Cik[3][1][1])-(.1206*Cik[3][1][2])))+(29.27*((.14625*(Vpk[1][8][2]*
          Wpk[3][8][0]))+((.0351*(Vpk[1][7][1]*Wpk[3][8][0]))+(Vpk[1][8][0]*
          Vpk[3][8][0])))))+((Vpk[1][11][2]*Vpk[3][11][2])+((Vpk[1][10][1]*
          Vpk[3][11][1])+(Vpk[1][11][0]*Vpk[3][11][0])))));
        temp[1] = ((.55*((Vpk[1][18][2]*Vpk[3][18][2])+((Vpk[1][17][1]*
          Vpk[3][18][1])+(Vpk[1][18][0]*Vpk[3][18][0]))))+((1.21*((Vpk[1][16][2]
          *Vpk[3][16][2])+((Vpk[1][15][0]*Vpk[3][16][0])+(Vpk[1][16][1]*
          Vpk[3][16][1]))))+((2.79*((Vpk[1][14][2]*Vpk[3][14][2])+((
          Vpk[1][13][1]*Vpk[3][14][1])+(Vpk[1][14][0]*Vpk[3][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[1][24][2]*Vpk[3][24][2])+((Vpk[1][23][1]*
          Vpk[3][24][1])+(Vpk[1][24][0]*Vpk[3][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[3][22][2])+((Vpk[1][21][0]*Vpk[3][22][0])+(Vpk[1][22][1]*
          Vpk[3][22][1]))))+((2.79*((Vpk[1][20][2]*Vpk[3][20][2])+((
          Vpk[1][19][1]*Vpk[3][20][1])+(Vpk[1][20][0]*Vpk[3][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[1][29][2]*Vpk[3][30][2])+((Vpk[1][30][0]*
          Vpk[3][30][0])+(Vpk[1][30][1]*Vpk[3][30][1]))))+((4.16*((Vpk[1][28][2]
          *Vpk[3][28][2])+((Vpk[1][27][0]*Vpk[3][28][0])+(Vpk[1][28][1]*
          Vpk[3][28][1]))))+((8.35*((Vpk[1][27][2]*Vpk[3][27][2])+((
          Vpk[1][26][1]*Vpk[3][27][1])+(Vpk[1][27][0]*Vpk[3][27][0]))))+temp[2])
          ));
        mm[1][3] = ((1.34*((Vpk[1][35][2]*Vpk[3][36][2])+((Vpk[1][36][0]*
          Vpk[3][36][0])+(Vpk[1][36][1]*Vpk[3][36][1]))))+((4.16*((Vpk[1][34][2]
          *Vpk[3][34][2])+((Vpk[1][33][0]*Vpk[3][34][0])+(Vpk[1][34][1]*
          Vpk[3][34][1]))))+((8.35*((Vpk[1][33][2]*Vpk[3][33][2])+((
          Vpk[1][32][1]*Vpk[3][33][1])+(Vpk[1][33][0]*Vpk[3][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[1][12][2]*Vpk[4][12][2])+((Vpk[1][11][0]*
          Vpk[4][12][0])+(Vpk[1][12][1]*Vpk[4][12][1]))))+(((29.27*((.14625*(
          Vpk[1][8][2]*Wpk[4][8][0]))+((.0351*(Vpk[1][7][1]*Wpk[4][8][0]))+(
          Vpk[1][8][0]*Vpk[4][8][0]))))-(.8305*Cik[3][1][0]))+((Vpk[1][11][2]*
          Vpk[4][11][2])+((Vpk[1][10][1]*Vpk[4][11][1])+(Vpk[1][11][0]*
          Vpk[4][11][0])))));
        temp[1] = ((.55*((Vpk[1][18][2]*Vpk[4][18][2])+((Vpk[1][17][1]*
          Vpk[4][18][1])+(Vpk[1][18][0]*Vpk[4][18][0]))))+((1.21*((Vpk[1][16][2]
          *Vpk[4][16][2])+((Vpk[1][15][0]*Vpk[4][16][0])+(Vpk[1][16][1]*
          Vpk[4][16][1]))))+((2.79*((Vpk[1][14][2]*Vpk[4][14][2])+((
          Vpk[1][13][1]*Vpk[4][14][1])+(Vpk[1][14][0]*Vpk[4][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[1][24][2]*Vpk[4][24][2])+((Vpk[1][23][1]*
          Vpk[4][24][1])+(Vpk[1][24][0]*Vpk[4][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[4][22][2])+((Vpk[1][21][0]*Vpk[4][22][0])+(Vpk[1][22][1]*
          Vpk[4][22][1]))))+((2.79*((Vpk[1][20][2]*Vpk[4][20][2])+((
          Vpk[1][19][1]*Vpk[4][20][1])+(Vpk[1][20][0]*Vpk[4][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[1][29][2]*Vpk[4][30][2])+((Vpk[1][30][0]*
          Vpk[4][30][0])+(Vpk[1][30][1]*Vpk[4][30][1]))))+((4.16*((Vpk[1][28][2]
          *Vpk[4][28][2])+((Vpk[1][27][0]*Vpk[4][28][0])+(Vpk[1][28][1]*
          Vpk[4][28][1]))))+((8.35*((Vpk[1][27][2]*Vpk[4][27][2])+((
          Vpk[1][26][1]*Vpk[4][27][1])+(Vpk[1][27][0]*Vpk[4][27][0]))))+temp[2])
          ));
        mm[1][4] = ((1.34*((Vpk[1][35][2]*Vpk[4][36][2])+((Vpk[1][36][0]*
          Vpk[4][36][0])+(Vpk[1][36][1]*Vpk[4][36][1]))))+((4.16*((Vpk[1][34][2]
          *Vpk[4][34][2])+((Vpk[1][33][0]*Vpk[4][34][0])+(Vpk[1][34][1]*
          Vpk[4][34][1]))))+((8.35*((Vpk[1][33][2]*Vpk[4][33][2])+((
          Vpk[1][32][1]*Vpk[4][33][1])+(Vpk[1][33][0]*Vpk[4][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[1][12][2]*Vpk[5][12][2])+((Vpk[1][11][0]*
          Vpk[5][12][0])+(Vpk[1][12][1]*Vpk[5][12][1]))))+(((2.003166*
          Cik[3][1][0])+(29.27*((.14625*(Vpk[1][8][2]*Wpk[5][8][0]))+((.0351*(
          Vpk[1][7][1]*Wpk[5][8][0]))+(Vpk[1][8][0]*Vpk[5][8][0])))))+((
          Vpk[1][11][2]*Vpk[5][11][2])+((Vpk[1][10][1]*Vpk[5][11][1])+(
          Vpk[1][11][0]*Vpk[5][11][0])))));
        temp[1] = ((.55*((Vpk[1][18][2]*Vpk[5][18][2])+((Vpk[1][17][1]*
          Vpk[5][18][1])+(Vpk[1][18][0]*Vpk[5][18][0]))))+((1.21*((Vpk[1][16][2]
          *Vpk[5][16][2])+((Vpk[1][15][0]*Vpk[5][16][0])+(Vpk[1][16][1]*
          Vpk[5][16][1]))))+((2.79*((Vpk[1][14][2]*Vpk[5][14][2])+((
          Vpk[1][13][1]*Vpk[5][14][1])+(Vpk[1][14][0]*Vpk[5][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[1][24][2]*Vpk[5][24][2])+((Vpk[1][23][1]*
          Vpk[5][24][1])+(Vpk[1][24][0]*Vpk[5][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[5][22][2])+((Vpk[1][21][0]*Vpk[5][22][0])+(Vpk[1][22][1]*
          Vpk[5][22][1]))))+((2.79*((Vpk[1][20][2]*Vpk[5][20][2])+((
          Vpk[1][19][1]*Vpk[5][20][1])+(Vpk[1][20][0]*Vpk[5][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[1][29][2]*Vpk[5][30][2])+((Vpk[1][30][0]*
          Vpk[5][30][0])+(Vpk[1][30][1]*Vpk[5][30][1]))))+((4.16*((Vpk[1][28][2]
          *Vpk[5][28][2])+((Vpk[1][27][0]*Vpk[5][28][0])+(Vpk[1][28][1]*
          Vpk[5][28][1]))))+((8.35*((Vpk[1][27][2]*Vpk[5][27][2])+((
          Vpk[1][26][1]*Vpk[5][27][1])+(Vpk[1][27][0]*Vpk[5][27][0]))))+temp[2])
          ));
        mm[1][5] = ((1.34*((Vpk[1][35][2]*Vpk[5][36][2])+((Vpk[1][36][0]*
          Vpk[5][36][0])+(Vpk[1][36][1]*Vpk[5][36][1]))))+((4.16*((Vpk[1][34][2]
          *Vpk[5][34][2])+((Vpk[1][33][0]*Vpk[5][34][0])+(Vpk[1][34][1]*
          Vpk[5][34][1]))))+((8.35*((Vpk[1][33][2]*Vpk[5][33][2])+((
          Vpk[1][32][1]*Vpk[5][33][1])+(Vpk[1][33][0]*Vpk[5][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[1][12][2]*Vpk[6][12][2])+((Vpk[1][11][0]*
          Vpk[6][12][0])+(Vpk[1][12][1]*Vpk[6][12][1]))))+((29.27*((.14625*(
          Vpk[1][8][2]*Wpk[6][8][0]))+((.0351*(Vpk[1][7][1]*Wpk[6][8][0]))+(
          Vpk[1][8][0]*Vpk[6][8][0]))))+((Vpk[1][11][2]*Vpk[6][11][2])+((
          Vpk[1][10][1]*Vpk[6][11][1])+(Vpk[1][11][0]*Vpk[6][11][0])))));
        temp[1] = ((.55*((Vpk[1][18][2]*Vpk[6][18][2])+((Vpk[1][17][1]*
          Vpk[6][18][1])+(Vpk[1][18][0]*Vpk[6][18][0]))))+((1.21*((Vpk[1][16][2]
          *Vpk[6][16][2])+((Vpk[1][15][0]*Vpk[6][16][0])+(Vpk[1][16][1]*
          Vpk[6][16][1]))))+((2.79*((Vpk[1][14][2]*Vpk[6][14][2])+((
          Vpk[1][13][1]*Vpk[6][14][1])+(Vpk[1][14][0]*Vpk[6][14][0]))))+temp[0])
          ));
        mm[1][6] = ((.55*((Vpk[1][24][2]*Vpk[6][24][2])+((Vpk[1][23][1]*
          Vpk[6][24][1])+(Vpk[1][24][0]*Vpk[6][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[6][22][2])+((Vpk[1][21][0]*Vpk[6][22][0])+(Vpk[1][22][1]*
          Vpk[6][22][1]))))+((2.79*((Vpk[1][20][2]*Vpk[6][20][2])+((
          Vpk[1][19][1]*Vpk[6][20][1])+(Vpk[1][20][0]*Vpk[6][20][0]))))+temp[1])
          ));
        temp[0] = ((2.79*((Vpk[1][14][2]*Vpk[7][14][2])+((Vpk[1][13][1]*
          Vpk[7][14][1])+(Vpk[1][14][0]*Vpk[7][14][0]))))+((5.89*((Vpk[1][12][2]
          *Vpk[7][12][2])+((Vpk[1][11][0]*Vpk[7][12][0])+(Vpk[1][12][1]*
          Vpk[7][12][1]))))+(((Vpk[1][11][2]*Vpk[7][11][2])+((Vpk[1][10][1]*
          Vpk[7][11][1])+(Vpk[1][11][0]*Vpk[7][11][0])))-(29.27*((.14625*(
          Vpk[1][8][2]*s8))+((.0351*(Vpk[1][7][1]*s8))+(.14625*(Vpk[1][8][0]*c8)
          )))))));
        temp[1] = ((2.79*((Vpk[1][20][2]*Vpk[7][20][2])+((Vpk[1][19][1]*
          Vpk[7][20][1])+(Vpk[1][20][0]*Vpk[7][20][0]))))+((.55*((Vpk[1][18][2]*
          Vpk[7][18][2])+((Vpk[1][17][1]*Vpk[7][18][1])+(Vpk[1][18][0]*
          Vpk[7][18][0]))))+((1.21*((Vpk[1][16][2]*Vpk[7][16][2])+((
          Vpk[1][15][0]*Vpk[7][16][0])+(Vpk[1][16][1]*Vpk[7][16][1]))))+temp[0])
          ));
        mm[1][7] = ((.55*((Vpk[1][24][2]*Vpk[7][24][2])+((Vpk[1][23][1]*
          Vpk[7][24][1])+(Vpk[1][24][0]*Vpk[7][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[7][22][2])+((Vpk[1][21][0]*Vpk[7][22][0])+(Vpk[1][22][1]*
          Vpk[7][22][1]))))+temp[1]));
        temp[0] = ((2.79*((Vpk[1][14][2]*Vpk[8][14][2])+((Vpk[1][13][1]*
          Vpk[8][14][1])+(Vpk[1][14][0]*Vpk[8][14][0]))))+((5.89*((Vpk[1][12][2]
          *Vpk[8][12][2])+((Vpk[1][11][0]*Vpk[8][12][0])+(Vpk[1][12][1]*
          Vpk[8][12][1]))))+(((Vpk[1][11][2]*Vpk[8][11][2])+((Vpk[1][10][1]*
          Vpk[8][11][1])+(Vpk[1][11][0]*Vpk[8][11][0])))-(1.027377*Vpk[1][8][0])
          )));
        temp[1] = ((2.79*((Vpk[1][20][2]*Vpk[8][20][2])+((Vpk[1][19][1]*
          Vpk[8][20][1])+(Vpk[1][20][0]*Vpk[8][20][0]))))+((.55*((Vpk[1][18][2]*
          Vpk[8][18][2])+((Vpk[1][17][1]*Vpk[8][18][1])+(Vpk[1][18][0]*
          Vpk[8][18][0]))))+((1.21*((Vpk[1][16][2]*Vpk[8][16][2])+((
          Vpk[1][15][0]*Vpk[8][16][0])+(Vpk[1][16][1]*Vpk[8][16][1]))))+temp[0])
          ));
        mm[1][8] = ((.55*((Vpk[1][24][2]*Vpk[8][24][2])+((Vpk[1][23][1]*
          Vpk[8][24][1])+(Vpk[1][24][0]*Vpk[8][24][0]))))+((1.21*((Vpk[1][22][2]
          *Vpk[8][22][2])+((Vpk[1][21][0]*Vpk[8][22][0])+(Vpk[1][22][1]*
          Vpk[8][22][1]))))+temp[1]));
        mm[1][9] = ((5.89*((Vpk[1][12][2]*Vpk[9][12][2])+((Vpk[1][11][0]*
          Vpk[9][12][0])+(Vpk[1][12][1]*Vpk[9][12][1]))))+((.0442*(Vpk[1][11][2]
          *Wpk[9][11][0]))+((Vpk[1][11][0]*Vpk[9][11][0])-(.0065*(Vpk[1][10][1]*
          Wpk[9][11][0])))));
        mm[1][10] = ((5.89*((Vpk[1][12][2]*Vpk[10][12][2])+((Vpk[1][11][0]*
          Vpk[10][12][0])+(Vpk[1][12][1]*Vpk[10][12][1]))))+(((.0065*(
          Vpk[1][10][1]*s11))-(.0442*(Vpk[1][11][0]*c11)))-(.0442*(Vpk[1][11][2]
          *s11))));
        mm[1][11] = ((.0065*Vpk[1][11][0])+(5.89*(Vpk[1][11][0]*Vpk[11][12][0]))
          );
        mm[1][12] = (5.89*((.078*Vpk[1][12][2])-(.0312*Vpk[1][12][1])));
        mm[1][13] = ((.55*((Vpk[1][18][2]*Vpk[13][18][2])+((Vpk[1][17][1]*
          Vpk[13][18][1])+(Vpk[1][18][0]*Vpk[13][18][0]))))+((1.21*((
          Vpk[1][16][2]*Vpk[13][16][2])+((Vpk[1][16][1]*Vpk[13][16][1])-(.0039*(
          Vpk[1][15][0]*Wpk[13][16][2])))))+(2.79*(Vpk[1][13][1]*Vpk[13][14][1])
          )));
        mm[1][14] = ((.55*((Vpk[1][18][2]*Vpk[14][18][2])+((Vpk[1][17][1]*
          Vpk[14][18][1])+(Vpk[1][18][0]*Vpk[14][18][0]))))+((1.21*((
          Vpk[1][16][2]*Vpk[14][16][2])+((Vpk[1][15][0]*Vpk[14][16][0])+(
          Vpk[1][16][1]*Vpk[14][16][1]))))+(2.79*((.0013*Vpk[1][14][0])-(.1326*
          Vpk[1][14][2])))));
        mm[1][15] = ((.55*((Vpk[1][18][2]*Vpk[15][18][2])+((Vpk[1][17][1]*
          Vpk[15][18][1])+(Vpk[1][18][0]*Vpk[15][18][0]))))+(1.21*(((.0039*(
          Vpk[1][15][0]*s16))-(.1378*(Vpk[1][16][1]*s16)))-(.1378*(Vpk[1][16][2]
          *c16)))));
        mm[1][16] = ((.004719*Vpk[1][16][2])+(.55*((Vpk[1][18][2]*Vpk[16][18][2]
          )+((.065*(Vpk[1][17][1]*Wpk[16][18][2]))-(.0078*(Vpk[1][18][0]*s18))))
          ));
        mm[1][17] = (.03575*(Vpk[1][17][1]*c18));
        mm[1][18] = -(.03575*Vpk[1][18][2]);
        mm[1][19] = ((.55*((Vpk[1][24][2]*Vpk[19][24][2])+((Vpk[1][23][1]*
          Vpk[19][24][1])+(Vpk[1][24][0]*Vpk[19][24][0]))))+((1.21*((
          Vpk[1][22][2]*Vpk[19][22][2])+((Vpk[1][22][1]*Vpk[19][22][1])-(.0039*(
          Vpk[1][21][0]*Wpk[19][22][2])))))+(2.79*(Vpk[1][19][1]*Vpk[19][20][1])
          )));
        mm[1][20] = ((.55*((Vpk[1][24][2]*Vpk[20][24][2])+((Vpk[1][23][1]*
          Vpk[20][24][1])+(Vpk[1][24][0]*Vpk[20][24][0]))))+((1.21*((
          Vpk[1][22][2]*Vpk[20][22][2])+((Vpk[1][21][0]*Vpk[20][22][0])+(
          Vpk[1][22][1]*Vpk[20][22][1]))))+(2.79*((.0013*Vpk[1][20][0])+(.1326*
          Vpk[1][20][2])))));
        mm[1][21] = ((.55*((Vpk[1][24][2]*Vpk[21][24][2])+((Vpk[1][23][1]*
          Vpk[21][24][1])+(Vpk[1][24][0]*Vpk[21][24][0]))))+(1.21*((.1378*(
          Vpk[1][22][2]*c22))+((.0039*(Vpk[1][21][0]*s22))+(.1378*(Vpk[1][22][1]
          *s22))))));
        mm[1][22] = ((.004719*Vpk[1][22][2])+(.55*((Vpk[1][24][2]*Vpk[22][24][2]
          )-((.0078*(Vpk[1][24][0]*s24))+(.065*(Vpk[1][23][1]*Wpk[22][24][2]))))
          ));
        mm[1][23] = -(.03575*(Vpk[1][23][1]*c24));
        mm[1][24] = (.03575*Vpk[1][24][2]);
        mm[1][25] = ((1.34*((Vpk[1][29][2]*Vpk[25][30][2])+((Vpk[1][30][0]*
          Vpk[25][30][0])+(Vpk[1][30][1]*Vpk[25][30][1]))))+((4.16*((
          Vpk[1][28][2]*Vpk[25][28][2])+((Vpk[1][27][0]*Vpk[25][28][0])+(
          Vpk[1][28][1]*Vpk[25][28][1]))))+(8.35*((Vpk[1][27][2]*Vpk[25][27][2])
          +((Vpk[1][26][1]*Vpk[25][27][1])+(Vpk[1][27][0]*Vpk[25][27][0]))))));
        mm[1][26] = ((1.34*((Vpk[1][29][2]*Vpk[26][30][2])+((Vpk[1][30][0]*
          Vpk[26][30][0])+(Vpk[1][30][1]*Vpk[26][30][1]))))+((4.16*((
          Vpk[1][28][2]*Vpk[26][28][2])+((Vpk[1][27][0]*Vpk[26][28][0])+(
          Vpk[1][28][1]*Vpk[26][28][1]))))+(8.35*((.2379*(Vpk[1][27][2]*s27))+((
          .2379*(Vpk[1][27][0]*c27))+(Vpk[1][26][1]*Vpk[26][27][1]))))));
        mm[1][27] = ((1.34*((Vpk[1][29][2]*Vpk[27][30][2])+((Vpk[1][30][0]*
          Vpk[27][30][0])+(Vpk[1][30][1]*Vpk[27][30][1]))))+((4.16*((.0416*(
          Vpk[1][28][2]*c28))+((.0416*(Vpk[1][28][1]*s28))+(Vpk[1][27][0]*
          Vpk[27][28][0]))))+(8.35*((.0143*Vpk[1][27][0])+(.0169*Vpk[1][27][2]))
          )));
        mm[1][28] = ((1.34*((Vpk[1][29][2]*Vpk[28][30][2])+((Vpk[1][30][0]*
          Vpk[28][30][0])+(Vpk[1][30][1]*Vpk[28][30][1]))))+(4.16*((.0039*
          Vpk[1][28][1])-(.2158*Vpk[1][28][2]))));
        mm[1][29] = -(1.34*((.039*((Vpk[1][30][0]*s30)+(Vpk[1][30][1]*c30)))+(
          .0442*(Vpk[1][29][2]*c30))));
        mm[1][30] = (.059228*Vpk[1][30][0]);
        mm[1][31] = ((1.34*((Vpk[1][35][2]*Vpk[31][36][2])+((Vpk[1][36][0]*
          Vpk[31][36][0])+(Vpk[1][36][1]*Vpk[31][36][1]))))+((4.16*((
          Vpk[1][34][2]*Vpk[31][34][2])+((Vpk[1][33][0]*Vpk[31][34][0])+(
          Vpk[1][34][1]*Vpk[31][34][1]))))+(8.35*((Vpk[1][33][2]*Vpk[31][33][2])
          +((Vpk[1][32][1]*Vpk[31][33][1])+(Vpk[1][33][0]*Vpk[31][33][0]))))));
        mm[1][32] = ((1.34*((Vpk[1][35][2]*Vpk[32][36][2])+((Vpk[1][36][0]*
          Vpk[32][36][0])+(Vpk[1][36][1]*Vpk[32][36][1]))))+((4.16*((
          Vpk[1][34][2]*Vpk[32][34][2])+((Vpk[1][33][0]*Vpk[32][34][0])+(
          Vpk[1][34][1]*Vpk[32][34][1]))))+(8.35*((.2379*(Vpk[1][33][2]*s33))+((
          .2379*(Vpk[1][33][0]*c33))+(Vpk[1][32][1]*Vpk[32][33][1]))))));
        mm[1][33] = ((1.34*((Vpk[1][35][2]*Vpk[33][36][2])+((Vpk[1][36][0]*
          Vpk[33][36][0])+(Vpk[1][36][1]*Vpk[33][36][1]))))+((4.16*(((
          Vpk[1][33][0]*Vpk[33][34][0])-(.0416*(Vpk[1][34][1]*s34)))-(.0416*(
          Vpk[1][34][2]*c34))))+(8.35*((.0143*Vpk[1][33][0])-(.0169*
          Vpk[1][33][2])))));
        mm[1][34] = ((1.34*((Vpk[1][35][2]*Vpk[34][36][2])+((Vpk[1][36][0]*
          Vpk[34][36][0])+(Vpk[1][36][1]*Vpk[34][36][1]))))+(4.16*((.0039*
          Vpk[1][34][1])-(.2158*Vpk[1][34][2]))));
        mm[1][35] = -(1.34*((.039*((Vpk[1][36][0]*s36)+(Vpk[1][36][1]*c36)))+(
          .0442*(Vpk[1][35][2]*c36))));
        mm[1][36] = (.059228*Vpk[1][36][0]);
        temp[0] = (((16.61*((Cik[3][2][2]*Cik[3][2][2])+((Cik[3][2][0]*
          Cik[3][2][0])+(Cik[3][2][1]*Cik[3][2][1]))))+(29.27*((Vpk[2][8][2]*
          Vpk[2][8][2])+((Vpk[2][7][1]*Vpk[2][7][1])+(Vpk[2][8][0]*Vpk[2][8][0])
          ))))+((Vpk[2][11][2]*Vpk[2][11][2])+((Vpk[2][10][1]*Vpk[2][10][1])+(
          Vpk[2][11][0]*Vpk[2][11][0]))));
        temp[1] = ((1.21*((Vpk[2][16][2]*Vpk[2][16][2])+((Vpk[2][15][0]*
          Vpk[2][15][0])+(Vpk[2][16][1]*Vpk[2][16][1]))))+((2.79*((Vpk[2][14][2]
          *Vpk[2][14][2])+((Vpk[2][13][1]*Vpk[2][13][1])+(Vpk[2][14][0]*
          Vpk[2][14][0]))))+((5.89*((Vpk[2][12][2]*Vpk[2][12][2])+((
          Vpk[2][11][0]*Vpk[2][11][0])+(Vpk[2][12][1]*Vpk[2][12][1]))))+temp[0])
          ));
        temp[2] = ((1.21*((Vpk[2][22][2]*Vpk[2][22][2])+((Vpk[2][21][0]*
          Vpk[2][21][0])+(Vpk[2][22][1]*Vpk[2][22][1]))))+((2.79*((Vpk[2][20][2]
          *Vpk[2][20][2])+((Vpk[2][19][1]*Vpk[2][19][1])+(Vpk[2][20][0]*
          Vpk[2][20][0]))))+((.55*((Vpk[2][18][2]*Vpk[2][18][2])+((Vpk[2][17][1]
          *Vpk[2][17][1])+(Vpk[2][18][0]*Vpk[2][18][0]))))+temp[1])));
        temp[3] = ((4.16*((Vpk[2][28][2]*Vpk[2][28][2])+((Vpk[2][27][0]*
          Vpk[2][27][0])+(Vpk[2][28][1]*Vpk[2][28][1]))))+((8.35*((Vpk[2][27][2]
          *Vpk[2][27][2])+((Vpk[2][26][1]*Vpk[2][26][1])+(Vpk[2][27][0]*
          Vpk[2][27][0]))))+((.55*((Vpk[2][24][2]*Vpk[2][24][2])+((Vpk[2][23][1]
          *Vpk[2][23][1])+(Vpk[2][24][0]*Vpk[2][24][0]))))+temp[2])));
        temp[4] = ((4.16*((Vpk[2][34][2]*Vpk[2][34][2])+((Vpk[2][33][0]*
          Vpk[2][33][0])+(Vpk[2][34][1]*Vpk[2][34][1]))))+((8.35*((Vpk[2][33][2]
          *Vpk[2][33][2])+((Vpk[2][32][1]*Vpk[2][32][1])+(Vpk[2][33][0]*
          Vpk[2][33][0]))))+((1.34*((Vpk[2][29][2]*Vpk[2][29][2])+((
          Vpk[2][30][0]*Vpk[2][30][0])+(Vpk[2][30][1]*Vpk[2][30][1]))))+temp[3])
          ));
        mm[2][2] = ((1.34*((Vpk[2][35][2]*Vpk[2][35][2])+((Vpk[2][36][0]*
          Vpk[2][36][0])+(Vpk[2][36][1]*Vpk[2][36][1]))))+temp[4]);
        temp[0] = ((5.89*((Vpk[2][12][2]*Vpk[3][12][2])+((Vpk[2][11][0]*
          Vpk[3][12][0])+(Vpk[2][12][1]*Vpk[3][12][1]))))+(((16.61*((.05*
          Cik[3][2][1])-(.1206*Cik[3][2][2])))+(29.27*((.14625*(Vpk[2][8][2]*
          Wpk[3][8][0]))+((.0351*(Vpk[2][7][1]*Wpk[3][8][0]))+(Vpk[2][8][0]*
          Vpk[3][8][0])))))+((Vpk[2][11][2]*Vpk[3][11][2])+((Vpk[2][10][1]*
          Vpk[3][11][1])+(Vpk[2][11][0]*Vpk[3][11][0])))));
        temp[1] = ((.55*((Vpk[2][18][2]*Vpk[3][18][2])+((Vpk[2][17][1]*
          Vpk[3][18][1])+(Vpk[2][18][0]*Vpk[3][18][0]))))+((1.21*((Vpk[2][16][2]
          *Vpk[3][16][2])+((Vpk[2][15][0]*Vpk[3][16][0])+(Vpk[2][16][1]*
          Vpk[3][16][1]))))+((2.79*((Vpk[2][14][2]*Vpk[3][14][2])+((
          Vpk[2][13][1]*Vpk[3][14][1])+(Vpk[2][14][0]*Vpk[3][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[2][24][2]*Vpk[3][24][2])+((Vpk[2][23][1]*
          Vpk[3][24][1])+(Vpk[2][24][0]*Vpk[3][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[3][22][2])+((Vpk[2][21][0]*Vpk[3][22][0])+(Vpk[2][22][1]*
          Vpk[3][22][1]))))+((2.79*((Vpk[2][20][2]*Vpk[3][20][2])+((
          Vpk[2][19][1]*Vpk[3][20][1])+(Vpk[2][20][0]*Vpk[3][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[2][29][2]*Vpk[3][30][2])+((Vpk[2][30][0]*
          Vpk[3][30][0])+(Vpk[2][30][1]*Vpk[3][30][1]))))+((4.16*((Vpk[2][28][2]
          *Vpk[3][28][2])+((Vpk[2][27][0]*Vpk[3][28][0])+(Vpk[2][28][1]*
          Vpk[3][28][1]))))+((8.35*((Vpk[2][27][2]*Vpk[3][27][2])+((
          Vpk[2][26][1]*Vpk[3][27][1])+(Vpk[2][27][0]*Vpk[3][27][0]))))+temp[2])
          ));
        mm[2][3] = ((1.34*((Vpk[2][35][2]*Vpk[3][36][2])+((Vpk[2][36][0]*
          Vpk[3][36][0])+(Vpk[2][36][1]*Vpk[3][36][1]))))+((4.16*((Vpk[2][34][2]
          *Vpk[3][34][2])+((Vpk[2][33][0]*Vpk[3][34][0])+(Vpk[2][34][1]*
          Vpk[3][34][1]))))+((8.35*((Vpk[2][33][2]*Vpk[3][33][2])+((
          Vpk[2][32][1]*Vpk[3][33][1])+(Vpk[2][33][0]*Vpk[3][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[2][12][2]*Vpk[4][12][2])+((Vpk[2][11][0]*
          Vpk[4][12][0])+(Vpk[2][12][1]*Vpk[4][12][1]))))+(((29.27*((.14625*(
          Vpk[2][8][2]*Wpk[4][8][0]))+((.0351*(Vpk[2][7][1]*Wpk[4][8][0]))+(
          Vpk[2][8][0]*Vpk[4][8][0]))))-(.8305*Cik[3][2][0]))+((Vpk[2][11][2]*
          Vpk[4][11][2])+((Vpk[2][10][1]*Vpk[4][11][1])+(Vpk[2][11][0]*
          Vpk[4][11][0])))));
        temp[1] = ((.55*((Vpk[2][18][2]*Vpk[4][18][2])+((Vpk[2][17][1]*
          Vpk[4][18][1])+(Vpk[2][18][0]*Vpk[4][18][0]))))+((1.21*((Vpk[2][16][2]
          *Vpk[4][16][2])+((Vpk[2][15][0]*Vpk[4][16][0])+(Vpk[2][16][1]*
          Vpk[4][16][1]))))+((2.79*((Vpk[2][14][2]*Vpk[4][14][2])+((
          Vpk[2][13][1]*Vpk[4][14][1])+(Vpk[2][14][0]*Vpk[4][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[2][24][2]*Vpk[4][24][2])+((Vpk[2][23][1]*
          Vpk[4][24][1])+(Vpk[2][24][0]*Vpk[4][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[4][22][2])+((Vpk[2][21][0]*Vpk[4][22][0])+(Vpk[2][22][1]*
          Vpk[4][22][1]))))+((2.79*((Vpk[2][20][2]*Vpk[4][20][2])+((
          Vpk[2][19][1]*Vpk[4][20][1])+(Vpk[2][20][0]*Vpk[4][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[2][29][2]*Vpk[4][30][2])+((Vpk[2][30][0]*
          Vpk[4][30][0])+(Vpk[2][30][1]*Vpk[4][30][1]))))+((4.16*((Vpk[2][28][2]
          *Vpk[4][28][2])+((Vpk[2][27][0]*Vpk[4][28][0])+(Vpk[2][28][1]*
          Vpk[4][28][1]))))+((8.35*((Vpk[2][27][2]*Vpk[4][27][2])+((
          Vpk[2][26][1]*Vpk[4][27][1])+(Vpk[2][27][0]*Vpk[4][27][0]))))+temp[2])
          ));
        mm[2][4] = ((1.34*((Vpk[2][35][2]*Vpk[4][36][2])+((Vpk[2][36][0]*
          Vpk[4][36][0])+(Vpk[2][36][1]*Vpk[4][36][1]))))+((4.16*((Vpk[2][34][2]
          *Vpk[4][34][2])+((Vpk[2][33][0]*Vpk[4][34][0])+(Vpk[2][34][1]*
          Vpk[4][34][1]))))+((8.35*((Vpk[2][33][2]*Vpk[4][33][2])+((
          Vpk[2][32][1]*Vpk[4][33][1])+(Vpk[2][33][0]*Vpk[4][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[2][12][2]*Vpk[5][12][2])+((Vpk[2][11][0]*
          Vpk[5][12][0])+(Vpk[2][12][1]*Vpk[5][12][1]))))+(((2.003166*
          Cik[3][2][0])+(29.27*((.14625*(Vpk[2][8][2]*Wpk[5][8][0]))+((.0351*(
          Vpk[2][7][1]*Wpk[5][8][0]))+(Vpk[2][8][0]*Vpk[5][8][0])))))+((
          Vpk[2][11][2]*Vpk[5][11][2])+((Vpk[2][10][1]*Vpk[5][11][1])+(
          Vpk[2][11][0]*Vpk[5][11][0])))));
        temp[1] = ((.55*((Vpk[2][18][2]*Vpk[5][18][2])+((Vpk[2][17][1]*
          Vpk[5][18][1])+(Vpk[2][18][0]*Vpk[5][18][0]))))+((1.21*((Vpk[2][16][2]
          *Vpk[5][16][2])+((Vpk[2][15][0]*Vpk[5][16][0])+(Vpk[2][16][1]*
          Vpk[5][16][1]))))+((2.79*((Vpk[2][14][2]*Vpk[5][14][2])+((
          Vpk[2][13][1]*Vpk[5][14][1])+(Vpk[2][14][0]*Vpk[5][14][0]))))+temp[0])
          ));
        temp[2] = ((.55*((Vpk[2][24][2]*Vpk[5][24][2])+((Vpk[2][23][1]*
          Vpk[5][24][1])+(Vpk[2][24][0]*Vpk[5][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[5][22][2])+((Vpk[2][21][0]*Vpk[5][22][0])+(Vpk[2][22][1]*
          Vpk[5][22][1]))))+((2.79*((Vpk[2][20][2]*Vpk[5][20][2])+((
          Vpk[2][19][1]*Vpk[5][20][1])+(Vpk[2][20][0]*Vpk[5][20][0]))))+temp[1])
          ));
        temp[3] = ((1.34*((Vpk[2][29][2]*Vpk[5][30][2])+((Vpk[2][30][0]*
          Vpk[5][30][0])+(Vpk[2][30][1]*Vpk[5][30][1]))))+((4.16*((Vpk[2][28][2]
          *Vpk[5][28][2])+((Vpk[2][27][0]*Vpk[5][28][0])+(Vpk[2][28][1]*
          Vpk[5][28][1]))))+((8.35*((Vpk[2][27][2]*Vpk[5][27][2])+((
          Vpk[2][26][1]*Vpk[5][27][1])+(Vpk[2][27][0]*Vpk[5][27][0]))))+temp[2])
          ));
        mm[2][5] = ((1.34*((Vpk[2][35][2]*Vpk[5][36][2])+((Vpk[2][36][0]*
          Vpk[5][36][0])+(Vpk[2][36][1]*Vpk[5][36][1]))))+((4.16*((Vpk[2][34][2]
          *Vpk[5][34][2])+((Vpk[2][33][0]*Vpk[5][34][0])+(Vpk[2][34][1]*
          Vpk[5][34][1]))))+((8.35*((Vpk[2][33][2]*Vpk[5][33][2])+((
          Vpk[2][32][1]*Vpk[5][33][1])+(Vpk[2][33][0]*Vpk[5][33][0]))))+temp[3])
          ));
        temp[0] = ((5.89*((Vpk[2][12][2]*Vpk[6][12][2])+((Vpk[2][11][0]*
          Vpk[6][12][0])+(Vpk[2][12][1]*Vpk[6][12][1]))))+((29.27*((.14625*(
          Vpk[2][8][2]*Wpk[6][8][0]))+((.0351*(Vpk[2][7][1]*Wpk[6][8][0]))+(
          Vpk[2][8][0]*Vpk[6][8][0]))))+((Vpk[2][11][2]*Vpk[6][11][2])+((
          Vpk[2][10][1]*Vpk[6][11][1])+(Vpk[2][11][0]*Vpk[6][11][0])))));
        temp[1] = ((.55*((Vpk[2][18][2]*Vpk[6][18][2])+((Vpk[2][17][1]*
          Vpk[6][18][1])+(Vpk[2][18][0]*Vpk[6][18][0]))))+((1.21*((Vpk[2][16][2]
          *Vpk[6][16][2])+((Vpk[2][15][0]*Vpk[6][16][0])+(Vpk[2][16][1]*
          Vpk[6][16][1]))))+((2.79*((Vpk[2][14][2]*Vpk[6][14][2])+((
          Vpk[2][13][1]*Vpk[6][14][1])+(Vpk[2][14][0]*Vpk[6][14][0]))))+temp[0])
          ));
        mm[2][6] = ((.55*((Vpk[2][24][2]*Vpk[6][24][2])+((Vpk[2][23][1]*
          Vpk[6][24][1])+(Vpk[2][24][0]*Vpk[6][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[6][22][2])+((Vpk[2][21][0]*Vpk[6][22][0])+(Vpk[2][22][1]*
          Vpk[6][22][1]))))+((2.79*((Vpk[2][20][2]*Vpk[6][20][2])+((
          Vpk[2][19][1]*Vpk[6][20][1])+(Vpk[2][20][0]*Vpk[6][20][0]))))+temp[1])
          ));
        temp[0] = ((2.79*((Vpk[2][14][2]*Vpk[7][14][2])+((Vpk[2][13][1]*
          Vpk[7][14][1])+(Vpk[2][14][0]*Vpk[7][14][0]))))+((5.89*((Vpk[2][12][2]
          *Vpk[7][12][2])+((Vpk[2][11][0]*Vpk[7][12][0])+(Vpk[2][12][1]*
          Vpk[7][12][1]))))+(((Vpk[2][11][2]*Vpk[7][11][2])+((Vpk[2][10][1]*
          Vpk[7][11][1])+(Vpk[2][11][0]*Vpk[7][11][0])))-(29.27*((.14625*(
          Vpk[2][8][2]*s8))+((.0351*(Vpk[2][7][1]*s8))+(.14625*(Vpk[2][8][0]*c8)
          )))))));
        temp[1] = ((2.79*((Vpk[2][20][2]*Vpk[7][20][2])+((Vpk[2][19][1]*
          Vpk[7][20][1])+(Vpk[2][20][0]*Vpk[7][20][0]))))+((.55*((Vpk[2][18][2]*
          Vpk[7][18][2])+((Vpk[2][17][1]*Vpk[7][18][1])+(Vpk[2][18][0]*
          Vpk[7][18][0]))))+((1.21*((Vpk[2][16][2]*Vpk[7][16][2])+((
          Vpk[2][15][0]*Vpk[7][16][0])+(Vpk[2][16][1]*Vpk[7][16][1]))))+temp[0])
          ));
        mm[2][7] = ((.55*((Vpk[2][24][2]*Vpk[7][24][2])+((Vpk[2][23][1]*
          Vpk[7][24][1])+(Vpk[2][24][0]*Vpk[7][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[7][22][2])+((Vpk[2][21][0]*Vpk[7][22][0])+(Vpk[2][22][1]*
          Vpk[7][22][1]))))+temp[1]));
        temp[0] = ((2.79*((Vpk[2][14][2]*Vpk[8][14][2])+((Vpk[2][13][1]*
          Vpk[8][14][1])+(Vpk[2][14][0]*Vpk[8][14][0]))))+((5.89*((Vpk[2][12][2]
          *Vpk[8][12][2])+((Vpk[2][11][0]*Vpk[8][12][0])+(Vpk[2][12][1]*
          Vpk[8][12][1]))))+(((Vpk[2][11][2]*Vpk[8][11][2])+((Vpk[2][10][1]*
          Vpk[8][11][1])+(Vpk[2][11][0]*Vpk[8][11][0])))-(1.027377*Vpk[2][8][0])
          )));
        temp[1] = ((2.79*((Vpk[2][20][2]*Vpk[8][20][2])+((Vpk[2][19][1]*
          Vpk[8][20][1])+(Vpk[2][20][0]*Vpk[8][20][0]))))+((.55*((Vpk[2][18][2]*
          Vpk[8][18][2])+((Vpk[2][17][1]*Vpk[8][18][1])+(Vpk[2][18][0]*
          Vpk[8][18][0]))))+((1.21*((Vpk[2][16][2]*Vpk[8][16][2])+((
          Vpk[2][15][0]*Vpk[8][16][0])+(Vpk[2][16][1]*Vpk[8][16][1]))))+temp[0])
          ));
        mm[2][8] = ((.55*((Vpk[2][24][2]*Vpk[8][24][2])+((Vpk[2][23][1]*
          Vpk[8][24][1])+(Vpk[2][24][0]*Vpk[8][24][0]))))+((1.21*((Vpk[2][22][2]
          *Vpk[8][22][2])+((Vpk[2][21][0]*Vpk[8][22][0])+(Vpk[2][22][1]*
          Vpk[8][22][1]))))+temp[1]));
        mm[2][9] = ((5.89*((Vpk[2][12][2]*Vpk[9][12][2])+((Vpk[2][11][0]*
          Vpk[9][12][0])+(Vpk[2][12][1]*Vpk[9][12][1]))))+((.0442*(Vpk[2][11][2]
          *Wpk[9][11][0]))+((Vpk[2][11][0]*Vpk[9][11][0])-(.0065*(Vpk[2][10][1]*
          Wpk[9][11][0])))));
        mm[2][10] = ((5.89*((Vpk[2][12][2]*Vpk[10][12][2])+((Vpk[2][11][0]*
          Vpk[10][12][0])+(Vpk[2][12][1]*Vpk[10][12][1]))))+(((.0065*(
          Vpk[2][10][1]*s11))-(.0442*(Vpk[2][11][0]*c11)))-(.0442*(Vpk[2][11][2]
          *s11))));
        mm[2][11] = ((.0065*Vpk[2][11][0])+(5.89*(Vpk[2][11][0]*Vpk[11][12][0]))
          );
        mm[2][12] = (5.89*((.078*Vpk[2][12][2])-(.0312*Vpk[2][12][1])));
        mm[2][13] = ((.55*((Vpk[2][18][2]*Vpk[13][18][2])+((Vpk[2][17][1]*
          Vpk[13][18][1])+(Vpk[2][18][0]*Vpk[13][18][0]))))+((1.21*((
          Vpk[2][16][2]*Vpk[13][16][2])+((Vpk[2][16][1]*Vpk[13][16][1])-(.0039*(
          Vpk[2][15][0]*Wpk[13][16][2])))))+(2.79*(Vpk[2][13][1]*Vpk[13][14][1])
          )));
        mm[2][14] = ((.55*((Vpk[2][18][2]*Vpk[14][18][2])+((Vpk[2][17][1]*
          Vpk[14][18][1])+(Vpk[2][18][0]*Vpk[14][18][0]))))+((1.21*((
          Vpk[2][16][2]*Vpk[14][16][2])+((Vpk[2][15][0]*Vpk[14][16][0])+(
          Vpk[2][16][1]*Vpk[14][16][1]))))+(2.79*((.0013*Vpk[2][14][0])-(.1326*
          Vpk[2][14][2])))));
        mm[2][15] = ((.55*((Vpk[2][18][2]*Vpk[15][18][2])+((Vpk[2][17][1]*
          Vpk[15][18][1])+(Vpk[2][18][0]*Vpk[15][18][0]))))+(1.21*(((.0039*(
          Vpk[2][15][0]*s16))-(.1378*(Vpk[2][16][1]*s16)))-(.1378*(Vpk[2][16][2]
          *c16)))));
        mm[2][16] = ((.004719*Vpk[2][16][2])+(.55*((Vpk[2][18][2]*Vpk[16][18][2]
          )+((.065*(Vpk[2][17][1]*Wpk[16][18][2]))-(.0078*(Vpk[2][18][0]*s18))))
          ));
        mm[2][17] = (.03575*(Vpk[2][17][1]*c18));
        mm[2][18] = -(.03575*Vpk[2][18][2]);
        mm[2][19] = ((.55*((Vpk[2][24][2]*Vpk[19][24][2])+((Vpk[2][23][1]*
          Vpk[19][24][1])+(Vpk[2][24][0]*Vpk[19][24][0]))))+((1.21*((
          Vpk[2][22][2]*Vpk[19][22][2])+((Vpk[2][22][1]*Vpk[19][22][1])-(.0039*(
          Vpk[2][21][0]*Wpk[19][22][2])))))+(2.79*(Vpk[2][19][1]*Vpk[19][20][1])
          )));
        mm[2][20] = ((.55*((Vpk[2][24][2]*Vpk[20][24][2])+((Vpk[2][23][1]*
          Vpk[20][24][1])+(Vpk[2][24][0]*Vpk[20][24][0]))))+((1.21*((
          Vpk[2][22][2]*Vpk[20][22][2])+((Vpk[2][21][0]*Vpk[20][22][0])+(
          Vpk[2][22][1]*Vpk[20][22][1]))))+(2.79*((.0013*Vpk[2][20][0])+(.1326*
          Vpk[2][20][2])))));
        mm[2][21] = ((.55*((Vpk[2][24][2]*Vpk[21][24][2])+((Vpk[2][23][1]*
          Vpk[21][24][1])+(Vpk[2][24][0]*Vpk[21][24][0]))))+(1.21*((.1378*(
          Vpk[2][22][2]*c22))+((.0039*(Vpk[2][21][0]*s22))+(.1378*(Vpk[2][22][1]
          *s22))))));
        mm[2][22] = ((.004719*Vpk[2][22][2])+(.55*((Vpk[2][24][2]*Vpk[22][24][2]
          )-((.0078*(Vpk[2][24][0]*s24))+(.065*(Vpk[2][23][1]*Wpk[22][24][2]))))
          ));
        mm[2][23] = -(.03575*(Vpk[2][23][1]*c24));
        mm[2][24] = (.03575*Vpk[2][24][2]);
        mm[2][25] = ((1.34*((Vpk[2][29][2]*Vpk[25][30][2])+((Vpk[2][30][0]*
          Vpk[25][30][0])+(Vpk[2][30][1]*Vpk[25][30][1]))))+((4.16*((
          Vpk[2][28][2]*Vpk[25][28][2])+((Vpk[2][27][0]*Vpk[25][28][0])+(
          Vpk[2][28][1]*Vpk[25][28][1]))))+(8.35*((Vpk[2][27][2]*Vpk[25][27][2])
          +((Vpk[2][26][1]*Vpk[25][27][1])+(Vpk[2][27][0]*Vpk[25][27][0]))))));
        mm[2][26] = ((1.34*((Vpk[2][29][2]*Vpk[26][30][2])+((Vpk[2][30][0]*
          Vpk[26][30][0])+(Vpk[2][30][1]*Vpk[26][30][1]))))+((4.16*((
          Vpk[2][28][2]*Vpk[26][28][2])+((Vpk[2][27][0]*Vpk[26][28][0])+(
          Vpk[2][28][1]*Vpk[26][28][1]))))+(8.35*((.2379*(Vpk[2][27][2]*s27))+((
          .2379*(Vpk[2][27][0]*c27))+(Vpk[2][26][1]*Vpk[26][27][1]))))));
        mm[2][27] = ((1.34*((Vpk[2][29][2]*Vpk[27][30][2])+((Vpk[2][30][0]*
          Vpk[27][30][0])+(Vpk[2][30][1]*Vpk[27][30][1]))))+((4.16*((.0416*(
          Vpk[2][28][2]*c28))+((.0416*(Vpk[2][28][1]*s28))+(Vpk[2][27][0]*
          Vpk[27][28][0]))))+(8.35*((.0143*Vpk[2][27][0])+(.0169*Vpk[2][27][2]))
          )));
        mm[2][28] = ((1.34*((Vpk[2][29][2]*Vpk[28][30][2])+((Vpk[2][30][0]*
          Vpk[28][30][0])+(Vpk[2][30][1]*Vpk[28][30][1]))))+(4.16*((.0039*
          Vpk[2][28][1])-(.2158*Vpk[2][28][2]))));
        mm[2][29] = -(1.34*((.039*((Vpk[2][30][0]*s30)+(Vpk[2][30][1]*c30)))+(
          .0442*(Vpk[2][29][2]*c30))));
        mm[2][30] = (.059228*Vpk[2][30][0]);
        mm[2][31] = ((1.34*((Vpk[2][35][2]*Vpk[31][36][2])+((Vpk[2][36][0]*
          Vpk[31][36][0])+(Vpk[2][36][1]*Vpk[31][36][1]))))+((4.16*((
          Vpk[2][34][2]*Vpk[31][34][2])+((Vpk[2][33][0]*Vpk[31][34][0])+(
          Vpk[2][34][1]*Vpk[31][34][1]))))+(8.35*((Vpk[2][33][2]*Vpk[31][33][2])
          +((Vpk[2][32][1]*Vpk[31][33][1])+(Vpk[2][33][0]*Vpk[31][33][0]))))));
        mm[2][32] = ((1.34*((Vpk[2][35][2]*Vpk[32][36][2])+((Vpk[2][36][0]*
          Vpk[32][36][0])+(Vpk[2][36][1]*Vpk[32][36][1]))))+((4.16*((
          Vpk[2][34][2]*Vpk[32][34][2])+((Vpk[2][33][0]*Vpk[32][34][0])+(
          Vpk[2][34][1]*Vpk[32][34][1]))))+(8.35*((.2379*(Vpk[2][33][2]*s33))+((
          .2379*(Vpk[2][33][0]*c33))+(Vpk[2][32][1]*Vpk[32][33][1]))))));
        mm[2][33] = ((1.34*((Vpk[2][35][2]*Vpk[33][36][2])+((Vpk[2][36][0]*
          Vpk[33][36][0])+(Vpk[2][36][1]*Vpk[33][36][1]))))+((4.16*(((
          Vpk[2][33][0]*Vpk[33][34][0])-(.0416*(Vpk[2][34][1]*s34)))-(.0416*(
          Vpk[2][34][2]*c34))))+(8.35*((.0143*Vpk[2][33][0])-(.0169*
          Vpk[2][33][2])))));
        mm[2][34] = ((1.34*((Vpk[2][35][2]*Vpk[34][36][2])+((Vpk[2][36][0]*
          Vpk[34][36][0])+(Vpk[2][36][1]*Vpk[34][36][1]))))+(4.16*((.0039*
          Vpk[2][34][1])-(.2158*Vpk[2][34][2]))));
        mm[2][35] = -(1.34*((.039*((Vpk[2][36][0]*s36)+(Vpk[2][36][1]*c36)))+(
          .0442*(Vpk[2][35][2]*c36))));
        mm[2][36] = (.059228*Vpk[2][36][0]);
        temp[0] = (((.006*(Wpk[3][11][2]*Wpk[3][11][2]))+((.001*(Wpk[3][10][1]*
          Wpk[3][10][1]))+(.006*(Wpk[3][11][0]*Wpk[3][11][0]))))+((Vpk[3][11][2]
          *Vpk[3][11][2])+((Vpk[3][11][0]*Vpk[3][11][0])+(Vpk[3][11][1]*
          Vpk[3][11][1]))));
        temp[1] = (((29.27*((.0213890625*(Wpk[3][8][0]*Wpk[3][8][0]))+((
          .00123201*(Wpk[3][8][0]*Wpk[3][8][0]))+(Vpk[3][8][0]*Vpk[3][8][0]))))+
          ((.73*(Wpk[3][8][2]*Wpk[3][8][2]))+((.32*(s7*s7))+(.63*(Wpk[3][8][0]*
          Wpk[3][8][0])))))+temp[0]);
        temp[2] = (((5.89*((Vpk[3][12][2]*Vpk[3][12][2])+((Vpk[3][12][0]*
          Vpk[3][12][0])+(Vpk[3][12][1]*Vpk[3][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[3][12][2]))+((.023*(Wpk[3][12][1]*Wpk[3][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[3][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[3][14][2]*Vpk[3][14][2])+((Vpk[3][14][0]*
          Vpk[3][14][0])+(Vpk[3][14][1]*Vpk[3][14][1]))))+((.025*(Wpk[3][14][2]*
          Wpk[3][14][2]))+((.005*(Wpk[3][14][0]*Wpk[3][14][0]))+(.025*(
          Wpk[3][13][1]*Wpk[3][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[3][16][2]*Vpk[3][16][2])+((Vpk[3][16][0]*
          Vpk[3][16][0])+(Vpk[3][16][1]*Vpk[3][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[3][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[3][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[3][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[3][18][2]*Vpk[3][18][2])+((Vpk[3][18][0]*
          Vpk[3][18][0])+(Vpk[3][18][1]*Vpk[3][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[3][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[3][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[3][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[3][20][2]*Vpk[3][20][2])+((Vpk[3][20][0]*
          Vpk[3][20][0])+(Vpk[3][20][1]*Vpk[3][20][1]))))+((.025*(Wpk[3][20][2]*
          Wpk[3][20][2]))+((.005*(Wpk[3][20][0]*Wpk[3][20][0]))+(.025*(
          Wpk[3][19][1]*Wpk[3][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[3][22][2]*Vpk[3][22][2])+((Vpk[3][22][0]*
          Vpk[3][22][0])+(Vpk[3][22][1]*Vpk[3][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[3][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[3][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[3][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[3][24][2]*Vpk[3][24][2])+((Vpk[3][24][0]*
          Vpk[3][24][0])+(Vpk[3][24][1]*Vpk[3][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[3][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[3][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[3][23][1])))))+temp[7]);
        temp[9] = ((4.16*((Vpk[3][28][2]*Vpk[3][28][2])+((Vpk[3][28][0]*
          Vpk[3][28][0])+(Vpk[3][28][1]*Vpk[3][28][1]))))+((.055*(Wpk[3][28][2]*
          Wpk[3][28][2]))+((.007*(Wpk[3][28][1]*Wpk[3][28][1]))+(.056*(
          Wpk[3][27][0]*Wpk[3][27][0])))));
        temp[10] = ((1.34*((Vpk[3][30][2]*Vpk[3][30][2])+((Vpk[3][30][0]*
          Vpk[3][30][0])+(Vpk[3][30][1]*Vpk[3][30][1]))))+((.0018*(Wpk[3][29][2]
          *Wpk[3][29][2]))+((.007*(Wpk[3][30][1]*Wpk[3][30][1]))+(.0075*(
          Wpk[3][30][0]*Wpk[3][30][0])))));
        temp[11] = (temp[10]+(temp[9]+(((8.35*((Vpk[3][27][2]*Vpk[3][27][2])+((
          Vpk[3][27][0]*Vpk[3][27][0])+(Vpk[3][27][1]*Vpk[3][27][1]))))+((.15*(
          Wpk[3][27][2]*Wpk[3][27][2]))+((.025*(s26*s26))+(.16*(Wpk[3][27][0]*
          Wpk[3][27][0])))))+temp[8])));
        temp[12] = ((4.16*((Vpk[3][34][2]*Vpk[3][34][2])+((Vpk[3][34][0]*
          Vpk[3][34][0])+(Vpk[3][34][1]*Vpk[3][34][1]))))+((.055*(Wpk[3][34][2]*
          Wpk[3][34][2]))+((.007*(Wpk[3][34][1]*Wpk[3][34][1]))+(.056*(
          Wpk[3][33][0]*Wpk[3][33][0])))));
        temp[13] = ((1.34*((Vpk[3][36][2]*Vpk[3][36][2])+((Vpk[3][36][0]*
          Vpk[3][36][0])+(Vpk[3][36][1]*Vpk[3][36][1]))))+((.0018*(Wpk[3][35][2]
          *Wpk[3][35][2]))+((.007*(Wpk[3][36][1]*Wpk[3][36][1]))+(.0075*(
          Wpk[3][36][0]*Wpk[3][36][0])))));
        mm[3][3] = (.4631068196+(temp[13]+(temp[12]+(((8.35*((Vpk[3][33][2]*
          Vpk[3][33][2])+((Vpk[3][33][0]*Vpk[3][33][0])+(Vpk[3][33][1]*
          Vpk[3][33][1]))))+((.15*(Wpk[3][33][2]*Wpk[3][33][2]))+((.025*(s32*s32
          ))+(.16*(Wpk[3][33][0]*Wpk[3][33][0])))))+temp[11]))));
        temp[0] = ((29.27*((.0213890625*(Wpk[3][8][0]*Wpk[4][8][0]))+((.00123201
          *(Wpk[3][8][0]*Wpk[4][8][0]))+(Vpk[3][8][0]*Vpk[4][8][0]))))+((.73*(
          Wpk[3][8][2]*Wpk[4][8][2]))+((.63*(Wpk[3][8][0]*Wpk[4][8][0]))-(.32*(
          Wpk[4][7][1]*s7)))));
        temp[1] = (temp[0]+(((.006*(Wpk[3][11][2]*Wpk[4][11][2]))+((.001*(
          Wpk[3][10][1]*Wpk[4][10][1]))+(.006*(Wpk[3][11][0]*Wpk[4][11][0]))))+(
          (Vpk[3][11][2]*Vpk[4][11][2])+((Vpk[3][11][0]*Vpk[4][11][0])+(
          Vpk[3][11][1]*Vpk[4][11][1])))));
        temp[2] = (((5.89*((Vpk[3][12][2]*Vpk[4][12][2])+((Vpk[3][12][0]*
          Vpk[4][12][0])+(Vpk[3][12][1]*Vpk[4][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[4][12][2]))+((.023*(Wpk[3][12][1]*Wpk[4][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[4][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[3][14][2]*Vpk[4][14][2])+((Vpk[3][14][0]*
          Vpk[4][14][0])+(Vpk[3][14][1]*Vpk[4][14][1]))))+((.025*(Wpk[3][14][2]*
          Wpk[4][14][2]))+((.005*(Wpk[3][14][0]*Wpk[4][14][0]))+(.025*(
          Wpk[3][13][1]*Wpk[4][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[3][16][2]*Vpk[4][16][2])+((Vpk[3][16][0]*
          Vpk[4][16][0])+(Vpk[3][16][1]*Vpk[4][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[4][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[4][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[4][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[3][18][2]*Vpk[4][18][2])+((Vpk[3][18][0]*
          Vpk[4][18][0])+(Vpk[3][18][1]*Vpk[4][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[4][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[4][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[4][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[3][20][2]*Vpk[4][20][2])+((Vpk[3][20][0]*
          Vpk[4][20][0])+(Vpk[3][20][1]*Vpk[4][20][1]))))+((.025*(Wpk[3][20][2]*
          Wpk[4][20][2]))+((.005*(Wpk[3][20][0]*Wpk[4][20][0]))+(.025*(
          Wpk[3][19][1]*Wpk[4][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[3][22][2]*Vpk[4][22][2])+((Vpk[3][22][0]*
          Vpk[4][22][0])+(Vpk[3][22][1]*Vpk[4][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[4][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[4][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[4][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[3][24][2]*Vpk[4][24][2])+((Vpk[3][24][0]*
          Vpk[4][24][0])+(Vpk[3][24][1]*Vpk[4][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[4][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[4][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[4][23][1])))))+temp[7]);
        temp[9] = ((4.16*((Vpk[3][28][2]*Vpk[4][28][2])+((Vpk[3][28][0]*
          Vpk[4][28][0])+(Vpk[3][28][1]*Vpk[4][28][1]))))+((.055*(Wpk[3][28][2]*
          Wpk[4][28][2]))+((.007*(Wpk[3][28][1]*Wpk[4][28][1]))+(.056*(
          Wpk[3][27][0]*Wpk[4][27][0])))));
        temp[10] = (temp[9]+(((8.35*((Vpk[3][27][2]*Vpk[4][27][2])+((
          Vpk[3][27][0]*Vpk[4][27][0])+(Vpk[3][27][1]*Vpk[4][27][1]))))+((.15*(
          Wpk[3][27][2]*Wpk[4][27][2]))+((.16*(Wpk[3][27][0]*Wpk[4][27][0]))-(
          .025*(Wpk[4][26][1]*s26)))))+temp[8]));
        temp[11] = (((1.34*((Vpk[3][30][2]*Vpk[4][30][2])+((Vpk[3][30][0]*
          Vpk[4][30][0])+(Vpk[3][30][1]*Vpk[4][30][1]))))+((.0018*(Wpk[3][29][2]
          *Wpk[4][29][2]))+((.007*(Wpk[3][30][1]*Wpk[4][30][1]))+(.0075*(
          Wpk[3][30][0]*Wpk[4][30][0])))))+temp[10]);
        temp[12] = ((4.16*((Vpk[3][34][2]*Vpk[4][34][2])+((Vpk[3][34][0]*
          Vpk[4][34][0])+(Vpk[3][34][1]*Vpk[4][34][1]))))+((.055*(Wpk[3][34][2]*
          Wpk[4][34][2]))+((.007*(Wpk[3][34][1]*Wpk[4][34][1]))+(.056*(
          Wpk[3][33][0]*Wpk[4][33][0])))));
        temp[13] = (temp[12]+(((8.35*((Vpk[3][33][2]*Vpk[4][33][2])+((
          Vpk[3][33][0]*Vpk[4][33][0])+(Vpk[3][33][1]*Vpk[4][33][1]))))+((.15*(
          Wpk[3][33][2]*Wpk[4][33][2]))+((.16*(Wpk[3][33][0]*Wpk[4][33][0]))-(
          .025*(Wpk[4][32][1]*s32)))))+temp[11]));
        mm[3][4] = (((1.34*((Vpk[3][36][2]*Vpk[4][36][2])+((Vpk[3][36][0]*
          Vpk[4][36][0])+(Vpk[3][36][1]*Vpk[4][36][1]))))+((.0018*(Wpk[3][35][2]
          *Wpk[4][35][2]))+((.007*(Wpk[3][36][1]*Wpk[4][36][1]))+(.0075*(
          Wpk[3][36][0]*Wpk[4][36][0])))))+temp[13]);
        temp[0] = ((29.27*((.0213890625*(Wpk[3][8][0]*Wpk[5][8][0]))+((.00123201
          *(Wpk[3][8][0]*Wpk[5][8][0]))+(Vpk[3][8][0]*Vpk[5][8][0]))))+((.73*(
          Wpk[3][8][2]*Wpk[5][8][2]))+((.63*(Wpk[3][8][0]*Wpk[5][8][0]))-(.32*(
          Wpk[5][7][1]*s7)))));
        temp[1] = (temp[0]+(((.006*(Wpk[3][11][2]*Wpk[5][11][2]))+((.001*(
          Wpk[3][10][1]*Wpk[5][10][1]))+(.006*(Wpk[3][11][0]*Wpk[5][11][0]))))+(
          (Vpk[3][11][2]*Vpk[5][11][2])+((Vpk[3][11][0]*Vpk[5][11][0])+(
          Vpk[3][11][1]*Vpk[5][11][1])))));
        temp[2] = (((5.89*((Vpk[3][12][2]*Vpk[5][12][2])+((Vpk[3][12][0]*
          Vpk[5][12][0])+(Vpk[3][12][1]*Vpk[5][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[5][12][2]))+((.023*(Wpk[3][12][1]*Wpk[5][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[5][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[3][14][2]*Vpk[5][14][2])+((Vpk[3][14][0]*
          Vpk[5][14][0])+(Vpk[3][14][1]*Vpk[5][14][1]))))+((.025*(Wpk[3][14][2]*
          Wpk[5][14][2]))+((.005*(Wpk[3][14][0]*Wpk[5][14][0]))+(.025*(
          Wpk[3][13][1]*Wpk[5][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[3][16][2]*Vpk[5][16][2])+((Vpk[3][16][0]*
          Vpk[5][16][0])+(Vpk[3][16][1]*Vpk[5][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[5][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[5][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[5][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[3][18][2]*Vpk[5][18][2])+((Vpk[3][18][0]*
          Vpk[5][18][0])+(Vpk[3][18][1]*Vpk[5][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[5][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[5][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[5][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[3][20][2]*Vpk[5][20][2])+((Vpk[3][20][0]*
          Vpk[5][20][0])+(Vpk[3][20][1]*Vpk[5][20][1]))))+((.025*(Wpk[3][20][2]*
          Wpk[5][20][2]))+((.005*(Wpk[3][20][0]*Wpk[5][20][0]))+(.025*(
          Wpk[3][19][1]*Wpk[5][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[3][22][2]*Vpk[5][22][2])+((Vpk[3][22][0]*
          Vpk[5][22][0])+(Vpk[3][22][1]*Vpk[5][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[5][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[5][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[5][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[3][24][2]*Vpk[5][24][2])+((Vpk[3][24][0]*
          Vpk[5][24][0])+(Vpk[3][24][1]*Vpk[5][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[5][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[5][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[5][23][1])))))+temp[7]);
        temp[9] = ((4.16*((Vpk[3][28][2]*Vpk[5][28][2])+((Vpk[3][28][0]*
          Vpk[5][28][0])+(Vpk[3][28][1]*Vpk[5][28][1]))))+((.055*(Wpk[3][28][2]*
          Wpk[5][28][2]))+((.007*(Wpk[3][28][1]*Wpk[5][28][1]))+(.056*(
          Wpk[3][27][0]*Wpk[5][27][0])))));
        temp[10] = (temp[9]+(((8.35*((Vpk[3][27][2]*Vpk[5][27][2])+((
          Vpk[3][27][0]*Vpk[5][27][0])+(Vpk[3][27][1]*Vpk[5][27][1]))))+((.15*(
          Wpk[3][27][2]*Wpk[5][27][2]))+((.16*(Wpk[3][27][0]*Wpk[5][27][0]))-(
          .025*(Wpk[5][26][1]*s26)))))+temp[8]));
        temp[11] = (((1.34*((Vpk[3][30][2]*Vpk[5][30][2])+((Vpk[3][30][0]*
          Vpk[5][30][0])+(Vpk[3][30][1]*Vpk[5][30][1]))))+((.0018*(Wpk[3][29][2]
          *Wpk[5][29][2]))+((.007*(Wpk[3][30][1]*Wpk[5][30][1]))+(.0075*(
          Wpk[3][30][0]*Wpk[5][30][0])))))+temp[10]);
        temp[12] = ((4.16*((Vpk[3][34][2]*Vpk[5][34][2])+((Vpk[3][34][0]*
          Vpk[5][34][0])+(Vpk[3][34][1]*Vpk[5][34][1]))))+((.055*(Wpk[3][34][2]*
          Wpk[5][34][2]))+((.007*(Wpk[3][34][1]*Wpk[5][34][1]))+(.056*(
          Wpk[3][33][0]*Wpk[5][33][0])))));
        temp[13] = (temp[12]+(((8.35*((Vpk[3][33][2]*Vpk[5][33][2])+((
          Vpk[3][33][0]*Vpk[5][33][0])+(Vpk[3][33][1]*Vpk[5][33][1]))))+((.15*(
          Wpk[3][33][2]*Wpk[5][33][2]))+((.16*(Wpk[3][33][0]*Wpk[5][33][0]))-(
          .025*(Wpk[5][32][1]*s32)))))+temp[11]));
        mm[3][5] = (((1.34*((Vpk[3][36][2]*Vpk[5][36][2])+((Vpk[3][36][0]*
          Vpk[5][36][0])+(Vpk[3][36][1]*Vpk[5][36][1]))))+((.0018*(Wpk[3][35][2]
          *Wpk[5][35][2]))+((.007*(Wpk[3][36][1]*Wpk[5][36][1]))+(.0075*(
          Wpk[3][36][0]*Wpk[5][36][0])))))+temp[13]);
        temp[0] = (((.006*(Wpk[3][11][2]*Wpk[6][11][2]))+((.001*(Wpk[3][10][1]*
          Wpk[6][10][1]))+(.006*(Wpk[3][11][0]*Wpk[6][11][0]))))+((Vpk[3][11][2]
          *Vpk[6][11][2])+((Vpk[3][11][0]*Vpk[6][11][0])+(Vpk[3][11][1]*
          Vpk[6][11][1]))));
        temp[1] = (((29.27*((.0213890625*(Wpk[3][8][0]*Wpk[6][8][0]))+((
          .00123201*(Wpk[3][8][0]*Wpk[6][8][0]))+(Vpk[3][8][0]*Vpk[6][8][0]))))+
          ((.73*(Wpk[3][8][2]*Wpk[6][8][2]))+((.32*(s7*s7))+(.63*(Wpk[3][8][0]*
          Wpk[6][8][0])))))+temp[0]);
        temp[2] = (((5.89*((Vpk[3][12][2]*Vpk[6][12][2])+((Vpk[3][12][0]*
          Vpk[6][12][0])+(Vpk[3][12][1]*Vpk[6][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[6][12][2]))+((.023*(Wpk[3][12][1]*Wpk[6][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[6][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[3][14][2]*Vpk[6][14][2])+((Vpk[3][14][0]*
          Vpk[6][14][0])+(Vpk[3][14][1]*Vpk[6][14][1]))))+((.025*(Wpk[3][14][2]*
          Wpk[6][14][2]))+((.005*(Wpk[3][14][0]*Wpk[6][14][0]))+(.025*(
          Wpk[3][13][1]*Wpk[6][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[3][16][2]*Vpk[6][16][2])+((Vpk[3][16][0]*
          Vpk[6][16][0])+(Vpk[3][16][1]*Vpk[6][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[6][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[6][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[6][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[3][18][2]*Vpk[6][18][2])+((Vpk[3][18][0]*
          Vpk[6][18][0])+(Vpk[3][18][1]*Vpk[6][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[6][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[6][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[6][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[3][20][2]*Vpk[6][20][2])+((Vpk[3][20][0]*
          Vpk[6][20][0])+(Vpk[3][20][1]*Vpk[6][20][1]))))+((.025*(Wpk[3][20][2]*
          Wpk[6][20][2]))+((.005*(Wpk[3][20][0]*Wpk[6][20][0]))+(.025*(
          Wpk[3][19][1]*Wpk[6][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[3][22][2]*Vpk[6][22][2])+((Vpk[3][22][0]*
          Vpk[6][22][0])+(Vpk[3][22][1]*Vpk[6][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[6][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[6][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[6][22][1])))))+temp[6]);
        mm[3][6] = (((.55*((Vpk[3][24][2]*Vpk[6][24][2])+((Vpk[3][24][0]*
          Vpk[6][24][0])+(Vpk[3][24][1]*Vpk[6][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[6][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[6][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[6][23][1])))))+temp[7]);
        temp[0] = ((((.006*(Wpk[3][11][2]*Wpk[7][11][2]))+((.001*(Wpk[3][10][1]*
          Wpk[7][10][1]))+(.006*(Wpk[3][11][0]*Wpk[7][11][0]))))+((Vpk[3][11][2]
          *Vpk[7][11][2])+((Vpk[3][11][0]*Vpk[7][11][0])+(Vpk[3][11][1]*
          Vpk[7][11][1]))))+(((.73*(Wpk[3][8][2]*c8))-(.63*(Wpk[3][8][0]*s8)))-(
          29.27*((.0213890625*(Wpk[3][8][0]*s8))+((.00123201*(Wpk[3][8][0]*s8))+
          (.14625*(Vpk[3][8][0]*c8)))))));
        temp[1] = (((5.89*((Vpk[3][12][2]*Vpk[7][12][2])+((Vpk[3][12][0]*
          Vpk[7][12][0])+(Vpk[3][12][1]*Vpk[7][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[7][12][2]))+((.023*(Wpk[3][12][1]*Wpk[7][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[7][11][0])))))+temp[0]);
        temp[2] = (((2.79*((Vpk[3][14][2]*Vpk[7][14][2])+((Vpk[3][14][0]*
          Vpk[7][14][0])+(Vpk[3][14][1]*Vpk[7][14][1]))))+((.025*(Wpk[3][14][2]*
          Wpk[7][14][2]))+((.005*(Wpk[3][14][0]*Wpk[7][14][0]))+(.025*(
          Wpk[3][13][1]*Wpk[7][13][1])))))+temp[1]);
        temp[3] = (((1.21*((Vpk[3][16][2]*Vpk[7][16][2])+((Vpk[3][16][0]*
          Vpk[7][16][0])+(Vpk[3][16][1]*Vpk[7][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[7][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[7][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[7][16][1])))))+temp[2]);
        temp[4] = (((.55*((Vpk[3][18][2]*Vpk[7][18][2])+((Vpk[3][18][0]*
          Vpk[7][18][0])+(Vpk[3][18][1]*Vpk[7][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[7][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[7][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[7][17][1])))))+temp[3]);
        temp[5] = (((2.79*((Vpk[3][20][2]*Vpk[7][20][2])+((Vpk[3][20][0]*
          Vpk[7][20][0])+(Vpk[3][20][1]*Vpk[7][20][1]))))+((.025*(Wpk[3][20][2]*
          Wpk[7][20][2]))+((.005*(Wpk[3][20][0]*Wpk[7][20][0]))+(.025*(
          Wpk[3][19][1]*Wpk[7][19][1])))))+temp[4]);
        temp[6] = (((1.21*((Vpk[3][22][2]*Vpk[7][22][2])+((Vpk[3][22][0]*
          Vpk[7][22][0])+(Vpk[3][22][1]*Vpk[7][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[7][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[7][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[7][22][1])))))+temp[5]);
        mm[3][7] = (((.55*((Vpk[3][24][2]*Vpk[7][24][2])+((Vpk[3][24][0]*
          Vpk[7][24][0])+(Vpk[3][24][1]*Vpk[7][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[7][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[7][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[7][23][1])))))+temp[6]);
        temp[0] = ((((.006*(Wpk[3][11][2]*Wpk[8][11][2]))+((.001*(Wpk[3][10][1]*
          Wpk[8][10][1]))+(.006*(Wpk[3][11][0]*Wpk[8][11][0]))))+((Vpk[3][11][2]
          *Vpk[8][11][2])+((Vpk[3][11][0]*Vpk[8][11][0])+(Vpk[3][11][1]*
          Vpk[8][11][1]))))-((.32*s7)+(1.027377*Vpk[3][8][0])));
        temp[1] = (((5.89*((Vpk[3][12][2]*Vpk[8][12][2])+((Vpk[3][12][0]*
          Vpk[8][12][0])+(Vpk[3][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[3][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[8][11][0])))))+temp[0]);
        temp[2] = ((1.21*((Vpk[3][16][2]*Vpk[8][16][2])+((Vpk[3][16][0]*
          Vpk[8][16][0])+(Vpk[3][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[3][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[3][16][1]*Wpk[8][16][1])))));
        temp[3] = (temp[2]+(((2.79*((Vpk[3][14][2]*Vpk[8][14][2])+((
          Vpk[3][14][0]*Vpk[8][14][0])+(Vpk[3][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[3][14][2]*Wpk[8][14][2]))+((.005*(Wpk[3][14][0]*Wpk[8][14][0]))+(
          .025*(Wpk[3][13][1]*c13)))))+temp[1]));
        temp[4] = (((.55*((Vpk[3][18][2]*Vpk[8][18][2])+((Vpk[3][18][0]*
          Vpk[8][18][0])+(Vpk[3][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[3][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[3][17][1]*Wpk[8][17][1])))))+temp[3]);
        temp[5] = ((1.21*((Vpk[3][22][2]*Vpk[8][22][2])+((Vpk[3][22][0]*
          Vpk[8][22][0])+(Vpk[3][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[3][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[3][22][1]*Wpk[8][22][1])))));
        temp[6] = (temp[5]+(((2.79*((Vpk[3][20][2]*Vpk[8][20][2])+((
          Vpk[3][20][0]*Vpk[8][20][0])+(Vpk[3][20][1]*Vpk[8][20][1]))))+((.025*(
          Wpk[3][20][2]*Wpk[8][20][2]))+((.005*(Wpk[3][20][0]*Wpk[8][20][0]))+(
          .025*(Wpk[3][19][1]*c19)))))+temp[4]));
        mm[3][8] = (((.55*((Vpk[3][24][2]*Vpk[8][24][2])+((Vpk[3][24][0]*
          Vpk[8][24][0])+(Vpk[3][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[3][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[3][23][1]*Wpk[8][23][1])))))+temp[6]);
        temp[0] = ((5.89*((Vpk[3][12][2]*Vpk[9][12][2])+((Vpk[3][12][0]*
          Vpk[9][12][0])+(Vpk[3][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[3][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[3][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[3][11][0]*Wpk[9][11][0])))));
        mm[3][9] = (temp[0]+(((.006*(Wpk[3][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[3][11][0]*Wpk[9][11][0]))-(.001*(Wpk[3][10][1]*s10))))+((.0442*(
          Vpk[3][11][2]*Wpk[9][11][0]))+((Vpk[3][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[3][11][1]*Wpk[9][11][0]))))));
        mm[3][10] = (((.006*((Wpk[3][11][2]*c11)-(Wpk[3][11][0]*s11)))+(((.0065*
          (Vpk[3][11][1]*s11))-(.0442*(Vpk[3][11][0]*c11)))-(.0442*(
          Vpk[3][11][2]*s11))))+((5.89*((Vpk[3][12][2]*Vpk[10][12][2])+((
          Vpk[3][12][0]*Vpk[10][12][0])+(Vpk[3][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[3][12][2]*Wpk[10][12][2]))+((.023*(Wpk[3][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[3][11][0]*s11))))));
        mm[3][11] = (((.001*Wpk[3][10][1])+(.0065*Vpk[3][11][0]))+((5.89*(
          Vpk[3][12][0]*Vpk[11][12][0]))+((.023*(Wpk[3][12][1]*c12))-(.03*(
          Wpk[3][12][2]*s12)))));
        mm[3][12] = ((.033*Wpk[3][11][0])+(5.89*((.078*Vpk[3][12][2])-(.0312*
          Vpk[3][12][1]))));
        temp[0] = (((1.21*((Vpk[3][16][2]*Vpk[13][16][2])+((Vpk[3][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[3][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[3][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[3][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[3][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[3][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[3][14][2]*c14))-(.005*(Wpk[3][14][0]*s14)
          ))));
        mm[3][13] = (((.55*((Vpk[3][18][2]*Vpk[13][18][2])+((Vpk[3][18][0]*
          Vpk[13][18][0])+(Vpk[3][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[3][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[3][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[3][13][1])+(2.79*((.0013*Vpk[3][14][0])-(.1326*
          Vpk[3][14][2]))))+((1.21*((Vpk[3][16][2]*Vpk[14][16][2])+((
          Vpk[3][16][0]*Vpk[14][16][0])+(Vpk[3][16][1]*Vpk[14][16][1]))))+((
          .0054*(Wpk[3][16][1]*c16))-(.005*(Wpk[3][16][2]*s16)))));
        mm[3][14] = (((.55*((Vpk[3][18][2]*Vpk[14][18][2])+((Vpk[3][18][0]*
          Vpk[14][18][0])+(Vpk[3][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[3][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[3][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[3][15] = (((.55*((Vpk[3][18][2]*Vpk[15][18][2])+((Vpk[3][18][0]*
          Vpk[15][18][0])+(Vpk[3][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[3][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[3][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[3][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[3][16][0]*s16))-(.1378*(Vpk[3][16][1]*s16)))-(.1378*(Vpk[3][16][2]
          *c16))))+((.0054*(Wpk[3][16][1]*c16))-(.005*(Wpk[3][16][2]*s16)))));
        mm[3][16] = (((.0012*Wpk[3][15][0])+(.004719*Vpk[3][16][2]))+((.55*((
          Vpk[3][18][2]*Vpk[16][18][2])+((.065*(Vpk[3][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[3][18][0]*s18)))))+((.0016*(Wpk[3][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[3][18][0]*Wpk[16][18][0]))-(.002*(Wpk[3][17][1]*s17))))))
          ;
        mm[3][17] = ((.03575*(Vpk[3][18][1]*c18))+((.0016*(Wpk[3][18][2]*c18))-(
          .0005*(Wpk[3][18][0]*s18))));
        mm[3][18] = ((.002*Wpk[3][17][1])-(.03575*Vpk[3][18][2]));
        temp[0] = (((1.21*((Vpk[3][22][2]*Vpk[19][22][2])+((Vpk[3][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[3][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[3][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[3][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[3][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[3][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[3][20][2]*c20))-(.005*(Wpk[3][20][0]*s20)
          ))));
        mm[3][19] = (((.55*((Vpk[3][24][2]*Vpk[19][24][2])+((Vpk[3][24][0]*
          Vpk[19][24][0])+(Vpk[3][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[3][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[3][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[3][19][1])+(2.79*((.0013*Vpk[3][20][0])+(.1326*
          Vpk[3][20][2]))))+((1.21*((Vpk[3][22][2]*Vpk[20][22][2])+((
          Vpk[3][22][0]*Vpk[20][22][0])+(Vpk[3][22][1]*Vpk[20][22][1]))))+((
          .0054*(Wpk[3][22][1]*c22))-(.005*(Wpk[3][22][2]*s22)))));
        mm[3][20] = (((.55*((Vpk[3][24][2]*Vpk[20][24][2])+((Vpk[3][24][0]*
          Vpk[20][24][0])+(Vpk[3][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[3][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[3][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[3][21] = (((.55*((Vpk[3][24][2]*Vpk[21][24][2])+((Vpk[3][24][0]*
          Vpk[21][24][0])+(Vpk[3][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[3][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[3][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[3][22][2]*c22))+((.0039*(Vpk[3][22][0]*s22))+(.1378*(Vpk[3][22][1]
          *s22)))))+((.0054*(Wpk[3][22][1]*c22))-(.005*(Wpk[3][22][2]*s22)))));
        mm[3][22] = (((.0012*Wpk[3][21][0])+(.004719*Vpk[3][22][2]))+((.55*((
          Vpk[3][24][2]*Vpk[22][24][2])-((.0078*(Vpk[3][24][0]*s24))+(.065*(
          Vpk[3][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[3][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[3][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[3][23][1]*s23))))));
        mm[3][23] = (((.0016*(Wpk[3][24][2]*c24))-(.0005*(Wpk[3][24][0]*s24)))-(
          .03575*(Vpk[3][24][1]*c24)));
        mm[3][24] = ((.002*Wpk[3][23][1])+(.03575*Vpk[3][24][2]));
        temp[0] = ((4.16*((Vpk[3][28][2]*Vpk[25][28][2])+((Vpk[3][28][0]*
          Vpk[25][28][0])+(Vpk[3][28][1]*Vpk[25][28][1]))))+((.055*(
          Wpk[3][28][2]*Wpk[25][28][2]))+((.007*(Wpk[3][28][1]*Wpk[25][28][1]))+
          (.056*(Wpk[3][27][0]*Wpk[25][27][0])))));
        temp[1] = ((1.34*((Vpk[3][30][2]*Vpk[25][30][2])+((Vpk[3][30][0]*
          Vpk[25][30][0])+(Vpk[3][30][1]*Vpk[25][30][1]))))+((.0018*(
          Wpk[3][29][2]*Wpk[25][29][2]))+((.007*(Wpk[3][30][1]*Wpk[25][30][1]))+
          (.0075*(Wpk[3][30][0]*Wpk[25][30][0])))));
        mm[3][25] = (temp[1]+(temp[0]+((8.35*((Vpk[3][27][2]*Vpk[25][27][2])+((
          Vpk[3][27][0]*Vpk[25][27][0])+(Vpk[3][27][1]*Vpk[25][27][1]))))+((.15*
          (Wpk[3][27][2]*Wpk[25][27][2]))+((.025*(s26*s26))+(.16*(Wpk[3][27][0]*
          Wpk[25][27][0])))))));
        temp[0] = (((4.16*((Vpk[3][28][2]*Vpk[26][28][2])+((Vpk[3][28][0]*
          Vpk[26][28][0])+(Vpk[3][28][1]*Vpk[26][28][1]))))+((.055*(
          Wpk[3][28][2]*Wpk[26][28][2]))+((.007*(Wpk[3][28][1]*Wpk[26][28][1]))-
          (.056*(Wpk[3][27][0]*s27)))))+((8.35*((.2379*(Vpk[3][27][2]*s27))+((
          .2379*(Vpk[3][27][0]*c27))+(Vpk[3][27][1]*Vpk[26][27][1]))))+((.15*(
          Wpk[3][27][2]*c27))-(.16*(Wpk[3][27][0]*s27)))));
        mm[3][26] = (((1.34*((Vpk[3][30][2]*Vpk[26][30][2])+((Vpk[3][30][0]*
          Vpk[26][30][0])+(Vpk[3][30][1]*Vpk[26][30][1]))))+((.0018*(
          Wpk[3][29][2]*Wpk[26][29][2]))+((.007*(Wpk[3][30][1]*Wpk[26][30][1]))+
          (.0075*(Wpk[3][30][0]*Wpk[26][30][0])))))+temp[0]);
        temp[0] = ((1.34*((Vpk[3][30][2]*Vpk[27][30][2])+((Vpk[3][30][0]*
          Vpk[27][30][0])+(Vpk[3][30][1]*Vpk[27][30][1]))))+((.0018*(
          Wpk[3][29][2]*Wpk[27][29][2]))+((.007*(Wpk[3][30][1]*Wpk[27][30][1]))+
          (.0075*(Wpk[3][30][0]*Wpk[27][30][0])))));
        mm[3][27] = (temp[0]+(((4.16*((.0416*(Vpk[3][28][2]*c28))+((.0416*(
          Vpk[3][28][1]*s28))+(Vpk[3][28][0]*Vpk[27][28][0]))))+((.007*(
          Wpk[3][28][1]*c28))-(.055*(Wpk[3][28][2]*s28))))+((8.35*((.0143*
          Vpk[3][27][0])+(.0169*Vpk[3][27][2])))-(.025*s26))));
        mm[3][28] = (((.056*Wpk[3][27][0])+(4.16*((.0039*Vpk[3][28][1])-(.2158*
          Vpk[3][28][2]))))+((1.34*((Vpk[3][30][2]*Vpk[28][30][2])+((
          Vpk[3][30][0]*Vpk[28][30][0])+(Vpk[3][30][1]*Vpk[28][30][1]))))+((
          .0075*(Wpk[3][30][0]*c30))-(.007*(Wpk[3][30][1]*s30)))));
        mm[3][29] = (((.0075*(Wpk[3][30][0]*c30))-(.007*(Wpk[3][30][1]*s30)))-(
          1.34*((.039*((Vpk[3][30][0]*s30)+(Vpk[3][30][1]*c30)))+(.0442*(
          Vpk[3][30][2]*c30)))));
        mm[3][30] = ((.0018*Wpk[3][29][2])+(.059228*Vpk[3][30][0]));
        temp[0] = ((4.16*((Vpk[3][34][2]*Vpk[31][34][2])+((Vpk[3][34][0]*
          Vpk[31][34][0])+(Vpk[3][34][1]*Vpk[31][34][1]))))+((.055*(
          Wpk[3][34][2]*Wpk[31][34][2]))+((.007*(Wpk[3][34][1]*Wpk[31][34][1]))+
          (.056*(Wpk[3][33][0]*Wpk[31][33][0])))));
        temp[1] = ((1.34*((Vpk[3][36][2]*Vpk[31][36][2])+((Vpk[3][36][0]*
          Vpk[31][36][0])+(Vpk[3][36][1]*Vpk[31][36][1]))))+((.0018*(
          Wpk[3][35][2]*Wpk[31][35][2]))+((.007*(Wpk[3][36][1]*Wpk[31][36][1]))+
          (.0075*(Wpk[3][36][0]*Wpk[31][36][0])))));
        mm[3][31] = (temp[1]+(temp[0]+((8.35*((Vpk[3][33][2]*Vpk[31][33][2])+((
          Vpk[3][33][0]*Vpk[31][33][0])+(Vpk[3][33][1]*Vpk[31][33][1]))))+((.15*
          (Wpk[3][33][2]*Wpk[31][33][2]))+((.025*(s32*s32))+(.16*(Wpk[3][33][0]*
          Wpk[31][33][0])))))));
        temp[0] = (((4.16*((Vpk[3][34][2]*Vpk[32][34][2])+((Vpk[3][34][0]*
          Vpk[32][34][0])+(Vpk[3][34][1]*Vpk[32][34][1]))))+((.055*(
          Wpk[3][34][2]*Wpk[32][34][2]))+((.007*(Wpk[3][34][1]*Wpk[32][34][1]))-
          (.056*(Wpk[3][33][0]*s33)))))+((8.35*((.2379*(Vpk[3][33][2]*s33))+((
          .2379*(Vpk[3][33][0]*c33))+(Vpk[3][33][1]*Vpk[32][33][1]))))+((.15*(
          Wpk[3][33][2]*c33))-(.16*(Wpk[3][33][0]*s33)))));
        mm[3][32] = (((1.34*((Vpk[3][36][2]*Vpk[32][36][2])+((Vpk[3][36][0]*
          Vpk[32][36][0])+(Vpk[3][36][1]*Vpk[32][36][1]))))+((.0018*(
          Wpk[3][35][2]*Wpk[32][35][2]))+((.007*(Wpk[3][36][1]*Wpk[32][36][1]))+
          (.0075*(Wpk[3][36][0]*Wpk[32][36][0])))))+temp[0]);
        temp[0] = ((1.34*((Vpk[3][36][2]*Vpk[33][36][2])+((Vpk[3][36][0]*
          Vpk[33][36][0])+(Vpk[3][36][1]*Vpk[33][36][1]))))+((.0018*(
          Wpk[3][35][2]*Wpk[33][35][2]))+((.007*(Wpk[3][36][1]*Wpk[33][36][1]))+
          (.0075*(Wpk[3][36][0]*Wpk[33][36][0])))));
        mm[3][33] = (temp[0]+(((4.16*(((Vpk[3][34][0]*Vpk[33][34][0])-(.0416*(
          Vpk[3][34][1]*s34)))-(.0416*(Vpk[3][34][2]*c34))))+((.007*(
          Wpk[3][34][1]*c34))-(.055*(Wpk[3][34][2]*s34))))+((8.35*((.0143*
          Vpk[3][33][0])-(.0169*Vpk[3][33][2])))-(.025*s32))));
        mm[3][34] = (((.056*Wpk[3][33][0])+(4.16*((.0039*Vpk[3][34][1])-(.2158*
          Vpk[3][34][2]))))+((1.34*((Vpk[3][36][2]*Vpk[34][36][2])+((
          Vpk[3][36][0]*Vpk[34][36][0])+(Vpk[3][36][1]*Vpk[34][36][1]))))+((
          .0075*(Wpk[3][36][0]*c36))-(.007*(Wpk[3][36][1]*s36)))));
        mm[3][35] = (((.0075*(Wpk[3][36][0]*c36))-(.007*(Wpk[3][36][1]*s36)))-(
          1.34*((.039*((Vpk[3][36][0]*s36)+(Vpk[3][36][1]*c36)))+(.0442*(
          Vpk[3][36][2]*c36)))));
        mm[3][36] = ((.0018*Wpk[3][35][2])+(.059228*Vpk[3][36][0]));
        temp[0] = ((29.27*((.0213890625*(Wpk[4][8][0]*Wpk[4][8][0]))+((.00123201
          *(Wpk[4][8][0]*Wpk[4][8][0]))+(Vpk[4][8][0]*Vpk[4][8][0]))))+((.73*(
          Wpk[4][8][2]*Wpk[4][8][2]))+((.32*(Wpk[4][7][1]*Wpk[4][7][1]))+(.63*(
          Wpk[4][8][0]*Wpk[4][8][0])))));
        temp[1] = (temp[0]+(((.006*(Wpk[4][11][2]*Wpk[4][11][2]))+((.001*(
          Wpk[4][10][1]*Wpk[4][10][1]))+(.006*(Wpk[4][11][0]*Wpk[4][11][0]))))+(
          (Vpk[4][11][2]*Vpk[4][11][2])+((Vpk[4][11][0]*Vpk[4][11][0])+(
          Vpk[4][11][1]*Vpk[4][11][1])))));
        temp[2] = (((5.89*((Vpk[4][12][2]*Vpk[4][12][2])+((Vpk[4][12][0]*
          Vpk[4][12][0])+(Vpk[4][12][1]*Vpk[4][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[4][12][2]))+((.023*(Wpk[4][12][1]*Wpk[4][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[4][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[4][14][2]*Vpk[4][14][2])+((Vpk[4][14][0]*
          Vpk[4][14][0])+(Vpk[4][14][1]*Vpk[4][14][1]))))+((.025*(Wpk[4][14][2]*
          Wpk[4][14][2]))+((.005*(Wpk[4][14][0]*Wpk[4][14][0]))+(.025*(
          Wpk[4][13][1]*Wpk[4][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[4][16][2]*Vpk[4][16][2])+((Vpk[4][16][0]*
          Vpk[4][16][0])+(Vpk[4][16][1]*Vpk[4][16][1]))))+((.005*(Wpk[4][16][2]*
          Wpk[4][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[4][15][0]))+(.0054*(
          Wpk[4][16][1]*Wpk[4][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[4][18][2]*Vpk[4][18][2])+((Vpk[4][18][0]*
          Vpk[4][18][0])+(Vpk[4][18][1]*Vpk[4][18][1]))))+((.0016*(Wpk[4][18][2]
          *Wpk[4][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[4][18][0]))+(.002*(
          Wpk[4][17][1]*Wpk[4][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[4][20][2]*Vpk[4][20][2])+((Vpk[4][20][0]*
          Vpk[4][20][0])+(Vpk[4][20][1]*Vpk[4][20][1]))))+((.025*(Wpk[4][20][2]*
          Wpk[4][20][2]))+((.005*(Wpk[4][20][0]*Wpk[4][20][0]))+(.025*(
          Wpk[4][19][1]*Wpk[4][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[4][22][2]*Vpk[4][22][2])+((Vpk[4][22][0]*
          Vpk[4][22][0])+(Vpk[4][22][1]*Vpk[4][22][1]))))+((.005*(Wpk[4][22][2]*
          Wpk[4][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[4][21][0]))+(.0054*(
          Wpk[4][22][1]*Wpk[4][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[4][24][2]*Vpk[4][24][2])+((Vpk[4][24][0]*
          Vpk[4][24][0])+(Vpk[4][24][1]*Vpk[4][24][1]))))+((.0016*(Wpk[4][24][2]
          *Wpk[4][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[4][24][0]))+(.002*(
          Wpk[4][23][1]*Wpk[4][23][1])))))+temp[7]);
        temp[9] = (((8.35*((Vpk[4][27][2]*Vpk[4][27][2])+((Vpk[4][27][0]*
          Vpk[4][27][0])+(Vpk[4][27][1]*Vpk[4][27][1]))))+((.15*(Wpk[4][27][2]*
          Wpk[4][27][2]))+((.025*(Wpk[4][26][1]*Wpk[4][26][1]))+(.16*(
          Wpk[4][27][0]*Wpk[4][27][0])))))+temp[8]);
        temp[10] = (((4.16*((Vpk[4][28][2]*Vpk[4][28][2])+((Vpk[4][28][0]*
          Vpk[4][28][0])+(Vpk[4][28][1]*Vpk[4][28][1]))))+((.055*(Wpk[4][28][2]*
          Wpk[4][28][2]))+((.007*(Wpk[4][28][1]*Wpk[4][28][1]))+(.056*(
          Wpk[4][27][0]*Wpk[4][27][0])))))+temp[9]);
        temp[11] = (((1.34*((Vpk[4][30][2]*Vpk[4][30][2])+((Vpk[4][30][0]*
          Vpk[4][30][0])+(Vpk[4][30][1]*Vpk[4][30][1]))))+((.0018*(Wpk[4][29][2]
          *Wpk[4][29][2]))+((.007*(Wpk[4][30][1]*Wpk[4][30][1]))+(.0075*(
          Wpk[4][30][0]*Wpk[4][30][0])))))+temp[10]);
        temp[12] = (((8.35*((Vpk[4][33][2]*Vpk[4][33][2])+((Vpk[4][33][0]*
          Vpk[4][33][0])+(Vpk[4][33][1]*Vpk[4][33][1]))))+((.15*(Wpk[4][33][2]*
          Wpk[4][33][2]))+((.025*(Wpk[4][32][1]*Wpk[4][32][1]))+(.16*(
          Wpk[4][33][0]*Wpk[4][33][0])))))+temp[11]);
        temp[13] = (((4.16*((Vpk[4][34][2]*Vpk[4][34][2])+((Vpk[4][34][0]*
          Vpk[4][34][0])+(Vpk[4][34][1]*Vpk[4][34][1]))))+((.055*(Wpk[4][34][2]*
          Wpk[4][34][2]))+((.007*(Wpk[4][34][1]*Wpk[4][34][1]))+(.056*(
          Wpk[4][33][0]*Wpk[4][33][0])))))+temp[12]);
        mm[4][4] = (.201525+(((1.34*((Vpk[4][36][2]*Vpk[4][36][2])+((
          Vpk[4][36][0]*Vpk[4][36][0])+(Vpk[4][36][1]*Vpk[4][36][1]))))+((.0018*
          (Wpk[4][35][2]*Wpk[4][35][2]))+((.007*(Wpk[4][36][1]*Wpk[4][36][1]))+(
          .0075*(Wpk[4][36][0]*Wpk[4][36][0])))))+temp[13]));
        temp[0] = (((29.27*((.0213890625*(Wpk[4][8][0]*Wpk[5][8][0]))+((
          .00123201*(Wpk[4][8][0]*Wpk[5][8][0]))+(Vpk[4][8][0]*Vpk[5][8][0]))))+
          ((.73*(Wpk[4][8][2]*Wpk[5][8][2]))+((.32*(Wpk[4][7][1]*Wpk[5][7][1]))+
          (.63*(Wpk[4][8][0]*Wpk[5][8][0])))))-.1001583);
        temp[1] = ((((.006*(Wpk[4][11][2]*Wpk[5][11][2]))+((.001*(Wpk[4][10][1]*
          Wpk[5][10][1]))+(.006*(Wpk[4][11][0]*Wpk[5][11][0]))))+((Vpk[4][11][2]
          *Vpk[5][11][2])+((Vpk[4][11][0]*Vpk[5][11][0])+(Vpk[4][11][1]*
          Vpk[5][11][1]))))+temp[0]);
        temp[2] = (((5.89*((Vpk[4][12][2]*Vpk[5][12][2])+((Vpk[4][12][0]*
          Vpk[5][12][0])+(Vpk[4][12][1]*Vpk[5][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[5][12][2]))+((.023*(Wpk[4][12][1]*Wpk[5][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[5][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[4][14][2]*Vpk[5][14][2])+((Vpk[4][14][0]*
          Vpk[5][14][0])+(Vpk[4][14][1]*Vpk[5][14][1]))))+((.025*(Wpk[4][14][2]*
          Wpk[5][14][2]))+((.005*(Wpk[4][14][0]*Wpk[5][14][0]))+(.025*(
          Wpk[4][13][1]*Wpk[5][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[4][16][2]*Vpk[5][16][2])+((Vpk[4][16][0]*
          Vpk[5][16][0])+(Vpk[4][16][1]*Vpk[5][16][1]))))+((.005*(Wpk[4][16][2]*
          Wpk[5][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[5][15][0]))+(.0054*(
          Wpk[4][16][1]*Wpk[5][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[4][18][2]*Vpk[5][18][2])+((Vpk[4][18][0]*
          Vpk[5][18][0])+(Vpk[4][18][1]*Vpk[5][18][1]))))+((.0016*(Wpk[4][18][2]
          *Wpk[5][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[5][18][0]))+(.002*(
          Wpk[4][17][1]*Wpk[5][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[4][20][2]*Vpk[5][20][2])+((Vpk[4][20][0]*
          Vpk[5][20][0])+(Vpk[4][20][1]*Vpk[5][20][1]))))+((.025*(Wpk[4][20][2]*
          Wpk[5][20][2]))+((.005*(Wpk[4][20][0]*Wpk[5][20][0]))+(.025*(
          Wpk[4][19][1]*Wpk[5][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[4][22][2]*Vpk[5][22][2])+((Vpk[4][22][0]*
          Vpk[5][22][0])+(Vpk[4][22][1]*Vpk[5][22][1]))))+((.005*(Wpk[4][22][2]*
          Wpk[5][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[5][21][0]))+(.0054*(
          Wpk[4][22][1]*Wpk[5][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[4][24][2]*Vpk[5][24][2])+((Vpk[4][24][0]*
          Vpk[5][24][0])+(Vpk[4][24][1]*Vpk[5][24][1]))))+((.0016*(Wpk[4][24][2]
          *Wpk[5][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[5][24][0]))+(.002*(
          Wpk[4][23][1]*Wpk[5][23][1])))))+temp[7]);
        temp[9] = (((8.35*((Vpk[4][27][2]*Vpk[5][27][2])+((Vpk[4][27][0]*
          Vpk[5][27][0])+(Vpk[4][27][1]*Vpk[5][27][1]))))+((.15*(Wpk[4][27][2]*
          Wpk[5][27][2]))+((.025*(Wpk[4][26][1]*Wpk[5][26][1]))+(.16*(
          Wpk[4][27][0]*Wpk[5][27][0])))))+temp[8]);
        temp[10] = (((4.16*((Vpk[4][28][2]*Vpk[5][28][2])+((Vpk[4][28][0]*
          Vpk[5][28][0])+(Vpk[4][28][1]*Vpk[5][28][1]))))+((.055*(Wpk[4][28][2]*
          Wpk[5][28][2]))+((.007*(Wpk[4][28][1]*Wpk[5][28][1]))+(.056*(
          Wpk[4][27][0]*Wpk[5][27][0])))))+temp[9]);
        temp[11] = (((1.34*((Vpk[4][30][2]*Vpk[5][30][2])+((Vpk[4][30][0]*
          Vpk[5][30][0])+(Vpk[4][30][1]*Vpk[5][30][1]))))+((.0018*(Wpk[4][29][2]
          *Wpk[5][29][2]))+((.007*(Wpk[4][30][1]*Wpk[5][30][1]))+(.0075*(
          Wpk[4][30][0]*Wpk[5][30][0])))))+temp[10]);
        temp[12] = (((8.35*((Vpk[4][33][2]*Vpk[5][33][2])+((Vpk[4][33][0]*
          Vpk[5][33][0])+(Vpk[4][33][1]*Vpk[5][33][1]))))+((.15*(Wpk[4][33][2]*
          Wpk[5][33][2]))+((.025*(Wpk[4][32][1]*Wpk[5][32][1]))+(.16*(
          Wpk[4][33][0]*Wpk[5][33][0])))))+temp[11]);
        temp[13] = (((4.16*((Vpk[4][34][2]*Vpk[5][34][2])+((Vpk[4][34][0]*
          Vpk[5][34][0])+(Vpk[4][34][1]*Vpk[5][34][1]))))+((.055*(Wpk[4][34][2]*
          Wpk[5][34][2]))+((.007*(Wpk[4][34][1]*Wpk[5][34][1]))+(.056*(
          Wpk[4][33][0]*Wpk[5][33][0])))))+temp[12]);
        mm[4][5] = (((1.34*((Vpk[4][36][2]*Vpk[5][36][2])+((Vpk[4][36][0]*
          Vpk[5][36][0])+(Vpk[4][36][1]*Vpk[5][36][1]))))+((.0018*(Wpk[4][35][2]
          *Wpk[5][35][2]))+((.007*(Wpk[4][36][1]*Wpk[5][36][1]))+(.0075*(
          Wpk[4][36][0]*Wpk[5][36][0])))))+temp[13]);
        temp[0] = ((29.27*((.0213890625*(Wpk[4][8][0]*Wpk[6][8][0]))+((.00123201
          *(Wpk[4][8][0]*Wpk[6][8][0]))+(Vpk[4][8][0]*Vpk[6][8][0]))))+((.73*(
          Wpk[4][8][2]*Wpk[6][8][2]))+((.63*(Wpk[4][8][0]*Wpk[6][8][0]))-(.32*(
          Wpk[4][7][1]*s7)))));
        temp[1] = (temp[0]+(((.006*(Wpk[4][11][2]*Wpk[6][11][2]))+((.001*(
          Wpk[4][10][1]*Wpk[6][10][1]))+(.006*(Wpk[4][11][0]*Wpk[6][11][0]))))+(
          (Vpk[4][11][2]*Vpk[6][11][2])+((Vpk[4][11][0]*Vpk[6][11][0])+(
          Vpk[4][11][1]*Vpk[6][11][1])))));
        temp[2] = (((5.89*((Vpk[4][12][2]*Vpk[6][12][2])+((Vpk[4][12][0]*
          Vpk[6][12][0])+(Vpk[4][12][1]*Vpk[6][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[6][12][2]))+((.023*(Wpk[4][12][1]*Wpk[6][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[6][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[4][14][2]*Vpk[6][14][2])+((Vpk[4][14][0]*
          Vpk[6][14][0])+(Vpk[4][14][1]*Vpk[6][14][1]))))+((.025*(Wpk[4][14][2]*
          Wpk[6][14][2]))+((.005*(Wpk[4][14][0]*Wpk[6][14][0]))+(.025*(
          Wpk[4][13][1]*Wpk[6][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[4][16][2]*Vpk[6][16][2])+((Vpk[4][16][0]*
          Vpk[6][16][0])+(Vpk[4][16][1]*Vpk[6][16][1]))))+((.005*(Wpk[4][16][2]*
          Wpk[6][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[6][15][0]))+(.0054*(
          Wpk[4][16][1]*Wpk[6][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[4][18][2]*Vpk[6][18][2])+((Vpk[4][18][0]*
          Vpk[6][18][0])+(Vpk[4][18][1]*Vpk[6][18][1]))))+((.0016*(Wpk[4][18][2]
          *Wpk[6][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[6][18][0]))+(.002*(
          Wpk[4][17][1]*Wpk[6][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[4][20][2]*Vpk[6][20][2])+((Vpk[4][20][0]*
          Vpk[6][20][0])+(Vpk[4][20][1]*Vpk[6][20][1]))))+((.025*(Wpk[4][20][2]*
          Wpk[6][20][2]))+((.005*(Wpk[4][20][0]*Wpk[6][20][0]))+(.025*(
          Wpk[4][19][1]*Wpk[6][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[4][22][2]*Vpk[6][22][2])+((Vpk[4][22][0]*
          Vpk[6][22][0])+(Vpk[4][22][1]*Vpk[6][22][1]))))+((.005*(Wpk[4][22][2]*
          Wpk[6][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[6][21][0]))+(.0054*(
          Wpk[4][22][1]*Wpk[6][22][1])))))+temp[6]);
        mm[4][6] = (((.55*((Vpk[4][24][2]*Vpk[6][24][2])+((Vpk[4][24][0]*
          Vpk[6][24][0])+(Vpk[4][24][1]*Vpk[6][24][1]))))+((.0016*(Wpk[4][24][2]
          *Wpk[6][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[6][24][0]))+(.002*(
          Wpk[4][23][1]*Wpk[6][23][1])))))+temp[7]);
        temp[0] = ((((.006*(Wpk[4][11][2]*Wpk[7][11][2]))+((.001*(Wpk[4][10][1]*
          Wpk[7][10][1]))+(.006*(Wpk[4][11][0]*Wpk[7][11][0]))))+((Vpk[4][11][2]
          *Vpk[7][11][2])+((Vpk[4][11][0]*Vpk[7][11][0])+(Vpk[4][11][1]*
          Vpk[7][11][1]))))+(((.73*(Wpk[4][8][2]*c8))-(.63*(Wpk[4][8][0]*s8)))-(
          29.27*((.0213890625*(Wpk[4][8][0]*s8))+((.00123201*(Wpk[4][8][0]*s8))+
          (.14625*(Vpk[4][8][0]*c8)))))));
        temp[1] = (((5.89*((Vpk[4][12][2]*Vpk[7][12][2])+((Vpk[4][12][0]*
          Vpk[7][12][0])+(Vpk[4][12][1]*Vpk[7][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[7][12][2]))+((.023*(Wpk[4][12][1]*Wpk[7][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[7][11][0])))))+temp[0]);
        temp[2] = (((2.79*((Vpk[4][14][2]*Vpk[7][14][2])+((Vpk[4][14][0]*
          Vpk[7][14][0])+(Vpk[4][14][1]*Vpk[7][14][1]))))+((.025*(Wpk[4][14][2]*
          Wpk[7][14][2]))+((.005*(Wpk[4][14][0]*Wpk[7][14][0]))+(.025*(
          Wpk[4][13][1]*Wpk[7][13][1])))))+temp[1]);
        temp[3] = (((1.21*((Vpk[4][16][2]*Vpk[7][16][2])+((Vpk[4][16][0]*
          Vpk[7][16][0])+(Vpk[4][16][1]*Vpk[7][16][1]))))+((.005*(Wpk[4][16][2]*
          Wpk[7][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[7][15][0]))+(.0054*(
          Wpk[4][16][1]*Wpk[7][16][1])))))+temp[2]);
        temp[4] = (((.55*((Vpk[4][18][2]*Vpk[7][18][2])+((Vpk[4][18][0]*
          Vpk[7][18][0])+(Vpk[4][18][1]*Vpk[7][18][1]))))+((.0016*(Wpk[4][18][2]
          *Wpk[7][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[7][18][0]))+(.002*(
          Wpk[4][17][1]*Wpk[7][17][1])))))+temp[3]);
        temp[5] = (((2.79*((Vpk[4][20][2]*Vpk[7][20][2])+((Vpk[4][20][0]*
          Vpk[7][20][0])+(Vpk[4][20][1]*Vpk[7][20][1]))))+((.025*(Wpk[4][20][2]*
          Wpk[7][20][2]))+((.005*(Wpk[4][20][0]*Wpk[7][20][0]))+(.025*(
          Wpk[4][19][1]*Wpk[7][19][1])))))+temp[4]);
        temp[6] = (((1.21*((Vpk[4][22][2]*Vpk[7][22][2])+((Vpk[4][22][0]*
          Vpk[7][22][0])+(Vpk[4][22][1]*Vpk[7][22][1]))))+((.005*(Wpk[4][22][2]*
          Wpk[7][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[7][21][0]))+(.0054*(
          Wpk[4][22][1]*Wpk[7][22][1])))))+temp[5]);
        mm[4][7] = (((.55*((Vpk[4][24][2]*Vpk[7][24][2])+((Vpk[4][24][0]*
          Vpk[7][24][0])+(Vpk[4][24][1]*Vpk[7][24][1]))))+((.0016*(Wpk[4][24][2]
          *Wpk[7][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[7][24][0]))+(.002*(
          Wpk[4][23][1]*Wpk[7][23][1])))))+temp[6]);
        temp[0] = (((.32*Wpk[4][7][1])-(1.027377*Vpk[4][8][0]))+(((.006*(
          Wpk[4][11][2]*Wpk[8][11][2]))+((.001*(Wpk[4][10][1]*Wpk[8][10][1]))+(
          .006*(Wpk[4][11][0]*Wpk[8][11][0]))))+((Vpk[4][11][2]*Vpk[8][11][2])+(
          (Vpk[4][11][0]*Vpk[8][11][0])+(Vpk[4][11][1]*Vpk[8][11][1])))));
        temp[1] = (((5.89*((Vpk[4][12][2]*Vpk[8][12][2])+((Vpk[4][12][0]*
          Vpk[8][12][0])+(Vpk[4][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[4][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[8][11][0])))))+temp[0]);
        temp[2] = ((1.21*((Vpk[4][16][2]*Vpk[8][16][2])+((Vpk[4][16][0]*
          Vpk[8][16][0])+(Vpk[4][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[4][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[4][16][1]*Wpk[8][16][1])))));
        temp[3] = (temp[2]+(((2.79*((Vpk[4][14][2]*Vpk[8][14][2])+((
          Vpk[4][14][0]*Vpk[8][14][0])+(Vpk[4][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[4][14][2]*Wpk[8][14][2]))+((.005*(Wpk[4][14][0]*Wpk[8][14][0]))+(
          .025*(Wpk[4][13][1]*c13)))))+temp[1]));
        temp[4] = (((.55*((Vpk[4][18][2]*Vpk[8][18][2])+((Vpk[4][18][0]*
          Vpk[8][18][0])+(Vpk[4][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[4][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[4][17][1]*Wpk[8][17][1])))))+temp[3]);
        temp[5] = ((1.21*((Vpk[4][22][2]*Vpk[8][22][2])+((Vpk[4][22][0]*
          Vpk[8][22][0])+(Vpk[4][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[4][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[4][22][1]*Wpk[8][22][1])))));
        temp[6] = (temp[5]+(((2.79*((Vpk[4][20][2]*Vpk[8][20][2])+((
          Vpk[4][20][0]*Vpk[8][20][0])+(Vpk[4][20][1]*Vpk[8][20][1]))))+((.025*(
          Wpk[4][20][2]*Wpk[8][20][2]))+((.005*(Wpk[4][20][0]*Wpk[8][20][0]))+(
          .025*(Wpk[4][19][1]*c19)))))+temp[4]));
        mm[4][8] = (((.55*((Vpk[4][24][2]*Vpk[8][24][2])+((Vpk[4][24][0]*
          Vpk[8][24][0])+(Vpk[4][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[4][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[4][23][1]*Wpk[8][23][1])))))+temp[6]);
        temp[0] = ((5.89*((Vpk[4][12][2]*Vpk[9][12][2])+((Vpk[4][12][0]*
          Vpk[9][12][0])+(Vpk[4][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[4][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[4][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[4][11][0]*Wpk[9][11][0])))));
        mm[4][9] = (temp[0]+(((.006*(Wpk[4][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[4][11][0]*Wpk[9][11][0]))-(.001*(Wpk[4][10][1]*s10))))+((.0442*(
          Vpk[4][11][2]*Wpk[9][11][0]))+((Vpk[4][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[4][11][1]*Wpk[9][11][0]))))));
        mm[4][10] = (((.006*((Wpk[4][11][2]*c11)-(Wpk[4][11][0]*s11)))+(((.0065*
          (Vpk[4][11][1]*s11))-(.0442*(Vpk[4][11][0]*c11)))-(.0442*(
          Vpk[4][11][2]*s11))))+((5.89*((Vpk[4][12][2]*Vpk[10][12][2])+((
          Vpk[4][12][0]*Vpk[10][12][0])+(Vpk[4][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[4][12][2]*Wpk[10][12][2]))+((.023*(Wpk[4][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[4][11][0]*s11))))));
        mm[4][11] = (((.001*Wpk[4][10][1])+(.0065*Vpk[4][11][0]))+((5.89*(
          Vpk[4][12][0]*Vpk[11][12][0]))+((.023*(Wpk[4][12][1]*c12))-(.03*(
          Wpk[4][12][2]*s12)))));
        mm[4][12] = ((.033*Wpk[4][11][0])+(5.89*((.078*Vpk[4][12][2])-(.0312*
          Vpk[4][12][1]))));
        temp[0] = (((1.21*((Vpk[4][16][2]*Vpk[13][16][2])+((Vpk[4][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[4][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[4][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[4][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[4][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[4][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[4][14][2]*c14))-(.005*(Wpk[4][14][0]*s14)
          ))));
        mm[4][13] = (((.55*((Vpk[4][18][2]*Vpk[13][18][2])+((Vpk[4][18][0]*
          Vpk[13][18][0])+(Vpk[4][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[4][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[4][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[4][13][1])+(2.79*((.0013*Vpk[4][14][0])-(.1326*
          Vpk[4][14][2]))))+((1.21*((Vpk[4][16][2]*Vpk[14][16][2])+((
          Vpk[4][16][0]*Vpk[14][16][0])+(Vpk[4][16][1]*Vpk[14][16][1]))))+((
          .0054*(Wpk[4][16][1]*c16))-(.005*(Wpk[4][16][2]*s16)))));
        mm[4][14] = (((.55*((Vpk[4][18][2]*Vpk[14][18][2])+((Vpk[4][18][0]*
          Vpk[14][18][0])+(Vpk[4][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[4][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[4][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[4][15] = (((.55*((Vpk[4][18][2]*Vpk[15][18][2])+((Vpk[4][18][0]*
          Vpk[15][18][0])+(Vpk[4][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[4][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[4][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[4][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[4][16][0]*s16))-(.1378*(Vpk[4][16][1]*s16)))-(.1378*(Vpk[4][16][2]
          *c16))))+((.0054*(Wpk[4][16][1]*c16))-(.005*(Wpk[4][16][2]*s16)))));
        mm[4][16] = (((.0012*Wpk[4][15][0])+(.004719*Vpk[4][16][2]))+((.55*((
          Vpk[4][18][2]*Vpk[16][18][2])+((.065*(Vpk[4][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[4][18][0]*s18)))))+((.0016*(Wpk[4][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[4][18][0]*Wpk[16][18][0]))-(.002*(Wpk[4][17][1]*s17))))))
          ;
        mm[4][17] = ((.03575*(Vpk[4][18][1]*c18))+((.0016*(Wpk[4][18][2]*c18))-(
          .0005*(Wpk[4][18][0]*s18))));
        mm[4][18] = ((.002*Wpk[4][17][1])-(.03575*Vpk[4][18][2]));
        temp[0] = (((1.21*((Vpk[4][22][2]*Vpk[19][22][2])+((Vpk[4][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[4][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[4][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[4][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[4][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[4][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[4][20][2]*c20))-(.005*(Wpk[4][20][0]*s20)
          ))));
        mm[4][19] = (((.55*((Vpk[4][24][2]*Vpk[19][24][2])+((Vpk[4][24][0]*
          Vpk[19][24][0])+(Vpk[4][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[4][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[4][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[4][19][1])+(2.79*((.0013*Vpk[4][20][0])+(.1326*
          Vpk[4][20][2]))))+((1.21*((Vpk[4][22][2]*Vpk[20][22][2])+((
          Vpk[4][22][0]*Vpk[20][22][0])+(Vpk[4][22][1]*Vpk[20][22][1]))))+((
          .0054*(Wpk[4][22][1]*c22))-(.005*(Wpk[4][22][2]*s22)))));
        mm[4][20] = (((.55*((Vpk[4][24][2]*Vpk[20][24][2])+((Vpk[4][24][0]*
          Vpk[20][24][0])+(Vpk[4][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[4][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[4][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[4][21] = (((.55*((Vpk[4][24][2]*Vpk[21][24][2])+((Vpk[4][24][0]*
          Vpk[21][24][0])+(Vpk[4][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[4][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[4][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[4][22][2]*c22))+((.0039*(Vpk[4][22][0]*s22))+(.1378*(Vpk[4][22][1]
          *s22)))))+((.0054*(Wpk[4][22][1]*c22))-(.005*(Wpk[4][22][2]*s22)))));
        mm[4][22] = (((.0012*Wpk[4][21][0])+(.004719*Vpk[4][22][2]))+((.55*((
          Vpk[4][24][2]*Vpk[22][24][2])-((.0078*(Vpk[4][24][0]*s24))+(.065*(
          Vpk[4][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[4][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[4][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[4][23][1]*s23))))));
        mm[4][23] = (((.0016*(Wpk[4][24][2]*c24))-(.0005*(Wpk[4][24][0]*s24)))-(
          .03575*(Vpk[4][24][1]*c24)));
        mm[4][24] = ((.002*Wpk[4][23][1])+(.03575*Vpk[4][24][2]));
        temp[0] = ((4.16*((Vpk[4][28][2]*Vpk[25][28][2])+((Vpk[4][28][0]*
          Vpk[25][28][0])+(Vpk[4][28][1]*Vpk[25][28][1]))))+((.055*(
          Wpk[4][28][2]*Wpk[25][28][2]))+((.007*(Wpk[4][28][1]*Wpk[25][28][1]))+
          (.056*(Wpk[4][27][0]*Wpk[25][27][0])))));
        temp[1] = ((1.34*((Vpk[4][30][2]*Vpk[25][30][2])+((Vpk[4][30][0]*
          Vpk[25][30][0])+(Vpk[4][30][1]*Vpk[25][30][1]))))+((.0018*(
          Wpk[4][29][2]*Wpk[25][29][2]))+((.007*(Wpk[4][30][1]*Wpk[25][30][1]))+
          (.0075*(Wpk[4][30][0]*Wpk[25][30][0])))));
        mm[4][25] = (temp[1]+(temp[0]+((8.35*((Vpk[4][27][2]*Vpk[25][27][2])+((
          Vpk[4][27][0]*Vpk[25][27][0])+(Vpk[4][27][1]*Vpk[25][27][1]))))+((.15*
          (Wpk[4][27][2]*Wpk[25][27][2]))+((.16*(Wpk[4][27][0]*Wpk[25][27][0]))-
          (.025*(Wpk[4][26][1]*s26)))))));
        temp[0] = (((4.16*((Vpk[4][28][2]*Vpk[26][28][2])+((Vpk[4][28][0]*
          Vpk[26][28][0])+(Vpk[4][28][1]*Vpk[26][28][1]))))+((.055*(
          Wpk[4][28][2]*Wpk[26][28][2]))+((.007*(Wpk[4][28][1]*Wpk[26][28][1]))-
          (.056*(Wpk[4][27][0]*s27)))))+((8.35*((.2379*(Vpk[4][27][2]*s27))+((
          .2379*(Vpk[4][27][0]*c27))+(Vpk[4][27][1]*Vpk[26][27][1]))))+((.15*(
          Wpk[4][27][2]*c27))-(.16*(Wpk[4][27][0]*s27)))));
        mm[4][26] = (((1.34*((Vpk[4][30][2]*Vpk[26][30][2])+((Vpk[4][30][0]*
          Vpk[26][30][0])+(Vpk[4][30][1]*Vpk[26][30][1]))))+((.0018*(
          Wpk[4][29][2]*Wpk[26][29][2]))+((.007*(Wpk[4][30][1]*Wpk[26][30][1]))+
          (.0075*(Wpk[4][30][0]*Wpk[26][30][0])))))+temp[0]);
        temp[0] = (((.025*Wpk[4][26][1])+(8.35*((.0143*Vpk[4][27][0])+(.0169*
          Vpk[4][27][2]))))+((4.16*((.0416*(Vpk[4][28][2]*c28))+((.0416*(
          Vpk[4][28][1]*s28))+(Vpk[4][28][0]*Vpk[27][28][0]))))+((.007*(
          Wpk[4][28][1]*c28))-(.055*(Wpk[4][28][2]*s28)))));
        mm[4][27] = (((1.34*((Vpk[4][30][2]*Vpk[27][30][2])+((Vpk[4][30][0]*
          Vpk[27][30][0])+(Vpk[4][30][1]*Vpk[27][30][1]))))+((.0018*(
          Wpk[4][29][2]*Wpk[27][29][2]))+((.007*(Wpk[4][30][1]*Wpk[27][30][1]))+
          (.0075*(Wpk[4][30][0]*Wpk[27][30][0])))))+temp[0]);
        mm[4][28] = (((.056*Wpk[4][27][0])+(4.16*((.0039*Vpk[4][28][1])-(.2158*
          Vpk[4][28][2]))))+((1.34*((Vpk[4][30][2]*Vpk[28][30][2])+((
          Vpk[4][30][0]*Vpk[28][30][0])+(Vpk[4][30][1]*Vpk[28][30][1]))))+((
          .0075*(Wpk[4][30][0]*c30))-(.007*(Wpk[4][30][1]*s30)))));
        mm[4][29] = (((.0075*(Wpk[4][30][0]*c30))-(.007*(Wpk[4][30][1]*s30)))-(
          1.34*((.039*((Vpk[4][30][0]*s30)+(Vpk[4][30][1]*c30)))+(.0442*(
          Vpk[4][30][2]*c30)))));
        mm[4][30] = ((.0018*Wpk[4][29][2])+(.059228*Vpk[4][30][0]));
        temp[0] = ((4.16*((Vpk[4][34][2]*Vpk[31][34][2])+((Vpk[4][34][0]*
          Vpk[31][34][0])+(Vpk[4][34][1]*Vpk[31][34][1]))))+((.055*(
          Wpk[4][34][2]*Wpk[31][34][2]))+((.007*(Wpk[4][34][1]*Wpk[31][34][1]))+
          (.056*(Wpk[4][33][0]*Wpk[31][33][0])))));
        temp[1] = ((1.34*((Vpk[4][36][2]*Vpk[31][36][2])+((Vpk[4][36][0]*
          Vpk[31][36][0])+(Vpk[4][36][1]*Vpk[31][36][1]))))+((.0018*(
          Wpk[4][35][2]*Wpk[31][35][2]))+((.007*(Wpk[4][36][1]*Wpk[31][36][1]))+
          (.0075*(Wpk[4][36][0]*Wpk[31][36][0])))));
        mm[4][31] = (temp[1]+(temp[0]+((8.35*((Vpk[4][33][2]*Vpk[31][33][2])+((
          Vpk[4][33][0]*Vpk[31][33][0])+(Vpk[4][33][1]*Vpk[31][33][1]))))+((.15*
          (Wpk[4][33][2]*Wpk[31][33][2]))+((.16*(Wpk[4][33][0]*Wpk[31][33][0]))-
          (.025*(Wpk[4][32][1]*s32)))))));
        temp[0] = (((4.16*((Vpk[4][34][2]*Vpk[32][34][2])+((Vpk[4][34][0]*
          Vpk[32][34][0])+(Vpk[4][34][1]*Vpk[32][34][1]))))+((.055*(
          Wpk[4][34][2]*Wpk[32][34][2]))+((.007*(Wpk[4][34][1]*Wpk[32][34][1]))-
          (.056*(Wpk[4][33][0]*s33)))))+((8.35*((.2379*(Vpk[4][33][2]*s33))+((
          .2379*(Vpk[4][33][0]*c33))+(Vpk[4][33][1]*Vpk[32][33][1]))))+((.15*(
          Wpk[4][33][2]*c33))-(.16*(Wpk[4][33][0]*s33)))));
        mm[4][32] = (((1.34*((Vpk[4][36][2]*Vpk[32][36][2])+((Vpk[4][36][0]*
          Vpk[32][36][0])+(Vpk[4][36][1]*Vpk[32][36][1]))))+((.0018*(
          Wpk[4][35][2]*Wpk[32][35][2]))+((.007*(Wpk[4][36][1]*Wpk[32][36][1]))+
          (.0075*(Wpk[4][36][0]*Wpk[32][36][0])))))+temp[0]);
        temp[0] = (((.025*Wpk[4][32][1])+(8.35*((.0143*Vpk[4][33][0])-(.0169*
          Vpk[4][33][2]))))+((4.16*(((Vpk[4][34][0]*Vpk[33][34][0])-(.0416*(
          Vpk[4][34][1]*s34)))-(.0416*(Vpk[4][34][2]*c34))))+((.007*(
          Wpk[4][34][1]*c34))-(.055*(Wpk[4][34][2]*s34)))));
        mm[4][33] = (((1.34*((Vpk[4][36][2]*Vpk[33][36][2])+((Vpk[4][36][0]*
          Vpk[33][36][0])+(Vpk[4][36][1]*Vpk[33][36][1]))))+((.0018*(
          Wpk[4][35][2]*Wpk[33][35][2]))+((.007*(Wpk[4][36][1]*Wpk[33][36][1]))+
          (.0075*(Wpk[4][36][0]*Wpk[33][36][0])))))+temp[0]);
        mm[4][34] = (((.056*Wpk[4][33][0])+(4.16*((.0039*Vpk[4][34][1])-(.2158*
          Vpk[4][34][2]))))+((1.34*((Vpk[4][36][2]*Vpk[34][36][2])+((
          Vpk[4][36][0]*Vpk[34][36][0])+(Vpk[4][36][1]*Vpk[34][36][1]))))+((
          .0075*(Wpk[4][36][0]*c36))-(.007*(Wpk[4][36][1]*s36)))));
        mm[4][35] = (((.0075*(Wpk[4][36][0]*c36))-(.007*(Wpk[4][36][1]*s36)))-(
          1.34*((.039*((Vpk[4][36][0]*s36)+(Vpk[4][36][1]*c36)))+(.0442*(
          Vpk[4][36][2]*c36)))));
        mm[4][36] = ((.0018*Wpk[4][35][2])+(.059228*Vpk[4][36][0]));
        temp[0] = ((29.27*((.0213890625*(Wpk[5][8][0]*Wpk[5][8][0]))+((.00123201
          *(Wpk[5][8][0]*Wpk[5][8][0]))+(Vpk[5][8][0]*Vpk[5][8][0]))))+((.73*(
          Wpk[5][8][2]*Wpk[5][8][2]))+((.32*(Wpk[5][7][1]*Wpk[5][7][1]))+(.63*(
          Wpk[5][8][0]*Wpk[5][8][0])))));
        temp[1] = (temp[0]+(((.006*(Wpk[5][11][2]*Wpk[5][11][2]))+((.001*(
          Wpk[5][10][1]*Wpk[5][10][1]))+(.006*(Wpk[5][11][0]*Wpk[5][11][0]))))+(
          (Vpk[5][11][2]*Vpk[5][11][2])+((Vpk[5][11][0]*Vpk[5][11][0])+(
          Vpk[5][11][1]*Vpk[5][11][1])))));
        temp[2] = (((5.89*((Vpk[5][12][2]*Vpk[5][12][2])+((Vpk[5][12][0]*
          Vpk[5][12][0])+(Vpk[5][12][1]*Vpk[5][12][1]))))+((.03*(Wpk[5][12][2]*
          Wpk[5][12][2]))+((.023*(Wpk[5][12][1]*Wpk[5][12][1]))+(.033*(
          Wpk[5][11][0]*Wpk[5][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[5][14][2]*Vpk[5][14][2])+((Vpk[5][14][0]*
          Vpk[5][14][0])+(Vpk[5][14][1]*Vpk[5][14][1]))))+((.025*(Wpk[5][14][2]*
          Wpk[5][14][2]))+((.005*(Wpk[5][14][0]*Wpk[5][14][0]))+(.025*(
          Wpk[5][13][1]*Wpk[5][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[5][16][2]*Vpk[5][16][2])+((Vpk[5][16][0]*
          Vpk[5][16][0])+(Vpk[5][16][1]*Vpk[5][16][1]))))+((.005*(Wpk[5][16][2]*
          Wpk[5][16][2]))+((.0012*(Wpk[5][15][0]*Wpk[5][15][0]))+(.0054*(
          Wpk[5][16][1]*Wpk[5][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[5][18][2]*Vpk[5][18][2])+((Vpk[5][18][0]*
          Vpk[5][18][0])+(Vpk[5][18][1]*Vpk[5][18][1]))))+((.0016*(Wpk[5][18][2]
          *Wpk[5][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[5][18][0]))+(.002*(
          Wpk[5][17][1]*Wpk[5][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[5][20][2]*Vpk[5][20][2])+((Vpk[5][20][0]*
          Vpk[5][20][0])+(Vpk[5][20][1]*Vpk[5][20][1]))))+((.025*(Wpk[5][20][2]*
          Wpk[5][20][2]))+((.005*(Wpk[5][20][0]*Wpk[5][20][0]))+(.025*(
          Wpk[5][19][1]*Wpk[5][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[5][22][2]*Vpk[5][22][2])+((Vpk[5][22][0]*
          Vpk[5][22][0])+(Vpk[5][22][1]*Vpk[5][22][1]))))+((.005*(Wpk[5][22][2]*
          Wpk[5][22][2]))+((.0012*(Wpk[5][21][0]*Wpk[5][21][0]))+(.0054*(
          Wpk[5][22][1]*Wpk[5][22][1])))))+temp[6]);
        temp[8] = (((.55*((Vpk[5][24][2]*Vpk[5][24][2])+((Vpk[5][24][0]*
          Vpk[5][24][0])+(Vpk[5][24][1]*Vpk[5][24][1]))))+((.0016*(Wpk[5][24][2]
          *Wpk[5][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[5][24][0]))+(.002*(
          Wpk[5][23][1]*Wpk[5][23][1])))))+temp[7]);
        temp[9] = (((8.35*((Vpk[5][27][2]*Vpk[5][27][2])+((Vpk[5][27][0]*
          Vpk[5][27][0])+(Vpk[5][27][1]*Vpk[5][27][1]))))+((.15*(Wpk[5][27][2]*
          Wpk[5][27][2]))+((.025*(Wpk[5][26][1]*Wpk[5][26][1]))+(.16*(
          Wpk[5][27][0]*Wpk[5][27][0])))))+temp[8]);
        temp[10] = (((4.16*((Vpk[5][28][2]*Vpk[5][28][2])+((Vpk[5][28][0]*
          Vpk[5][28][0])+(Vpk[5][28][1]*Vpk[5][28][1]))))+((.055*(Wpk[5][28][2]*
          Wpk[5][28][2]))+((.007*(Wpk[5][28][1]*Wpk[5][28][1]))+(.056*(
          Wpk[5][27][0]*Wpk[5][27][0])))))+temp[9]);
        temp[11] = (((1.34*((Vpk[5][30][2]*Vpk[5][30][2])+((Vpk[5][30][0]*
          Vpk[5][30][0])+(Vpk[5][30][1]*Vpk[5][30][1]))))+((.0018*(Wpk[5][29][2]
          *Wpk[5][29][2]))+((.007*(Wpk[5][30][1]*Wpk[5][30][1]))+(.0075*(
          Wpk[5][30][0]*Wpk[5][30][0])))))+temp[10]);
        temp[12] = (((8.35*((Vpk[5][33][2]*Vpk[5][33][2])+((Vpk[5][33][0]*
          Vpk[5][33][0])+(Vpk[5][33][1]*Vpk[5][33][1]))))+((.15*(Wpk[5][33][2]*
          Wpk[5][33][2]))+((.025*(Wpk[5][32][1]*Wpk[5][32][1]))+(.16*(
          Wpk[5][33][0]*Wpk[5][33][0])))))+temp[11]);
        temp[13] = (((4.16*((Vpk[5][34][2]*Vpk[5][34][2])+((Vpk[5][34][0]*
          Vpk[5][34][0])+(Vpk[5][34][1]*Vpk[5][34][1]))))+((.055*(Wpk[5][34][2]*
          Wpk[5][34][2]))+((.007*(Wpk[5][34][1]*Wpk[5][34][1]))+(.056*(
          Wpk[5][33][0]*Wpk[5][33][0])))))+temp[12]);
        mm[5][5] = (.4715818196+(((1.34*((Vpk[5][36][2]*Vpk[5][36][2])+((
          Vpk[5][36][0]*Vpk[5][36][0])+(Vpk[5][36][1]*Vpk[5][36][1]))))+((.0018*
          (Wpk[5][35][2]*Wpk[5][35][2]))+((.007*(Wpk[5][36][1]*Wpk[5][36][1]))+(
          .0075*(Wpk[5][36][0]*Wpk[5][36][0])))))+temp[13]));
        temp[0] = ((29.27*((.0213890625*(Wpk[5][8][0]*Wpk[6][8][0]))+((.00123201
          *(Wpk[5][8][0]*Wpk[6][8][0]))+(Vpk[5][8][0]*Vpk[6][8][0]))))+((.73*(
          Wpk[5][8][2]*Wpk[6][8][2]))+((.63*(Wpk[5][8][0]*Wpk[6][8][0]))-(.32*(
          Wpk[5][7][1]*s7)))));
        temp[1] = (temp[0]+(((.006*(Wpk[5][11][2]*Wpk[6][11][2]))+((.001*(
          Wpk[5][10][1]*Wpk[6][10][1]))+(.006*(Wpk[5][11][0]*Wpk[6][11][0]))))+(
          (Vpk[5][11][2]*Vpk[6][11][2])+((Vpk[5][11][0]*Vpk[6][11][0])+(
          Vpk[5][11][1]*Vpk[6][11][1])))));
        temp[2] = (((5.89*((Vpk[5][12][2]*Vpk[6][12][2])+((Vpk[5][12][0]*
          Vpk[6][12][0])+(Vpk[5][12][1]*Vpk[6][12][1]))))+((.03*(Wpk[5][12][2]*
          Wpk[6][12][2]))+((.023*(Wpk[5][12][1]*Wpk[6][12][1]))+(.033*(
          Wpk[5][11][0]*Wpk[6][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[5][14][2]*Vpk[6][14][2])+((Vpk[5][14][0]*
          Vpk[6][14][0])+(Vpk[5][14][1]*Vpk[6][14][1]))))+((.025*(Wpk[5][14][2]*
          Wpk[6][14][2]))+((.005*(Wpk[5][14][0]*Wpk[6][14][0]))+(.025*(
          Wpk[5][13][1]*Wpk[6][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[5][16][2]*Vpk[6][16][2])+((Vpk[5][16][0]*
          Vpk[6][16][0])+(Vpk[5][16][1]*Vpk[6][16][1]))))+((.005*(Wpk[5][16][2]*
          Wpk[6][16][2]))+((.0012*(Wpk[5][15][0]*Wpk[6][15][0]))+(.0054*(
          Wpk[5][16][1]*Wpk[6][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[5][18][2]*Vpk[6][18][2])+((Vpk[5][18][0]*
          Vpk[6][18][0])+(Vpk[5][18][1]*Vpk[6][18][1]))))+((.0016*(Wpk[5][18][2]
          *Wpk[6][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[6][18][0]))+(.002*(
          Wpk[5][17][1]*Wpk[6][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[5][20][2]*Vpk[6][20][2])+((Vpk[5][20][0]*
          Vpk[6][20][0])+(Vpk[5][20][1]*Vpk[6][20][1]))))+((.025*(Wpk[5][20][2]*
          Wpk[6][20][2]))+((.005*(Wpk[5][20][0]*Wpk[6][20][0]))+(.025*(
          Wpk[5][19][1]*Wpk[6][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[5][22][2]*Vpk[6][22][2])+((Vpk[5][22][0]*
          Vpk[6][22][0])+(Vpk[5][22][1]*Vpk[6][22][1]))))+((.005*(Wpk[5][22][2]*
          Wpk[6][22][2]))+((.0012*(Wpk[5][21][0]*Wpk[6][21][0]))+(.0054*(
          Wpk[5][22][1]*Wpk[6][22][1])))))+temp[6]);
        mm[5][6] = (((.55*((Vpk[5][24][2]*Vpk[6][24][2])+((Vpk[5][24][0]*
          Vpk[6][24][0])+(Vpk[5][24][1]*Vpk[6][24][1]))))+((.0016*(Wpk[5][24][2]
          *Wpk[6][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[6][24][0]))+(.002*(
          Wpk[5][23][1]*Wpk[6][23][1])))))+temp[7]);
        temp[0] = ((((.006*(Wpk[5][11][2]*Wpk[7][11][2]))+((.001*(Wpk[5][10][1]*
          Wpk[7][10][1]))+(.006*(Wpk[5][11][0]*Wpk[7][11][0]))))+((Vpk[5][11][2]
          *Vpk[7][11][2])+((Vpk[5][11][0]*Vpk[7][11][0])+(Vpk[5][11][1]*
          Vpk[7][11][1]))))+(((.73*(Wpk[5][8][2]*c8))-(.63*(Wpk[5][8][0]*s8)))-(
          29.27*((.0213890625*(Wpk[5][8][0]*s8))+((.00123201*(Wpk[5][8][0]*s8))+
          (.14625*(Vpk[5][8][0]*c8)))))));
        temp[1] = (((5.89*((Vpk[5][12][2]*Vpk[7][12][2])+((Vpk[5][12][0]*
          Vpk[7][12][0])+(Vpk[5][12][1]*Vpk[7][12][1]))))+((.03*(Wpk[5][12][2]*
          Wpk[7][12][2]))+((.023*(Wpk[5][12][1]*Wpk[7][12][1]))+(.033*(
          Wpk[5][11][0]*Wpk[7][11][0])))))+temp[0]);
        temp[2] = (((2.79*((Vpk[5][14][2]*Vpk[7][14][2])+((Vpk[5][14][0]*
          Vpk[7][14][0])+(Vpk[5][14][1]*Vpk[7][14][1]))))+((.025*(Wpk[5][14][2]*
          Wpk[7][14][2]))+((.005*(Wpk[5][14][0]*Wpk[7][14][0]))+(.025*(
          Wpk[5][13][1]*Wpk[7][13][1])))))+temp[1]);
        temp[3] = (((1.21*((Vpk[5][16][2]*Vpk[7][16][2])+((Vpk[5][16][0]*
          Vpk[7][16][0])+(Vpk[5][16][1]*Vpk[7][16][1]))))+((.005*(Wpk[5][16][2]*
          Wpk[7][16][2]))+((.0012*(Wpk[5][15][0]*Wpk[7][15][0]))+(.0054*(
          Wpk[5][16][1]*Wpk[7][16][1])))))+temp[2]);
        temp[4] = (((.55*((Vpk[5][18][2]*Vpk[7][18][2])+((Vpk[5][18][0]*
          Vpk[7][18][0])+(Vpk[5][18][1]*Vpk[7][18][1]))))+((.0016*(Wpk[5][18][2]
          *Wpk[7][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[7][18][0]))+(.002*(
          Wpk[5][17][1]*Wpk[7][17][1])))))+temp[3]);
        temp[5] = (((2.79*((Vpk[5][20][2]*Vpk[7][20][2])+((Vpk[5][20][0]*
          Vpk[7][20][0])+(Vpk[5][20][1]*Vpk[7][20][1]))))+((.025*(Wpk[5][20][2]*
          Wpk[7][20][2]))+((.005*(Wpk[5][20][0]*Wpk[7][20][0]))+(.025*(
          Wpk[5][19][1]*Wpk[7][19][1])))))+temp[4]);
        temp[6] = (((1.21*((Vpk[5][22][2]*Vpk[7][22][2])+((Vpk[5][22][0]*
          Vpk[7][22][0])+(Vpk[5][22][1]*Vpk[7][22][1]))))+((.005*(Wpk[5][22][2]*
          Wpk[7][22][2]))+((.0012*(Wpk[5][21][0]*Wpk[7][21][0]))+(.0054*(
          Wpk[5][22][1]*Wpk[7][22][1])))))+temp[5]);
        mm[5][7] = (((.55*((Vpk[5][24][2]*Vpk[7][24][2])+((Vpk[5][24][0]*
          Vpk[7][24][0])+(Vpk[5][24][1]*Vpk[7][24][1]))))+((.0016*(Wpk[5][24][2]
          *Wpk[7][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[7][24][0]))+(.002*(
          Wpk[5][23][1]*Wpk[7][23][1])))))+temp[6]);
        temp[0] = (((.32*Wpk[5][7][1])-(1.027377*Vpk[5][8][0]))+(((.006*(
          Wpk[5][11][2]*Wpk[8][11][2]))+((.001*(Wpk[5][10][1]*Wpk[8][10][1]))+(
          .006*(Wpk[5][11][0]*Wpk[8][11][0]))))+((Vpk[5][11][2]*Vpk[8][11][2])+(
          (Vpk[5][11][0]*Vpk[8][11][0])+(Vpk[5][11][1]*Vpk[8][11][1])))));
        temp[1] = (((5.89*((Vpk[5][12][2]*Vpk[8][12][2])+((Vpk[5][12][0]*
          Vpk[8][12][0])+(Vpk[5][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[5][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[5][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[5][11][0]*Wpk[8][11][0])))))+temp[0]);
        temp[2] = ((1.21*((Vpk[5][16][2]*Vpk[8][16][2])+((Vpk[5][16][0]*
          Vpk[8][16][0])+(Vpk[5][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[5][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[5][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[5][16][1]*Wpk[8][16][1])))));
        temp[3] = (temp[2]+(((2.79*((Vpk[5][14][2]*Vpk[8][14][2])+((
          Vpk[5][14][0]*Vpk[8][14][0])+(Vpk[5][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[5][14][2]*Wpk[8][14][2]))+((.005*(Wpk[5][14][0]*Wpk[8][14][0]))+(
          .025*(Wpk[5][13][1]*c13)))))+temp[1]));
        temp[4] = (((.55*((Vpk[5][18][2]*Vpk[8][18][2])+((Vpk[5][18][0]*
          Vpk[8][18][0])+(Vpk[5][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[5][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[5][17][1]*Wpk[8][17][1])))))+temp[3]);
        temp[5] = ((1.21*((Vpk[5][22][2]*Vpk[8][22][2])+((Vpk[5][22][0]*
          Vpk[8][22][0])+(Vpk[5][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[5][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[5][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[5][22][1]*Wpk[8][22][1])))));
        temp[6] = (temp[5]+(((2.79*((Vpk[5][20][2]*Vpk[8][20][2])+((
          Vpk[5][20][0]*Vpk[8][20][0])+(Vpk[5][20][1]*Vpk[8][20][1]))))+((.025*(
          Wpk[5][20][2]*Wpk[8][20][2]))+((.005*(Wpk[5][20][0]*Wpk[8][20][0]))+(
          .025*(Wpk[5][19][1]*c19)))))+temp[4]));
        mm[5][8] = (((.55*((Vpk[5][24][2]*Vpk[8][24][2])+((Vpk[5][24][0]*
          Vpk[8][24][0])+(Vpk[5][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[5][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[5][23][1]*Wpk[8][23][1])))))+temp[6]);
        temp[0] = ((5.89*((Vpk[5][12][2]*Vpk[9][12][2])+((Vpk[5][12][0]*
          Vpk[9][12][0])+(Vpk[5][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[5][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[5][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[5][11][0]*Wpk[9][11][0])))));
        mm[5][9] = (temp[0]+(((.006*(Wpk[5][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[5][11][0]*Wpk[9][11][0]))-(.001*(Wpk[5][10][1]*s10))))+((.0442*(
          Vpk[5][11][2]*Wpk[9][11][0]))+((Vpk[5][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[5][11][1]*Wpk[9][11][0]))))));
        mm[5][10] = (((.006*((Wpk[5][11][2]*c11)-(Wpk[5][11][0]*s11)))+(((.0065*
          (Vpk[5][11][1]*s11))-(.0442*(Vpk[5][11][0]*c11)))-(.0442*(
          Vpk[5][11][2]*s11))))+((5.89*((Vpk[5][12][2]*Vpk[10][12][2])+((
          Vpk[5][12][0]*Vpk[10][12][0])+(Vpk[5][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[5][12][2]*Wpk[10][12][2]))+((.023*(Wpk[5][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[5][11][0]*s11))))));
        mm[5][11] = (((.001*Wpk[5][10][1])+(.0065*Vpk[5][11][0]))+((5.89*(
          Vpk[5][12][0]*Vpk[11][12][0]))+((.023*(Wpk[5][12][1]*c12))-(.03*(
          Wpk[5][12][2]*s12)))));
        mm[5][12] = ((.033*Wpk[5][11][0])+(5.89*((.078*Vpk[5][12][2])-(.0312*
          Vpk[5][12][1]))));
        temp[0] = (((1.21*((Vpk[5][16][2]*Vpk[13][16][2])+((Vpk[5][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[5][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[5][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[5][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[5][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[5][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[5][14][2]*c14))-(.005*(Wpk[5][14][0]*s14)
          ))));
        mm[5][13] = (((.55*((Vpk[5][18][2]*Vpk[13][18][2])+((Vpk[5][18][0]*
          Vpk[13][18][0])+(Vpk[5][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[5][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[5][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[5][13][1])+(2.79*((.0013*Vpk[5][14][0])-(.1326*
          Vpk[5][14][2]))))+((1.21*((Vpk[5][16][2]*Vpk[14][16][2])+((
          Vpk[5][16][0]*Vpk[14][16][0])+(Vpk[5][16][1]*Vpk[14][16][1]))))+((
          .0054*(Wpk[5][16][1]*c16))-(.005*(Wpk[5][16][2]*s16)))));
        mm[5][14] = (((.55*((Vpk[5][18][2]*Vpk[14][18][2])+((Vpk[5][18][0]*
          Vpk[14][18][0])+(Vpk[5][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[5][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[5][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[5][15] = (((.55*((Vpk[5][18][2]*Vpk[15][18][2])+((Vpk[5][18][0]*
          Vpk[15][18][0])+(Vpk[5][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[5][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[5][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[5][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[5][16][0]*s16))-(.1378*(Vpk[5][16][1]*s16)))-(.1378*(Vpk[5][16][2]
          *c16))))+((.0054*(Wpk[5][16][1]*c16))-(.005*(Wpk[5][16][2]*s16)))));
        mm[5][16] = (((.0012*Wpk[5][15][0])+(.004719*Vpk[5][16][2]))+((.55*((
          Vpk[5][18][2]*Vpk[16][18][2])+((.065*(Vpk[5][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[5][18][0]*s18)))))+((.0016*(Wpk[5][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[5][18][0]*Wpk[16][18][0]))-(.002*(Wpk[5][17][1]*s17))))))
          ;
        mm[5][17] = ((.03575*(Vpk[5][18][1]*c18))+((.0016*(Wpk[5][18][2]*c18))-(
          .0005*(Wpk[5][18][0]*s18))));
        mm[5][18] = ((.002*Wpk[5][17][1])-(.03575*Vpk[5][18][2]));
        temp[0] = (((1.21*((Vpk[5][22][2]*Vpk[19][22][2])+((Vpk[5][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[5][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[5][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[5][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[5][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[5][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[5][20][2]*c20))-(.005*(Wpk[5][20][0]*s20)
          ))));
        mm[5][19] = (((.55*((Vpk[5][24][2]*Vpk[19][24][2])+((Vpk[5][24][0]*
          Vpk[19][24][0])+(Vpk[5][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[5][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[5][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[5][19][1])+(2.79*((.0013*Vpk[5][20][0])+(.1326*
          Vpk[5][20][2]))))+((1.21*((Vpk[5][22][2]*Vpk[20][22][2])+((
          Vpk[5][22][0]*Vpk[20][22][0])+(Vpk[5][22][1]*Vpk[20][22][1]))))+((
          .0054*(Wpk[5][22][1]*c22))-(.005*(Wpk[5][22][2]*s22)))));
        mm[5][20] = (((.55*((Vpk[5][24][2]*Vpk[20][24][2])+((Vpk[5][24][0]*
          Vpk[20][24][0])+(Vpk[5][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[5][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[5][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[5][21] = (((.55*((Vpk[5][24][2]*Vpk[21][24][2])+((Vpk[5][24][0]*
          Vpk[21][24][0])+(Vpk[5][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[5][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[5][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[5][22][2]*c22))+((.0039*(Vpk[5][22][0]*s22))+(.1378*(Vpk[5][22][1]
          *s22)))))+((.0054*(Wpk[5][22][1]*c22))-(.005*(Wpk[5][22][2]*s22)))));
        mm[5][22] = (((.0012*Wpk[5][21][0])+(.004719*Vpk[5][22][2]))+((.55*((
          Vpk[5][24][2]*Vpk[22][24][2])-((.0078*(Vpk[5][24][0]*s24))+(.065*(
          Vpk[5][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[5][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[5][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[5][23][1]*s23))))));
        mm[5][23] = (((.0016*(Wpk[5][24][2]*c24))-(.0005*(Wpk[5][24][0]*s24)))-(
          .03575*(Vpk[5][24][1]*c24)));
        mm[5][24] = ((.002*Wpk[5][23][1])+(.03575*Vpk[5][24][2]));
        temp[0] = ((4.16*((Vpk[5][28][2]*Vpk[25][28][2])+((Vpk[5][28][0]*
          Vpk[25][28][0])+(Vpk[5][28][1]*Vpk[25][28][1]))))+((.055*(
          Wpk[5][28][2]*Wpk[25][28][2]))+((.007*(Wpk[5][28][1]*Wpk[25][28][1]))+
          (.056*(Wpk[5][27][0]*Wpk[25][27][0])))));
        temp[1] = ((1.34*((Vpk[5][30][2]*Vpk[25][30][2])+((Vpk[5][30][0]*
          Vpk[25][30][0])+(Vpk[5][30][1]*Vpk[25][30][1]))))+((.0018*(
          Wpk[5][29][2]*Wpk[25][29][2]))+((.007*(Wpk[5][30][1]*Wpk[25][30][1]))+
          (.0075*(Wpk[5][30][0]*Wpk[25][30][0])))));
        mm[5][25] = (temp[1]+(temp[0]+((8.35*((Vpk[5][27][2]*Vpk[25][27][2])+((
          Vpk[5][27][0]*Vpk[25][27][0])+(Vpk[5][27][1]*Vpk[25][27][1]))))+((.15*
          (Wpk[5][27][2]*Wpk[25][27][2]))+((.16*(Wpk[5][27][0]*Wpk[25][27][0]))-
          (.025*(Wpk[5][26][1]*s26)))))));
        temp[0] = (((4.16*((Vpk[5][28][2]*Vpk[26][28][2])+((Vpk[5][28][0]*
          Vpk[26][28][0])+(Vpk[5][28][1]*Vpk[26][28][1]))))+((.055*(
          Wpk[5][28][2]*Wpk[26][28][2]))+((.007*(Wpk[5][28][1]*Wpk[26][28][1]))-
          (.056*(Wpk[5][27][0]*s27)))))+((8.35*((.2379*(Vpk[5][27][2]*s27))+((
          .2379*(Vpk[5][27][0]*c27))+(Vpk[5][27][1]*Vpk[26][27][1]))))+((.15*(
          Wpk[5][27][2]*c27))-(.16*(Wpk[5][27][0]*s27)))));
        mm[5][26] = (((1.34*((Vpk[5][30][2]*Vpk[26][30][2])+((Vpk[5][30][0]*
          Vpk[26][30][0])+(Vpk[5][30][1]*Vpk[26][30][1]))))+((.0018*(
          Wpk[5][29][2]*Wpk[26][29][2]))+((.007*(Wpk[5][30][1]*Wpk[26][30][1]))+
          (.0075*(Wpk[5][30][0]*Wpk[26][30][0])))))+temp[0]);
        temp[0] = (((.025*Wpk[5][26][1])+(8.35*((.0143*Vpk[5][27][0])+(.0169*
          Vpk[5][27][2]))))+((4.16*((.0416*(Vpk[5][28][2]*c28))+((.0416*(
          Vpk[5][28][1]*s28))+(Vpk[5][28][0]*Vpk[27][28][0]))))+((.007*(
          Wpk[5][28][1]*c28))-(.055*(Wpk[5][28][2]*s28)))));
        mm[5][27] = (((1.34*((Vpk[5][30][2]*Vpk[27][30][2])+((Vpk[5][30][0]*
          Vpk[27][30][0])+(Vpk[5][30][1]*Vpk[27][30][1]))))+((.0018*(
          Wpk[5][29][2]*Wpk[27][29][2]))+((.007*(Wpk[5][30][1]*Wpk[27][30][1]))+
          (.0075*(Wpk[5][30][0]*Wpk[27][30][0])))))+temp[0]);
        mm[5][28] = (((.056*Wpk[5][27][0])+(4.16*((.0039*Vpk[5][28][1])-(.2158*
          Vpk[5][28][2]))))+((1.34*((Vpk[5][30][2]*Vpk[28][30][2])+((
          Vpk[5][30][0]*Vpk[28][30][0])+(Vpk[5][30][1]*Vpk[28][30][1]))))+((
          .0075*(Wpk[5][30][0]*c30))-(.007*(Wpk[5][30][1]*s30)))));
        mm[5][29] = (((.0075*(Wpk[5][30][0]*c30))-(.007*(Wpk[5][30][1]*s30)))-(
          1.34*((.039*((Vpk[5][30][0]*s30)+(Vpk[5][30][1]*c30)))+(.0442*(
          Vpk[5][30][2]*c30)))));
        mm[5][30] = ((.0018*Wpk[5][29][2])+(.059228*Vpk[5][30][0]));
        temp[0] = ((4.16*((Vpk[5][34][2]*Vpk[31][34][2])+((Vpk[5][34][0]*
          Vpk[31][34][0])+(Vpk[5][34][1]*Vpk[31][34][1]))))+((.055*(
          Wpk[5][34][2]*Wpk[31][34][2]))+((.007*(Wpk[5][34][1]*Wpk[31][34][1]))+
          (.056*(Wpk[5][33][0]*Wpk[31][33][0])))));
        temp[1] = ((1.34*((Vpk[5][36][2]*Vpk[31][36][2])+((Vpk[5][36][0]*
          Vpk[31][36][0])+(Vpk[5][36][1]*Vpk[31][36][1]))))+((.0018*(
          Wpk[5][35][2]*Wpk[31][35][2]))+((.007*(Wpk[5][36][1]*Wpk[31][36][1]))+
          (.0075*(Wpk[5][36][0]*Wpk[31][36][0])))));
        mm[5][31] = (temp[1]+(temp[0]+((8.35*((Vpk[5][33][2]*Vpk[31][33][2])+((
          Vpk[5][33][0]*Vpk[31][33][0])+(Vpk[5][33][1]*Vpk[31][33][1]))))+((.15*
          (Wpk[5][33][2]*Wpk[31][33][2]))+((.16*(Wpk[5][33][0]*Wpk[31][33][0]))-
          (.025*(Wpk[5][32][1]*s32)))))));
        temp[0] = (((4.16*((Vpk[5][34][2]*Vpk[32][34][2])+((Vpk[5][34][0]*
          Vpk[32][34][0])+(Vpk[5][34][1]*Vpk[32][34][1]))))+((.055*(
          Wpk[5][34][2]*Wpk[32][34][2]))+((.007*(Wpk[5][34][1]*Wpk[32][34][1]))-
          (.056*(Wpk[5][33][0]*s33)))))+((8.35*((.2379*(Vpk[5][33][2]*s33))+((
          .2379*(Vpk[5][33][0]*c33))+(Vpk[5][33][1]*Vpk[32][33][1]))))+((.15*(
          Wpk[5][33][2]*c33))-(.16*(Wpk[5][33][0]*s33)))));
        mm[5][32] = (((1.34*((Vpk[5][36][2]*Vpk[32][36][2])+((Vpk[5][36][0]*
          Vpk[32][36][0])+(Vpk[5][36][1]*Vpk[32][36][1]))))+((.0018*(
          Wpk[5][35][2]*Wpk[32][35][2]))+((.007*(Wpk[5][36][1]*Wpk[32][36][1]))+
          (.0075*(Wpk[5][36][0]*Wpk[32][36][0])))))+temp[0]);
        temp[0] = (((.025*Wpk[5][32][1])+(8.35*((.0143*Vpk[5][33][0])-(.0169*
          Vpk[5][33][2]))))+((4.16*(((Vpk[5][34][0]*Vpk[33][34][0])-(.0416*(
          Vpk[5][34][1]*s34)))-(.0416*(Vpk[5][34][2]*c34))))+((.007*(
          Wpk[5][34][1]*c34))-(.055*(Wpk[5][34][2]*s34)))));
        mm[5][33] = (((1.34*((Vpk[5][36][2]*Vpk[33][36][2])+((Vpk[5][36][0]*
          Vpk[33][36][0])+(Vpk[5][36][1]*Vpk[33][36][1]))))+((.0018*(
          Wpk[5][35][2]*Wpk[33][35][2]))+((.007*(Wpk[5][36][1]*Wpk[33][36][1]))+
          (.0075*(Wpk[5][36][0]*Wpk[33][36][0])))))+temp[0]);
        mm[5][34] = (((.056*Wpk[5][33][0])+(4.16*((.0039*Vpk[5][34][1])-(.2158*
          Vpk[5][34][2]))))+((1.34*((Vpk[5][36][2]*Vpk[34][36][2])+((
          Vpk[5][36][0]*Vpk[34][36][0])+(Vpk[5][36][1]*Vpk[34][36][1]))))+((
          .0075*(Wpk[5][36][0]*c36))-(.007*(Wpk[5][36][1]*s36)))));
        mm[5][35] = (((.0075*(Wpk[5][36][0]*c36))-(.007*(Wpk[5][36][1]*s36)))-(
          1.34*((.039*((Vpk[5][36][0]*s36)+(Vpk[5][36][1]*c36)))+(.0442*(
          Vpk[5][36][2]*c36)))));
        mm[5][36] = ((.0018*Wpk[5][35][2])+(.059228*Vpk[5][36][0]));
        temp[0] = (((.006*(Wpk[6][11][2]*Wpk[6][11][2]))+((.001*(Wpk[6][10][1]*
          Wpk[6][10][1]))+(.006*(Wpk[6][11][0]*Wpk[6][11][0]))))+((Vpk[6][11][2]
          *Vpk[6][11][2])+((Vpk[6][11][0]*Vpk[6][11][0])+(Vpk[6][11][1]*
          Vpk[6][11][1]))));
        temp[1] = (((29.27*((.0213890625*(Wpk[6][8][0]*Wpk[6][8][0]))+((
          .00123201*(Wpk[6][8][0]*Wpk[6][8][0]))+(Vpk[6][8][0]*Vpk[6][8][0]))))+
          ((.73*(Wpk[6][8][2]*Wpk[6][8][2]))+((.32*(s7*s7))+(.63*(Wpk[6][8][0]*
          Wpk[6][8][0])))))+temp[0]);
        temp[2] = (((5.89*((Vpk[6][12][2]*Vpk[6][12][2])+((Vpk[6][12][0]*
          Vpk[6][12][0])+(Vpk[6][12][1]*Vpk[6][12][1]))))+((.03*(Wpk[6][12][2]*
          Wpk[6][12][2]))+((.023*(Wpk[6][12][1]*Wpk[6][12][1]))+(.033*(
          Wpk[6][11][0]*Wpk[6][11][0])))))+temp[1]);
        temp[3] = (((2.79*((Vpk[6][14][2]*Vpk[6][14][2])+((Vpk[6][14][0]*
          Vpk[6][14][0])+(Vpk[6][14][1]*Vpk[6][14][1]))))+((.025*(Wpk[6][14][2]*
          Wpk[6][14][2]))+((.005*(Wpk[6][14][0]*Wpk[6][14][0]))+(.025*(
          Wpk[6][13][1]*Wpk[6][13][1])))))+temp[2]);
        temp[4] = (((1.21*((Vpk[6][16][2]*Vpk[6][16][2])+((Vpk[6][16][0]*
          Vpk[6][16][0])+(Vpk[6][16][1]*Vpk[6][16][1]))))+((.005*(Wpk[6][16][2]*
          Wpk[6][16][2]))+((.0012*(Wpk[6][15][0]*Wpk[6][15][0]))+(.0054*(
          Wpk[6][16][1]*Wpk[6][16][1])))))+temp[3]);
        temp[5] = (((.55*((Vpk[6][18][2]*Vpk[6][18][2])+((Vpk[6][18][0]*
          Vpk[6][18][0])+(Vpk[6][18][1]*Vpk[6][18][1]))))+((.0016*(Wpk[6][18][2]
          *Wpk[6][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[6][18][0]))+(.002*(
          Wpk[6][17][1]*Wpk[6][17][1])))))+temp[4]);
        temp[6] = (((2.79*((Vpk[6][20][2]*Vpk[6][20][2])+((Vpk[6][20][0]*
          Vpk[6][20][0])+(Vpk[6][20][1]*Vpk[6][20][1]))))+((.025*(Wpk[6][20][2]*
          Wpk[6][20][2]))+((.005*(Wpk[6][20][0]*Wpk[6][20][0]))+(.025*(
          Wpk[6][19][1]*Wpk[6][19][1])))))+temp[5]);
        temp[7] = (((1.21*((Vpk[6][22][2]*Vpk[6][22][2])+((Vpk[6][22][0]*
          Vpk[6][22][0])+(Vpk[6][22][1]*Vpk[6][22][1]))))+((.005*(Wpk[6][22][2]*
          Wpk[6][22][2]))+((.0012*(Wpk[6][21][0]*Wpk[6][21][0]))+(.0054*(
          Wpk[6][22][1]*Wpk[6][22][1])))))+temp[6]);
        mm[6][6] = (((.55*((Vpk[6][24][2]*Vpk[6][24][2])+((Vpk[6][24][0]*
          Vpk[6][24][0])+(Vpk[6][24][1]*Vpk[6][24][1]))))+((.0016*(Wpk[6][24][2]
          *Wpk[6][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[6][24][0]))+(.002*(
          Wpk[6][23][1]*Wpk[6][23][1])))))+temp[7]);
        temp[0] = ((((.006*(Wpk[6][11][2]*Wpk[7][11][2]))+((.001*(Wpk[6][10][1]*
          Wpk[7][10][1]))+(.006*(Wpk[6][11][0]*Wpk[7][11][0]))))+((Vpk[6][11][2]
          *Vpk[7][11][2])+((Vpk[6][11][0]*Vpk[7][11][0])+(Vpk[6][11][1]*
          Vpk[7][11][1]))))+(((.73*(Wpk[6][8][2]*c8))-(.63*(Wpk[6][8][0]*s8)))-(
          29.27*((.0213890625*(Wpk[6][8][0]*s8))+((.00123201*(Wpk[6][8][0]*s8))+
          (.14625*(Vpk[6][8][0]*c8)))))));
        temp[1] = (((5.89*((Vpk[6][12][2]*Vpk[7][12][2])+((Vpk[6][12][0]*
          Vpk[7][12][0])+(Vpk[6][12][1]*Vpk[7][12][1]))))+((.03*(Wpk[6][12][2]*
          Wpk[7][12][2]))+((.023*(Wpk[6][12][1]*Wpk[7][12][1]))+(.033*(
          Wpk[6][11][0]*Wpk[7][11][0])))))+temp[0]);
        temp[2] = (((2.79*((Vpk[6][14][2]*Vpk[7][14][2])+((Vpk[6][14][0]*
          Vpk[7][14][0])+(Vpk[6][14][1]*Vpk[7][14][1]))))+((.025*(Wpk[6][14][2]*
          Wpk[7][14][2]))+((.005*(Wpk[6][14][0]*Wpk[7][14][0]))+(.025*(
          Wpk[6][13][1]*Wpk[7][13][1])))))+temp[1]);
        temp[3] = (((1.21*((Vpk[6][16][2]*Vpk[7][16][2])+((Vpk[6][16][0]*
          Vpk[7][16][0])+(Vpk[6][16][1]*Vpk[7][16][1]))))+((.005*(Wpk[6][16][2]*
          Wpk[7][16][2]))+((.0012*(Wpk[6][15][0]*Wpk[7][15][0]))+(.0054*(
          Wpk[6][16][1]*Wpk[7][16][1])))))+temp[2]);
        temp[4] = (((.55*((Vpk[6][18][2]*Vpk[7][18][2])+((Vpk[6][18][0]*
          Vpk[7][18][0])+(Vpk[6][18][1]*Vpk[7][18][1]))))+((.0016*(Wpk[6][18][2]
          *Wpk[7][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[7][18][0]))+(.002*(
          Wpk[6][17][1]*Wpk[7][17][1])))))+temp[3]);
        temp[5] = (((2.79*((Vpk[6][20][2]*Vpk[7][20][2])+((Vpk[6][20][0]*
          Vpk[7][20][0])+(Vpk[6][20][1]*Vpk[7][20][1]))))+((.025*(Wpk[6][20][2]*
          Wpk[7][20][2]))+((.005*(Wpk[6][20][0]*Wpk[7][20][0]))+(.025*(
          Wpk[6][19][1]*Wpk[7][19][1])))))+temp[4]);
        temp[6] = (((1.21*((Vpk[6][22][2]*Vpk[7][22][2])+((Vpk[6][22][0]*
          Vpk[7][22][0])+(Vpk[6][22][1]*Vpk[7][22][1]))))+((.005*(Wpk[6][22][2]*
          Wpk[7][22][2]))+((.0012*(Wpk[6][21][0]*Wpk[7][21][0]))+(.0054*(
          Wpk[6][22][1]*Wpk[7][22][1])))))+temp[5]);
        mm[6][7] = (((.55*((Vpk[6][24][2]*Vpk[7][24][2])+((Vpk[6][24][0]*
          Vpk[7][24][0])+(Vpk[6][24][1]*Vpk[7][24][1]))))+((.0016*(Wpk[6][24][2]
          *Wpk[7][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[7][24][0]))+(.002*(
          Wpk[6][23][1]*Wpk[7][23][1])))))+temp[6]);
        temp[0] = ((((.006*(Wpk[6][11][2]*Wpk[8][11][2]))+((.001*(Wpk[6][10][1]*
          Wpk[8][10][1]))+(.006*(Wpk[6][11][0]*Wpk[8][11][0]))))+((Vpk[6][11][2]
          *Vpk[8][11][2])+((Vpk[6][11][0]*Vpk[8][11][0])+(Vpk[6][11][1]*
          Vpk[8][11][1]))))-((.32*s7)+(1.027377*Vpk[6][8][0])));
        temp[1] = (((5.89*((Vpk[6][12][2]*Vpk[8][12][2])+((Vpk[6][12][0]*
          Vpk[8][12][0])+(Vpk[6][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[6][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[6][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[6][11][0]*Wpk[8][11][0])))))+temp[0]);
        temp[2] = ((1.21*((Vpk[6][16][2]*Vpk[8][16][2])+((Vpk[6][16][0]*
          Vpk[8][16][0])+(Vpk[6][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[6][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[6][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[6][16][1]*Wpk[8][16][1])))));
        temp[3] = (temp[2]+(((2.79*((Vpk[6][14][2]*Vpk[8][14][2])+((
          Vpk[6][14][0]*Vpk[8][14][0])+(Vpk[6][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[6][14][2]*Wpk[8][14][2]))+((.005*(Wpk[6][14][0]*Wpk[8][14][0]))+(
          .025*(Wpk[6][13][1]*c13)))))+temp[1]));
        temp[4] = (((.55*((Vpk[6][18][2]*Vpk[8][18][2])+((Vpk[6][18][0]*
          Vpk[8][18][0])+(Vpk[6][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[6][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[6][17][1]*Wpk[8][17][1])))))+temp[3]);
        temp[5] = ((1.21*((Vpk[6][22][2]*Vpk[8][22][2])+((Vpk[6][22][0]*
          Vpk[8][22][0])+(Vpk[6][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[6][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[6][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[6][22][1]*Wpk[8][22][1])))));
        temp[6] = (temp[5]+(((2.79*((Vpk[6][20][2]*Vpk[8][20][2])+((
          Vpk[6][20][0]*Vpk[8][20][0])+(Vpk[6][20][1]*Vpk[8][20][1]))))+((.025*(
          Wpk[6][20][2]*Wpk[8][20][2]))+((.005*(Wpk[6][20][0]*Wpk[8][20][0]))+(
          .025*(Wpk[6][19][1]*c19)))))+temp[4]));
        mm[6][8] = (((.55*((Vpk[6][24][2]*Vpk[8][24][2])+((Vpk[6][24][0]*
          Vpk[8][24][0])+(Vpk[6][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[6][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[6][23][1]*Wpk[8][23][1])))))+temp[6]);
        temp[0] = ((5.89*((Vpk[6][12][2]*Vpk[9][12][2])+((Vpk[6][12][0]*
          Vpk[9][12][0])+(Vpk[6][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[6][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[6][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[6][11][0]*Wpk[9][11][0])))));
        mm[6][9] = (temp[0]+(((.006*(Wpk[6][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[6][11][0]*Wpk[9][11][0]))-(.001*(Wpk[6][10][1]*s10))))+((.0442*(
          Vpk[6][11][2]*Wpk[9][11][0]))+((Vpk[6][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[6][11][1]*Wpk[9][11][0]))))));
        mm[6][10] = (((.006*((Wpk[6][11][2]*c11)-(Wpk[6][11][0]*s11)))+(((.0065*
          (Vpk[6][11][1]*s11))-(.0442*(Vpk[6][11][0]*c11)))-(.0442*(
          Vpk[6][11][2]*s11))))+((5.89*((Vpk[6][12][2]*Vpk[10][12][2])+((
          Vpk[6][12][0]*Vpk[10][12][0])+(Vpk[6][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[6][12][2]*Wpk[10][12][2]))+((.023*(Wpk[6][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[6][11][0]*s11))))));
        mm[6][11] = (((.001*Wpk[6][10][1])+(.0065*Vpk[6][11][0]))+((5.89*(
          Vpk[6][12][0]*Vpk[11][12][0]))+((.023*(Wpk[6][12][1]*c12))-(.03*(
          Wpk[6][12][2]*s12)))));
        mm[6][12] = ((.033*Wpk[6][11][0])+(5.89*((.078*Vpk[6][12][2])-(.0312*
          Vpk[6][12][1]))));
        temp[0] = (((1.21*((Vpk[6][16][2]*Vpk[13][16][2])+((Vpk[6][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[6][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[6][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[6][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[6][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[6][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[6][14][2]*c14))-(.005*(Wpk[6][14][0]*s14)
          ))));
        mm[6][13] = (((.55*((Vpk[6][18][2]*Vpk[13][18][2])+((Vpk[6][18][0]*
          Vpk[13][18][0])+(Vpk[6][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[6][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[6][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[6][13][1])+(2.79*((.0013*Vpk[6][14][0])-(.1326*
          Vpk[6][14][2]))))+((1.21*((Vpk[6][16][2]*Vpk[14][16][2])+((
          Vpk[6][16][0]*Vpk[14][16][0])+(Vpk[6][16][1]*Vpk[14][16][1]))))+((
          .0054*(Wpk[6][16][1]*c16))-(.005*(Wpk[6][16][2]*s16)))));
        mm[6][14] = (((.55*((Vpk[6][18][2]*Vpk[14][18][2])+((Vpk[6][18][0]*
          Vpk[14][18][0])+(Vpk[6][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[6][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[6][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[6][15] = (((.55*((Vpk[6][18][2]*Vpk[15][18][2])+((Vpk[6][18][0]*
          Vpk[15][18][0])+(Vpk[6][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[6][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[6][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[6][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[6][16][0]*s16))-(.1378*(Vpk[6][16][1]*s16)))-(.1378*(Vpk[6][16][2]
          *c16))))+((.0054*(Wpk[6][16][1]*c16))-(.005*(Wpk[6][16][2]*s16)))));
        mm[6][16] = (((.0012*Wpk[6][15][0])+(.004719*Vpk[6][16][2]))+((.55*((
          Vpk[6][18][2]*Vpk[16][18][2])+((.065*(Vpk[6][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[6][18][0]*s18)))))+((.0016*(Wpk[6][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[6][18][0]*Wpk[16][18][0]))-(.002*(Wpk[6][17][1]*s17))))))
          ;
        mm[6][17] = ((.03575*(Vpk[6][18][1]*c18))+((.0016*(Wpk[6][18][2]*c18))-(
          .0005*(Wpk[6][18][0]*s18))));
        mm[6][18] = ((.002*Wpk[6][17][1])-(.03575*Vpk[6][18][2]));
        temp[0] = (((1.21*((Vpk[6][22][2]*Vpk[19][22][2])+((Vpk[6][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[6][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[6][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[6][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[6][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[6][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[6][20][2]*c20))-(.005*(Wpk[6][20][0]*s20)
          ))));
        mm[6][19] = (((.55*((Vpk[6][24][2]*Vpk[19][24][2])+((Vpk[6][24][0]*
          Vpk[19][24][0])+(Vpk[6][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[6][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[6][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[6][19][1])+(2.79*((.0013*Vpk[6][20][0])+(.1326*
          Vpk[6][20][2]))))+((1.21*((Vpk[6][22][2]*Vpk[20][22][2])+((
          Vpk[6][22][0]*Vpk[20][22][0])+(Vpk[6][22][1]*Vpk[20][22][1]))))+((
          .0054*(Wpk[6][22][1]*c22))-(.005*(Wpk[6][22][2]*s22)))));
        mm[6][20] = (((.55*((Vpk[6][24][2]*Vpk[20][24][2])+((Vpk[6][24][0]*
          Vpk[20][24][0])+(Vpk[6][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[6][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[6][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[6][21] = (((.55*((Vpk[6][24][2]*Vpk[21][24][2])+((Vpk[6][24][0]*
          Vpk[21][24][0])+(Vpk[6][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[6][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[6][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[6][22][2]*c22))+((.0039*(Vpk[6][22][0]*s22))+(.1378*(Vpk[6][22][1]
          *s22)))))+((.0054*(Wpk[6][22][1]*c22))-(.005*(Wpk[6][22][2]*s22)))));
        mm[6][22] = (((.0012*Wpk[6][21][0])+(.004719*Vpk[6][22][2]))+((.55*((
          Vpk[6][24][2]*Vpk[22][24][2])-((.0078*(Vpk[6][24][0]*s24))+(.065*(
          Vpk[6][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[6][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[6][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[6][23][1]*s23))))));
        mm[6][23] = (((.0016*(Wpk[6][24][2]*c24))-(.0005*(Wpk[6][24][0]*s24)))-(
          .03575*(Vpk[6][24][1]*c24)));
        mm[6][24] = ((.002*Wpk[6][23][1])+(.03575*Vpk[6][24][2]));
        mm[6][25] = 0.;
        mm[6][26] = 0.;
        mm[6][27] = 0.;
        mm[6][28] = 0.;
        mm[6][29] = 0.;
        mm[6][30] = 0.;
        mm[6][31] = 0.;
        mm[6][32] = 0.;
        mm[6][33] = 0.;
        mm[6][34] = 0.;
        mm[6][35] = 0.;
        mm[6][36] = 0.;
        temp[0] = (((.1*(c8*c8))+(29.27*(.0213890625+(.00123201*(s8*s8)))))+(((
          .006*(Wpk[7][11][2]*Wpk[7][11][2]))+((.001*(Wpk[7][10][1]*
          Wpk[7][10][1]))+(.006*(Wpk[7][11][0]*Wpk[7][11][0]))))+((Vpk[7][11][2]
          *Vpk[7][11][2])+((Vpk[7][11][0]*Vpk[7][11][0])+(Vpk[7][11][1]*
          Vpk[7][11][1])))));
        temp[1] = (((5.89*((Vpk[7][12][2]*Vpk[7][12][2])+((Vpk[7][12][0]*
          Vpk[7][12][0])+(Vpk[7][12][1]*Vpk[7][12][1]))))+((.03*(Wpk[7][12][2]*
          Wpk[7][12][2]))+((.023*(Wpk[7][12][1]*Wpk[7][12][1]))+(.033*(
          Wpk[7][11][0]*Wpk[7][11][0])))))+temp[0]);
        temp[2] = (((2.79*((Vpk[7][14][2]*Vpk[7][14][2])+((Vpk[7][14][0]*
          Vpk[7][14][0])+(Vpk[7][14][1]*Vpk[7][14][1]))))+((.025*(Wpk[7][14][2]*
          Wpk[7][14][2]))+((.005*(Wpk[7][14][0]*Wpk[7][14][0]))+(.025*(
          Wpk[7][13][1]*Wpk[7][13][1])))))+temp[1]);
        temp[3] = (((1.21*((Vpk[7][16][2]*Vpk[7][16][2])+((Vpk[7][16][0]*
          Vpk[7][16][0])+(Vpk[7][16][1]*Vpk[7][16][1]))))+((.005*(Wpk[7][16][2]*
          Wpk[7][16][2]))+((.0012*(Wpk[7][15][0]*Wpk[7][15][0]))+(.0054*(
          Wpk[7][16][1]*Wpk[7][16][1])))))+temp[2]);
        temp[4] = (((.55*((Vpk[7][18][2]*Vpk[7][18][2])+((Vpk[7][18][0]*
          Vpk[7][18][0])+(Vpk[7][18][1]*Vpk[7][18][1]))))+((.0016*(Wpk[7][18][2]
          *Wpk[7][18][2]))+((.0005*(Wpk[7][18][0]*Wpk[7][18][0]))+(.002*(
          Wpk[7][17][1]*Wpk[7][17][1])))))+temp[3]);
        temp[5] = (((2.79*((Vpk[7][20][2]*Vpk[7][20][2])+((Vpk[7][20][0]*
          Vpk[7][20][0])+(Vpk[7][20][1]*Vpk[7][20][1]))))+((.025*(Wpk[7][20][2]*
          Wpk[7][20][2]))+((.005*(Wpk[7][20][0]*Wpk[7][20][0]))+(.025*(
          Wpk[7][19][1]*Wpk[7][19][1])))))+temp[4]);
        temp[6] = (((1.21*((Vpk[7][22][2]*Vpk[7][22][2])+((Vpk[7][22][0]*
          Vpk[7][22][0])+(Vpk[7][22][1]*Vpk[7][22][1]))))+((.005*(Wpk[7][22][2]*
          Wpk[7][22][2]))+((.0012*(Wpk[7][21][0]*Wpk[7][21][0]))+(.0054*(
          Wpk[7][22][1]*Wpk[7][22][1])))))+temp[5]);
        mm[7][7] = (.63+(((.55*((Vpk[7][24][2]*Vpk[7][24][2])+((Vpk[7][24][0]*
          Vpk[7][24][0])+(Vpk[7][24][1]*Vpk[7][24][1]))))+((.0016*(Wpk[7][24][2]
          *Wpk[7][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[7][24][0]))+(.002*(
          Wpk[7][23][1]*Wpk[7][23][1])))))+temp[6]));
        temp[0] = ((.15025388625*c8)+(((.006*(Wpk[7][11][2]*Wpk[8][11][2]))+((
          .001*(Wpk[7][10][1]*Wpk[8][10][1]))+(.006*(Wpk[7][11][0]*Wpk[8][11][0]
          ))))+((Vpk[7][11][2]*Vpk[8][11][2])+((Vpk[7][11][0]*Vpk[8][11][0])+(
          Vpk[7][11][1]*Vpk[8][11][1])))));
        temp[1] = (temp[0]+((5.89*((Vpk[7][12][2]*Vpk[8][12][2])+((Vpk[7][12][0]
          *Vpk[8][12][0])+(Vpk[7][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[7][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[7][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[7][11][0]*Wpk[8][11][0]))))));
        temp[2] = ((1.21*((Vpk[7][16][2]*Vpk[8][16][2])+((Vpk[7][16][0]*
          Vpk[8][16][0])+(Vpk[7][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[7][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[7][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[7][16][1]*Wpk[8][16][1])))));
        temp[3] = (temp[2]+(((2.79*((Vpk[7][14][2]*Vpk[8][14][2])+((
          Vpk[7][14][0]*Vpk[8][14][0])+(Vpk[7][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[7][14][2]*Wpk[8][14][2]))+((.005*(Wpk[7][14][0]*Wpk[8][14][0]))+(
          .025*(Wpk[7][13][1]*c13)))))+temp[1]));
        temp[4] = (((.55*((Vpk[7][18][2]*Vpk[8][18][2])+((Vpk[7][18][0]*
          Vpk[8][18][0])+(Vpk[7][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[7][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[7][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[7][17][1]*Wpk[8][17][1])))))+temp[3]);
        temp[5] = ((1.21*((Vpk[7][22][2]*Vpk[8][22][2])+((Vpk[7][22][0]*
          Vpk[8][22][0])+(Vpk[7][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[7][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[7][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[7][22][1]*Wpk[8][22][1])))));
        temp[6] = (temp[5]+(((2.79*((Vpk[7][20][2]*Vpk[8][20][2])+((
          Vpk[7][20][0]*Vpk[8][20][0])+(Vpk[7][20][1]*Vpk[8][20][1]))))+((.025*(
          Wpk[7][20][2]*Wpk[8][20][2]))+((.005*(Wpk[7][20][0]*Wpk[8][20][0]))+(
          .025*(Wpk[7][19][1]*c19)))))+temp[4]));
        mm[7][8] = (((.55*((Vpk[7][24][2]*Vpk[8][24][2])+((Vpk[7][24][0]*
          Vpk[8][24][0])+(Vpk[7][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[7][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[7][23][1]*Wpk[8][23][1])))))+temp[6]);
        temp[0] = ((5.89*((Vpk[7][12][2]*Vpk[9][12][2])+((Vpk[7][12][0]*
          Vpk[9][12][0])+(Vpk[7][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[7][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[7][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[7][11][0]*Wpk[9][11][0])))));
        mm[7][9] = (temp[0]+(((.006*(Wpk[7][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[7][11][0]*Wpk[9][11][0]))-(.001*(Wpk[7][10][1]*s10))))+((.0442*(
          Vpk[7][11][2]*Wpk[9][11][0]))+((Vpk[7][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[7][11][1]*Wpk[9][11][0]))))));
        mm[7][10] = (((.006*((Wpk[7][11][2]*c11)-(Wpk[7][11][0]*s11)))+(((.0065*
          (Vpk[7][11][1]*s11))-(.0442*(Vpk[7][11][0]*c11)))-(.0442*(
          Vpk[7][11][2]*s11))))+((5.89*((Vpk[7][12][2]*Vpk[10][12][2])+((
          Vpk[7][12][0]*Vpk[10][12][0])+(Vpk[7][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[7][12][2]*Wpk[10][12][2]))+((.023*(Wpk[7][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[7][11][0]*s11))))));
        mm[7][11] = (((.001*Wpk[7][10][1])+(.0065*Vpk[7][11][0]))+((5.89*(
          Vpk[7][12][0]*Vpk[11][12][0]))+((.023*(Wpk[7][12][1]*c12))-(.03*(
          Wpk[7][12][2]*s12)))));
        mm[7][12] = ((.033*Wpk[7][11][0])+(5.89*((.078*Vpk[7][12][2])-(.0312*
          Vpk[7][12][1]))));
        temp[0] = (((1.21*((Vpk[7][16][2]*Vpk[13][16][2])+((Vpk[7][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[7][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[7][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[7][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[7][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[7][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[7][14][2]*c14))-(.005*(Wpk[7][14][0]*s14)
          ))));
        mm[7][13] = (((.55*((Vpk[7][18][2]*Vpk[13][18][2])+((Vpk[7][18][0]*
          Vpk[13][18][0])+(Vpk[7][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[7][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[7][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[7][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[7][13][1])+(2.79*((.0013*Vpk[7][14][0])-(.1326*
          Vpk[7][14][2]))))+((1.21*((Vpk[7][16][2]*Vpk[14][16][2])+((
          Vpk[7][16][0]*Vpk[14][16][0])+(Vpk[7][16][1]*Vpk[14][16][1]))))+((
          .0054*(Wpk[7][16][1]*c16))-(.005*(Wpk[7][16][2]*s16)))));
        mm[7][14] = (((.55*((Vpk[7][18][2]*Vpk[14][18][2])+((Vpk[7][18][0]*
          Vpk[14][18][0])+(Vpk[7][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[7][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[7][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[7][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[7][15] = (((.55*((Vpk[7][18][2]*Vpk[15][18][2])+((Vpk[7][18][0]*
          Vpk[15][18][0])+(Vpk[7][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[7][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[7][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[7][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[7][16][0]*s16))-(.1378*(Vpk[7][16][1]*s16)))-(.1378*(Vpk[7][16][2]
          *c16))))+((.0054*(Wpk[7][16][1]*c16))-(.005*(Wpk[7][16][2]*s16)))));
        mm[7][16] = (((.0012*Wpk[7][15][0])+(.004719*Vpk[7][16][2]))+((.55*((
          Vpk[7][18][2]*Vpk[16][18][2])+((.065*(Vpk[7][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[7][18][0]*s18)))))+((.0016*(Wpk[7][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[7][18][0]*Wpk[16][18][0]))-(.002*(Wpk[7][17][1]*s17))))))
          ;
        mm[7][17] = ((.03575*(Vpk[7][18][1]*c18))+((.0016*(Wpk[7][18][2]*c18))-(
          .0005*(Wpk[7][18][0]*s18))));
        mm[7][18] = ((.002*Wpk[7][17][1])-(.03575*Vpk[7][18][2]));
        temp[0] = (((1.21*((Vpk[7][22][2]*Vpk[19][22][2])+((Vpk[7][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[7][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[7][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[7][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[7][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[7][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[7][20][2]*c20))-(.005*(Wpk[7][20][0]*s20)
          ))));
        mm[7][19] = (((.55*((Vpk[7][24][2]*Vpk[19][24][2])+((Vpk[7][24][0]*
          Vpk[19][24][0])+(Vpk[7][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[7][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[7][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*Wpk[7][19][1])+(2.79*((.0013*Vpk[7][20][0])+(.1326*
          Vpk[7][20][2]))))+((1.21*((Vpk[7][22][2]*Vpk[20][22][2])+((
          Vpk[7][22][0]*Vpk[20][22][0])+(Vpk[7][22][1]*Vpk[20][22][1]))))+((
          .0054*(Wpk[7][22][1]*c22))-(.005*(Wpk[7][22][2]*s22)))));
        mm[7][20] = (((.55*((Vpk[7][24][2]*Vpk[20][24][2])+((Vpk[7][24][0]*
          Vpk[20][24][0])+(Vpk[7][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[7][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[7][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[7][21] = (((.55*((Vpk[7][24][2]*Vpk[21][24][2])+((Vpk[7][24][0]*
          Vpk[21][24][0])+(Vpk[7][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[7][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[7][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[7][22][2]*c22))+((.0039*(Vpk[7][22][0]*s22))+(.1378*(Vpk[7][22][1]
          *s22)))))+((.0054*(Wpk[7][22][1]*c22))-(.005*(Wpk[7][22][2]*s22)))));
        mm[7][22] = (((.0012*Wpk[7][21][0])+(.004719*Vpk[7][22][2]))+((.55*((
          Vpk[7][24][2]*Vpk[22][24][2])-((.0078*(Vpk[7][24][0]*s24))+(.065*(
          Vpk[7][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[7][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[7][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[7][23][1]*s23))))));
        mm[7][23] = (((.0016*(Wpk[7][24][2]*c24))-(.0005*(Wpk[7][24][0]*s24)))-(
          .03575*(Vpk[7][24][1]*c24)));
        mm[7][24] = ((.002*Wpk[7][23][1])+(.03575*Vpk[7][24][2]));
        mm[7][25] = 0.;
        mm[7][26] = 0.;
        mm[7][27] = 0.;
        mm[7][28] = 0.;
        mm[7][29] = 0.;
        mm[7][30] = 0.;
        mm[7][31] = 0.;
        mm[7][32] = 0.;
        mm[7][33] = 0.;
        mm[7][34] = 0.;
        mm[7][35] = 0.;
        mm[7][36] = 0.;
        temp[0] = ((5.89*((Vpk[8][12][2]*Vpk[8][12][2])+((Vpk[8][12][0]*
          Vpk[8][12][0])+(Vpk[8][12][1]*Vpk[8][12][1]))))+((.03*(Wpk[8][12][2]*
          Wpk[8][12][2]))+((.023*(Wpk[8][12][1]*Wpk[8][12][1]))+(.033*(
          Wpk[8][11][0]*Wpk[8][11][0])))));
        temp[1] = (temp[0]+(((.006*(Wpk[8][11][2]*Wpk[8][11][2]))+((.001*(
          Wpk[8][10][1]*Wpk[8][10][1]))+(.006*(Wpk[8][11][0]*Wpk[8][11][0]))))+(
          (Vpk[8][11][2]*Vpk[8][11][2])+((Vpk[8][11][0]*Vpk[8][11][0])+(
          Vpk[8][11][1]*Vpk[8][11][1])))));
        temp[2] = ((1.21*((Vpk[8][16][2]*Vpk[8][16][2])+((Vpk[8][16][0]*
          Vpk[8][16][0])+(Vpk[8][16][1]*Vpk[8][16][1]))))+((.005*(Wpk[8][16][2]*
          Wpk[8][16][2]))+((.0012*(Wpk[8][15][0]*Wpk[8][15][0]))+(.0054*(
          Wpk[8][16][1]*Wpk[8][16][1])))));
        temp[3] = ((.55*((Vpk[8][18][2]*Vpk[8][18][2])+((Vpk[8][18][0]*
          Vpk[8][18][0])+(Vpk[8][18][1]*Vpk[8][18][1]))))+((.0016*(Wpk[8][18][2]
          *Wpk[8][18][2]))+((.0005*(Wpk[8][18][0]*Wpk[8][18][0]))+(.002*(
          Wpk[8][17][1]*Wpk[8][17][1])))));
        temp[4] = (temp[3]+(temp[2]+(((2.79*((Vpk[8][14][2]*Vpk[8][14][2])+((
          Vpk[8][14][0]*Vpk[8][14][0])+(Vpk[8][14][1]*Vpk[8][14][1]))))+((.025*(
          Wpk[8][14][2]*Wpk[8][14][2]))+((.005*(Wpk[8][14][0]*Wpk[8][14][0]))+(
          .025*(c13*c13)))))+temp[1])));
        temp[5] = ((1.21*((Vpk[8][22][2]*Vpk[8][22][2])+((Vpk[8][22][0]*
          Vpk[8][22][0])+(Vpk[8][22][1]*Vpk[8][22][1]))))+((.005*(Wpk[8][22][2]*
          Wpk[8][22][2]))+((.0012*(Wpk[8][21][0]*Wpk[8][21][0]))+(.0054*(
          Wpk[8][22][1]*Wpk[8][22][1])))));
        temp[6] = ((.55*((Vpk[8][24][2]*Vpk[8][24][2])+((Vpk[8][24][0]*
          Vpk[8][24][0])+(Vpk[8][24][1]*Vpk[8][24][1]))))+((.0016*(Wpk[8][24][2]
          *Wpk[8][24][2]))+((.0005*(Wpk[8][24][0]*Wpk[8][24][0]))+(.002*(
          Wpk[8][23][1]*Wpk[8][23][1])))));
        mm[8][8] = (.3560609327+(temp[6]+(temp[5]+(((2.79*((Vpk[8][20][2]*
          Vpk[8][20][2])+((Vpk[8][20][0]*Vpk[8][20][0])+(Vpk[8][20][1]*
          Vpk[8][20][1]))))+((.025*(Wpk[8][20][2]*Wpk[8][20][2]))+((.005*(
          Wpk[8][20][0]*Wpk[8][20][0]))+(.025*(c19*c19)))))+temp[4]))));
        temp[0] = ((5.89*((Vpk[8][12][2]*Vpk[9][12][2])+((Vpk[8][12][0]*
          Vpk[9][12][0])+(Vpk[8][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[8][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[8][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[8][11][0]*Wpk[9][11][0])))));
        mm[8][9] = (temp[0]+(((.006*(Wpk[8][11][2]*Wpk[9][11][2]))+((.006*(
          Wpk[8][11][0]*Wpk[9][11][0]))-(.001*(Wpk[8][10][1]*s10))))+((.0442*(
          Vpk[8][11][2]*Wpk[9][11][0]))+((Vpk[8][11][0]*Vpk[9][11][0])-(.0065*(
          Vpk[8][11][1]*Wpk[9][11][0]))))));
        mm[8][10] = (((.006*((Wpk[8][11][2]*c11)-(Wpk[8][11][0]*s11)))+(((.0065*
          (Vpk[8][11][1]*s11))-(.0442*(Vpk[8][11][0]*c11)))-(.0442*(
          Vpk[8][11][2]*s11))))+((5.89*((Vpk[8][12][2]*Vpk[10][12][2])+((
          Vpk[8][12][0]*Vpk[10][12][0])+(Vpk[8][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[8][12][2]*Wpk[10][12][2]))+((.023*(Wpk[8][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[8][11][0]*s11))))));
        mm[8][11] = (((.001*Wpk[8][10][1])+(.0065*Vpk[8][11][0]))+((5.89*(
          Vpk[8][12][0]*Vpk[11][12][0]))+((.023*(Wpk[8][12][1]*c12))-(.03*(
          Wpk[8][12][2]*s12)))));
        mm[8][12] = ((.033*Wpk[8][11][0])+(5.89*((.078*Vpk[8][12][2])-(.0312*
          Vpk[8][12][1]))));
        temp[0] = (((1.21*((Vpk[8][16][2]*Vpk[13][16][2])+((Vpk[8][16][1]*
          Vpk[13][16][1])-(.0039*(Vpk[8][16][0]*Wpk[13][16][2])))))+((.005*(
          Wpk[8][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[8][15][0]*Wpk[13][15][0]))
          +(.0054*(Wpk[8][16][1]*Wpk[13][16][1])))))+((2.79*(Vpk[8][14][1]*
          Vpk[13][14][1]))+((.025*(Wpk[8][14][2]*c14))-(.005*(Wpk[8][14][0]*s14)
          ))));
        mm[8][13] = (((.55*((Vpk[8][18][2]*Vpk[13][18][2])+((Vpk[8][18][0]*
          Vpk[13][18][0])+(Vpk[8][18][1]*Vpk[13][18][1]))))+((.0016*(
          Wpk[8][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[8][18][0]*Wpk[13][18][0]))
          +(.002*(Wpk[8][17][1]*Wpk[13][17][1])))))+temp[0]);
        temp[0] = (((.025*c13)+(2.79*((.0013*Vpk[8][14][0])-(.1326*Vpk[8][14][2]
          ))))+((1.21*((Vpk[8][16][2]*Vpk[14][16][2])+((Vpk[8][16][0]*
          Vpk[14][16][0])+(Vpk[8][16][1]*Vpk[14][16][1]))))+((.0054*(
          Wpk[8][16][1]*c16))-(.005*(Wpk[8][16][2]*s16)))));
        mm[8][14] = (((.55*((Vpk[8][18][2]*Vpk[14][18][2])+((Vpk[8][18][0]*
          Vpk[14][18][0])+(Vpk[8][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[8][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[8][18][0]*Wpk[14][18][0]))
          +(.002*(Wpk[8][17][1]*Wpk[14][17][1])))))+temp[0]);
        mm[8][15] = (((.55*((Vpk[8][18][2]*Vpk[15][18][2])+((Vpk[8][18][0]*
          Vpk[15][18][0])+(Vpk[8][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[8][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[8][18][0]*Wpk[15][18][0]))
          +(.002*(Wpk[8][17][1]*Wpk[15][17][1])))))+((1.21*(((.0039*(
          Vpk[8][16][0]*s16))-(.1378*(Vpk[8][16][1]*s16)))-(.1378*(Vpk[8][16][2]
          *c16))))+((.0054*(Wpk[8][16][1]*c16))-(.005*(Wpk[8][16][2]*s16)))));
        mm[8][16] = (((.0012*Wpk[8][15][0])+(.004719*Vpk[8][16][2]))+((.55*((
          Vpk[8][18][2]*Vpk[16][18][2])+((.065*(Vpk[8][18][1]*Wpk[16][18][2]))-(
          .0078*(Vpk[8][18][0]*s18)))))+((.0016*(Wpk[8][18][2]*Wpk[16][18][2]))+
          ((.0005*(Wpk[8][18][0]*Wpk[16][18][0]))-(.002*(Wpk[8][17][1]*s17))))))
          ;
        mm[8][17] = ((.03575*(Vpk[8][18][1]*c18))+((.0016*(Wpk[8][18][2]*c18))-(
          .0005*(Wpk[8][18][0]*s18))));
        mm[8][18] = ((.002*Wpk[8][17][1])-(.03575*Vpk[8][18][2]));
        temp[0] = (((1.21*((Vpk[8][22][2]*Vpk[19][22][2])+((Vpk[8][22][1]*
          Vpk[19][22][1])-(.0039*(Vpk[8][22][0]*Wpk[19][22][2])))))+((.005*(
          Wpk[8][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[8][21][0]*Wpk[19][21][0]))
          +(.0054*(Wpk[8][22][1]*Wpk[19][22][1])))))+((2.79*(Vpk[8][20][1]*
          Vpk[19][20][1]))+((.025*(Wpk[8][20][2]*c20))-(.005*(Wpk[8][20][0]*s20)
          ))));
        mm[8][19] = (((.55*((Vpk[8][24][2]*Vpk[19][24][2])+((Vpk[8][24][0]*
          Vpk[19][24][0])+(Vpk[8][24][1]*Vpk[19][24][1]))))+((.0016*(
          Wpk[8][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[8][24][0]*Wpk[19][24][0]))
          +(.002*(Wpk[8][23][1]*Wpk[19][23][1])))))+temp[0]);
        temp[0] = (((.025*c19)+(2.79*((.0013*Vpk[8][20][0])+(.1326*Vpk[8][20][2]
          ))))+((1.21*((Vpk[8][22][2]*Vpk[20][22][2])+((Vpk[8][22][0]*
          Vpk[20][22][0])+(Vpk[8][22][1]*Vpk[20][22][1]))))+((.0054*(
          Wpk[8][22][1]*c22))-(.005*(Wpk[8][22][2]*s22)))));
        mm[8][20] = (((.55*((Vpk[8][24][2]*Vpk[20][24][2])+((Vpk[8][24][0]*
          Vpk[20][24][0])+(Vpk[8][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[8][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[8][24][0]*Wpk[20][24][0]))
          +(.002*(Wpk[8][23][1]*Wpk[20][23][1])))))+temp[0]);
        mm[8][21] = (((.55*((Vpk[8][24][2]*Vpk[21][24][2])+((Vpk[8][24][0]*
          Vpk[21][24][0])+(Vpk[8][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[8][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[8][24][0]*Wpk[21][24][0]))
          +(.002*(Wpk[8][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[8][22][2]*c22))+((.0039*(Vpk[8][22][0]*s22))+(.1378*(Vpk[8][22][1]
          *s22)))))+((.0054*(Wpk[8][22][1]*c22))-(.005*(Wpk[8][22][2]*s22)))));
        mm[8][22] = (((.0012*Wpk[8][21][0])+(.004719*Vpk[8][22][2]))+((.55*((
          Vpk[8][24][2]*Vpk[22][24][2])-((.0078*(Vpk[8][24][0]*s24))+(.065*(
          Vpk[8][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[8][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[8][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[8][23][1]*s23))))));
        mm[8][23] = (((.0016*(Wpk[8][24][2]*c24))-(.0005*(Wpk[8][24][0]*s24)))-(
          .03575*(Vpk[8][24][1]*c24)));
        mm[8][24] = ((.002*Wpk[8][23][1])+(.03575*Vpk[8][24][2]));
        mm[8][25] = 0.;
        mm[8][26] = 0.;
        mm[8][27] = 0.;
        mm[8][28] = 0.;
        mm[8][29] = 0.;
        mm[8][30] = 0.;
        mm[8][31] = 0.;
        mm[8][32] = 0.;
        mm[8][33] = 0.;
        mm[8][34] = 0.;
        mm[8][35] = 0.;
        mm[8][36] = 0.;
        temp[0] = ((5.89*((Vpk[9][12][2]*Vpk[9][12][2])+((Vpk[9][12][0]*
          Vpk[9][12][0])+(Vpk[9][12][1]*Vpk[9][12][1]))))+((.03*(Wpk[9][12][2]*
          Wpk[9][12][2]))+((.023*(Wpk[9][12][1]*Wpk[9][12][1]))+(.033*(
          Wpk[9][11][0]*Wpk[9][11][0])))));
        mm[9][9] = (temp[0]+(((.00195364*(Wpk[9][11][0]*Wpk[9][11][0]))+((
          4.225e-5*(Wpk[9][11][0]*Wpk[9][11][0]))+(Vpk[9][11][0]*Vpk[9][11][0]))
          )+((.006*(Wpk[9][11][2]*Wpk[9][11][2]))+((.001*(s10*s10))+(.006*(
          Wpk[9][11][0]*Wpk[9][11][0]))))));
        mm[9][10] = (((.006*((Wpk[9][11][2]*c11)-(Wpk[9][11][0]*s11)))-((
          .00195364*(Wpk[9][11][0]*s11))+((4.225e-5*(Wpk[9][11][0]*s11))+(.0442*
          (Vpk[9][11][0]*c11)))))+((5.89*((Vpk[9][12][2]*Vpk[10][12][2])+((
          Vpk[9][12][0]*Vpk[10][12][0])+(Vpk[9][12][1]*Vpk[10][12][1]))))+((.03*
          (Wpk[9][12][2]*Wpk[10][12][2]))+((.023*(Wpk[9][12][1]*Wpk[10][12][1]))
          -(.033*(Wpk[9][11][0]*s11))))));
        mm[9][11] = (((.0065*Vpk[9][11][0])-(.001*s10))+((5.89*(Vpk[9][12][0]*
          Vpk[11][12][0]))+((.023*(Wpk[9][12][1]*c12))-(.03*(Wpk[9][12][2]*s12))
          )));
        mm[9][12] = ((.033*Wpk[9][11][0])+(5.89*((.078*Vpk[9][12][2])-(.0312*
          Vpk[9][12][1]))));
        mm[9][13] = 0.;
        mm[9][14] = 0.;
        mm[9][15] = 0.;
        mm[9][16] = 0.;
        mm[9][17] = 0.;
        mm[9][18] = 0.;
        mm[9][19] = 0.;
        mm[9][20] = 0.;
        mm[9][21] = 0.;
        mm[9][22] = 0.;
        mm[9][23] = 0.;
        mm[9][24] = 0.;
        mm[9][25] = 0.;
        mm[9][26] = 0.;
        mm[9][27] = 0.;
        mm[9][28] = 0.;
        mm[9][29] = 0.;
        mm[9][30] = 0.;
        mm[9][31] = 0.;
        mm[9][32] = 0.;
        mm[9][33] = 0.;
        mm[9][34] = 0.;
        mm[9][35] = 0.;
        mm[9][36] = 0.;
        mm[10][10] = (.00795364+((4.225e-5*(s11*s11))+((5.89*((Vpk[10][12][2]*
          Vpk[10][12][2])+((Vpk[10][12][0]*Vpk[10][12][0])+(Vpk[10][12][1]*
          Vpk[10][12][1]))))+((.03*(Wpk[10][12][2]*Wpk[10][12][2]))+((.023*(
          Wpk[10][12][1]*Wpk[10][12][1]))+(.033*(s11*s11)))))));
        mm[10][11] = (((5.89*(Vpk[10][12][0]*Vpk[11][12][0]))+((.023*(
          Wpk[10][12][1]*c12))-(.03*(Wpk[10][12][2]*s12))))-(.0002873*c11));
        mm[10][12] = ((5.89*((.078*Vpk[10][12][2])-(.0312*Vpk[10][12][1])))-(
          .033*s11));
        mm[10][13] = 0.;
        mm[10][14] = 0.;
        mm[10][15] = 0.;
        mm[10][16] = 0.;
        mm[10][17] = 0.;
        mm[10][18] = 0.;
        mm[10][19] = 0.;
        mm[10][20] = 0.;
        mm[10][21] = 0.;
        mm[10][22] = 0.;
        mm[10][23] = 0.;
        mm[10][24] = 0.;
        mm[10][25] = 0.;
        mm[10][26] = 0.;
        mm[10][27] = 0.;
        mm[10][28] = 0.;
        mm[10][29] = 0.;
        mm[10][30] = 0.;
        mm[10][31] = 0.;
        mm[10][32] = 0.;
        mm[10][33] = 0.;
        mm[10][34] = 0.;
        mm[10][35] = 0.;
        mm[10][36] = 0.;
        mm[11][11] = (.02404225+((.007*(s12*s12))+(5.89*(Vpk[11][12][0]*
          Vpk[11][12][0]))));
        mm[11][12] = 0.;
        mm[11][13] = 0.;
        mm[11][14] = 0.;
        mm[11][15] = 0.;
        mm[11][16] = 0.;
        mm[11][17] = 0.;
        mm[11][18] = 0.;
        mm[11][19] = 0.;
        mm[11][20] = 0.;
        mm[11][21] = 0.;
        mm[11][22] = 0.;
        mm[11][23] = 0.;
        mm[11][24] = 0.;
        mm[11][25] = 0.;
        mm[11][26] = 0.;
        mm[11][27] = 0.;
        mm[11][28] = 0.;
        mm[11][29] = 0.;
        mm[11][30] = 0.;
        mm[11][31] = 0.;
        mm[11][32] = 0.;
        mm[11][33] = 0.;
        mm[11][34] = 0.;
        mm[11][35] = 0.;
        mm[11][36] = 0.;
        mm[12][12] = .0745683216;
        mm[12][13] = 0.;
        mm[12][14] = 0.;
        mm[12][15] = 0.;
        mm[12][16] = 0.;
        mm[12][17] = 0.;
        mm[12][18] = 0.;
        mm[12][19] = 0.;
        mm[12][20] = 0.;
        mm[12][21] = 0.;
        mm[12][22] = 0.;
        mm[12][23] = 0.;
        mm[12][24] = 0.;
        mm[12][25] = 0.;
        mm[12][26] = 0.;
        mm[12][27] = 0.;
        mm[12][28] = 0.;
        mm[12][29] = 0.;
        mm[12][30] = 0.;
        mm[12][31] = 0.;
        mm[12][32] = 0.;
        mm[12][33] = 0.;
        mm[12][34] = 0.;
        mm[12][35] = 0.;
        mm[12][36] = 0.;
        temp[0] = (((.02*(c14*c14))+(2.79*(Vpk[13][14][1]*Vpk[13][14][1])))+((
          1.21*((Vpk[13][16][2]*Vpk[13][16][2])+((1.521e-5*(Wpk[13][16][2]*
          Wpk[13][16][2]))+(Vpk[13][16][1]*Vpk[13][16][1]))))+((.005*(
          Wpk[13][16][2]*Wpk[13][16][2]))+((.0012*(Wpk[13][15][0]*Wpk[13][15][0]
          ))+(.0054*(Wpk[13][16][1]*Wpk[13][16][1]))))));
        mm[13][13] = (.005+(((.55*((Vpk[13][18][2]*Vpk[13][18][2])+((
          Vpk[13][18][0]*Vpk[13][18][0])+(Vpk[13][18][1]*Vpk[13][18][1]))))+((
          .0016*(Wpk[13][18][2]*Wpk[13][18][2]))+((.0005*(Wpk[13][18][0]*
          Wpk[13][18][0]))+(.002*(Wpk[13][17][1]*Wpk[13][17][1])))))+temp[0]));
        mm[13][14] = (((.55*((Vpk[13][18][2]*Vpk[14][18][2])+((Vpk[13][18][0]*
          Vpk[14][18][0])+(Vpk[13][18][1]*Vpk[14][18][1]))))+((.0016*(
          Wpk[13][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[13][18][0]*Wpk[14][18][0]
          ))+(.002*(Wpk[13][17][1]*Wpk[14][17][1])))))+((1.21*((Vpk[13][16][2]*
          Vpk[14][16][2])+((Vpk[13][16][1]*Vpk[14][16][1])-(.0039*(
          Vpk[14][16][0]*Wpk[13][16][2])))))+((.0054*(Wpk[13][16][1]*c16))-(.005
          *(Wpk[13][16][2]*s16)))));
        mm[13][15] = (((.55*((Vpk[13][18][2]*Vpk[15][18][2])+((Vpk[13][18][0]*
          Vpk[15][18][0])+(Vpk[13][18][1]*Vpk[15][18][1]))))+((.0016*(
          Wpk[13][18][2]*Wpk[15][18][2]))+((.0005*(Wpk[13][18][0]*Wpk[15][18][0]
          ))+(.002*(Wpk[13][17][1]*Wpk[15][17][1])))))+(((.0054*(Wpk[13][16][1]*
          c16))-(.005*(Wpk[13][16][2]*s16)))-(1.21*((.1378*(Vpk[13][16][2]*c16))
          +((1.521e-5*(Wpk[13][16][2]*s16))+(.1378*(Vpk[13][16][1]*s16)))))));
        mm[13][16] = (((.0012*Wpk[13][15][0])+(.004719*Vpk[13][16][2]))+((.55*((
          Vpk[13][18][2]*Vpk[16][18][2])+((.065*(Vpk[13][18][1]*Wpk[16][18][2]))
          -(.0078*(Vpk[13][18][0]*s18)))))+((.0016*(Wpk[13][18][2]*
          Wpk[16][18][2]))+((.0005*(Wpk[13][18][0]*Wpk[16][18][0]))-(.002*(
          Wpk[13][17][1]*s17))))));
        mm[13][17] = ((.03575*(Vpk[13][18][1]*c18))+((.0016*(Wpk[13][18][2]*c18)
          )-(.0005*(Wpk[13][18][0]*s18))));
        mm[13][18] = ((.002*Wpk[13][17][1])-(.03575*Vpk[13][18][2]));
        mm[13][19] = 0.;
        mm[13][20] = 0.;
        mm[13][21] = 0.;
        mm[13][22] = 0.;
        mm[13][23] = 0.;
        mm[13][24] = 0.;
        mm[13][25] = 0.;
        mm[13][26] = 0.;
        mm[13][27] = 0.;
        mm[13][28] = 0.;
        mm[13][29] = 0.;
        mm[13][30] = 0.;
        mm[13][31] = 0.;
        mm[13][32] = 0.;
        mm[13][33] = 0.;
        mm[13][34] = 0.;
        mm[13][35] = 0.;
        mm[13][36] = 0.;
        mm[14][14] = (.0790606155+(((.0004*(c16*c16))+(1.21*((Vpk[14][16][2]*
          Vpk[14][16][2])+((Vpk[14][16][0]*Vpk[14][16][0])+(Vpk[14][16][1]*
          Vpk[14][16][1])))))+((.55*((Vpk[14][18][2]*Vpk[14][18][2])+((
          Vpk[14][18][0]*Vpk[14][18][0])+(Vpk[14][18][1]*Vpk[14][18][1]))))+((
          .0016*(Wpk[14][18][2]*Wpk[14][18][2]))+((.0005*(Wpk[14][18][0]*
          Wpk[14][18][0]))+(.002*(Wpk[14][17][1]*Wpk[14][17][1])))))));
        mm[14][15] = (.005+(((.0004*(c16*c16))+(1.21*(((.0039*(Vpk[14][16][0]*
          s16))-(.1378*(Vpk[14][16][1]*s16)))-(.1378*(Vpk[14][16][2]*c16)))))+((
          .55*((Vpk[14][18][2]*Vpk[15][18][2])+((Vpk[14][18][0]*Vpk[15][18][0])+
          (Vpk[14][18][1]*Vpk[15][18][1]))))+((.0016*(Wpk[14][18][2]*
          Wpk[15][18][2]))+((.0005*(Wpk[14][18][0]*Wpk[15][18][0]))+(.002*(
          Wpk[14][17][1]*Wpk[15][17][1])))))));
        mm[14][16] = ((.004719*Vpk[14][16][2])+((.55*((Vpk[14][18][2]*
          Vpk[16][18][2])+((.065*(Vpk[14][18][1]*Wpk[16][18][2]))-(.0078*(
          Vpk[14][18][0]*s18)))))+((.0016*(Wpk[14][18][2]*Wpk[16][18][2]))+((
          .0005*(Wpk[14][18][0]*Wpk[16][18][0]))-(.002*(Wpk[14][17][1]*s17))))))
          ;
        mm[14][17] = ((.03575*(Vpk[14][18][1]*c18))+((.0016*(Wpk[14][18][2]*c18)
          )-(.0005*(Wpk[14][18][0]*s18))));
        mm[14][18] = ((.002*Wpk[14][17][1])-(.03575*Vpk[14][18][2]));
        mm[14][19] = 0.;
        mm[14][20] = 0.;
        mm[14][21] = 0.;
        mm[14][22] = 0.;
        mm[14][23] = 0.;
        mm[14][24] = 0.;
        mm[14][25] = 0.;
        mm[14][26] = 0.;
        mm[14][27] = 0.;
        mm[14][28] = 0.;
        mm[14][29] = 0.;
        mm[14][30] = 0.;
        mm[14][31] = 0.;
        mm[14][32] = 0.;
        mm[14][33] = 0.;
        mm[14][34] = 0.;
        mm[14][35] = 0.;
        mm[14][36] = 0.;
        mm[15][15] = (.005+(((.0004*(c16*c16))+(1.21*(.01898884+(
          1.52100000000016e-5*(s16*s16)))))+((.55*((Vpk[15][18][2]*
          Vpk[15][18][2])+((Vpk[15][18][0]*Vpk[15][18][0])+(Vpk[15][18][1]*
          Vpk[15][18][1]))))+((.0016*(Wpk[15][18][2]*Wpk[15][18][2]))+((.0005*(
          Wpk[15][18][0]*Wpk[15][18][0]))+(.002*(Wpk[15][17][1]*Wpk[15][17][1]))
          )))));
        mm[15][16] = (((.55*((Vpk[15][18][2]*Vpk[16][18][2])+((.065*(
          Vpk[15][18][1]*Wpk[16][18][2]))-(.0078*(Vpk[15][18][0]*s18)))))+((
          .0016*(Wpk[15][18][2]*Wpk[16][18][2]))+((.0005*(Wpk[15][18][0]*
          Wpk[16][18][0]))-(.002*(Wpk[15][17][1]*s17)))))-(.0006502782*c16));
        mm[15][17] = ((.03575*(Vpk[15][18][1]*c18))+((.0016*(Wpk[15][18][2]*c18)
          )-(.0005*(Wpk[15][18][0]*s18))));
        mm[15][18] = ((.002*Wpk[15][17][1])-(.03575*Vpk[15][18][2]));
        mm[15][19] = 0.;
        mm[15][20] = 0.;
        mm[15][21] = 0.;
        mm[15][22] = 0.;
        mm[15][23] = 0.;
        mm[15][24] = 0.;
        mm[15][25] = 0.;
        mm[15][26] = 0.;
        mm[15][27] = 0.;
        mm[15][28] = 0.;
        mm[15][29] = 0.;
        mm[15][30] = 0.;
        mm[15][31] = 0.;
        mm[15][32] = 0.;
        mm[15][33] = 0.;
        mm[15][34] = 0.;
        mm[15][35] = 0.;
        mm[15][36] = 0.;
        mm[16][16] = (.0012184041+((.55*((Vpk[16][18][2]*Vpk[16][18][2])+((
          6.084e-5*(s18*s18))+(.004225*(Wpk[16][18][2]*Wpk[16][18][2])))))+((
          .0016*(Wpk[16][18][2]*Wpk[16][18][2]))+((.0005*(Wpk[16][18][0]*
          Wpk[16][18][0]))+(.002*(s17*s17))))));
        mm[16][17] = ((.00232375*(Wpk[16][18][2]*c18))+((.0016*(Wpk[16][18][2]*
          c18))-(.0005*(Wpk[16][18][0]*s18))));
        mm[16][18] = -((.002*s17)+(.03575*Vpk[16][18][2]));
        mm[16][19] = 0.;
        mm[16][20] = 0.;
        mm[16][21] = 0.;
        mm[16][22] = 0.;
        mm[16][23] = 0.;
        mm[16][24] = 0.;
        mm[16][25] = 0.;
        mm[16][26] = 0.;
        mm[16][27] = 0.;
        mm[16][28] = 0.;
        mm[16][29] = 0.;
        mm[16][30] = 0.;
        mm[16][31] = 0.;
        mm[16][32] = 0.;
        mm[16][33] = 0.;
        mm[16][34] = 0.;
        mm[16][35] = 0.;
        mm[16][36] = 0.;
        mm[17][17] = (.0005+(.00342375*(c18*c18)));
        mm[17][18] = 0.;
        mm[17][19] = 0.;
        mm[17][20] = 0.;
        mm[17][21] = 0.;
        mm[17][22] = 0.;
        mm[17][23] = 0.;
        mm[17][24] = 0.;
        mm[17][25] = 0.;
        mm[17][26] = 0.;
        mm[17][27] = 0.;
        mm[17][28] = 0.;
        mm[17][29] = 0.;
        mm[17][30] = 0.;
        mm[17][31] = 0.;
        mm[17][32] = 0.;
        mm[17][33] = 0.;
        mm[17][34] = 0.;
        mm[17][35] = 0.;
        mm[17][36] = 0.;
        mm[18][18] = .00432375;
        mm[18][19] = 0.;
        mm[18][20] = 0.;
        mm[18][21] = 0.;
        mm[18][22] = 0.;
        mm[18][23] = 0.;
        mm[18][24] = 0.;
        mm[18][25] = 0.;
        mm[18][26] = 0.;
        mm[18][27] = 0.;
        mm[18][28] = 0.;
        mm[18][29] = 0.;
        mm[18][30] = 0.;
        mm[18][31] = 0.;
        mm[18][32] = 0.;
        mm[18][33] = 0.;
        mm[18][34] = 0.;
        mm[18][35] = 0.;
        mm[18][36] = 0.;
        temp[0] = (((.02*(c20*c20))+(2.79*(Vpk[19][20][1]*Vpk[19][20][1])))+((
          1.21*((Vpk[19][22][2]*Vpk[19][22][2])+((1.521e-5*(Wpk[19][22][2]*
          Wpk[19][22][2]))+(Vpk[19][22][1]*Vpk[19][22][1]))))+((.005*(
          Wpk[19][22][2]*Wpk[19][22][2]))+((.0012*(Wpk[19][21][0]*Wpk[19][21][0]
          ))+(.0054*(Wpk[19][22][1]*Wpk[19][22][1]))))));
        mm[19][19] = (.005+(((.55*((Vpk[19][24][2]*Vpk[19][24][2])+((
          Vpk[19][24][0]*Vpk[19][24][0])+(Vpk[19][24][1]*Vpk[19][24][1]))))+((
          .0016*(Wpk[19][24][2]*Wpk[19][24][2]))+((.0005*(Wpk[19][24][0]*
          Wpk[19][24][0]))+(.002*(Wpk[19][23][1]*Wpk[19][23][1])))))+temp[0]));
        mm[19][20] = (((.55*((Vpk[19][24][2]*Vpk[20][24][2])+((Vpk[19][24][0]*
          Vpk[20][24][0])+(Vpk[19][24][1]*Vpk[20][24][1]))))+((.0016*(
          Wpk[19][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[19][24][0]*Wpk[20][24][0]
          ))+(.002*(Wpk[19][23][1]*Wpk[20][23][1])))))+((1.21*((Vpk[19][22][2]*
          Vpk[20][22][2])+((Vpk[19][22][1]*Vpk[20][22][1])-(.0039*(
          Vpk[20][22][0]*Wpk[19][22][2])))))+((.0054*(Wpk[19][22][1]*c22))-(.005
          *(Wpk[19][22][2]*s22)))));
        mm[19][21] = (((.55*((Vpk[19][24][2]*Vpk[21][24][2])+((Vpk[19][24][0]*
          Vpk[21][24][0])+(Vpk[19][24][1]*Vpk[21][24][1]))))+((.0016*(
          Wpk[19][24][2]*Wpk[21][24][2]))+((.0005*(Wpk[19][24][0]*Wpk[21][24][0]
          ))+(.002*(Wpk[19][23][1]*Wpk[21][23][1])))))+((1.21*((.1378*(
          Vpk[19][22][2]*c22))+((.1378*(Vpk[19][22][1]*s22))-(1.521e-5*(
          Wpk[19][22][2]*s22)))))+((.0054*(Wpk[19][22][1]*c22))-(.005*(
          Wpk[19][22][2]*s22)))));
        mm[19][22] = (((.0012*Wpk[19][21][0])+(.004719*Vpk[19][22][2]))+((.55*((
          Vpk[19][24][2]*Vpk[22][24][2])-((.0078*(Vpk[19][24][0]*s24))+(.065*(
          Vpk[19][24][1]*Wpk[22][24][2])))))+((.0016*(Wpk[19][24][2]*
          Wpk[22][24][2]))+((.0005*(Wpk[19][24][0]*Wpk[22][24][0]))-(.002*(
          Wpk[19][23][1]*s23))))));
        mm[19][23] = (((.0016*(Wpk[19][24][2]*c24))-(.0005*(Wpk[19][24][0]*s24))
          )-(.03575*(Vpk[19][24][1]*c24)));
        mm[19][24] = ((.002*Wpk[19][23][1])+(.03575*Vpk[19][24][2]));
        mm[19][25] = 0.;
        mm[19][26] = 0.;
        mm[19][27] = 0.;
        mm[19][28] = 0.;
        mm[19][29] = 0.;
        mm[19][30] = 0.;
        mm[19][31] = 0.;
        mm[19][32] = 0.;
        mm[19][33] = 0.;
        mm[19][34] = 0.;
        mm[19][35] = 0.;
        mm[19][36] = 0.;
        mm[20][20] = (.0790606155+(((.0004*(c22*c22))+(1.21*((Vpk[20][22][2]*
          Vpk[20][22][2])+((Vpk[20][22][0]*Vpk[20][22][0])+(Vpk[20][22][1]*
          Vpk[20][22][1])))))+((.55*((Vpk[20][24][2]*Vpk[20][24][2])+((
          Vpk[20][24][0]*Vpk[20][24][0])+(Vpk[20][24][1]*Vpk[20][24][1]))))+((
          .0016*(Wpk[20][24][2]*Wpk[20][24][2]))+((.0005*(Wpk[20][24][0]*
          Wpk[20][24][0]))+(.002*(Wpk[20][23][1]*Wpk[20][23][1])))))));
        mm[20][21] = (.005+(((.0004*(c22*c22))+(1.21*((.1378*(Vpk[20][22][2]*c22
          ))+((.0039*(Vpk[20][22][0]*s22))+(.1378*(Vpk[20][22][1]*s22))))))+((
          .55*((Vpk[20][24][2]*Vpk[21][24][2])+((Vpk[20][24][0]*Vpk[21][24][0])+
          (Vpk[20][24][1]*Vpk[21][24][1]))))+((.0016*(Wpk[20][24][2]*
          Wpk[21][24][2]))+((.0005*(Wpk[20][24][0]*Wpk[21][24][0]))+(.002*(
          Wpk[20][23][1]*Wpk[21][23][1])))))));
        mm[20][22] = ((.004719*Vpk[20][22][2])+((.55*((Vpk[20][24][2]*
          Vpk[22][24][2])-((.0078*(Vpk[20][24][0]*s24))+(.065*(Vpk[20][24][1]*
          Wpk[22][24][2])))))+((.0016*(Wpk[20][24][2]*Wpk[22][24][2]))+((.0005*(
          Wpk[20][24][0]*Wpk[22][24][0]))-(.002*(Wpk[20][23][1]*s23))))));
        mm[20][23] = (((.0016*(Wpk[20][24][2]*c24))-(.0005*(Wpk[20][24][0]*s24))
          )-(.03575*(Vpk[20][24][1]*c24)));
        mm[20][24] = ((.002*Wpk[20][23][1])+(.03575*Vpk[20][24][2]));
        mm[20][25] = 0.;
        mm[20][26] = 0.;
        mm[20][27] = 0.;
        mm[20][28] = 0.;
        mm[20][29] = 0.;
        mm[20][30] = 0.;
        mm[20][31] = 0.;
        mm[20][32] = 0.;
        mm[20][33] = 0.;
        mm[20][34] = 0.;
        mm[20][35] = 0.;
        mm[20][36] = 0.;
        mm[21][21] = (.005+(((.0004*(c22*c22))+(1.21*(.01898884+(
          1.52100000000016e-5*(s22*s22)))))+((.55*((Vpk[21][24][2]*
          Vpk[21][24][2])+((Vpk[21][24][0]*Vpk[21][24][0])+(Vpk[21][24][1]*
          Vpk[21][24][1]))))+((.0016*(Wpk[21][24][2]*Wpk[21][24][2]))+((.0005*(
          Wpk[21][24][0]*Wpk[21][24][0]))+(.002*(Wpk[21][23][1]*Wpk[21][23][1]))
          )))));
        mm[21][22] = ((.0006502782*c22)+((.55*((Vpk[21][24][2]*Vpk[22][24][2])-(
          (.0078*(Vpk[21][24][0]*s24))+(.065*(Vpk[21][24][1]*Wpk[22][24][2])))))
          +((.0016*(Wpk[21][24][2]*Wpk[22][24][2]))+((.0005*(Wpk[21][24][0]*
          Wpk[22][24][0]))-(.002*(Wpk[21][23][1]*s23))))));
        mm[21][23] = (((.0016*(Wpk[21][24][2]*c24))-(.0005*(Wpk[21][24][0]*s24))
          )-(.03575*(Vpk[21][24][1]*c24)));
        mm[21][24] = ((.002*Wpk[21][23][1])+(.03575*Vpk[21][24][2]));
        mm[21][25] = 0.;
        mm[21][26] = 0.;
        mm[21][27] = 0.;
        mm[21][28] = 0.;
        mm[21][29] = 0.;
        mm[21][30] = 0.;
        mm[21][31] = 0.;
        mm[21][32] = 0.;
        mm[21][33] = 0.;
        mm[21][34] = 0.;
        mm[21][35] = 0.;
        mm[21][36] = 0.;
        mm[22][22] = (.0012184041+((.55*((Vpk[22][24][2]*Vpk[22][24][2])+((
          6.084e-5*(s24*s24))+(.004225*(Wpk[22][24][2]*Wpk[22][24][2])))))+((
          .0016*(Wpk[22][24][2]*Wpk[22][24][2]))+((.0005*(Wpk[22][24][0]*
          Wpk[22][24][0]))+(.002*(s23*s23))))));
        mm[22][23] = ((.00232375*(Wpk[22][24][2]*c24))+((.0016*(Wpk[22][24][2]*
          c24))-(.0005*(Wpk[22][24][0]*s24))));
        mm[22][24] = ((.03575*Vpk[22][24][2])-(.002*s23));
        mm[22][25] = 0.;
        mm[22][26] = 0.;
        mm[22][27] = 0.;
        mm[22][28] = 0.;
        mm[22][29] = 0.;
        mm[22][30] = 0.;
        mm[22][31] = 0.;
        mm[22][32] = 0.;
        mm[22][33] = 0.;
        mm[22][34] = 0.;
        mm[22][35] = 0.;
        mm[22][36] = 0.;
        mm[23][23] = (.0005+(.00342375*(c24*c24)));
        mm[23][24] = 0.;
        mm[23][25] = 0.;
        mm[23][26] = 0.;
        mm[23][27] = 0.;
        mm[23][28] = 0.;
        mm[23][29] = 0.;
        mm[23][30] = 0.;
        mm[23][31] = 0.;
        mm[23][32] = 0.;
        mm[23][33] = 0.;
        mm[23][34] = 0.;
        mm[23][35] = 0.;
        mm[23][36] = 0.;
        mm[24][24] = .00432375;
        mm[24][25] = 0.;
        mm[24][26] = 0.;
        mm[24][27] = 0.;
        mm[24][28] = 0.;
        mm[24][29] = 0.;
        mm[24][30] = 0.;
        mm[24][31] = 0.;
        mm[24][32] = 0.;
        mm[24][33] = 0.;
        mm[24][34] = 0.;
        mm[24][35] = 0.;
        mm[24][36] = 0.;
        temp[0] = ((4.16*((Vpk[25][28][2]*Vpk[25][28][2])+((Vpk[25][28][0]*
          Vpk[25][28][0])+(Vpk[25][28][1]*Vpk[25][28][1]))))+((.055*(
          Wpk[25][28][2]*Wpk[25][28][2]))+((.007*(Wpk[25][28][1]*Wpk[25][28][1])
          )+(.056*(Wpk[25][27][0]*Wpk[25][27][0])))));
        temp[1] = ((1.34*((Vpk[25][30][2]*Vpk[25][30][2])+((Vpk[25][30][0]*
          Vpk[25][30][0])+(Vpk[25][30][1]*Vpk[25][30][1]))))+((.0018*(
          Wpk[25][29][2]*Wpk[25][29][2]))+((.007*(Wpk[25][30][1]*Wpk[25][30][1])
          )+(.0075*(Wpk[25][30][0]*Wpk[25][30][0])))));
        mm[25][25] = (temp[1]+(temp[0]+((8.35*((Vpk[25][27][2]*Vpk[25][27][2])+(
          (Vpk[25][27][0]*Vpk[25][27][0])+(Vpk[25][27][1]*Vpk[25][27][1]))))+((
          .15*(Wpk[25][27][2]*Wpk[25][27][2]))+((.025*(s26*s26))+(.16*(
          Wpk[25][27][0]*Wpk[25][27][0])))))));
        temp[0] = (((4.16*((Vpk[25][28][2]*Vpk[26][28][2])+((Vpk[25][28][0]*
          Vpk[26][28][0])+(Vpk[25][28][1]*Vpk[26][28][1]))))+((.055*(
          Wpk[25][28][2]*Wpk[26][28][2]))+((.007*(Wpk[25][28][1]*Wpk[26][28][1])
          )-(.056*(Wpk[25][27][0]*s27)))))+((8.35*((.2379*(Vpk[25][27][2]*s27))+
          ((.2379*(Vpk[25][27][0]*c27))+(Vpk[25][27][1]*Vpk[26][27][1]))))+((.15
          *(Wpk[25][27][2]*c27))-(.16*(Wpk[25][27][0]*s27)))));
        mm[25][26] = (((1.34*((Vpk[25][30][2]*Vpk[26][30][2])+((Vpk[25][30][0]*
          Vpk[26][30][0])+(Vpk[25][30][1]*Vpk[26][30][1]))))+((.0018*(
          Wpk[25][29][2]*Wpk[26][29][2]))+((.007*(Wpk[25][30][1]*Wpk[26][30][1])
          )+(.0075*(Wpk[25][30][0]*Wpk[26][30][0])))))+temp[0]);
        temp[0] = ((1.34*((Vpk[25][30][2]*Vpk[27][30][2])+((Vpk[25][30][0]*
          Vpk[27][30][0])+(Vpk[25][30][1]*Vpk[27][30][1]))))+((.0018*(
          Wpk[25][29][2]*Wpk[27][29][2]))+((.007*(Wpk[25][30][1]*Wpk[27][30][1])
          )+(.0075*(Wpk[25][30][0]*Wpk[27][30][0])))));
        mm[25][27] = (temp[0]+(((4.16*((.0416*(Vpk[25][28][2]*c28))+((.0416*(
          Vpk[25][28][1]*s28))+(Vpk[25][28][0]*Vpk[27][28][0]))))+((.007*(
          Wpk[25][28][1]*c28))-(.055*(Wpk[25][28][2]*s28))))+((8.35*((.0143*
          Vpk[25][27][0])+(.0169*Vpk[25][27][2])))-(.025*s26))));
        mm[25][28] = (((.056*Wpk[25][27][0])+(4.16*((.0039*Vpk[25][28][1])-(
          .2158*Vpk[25][28][2]))))+((1.34*((Vpk[25][30][2]*Vpk[28][30][2])+((
          Vpk[25][30][0]*Vpk[28][30][0])+(Vpk[25][30][1]*Vpk[28][30][1]))))+((
          .0075*(Wpk[25][30][0]*c30))-(.007*(Wpk[25][30][1]*s30)))));
        mm[25][29] = (((.0075*(Wpk[25][30][0]*c30))-(.007*(Wpk[25][30][1]*s30)))
          -(1.34*((.039*((Vpk[25][30][0]*s30)+(Vpk[25][30][1]*c30)))+(.0442*(
          Vpk[25][30][2]*c30)))));
        mm[25][30] = ((.0018*Wpk[25][29][2])+(.059228*Vpk[25][30][0]));
        mm[25][31] = 0.;
        mm[25][32] = 0.;
        mm[25][33] = 0.;
        mm[25][34] = 0.;
        mm[25][35] = 0.;
        mm[25][36] = 0.;
        temp[0] = (((.01*(s27*s27))+(8.35*((.05659641*(s27*s27))+((.05659641*(
          c27*c27))+(Vpk[26][27][1]*Vpk[26][27][1])))))+((4.16*((Vpk[26][28][2]*
          Vpk[26][28][2])+((Vpk[26][28][0]*Vpk[26][28][0])+(Vpk[26][28][1]*
          Vpk[26][28][1]))))+((.055*(Wpk[26][28][2]*Wpk[26][28][2]))+((.007*(
          Wpk[26][28][1]*Wpk[26][28][1]))+(.056*(s27*s27))))));
        mm[26][26] = (.15+(((1.34*((Vpk[26][30][2]*Vpk[26][30][2])+((
          Vpk[26][30][0]*Vpk[26][30][0])+(Vpk[26][30][1]*Vpk[26][30][1]))))+((
          .0018*(Wpk[26][29][2]*Wpk[26][29][2]))+((.007*(Wpk[26][30][1]*
          Wpk[26][30][1]))+(.0075*(Wpk[26][30][0]*Wpk[26][30][0])))))+temp[0]));
        temp[0] = ((1.34*((Vpk[26][30][2]*Vpk[27][30][2])+((Vpk[26][30][0]*
          Vpk[27][30][0])+(Vpk[26][30][1]*Vpk[27][30][1]))))+((.0018*(
          Wpk[26][29][2]*Wpk[27][29][2]))+((.007*(Wpk[26][30][1]*Wpk[27][30][1])
          )+(.0075*(Wpk[26][30][0]*Wpk[27][30][0])))));
        mm[26][27] = (temp[0]+((8.35*((.00340197*c27)+(.00402051*s27)))+((4.16*(
          (.0416*(Vpk[26][28][2]*c28))+((.0416*(Vpk[26][28][1]*s28))+(
          Vpk[26][28][0]*Vpk[27][28][0]))))+((.007*(Wpk[26][28][1]*c28))-(.055*(
          Wpk[26][28][2]*s28))))));
        mm[26][28] = (((1.34*((Vpk[26][30][2]*Vpk[28][30][2])+((Vpk[26][30][0]*
          Vpk[28][30][0])+(Vpk[26][30][1]*Vpk[28][30][1]))))+((.0075*(
          Wpk[26][30][0]*c30))-(.007*(Wpk[26][30][1]*s30))))+((4.16*((.0039*
          Vpk[26][28][1])-(.2158*Vpk[26][28][2])))-(.056*s27)));
        mm[26][29] = (((.0075*(Wpk[26][30][0]*c30))-(.007*(Wpk[26][30][1]*s30)))
          -(1.34*((.039*((Vpk[26][30][0]*s30)+(Vpk[26][30][1]*c30)))+(.0442*(
          Vpk[26][30][2]*c30)))));
        mm[26][30] = ((.0018*Wpk[26][29][2])+(.059228*Vpk[26][30][0]));
        mm[26][31] = 0.;
        mm[26][32] = 0.;
        mm[26][33] = 0.;
        mm[26][34] = 0.;
        mm[26][35] = 0.;
        mm[26][36] = 0.;
        mm[27][27] = (.036092335+(((.048*(s28*s28))+(4.16*((.00173056*(c28*c28))
          +((.00173056*(s28*s28))+(Vpk[27][28][0]*Vpk[27][28][0])))))+((1.34*((
          Vpk[27][30][2]*Vpk[27][30][2])+((Vpk[27][30][0]*Vpk[27][30][0])+(
          Vpk[27][30][1]*Vpk[27][30][1]))))+((.0018*(Wpk[27][29][2]*
          Wpk[27][29][2]))+((.007*(Wpk[27][30][1]*Wpk[27][30][1]))+(.0075*(
          Wpk[27][30][0]*Wpk[27][30][0])))))));
        mm[27][28] = ((4.16*((.00016224*s28)-(.00897728*c28)))+((1.34*((
          Vpk[27][30][2]*Vpk[28][30][2])+((Vpk[27][30][0]*Vpk[28][30][0])+(
          Vpk[27][30][1]*Vpk[28][30][1]))))+((.0075*(Wpk[27][30][0]*c30))-(.007*
          (Wpk[27][30][1]*s30)))));
        mm[27][29] = (((.0075*(Wpk[27][30][0]*c30))-(.007*(Wpk[27][30][1]*s30)))
          -(1.34*((.039*((Vpk[27][30][0]*s30)+(Vpk[27][30][1]*c30)))+(.0442*(
          Vpk[27][30][2]*c30)))));
        mm[27][30] = ((.0018*Wpk[27][29][2])+(.059228*Vpk[27][30][0]));
        mm[27][31] = 0.;
        mm[27][32] = 0.;
        mm[27][33] = 0.;
        mm[27][34] = 0.;
        mm[27][35] = 0.;
        mm[27][36] = 0.;
        mm[28][28] = (.256792976+((.0005*(c30*c30))+(1.34*((Vpk[28][30][2]*
          Vpk[28][30][2])+((Vpk[28][30][0]*Vpk[28][30][0])+(Vpk[28][30][1]*
          Vpk[28][30][1]))))));
        mm[28][29] = (.007+((.0005*(c30*c30))-(1.34*((.039*((Vpk[28][30][0]*s30)
          +(Vpk[28][30][1]*c30)))+(.0442*(Vpk[28][30][2]*c30))))));
        mm[28][30] = (.059228*Vpk[28][30][0]);
        mm[28][31] = 0.;
        mm[28][32] = 0.;
        mm[28][33] = 0.;
        mm[28][34] = 0.;
        mm[28][35] = 0.;
        mm[28][36] = 0.;
        mm[29][29] = (.007+((.0005*(c30*c30))+(1.34*(.001521+(.00195364*(c30*c30
          ))))));
        mm[29][30] = -(.002309892*s30);
        mm[29][31] = 0.;
        mm[29][32] = 0.;
        mm[29][33] = 0.;
        mm[29][34] = 0.;
        mm[29][35] = 0.;
        mm[29][36] = 0.;
        mm[30][30] = .0044178776;
        mm[30][31] = 0.;
        mm[30][32] = 0.;
        mm[30][33] = 0.;
        mm[30][34] = 0.;
        mm[30][35] = 0.;
        mm[30][36] = 0.;
        temp[0] = ((4.16*((Vpk[31][34][2]*Vpk[31][34][2])+((Vpk[31][34][0]*
          Vpk[31][34][0])+(Vpk[31][34][1]*Vpk[31][34][1]))))+((.055*(
          Wpk[31][34][2]*Wpk[31][34][2]))+((.007*(Wpk[31][34][1]*Wpk[31][34][1])
          )+(.056*(Wpk[31][33][0]*Wpk[31][33][0])))));
        temp[1] = ((1.34*((Vpk[31][36][2]*Vpk[31][36][2])+((Vpk[31][36][0]*
          Vpk[31][36][0])+(Vpk[31][36][1]*Vpk[31][36][1]))))+((.0018*(
          Wpk[31][35][2]*Wpk[31][35][2]))+((.007*(Wpk[31][36][1]*Wpk[31][36][1])
          )+(.0075*(Wpk[31][36][0]*Wpk[31][36][0])))));
        mm[31][31] = (temp[1]+(temp[0]+((8.35*((Vpk[31][33][2]*Vpk[31][33][2])+(
          (Vpk[31][33][0]*Vpk[31][33][0])+(Vpk[31][33][1]*Vpk[31][33][1]))))+((
          .15*(Wpk[31][33][2]*Wpk[31][33][2]))+((.025*(s32*s32))+(.16*(
          Wpk[31][33][0]*Wpk[31][33][0])))))));
        temp[0] = (((4.16*((Vpk[31][34][2]*Vpk[32][34][2])+((Vpk[31][34][0]*
          Vpk[32][34][0])+(Vpk[31][34][1]*Vpk[32][34][1]))))+((.055*(
          Wpk[31][34][2]*Wpk[32][34][2]))+((.007*(Wpk[31][34][1]*Wpk[32][34][1])
          )-(.056*(Wpk[31][33][0]*s33)))))+((8.35*((.2379*(Vpk[31][33][2]*s33))+
          ((.2379*(Vpk[31][33][0]*c33))+(Vpk[31][33][1]*Vpk[32][33][1]))))+((.15
          *(Wpk[31][33][2]*c33))-(.16*(Wpk[31][33][0]*s33)))));
        mm[31][32] = (((1.34*((Vpk[31][36][2]*Vpk[32][36][2])+((Vpk[31][36][0]*
          Vpk[32][36][0])+(Vpk[31][36][1]*Vpk[32][36][1]))))+((.0018*(
          Wpk[31][35][2]*Wpk[32][35][2]))+((.007*(Wpk[31][36][1]*Wpk[32][36][1])
          )+(.0075*(Wpk[31][36][0]*Wpk[32][36][0])))))+temp[0]);
        temp[0] = ((1.34*((Vpk[31][36][2]*Vpk[33][36][2])+((Vpk[31][36][0]*
          Vpk[33][36][0])+(Vpk[31][36][1]*Vpk[33][36][1]))))+((.0018*(
          Wpk[31][35][2]*Wpk[33][35][2]))+((.007*(Wpk[31][36][1]*Wpk[33][36][1])
          )+(.0075*(Wpk[31][36][0]*Wpk[33][36][0])))));
        mm[31][33] = (temp[0]+(((4.16*(((Vpk[31][34][0]*Vpk[33][34][0])-(.0416*(
          Vpk[31][34][1]*s34)))-(.0416*(Vpk[31][34][2]*c34))))+((.007*(
          Wpk[31][34][1]*c34))-(.055*(Wpk[31][34][2]*s34))))+((8.35*((.0143*
          Vpk[31][33][0])-(.0169*Vpk[31][33][2])))-(.025*s32))));
        mm[31][34] = (((.056*Wpk[31][33][0])+(4.16*((.0039*Vpk[31][34][1])-(
          .2158*Vpk[31][34][2]))))+((1.34*((Vpk[31][36][2]*Vpk[34][36][2])+((
          Vpk[31][36][0]*Vpk[34][36][0])+(Vpk[31][36][1]*Vpk[34][36][1]))))+((
          .0075*(Wpk[31][36][0]*c36))-(.007*(Wpk[31][36][1]*s36)))));
        mm[31][35] = (((.0075*(Wpk[31][36][0]*c36))-(.007*(Wpk[31][36][1]*s36)))
          -(1.34*((.039*((Vpk[31][36][0]*s36)+(Vpk[31][36][1]*c36)))+(.0442*(
          Vpk[31][36][2]*c36)))));
        mm[31][36] = ((.0018*Wpk[31][35][2])+(.059228*Vpk[31][36][0]));
        temp[0] = (((.01*(s33*s33))+(8.35*((.05659641*(s33*s33))+((.05659641*(
          c33*c33))+(Vpk[32][33][1]*Vpk[32][33][1])))))+((4.16*((Vpk[32][34][2]*
          Vpk[32][34][2])+((Vpk[32][34][0]*Vpk[32][34][0])+(Vpk[32][34][1]*
          Vpk[32][34][1]))))+((.055*(Wpk[32][34][2]*Wpk[32][34][2]))+((.007*(
          Wpk[32][34][1]*Wpk[32][34][1]))+(.056*(s33*s33))))));
        mm[32][32] = (.15+(((1.34*((Vpk[32][36][2]*Vpk[32][36][2])+((
          Vpk[32][36][0]*Vpk[32][36][0])+(Vpk[32][36][1]*Vpk[32][36][1]))))+((
          .0018*(Wpk[32][35][2]*Wpk[32][35][2]))+((.007*(Wpk[32][36][1]*
          Wpk[32][36][1]))+(.0075*(Wpk[32][36][0]*Wpk[32][36][0])))))+temp[0]));
        temp[0] = ((1.34*((Vpk[32][36][2]*Vpk[33][36][2])+((Vpk[32][36][0]*
          Vpk[33][36][0])+(Vpk[32][36][1]*Vpk[33][36][1]))))+((.0018*(
          Wpk[32][35][2]*Wpk[33][35][2]))+((.007*(Wpk[32][36][1]*Wpk[33][36][1])
          )+(.0075*(Wpk[32][36][0]*Wpk[33][36][0])))));
        mm[32][33] = (temp[0]+((8.35*((.00340197*c33)-(.00402051*s33)))+((4.16*(
          ((Vpk[32][34][0]*Vpk[33][34][0])-(.0416*(Vpk[32][34][1]*s34)))-(.0416*
          (Vpk[32][34][2]*c34))))+((.007*(Wpk[32][34][1]*c34))-(.055*(
          Wpk[32][34][2]*s34))))));
        mm[32][34] = (((1.34*((Vpk[32][36][2]*Vpk[34][36][2])+((Vpk[32][36][0]*
          Vpk[34][36][0])+(Vpk[32][36][1]*Vpk[34][36][1]))))+((.0075*(
          Wpk[32][36][0]*c36))-(.007*(Wpk[32][36][1]*s36))))+((4.16*((.0039*
          Vpk[32][34][1])-(.2158*Vpk[32][34][2])))-(.056*s33)));
        mm[32][35] = (((.0075*(Wpk[32][36][0]*c36))-(.007*(Wpk[32][36][1]*s36)))
          -(1.34*((.039*((Vpk[32][36][0]*s36)+(Vpk[32][36][1]*c36)))+(.0442*(
          Vpk[32][36][2]*c36)))));
        mm[32][36] = ((.0018*Wpk[32][35][2])+(.059228*Vpk[32][36][0]));
        mm[33][33] = (.036092335+(((.048*(s34*s34))+(4.16*((.00173056*(c34*c34))
          +((.00173056*(s34*s34))+(Vpk[33][34][0]*Vpk[33][34][0])))))+((1.34*((
          Vpk[33][36][2]*Vpk[33][36][2])+((Vpk[33][36][0]*Vpk[33][36][0])+(
          Vpk[33][36][1]*Vpk[33][36][1]))))+((.0018*(Wpk[33][35][2]*
          Wpk[33][35][2]))+((.007*(Wpk[33][36][1]*Wpk[33][36][1]))+(.0075*(
          Wpk[33][36][0]*Wpk[33][36][0])))))));
        mm[33][34] = ((4.16*((.00897728*c34)-(.00016224*s34)))+((1.34*((
          Vpk[33][36][2]*Vpk[34][36][2])+((Vpk[33][36][0]*Vpk[34][36][0])+(
          Vpk[33][36][1]*Vpk[34][36][1]))))+((.0075*(Wpk[33][36][0]*c36))-(.007*
          (Wpk[33][36][1]*s36)))));
        mm[33][35] = (((.0075*(Wpk[33][36][0]*c36))-(.007*(Wpk[33][36][1]*s36)))
          -(1.34*((.039*((Vpk[33][36][0]*s36)+(Vpk[33][36][1]*c36)))+(.0442*(
          Vpk[33][36][2]*c36)))));
        mm[33][36] = ((.0018*Wpk[33][35][2])+(.059228*Vpk[33][36][0]));
        mm[34][34] = (.256792976+((.0005*(c36*c36))+(1.34*((Vpk[34][36][2]*
          Vpk[34][36][2])+((Vpk[34][36][0]*Vpk[34][36][0])+(Vpk[34][36][1]*
          Vpk[34][36][1]))))));
        mm[34][35] = (.007+((.0005*(c36*c36))-(1.34*((.039*((Vpk[34][36][0]*s36)
          +(Vpk[34][36][1]*c36)))+(.0442*(Vpk[34][36][2]*c36))))));
        mm[34][36] = (.059228*Vpk[34][36][0]);
        mm[35][35] = (.007+((.0005*(c36*c36))+(1.34*(.001521+(.00195364*(c36*c36
          ))))));
        mm[35][36] = -(.002309892*s36);
        mm[36][36] = .0044178776;
/*
Check for singular mass matrix
*/
        for (i = 0; i < 37; i++) {
            if (mm[i][i] < 1e-13) {
                skel18seterr(routine,47);
            }
        }
        mmflg = 1;
    }
/*
 Used 13.24 seconds CPU time,
 114688 additional bytes of memory.
 Equations contain 4147 adds/subtracts/negates
                   7146 multiplies
                      0 divides
                   1049 assignments
*/
}

void skel18dommldu(int routine)
{
    int i;

    if (mmlduflg == 0) {
        skel18domm(routine);
/*
Numerically decompose the mass matrix
*/
        skel18ldudcomp(37,37,mmap,1e-13,(double *) workss,works,(double *) mm,(double *) (double *) mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 37; i++) {
            if (mdi[i] <= 1e-13) {
                skel18seterr(routine,47);
            }
        }
        mmlduflg = 1;
    }
}

void skel18lhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    skel18dommldu(routine);
    skel18dofs0();
}

void skel18massmat(double (*mmat)[37])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(57,23);
        return;
    }
    skel18domm(57);
    for (i = 0; i < 37; i++) {
        for (j = i; j <= 36; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void skel18frcmat(double *fmat)
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(58,23);
        return;
    }
    skel18dofs0();
    for (i = 0; i < 37; i++) {
        fmat[i] = fs0[i];
    }
}

void skel18mfrc(double *imult)
{

}

void skel18equivht(double *tau)
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[37][3],tstareq[37][3];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    skel18dovpk();
    temp[0] = (((ufk[3][2]*Vpk[0][12][2])+((ufk[3][0]*Vpk[0][11][0])+(ufk[3][1]*
      Vpk[0][12][1])))+(((ufk[2][2]*Vpk[0][11][2])+((ufk[2][0]*Vpk[0][11][0])+(
      ufk[2][1]*Vpk[0][10][1])))+(((Cik[3][0][2]*ufk[0][2])+((Cik[3][0][0]*
      ufk[0][0])+(Cik[3][0][1]*ufk[0][1])))+((ufk[1][2]*Vpk[0][8][2])+((
      ufk[1][0]*Vpk[0][8][0])+(ufk[1][1]*Vpk[0][7][1]))))));
    temp[1] = (((ufk[7][2]*Vpk[0][20][2])+((ufk[7][0]*Vpk[0][20][0])+(ufk[7][1]*
      Vpk[0][19][1])))+(((ufk[6][2]*Vpk[0][18][2])+((ufk[6][0]*Vpk[0][18][0])+(
      ufk[6][1]*Vpk[0][17][1])))+(((ufk[5][2]*Vpk[0][16][2])+((ufk[5][0]*
      Vpk[0][15][0])+(ufk[5][1]*Vpk[0][16][1])))+(((ufk[4][2]*Vpk[0][14][2])+((
      ufk[4][0]*Vpk[0][14][0])+(ufk[4][1]*Vpk[0][13][1])))+temp[0]))));
    temp[2] = (((ufk[11][2]*Vpk[0][28][2])+((ufk[11][0]*Vpk[0][27][0])+(
      ufk[11][1]*Vpk[0][28][1])))+(((ufk[10][2]*Vpk[0][27][2])+((ufk[10][0]*
      Vpk[0][27][0])+(ufk[10][1]*Vpk[0][26][1])))+(((ufk[9][2]*Vpk[0][24][2])+((
      ufk[9][0]*Vpk[0][24][0])+(ufk[9][1]*Vpk[0][23][1])))+(((ufk[8][2]*
      Vpk[0][22][2])+((ufk[8][0]*Vpk[0][21][0])+(ufk[8][1]*Vpk[0][22][1])))+
      temp[1]))));
    tau[0] = (utau[0]+(((ufk[15][2]*Vpk[0][35][2])+((ufk[15][0]*Vpk[0][36][0])+(
      ufk[15][1]*Vpk[0][36][1])))+(((ufk[14][2]*Vpk[0][34][2])+((ufk[14][0]*
      Vpk[0][33][0])+(ufk[14][1]*Vpk[0][34][1])))+(((ufk[13][2]*Vpk[0][33][2])+(
      (ufk[13][0]*Vpk[0][33][0])+(ufk[13][1]*Vpk[0][32][1])))+(((ufk[12][2]*
      Vpk[0][29][2])+((ufk[12][0]*Vpk[0][30][0])+(ufk[12][1]*Vpk[0][30][1])))+
      temp[2])))));
    temp[0] = (((ufk[3][2]*Vpk[1][12][2])+((ufk[3][0]*Vpk[1][11][0])+(ufk[3][1]*
      Vpk[1][12][1])))+(((ufk[2][2]*Vpk[1][11][2])+((ufk[2][0]*Vpk[1][11][0])+(
      ufk[2][1]*Vpk[1][10][1])))+(((Cik[3][1][2]*ufk[0][2])+((Cik[3][1][0]*
      ufk[0][0])+(Cik[3][1][1]*ufk[0][1])))+((ufk[1][2]*Vpk[1][8][2])+((
      ufk[1][0]*Vpk[1][8][0])+(ufk[1][1]*Vpk[1][7][1]))))));
    temp[1] = (((ufk[7][2]*Vpk[1][20][2])+((ufk[7][0]*Vpk[1][20][0])+(ufk[7][1]*
      Vpk[1][19][1])))+(((ufk[6][2]*Vpk[1][18][2])+((ufk[6][0]*Vpk[1][18][0])+(
      ufk[6][1]*Vpk[1][17][1])))+(((ufk[5][2]*Vpk[1][16][2])+((ufk[5][0]*
      Vpk[1][15][0])+(ufk[5][1]*Vpk[1][16][1])))+(((ufk[4][2]*Vpk[1][14][2])+((
      ufk[4][0]*Vpk[1][14][0])+(ufk[4][1]*Vpk[1][13][1])))+temp[0]))));
    temp[2] = (((ufk[11][2]*Vpk[1][28][2])+((ufk[11][0]*Vpk[1][27][0])+(
      ufk[11][1]*Vpk[1][28][1])))+(((ufk[10][2]*Vpk[1][27][2])+((ufk[10][0]*
      Vpk[1][27][0])+(ufk[10][1]*Vpk[1][26][1])))+(((ufk[9][2]*Vpk[1][24][2])+((
      ufk[9][0]*Vpk[1][24][0])+(ufk[9][1]*Vpk[1][23][1])))+(((ufk[8][2]*
      Vpk[1][22][2])+((ufk[8][0]*Vpk[1][21][0])+(ufk[8][1]*Vpk[1][22][1])))+
      temp[1]))));
    tau[1] = (utau[1]+(((ufk[15][2]*Vpk[1][35][2])+((ufk[15][0]*Vpk[1][36][0])+(
      ufk[15][1]*Vpk[1][36][1])))+(((ufk[14][2]*Vpk[1][34][2])+((ufk[14][0]*
      Vpk[1][33][0])+(ufk[14][1]*Vpk[1][34][1])))+(((ufk[13][2]*Vpk[1][33][2])+(
      (ufk[13][0]*Vpk[1][33][0])+(ufk[13][1]*Vpk[1][32][1])))+(((ufk[12][2]*
      Vpk[1][29][2])+((ufk[12][0]*Vpk[1][30][0])+(ufk[12][1]*Vpk[1][30][1])))+
      temp[2])))));
    temp[0] = (((ufk[3][2]*Vpk[2][12][2])+((ufk[3][0]*Vpk[2][11][0])+(ufk[3][1]*
      Vpk[2][12][1])))+(((ufk[2][2]*Vpk[2][11][2])+((ufk[2][0]*Vpk[2][11][0])+(
      ufk[2][1]*Vpk[2][10][1])))+(((Cik[3][2][2]*ufk[0][2])+((Cik[3][2][0]*
      ufk[0][0])+(Cik[3][2][1]*ufk[0][1])))+((ufk[1][2]*Vpk[2][8][2])+((
      ufk[1][0]*Vpk[2][8][0])+(ufk[1][1]*Vpk[2][7][1]))))));
    temp[1] = (((ufk[7][2]*Vpk[2][20][2])+((ufk[7][0]*Vpk[2][20][0])+(ufk[7][1]*
      Vpk[2][19][1])))+(((ufk[6][2]*Vpk[2][18][2])+((ufk[6][0]*Vpk[2][18][0])+(
      ufk[6][1]*Vpk[2][17][1])))+(((ufk[5][2]*Vpk[2][16][2])+((ufk[5][0]*
      Vpk[2][15][0])+(ufk[5][1]*Vpk[2][16][1])))+(((ufk[4][2]*Vpk[2][14][2])+((
      ufk[4][0]*Vpk[2][14][0])+(ufk[4][1]*Vpk[2][13][1])))+temp[0]))));
    temp[2] = (((ufk[11][2]*Vpk[2][28][2])+((ufk[11][0]*Vpk[2][27][0])+(
      ufk[11][1]*Vpk[2][28][1])))+(((ufk[10][2]*Vpk[2][27][2])+((ufk[10][0]*
      Vpk[2][27][0])+(ufk[10][1]*Vpk[2][26][1])))+(((ufk[9][2]*Vpk[2][24][2])+((
      ufk[9][0]*Vpk[2][24][0])+(ufk[9][1]*Vpk[2][23][1])))+(((ufk[8][2]*
      Vpk[2][22][2])+((ufk[8][0]*Vpk[2][21][0])+(ufk[8][1]*Vpk[2][22][1])))+
      temp[1]))));
    tau[2] = (utau[2]+(((ufk[15][2]*Vpk[2][35][2])+((ufk[15][0]*Vpk[2][36][0])+(
      ufk[15][1]*Vpk[2][36][1])))+(((ufk[14][2]*Vpk[2][34][2])+((ufk[14][0]*
      Vpk[2][33][0])+(ufk[14][1]*Vpk[2][34][1])))+(((ufk[13][2]*Vpk[2][33][2])+(
      (ufk[13][0]*Vpk[2][33][0])+(ufk[13][1]*Vpk[2][32][1])))+(((ufk[12][2]*
      Vpk[2][29][2])+((ufk[12][0]*Vpk[2][30][0])+(ufk[12][1]*Vpk[2][30][1])))+
      temp[2])))));
    temp[0] = (((((.1206*ufk[0][2])-(.05*ufk[0][1]))-utk[0][0])+((((utk[1][1]*s7
      )-(utk[1][0]*Wpk[3][8][0]))-(utk[1][2]*Wpk[3][8][2]))-((.14625*(ufk[1][2]*
      Wpk[3][8][0]))+((.0351*(ufk[1][1]*Wpk[3][8][0]))+(ufk[1][0]*Vpk[3][8][0]))
      )))-(((ufk[2][2]*Vpk[3][11][2])+((ufk[2][0]*Vpk[3][11][0])+(ufk[2][1]*
      Vpk[3][11][1])))+((utk[2][2]*Wpk[3][11][2])+((utk[2][0]*Wpk[3][11][0])+(
      utk[2][1]*Wpk[3][10][1])))));
    temp[1] = ((temp[0]-(((ufk[3][2]*Vpk[3][12][2])+((ufk[3][0]*Vpk[3][12][0])+(
      ufk[3][1]*Vpk[3][12][1])))+((utk[3][2]*Wpk[3][12][2])+((utk[3][0]*
      Wpk[3][11][0])+(utk[3][1]*Wpk[3][12][1])))))-(((ufk[4][2]*Vpk[3][14][2])+(
      (ufk[4][0]*Vpk[3][14][0])+(ufk[4][1]*Vpk[3][14][1])))+((utk[4][2]*
      Wpk[3][14][2])+((utk[4][0]*Wpk[3][14][0])+(utk[4][1]*Wpk[3][13][1])))));
    temp[2] = ((temp[1]-(((ufk[5][2]*Vpk[3][16][2])+((ufk[5][0]*Vpk[3][16][0])+(
      ufk[5][1]*Vpk[3][16][1])))+((utk[5][2]*Wpk[3][16][2])+((utk[5][0]*
      Wpk[3][15][0])+(utk[5][1]*Wpk[3][16][1])))))-(((ufk[6][2]*Vpk[3][18][2])+(
      (ufk[6][0]*Vpk[3][18][0])+(ufk[6][1]*Vpk[3][18][1])))+((utk[6][2]*
      Wpk[3][18][2])+((utk[6][0]*Wpk[3][18][0])+(utk[6][1]*Wpk[3][17][1])))));
    temp[3] = ((temp[2]-(((ufk[7][2]*Vpk[3][20][2])+((ufk[7][0]*Vpk[3][20][0])+(
      ufk[7][1]*Vpk[3][20][1])))+((utk[7][2]*Wpk[3][20][2])+((utk[7][0]*
      Wpk[3][20][0])+(utk[7][1]*Wpk[3][19][1])))))-(((ufk[8][2]*Vpk[3][22][2])+(
      (ufk[8][0]*Vpk[3][22][0])+(ufk[8][1]*Vpk[3][22][1])))+((utk[8][2]*
      Wpk[3][22][2])+((utk[8][0]*Wpk[3][21][0])+(utk[8][1]*Wpk[3][22][1])))));
    temp[4] = (((((utk[10][1]*s26)-(utk[10][0]*Wpk[3][27][0]))-(utk[10][2]*
      Wpk[3][27][2]))-((ufk[10][2]*Vpk[3][27][2])+((ufk[10][0]*Vpk[3][27][0])+(
      ufk[10][1]*Vpk[3][27][1]))))+(temp[3]-(((ufk[9][2]*Vpk[3][24][2])+((
      ufk[9][0]*Vpk[3][24][0])+(ufk[9][1]*Vpk[3][24][1])))+((utk[9][2]*
      Wpk[3][24][2])+((utk[9][0]*Wpk[3][24][0])+(utk[9][1]*Wpk[3][23][1]))))));
    temp[5] = ((temp[4]-(((ufk[11][2]*Vpk[3][28][2])+((ufk[11][0]*Vpk[3][28][0])
      +(ufk[11][1]*Vpk[3][28][1])))+((utk[11][2]*Wpk[3][28][2])+((utk[11][0]*
      Wpk[3][27][0])+(utk[11][1]*Wpk[3][28][1])))))-(((ufk[12][2]*Vpk[3][30][2])
      +((ufk[12][0]*Vpk[3][30][0])+(ufk[12][1]*Vpk[3][30][1])))+((utk[12][2]*
      Wpk[3][29][2])+((utk[12][0]*Wpk[3][30][0])+(utk[12][1]*Wpk[3][30][1])))));
    temp[6] = ((((((utk[13][1]*s32)-(utk[13][0]*Wpk[3][33][0]))-(utk[13][2]*
      Wpk[3][33][2]))-((ufk[13][2]*Vpk[3][33][2])+((ufk[13][0]*Vpk[3][33][0])+(
      ufk[13][1]*Vpk[3][33][1]))))+temp[5])-(((ufk[14][2]*Vpk[3][34][2])+((
      ufk[14][0]*Vpk[3][34][0])+(ufk[14][1]*Vpk[3][34][1])))+((utk[14][2]*
      Wpk[3][34][2])+((utk[14][0]*Wpk[3][33][0])+(utk[14][1]*Wpk[3][34][1])))));
    tau[3] = (utau[3]-(temp[6]-(((ufk[15][2]*Vpk[3][36][2])+((ufk[15][0]*
      Vpk[3][36][0])+(ufk[15][1]*Vpk[3][36][1])))+((utk[15][2]*Wpk[3][35][2])+((
      utk[15][0]*Wpk[3][36][0])+(utk[15][1]*Wpk[3][36][1]))))));
    temp[0] = ((((.05*ufk[0][0])-utk[0][1])-(((.14625*(ufk[1][2]*Wpk[4][8][0]))+
      ((.0351*(ufk[1][1]*Wpk[4][8][0]))+(ufk[1][0]*Vpk[4][8][0])))+((utk[1][2]*
      Wpk[4][8][2])+((utk[1][0]*Wpk[4][8][0])+(utk[1][1]*Wpk[4][7][1])))))-(((
      ufk[2][2]*Vpk[4][11][2])+((ufk[2][0]*Vpk[4][11][0])+(ufk[2][1]*
      Vpk[4][11][1])))+((utk[2][2]*Wpk[4][11][2])+((utk[2][0]*Wpk[4][11][0])+(
      utk[2][1]*Wpk[4][10][1])))));
    temp[1] = ((temp[0]-(((ufk[3][2]*Vpk[4][12][2])+((ufk[3][0]*Vpk[4][12][0])+(
      ufk[3][1]*Vpk[4][12][1])))+((utk[3][2]*Wpk[4][12][2])+((utk[3][0]*
      Wpk[4][11][0])+(utk[3][1]*Wpk[4][12][1])))))-(((ufk[4][2]*Vpk[4][14][2])+(
      (ufk[4][0]*Vpk[4][14][0])+(ufk[4][1]*Vpk[4][14][1])))+((utk[4][2]*
      Wpk[4][14][2])+((utk[4][0]*Wpk[4][14][0])+(utk[4][1]*Wpk[4][13][1])))));
    temp[2] = ((temp[1]-(((ufk[5][2]*Vpk[4][16][2])+((ufk[5][0]*Vpk[4][16][0])+(
      ufk[5][1]*Vpk[4][16][1])))+((utk[5][2]*Wpk[4][16][2])+((utk[5][0]*
      Wpk[4][15][0])+(utk[5][1]*Wpk[4][16][1])))))-(((ufk[6][2]*Vpk[4][18][2])+(
      (ufk[6][0]*Vpk[4][18][0])+(ufk[6][1]*Vpk[4][18][1])))+((utk[6][2]*
      Wpk[4][18][2])+((utk[6][0]*Wpk[4][18][0])+(utk[6][1]*Wpk[4][17][1])))));
    temp[3] = ((temp[2]-(((ufk[7][2]*Vpk[4][20][2])+((ufk[7][0]*Vpk[4][20][0])+(
      ufk[7][1]*Vpk[4][20][1])))+((utk[7][2]*Wpk[4][20][2])+((utk[7][0]*
      Wpk[4][20][0])+(utk[7][1]*Wpk[4][19][1])))))-(((ufk[8][2]*Vpk[4][22][2])+(
      (ufk[8][0]*Vpk[4][22][0])+(ufk[8][1]*Vpk[4][22][1])))+((utk[8][2]*
      Wpk[4][22][2])+((utk[8][0]*Wpk[4][21][0])+(utk[8][1]*Wpk[4][22][1])))));
    temp[4] = ((temp[3]-(((ufk[9][2]*Vpk[4][24][2])+((ufk[9][0]*Vpk[4][24][0])+(
      ufk[9][1]*Vpk[4][24][1])))+((utk[9][2]*Wpk[4][24][2])+((utk[9][0]*
      Wpk[4][24][0])+(utk[9][1]*Wpk[4][23][1])))))-(((ufk[10][2]*Vpk[4][27][2])+
      ((ufk[10][0]*Vpk[4][27][0])+(ufk[10][1]*Vpk[4][27][1])))+((utk[10][2]*
      Wpk[4][27][2])+((utk[10][0]*Wpk[4][27][0])+(utk[10][1]*Wpk[4][26][1])))));
    temp[5] = ((temp[4]-(((ufk[11][2]*Vpk[4][28][2])+((ufk[11][0]*Vpk[4][28][0])
      +(ufk[11][1]*Vpk[4][28][1])))+((utk[11][2]*Wpk[4][28][2])+((utk[11][0]*
      Wpk[4][27][0])+(utk[11][1]*Wpk[4][28][1])))))-(((ufk[12][2]*Vpk[4][30][2])
      +((ufk[12][0]*Vpk[4][30][0])+(ufk[12][1]*Vpk[4][30][1])))+((utk[12][2]*
      Wpk[4][29][2])+((utk[12][0]*Wpk[4][30][0])+(utk[12][1]*Wpk[4][30][1])))));
    temp[6] = ((temp[5]-(((ufk[13][2]*Vpk[4][33][2])+((ufk[13][0]*Vpk[4][33][0])
      +(ufk[13][1]*Vpk[4][33][1])))+((utk[13][2]*Wpk[4][33][2])+((utk[13][0]*
      Wpk[4][33][0])+(utk[13][1]*Wpk[4][32][1])))))-(((ufk[14][2]*Vpk[4][34][2])
      +((ufk[14][0]*Vpk[4][34][0])+(ufk[14][1]*Vpk[4][34][1])))+((utk[14][2]*
      Wpk[4][34][2])+((utk[14][0]*Wpk[4][33][0])+(utk[14][1]*Wpk[4][34][1])))));
    tau[4] = (utau[4]-(temp[6]-(((ufk[15][2]*Vpk[4][36][2])+((ufk[15][0]*
      Vpk[4][36][0])+(ufk[15][1]*Vpk[4][36][1])))+((utk[15][2]*Wpk[4][35][2])+((
      utk[15][0]*Wpk[4][36][0])+(utk[15][1]*Wpk[4][36][1]))))));
    temp[0] = (((utk[0][2]+(.1206*ufk[0][0]))+(((.14625*(ufk[1][2]*Wpk[5][8][0])
      )+((.0351*(ufk[1][1]*Wpk[5][8][0]))+(ufk[1][0]*Vpk[5][8][0])))+((utk[1][2]
      *Wpk[5][8][2])+((utk[1][0]*Wpk[5][8][0])+(utk[1][1]*Wpk[5][7][1])))))+(((
      ufk[2][2]*Vpk[5][11][2])+((ufk[2][0]*Vpk[5][11][0])+(ufk[2][1]*
      Vpk[5][11][1])))+((utk[2][2]*Wpk[5][11][2])+((utk[2][0]*Wpk[5][11][0])+(
      utk[2][1]*Wpk[5][10][1])))));
    temp[1] = ((((ufk[4][2]*Vpk[5][14][2])+((ufk[4][0]*Vpk[5][14][0])+(ufk[4][1]
      *Vpk[5][14][1])))+((utk[4][2]*Wpk[5][14][2])+((utk[4][0]*Wpk[5][14][0])+(
      utk[4][1]*Wpk[5][13][1]))))+((((ufk[3][2]*Vpk[5][12][2])+((ufk[3][0]*
      Vpk[5][12][0])+(ufk[3][1]*Vpk[5][12][1])))+((utk[3][2]*Wpk[5][12][2])+((
      utk[3][0]*Wpk[5][11][0])+(utk[3][1]*Wpk[5][12][1]))))+temp[0]));
    temp[2] = ((((ufk[6][2]*Vpk[5][18][2])+((ufk[6][0]*Vpk[5][18][0])+(ufk[6][1]
      *Vpk[5][18][1])))+((utk[6][2]*Wpk[5][18][2])+((utk[6][0]*Wpk[5][18][0])+(
      utk[6][1]*Wpk[5][17][1]))))+((((ufk[5][2]*Vpk[5][16][2])+((ufk[5][0]*
      Vpk[5][16][0])+(ufk[5][1]*Vpk[5][16][1])))+((utk[5][2]*Wpk[5][16][2])+((
      utk[5][0]*Wpk[5][15][0])+(utk[5][1]*Wpk[5][16][1]))))+temp[1]));
    temp[3] = ((((ufk[8][2]*Vpk[5][22][2])+((ufk[8][0]*Vpk[5][22][0])+(ufk[8][1]
      *Vpk[5][22][1])))+((utk[8][2]*Wpk[5][22][2])+((utk[8][0]*Wpk[5][21][0])+(
      utk[8][1]*Wpk[5][22][1]))))+((((ufk[7][2]*Vpk[5][20][2])+((ufk[7][0]*
      Vpk[5][20][0])+(ufk[7][1]*Vpk[5][20][1])))+((utk[7][2]*Wpk[5][20][2])+((
      utk[7][0]*Wpk[5][20][0])+(utk[7][1]*Wpk[5][19][1]))))+temp[2]));
    temp[4] = ((((ufk[10][2]*Vpk[5][27][2])+((ufk[10][0]*Vpk[5][27][0])+(
      ufk[10][1]*Vpk[5][27][1])))+((utk[10][2]*Wpk[5][27][2])+((utk[10][0]*
      Wpk[5][27][0])+(utk[10][1]*Wpk[5][26][1]))))+((((ufk[9][2]*Vpk[5][24][2])+
      ((ufk[9][0]*Vpk[5][24][0])+(ufk[9][1]*Vpk[5][24][1])))+((utk[9][2]*
      Wpk[5][24][2])+((utk[9][0]*Wpk[5][24][0])+(utk[9][1]*Wpk[5][23][1]))))+
      temp[3]));
    temp[5] = ((((ufk[12][2]*Vpk[5][30][2])+((ufk[12][0]*Vpk[5][30][0])+(
      ufk[12][1]*Vpk[5][30][1])))+((utk[12][2]*Wpk[5][29][2])+((utk[12][0]*
      Wpk[5][30][0])+(utk[12][1]*Wpk[5][30][1]))))+((((ufk[11][2]*Vpk[5][28][2])
      +((ufk[11][0]*Vpk[5][28][0])+(ufk[11][1]*Vpk[5][28][1])))+((utk[11][2]*
      Wpk[5][28][2])+((utk[11][0]*Wpk[5][27][0])+(utk[11][1]*Wpk[5][28][1]))))+
      temp[4]));
    temp[6] = ((((ufk[14][2]*Vpk[5][34][2])+((ufk[14][0]*Vpk[5][34][0])+(
      ufk[14][1]*Vpk[5][34][1])))+((utk[14][2]*Wpk[5][34][2])+((utk[14][0]*
      Wpk[5][33][0])+(utk[14][1]*Wpk[5][34][1]))))+((((ufk[13][2]*Vpk[5][33][2])
      +((ufk[13][0]*Vpk[5][33][0])+(ufk[13][1]*Vpk[5][33][1])))+((utk[13][2]*
      Wpk[5][33][2])+((utk[13][0]*Wpk[5][33][0])+(utk[13][1]*Wpk[5][32][1]))))+
      temp[5]));
    tau[5] = (utau[5]+((((ufk[15][2]*Vpk[5][36][2])+((ufk[15][0]*Vpk[5][36][0])+
      (ufk[15][1]*Vpk[5][36][1])))+((utk[15][2]*Wpk[5][35][2])+((utk[15][0]*
      Wpk[5][36][0])+(utk[15][1]*Wpk[5][36][1]))))+temp[6]));
    temp[0] = (((((utk[1][1]*s7)-(utk[1][0]*Wpk[6][8][0]))-(utk[1][2]*
      Wpk[6][8][2]))-((.14625*(ufk[1][2]*Wpk[6][8][0]))+((.0351*(ufk[1][1]*
      Wpk[6][8][0]))+(ufk[1][0]*Vpk[6][8][0]))))-(((ufk[2][2]*Vpk[6][11][2])+((
      ufk[2][0]*Vpk[6][11][0])+(ufk[2][1]*Vpk[6][11][1])))+((utk[2][2]*
      Wpk[6][11][2])+((utk[2][0]*Wpk[6][11][0])+(utk[2][1]*Wpk[6][10][1])))));
    temp[1] = ((temp[0]-(((ufk[3][2]*Vpk[6][12][2])+((ufk[3][0]*Vpk[6][12][0])+(
      ufk[3][1]*Vpk[6][12][1])))+((utk[3][2]*Wpk[6][12][2])+((utk[3][0]*
      Wpk[6][11][0])+(utk[3][1]*Wpk[6][12][1])))))-(((ufk[4][2]*Vpk[6][14][2])+(
      (ufk[4][0]*Vpk[6][14][0])+(ufk[4][1]*Vpk[6][14][1])))+((utk[4][2]*
      Wpk[6][14][2])+((utk[4][0]*Wpk[6][14][0])+(utk[4][1]*Wpk[6][13][1])))));
    temp[2] = ((temp[1]-(((ufk[5][2]*Vpk[6][16][2])+((ufk[5][0]*Vpk[6][16][0])+(
      ufk[5][1]*Vpk[6][16][1])))+((utk[5][2]*Wpk[6][16][2])+((utk[5][0]*
      Wpk[6][15][0])+(utk[5][1]*Wpk[6][16][1])))))-(((ufk[6][2]*Vpk[6][18][2])+(
      (ufk[6][0]*Vpk[6][18][0])+(ufk[6][1]*Vpk[6][18][1])))+((utk[6][2]*
      Wpk[6][18][2])+((utk[6][0]*Wpk[6][18][0])+(utk[6][1]*Wpk[6][17][1])))));
    temp[3] = ((temp[2]-(((ufk[7][2]*Vpk[6][20][2])+((ufk[7][0]*Vpk[6][20][0])+(
      ufk[7][1]*Vpk[6][20][1])))+((utk[7][2]*Wpk[6][20][2])+((utk[7][0]*
      Wpk[6][20][0])+(utk[7][1]*Wpk[6][19][1])))))-(((ufk[8][2]*Vpk[6][22][2])+(
      (ufk[8][0]*Vpk[6][22][0])+(ufk[8][1]*Vpk[6][22][1])))+((utk[8][2]*
      Wpk[6][22][2])+((utk[8][0]*Wpk[6][21][0])+(utk[8][1]*Wpk[6][22][1])))));
    tau[6] = (utau[6]-(temp[3]-(((ufk[9][2]*Vpk[6][24][2])+((ufk[9][0]*
      Vpk[6][24][0])+(ufk[9][1]*Vpk[6][24][1])))+((utk[9][2]*Wpk[6][24][2])+((
      utk[9][0]*Wpk[6][24][0])+(utk[9][1]*Wpk[6][23][1]))))));
    temp[0] = ((((.14625*(ufk[1][2]*s8))+((.0351*(ufk[1][1]*s8))+(.14625*(
      ufk[1][0]*c8))))+((utk[1][0]*s8)-(utk[1][2]*c8)))-(((ufk[2][2]*
      Vpk[7][11][2])+((ufk[2][0]*Vpk[7][11][0])+(ufk[2][1]*Vpk[7][11][1])))+((
      utk[2][2]*Wpk[7][11][2])+((utk[2][0]*Wpk[7][11][0])+(utk[2][1]*
      Wpk[7][10][1])))));
    temp[1] = ((temp[0]-(((ufk[3][2]*Vpk[7][12][2])+((ufk[3][0]*Vpk[7][12][0])+(
      ufk[3][1]*Vpk[7][12][1])))+((utk[3][2]*Wpk[7][12][2])+((utk[3][0]*
      Wpk[7][11][0])+(utk[3][1]*Wpk[7][12][1])))))-(((ufk[4][2]*Vpk[7][14][2])+(
      (ufk[4][0]*Vpk[7][14][0])+(ufk[4][1]*Vpk[7][14][1])))+((utk[4][2]*
      Wpk[7][14][2])+((utk[4][0]*Wpk[7][14][0])+(utk[4][1]*Wpk[7][13][1])))));
    temp[2] = ((temp[1]-(((ufk[5][2]*Vpk[7][16][2])+((ufk[5][0]*Vpk[7][16][0])+(
      ufk[5][1]*Vpk[7][16][1])))+((utk[5][2]*Wpk[7][16][2])+((utk[5][0]*
      Wpk[7][15][0])+(utk[5][1]*Wpk[7][16][1])))))-(((ufk[6][2]*Vpk[7][18][2])+(
      (ufk[6][0]*Vpk[7][18][0])+(ufk[6][1]*Vpk[7][18][1])))+((utk[6][2]*
      Wpk[7][18][2])+((utk[6][0]*Wpk[7][18][0])+(utk[6][1]*Wpk[7][17][1])))));
    temp[3] = ((temp[2]-(((ufk[7][2]*Vpk[7][20][2])+((ufk[7][0]*Vpk[7][20][0])+(
      ufk[7][1]*Vpk[7][20][1])))+((utk[7][2]*Wpk[7][20][2])+((utk[7][0]*
      Wpk[7][20][0])+(utk[7][1]*Wpk[7][19][1])))))-(((ufk[8][2]*Vpk[7][22][2])+(
      (ufk[8][0]*Vpk[7][22][0])+(ufk[8][1]*Vpk[7][22][1])))+((utk[8][2]*
      Wpk[7][22][2])+((utk[8][0]*Wpk[7][21][0])+(utk[8][1]*Wpk[7][22][1])))));
    tau[7] = (utau[7]-(temp[3]-(((ufk[9][2]*Vpk[7][24][2])+((ufk[9][0]*
      Vpk[7][24][0])+(ufk[9][1]*Vpk[7][24][1])))+((utk[9][2]*Wpk[7][24][2])+((
      utk[9][0]*Wpk[7][24][0])+(utk[9][1]*Wpk[7][23][1]))))));
    temp[0] = ((((.0351*ufk[1][0])-utk[1][1])-(((ufk[2][2]*Vpk[8][11][2])+((
      ufk[2][0]*Vpk[8][11][0])+(ufk[2][1]*Vpk[8][11][1])))+((utk[2][2]*
      Wpk[8][11][2])+((utk[2][0]*Wpk[8][11][0])+(utk[2][1]*Wpk[8][10][1])))))-((
      (ufk[3][2]*Vpk[8][12][2])+((ufk[3][0]*Vpk[8][12][0])+(ufk[3][1]*
      Vpk[8][12][1])))+((utk[3][2]*Wpk[8][12][2])+((utk[3][0]*Wpk[8][11][0])+(
      utk[3][1]*Wpk[8][12][1])))));
    temp[1] = ((temp[0]-(((ufk[4][2]*Vpk[8][14][2])+((ufk[4][0]*Vpk[8][14][0])+(
      ufk[4][1]*Vpk[8][14][1])))+((utk[4][2]*Wpk[8][14][2])+((utk[4][0]*
      Wpk[8][14][0])+(utk[4][1]*c13)))))-(((ufk[5][2]*Vpk[8][16][2])+((ufk[5][0]
      *Vpk[8][16][0])+(ufk[5][1]*Vpk[8][16][1])))+((utk[5][2]*Wpk[8][16][2])+((
      utk[5][0]*Wpk[8][15][0])+(utk[5][1]*Wpk[8][16][1])))));
    temp[2] = ((temp[1]-(((ufk[6][2]*Vpk[8][18][2])+((ufk[6][0]*Vpk[8][18][0])+(
      ufk[6][1]*Vpk[8][18][1])))+((utk[6][2]*Wpk[8][18][2])+((utk[6][0]*
      Wpk[8][18][0])+(utk[6][1]*Wpk[8][17][1])))))-(((ufk[7][2]*Vpk[8][20][2])+(
      (ufk[7][0]*Vpk[8][20][0])+(ufk[7][1]*Vpk[8][20][1])))+((utk[7][2]*
      Wpk[8][20][2])+((utk[7][0]*Wpk[8][20][0])+(utk[7][1]*c19)))));
    tau[8] = (utau[8]-((temp[2]-(((ufk[8][2]*Vpk[8][22][2])+((ufk[8][0]*
      Vpk[8][22][0])+(ufk[8][1]*Vpk[8][22][1])))+((utk[8][2]*Wpk[8][22][2])+((
      utk[8][0]*Wpk[8][21][0])+(utk[8][1]*Wpk[8][22][1])))))-(((ufk[9][2]*
      Vpk[8][24][2])+((ufk[9][0]*Vpk[8][24][0])+(ufk[9][1]*Vpk[8][24][1])))+((
      utk[9][2]*Wpk[8][24][2])+((utk[9][0]*Wpk[8][24][0])+(utk[9][1]*
      Wpk[8][23][1]))))));
    tau[9] = (utau[9]-(((((.0065*(ufk[2][1]*Wpk[9][11][0]))-(ufk[2][0]*
      Vpk[9][11][0]))-(.0442*(ufk[2][2]*Wpk[9][11][0])))+(((utk[2][1]*s10)-(
      utk[2][0]*Wpk[9][11][0]))-(utk[2][2]*Wpk[9][11][2])))-(((ufk[3][2]*
      Vpk[9][12][2])+((ufk[3][0]*Vpk[9][12][0])+(ufk[3][1]*Vpk[9][12][1])))+((
      utk[3][2]*Wpk[9][12][2])+((utk[3][0]*Wpk[9][11][0])+(utk[3][1]*
      Wpk[9][12][1]))))));
    tau[10] = (utau[10]-((((.0442*(ufk[2][2]*s11))+((.0442*(ufk[2][0]*c11))-(
      .0065*(ufk[2][1]*s11))))+((utk[2][0]*s11)-(utk[2][2]*c11)))+((((utk[3][0]*
      s11)-(utk[3][1]*Wpk[10][12][1]))-(utk[3][2]*Wpk[10][12][2]))-((ufk[3][2]*
      Vpk[10][12][2])+((ufk[3][0]*Vpk[10][12][0])+(ufk[3][1]*Vpk[10][12][1])))))
      );
    tau[11] = (utau[11]-((((utk[3][2]*s12)-(utk[3][1]*c12))-(ufk[3][0]*
      Vpk[11][12][0]))-(utk[2][1]+(.0065*ufk[2][0]))));
    tau[12] = (utau[12]-(((.0312*ufk[3][1])-(.078*ufk[3][2]))-utk[3][0]));
    temp[0] = ((((utk[4][0]*s14)-(utk[4][2]*c14))-(ufk[4][1]*Vpk[13][14][1]))+((
      ((.0039*(ufk[5][0]*Wpk[13][16][2]))-(ufk[5][1]*Vpk[13][16][1]))-(ufk[5][2]
      *Vpk[13][16][2]))-((utk[5][2]*Wpk[13][16][2])+((utk[5][0]*Wpk[13][15][0])+
      (utk[5][1]*Wpk[13][16][1])))));
    tau[13] = (utau[13]-(temp[0]-(((ufk[6][2]*Vpk[13][18][2])+((ufk[6][0]*
      Vpk[13][18][0])+(ufk[6][1]*Vpk[13][18][1])))+((utk[6][2]*Wpk[13][18][2])+(
      (utk[6][0]*Wpk[13][18][0])+(utk[6][1]*Wpk[13][17][1]))))));
    tau[14] = (utau[14]-(((((.1326*ufk[4][2])-(.0013*ufk[4][0]))-utk[4][1])+(((
      utk[5][2]*s16)-(utk[5][1]*c16))-((ufk[5][2]*Vpk[14][16][2])+((ufk[5][0]*
      Vpk[14][16][0])+(ufk[5][1]*Vpk[14][16][1])))))-(((ufk[6][2]*Vpk[14][18][2]
      )+((ufk[6][0]*Vpk[14][18][0])+(ufk[6][1]*Vpk[14][18][1])))+((utk[6][2]*
      Wpk[14][18][2])+((utk[6][0]*Wpk[14][18][0])+(utk[6][1]*Wpk[14][17][1])))))
      );
    tau[15] = (utau[15]-((((.1378*(ufk[5][2]*c16))+((.1378*(ufk[5][1]*s16))-(
      .0039*(ufk[5][0]*s16))))+((utk[5][2]*s16)-(utk[5][1]*c16)))-(((ufk[6][2]*
      Vpk[15][18][2])+((ufk[6][0]*Vpk[15][18][0])+(ufk[6][1]*Vpk[15][18][1])))+(
      (utk[6][2]*Wpk[15][18][2])+((utk[6][0]*Wpk[15][18][0])+(utk[6][1]*
      Wpk[15][17][1]))))));
    tau[16] = (utau[16]-(((((.0078*(ufk[6][0]*s18))-(.065*(ufk[6][1]*
      Wpk[16][18][2])))-(ufk[6][2]*Vpk[16][18][2]))+(((utk[6][1]*s17)-(utk[6][0]
      *Wpk[16][18][0]))-(utk[6][2]*Wpk[16][18][2])))-(utk[5][0]+(.0039*ufk[5][2]
      ))));
    tau[17] = (utau[17]-(((utk[6][0]*s18)-(utk[6][2]*c18))-(.065*(ufk[6][1]*c18)
      )));
    tau[18] = (utau[18]-((.065*ufk[6][2])-utk[6][1]));
    temp[0] = ((((utk[7][0]*s20)-(utk[7][2]*c20))-(ufk[7][1]*Vpk[19][20][1]))+((
      ((.0039*(ufk[8][0]*Wpk[19][22][2]))-(ufk[8][1]*Vpk[19][22][1]))-(ufk[8][2]
      *Vpk[19][22][2]))-((utk[8][2]*Wpk[19][22][2])+((utk[8][0]*Wpk[19][21][0])+
      (utk[8][1]*Wpk[19][22][1])))));
    tau[19] = (utau[19]-(temp[0]-(((ufk[9][2]*Vpk[19][24][2])+((ufk[9][0]*
      Vpk[19][24][0])+(ufk[9][1]*Vpk[19][24][1])))+((utk[9][2]*Wpk[19][24][2])+(
      (utk[9][0]*Wpk[19][24][0])+(utk[9][1]*Wpk[19][23][1]))))));
    tau[20] = (utau[20]-(((((utk[8][2]*s22)-(utk[8][1]*c22))-((ufk[8][2]*
      Vpk[20][22][2])+((ufk[8][0]*Vpk[20][22][0])+(ufk[8][1]*Vpk[20][22][1]))))-
      (utk[7][1]+((.0013*ufk[7][0])+(.1326*ufk[7][2]))))-(((ufk[9][2]*
      Vpk[20][24][2])+((ufk[9][0]*Vpk[20][24][0])+(ufk[9][1]*Vpk[20][24][1])))+(
      (utk[9][2]*Wpk[20][24][2])+((utk[9][0]*Wpk[20][24][0])+(utk[9][1]*
      Wpk[20][23][1]))))));
    tau[21] = (utau[21]-((((utk[8][2]*s22)-(utk[8][1]*c22))-((.1378*(ufk[8][2]*
      c22))+((.0039*(ufk[8][0]*s22))+(.1378*(ufk[8][1]*s22)))))-(((ufk[9][2]*
      Vpk[21][24][2])+((ufk[9][0]*Vpk[21][24][0])+(ufk[9][1]*Vpk[21][24][1])))+(
      (utk[9][2]*Wpk[21][24][2])+((utk[9][0]*Wpk[21][24][0])+(utk[9][1]*
      Wpk[21][23][1]))))));
    tau[22] = (utau[22]-(((((.0078*(ufk[9][0]*s24))+(.065*(ufk[9][1]*
      Wpk[22][24][2])))-(ufk[9][2]*Vpk[22][24][2]))+(((utk[9][1]*s23)-(utk[9][0]
      *Wpk[22][24][0]))-(utk[9][2]*Wpk[22][24][2])))-(utk[8][0]+(.0039*ufk[8][2]
      ))));
    tau[23] = (utau[23]-((.065*(ufk[9][1]*c24))+((utk[9][0]*s24)-(utk[9][2]*c24)
      )));
    tau[24] = (utau[24]+(utk[9][1]+(.065*ufk[9][2])));
    temp[0] = (((((utk[10][1]*s26)-(utk[10][0]*Wpk[25][27][0]))-(utk[10][2]*
      Wpk[25][27][2]))-((ufk[10][2]*Vpk[25][27][2])+((ufk[10][0]*Vpk[25][27][0])
      +(ufk[10][1]*Vpk[25][27][1]))))-(((ufk[11][2]*Vpk[25][28][2])+((ufk[11][0]
      *Vpk[25][28][0])+(ufk[11][1]*Vpk[25][28][1])))+((utk[11][2]*Wpk[25][28][2]
      )+((utk[11][0]*Wpk[25][27][0])+(utk[11][1]*Wpk[25][28][1])))));
    tau[25] = (utau[25]-(temp[0]-(((ufk[12][2]*Vpk[25][30][2])+((ufk[12][0]*
      Vpk[25][30][0])+(ufk[12][1]*Vpk[25][30][1])))+((utk[12][2]*Wpk[25][29][2])
      +((utk[12][0]*Wpk[25][30][0])+(utk[12][1]*Wpk[25][30][1]))))));
    temp[0] = ((((utk[10][0]*s27)-(utk[10][2]*c27))-((.2379*(ufk[10][2]*s27))+((
      .2379*(ufk[10][0]*c27))+(ufk[10][1]*Vpk[26][27][1]))))+((((utk[11][0]*s27)
      -(utk[11][1]*Wpk[26][28][1]))-(utk[11][2]*Wpk[26][28][2]))-((ufk[11][2]*
      Vpk[26][28][2])+((ufk[11][0]*Vpk[26][28][0])+(ufk[11][1]*Vpk[26][28][1])))
      ));
    tau[26] = (utau[26]-(temp[0]-(((ufk[12][2]*Vpk[26][30][2])+((ufk[12][0]*
      Vpk[26][30][0])+(ufk[12][1]*Vpk[26][30][1])))+((utk[12][2]*Wpk[26][29][2])
      +((utk[12][0]*Wpk[26][30][0])+(utk[12][1]*Wpk[26][30][1]))))));
    tau[27] = (utau[27]-(((((utk[11][2]*s28)-(utk[11][1]*c28))-((.0416*(
      ufk[11][2]*c28))+((.0416*(ufk[11][1]*s28))+(ufk[11][0]*Vpk[27][28][0]))))-
      (utk[10][1]+((.0143*ufk[10][0])+(.0169*ufk[10][2]))))-(((ufk[12][2]*
      Vpk[27][30][2])+((ufk[12][0]*Vpk[27][30][0])+(ufk[12][1]*Vpk[27][30][1])))
      +((utk[12][2]*Wpk[27][29][2])+((utk[12][0]*Wpk[27][30][0])+(utk[12][1]*
      Wpk[27][30][1]))))));
    tau[28] = (utau[28]-((((.2158*ufk[11][2])-(.0039*ufk[11][1]))-utk[11][0])+((
      (utk[12][1]*s30)-(utk[12][0]*c30))-((ufk[12][2]*Vpk[28][30][2])+((
      ufk[12][0]*Vpk[28][30][0])+(ufk[12][1]*Vpk[28][30][1]))))));
    tau[29] = (utau[29]-(((.039*((ufk[12][0]*s30)+(ufk[12][1]*c30)))+(.0442*(
      ufk[12][2]*c30)))+((utk[12][1]*s30)-(utk[12][0]*c30))));
    tau[30] = (utau[30]+(utk[12][2]+(.0442*ufk[12][0])));
    temp[0] = (((((utk[13][1]*s32)-(utk[13][0]*Wpk[31][33][0]))-(utk[13][2]*
      Wpk[31][33][2]))-((ufk[13][2]*Vpk[31][33][2])+((ufk[13][0]*Vpk[31][33][0])
      +(ufk[13][1]*Vpk[31][33][1]))))-(((ufk[14][2]*Vpk[31][34][2])+((ufk[14][0]
      *Vpk[31][34][0])+(ufk[14][1]*Vpk[31][34][1])))+((utk[14][2]*Wpk[31][34][2]
      )+((utk[14][0]*Wpk[31][33][0])+(utk[14][1]*Wpk[31][34][1])))));
    tau[31] = (utau[31]-(temp[0]-(((ufk[15][2]*Vpk[31][36][2])+((ufk[15][0]*
      Vpk[31][36][0])+(ufk[15][1]*Vpk[31][36][1])))+((utk[15][2]*Wpk[31][35][2])
      +((utk[15][0]*Wpk[31][36][0])+(utk[15][1]*Wpk[31][36][1]))))));
    temp[0] = ((((utk[13][0]*s33)-(utk[13][2]*c33))-((.2379*(ufk[13][2]*s33))+((
      .2379*(ufk[13][0]*c33))+(ufk[13][1]*Vpk[32][33][1]))))+((((utk[14][0]*s33)
      -(utk[14][1]*Wpk[32][34][1]))-(utk[14][2]*Wpk[32][34][2]))-((ufk[14][2]*
      Vpk[32][34][2])+((ufk[14][0]*Vpk[32][34][0])+(ufk[14][1]*Vpk[32][34][1])))
      ));
    tau[32] = (utau[32]-(temp[0]-(((ufk[15][2]*Vpk[32][36][2])+((ufk[15][0]*
      Vpk[32][36][0])+(ufk[15][1]*Vpk[32][36][1])))+((utk[15][2]*Wpk[32][35][2])
      +((utk[15][0]*Wpk[32][36][0])+(utk[15][1]*Wpk[32][36][1]))))));
    tau[33] = (utau[33]-(((((.0169*ufk[13][2])-(.0143*ufk[13][0]))-utk[13][1])+(
      ((.0416*(ufk[14][2]*c34))+((.0416*(ufk[14][1]*s34))-(ufk[14][0]*
      Vpk[33][34][0])))+((utk[14][2]*s34)-(utk[14][1]*c34))))-(((ufk[15][2]*
      Vpk[33][36][2])+((ufk[15][0]*Vpk[33][36][0])+(ufk[15][1]*Vpk[33][36][1])))
      +((utk[15][2]*Wpk[33][35][2])+((utk[15][0]*Wpk[33][36][0])+(utk[15][1]*
      Wpk[33][36][1]))))));
    tau[34] = (utau[34]-((((.2158*ufk[14][2])-(.0039*ufk[14][1]))-utk[14][0])+((
      (utk[15][1]*s36)-(utk[15][0]*c36))-((ufk[15][2]*Vpk[34][36][2])+((
      ufk[15][0]*Vpk[34][36][0])+(ufk[15][1]*Vpk[34][36][1]))))));
    tau[35] = (utau[35]-(((.039*((ufk[15][0]*s36)+(ufk[15][1]*c36)))+(.0442*(
      ufk[15][2]*c36)))+((utk[15][1]*s36)-(utk[15][0]*c36))));
    tau[36] = (utau[36]+(utk[15][2]+(.0442*ufk[15][0])));
/*
Op counts below do not include called subroutines
*/
/*
 Used 2.59 seconds CPU time,
 8192 additional bytes of memory.
 Equations contain  843 adds/subtracts/negates
                    867 multiplies
                      0 divides
                     84 assignments
*/
}

void skel18fulltrq(double *udotin, double *multin, double *trqout)
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[37][3],tstarr[37][3],Otkr[37][3],Atir[37][3],Atkr[37][3];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[6][0] = (udotin[3]+udotin[6]);
    Otkr[6][1] = ((u[6]*wk[6][2])+((udotin[4]*c6)+(udotin[5]*s6)));
    Otkr[6][2] = (((udotin[5]*c6)-(udotin[4]*s6))-(u[6]*wk[6][1]));
    Otkr[7][0] = ((u[7]*wk[7][1])+((Otkr[6][0]*c7)+(Otkr[6][1]*s7)));
    Otkr[7][1] = (((Otkr[6][1]*c7)-(Otkr[6][0]*s7))-(u[7]*wk[7][0]));
    Otkr[7][2] = (Otkr[6][2]+udotin[7]);
    Otkr[8][0] = (((Otkr[7][0]*c8)-(Otkr[7][2]*s8))-(u[8]*wk[8][2]));
    Otkr[8][1] = (Otkr[7][1]+udotin[8]);
    Otkr[8][2] = ((u[8]*wk[8][0])+((Otkr[7][0]*s8)+(Otkr[7][2]*c8)));
    Otkr[9][0] = (Otkr[8][0]+udotin[9]);
    Otkr[9][1] = ((u[9]*wk[9][2])+((Otkr[8][1]*c9)+(Otkr[8][2]*s9)));
    Otkr[9][2] = (((Otkr[8][2]*c9)-(Otkr[8][1]*s9))-(u[9]*wk[9][1]));
    Otkr[10][0] = ((u[10]*wk[10][1])+((Otkr[9][0]*c10)+(Otkr[9][1]*s10)));
    Otkr[10][1] = (((Otkr[9][1]*c10)-(Otkr[9][0]*s10))-(u[10]*wk[10][0]));
    Otkr[10][2] = (Otkr[9][2]+udotin[10]);
    Otkr[11][0] = (((Otkr[10][0]*c11)-(Otkr[10][2]*s11))-(u[11]*wk[11][2]));
    Otkr[11][1] = (Otkr[10][1]+udotin[11]);
    Otkr[11][2] = ((u[11]*wk[11][0])+((Otkr[10][0]*s11)+(Otkr[10][2]*c11)));
    Otkr[12][0] = (Otkr[11][0]+udotin[12]);
    Otkr[12][1] = ((u[12]*wk[12][2])+((Otkr[11][1]*c12)+(Otkr[11][2]*s12)));
    Otkr[12][2] = (((Otkr[11][2]*c12)-(Otkr[11][1]*s12))-(u[12]*wk[12][1]));
    Otkr[13][0] = ((u[13]*wk[13][1])+((Otkr[8][0]*c13)+(Otkr[8][1]*s13)));
    Otkr[13][1] = (((Otkr[8][1]*c13)-(Otkr[8][0]*s13))-(u[13]*wk[13][0]));
    Otkr[13][2] = (Otkr[8][2]+udotin[13]);
    Otkr[14][0] = (((Otkr[13][0]*c14)-(Otkr[13][2]*s14))-(u[14]*wk[14][2]));
    Otkr[14][1] = (Otkr[13][1]+udotin[14]);
    Otkr[14][2] = ((u[14]*wk[14][0])+((Otkr[13][0]*s14)+(Otkr[13][2]*c14)));
    Otkr[15][0] = (((Otkr[14][0]*c15)-(Otkr[14][2]*s15))-(u[15]*wk[15][2]));
    Otkr[15][1] = (Otkr[14][1]+udotin[15]);
    Otkr[15][2] = ((u[15]*wk[15][0])+((Otkr[14][0]*s15)+(Otkr[14][2]*c15)));
    Otkr[16][0] = (Otkr[15][0]+udotin[16]);
    Otkr[16][1] = ((u[16]*wk[16][2])+((Otkr[15][1]*c16)+(Otkr[15][2]*s16)));
    Otkr[16][2] = (((Otkr[15][2]*c16)-(Otkr[15][1]*s16))-(u[16]*wk[16][1]));
    Otkr[17][0] = ((u[17]*wk[17][1])+((Otkr[16][0]*c17)+(Otkr[16][1]*s17)));
    Otkr[17][1] = (((Otkr[16][1]*c17)-(Otkr[16][0]*s17))-(u[17]*wk[17][0]));
    Otkr[17][2] = (Otkr[16][2]+udotin[17]);
    Otkr[18][0] = (((Otkr[17][0]*c18)-(Otkr[17][2]*s18))-(u[18]*wk[18][2]));
    Otkr[18][1] = (Otkr[17][1]+udotin[18]);
    Otkr[18][2] = ((u[18]*wk[18][0])+((Otkr[17][0]*s18)+(Otkr[17][2]*c18)));
    Otkr[19][0] = ((u[19]*wk[19][1])+((Otkr[8][0]*c19)+(Otkr[8][1]*s19)));
    Otkr[19][1] = (((Otkr[8][1]*c19)-(Otkr[8][0]*s19))-(u[19]*wk[19][0]));
    Otkr[19][2] = (Otkr[8][2]+udotin[19]);
    Otkr[20][0] = (((Otkr[19][0]*c20)-(Otkr[19][2]*s20))-(u[20]*wk[20][2]));
    Otkr[20][1] = (Otkr[19][1]+udotin[20]);
    Otkr[20][2] = ((u[20]*wk[20][0])+((Otkr[19][0]*s20)+(Otkr[19][2]*c20)));
    Otkr[21][0] = (((Otkr[20][0]*c21)-(Otkr[20][2]*s21))-(u[21]*wk[21][2]));
    Otkr[21][1] = (Otkr[20][1]+udotin[21]);
    Otkr[21][2] = ((u[21]*wk[21][0])+((Otkr[20][0]*s21)+(Otkr[20][2]*c21)));
    Otkr[22][0] = (Otkr[21][0]+udotin[22]);
    Otkr[22][1] = ((u[22]*wk[22][2])+((Otkr[21][1]*c22)+(Otkr[21][2]*s22)));
    Otkr[22][2] = (((Otkr[21][2]*c22)-(Otkr[21][1]*s22))-(u[22]*wk[22][1]));
    Otkr[23][0] = ((u[23]*wk[23][1])+((Otkr[22][0]*c23)+(Otkr[22][1]*s23)));
    Otkr[23][1] = (((Otkr[22][1]*c23)-(Otkr[22][0]*s23))-(u[23]*wk[23][0]));
    Otkr[23][2] = (Otkr[22][2]+udotin[23]);
    Otkr[24][0] = (((Otkr[23][0]*c24)-(Otkr[23][2]*s24))-(u[24]*wk[24][2]));
    Otkr[24][1] = (Otkr[23][1]+udotin[24]);
    Otkr[24][2] = ((u[24]*wk[24][0])+((Otkr[23][0]*s24)+(Otkr[23][2]*c24)));
    Otkr[25][0] = (udotin[3]+udotin[25]);
    Otkr[25][1] = ((u[25]*wk[25][2])+((udotin[4]*c25)+(udotin[5]*s25)));
    Otkr[25][2] = (((udotin[5]*c25)-(udotin[4]*s25))-(u[25]*wk[25][1]));
    Otkr[26][0] = ((u[26]*wk[26][1])+((Otkr[25][0]*c26)+(Otkr[25][1]*s26)));
    Otkr[26][1] = (((Otkr[25][1]*c26)-(Otkr[25][0]*s26))-(u[26]*wk[26][0]));
    Otkr[26][2] = (Otkr[25][2]+udotin[26]);
    Otkr[27][0] = (((Otkr[26][0]*c27)-(Otkr[26][2]*s27))-(u[27]*wk[27][2]));
    Otkr[27][1] = (Otkr[26][1]+udotin[27]);
    Otkr[27][2] = ((u[27]*wk[27][0])+((Otkr[26][0]*s27)+(Otkr[26][2]*c27)));
    Otkr[28][0] = (Otkr[27][0]+udotin[28]);
    Otkr[28][1] = ((u[28]*wk[28][2])+((Otkr[27][1]*c28)+(Otkr[27][2]*s28)));
    Otkr[28][2] = (((Otkr[27][2]*c28)-(Otkr[27][1]*s28))-(u[28]*wk[28][1]));
    Otkr[29][0] = (Otkr[28][0]+udotin[29]);
    Otkr[29][1] = ((u[29]*wk[29][2])+((Otkr[28][1]*c29)+(Otkr[28][2]*s29)));
    Otkr[29][2] = (((Otkr[28][2]*c29)-(Otkr[28][1]*s29))-(u[29]*wk[29][1]));
    Otkr[30][0] = ((u[30]*wk[30][1])+((Otkr[29][0]*c30)+(Otkr[29][1]*s30)));
    Otkr[30][1] = (((Otkr[29][1]*c30)-(Otkr[29][0]*s30))-(u[30]*wk[30][0]));
    Otkr[30][2] = (Otkr[29][2]+udotin[30]);
    Otkr[31][0] = (udotin[3]+udotin[31]);
    Otkr[31][1] = ((u[31]*wk[31][2])+((udotin[4]*c31)+(udotin[5]*s31)));
    Otkr[31][2] = (((udotin[5]*c31)-(udotin[4]*s31))-(u[31]*wk[31][1]));
    Otkr[32][0] = ((u[32]*wk[32][1])+((Otkr[31][0]*c32)+(Otkr[31][1]*s32)));
    Otkr[32][1] = (((Otkr[31][1]*c32)-(Otkr[31][0]*s32))-(u[32]*wk[32][0]));
    Otkr[32][2] = (Otkr[31][2]+udotin[32]);
    Otkr[33][0] = (((Otkr[32][0]*c33)-(Otkr[32][2]*s33))-(u[33]*wk[33][2]));
    Otkr[33][1] = (Otkr[32][1]+udotin[33]);
    Otkr[33][2] = ((u[33]*wk[33][0])+((Otkr[32][0]*s33)+(Otkr[32][2]*c33)));
    Otkr[34][0] = (Otkr[33][0]+udotin[34]);
    Otkr[34][1] = ((u[34]*wk[34][2])+((Otkr[33][1]*c34)+(Otkr[33][2]*s34)));
    Otkr[34][2] = (((Otkr[33][2]*c34)-(Otkr[33][1]*s34))-(u[34]*wk[34][1]));
    Otkr[35][0] = (Otkr[34][0]+udotin[35]);
    Otkr[35][1] = ((u[35]*wk[35][2])+((Otkr[34][1]*c35)+(Otkr[34][2]*s35)));
    Otkr[35][2] = (((Otkr[34][2]*c35)-(Otkr[34][1]*s35))-(u[35]*wk[35][1]));
    Otkr[36][0] = ((u[36]*wk[36][1])+((Otkr[35][0]*c36)+(Otkr[35][1]*s36)));
    Otkr[36][1] = (((Otkr[35][1]*c36)-(Otkr[35][0]*s36))-(u[36]*wk[36][0]));
    Otkr[36][2] = (Otkr[35][2]+udotin[36]);
    Atkr[3][0] = ((Cik[3][2][0]*udotin[2])+((Cik[3][0][0]*udotin[0])+(
      Cik[3][1][0]*udotin[1])));
    Atkr[3][1] = ((Cik[3][2][1]*udotin[2])+((Cik[3][0][1]*udotin[0])+(
      Cik[3][1][1]*udotin[1])));
    Atkr[3][2] = ((Cik[3][2][2]*udotin[2])+((Cik[3][0][2]*udotin[0])+(
      Cik[3][1][2]*udotin[1])));
    Atkr[5][0] = (Atkr[3][0]+(((.1206*udotin[5])-(.05*udotin[4]))-((.05*(u[3]*
      u[5]))+(.1206*(u[3]*u[4])))));
    Atkr[5][1] = (Atkr[3][1]+((.05*udotin[3])+((.1206*(u[3]*u[3]))+(u[5]*
      Wkrpk[5][0]))));
    Atkr[5][2] = (Atkr[3][2]+(((.05*(u[3]*u[3]))-(u[4]*Wkrpk[5][0]))-(.1206*
      udotin[3])));
    Atir[6][0] = (Atkr[5][0]+(((.05*udotin[4])-(.1206*udotin[5]))+((.05*(u[3]*
      u[5]))+(.1206*(u[3]*u[4])))));
    Atir[6][1] = (Atkr[5][1]+(((u[5]*Wirk[6][0])-(.1206*(u[3]*u[3])))-(.05*
      udotin[3])));
    Atir[6][2] = (Atkr[5][2]+((.1206*udotin[3])-((.05*(u[3]*u[3]))+(u[4]*
      Wirk[6][0]))));
    Atkr[6][1] = ((Atir[6][1]*c6)+(Atir[6][2]*s6));
    Atkr[6][2] = ((Atir[6][2]*c6)-(Atir[6][1]*s6));
    Atkr[7][0] = ((Atir[6][0]*c7)+(Atkr[6][1]*s7));
    Atkr[7][1] = ((Atkr[6][1]*c7)-(Atir[6][0]*s7));
    Atkr[8][0] = (((Atkr[7][0]*c8)-(Atkr[6][2]*s8))+(((.14625*(wk[8][0]*wk[8][1]
      ))-(.0351*(wk[8][0]*wk[8][2])))-((.0351*Otkr[8][1])+(.14625*Otkr[8][2]))))
      ;
    Atkr[8][1] = (Atkr[7][1]+((.0351*Otkr[8][0])+((wk[8][2]*Wkrpk[8][0])-(.14625
      *(wk[8][0]*wk[8][0])))));
    Atkr[8][2] = (((.14625*Otkr[8][0])+((.0351*(wk[8][0]*wk[8][0]))-(wk[8][1]*
      Wkrpk[8][0])))+((Atkr[6][2]*c8)+(Atkr[7][0]*s8)));
    Atir[9][0] = (Atkr[8][0]+(((.24635*(wk[8][0]*wk[8][1]))-(.0013*(wk[8][0]*
      wk[8][2])))-((.0013*Otkr[8][1])+(.24635*Otkr[8][2]))));
    Atir[9][1] = (Atkr[8][1]+((.0013*Otkr[8][0])+((Wirk[9][0]*wk[8][2])-(.24635*
      (wk[8][0]*wk[8][0])))));
    Atir[9][2] = (Atkr[8][2]+((.24635*Otkr[8][0])+((.0013*(wk[8][0]*wk[8][0]))-(
      Wirk[9][0]*wk[8][1]))));
    Atkr[9][1] = ((Atir[9][1]*c9)+(Atir[9][2]*s9));
    Atkr[9][2] = ((Atir[9][2]*c9)-(Atir[9][1]*s9));
    Atkr[10][0] = ((Atir[9][0]*c10)+(Atkr[9][1]*s10));
    Atkr[10][1] = ((Atkr[9][1]*c10)-(Atir[9][0]*s10));
    Atkr[11][0] = (((Atkr[10][0]*c11)-(Atkr[9][2]*s11))+(((.0065*Otkr[11][1])-(
      .0442*Otkr[11][2]))+((.0065*(wk[11][0]*wk[11][2]))+(.0442*(wk[11][0]*
      wk[11][1])))));
    Atkr[11][1] = (Atkr[10][1]+(((wk[11][2]*Wkrpk[11][0])-(.0442*(wk[11][0]*
      wk[11][0])))-(.0065*Otkr[11][0])));
    Atkr[11][2] = (((.0442*Otkr[11][0])-((.0065*(wk[11][0]*wk[11][0]))+(
      wk[11][1]*Wkrpk[11][0])))+((Atkr[9][2]*c11)+(Atkr[10][0]*s11)));
    Atir[12][0] = (Atkr[11][0]+(((.0065*Otkr[11][1])-(.0442*Otkr[11][2]))+((
      .0065*(wk[11][0]*wk[11][2]))+(.0442*(wk[11][0]*wk[11][1])))));
    Atir[12][1] = (Atkr[11][1]+(((Wirk[12][0]*wk[11][2])-(.0442*(wk[11][0]*
      wk[11][0])))-(.0065*Otkr[11][0])));
    Atir[12][2] = (Atkr[11][2]+((.0442*Otkr[11][0])-((.0065*(wk[11][0]*wk[11][0]
      ))+(Wirk[12][0]*wk[11][1]))));
    Atkr[12][0] = (Atir[12][0]+(((.0312*Otkr[12][1])-(.078*Otkr[12][2]))+((.0312
      *(wk[12][0]*wk[12][2]))+(.078*(wk[12][0]*wk[12][1])))));
    Atkr[12][1] = (((Atir[12][1]*c12)+(Atir[12][2]*s12))+(((wk[12][2]*
      Wkrpk[12][0])-(.078*(wk[12][0]*wk[12][0])))-(.0312*Otkr[12][0])));
    Atkr[12][2] = (((.078*Otkr[12][0])-((.0312*(wk[12][0]*wk[12][0]))+(wk[12][1]
      *Wkrpk[12][0])))+((Atir[12][2]*c12)-(Atir[12][1]*s12)));
    Atir[13][0] = (Atkr[8][0]+(((.0013*Otkr[8][1])-(.18915*Otkr[8][2]))+((
      Wirk[13][2]*wk[8][1])-(Wirk[13][1]*wk[8][2]))));
    Atir[13][1] = (Atkr[8][1]+(((.1768*Otkr[8][2])-(.0013*Otkr[8][0]))+((
      Wirk[13][0]*wk[8][2])-(Wirk[13][2]*wk[8][0]))));
    Atir[13][2] = (Atkr[8][2]+(((.18915*Otkr[8][0])-(.1768*Otkr[8][1]))+((
      Wirk[13][1]*wk[8][0])-(Wirk[13][0]*wk[8][1]))));
    Atkr[13][0] = ((Atir[13][0]*c13)+(Atir[13][1]*s13));
    Atkr[13][1] = ((Atir[13][1]*c13)-(Atir[13][0]*s13));
    Atkr[14][0] = (((.0013*Otkr[14][1])-((.1326*(wk[14][1]*wk[14][1]))+(
      wk[14][2]*Wkrpk[14][1])))+((Atkr[13][0]*c14)-(Atir[13][2]*s14)));
    Atkr[14][1] = (Atkr[13][1]+(((.0013*(wk[14][1]*wk[14][2]))+(.1326*(wk[14][0]
      *wk[14][1])))+((.1326*Otkr[14][2])-(.0013*Otkr[14][0]))));
    Atkr[14][2] = (((Atir[13][2]*c14)+(Atkr[13][0]*s14))+(((wk[14][0]*
      Wkrpk[14][1])-(.0013*(wk[14][1]*wk[14][1])))-(.1326*Otkr[14][1])));
    Atir[15][0] = (Atkr[14][0]+((.0013*Otkr[14][1])-((.1326*(wk[14][1]*wk[14][1]
      ))+(Wirk[15][1]*wk[14][2]))));
    Atir[15][1] = (Atkr[14][1]+(((.0013*(wk[14][1]*wk[14][2]))+(.1326*(wk[14][0]
      *wk[14][1])))+((.1326*Otkr[14][2])-(.0013*Otkr[14][0]))));
    Atir[15][2] = (Atkr[14][2]+(((Wirk[15][1]*wk[14][0])-(.0013*(wk[14][1]*
      wk[14][1])))-(.1326*Otkr[14][1])));
    Atkr[15][0] = ((Atir[15][0]*c15)-(Atir[15][2]*s15));
    Atkr[15][2] = ((Atir[15][0]*s15)+(Atir[15][2]*c15));
    Atkr[16][0] = (Atkr[15][0]+(((wk[16][1]*Wkrpk[16][2])-(.1378*(wk[16][2]*
      wk[16][2])))-(.0039*Otkr[16][2])));
    Atkr[16][1] = (((.1378*Otkr[16][2])-((.0039*(wk[16][2]*wk[16][2]))+(
      wk[16][0]*Wkrpk[16][2])))+((Atir[15][1]*c16)+(Atkr[15][2]*s16)));
    Atkr[16][2] = (((Atkr[15][2]*c16)-(Atir[15][1]*s16))+(((.0039*Otkr[16][0])-(
      .1378*Otkr[16][1]))+((.0039*(wk[16][1]*wk[16][2]))+(.1378*(wk[16][0]*
      wk[16][2])))));
    Atir[17][0] = (Atkr[16][0]+(((Wirk[17][2]*wk[16][1])-(.1378*(wk[16][2]*
      wk[16][2])))-(.0039*Otkr[16][2])));
    Atir[17][1] = (Atkr[16][1]+((.1378*Otkr[16][2])-((.0039*(wk[16][2]*wk[16][2]
      ))+(Wirk[17][2]*wk[16][0]))));
    Atir[17][2] = (Atkr[16][2]+(((.0039*Otkr[16][0])-(.1378*Otkr[16][1]))+((
      .0039*(wk[16][1]*wk[16][2]))+(.1378*(wk[16][0]*wk[16][2])))));
    Atkr[17][0] = ((Atir[17][0]*c17)+(Atir[17][1]*s17));
    Atkr[17][1] = ((Atir[17][1]*c17)-(Atir[17][0]*s17));
    Atkr[18][0] = (((Atkr[17][0]*c18)-(Atir[17][2]*s18))-(.065*((wk[18][1]*
      wk[18][1])+(wk[18][2]*wk[18][2]))));
    Atkr[18][1] = (Atkr[17][1]+(.065*(Otkr[18][2]+(wk[18][0]*wk[18][1]))));
    Atkr[18][2] = ((.065*((wk[18][0]*wk[18][2])-Otkr[18][1]))+((Atir[17][2]*c18)
      +(Atkr[17][0]*s18)));
    Atir[19][0] = (Atkr[8][0]+(((.0013*Otkr[8][1])-(.18915*Otkr[8][2]))+((
      Wirk[19][2]*wk[8][1])-(Wirk[19][1]*wk[8][2]))));
    Atir[19][1] = (Atkr[8][1]+(((Wirk[19][0]*wk[8][2])-(Wirk[19][2]*wk[8][0]))-(
      (.0013*Otkr[8][0])+(.1768*Otkr[8][2]))));
    Atir[19][2] = (Atkr[8][2]+(((.1768*Otkr[8][1])+(.18915*Otkr[8][0]))+((
      Wirk[19][1]*wk[8][0])-(Wirk[19][0]*wk[8][1]))));
    Atkr[19][0] = ((Atir[19][0]*c19)+(Atir[19][1]*s19));
    Atkr[19][1] = ((Atir[19][1]*c19)-(Atir[19][0]*s19));
    Atkr[20][0] = (((.0013*Otkr[20][1])+((.1326*(wk[20][1]*wk[20][1]))-(
      wk[20][2]*Wkrpk[20][1])))+((Atkr[19][0]*c20)-(Atir[19][2]*s20)));
    Atkr[20][1] = (Atkr[19][1]+(((.0013*(wk[20][1]*wk[20][2]))-(.1326*(wk[20][0]
      *wk[20][1])))-((.0013*Otkr[20][0])+(.1326*Otkr[20][2]))));
    Atkr[20][2] = (((.1326*Otkr[20][1])+((wk[20][0]*Wkrpk[20][1])-(.0013*(
      wk[20][1]*wk[20][1]))))+((Atir[19][2]*c20)+(Atkr[19][0]*s20)));
    Atir[21][0] = (Atkr[20][0]+((.0013*Otkr[20][1])+((.1326*(wk[20][1]*wk[20][1]
      ))-(Wirk[21][1]*wk[20][2]))));
    Atir[21][1] = (Atkr[20][1]+(((.0013*(wk[20][1]*wk[20][2]))-(.1326*(wk[20][0]
      *wk[20][1])))-((.0013*Otkr[20][0])+(.1326*Otkr[20][2]))));
    Atir[21][2] = (Atkr[20][2]+((.1326*Otkr[20][1])+((Wirk[21][1]*wk[20][0])-(
      .0013*(wk[20][1]*wk[20][1])))));
    Atkr[21][0] = ((Atir[21][0]*c21)-(Atir[21][2]*s21));
    Atkr[21][2] = ((Atir[21][0]*s21)+(Atir[21][2]*c21));
    Atkr[22][0] = (Atkr[21][0]+(((.1378*(wk[22][2]*wk[22][2]))+(wk[22][1]*
      Wkrpk[22][2]))-(.0039*Otkr[22][2])));
    Atkr[22][1] = (((Atir[21][1]*c22)+(Atkr[21][2]*s22))-((.1378*Otkr[22][2])+((
      .0039*(wk[22][2]*wk[22][2]))+(wk[22][0]*Wkrpk[22][2]))));
    Atkr[22][2] = (((Atkr[21][2]*c22)-(Atir[21][1]*s22))+(((.0039*Otkr[22][0])+(
      .1378*Otkr[22][1]))+((.0039*(wk[22][1]*wk[22][2]))-(.1378*(wk[22][0]*
      wk[22][2])))));
    Atir[23][0] = (Atkr[22][0]+(((.1378*(wk[22][2]*wk[22][2]))+(Wirk[23][2]*
      wk[22][1]))-(.0039*Otkr[22][2])));
    Atir[23][1] = (Atkr[22][1]-((.1378*Otkr[22][2])+((.0039*(wk[22][2]*wk[22][2]
      ))+(Wirk[23][2]*wk[22][0]))));
    Atir[23][2] = (Atkr[22][2]+(((.0039*Otkr[22][0])+(.1378*Otkr[22][1]))+((
      .0039*(wk[22][1]*wk[22][2]))-(.1378*(wk[22][0]*wk[22][2])))));
    Atkr[23][0] = ((Atir[23][0]*c23)+(Atir[23][1]*s23));
    Atkr[23][1] = ((Atir[23][1]*c23)-(Atir[23][0]*s23));
    Atkr[24][0] = ((.065*((wk[24][1]*wk[24][1])+(wk[24][2]*wk[24][2])))+((
      Atkr[23][0]*c24)-(Atir[23][2]*s24)));
    Atkr[24][1] = (Atkr[23][1]-(.065*(Otkr[24][2]+(wk[24][0]*wk[24][1]))));
    Atkr[24][2] = ((.065*(Otkr[24][1]-(wk[24][0]*wk[24][2])))+((Atir[23][2]*c24)
      +(Atkr[23][0]*s24)));
    Atir[25][0] = (Atkr[5][0]+(((.0058*udotin[4])+(.0406*udotin[5]))+((u[4]*
      Wirk[25][2])-(u[5]*Wirk[25][1]))));
    Atir[25][1] = (Atkr[5][1]+(((.1118*udotin[5])-(.0058*udotin[3]))+((u[5]*
      Wirk[25][0])-(u[3]*Wirk[25][2]))));
    Atir[25][2] = (Atkr[5][2]+(((u[3]*Wirk[25][1])-(u[4]*Wirk[25][0]))-((.0406*
      udotin[3])+(.1118*udotin[4]))));
    Atkr[25][1] = ((Atir[25][1]*c25)+(Atir[25][2]*s25));
    Atkr[25][2] = ((Atir[25][2]*c25)-(Atir[25][1]*s25));
    Atkr[26][0] = ((Atir[25][0]*c26)+(Atkr[25][1]*s26));
    Atkr[26][1] = ((Atkr[25][1]*c26)-(Atir[25][0]*s26));
    Atkr[27][0] = (((Atkr[26][0]*c27)-(Atkr[25][2]*s27))+(((.0143*Otkr[27][1])+(
      .2379*Otkr[27][2]))+((wk[27][1]*Wkrpk[27][2])-(wk[27][2]*Wkrpk[27][1]))));
    Atkr[27][1] = (Atkr[26][1]+(((wk[27][2]*Wkrpk[27][0])-(wk[27][0]*
      Wkrpk[27][2]))-((.0143*Otkr[27][0])+(.0169*Otkr[27][2]))));
    Atkr[27][2] = (((Atkr[25][2]*c27)+(Atkr[26][0]*s27))+(((.0169*Otkr[27][1])-(
      .2379*Otkr[27][0]))+((wk[27][0]*Wkrpk[27][1])-(wk[27][1]*Wkrpk[27][0]))));
    Atir[28][0] = (Atkr[27][0]+(((.0143*Otkr[27][1])+(.2379*Otkr[27][2]))+((
      Wirk[28][2]*wk[27][1])-(Wirk[28][1]*wk[27][2]))));
    Atir[28][1] = (Atkr[27][1]+(((Wirk[28][0]*wk[27][2])-(Wirk[28][2]*wk[27][0])
      )-((.0143*Otkr[27][0])+(.0169*Otkr[27][2]))));
    Atir[28][2] = (Atkr[27][2]+(((.0169*Otkr[27][1])-(.2379*Otkr[27][0]))+((
      Wirk[28][1]*wk[27][0])-(Wirk[28][0]*wk[27][1]))));
    Atkr[28][0] = (Atir[28][0]+(((.2158*Otkr[28][2])-(.0039*Otkr[28][1]))+((
      wk[28][1]*Wkrpk[28][2])-(wk[28][2]*Wkrpk[28][1]))));
    Atkr[28][1] = (((Atir[28][1]*c28)+(Atir[28][2]*s28))+(((.0039*Otkr[28][0])-(
      .0078*Otkr[28][2]))+((wk[28][2]*Wkrpk[28][0])-(wk[28][0]*Wkrpk[28][2]))));
    Atkr[28][2] = (((Atir[28][2]*c28)-(Atir[28][1]*s28))+(((.0078*Otkr[28][1])-(
      .2158*Otkr[28][0]))+((wk[28][0]*Wkrpk[28][1])-(wk[28][1]*Wkrpk[28][0]))));
    Atir[29][0] = (Atkr[28][0]+(((.2158*Otkr[28][2])-(.0039*Otkr[28][1]))+((
      Wirk[29][2]*wk[28][1])-(Wirk[29][1]*wk[28][2]))));
    Atir[29][1] = (Atkr[28][1]+(((.0039*Otkr[28][0])-(.0078*Otkr[28][2]))+((
      Wirk[29][0]*wk[28][2])-(Wirk[29][2]*wk[28][0]))));
    Atir[29][2] = (Atkr[28][2]+(((.0078*Otkr[28][1])-(.2158*Otkr[28][0]))+((
      Wirk[29][1]*wk[28][0])-(Wirk[29][0]*wk[28][1]))));
    Atkr[29][1] = ((Atir[29][1]*c29)+(Atir[29][2]*s29));
    Atkr[29][2] = ((Atir[29][2]*c29)-(Atir[29][1]*s29));
    Atkr[30][0] = (((Atir[29][0]*c30)+(Atkr[29][1]*s30))+(((.039*Otkr[30][1])+(
      .0442*Otkr[30][2]))+((.039*(wk[30][0]*wk[30][2]))-(.0442*(wk[30][0]*
      wk[30][1])))));
    Atkr[30][1] = (((Atkr[29][1]*c30)-(Atir[29][0]*s30))+(((.0442*(wk[30][0]*
      wk[30][0]))+(wk[30][2]*Wkrpk[30][0]))-(.039*Otkr[30][0])));
    Atkr[30][2] = (Atkr[29][2]-((.0442*Otkr[30][0])+((.039*(wk[30][0]*wk[30][0])
      )+(wk[30][1]*Wkrpk[30][0]))));
    Atir[31][0] = (Atkr[5][0]+(((.0058*udotin[4])+(.0406*udotin[5]))+((u[4]*
      Wirk[31][2])-(u[5]*Wirk[31][1]))));
    Atir[31][1] = (Atkr[5][1]+(((u[5]*Wirk[31][0])-(u[3]*Wirk[31][2]))-((.0058*
      udotin[3])+(.1118*udotin[5]))));
    Atir[31][2] = (Atkr[5][2]+(((.1118*udotin[4])-(.0406*udotin[3]))+((u[3]*
      Wirk[31][1])-(u[4]*Wirk[31][0]))));
    Atkr[31][1] = ((Atir[31][1]*c31)+(Atir[31][2]*s31));
    Atkr[31][2] = ((Atir[31][2]*c31)-(Atir[31][1]*s31));
    Atkr[32][0] = ((Atir[31][0]*c32)+(Atkr[31][1]*s32));
    Atkr[32][1] = ((Atkr[31][1]*c32)-(Atir[31][0]*s32));
    Atkr[33][0] = (((Atkr[32][0]*c33)-(Atkr[31][2]*s33))+(((.0143*Otkr[33][1])+(
      .2379*Otkr[33][2]))+((wk[33][1]*Wkrpk[33][2])-(wk[33][2]*Wkrpk[33][1]))));
    Atkr[33][1] = (Atkr[32][1]+(((.0169*Otkr[33][2])-(.0143*Otkr[33][0]))+((
      wk[33][2]*Wkrpk[33][0])-(wk[33][0]*Wkrpk[33][2]))));
    Atkr[33][2] = (((Atkr[31][2]*c33)+(Atkr[32][0]*s33))+(((wk[33][0]*
      Wkrpk[33][1])-(wk[33][1]*Wkrpk[33][0]))-((.0169*Otkr[33][1])+(.2379*
      Otkr[33][0]))));
    Atir[34][0] = (Atkr[33][0]+(((.0143*Otkr[33][1])+(.2379*Otkr[33][2]))+((
      Wirk[34][2]*wk[33][1])-(Wirk[34][1]*wk[33][2]))));
    Atir[34][1] = (Atkr[33][1]+(((.0169*Otkr[33][2])-(.0143*Otkr[33][0]))+((
      Wirk[34][0]*wk[33][2])-(Wirk[34][2]*wk[33][0]))));
    Atir[34][2] = (Atkr[33][2]+(((Wirk[34][1]*wk[33][0])-(Wirk[34][0]*wk[33][1])
      )-((.0169*Otkr[33][1])+(.2379*Otkr[33][0]))));
    Atkr[34][0] = (Atir[34][0]+(((.2158*Otkr[34][2])-(.0039*Otkr[34][1]))+((
      wk[34][1]*Wkrpk[34][2])-(wk[34][2]*Wkrpk[34][1]))));
    Atkr[34][1] = (((Atir[34][1]*c34)+(Atir[34][2]*s34))+(((.0039*Otkr[34][0])+(
      .0078*Otkr[34][2]))+((wk[34][2]*Wkrpk[34][0])-(wk[34][0]*Wkrpk[34][2]))));
    Atkr[34][2] = (((Atir[34][2]*c34)-(Atir[34][1]*s34))+(((wk[34][0]*
      Wkrpk[34][1])-(wk[34][1]*Wkrpk[34][0]))-((.0078*Otkr[34][1])+(.2158*
      Otkr[34][0]))));
    Atir[35][0] = (Atkr[34][0]+(((.2158*Otkr[34][2])-(.0039*Otkr[34][1]))+((
      Wirk[35][2]*wk[34][1])-(Wirk[35][1]*wk[34][2]))));
    Atir[35][1] = (Atkr[34][1]+(((.0039*Otkr[34][0])+(.0078*Otkr[34][2]))+((
      Wirk[35][0]*wk[34][2])-(Wirk[35][2]*wk[34][0]))));
    Atir[35][2] = (Atkr[34][2]+(((Wirk[35][1]*wk[34][0])-(Wirk[35][0]*wk[34][1])
      )-((.0078*Otkr[34][1])+(.2158*Otkr[34][0]))));
    Atkr[35][1] = ((Atir[35][1]*c35)+(Atir[35][2]*s35));
    Atkr[35][2] = ((Atir[35][2]*c35)-(Atir[35][1]*s35));
    Atkr[36][0] = (((Atir[35][0]*c36)+(Atkr[35][1]*s36))+(((.039*Otkr[36][1])+(
      .0442*Otkr[36][2]))+((.039*(wk[36][0]*wk[36][2]))-(.0442*(wk[36][0]*
      wk[36][1])))));
    Atkr[36][1] = (((Atkr[35][1]*c36)-(Atir[35][0]*s36))+(((.0442*(wk[36][0]*
      wk[36][0]))+(wk[36][2]*Wkrpk[36][0]))-(.039*Otkr[36][0])));
    Atkr[36][2] = (Atkr[35][2]-((.0442*Otkr[36][0])+((.039*(wk[36][0]*wk[36][0])
      )+(wk[36][1]*Wkrpk[36][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = (ufk[0][0]-(16.61*Atkr[5][0]));
    fstarr[5][1] = (ufk[0][1]-(16.61*Atkr[5][1]));
    fstarr[5][2] = (ufk[0][2]-(16.61*Atkr[5][2]));
    fstarr[8][0] = (ufk[1][0]-(29.27*Atkr[8][0]));
    fstarr[8][1] = (ufk[1][1]-(29.27*Atkr[8][1]));
    fstarr[8][2] = (ufk[1][2]-(29.27*Atkr[8][2]));
    fstarr[11][0] = (ufk[2][0]-Atkr[11][0]);
    fstarr[11][1] = (ufk[2][1]-Atkr[11][1]);
    fstarr[11][2] = (ufk[2][2]-Atkr[11][2]);
    fstarr[12][0] = (ufk[3][0]-(5.89*Atkr[12][0]));
    fstarr[12][1] = (ufk[3][1]-(5.89*Atkr[12][1]));
    fstarr[12][2] = (ufk[3][2]-(5.89*Atkr[12][2]));
    fstarr[14][0] = (ufk[4][0]-(2.79*Atkr[14][0]));
    fstarr[14][1] = (ufk[4][1]-(2.79*Atkr[14][1]));
    fstarr[14][2] = (ufk[4][2]-(2.79*Atkr[14][2]));
    fstarr[16][0] = (ufk[5][0]-(1.21*Atkr[16][0]));
    fstarr[16][1] = (ufk[5][1]-(1.21*Atkr[16][1]));
    fstarr[16][2] = (ufk[5][2]-(1.21*Atkr[16][2]));
    fstarr[18][0] = (ufk[6][0]-(.55*Atkr[18][0]));
    fstarr[18][1] = (ufk[6][1]-(.55*Atkr[18][1]));
    fstarr[18][2] = (ufk[6][2]-(.55*Atkr[18][2]));
    fstarr[20][0] = (ufk[7][0]-(2.79*Atkr[20][0]));
    fstarr[20][1] = (ufk[7][1]-(2.79*Atkr[20][1]));
    fstarr[20][2] = (ufk[7][2]-(2.79*Atkr[20][2]));
    fstarr[22][0] = (ufk[8][0]-(1.21*Atkr[22][0]));
    fstarr[22][1] = (ufk[8][1]-(1.21*Atkr[22][1]));
    fstarr[22][2] = (ufk[8][2]-(1.21*Atkr[22][2]));
    fstarr[24][0] = (ufk[9][0]-(.55*Atkr[24][0]));
    fstarr[24][1] = (ufk[9][1]-(.55*Atkr[24][1]));
    fstarr[24][2] = (ufk[9][2]-(.55*Atkr[24][2]));
    fstarr[27][0] = (ufk[10][0]-(8.35*Atkr[27][0]));
    fstarr[27][1] = (ufk[10][1]-(8.35*Atkr[27][1]));
    fstarr[27][2] = (ufk[10][2]-(8.35*Atkr[27][2]));
    fstarr[28][0] = (ufk[11][0]-(4.16*Atkr[28][0]));
    fstarr[28][1] = (ufk[11][1]-(4.16*Atkr[28][1]));
    fstarr[28][2] = (ufk[11][2]-(4.16*Atkr[28][2]));
    fstarr[30][0] = (ufk[12][0]-(1.34*Atkr[30][0]));
    fstarr[30][1] = (ufk[12][1]-(1.34*Atkr[30][1]));
    fstarr[30][2] = (ufk[12][2]-(1.34*Atkr[30][2]));
    fstarr[33][0] = (ufk[13][0]-(8.35*Atkr[33][0]));
    fstarr[33][1] = (ufk[13][1]-(8.35*Atkr[33][1]));
    fstarr[33][2] = (ufk[13][2]-(8.35*Atkr[33][2]));
    fstarr[34][0] = (ufk[14][0]-(4.16*Atkr[34][0]));
    fstarr[34][1] = (ufk[14][1]-(4.16*Atkr[34][1]));
    fstarr[34][2] = (ufk[14][2]-(4.16*Atkr[34][2]));
    fstarr[36][0] = (ufk[15][0]-(1.34*Atkr[36][0]));
    fstarr[36][1] = (ufk[15][1]-(1.34*Atkr[36][1]));
    fstarr[36][2] = (ufk[15][2]-(1.34*Atkr[36][2]));
    tstarr[5][0] = (utk[0][0]-(WkIkWk[5][0]+(.18*udotin[3])));
    tstarr[5][1] = (utk[0][1]-(WkIkWk[5][1]+(.16*udotin[4])));
    tstarr[5][2] = (utk[0][2]-(WkIkWk[5][2]+(.23*udotin[5])));
    tstarr[8][0] = (utk[1][0]-(WkIkWk[8][0]+(.63*Otkr[8][0])));
    tstarr[8][1] = (utk[1][1]-(WkIkWk[8][1]+(.32*Otkr[8][1])));
    tstarr[8][2] = (utk[1][2]-(WkIkWk[8][2]+(.73*Otkr[8][2])));
    tstarr[11][0] = (utk[2][0]-(WkIkWk[11][0]+(.006*Otkr[11][0])));
    tstarr[11][1] = (utk[2][1]-(.001*Otkr[11][1]));
    tstarr[11][2] = (utk[2][2]-(WkIkWk[11][2]+(.006*Otkr[11][2])));
    tstarr[12][0] = (utk[3][0]-(WkIkWk[12][0]+(.033*Otkr[12][0])));
    tstarr[12][1] = (utk[3][1]-(WkIkWk[12][1]+(.023*Otkr[12][1])));
    tstarr[12][2] = (utk[3][2]-(WkIkWk[12][2]+(.03*Otkr[12][2])));
    tstarr[14][0] = (utk[4][0]-(.005*Otkr[14][0]));
    tstarr[14][1] = (utk[4][1]-(WkIkWk[14][1]+(.025*Otkr[14][1])));
    tstarr[14][2] = (utk[4][2]-(WkIkWk[14][2]+(.025*Otkr[14][2])));
    tstarr[16][0] = (utk[5][0]-(WkIkWk[16][0]+(.0012*Otkr[16][0])));
    tstarr[16][1] = (utk[5][1]-(WkIkWk[16][1]+(.0054*Otkr[16][1])));
    tstarr[16][2] = (utk[5][2]-(WkIkWk[16][2]+(.005*Otkr[16][2])));
    tstarr[18][0] = (utk[6][0]-(WkIkWk[18][0]+(.0005*Otkr[18][0])));
    tstarr[18][1] = (utk[6][1]-(WkIkWk[18][1]+(.002*Otkr[18][1])));
    tstarr[18][2] = (utk[6][2]-(WkIkWk[18][2]+(.0016*Otkr[18][2])));
    tstarr[20][0] = (utk[7][0]-(.005*Otkr[20][0]));
    tstarr[20][1] = (utk[7][1]-(WkIkWk[20][1]+(.025*Otkr[20][1])));
    tstarr[20][2] = (utk[7][2]-(WkIkWk[20][2]+(.025*Otkr[20][2])));
    tstarr[22][0] = (utk[8][0]-(WkIkWk[22][0]+(.0012*Otkr[22][0])));
    tstarr[22][1] = (utk[8][1]-(WkIkWk[22][1]+(.0054*Otkr[22][1])));
    tstarr[22][2] = (utk[8][2]-(WkIkWk[22][2]+(.005*Otkr[22][2])));
    tstarr[24][0] = (utk[9][0]-(WkIkWk[24][0]+(.0005*Otkr[24][0])));
    tstarr[24][1] = (utk[9][1]-(WkIkWk[24][1]+(.002*Otkr[24][1])));
    tstarr[24][2] = (utk[9][2]-(WkIkWk[24][2]+(.0016*Otkr[24][2])));
    tstarr[27][0] = (utk[10][0]-(WkIkWk[27][0]+(.16*Otkr[27][0])));
    tstarr[27][1] = (utk[10][1]-(WkIkWk[27][1]+(.025*Otkr[27][1])));
    tstarr[27][2] = (utk[10][2]-(WkIkWk[27][2]+(.15*Otkr[27][2])));
    tstarr[28][0] = (utk[11][0]-(WkIkWk[28][0]+(.056*Otkr[28][0])));
    tstarr[28][1] = (utk[11][1]-(WkIkWk[28][1]+(.007*Otkr[28][1])));
    tstarr[28][2] = (utk[11][2]-(WkIkWk[28][2]+(.055*Otkr[28][2])));
    tstarr[30][0] = (utk[12][0]-(WkIkWk[30][0]+(.0075*Otkr[30][0])));
    tstarr[30][1] = (utk[12][1]-(WkIkWk[30][1]+(.007*Otkr[30][1])));
    tstarr[30][2] = (utk[12][2]-(WkIkWk[30][2]+(.0018*Otkr[30][2])));
    tstarr[33][0] = (utk[13][0]-(WkIkWk[33][0]+(.16*Otkr[33][0])));
    tstarr[33][1] = (utk[13][1]-(WkIkWk[33][1]+(.025*Otkr[33][1])));
    tstarr[33][2] = (utk[13][2]-(WkIkWk[33][2]+(.15*Otkr[33][2])));
    tstarr[34][0] = (utk[14][0]-(WkIkWk[34][0]+(.056*Otkr[34][0])));
    tstarr[34][1] = (utk[14][1]-(WkIkWk[34][1]+(.007*Otkr[34][1])));
    tstarr[34][2] = (utk[14][2]-(WkIkWk[34][2]+(.055*Otkr[34][2])));
    tstarr[36][0] = (utk[15][0]-(WkIkWk[36][0]+(.0075*Otkr[36][0])));
    tstarr[36][1] = (utk[15][1]-(WkIkWk[36][1]+(.007*Otkr[36][1])));
    tstarr[36][2] = (utk[15][2]-(WkIkWk[36][2]+(.0018*Otkr[36][2])));
/*
Now calculate the torques
*/
    skel18dovpk();
    temp[0] = (((fstarr[12][2]*Vpk[0][12][2])+((fstarr[12][0]*Vpk[0][11][0])+(
      fstarr[12][1]*Vpk[0][12][1])))+(((fstarr[11][2]*Vpk[0][11][2])+((
      fstarr[11][0]*Vpk[0][11][0])+(fstarr[11][1]*Vpk[0][10][1])))+(((
      Cik[3][0][2]*fstarr[5][2])+((Cik[3][0][0]*fstarr[5][0])+(Cik[3][0][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[0][8][2])+((fstarr[8][0]*Vpk[0][8][0])+
      (fstarr[8][1]*Vpk[0][7][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[0][20][2])+((fstarr[20][0]*Vpk[0][20][0])+(
      fstarr[20][1]*Vpk[0][19][1])))+(((fstarr[18][2]*Vpk[0][18][2])+((
      fstarr[18][0]*Vpk[0][18][0])+(fstarr[18][1]*Vpk[0][17][1])))+(((
      fstarr[16][2]*Vpk[0][16][2])+((fstarr[16][0]*Vpk[0][15][0])+(fstarr[16][1]
      *Vpk[0][16][1])))+(((fstarr[14][2]*Vpk[0][14][2])+((fstarr[14][0]*
      Vpk[0][14][0])+(fstarr[14][1]*Vpk[0][13][1])))+temp[0]))));
    temp[2] = (((fstarr[28][2]*Vpk[0][28][2])+((fstarr[28][0]*Vpk[0][27][0])+(
      fstarr[28][1]*Vpk[0][28][1])))+(((fstarr[27][2]*Vpk[0][27][2])+((
      fstarr[27][0]*Vpk[0][27][0])+(fstarr[27][1]*Vpk[0][26][1])))+(((
      fstarr[24][2]*Vpk[0][24][2])+((fstarr[24][0]*Vpk[0][24][0])+(fstarr[24][1]
      *Vpk[0][23][1])))+(((fstarr[22][2]*Vpk[0][22][2])+((fstarr[22][0]*
      Vpk[0][21][0])+(fstarr[22][1]*Vpk[0][22][1])))+temp[1]))));
    trqout[0] = -(utau[0]+(((fstarr[36][2]*Vpk[0][35][2])+((fstarr[36][0]*
      Vpk[0][36][0])+(fstarr[36][1]*Vpk[0][36][1])))+(((fstarr[34][2]*
      Vpk[0][34][2])+((fstarr[34][0]*Vpk[0][33][0])+(fstarr[34][1]*Vpk[0][34][1]
      )))+(((fstarr[33][2]*Vpk[0][33][2])+((fstarr[33][0]*Vpk[0][33][0])+(
      fstarr[33][1]*Vpk[0][32][1])))+(((fstarr[30][2]*Vpk[0][29][2])+((
      fstarr[30][0]*Vpk[0][30][0])+(fstarr[30][1]*Vpk[0][30][1])))+temp[2])))));
    temp[0] = (((fstarr[12][2]*Vpk[1][12][2])+((fstarr[12][0]*Vpk[1][11][0])+(
      fstarr[12][1]*Vpk[1][12][1])))+(((fstarr[11][2]*Vpk[1][11][2])+((
      fstarr[11][0]*Vpk[1][11][0])+(fstarr[11][1]*Vpk[1][10][1])))+(((
      Cik[3][1][2]*fstarr[5][2])+((Cik[3][1][0]*fstarr[5][0])+(Cik[3][1][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[1][8][2])+((fstarr[8][0]*Vpk[1][8][0])+
      (fstarr[8][1]*Vpk[1][7][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[1][20][2])+((fstarr[20][0]*Vpk[1][20][0])+(
      fstarr[20][1]*Vpk[1][19][1])))+(((fstarr[18][2]*Vpk[1][18][2])+((
      fstarr[18][0]*Vpk[1][18][0])+(fstarr[18][1]*Vpk[1][17][1])))+(((
      fstarr[16][2]*Vpk[1][16][2])+((fstarr[16][0]*Vpk[1][15][0])+(fstarr[16][1]
      *Vpk[1][16][1])))+(((fstarr[14][2]*Vpk[1][14][2])+((fstarr[14][0]*
      Vpk[1][14][0])+(fstarr[14][1]*Vpk[1][13][1])))+temp[0]))));
    temp[2] = (((fstarr[28][2]*Vpk[1][28][2])+((fstarr[28][0]*Vpk[1][27][0])+(
      fstarr[28][1]*Vpk[1][28][1])))+(((fstarr[27][2]*Vpk[1][27][2])+((
      fstarr[27][0]*Vpk[1][27][0])+(fstarr[27][1]*Vpk[1][26][1])))+(((
      fstarr[24][2]*Vpk[1][24][2])+((fstarr[24][0]*Vpk[1][24][0])+(fstarr[24][1]
      *Vpk[1][23][1])))+(((fstarr[22][2]*Vpk[1][22][2])+((fstarr[22][0]*
      Vpk[1][21][0])+(fstarr[22][1]*Vpk[1][22][1])))+temp[1]))));
    trqout[1] = -(utau[1]+(((fstarr[36][2]*Vpk[1][35][2])+((fstarr[36][0]*
      Vpk[1][36][0])+(fstarr[36][1]*Vpk[1][36][1])))+(((fstarr[34][2]*
      Vpk[1][34][2])+((fstarr[34][0]*Vpk[1][33][0])+(fstarr[34][1]*Vpk[1][34][1]
      )))+(((fstarr[33][2]*Vpk[1][33][2])+((fstarr[33][0]*Vpk[1][33][0])+(
      fstarr[33][1]*Vpk[1][32][1])))+(((fstarr[30][2]*Vpk[1][29][2])+((
      fstarr[30][0]*Vpk[1][30][0])+(fstarr[30][1]*Vpk[1][30][1])))+temp[2])))));
    temp[0] = (((fstarr[12][2]*Vpk[2][12][2])+((fstarr[12][0]*Vpk[2][11][0])+(
      fstarr[12][1]*Vpk[2][12][1])))+(((fstarr[11][2]*Vpk[2][11][2])+((
      fstarr[11][0]*Vpk[2][11][0])+(fstarr[11][1]*Vpk[2][10][1])))+(((
      Cik[3][2][2]*fstarr[5][2])+((Cik[3][2][0]*fstarr[5][0])+(Cik[3][2][1]*
      fstarr[5][1])))+((fstarr[8][2]*Vpk[2][8][2])+((fstarr[8][0]*Vpk[2][8][0])+
      (fstarr[8][1]*Vpk[2][7][1]))))));
    temp[1] = (((fstarr[20][2]*Vpk[2][20][2])+((fstarr[20][0]*Vpk[2][20][0])+(
      fstarr[20][1]*Vpk[2][19][1])))+(((fstarr[18][2]*Vpk[2][18][2])+((
      fstarr[18][0]*Vpk[2][18][0])+(fstarr[18][1]*Vpk[2][17][1])))+(((
      fstarr[16][2]*Vpk[2][16][2])+((fstarr[16][0]*Vpk[2][15][0])+(fstarr[16][1]
      *Vpk[2][16][1])))+(((fstarr[14][2]*Vpk[2][14][2])+((fstarr[14][0]*
      Vpk[2][14][0])+(fstarr[14][1]*Vpk[2][13][1])))+temp[0]))));
    temp[2] = (((fstarr[28][2]*Vpk[2][28][2])+((fstarr[28][0]*Vpk[2][27][0])+(
      fstarr[28][1]*Vpk[2][28][1])))+(((fstarr[27][2]*Vpk[2][27][2])+((
      fstarr[27][0]*Vpk[2][27][0])+(fstarr[27][1]*Vpk[2][26][1])))+(((
      fstarr[24][2]*Vpk[2][24][2])+((fstarr[24][0]*Vpk[2][24][0])+(fstarr[24][1]
      *Vpk[2][23][1])))+(((fstarr[22][2]*Vpk[2][22][2])+((fstarr[22][0]*
      Vpk[2][21][0])+(fstarr[22][1]*Vpk[2][22][1])))+temp[1]))));
    trqout[2] = -(utau[2]+(((fstarr[36][2]*Vpk[2][35][2])+((fstarr[36][0]*
      Vpk[2][36][0])+(fstarr[36][1]*Vpk[2][36][1])))+(((fstarr[34][2]*
      Vpk[2][34][2])+((fstarr[34][0]*Vpk[2][33][0])+(fstarr[34][1]*Vpk[2][34][1]
      )))+(((fstarr[33][2]*Vpk[2][33][2])+((fstarr[33][0]*Vpk[2][33][0])+(
      fstarr[33][1]*Vpk[2][32][1])))+(((fstarr[30][2]*Vpk[2][29][2])+((
      fstarr[30][0]*Vpk[2][30][0])+(fstarr[30][1]*Vpk[2][30][1])))+temp[2])))));
    temp[0] = (((tstarr[5][0]+((.05*fstarr[5][1])-(.1206*fstarr[5][2])))+(((
      .14625*(fstarr[8][2]*Wpk[3][8][0]))+((.0351*(fstarr[8][1]*Wpk[3][8][0]))+(
      fstarr[8][0]*Vpk[3][8][0])))+((tstarr[8][2]*Wpk[3][8][2])+((tstarr[8][0]*
      Wpk[3][8][0])-(tstarr[8][1]*s7)))))+(((fstarr[11][2]*Vpk[3][11][2])+((
      fstarr[11][0]*Vpk[3][11][0])+(fstarr[11][1]*Vpk[3][11][1])))+((
      tstarr[11][2]*Wpk[3][11][2])+((tstarr[11][0]*Wpk[3][11][0])+(tstarr[11][1]
      *Wpk[3][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[3][14][2])+((fstarr[14][0]*Vpk[3][14][0])+(
      fstarr[14][1]*Vpk[3][14][1])))+((tstarr[14][2]*Wpk[3][14][2])+((
      tstarr[14][0]*Wpk[3][14][0])+(tstarr[14][1]*Wpk[3][13][1]))))+((((
      fstarr[12][2]*Vpk[3][12][2])+((fstarr[12][0]*Vpk[3][12][0])+(fstarr[12][1]
      *Vpk[3][12][1])))+((tstarr[12][2]*Wpk[3][12][2])+((tstarr[12][0]*
      Wpk[3][11][0])+(tstarr[12][1]*Wpk[3][12][1]))))+temp[0]));
    temp[2] = ((((fstarr[18][2]*Vpk[3][18][2])+((fstarr[18][0]*Vpk[3][18][0])+(
      fstarr[18][1]*Vpk[3][18][1])))+((tstarr[18][2]*Wpk[3][18][2])+((
      tstarr[18][0]*Wpk[3][18][0])+(tstarr[18][1]*Wpk[3][17][1]))))+((((
      fstarr[16][2]*Vpk[3][16][2])+((fstarr[16][0]*Vpk[3][16][0])+(fstarr[16][1]
      *Vpk[3][16][1])))+((tstarr[16][2]*Wpk[3][16][2])+((tstarr[16][0]*
      Wpk[3][15][0])+(tstarr[16][1]*Wpk[3][16][1]))))+temp[1]));
    temp[3] = ((((fstarr[22][2]*Vpk[3][22][2])+((fstarr[22][0]*Vpk[3][22][0])+(
      fstarr[22][1]*Vpk[3][22][1])))+((tstarr[22][2]*Wpk[3][22][2])+((
      tstarr[22][0]*Wpk[3][21][0])+(tstarr[22][1]*Wpk[3][22][1]))))+((((
      fstarr[20][2]*Vpk[3][20][2])+((fstarr[20][0]*Vpk[3][20][0])+(fstarr[20][1]
      *Vpk[3][20][1])))+((tstarr[20][2]*Wpk[3][20][2])+((tstarr[20][0]*
      Wpk[3][20][0])+(tstarr[20][1]*Wpk[3][19][1]))))+temp[2]));
    temp[4] = ((((fstarr[27][2]*Vpk[3][27][2])+((fstarr[27][0]*Vpk[3][27][0])+(
      fstarr[27][1]*Vpk[3][27][1])))+((tstarr[27][2]*Wpk[3][27][2])+((
      tstarr[27][0]*Wpk[3][27][0])-(tstarr[27][1]*s26))))+((((fstarr[24][2]*
      Vpk[3][24][2])+((fstarr[24][0]*Vpk[3][24][0])+(fstarr[24][1]*Vpk[3][24][1]
      )))+((tstarr[24][2]*Wpk[3][24][2])+((tstarr[24][0]*Wpk[3][24][0])+(
      tstarr[24][1]*Wpk[3][23][1]))))+temp[3]));
    temp[5] = ((((fstarr[30][2]*Vpk[3][30][2])+((fstarr[30][0]*Vpk[3][30][0])+(
      fstarr[30][1]*Vpk[3][30][1])))+((tstarr[30][2]*Wpk[3][29][2])+((
      tstarr[30][0]*Wpk[3][30][0])+(tstarr[30][1]*Wpk[3][30][1]))))+((((
      fstarr[28][2]*Vpk[3][28][2])+((fstarr[28][0]*Vpk[3][28][0])+(fstarr[28][1]
      *Vpk[3][28][1])))+((tstarr[28][2]*Wpk[3][28][2])+((tstarr[28][0]*
      Wpk[3][27][0])+(tstarr[28][1]*Wpk[3][28][1]))))+temp[4]));
    temp[6] = ((((fstarr[34][2]*Vpk[3][34][2])+((fstarr[34][0]*Vpk[3][34][0])+(
      fstarr[34][1]*Vpk[3][34][1])))+((tstarr[34][2]*Wpk[3][34][2])+((
      tstarr[34][0]*Wpk[3][33][0])+(tstarr[34][1]*Wpk[3][34][1]))))+((((
      fstarr[33][2]*Vpk[3][33][2])+((fstarr[33][0]*Vpk[3][33][0])+(fstarr[33][1]
      *Vpk[3][33][1])))+((tstarr[33][2]*Wpk[3][33][2])+((tstarr[33][0]*
      Wpk[3][33][0])-(tstarr[33][1]*s32))))+temp[5]));
    trqout[3] = -(utau[3]+((((fstarr[36][2]*Vpk[3][36][2])+((fstarr[36][0]*
      Vpk[3][36][0])+(fstarr[36][1]*Vpk[3][36][1])))+((tstarr[36][2]*
      Wpk[3][35][2])+((tstarr[36][0]*Wpk[3][36][0])+(tstarr[36][1]*Wpk[3][36][1]
      ))))+temp[6]));
    temp[0] = (((tstarr[5][1]-(.05*fstarr[5][0]))+(((.14625*(fstarr[8][2]*
      Wpk[4][8][0]))+((.0351*(fstarr[8][1]*Wpk[4][8][0]))+(fstarr[8][0]*
      Vpk[4][8][0])))+((tstarr[8][2]*Wpk[4][8][2])+((tstarr[8][0]*Wpk[4][8][0])+
      (tstarr[8][1]*Wpk[4][7][1])))))+(((fstarr[11][2]*Vpk[4][11][2])+((
      fstarr[11][0]*Vpk[4][11][0])+(fstarr[11][1]*Vpk[4][11][1])))+((
      tstarr[11][2]*Wpk[4][11][2])+((tstarr[11][0]*Wpk[4][11][0])+(tstarr[11][1]
      *Wpk[4][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[4][14][2])+((fstarr[14][0]*Vpk[4][14][0])+(
      fstarr[14][1]*Vpk[4][14][1])))+((tstarr[14][2]*Wpk[4][14][2])+((
      tstarr[14][0]*Wpk[4][14][0])+(tstarr[14][1]*Wpk[4][13][1]))))+((((
      fstarr[12][2]*Vpk[4][12][2])+((fstarr[12][0]*Vpk[4][12][0])+(fstarr[12][1]
      *Vpk[4][12][1])))+((tstarr[12][2]*Wpk[4][12][2])+((tstarr[12][0]*
      Wpk[4][11][0])+(tstarr[12][1]*Wpk[4][12][1]))))+temp[0]));
    temp[2] = ((((fstarr[18][2]*Vpk[4][18][2])+((fstarr[18][0]*Vpk[4][18][0])+(
      fstarr[18][1]*Vpk[4][18][1])))+((tstarr[18][2]*Wpk[4][18][2])+((
      tstarr[18][0]*Wpk[4][18][0])+(tstarr[18][1]*Wpk[4][17][1]))))+((((
      fstarr[16][2]*Vpk[4][16][2])+((fstarr[16][0]*Vpk[4][16][0])+(fstarr[16][1]
      *Vpk[4][16][1])))+((tstarr[16][2]*Wpk[4][16][2])+((tstarr[16][0]*
      Wpk[4][15][0])+(tstarr[16][1]*Wpk[4][16][1]))))+temp[1]));
    temp[3] = ((((fstarr[22][2]*Vpk[4][22][2])+((fstarr[22][0]*Vpk[4][22][0])+(
      fstarr[22][1]*Vpk[4][22][1])))+((tstarr[22][2]*Wpk[4][22][2])+((
      tstarr[22][0]*Wpk[4][21][0])+(tstarr[22][1]*Wpk[4][22][1]))))+((((
      fstarr[20][2]*Vpk[4][20][2])+((fstarr[20][0]*Vpk[4][20][0])+(fstarr[20][1]
      *Vpk[4][20][1])))+((tstarr[20][2]*Wpk[4][20][2])+((tstarr[20][0]*
      Wpk[4][20][0])+(tstarr[20][1]*Wpk[4][19][1]))))+temp[2]));
    temp[4] = ((((fstarr[27][2]*Vpk[4][27][2])+((fstarr[27][0]*Vpk[4][27][0])+(
      fstarr[27][1]*Vpk[4][27][1])))+((tstarr[27][2]*Wpk[4][27][2])+((
      tstarr[27][0]*Wpk[4][27][0])+(tstarr[27][1]*Wpk[4][26][1]))))+((((
      fstarr[24][2]*Vpk[4][24][2])+((fstarr[24][0]*Vpk[4][24][0])+(fstarr[24][1]
      *Vpk[4][24][1])))+((tstarr[24][2]*Wpk[4][24][2])+((tstarr[24][0]*
      Wpk[4][24][0])+(tstarr[24][1]*Wpk[4][23][1]))))+temp[3]));
    temp[5] = ((((fstarr[30][2]*Vpk[4][30][2])+((fstarr[30][0]*Vpk[4][30][0])+(
      fstarr[30][1]*Vpk[4][30][1])))+((tstarr[30][2]*Wpk[4][29][2])+((
      tstarr[30][0]*Wpk[4][30][0])+(tstarr[30][1]*Wpk[4][30][1]))))+((((
      fstarr[28][2]*Vpk[4][28][2])+((fstarr[28][0]*Vpk[4][28][0])+(fstarr[28][1]
      *Vpk[4][28][1])))+((tstarr[28][2]*Wpk[4][28][2])+((tstarr[28][0]*
      Wpk[4][27][0])+(tstarr[28][1]*Wpk[4][28][1]))))+temp[4]));
    temp[6] = ((((fstarr[34][2]*Vpk[4][34][2])+((fstarr[34][0]*Vpk[4][34][0])+(
      fstarr[34][1]*Vpk[4][34][1])))+((tstarr[34][2]*Wpk[4][34][2])+((
      tstarr[34][0]*Wpk[4][33][0])+(tstarr[34][1]*Wpk[4][34][1]))))+((((
      fstarr[33][2]*Vpk[4][33][2])+((fstarr[33][0]*Vpk[4][33][0])+(fstarr[33][1]
      *Vpk[4][33][1])))+((tstarr[33][2]*Wpk[4][33][2])+((tstarr[33][0]*
      Wpk[4][33][0])+(tstarr[33][1]*Wpk[4][32][1]))))+temp[5]));
    trqout[4] = -(utau[4]+((((fstarr[36][2]*Vpk[4][36][2])+((fstarr[36][0]*
      Vpk[4][36][0])+(fstarr[36][1]*Vpk[4][36][1])))+((tstarr[36][2]*
      Wpk[4][35][2])+((tstarr[36][0]*Wpk[4][36][0])+(tstarr[36][1]*Wpk[4][36][1]
      ))))+temp[6]));
    temp[0] = (((tstarr[5][2]+(.1206*fstarr[5][0]))+(((.14625*(fstarr[8][2]*
      Wpk[5][8][0]))+((.0351*(fstarr[8][1]*Wpk[5][8][0]))+(fstarr[8][0]*
      Vpk[5][8][0])))+((tstarr[8][2]*Wpk[5][8][2])+((tstarr[8][0]*Wpk[5][8][0])+
      (tstarr[8][1]*Wpk[5][7][1])))))+(((fstarr[11][2]*Vpk[5][11][2])+((
      fstarr[11][0]*Vpk[5][11][0])+(fstarr[11][1]*Vpk[5][11][1])))+((
      tstarr[11][2]*Wpk[5][11][2])+((tstarr[11][0]*Wpk[5][11][0])+(tstarr[11][1]
      *Wpk[5][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[5][14][2])+((fstarr[14][0]*Vpk[5][14][0])+(
      fstarr[14][1]*Vpk[5][14][1])))+((tstarr[14][2]*Wpk[5][14][2])+((
      tstarr[14][0]*Wpk[5][14][0])+(tstarr[14][1]*Wpk[5][13][1]))))+((((
      fstarr[12][2]*Vpk[5][12][2])+((fstarr[12][0]*Vpk[5][12][0])+(fstarr[12][1]
      *Vpk[5][12][1])))+((tstarr[12][2]*Wpk[5][12][2])+((tstarr[12][0]*
      Wpk[5][11][0])+(tstarr[12][1]*Wpk[5][12][1]))))+temp[0]));
    temp[2] = ((((fstarr[18][2]*Vpk[5][18][2])+((fstarr[18][0]*Vpk[5][18][0])+(
      fstarr[18][1]*Vpk[5][18][1])))+((tstarr[18][2]*Wpk[5][18][2])+((
      tstarr[18][0]*Wpk[5][18][0])+(tstarr[18][1]*Wpk[5][17][1]))))+((((
      fstarr[16][2]*Vpk[5][16][2])+((fstarr[16][0]*Vpk[5][16][0])+(fstarr[16][1]
      *Vpk[5][16][1])))+((tstarr[16][2]*Wpk[5][16][2])+((tstarr[16][0]*
      Wpk[5][15][0])+(tstarr[16][1]*Wpk[5][16][1]))))+temp[1]));
    temp[3] = ((((fstarr[22][2]*Vpk[5][22][2])+((fstarr[22][0]*Vpk[5][22][0])+(
      fstarr[22][1]*Vpk[5][22][1])))+((tstarr[22][2]*Wpk[5][22][2])+((
      tstarr[22][0]*Wpk[5][21][0])+(tstarr[22][1]*Wpk[5][22][1]))))+((((
      fstarr[20][2]*Vpk[5][20][2])+((fstarr[20][0]*Vpk[5][20][0])+(fstarr[20][1]
      *Vpk[5][20][1])))+((tstarr[20][2]*Wpk[5][20][2])+((tstarr[20][0]*
      Wpk[5][20][0])+(tstarr[20][1]*Wpk[5][19][1]))))+temp[2]));
    temp[4] = ((((fstarr[27][2]*Vpk[5][27][2])+((fstarr[27][0]*Vpk[5][27][0])+(
      fstarr[27][1]*Vpk[5][27][1])))+((tstarr[27][2]*Wpk[5][27][2])+((
      tstarr[27][0]*Wpk[5][27][0])+(tstarr[27][1]*Wpk[5][26][1]))))+((((
      fstarr[24][2]*Vpk[5][24][2])+((fstarr[24][0]*Vpk[5][24][0])+(fstarr[24][1]
      *Vpk[5][24][1])))+((tstarr[24][2]*Wpk[5][24][2])+((tstarr[24][0]*
      Wpk[5][24][0])+(tstarr[24][1]*Wpk[5][23][1]))))+temp[3]));
    temp[5] = ((((fstarr[30][2]*Vpk[5][30][2])+((fstarr[30][0]*Vpk[5][30][0])+(
      fstarr[30][1]*Vpk[5][30][1])))+((tstarr[30][2]*Wpk[5][29][2])+((
      tstarr[30][0]*Wpk[5][30][0])+(tstarr[30][1]*Wpk[5][30][1]))))+((((
      fstarr[28][2]*Vpk[5][28][2])+((fstarr[28][0]*Vpk[5][28][0])+(fstarr[28][1]
      *Vpk[5][28][1])))+((tstarr[28][2]*Wpk[5][28][2])+((tstarr[28][0]*
      Wpk[5][27][0])+(tstarr[28][1]*Wpk[5][28][1]))))+temp[4]));
    temp[6] = ((((fstarr[34][2]*Vpk[5][34][2])+((fstarr[34][0]*Vpk[5][34][0])+(
      fstarr[34][1]*Vpk[5][34][1])))+((tstarr[34][2]*Wpk[5][34][2])+((
      tstarr[34][0]*Wpk[5][33][0])+(tstarr[34][1]*Wpk[5][34][1]))))+((((
      fstarr[33][2]*Vpk[5][33][2])+((fstarr[33][0]*Vpk[5][33][0])+(fstarr[33][1]
      *Vpk[5][33][1])))+((tstarr[33][2]*Wpk[5][33][2])+((tstarr[33][0]*
      Wpk[5][33][0])+(tstarr[33][1]*Wpk[5][32][1]))))+temp[5]));
    trqout[5] = -(utau[5]+((((fstarr[36][2]*Vpk[5][36][2])+((fstarr[36][0]*
      Vpk[5][36][0])+(fstarr[36][1]*Vpk[5][36][1])))+((tstarr[36][2]*
      Wpk[5][35][2])+((tstarr[36][0]*Wpk[5][36][0])+(tstarr[36][1]*Wpk[5][36][1]
      ))))+temp[6]));
    temp[0] = ((((.14625*(fstarr[8][2]*Wpk[6][8][0]))+((.0351*(fstarr[8][1]*
      Wpk[6][8][0]))+(fstarr[8][0]*Vpk[6][8][0])))+((tstarr[8][2]*Wpk[6][8][2])+
      ((tstarr[8][0]*Wpk[6][8][0])-(tstarr[8][1]*s7))))+(((fstarr[11][2]*
      Vpk[6][11][2])+((fstarr[11][0]*Vpk[6][11][0])+(fstarr[11][1]*Vpk[6][11][1]
      )))+((tstarr[11][2]*Wpk[6][11][2])+((tstarr[11][0]*Wpk[6][11][0])+(
      tstarr[11][1]*Wpk[6][10][1])))));
    temp[1] = ((((fstarr[14][2]*Vpk[6][14][2])+((fstarr[14][0]*Vpk[6][14][0])+(
      fstarr[14][1]*Vpk[6][14][1])))+((tstarr[14][2]*Wpk[6][14][2])+((
      tstarr[14][0]*Wpk[6][14][0])+(tstarr[14][1]*Wpk[6][13][1]))))+((((
      fstarr[12][2]*Vpk[6][12][2])+((fstarr[12][0]*Vpk[6][12][0])+(fstarr[12][1]
      *Vpk[6][12][1])))+((tstarr[12][2]*Wpk[6][12][2])+((tstarr[12][0]*
      Wpk[6][11][0])+(tstarr[12][1]*Wpk[6][12][1]))))+temp[0]));
    temp[2] = ((((fstarr[18][2]*Vpk[6][18][2])+((fstarr[18][0]*Vpk[6][18][0])+(
      fstarr[18][1]*Vpk[6][18][1])))+((tstarr[18][2]*Wpk[6][18][2])+((
      tstarr[18][0]*Wpk[6][18][0])+(tstarr[18][1]*Wpk[6][17][1]))))+((((
      fstarr[16][2]*Vpk[6][16][2])+((fstarr[16][0]*Vpk[6][16][0])+(fstarr[16][1]
      *Vpk[6][16][1])))+((tstarr[16][2]*Wpk[6][16][2])+((tstarr[16][0]*
      Wpk[6][15][0])+(tstarr[16][1]*Wpk[6][16][1]))))+temp[1]));
    temp[3] = ((((fstarr[22][2]*Vpk[6][22][2])+((fstarr[22][0]*Vpk[6][22][0])+(
      fstarr[22][1]*Vpk[6][22][1])))+((tstarr[22][2]*Wpk[6][22][2])+((
      tstarr[22][0]*Wpk[6][21][0])+(tstarr[22][1]*Wpk[6][22][1]))))+((((
      fstarr[20][2]*Vpk[6][20][2])+((fstarr[20][0]*Vpk[6][20][0])+(fstarr[20][1]
      *Vpk[6][20][1])))+((tstarr[20][2]*Wpk[6][20][2])+((tstarr[20][0]*
      Wpk[6][20][0])+(tstarr[20][1]*Wpk[6][19][1]))))+temp[2]));
    trqout[6] = -(utau[6]+((((fstarr[24][2]*Vpk[6][24][2])+((fstarr[24][0]*
      Vpk[6][24][0])+(fstarr[24][1]*Vpk[6][24][1])))+((tstarr[24][2]*
      Wpk[6][24][2])+((tstarr[24][0]*Wpk[6][24][0])+(tstarr[24][1]*Wpk[6][23][1]
      ))))+temp[3]));
    temp[0] = ((((fstarr[11][2]*Vpk[7][11][2])+((fstarr[11][0]*Vpk[7][11][0])+(
      fstarr[11][1]*Vpk[7][11][1])))+((tstarr[11][2]*Wpk[7][11][2])+((
      tstarr[11][0]*Wpk[7][11][0])+(tstarr[11][1]*Wpk[7][10][1]))))+(((
      tstarr[8][2]*c8)-(tstarr[8][0]*s8))-((.14625*(fstarr[8][2]*s8))+((.0351*(
      fstarr[8][1]*s8))+(.14625*(fstarr[8][0]*c8))))));
    temp[1] = ((((fstarr[14][2]*Vpk[7][14][2])+((fstarr[14][0]*Vpk[7][14][0])+(
      fstarr[14][1]*Vpk[7][14][1])))+((tstarr[14][2]*Wpk[7][14][2])+((
      tstarr[14][0]*Wpk[7][14][0])+(tstarr[14][1]*Wpk[7][13][1]))))+((((
      fstarr[12][2]*Vpk[7][12][2])+((fstarr[12][0]*Vpk[7][12][0])+(fstarr[12][1]
      *Vpk[7][12][1])))+((tstarr[12][2]*Wpk[7][12][2])+((tstarr[12][0]*
      Wpk[7][11][0])+(tstarr[12][1]*Wpk[7][12][1]))))+temp[0]));
    temp[2] = ((((fstarr[18][2]*Vpk[7][18][2])+((fstarr[18][0]*Vpk[7][18][0])+(
      fstarr[18][1]*Vpk[7][18][1])))+((tstarr[18][2]*Wpk[7][18][2])+((
      tstarr[18][0]*Wpk[7][18][0])+(tstarr[18][1]*Wpk[7][17][1]))))+((((
      fstarr[16][2]*Vpk[7][16][2])+((fstarr[16][0]*Vpk[7][16][0])+(fstarr[16][1]
      *Vpk[7][16][1])))+((tstarr[16][2]*Wpk[7][16][2])+((tstarr[16][0]*
      Wpk[7][15][0])+(tstarr[16][1]*Wpk[7][16][1]))))+temp[1]));
    temp[3] = ((((fstarr[22][2]*Vpk[7][22][2])+((fstarr[22][0]*Vpk[7][22][0])+(
      fstarr[22][1]*Vpk[7][22][1])))+((tstarr[22][2]*Wpk[7][22][2])+((
      tstarr[22][0]*Wpk[7][21][0])+(tstarr[22][1]*Wpk[7][22][1]))))+((((
      fstarr[20][2]*Vpk[7][20][2])+((fstarr[20][0]*Vpk[7][20][0])+(fstarr[20][1]
      *Vpk[7][20][1])))+((tstarr[20][2]*Wpk[7][20][2])+((tstarr[20][0]*
      Wpk[7][20][0])+(tstarr[20][1]*Wpk[7][19][1]))))+temp[2]));
    trqout[7] = -(utau[7]+((((fstarr[24][2]*Vpk[7][24][2])+((fstarr[24][0]*
      Vpk[7][24][0])+(fstarr[24][1]*Vpk[7][24][1])))+((tstarr[24][2]*
      Wpk[7][24][2])+((tstarr[24][0]*Wpk[7][24][0])+(tstarr[24][1]*Wpk[7][23][1]
      ))))+temp[3]));
    temp[0] = (((tstarr[8][1]-(.0351*fstarr[8][0]))+(((fstarr[11][2]*
      Vpk[8][11][2])+((fstarr[11][0]*Vpk[8][11][0])+(fstarr[11][1]*Vpk[8][11][1]
      )))+((tstarr[11][2]*Wpk[8][11][2])+((tstarr[11][0]*Wpk[8][11][0])+(
      tstarr[11][1]*Wpk[8][10][1])))))+(((fstarr[12][2]*Vpk[8][12][2])+((
      fstarr[12][0]*Vpk[8][12][0])+(fstarr[12][1]*Vpk[8][12][1])))+((
      tstarr[12][2]*Wpk[8][12][2])+((tstarr[12][0]*Wpk[8][11][0])+(tstarr[12][1]
      *Wpk[8][12][1])))));
    temp[1] = ((((fstarr[16][2]*Vpk[8][16][2])+((fstarr[16][0]*Vpk[8][16][0])+(
      fstarr[16][1]*Vpk[8][16][1])))+((tstarr[16][2]*Wpk[8][16][2])+((
      tstarr[16][0]*Wpk[8][15][0])+(tstarr[16][1]*Wpk[8][16][1]))))+((((
      fstarr[14][2]*Vpk[8][14][2])+((fstarr[14][0]*Vpk[8][14][0])+(fstarr[14][1]
      *Vpk[8][14][1])))+((tstarr[14][2]*Wpk[8][14][2])+((tstarr[14][0]*
      Wpk[8][14][0])+(tstarr[14][1]*c13))))+temp[0]));
    temp[2] = ((((fstarr[20][2]*Vpk[8][20][2])+((fstarr[20][0]*Vpk[8][20][0])+(
      fstarr[20][1]*Vpk[8][20][1])))+((tstarr[20][2]*Wpk[8][20][2])+((
      tstarr[20][0]*Wpk[8][20][0])+(tstarr[20][1]*c19))))+((((fstarr[18][2]*
      Vpk[8][18][2])+((fstarr[18][0]*Vpk[8][18][0])+(fstarr[18][1]*Vpk[8][18][1]
      )))+((tstarr[18][2]*Wpk[8][18][2])+((tstarr[18][0]*Wpk[8][18][0])+(
      tstarr[18][1]*Wpk[8][17][1]))))+temp[1]));
    trqout[8] = -(utau[8]+((((fstarr[24][2]*Vpk[8][24][2])+((fstarr[24][0]*
      Vpk[8][24][0])+(fstarr[24][1]*Vpk[8][24][1])))+((tstarr[24][2]*
      Wpk[8][24][2])+((tstarr[24][0]*Wpk[8][24][0])+(tstarr[24][1]*Wpk[8][23][1]
      ))))+((((fstarr[22][2]*Vpk[8][22][2])+((fstarr[22][0]*Vpk[8][22][0])+(
      fstarr[22][1]*Vpk[8][22][1])))+((tstarr[22][2]*Wpk[8][22][2])+((
      tstarr[22][0]*Wpk[8][21][0])+(tstarr[22][1]*Wpk[8][22][1]))))+temp[2])));
    trqout[9] = -(utau[9]+((((.0442*(fstarr[11][2]*Wpk[9][11][0]))+((
      fstarr[11][0]*Vpk[9][11][0])-(.0065*(fstarr[11][1]*Wpk[9][11][0]))))+((
      tstarr[11][2]*Wpk[9][11][2])+((tstarr[11][0]*Wpk[9][11][0])-(tstarr[11][1]
      *s10))))+(((fstarr[12][2]*Vpk[9][12][2])+((fstarr[12][0]*Vpk[9][12][0])+(
      fstarr[12][1]*Vpk[9][12][1])))+((tstarr[12][2]*Wpk[9][12][2])+((
      tstarr[12][0]*Wpk[9][11][0])+(tstarr[12][1]*Wpk[9][12][1]))))));
    trqout[10] = -(utau[10]+((((fstarr[12][2]*Vpk[10][12][2])+((fstarr[12][0]*
      Vpk[10][12][0])+(fstarr[12][1]*Vpk[10][12][1])))+((tstarr[12][2]*
      Wpk[10][12][2])+((tstarr[12][1]*Wpk[10][12][1])-(tstarr[12][0]*s11))))+(((
      tstarr[11][2]*c11)-(tstarr[11][0]*s11))+(((.0065*(fstarr[11][1]*s11))-(
      .0442*(fstarr[11][0]*c11)))-(.0442*(fstarr[11][2]*s11))))));
    trqout[11] = -(utau[11]+((tstarr[11][1]+(.0065*fstarr[11][0]))+((
      fstarr[12][0]*Vpk[11][12][0])+((tstarr[12][1]*c12)-(tstarr[12][2]*s12)))))
      ;
    trqout[12] = -(utau[12]+(tstarr[12][0]+((.078*fstarr[12][2])-(.0312*
      fstarr[12][1]))));
    temp[0] = (((fstarr[14][1]*Vpk[13][14][1])+((tstarr[14][2]*c14)-(
      tstarr[14][0]*s14)))+(((fstarr[16][2]*Vpk[13][16][2])+((fstarr[16][1]*
      Vpk[13][16][1])-(.0039*(fstarr[16][0]*Wpk[13][16][2]))))+((tstarr[16][2]*
      Wpk[13][16][2])+((tstarr[16][0]*Wpk[13][15][0])+(tstarr[16][1]*
      Wpk[13][16][1])))));
    trqout[13] = -(utau[13]+(temp[0]+(((fstarr[18][2]*Vpk[13][18][2])+((
      fstarr[18][0]*Vpk[13][18][0])+(fstarr[18][1]*Vpk[13][18][1])))+((
      tstarr[18][2]*Wpk[13][18][2])+((tstarr[18][0]*Wpk[13][18][0])+(
      tstarr[18][1]*Wpk[13][17][1]))))));
    trqout[14] = -(utau[14]+(((tstarr[14][1]+((.0013*fstarr[14][0])-(.1326*
      fstarr[14][2])))+(((fstarr[16][2]*Vpk[14][16][2])+((fstarr[16][0]*
      Vpk[14][16][0])+(fstarr[16][1]*Vpk[14][16][1])))+((tstarr[16][1]*c16)-(
      tstarr[16][2]*s16))))+(((fstarr[18][2]*Vpk[14][18][2])+((fstarr[18][0]*
      Vpk[14][18][0])+(fstarr[18][1]*Vpk[14][18][1])))+((tstarr[18][2]*
      Wpk[14][18][2])+((tstarr[18][0]*Wpk[14][18][0])+(tstarr[18][1]*
      Wpk[14][17][1]))))));
    trqout[15] = -(utau[15]+((((fstarr[18][2]*Vpk[15][18][2])+((fstarr[18][0]*
      Vpk[15][18][0])+(fstarr[18][1]*Vpk[15][18][1])))+((tstarr[18][2]*
      Wpk[15][18][2])+((tstarr[18][0]*Wpk[15][18][0])+(tstarr[18][1]*
      Wpk[15][17][1]))))+(((tstarr[16][1]*c16)-(tstarr[16][2]*s16))+(((.0039*(
      fstarr[16][0]*s16))-(.1378*(fstarr[16][1]*s16)))-(.1378*(fstarr[16][2]*c16
      ))))));
    trqout[16] = -(utau[16]+((tstarr[16][0]+(.0039*fstarr[16][2]))+(((
      fstarr[18][2]*Vpk[16][18][2])+((.065*(fstarr[18][1]*Wpk[16][18][2]))-(
      .0078*(fstarr[18][0]*s18))))+((tstarr[18][2]*Wpk[16][18][2])+((
      tstarr[18][0]*Wpk[16][18][0])-(tstarr[18][1]*s17))))));
    trqout[17] = -(utau[17]+((.065*(fstarr[18][1]*c18))+((tstarr[18][2]*c18)-(
      tstarr[18][0]*s18))));
    trqout[18] = -(utau[18]+(tstarr[18][1]-(.065*fstarr[18][2])));
    temp[0] = (((fstarr[20][1]*Vpk[19][20][1])+((tstarr[20][2]*c20)-(
      tstarr[20][0]*s20)))+(((fstarr[22][2]*Vpk[19][22][2])+((fstarr[22][1]*
      Vpk[19][22][1])-(.0039*(fstarr[22][0]*Wpk[19][22][2]))))+((tstarr[22][2]*
      Wpk[19][22][2])+((tstarr[22][0]*Wpk[19][21][0])+(tstarr[22][1]*
      Wpk[19][22][1])))));
    trqout[19] = -(utau[19]+(temp[0]+(((fstarr[24][2]*Vpk[19][24][2])+((
      fstarr[24][0]*Vpk[19][24][0])+(fstarr[24][1]*Vpk[19][24][1])))+((
      tstarr[24][2]*Wpk[19][24][2])+((tstarr[24][0]*Wpk[19][24][0])+(
      tstarr[24][1]*Wpk[19][23][1]))))));
    trqout[20] = -(utau[20]+(((tstarr[20][1]+((.0013*fstarr[20][0])+(.1326*
      fstarr[20][2])))+(((fstarr[22][2]*Vpk[20][22][2])+((fstarr[22][0]*
      Vpk[20][22][0])+(fstarr[22][1]*Vpk[20][22][1])))+((tstarr[22][1]*c22)-(
      tstarr[22][2]*s22))))+(((fstarr[24][2]*Vpk[20][24][2])+((fstarr[24][0]*
      Vpk[20][24][0])+(fstarr[24][1]*Vpk[20][24][1])))+((tstarr[24][2]*
      Wpk[20][24][2])+((tstarr[24][0]*Wpk[20][24][0])+(tstarr[24][1]*
      Wpk[20][23][1]))))));
    trqout[21] = -(utau[21]+((((.1378*(fstarr[22][2]*c22))+((.0039*(
      fstarr[22][0]*s22))+(.1378*(fstarr[22][1]*s22))))+((tstarr[22][1]*c22)-(
      tstarr[22][2]*s22)))+(((fstarr[24][2]*Vpk[21][24][2])+((fstarr[24][0]*
      Vpk[21][24][0])+(fstarr[24][1]*Vpk[21][24][1])))+((tstarr[24][2]*
      Wpk[21][24][2])+((tstarr[24][0]*Wpk[21][24][0])+(tstarr[24][1]*
      Wpk[21][23][1]))))));
    trqout[22] = -(utau[22]+((tstarr[22][0]+(.0039*fstarr[22][2]))+(((
      fstarr[24][2]*Vpk[22][24][2])-((.0078*(fstarr[24][0]*s24))+(.065*(
      fstarr[24][1]*Wpk[22][24][2]))))+((tstarr[24][2]*Wpk[22][24][2])+((
      tstarr[24][0]*Wpk[22][24][0])-(tstarr[24][1]*s23))))));
    trqout[23] = -(utau[23]+(((tstarr[24][2]*c24)-(tstarr[24][0]*s24))-(.065*(
      fstarr[24][1]*c24))));
    trqout[24] = -(utau[24]+(tstarr[24][1]+(.065*fstarr[24][2])));
    temp[0] = ((((fstarr[27][2]*Vpk[25][27][2])+((fstarr[27][0]*Vpk[25][27][0])+
      (fstarr[27][1]*Vpk[25][27][1])))+((tstarr[27][2]*Wpk[25][27][2])+((
      tstarr[27][0]*Wpk[25][27][0])-(tstarr[27][1]*s26))))+(((fstarr[28][2]*
      Vpk[25][28][2])+((fstarr[28][0]*Vpk[25][28][0])+(fstarr[28][1]*
      Vpk[25][28][1])))+((tstarr[28][2]*Wpk[25][28][2])+((tstarr[28][0]*
      Wpk[25][27][0])+(tstarr[28][1]*Wpk[25][28][1])))));
    trqout[25] = -(utau[25]+((((fstarr[30][2]*Vpk[25][30][2])+((fstarr[30][0]*
      Vpk[25][30][0])+(fstarr[30][1]*Vpk[25][30][1])))+((tstarr[30][2]*
      Wpk[25][29][2])+((tstarr[30][0]*Wpk[25][30][0])+(tstarr[30][1]*
      Wpk[25][30][1]))))+temp[0]));
    temp[0] = ((((.2379*(fstarr[27][2]*s27))+((.2379*(fstarr[27][0]*c27))+(
      fstarr[27][1]*Vpk[26][27][1])))+((tstarr[27][2]*c27)-(tstarr[27][0]*s27)))
      +(((fstarr[28][2]*Vpk[26][28][2])+((fstarr[28][0]*Vpk[26][28][0])+(
      fstarr[28][1]*Vpk[26][28][1])))+((tstarr[28][2]*Wpk[26][28][2])+((
      tstarr[28][1]*Wpk[26][28][1])-(tstarr[28][0]*s27)))));
    trqout[26] = -(utau[26]+((((fstarr[30][2]*Vpk[26][30][2])+((fstarr[30][0]*
      Vpk[26][30][0])+(fstarr[30][1]*Vpk[26][30][1])))+((tstarr[30][2]*
      Wpk[26][29][2])+((tstarr[30][0]*Wpk[26][30][0])+(tstarr[30][1]*
      Wpk[26][30][1]))))+temp[0]));
    trqout[27] = -(utau[27]+(((tstarr[27][1]+((.0143*fstarr[27][0])+(.0169*
      fstarr[27][2])))+(((.0416*(fstarr[28][2]*c28))+((.0416*(fstarr[28][1]*s28)
      )+(fstarr[28][0]*Vpk[27][28][0])))+((tstarr[28][1]*c28)-(tstarr[28][2]*s28
      ))))+(((fstarr[30][2]*Vpk[27][30][2])+((fstarr[30][0]*Vpk[27][30][0])+(
      fstarr[30][1]*Vpk[27][30][1])))+((tstarr[30][2]*Wpk[27][29][2])+((
      tstarr[30][0]*Wpk[27][30][0])+(tstarr[30][1]*Wpk[27][30][1]))))));
    trqout[28] = -(utau[28]+((tstarr[28][0]+((.0039*fstarr[28][1])-(.2158*
      fstarr[28][2])))+(((fstarr[30][2]*Vpk[28][30][2])+((fstarr[30][0]*
      Vpk[28][30][0])+(fstarr[30][1]*Vpk[28][30][1])))+((tstarr[30][0]*c30)-(
      tstarr[30][1]*s30)))));
    trqout[29] = -(utau[29]+(((tstarr[30][0]*c30)-(tstarr[30][1]*s30))-((.039*((
      fstarr[30][0]*s30)+(fstarr[30][1]*c30)))+(.0442*(fstarr[30][2]*c30)))));
    trqout[30] = -(utau[30]+(tstarr[30][2]+(.0442*fstarr[30][0])));
    temp[0] = ((((fstarr[33][2]*Vpk[31][33][2])+((fstarr[33][0]*Vpk[31][33][0])+
      (fstarr[33][1]*Vpk[31][33][1])))+((tstarr[33][2]*Wpk[31][33][2])+((
      tstarr[33][0]*Wpk[31][33][0])-(tstarr[33][1]*s32))))+(((fstarr[34][2]*
      Vpk[31][34][2])+((fstarr[34][0]*Vpk[31][34][0])+(fstarr[34][1]*
      Vpk[31][34][1])))+((tstarr[34][2]*Wpk[31][34][2])+((tstarr[34][0]*
      Wpk[31][33][0])+(tstarr[34][1]*Wpk[31][34][1])))));
    trqout[31] = -(utau[31]+((((fstarr[36][2]*Vpk[31][36][2])+((fstarr[36][0]*
      Vpk[31][36][0])+(fstarr[36][1]*Vpk[31][36][1])))+((tstarr[36][2]*
      Wpk[31][35][2])+((tstarr[36][0]*Wpk[31][36][0])+(tstarr[36][1]*
      Wpk[31][36][1]))))+temp[0]));
    temp[0] = ((((.2379*(fstarr[33][2]*s33))+((.2379*(fstarr[33][0]*c33))+(
      fstarr[33][1]*Vpk[32][33][1])))+((tstarr[33][2]*c33)-(tstarr[33][0]*s33)))
      +(((fstarr[34][2]*Vpk[32][34][2])+((fstarr[34][0]*Vpk[32][34][0])+(
      fstarr[34][1]*Vpk[32][34][1])))+((tstarr[34][2]*Wpk[32][34][2])+((
      tstarr[34][1]*Wpk[32][34][1])-(tstarr[34][0]*s33)))));
    trqout[32] = -(utau[32]+((((fstarr[36][2]*Vpk[32][36][2])+((fstarr[36][0]*
      Vpk[32][36][0])+(fstarr[36][1]*Vpk[32][36][1])))+((tstarr[36][2]*
      Wpk[32][35][2])+((tstarr[36][0]*Wpk[32][36][0])+(tstarr[36][1]*
      Wpk[32][36][1]))))+temp[0]));
    trqout[33] = -(utau[33]+(((tstarr[33][1]+((.0143*fstarr[33][0])-(.0169*
      fstarr[33][2])))+(((tstarr[34][1]*c34)-(tstarr[34][2]*s34))+(((
      fstarr[34][0]*Vpk[33][34][0])-(.0416*(fstarr[34][1]*s34)))-(.0416*(
      fstarr[34][2]*c34)))))+(((fstarr[36][2]*Vpk[33][36][2])+((fstarr[36][0]*
      Vpk[33][36][0])+(fstarr[36][1]*Vpk[33][36][1])))+((tstarr[36][2]*
      Wpk[33][35][2])+((tstarr[36][0]*Wpk[33][36][0])+(tstarr[36][1]*
      Wpk[33][36][1]))))));
    trqout[34] = -(utau[34]+((tstarr[34][0]+((.0039*fstarr[34][1])-(.2158*
      fstarr[34][2])))+(((fstarr[36][2]*Vpk[34][36][2])+((fstarr[36][0]*
      Vpk[34][36][0])+(fstarr[36][1]*Vpk[34][36][1])))+((tstarr[36][0]*c36)-(
      tstarr[36][1]*s36)))));
    trqout[35] = -(utau[35]+(((tstarr[36][0]*c36)-(tstarr[36][1]*s36))-((.039*((
      fstarr[36][0]*s36)+(fstarr[36][1]*c36)))+(.0442*(fstarr[36][2]*c36)))));
    trqout[36] = -(utau[36]+(tstarr[36][2]+(.0442*fstarr[36][0])));
/*
Op counts below do not include called subroutines
*/
/*
 Used 3.31 seconds CPU time,
 40960 additional bytes of memory.
 Equations contain 1570 adds/subtracts/negates
                   1675 multiplies
                      0 divides
                    401 assignments
*/
}

void skel18comptrq(double *udotin, double *trqout)
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    double multin[1];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(60,23);
        return;
    }
    skel18fulltrq(udotin,multin,trqout);
}

void skel18multtrq(double *multin, double *trqout)
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(65,23);
        return;
    }
    for (i = 0; i < 37; i++) {
        trqout[i] = 0.;
    }
}

void skel18fs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
    fs[5] = fs0[5];
    fs[6] = fs0[6];
    fs[7] = fs0[7];
    fs[8] = fs0[8];
    fs[9] = fs0[9];
    fs[10] = fs0[10];
    fs[11] = fs0[11];
    fs[12] = fs0[12];
    fs[13] = fs0[13];
    fs[14] = fs0[14];
    fs[15] = fs0[15];
    fs[16] = fs0[16];
    fs[17] = fs0[17];
    fs[18] = fs0[18];
    fs[19] = fs0[19];
    fs[20] = fs0[20];
    fs[21] = fs0[21];
    fs[22] = fs0[22];
    fs[23] = fs0[23];
    fs[24] = fs0[24];
    fs[25] = fs0[25];
    fs[26] = fs0[26];
    fs[27] = fs0[27];
    fs[28] = fs0[28];
    fs[29] = fs0[29];
    fs[30] = fs0[30];
    fs[31] = fs0[31];
    fs[32] = fs0[32];
    fs[33] = fs0[33];
    fs[34] = fs0[34];
    fs[35] = fs0[35];
    fs[36] = fs0[36];
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18fsmult(void)
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 37; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18fsfull(void)
{

/*
Compute Fs (including all forces)
*/
    skel18fsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
    fs[21] = (fs[21]+fs0[21]);
    fs[22] = (fs[22]+fs0[22]);
    fs[23] = (fs[23]+fs0[23]);
    fs[24] = (fs[24]+fs0[24]);
    fs[25] = (fs[25]+fs0[25]);
    fs[26] = (fs[26]+fs0[26]);
    fs[27] = (fs[27]+fs0[27]);
    fs[28] = (fs[28]+fs0[28]);
    fs[29] = (fs[29]+fs0[29]);
    fs[30] = (fs[30]+fs0[30]);
    fs[31] = (fs[31]+fs0[31]);
    fs[32] = (fs[32]+fs0[32]);
    fs[33] = (fs[33]+fs0[33]);
    fs[34] = (fs[34]+fs0[34]);
    fs[35] = (fs[35]+fs0[35]);
    fs[36] = (fs[36]+fs0[36]);
/*
 Used 0.03 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   37 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18fsgenmult(void)
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 37; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18fsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    skel18fsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
    fs[21] = (fs[21]+fs0[21]);
    fs[22] = (fs[22]+fs0[22]);
    fs[23] = (fs[23]+fs0[23]);
    fs[24] = (fs[24]+fs0[24]);
    fs[25] = (fs[25]+fs0[25]);
    fs[26] = (fs[26]+fs0[26]);
    fs[27] = (fs[27]+fs0[27]);
    fs[28] = (fs[28]+fs0[28]);
    fs[29] = (fs[29]+fs0[29]);
    fs[30] = (fs[30]+fs0[30]);
    fs[31] = (fs[31]+fs0[31]);
    fs[32] = (fs[32]+fs0[32]);
    fs[33] = (fs[33]+fs0[33]);
    fs[34] = (fs[34]+fs0[34]);
    fs[35] = (fs[35]+fs0[35]);
    fs[36] = (fs[36]+fs0[36]);
/*
 Used 0.03 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   37 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18rhs(void)
{
/*
Generated 23-Nov-1999 14:31:05 by SD/FAST, Kane's formulation
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
    tauc[0] = utau[0];
    tauc[1] = utau[1];
    tauc[2] = utau[2];
    tauc[3] = utau[3];
    tauc[4] = utau[4];
    tauc[5] = utau[5];
    tauc[6] = utau[6];
    tauc[7] = utau[7];
    tauc[8] = utau[8];
    tauc[9] = utau[9];
    tauc[10] = utau[10];
    tauc[11] = utau[11];
    tauc[12] = utau[12];
    tauc[13] = utau[13];
    tauc[14] = utau[14];
    tauc[15] = utau[15];
    tauc[16] = utau[16];
    tauc[17] = utau[17];
    tauc[18] = utau[18];
    tauc[19] = utau[19];
    tauc[20] = utau[20];
    tauc[21] = utau[21];
    tauc[22] = utau[22];
    tauc[23] = utau[23];
    tauc[24] = utau[24];
    tauc[25] = utau[25];
    tauc[26] = utau[26];
    tauc[27] = utau[27];
    tauc[28] = utau[28];
    tauc[29] = utau[29];
    tauc[30] = utau[30];
    tauc[31] = utau[31];
    tauc[32] = utau[32];
    tauc[33] = utau[33];
    tauc[34] = utau[34];
    tauc[35] = utau[35];
    tauc[36] = utau[36];
    skel18doiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[6][0] = (udot[3]+udot[6]);
    Onkb[6][1] = ((udot[4]*c6)+(udot[5]*s6));
    Onkb[6][2] = ((udot[5]*c6)-(udot[4]*s6));
    Onkb[7][0] = ((Onkb[6][0]*c7)+(Onkb[6][1]*s7));
    Onkb[7][1] = ((Onkb[6][1]*c7)-(Onkb[6][0]*s7));
    Onkb[7][2] = (Onkb[6][2]+udot[7]);
    Onkb[8][0] = ((Onkb[7][0]*c8)-(Onkb[7][2]*s8));
    Onkb[8][1] = (Onkb[7][1]+udot[8]);
    Onkb[8][2] = ((Onkb[7][0]*s8)+(Onkb[7][2]*c8));
    Onkb[9][0] = (Onkb[8][0]+udot[9]);
    Onkb[9][1] = ((Onkb[8][1]*c9)+(Onkb[8][2]*s9));
    Onkb[9][2] = ((Onkb[8][2]*c9)-(Onkb[8][1]*s9));
    Onkb[10][0] = ((Onkb[9][0]*c10)+(Onkb[9][1]*s10));
    Onkb[10][1] = ((Onkb[9][1]*c10)-(Onkb[9][0]*s10));
    Onkb[10][2] = (Onkb[9][2]+udot[10]);
    Onkb[11][0] = ((Onkb[10][0]*c11)-(Onkb[10][2]*s11));
    Onkb[11][1] = (Onkb[10][1]+udot[11]);
    Onkb[11][2] = ((Onkb[10][0]*s11)+(Onkb[10][2]*c11));
    Onkb[12][0] = (Onkb[11][0]+udot[12]);
    Onkb[12][1] = ((Onkb[11][1]*c12)+(Onkb[11][2]*s12));
    Onkb[12][2] = ((Onkb[11][2]*c12)-(Onkb[11][1]*s12));
    Onkb[13][0] = ((Onkb[8][0]*c13)+(Onkb[8][1]*s13));
    Onkb[13][1] = ((Onkb[8][1]*c13)-(Onkb[8][0]*s13));
    Onkb[13][2] = (Onkb[8][2]+udot[13]);
    Onkb[14][0] = ((Onkb[13][0]*c14)-(Onkb[13][2]*s14));
    Onkb[14][1] = (Onkb[13][1]+udot[14]);
    Onkb[14][2] = ((Onkb[13][0]*s14)+(Onkb[13][2]*c14));
    Onkb[15][0] = ((Onkb[14][0]*c15)-(Onkb[14][2]*s15));
    Onkb[15][1] = (Onkb[14][1]+udot[15]);
    Onkb[15][2] = ((Onkb[14][0]*s15)+(Onkb[14][2]*c15));
    Onkb[16][0] = (Onkb[15][0]+udot[16]);
    Onkb[16][1] = ((Onkb[15][1]*c16)+(Onkb[15][2]*s16));
    Onkb[16][2] = ((Onkb[15][2]*c16)-(Onkb[15][1]*s16));
    Onkb[17][0] = ((Onkb[16][0]*c17)+(Onkb[16][1]*s17));
    Onkb[17][1] = ((Onkb[16][1]*c17)-(Onkb[16][0]*s17));
    Onkb[17][2] = (Onkb[16][2]+udot[17]);
    Onkb[18][0] = ((Onkb[17][0]*c18)-(Onkb[17][2]*s18));
    Onkb[18][1] = (Onkb[17][1]+udot[18]);
    Onkb[18][2] = ((Onkb[17][0]*s18)+(Onkb[17][2]*c18));
    Onkb[19][0] = ((Onkb[8][0]*c19)+(Onkb[8][1]*s19));
    Onkb[19][1] = ((Onkb[8][1]*c19)-(Onkb[8][0]*s19));
    Onkb[19][2] = (Onkb[8][2]+udot[19]);
    Onkb[20][0] = ((Onkb[19][0]*c20)-(Onkb[19][2]*s20));
    Onkb[20][1] = (Onkb[19][1]+udot[20]);
    Onkb[20][2] = ((Onkb[19][0]*s20)+(Onkb[19][2]*c20));
    Onkb[21][0] = ((Onkb[20][0]*c21)-(Onkb[20][2]*s21));
    Onkb[21][1] = (Onkb[20][1]+udot[21]);
    Onkb[21][2] = ((Onkb[20][0]*s21)+(Onkb[20][2]*c21));
    Onkb[22][0] = (Onkb[21][0]+udot[22]);
    Onkb[22][1] = ((Onkb[21][1]*c22)+(Onkb[21][2]*s22));
    Onkb[22][2] = ((Onkb[21][2]*c22)-(Onkb[21][1]*s22));
    Onkb[23][0] = ((Onkb[22][0]*c23)+(Onkb[22][1]*s23));
    Onkb[23][1] = ((Onkb[22][1]*c23)-(Onkb[22][0]*s23));
    Onkb[23][2] = (Onkb[22][2]+udot[23]);
    Onkb[24][0] = ((Onkb[23][0]*c24)-(Onkb[23][2]*s24));
    Onkb[24][1] = (Onkb[23][1]+udot[24]);
    Onkb[24][2] = ((Onkb[23][0]*s24)+(Onkb[23][2]*c24));
    Onkb[25][0] = (udot[3]+udot[25]);
    Onkb[25][1] = ((udot[4]*c25)+(udot[5]*s25));
    Onkb[25][2] = ((udot[5]*c25)-(udot[4]*s25));
    Onkb[26][0] = ((Onkb[25][0]*c26)+(Onkb[25][1]*s26));
    Onkb[26][1] = ((Onkb[25][1]*c26)-(Onkb[25][0]*s26));
    Onkb[26][2] = (Onkb[25][2]+udot[26]);
    Onkb[27][0] = ((Onkb[26][0]*c27)-(Onkb[26][2]*s27));
    Onkb[27][1] = (Onkb[26][1]+udot[27]);
    Onkb[27][2] = ((Onkb[26][0]*s27)+(Onkb[26][2]*c27));
    Onkb[28][0] = (Onkb[27][0]+udot[28]);
    Onkb[28][1] = ((Onkb[27][1]*c28)+(Onkb[27][2]*s28));
    Onkb[28][2] = ((Onkb[27][2]*c28)-(Onkb[27][1]*s28));
    Onkb[29][0] = (Onkb[28][0]+udot[29]);
    Onkb[29][1] = ((Onkb[28][1]*c29)+(Onkb[28][2]*s29));
    Onkb[29][2] = ((Onkb[28][2]*c29)-(Onkb[28][1]*s29));
    Onkb[30][0] = ((Onkb[29][0]*c30)+(Onkb[29][1]*s30));
    Onkb[30][1] = ((Onkb[29][1]*c30)-(Onkb[29][0]*s30));
    Onkb[30][2] = (Onkb[29][2]+udot[30]);
    Onkb[31][0] = (udot[3]+udot[31]);
    Onkb[31][1] = ((udot[4]*c31)+(udot[5]*s31));
    Onkb[31][2] = ((udot[5]*c31)-(udot[4]*s31));
    Onkb[32][0] = ((Onkb[31][0]*c32)+(Onkb[31][1]*s32));
    Onkb[32][1] = ((Onkb[31][1]*c32)-(Onkb[31][0]*s32));
    Onkb[32][2] = (Onkb[31][2]+udot[32]);
    Onkb[33][0] = ((Onkb[32][0]*c33)-(Onkb[32][2]*s33));
    Onkb[33][1] = (Onkb[32][1]+udot[33]);
    Onkb[33][2] = ((Onkb[32][0]*s33)+(Onkb[32][2]*c33));
    Onkb[34][0] = (Onkb[33][0]+udot[34]);
    Onkb[34][1] = ((Onkb[33][1]*c34)+(Onkb[33][2]*s34));
    Onkb[34][2] = ((Onkb[33][2]*c34)-(Onkb[33][1]*s34));
    Onkb[35][0] = (Onkb[34][0]+udot[35]);
    Onkb[35][1] = ((Onkb[34][1]*c35)+(Onkb[34][2]*s35));
    Onkb[35][2] = ((Onkb[34][2]*c35)-(Onkb[34][1]*s35));
    Onkb[36][0] = ((Onkb[35][0]*c36)+(Onkb[35][1]*s36));
    Onkb[36][1] = ((Onkb[35][1]*c36)-(Onkb[35][0]*s36));
    Onkb[36][2] = (Onkb[35][2]+udot[36]);
    onk[8][0] = (Onkb[8][0]+Otk[8][0]);
    onk[8][1] = (Onkb[8][1]+Otk[7][1]);
    onk[8][2] = (Onkb[8][2]+Otk[8][2]);
    onk[11][0] = (Onkb[11][0]+Otk[11][0]);
    onk[11][1] = (Onkb[11][1]+Otk[10][1]);
    onk[11][2] = (Onkb[11][2]+Otk[11][2]);
    onk[12][0] = (Onkb[12][0]+Otk[11][0]);
    onk[12][1] = (Onkb[12][1]+Otk[12][1]);
    onk[12][2] = (Onkb[12][2]+Otk[12][2]);
    onk[14][0] = (Onkb[14][0]+Otk[14][0]);
    onk[14][1] = (Onkb[14][1]+Otk[13][1]);
    onk[14][2] = (Onkb[14][2]+Otk[14][2]);
    onk[16][0] = (Onkb[16][0]+Otk[15][0]);
    onk[16][1] = (Onkb[16][1]+Otk[16][1]);
    onk[16][2] = (Onkb[16][2]+Otk[16][2]);
    onk[18][0] = (Onkb[18][0]+Otk[18][0]);
    onk[18][1] = (Onkb[18][1]+Otk[17][1]);
    onk[18][2] = (Onkb[18][2]+Otk[18][2]);
    onk[20][0] = (Onkb[20][0]+Otk[20][0]);
    onk[20][1] = (Onkb[20][1]+Otk[19][1]);
    onk[20][2] = (Onkb[20][2]+Otk[20][2]);
    onk[22][0] = (Onkb[22][0]+Otk[21][0]);
    onk[22][1] = (Onkb[22][1]+Otk[22][1]);
    onk[22][2] = (Onkb[22][2]+Otk[22][2]);
    onk[24][0] = (Onkb[24][0]+Otk[24][0]);
    onk[24][1] = (Onkb[24][1]+Otk[23][1]);
    onk[24][2] = (Onkb[24][2]+Otk[24][2]);
    onk[27][0] = (Onkb[27][0]+Otk[27][0]);
    onk[27][1] = (Onkb[27][1]+Otk[26][1]);
    onk[27][2] = (Onkb[27][2]+Otk[27][2]);
    onk[28][0] = (Onkb[28][0]+Otk[27][0]);
    onk[28][1] = (Onkb[28][1]+Otk[28][1]);
    onk[28][2] = (Onkb[28][2]+Otk[28][2]);
    onk[30][0] = (Onkb[30][0]+Otk[30][0]);
    onk[30][1] = (Onkb[30][1]+Otk[30][1]);
    onk[30][2] = (Onkb[30][2]+Otk[29][2]);
    onk[33][0] = (Onkb[33][0]+Otk[33][0]);
    onk[33][1] = (Onkb[33][1]+Otk[32][1]);
    onk[33][2] = (Onkb[33][2]+Otk[33][2]);
    onk[34][0] = (Onkb[34][0]+Otk[33][0]);
    onk[34][1] = (Onkb[34][1]+Otk[34][1]);
    onk[34][2] = (Onkb[34][2]+Otk[34][2]);
    onk[36][0] = (Onkb[36][0]+Otk[36][0]);
    onk[36][1] = (Onkb[36][1]+Otk[36][1]);
    onk[36][2] = (Onkb[36][2]+Otk[35][2]);
    onb[0][0] = udot[3];
    onb[0][1] = udot[4];
    onb[0][2] = udot[5];
    onb[1][0] = onk[8][0];
    onb[1][1] = onk[8][1];
    onb[1][2] = onk[8][2];
    onb[2][0] = onk[11][0];
    onb[2][1] = onk[11][1];
    onb[2][2] = onk[11][2];
    onb[3][0] = onk[12][0];
    onb[3][1] = onk[12][1];
    onb[3][2] = onk[12][2];
    onb[4][0] = onk[14][0];
    onb[4][1] = onk[14][1];
    onb[4][2] = onk[14][2];
    onb[5][0] = onk[16][0];
    onb[5][1] = onk[16][1];
    onb[5][2] = onk[16][2];
    onb[6][0] = onk[18][0];
    onb[6][1] = onk[18][1];
    onb[6][2] = onk[18][2];
    onb[7][0] = onk[20][0];
    onb[7][1] = onk[20][1];
    onb[7][2] = onk[20][2];
    onb[8][0] = onk[22][0];
    onb[8][1] = onk[22][1];
    onb[8][2] = onk[22][2];
    onb[9][0] = onk[24][0];
    onb[9][1] = onk[24][1];
    onb[9][2] = onk[24][2];
    onb[10][0] = onk[27][0];
    onb[10][1] = onk[27][1];
    onb[10][2] = onk[27][2];
    onb[11][0] = onk[28][0];
    onb[11][1] = onk[28][1];
    onb[11][2] = onk[28][2];
    onb[12][0] = onk[30][0];
    onb[12][1] = onk[30][1];
    onb[12][2] = onk[30][2];
    onb[13][0] = onk[33][0];
    onb[13][1] = onk[33][1];
    onb[13][2] = onk[33][2];
    onb[14][0] = onk[34][0];
    onb[14][1] = onk[34][1];
    onb[14][2] = onk[34][2];
    onb[15][0] = onk[36][0];
    onb[15][1] = onk[36][1];
    onb[15][2] = onk[36][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-udot[5]);
    dyad[0][0][2] = (udot[4]+w0w2[0]);
    dyad[0][1][0] = (udot[5]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-udot[3]);
    dyad[0][2][0] = (w0w2[0]-udot[4]);
    dyad[0][2][1] = (udot[3]+w1w2[0]);
    dyad[0][2][2] = w00w11[0];
    dyad[1][0][0] = w11w22[1];
    dyad[1][0][1] = (w0w1[1]-onk[8][2]);
    dyad[1][0][2] = (onk[8][1]+w0w2[1]);
    dyad[1][1][0] = (onk[8][2]+w0w1[1]);
    dyad[1][1][1] = w00w22[1];
    dyad[1][1][2] = (w1w2[1]-onk[8][0]);
    dyad[1][2][0] = (w0w2[1]-onk[8][1]);
    dyad[1][2][1] = (onk[8][0]+w1w2[1]);
    dyad[1][2][2] = w00w11[1];
    dyad[2][0][0] = w11w22[2];
    dyad[2][0][1] = (w0w1[2]-onk[11][2]);
    dyad[2][0][2] = (onk[11][1]+w0w2[2]);
    dyad[2][1][0] = (onk[11][2]+w0w1[2]);
    dyad[2][1][1] = w00w22[2];
    dyad[2][1][2] = (w1w2[2]-onk[11][0]);
    dyad[2][2][0] = (w0w2[2]-onk[11][1]);
    dyad[2][2][1] = (onk[11][0]+w1w2[2]);
    dyad[2][2][2] = w00w11[2];
    dyad[3][0][0] = w11w22[3];
    dyad[3][0][1] = (w0w1[3]-onk[12][2]);
    dyad[3][0][2] = (onk[12][1]+w0w2[3]);
    dyad[3][1][0] = (onk[12][2]+w0w1[3]);
    dyad[3][1][1] = w00w22[3];
    dyad[3][1][2] = (w1w2[3]-onk[12][0]);
    dyad[3][2][0] = (w0w2[3]-onk[12][1]);
    dyad[3][2][1] = (onk[12][0]+w1w2[3]);
    dyad[3][2][2] = w00w11[3];
    dyad[4][0][0] = w11w22[4];
    dyad[4][0][1] = (w0w1[4]-onk[14][2]);
    dyad[4][0][2] = (onk[14][1]+w0w2[4]);
    dyad[4][1][0] = (onk[14][2]+w0w1[4]);
    dyad[4][1][1] = w00w22[4];
    dyad[4][1][2] = (w1w2[4]-onk[14][0]);
    dyad[4][2][0] = (w0w2[4]-onk[14][1]);
    dyad[4][2][1] = (onk[14][0]+w1w2[4]);
    dyad[4][2][2] = w00w11[4];
    dyad[5][0][0] = w11w22[5];
    dyad[5][0][1] = (w0w1[5]-onk[16][2]);
    dyad[5][0][2] = (onk[16][1]+w0w2[5]);
    dyad[5][1][0] = (onk[16][2]+w0w1[5]);
    dyad[5][1][1] = w00w22[5];
    dyad[5][1][2] = (w1w2[5]-onk[16][0]);
    dyad[5][2][0] = (w0w2[5]-onk[16][1]);
    dyad[5][2][1] = (onk[16][0]+w1w2[5]);
    dyad[5][2][2] = w00w11[5];
    dyad[6][0][0] = w11w22[6];
    dyad[6][0][1] = (w0w1[6]-onk[18][2]);
    dyad[6][0][2] = (onk[18][1]+w0w2[6]);
    dyad[6][1][0] = (onk[18][2]+w0w1[6]);
    dyad[6][1][1] = w00w22[6];
    dyad[6][1][2] = (w1w2[6]-onk[18][0]);
    dyad[6][2][0] = (w0w2[6]-onk[18][1]);
    dyad[6][2][1] = (onk[18][0]+w1w2[6]);
    dyad[6][2][2] = w00w11[6];
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-onk[20][2]);
    dyad[7][0][2] = (onk[20][1]+w0w2[7]);
    dyad[7][1][0] = (onk[20][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-onk[20][0]);
    dyad[7][2][0] = (w0w2[7]-onk[20][1]);
    dyad[7][2][1] = (onk[20][0]+w1w2[7]);
    dyad[7][2][2] = w00w11[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-onk[22][2]);
    dyad[8][0][2] = (onk[22][1]+w0w2[8]);
    dyad[8][1][0] = (onk[22][2]+w0w1[8]);
    dyad[8][1][1] = w00w22[8];
    dyad[8][1][2] = (w1w2[8]-onk[22][0]);
    dyad[8][2][0] = (w0w2[8]-onk[22][1]);
    dyad[8][2][1] = (onk[22][0]+w1w2[8]);
    dyad[8][2][2] = w00w11[8];
    dyad[9][0][0] = w11w22[9];
    dyad[9][0][1] = (w0w1[9]-onk[24][2]);
    dyad[9][0][2] = (onk[24][1]+w0w2[9]);
    dyad[9][1][0] = (onk[24][2]+w0w1[9]);
    dyad[9][1][1] = w00w22[9];
    dyad[9][1][2] = (w1w2[9]-onk[24][0]);
    dyad[9][2][0] = (w0w2[9]-onk[24][1]);
    dyad[9][2][1] = (onk[24][0]+w1w2[9]);
    dyad[9][2][2] = w00w11[9];
    dyad[10][0][0] = w11w22[10];
    dyad[10][0][1] = (w0w1[10]-onk[27][2]);
    dyad[10][0][2] = (onk[27][1]+w0w2[10]);
    dyad[10][1][0] = (onk[27][2]+w0w1[10]);
    dyad[10][1][1] = w00w22[10];
    dyad[10][1][2] = (w1w2[10]-onk[27][0]);
    dyad[10][2][0] = (w0w2[10]-onk[27][1]);
    dyad[10][2][1] = (onk[27][0]+w1w2[10]);
    dyad[10][2][2] = w00w11[10];
    dyad[11][0][0] = w11w22[11];
    dyad[11][0][1] = (w0w1[11]-onk[28][2]);
    dyad[11][0][2] = (onk[28][1]+w0w2[11]);
    dyad[11][1][0] = (onk[28][2]+w0w1[11]);
    dyad[11][1][1] = w00w22[11];
    dyad[11][1][2] = (w1w2[11]-onk[28][0]);
    dyad[11][2][0] = (w0w2[11]-onk[28][1]);
    dyad[11][2][1] = (onk[28][0]+w1w2[11]);
    dyad[11][2][2] = w00w11[11];
    dyad[12][0][0] = w11w22[12];
    dyad[12][0][1] = (w0w1[12]-onk[30][2]);
    dyad[12][0][2] = (onk[30][1]+w0w2[12]);
    dyad[12][1][0] = (onk[30][2]+w0w1[12]);
    dyad[12][1][1] = w00w22[12];
    dyad[12][1][2] = (w1w2[12]-onk[30][0]);
    dyad[12][2][0] = (w0w2[12]-onk[30][1]);
    dyad[12][2][1] = (onk[30][0]+w1w2[12]);
    dyad[12][2][2] = w00w11[12];
    dyad[13][0][0] = w11w22[13];
    dyad[13][0][1] = (w0w1[13]-onk[33][2]);
    dyad[13][0][2] = (onk[33][1]+w0w2[13]);
    dyad[13][1][0] = (onk[33][2]+w0w1[13]);
    dyad[13][1][1] = w00w22[13];
    dyad[13][1][2] = (w1w2[13]-onk[33][0]);
    dyad[13][2][0] = (w0w2[13]-onk[33][1]);
    dyad[13][2][1] = (onk[33][0]+w1w2[13]);
    dyad[13][2][2] = w00w11[13];
    dyad[14][0][0] = w11w22[14];
    dyad[14][0][1] = (w0w1[14]-onk[34][2]);
    dyad[14][0][2] = (onk[34][1]+w0w2[14]);
    dyad[14][1][0] = (onk[34][2]+w0w1[14]);
    dyad[14][1][1] = w00w22[14];
    dyad[14][1][2] = (w1w2[14]-onk[34][0]);
    dyad[14][2][0] = (w0w2[14]-onk[34][1]);
    dyad[14][2][1] = (onk[34][0]+w1w2[14]);
    dyad[14][2][2] = w00w11[14];
    dyad[15][0][0] = w11w22[15];
    dyad[15][0][1] = (w0w1[15]-onk[36][2]);
    dyad[15][0][2] = (onk[36][1]+w0w2[15]);
    dyad[15][1][0] = (onk[36][2]+w0w1[15]);
    dyad[15][1][1] = w00w22[15];
    dyad[15][1][2] = (w1w2[15]-onk[36][0]);
    dyad[15][2][0] = (w0w2[15]-onk[36][1]);
    dyad[15][2][1] = (onk[36][0]+w1w2[15]);
    dyad[15][2][2] = w00w11[15];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[3][0] = ((Cik[3][2][0]*udot[2])+((Cik[3][0][0]*udot[0])+(Cik[3][1][0]*
      udot[1])));
    Ankb[3][1] = ((Cik[3][2][1]*udot[2])+((Cik[3][0][1]*udot[0])+(Cik[3][1][1]*
      udot[1])));
    Ankb[3][2] = ((Cik[3][2][2]*udot[2])+((Cik[3][0][2]*udot[0])+(Cik[3][1][2]*
      udot[1])));
    Ankb[5][0] = (Ankb[3][0]+((.1206*udot[5])-(.05*udot[4])));
    Ankb[5][1] = (Ankb[3][1]+(.05*udot[3]));
    Ankb[5][2] = (Ankb[3][2]-(.1206*udot[3]));
    AOnkri[6][0] = (Ankb[5][0]+((.05*udot[4])-(.1206*udot[5])));
    AOnkri[6][1] = (Ankb[5][1]-(.05*udot[3]));
    AOnkri[6][2] = (Ankb[5][2]+(.1206*udot[3]));
    Ankb[6][1] = ((AOnkri[6][1]*c6)+(AOnkri[6][2]*s6));
    Ankb[6][2] = ((AOnkri[6][2]*c6)-(AOnkri[6][1]*s6));
    Ankb[7][0] = ((Ankb[6][1]*s7)+(AOnkri[6][0]*c7));
    Ankb[7][1] = ((Ankb[6][1]*c7)-(AOnkri[6][0]*s7));
    Ankb[8][0] = (((Ankb[7][0]*c8)-(Ankb[6][2]*s8))-((.0351*Onkb[8][1])+(.14625*
      Onkb[8][2])));
    Ankb[8][1] = (Ankb[7][1]+(.0351*Onkb[8][0]));
    Ankb[8][2] = ((.14625*Onkb[8][0])+((Ankb[6][2]*c8)+(Ankb[7][0]*s8)));
    AOnkri[9][0] = (Ankb[8][0]-((.0013*Onkb[8][1])+(.24635*Onkb[8][2])));
    AOnkri[9][1] = (Ankb[8][1]+(.0013*Onkb[8][0]));
    AOnkri[9][2] = (Ankb[8][2]+(.24635*Onkb[8][0]));
    Ankb[9][1] = ((AOnkri[9][1]*c9)+(AOnkri[9][2]*s9));
    Ankb[9][2] = ((AOnkri[9][2]*c9)-(AOnkri[9][1]*s9));
    Ankb[10][0] = ((Ankb[9][1]*s10)+(AOnkri[9][0]*c10));
    Ankb[10][1] = ((Ankb[9][1]*c10)-(AOnkri[9][0]*s10));
    Ankb[11][0] = (((.0065*Onkb[11][1])-(.0442*Onkb[11][2]))+((Ankb[10][0]*c11)-
      (Ankb[9][2]*s11)));
    Ankb[11][1] = (Ankb[10][1]-(.0065*Onkb[11][0]));
    Ankb[11][2] = ((.0442*Onkb[11][0])+((Ankb[9][2]*c11)+(Ankb[10][0]*s11)));
    AOnkri[12][0] = (Ankb[11][0]+((.0065*Onkb[11][1])-(.0442*Onkb[11][2])));
    AOnkri[12][1] = (Ankb[11][1]-(.0065*Onkb[11][0]));
    AOnkri[12][2] = (Ankb[11][2]+(.0442*Onkb[11][0]));
    Ankb[12][0] = (AOnkri[12][0]+((.0312*Onkb[12][1])-(.078*Onkb[12][2])));
    Ankb[12][1] = (((AOnkri[12][1]*c12)+(AOnkri[12][2]*s12))-(.0312*Onkb[12][0])
      );
    Ankb[12][2] = ((.078*Onkb[12][0])+((AOnkri[12][2]*c12)-(AOnkri[12][1]*s12)))
      ;
    AOnkri[13][0] = (Ankb[8][0]+((.0013*Onkb[8][1])-(.18915*Onkb[8][2])));
    AOnkri[13][1] = (Ankb[8][1]+((.1768*Onkb[8][2])-(.0013*Onkb[8][0])));
    AOnkri[13][2] = (Ankb[8][2]+((.18915*Onkb[8][0])-(.1768*Onkb[8][1])));
    Ankb[13][0] = ((AOnkri[13][0]*c13)+(AOnkri[13][1]*s13));
    Ankb[13][1] = ((AOnkri[13][1]*c13)-(AOnkri[13][0]*s13));
    Ankb[14][0] = ((.0013*Onkb[14][1])+((Ankb[13][0]*c14)-(AOnkri[13][2]*s14)));
    Ankb[14][1] = (Ankb[13][1]+((.1326*Onkb[14][2])-(.0013*Onkb[14][0])));
    Ankb[14][2] = (((Ankb[13][0]*s14)+(AOnkri[13][2]*c14))-(.1326*Onkb[14][1]));
    AOnkri[15][0] = (Ankb[14][0]+(.0013*Onkb[14][1]));
    AOnkri[15][1] = (Ankb[14][1]+((.1326*Onkb[14][2])-(.0013*Onkb[14][0])));
    AOnkri[15][2] = (Ankb[14][2]-(.1326*Onkb[14][1]));
    Ankb[15][0] = ((AOnkri[15][0]*c15)-(AOnkri[15][2]*s15));
    Ankb[15][2] = ((AOnkri[15][0]*s15)+(AOnkri[15][2]*c15));
    Ankb[16][0] = (Ankb[15][0]-(.0039*Onkb[16][2]));
    Ankb[16][1] = ((.1378*Onkb[16][2])+((Ankb[15][2]*s16)+(AOnkri[15][1]*c16)));
    Ankb[16][2] = (((.0039*Onkb[16][0])-(.1378*Onkb[16][1]))+((Ankb[15][2]*c16)-
      (AOnkri[15][1]*s16)));
    AOnkri[17][0] = (Ankb[16][0]-(.0039*Onkb[16][2]));
    AOnkri[17][1] = (Ankb[16][1]+(.1378*Onkb[16][2]));
    AOnkri[17][2] = (Ankb[16][2]+((.0039*Onkb[16][0])-(.1378*Onkb[16][1])));
    Ankb[17][0] = ((AOnkri[17][0]*c17)+(AOnkri[17][1]*s17));
    Ankb[17][1] = ((AOnkri[17][1]*c17)-(AOnkri[17][0]*s17));
    Ankb[18][0] = ((Ankb[17][0]*c18)-(AOnkri[17][2]*s18));
    Ankb[18][1] = (Ankb[17][1]+(.065*Onkb[18][2]));
    Ankb[18][2] = (((Ankb[17][0]*s18)+(AOnkri[17][2]*c18))-(.065*Onkb[18][1]));
    AOnkri[19][0] = (Ankb[8][0]+((.0013*Onkb[8][1])-(.18915*Onkb[8][2])));
    AOnkri[19][1] = (Ankb[8][1]-((.0013*Onkb[8][0])+(.1768*Onkb[8][2])));
    AOnkri[19][2] = (Ankb[8][2]+((.1768*Onkb[8][1])+(.18915*Onkb[8][0])));
    Ankb[19][0] = ((AOnkri[19][0]*c19)+(AOnkri[19][1]*s19));
    Ankb[19][1] = ((AOnkri[19][1]*c19)-(AOnkri[19][0]*s19));
    Ankb[20][0] = ((.0013*Onkb[20][1])+((Ankb[19][0]*c20)-(AOnkri[19][2]*s20)));
    Ankb[20][1] = (Ankb[19][1]-((.0013*Onkb[20][0])+(.1326*Onkb[20][2])));
    Ankb[20][2] = ((.1326*Onkb[20][1])+((Ankb[19][0]*s20)+(AOnkri[19][2]*c20)));
    AOnkri[21][0] = (Ankb[20][0]+(.0013*Onkb[20][1]));
    AOnkri[21][1] = (Ankb[20][1]-((.0013*Onkb[20][0])+(.1326*Onkb[20][2])));
    AOnkri[21][2] = (Ankb[20][2]+(.1326*Onkb[20][1]));
    Ankb[21][0] = ((AOnkri[21][0]*c21)-(AOnkri[21][2]*s21));
    Ankb[21][2] = ((AOnkri[21][0]*s21)+(AOnkri[21][2]*c21));
    Ankb[22][0] = (Ankb[21][0]-(.0039*Onkb[22][2]));
    Ankb[22][1] = (((Ankb[21][2]*s22)+(AOnkri[21][1]*c22))-(.1378*Onkb[22][2]));
    Ankb[22][2] = (((.0039*Onkb[22][0])+(.1378*Onkb[22][1]))+((Ankb[21][2]*c22)-
      (AOnkri[21][1]*s22)));
    AOnkri[23][0] = (Ankb[22][0]-(.0039*Onkb[22][2]));
    AOnkri[23][1] = (Ankb[22][1]-(.1378*Onkb[22][2]));
    AOnkri[23][2] = (Ankb[22][2]+((.0039*Onkb[22][0])+(.1378*Onkb[22][1])));
    Ankb[23][0] = ((AOnkri[23][0]*c23)+(AOnkri[23][1]*s23));
    Ankb[23][1] = ((AOnkri[23][1]*c23)-(AOnkri[23][0]*s23));
    Ankb[24][0] = ((Ankb[23][0]*c24)-(AOnkri[23][2]*s24));
    Ankb[24][1] = (Ankb[23][1]-(.065*Onkb[24][2]));
    Ankb[24][2] = ((.065*Onkb[24][1])+((Ankb[23][0]*s24)+(AOnkri[23][2]*c24)));
    AOnkri[25][0] = (Ankb[5][0]+((.0058*udot[4])+(.0406*udot[5])));
    AOnkri[25][1] = (Ankb[5][1]+((.1118*udot[5])-(.0058*udot[3])));
    AOnkri[25][2] = (Ankb[5][2]-((.0406*udot[3])+(.1118*udot[4])));
    Ankb[25][1] = ((AOnkri[25][1]*c25)+(AOnkri[25][2]*s25));
    Ankb[25][2] = ((AOnkri[25][2]*c25)-(AOnkri[25][1]*s25));
    Ankb[26][0] = ((Ankb[25][1]*s26)+(AOnkri[25][0]*c26));
    Ankb[26][1] = ((Ankb[25][1]*c26)-(AOnkri[25][0]*s26));
    Ankb[27][0] = (((.0143*Onkb[27][1])+(.2379*Onkb[27][2]))+((Ankb[26][0]*c27)-
      (Ankb[25][2]*s27)));
    Ankb[27][1] = (Ankb[26][1]-((.0143*Onkb[27][0])+(.0169*Onkb[27][2])));
    Ankb[27][2] = (((.0169*Onkb[27][1])-(.2379*Onkb[27][0]))+((Ankb[25][2]*c27)+
      (Ankb[26][0]*s27)));
    AOnkri[28][0] = (Ankb[27][0]+((.0143*Onkb[27][1])+(.2379*Onkb[27][2])));
    AOnkri[28][1] = (Ankb[27][1]-((.0143*Onkb[27][0])+(.0169*Onkb[27][2])));
    AOnkri[28][2] = (Ankb[27][2]+((.0169*Onkb[27][1])-(.2379*Onkb[27][0])));
    Ankb[28][0] = (AOnkri[28][0]+((.2158*Onkb[28][2])-(.0039*Onkb[28][1])));
    Ankb[28][1] = (((.0039*Onkb[28][0])-(.0078*Onkb[28][2]))+((AOnkri[28][1]*c28
      )+(AOnkri[28][2]*s28)));
    Ankb[28][2] = (((.0078*Onkb[28][1])-(.2158*Onkb[28][0]))+((AOnkri[28][2]*c28
      )-(AOnkri[28][1]*s28)));
    AOnkri[29][0] = (Ankb[28][0]+((.2158*Onkb[28][2])-(.0039*Onkb[28][1])));
    AOnkri[29][1] = (Ankb[28][1]+((.0039*Onkb[28][0])-(.0078*Onkb[28][2])));
    AOnkri[29][2] = (Ankb[28][2]+((.0078*Onkb[28][1])-(.2158*Onkb[28][0])));
    Ankb[29][1] = ((AOnkri[29][1]*c29)+(AOnkri[29][2]*s29));
    Ankb[29][2] = ((AOnkri[29][2]*c29)-(AOnkri[29][1]*s29));
    Ankb[30][0] = (((.039*Onkb[30][1])+(.0442*Onkb[30][2]))+((Ankb[29][1]*s30)+(
      AOnkri[29][0]*c30)));
    Ankb[30][1] = (((Ankb[29][1]*c30)-(AOnkri[29][0]*s30))-(.039*Onkb[30][0]));
    Ankb[30][2] = (Ankb[29][2]-(.0442*Onkb[30][0]));
    AOnkri[31][0] = (Ankb[5][0]+((.0058*udot[4])+(.0406*udot[5])));
    AOnkri[31][1] = (Ankb[5][1]-((.0058*udot[3])+(.1118*udot[5])));
    AOnkri[31][2] = (Ankb[5][2]+((.1118*udot[4])-(.0406*udot[3])));
    Ankb[31][1] = ((AOnkri[31][1]*c31)+(AOnkri[31][2]*s31));
    Ankb[31][2] = ((AOnkri[31][2]*c31)-(AOnkri[31][1]*s31));
    Ankb[32][0] = ((Ankb[31][1]*s32)+(AOnkri[31][0]*c32));
    Ankb[32][1] = ((Ankb[31][1]*c32)-(AOnkri[31][0]*s32));
    Ankb[33][0] = (((.0143*Onkb[33][1])+(.2379*Onkb[33][2]))+((Ankb[32][0]*c33)-
      (Ankb[31][2]*s33)));
    Ankb[33][1] = (Ankb[32][1]+((.0169*Onkb[33][2])-(.0143*Onkb[33][0])));
    Ankb[33][2] = (((Ankb[31][2]*c33)+(Ankb[32][0]*s33))-((.0169*Onkb[33][1])+(
      .2379*Onkb[33][0])));
    AOnkri[34][0] = (Ankb[33][0]+((.0143*Onkb[33][1])+(.2379*Onkb[33][2])));
    AOnkri[34][1] = (Ankb[33][1]+((.0169*Onkb[33][2])-(.0143*Onkb[33][0])));
    AOnkri[34][2] = (Ankb[33][2]-((.0169*Onkb[33][1])+(.2379*Onkb[33][0])));
    Ankb[34][0] = (AOnkri[34][0]+((.2158*Onkb[34][2])-(.0039*Onkb[34][1])));
    Ankb[34][1] = (((.0039*Onkb[34][0])+(.0078*Onkb[34][2]))+((AOnkri[34][1]*c34
      )+(AOnkri[34][2]*s34)));
    Ankb[34][2] = (((AOnkri[34][2]*c34)-(AOnkri[34][1]*s34))-((.0078*Onkb[34][1]
      )+(.2158*Onkb[34][0])));
    AOnkri[35][0] = (Ankb[34][0]+((.2158*Onkb[34][2])-(.0039*Onkb[34][1])));
    AOnkri[35][1] = (Ankb[34][1]+((.0039*Onkb[34][0])+(.0078*Onkb[34][2])));
    AOnkri[35][2] = (Ankb[34][2]-((.0078*Onkb[34][1])+(.2158*Onkb[34][0])));
    Ankb[35][1] = ((AOnkri[35][1]*c35)+(AOnkri[35][2]*s35));
    Ankb[35][2] = ((AOnkri[35][2]*c35)-(AOnkri[35][1]*s35));
    Ankb[36][0] = (((.039*Onkb[36][1])+(.0442*Onkb[36][2]))+((Ankb[35][1]*s36)+(
      AOnkri[35][0]*c36)));
    Ankb[36][1] = (((Ankb[35][1]*c36)-(AOnkri[35][0]*s36))-(.039*Onkb[36][0]));
    Ankb[36][2] = (Ankb[35][2]-(.0442*Onkb[36][0]));
    AnkAtk[5][0] = (Ankb[5][0]+Atk[5][0]);
    AnkAtk[5][1] = (Ankb[5][1]+Atk[5][1]);
    AnkAtk[5][2] = (Ankb[5][2]+Atk[5][2]);
    ank[5][0] = ((AnkAtk[5][2]*Cik[3][0][2])+((AnkAtk[5][0]*Cik[3][0][0])+(
      AnkAtk[5][1]*Cik[3][0][1])));
    ank[5][1] = ((AnkAtk[5][2]*Cik[3][1][2])+((AnkAtk[5][0]*Cik[3][1][0])+(
      AnkAtk[5][1]*Cik[3][1][1])));
    ank[5][2] = ((AnkAtk[5][2]*Cik[3][2][2])+((AnkAtk[5][0]*Cik[3][2][0])+(
      AnkAtk[5][1]*Cik[3][2][1])));
    AnkAtk[8][0] = (Ankb[8][0]+Atk[8][0]);
    AnkAtk[8][1] = (Ankb[8][1]+Atk[8][1]);
    AnkAtk[8][2] = (Ankb[8][2]+Atk[8][2]);
    ank[8][0] = ((AnkAtk[8][2]*cnk[8][0][2])+((AnkAtk[8][0]*cnk[8][0][0])+(
      AnkAtk[8][1]*cnk[7][0][1])));
    ank[8][1] = ((AnkAtk[8][2]*cnk[8][1][2])+((AnkAtk[8][0]*cnk[8][1][0])+(
      AnkAtk[8][1]*cnk[7][1][1])));
    ank[8][2] = ((AnkAtk[8][2]*cnk[8][2][2])+((AnkAtk[8][0]*cnk[8][2][0])+(
      AnkAtk[8][1]*cnk[7][2][1])));
    AnkAtk[11][0] = (Ankb[11][0]+Atk[11][0]);
    AnkAtk[11][1] = (Ankb[11][1]+Atk[11][1]);
    AnkAtk[11][2] = (Ankb[11][2]+Atk[11][2]);
    ank[11][0] = ((AnkAtk[11][2]*cnk[11][0][2])+((AnkAtk[11][0]*cnk[11][0][0])+(
      AnkAtk[11][1]*cnk[10][0][1])));
    ank[11][1] = ((AnkAtk[11][2]*cnk[11][1][2])+((AnkAtk[11][0]*cnk[11][1][0])+(
      AnkAtk[11][1]*cnk[10][1][1])));
    ank[11][2] = ((AnkAtk[11][2]*cnk[11][2][2])+((AnkAtk[11][0]*cnk[11][2][0])+(
      AnkAtk[11][1]*cnk[10][2][1])));
    AnkAtk[12][0] = (Ankb[12][0]+Atk[12][0]);
    AnkAtk[12][1] = (Ankb[12][1]+Atk[12][1]);
    AnkAtk[12][2] = (Ankb[12][2]+Atk[12][2]);
    ank[12][0] = ((AnkAtk[12][2]*cnk[12][0][2])+((AnkAtk[12][0]*cnk[11][0][0])+(
      AnkAtk[12][1]*cnk[12][0][1])));
    ank[12][1] = ((AnkAtk[12][2]*cnk[12][1][2])+((AnkAtk[12][0]*cnk[11][1][0])+(
      AnkAtk[12][1]*cnk[12][1][1])));
    ank[12][2] = ((AnkAtk[12][2]*cnk[12][2][2])+((AnkAtk[12][0]*cnk[11][2][0])+(
      AnkAtk[12][1]*cnk[12][2][1])));
    AnkAtk[14][0] = (Ankb[14][0]+Atk[14][0]);
    AnkAtk[14][1] = (Ankb[14][1]+Atk[14][1]);
    AnkAtk[14][2] = (Ankb[14][2]+Atk[14][2]);
    ank[14][0] = ((AnkAtk[14][2]*cnk[14][0][2])+((AnkAtk[14][0]*cnk[14][0][0])+(
      AnkAtk[14][1]*cnk[13][0][1])));
    ank[14][1] = ((AnkAtk[14][2]*cnk[14][1][2])+((AnkAtk[14][0]*cnk[14][1][0])+(
      AnkAtk[14][1]*cnk[13][1][1])));
    ank[14][2] = ((AnkAtk[14][2]*cnk[14][2][2])+((AnkAtk[14][0]*cnk[14][2][0])+(
      AnkAtk[14][1]*cnk[13][2][1])));
    AnkAtk[16][0] = (Ankb[16][0]+Atk[16][0]);
    AnkAtk[16][1] = (Ankb[16][1]+Atk[16][1]);
    AnkAtk[16][2] = (Ankb[16][2]+Atk[16][2]);
    ank[16][0] = ((AnkAtk[16][2]*cnk[16][0][2])+((AnkAtk[16][0]*cnk[15][0][0])+(
      AnkAtk[16][1]*cnk[16][0][1])));
    ank[16][1] = ((AnkAtk[16][2]*cnk[16][1][2])+((AnkAtk[16][0]*cnk[15][1][0])+(
      AnkAtk[16][1]*cnk[16][1][1])));
    ank[16][2] = ((AnkAtk[16][2]*cnk[16][2][2])+((AnkAtk[16][0]*cnk[15][2][0])+(
      AnkAtk[16][1]*cnk[16][2][1])));
    AnkAtk[18][0] = (Ankb[18][0]+Atk[18][0]);
    AnkAtk[18][1] = (Ankb[18][1]+Atk[18][1]);
    AnkAtk[18][2] = (Ankb[18][2]+Atk[18][2]);
    ank[18][0] = ((AnkAtk[18][2]*cnk[18][0][2])+((AnkAtk[18][0]*cnk[18][0][0])+(
      AnkAtk[18][1]*cnk[17][0][1])));
    ank[18][1] = ((AnkAtk[18][2]*cnk[18][1][2])+((AnkAtk[18][0]*cnk[18][1][0])+(
      AnkAtk[18][1]*cnk[17][1][1])));
    ank[18][2] = ((AnkAtk[18][2]*cnk[18][2][2])+((AnkAtk[18][0]*cnk[18][2][0])+(
      AnkAtk[18][1]*cnk[17][2][1])));
    AnkAtk[20][0] = (Ankb[20][0]+Atk[20][0]);
    AnkAtk[20][1] = (Ankb[20][1]+Atk[20][1]);
    AnkAtk[20][2] = (Ankb[20][2]+Atk[20][2]);
    ank[20][0] = ((AnkAtk[20][2]*cnk[20][0][2])+((AnkAtk[20][0]*cnk[20][0][0])+(
      AnkAtk[20][1]*cnk[19][0][1])));
    ank[20][1] = ((AnkAtk[20][2]*cnk[20][1][2])+((AnkAtk[20][0]*cnk[20][1][0])+(
      AnkAtk[20][1]*cnk[19][1][1])));
    ank[20][2] = ((AnkAtk[20][2]*cnk[20][2][2])+((AnkAtk[20][0]*cnk[20][2][0])+(
      AnkAtk[20][1]*cnk[19][2][1])));
    AnkAtk[22][0] = (Ankb[22][0]+Atk[22][0]);
    AnkAtk[22][1] = (Ankb[22][1]+Atk[22][1]);
    AnkAtk[22][2] = (Ankb[22][2]+Atk[22][2]);
    ank[22][0] = ((AnkAtk[22][2]*cnk[22][0][2])+((AnkAtk[22][0]*cnk[21][0][0])+(
      AnkAtk[22][1]*cnk[22][0][1])));
    ank[22][1] = ((AnkAtk[22][2]*cnk[22][1][2])+((AnkAtk[22][0]*cnk[21][1][0])+(
      AnkAtk[22][1]*cnk[22][1][1])));
    ank[22][2] = ((AnkAtk[22][2]*cnk[22][2][2])+((AnkAtk[22][0]*cnk[21][2][0])+(
      AnkAtk[22][1]*cnk[22][2][1])));
    AnkAtk[24][0] = (Ankb[24][0]+Atk[24][0]);
    AnkAtk[24][1] = (Ankb[24][1]+Atk[24][1]);
    AnkAtk[24][2] = (Ankb[24][2]+Atk[24][2]);
    ank[24][0] = ((AnkAtk[24][2]*cnk[24][0][2])+((AnkAtk[24][0]*cnk[24][0][0])+(
      AnkAtk[24][1]*cnk[23][0][1])));
    ank[24][1] = ((AnkAtk[24][2]*cnk[24][1][2])+((AnkAtk[24][0]*cnk[24][1][0])+(
      AnkAtk[24][1]*cnk[23][1][1])));
    ank[24][2] = ((AnkAtk[24][2]*cnk[24][2][2])+((AnkAtk[24][0]*cnk[24][2][0])+(
      AnkAtk[24][1]*cnk[23][2][1])));
    AnkAtk[27][0] = (Ankb[27][0]+Atk[27][0]);
    AnkAtk[27][1] = (Ankb[27][1]+Atk[27][1]);
    AnkAtk[27][2] = (Ankb[27][2]+Atk[27][2]);
    ank[27][0] = ((AnkAtk[27][2]*cnk[27][0][2])+((AnkAtk[27][0]*cnk[27][0][0])+(
      AnkAtk[27][1]*cnk[26][0][1])));
    ank[27][1] = ((AnkAtk[27][2]*cnk[27][1][2])+((AnkAtk[27][0]*cnk[27][1][0])+(
      AnkAtk[27][1]*cnk[26][1][1])));
    ank[27][2] = ((AnkAtk[27][2]*cnk[27][2][2])+((AnkAtk[27][0]*cnk[27][2][0])+(
      AnkAtk[27][1]*cnk[26][2][1])));
    AnkAtk[28][0] = (Ankb[28][0]+Atk[28][0]);
    AnkAtk[28][1] = (Ankb[28][1]+Atk[28][1]);
    AnkAtk[28][2] = (Ankb[28][2]+Atk[28][2]);
    ank[28][0] = ((AnkAtk[28][2]*cnk[28][0][2])+((AnkAtk[28][0]*cnk[27][0][0])+(
      AnkAtk[28][1]*cnk[28][0][1])));
    ank[28][1] = ((AnkAtk[28][2]*cnk[28][1][2])+((AnkAtk[28][0]*cnk[27][1][0])+(
      AnkAtk[28][1]*cnk[28][1][1])));
    ank[28][2] = ((AnkAtk[28][2]*cnk[28][2][2])+((AnkAtk[28][0]*cnk[27][2][0])+(
      AnkAtk[28][1]*cnk[28][2][1])));
    AnkAtk[30][0] = (Ankb[30][0]+Atk[30][0]);
    AnkAtk[30][1] = (Ankb[30][1]+Atk[30][1]);
    AnkAtk[30][2] = (Ankb[30][2]+Atk[30][2]);
    ank[30][0] = ((AnkAtk[30][2]*cnk[29][0][2])+((AnkAtk[30][0]*cnk[30][0][0])+(
      AnkAtk[30][1]*cnk[30][0][1])));
    ank[30][1] = ((AnkAtk[30][2]*cnk[29][1][2])+((AnkAtk[30][0]*cnk[30][1][0])+(
      AnkAtk[30][1]*cnk[30][1][1])));
    ank[30][2] = ((AnkAtk[30][2]*cnk[29][2][2])+((AnkAtk[30][0]*cnk[30][2][0])+(
      AnkAtk[30][1]*cnk[30][2][1])));
    AnkAtk[33][0] = (Ankb[33][0]+Atk[33][0]);
    AnkAtk[33][1] = (Ankb[33][1]+Atk[33][1]);
    AnkAtk[33][2] = (Ankb[33][2]+Atk[33][2]);
    ank[33][0] = ((AnkAtk[33][2]*cnk[33][0][2])+((AnkAtk[33][0]*cnk[33][0][0])+(
      AnkAtk[33][1]*cnk[32][0][1])));
    ank[33][1] = ((AnkAtk[33][2]*cnk[33][1][2])+((AnkAtk[33][0]*cnk[33][1][0])+(
      AnkAtk[33][1]*cnk[32][1][1])));
    ank[33][2] = ((AnkAtk[33][2]*cnk[33][2][2])+((AnkAtk[33][0]*cnk[33][2][0])+(
      AnkAtk[33][1]*cnk[32][2][1])));
    AnkAtk[34][0] = (Ankb[34][0]+Atk[34][0]);
    AnkAtk[34][1] = (Ankb[34][1]+Atk[34][1]);
    AnkAtk[34][2] = (Ankb[34][2]+Atk[34][2]);
    ank[34][0] = ((AnkAtk[34][2]*cnk[34][0][2])+((AnkAtk[34][0]*cnk[33][0][0])+(
      AnkAtk[34][1]*cnk[34][0][1])));
    ank[34][1] = ((AnkAtk[34][2]*cnk[34][1][2])+((AnkAtk[34][0]*cnk[33][1][0])+(
      AnkAtk[34][1]*cnk[34][1][1])));
    ank[34][2] = ((AnkAtk[34][2]*cnk[34][2][2])+((AnkAtk[34][0]*cnk[33][2][0])+(
      AnkAtk[34][1]*cnk[34][2][1])));
    AnkAtk[36][0] = (Ankb[36][0]+Atk[36][0]);
    AnkAtk[36][1] = (Ankb[36][1]+Atk[36][1]);
    AnkAtk[36][2] = (Ankb[36][2]+Atk[36][2]);
    ank[36][0] = ((AnkAtk[36][2]*cnk[35][0][2])+((AnkAtk[36][0]*cnk[36][0][0])+(
      AnkAtk[36][1]*cnk[36][0][1])));
    ank[36][1] = ((AnkAtk[36][2]*cnk[35][1][2])+((AnkAtk[36][0]*cnk[36][1][0])+(
      AnkAtk[36][1]*cnk[36][1][1])));
    ank[36][2] = ((AnkAtk[36][2]*cnk[35][2][2])+((AnkAtk[36][0]*cnk[36][2][0])+(
      AnkAtk[36][1]*cnk[36][2][1])));
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    anb[1][0] = ank[8][0];
    anb[1][1] = ank[8][1];
    anb[1][2] = ank[8][2];
    anb[2][0] = ank[11][0];
    anb[2][1] = ank[11][1];
    anb[2][2] = ank[11][2];
    anb[3][0] = ank[12][0];
    anb[3][1] = ank[12][1];
    anb[3][2] = ank[12][2];
    anb[4][0] = ank[14][0];
    anb[4][1] = ank[14][1];
    anb[4][2] = ank[14][2];
    anb[5][0] = ank[16][0];
    anb[5][1] = ank[16][1];
    anb[5][2] = ank[16][2];
    anb[6][0] = ank[18][0];
    anb[6][1] = ank[18][1];
    anb[6][2] = ank[18][2];
    anb[7][0] = ank[20][0];
    anb[7][1] = ank[20][1];
    anb[7][2] = ank[20][2];
    anb[8][0] = ank[22][0];
    anb[8][1] = ank[22][1];
    anb[8][2] = ank[22][2];
    anb[9][0] = ank[24][0];
    anb[9][1] = ank[24][1];
    anb[9][2] = ank[24][2];
    anb[10][0] = ank[27][0];
    anb[10][1] = ank[27][1];
    anb[10][2] = ank[27][2];
    anb[11][0] = ank[28][0];
    anb[11][1] = ank[28][1];
    anb[11][2] = ank[28][2];
    anb[12][0] = ank[30][0];
    anb[12][1] = ank[30][1];
    anb[12][2] = ank[30][2];
    anb[13][0] = ank[33][0];
    anb[13][1] = ank[33][1];
    anb[13][2] = ank[33][2];
    anb[14][0] = ank[34][0];
    anb[14][1] = ank[34][1];
    anb[14][2] = ank[34][2];
    anb[15][0] = ank[36][0];
    anb[15][1] = ank[36][1];
    anb[15][2] = ank[36][2];
    roustate = 3;
/*
 Used 1.18 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  590 adds/subtracts/negates
                    545 multiplies
                      0 divides
                    639 assignments
*/
}

void skel18pseudo(double *lqout, double *luout)
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void skel18psqdot(double *lqdout)
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void skel18psudot(double *ludout)
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void skel18perr(double *errs)
{

}

void skel18verr(double *errs)
{

}

void skel18aerr(double *errs)
{

}

int skel18indx(int joint, int axis)
{
    int offs,gotit;

    if (skel18chkjaxis(36,joint,axis) != 0) {
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

void skel18presacc(int joint, int axis, double prval)
{

}

void skel18presvel(int joint, int axis, double prval)
{

}

void skel18prespos(int joint, int axis, double prval)
{

}

void skel18getht(int joint, int axis, double *torque)
{

    if (skel18chkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        skel18seterr(30,24);
        return;
    }
    *torque = tauc[skel18indx(joint,axis)];
}

void skel18hinget(int joint, int axis, double torque)
{

    if (skel18chkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        skel18seterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[skel18indx(joint,axis)] = mtau[skel18indx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[skel18indx(joint,axis)] = utau[skel18indx(joint,axis)]+torque;
    }
}

void skel18pointf(int body, double *point, double *force)
{
    double torque[3];

    if (skel18chkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        skel18seterr(11,23);
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

void skel18bodyt(int body, double *torque)
{

    if (skel18chkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        skel18seterr(12,23);
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

void skel18doww(int routine)
{

    roustate = 2;
    if (wwflg == 0) {
        wwflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void skel18xudot0(int routine, double *oudot0)
{
/*
Compute unconstrained equations
*/
    int i;

    skel18lhs(routine);
/*
Solve equations for udots
*/
    skel18fs0();
    skel18ldubslv(37,37,mmap,works,(double *) mlo,mdi,fs,udot);
    for (i = 0; i <= 36; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void skel18udot0(double *oudot0)
{

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(66,23);
        return;
    }
    skel18xudot0(66,oudot0);
}

void skel18setudot(double *iudot)
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(68,23);
        return;
    }
    for (i = 0; i <= 36; i++) {
        udot[i] = iudot[i];
    }
    skel18rhs();
}

void skel18xudotm(int routine, double *imult, double *oudotm)
{
/*
Compute udots due only to multipliers
*/
    int i;

    skel18lhs(routine);
    for (i = 0; i <= 36; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 36; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     74 assignments
*/
}

void skel18udotm(double *imult, double *oudotm)
{

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(67,23);
        return;
    }
    skel18xudotm(67,imult,oudotm);
}

void skel18deriv(double *oqdot, double *oudot)
{
/*
This is the derivative section for a 16-body ground-based
system with 37 hinge degree(s) of freedom.
*/
    int i;
    double udot0[37],udot1[37];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        skel18seterr(17,32);
    }
    if (stabposq == 1) {
        skel18seterr(17,33);
    }
    wsiz = 0;
/*
Compute unconstrained equations
*/
    skel18xudot0(17,udot0);
    skel18rhs();
    wrank = 0;
    for (i = 0; i <= 37; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 36; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     75 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void skel18resid(double *eqdot, double *eudot, double *emults, double *resid)
{
    int i;
    double uderrs[37];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(16,23);
        return;
    }
    if (stabposq == 1) {
        skel18seterr(16,33);
    }
    skel18fulltrq(eudot,emults,uderrs);
    for (i = 0; i < 38; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 37; i++) {
        resid[38+i] = uderrs[i];
    }
    for (i = 0; i < 37; i++) {
        udot[i] = eudot[i];
    }
    skel18rhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   38 adds/subtracts/negates
                      0 multiplies
                      0 divides
                    112 assignments
*/
}

void skel18mult(double *omults, int *owrank, int *omultmap)
{

    if (roustate != 3) {
        skel18seterr(34,24);
        return;
    }
    *owrank = wrank;
}

void skel18reac(double (*force)[3], double (*torque)[3])
{
/*
Generated 23-Nov-1999 14:31:07 by SD/FAST, Kane's formulation
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
        skel18seterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[36][0] = ((1.34*AnkAtk[36][0])-ufk[15][0]);
    fc[36][1] = ((1.34*AnkAtk[36][1])-ufk[15][1]);
    fc[36][2] = ((1.34*AnkAtk[36][2])-ufk[15][2]);
    tc[36][0] = ((WkIkWk[36][0]+(.0075*onk[36][0]))-(utk[15][0]+((.039*fc[36][1]
      )+(.0442*fc[36][2]))));
    tc[36][1] = ((WkIkWk[36][1]+(.007*onk[36][1]))-(utk[15][1]-(.039*fc[36][0]))
      );
    tc[36][2] = ((WkIkWk[36][2]+(.0018*onk[36][2]))-(utk[15][2]-(.0442*fc[36][0]
      )));
    fccikt[36][0] = ((fc[36][0]*c36)-(fc[36][1]*s36));
    fccikt[36][1] = ((fc[36][0]*s36)+(fc[36][1]*c36));
    fccikt[36][2] = fc[36][2];
    ffk[35][0] = -fccikt[36][0];
    ffk[35][1] = -fccikt[36][1];
    ffk[35][2] = -fccikt[36][2];
    ttk[35][0] = -((tc[36][0]*c36)-(tc[36][1]*s36));
    ttk[35][1] = -((tc[36][0]*s36)+(tc[36][1]*c36));
    ttk[35][2] = -tc[36][2];
    fc[35][0] = -ffk[35][0];
    fc[35][1] = -ffk[35][1];
    fc[35][2] = -ffk[35][2];
    tc[35][0] = -ttk[35][0];
    tc[35][1] = -ttk[35][1];
    tc[35][2] = -ttk[35][2];
    fccikt[35][0] = fc[35][0];
    fccikt[35][1] = ((fc[35][1]*c35)-(fc[35][2]*s35));
    fccikt[35][2] = ((fc[35][1]*s35)+(fc[35][2]*c35));
    ffk[34][0] = (ufk[14][0]-fccikt[35][0]);
    ffk[34][1] = (ufk[14][1]-fccikt[35][1]);
    ffk[34][2] = (ufk[14][2]-fccikt[35][2]);
    ttk[34][0] = (utk[14][0]-(tc[35][0]+((.0039*fccikt[35][1])-(.2158*
      fccikt[35][2]))));
    ttk[34][1] = (utk[14][1]-(((tc[35][1]*c35)-(tc[35][2]*s35))-((.0039*
      fccikt[35][0])+(.0078*fccikt[35][2]))));
    ttk[34][2] = (utk[14][2]-(((.0078*fccikt[35][1])+(.2158*fccikt[35][0]))+((
      tc[35][1]*s35)+(tc[35][2]*c35))));
    fc[34][0] = ((4.16*AnkAtk[34][0])-ffk[34][0]);
    fc[34][1] = ((4.16*AnkAtk[34][1])-ffk[34][1]);
    fc[34][2] = ((4.16*AnkAtk[34][2])-ffk[34][2]);
    tc[34][0] = ((WkIkWk[34][0]+(.056*onk[34][0]))-(ttk[34][0]+((.2158*fc[34][2]
      )-(.0039*fc[34][1]))));
    tc[34][1] = ((WkIkWk[34][1]+(.007*onk[34][1]))-(ttk[34][1]+((.0039*fc[34][0]
      )+(.0078*fc[34][2]))));
    tc[34][2] = ((WkIkWk[34][2]+(.055*onk[34][2]))-(ttk[34][2]-((.0078*fc[34][1]
      )+(.2158*fc[34][0]))));
    fccikt[34][0] = fc[34][0];
    fccikt[34][1] = ((fc[34][1]*c34)-(fc[34][2]*s34));
    fccikt[34][2] = ((fc[34][1]*s34)+(fc[34][2]*c34));
    ffk[33][0] = (ufk[13][0]-fccikt[34][0]);
    ffk[33][1] = (ufk[13][1]-fccikt[34][1]);
    ffk[33][2] = (ufk[13][2]-fccikt[34][2]);
    ttk[33][0] = (utk[13][0]-(tc[34][0]-((.0143*fccikt[34][1])+(.2379*
      fccikt[34][2]))));
    ttk[33][1] = (utk[13][1]-(((.0143*fccikt[34][0])-(.0169*fccikt[34][2]))+((
      tc[34][1]*c34)-(tc[34][2]*s34))));
    ttk[33][2] = (utk[13][2]-(((.0169*fccikt[34][1])+(.2379*fccikt[34][0]))+((
      tc[34][1]*s34)+(tc[34][2]*c34))));
    fc[33][0] = ((8.35*AnkAtk[33][0])-ffk[33][0]);
    fc[33][1] = ((8.35*AnkAtk[33][1])-ffk[33][1]);
    fc[33][2] = ((8.35*AnkAtk[33][2])-ffk[33][2]);
    tc[33][0] = ((WkIkWk[33][0]+(.16*onk[33][0]))-(ttk[33][0]+((.0143*fc[33][1])
      +(.2379*fc[33][2]))));
    tc[33][1] = ((WkIkWk[33][1]+(.025*onk[33][1]))-(ttk[33][1]+((.0169*fc[33][2]
      )-(.0143*fc[33][0]))));
    tc[33][2] = ((WkIkWk[33][2]+(.15*onk[33][2]))-(ttk[33][2]-((.0169*fc[33][1])
      +(.2379*fc[33][0]))));
    fccikt[33][0] = ((fc[33][0]*c33)+(fc[33][2]*s33));
    fccikt[33][1] = fc[33][1];
    fccikt[33][2] = ((fc[33][2]*c33)-(fc[33][0]*s33));
    ffk[32][0] = -fccikt[33][0];
    ffk[32][1] = -fccikt[33][1];
    ffk[32][2] = -fccikt[33][2];
    ttk[32][0] = -((tc[33][0]*c33)+(tc[33][2]*s33));
    ttk[32][1] = -tc[33][1];
    ttk[32][2] = -((tc[33][2]*c33)-(tc[33][0]*s33));
    fc[32][0] = -ffk[32][0];
    fc[32][1] = -ffk[32][1];
    fc[32][2] = -ffk[32][2];
    tc[32][0] = -ttk[32][0];
    tc[32][1] = -ttk[32][1];
    tc[32][2] = -ttk[32][2];
    fccikt[32][0] = ((fc[32][0]*c32)-(fc[32][1]*s32));
    fccikt[32][1] = ((fc[32][0]*s32)+(fc[32][1]*c32));
    fccikt[32][2] = fc[32][2];
    ffk[31][0] = -fccikt[32][0];
    ffk[31][1] = -fccikt[32][1];
    ffk[31][2] = -fccikt[32][2];
    ttk[31][0] = -((tc[32][0]*c32)-(tc[32][1]*s32));
    ttk[31][1] = -((tc[32][0]*s32)+(tc[32][1]*c32));
    ttk[31][2] = -tc[32][2];
    fc[31][0] = -ffk[31][0];
    fc[31][1] = -ffk[31][1];
    fc[31][2] = -ffk[31][2];
    tc[31][0] = -ttk[31][0];
    tc[31][1] = -ttk[31][1];
    tc[31][2] = -ttk[31][2];
    fccikt[31][0] = fc[31][0];
    fccikt[31][1] = ((fc[31][1]*c31)-(fc[31][2]*s31));
    fccikt[31][2] = ((fc[31][1]*s31)+(fc[31][2]*c31));
    ffk[5][0] = (ufk[0][0]-fccikt[31][0]);
    ffk[5][1] = (ufk[0][1]-fccikt[31][1]);
    ffk[5][2] = (ufk[0][2]-fccikt[31][2]);
    ttk[5][0] = (utk[0][0]-(tc[31][0]-((.0058*fccikt[31][1])+(.0406*
      fccikt[31][2]))));
    ttk[5][1] = (utk[0][1]-(((.0058*fccikt[31][0])+(.1118*fccikt[31][2]))+((
      tc[31][1]*c31)-(tc[31][2]*s31))));
    ttk[5][2] = (utk[0][2]-(((.0406*fccikt[31][0])-(.1118*fccikt[31][1]))+((
      tc[31][1]*s31)+(tc[31][2]*c31))));
    fc[30][0] = ((1.34*AnkAtk[30][0])-ufk[12][0]);
    fc[30][1] = ((1.34*AnkAtk[30][1])-ufk[12][1]);
    fc[30][2] = ((1.34*AnkAtk[30][2])-ufk[12][2]);
    tc[30][0] = ((WkIkWk[30][0]+(.0075*onk[30][0]))-(utk[12][0]+((.039*fc[30][1]
      )+(.0442*fc[30][2]))));
    tc[30][1] = ((WkIkWk[30][1]+(.007*onk[30][1]))-(utk[12][1]-(.039*fc[30][0]))
      );
    tc[30][2] = ((WkIkWk[30][2]+(.0018*onk[30][2]))-(utk[12][2]-(.0442*fc[30][0]
      )));
    fccikt[30][0] = ((fc[30][0]*c30)-(fc[30][1]*s30));
    fccikt[30][1] = ((fc[30][0]*s30)+(fc[30][1]*c30));
    fccikt[30][2] = fc[30][2];
    ffk[29][0] = -fccikt[30][0];
    ffk[29][1] = -fccikt[30][1];
    ffk[29][2] = -fccikt[30][2];
    ttk[29][0] = -((tc[30][0]*c30)-(tc[30][1]*s30));
    ttk[29][1] = -((tc[30][0]*s30)+(tc[30][1]*c30));
    ttk[29][2] = -tc[30][2];
    fc[29][0] = -ffk[29][0];
    fc[29][1] = -ffk[29][1];
    fc[29][2] = -ffk[29][2];
    tc[29][0] = -ttk[29][0];
    tc[29][1] = -ttk[29][1];
    tc[29][2] = -ttk[29][2];
    fccikt[29][0] = fc[29][0];
    fccikt[29][1] = ((fc[29][1]*c29)-(fc[29][2]*s29));
    fccikt[29][2] = ((fc[29][1]*s29)+(fc[29][2]*c29));
    ffk[28][0] = (ufk[11][0]-fccikt[29][0]);
    ffk[28][1] = (ufk[11][1]-fccikt[29][1]);
    ffk[28][2] = (ufk[11][2]-fccikt[29][2]);
    ttk[28][0] = (utk[11][0]-(tc[29][0]+((.0039*fccikt[29][1])-(.2158*
      fccikt[29][2]))));
    ttk[28][1] = (utk[11][1]-(((.0078*fccikt[29][2])-(.0039*fccikt[29][0]))+((
      tc[29][1]*c29)-(tc[29][2]*s29))));
    ttk[28][2] = (utk[11][2]-(((.2158*fccikt[29][0])-(.0078*fccikt[29][1]))+((
      tc[29][1]*s29)+(tc[29][2]*c29))));
    fc[28][0] = ((4.16*AnkAtk[28][0])-ffk[28][0]);
    fc[28][1] = ((4.16*AnkAtk[28][1])-ffk[28][1]);
    fc[28][2] = ((4.16*AnkAtk[28][2])-ffk[28][2]);
    tc[28][0] = ((WkIkWk[28][0]+(.056*onk[28][0]))-(ttk[28][0]+((.2158*fc[28][2]
      )-(.0039*fc[28][1]))));
    tc[28][1] = ((WkIkWk[28][1]+(.007*onk[28][1]))-(ttk[28][1]+((.0039*fc[28][0]
      )-(.0078*fc[28][2]))));
    tc[28][2] = ((WkIkWk[28][2]+(.055*onk[28][2]))-(ttk[28][2]+((.0078*fc[28][1]
      )-(.2158*fc[28][0]))));
    fccikt[28][0] = fc[28][0];
    fccikt[28][1] = ((fc[28][1]*c28)-(fc[28][2]*s28));
    fccikt[28][2] = ((fc[28][1]*s28)+(fc[28][2]*c28));
    ffk[27][0] = (ufk[10][0]-fccikt[28][0]);
    ffk[27][1] = (ufk[10][1]-fccikt[28][1]);
    ffk[27][2] = (ufk[10][2]-fccikt[28][2]);
    ttk[27][0] = (utk[10][0]-(tc[28][0]-((.0143*fccikt[28][1])+(.2379*
      fccikt[28][2]))));
    ttk[27][1] = (utk[10][1]-(((.0143*fccikt[28][0])+(.0169*fccikt[28][2]))+((
      tc[28][1]*c28)-(tc[28][2]*s28))));
    ttk[27][2] = (utk[10][2]-(((.2379*fccikt[28][0])-(.0169*fccikt[28][1]))+((
      tc[28][1]*s28)+(tc[28][2]*c28))));
    fc[27][0] = ((8.35*AnkAtk[27][0])-ffk[27][0]);
    fc[27][1] = ((8.35*AnkAtk[27][1])-ffk[27][1]);
    fc[27][2] = ((8.35*AnkAtk[27][2])-ffk[27][2]);
    tc[27][0] = ((WkIkWk[27][0]+(.16*onk[27][0]))-(ttk[27][0]+((.0143*fc[27][1])
      +(.2379*fc[27][2]))));
    tc[27][1] = ((WkIkWk[27][1]+(.025*onk[27][1]))-(ttk[27][1]-((.0143*fc[27][0]
      )+(.0169*fc[27][2]))));
    tc[27][2] = ((WkIkWk[27][2]+(.15*onk[27][2]))-(ttk[27][2]+((.0169*fc[27][1])
      -(.2379*fc[27][0]))));
    fccikt[27][0] = ((fc[27][0]*c27)+(fc[27][2]*s27));
    fccikt[27][1] = fc[27][1];
    fccikt[27][2] = ((fc[27][2]*c27)-(fc[27][0]*s27));
    ffk[26][0] = -fccikt[27][0];
    ffk[26][1] = -fccikt[27][1];
    ffk[26][2] = -fccikt[27][2];
    ttk[26][0] = -((tc[27][0]*c27)+(tc[27][2]*s27));
    ttk[26][1] = -tc[27][1];
    ttk[26][2] = -((tc[27][2]*c27)-(tc[27][0]*s27));
    fc[26][0] = -ffk[26][0];
    fc[26][1] = -ffk[26][1];
    fc[26][2] = -ffk[26][2];
    tc[26][0] = -ttk[26][0];
    tc[26][1] = -ttk[26][1];
    tc[26][2] = -ttk[26][2];
    fccikt[26][0] = ((fc[26][0]*c26)-(fc[26][1]*s26));
    fccikt[26][1] = ((fc[26][0]*s26)+(fc[26][1]*c26));
    fccikt[26][2] = fc[26][2];
    ffk[25][0] = -fccikt[26][0];
    ffk[25][1] = -fccikt[26][1];
    ffk[25][2] = -fccikt[26][2];
    ttk[25][0] = -((tc[26][0]*c26)-(tc[26][1]*s26));
    ttk[25][1] = -((tc[26][0]*s26)+(tc[26][1]*c26));
    ttk[25][2] = -tc[26][2];
    fc[25][0] = -ffk[25][0];
    fc[25][1] = -ffk[25][1];
    fc[25][2] = -ffk[25][2];
    tc[25][0] = -ttk[25][0];
    tc[25][1] = -ttk[25][1];
    tc[25][2] = -ttk[25][2];
    fccikt[25][0] = fc[25][0];
    fccikt[25][1] = ((fc[25][1]*c25)-(fc[25][2]*s25));
    fccikt[25][2] = ((fc[25][1]*s25)+(fc[25][2]*c25));
    ffk[5][0] = (ffk[5][0]-fccikt[25][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[25][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[25][2]);
    ttk[5][0] = (ttk[5][0]-(tc[25][0]-((.0058*fccikt[25][1])+(.0406*
      fccikt[25][2]))));
    ttk[5][1] = (ttk[5][1]-(((.0058*fccikt[25][0])-(.1118*fccikt[25][2]))+((
      tc[25][1]*c25)-(tc[25][2]*s25))));
    ttk[5][2] = (ttk[5][2]-(((.0406*fccikt[25][0])+(.1118*fccikt[25][1]))+((
      tc[25][1]*s25)+(tc[25][2]*c25))));
    fc[24][0] = ((.55*AnkAtk[24][0])-ufk[9][0]);
    fc[24][1] = ((.55*AnkAtk[24][1])-ufk[9][1]);
    fc[24][2] = ((.55*AnkAtk[24][2])-ufk[9][2]);
    tc[24][0] = ((WkIkWk[24][0]+(.0005*onk[24][0]))-utk[9][0]);
    tc[24][1] = ((WkIkWk[24][1]+(.002*onk[24][1]))-(utk[9][1]-(.065*fc[24][2])))
      ;
    tc[24][2] = ((WkIkWk[24][2]+(.0016*onk[24][2]))-(utk[9][2]+(.065*fc[24][1]))
      );
    fccikt[24][0] = ((fc[24][0]*c24)+(fc[24][2]*s24));
    fccikt[24][1] = fc[24][1];
    fccikt[24][2] = ((fc[24][2]*c24)-(fc[24][0]*s24));
    ffk[23][0] = -fccikt[24][0];
    ffk[23][1] = -fccikt[24][1];
    ffk[23][2] = -fccikt[24][2];
    ttk[23][0] = -((tc[24][0]*c24)+(tc[24][2]*s24));
    ttk[23][1] = -tc[24][1];
    ttk[23][2] = -((tc[24][2]*c24)-(tc[24][0]*s24));
    fc[23][0] = -ffk[23][0];
    fc[23][1] = -ffk[23][1];
    fc[23][2] = -ffk[23][2];
    tc[23][0] = -ttk[23][0];
    tc[23][1] = -ttk[23][1];
    tc[23][2] = -ttk[23][2];
    fccikt[23][0] = ((fc[23][0]*c23)-(fc[23][1]*s23));
    fccikt[23][1] = ((fc[23][0]*s23)+(fc[23][1]*c23));
    fccikt[23][2] = fc[23][2];
    ffk[22][0] = (ufk[8][0]-fccikt[23][0]);
    ffk[22][1] = (ufk[8][1]-fccikt[23][1]);
    ffk[22][2] = (ufk[8][2]-fccikt[23][2]);
    ttk[22][0] = (utk[8][0]-((.0039*fccikt[23][2])+((tc[23][0]*c23)-(tc[23][1]*
      s23))));
    ttk[22][1] = (utk[8][1]-((.1378*fccikt[23][2])+((tc[23][0]*s23)+(tc[23][1]*
      c23))));
    ttk[22][2] = (utk[8][2]-(tc[23][2]-((.0039*fccikt[23][0])+(.1378*
      fccikt[23][1]))));
    fc[22][0] = ((1.21*AnkAtk[22][0])-ffk[22][0]);
    fc[22][1] = ((1.21*AnkAtk[22][1])-ffk[22][1]);
    fc[22][2] = ((1.21*AnkAtk[22][2])-ffk[22][2]);
    tc[22][0] = ((WkIkWk[22][0]+(.0012*onk[22][0]))-(ttk[22][0]-(.0039*fc[22][2]
      )));
    tc[22][1] = ((WkIkWk[22][1]+(.0054*onk[22][1]))-(ttk[22][1]-(.1378*fc[22][2]
      )));
    tc[22][2] = ((WkIkWk[22][2]+(.005*onk[22][2]))-(ttk[22][2]+((.0039*fc[22][0]
      )+(.1378*fc[22][1]))));
    fccikt[22][0] = fc[22][0];
    fccikt[22][1] = ((fc[22][1]*c22)-(fc[22][2]*s22));
    fccikt[22][2] = ((fc[22][1]*s22)+(fc[22][2]*c22));
    ffk[21][0] = -fccikt[22][0];
    ffk[21][1] = -fccikt[22][1];
    ffk[21][2] = -fccikt[22][2];
    ttk[21][0] = -tc[22][0];
    ttk[21][1] = -((tc[22][1]*c22)-(tc[22][2]*s22));
    ttk[21][2] = -((tc[22][1]*s22)+(tc[22][2]*c22));
    fc[21][0] = -ffk[21][0];
    fc[21][1] = -ffk[21][1];
    fc[21][2] = -ffk[21][2];
    tc[21][0] = -ttk[21][0];
    tc[21][1] = -ttk[21][1];
    tc[21][2] = -ttk[21][2];
    fccikt[21][0] = ((fc[21][0]*c21)+(fc[21][2]*s21));
    fccikt[21][1] = fc[21][1];
    fccikt[21][2] = ((fc[21][2]*c21)-(fc[21][0]*s21));
    ffk[20][0] = (ufk[7][0]-fccikt[21][0]);
    ffk[20][1] = (ufk[7][1]-fccikt[21][1]);
    ffk[20][2] = (ufk[7][2]-fccikt[21][2]);
    ttk[20][0] = (utk[7][0]-(((tc[21][0]*c21)+(tc[21][2]*s21))-(.0013*
      fccikt[21][1])));
    ttk[20][1] = (utk[7][1]-(tc[21][1]+((.0013*fccikt[21][0])+(.1326*
      fccikt[21][2]))));
    ttk[20][2] = (utk[7][2]-(((tc[21][2]*c21)-(tc[21][0]*s21))-(.1326*
      fccikt[21][1])));
    fc[20][0] = ((2.79*AnkAtk[20][0])-ffk[20][0]);
    fc[20][1] = ((2.79*AnkAtk[20][1])-ffk[20][1]);
    fc[20][2] = ((2.79*AnkAtk[20][2])-ffk[20][2]);
    tc[20][0] = ((.005*onk[20][0])-(ttk[20][0]+(.0013*fc[20][1])));
    tc[20][1] = ((WkIkWk[20][1]+(.025*onk[20][1]))-(ttk[20][1]-((.0013*fc[20][0]
      )+(.1326*fc[20][2]))));
    tc[20][2] = ((WkIkWk[20][2]+(.025*onk[20][2]))-(ttk[20][2]+(.1326*fc[20][1])
      ));
    fccikt[20][0] = ((fc[20][0]*c20)+(fc[20][2]*s20));
    fccikt[20][1] = fc[20][1];
    fccikt[20][2] = ((fc[20][2]*c20)-(fc[20][0]*s20));
    ffk[19][0] = -fccikt[20][0];
    ffk[19][1] = -fccikt[20][1];
    ffk[19][2] = -fccikt[20][2];
    ttk[19][0] = -((tc[20][0]*c20)+(tc[20][2]*s20));
    ttk[19][1] = -tc[20][1];
    ttk[19][2] = -((tc[20][2]*c20)-(tc[20][0]*s20));
    fc[19][0] = -ffk[19][0];
    fc[19][1] = -ffk[19][1];
    fc[19][2] = -ffk[19][2];
    tc[19][0] = -ttk[19][0];
    tc[19][1] = -ttk[19][1];
    tc[19][2] = -ttk[19][2];
    fccikt[19][0] = ((fc[19][0]*c19)-(fc[19][1]*s19));
    fccikt[19][1] = ((fc[19][0]*s19)+(fc[19][1]*c19));
    fccikt[19][2] = fc[19][2];
    ffk[8][0] = (ufk[1][0]-fccikt[19][0]);
    ffk[8][1] = (ufk[1][1]-fccikt[19][1]);
    ffk[8][2] = (ufk[1][2]-fccikt[19][2]);
    ttk[8][0] = (utk[1][0]-(((.18915*fccikt[19][2])-(.0013*fccikt[19][1]))+((
      tc[19][0]*c19)-(tc[19][1]*s19))));
    ttk[8][1] = (utk[1][1]-(((.0013*fccikt[19][0])+(.1768*fccikt[19][2]))+((
      tc[19][0]*s19)+(tc[19][1]*c19))));
    ttk[8][2] = (utk[1][2]-(tc[19][2]-((.1768*fccikt[19][1])+(.18915*
      fccikt[19][0]))));
    fc[18][0] = ((.55*AnkAtk[18][0])-ufk[6][0]);
    fc[18][1] = ((.55*AnkAtk[18][1])-ufk[6][1]);
    fc[18][2] = ((.55*AnkAtk[18][2])-ufk[6][2]);
    tc[18][0] = ((WkIkWk[18][0]+(.0005*onk[18][0]))-utk[6][0]);
    tc[18][1] = ((WkIkWk[18][1]+(.002*onk[18][1]))-(utk[6][1]+(.065*fc[18][2])))
      ;
    tc[18][2] = ((WkIkWk[18][2]+(.0016*onk[18][2]))-(utk[6][2]-(.065*fc[18][1]))
      );
    fccikt[18][0] = ((fc[18][0]*c18)+(fc[18][2]*s18));
    fccikt[18][1] = fc[18][1];
    fccikt[18][2] = ((fc[18][2]*c18)-(fc[18][0]*s18));
    ffk[17][0] = -fccikt[18][0];
    ffk[17][1] = -fccikt[18][1];
    ffk[17][2] = -fccikt[18][2];
    ttk[17][0] = -((tc[18][0]*c18)+(tc[18][2]*s18));
    ttk[17][1] = -tc[18][1];
    ttk[17][2] = -((tc[18][2]*c18)-(tc[18][0]*s18));
    fc[17][0] = -ffk[17][0];
    fc[17][1] = -ffk[17][1];
    fc[17][2] = -ffk[17][2];
    tc[17][0] = -ttk[17][0];
    tc[17][1] = -ttk[17][1];
    tc[17][2] = -ttk[17][2];
    fccikt[17][0] = ((fc[17][0]*c17)-(fc[17][1]*s17));
    fccikt[17][1] = ((fc[17][0]*s17)+(fc[17][1]*c17));
    fccikt[17][2] = fc[17][2];
    ffk[16][0] = (ufk[5][0]-fccikt[17][0]);
    ffk[16][1] = (ufk[5][1]-fccikt[17][1]);
    ffk[16][2] = (ufk[5][2]-fccikt[17][2]);
    ttk[16][0] = (utk[5][0]-((.0039*fccikt[17][2])+((tc[17][0]*c17)-(tc[17][1]*
      s17))));
    ttk[16][1] = (utk[5][1]-(((tc[17][0]*s17)+(tc[17][1]*c17))-(.1378*
      fccikt[17][2])));
    ttk[16][2] = (utk[5][2]-(tc[17][2]+((.1378*fccikt[17][1])-(.0039*
      fccikt[17][0]))));
    fc[16][0] = ((1.21*AnkAtk[16][0])-ffk[16][0]);
    fc[16][1] = ((1.21*AnkAtk[16][1])-ffk[16][1]);
    fc[16][2] = ((1.21*AnkAtk[16][2])-ffk[16][2]);
    tc[16][0] = ((WkIkWk[16][0]+(.0012*onk[16][0]))-(ttk[16][0]-(.0039*fc[16][2]
      )));
    tc[16][1] = ((WkIkWk[16][1]+(.0054*onk[16][1]))-(ttk[16][1]+(.1378*fc[16][2]
      )));
    tc[16][2] = ((WkIkWk[16][2]+(.005*onk[16][2]))-(ttk[16][2]+((.0039*fc[16][0]
      )-(.1378*fc[16][1]))));
    fccikt[16][0] = fc[16][0];
    fccikt[16][1] = ((fc[16][1]*c16)-(fc[16][2]*s16));
    fccikt[16][2] = ((fc[16][1]*s16)+(fc[16][2]*c16));
    ffk[15][0] = -fccikt[16][0];
    ffk[15][1] = -fccikt[16][1];
    ffk[15][2] = -fccikt[16][2];
    ttk[15][0] = -tc[16][0];
    ttk[15][1] = -((tc[16][1]*c16)-(tc[16][2]*s16));
    ttk[15][2] = -((tc[16][1]*s16)+(tc[16][2]*c16));
    fc[15][0] = -ffk[15][0];
    fc[15][1] = -ffk[15][1];
    fc[15][2] = -ffk[15][2];
    tc[15][0] = -ttk[15][0];
    tc[15][1] = -ttk[15][1];
    tc[15][2] = -ttk[15][2];
    fccikt[15][0] = ((fc[15][0]*c15)+(fc[15][2]*s15));
    fccikt[15][1] = fc[15][1];
    fccikt[15][2] = ((fc[15][2]*c15)-(fc[15][0]*s15));
    ffk[14][0] = (ufk[4][0]-fccikt[15][0]);
    ffk[14][1] = (ufk[4][1]-fccikt[15][1]);
    ffk[14][2] = (ufk[4][2]-fccikt[15][2]);
    ttk[14][0] = (utk[4][0]-(((tc[15][0]*c15)+(tc[15][2]*s15))-(.0013*
      fccikt[15][1])));
    ttk[14][1] = (utk[4][1]-(tc[15][1]+((.0013*fccikt[15][0])-(.1326*
      fccikt[15][2]))));
    ttk[14][2] = (utk[4][2]-((.1326*fccikt[15][1])+((tc[15][2]*c15)-(tc[15][0]*
      s15))));
    fc[14][0] = ((2.79*AnkAtk[14][0])-ffk[14][0]);
    fc[14][1] = ((2.79*AnkAtk[14][1])-ffk[14][1]);
    fc[14][2] = ((2.79*AnkAtk[14][2])-ffk[14][2]);
    tc[14][0] = ((.005*onk[14][0])-(ttk[14][0]+(.0013*fc[14][1])));
    tc[14][1] = ((WkIkWk[14][1]+(.025*onk[14][1]))-(ttk[14][1]+((.1326*fc[14][2]
      )-(.0013*fc[14][0]))));
    tc[14][2] = ((WkIkWk[14][2]+(.025*onk[14][2]))-(ttk[14][2]-(.1326*fc[14][1])
      ));
    fccikt[14][0] = ((fc[14][0]*c14)+(fc[14][2]*s14));
    fccikt[14][1] = fc[14][1];
    fccikt[14][2] = ((fc[14][2]*c14)-(fc[14][0]*s14));
    ffk[13][0] = -fccikt[14][0];
    ffk[13][1] = -fccikt[14][1];
    ffk[13][2] = -fccikt[14][2];
    ttk[13][0] = -((tc[14][0]*c14)+(tc[14][2]*s14));
    ttk[13][1] = -tc[14][1];
    ttk[13][2] = -((tc[14][2]*c14)-(tc[14][0]*s14));
    fc[13][0] = -ffk[13][0];
    fc[13][1] = -ffk[13][1];
    fc[13][2] = -ffk[13][2];
    tc[13][0] = -ttk[13][0];
    tc[13][1] = -ttk[13][1];
    tc[13][2] = -ttk[13][2];
    fccikt[13][0] = ((fc[13][0]*c13)-(fc[13][1]*s13));
    fccikt[13][1] = ((fc[13][0]*s13)+(fc[13][1]*c13));
    fccikt[13][2] = fc[13][2];
    ffk[8][0] = (ffk[8][0]-fccikt[13][0]);
    ffk[8][1] = (ffk[8][1]-fccikt[13][1]);
    ffk[8][2] = (ffk[8][2]-fccikt[13][2]);
    ttk[8][0] = (ttk[8][0]-(((.18915*fccikt[13][2])-(.0013*fccikt[13][1]))+((
      tc[13][0]*c13)-(tc[13][1]*s13))));
    ttk[8][1] = (ttk[8][1]-(((.0013*fccikt[13][0])-(.1768*fccikt[13][2]))+((
      tc[13][0]*s13)+(tc[13][1]*c13))));
    ttk[8][2] = (ttk[8][2]-(tc[13][2]+((.1768*fccikt[13][1])-(.18915*
      fccikt[13][0]))));
    fc[12][0] = ((5.89*AnkAtk[12][0])-ufk[3][0]);
    fc[12][1] = ((5.89*AnkAtk[12][1])-ufk[3][1]);
    fc[12][2] = ((5.89*AnkAtk[12][2])-ufk[3][2]);
    tc[12][0] = ((WkIkWk[12][0]+(.033*onk[12][0]))-(utk[3][0]+((.0312*fc[12][1])
      -(.078*fc[12][2]))));
    tc[12][1] = ((WkIkWk[12][1]+(.023*onk[12][1]))-(utk[3][1]-(.0312*fc[12][0]))
      );
    tc[12][2] = ((WkIkWk[12][2]+(.03*onk[12][2]))-(utk[3][2]+(.078*fc[12][0])));
    fccikt[12][0] = fc[12][0];
    fccikt[12][1] = ((fc[12][1]*c12)-(fc[12][2]*s12));
    fccikt[12][2] = ((fc[12][1]*s12)+(fc[12][2]*c12));
    ffk[11][0] = (ufk[2][0]-fccikt[12][0]);
    ffk[11][1] = (ufk[2][1]-fccikt[12][1]);
    ffk[11][2] = (ufk[2][2]-fccikt[12][2]);
    ttk[11][0] = (utk[2][0]-(tc[12][0]+((.0442*fccikt[12][2])-(.0065*
      fccikt[12][1]))));
    ttk[11][1] = (utk[2][1]-((.0065*fccikt[12][0])+((tc[12][1]*c12)-(tc[12][2]*
      s12))));
    ttk[11][2] = (utk[2][2]-(((tc[12][1]*s12)+(tc[12][2]*c12))-(.0442*
      fccikt[12][0])));
    fc[11][0] = (AnkAtk[11][0]-ffk[11][0]);
    fc[11][1] = (AnkAtk[11][1]-ffk[11][1]);
    fc[11][2] = (AnkAtk[11][2]-ffk[11][2]);
    tc[11][0] = ((WkIkWk[11][0]+(.006*onk[11][0]))-(ttk[11][0]+((.0065*fc[11][1]
      )-(.0442*fc[11][2]))));
    tc[11][1] = ((.001*onk[11][1])-(ttk[11][1]-(.0065*fc[11][0])));
    tc[11][2] = ((WkIkWk[11][2]+(.006*onk[11][2]))-(ttk[11][2]+(.0442*fc[11][0])
      ));
    fccikt[11][0] = ((fc[11][0]*c11)+(fc[11][2]*s11));
    fccikt[11][1] = fc[11][1];
    fccikt[11][2] = ((fc[11][2]*c11)-(fc[11][0]*s11));
    ffk[10][0] = -fccikt[11][0];
    ffk[10][1] = -fccikt[11][1];
    ffk[10][2] = -fccikt[11][2];
    ttk[10][0] = -((tc[11][0]*c11)+(tc[11][2]*s11));
    ttk[10][1] = -tc[11][1];
    ttk[10][2] = -((tc[11][2]*c11)-(tc[11][0]*s11));
    fc[10][0] = -ffk[10][0];
    fc[10][1] = -ffk[10][1];
    fc[10][2] = -ffk[10][2];
    tc[10][0] = -ttk[10][0];
    tc[10][1] = -ttk[10][1];
    tc[10][2] = -ttk[10][2];
    fccikt[10][0] = ((fc[10][0]*c10)-(fc[10][1]*s10));
    fccikt[10][1] = ((fc[10][0]*s10)+(fc[10][1]*c10));
    fccikt[10][2] = fc[10][2];
    ffk[9][0] = -fccikt[10][0];
    ffk[9][1] = -fccikt[10][1];
    ffk[9][2] = -fccikt[10][2];
    ttk[9][0] = -((tc[10][0]*c10)-(tc[10][1]*s10));
    ttk[9][1] = -((tc[10][0]*s10)+(tc[10][1]*c10));
    ttk[9][2] = -tc[10][2];
    fc[9][0] = -ffk[9][0];
    fc[9][1] = -ffk[9][1];
    fc[9][2] = -ffk[9][2];
    tc[9][0] = -ttk[9][0];
    tc[9][1] = -ttk[9][1];
    tc[9][2] = -ttk[9][2];
    fccikt[9][0] = fc[9][0];
    fccikt[9][1] = ((fc[9][1]*c9)-(fc[9][2]*s9));
    fccikt[9][2] = ((fc[9][1]*s9)+(fc[9][2]*c9));
    ffk[8][0] = (ffk[8][0]-fccikt[9][0]);
    ffk[8][1] = (ffk[8][1]-fccikt[9][1]);
    ffk[8][2] = (ffk[8][2]-fccikt[9][2]);
    ttk[8][0] = (ttk[8][0]-(tc[9][0]+((.0013*fccikt[9][1])+(.24635*fccikt[9][2])
      )));
    ttk[8][1] = (ttk[8][1]-(((tc[9][1]*c9)-(tc[9][2]*s9))-(.0013*fccikt[9][0])))
      ;
    ttk[8][2] = (ttk[8][2]-(((tc[9][1]*s9)+(tc[9][2]*c9))-(.24635*fccikt[9][0]))
      );
    fc[8][0] = ((29.27*AnkAtk[8][0])-ffk[8][0]);
    fc[8][1] = ((29.27*AnkAtk[8][1])-ffk[8][1]);
    fc[8][2] = ((29.27*AnkAtk[8][2])-ffk[8][2]);
    tc[8][0] = ((WkIkWk[8][0]+(.63*onk[8][0]))-(ttk[8][0]-((.0351*fc[8][1])+(
      .14625*fc[8][2]))));
    tc[8][1] = ((WkIkWk[8][1]+(.32*onk[8][1]))-(ttk[8][1]+(.0351*fc[8][0])));
    tc[8][2] = ((WkIkWk[8][2]+(.73*onk[8][2]))-(ttk[8][2]+(.14625*fc[8][0])));
    fccikt[8][0] = ((fc[8][0]*c8)+(fc[8][2]*s8));
    fccikt[8][1] = fc[8][1];
    fccikt[8][2] = ((fc[8][2]*c8)-(fc[8][0]*s8));
    ffk[7][0] = -fccikt[8][0];
    ffk[7][1] = -fccikt[8][1];
    ffk[7][2] = -fccikt[8][2];
    ttk[7][0] = -((tc[8][0]*c8)+(tc[8][2]*s8));
    ttk[7][1] = -tc[8][1];
    ttk[7][2] = -((tc[8][2]*c8)-(tc[8][0]*s8));
    fc[7][0] = -ffk[7][0];
    fc[7][1] = -ffk[7][1];
    fc[7][2] = -ffk[7][2];
    tc[7][0] = -ttk[7][0];
    tc[7][1] = -ttk[7][1];
    tc[7][2] = -ttk[7][2];
    fccikt[7][0] = ((fc[7][0]*c7)-(fc[7][1]*s7));
    fccikt[7][1] = ((fc[7][0]*s7)+(fc[7][1]*c7));
    fccikt[7][2] = fc[7][2];
    ffk[6][0] = -fccikt[7][0];
    ffk[6][1] = -fccikt[7][1];
    ffk[6][2] = -fccikt[7][2];
    ttk[6][0] = -((tc[7][0]*c7)-(tc[7][1]*s7));
    ttk[6][1] = -((tc[7][0]*s7)+(tc[7][1]*c7));
    ttk[6][2] = -tc[7][2];
    fc[6][0] = -ffk[6][0];
    fc[6][1] = -ffk[6][1];
    fc[6][2] = -ffk[6][2];
    tc[6][0] = -ttk[6][0];
    tc[6][1] = -ttk[6][1];
    tc[6][2] = -ttk[6][2];
    fccikt[6][0] = fc[6][0];
    fccikt[6][1] = ((fc[6][1]*c6)-(fc[6][2]*s6));
    fccikt[6][2] = ((fc[6][1]*s6)+(fc[6][2]*c6));
    ffk[5][0] = (ffk[5][0]-fccikt[6][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[6][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[6][2]);
    ttk[5][0] = (ttk[5][0]-(tc[6][0]+((.1206*fccikt[6][2])-(.05*fccikt[6][1]))))
      ;
    ttk[5][1] = (ttk[5][1]-((.05*fccikt[6][0])+((tc[6][1]*c6)-(tc[6][2]*s6))));
    ttk[5][2] = (ttk[5][2]-(((tc[6][1]*s6)+(tc[6][2]*c6))-(.1206*fccikt[6][0])))
      ;
    fc[5][0] = ((16.61*AnkAtk[5][0])-ffk[5][0]);
    fc[5][1] = ((16.61*AnkAtk[5][1])-ffk[5][1]);
    fc[5][2] = ((16.61*AnkAtk[5][2])-ffk[5][2]);
    tc[5][0] = ((WkIkWk[5][0]+(.18*udot[3]))-(ttk[5][0]+((.1206*fc[5][2])-(.05*
      fc[5][1]))));
    tc[5][1] = ((WkIkWk[5][1]+(.16*udot[4]))-(ttk[5][1]+(.05*fc[5][0])));
    tc[5][2] = ((WkIkWk[5][2]+(.23*udot[5]))-(ttk[5][2]-(.1206*fc[5][0])));
    fccikt[5][0] = fc[5][0];
    fccikt[5][1] = fc[5][1];
    fccikt[5][2] = fc[5][2];
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -tc[5][0];
    ttk[4][1] = -tc[5][1];
    ttk[4][2] = -tc[5][2];
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = fc[4][0];
    fccikt[4][1] = fc[4][1];
    fccikt[4][2] = fc[4][2];
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -tc[4][0];
    ttk[3][1] = -tc[4][1];
    ttk[3][2] = -tc[4][2];
    fc[3][0] = -ffk[3][0];
    fc[3][1] = -ffk[3][1];
    fc[3][2] = -ffk[3][2];
    tc[3][0] = -ttk[3][0];
    tc[3][1] = -ttk[3][1];
    tc[3][2] = -ttk[3][2];
    fccikt[3][0] = ((Cik[3][0][2]*fc[3][2])+((Cik[3][0][0]*fc[3][0])+(
      Cik[3][0][1]*fc[3][1])));
    fccikt[3][1] = ((Cik[3][1][2]*fc[3][2])+((Cik[3][1][0]*fc[3][0])+(
      Cik[3][1][1]*fc[3][1])));
    fccikt[3][2] = ((Cik[3][2][2]*fc[3][2])+((Cik[3][2][0]*fc[3][0])+(
      Cik[3][2][1]*fc[3][1])));
    ffk[2][0] = -fccikt[3][0];
    ffk[2][1] = -fccikt[3][1];
    ffk[2][2] = -fccikt[3][2];
    ttk[2][0] = -((Cik[3][0][2]*tc[3][2])+((Cik[3][0][0]*tc[3][0])+(Cik[3][0][1]
      *tc[3][1])));
    ttk[2][1] = -((Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(Cik[3][1][1]
      *tc[3][1])));
    ttk[2][2] = -((Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(Cik[3][2][1]
      *tc[3][1])));
    fc[2][0] = -ffk[2][0];
    fc[2][1] = -ffk[2][1];
    fc[2][2] = -ffk[2][2];
    tc[2][0] = -ttk[2][0];
    tc[2][1] = -ttk[2][1];
    tc[2][2] = -ttk[2][2];
    fccikt[2][0] = fc[2][0];
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -(tc[2][0]-(fccikt[2][1]*q[2]));
    ttk[1][1] = -(tc[2][1]+(fccikt[2][0]*q[2]));
    ttk[1][2] = -tc[2][2];
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = fc[1][0];
    fccikt[1][1] = fc[1][1];
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = -fccikt[1][0];
    ffk[0][1] = -fccikt[1][1];
    ffk[0][2] = -fccikt[1][2];
    ttk[0][0] = -(tc[1][0]+(fccikt[1][2]*q[1]));
    ttk[0][1] = -tc[1][1];
    ttk[0][2] = -(tc[1][2]-(fccikt[1][0]*q[1]));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[5][0];
    torque[0][0] = tc[5][0];
    force[0][1] = fc[5][1];
    torque[0][1] = tc[5][1];
    force[0][2] = fc[5][2];
    torque[0][2] = tc[5][2];
    force[1][0] = fc[8][0];
    torque[1][0] = tc[8][0];
    force[1][1] = fc[8][1];
    torque[1][1] = tc[8][1];
    force[1][2] = fc[8][2];
    torque[1][2] = tc[8][2];
    force[2][0] = fc[11][0];
    torque[2][0] = tc[11][0];
    force[2][1] = fc[11][1];
    torque[2][1] = tc[11][1];
    force[2][2] = fc[11][2];
    torque[2][2] = tc[11][2];
    force[3][0] = fc[12][0];
    torque[3][0] = tc[12][0];
    force[3][1] = fc[12][1];
    torque[3][1] = tc[12][1];
    force[3][2] = fc[12][2];
    torque[3][2] = tc[12][2];
    force[4][0] = fc[14][0];
    torque[4][0] = tc[14][0];
    force[4][1] = fc[14][1];
    torque[4][1] = tc[14][1];
    force[4][2] = fc[14][2];
    torque[4][2] = tc[14][2];
    force[5][0] = fc[16][0];
    torque[5][0] = tc[16][0];
    force[5][1] = fc[16][1];
    torque[5][1] = tc[16][1];
    force[5][2] = fc[16][2];
    torque[5][2] = tc[16][2];
    force[6][0] = fc[18][0];
    torque[6][0] = tc[18][0];
    force[6][1] = fc[18][1];
    torque[6][1] = tc[18][1];
    force[6][2] = fc[18][2];
    torque[6][2] = tc[18][2];
    force[7][0] = fc[20][0];
    torque[7][0] = tc[20][0];
    force[7][1] = fc[20][1];
    torque[7][1] = tc[20][1];
    force[7][2] = fc[20][2];
    torque[7][2] = tc[20][2];
    force[8][0] = fc[22][0];
    torque[8][0] = tc[22][0];
    force[8][1] = fc[22][1];
    torque[8][1] = tc[22][1];
    force[8][2] = fc[22][2];
    torque[8][2] = tc[22][2];
    force[9][0] = fc[24][0];
    torque[9][0] = tc[24][0];
    force[9][1] = fc[24][1];
    torque[9][1] = tc[24][1];
    force[9][2] = fc[24][2];
    torque[9][2] = tc[24][2];
    force[10][0] = fc[27][0];
    torque[10][0] = tc[27][0];
    force[10][1] = fc[27][1];
    torque[10][1] = tc[27][1];
    force[10][2] = fc[27][2];
    torque[10][2] = tc[27][2];
    force[11][0] = fc[28][0];
    torque[11][0] = tc[28][0];
    force[11][1] = fc[28][1];
    torque[11][1] = tc[28][1];
    force[11][2] = fc[28][2];
    torque[11][2] = tc[28][2];
    force[12][0] = fc[30][0];
    torque[12][0] = tc[30][0];
    force[12][1] = fc[30][1];
    torque[12][1] = tc[30][1];
    force[12][2] = fc[30][2];
    torque[12][2] = tc[30][2];
    force[13][0] = fc[33][0];
    torque[13][0] = tc[33][0];
    force[13][1] = fc[33][1];
    torque[13][1] = tc[33][1];
    force[13][2] = fc[33][2];
    torque[13][2] = tc[33][2];
    force[14][0] = fc[34][0];
    torque[14][0] = tc[34][0];
    force[14][1] = fc[34][1];
    torque[14][1] = tc[34][1];
    force[14][2] = fc[34][2];
    torque[14][2] = tc[34][2];
    force[15][0] = fc[36][0];
    torque[15][0] = tc[36][0];
    force[15][1] = fc[36][1];
    torque[15][1] = tc[36][1];
    force[15][2] = fc[36][2];
    torque[15][2] = tc[36][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 1.28 seconds CPU time,
 40960 additional bytes of memory.
 Equations contain  767 adds/subtracts/negates
                    507 multiplies
                      0 divides
                    642 assignments
*/
}

void skel18mom(double *lm, double *am, double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 23-Nov-1999 14:31:08 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[16][3],hnk[16][3];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(19,23);
        return;
    }
    lm[0] = ((1.34*vnk[36][0])+((4.16*vnk[34][0])+((8.35*vnk[33][0])+((1.34*
      vnk[30][0])+((4.16*vnk[28][0])+((8.35*vnk[27][0])+((.55*vnk[24][0])+((1.21
      *vnk[22][0])+((2.79*vnk[20][0])+((.55*vnk[18][0])+((1.21*vnk[16][0])+((
      2.79*vnk[14][0])+((5.89*vnk[12][0])+(vnk[11][0]+((16.61*vnk[5][0])+(29.27*
      vnk[8][0]))))))))))))))));
    lm[1] = ((1.34*vnk[36][1])+((4.16*vnk[34][1])+((8.35*vnk[33][1])+((1.34*
      vnk[30][1])+((4.16*vnk[28][1])+((8.35*vnk[27][1])+((.55*vnk[24][1])+((1.21
      *vnk[22][1])+((2.79*vnk[20][1])+((.55*vnk[18][1])+((1.21*vnk[16][1])+((
      2.79*vnk[14][1])+((5.89*vnk[12][1])+(vnk[11][1]+((16.61*vnk[5][1])+(29.27*
      vnk[8][1]))))))))))))))));
    lm[2] = ((1.34*vnk[36][2])+((4.16*vnk[34][2])+((8.35*vnk[33][2])+((1.34*
      vnk[30][2])+((4.16*vnk[28][2])+((8.35*vnk[27][2])+((.55*vnk[24][2])+((1.21
      *vnk[22][2])+((2.79*vnk[20][2])+((.55*vnk[18][2])+((1.21*vnk[16][2])+((
      2.79*vnk[14][2])+((5.89*vnk[12][2])+(vnk[11][2]+((16.61*vnk[5][2])+(29.27*
      vnk[8][2]))))))))))))))));
    temp[0] = (((16.61*((rnk[5][1]*vnk[5][2])-(rnk[5][2]*vnk[5][1])))+((.23*(
      Cik[3][0][2]*u[5]))+((.16*(Cik[3][0][1]*u[4]))+(.18*(Cik[3][0][0]*u[3]))))
      )+((29.27*((rnk[8][1]*vnk[8][2])-(rnk[8][2]*vnk[8][1])))+((.73*(
      cnk[8][0][2]*wk[8][2]))+((.32*(cnk[7][0][1]*wk[8][1]))+(.63*(cnk[8][0][0]*
      wk[8][0]))))));
    temp[1] = (((5.89*((rnk[12][1]*vnk[12][2])-(rnk[12][2]*vnk[12][1])))+((.03*(
      cnk[12][0][2]*wk[12][2]))+((.023*(cnk[12][0][1]*wk[12][1]))+(.033*(
      cnk[11][0][0]*wk[12][0])))))+((((.006*(cnk[11][0][2]*wk[11][2]))+((.001*(
      cnk[10][0][1]*wk[11][1]))+(.006*(cnk[11][0][0]*wk[11][0]))))+((rnk[11][1]*
      vnk[11][2])-(rnk[11][2]*vnk[11][1])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][1]*vnk[16][2])-(rnk[16][2]*vnk[16][1])))+((.005*
      (cnk[16][0][2]*wk[16][2]))+((.0012*(cnk[15][0][0]*wk[16][0]))+(.0054*(
      cnk[16][0][1]*wk[16][1])))))+(((2.79*((rnk[14][1]*vnk[14][2])-(rnk[14][2]*
      vnk[14][1])))+((.025*(cnk[14][0][2]*wk[14][2]))+((.005*(cnk[14][0][0]*
      wk[14][0]))+(.025*(cnk[13][0][1]*wk[14][1])))))+temp[1]));
    temp[3] = (((2.79*((rnk[20][1]*vnk[20][2])-(rnk[20][2]*vnk[20][1])))+((.025*
      (cnk[20][0][2]*wk[20][2]))+((.005*(cnk[20][0][0]*wk[20][0]))+(.025*(
      cnk[19][0][1]*wk[20][1])))))+(((.55*((rnk[18][1]*vnk[18][2])-(rnk[18][2]*
      vnk[18][1])))+((.0016*(cnk[18][0][2]*wk[18][2]))+((.0005*(cnk[18][0][0]*
      wk[18][0]))+(.002*(cnk[17][0][1]*wk[18][1])))))+temp[2]));
    temp[4] = (((.55*((rnk[24][1]*vnk[24][2])-(rnk[24][2]*vnk[24][1])))+((.0016*
      (cnk[24][0][2]*wk[24][2]))+((.0005*(cnk[24][0][0]*wk[24][0]))+(.002*(
      cnk[23][0][1]*wk[24][1])))))+(((1.21*((rnk[22][1]*vnk[22][2])-(rnk[22][2]*
      vnk[22][1])))+((.005*(cnk[22][0][2]*wk[22][2]))+((.0012*(cnk[21][0][0]*
      wk[22][0]))+(.0054*(cnk[22][0][1]*wk[22][1])))))+temp[3]));
    temp[5] = (((4.16*((rnk[28][1]*vnk[28][2])-(rnk[28][2]*vnk[28][1])))+((.055*
      (cnk[28][0][2]*wk[28][2]))+((.007*(cnk[28][0][1]*wk[28][1]))+(.056*(
      cnk[27][0][0]*wk[28][0])))))+(((8.35*((rnk[27][1]*vnk[27][2])-(rnk[27][2]*
      vnk[27][1])))+((.15*(cnk[27][0][2]*wk[27][2]))+((.025*(cnk[26][0][1]*
      wk[27][1]))+(.16*(cnk[27][0][0]*wk[27][0])))))+temp[4]));
    temp[6] = (((8.35*((rnk[33][1]*vnk[33][2])-(rnk[33][2]*vnk[33][1])))+((.15*(
      cnk[33][0][2]*wk[33][2]))+((.025*(cnk[32][0][1]*wk[33][1]))+(.16*(
      cnk[33][0][0]*wk[33][0])))))+(((1.34*((rnk[30][1]*vnk[30][2])-(rnk[30][2]*
      vnk[30][1])))+((.0018*(cnk[29][0][2]*wk[30][2]))+((.007*(cnk[30][0][1]*
      wk[30][1]))+(.0075*(cnk[30][0][0]*wk[30][0])))))+temp[5]));
    am[0] = ((((1.34*((rnk[36][1]*vnk[36][2])-(rnk[36][2]*vnk[36][1])))+((.0018*
      (cnk[35][0][2]*wk[36][2]))+((.007*(cnk[36][0][1]*wk[36][1]))+(.0075*(
      cnk[36][0][0]*wk[36][0])))))+(((4.16*((rnk[34][1]*vnk[34][2])-(rnk[34][2]*
      vnk[34][1])))+((.055*(cnk[34][0][2]*wk[34][2]))+((.007*(cnk[34][0][1]*
      wk[34][1]))+(.056*(cnk[33][0][0]*wk[34][0])))))+temp[6]))-((com[1]*lm[2])-
      (com[2]*lm[1])));
    temp[0] = (((16.61*((rnk[5][2]*vnk[5][0])-(rnk[5][0]*vnk[5][2])))+((.23*(
      Cik[3][1][2]*u[5]))+((.16*(Cik[3][1][1]*u[4]))+(.18*(Cik[3][1][0]*u[3]))))
      )+((29.27*((rnk[8][2]*vnk[8][0])-(rnk[8][0]*vnk[8][2])))+((.73*(
      cnk[8][1][2]*wk[8][2]))+((.32*(cnk[7][1][1]*wk[8][1]))+(.63*(cnk[8][1][0]*
      wk[8][0]))))));
    temp[1] = (((5.89*((rnk[12][2]*vnk[12][0])-(rnk[12][0]*vnk[12][2])))+((.03*(
      cnk[12][1][2]*wk[12][2]))+((.023*(cnk[12][1][1]*wk[12][1]))+(.033*(
      cnk[11][1][0]*wk[12][0])))))+((((.006*(cnk[11][1][2]*wk[11][2]))+((.001*(
      cnk[10][1][1]*wk[11][1]))+(.006*(cnk[11][1][0]*wk[11][0]))))+((rnk[11][2]*
      vnk[11][0])-(rnk[11][0]*vnk[11][2])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][2]*vnk[16][0])-(rnk[16][0]*vnk[16][2])))+((.005*
      (cnk[16][1][2]*wk[16][2]))+((.0012*(cnk[15][1][0]*wk[16][0]))+(.0054*(
      cnk[16][1][1]*wk[16][1])))))+(((2.79*((rnk[14][2]*vnk[14][0])-(rnk[14][0]*
      vnk[14][2])))+((.025*(cnk[14][1][2]*wk[14][2]))+((.005*(cnk[14][1][0]*
      wk[14][0]))+(.025*(cnk[13][1][1]*wk[14][1])))))+temp[1]));
    temp[3] = (((2.79*((rnk[20][2]*vnk[20][0])-(rnk[20][0]*vnk[20][2])))+((.025*
      (cnk[20][1][2]*wk[20][2]))+((.005*(cnk[20][1][0]*wk[20][0]))+(.025*(
      cnk[19][1][1]*wk[20][1])))))+(((.55*((rnk[18][2]*vnk[18][0])-(rnk[18][0]*
      vnk[18][2])))+((.0016*(cnk[18][1][2]*wk[18][2]))+((.0005*(cnk[18][1][0]*
      wk[18][0]))+(.002*(cnk[17][1][1]*wk[18][1])))))+temp[2]));
    temp[4] = (((.55*((rnk[24][2]*vnk[24][0])-(rnk[24][0]*vnk[24][2])))+((.0016*
      (cnk[24][1][2]*wk[24][2]))+((.0005*(cnk[24][1][0]*wk[24][0]))+(.002*(
      cnk[23][1][1]*wk[24][1])))))+(((1.21*((rnk[22][2]*vnk[22][0])-(rnk[22][0]*
      vnk[22][2])))+((.005*(cnk[22][1][2]*wk[22][2]))+((.0012*(cnk[21][1][0]*
      wk[22][0]))+(.0054*(cnk[22][1][1]*wk[22][1])))))+temp[3]));
    temp[5] = (((4.16*((rnk[28][2]*vnk[28][0])-(rnk[28][0]*vnk[28][2])))+((.055*
      (cnk[28][1][2]*wk[28][2]))+((.007*(cnk[28][1][1]*wk[28][1]))+(.056*(
      cnk[27][1][0]*wk[28][0])))))+(((8.35*((rnk[27][2]*vnk[27][0])-(rnk[27][0]*
      vnk[27][2])))+((.15*(cnk[27][1][2]*wk[27][2]))+((.025*(cnk[26][1][1]*
      wk[27][1]))+(.16*(cnk[27][1][0]*wk[27][0])))))+temp[4]));
    temp[6] = (((8.35*((rnk[33][2]*vnk[33][0])-(rnk[33][0]*vnk[33][2])))+((.15*(
      cnk[33][1][2]*wk[33][2]))+((.025*(cnk[32][1][1]*wk[33][1]))+(.16*(
      cnk[33][1][0]*wk[33][0])))))+(((1.34*((rnk[30][2]*vnk[30][0])-(rnk[30][0]*
      vnk[30][2])))+((.0018*(cnk[29][1][2]*wk[30][2]))+((.007*(cnk[30][1][1]*
      wk[30][1]))+(.0075*(cnk[30][1][0]*wk[30][0])))))+temp[5]));
    am[1] = ((((1.34*((rnk[36][2]*vnk[36][0])-(rnk[36][0]*vnk[36][2])))+((.0018*
      (cnk[35][1][2]*wk[36][2]))+((.007*(cnk[36][1][1]*wk[36][1]))+(.0075*(
      cnk[36][1][0]*wk[36][0])))))+(((4.16*((rnk[34][2]*vnk[34][0])-(rnk[34][0]*
      vnk[34][2])))+((.055*(cnk[34][1][2]*wk[34][2]))+((.007*(cnk[34][1][1]*
      wk[34][1]))+(.056*(cnk[33][1][0]*wk[34][0])))))+temp[6]))-((com[2]*lm[0])-
      (com[0]*lm[2])));
    temp[0] = (((16.61*((rnk[5][0]*vnk[5][1])-(rnk[5][1]*vnk[5][0])))+((.23*(
      Cik[3][2][2]*u[5]))+((.16*(Cik[3][2][1]*u[4]))+(.18*(Cik[3][2][0]*u[3]))))
      )+((29.27*((rnk[8][0]*vnk[8][1])-(rnk[8][1]*vnk[8][0])))+((.73*(
      cnk[8][2][2]*wk[8][2]))+((.32*(cnk[7][2][1]*wk[8][1]))+(.63*(cnk[8][2][0]*
      wk[8][0]))))));
    temp[1] = (((5.89*((rnk[12][0]*vnk[12][1])-(rnk[12][1]*vnk[12][0])))+((.03*(
      cnk[12][2][2]*wk[12][2]))+((.023*(cnk[12][2][1]*wk[12][1]))+(.033*(
      cnk[11][2][0]*wk[12][0])))))+((((.006*(cnk[11][2][2]*wk[11][2]))+((.001*(
      cnk[10][2][1]*wk[11][1]))+(.006*(cnk[11][2][0]*wk[11][0]))))+((rnk[11][0]*
      vnk[11][1])-(rnk[11][1]*vnk[11][0])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][0]*vnk[16][1])-(rnk[16][1]*vnk[16][0])))+((.005*
      (cnk[16][2][2]*wk[16][2]))+((.0012*(cnk[15][2][0]*wk[16][0]))+(.0054*(
      cnk[16][2][1]*wk[16][1])))))+(((2.79*((rnk[14][0]*vnk[14][1])-(rnk[14][1]*
      vnk[14][0])))+((.025*(cnk[14][2][2]*wk[14][2]))+((.005*(cnk[14][2][0]*
      wk[14][0]))+(.025*(cnk[13][2][1]*wk[14][1])))))+temp[1]));
    temp[3] = (((2.79*((rnk[20][0]*vnk[20][1])-(rnk[20][1]*vnk[20][0])))+((.025*
      (cnk[20][2][2]*wk[20][2]))+((.005*(cnk[20][2][0]*wk[20][0]))+(.025*(
      cnk[19][2][1]*wk[20][1])))))+(((.55*((rnk[18][0]*vnk[18][1])-(rnk[18][1]*
      vnk[18][0])))+((.0016*(cnk[18][2][2]*wk[18][2]))+((.0005*(cnk[18][2][0]*
      wk[18][0]))+(.002*(cnk[17][2][1]*wk[18][1])))))+temp[2]));
    temp[4] = (((.55*((rnk[24][0]*vnk[24][1])-(rnk[24][1]*vnk[24][0])))+((.0016*
      (cnk[24][2][2]*wk[24][2]))+((.0005*(cnk[24][2][0]*wk[24][0]))+(.002*(
      cnk[23][2][1]*wk[24][1])))))+(((1.21*((rnk[22][0]*vnk[22][1])-(rnk[22][1]*
      vnk[22][0])))+((.005*(cnk[22][2][2]*wk[22][2]))+((.0012*(cnk[21][2][0]*
      wk[22][0]))+(.0054*(cnk[22][2][1]*wk[22][1])))))+temp[3]));
    temp[5] = (((4.16*((rnk[28][0]*vnk[28][1])-(rnk[28][1]*vnk[28][0])))+((.055*
      (cnk[28][2][2]*wk[28][2]))+((.007*(cnk[28][2][1]*wk[28][1]))+(.056*(
      cnk[27][2][0]*wk[28][0])))))+(((8.35*((rnk[27][0]*vnk[27][1])-(rnk[27][1]*
      vnk[27][0])))+((.15*(cnk[27][2][2]*wk[27][2]))+((.025*(cnk[26][2][1]*
      wk[27][1]))+(.16*(cnk[27][2][0]*wk[27][0])))))+temp[4]));
    temp[6] = (((8.35*((rnk[33][0]*vnk[33][1])-(rnk[33][1]*vnk[33][0])))+((.15*(
      cnk[33][2][2]*wk[33][2]))+((.025*(cnk[32][2][1]*wk[33][1]))+(.16*(
      cnk[33][2][0]*wk[33][0])))))+(((1.34*((rnk[30][0]*vnk[30][1])-(rnk[30][1]*
      vnk[30][0])))+((.0018*(cnk[29][2][2]*wk[30][2]))+((.007*(cnk[30][2][1]*
      wk[30][1]))+(.0075*(cnk[30][2][0]*wk[30][0])))))+temp[5]));
    am[2] = ((((1.34*((rnk[36][0]*vnk[36][1])-(rnk[36][1]*vnk[36][0])))+((.0018*
      (cnk[35][2][2]*wk[36][2]))+((.007*(cnk[36][2][1]*wk[36][1]))+(.0075*(
      cnk[36][2][0]*wk[36][0])))))+(((4.16*((rnk[34][0]*vnk[34][1])-(rnk[34][1]*
      vnk[34][0])))+((.055*(cnk[34][2][2]*wk[34][2]))+((.007*(cnk[34][2][1]*
      wk[34][1]))+(.056*(cnk[33][2][0]*wk[34][0])))))+temp[6]))-((com[0]*lm[1])-
      (com[1]*lm[0])));
    temp[0] = (((16.61*((vnk[5][2]*vnk[5][2])+((vnk[5][0]*vnk[5][0])+(vnk[5][1]*
      vnk[5][1]))))+((.23*(u[5]*u[5]))+((.16*(u[4]*u[4]))+(.18*(u[3]*u[3])))))+(
      (29.27*((vnk[8][2]*vnk[8][2])+((vnk[8][0]*vnk[8][0])+(vnk[8][1]*vnk[8][1])
      )))+((.73*(wk[8][2]*wk[8][2]))+((.32*(wk[8][1]*wk[8][1]))+(.63*(wk[8][0]*
      wk[8][0]))))));
    temp[1] = (((5.89*((vnk[12][2]*vnk[12][2])+((vnk[12][0]*vnk[12][0])+(
      vnk[12][1]*vnk[12][1]))))+((.03*(wk[12][2]*wk[12][2]))+((.023*(wk[12][1]*
      wk[12][1]))+(.033*(wk[12][0]*wk[12][0])))))+((((.006*(wk[11][2]*wk[11][2])
      )+((.001*(wk[11][1]*wk[11][1]))+(.006*(wk[11][0]*wk[11][0]))))+((
      vnk[11][2]*vnk[11][2])+((vnk[11][0]*vnk[11][0])+(vnk[11][1]*vnk[11][1]))))
      +temp[0]));
    temp[2] = (((1.21*((vnk[16][2]*vnk[16][2])+((vnk[16][0]*vnk[16][0])+(
      vnk[16][1]*vnk[16][1]))))+((.005*(wk[16][2]*wk[16][2]))+((.0012*(wk[16][0]
      *wk[16][0]))+(.0054*(wk[16][1]*wk[16][1])))))+(((2.79*((vnk[14][2]*
      vnk[14][2])+((vnk[14][0]*vnk[14][0])+(vnk[14][1]*vnk[14][1]))))+((.025*(
      wk[14][2]*wk[14][2]))+((.005*(wk[14][0]*wk[14][0]))+(.025*(wk[14][1]*
      wk[14][1])))))+temp[1]));
    temp[3] = (((2.79*((vnk[20][2]*vnk[20][2])+((vnk[20][0]*vnk[20][0])+(
      vnk[20][1]*vnk[20][1]))))+((.025*(wk[20][2]*wk[20][2]))+((.005*(wk[20][0]*
      wk[20][0]))+(.025*(wk[20][1]*wk[20][1])))))+(((.55*((vnk[18][2]*vnk[18][2]
      )+((vnk[18][0]*vnk[18][0])+(vnk[18][1]*vnk[18][1]))))+((.0016*(wk[18][2]*
      wk[18][2]))+((.0005*(wk[18][0]*wk[18][0]))+(.002*(wk[18][1]*wk[18][1])))))
      +temp[2]));
    temp[4] = (((.55*((vnk[24][2]*vnk[24][2])+((vnk[24][0]*vnk[24][0])+(
      vnk[24][1]*vnk[24][1]))))+((.0016*(wk[24][2]*wk[24][2]))+((.0005*(
      wk[24][0]*wk[24][0]))+(.002*(wk[24][1]*wk[24][1])))))+(((1.21*((vnk[22][2]
      *vnk[22][2])+((vnk[22][0]*vnk[22][0])+(vnk[22][1]*vnk[22][1]))))+((.005*(
      wk[22][2]*wk[22][2]))+((.0012*(wk[22][0]*wk[22][0]))+(.0054*(wk[22][1]*
      wk[22][1])))))+temp[3]));
    temp[5] = (((4.16*((vnk[28][2]*vnk[28][2])+((vnk[28][0]*vnk[28][0])+(
      vnk[28][1]*vnk[28][1]))))+((.055*(wk[28][2]*wk[28][2]))+((.007*(wk[28][1]*
      wk[28][1]))+(.056*(wk[28][0]*wk[28][0])))))+(((8.35*((vnk[27][2]*
      vnk[27][2])+((vnk[27][0]*vnk[27][0])+(vnk[27][1]*vnk[27][1]))))+((.15*(
      wk[27][2]*wk[27][2]))+((.025*(wk[27][1]*wk[27][1]))+(.16*(wk[27][0]*
      wk[27][0])))))+temp[4]));
    temp[6] = (((8.35*((vnk[33][2]*vnk[33][2])+((vnk[33][0]*vnk[33][0])+(
      vnk[33][1]*vnk[33][1]))))+((.15*(wk[33][2]*wk[33][2]))+((.025*(wk[33][1]*
      wk[33][1]))+(.16*(wk[33][0]*wk[33][0])))))+(((1.34*((vnk[30][2]*vnk[30][2]
      )+((vnk[30][0]*vnk[30][0])+(vnk[30][1]*vnk[30][1]))))+((.0018*(wk[30][2]*
      wk[30][2]))+((.007*(wk[30][1]*wk[30][1]))+(.0075*(wk[30][0]*wk[30][0])))))
      +temp[5]));
    *ke = (.5*(((1.34*((vnk[36][2]*vnk[36][2])+((vnk[36][0]*vnk[36][0])+(
      vnk[36][1]*vnk[36][1]))))+((.0018*(wk[36][2]*wk[36][2]))+((.007*(wk[36][1]
      *wk[36][1]))+(.0075*(wk[36][0]*wk[36][0])))))+(((4.16*((vnk[34][2]*
      vnk[34][2])+((vnk[34][0]*vnk[34][0])+(vnk[34][1]*vnk[34][1]))))+((.055*(
      wk[34][2]*wk[34][2]))+((.007*(wk[34][1]*wk[34][1]))+(.056*(wk[34][0]*
      wk[34][0])))))+temp[6])));
/*
 Used 0.78 seconds CPU time,
 49152 additional bytes of memory.
 Equations contain  383 adds/subtracts/negates
                    640 multiplies
                      0 divides
                     35 assignments
*/
}

void skel18sys(double *mtoto, double *cm, double (*icm)[3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 23-Nov-1999 14:31:09 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 69073f01
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[37][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(20,23);
        return;
    }
    *mtoto = 89.57;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    temp[0] = (((16.61*((rnk[5][1]*rnk[5][1])+(rnk[5][2]*rnk[5][2])))+((.23*(
      Cik[3][0][2]*Cik[3][0][2]))+((.16*(Cik[3][0][1]*Cik[3][0][1]))+(.18*(
      Cik[3][0][0]*Cik[3][0][0])))))+((29.27*((rnk[8][1]*rnk[8][1])+(rnk[8][2]*
      rnk[8][2])))+((.73*(cnk[8][0][2]*cnk[8][0][2]))+((.32*(cnk[7][0][1]*
      cnk[7][0][1]))+(.63*(cnk[8][0][0]*cnk[8][0][0]))))));
    temp[1] = (((5.89*((rnk[12][1]*rnk[12][1])+(rnk[12][2]*rnk[12][2])))+((.03*(
      cnk[12][0][2]*cnk[12][0][2]))+((.023*(cnk[12][0][1]*cnk[12][0][1]))+(.033*
      (cnk[11][0][0]*cnk[11][0][0])))))+((((.006*(cnk[11][0][2]*cnk[11][0][2]))+
      ((.001*(cnk[10][0][1]*cnk[10][0][1]))+(.006*(cnk[11][0][0]*cnk[11][0][0]))
      ))+((rnk[11][1]*rnk[11][1])+(rnk[11][2]*rnk[11][2])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][1]*rnk[16][1])+(rnk[16][2]*rnk[16][2])))+((.005*
      (cnk[16][0][2]*cnk[16][0][2]))+((.0012*(cnk[15][0][0]*cnk[15][0][0]))+(
      .0054*(cnk[16][0][1]*cnk[16][0][1])))))+(((2.79*((rnk[14][1]*rnk[14][1])+(
      rnk[14][2]*rnk[14][2])))+((.025*(cnk[14][0][2]*cnk[14][0][2]))+((.005*(
      cnk[14][0][0]*cnk[14][0][0]))+(.025*(cnk[13][0][1]*cnk[13][0][1])))))+
      temp[1]));
    temp[3] = (((2.79*((rnk[20][1]*rnk[20][1])+(rnk[20][2]*rnk[20][2])))+((.025*
      (cnk[20][0][2]*cnk[20][0][2]))+((.005*(cnk[20][0][0]*cnk[20][0][0]))+(.025
      *(cnk[19][0][1]*cnk[19][0][1])))))+(((.55*((rnk[18][1]*rnk[18][1])+(
      rnk[18][2]*rnk[18][2])))+((.0016*(cnk[18][0][2]*cnk[18][0][2]))+((.0005*(
      cnk[18][0][0]*cnk[18][0][0]))+(.002*(cnk[17][0][1]*cnk[17][0][1])))))+
      temp[2]));
    temp[4] = (((.55*((rnk[24][1]*rnk[24][1])+(rnk[24][2]*rnk[24][2])))+((.0016*
      (cnk[24][0][2]*cnk[24][0][2]))+((.0005*(cnk[24][0][0]*cnk[24][0][0]))+(
      .002*(cnk[23][0][1]*cnk[23][0][1])))))+(((1.21*((rnk[22][1]*rnk[22][1])+(
      rnk[22][2]*rnk[22][2])))+((.005*(cnk[22][0][2]*cnk[22][0][2]))+((.0012*(
      cnk[21][0][0]*cnk[21][0][0]))+(.0054*(cnk[22][0][1]*cnk[22][0][1])))))+
      temp[3]));
    temp[5] = (((4.16*((rnk[28][1]*rnk[28][1])+(rnk[28][2]*rnk[28][2])))+((.055*
      (cnk[28][0][2]*cnk[28][0][2]))+((.007*(cnk[28][0][1]*cnk[28][0][1]))+(.056
      *(cnk[27][0][0]*cnk[27][0][0])))))+(((8.35*((rnk[27][1]*rnk[27][1])+(
      rnk[27][2]*rnk[27][2])))+((.15*(cnk[27][0][2]*cnk[27][0][2]))+((.025*(
      cnk[26][0][1]*cnk[26][0][1]))+(.16*(cnk[27][0][0]*cnk[27][0][0])))))+
      temp[4]));
    temp[6] = (((8.35*((rnk[33][1]*rnk[33][1])+(rnk[33][2]*rnk[33][2])))+((.15*(
      cnk[33][0][2]*cnk[33][0][2]))+((.025*(cnk[32][0][1]*cnk[32][0][1]))+(.16*(
      cnk[33][0][0]*cnk[33][0][0])))))+(((1.34*((rnk[30][1]*rnk[30][1])+(
      rnk[30][2]*rnk[30][2])))+((.0018*(cnk[29][0][2]*cnk[29][0][2]))+((.007*(
      cnk[30][0][1]*cnk[30][0][1]))+(.0075*(cnk[30][0][0]*cnk[30][0][0])))))+
      temp[5]));
    icm[0][0] = ((((1.34*((rnk[36][1]*rnk[36][1])+(rnk[36][2]*rnk[36][2])))+((
      .0018*(cnk[35][0][2]*cnk[35][0][2]))+((.007*(cnk[36][0][1]*cnk[36][0][1]))
      +(.0075*(cnk[36][0][0]*cnk[36][0][0])))))+(((4.16*((rnk[34][1]*rnk[34][1])
      +(rnk[34][2]*rnk[34][2])))+((.055*(cnk[34][0][2]*cnk[34][0][2]))+((.007*(
      cnk[34][0][1]*cnk[34][0][1]))+(.056*(cnk[33][0][0]*cnk[33][0][0])))))+
      temp[6]))-(89.57*((com[1]*com[1])+(com[2]*com[2]))));
    temp[0] = ((((.23*(Cik[3][0][2]*Cik[3][1][2]))+((.16*(Cik[3][0][1]*
      Cik[3][1][1]))+(.18*(Cik[3][0][0]*Cik[3][1][0]))))-(16.61*(rnk[5][0]*
      rnk[5][1])))+(((.73*(cnk[8][0][2]*cnk[8][1][2]))+((.32*(cnk[7][0][1]*
      cnk[7][1][1]))+(.63*(cnk[8][0][0]*cnk[8][1][0]))))-(29.27*(rnk[8][0]*
      rnk[8][1]))));
    temp[1] = ((((.03*(cnk[12][0][2]*cnk[12][1][2]))+((.023*(cnk[12][0][1]*
      cnk[12][1][1]))+(.033*(cnk[11][0][0]*cnk[11][1][0]))))-(5.89*(rnk[12][0]*
      rnk[12][1])))+((((.006*(cnk[11][0][2]*cnk[11][1][2]))+((.001*(
      cnk[10][0][1]*cnk[10][1][1]))+(.006*(cnk[11][0][0]*cnk[11][1][0]))))-(
      rnk[11][0]*rnk[11][1]))+temp[0]));
    temp[2] = ((((.005*(cnk[16][0][2]*cnk[16][1][2]))+((.0012*(cnk[15][0][0]*
      cnk[15][1][0]))+(.0054*(cnk[16][0][1]*cnk[16][1][1]))))-(1.21*(rnk[16][0]*
      rnk[16][1])))+((((.025*(cnk[14][0][2]*cnk[14][1][2]))+((.005*(
      cnk[14][0][0]*cnk[14][1][0]))+(.025*(cnk[13][0][1]*cnk[13][1][1]))))-(2.79
      *(rnk[14][0]*rnk[14][1])))+temp[1]));
    temp[3] = ((((.025*(cnk[20][0][2]*cnk[20][1][2]))+((.005*(cnk[20][0][0]*
      cnk[20][1][0]))+(.025*(cnk[19][0][1]*cnk[19][1][1]))))-(2.79*(rnk[20][0]*
      rnk[20][1])))+((((.0016*(cnk[18][0][2]*cnk[18][1][2]))+((.0005*(
      cnk[18][0][0]*cnk[18][1][0]))+(.002*(cnk[17][0][1]*cnk[17][1][1]))))-(.55*
      (rnk[18][0]*rnk[18][1])))+temp[2]));
    temp[4] = ((((.0016*(cnk[24][0][2]*cnk[24][1][2]))+((.0005*(cnk[24][0][0]*
      cnk[24][1][0]))+(.002*(cnk[23][0][1]*cnk[23][1][1]))))-(.55*(rnk[24][0]*
      rnk[24][1])))+((((.005*(cnk[22][0][2]*cnk[22][1][2]))+((.0012*(
      cnk[21][0][0]*cnk[21][1][0]))+(.0054*(cnk[22][0][1]*cnk[22][1][1]))))-(
      1.21*(rnk[22][0]*rnk[22][1])))+temp[3]));
    temp[5] = ((((.055*(cnk[28][0][2]*cnk[28][1][2]))+((.007*(cnk[28][0][1]*
      cnk[28][1][1]))+(.056*(cnk[27][0][0]*cnk[27][1][0]))))-(4.16*(rnk[28][0]*
      rnk[28][1])))+((((.15*(cnk[27][0][2]*cnk[27][1][2]))+((.025*(cnk[26][0][1]
      *cnk[26][1][1]))+(.16*(cnk[27][0][0]*cnk[27][1][0]))))-(8.35*(rnk[27][0]*
      rnk[27][1])))+temp[4]));
    temp[6] = ((((.15*(cnk[33][0][2]*cnk[33][1][2]))+((.025*(cnk[32][0][1]*
      cnk[32][1][1]))+(.16*(cnk[33][0][0]*cnk[33][1][0]))))-(8.35*(rnk[33][0]*
      rnk[33][1])))+((((.0018*(cnk[29][0][2]*cnk[29][1][2]))+((.007*(
      cnk[30][0][1]*cnk[30][1][1]))+(.0075*(cnk[30][0][0]*cnk[30][1][0]))))-(
      1.34*(rnk[30][0]*rnk[30][1])))+temp[5]));
    icm[0][1] = ((89.57*(com[0]*com[1]))+((((.0018*(cnk[35][0][2]*cnk[35][1][2])
      )+((.007*(cnk[36][0][1]*cnk[36][1][1]))+(.0075*(cnk[36][0][0]*
      cnk[36][1][0]))))-(1.34*(rnk[36][0]*rnk[36][1])))+((((.055*(cnk[34][0][2]*
      cnk[34][1][2]))+((.007*(cnk[34][0][1]*cnk[34][1][1]))+(.056*(cnk[33][0][0]
      *cnk[33][1][0]))))-(4.16*(rnk[34][0]*rnk[34][1])))+temp[6])));
    temp[0] = ((((.23*(Cik[3][0][2]*Cik[3][2][2]))+((.16*(Cik[3][0][1]*
      Cik[3][2][1]))+(.18*(Cik[3][0][0]*Cik[3][2][0]))))-(16.61*(rnk[5][0]*
      rnk[5][2])))+(((.73*(cnk[8][0][2]*cnk[8][2][2]))+((.32*(cnk[7][0][1]*
      cnk[7][2][1]))+(.63*(cnk[8][0][0]*cnk[8][2][0]))))-(29.27*(rnk[8][0]*
      rnk[8][2]))));
    temp[1] = ((((.03*(cnk[12][0][2]*cnk[12][2][2]))+((.023*(cnk[12][0][1]*
      cnk[12][2][1]))+(.033*(cnk[11][0][0]*cnk[11][2][0]))))-(5.89*(rnk[12][0]*
      rnk[12][2])))+((((.006*(cnk[11][0][2]*cnk[11][2][2]))+((.001*(
      cnk[10][0][1]*cnk[10][2][1]))+(.006*(cnk[11][0][0]*cnk[11][2][0]))))-(
      rnk[11][0]*rnk[11][2]))+temp[0]));
    temp[2] = ((((.005*(cnk[16][0][2]*cnk[16][2][2]))+((.0012*(cnk[15][0][0]*
      cnk[15][2][0]))+(.0054*(cnk[16][0][1]*cnk[16][2][1]))))-(1.21*(rnk[16][0]*
      rnk[16][2])))+((((.025*(cnk[14][0][2]*cnk[14][2][2]))+((.005*(
      cnk[14][0][0]*cnk[14][2][0]))+(.025*(cnk[13][0][1]*cnk[13][2][1]))))-(2.79
      *(rnk[14][0]*rnk[14][2])))+temp[1]));
    temp[3] = ((((.025*(cnk[20][0][2]*cnk[20][2][2]))+((.005*(cnk[20][0][0]*
      cnk[20][2][0]))+(.025*(cnk[19][0][1]*cnk[19][2][1]))))-(2.79*(rnk[20][0]*
      rnk[20][2])))+((((.0016*(cnk[18][0][2]*cnk[18][2][2]))+((.0005*(
      cnk[18][0][0]*cnk[18][2][0]))+(.002*(cnk[17][0][1]*cnk[17][2][1]))))-(.55*
      (rnk[18][0]*rnk[18][2])))+temp[2]));
    temp[4] = ((((.0016*(cnk[24][0][2]*cnk[24][2][2]))+((.0005*(cnk[24][0][0]*
      cnk[24][2][0]))+(.002*(cnk[23][0][1]*cnk[23][2][1]))))-(.55*(rnk[24][0]*
      rnk[24][2])))+((((.005*(cnk[22][0][2]*cnk[22][2][2]))+((.0012*(
      cnk[21][0][0]*cnk[21][2][0]))+(.0054*(cnk[22][0][1]*cnk[22][2][1]))))-(
      1.21*(rnk[22][0]*rnk[22][2])))+temp[3]));
    temp[5] = ((((.055*(cnk[28][0][2]*cnk[28][2][2]))+((.007*(cnk[28][0][1]*
      cnk[28][2][1]))+(.056*(cnk[27][0][0]*cnk[27][2][0]))))-(4.16*(rnk[28][0]*
      rnk[28][2])))+((((.15*(cnk[27][0][2]*cnk[27][2][2]))+((.025*(cnk[26][0][1]
      *cnk[26][2][1]))+(.16*(cnk[27][0][0]*cnk[27][2][0]))))-(8.35*(rnk[27][0]*
      rnk[27][2])))+temp[4]));
    temp[6] = ((((.15*(cnk[33][0][2]*cnk[33][2][2]))+((.025*(cnk[32][0][1]*
      cnk[32][2][1]))+(.16*(cnk[33][0][0]*cnk[33][2][0]))))-(8.35*(rnk[33][0]*
      rnk[33][2])))+((((.0018*(cnk[29][0][2]*cnk[29][2][2]))+((.007*(
      cnk[30][0][1]*cnk[30][2][1]))+(.0075*(cnk[30][0][0]*cnk[30][2][0]))))-(
      1.34*(rnk[30][0]*rnk[30][2])))+temp[5]));
    icm[0][2] = ((89.57*(com[0]*com[2]))+((((.0018*(cnk[35][0][2]*cnk[35][2][2])
      )+((.007*(cnk[36][0][1]*cnk[36][2][1]))+(.0075*(cnk[36][0][0]*
      cnk[36][2][0]))))-(1.34*(rnk[36][0]*rnk[36][2])))+((((.055*(cnk[34][0][2]*
      cnk[34][2][2]))+((.007*(cnk[34][0][1]*cnk[34][2][1]))+(.056*(cnk[33][0][0]
      *cnk[33][2][0]))))-(4.16*(rnk[34][0]*rnk[34][2])))+temp[6])));
    icm[1][0] = icm[0][1];
    temp[0] = (((16.61*((rnk[5][0]*rnk[5][0])+(rnk[5][2]*rnk[5][2])))+((.23*(
      Cik[3][1][2]*Cik[3][1][2]))+((.16*(Cik[3][1][1]*Cik[3][1][1]))+(.18*(
      Cik[3][1][0]*Cik[3][1][0])))))+((29.27*((rnk[8][0]*rnk[8][0])+(rnk[8][2]*
      rnk[8][2])))+((.73*(cnk[8][1][2]*cnk[8][1][2]))+((.32*(cnk[7][1][1]*
      cnk[7][1][1]))+(.63*(cnk[8][1][0]*cnk[8][1][0]))))));
    temp[1] = (((5.89*((rnk[12][0]*rnk[12][0])+(rnk[12][2]*rnk[12][2])))+((.03*(
      cnk[12][1][2]*cnk[12][1][2]))+((.023*(cnk[12][1][1]*cnk[12][1][1]))+(.033*
      (cnk[11][1][0]*cnk[11][1][0])))))+((((.006*(cnk[11][1][2]*cnk[11][1][2]))+
      ((.001*(cnk[10][1][1]*cnk[10][1][1]))+(.006*(cnk[11][1][0]*cnk[11][1][0]))
      ))+((rnk[11][0]*rnk[11][0])+(rnk[11][2]*rnk[11][2])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][0]*rnk[16][0])+(rnk[16][2]*rnk[16][2])))+((.005*
      (cnk[16][1][2]*cnk[16][1][2]))+((.0012*(cnk[15][1][0]*cnk[15][1][0]))+(
      .0054*(cnk[16][1][1]*cnk[16][1][1])))))+(((2.79*((rnk[14][0]*rnk[14][0])+(
      rnk[14][2]*rnk[14][2])))+((.025*(cnk[14][1][2]*cnk[14][1][2]))+((.005*(
      cnk[14][1][0]*cnk[14][1][0]))+(.025*(cnk[13][1][1]*cnk[13][1][1])))))+
      temp[1]));
    temp[3] = (((2.79*((rnk[20][0]*rnk[20][0])+(rnk[20][2]*rnk[20][2])))+((.025*
      (cnk[20][1][2]*cnk[20][1][2]))+((.005*(cnk[20][1][0]*cnk[20][1][0]))+(.025
      *(cnk[19][1][1]*cnk[19][1][1])))))+(((.55*((rnk[18][0]*rnk[18][0])+(
      rnk[18][2]*rnk[18][2])))+((.0016*(cnk[18][1][2]*cnk[18][1][2]))+((.0005*(
      cnk[18][1][0]*cnk[18][1][0]))+(.002*(cnk[17][1][1]*cnk[17][1][1])))))+
      temp[2]));
    temp[4] = (((.55*((rnk[24][0]*rnk[24][0])+(rnk[24][2]*rnk[24][2])))+((.0016*
      (cnk[24][1][2]*cnk[24][1][2]))+((.0005*(cnk[24][1][0]*cnk[24][1][0]))+(
      .002*(cnk[23][1][1]*cnk[23][1][1])))))+(((1.21*((rnk[22][0]*rnk[22][0])+(
      rnk[22][2]*rnk[22][2])))+((.005*(cnk[22][1][2]*cnk[22][1][2]))+((.0012*(
      cnk[21][1][0]*cnk[21][1][0]))+(.0054*(cnk[22][1][1]*cnk[22][1][1])))))+
      temp[3]));
    temp[5] = (((4.16*((rnk[28][0]*rnk[28][0])+(rnk[28][2]*rnk[28][2])))+((.055*
      (cnk[28][1][2]*cnk[28][1][2]))+((.007*(cnk[28][1][1]*cnk[28][1][1]))+(.056
      *(cnk[27][1][0]*cnk[27][1][0])))))+(((8.35*((rnk[27][0]*rnk[27][0])+(
      rnk[27][2]*rnk[27][2])))+((.15*(cnk[27][1][2]*cnk[27][1][2]))+((.025*(
      cnk[26][1][1]*cnk[26][1][1]))+(.16*(cnk[27][1][0]*cnk[27][1][0])))))+
      temp[4]));
    temp[6] = (((8.35*((rnk[33][0]*rnk[33][0])+(rnk[33][2]*rnk[33][2])))+((.15*(
      cnk[33][1][2]*cnk[33][1][2]))+((.025*(cnk[32][1][1]*cnk[32][1][1]))+(.16*(
      cnk[33][1][0]*cnk[33][1][0])))))+(((1.34*((rnk[30][0]*rnk[30][0])+(
      rnk[30][2]*rnk[30][2])))+((.0018*(cnk[29][1][2]*cnk[29][1][2]))+((.007*(
      cnk[30][1][1]*cnk[30][1][1]))+(.0075*(cnk[30][1][0]*cnk[30][1][0])))))+
      temp[5]));
    icm[1][1] = ((((1.34*((rnk[36][0]*rnk[36][0])+(rnk[36][2]*rnk[36][2])))+((
      .0018*(cnk[35][1][2]*cnk[35][1][2]))+((.007*(cnk[36][1][1]*cnk[36][1][1]))
      +(.0075*(cnk[36][1][0]*cnk[36][1][0])))))+(((4.16*((rnk[34][0]*rnk[34][0])
      +(rnk[34][2]*rnk[34][2])))+((.055*(cnk[34][1][2]*cnk[34][1][2]))+((.007*(
      cnk[34][1][1]*cnk[34][1][1]))+(.056*(cnk[33][1][0]*cnk[33][1][0])))))+
      temp[6]))-(89.57*((com[0]*com[0])+(com[2]*com[2]))));
    temp[0] = ((((.23*(Cik[3][1][2]*Cik[3][2][2]))+((.16*(Cik[3][1][1]*
      Cik[3][2][1]))+(.18*(Cik[3][1][0]*Cik[3][2][0]))))-(16.61*(rnk[5][1]*
      rnk[5][2])))+(((.73*(cnk[8][1][2]*cnk[8][2][2]))+((.32*(cnk[7][1][1]*
      cnk[7][2][1]))+(.63*(cnk[8][1][0]*cnk[8][2][0]))))-(29.27*(rnk[8][1]*
      rnk[8][2]))));
    temp[1] = ((((.03*(cnk[12][1][2]*cnk[12][2][2]))+((.023*(cnk[12][1][1]*
      cnk[12][2][1]))+(.033*(cnk[11][1][0]*cnk[11][2][0]))))-(5.89*(rnk[12][1]*
      rnk[12][2])))+((((.006*(cnk[11][1][2]*cnk[11][2][2]))+((.001*(
      cnk[10][1][1]*cnk[10][2][1]))+(.006*(cnk[11][1][0]*cnk[11][2][0]))))-(
      rnk[11][1]*rnk[11][2]))+temp[0]));
    temp[2] = ((((.005*(cnk[16][1][2]*cnk[16][2][2]))+((.0012*(cnk[15][1][0]*
      cnk[15][2][0]))+(.0054*(cnk[16][1][1]*cnk[16][2][1]))))-(1.21*(rnk[16][1]*
      rnk[16][2])))+((((.025*(cnk[14][1][2]*cnk[14][2][2]))+((.005*(
      cnk[14][1][0]*cnk[14][2][0]))+(.025*(cnk[13][1][1]*cnk[13][2][1]))))-(2.79
      *(rnk[14][1]*rnk[14][2])))+temp[1]));
    temp[3] = ((((.025*(cnk[20][1][2]*cnk[20][2][2]))+((.005*(cnk[20][1][0]*
      cnk[20][2][0]))+(.025*(cnk[19][1][1]*cnk[19][2][1]))))-(2.79*(rnk[20][1]*
      rnk[20][2])))+((((.0016*(cnk[18][1][2]*cnk[18][2][2]))+((.0005*(
      cnk[18][1][0]*cnk[18][2][0]))+(.002*(cnk[17][1][1]*cnk[17][2][1]))))-(.55*
      (rnk[18][1]*rnk[18][2])))+temp[2]));
    temp[4] = ((((.0016*(cnk[24][1][2]*cnk[24][2][2]))+((.0005*(cnk[24][1][0]*
      cnk[24][2][0]))+(.002*(cnk[23][1][1]*cnk[23][2][1]))))-(.55*(rnk[24][1]*
      rnk[24][2])))+((((.005*(cnk[22][1][2]*cnk[22][2][2]))+((.0012*(
      cnk[21][1][0]*cnk[21][2][0]))+(.0054*(cnk[22][1][1]*cnk[22][2][1]))))-(
      1.21*(rnk[22][1]*rnk[22][2])))+temp[3]));
    temp[5] = ((((.055*(cnk[28][1][2]*cnk[28][2][2]))+((.007*(cnk[28][1][1]*
      cnk[28][2][1]))+(.056*(cnk[27][1][0]*cnk[27][2][0]))))-(4.16*(rnk[28][1]*
      rnk[28][2])))+((((.15*(cnk[27][1][2]*cnk[27][2][2]))+((.025*(cnk[26][1][1]
      *cnk[26][2][1]))+(.16*(cnk[27][1][0]*cnk[27][2][0]))))-(8.35*(rnk[27][1]*
      rnk[27][2])))+temp[4]));
    temp[6] = ((((.15*(cnk[33][1][2]*cnk[33][2][2]))+((.025*(cnk[32][1][1]*
      cnk[32][2][1]))+(.16*(cnk[33][1][0]*cnk[33][2][0]))))-(8.35*(rnk[33][1]*
      rnk[33][2])))+((((.0018*(cnk[29][1][2]*cnk[29][2][2]))+((.007*(
      cnk[30][1][1]*cnk[30][2][1]))+(.0075*(cnk[30][1][0]*cnk[30][2][0]))))-(
      1.34*(rnk[30][1]*rnk[30][2])))+temp[5]));
    icm[1][2] = ((89.57*(com[1]*com[2]))+((((.0018*(cnk[35][1][2]*cnk[35][2][2])
      )+((.007*(cnk[36][1][1]*cnk[36][2][1]))+(.0075*(cnk[36][1][0]*
      cnk[36][2][0]))))-(1.34*(rnk[36][1]*rnk[36][2])))+((((.055*(cnk[34][1][2]*
      cnk[34][2][2]))+((.007*(cnk[34][1][1]*cnk[34][2][1]))+(.056*(cnk[33][1][0]
      *cnk[33][2][0]))))-(4.16*(rnk[34][1]*rnk[34][2])))+temp[6])));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((16.61*((rnk[5][0]*rnk[5][0])+(rnk[5][1]*rnk[5][1])))+((.23*(
      Cik[3][2][2]*Cik[3][2][2]))+((.16*(Cik[3][2][1]*Cik[3][2][1]))+(.18*(
      Cik[3][2][0]*Cik[3][2][0])))))+((29.27*((rnk[8][0]*rnk[8][0])+(rnk[8][1]*
      rnk[8][1])))+((.73*(cnk[8][2][2]*cnk[8][2][2]))+((.32*(cnk[7][2][1]*
      cnk[7][2][1]))+(.63*(cnk[8][2][0]*cnk[8][2][0]))))));
    temp[1] = (((5.89*((rnk[12][0]*rnk[12][0])+(rnk[12][1]*rnk[12][1])))+((.03*(
      cnk[12][2][2]*cnk[12][2][2]))+((.023*(cnk[12][2][1]*cnk[12][2][1]))+(.033*
      (cnk[11][2][0]*cnk[11][2][0])))))+((((.006*(cnk[11][2][2]*cnk[11][2][2]))+
      ((.001*(cnk[10][2][1]*cnk[10][2][1]))+(.006*(cnk[11][2][0]*cnk[11][2][0]))
      ))+((rnk[11][0]*rnk[11][0])+(rnk[11][1]*rnk[11][1])))+temp[0]));
    temp[2] = (((1.21*((rnk[16][0]*rnk[16][0])+(rnk[16][1]*rnk[16][1])))+((.005*
      (cnk[16][2][2]*cnk[16][2][2]))+((.0012*(cnk[15][2][0]*cnk[15][2][0]))+(
      .0054*(cnk[16][2][1]*cnk[16][2][1])))))+(((2.79*((rnk[14][0]*rnk[14][0])+(
      rnk[14][1]*rnk[14][1])))+((.025*(cnk[14][2][2]*cnk[14][2][2]))+((.005*(
      cnk[14][2][0]*cnk[14][2][0]))+(.025*(cnk[13][2][1]*cnk[13][2][1])))))+
      temp[1]));
    temp[3] = (((2.79*((rnk[20][0]*rnk[20][0])+(rnk[20][1]*rnk[20][1])))+((.025*
      (cnk[20][2][2]*cnk[20][2][2]))+((.005*(cnk[20][2][0]*cnk[20][2][0]))+(.025
      *(cnk[19][2][1]*cnk[19][2][1])))))+(((.55*((rnk[18][0]*rnk[18][0])+(
      rnk[18][1]*rnk[18][1])))+((.0016*(cnk[18][2][2]*cnk[18][2][2]))+((.0005*(
      cnk[18][2][0]*cnk[18][2][0]))+(.002*(cnk[17][2][1]*cnk[17][2][1])))))+
      temp[2]));
    temp[4] = (((.55*((rnk[24][0]*rnk[24][0])+(rnk[24][1]*rnk[24][1])))+((.0016*
      (cnk[24][2][2]*cnk[24][2][2]))+((.0005*(cnk[24][2][0]*cnk[24][2][0]))+(
      .002*(cnk[23][2][1]*cnk[23][2][1])))))+(((1.21*((rnk[22][0]*rnk[22][0])+(
      rnk[22][1]*rnk[22][1])))+((.005*(cnk[22][2][2]*cnk[22][2][2]))+((.0012*(
      cnk[21][2][0]*cnk[21][2][0]))+(.0054*(cnk[22][2][1]*cnk[22][2][1])))))+
      temp[3]));
    temp[5] = (((4.16*((rnk[28][0]*rnk[28][0])+(rnk[28][1]*rnk[28][1])))+((.055*
      (cnk[28][2][2]*cnk[28][2][2]))+((.007*(cnk[28][2][1]*cnk[28][2][1]))+(.056
      *(cnk[27][2][0]*cnk[27][2][0])))))+(((8.35*((rnk[27][0]*rnk[27][0])+(
      rnk[27][1]*rnk[27][1])))+((.15*(cnk[27][2][2]*cnk[27][2][2]))+((.025*(
      cnk[26][2][1]*cnk[26][2][1]))+(.16*(cnk[27][2][0]*cnk[27][2][0])))))+
      temp[4]));
    temp[6] = (((8.35*((rnk[33][0]*rnk[33][0])+(rnk[33][1]*rnk[33][1])))+((.15*(
      cnk[33][2][2]*cnk[33][2][2]))+((.025*(cnk[32][2][1]*cnk[32][2][1]))+(.16*(
      cnk[33][2][0]*cnk[33][2][0])))))+(((1.34*((rnk[30][0]*rnk[30][0])+(
      rnk[30][1]*rnk[30][1])))+((.0018*(cnk[29][2][2]*cnk[29][2][2]))+((.007*(
      cnk[30][2][1]*cnk[30][2][1]))+(.0075*(cnk[30][2][0]*cnk[30][2][0])))))+
      temp[5]));
    icm[2][2] = ((((1.34*((rnk[36][0]*rnk[36][0])+(rnk[36][1]*rnk[36][1])))+((
      .0018*(cnk[35][2][2]*cnk[35][2][2]))+((.007*(cnk[36][2][1]*cnk[36][2][1]))
      +(.0075*(cnk[36][2][0]*cnk[36][2][0])))))+(((4.16*((rnk[34][0]*rnk[34][0])
      +(rnk[34][1]*rnk[34][1])))+((.055*(cnk[34][2][2]*cnk[34][2][2]))+((.007*(
      cnk[34][2][1]*cnk[34][2][1]))+(.056*(cnk[33][2][0]*cnk[33][2][0])))))+
      temp[6]))-(89.57*((com[0]*com[0])+(com[1]*com[1]))));
/*
 Used 2.22 seconds CPU time,
 81920 additional bytes of memory.
 Equations contain  435 adds/subtracts/negates
                    825 multiplies
                      0 divides
                     55 assignments
*/
}

void skel18pos(int body, double *pt, double *loc)
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (skel18chkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(21,23);
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

void skel18vel(int body, double *pt, double *velo)
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (skel18chkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(22,23);
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

void skel18orient(int body, double (*dircos)[3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (skel18chkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(23,23);
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

void skel18angvel(int body, double *avel)
{
/*
Return angular velocity of the body.

*/

    if (skel18chkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(24,23);
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

void skel18trans(int frbod, double *ivec, int tobod, double *ovec)
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (skel18chkbnum(25,frbod) != 0) {
        return;
    }
    if (skel18chkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(25,23);
        return;
    }
    if (frbod == tobod) {
        skel18vcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        skel18vcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        skel18vcopy(ivec,pv);
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

void skel18rel2cart(int coord, int body, double *point, double *linchg, double *rotchg)
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 36)) {
        skel18seterr(59,45);
        return;
    }
    if (skel18chkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        skel18seterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        skel18vset(0.,0.,0.,linchg);
        skel18vset(0.,0.,0.,rotchg);
        return;
    }
    skel18dovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        skel18vcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    skel18vcross(rotchg,pv,linchg);
    skel18vadd(linchg,lin,linchg);
}

void skel18acc(int body, double *pt, double *accel)
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (skel18chkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        skel18seterr(32,24);
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

void skel18angacc(int body, double *aacc)
{
/*
Return angular acceleration of the body.

*/

    if (skel18chkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        skel18seterr(33,24);
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

void skel18grav(double *gravin)
{

    skel18seterr(1,19);
    roustate = 0;
}

void skel18mass(int body, double massin)
{

    if (skel18chkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        skel18seterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        skel18seterr(2,19);
    }
    roustate = 0;
}

void skel18iner(int body, double (*inerin)[3])
{
    int anyques;

    if (skel18chkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        skel18seterr(3,15);
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
        skel18seterr(3,19);
    }
    roustate = 0;
}

void skel18btj(int joint, double *btjin)
{
    int anyques;

    if (skel18chkjnum(4,joint) != 0) {
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
        skel18seterr(4,19);
    }
    roustate = 0;
}

void skel18itj(int joint, double *itjin)
{
    int anyques;

    if (skel18chkjnum(5,joint) != 0) {
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
        skel18seterr(5,19);
    }
    roustate = 0;
}

void skel18pin(int joint, int pinno, double *pinin)
{
    int anyques,offs;

    if (skel18chkjpin(6,joint,pinno) != 0) {
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
        skel18seterr(6,19);
    }
    roustate = 0;
}

void skel18pres(int joint, int axis, int presin)
{
    int anyques;

    if (skel18chkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        skel18seterr(37,20);
    }
    anyques = 0;
    if (presq[skel18indx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[skel18indx(joint,axis)] = 1.;
        } else {
            pres[skel18indx(joint,axis)] = 0.;
        }
        presq[skel18indx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        skel18seterr(37,19);
    }
    wwflg = 0;
}

void skel18stab(double velin, double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void skel18getgrav(double *gravout)
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void skel18getmass(int body, double *massout)
{

    if (skel18chkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        skel18seterr(40,15);
        return;
    }
    *massout = mk[body];
}

void skel18getiner(int body, double (*inerout)[3])
{

    if (skel18chkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        skel18seterr(41,15);
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

void skel18getbtj(int joint, double *btjout)
{

    if (skel18chkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void skel18getitj(int joint, double *itjout)
{

    if (skel18chkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void skel18getpin(int joint, int pinno, double *pinout)
{
    int offs;

    if (skel18chkjpin(44,joint,pinno) != 0) {
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

void skel18getpres(int joint, int axis, int *presout)
{

    if (skel18chkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[skel18indx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void skel18getstab(double *velout, double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void skel18info(int *info)
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
    info[11] = 0;
/* info entries from 12-49 are reserved */
}

void skel18jnt(int joint, int *info, int *tran)
{
    int i,offs;

    if (skel18chkjnum(48,joint) != 0) {
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

void skel18cons(int consno, int *info)
{

    if (skel18chkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

int skel18chkbnum(int routine, int bnum)
{

    if ((bnum < -1) || (bnum > 15)) {
        skel18seterr(routine,15);
        return 1;
    }
    return 0;
}

int skel18chkjnum(int routine, int jnum)
{

    if ((jnum < 0) || (jnum > 15)) {
        skel18seterr(routine,16);
        return 1;
    }
    return 0;
}

int skel18chkucnum(int routine, int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        skel18seterr(routine,21);
        return 1;
    }
    return 0;
}

int skel18chkjaxis(int routine, int jnum, int axnum)
{
    int maxax;

    if (skel18chkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        skel18seterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        skel18seterr(routine,18);
        return 1;
    }
    return 0;
}

int skel18chkjpin(int routine, int jnum, int pinno)
{
    int maxax,pinok;

    if (skel18chkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        skel18seterr(routine,17);
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
        skel18seterr(routine,18);
        return 1;
    }
    return 0;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void skel18st2ang(double *st, double *stang)
{
    int i;
    double dc[3][3];

    for (i = 0; i < 37; i++) {
        stang[i] = st[i];
    }
    skel18quat2dc(st[3],st[4],st[5],st[37],dc);
    skel18dc2ang(dc,&stang[3],&stang[4],&stang[5]);
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void skel18ang2st(double *stang, double *st)
{
    int i;
    double dc[3][3];

    for (i = 0; i < 37; i++) {
        st[i] = stang[i];
    }
    skel18ang2dc(stang[3],stang[4],stang[5],dc);
    skel18dc2quat(dc,&st[3],&st[4],&st[5],&st[37]);
}

/* Normalize Euler parameters in state. */

void skel18nrmsterr(double *st, double *normst, int routine)
{
    int i;
    double norm;

    for (i = 0; i < 38; i++) {
        normst[i] = st[i];
    }
    norm = sqrt(st[3]*st[3]+st[4]*st[4]+st[5]*st[5]+st[37]*st[37]);
    if (routine != 0) {
        if ((norm < .9) || (norm > 1.1)) {
            skel18seterr(routine,14);
        }
    }
    if (norm == 0.) {
        normst[37] = 1.;
        norm = 1.;
    }
    norm = 1./norm;
    normst[3] = normst[3]*norm;
    normst[4] = normst[4]*norm;
    normst[5] = normst[5]*norm;
    normst[37] = normst[37]*norm;
}

void skel18normst(double *st, double *normst)
{

    skel18nrmsterr(st,normst,0);
}

void skel18gentime(int *gentm)
{

    *gentm = 143031;
}
/*
Done. CPU seconds used: 38.55  Memory used: 1654784 bytes.
Equation complexity:
  sdstate:  1098 adds  1653 multiplies     1 divides  1337 assignments
  sdderiv: 17565 adds 22313 multiplies    37 divides 17532 assignments
  sdresid:  3765 adds  4709 multiplies     0 divides  2866 assignments
  sdreac:    767 adds   507 multiplies     0 divides   642 assignments
  sdmom:     383 adds   640 multiplies     0 divides    35 assignments
  sdsys:     435 adds   825 multiplies     0 divides    55 assignments
*/
