#include <stdlib.h>

#include "DLight.h"
#include "dance.h"
#include "danceTcl.h"
#include "ViewManager.h"
#include "DView.h"

#define	LDISPLAY_WIRE	 1

static int *gLightArray = NULL;

DLight::DLight(Tcl_Interp	*interp, char *name, int argc, char **argv)
{
	// Determine the maximum number of lights available.
	int maxLights; glGetIntegerv(GL_MAX_LIGHTS,&maxLights);

	// Initialize light array.
	if (gLightArray == NULL)	{
		gLightArray = new int[maxLights];
		for (int i=0; i	< maxLights; i++) gLightArray[i]	= 0;
	}


	// Find position of first non-defined light.
	int i;
	for (i=0; i < maxLights; i++)
		if (gLightArray[i] == 0) break;


	if (i == maxLights) {
		Tcl_AppendResult(interp,"WARNING: Reusing Light	0 as all lights	are already in use.\n",(char *)NULL);
		m_ID = (GLenum)GL_LIGHT0;
		return;
	}
	else {
	   m_ID =	(GLenum)(GL_LIGHT0 + i);
	   gLightArray[i] = 1;
	}

	setType("light");
	setBaseType("light");

	m_Type = ePoint;
	m_LightsOn = 1;

	GLfloat value[4];



	// Set default values based on OpenGL standard.
	if (m_ID == GL_LIGHT0) {
		m_Diffuse[0] = m_Diffuse[1] = m_Diffuse[2] = m_Diffuse[3] = 1.0;
		m_Specular[0] = m_Specular[1] = m_Specular[2] = m_Specular[3] = 1.0;
	}
	else {
		m_Diffuse[0] = m_Diffuse[1] = m_Diffuse[2] = 0.0; 
		m_Diffuse[3] = 1.0;
		m_Specular[0] = m_Specular[1] = m_Specular[2] = 0.0;
		m_Specular[3] = 1.0;
	}
	m_Ambient[0] = m_Ambient[1] = m_Ambient[2] = 0.0; m_Ambient[3] = 1.0;
	m_Position[0] = m_Position[1] = 0.0; m_Position[2] = 1.0; m_Position[3] = 0.0;

	// Override light parameters if arguments provided.
	if( argc == 5 )
	{
		value[0] = (float)atof(argv[1]);
		value[1] = (float)atof(argv[2]);
		value[2] = (float)atof(argv[3]);
		value[3] = (float)atof(argv[4]);
	
		if (strcmp(argv[0],"position") == 0)
			memcpy(m_Position,value,4*sizeof(GLfloat));
		else if (strcmp(argv[0],"diffuse") == 0)
			memcpy(m_Diffuse,value,4*sizeof(GLfloat));
		else if (strcmp(argv[0],"specular") == 0)
			memcpy(m_Specular,value,4*sizeof(GLfloat));
		else if (strcmp(argv[0],"ambient") == 0)
			memcpy(m_Ambient,value,4*sizeof(GLfloat));
	}
}

DLight::~DLight(void)
{
	// Disable light for all views.
	for (int i = 0;	i < dance::AllViews->size(); i++) {
		DView *view = (DView *)dance::AllViews->get(i);
		view->set();
		glDisable(m_ID);
	}
	gLightArray[(m_ID-GL_LIGHT0)] = 0;
}

int DLight::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    if( DanceObject::Command(clientData, interp, argc, argv) == TCL_OK ) return TCL_OK ;
   
	if( argc == 0) 
	{
		danceTcl::OutputMessage("Expected {position x y z w}|"
			     "diffuse|ambient|specular r g b a\n") ;
	    return TCL_ERROR ;
	}

	char resultString[256];
	if (strcmp(argv[0],"lighttype") == 0) {
		if (m_Type == ePoint)
			strcpy(resultString,"Point");
		else
			strcpy(resultString,"Invalid");
		Tcl_AppendResult(interp,resultString, NULL);
		return TCL_OK;
	}
	else if (strcmp(argv[0],"-visible") == 0) {
		if (argc > 1)
			m_LightsOn = atoi(argv[1]);
		if (dance::FocusWindow)
			dance::FocusWindow->postRedisplay();
		return TCL_OK;
	}

	GLfloat *parm;
	if (strcmp(argv[0],"position") == 0)
		parm = m_Position;
	else if	(strcmp(argv[0],"diffuse") == 0)
		parm = m_Diffuse;
	else if	(strcmp(argv[0],"ambient") == 0)
		parm = m_Ambient; 
	else if	(strcmp(argv[0],"specular") == 0)
	    parm = m_Specular;

	GLfloat	value[4];
	if (argc == 1) {
		memcpy(value,parm,4*sizeof(GLfloat));
		sprintf(resultString,"%f %f %f %f\n",value[0],value[1],value[2],value[3]);
		Tcl_AppendResult(interp,resultString,NULL);
		return TCL_OK;
	}
	if( argc != 5 )
	{
		danceTcl::OutputMessage("Usage: light <name> "
			"position|diffuse|ambient|specular a1 a2 a3 a4") ;
		return TCL_ERROR ;
	}
	value[0] = (GLfloat) atof(argv[1]);
	value[1] = (GLfloat) atof(argv[2]);
	value[2] = (GLfloat) atof(argv[3]);
	value[3] = (GLfloat) atof(argv[4]);
	memcpy(parm,value,4*sizeof(GLfloat));

	return TCL_OK;
}

void DLight::Interact(Event *event)
{
	// Get the depth value of the window of	the current location.
	GLdouble win[3];
	GLdouble wpos[3];
	wpos[0]	= (GLdouble)m_Position[0];
	wpos[1]	= (GLdouble)m_Position[1];
	wpos[2]	= (GLdouble)m_Position[2];
	event->Window->getWindowCoords(wpos,(double *)win);
	event->Window->getWorldCoords(wpos,event->winX,event->winY,win[2]);
	m_Position[0] = (GLfloat)wpos[0];
	m_Position[1] = (GLfloat)wpos[1];
	m_Position[2] = (GLfloat)wpos[2];
}

void DLight::output(int mode)
{
	glDisable(GL_LIGHTING);
	glColor4fv(m_Diffuse);

	// Display light icon.
	if (m_LightsOn) {
		glPushMatrix();
		glTranslatef(m_Position[0],m_Position[1],m_Position[2]);

		double radius = 0.02 * dance::FocusWindow->getFrustumWidth(0.0);
		glutSolidSphere(radius, 8, 6);
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glEnable(m_ID);
	glLightfv(m_ID, GL_POSITION, m_Position);
	glLightfv(m_ID, GL_DIFFUSE, m_Diffuse);
	glLightfv(m_ID, GL_SPECULAR, m_Specular);
	glLightfv(m_ID, GL_AMBIENT, m_Ambient);
	glShadeModel(GL_SMOOTH);
}

void DLight::print(FILE * fptr)
{
	fprintf(fptr,"instance light %s position %f %f %f %f\n",
		getName(),
		m_Position[0],m_Position[1],m_Position[2],m_Position[3]);
	fprintf(fptr,"light %s diffuse %f %f %f %f\n",
		getName(),
		m_Diffuse[0],m_Diffuse[1],m_Diffuse[2],m_Diffuse[3]);
	fprintf(fptr,"light %s ambient %f %f %f %f\n",
		getName(),
		m_Ambient[0],m_Ambient[1],m_Ambient[2],m_Ambient[3]);
	fprintf(fptr,"light %s specular %f %f %f %f\n",
		getName(),
		m_Specular[0],m_Specular[1],m_Specular[2],m_Specular[3]);
	
	fprintf(fptr,"\n");

}
