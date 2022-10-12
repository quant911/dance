
typedef	GLubyte	GlubyteVector[3] ;

#ifdef WIN32
#ifdef _EXPORTING_GR
#define DLLENTRY_GR __declspec(dllexport)
#else
#define DLLENTRY_GR __declspec(dllimport)
#endif
#else
#define DLLENTRY_GR
#endif

class DLLENTRY_GR Texture {
public:
  Texture() ;
  ~Texture() ;
  int loadPPM(FILE *fp,int x, int	y) ;
  int getHeaderPPM(FILE *fp, int *x, int *y) ;
  int loadTexture(char *fname) ;
  char fname[256] ;
  int m_x;
  int m_y	;
  GLubyte	*im ;
  GLuint m_texName ;
} ;


