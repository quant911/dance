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



#ifndef	myVECTOR_H
#define	myVECTOR_H
typedef	double Vector[3] ;

#ifndef	DLLENTRY
#ifdef WIN32
#include <windows.h>

#define	DLLENTRY __declspec(dllexport)

#else

#define	DLLENTRY
#endif
#endif

DLLENTRY void printVector(Vector v) ;

DLLENTRY void VecAdd(Vector c, Vector a, Vector	b) ;

DLLENTRY void setVector(Vector v, double a, double b, double c)	;

DLLENTRY void VecSubtract(Vector c, Vector a, Vector b)	;

DLLENTRY int VecEq( Vector a, Vector b)	;

DLLENTRY void zeroVector(Vector	a) ;

DLLENTRY void VecCopy(Vector c, Vector a) ;

DLLENTRY double	VecDotProd(Vector a,Vector b) ;

DLLENTRY void VecCrossProd(Vector c, Vector a, Vector b) ;

DLLENTRY void VecInter(Vector c, Vector	a, Vector b, double t) ;

DLLENTRY void VecNumMul(Vector c, Vector a, double n) ;

DLLENTRY void VecScale(Vector c, double	n) ;

DLLENTRY double	VecLength(Vector v) ;

DLLENTRY void VecNormalize(Vector v) ;

DLLENTRY double	*aVecNormalize(double *v, int n) ;

DLLENTRY double	aVecLength(double *v, int n) ;
#endif























