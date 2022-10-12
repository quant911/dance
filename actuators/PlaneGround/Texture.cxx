#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tcl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "dance.h"
#include "danceTcl.h"
#include "Texture.h"


GLuint g_TexName ;

Texture::Texture()
{
    m_x = 0 ;
    m_y = 0 ;
    im = NULL ;
}


Texture::~Texture()
{
    if(im != NULL)
    {
	free(im) ;
	im = NULL ;
    }
}

int Texture::loadTexture(char *fname)
{
    FILE *fp ;
  
    if(im != NULL)
    {
	free(im) ;
	im = NULL ;
    }


    fp = fopen(fname,"r") ;
    if(	fp == NULL )
    {
	danceTcl::OutputMessage("loadTexture: Cannot open file %s.", fname) ;
	return TCL_ERROR;
    }

    // read the header
    if( getHeaderPPM(fp, &m_x, &m_y) == TCL_ERROR )
    {
	danceTcl::OutputMessage("loadTexture: Error reading file.") ;
	return TCL_ERROR ;
    }
    
    if( m_x * m_y > 10000000 )
    {
	danceTcl::OutputMessage("loadTexture: File too big.") ;
	return TCL_ERROR ;
    }

        
    // alocate image
    if((im = (GLubyte *) malloc(sizeof(GLubyte *)*m_x*m_y*3)) == NULL)
    {
	danceTcl::OutputMessage("Not enough memory!\n") ;
	return TCL_ERROR ;
    }
    
    // read the image
    if(	loadPPM(fp, m_x, m_y) == TCL_ERROR )
    {
	danceTcl::OutputMessage("ERROR: texture was not loaded.\n") ;
	return TCL_ERROR ;
    }

    /**
    for(  i = 0	; i < x	; i++ )
	for(  j	= 0 ; j	< y; j++)
	    printf("%d %d %d\n", im[i][j][0],im[i][j][1],
		   im[i][j][2])	;
		   **/
 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1) ;

#if WIN32
    glGenTextures(1, &m_texName) ;
    glBindTexture(GL_TEXTURE_2D, m_texName) ;
#endif
    glTexImage2D(GL_TEXTURE_2D,	0, 3, m_x, m_y,0,GL_RGB, GL_UNSIGNED_BYTE,
		 im) ;

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) ;
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST) ;
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) ;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL) ;

    g_TexName = m_texName ;
    fclose(fp) ;
    return TCL_OK ;
}


int Texture::getHeaderPPM(FILE *fp, int *x, int *y)
{ 
    char s[256] ;
    s[0] = '\0' ;
    fgets(s,100,fp) ;
    if( strncmp(s, "P6", 2) != 0 )
    {
	danceTcl::OutputMessage("Texture: wrong format must be P6.") ;
	return TCL_ERROR;
    }
    fgets(s,100,fp);
    if( sscanf(s, "%d %d", x, y) != 2 )
    {
	danceTcl::OutputMessage("Texture: wrong format expected <x> <y>.") ;
	return TCL_ERROR;
    }
	fgets(s,100,fp);
	int maxCol ;
    if( sscanf(s, "%d", &maxCol) != 1 )
    {
	danceTcl::OutputMessage("Texture: wrong format expected <maxCol>.") ;
	return TCL_ERROR;
    }
    return TCL_OK ;
}    

// Header must be read already
int Texture::loadPPM(FILE *fp, int x, int y)
{
    int	i,j;
 
      /**
    for( i = 0 ; i < x ; i++ )
	for( j = 0 ; j < y ; j++ )
	{
	    //	    c =	((((i&0x8)==0)^((j&0x8))==0))*255 ;
	    c =	(int) ((float) ((x - i)	 / (float) x ) * 255) ;
	    //	    c =	255 ;
	    im[i][j][0]	= (GLubyte) c ;
	    im[i][j][1]	= (GLubyte) c ;
	    im[i][j][2]	= (GLubyte) c ;
	}
    **/
	int count = 0 ;
    for( i = 0 ; i < x ; i++ )
	for( j = 0 ; j < y; j++)
	{
	   if(feof(fp))	
	   {
	       danceTcl::OutputMessage("loadPPM: unexpected end of file.") ;
	       return TCL_ERROR ;
	   }
	   else
	   {
			fread((void *) &im[count] , sizeof(GLubyte), 3, fp) ;
			count += 3 ;
	   }
	}


    danceTcl::OutputMessage("Texture file read properly.") ;
    return TCL_OK ;
}






