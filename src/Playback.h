#ifndef	PLAYBACK_H
#define	 PLAYBACK_H

#define	MAX_DOFS 50

class KFrame {
public:
   KFrame() ;
  ~KFrame() ;
  char (*line)[MAX_LINE] ;
  int nlines ;
} ;

class Playback {
public:
  Playback() ;
  ~Playback() ;
  int setCurrent(int n)	;
  void close(void) ;
  int load(char	*fn) ;
  int loadInMemory(char	*fn) ;

  char fname[MAX_LINE] ;
  FILE *pbfp ;
  int isCached ;
  KFrame *frame	;
  int nframes ;
  int current ;

} ;


#endif
