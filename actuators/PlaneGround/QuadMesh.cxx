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

#ifdef WIN32
#include <windows.h>
#endif

#include "defs.h"
#include <GL/gl.h>
#include "dance.h"
#include "danceTcl.h"
#include "QuadMesh.h"

QuadMesh::QuadMesh()
{
    nx = 0 ;
    ny = 0 ;

    for( int i = 0 ; i < MAX_QUAD_POINTS_X ; i++ )
	for( int j = 0 ; j < MAX_QUAD_POINTS_Y ; j++ )
	{
	    setVector(normals[i][j],0.0,0.0,0.0) ;
	    setVector(points[i][j],0.0,0.0,0.0)	;
	}
    return ;
}

void QuadMesh::calcInerTensor(double inerTensor[3][3], double mass)
{
	int i,j,k,l;
	int nx,	ny;
	getDim(&nx,&ny)	;

	static Vector points[MAX_QUAD_POINTS_X][MAX_QUAD_POINTS_Y] ;
	getPointsMesh(points) ;
	double massPoint = mass	/ (double) (nx*ny) ;
	for( i = 0 ; i < 3 ; i++ )
	    for( j = 0 ; j < 3 ; j++ )
		inerTensor[i][j] = 0.0 ;


	for( i = 0 ; i < 3 ; i++ )
	    for( j = 0 ; j < 3 ; j++ )
		for( k = 0 ; k < nx ; k++ )
		    for( l = 0 ; l < ny	; l++ )
		    {
			if( i == j)
			    switch (i)
			    {
			    case 0:
			      inerTensor[0][0] += points[k][l][1]*points[k][l][1]+
				points[k][l][2]*points[k][l][2]	;
			      break ;
			    case 1:
			      inerTensor[1][1] += points[k][l][0]*points[k][l][0]+
				points[k][l][2]*points[k][l][2]	;
			      break ;
			    case 2:
			      inerTensor[2][2] += points[k][l][0]*points[k][l][0]+
				points[k][l][1]*points[k][l][1]	;
			      break ;
			    }
			else		// follow the minus sign convention
			    inerTensor[i][j] -=	points[k][l][i]*points[k][l][j]	;
		    }
	for( i = 0 ; i < 3 ; i++ )
	    for( j = 0 ; j < 3 ; j++)
		inerTensor[i][j] *= massPoint ;

}

void QuadMesh::getDim(int *x, int *y)
{
    *x = nx ; *y = ny ;
}

void QuadMesh::getPointsMesh(Vector
points[MAX_QUAD_POINTS_X][MAX_QUAD_POINTS_Y])
{
    return ;
}


/***************************************************
  PROC:	QuadMesh::calcNormal()
  DOES:	calculates normals for a quadrilateral mesh.
	No exploitation	of adjacency properties	yet.
****************************************************/

void QuadMesh::calcNormals()
{
    int	i,j ;
    Vector v1,v2 ;

    for( i = 0 ; i < (nx-1) ; i++)
	for( j = 0 ; j < (ny-1)	; j++)
	{
	    VecSubtract(v1,points[i][j+1],points[i][j])	;
	    VecSubtract(v2,points[i+1][j],points[i][j])	;
	    VecCrossProd(normals[i][j],	v1, v2)	;
	    VecNormalize(normals[i][j])	;
	}
    return ;
}

#ifndef	NO_GL
void QuadMesh::display(int style)
{
    int	i,j ;


    if (( nx < 2) || (ny < 2))
    {
	danceTcl::OutputMessage("QuadMesh::display() wrong number of quad dimensions");
	return ;
    }

    glColor4f(1.0,1.0,1.0,1.0);
    if(	nx < ny	)		     //	we save	more by	using the feature on the
	for( i = 0 ; i < nx-1 ;	i++ )  // y dimension
	{
	    glBegin(GL_QUAD_STRIP) ;
	    for( j = 0 ; j < ny-1 ; j++	)
	    {
		glNormal3dv(normals[i][j]) ;
		glVertex3dv(points[i][j]) ;
		glVertex3dv(points[i][j+1]) ;
		glVertex3dv(points[i+1][j]) ;
		glVertex3dv(points[i+1][j+1]) ;
	    }
	    glEnd() ;

	}
    else
	for( j = 0 ; j < ny-1 ;	j++ )
	{
	    glBegin(GL_QUAD_STRIP) ;
	    for( i = 0 ; i < nx-1 ; i++	)
	    {
		glNormal3dv(normals[i][j]) ;
		glVertex3dv(points[i][j]) ;
		glVertex3dv(points[i][j+1]) ;
		glVertex3dv(points[i+1][j]) ;
		glVertex3dv(points[i+1][j+1]) ;
	    }
	    glEnd() ;

	}


    return ;
}

#else
void QuadMesh::display(int style) { return ;}
#endif

/**************************************************
  PROC:	calcInterscLine()
  DOES:	calculates the intersection of a line with the
	a quad mesh whose quadrilaterals are square with
	respect	to the x and  z	axis
***************************************************/

double * QuadMesh::calcInterscLine(Vector point1, Vector point2, Vector
intersc)
{

    int	found  ;
    Plane plane	;
    double div,	xsign,ysign,a ;
    int	i,j ;
    Vector dp ;

    found = FALSE ;
    for( i = 0 ; (i < nx-1) && (!found)	; i++ )
	for( j = 0 ; (j	< ny-1)	&& (!found) ; j++)
	{
	    // make the	plane Ax+by+cz+d = 0
	    plane.a = normals[i][j][0] ;
	    plane.b = normals[i][j][1] ;
	    plane.c = normals[i][j][2] ;
	    plane.d = 0.0 - VecDotProd(normals[i][j],points[i][j]) ;

	    VecSubtract(dp,point2,point1) ;
	    div	= VecDotProd(dp,normals[i][j]) ;
	    if (div != (double)	0.0)
	    {
		a = 0.0	-(plane.d + VecDotProd(normals[i][j],point1)) /	div
;
		VecNumMul(intersc,dp,a)	;
		VecAdd(intersc,intersc,point1) ;
	    }
	    // check and see if	that point is in the quadrilateral
	    // exploit the fact	that quadrilaterals are	square
	    // and do not change slope along the z axis
	    if ( (intersc[0] > points[i][j][0])	&& (intersc[0] <
points[i+1][j+1][0]))
	    {
		xsign =	(intersc[0]-point1[0])*(intersc[0] - point2[0])	;
		ysign =	(intersc[1]-point1[1])*(intersc[1] - point2[1])	;
		// check if the	point is in the	line segment (point1,point2)
		if( (xsign <= 0.0) && (ysign <=	0.0))
		    found = TRUE ;
	    }
	    else found = FALSE ;
	}

    if(	found == FALSE )
    {
	danceTcl::OutputMessage("no intersection could be found!? Something wrong?") ;
	return NULL ;
    }
    else return	 &intersc[0] ;
}



// useText = 0 no texture
// useText = 1 apply on	large 4 corners
// useText = 2 apple per quad
void QuadMesh::displayCheck(GLfloat c1[4], GLfloat c2[4], int textureMode)
{
    int	i,j ;
    int	flip = 0, outFlip = 0 ;
    GLfloat white[4] = {1.0,1.0,1.0,1.0} ;
    GLfloat blue[4] = {	0.0,0.0,1.0,1.0} ;


    if (( nx < 2) || (ny < 2))
    {
		danceTcl::OutputMessage("QuadMesh::draw() wrong number of quad dimensions\n") ;
	return ;
    }


    // first draw the border as	line so	that the ground	is visible
    // even when the seen from the side
    int	prev_l ;
    if(	(prev_l	= glIsEnabled(GL_LIGHTING)) == GL_TRUE)
    {
	glDisable(GL_LIGHTING) ;
    }


    if(	!textureMode )
    {
	glColor3f(0.0,0.0,1.0) ;
	glMaterialfv(GL_FRONT_AND_BACK,	GL_AMBIENT_AND_DIFFUSE,c2) ;
	glLineWidth(5) ;
	glBegin(GL_LINE_LOOP) ;
	{
	    glVertex3dv(points[0][0]) ;
	    glVertex3dv(points[0][nx-1]) ;
	    glVertex3dv(points[ny-1][nx-1]) ;
	    glVertex3dv(points[ny-1][0]) ;
	}
	glEnd()	;
	glLineWidth(1) ;
	if( prev_l == GL_TRUE)
	    glEnable(GL_LIGHTING);
    }
    if(	textureMode )
    {
	extern GLuint g_TexName ;
	glEnable(GL_TEXTURE_2D)	;
	#ifndef IRIX
	glBindTexture(GL_TEXTURE_2D, g_TexName) ;
	#endif
    }
    // if(glIsEnabled(GL_TEXTURE_2D) ==	GL_TRUE)
    //	printf("Texture	is enabled\n") ;

    float t_x, t_dx = (float) 1.0 / (float) (nx-1) ;
    float t_y, t_dy = (float) 1.0 / (float) (ny-1) ;

    if(	nx < ny	)		     //	we save	more by	using the feature on the
	for( i = 0 ; i < nx-1 ;	i++ )  // y dimension
	{
	    glBegin(GL_QUAD_STRIP) ;
	    for( j = 0 ; j < ny-1 ; j++	)
	    {


		if (flip == 0)
		{
		    flip = 1 ;
		    glColor4f(c2[0],c2[1],c2[2],c2[3]) ;
		    if( prev_l == GL_TRUE) 
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,c2) ;
		}
		else
		{
		    flip = 0 ;
		    glColor4f(c1[0],c1[1],c1[2],c1[3]) ;
		    if( prev_l == GL_TRUE )
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,c1) ;
		}

		// draw
		if( textureMode	== 1)
		{
		    t_x	= i*t_dx ;
		    t_y	= j*t_dy ;
		}
		else if	(textureMode ==	2)
		{
		    t_x	= 0.0 ;
		    t_y	= 0.0 ;
		}
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glNormal3dv(normals[i][j]) ;
		glVertex3dv(points[i][j]) ;
		if( textureMode	== 1) t_y += t_dy ;
		else if( textureMode ==	2) t_y = 1.0 ;
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i][j+1]) ;
		if( textureMode	== 1)
		{
		    t_y	= j*t_dy ;
		    t_x	+= t_dx	;
		}
		else if( textureMode ==	2)
		{
		    t_y	= 0.0 ;
		    t_x	= 1.0 ;
		}
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i+1][j]) ;
		if( textureMode	== 1) t_y += t_dy ;
		else if( textureMode ==	2) t_y = 1.0 ;
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i+1][j+1]) ;
	    }
	    glEnd() ;
	    // we finished a row so find out with what we
	    // should start the	next one
	    if(	outFlip	== 0)
	    {
		outFlip	= 1 ; flip = 1 ;
	    }
	    else
	    {
		outFlip	= 0 ; flip = 0 ;
	    }

	}
    else
	for( j = 0 ; j < ny-1 ;	j++ )
	{
	    glBegin(GL_QUAD_STRIP) ;
	    for( i = 0 ; i < nx-1 ; i++	)
	    {
		if (flip == 0)
		{
		    flip = 1 ;
		    glColor4f(c2[0],c2[1],c2[2],c2[3]) ;
		    if( prev_l == GL_TRUE)
			glMaterialfv((GLenum) GL_FRONT_AND_BACK, (GLenum)GL_AMBIENT_AND_DIFFUSE,c2) ;
		}
		else
		{
		    flip = 0 ;
		    glColor4f(c1[0],c1[1],c1[2],c1[3]) ;
		    if( prev_l == GL_TRUE) 
			glMaterialfv((GLenum) GL_FRONT_AND_BACK, (GLenum) GL_AMBIENT_AND_DIFFUSE,c1) ;
		}



		if( textureMode	== 1)
		{
		    t_x	= i*t_dx ;
		    t_y	= j*t_dy ;
		}
		else if	(textureMode ==	2)
		{
		    t_x	= 0.0 ;
		    t_y	= 0.0 ;
		}
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glNormal3dv(normals[i][j]) ;
		glVertex3dv(points[i][j]) ;
		if( textureMode	== 1) t_y += t_dy ;
		else if( textureMode ==	2) t_y = 1.0 ;
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i][j+1]) ;
		if( textureMode	== 1)
		{
		    t_y	= j*t_dy ;
		    t_x	+= t_dx	;
		}
		else if( textureMode ==	2)
		{
		    t_y	= 0.0 ;
		    t_x	= 1.0 ;
		}
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i+1][j]) ;
		if( textureMode	== 1) t_y += t_dy ;
		else if( textureMode ==	2) t_y = 1.0 ;
		if( textureMode	) glTexCoord2f(t_x,t_y);
		glVertex3dv(points[i+1][j+1]) ;

	    }
	    glEnd() ;
	    if(	outFlip	== 0)
	    {
		outFlip	= 1 ; flip = 1 ;
	    }
	    else
	    {
		outFlip	= 0 ; flip = 0 ;
	    }
	}

     if( textureMode )
	glDisable(GL_TEXTURE_2D) ;
    return ;
}


// calc	a bounding box for a quad mesh
int QuadMesh::calcBoundingBox(BoundingBox *box)
{

    double xMin;
    double yMin;
    double zMin;
    double xMax;
    double yMax;
    double zMax;

	// Only	need to	check the corners.
    for( int k = 0 ; k < nx ; k	+= nx-1	)
	for( int l = 0 ; l < ny	; l += ny-1 )
	{
		if ((k == 0) && (l == 0)) {
		    xMax = xMin	= points[k][l][0];
			yMax = yMin = points[k][l][1];
			zMax = zMin = points[k][l][2];
		}
		else {
	    if(	points[k][l][0]	> xMax ) xMax =	points[k][l][0]	;
	    if(	points[k][l][0]	< xMin ) xMin =	points[k][l][0]	;

	    if(	points[k][l][1]	> yMax ) yMax =	points[k][l][1]	;
	    if(	points[k][l][1]	< yMin ) yMin =	points[k][l][1]	;

	    if(	points[k][l][2]	> zMax ) zMax =	points[k][l][2]	;
	    if(	points[k][l][2]	< zMin ) zMin =	points[k][l][2]	;
		}
	}

    boundingBox.xMin = xMin;
    boundingBox.yMin = yMin;
    boundingBox.zMin = zMin;
    boundingBox.xMax = xMax;
    boundingBox.yMax = yMax;
    boundingBox.zMax = zMax;

    if(	fabs(xMin - xMax) < 0.000001 )
    {
	boundingBox.xMin -= 0.1	;
	boundingBox.xMax += 0.1	;
    }
    if(	fabs(yMin - yMax) < 0.000001 )
    {
	boundingBox.yMin -= 0.1	;
	boundingBox.yMax += 0.1	;
    }
    if(	fabs(zMin - zMax) < 0.000001 )
    {
	boundingBox.zMin -= 0.1	;
	boundingBox.zMax += 0.1	;
    }

    // Now adjust these	bounding box points via	the fix	Matrix
	box->copy(&boundingBox);
    return (1);
}
