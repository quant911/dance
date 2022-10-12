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




#ifndef	myMATH_H
#define	myMATH_H

#include "vector.h"
#include "CoordSystem.h"


DLLENTRY double VecLength(double *v, int size) ;

void calcNormal(Vector *p[],int	nver, Vector v)	;

/*** Point ***/

// void localToWorld( Vector plocal, Vector pworld, CoordSystem   * cs) ;


DLLENTRY void printPoints(double	* geom,	int size, int dim) ;


DLLENTRY double	inter(double a,	double b, double t) ;


/**** Array ****/
DLLENTRY void D2ArrayCopy( int n,int m,double *c,double *a) ;

DLLENTRY void I2ArrayCopy( int n,int m,int *c,int *a) ;

DLLENTRY double * transpArray(double *at, double	*a, int	n, int m) ;
DLLENTRY float *  transpArrayFloat(float *at, float *a, int n, int m) ;

DLLENTRY double * addArray(double *c, double *a,	double *b, int n, int m) ;

DLLENTRY double * subtractArray(double *c, double *a, double *b,	int n, int m) ;

DLLENTRY double * multNumArray( double num, double * a, int n, int m) ;

DLLENTRY double * MultNumArray( double *c, double num, double * a, int n, int m)	;

DLLENTRY double * multArray(double *c, double *a, double	*b, int	n1, int	m, int n2) ;

DLLENTRY double qT_M_q(double *m, double	*q, int	n) ;

DLLENTRY void printArray( double	*a, int	n, int m) ;

DLLENTRY int isDiagonal(double *a,int n)	;

/*************** end array ****************/

DLLENTRY double Norm(double q[],	int n) ;

/*** other ***/
DLLENTRY double Bernst3(	double x, int i) ;

DLLENTRY double dBernst3( double	x, int i) ;

DLLENTRY double ddBernst3( double x, int	i) ;

DLLENTRY double * EulerIntegr(double dq[], double q[], int n, double dt)	;




/**********************************************
 Rotation using	matrices
 **********************************************/

DLLENTRY void rotateCSorigin_mat(CoordSystem *cs, double	rot[3][3]) ;
DLLENTRY void rotatePoint_mat(Vector point, double rot[3][3]) ;
DLLENTRY void transformPoint_mat(Vector point, double rot[4][4])	;
DLLENTRY void transformPoints_mat(Vector *points, int n, Vector	*newpoints, double transmat[4][4]) ;
DLLENTRY void rotPoint_mat4(Vector point, double transmat[4][4]) ;
DLLENTRY void relativeToFrame(double mat[4][4], double wmat[4][4], double rmat[4][4]);

DLLENTRY void XRotatePoints(Vector *points, int npoints, double degrees) ;
DLLENTRY void YRotatePoints(Vector *points, int npoints, double degrees) ;
DLLENTRY void ZRotatePoints(Vector *points, int npoints, double degrees) ;


DLLENTRY char * convIntToStr(int frameNumber, char *s) ;

/**********************************************************/

void embedCsInCs(CoordSystem * cs_guest, CoordSystem * cs_host)	;

double *constrTransfMatrixFromCs(double	m[4][4], CoordSystem *cs) ;

DLLENTRY double *invSmart4(double inv[4][4], double a[4][4]) ;

DLLENTRY double * quatToMat(double q[4],double m[4][4]) ;


DLLENTRY void setIdentMat(double *m, int n) ;

DLLENTRY void compRotMat4(double c[4][4], double m1[4][4], double m2[4][4]) ;


DLLENTRY double *lineIntersection(Vector v1, Vector v2, Vector w1, Vector w2, 
			 Vector intersection, int infinite) ;
#endif


