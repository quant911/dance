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



#include <stdio.h>
#include <math.h>
#include "vector.h"


#ifndef	VECTOR_MACRO

void zeroVector(Vector a)
{
    a[0] = a[1]	= a[2] = 0.0 ;
    return ;
}

int
VecEq(Vector a,	Vector b)
{
    if ((a[0] == b[0]) && (a[1]	== b[1]) && (a[2] == b[2]))
	return 1 ;
    else return	0 ;
}

void setVector(Vector v, double	a, double b, double c)
{
    v[0] = a ;
    v[1] = b ;
    v[2] = c ;
    return ;
}

void
printVector(Vector v)
{
	printf("%f %f %f\n", v[0],v[1],v[2]) ;
}

void
VecSubtract(Vector c, Vector a,	Vector b)
{

	c[0] = a[0] - b[0] ;
	c[1] = a[1] - b[1] ;
	c[2] = a[2] - b[2] ;
}

void
VecAdd(Vector c, Vector	a, Vector b)
{

	c[0] = a[0] + b[0] ;
	c[1] = a[1] + b[1] ;
	c[2] = a[2] + b[2] ;
}


void
VecCopy(Vector c, Vector a)
{
    c[0] = a[0]	;
    c[1] = a[1]	;
    c[2] = a[2]	;
}


double VecDotProd(Vector a,Vector b)
{
    return( a[0]*b[0]+a[1]*b[1]+a[2]*b[2] ) ;
}

void VecCrossProd(Vector c, Vector a, Vector b)
{
    c[0] = a[1]*b[2] - a[2]*b[1] ;
    c[1] = -a[0]*b[2] +	a[2]*b[0] ;
    c[2] = a[0]*b[1] - a[1]*b[0] ;
}


void VecInter(Vector c,	Vector a, Vector b, double t)
{
    double t1 ;

    t1 = 1.0-t ;
    c[0] = a[0]*t1+b[0]*t ;
    c[1] = a[1]*t1+b[1]*t ;
    c[2] = a[2]*t1+b[2]*t ;
}

void VecNumMul(Vector c, Vector	a, double n)
{
	c[0] = a[0]*n ;
	c[1] = a[1]*n ;
	c[2] = a[2]*n ;
}

void VecScale(Vector c,	double n)
{
	c[0] *=	n ;
	c[1] *=	n ;
	c[2] *=	n ;
}

double VecLength(Vector	v)
{
	return sqrt( (v[0]*v[0]	+ v[1]*v[1] + v[2]*v[2]) ) ;
}

void
VecNormalize(Vector v)
{
	double	norm ;

	if ( (norm = VecLength(v)) == 0)
	{
		fprintf(stderr,"Warning: a zero	vector was given to VecNormalize\n") ;
		return ;
	}

	norm = 1.0 / norm ;
	v[0] *=	 norm ;
	v[1] *=	 norm ;
	v[2] *=	 norm ;
	return ;
}

#endif

/******************************************************
  These	functions are never macros
*******************************************************/


double aVecLength( double *v, int n)
{
    int	i ;
    double l ;

    l =	0.0 ;
    for( i = 0 ; i < n ; i++)
	l += v[i]*v[i] ;
    return sqrt(l) ;
}

double *aVecNormalize(double *v, int n)
{
    double norm	 ;
    int	i ;

    if(	(norm =	aVecLength(v,n)) == 0)
    {
	fprintf(stderr,"Warning: a zero	vector was given to aVecNormalize\n") ;
	return v ;
    }

    norm = 1.0 / norm ;
    for( i = 0 ; i < n ; i++)
	v[i] *=	norm ;
    return v ;
}





