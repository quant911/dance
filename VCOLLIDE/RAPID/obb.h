
/*************************************************************************\

  Copyright 1995 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             S. Gottschalk
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {gottscha}@cs.unc.edu


\**************************************************************************/

#ifndef OBB_H
#define OBB_H

//
// This routine is used to solve the least-squares problems of closest point to
// a bounding box or triangle.
//
#ifdef WIN32
#include <windows.h>
#endif
#include <math.h>
#include "f2c.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int lmderBound_(S_fp fcn, integer *m, integer *n, doublereal *x,
        doublereal *fvec, doublereal *fjac, integer *ldfjac, doublereal *ftol,
         doublereal *xtol, doublereal *gtol, integer *maxfev, doublereal *
        diag, integer *mode, doublereal *factor, integer *nprint, integer *
        info, integer *nfev, integer *njev, integer *ipvt, doublereal *qtf,
        doublereal *lb, doublereal *ub,
        doublereal *wa1, doublereal *wa2, doublereal *wa3, doublereal *wa4);

#ifdef __cplusplus
}
#endif
//
// End of numerical stuff
//

class tri
{
public:
  int id;
  double p1[3], p2[3], p3[3];
};


class box
{
public:
	void displayTriangles(void);
	void displayPointInBox(int levels);
	void GetLocalCoords(double local[3], double point[3]);

  // placement in parent's space
  // box to parent space: x_m = pR*x_b + pT
  // parent to box space: x_b = pR.T()*(x_m - pT)
  double pR[3][3];
  double pT[3];
  
  // dimensions
  double d[3];        // this is "radius", that is, 
                      // half the measure of a side length

  double pointInBox[3]; // point in box in outermost frame coords.

  box *P;  // points to but does not "own".  
  box *N;

  tri *trp;
 
  box();
  void display(int levels);
  inline int leaf() { return (!P && !N); } 
  inline double size() { return d[0]; } 

  int split_recurse(int *t, int n);
  int split_recurse(int *t);               // specialized for leaf nodes

  // All distances are squared to avoid sqrt computation
  double GetLowerBoundMin(double point[3]);
  double GetUpperBoundMin(double point[3]);
  double GetDistanceToTri(double point[3], double closest[3]);

  int  ProjectsInTriangle(double local[3]);

private:
  
  static box *ActiveOBB;
  double m_TestPoint[3];
  double m_TestPointWorld[3];
  double m_LocalPoint[3];
 
  double GetDistanceToBox(double point[3]);
  void EvalFvecBox(doublereal *x, doublereal *fvec);
  void EvalFjacBox(doublereal *x, doublereal *fjac);
  static int EvalLeastSquaresBox(integer *m, integer *n, doublereal *x,
                doublereal *fvec, doublereal *fjac, integer *ldfjac,
                integer *iflag);

};

const int RAPID_BUILD_STATE_CONST = 0;     // "empty" state, after constructor
const int RAPID_BUILD_STATE_BEGIN = 1;     // after BeginModel()
const int RAPID_BUILD_STATE_ADDTRI = 2;    // after AddTri()
const int RAPID_BUILD_STATE_PROCESSED = 3; // after EndModel()

#endif
