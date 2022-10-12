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

#include "defs.h"

#include "myMath.h"

#ifndef	_MONITORPOINTS_H
#define	_MONITORPOINTS_H

class DLLENTRY MonitorPoints {
public:
  MonitorPoints() ;
  virtual ~MonitorPoints() ;
  int Allocate(int n) ;
  void Deallocate(void) ;

  int m_NumPoints ;
  Vector *m_Point ;
  Vector *m_PrevPos ;

  double *m_PrevPosTimeStamp ;
  int *m_InCollision ;

  void Reset(void) ;
} ;

#endif

