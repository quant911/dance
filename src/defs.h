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



#ifndef _DEFS_H_
#define _DEFS_H_

#define	OK   1
#define	ERR -1
#define	TRUE 1
#define	FALSE 0

#define	EXIT 0

#define	MAX_LINE 250
#define	VECSIZE	4
#define	MAX_ARGS 50

typedef	int myBOOL;
#define	STRLEN 100
typedef	char STR[STRLEN];

#define	LDISPLAY_WIRE	     1
#define	LDISPLAY_MONITOR     2
#define	LDISPLAY_SHADOW	     4
#define	LDISPLAY_SOLID       8
#define	LDISPLAY_SELECTION  16

// For joints.
#define	JDISPLAY_CENTRES    32
#define JDISPLAY_MANIPS     64
#define JDISPLAY_SELECTION	128

#ifdef WIN32
#include <windows.h>

//  #ifdef _IMPORTING
//  #define	DLLENTRY __declspec(dllimport)
//  #else
//  #define	DLLENTRY __declspec(dllexport)
//  #endif

#ifdef _EXPORTING_DANCE_CORE
#define	DLLENTRY __declspec(dllexport)
#else
#define	DLLENTRY __declspec(dllimport)
#endif

#define	DLLEXPORT __declspec(dllexport)
#define	DLLIMPORT __declspec(dllimport)
#else
#define	DLLENTRY
#define	DLLEXPORT
#define	DLLIMPORT

#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../libinclude/tcl.h"
#include "../libinclude/tk.h"

#ifndef	M_PI
#define	M_PI		3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2          1.57079632679489661923
#endif

#ifndef MAXFLOAT
#define  MAXFLOAT        ((float)3.40282346638528860e+38)  
#endif

#ifndef MINFLOAT
#define MINFLOAT         (-(float)3.40282346638528860e+38)
#endif 

#endif // _DEFS_H_


