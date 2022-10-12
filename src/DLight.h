#ifndef	_DLIGHT_H
#define	_DLIGHT_H

#include "DanceObject.h"

#include <tcl.h>
#include <GL/gl.h>

/** Types of lights */
typedef enum LightType {
	ePoint,
	eDirectional,
	eSpotLight
};

class DLLENTRY DLight: public DanceObject {
private:
  LightType m_Type;
  short m_LightsOn;
  GLenum m_ID;

  GLfloat m_Position[4];
  GLfloat m_Diffuse[4];
  GLfloat m_Specular[4];
  GLfloat m_Ambient[4];



public:
  void print(FILE *fptr);

  DLight(Tcl_Interp *interp, char *name,	int argc, char **argv);
  ~DLight();

  void GetPosition(GLfloat p[4]) { memcpy(&p[0],&m_Position[0], 4*sizeof(GLfloat)) ;} ;

  int IsOn(void) { return m_LightsOn ;} ;
  void Interact(Event *event);
  void output(int mode = 0);
  int Command(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv);
};

#endif
