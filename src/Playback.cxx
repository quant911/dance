#include <stdlib.h>
#include "defs.h"
#include "Playback.h"


KFrame::KFrame()
{
    nlines = 0 ;
    line = NULL	;
}

KFrame::~KFrame()
{
    if(	line !=	NULL)
    {
	free(line) ;
	line = NULL ;
    }
}


Playback::Playback()
{
    pbfp = NULL	;
    fname[0] = '\0' ;
    isCached = FALSE ;
    frame = NULL ;
    nframes = 0	;
    current = -1 ;
}



Playback::~Playback()
{
    this->close() ;
}

void Playback::close(void)
{
    if(	pbfp !=	NULL )
	fclose(pbfp) ;
    pbfp = NULL	;
    isCached = FALSE ;
    fname[0] = '0' ;
    if(	frame != NULL )
	delete [] frame	;
    frame = NULL ;
    nframes = 0	;
    current = -1 ;
}

int Playback::load(char	*fn)
{
    this->close() ;
    if((pbfp = fopen(fn,"r")) == NULL )
    {
	fprintf(stderr,"Cannot read file %s\n",	fn) ;
	return TCL_ERROR ;
    }
    strcpy(fname,fn) ;

    return TCL_OK ;
}

// load	the file into memory
int Playback::loadInMemory(char	*fn)
{
    char l[MAX_LINE] ;
    int	i, nj,nf ;
    char (*oline)[MAX_LINE] = NULL ;

    // open file and store the pointer
    this->close() ;
    if((pbfp = fopen(fn,"r")) == NULL )
    {
	fprintf(stderr,"Cannot read file %s\n",	fn) ;
	return TCL_ERROR ;
    }

    printf("Loading file %s in memory\n", fn) ;

    // find how	many frames are	in the file
    nframes = 0	;
    while(!feof(pbfp))
    {
	fgets(l,MAX_LINE,pbfp) ;
	if( l[0] == 'e')
	    nframes++ ;
    }
    // rewind by closing and opening again
    fclose(pbfp) ;
    if((pbfp = fopen(fn,"r")) == NULL )
    {
	fprintf(stderr,"Cannot read file %s\n",	fn) ;
	return TCL_ERROR ;
    }

    // allocate	the frames
    frame = new	KFrame[nframes]	;
    if(	frame == NULL )
    {
	fprintf(stderr,"Cannot allocate	frames\n") ;
	return TCL_ERROR ;
    }

    for( nf = 0	; nf < nframes ; nf++ )
    {
	fgets(l,MAX_LINE,pbfp) ;
	nj =0 ;
	while( l[0] != 'e')
	{
	    nj++ ;
	    if(	nj != 1	)
	    {
		if( oline != NULL )
		{
		    free(oline)	;
		    oline = NULL ;
		}
		//oline	= new (char (*)[MAX_LINE])[nj-1] ;
		oline =	(char (*)[MAX_LINE]) malloc((nj-1)*sizeof(char)*MAX_LINE) ;
		if( oline == NULL)
		{
		    fprintf(stderr,"No more memory\n") ;
		    return TCL_ERROR ;
		}
		for( i = 0 ; i < (nj-1)	; i++)
		    strcpy(oline[i],frame[nf].line[i]) ;
	    }
	    if(	frame[nf].line != NULL )
	    {
		free( frame[nf].line ) ;
		frame[nf].line = NULL ;
	    }
	    //frame[nf].line = new (char (*)[MAX_LINE])	[nj] ;
	    frame[nf].line = (char (*)[MAX_LINE]) malloc(nj*sizeof(char)*MAX_LINE) ;
	    if(	frame[nf].line == NULL )
	    {
		    fprintf(stderr,"No more memory\n") ;
		    return TCL_ERROR ;
	    }
	    if(	nj != 1)
		// restore the previously read lines
		for( i = 0 ; i < nj-1 ;	i++)
		    strcpy(frame[nf].line[i],oline[i]) ;
	    // copy next line
	    // printf("Line read = |%s|\n", l) ;
	    strcpy(frame[nf].line[nj-1],l) ;
	    //printf("Line copied = |%s|\n",frame[nf].line[nj-1] ) ;
	    frame[nf].nlines = nj ;
	    fgets(l,MAX_LINE,pbfp) ;
	} // while
	frame[nf].nlines = nj ;
	if( oline != NULL )
	{
	    free(oline)	;
	    oline = NULL ;
	}
	//for( i = 0 ; i < frame[nf].nlines ; i++ )
	//   printf("%s",  frame[nf].line[i]) ;
    }

    strcpy(fname,fn) ; // save the file	name
    isCached = TRUE ;
    current = 0	;

    printf("File loaded	successfuly. Read %d frames\n",	nframes) ;
    // for( int	j = 0 ;	j < nf ; j++ )
    //	  for( i = 0 ; i < frame[j].nlines ; i++ )
    //	  printf("%s",	frame[j].line[i]) ;

    return TCL_OK ;
}

int Playback::setCurrent(int n)
{
    if(	(n < 0)	|| (n >= nframes))
    {
	fprintf(stderr,"Index out of bounds!\n") ;
	return TCL_ERROR ;
    }
    else
    {
	current	= n ;
	return TCL_OK ;
    }
}


