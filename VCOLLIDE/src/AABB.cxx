/************************************************************************\

  Copyright 1997 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL
  HILL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL,
  INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
  ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
  EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
  BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION
  TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.


   --------------------------------- 
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   geom@cs.unc.edu               |
  |                                 |
   ---------------------------------
  
     
  The authors may be contacted via:

  US Mail:  A. Pattekar/J. Cohen/T. Hudson/S. Gottschalk/M. Lin/D. Manocha
            Department of Computer Science
            Sitterson Hall, CB #3175
            University of N. Carolina
            Chapel Hill, NC 27599-3175
	    
  Phone:    (919)962-1749
	    
  EMail:    geom@cs.unc.edu

\************************************************************************/


/************************************************************************\
Filename: AABB.CXX
--
Description: This file defines the class AABB, which is used to
             store information about an axis aligned bounding
             box.

\************************************************************************/

#include "AABB.h"
#include "EndPoint.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

void AABB::Display(void)
{
	double *minPt = lo->val;
	double *maxPt = hi->val;

	glPushMatrix();
	glBegin(GL_LINES);

	glVertex3d(minPt[0],minPt[1],minPt[2]);
	glVertex3d(maxPt[0],minPt[1],minPt[2]);
	glVertex3d(minPt[0],minPt[1],maxPt[2]);
	glVertex3d(maxPt[0],minPt[1],maxPt[2]);
	glVertex3d(minPt[0],maxPt[1],minPt[2]);
	glVertex3d(maxPt[0],maxPt[1],minPt[2]);
	glVertex3d(minPt[0],maxPt[1],maxPt[2]);
	glVertex3d(maxPt[0],maxPt[1],maxPt[2]);
	///////////////////////////////////////
	glVertex3d(minPt[0],minPt[1],minPt[2]);
	glVertex3d(minPt[0],maxPt[1],minPt[2]);
	glVertex3d(minPt[0],minPt[1],maxPt[2]);
	glVertex3d(minPt[0],maxPt[1],maxPt[2]);
	glVertex3d(maxPt[0],minPt[1],minPt[2]);
	glVertex3d(maxPt[0],maxPt[1],minPt[2]);
	glVertex3d(maxPt[0],minPt[1],maxPt[2]);
	glVertex3d(maxPt[0],maxPt[1],maxPt[2]);
	///////////////////////////////////////
	glVertex3d(minPt[0],minPt[1],minPt[2]);
	glVertex3d(minPt[0],minPt[1],maxPt[2]);
	glVertex3d(minPt[0],maxPt[1],minPt[2]);
	glVertex3d(minPt[0],maxPt[1],maxPt[2]);
	glVertex3d(maxPt[0],minPt[1],minPt[2]);
	glVertex3d(maxPt[0],minPt[1],maxPt[2]);
	glVertex3d(maxPt[0],maxPt[1],minPt[2]);
	glVertex3d(maxPt[0],maxPt[1],maxPt[2]);
	glEnd();
	glPopMatrix();
}
