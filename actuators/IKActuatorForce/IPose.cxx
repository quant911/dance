#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "IPose.h"

IPose::IPose(void)
{
    m_transTime = -1 ;
    m_startTime = -1 ;
    m_next = NULL ;
    m_nextID = -1 ;
    m_id = -1 ;
    m_nparams = 0 ;
}

IPose::IPose(int id, int nparam, CtrPrm *q, double transTime)
{
    m_transTime = transTime ;
    m_startTime = -1 ;
    m_next = NULL ;
    m_nextID = -1 ;
    m_id = id ;
    m_nparams = nparam ;
    
    for( int i = 0 ; i < nparam ; i++ )
	m_q[i] = q[i] ;
}


void IPose::Save(FILE *fp)
{
    fprintf(fp, "Pose %d next %d\n", m_id, m_nextID) ;
    fprintf(fp, "transTime %lf numTriplets %d", m_transTime, m_nparams) ; 
    for( int i = 0 ; i < m_nparams ; i++ )
    {
	fprintf(fp, " %lf %lf %lf", m_q[i].v, m_q[i].ks, m_q[i].kd ) ;
    }
    fprintf(fp, "\n") ;
}

int IPose::Load(FILE *fp)
{
	char line[256] ;
	line[0] = '#' ;

	while( (!feof(fp)) && (( line[0] == '#') || (line[0] == '\n')))
		fgets(line,256,fp) ;

	if( feof(fp) ) return -1 ;
    if( sscanf(line, "Pose %d next %d", &m_id, &m_nextID) != 2)
    {
	danceTcl::OutputMessage("Expected: Pose <num> next <num>\n") ;
	return -1 ;
    }


    if ( fscanf(fp, "transTime %lf numTriplets %d", &m_transTime, &m_nparams) != 2 )
    {
	danceTcl::OutputMessage("Expected: transTime <num> numTriplest <num>") ;
	return -1 ;
    }
    int count = 0 ;
    while( (!feof(fp)) && ( count != m_nparams))
    {
	if( fscanf(fp, "%lf %lf %lf", &m_q[count].v, &m_q[count].ks, &m_q[count].kd) != 3 )
	{
	    danceTcl::OutputMessage("Syntax error: Expected three doubles.") ;
	    return -1 ;
	}
	count++ ;
    }
    return 1 ;
}


