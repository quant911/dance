#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "KeyFrame.h"

#ifdef WIN32
#ifndef printf
#define print danceTcl::OutputeResult
#endif
#endif

#ifndef MAX_LINE
#define MAX_LINE 256
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static void parseComment(FILE *fp)
{
        // Read comment until newline.
        while (fgetc(fp) != (int)'\n');
        return ;
}


KeyFrame::KeyFrame()
{
    m_nparam = 0 ;
    m_param = NULL ;
    m_next =  NULL ;
    m_previous = NULL ;
    m_time = 0 ;
}

KeyFrame::KeyFrame(double time, int n, double *p)
{
    m_nparam = n ;
    m_param = new double [n] ;
    if( m_param == NULL )
    {
	printf("Cannot allocate key frame params!\n") ;
	return ;
    }

    for( int i = 0 ; i < n ; i++ )
    {
	m_param[i] = p[i] ;
    }
    m_next = NULL ;
    m_previous = NULL ;
    m_time = time ;
}

KeyFrame::~KeyFrame()
{
    if( m_param != NULL ) delete [] m_param ;
}

void KeyFrame::Save(FILE *fp)
{
    fprintf(fp, "\t\tkeyFrame {") ;
    fprintf(fp, " time %lf", m_time) ;
    for( int i = 0 ; i < m_nparam ; i++ )
    {
	fprintf(fp, " %lf", m_param[i]) ;
    }
    fprintf(fp, " }\n") ;
}

int KeyFrame::Read(FILE *fp)
{
    char token[MAX_LINE];
    int result ;
    double param[MAX_NUM_PARAM] ;
    int done = FALSE ;
    int timeRead = FALSE ;

    // get the opening bracket
    fscanf(fp,"%s", token) ;
    if( strcmp(token, "{") != 0 )
    {
	printf("ERROR: KeyFrame Read: expected '{'\n'") ;
	return 0 ;
    }
    m_nparam = 0 ;
    do {
	result = fscanf(fp,"%s",token);
	if( result > 0 )
	{
	    if( strcmp(token, "#") == 0 )
		parseComment(fp) ;
	    else if( strcmp(token, "}") == 0 )
	    {
		done = TRUE ;
	    }
	    else if( strcmp(token, "time") == 0 )
	    {
		result =  fscanf(fp,"%s",token);
		if( result > 0 )
		    m_time = atof(token) ;
		{
		    timeRead = TRUE ;
		}
	    }
	    else		// read param
	    {
		    param[m_nparam] = atof(token) ;
		    m_nparam++ ;
	    }
	}
	else
	{
	    printf("Unexpected end of file!\n") ;
	}

    } while ((!feof(fp)) && (done == FALSE)) ;

    if( feof(fp) )
    {
	printf("ERROR: Key frame not read properly.\n") ;
	m_nparam = 0 ;
    }
    
    if( timeRead == FALSE ) 
    {
	printf("ERROR: time of keyframe not read properly.\n") ;
    }
    if( m_nparam > 0 )
    {
	m_param = new double [m_nparam] ;
	if( m_param == NULL )
	{
	    printf("ERROR: no more memory!\n") ;
	    m_nparam = 0 ;
	}
	
	// copy the param and index
	for( int i = 0 ; i < m_nparam ; i++ )
	{
	    m_param[i] = param[i] ;
	}
    }

    return m_nparam ;

}
    




