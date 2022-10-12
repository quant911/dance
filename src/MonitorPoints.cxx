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

#include "MonitorPoints.h"
#include "danceTcl.h"

/** Constructor */
MonitorPoints::MonitorPoints()
{
    m_NumPoints = 0 ; 
    m_Point = NULL ; 
    m_PrevPos = NULL ;
    m_InCollision = NULL;
    m_PrevPosTimeStamp = NULL ;
}

/** Destructor */
MonitorPoints::~MonitorPoints()
{ 
    if( m_NumPoints == 0 ) return ;
    Deallocate() ;
}

/** 
  * Allocates the neccessary memory for np number of points
  *
  * Allocates the vector arrays to hold the points, their previous position,
  * their under ground status.
  *
  * @param np 
  * The number of points
  * @returns 
  * The number of allocated points
  */
int MonitorPoints::Allocate(int np)
{
    if( np < 1  ) return 0 ;

    if( m_Point != NULL ) delete [] m_Point  ;
    m_Point = new Vector [np] ;
    if( m_Point == NULL )
    {
	danceTcl::OutputMessage("MonitorPoints::Allocate:"
			       "Cannot allocate memory!") ;
	return 0 ;
    }
    
    if (m_InCollision != NULL) delete [] m_InCollision ;
    m_InCollision = new int [np] ;
    if( m_InCollision == NULL )
    {
	danceTcl::OutputMessage("MonitorPoints::Allocate:"
			       "Cannot allocate memory!") ;
	Deallocate() ;
	return 0 ;
    }

    if( m_PrevPos != NULL ) delete [] m_PrevPos ;
    m_PrevPos = new Vector [np] ;
    if( m_PrevPos == NULL )
    {
	danceTcl::OutputMessage("MonitorPoints::Allocate:"
			       "Cannot allocate memory!") ;
	Deallocate() ;
	return 0 ;
    }
    
    if( m_PrevPosTimeStamp != NULL ) delete [] m_PrevPosTimeStamp ;
    m_PrevPosTimeStamp = new double [np] ;
    if( m_PrevPosTimeStamp == NULL )
    {
	danceTcl::OutputMessage("MonitorPoints::Allocate:"
				"Cannot allocate memory!") ;
	Deallocate() ;
	return 0 ;
    }

    m_NumPoints = np ;
    return np ;    
}

/**
  * Delete all the vector arrays 
  *
  * Deletes the m_PrevPos, m_Points, m_InCollision
  * and sets the m_NumPoints to zero
  */
void MonitorPoints::Deallocate(void) 
{
    if( m_Point == NULL ) delete [] m_Point  ;
    if (m_InCollision != NULL) delete [] m_InCollision ;
    if( m_PrevPos != NULL ) delete [] m_PrevPos ; 
    
    m_NumPoints = 0 ;
}

/** set all points to be above the ground */
void MonitorPoints::Reset(void)
{
	for( int i = 0 ; i < m_NumPoints ; i++ )
		m_InCollision[i] = FALSE ;
}