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



#ifndef	_BOUNDINGBOX_H_
#define	_BOUNDINGBOX_H_	1

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

#include "myMath.h"

class DLLENTRY BoundingBox {
public:
	void MakeEmpty(void);
    BoundingBox();

    BoundingBox	*merge(BoundingBox *, BoundingBox *);
    void copy(BoundingBox *);
    void display(float r=0.0, float g=0.7, float b=0.0,	float a=1.0);
    void update(double transMat[4][4]);
    void scale(double x, double	y, double z);
    int	update(Vector point, int init=0);

    void getDimensions(double dim[3]);
    int isEmpty();

    // Actual coordinates of box.
    double xMin, yMin, zMin ;
    double xMax, yMax, zMax ;

} ;
#endif
