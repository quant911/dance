#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "IPose.h"
#include "IPoseGraph.h"

IPoseGraph::IPoseGraph()
{
    m_nposes = 0 ;
    m_current = NULL ;
    m_first = NULL ;
    m_last = NULL ;
}

IPoseGraph::~IPoseGraph()
{
    DeletePoses() ;
}

void IPoseGraph::DeletePoses(void)
{
    for( int i = 0 ; i < m_nposes ; i++ )
   	delete m_poses[i] ;
    m_first = NULL ;
    m_last = NULL ;
    m_current = NULL ;
    m_nposes = 0 ;
    
}

// Allways at the end
void IPoseGraph::Add(IPose *p) 
{
    if( m_nposes > MAX_NPOSES - 1 )
    {
	danceTcl::OutputMessage("Maximum number of poses exceeded.") ;
	return ;
    }
    
    if( m_first == NULL )
	m_first = p ;
    else
    {
   	m_last->SetNext(p) ;
        m_last->SetNextID(m_nposes) ;
    }
    m_last = p ;

    m_poses[m_nposes] = p ;
    m_nposes++ ;
}

void IPoseGraph::Add(int nparam, CtrPrm *param, double transTime, double currentTime)
{
    
    if(m_last != NULL)
    {
	if( m_lastTime >= 0.0 )
	    m_last->SetTransTime(currentTime - m_lastTime) ;
	else 
	    m_last->SetTransTime(currentTime) ;
    }
	
    m_lastTime = currentTime ;
    IPose *p = new IPose(m_nposes, nparam, param, 0.5 ) ;
    if( p == NULL )
    {
	danceTcl::OutputMessage("IPoseGraph::AddPose:Cannot allocate memory.") ;
	return ;
    }
    Add(p) ;
}

void IPoseGraph::Add(int nparam, CtrPrm *param, double transTime)
{
   
    IPose *p = new IPose(m_nposes, nparam, param, 0.5 ) ;
    if( p == NULL )
    {
	danceTcl::OutputMessage("IPoseGraph::AddPose:Cannot allocate memory.") ;
	return ;
    }
    Add(p) ;
}

IPose *IPoseGraph::GetNext(double time)
{
    if( m_nposes == 0 ) return NULL ;
    // sanity check
    if( m_current == NULL )
    {
	m_current = m_first ;
	m_first->SetStartTime(time) ;
    }
    
    if( m_current->GetTransTime() + m_current->GetStartTime() < time )
    {
  	m_current = m_current->GetNext() ;
	if( m_current == NULL )
	{
	    danceTcl::OutputMessage("PoseGraph finished.") ;
	    return NULL ;
	}
	else
	{
	    danceTcl::OutputMessage("Moving to pose %d", m_current->GetID()) ;
 	    m_current->SetStartTime(time) ;
	}
    }
    return m_current ;
}

void IPoseGraph::Save(char *fname)
{
    FILE *fp = fopen(fname, "w") ;
    if( fp == NULL )
    {
	danceTcl::OutputMessage("Cannot open $s", fname) ;
	return ;
    }

    Save(fp) ;
    fclose(fp) ;
}

void IPoseGraph::Save(FILE *fp)
{ 
    for( int i = 0 ; i < m_nposes ; i++ )
	m_poses[i]->Save(fp) ;
    
    // for( IPose *p = m_first ; p ; p = p->GetNext())
    //{
    //p->Save(fp) ;
    //if( p->m_next == m_first ) // cyclic graph
    //    break ;
    //}
}    

void IPoseGraph::Load(char *fname)
{
    FILE *fp = fopen(fname, "r") ;
    if( fp == NULL )
    {
	danceTcl::OutputMessage("Cannot open $s", fname) ;
	return ;
    }
    
    Load(fp) ;
    fclose(fp) ; 
}

void IPoseGraph::Load(FILE *fp)
{
    
    DeletePoses() ;
    while( !feof(fp) )
    {
	IPose *p = new IPose ;
	if( p->Load(fp) == -1 )
	    delete p ;
	else
	    Add(p) ;
    }
    // fix the next fields
    for( int i = 0 ; i < m_nposes ; i++ )
    {
	m_poses[i]->SetNext(m_poses[m_poses[i]->GetNextID()]) ;
    }
    danceTcl::OutputMessage("Loaded %d poses.", m_nposes) ;
}

CtrPrm *IPoseGraph::GetParams(double time) 
{
    IPose *p = GetNext(time) ;
    if( p == NULL )
    {
	danceTcl::OutputMessage("No next pose! ") ;
	return NULL ;
    }
    else
	return p->GetParams() ; 
}



