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



#include "BoundingBox.h"
#include <math.h>

#define	min(x,y) (((x) < (y)) ?	(x) : (y))
#define	max(x,y) (((x) > (y)) ?	(x) : (y))


BoundingBox::BoundingBox()
{
	xMin = 0.0; yMin = 0.0;	zMin = 0.0;
	xMax = 0.0; yMax = 0.0;	zMax = 0.0;
}

BoundingBox *BoundingBox::merge(BoundingBox *b1, BoundingBox *b2)
{
  // Special case if merging with an empty box.
  if (b1->xMin-b1->xMax	== 0.0
   && b1->yMin-b1->yMax	== 0.0
   && b1->zMin-b1->zMax	== 0.0)	{
     b1->xMin =	b2->xMin;
     b1->yMin =	b2->yMin;
     b1->zMin =	b2->zMin;
     b1->xMax =	b2->xMax;
     b1->yMax =	b2->yMax;
     b1->zMax =	b2->zMax;

  }
  else {
     b1->xMin =	min(b1->xMin, b2->xMin)	;
     b1->xMax =	max(b1->xMax, b2->xMax)	;
     b1->yMin =	min(b1->yMin, b2->yMin)	;
     b1->yMax =	max(b1->yMax, b2->yMax)	;
     b1->zMin =	min(b1->zMin, b2->zMin)	;
     b1->zMax =	max(b1->zMax, b2->zMax)	;
  }

  return b1 ;
}


void  BoundingBox::copy(BoundingBox *b)
{
    xMin = b->xMin ;
    xMax = b->xMax ;
    yMin = b->yMin ;
    yMax = b->yMax ;
    zMin = b->zMin ;
    zMax = b->zMax ;
}

void   BoundingBox::display(float r, float g, float b, float a)
{
    glColor4f(r,g,b,a);
    glBegin(GL_LINES);
	glVertex3d(xMin,yMin,zMin);
	glVertex3d(xMin,yMin,zMax);

	glVertex3d(xMin,yMax,zMin);
	glVertex3d(xMin,yMax,zMax);

	glVertex3d(xMax,yMin,zMin);
	glVertex3d(xMax,yMin,zMax);

	glVertex3d(xMax,yMax,zMin);
	glVertex3d(xMax,yMax,zMax);

	glVertex3d(xMin,yMin,zMin);
	glVertex3d(xMin,yMax,zMin);

	glVertex3d(xMax,yMin,zMin);
	glVertex3d(xMax,yMax,zMin);

	glVertex3d(xMin,yMin,zMax);
	glVertex3d(xMin,yMax,zMax);

	glVertex3d(xMax,yMin,zMax);
	glVertex3d(xMax,yMax,zMax);

	glVertex3d(xMin,yMin,zMin);
	glVertex3d(xMax,yMin,zMin);

	glVertex3d(xMin,yMax,zMin);
	glVertex3d(xMax,yMax,zMin);

	glVertex3d(xMin,yMin,zMax);
	glVertex3d(xMax,yMin,zMax);

	glVertex3d(xMin,yMax,zMax);
	glVertex3d(xMax,yMax,zMax);

    glEnd();

}

void BoundingBox::getDimensions(double dim[3])
{
	dim[0] = xMax - xMin;
	dim[1] = yMax - yMin;
	dim[2] = zMax - zMin;
}

// isEmpty:
//	return 1 if box is empty, 0 if not
int BoundingBox::isEmpty(void)
{
	double dim[3]; getDimensions(dim);
	if (fabs(dim[0]) < 0.000001 && fabs(dim[1]) < 0.000001 && fabs(dim[2]) < 0.000001)
		return 1;
	return 0;
}

// update:
//	Given the transformation matrix, update	the bounding box after
//	transforming it.
//
void	BoundingBox::update(double transMat[4][4])
{
	// We must transform each of the points	in the bounding	box,
	// the convex hull, to find and	choose the min and max from
	// these transformed points.
	double xmin = xMin, ymin = yMin, zmin =	zMin;
	double xmax = xMax, ymax = yMax, zmax =	zMax;

	double trans_point[3];
	trans_point[0] = xmin; trans_point[1] =	ymin; trans_point[2] = zmin;
	transformPoint_mat(trans_point,transMat);
	update(trans_point,1);

	trans_point[0] = xmin; trans_point[1] =	ymin; trans_point[2] = zmax;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmin; trans_point[1] =	ymax; trans_point[2] = zmin;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmin; trans_point[1] =	ymax; trans_point[2] = zmax;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmax; trans_point[1] =	ymin; trans_point[2] = zmin;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmax; trans_point[1] =	ymin; trans_point[2] = zmax;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmax; trans_point[1] =	ymax; trans_point[2] = zmin;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);

	trans_point[0] = xmax; trans_point[1] =	ymax; trans_point[2] = zmax;
	transformPoint_mat(trans_point,transMat);
	update(trans_point);
}

// update:
//	Given the point, updates the bounding box to include the point.
//
// returns: 0 on failure, 1 on success

int	BoundingBox::update(Vector point, int init)
{
	int retval = 0;

	if (init) {
	    xMin = xMax	= point[0];
	    yMin = yMax	= point[1];
	    zMin = zMax	= point[2];
	    return(1);
	}

	if (point[0] < xMin) {
	      xMin = point[0];
	      retval = 1;
	}
	if (point[0] > xMax) {
	      xMax = point[0];
	      retval = 1;
	}
	if (point[1] < yMin) {
	      yMin = point[1];
	      retval = 1;
	}
	if (point[1] > yMax) {
	      yMax = point[1];
	      retval = 1;
	}
	if (point[2] < zMin) {
	      zMin = point[2];
	      retval = 1;
	}
	if (point[2] > zMax) {
	      zMax = point[2];
	      retval = 1;
	}
	return(retval);
}

void BoundingBox::scale(double x, double y, double z)
{
	xMin = x*xMin;
	yMin = y*yMin;
	zMin = z*zMin;
	xMax = x*xMax;
	yMax = y*yMax;
	zMax = z*zMax;
}



void BoundingBox::MakeEmpty()
{
	xMin = yMin = zMin = 0.0;
	xMax = yMax = zMax = 0.0;
}
