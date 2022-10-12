#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "danceTcl.h"
#include "KeyFrame.h"
#include "AnimationSequence.h"

#ifndef EPS
#define EPS 0.00001
#endif


static void parseComment(FILE *fp)
{
        // Read comment until newline.
        while (fgetc(fp) != (int)'\n');
        return ;
}

AnimationSequence::AnimationSequence()
{
    m_nKeyFrames = 0 ;
    m_firstKeyFrame = NULL ;
    m_lastKeyFrame = NULL ;
    m_nLegends = 0 ;
    m_legends = NULL ;
}

AnimationSequence::~AnimationSequence()
{
    Clear() ;
}

void AnimationSequence::Clear(void)
{
    DeleteKeyFrames() ;
    DeleteLegend() ;
}

int AnimationSequence::InsertKeyFrame(double time, int nparam, double *params)
{
    KeyFrame *kf = new KeyFrame(time, nparam, params) ;
    if( kf == NULL ) return 0 ;
    InsertKeyFrame(kf) ;
    return 1 ;
}

// Inserts a key frame in the sequence at the appropriate
// place with respect to the time field
void AnimationSequence::InsertKeyFrame(KeyFrame *kf_new)
{

    if( GetSize() == 0 ) 
    {
	m_firstKeyFrame = kf_new ;
	m_lastKeyFrame = kf_new ;
	m_nKeyFrames++ ;
    }
    else if( kf_new->m_time > m_lastKeyFrame->m_time ) 
    {
	// insert at the end
	m_lastKeyFrame->m_next = kf_new ;
	kf_new->m_previous = m_lastKeyFrame ;
	m_lastKeyFrame = kf_new ;
	m_nKeyFrames++ ;
    }
    else if( kf_new->m_time < m_firstKeyFrame->m_time )
    {
	// insert in the beginning
	m_firstKeyFrame->m_previous = kf_new ;
	kf_new->m_next = m_firstKeyFrame ;
	m_firstKeyFrame = kf_new ;
	m_nKeyFrames++ ;
    }
    else if( fabs(kf_new->m_time - m_lastKeyFrame->m_time) < EPS )
    {
	// replace the last one
	ReplaceKeyFrame(m_lastKeyFrame, kf_new) ;
    }
    else if( fabs(kf_new->m_time - m_firstKeyFrame->m_time) < EPS )
    {
	// replace the first one
	ReplaceKeyFrame(m_firstKeyFrame, kf_new) ;
    }
    else
    {
	KeyFrame *kf ;
	for( kf = m_firstKeyFrame ; ( (kf != NULL) && 
	       (kf->m_time < kf_new->m_time) ); kf = kf->m_next) ;
	// put it between kf->previous and kf but first
	// check to see if it should override ont of the two
	if( fabs(kf_new->m_time - kf->m_previous->m_time) < EPS )
	    ReplaceKeyFrame(kf->m_previous, kf_new) ;
	else if( fabs(kf_new->m_time - kf->m_time) < EPS )
	    ReplaceKeyFrame(kf, kf_new) ;
	else
	{
	    // put it between kf->m_previous and kf
	    kf_new->m_previous = kf->m_previous ;
	    kf_new->m_next = kf ;
	    (kf->m_previous)->m_next = kf_new ;
	    kf->m_previous = kf_new ;
	    m_nKeyFrames++ ;
	}
    }
}

int AnimationSequence::Save(char *fname)
{
    FILE *fp ;
    if( (fp = fopen(fname,"w")) == NULL )
    {
	danceTcl::OutputMessage("Cannot open file %s\n", fname) ;
	return -1 ;
    }
    int res = Save(fp) ;
    fclose(fp) ;
    return res ;
}

int AnimationSequence::Read(char *fname)
{
    FILE *fp ;
    if( (fp = fopen(fname,"r")) == NULL )
    {
	danceTcl::OutputMessage("Cannot open file %s\n", fname) ;
	return -1 ;
    }
    int res = Read(fp) ;
    fclose(fp) ;
    return res ;
}

int AnimationSequence::Save(FILE *fp)
{
    fprintf(fp, "AnimationSequence {\n") ;
    fprintf(fp, "\tlegend {\n") ;
    for( int i = 0 ; i < m_nLegends ; i++ )
	fprintf(fp, "\t\t%s %d\n", m_legends[i].name, m_legends[i].index) ;
    fprintf(fp, "\t}\n") ;
    fprintf(fp, "\tkeyFrames {\n") ;
    for( KeyFrame *kf = m_firstKeyFrame ; kf != NULL ; kf = kf->m_next )
	kf->Save(fp) ;
    fprintf(fp, "\t}\n") ;
    fprintf(fp, "}\n") ;
    return m_nKeyFrames ;
}

int AnimationSequence::Read(FILE *fp)
{
    char token[MAX_LINE] ;
    int result ;

    // clear anything that used to be there
    Clear() ;
    do {
	result = fscanf(fp,"%s", token) ;
	if( result > 0 )
	{
	    if( strcmp(token, "#") == 0 )
		parseComment(fp) ;
	    else if( strcmp(token, "keyFrames") == 0)
		ReadKeyFrames(fp) ;
	    else if( strcmp(token, "legend") == 0) 
	    {
		ReadLegend(fp) ;
	    }
	    else if( strcmp(token, "}") == 0 )
	    {
		danceTcl::OutputMessage("Animation sequence successfully read\n") ;
		return m_nKeyFrames ;
	    }
	}
	
    } while( !feof(fp) ) ;
    return 0 ;
}
		
int AnimationSequence::ReadKeyFrames(FILE *fp)
{
    int result ;
    char token[MAX_LINE] ;

    if( m_firstKeyFrame != NULL )
    {
	DeleteKeyFrames() ;
    }
    // get the opening bracket
    fscanf(fp, "%s", token) ;
    if( !(strcmp(token ,"{") == 0) )
    {
	danceTcl::OutputMessage("ERROR: ReadKeyFrames: missing '{'\n") ;
	return 0 ;
    }
    
    do {
	result = fscanf(fp, "%s", token) ;
	if( result > 0 )
	{
	    if( strcmp(token, "#") == 0 )
	    {
		parseComment(fp) ;
	    }
	    else if( strcmp(token, "keyFrame") == 0 )
	    {
		KeyFrame *kf = new KeyFrame ;
		if( kf == NULL )
		{
		    danceTcl::OutputMessage("ERROR: ReadKeyFrames: cannot allocate memory.\n") ;
		    return 0 ;
		}
		
		if( !(kf->Read(fp) > 0) )
		{
		    danceTcl::OutputMessage("Error reading key frame number %d\n", m_nKeyFrames) ;
		    danceTcl::OutputMessage("Animation sequence partially read\n") ;
		    delete kf ;
		    return m_nKeyFrames ;
		}
		
		InsertKeyFrame(kf) ;
	    }
	    else if( strcmp(token, "}") == 0 )
	    {
		danceTcl::OutputMessage("Read %d key frames.\n", m_nKeyFrames) ;
		return m_nKeyFrames ;
	    }
	}
	else
	{
	    danceTcl::OutputMessage("ERROR: ReadKeyFrames: Unexpected end of file!\n") ;
	    DeleteKeyFrames() ;
	    return m_nKeyFrames ;
	}
    } while( !feof(fp)) ;
    
    danceTcl::OutputMessage("ERROR: unexpectd end of file.\n") ;
    DeleteKeyFrames() ;
    return  m_nKeyFrames ;
}

void AnimationSequence::DeleteKeyFrames(void)
{
    KeyFrame *prev ;
    if( m_firstKeyFrame == NULL ) return ;
    for( KeyFrame *k = m_firstKeyFrame ; k != NULL ; k = k->m_next )
    {
	if( k->m_previous != NULL )
	    delete k->m_previous ;
	prev = k ;
    }
    if( prev != NULL )
	delete prev ;

    m_firstKeyFrame = NULL ;
    m_lastKeyFrame = NULL ;
    m_nKeyFrames = 0 ;
}

int AnimationSequence::ReadLegend(FILE *fp)
{

    int done = FALSE, expectingIndex = FALSE ;
    int result ;
    char token[MAX_LINE] ;
    
    int index[MAX_NUM_PARAM] ;
    char legend[MAX_NUM_PARAM][MAX_LINE] ;

    // clear previous legends
    if( m_legends != NULL )
	DeleteLegend() ;

    
    // get the opening bracket
    fscanf(fp, "%s", token) ;
    if( !(strcmp(token ,"{") == 0) )
    {
	danceTcl::OutputMessage("ERROR: ReadLegend: missing '{'\n") ;
	return 0 ;
    }
    do {
	result = fscanf(fp, "%s", token) ;
	if( result > 0 )
	{
	    if( strcmp(token, "#") == 0 )
	    {
		parseComment(fp) ;
	    }
	    else if( strcmp(token, "}") == 0 )
	    {
		done = TRUE ;
	    }
	    else
	    {
		if( expectingIndex == FALSE )
		{
		    strcpy(legend[m_nLegends], token) ;
		    expectingIndex = TRUE ;
		}
		else
		{
		    index[m_nLegends] = atoi(token) ;
		    m_nLegends++ ;
		    expectingIndex = FALSE ;
		}
	    }
	}
    } while(( !feof(fp)) && (done == FALSE)) ;

    if( done == FALSE )
    {
	danceTcl::OutputMessage("ERROR: ReadLegend: Unexpected end of file.\n") ;
	DeleteLegend() ;
    }

    if( m_nLegends > 0 )
    {
	m_legends = new Legend [m_nLegends] ;
	if( m_legends == NULL )
	{
	    danceTcl::OutputMessage("ERROR: no more memory!\n") ;
	    m_nLegends = 0 ;
	}
	for( int i = 0 ; i < m_nLegends ; i++ )
	{
	    strcpy(m_legends[i].name, legend[i]) ;
	    m_legends[i].index = index[i] ;
	}
	danceTcl::OutputMessage("Read %d legends.\n", m_nLegends) ;
    }

    return m_nLegends ;

}
	    
void AnimationSequence::DeleteLegend(void)
{
    if( m_legends != NULL )
    {
	delete [] m_legends ;
	m_legends = NULL ;
    }
    m_nLegends = 0 ;
}


void AnimationSequence::DeleteKeyFrame(int index)
{
    int count = 0 ;

    for( KeyFrame *kf = m_firstKeyFrame ; kf != NULL ; kf = kf->m_next)
	if( count == index )
	{
	    DeleteKeyFrame(kf) ;
	    return ;
	}
}

void AnimationSequence::DeleteKeyFrame(KeyFrame *kfdel)
{
    for( KeyFrame *kf = m_firstKeyFrame ; kf != NULL ; kf = kf->m_next)
    {
	if( kf == kfdel )
	{
	    if( kf->m_previous != NULL ) (kf->m_previous)->m_next = kf->m_next ;
	    if( kf->m_next != NULL ) (kf->m_next)->m_previous = kf->m_previous ;

	    if( kf == m_firstKeyFrame )
	    {
		if( m_lastKeyFrame == m_firstKeyFrame )
		{
		    // all null
		    m_lastKeyFrame = NULL ;
		    m_firstKeyFrame = NULL ;
		}
		else
		{
		    // delete the head
		    (m_firstKeyFrame->m_next)->m_previous = NULL ;
		    m_firstKeyFrame = m_firstKeyFrame->m_next ;
		}
	    }
	    else if( kf == m_lastKeyFrame )
	    {
		(m_lastKeyFrame->m_previous)->m_next = NULL ;
		m_lastKeyFrame = m_lastKeyFrame->m_previous ;
	    }
	    delete kf ;
	    m_nKeyFrames-- ;
	    return ;
	}
    }
}

// replaces the kf_old with kf_new in the sequence and deletes kf_old
void AnimationSequence::ReplaceKeyFrame(KeyFrame *kf_old, KeyFrame *kf_new)
{
    if( kf_old == NULL ) return ;
    DeleteKeyFrame(kf_old) ;
    InsertKeyFrame(kf_new) ;
}

double AnimationSequence::GetStartTime(void)
{
    if( m_firstKeyFrame != NULL )
	return m_firstKeyFrame->m_time ;
    else
	return -1 ;
}


double AnimationSequence::GetEndTime(void)
{
    if( m_lastKeyFrame != NULL )
	return m_lastKeyFrame->m_time ;
    else
	return -1 ;
}


// Fills in a preallocated array (params) as follows:
//  If there is a key frame at 'time' the parameters of
// that keyframe are returned. If not linear interpolations
// between the closest keyframes is the answer unless no interpolation
// is desired in which case the fist key frame is returned.
// If the time is out of bounds 0 is returned otherwise
// the number of parameters are returned.
int AnimationSequence::GetKeyFrame(double time, double *params, int interpolation)
{
    // find the key frames and interpolate if needed
    if( GetSize() == 0 ) 
    {
	return 0 ;
    }
    else if( (time > m_lastKeyFrame->m_time ) && 
	     (time < m_firstKeyFrame->m_time ))
    {
	return 0 ;
    }
    else if( fabs(time - m_lastKeyFrame->m_time) < EPS )
    {
	// return the last one
	memcpy(params, m_lastKeyFrame->m_param, 
	       sizeof(double)*m_lastKeyFrame->m_nparam) ;
    }
    else if( fabs(time - m_firstKeyFrame->m_time) < EPS )
    {
	// return the first one
	memcpy(params, m_firstKeyFrame->m_param, 
	       sizeof(double)*m_firstKeyFrame->m_nparam) ;
    }
    else
    {
	KeyFrame *kf ;
	for( kf = m_firstKeyFrame ; ( (kf != NULL) && 
				      (kf->m_time < time) ); kf = kf->m_next) ;
	// somewhere between kf->previous and kf but first
	// check to see if it should override one of the two
	if( fabs(time - kf->m_previous->m_time) < EPS )
	    memcpy(params, kf->m_previous->m_param,
		   sizeof(double)*kf->m_previous->m_nparam) ;
	else if( fabs(time - kf->m_time) < EPS )
	    memcpy(params, kf->m_param, sizeof(double)*kf->m_nparam) ;
	else
	{
	    if( interpolation == TRUE ) 
		InterpolateKeyFrames(kf->m_previous, kf, time, params) ;
	    else
			memcpy(params, kf->m_previous->m_param,
			 sizeof(double)*kf->m_previous->m_nparam) ;
	}
    }
    return m_firstKeyFrame->m_nparam ;
}


KeyFrame *AnimationSequence::GetKeyFrame(double time)
{
 
    KeyFrame *kf ;

    for( kf = m_firstKeyFrame ; kf != m_lastKeyFrame ; kf = kf->m_next)
	if( fabs(time - kf->m_time) < EPS ) break ;
    return kf ;
   
}

void AnimationSequence::InterpolateKeyFrames(KeyFrame *kf1, KeyFrame *kf2, double time,
					     double *paramInt)
{
    if( (kf2->m_time - kf1->m_time ) <= (double) 0.0)
    {
	danceTcl::OutputMessage("ERROR: interpolation of key frames that are at the same time"
	       " or at the wrong order!\n") ;
	return ;
    }
    double a = (time - kf1->m_time ) / (kf2->m_time - kf1->m_time) ;
    for( int i = 0 ; i < kf1->m_nparam ; i++ )
    {
	paramInt[i] = kf1->m_param[i]*(1 - a) + a*kf2->m_param[i] ;
    }
    return ;
}

void AnimationSequence::DeleteKeyFrame(double time)
{
    KeyFrame *kf = GetKeyFrame(time) ;
    if( kf == NULL ) 
    {
	danceTcl::OutputMessage("No key frame at time %lf\n", time) ;
	return ;
    }
    DeleteKeyFrame(kf) ;
}
