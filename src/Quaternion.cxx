#include <stdio.h>
#include "Quaternion.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double *Quaternion::toMatrix(double m[3][3])
{
	  double mat[4][4]; toMatrix(mat);
	  for (int i = 0; i < 3; i++)
		  for (int j = 0; j < 3; j++)
			  m[i][j] = mat[i][j];
	  return &m[0][0];
}

// creates a rotation matrix 4x4 from a	qauternion
// To matrix follows the column	vector convention
// v' =	m*v
double * Quaternion::toMatrix(double m[4][4])
{

	double w,x,y,z,s,xs,ys,zs,wx,wy,wz,xx,yy,zz,xy,yz,xz;

	x = e[0];
	y = e[1];
	z = e[2];
	w = e[3];

	s = 2.0/(x*x + y*y + z*z + w*w);
	xs = x*s; ys = y*s; zs = z*s;

	wx = w*xs; wy =	w*ys; wz = w*zs;
	xx = x*xs; xy =	x*ys; xz = x*zs;
	yy = y*ys; yz =	y*zs; zz = z*zs;

	m[0][0]	= 1.0 -	(yy+zz);
	m[0][1]	= xy+wz;
	m[0][2]	= xz-wy;
	m[0][3]	= 0.0;

	m[1][0]	= xy - wz;
	m[1][1]	= 1.0 -	(xx+zz);
	m[1][2]	= yz + wx;
	m[1][3]	= 0.0;

	m[2][0]	= xz+wy;
	m[2][1]	= yz-wx;
	m[2][2]	= 1.0 -	(xx+yy);
	m[2][3]	= 0.0;

	m[3][0]	= 0.0;
	m[3][1]	= 0.0;
	m[3][2]	= 0.0;
	m[3][3]	= 1.0;

    return &m[0][0];
}

// creates a rotation matrix 4x4 from a	qauternion
// To matrix follows the column	vector convention
// v' =	m*v
float * Quaternion::toMatrix(float m[4][4])
{

	double mat[4][4];
	toMatrix(mat);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = (float)mat[i][j];

	return &m[0][0];
}

void Quaternion::fromMatrix(double m[3][3])
{
	double mat[4][4];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			mat[i][j] = m[i][j];
		}
	mat[0][3] = 0.0;
	mat[1][3] = 0.0;
	mat[2][3] = 0.0;

	mat[3][0] = 0.0;
	mat[3][1] = 0.0;
	mat[3][2] = 0.0;
	mat[3][3] = 1.0;
	fromMatrix(mat);
}

void Quaternion::fromMatrix(float m[4][4])
{
	double mat[4][4];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			mat[i][j] = m[i][j];
		}
	mat[0][3] = 0.0;
	mat[1][3] = 0.0;
	mat[2][3] = 0.0;

	mat[3][0] = 0.0;
	mat[3][1] = 0.0;
	mat[3][2] = 0.0;
	mat[3][3] = 1.0;
	fromMatrix(mat);
}

// Matrix is expected to be used v'=m*v	where v	is
// of a	column vector
void Quaternion::fromMatrix(double m[4][4])
{
    double tr,s;
    int	i,j,k;

    tr = m[0][0]+m[1][1]+m[2][2];
    if (tr + 1.0 > 1e-10) {
	s = sqrt(tr+1.0);
	e[3] = s*0.5;
	s = 0.5/s;

	e[0] = (m[1][2]-m[2][1])*s;
	e[1] = (m[2][0]-m[0][2])*s;
	e[2] = (m[0][1]-m[1][0])*s;
    }
    else {
	i = 0;
	if (m[1][1] > m[0][0]) i = 1;
	if (m[2][2] > m[i][i]) i = 2;
	j = (i+1) % 3; k = (j+1) % 3;

	s = sqrt((m[i][i]-(m[j][j]+m[k][k])) + 1.0);
	e[i] = s*0.5;
	s = 0.5/s;
	e[j] = (m[i][j]	+ m[j][i])*s;
	e[k] = (m[i][k]	+ m[k][i])*s;
	e[3] = (m[j][k]	- m[k][j])*s;
    }

	calcAzimElevTwist();
    return ;
}

void Quaternion::fromVector(double v[4]) 
{
	e[0] = v[0]; e[1] = v[1]; e[2] = v[2]; e[3] = v[3];
	calcAzimElevTwist();
}


// Does not set Azim, Elev, Twist (called from Set(Azim,Elev,Twist)
void Quaternion::set(double rad, double axis[3])
{

    double angle2 = rad*0.5 ;
    double sin2	= sin(angle2) ;

	// Normalize axis.
	double mag = sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]);
	axis[0] /= mag;
	axis[1] /= mag;
	axis[2] /= mag;

    e[0] = sin2*axis[0]	;
    e[1] = sin2*axis[1]	;
    e[2] = sin2*axis[2]	;
    e[3] = cos(angle2) ;

}

// multiplies q1*q2 and	stores the result in the calling quaternion.
void Quaternion::multiply(Quaternion *q1, Quaternion *q2)
{
    Vector t1, t2 ;

    VecCrossProd(t2, q1->e, q2->e) ;
    VecNumMul(t1, q2->e, q1->e[3]) ;
    VecAdd(t2, t2, t1) ;
    VecNumMul(t1, q1->e, q2->e[3]) ;
    VecAdd(e, t1, t2) ;
    e[3] = q1->e[3] * q2->e[3] - VecDotProd(q1->e, q2->e) ;
	calcAzimElevTwist();
}

void Quaternion::multiply(Quaternion *q)
{
    Quaternion q1 ;
    q1.copy(this) ;
    multiply(&q1, q) ;
}

void Quaternion::set(double azim, double elev, double twist)
{
	// Convert angles to radians
	m_Azimuth = M_PI/180.0*azim;
	// We only allow positive elevation values. If a negative one is
	// entered, we convert it to a positive value.
	if (elev < 0.0) elev *= -1.0;
	m_Elevation = M_PI/180.0*elev;
	m_Twist = M_PI/180.0*twist;

	// Adjust to zero if very small.
	if (fabs(m_Azimuth) < 0.000001) m_Azimuth = 0.0;
	if (fabs(m_Elevation) < 0.000001) m_Elevation = 0.0;
	if (fabs(m_Twist) < 0.000001) m_Twist = 0.0;

	// Convert to spherical coordinates with radius 1
	Vector axis;
	axis[0] = sin(m_Elevation)*cos(m_Azimuth);
	axis[1] = cos(m_Elevation);
	axis[2] = sin(m_Elevation)*sin(m_Azimuth);

	set(m_Twist,axis);
}

int Quaternion::toAzimElevTwist(double * azim, double * elev, double * twist)
{
    double conv = 180.0 / M_PI ;
	*azim = m_Azimuth*conv ;
	*elev = m_Elevation*conv ;
	*twist = m_Twist*conv ;
	return 1;
}

// Returns the axis of rotation and angle in the quaternion.
void Quaternion::getAxisAngle(double axis [3], double *angle)
{
	double half_angle = acos(e[3]);
	*angle = half_angle*2.0;

    double sin2	= sin(half_angle);
	if (fabs(sin2) < 0.0001) { // No twist rotation
		axis[0] = 0.0; axis[1] = 1.0; axis[2] = 0.0;
		return;
	}

	// Axis of rotation.
	axis[0] = e[0]/sin2;
	axis[1] = e[1]/sin2;
	axis[2] = e[2]/sin2;
}

// calcAzimElevTwist:
// Converts stored quaternion into azimuth, elevation and twist angles.
// This should be called in cases where the m_Twist, m_Azimuth and
// m_Elevation have not be initialized or provided. DO NOT call this if
// we are setting the quaternion using set(azim,elev,twist).
//
void Quaternion::calcAzimElevTwist()
{
	// We use m_Twist to distinguish between positive and negative twist angles.
	// An acos operation would always return a positive angle which would lose the
	// negative angle information and incorrectly produce a positive sin instead of
	// a negative one.
	double half_angle = acos(e[3]);
	m_Twist = half_angle*2.0;
		
        double sin2	= sin(half_angle);
	if (fabs(sin2) < 0.0001) { // No twist rotation
		m_Elevation = 0.0; m_Azimuth = 0.0;
		// Note, this may cause some discontinuities in the rotation
		// axis, as a quaternion with a zero twist angle can have an infinite 
		// number of rotation axes.
		return;
	}

	// Axis of rotation.
	double rotaxis[3];
	rotaxis[0] = e[0]/sin2;
	rotaxis[1] = e[1]/sin2;
	rotaxis[2] = e[2]/sin2;
	// Renormalize to account for truncation errors.
	VecNormalize(rotaxis);


	// Inverse operation to find spherical coordinates.
	double projXZ = sqrt(rotaxis[0]*rotaxis[0] + rotaxis[2]*rotaxis[2]);

	// m_Elevation has 0 at the positive y axis and Pi at the negative y axis
	// arctan gives Pi/2 at the positive y axis and -Pi/2 at the negative y axis
	// Therefore, we perform a linear mapping to go to our correct elevation space
	//
	m_Elevation = -1.0*atan2(rotaxis[1],projXZ)+M_PI*0.5;
	m_Azimuth = atan2(rotaxis[2],rotaxis[0]);
}


// Slerp operation: Adapted from Watt and Watt
void Quaternion::Slerp(Quaternion *targetQuat, double t, Quaternion *interpolated)
{
	double cosom = e[0]*targetQuat->e[0] + e[1]*targetQuat->e[1] + e[2]*targetQuat->e[2] + e[3]*targetQuat->e[3];
	double sclp, sclq;
	if ((1.0 + cosom) > 0.00001) {
		if ((1.0-cosom) > 0.00001) {
			double omega = acos(cosom);
			double sinom = sin(omega);
			sclp = sin((1.0-t)*omega)/sinom;
			sclq = sin(t*omega)/sinom;
		}
		else {
			sclp = 1.0-t;
			sclq = t;
		}
		for (int i = 0; i < 4; i++)
			interpolated->e[i] = sclp*e[i] + sclq*targetQuat->e[i];
	}
	else {
		interpolated->e[0] = -1.0*e[1];
		interpolated->e[1] = e[0];
		interpolated->e[2] = -1.0*e[3];
		interpolated->e[3] = e[2];
		sclp = sin((1.0-t)*M_PI/2.0);
		sclq = sin(t*M_PI/2.0);
		for (int i = 0; i < 3; i++) 
			interpolated->e[i] = sclp*e[i] + sclq*interpolated->e[i];
	}
}
