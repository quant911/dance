/************************************************************

************************************************************/
#ifndef GLutilities_h
#define GLutilities_h
#include "defs.h"

DLLENTRY void GLdrawAxes(double length);
DLLENTRY void GLdrawCircle(double radius, int numSides);
DLLENTRY void GLdrawCylinder(double radLengthRatio, double point1[3], double point2[3]);
DLLENTRY void GLdrawVector(double point[3], double vector[3]);
DLLENTRY void GLdrawVector(double point[3], double direction[3], double mag);
DLLENTRY void GLmakeRasterFont(void);
DLLENTRY void GLlabel(char *s, int size = 12);
DLLENTRY void GLprintString(char *s);
DLLENTRY void GLdrawSphere(double radius, double centre[3]);
extern GLubyte rasters[][13];

#endif

