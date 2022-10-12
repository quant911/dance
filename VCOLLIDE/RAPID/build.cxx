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


#include "RAPID_version.h"

static char rapidtag_data[] = "RAPIDTAG  file: "__FILE__"    date: "__DATE__"    time: "__TIME__;

// to silence the compiler's complaints about unreferenced identifiers.
static void r1(char *f){  r1(f);  r1(rapidtag_data);  r1(rapid_version);}

static double dot(double v1[3], double v2[3]) {
	return(v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

#include "RAPID.h"
#include "matvec.h"
#include "moments.h"
#include "obb.h"
#include <string.h>

#include <GL/gl.h>

box *box::ActiveOBB = NULL; // Used to keep track of which box are we working
			    // with for the least-squares routines.

extern int RAPID_initialized;
void RAPID_initialize();

int
RAPID_model::BeginModel()
{
  int bs = build_state;
  
  if (!RAPID_initialized) RAPID_initialize();
  
  // free whatever storage we had.  Remember, it's okay to delete null
  // pointers in C++, so we don't have to check them first.
  delete [] b;   b = 0;
  num_boxes_alloced = 0;
  delete [] tris;   tris = 0;
  num_tris = 0;
  num_tris_alloced = 0;

  build_state = RAPID_BUILD_STATE_BEGIN;
  
  if (bs == RAPID_BUILD_STATE_CONST) return RAPID_OK;

  if (bs == RAPID_BUILD_STATE_PROCESSED) return RAPID_OK;

  if (bs == RAPID_BUILD_STATE_BEGIN) 
    return RAPID_ERR_BUILD_OUT_OF_SEQUENCE;
  
  if (bs == RAPID_BUILD_STATE_ADDTRI) 
    return RAPID_ERR_BUILD_OUT_OF_SEQUENCE;

  return RAPID_OK;
}

int
RAPID_model::EndModel()
{
  if (!RAPID_initialized) RAPID_initialize();

  if (num_tris == 0)
    {
      return RAPID_ERR_BUILD_EMPTY_MODEL;
    }

  int myrc = build_hierarchy();
  if (myrc == RAPID_OK)
    {
      // only change to processed state if successful.
      build_state = RAPID_BUILD_STATE_PROCESSED;
      return RAPID_OK;
    }
  else return myrc;

}

int
RAPID_model::AddTri(const double *p1, const double *p2, const double *p3, int id)
{
  if (!RAPID_initialized) RAPID_initialize();

  int myrc = RAPID_OK; // we'll return this unless a problem is found

  if (build_state == RAPID_BUILD_STATE_PROCESSED)
    {
      // client forgot to call BeginModel() before calling AddTri().
      return RAPID_ERR_BUILD_OUT_OF_SEQUENCE;
    }
  
  // first make sure that we haven't filled up our allocation.
  // if we have, allocate a new array of twice the size, and copy
  // the old data to it.

  if (num_tris == num_tris_alloced)
    {
      // decide on new size -- accounting for first time, where none are 
      // allocated
      int n = num_tris_alloced*2;
      if (n == 0) n = 1;

      // make new array, and copy the old one to it
      tri *t = new tri[n];

      // if we can't get any more space, return an error
      if (!t)
	{
	  // we are leaving the model unchanged.
	  return RAPID_ERR_MODEL_OUT_OF_MEMORY;
	}
      
      int i;
      for(i=0; i<num_tris; i++) t[i] = tris[i]; 

      // free the old array and reassign.  
      delete [] tris;
      tris = t;
      
      // update the allocation counter.
      num_tris_alloced = n;
    }

  // now copy the new tri into the array
  tris[num_tris].p1[0] = p1[0];
  tris[num_tris].p1[1] = p1[1];
  tris[num_tris].p1[2] = p1[2];
  tris[num_tris].p2[0] = p2[0];
  tris[num_tris].p2[1] = p2[1];
  tris[num_tris].p2[2] = p2[2];
  tris[num_tris].p3[0] = p3[0];
  tris[num_tris].p3[1] = p3[1];
  tris[num_tris].p3[2] = p3[2];
  tris[num_tris].id = id;

  // update the counter
  num_tris++;

  return myrc;
}



// not a full sort -- just makes column 1 the largest
int
eigen_and_sort1(double evecs[3][3], double cov[3][3])
{
  double t;
  double evals[3];
  int n;

  n = Meigen(evecs, evals, cov);
  
  if (evals[2] > evals[0])
    {
      if (evals[2] > evals[1])
	{
	  // 2 is largest, swap with column 0
	  t = evecs[0][2]; 
	  evecs[0][2] = evecs[0][0]; 
	  evecs[0][0] = t;
	  t = evecs[1][2]; 
	  evecs[1][2] = evecs[1][0]; 
	  evecs[1][0] = t;
	  t = evecs[2][2]; 
	  evecs[2][2] = evecs[2][0]; 
	  evecs[2][0] = t;
	}
      else
	{
	  // 1 is largest, swap with column 0
	  t = evecs[0][1]; 
	  evecs[0][1] = evecs[0][0]; 
	  evecs[0][0] = t;
	  t = evecs[1][1]; 
	  evecs[1][1] = evecs[1][0]; 
	  evecs[1][0] = t;
	  t = evecs[2][1]; 
	  evecs[2][1] = evecs[2][0]; 
	  evecs[2][0] = t;
	}
    }
  else
    {
      if (evals[0] > evals[1])
	{
	  // 0 is largest, do nothing
	}
      else
	{
  	  // 1 is largest
	  t = evecs[0][1]; 
	  evecs[0][1] = evecs[0][0]; 
	  evecs[0][0] = t;
	  t = evecs[1][1]; 
	  evecs[1][1] = evecs[1][0]; 
	  evecs[1][0] = t;
	  t = evecs[2][1]; 
	  evecs[2][1] = evecs[2][0]; 
	  evecs[2][0] = t;
	}
    }

  // we are returning the number of iterations Meigen took.
  // too many iterations means our chosen orientation is bad.
  return n; 
}


inline
void
minmax(double &mn, double &mx, double v)
{
  if (v < mn) mn = v;
  else if (v > mx) mx = v;
}


static moment *RAPID_moment = 0;
static tri *RAPID_tri = 0;
static box *RAPID_boxes = 0;
static int RAPID_boxes_inited = 0;


/*

  There are <n> tri structures in an array starting at <t>.
  
  We are told that the mean point is <mp> and the orientation
  for the parent box will be <or>.  The split axis is to be the 
  vector given by <ax>.

  <or>, <ax>, and <mp> are model space coordinates.

*/



int
RAPID_model::build_hierarchy()
{
  // allocate the boxes and set the box list globals

  num_boxes_alloced = num_tris * 2;
  b = new box[num_boxes_alloced];
  if (b == 0) return RAPID_ERR_MODEL_OUT_OF_MEMORY;
  RAPID_boxes = b;
  RAPID_boxes_inited = 1;   // we are in process of initializing b[0].
  
  // Determine initial orientation, mean point, and splitting axis.

  int i; 
  accum M;
  
  double C[3][3];
  
  RAPID_moment = new moment[num_tris]; 
  if (RAPID_moment == 0)
    {
      delete [] b;
      return RAPID_ERR_MODEL_OUT_OF_MEMORY;
    }
  compute_moments(RAPID_moment, tris, num_tris);

  clear_accum(M);  
  for(i=0; i<num_tris; i++)
    accum_moment(M, RAPID_moment[i]);
  
  mean_from_accum(b[0].pT, M);
  covariance_from_accum(C, M);
  
  eigen_and_sort1(b[0].pR, C);

  // create the index list
  int *t = new int[num_tris];
  if (t == 0)
    {
      delete [] b;
      delete [] RAPID_moment;
      return RAPID_ERR_MODEL_OUT_OF_MEMORY;
    }
  for(i=0; i<num_tris; i++) t[i] = i;

  // set the tri pointer
  RAPID_tri = tris;
  
  // do the build
  int rc = b[0].split_recurse(t, num_tris);
  if (rc != RAPID_OK)
    {
      delete [] b;
      delete [] RAPID_moment;
      delete [] t;
      return RAPID_ERR_MODEL_OUT_OF_MEMORY;
    }
  
  // free the moment list
  delete [] RAPID_moment;  RAPID_moment = 0;

  // null the tri pointer
  RAPID_tri = 0;
  
  // free the index list
  delete [] t;

  return RAPID_OK;
}



inline
void
reaccum_moments(accum &A, int *t, int n)
{
  clear_accum(A);
  for(int i=0; i<n; i++)
      accum_moment(A, RAPID_moment[t[i]]);
}

box::box() {
	m_LocalPoint[0] = m_LocalPoint[1] = m_LocalPoint[2] = 0.0;
	trp = NULL;
}

// Returns the lower bound on the minimum distance between
// the point and the box.
// point is in the box's frame of reference.
//
// Returns the squared distance (to avoid square root)
//
double box::GetLowerBoundMin(double point[3])
{
	return(GetDistanceToBox(point));
}

// Returns upper bound distance on point.
// Point is given in link-frame coordinates.
//
double box::GetUpperBoundMin(double point[3])
{
	memcpy(m_TestPointWorld,point,3*sizeof(double));

	double result = 0.0;
	double diff;
	for (int i = 0; i < 3; i++) {
	        diff = point[i]-pointInBox[i];
			result += diff*diff;
	}
	return(result);
}

int
box::split_recurse(int *t, int n)
{
  // The orientation for the parent box is already assigned to this->pR.
  // The axis along which to split will be column 0 of this->pR.
  // The mean point is passed in on this->pT.

  // When this routine completes, the position and orientation in model
  // space will be established, as well as its dimensions.  Child boxes
  // will be constructed and placed in the parent's CS.

  if (n == 1)
      return split_recurse(t);
    
  
  // walk along the tris for the box, and do the following:
  //   1. collect the max and min of the vertices along the axes of <or>.
  //   2. decide which group the triangle goes in, performing appropriate swap.
  //   3. accumulate the mean point and covariance data for that triangle.

  accum M1, M2;
  double C[3][3];
  double c[3];
  double minval[3], maxval[3];

  int rc;   // for return code on procedure calls.
  int in;
  tri *ptr;
  int i;
  double axdmp;
  int n1 = 0;  // The number of tris in group 1.  
  // Group 2 will have n - n1 tris.

  // project approximate mean point onto splitting axis, and get coord.
  axdmp = (pR[0][0] * pT[0] + pR[1][0] * pT[1] + pR[2][0] * pT[2]);

  clear_accum(M1);
  clear_accum(M2);

  MTxV(c, pR, RAPID_tri[t[0]].p1);
  minval[0] = maxval[0] = c[0];
  minval[1] = maxval[1] = c[1];
  minval[2] = maxval[2] = c[2];


  for(i=0; i<n; i++)
    {
      in = t[i];
      ptr = RAPID_tri + in;
    
	  
	  if (i == 0) // Grab a point that resides in this bounding box to compute
				  // an upper bound on the minimum distance for proximity checks.
		memcpy(pointInBox,ptr->p1,3*sizeof(double)); 
      
      MTxV(c, pR, ptr->p1);
      minmax(minval[0], maxval[0], c[0]);
      minmax(minval[1], maxval[1], c[1]);
	  minmax(minval[2], maxval[2], c[2]);
    

      MTxV(c, pR, ptr->p2);
      minmax(minval[0], maxval[0], c[0]);
      minmax(minval[1], maxval[1], c[1]);
      minmax(minval[2], maxval[2], c[2]);

      MTxV(c, pR, ptr->p3);
      minmax(minval[0], maxval[0], c[0]);
      minmax(minval[1], maxval[1], c[1]);
      minmax(minval[2], maxval[2], c[2]);

      // grab the mean point of the in'th triangle, project
      // it onto the splitting axis (1st column of pR) and
      // see where it lies with respect to axdmp.
      mean_from_moment(c, RAPID_moment[in]);

      if (((pR[0][0]*c[0] + pR[1][0]*c[1] + pR[2][0]*c[2]) < axdmp)
	  && ((n!=2)) || ((n==2) && (i==0)))    
	{
	  // accumulate first and second order moments for group 1
	  accum_moment(M1, RAPID_moment[in]);

	  // put it in group 1 by swapping t[i] with t[n1]
	  int temp = t[i];
	  t[i] = t[n1];
	  t[n1] = temp;
	  n1++;
	}
      else
	{
	  // accumulate first and second order moments for group 2
	  accum_moment(M2, RAPID_moment[in]);

	  // leave it in group 2
	  // do nothing...it happens by default
	}
    }

  // done using this->pT as a mean point.


  // error check!
  if ((n1 == 0) || (n1 == n))
    {
      // our partitioning has failed: all the triangles fell into just
      // one of the groups.  So, we arbitrarily partition them into
      // equal parts, and proceed.

      n1 = n/2;
      
      // now recompute accumulated stuff
      reaccum_moments(M1, t, n1);
      reaccum_moments(M2, t + n1, n - n1);
    }

  // With the max and min data, determine the center point and dimensions
  // of the parent box.

  c[0] = (minval[0] + maxval[0])*0.5;
  c[1] = (minval[1] + maxval[1])*0.5;
  c[2] = (minval[2] + maxval[2])*0.5;
  
  pT[0] = c[0] * pR[0][0] + c[1] * pR[0][1] + c[2] * pR[0][2];
  pT[1] = c[0] * pR[1][0] + c[1] * pR[1][1] + c[2] * pR[1][2];
  pT[2] = c[0] * pR[2][0] + c[1] * pR[2][1] + c[2] * pR[2][2];
  d[0] = (maxval[0] - minval[0])*0.5;
  d[1] = (maxval[1] - minval[1])*0.5;
  d[2] = (maxval[2] - minval[2])*0.5;

  // allocate new boxes
  P = RAPID_boxes + RAPID_boxes_inited++;
  N = RAPID_boxes + RAPID_boxes_inited++;

  // Compute the orienations for the child boxes (eigenvectors of
  // covariance matrix).  Select the direction of maximum spread to be
  // the split axis for each child.
  
  double tR[3][3];
  
  if (n1 > 1)
    {
      mean_from_accum(P->pT, M1);
      covariance_from_accum(C, M1);

      if (eigen_and_sort1(tR, C) > 30)
	{
	  // unable to find an orientation.  We'll just pick identity.
	  Midentity(tR);
	}

      McM(P->pR, tR);
      if ((rc = P->split_recurse(t, n1)) != RAPID_OK) return rc;
    }
  else
    {
      if ((rc = P->split_recurse(t)) != RAPID_OK) return rc;
    }
  McM(C, P->pR);  MTxM(P->pR, pR, C);   // and F1
  VmV(c, P->pT, pT);  MTxV(P->pT, pR, c);
  
  if ((n-n1) > 1)
    {      
      mean_from_accum(N->pT, M2);
      covariance_from_accum (C, M2);

      if (eigen_and_sort1(tR, C) > 30)
	{
	  // unable to find an orientation.  We'll just pick identity.
	  Midentity(tR);
	}
      
      McM(N->pR, tR);
      if ((rc = N->split_recurse(t + n1, n - n1)) != RAPID_OK) return rc;
    }
  else
    {
      if ((rc = N->split_recurse(t+n1)) != RAPID_OK) return rc;
    }
  McM(C, N->pR); MTxM(N->pR, pR, C);
  VmV(c, N->pT, pT);  MTxV(N->pT, pR, c);  

  return RAPID_OK;
}

int
box::split_recurse(int *t)
{
  // For a single triangle, orientation is easily determined.
  // The major axis is parallel to the longest edge.
  // The minor axis is normal to the triangle.
  // The in-between axis is determine by these two.

  // this->pR, this->d, and this->pT are set herein.

  P = N = 0;
  tri *ptr = RAPID_tri + t[0];

  // Find the major axis: parallel to the longest edge.
  double u12[3], u23[3], u31[3];

  // First compute the squared-lengths of each edge
  VmV(u12, ptr->p1, ptr->p2);  
  double d12 = VdotV(u12,u12);
  VmV(u23, ptr->p2, ptr->p3);  
  double d23 = VdotV(u23,u23);
  VmV(u31, ptr->p3, ptr->p1);  
  double d31 = VdotV(u31,u31);

  // Find the edge of longest squared-length, normalize it to
  // unit length, and put result into a0.
  double a0[3];
  double l;  
  if (d12 > d23)
    {
      if (d12 > d31)
	{
	  l = 1.0 / sqrt(d12); 
	  a0[0] = u12[0] * l; 
	  a0[1] = u12[1] * l;
	  a0[2] = u12[2] * l;
	}
      else 
	{
	  l = 1.0 / sqrt(d31);
	  a0[0] = u31[0] * l;
	  a0[1] = u31[1] * l;
	  a0[2] = u31[2] * l;
	}
    }
  else 
    {
      if (d23 > d31)
	{
	  l = 1.0 / sqrt(d23);
	  a0[0] = u23[0] * l;
	  a0[1] = u23[1] * l;
	  a0[2] = u23[2] * l;
	}
      else
	{
	  l = 1.0 / sqrt(d31);
	  a0[0] = u31[0] * l;
	  a0[1] = u31[1] * l;
	  a0[2] = u31[2] * l;
	}
    }

  // Now compute unit normal to triangle, and put into a2.
  double a2[3];
  VcrossV(a2, u12, u23);
  l = 1.0 / Vlength(a2);  a2[0] *= l;  a2[1] *= l;  a2[2] *= l;

  // a1 is a2 cross a0.
  double a1[3];
  VcrossV(a1, a2, a0);

  // Now make the columns of this->pR the vectors a0, a1, and a2.
  pR[0][0] = a0[0];  pR[0][1] = a1[0];  pR[0][2] = a2[0];
  pR[1][0] = a0[1];  pR[1][1] = a1[1];  pR[1][2] = a2[1];
  pR[2][0] = a0[2];  pR[2][1] = a1[2];  pR[2][2] = a2[2];
  
  // Now compute the maximum and minimum extents of each vertex 
  // along each of the box axes.  From this we will compute the 
  // box center and box dimensions.
  double minval[3], maxval[3];
  double c[3];
  
  MTxV(c, pR, ptr->p1);
  minval[0] = maxval[0] = c[0];
  minval[1] = maxval[1] = c[1];
  minval[2] = maxval[2] = c[2];

  MTxV(c, pR, ptr->p2);
  minmax(minval[0], maxval[0], c[0]);
  minmax(minval[1], maxval[1], c[1]);
  minmax(minval[2], maxval[2], c[2]);
  
  MTxV(c, pR, ptr->p3);
  minmax(minval[0], maxval[0], c[0]);
  minmax(minval[1], maxval[1], c[1]);
  minmax(minval[2], maxval[2], c[2]);
  
  // With the max and min data, determine the center point and dimensions
  // of the box
  c[0] = (minval[0] + maxval[0])*0.5;
  c[1] = (minval[1] + maxval[1])*0.5;
  c[2] = (minval[2] + maxval[2])*0.5;

  pT[0] = c[0] * pR[0][0] + c[1] * pR[0][1] + c[2] * pR[0][2];
  pT[1] = c[0] * pR[1][0] + c[1] * pR[1][1] + c[2] * pR[1][2];
  pT[2] = c[0] * pR[2][0] + c[1] * pR[2][1] + c[2] * pR[2][2];

  d[0] = (maxval[0] - minval[0])*0.5;
  d[1] = (maxval[1] - minval[1])*0.5;
  d[2] = (maxval[2] - minval[2])*0.5;
  
  // Assign the one triangle to this box
  trp = ptr;

  return RAPID_OK;
}

void box::displayPointInBox(int levels)
{
	if (levels == 0) return;

	if (leaf()) return;
	
	glColor3b(255-50*levels,50*levels,0);

	glBegin(GL_LINES);
	glVertex3dv(pointInBox);
	glVertex3dv(m_TestPointWorld);
	glEnd();
	
	
	levels--;
	if (P) P->displayPointInBox(levels);
	if (N) N->displayPointInBox(levels);
	
}

// Displays the bounding box relative to parent.
void box::display(int levels)
{
	// Return early when maximum levels reached.
	if (levels == 0) return;

	// If this is a leaf node, do not draw the box for it.
	if (leaf()) 
		return;
	
	// Draw this box.
	glPushMatrix();
	glTranslated(pT[0],pT[1],pT[2]);

	// Convert rotation matrix to OpenGL rotation matrix.
	double rmat[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (i == 3 || j == 3)
				rmat[j*4+i] = 0.0;
			else
				rmat[j*4+i] = pR[i][j];
		}
	rmat[15] = 1.0;

	glMultMatrixd(rmat);
	glColor3b(255-50*levels,50*levels,0);

	// Display closest point found.
	/* Uncomment if want to display distances.
	glRasterPos3dv(m_LocalPoint);
	double dist = pow(m_LocalPoint[0] - m_TestPoint[0],2.0)
				+ pow(m_LocalPoint[1] - m_TestPoint[1],2.0)
				+ pow(m_LocalPoint[2] - m_TestPoint[2],2.0);
	char label[256];
	sprintf(label,"%f",dist);
	GLlabel(label);

	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex3dv(m_LocalPoint);
	glVertex3dv(m_TestPoint);
	glEnd();
	glLineWidth(1.0);
	*/

	glBegin(GL_LINES);
	glVertex3d(d[0],d[1],d[2]);
	glVertex3d(-d[0],d[1],d[2]);
	glVertex3d(d[0],-d[1],d[2]);
	glVertex3d(-d[0],-d[1],d[2]);
	glVertex3d(d[0],d[1],-d[2]);
	glVertex3d(-d[0],d[1],-d[2]);
	glVertex3d(d[0],-d[1],-d[2]);
	glVertex3d(-d[0],-d[1],-d[2]);

	glVertex3d(d[0],d[1],d[2]);
	glVertex3d(d[0],-d[1],d[2]);
	glVertex3d(-d[0],d[1],d[2]);
	glVertex3d(-d[0],-d[1],d[2]);
	glVertex3d(d[0],d[1],-d[2]);
	glVertex3d(d[0],-d[1],-d[2]);
	glVertex3d(-d[0],d[1],-d[2]);
	glVertex3d(-d[0],-d[1],-d[2]);

	glVertex3d(d[0],d[1],d[2]);
	glVertex3d(d[0],d[1],-d[2]);
	glVertex3d(-d[0],d[1],d[2]);
	glVertex3d(-d[0],d[1],-d[2]);
	glVertex3d(d[0],-d[1],d[2]);
	glVertex3d(d[0],-d[1],-d[2]);
	glVertex3d(-d[0],-d[1],d[2]);
	glVertex3d(-d[0],-d[1],-d[2]);
	glEnd();

	levels--;
	if (P)
		P->display(levels);
	if (N)
		N->display(levels);

	glPopMatrix();
	
}

// GetDistanceToBox:
//	Assumes point is in the OBB frame of reference.
//	Saves point to m_TestPoint for visualization tracking.
//	Saves closest point in m_LocalPoint
//
double box::GetDistanceToBox(double point[])
{
	memcpy(m_TestPoint,point,3*sizeof(double));
	ActiveOBB = this;

 	integer m = 3;
	integer n = 3;
      
   
    integer ldfjac = 3; // leading dimension of fjac
    integer info = -1;
    static integer ipvt[3];

	// Set bounds of search.
	static doublereal lb[3] = {-1.0,-1.0,-1.0}, ub[3] = {1.0, 1.0, 1.0};

	// Set initial guess.
	static doublereal x[3];
	x[0] = 0.0; x[1] = 0.0; x[2] = 0.0;

	static doublereal fvec[3]; // Stores function values.
	static doublereal fjac[9]; // Stores Jacobian matrix.

	// Tolerances.
        doublereal ftol = 0.001, xtol = 0.001, gtol = 0.001;
        integer maxfev = 100;

	// Used by the routines.
        doublereal *diag = new doublereal[3];
        doublereal *qtf = new doublereal[3];
        integer mode = 1; // Internally scale variables.

      	doublereal factor = 100.0; // Default 100.0, to determine initial step bound.
        integer nprint = 0; // Control printing of iterates.
        integer nfev, njev;
         
        // Work arrays
        doublereal *wa1 = new doublereal[n];
        doublereal *wa2 = new doublereal[n];
        doublereal *wa3 = new doublereal[n];
        doublereal *wa4 = new doublereal[m];
        lmderBound_((S_fp)EvalLeastSquaresBox, &m, &n, x, fvec, fjac, 
	        &ldfjac, &ftol, &xtol, &gtol, &maxfev, diag, &mode, 
		&factor, &nprint, &info, &nfev, &njev, ipvt, qtf,lb,ub,
                wa1, wa2, wa3, wa4);
        delete [] diag;
        delete [] qtf;
        delete [] wa1;
        delete [] wa2;
        delete [] wa3;
        delete [] wa4;

	/* Uncomment if wish to see result codes of search
	switch(info) {
		case 0:
		fprintf(stderr,"Improper input parameters\n");
		break;
		case 1:
		fprintf(stderr,"Both actual and predicted relative reductions in\n",
			"the sum of squares are at most ftol.\n");
		break;
		case 2:
		fprintf(stderr,"Relative error between two consecutive iterates\n",
			"is at most xtol.\n");
		break;
		case 3:
		fprintf(stderr,"Conditions for 1 and 2 both hold.\n");
		break;
		case 4:
		fprintf(stderr,"Cosine of angle between fvec and any column\n",
			"of the jacobian is at most gtol in absolute value.\n");
		break;
		case 5:
		fprintf(stderr,"Number of calls to fcn with iflag = 1 has\n",
			"reached maxfev.\n");
		break;
		case 6:
		fprintf(stderr,"Ftol is too small. No further reduction in\n",
			"the sum of squares is possible.\n");
		break;
	}
	*/

	// Do not include the origin as this point is relative to the
	// origin.
	double result = 0.0;
	for (int i=0; i < 3; i++) {
		m_LocalPoint[i] = x[i]*d[i];
		result += fvec[i]*fvec[i];
	}
	return(result);
}

// GetDistanceToTri:
//	point is in outermost frame of reference 
//
double box::GetDistanceToTri(double point[], double closest[])
{
	
	// Use David Eberly's algorithm for the shortest
	// point to a triangle.

	// Ok, now compute a some values.
	// e0 is vector from p1 to p2, e1 is vector from p1 to p3
	// diff is vector difference between p1 and point
	double e0[3] , e1[3], diff[3];
	int i;
	for (i = 0; i < 3; i++) {
		e0[i] = trp->p2[i] - trp->p1[i];
		e1[i] = trp->p3[i] - trp->p1[i];
		diff[i] = trp->p1[i] - point[i];
	}

	double a = dot(e0,e0);
	double b = dot(e0,e1);
	double c = dot(e1,e1);
	double d = dot(e0,diff);
	double e = dot(e1,diff);
	double f = dot(diff,diff);

	// Determinant which classifies quadratic
	// A*C-B*B = |Cross(e0,e1)|^2 >= 0
    	// A-2*B+C = Dot(e0,e0)-2*Dot(e0,e1)+Dot(e1,e1) = |e0-e1|^2 > 0
	// Although this should be positive given we have a valid cross product, in reality,
	// it is possible for small edge lengths that floating point round-off errors lead to
	// a small negative quantity. Hence, take the abs value.
	double det = fabs(a*c-b*b); 

	// Finds projection of point onto plane of triangle.
	// Solves for s,t: where plane is pt1 + s (pt2 - pt1) + t (pt3 - pt1)

	// The actual solution must divide by det for s and t, but to avoid 
	// unnecessary divisions, all future comparisons are scaled by det so
	// division is only done once we find the solution.
	// IE., we search in the domain s = [0,det], t = [0,det], with s+t <= det
	double s = b*e - c*d;
	double t = b*d - a*e;

	// Regions:
	//            t
	//      \     |
	//	     \  2 |
	//        \   |
	//         \  |
	//          \ |   
	//        3  \|
	//            |\     1
	//            | \
	//            |  \
	//            | 0 \
	//   _________|____\__________ s
	//	      |     \
	//        4   |  5   \    6
	//            |       \


	double result = 0.0;
    	if ( s+t <= det )
    	{
        	if ( s < 0 )
        	{
            		if ( t < 0 )  // region 4
            		{
                		if ( d < 0 )
                		{
                    			t = 0;
                    			if ( -d >= a )
                    			{
                        			s = 1;
                        			result = a+2*d+f;
                    			}
                    			else
                    			{
                        			s = -d/a;
                        			result = d*s+f;
                    			}
                		}
                		else
                		{
                    			s = 0;
                    			if ( e >= 0 )
                    			{
                        			t = 0;
                        			result = f;
                    			}
                    			else if ( -e >= c )
                    			{
                        			t = 1;
                        			result = c+2*e+f;
                    			}
                    			else
                    			{
                        			t = -e/c;
                        			result = e*t+f;
                    			}
                		}
            		}
            		else  // region 3
            		{
                		s = 0;
                		if ( e >= 0 )
                		{
                    			t = 0;
                    			result = f;
                		}
                		else if ( -e >= c )
                		{
                    			t = 1;
                    			result = c+2*e+f;
                		}
                		else
                		{
                    			t = -e/c;
                    			result = e*t+f;
                		}
            		}
        	}
        	else if ( t < 0 )  // region 5
        	{
            		t = 0;
            		if ( d >= 0 )
            		{
                		s = 0;
                		result=f;
            		}
            		else if ( -d >= a )
            		{
                		s = 1;
                		result = a+2*d+f;
            		}
            		else
            		{
                		s = -d/a;
                		result = d*s+f;
            		}
        	}
        	else  // region 0
        	{
            		// minimum at interior point
            		double invDet = 1.0f/det;
            		s *= invDet;
            		t *= invDet;
            		result = s*(a*s+b*t+2*d)+t*(b*s+c*t+2*e)+f;
        	}
    	}
    	else
    	{
        	double tmp0, tmp1, numer, denom;

	        if ( s < 0 )  // region 2
        	{
            		tmp0 = b+d;
            		tmp1 = c+e;
            		if ( tmp1 > tmp0 )
            		{
                		numer = tmp1 - tmp0;
                		denom = a-2*b+c;
                		if ( numer >= denom )
                		{
                    			s = 1;
                    			t = 0;
                    			result = a+2*d+f;
                		}
                		else
                		{
                    			s = numer/denom;
                    			t = 1-s;
                    			result = s*(a*s+b*t+2*d)+t*(b*s+c*t+2*e)+f;
                		}
            		}
            		else
            		{
                		s = 0;
                		if ( tmp1 <= 0 )
                		{
                    			t = 1;
                    			result = c+2*e+f;
                		}
                		else if ( e >= 0 )
                		{
                    			t = 0;
                    			result = f;
                		}
                		else
                		{
                    			t = -e/c;
                    			result = e*t+f;
                		}
            		}
        	}
        	else if ( t < 0 )  // region 6
        	{
            		tmp0 = b+e;
            		tmp1 = a+d;
            		if ( tmp1 > tmp0 )
            		{
                		numer = tmp1 - tmp0;
                		denom = a-2*b+c;
                		if ( numer >= denom)
                		{
                    			t = 1;
                    			s = 0;
                    			result = c+2*e+f;
                		}
                		else
                		{
                    			t = numer/denom;
                    			s = 1-t;
                    			result = s*(a*s+b*t+2*d)+t*(b*s+c*t+2*e)+f;
                		}
            		}
            		else
            		{
                		t = 0;
                		if ( tmp1 <= 0 )
                		{
                    			s = 1;
                    			result = a+2*d+f;
                		}
                		else if ( d >= 0 )
                		{
                    			s = 0;
                    			result = f;
                		}
                		else
                		{
                    			s = -d/a;
                    			result = d*s+f;
                		}
            		}
        	}
        	else  // region 1
        	{
            		numer = c+e-b-d;
            		if ( numer <= 0 )
            		{
                		s = 0;
                		t = 1;
                		result = c+2*e+f;
            		}
            		else
            		{
                		denom = a-2*b+c;
                		if ( numer >= denom )
                		{
                    			s = 1;
                    			t = 0;
                    			result = a+2*d+f;
                		}
                		else
                		{
                    			s = numer/denom;
                    			t = 1-s;
                    			result = s*(a*s+b*t+2*d)+t*(b*s+c*t+2*e)+f;
                		}
            		}
        	}
    	}

	
	for (i = 0; i < 3; i++) 
		closest[i] = trp->p1[i] + e0[i]*s + e1[i]*t; 

	return(result);
}

// EvalLeastSquares:
//
//	   x: vector of size n unknowns
//	fvec: vector of size m unknowns
//    ldfjac: leading dimension of jacobian
//	fjac: matrix of size ldfjac and n
//     iflag: 1 for fvec of x (do not alter fjac)
//	      2 for fjac at x (do not alter fvec)
//
int box::EvalLeastSquaresBox(integer *m, integer *n, doublereal *x,
           doublereal *fvec, doublereal *fjac, integer *ldfjac,
           integer *iflag)
{
	if (*iflag == 1) 
		ActiveOBB->EvalFvecBox(x,fvec);
	else if (*iflag == 2)
		ActiveOBB->EvalFjacBox(x,fjac);
	return(0);
}

// EvalFvec:
//
void box::EvalFvecBox(doublereal *x, doublereal *fvec)
{
	// Subtract point from computed box point.
	// Note: pT not needed as m_TestPoint is relative to 
	// pT as origin.
	for (int i = 0; i < 3; i++) 
		fvec[i] = x[i]*d[i] - m_TestPoint[i];
} 

// EvalFjac
//	Note: fjac is an mxn matrix, but in column major order
//
void box::EvalFjacBox(doublereal *x, doublereal *fjac)
{
	// Jacobian is constant.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (i == j) 
			   fjac[j*3+i] = d[i];
			else
			   fjac[j*3+i] = 0.0;
		}
}

// GetLocalCoords:
//	Transforms point in outer frame to local OBB frame.
void box::GetLocalCoords(double local[], double point[])
{
	// Convert point to local frame of reference of link.
	// Get local vector direction in world space.
	double opoint[3];
	for (int i = 0; i < 3; i++)
		opoint[i] = point[i] - pT[i];
	// Transform this to the local frame.
	for (int col = 0; col < 3; col++) 
		local[col] = opoint[0]*pR[0][col]
			+ opoint[1]*pR[1][col]
			+ opoint[2]*pR[2][col];
}

// displayTriangles:
//	Displays triangles inside a given OBB.
void box::displayTriangles()
{
	if (leaf()) {
	
		glBegin(GL_TRIANGLES);
		glVertex3dv(trp->p1);
		glVertex3dv(trp->p2);
		glVertex3dv(trp->p3);
		glEnd();
		
		return;
	}


	if (P)
		P->displayTriangles();
	if (N)
		N->displayTriangles();

}

// ProjectsInTriangle:
//	Returns 1 if projects in triangle, else 0
int  box::ProjectsInTriangle(double local[3]) 
{
        // Use David Eberly's algorithm for the shortest
        // point to a triangle.

        // Ok, now compute a some values.
        // e0 is vector from p1 to p2, e1 is vector from p1 to p3
        // diff is vector difference between p1 and point
        double e0[3] , e1[3], diff[3];
        int i;
        for (i = 0; i < 3; i++) {
                e0[i] = trp->p2[i] - trp->p1[i];
                e1[i] = trp->p3[i] - trp->p1[i];
                diff[i] = trp->p1[i] - local[i];
        }

        double a = dot(e0,e0);
        double b = dot(e0,e1);
        double c = dot(e1,e1);
        double d = dot(e0,diff);
        double e = dot(e1,diff);
        double f = dot(diff,diff);

        // Determinant which classifies quadratic
        // A*C-B*B = |Cross(e0,e1)|^2 >= 0
        // A-2*B+C = Dot(e0,e0)-2*Dot(e0,e1)+Dot(e1,e1) = |e0-e1|^2 > 0
        // Although this should be positive given we have a valid cross product, in reality,
        // it is possible for small edge lengths that floating point round-off errors lead to
        // a small negative quantity. Hence, take the abs value.
        double det = fabs(a*c-b*b);

        // Finds projection of point onto plane of triangle.
        // Solves for s,t: where plane is pt1 + s (pt2 - pt1) + t (pt3 - pt1)

        // The actual solution must divide by det for s and t, but to avoid
        // unnecessary divisions, all future comparisons are scaled by det so
        // division is only done once we find the solution.
        // IE., we search in the domain s = [0,det], t = [0,det], with s+t <= det
        double s = b*e - c*d;
        double t = b*d - a*e;

	if (s + t <= det && s >= 0 && t >= 0)
		return 1;

	return 0;
}

