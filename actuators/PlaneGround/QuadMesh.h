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


#ifndef	_QUADMESH_H_
#define	_QUADMESH_H_ 1

#include "vector.h"
#include "BoundingBox.h"

#ifdef WIN32
#ifdef _EXPORTING_GR
#define DLLENTRY_GR __declspec(dllexport)
#else
#define DLLENTRY_GR __declspec(dllimport)
#endif
#else
#define DLLENTRY_GR
#endif

class DLLENTRY_GR Plane {
public:
    double a ;
    double b ;
    double c ;
    double d ;

//    void getNormal() ;
} ;

#define	MAX_QUAD_POINTS_X   100	// maximum number of points per	quad mesh dimension
#define	MAX_QUAD_POINTS_Y   100

class DLLENTRY_GR QuadMesh {
private:
    BoundingBox	boundingBox;

public:
    QuadMesh() ;
    void calcInerTensor(double inerTensor[3][3], double	mass);
    void getPointsMesh(Vector points[MAX_QUAD_POINTS_X][MAX_QUAD_POINTS_Y])
;
    void getDim(int *,int*) ;
    Vector points[MAX_QUAD_POINTS_X][MAX_QUAD_POINTS_Y]	;
    Vector normals[MAX_QUAD_POINTS_X][MAX_QUAD_POINTS_Y] ;
    int	nx ;
    int	ny ;
    void  calcNormals()	;
    void display(int style=0);
    void displayCheck(GLfloat c1[4], GLfloat c2[4],int useText = 0)	;
    double *calcInterscLine(Vector, Vector, Vector) ;
    int	calcBoundingBox(BoundingBox *box);

} ;

#endif
