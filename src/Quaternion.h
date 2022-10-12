#ifndef	QUATERNION_H
#define	QUATERNION_H

#include <math.h>
#include <stdio.h>
#include "vector.h"

class DLLENTRY Quaternion {
private:
  double e[4] ;
  void calcAzimElevTwist(void);

public:
	void Slerp(Quaternion *targetQuat, double t, Quaternion *interpolated);
	void getAxisAngle(double axis[3], double *angle);
	int toAzimElevTwist(double *azim, double *elev, double *twist);
	double m_Twist;
	double m_Azimuth;
	double m_Elevation;
	void set(double azim, double elev, double twist);
  inline double	get(int	i) { return (e[i]); };
  double *toMatrix(double m[4][4]) ;
  double *toMatrix(double m[3][3]) ;
  float  *toMatrix(float m[4][4]);
  void fromMatrix(double m[3][3]) ;
  void fromMatrix(double m[4][4]) ;
  void fromMatrix(float m[4][4]) ;
  void fromVector(double v[4]);
  inline void toVector(double v[4]) {v[0] = e[0]; v[1] = e[1]; v[2] = e[2]; v[3] = e[3];};
  inline void set(double x, double y, double z,	double w)
	{ e[0] = x; e[1] = y; e[2] = z;	e[3] = w; calcAzimElevTwist();};
  void set(double rad, double axis[3]) ;
  inline void set(int index, double value) { e[index] =	value; calcAzimElevTwist(); } ;
  void print(FILE *fp) { fprintf(fp,"%f	%f %f %f\n",e[0],e[1],e[2],e[3]) ; } ;
  void multiply(Quaternion *q1,	Quaternion *q2)	;
  void multiply(Quaternion *q) ;
  void copy(Quaternion *q) { e[0] = q->e[0]; e[1] = q->e[1] ; e[2] = q->e[2] ;
  e[3] = q->e[3] ; calcAzimElevTwist(); } ;

} ;


#endif
