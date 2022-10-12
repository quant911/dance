#include "defs.h"
#include "danceTcl.h"
#include "ParticlePoint.h"
#include "ParticlePointList.h"


PListElement::PListElement(ParticlePoint *p)
{
    m_particle = p ;
    m_next = NULL ;
}

PListElement::~PListElement() 
{
    if( m_particle ) delete m_particle ;
}

ParticlePointList::ParticlePointList()
{
    m_numElements = 0 ;
    m_first = NULL ;
    m_last = NULL ;
}

ParticlePointList::~ParticlePointList()
{
    int i ;
    for( i = 0 ; i < m_numElements ; i++)
    {
	PListElement *e = m_first ;
	m_first = m_first->m_next ;
	delete e ;
    }
}

void ParticlePointList::output(int mode)
{
    for( PListElement *e = m_first ; e ; e = e->m_next )
    {
	e->m_particle->output(mode) ;
    }
}

int ParticlePointList::add(ParticlePoint *p)
{
    if( p == NULL )
    {
	danceTcl::OutputMessage("ERROR: ParticlePoint::add(),"
				"passed in NULL pointer.") ;
	return 0;
    }
    PListElement *e = new PListElement(p) ;
    if( e == NULL )
    {
	danceTcl::OutputMessage("ERROR: ParticlePoint::add(),"
				"out of memory.") ;
	return 0 ;
    }
    if( m_first == NULL )
   	m_first = m_last = e ;
    else
    {
	m_last->m_next = e ;
	m_last = e ;
    }
    
    m_numElements++ ;
    return 1 ;
	
}


int ParticlePointList::remove(PListElement *e)
{
    if( m_numElements == 1)
    {
	m_last = m_first = NULL ;
	delete e ;
    }
    else if( e == m_last )
    {
	PListElement *e1 ;
	for( e1 = m_first ; e1->m_next != e ; e1 = e1->m_next ) ;
	m_last = e1 ;
	m_last->m_next = NULL ;
	delete e ;
    }
    else if( e->m_next != NULL)
    {
	// copy the next one in e and delete the next one
	// We have to update the m_last possibly
	delete e->m_particle ;
	if( m_last == e->m_next )
	    m_last = e ;
	e->m_particle = e->m_next->m_particle ;
	e->m_next->m_particle = NULL ;
	PListElement *temp = e->m_next ;
	e->m_next = e->m_next->m_next ;
	delete temp ;
    }
    m_numElements-- ;
    return m_numElements ;
}

// Runs throught the list and removes the particles
// whose time has expired
int ParticlePointList::removeDead(double time, double lifeTime)
{
    for( PListElement *e = m_first ; e ; e = e->m_next )
    {
	if( time - e->m_particle->m_birthTime > lifeTime )
	    remove(e) ;
    }
    return m_numElements ;
}

