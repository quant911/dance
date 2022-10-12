/************************************************************************
      ---------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project


 ***************************************************************
 ******General License Agreement and Lack of Warranty ***********
 ****************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/

#include "defs.h"
#include <stdlib.h>
#include "dance.h"
#include "danceTcl.h"
#include "DView.h"
#include "ViewManager.h"
#include "Quaternion.h"
#include "BoundingBox.h"

enum ViewTypes {
	VIEW_TOP,
	VIEW_FRONT,
	VIEW_RIGHT,
	VIEW_PERSP
};

int DView::MasterWindow = -1;

// DView:
//
DView::DView()
{
	WindowID = -1;
	Lights = 0;
	Solids = 0;
	Shadows	= 0;
	BackgroundColor[0] = 1.0;
	BackgroundColor[1] = 1.0;
	BackgroundColor[2] = 1.0;
	BackgroundColor[3] = 1.0;

	// Initialize view data	members.
	Arcball	= NULL;
	Modelview = new	double[16];
	Projection = new double[16];
	setBaseType("view");
	setType("view");

	m_FrameNumber = 1 ;
	strcpy(m_DumpDirectory, ".") ;
	m_HalfSizeCom[0] = '\0' ;
	strcpy(m_DumpFileName, "f") ;
	m_IsDumped = FALSE ;
}

// DView:
//	NOTE: Cannot call a constructor	within a constructor.
//
DView::DView(Tcl_Interp *interp, char *name, int argc, char **argv)
{
	WindowID = -1;
	Lights = 0;
	Solids = 0;
	Shadows	= 0;
	BackgroundColor[0] = 0.0;
	BackgroundColor[1] = 0.0;
	BackgroundColor[2] = 0.0;
	BackgroundColor[3] = 1.0;

	// Initialize view data	members.
	Arcball	= NULL;
	Modelview = new	double[16];
	Projection = new double[16];
	setBaseType("view");
	setType("view");

	if (argc != 5) {
		danceTcl::OutputMessage("WARNING: view <name> "
					" <persp|top|front|right> "
					"<x> <y> <width> <height>\n"
					"Window created but not defined.");
		return;
	}
	
	m_FrameNumber = 1 ;
	strcpy(m_DumpDirectory, ".") ;
	m_HalfSizeCom[0] = '\0' ;
	strcpy(m_DumpFileName, "f") ;
	m_IsDumped = FALSE ;

	int x =	atoi(argv[1]);
	int y =	atoi(argv[2]);
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	create(name, argv[0], x, y, width, height);
}

// ~View:
//	Destructor for View
DView::~DView()
{
	if (Arcball) delete Arcball;
	if (Modelview) delete [] Modelview;
	if (Projection)	delete [] Projection;

	// disable all Callbacks
	if (WindowID !=	-1) {
	   glutSetWindow(WindowID);
	   glutMotionFunc(NULL);
	   glutPassiveMotionFunc(NULL);
	   glutMouseFunc(NULL);
	   glutKeyboardFunc(NULL);
	   glutHideWindow();

	   glFinish(); // Flush out any OpenGL calls in pipe.

	   // Do not remove this callback or Tcl interface will	freeze.
	   // TODO: Put	Tcl checking outside Idle function, to remove this
	   // dependency.
	   // glutIdleFunc(NULL);

	   // Need MasterWindow	for shared contexts and	glutMainLoop
	   if (WindowID	!= MasterWindow) 
	       glutDestroyWindow(WindowID);
	   
	}
}

// adjustArcballCamera:
//	Adjust arcball associated with the view	by using the given coords.
//	NOTE: This only works for the perspective camera view.
//
//	coords:	Coordinates for	arcball.
//
void DView::adjustArcballCamera(HVect coords)
{
	if (Perspective) {
		Ball_Mouse(Arcball,coords);
		Ball_Update(Arcball);
	}
}

// adjustArcballCircle:
//	Adjusts	centre and radius of Arcball circle
//
//	x,y: centre of ball
//	radius:	radius of ball
//
void DView::adjustArcballCircle(double x, double	y, double radius)
{
	HVect coords; coords.x = x; coords.y = y;
	Ball_Place(Arcball, coords, radius);
}

//
// AttachCamera:
//	Attach cameras to quadview. Must create	windows	first.
//	Builds the viewing and projection matrices.
//
void DView::AttachCamera(BoundingBox *box)
{
	if (box == NULL) 
		setCamera(SCALE_FOR_BB,-1.0,-1.0,-1.0,1.0,1.0,1.0);
	else 
		setCamera(SCALE_FOR_BB,box->xMin,box->yMin,box->zMin,
							   box->xMax,box->yMax,box->zMax);
	postRedisplay();
}

// attachMenu:
//	Attaches the given menu	to the View
//
//	  menu:	Menu ID, using GLUT identifiers
//
void DView::attachMenu(int menu)
{
	glutSetMenu(menu);

	// Attach this menu to each of the four	views in the quadview.
	glutSetWindow(WindowID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// beginInteraction:
//	Begins an interactive session with the window.
//
//	mode:	Type of	edit mode
//
void DView::beginInteraction(int	mode)
{
	switch(mode) {
	   case	camera_arcball:
		Ball_BeginDrag(Arcball);
	   break;
	}
}

// usage:
//
void DView::usage(Tcl_Interp *interp)
{
	danceTcl::OutputMessage("USAGE:	view <name>\n",
		"create	persp|top|front|right <x> <y> <width> <height>\n",
		"|pan <x> <y>\n",
		"|target <x> <y> <z>\n",
		"|arcball <x> <y>\n",
		"|distance <dist>\n",
		"|clipBounds <left> <right> <bottom> <top>\n",
		"|dump\n",
		"|refresh\n",
		"|background <r> <g> <b> <a> >\n",
		"|lights on|off\n",
		"|-postscript <filename>\n",
		"|shadows on|off\n",
		"|solids on|off\n",
		"|projection persp|ortho <left> <right> <bottom> <top> <near> <far>\n");
}

// Command:
//
int DView::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
	char resultString[256];

	if (argc == 0) {
		usage(interp);
		return TCL_ERROR;
	}
	if (strcmp(argv[0],"background") == 0) {
		if (argc == 1) { // retrieve background colour
			float color[4];
			getBackgroundColor(color);
			sprintf(resultString,"%f",color[0]);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",color[1]);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",color[2]);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",color[3]);
			Tcl_AppendElement(interp,resultString);
			return TCL_OK;
		}
		else if (argc != 5) {
		   danceTcl::OutputMessage("background <r> <g> <b> <a>\n");
		   return(TCL_ERROR);
		}
		setBackgroundColor(atof(argv[1]),atof(argv[2]),
				   atof(argv[3]),atof(argv[4]));
		postRedisplay();
		return TCL_OK;
	}
	else if (strcmp(argv[0],"projtype") == 0) {
		if (argc == 1) {
			if (ProjectionType == VIEW_PERSP) strcpy(resultString,"persp");
			if (ProjectionType == VIEW_TOP) strcpy(resultString,"top");
			if (ProjectionType == VIEW_RIGHT) strcpy(resultString,"right");
			if (ProjectionType == VIEW_FRONT) strcpy(resultString,"front");
			danceTcl::OutputResult("%s", resultString);
		}
		else {
			Perspective = 0;
			if (strcmp(argv[1],"persp") == 0) {
				ProjectionType = VIEW_PERSP;
				Perspective = 1;
			}
			else if (strcmp(argv[1],"top") == 0) ProjectionType = VIEW_TOP;
			else if (strcmp(argv[1],"front") == 0) ProjectionType = VIEW_FRONT;
			else if (strcmp(argv[1],"right") == 0) ProjectionType = VIEW_RIGHT;
			resetCamera();
		}
		return TCL_OK;
	}
	else if	(strcmp(argv[0],"create") == 0 ){
		if (argc != 6) {
			danceTcl::OutputMessage("create	",
			"<persp|top|right|front> <x> <y> <width> <height>\n");
			return TCL_ERROR;
		}
		create(getName(),argv[1],atoi(argv[2]),atoi(argv[3]),
				atoi(argv[4]),atoi(argv[5]));
	}
	else if	(strcmp(argv[0],"dump")	== 0) 
	{
	    if( argc < 2) 
	    {
		DumpPPM(m_DumpFileName) ;
		return TCL_OK ;
	    }
	    int count = 1 ;
	    while(count <= argc-1)
	    {
		if( strcmp(argv[count], "start") == 0 )
		{
		    m_IsDumped = TRUE ;
		    count++;
		}
		else if( strcmp(argv[count], "stop") == 0 )
		{
		    danceTcl::OutputMessage("Stop dumping %s", getName()) ;
		    m_IsDumped = FALSE ;
		    count++ ;
		}
		else if( strncmp(argv[count], "-f",2) == 0 )
		{
		    if(argv[count][2] != '\0')
			strcpy(m_DumpFileName, &argv[count][2]) ;
		    else
			danceTcl::OutputMessage("usage: -f<fname> (no space between)") ;
			if( count == argc - 1)
				DumpPPM(m_DumpFileName) ;	
		    count++ ;
		}
		else if( strncmp(argv[count], "-d",2) == 0 )
		{
		    if(argv[count][2] != '\0')
			strcpy(m_DumpDirectory, &argv[count][2]) ;
		    else
			danceTcl::OutputMessage("usage: -d<dname> (no space between)") ;
		    count++ ;
		}
		else if( strncmp(argv[count], "-n",2) == 0 )
		{
		    if(argv[count][2] != '\0')
			m_FrameNumber = atoi( &argv[count][2]) ;
		    else
			danceTcl::OutputMessage("usage: -n<number> (no space between)") ;
		    count++ ;
		}
		else if( strcmp(argv[count], "-h") == 0 )
		{
		    danceTcl::OutputMessage("usage: dump [-h] [-f<filename>] [-d<directory>] "
					    "[-c<halfSizeComand>]"
					    "[start|stop]") ;
		    count++ ;
		}
		else if( strncmp(argv[count], "-c", 2) == 0 ) {
		     if(argv[count][2] != '\0')
			strcpy(m_HalfSizeCom, &argv[count][2]) ;
		    else
			danceTcl::OutputMessage("usage: -c<half_size_command> (no space between)") ;
		    count++ ;
		}
		else
		{
		    danceTcl::OutputMessage("usage: dump [-h] [-f<filename>] "
					    "[-c<half_size_command>] "
					    "[-d<directory>] "
					    "[start|stop]") ;
		    return TCL_OK ;
		}
	    }
	    return TCL_OK ;
	}
	else if (strcmp(argv[0],"fitview") == 0) {
		BoundingBox *box = dance::GetSceneBox();
		AttachCamera(box);
		return TCL_OK;
	}	
	else if (strcmp(argv[0],"geometry") == 0) {
		if (argc == 1) {
			sscanf(resultString,"%d %d %d %d\n",X,Y,
			       Width, Height) ;
			danceTcl::OutputResult("%s",resultString);
		}
		return TCL_OK ;
	}
	else if	(strcmp(argv[0],"refresh") == 0) {
		if (WindowID ==	-1) {
			danceTcl::OutputMessage("ERROR:	You must use create to open a window first for this view.");
			return TCL_ERROR;

		}
		postRedisplay();
	}
	else if	(strcmp(argv[0],"lights") == 0)	{
		if (argc == 1) {
			if (Lights) 
				danceTcl::OutputMessage("on");
			else
				danceTcl::OutputMessage("off");
			return TCL_OK;
		}
		if (strcmp(argv[1],"on") == 0) {
		   Lights = 1;
		   danceTcl::OutputMessage("Lights are on.");
		}
		else {
		   Lights = 0;
		   danceTcl::OutputMessage("Lights are off.\n");
		}
		if (WindowID !=	-1)
			postRedisplay();
		return TCL_OK;
	}
	else if	(strcmp(argv[0],"solids") == 0)	{
		if (argc == 1) {
			if (Solids) 
				danceTcl::OutputMessage("on");
			else
				danceTcl::OutputMessage("off");
			return TCL_OK;
		}
		if (strcmp(argv[1],"on") == 0) {
		   Solids = 1;
		   danceTcl::OutputMessage("Solids are on.\n");
		}
		else {
		   Solids = 0;
		   danceTcl::OutputMessage("Solids are off.\n");
		}
		if (WindowID !=	-1)
			postRedisplay();
		return TCL_OK;
	}
	else if	(strcmp(argv[0],"shadows") == 0) {
		if (strcmp(argv[1],"on") == 0) {
		   Shadows = 1;
		   danceTcl::OutputMessage("Shadows are	on.\n");
		}
		else {
		   Shadows = 0;
		   danceTcl::OutputMessage("Shadows are	off.\n");
		}
		if (WindowID !=	-1)
			postRedisplay();
		return TCL_OK ;
	}
	else if (strcmp(argv[0],"pan") == 0) {
		if (argc == 3) {
			Panx = atof(argv[1]);
			Pany = atof(argv[2]);
			postRedisplay();
		}
		else {
			sprintf(resultString,"%f",Panx);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Pany);
			Tcl_AppendElement(interp,resultString);
		}
		return TCL_OK;
	}
	else if (strcmp(argv[0],"arcball") == 0) {
		if (argc == 3) {
			HVect arccoords;
			arccoords.x = (float)atof(argv[1]);
		    arccoords.y = (float)atof(argv[2]);
			adjustArcballCamera(arccoords);
			Ball_BeginDrag(Arcball);
			Ball_EndDrag(Arcball);
			postRedisplay();
		}
		else {
			sprintf(resultString,"%f",Arcball->vNow.x);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Arcball->vNow.y);
			Tcl_AppendElement(interp,resultString);
		}
		return TCL_OK;
	}
	else if (strcmp(argv[0],"orientation") == 0) {
		if (argc == 17) {
			float init[16];
			for (int i=0;i<16;i++)
				init[i] = (float)atof(argv[i+1]);
			Ball_Init(Arcball,init);
			postRedisplay();
		}
		else {
			HMatrix mat;
			Ball_Value(Arcball,mat);
			for (int i=0; i < 16; i++) {
				sprintf(resultString,"%f",((float *)mat)[i]);
				Tcl_AppendElement(interp,resultString);
			}
		}
		return TCL_OK;
	}
	else if (strcmp(argv[0],"distance") == 0) {
		if (argc == 2) {
			dollyCameraDist(atof(argv[1]));
			postRedisplay();
		}
		else {
			sprintf(resultString,"%f",Dist);
			danceTcl::OutputResult(resultString);
		}
		return TCL_OK;
	}
	else if (strcmp(argv[0],"target") == 0) {
		if (argc == 4) {
			Target[0] = (float)atof(argv[1]);
			Target[1] = (float)atof(argv[2]);
			Target[2] = (float)atof(argv[3]);
			postRedisplay();
		}
		else {
			sprintf(resultString,"%f",Target[0]);
			Tcl_AppendElement(interp,resultString);

			sprintf(resultString,"%f",Target[1]);
			Tcl_AppendElement(interp,resultString);

			sprintf(resultString,"%f",Target[2]);
			Tcl_AppendElement(interp,resultString);
		}
		return TCL_OK;
	}
	else if (strcmp(argv[0],"clipBounds") == 0) {
		if (argc == 7) {
			Left = atof(argv[1]);
			Right = atof(argv[2]);
			Bottom = atof(argv[3]);
			Top = atof(argv[4]);
			Near = atof(argv[5]);
			Far = atof(argv[6]);
			setProjection(Left,Right,Bottom, Top, Near, Far);
			postRedisplay();
		}
		else {
			sprintf(resultString,"%f",Left);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Right);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Bottom);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Top);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Near);
			Tcl_AppendElement(interp,resultString);
			sprintf(resultString,"%f",Far);
			Tcl_AppendElement(interp,resultString);
		}
		return TCL_OK;
	}
	else {
		usage(interp);
		return TCL_OK;
	}
	return DanceObject::Command(clientData,interp,argc,argv);
}

// create:
//
int DView::create(char *name, char *typeString, int x, int y, int width,	int height)
{

    X = x;
	Y = y;
	Width = width;
	Height = height;
	glutInitWindowSize(width,height);

	// On Linux systems, position refers to	the corner of the
	// window, not the corner of the rendering context (viewport)
#ifdef SGI
	glutInitWindowPosition(X,Y);
#else
	glutInitWindowPosition(X-WINFRAME_WIDTH,Y-WINFRAME_WIDTH-WINTITLEBAR_HEIGHT);
#endif

	setName(name);

	char windowName[256];
	sprintf(windowName,"%s(%s)",name,typeString);
    if (MasterWindow ==	-1) {
		MasterWindow = WindowID	= glutCreateWindow(windowName);
		Tcl_CreateTimerHandler(10,dance::mainLoop,(ClientData) NULL);
	}
    else 
	WindowID = glutCreateSharedWindow(windowName,MasterWindow);

	if (WindowID !=	-1) {
	    glutDisplayFunc(dance::DisplayCB);
	    glutIdleFunc(dance::IdleCB);
	    glutKeyboardFunc(dance::KeyboardCB);
	    glutMouseFunc(dance::MouseCB);
	    glutMotionFunc(dance::MotionCB);
	    glutPassiveMotionFunc(dance::PassiveMotionCB);
	    glutReshapeFunc(ReshapeCB);
	}

	ProjectionType = VIEW_PERSP;

	Perspective = 0;
	if (strcmp(typeString,"top") ==	0) ProjectionType = VIEW_TOP;
	if (strcmp(typeString,"right") == 0) ProjectionType = VIEW_RIGHT;
	if (strcmp(typeString,"front") == 0) ProjectionType = VIEW_FRONT;
	if (ProjectionType == VIEW_PERSP) Perspective = 1;

	glEnable(GL_DEPTH_TEST);
	setCamera(SCALE_FOR_BB,-1.0,-1.0,-1.0,1.0,1.0,1.0);

	strcpy(m_DumpFileName, getName()) ;

	return WindowID;
}

// detachMenu:
//	Detaches the given menu
//
//	  menu:	Menu ID, using GLUT identifiers
//
void DView::detachMenu(int menu)
{
	glutSetMenu(menu);

	// Attach this menu
	glutSetWindow(WindowID);
	glutDetachMenu(GLUT_RIGHT_BUTTON);
}

// dollyCamera:
//	Zoom camera in and out and specify target.
//
//	percentage: Percentage factor distance
//
void DView::dollyCamera(GLdouble	percentage)
{

	if (Perspective	== 0)
		return;

	GLdouble dist =	percentage*Dist;
	dollyCameraDist(dist);
}

// dollyCameraDist:
//
void DView::dollyCameraDist(double dist) 
{
	// Do not adjust distance if in	orthographic mode.
	if (Perspective) {
	    double ratiox = Right/Near;
	    double ratioy = Top/Near;

	    // Prevents	negative near clipping plane. However, we still	update the
	    // virtual_near value to allow us to gracefully zoom out without moving
	    // the near	clipping plane as we zoom out.
	    Virtual_near = Virtual_near	+ (dist	- Dist);

	    // Do not adjust near and far clipping planes if we	have reached the limits.
	    if (Virtual_near > Limit_near) {
	       Limit_near = 0.01;
	       Near += (dist - Dist);
	       Far += (dist - Dist);

	       Right= ratiox*Near;
	       Left = -1.0*Right;
	       Top = ratioy*Near;
	       Bottom =	-1.0*Top;

	       setProjection(Left,Right,Bottom,Top,Near,Far);
	    }
	    else Limit_near = Near;

	    // Calculate new bounds for	left,right,top,bottom.
	    Dist = dist;
	}
}

// drawArcball:
//	Draws arcball in given view
//
//	view: Given view
//
void DView::drawArcball()
{
	Ball_Draw(Arcball);
}


// endInteraction:
//	Ends an	interactive session with the window.
//
//	mode:	Type of	edit mode
//
void DView::endInteraction(int mode)
{
	switch(mode) {
	   case	camera_arcball:
		Ball_EndDrag(Arcball);
	   break;
	}
}

// getBackgroundColor:
//	color[4]  : Returns r,g,b,a
//
void DView::getBackgroundColor(GLfloat color[4])
{
	memcpy(color,BackgroundColor,4*sizeof(GLfloat));
}

// getBounds:
//
void DView::getBounds(double *left, double *right, double *top, double *bottom)
{
	*left =	Left;
	*right = Right;
	*top = Top;
	*bottom	= Bottom;
}

// getCenter:
//
void DView::getCenter(double center[3])
{
	getWorldCoords(center, (double) Width*0.5, 
			(double) Height*0.5, 0.5);
}


// getCameraParms:
//	Retrieves the camera parameters	for the	given view.
//
//	view	  : view ID
//	dist	  : camera distance to target
//	panx, pany: Panning coordinates.
//	target	  : camera target
//
void DView::getCameraParms(GLdouble *dist,
		GLdouble *panx,	GLdouble *pany,	GLdouble target[3])
{
	*dist =	Dist;
	*panx =	Panx;
	*pany =	Pany;

	for (int i = 0;	i < 3; i++)
		target[i] = Target[i];
}

// getCameraOrientation:
//	Retrieves the orientation matrix for the camera.
//
void DView::getCameraOrientation(float mat[4][4])
{
       double dmat[16];
       memcpy(dmat,Modelview,16*sizeof(GLdouble));

       // Eliminate translational component.
       dmat[12]	= dmat[13] = dmat[14] =	0.0;

       // Convert to float matrix
       for (int	i=0; i < 4; i++)
	   for (int j=0; j < 4;	j++)
	       mat[i][j] = dmat[i*4+j];
}

// getCameraTransformation:
//	Retrieves the transformation matrix for	the camera.
//
void DView::getCameraTransformation(float mat[4][4])
{
       double dmat[16];
       memcpy(dmat,Modelview,16*sizeof(GLdouble));

       // Convert to float matrix
       for (int	i=0; i < 4; i++)
	   for (int j=0; j < 4;	j++)
	       mat[i][j] = dmat[i*4+j];
}


// getProjection:
//	Retrieves the projection matrix	for the	camera view.
//
void DView::getProjection(double	*projection)
{
	memcpy(projection,Projection,16*sizeof(double));
}

// getReferenceFrame:
//	Retrieves the reference	frame axes of the window.
//
//	view: Given view ID
//	basisX,	basisY,	basisZ:	basis vectors
//
void DView::getReferenceFrame(double basisX[3], double basisY[3], double	basisZ[3])
{
	getViewPlane(basisX,basisY);

	// Get cross product for third vector.
	basisZ[0] = basisX[1]*basisY[2]	- basisX[2]*basisY[1];
	basisZ[1] = basisX[2]*basisY[0]	- basisX[0]*basisY[2];
	basisZ[2] = basisX[0]*basisY[1]	- basisX[1]*basisY[0];
}

// getSize:
//	Retrieves the size of the window (active or given).
//
void DView::getSize(int *width, int *height)
{
    GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm) ;
    if( rm != GL_SELECT )
	glutSetWindow(WindowID);
    *width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
    *height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
}

// getViewPlane:
//	Retrieves basis	vectors	for the	viewing	plane of the given window.
//	NOTE: Matrices mNow is in column major order (1st index	is column)
//	Basis vectors correspond to rows of the	matrix.
//
//	view: Given view ID
//	basisX,	basisY:	basis vectors
//
void DView::getViewPlane(double basisX[3], double basisY[3])
{
	HMatrix	mNow;
	Ball_Value(Arcball,mNow);

	double basisZ[3];
	for (int i=0; i	< 3; i++) {
	    basisX[i] =	mNow[i][0];
	    basisY[i] =	mNow[i][1];
	    basisZ[i] =	mNow[i][2];
	}

	double x,y,z;
	if (ProjectionType == VIEW_RIGHT) {
	    x =	basisX[0]; z = basisX[2];
	    basisX[0] =	z; basisX[2] = -1.0*x;

	    x =	basisY[0]; z = basisY[2];
	    basisY[0] =	z; basisY[2] = -1.0*x;
	}
	else if	(ProjectionType	== VIEW_TOP) {
	    y =	basisX[1]; z = basisX[2];
	    basisX[1] =	z; basisX[2] = -1.0*y;
	    y =	basisY[1]; z = basisY[2];
	    basisY[1] =	z; basisY[2] = -1.0*y;
	}
}

// getViewport:
//	Retrieves the viewport for the given view.
//
void DView::getViewport(int viewport[4])
{
    GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm) ;
    if( rm != GL_SELECT )
	glutSetWindow(WindowID);
    glGetIntegerv(GL_VIEWPORT,(GLint *)viewport);
}

// getWindowCoords:
//	Given a	world point, gets the window coordinates
//	NOTE: We use the Projection instead of reading
//	off the	PROJECTION stack directly because a picking operation
//	will alter the matrix on the stack and return incorrect	results.
//
void DView::getWindowCoords(GLdouble *world, GLdouble *win)
{
    GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm) ;
    if( rm != GL_SELECT )
	glutSetWindow(WindowID);
    int viewport[4]; glGetIntegerv(GL_VIEWPORT,(GLint *)viewport);
    
    gluProject(world[0],world[1],world[2],
	       Modelview,Projection,
	       (GLint *)viewport, &win[0],&win[1],&win[2]);
}

// getWorldCoords:
//	NOTE: We use the ViewsInfo[view].projection instead of reading
//	off the	PROJECTION stack directly because a picking operation
//	will alter the matrix on the stack and return incorrect	results.
//
double DView::getWorldCoords(GLdouble *world, int x, int y, GLdouble z)
{
    static GLdouble prevDepth = 1.0 ;
    
    GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm) ;
    if( rm != GL_SELECT )
	glutSetWindow(WindowID);
    
	int viewport[4]; glGetIntegerv(GL_VIEWPORT,(GLint *)viewport);


	int winx = x;
	int winy = viewport[3] - y;
	if (z <	0.0)
	{
		float zfloat ;
		glReadPixels( winx, winy,
			  1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&zfloat);
		if( fabs(zfloat - 1.0) < 0.000001 )
		    zfloat = prevDepth ;
		z = (double) zfloat ;
	}
	gluUnProject((double) winx,(double) winy,z,
		     Modelview,Projection,
		     (GLint *)viewport,	&(world[0]),&(world[1]),&(world[2]));
	prevDepth = z ;
	return(z);
}

// keyboardCB:
int DView::KeyboardCB( unsigned char key, int x, int y )
{
    switch(key) {
	case 32:
	    resetCamera();
	    postRedisplay();
	    return 1;
	    break;
	case 'f':
	  {
	      BoundingBox *box = dance::GetSceneBox();
	      AttachCamera(box);
	  }
	  return 1;
	  break ;
    }
    return 0;
}

// moveCamera:
//	Moves the camera for the given view.
//
//	dist		: Distance from	camera to target.
//	panx,pany	: Translation of camera	pan.
//	target[3]	: Target in world space	of camera.
//	arccoords	: 2D vector of coordinates for the arcball position.
//
void DView::moveCamera(GLdouble dist, GLdouble panx, GLdouble pany,
			  GLdouble target[3], HVect arccoords)
{
	// Set camera data.
	memcpy(Target,target,3*sizeof(GLdouble));
	Dist = dist;
	Panx = panx;
	Pany = pany;
	Ball_Mouse(Arcball,arccoords);
}

// panCamera:
//	Pans the camera	around the viewing plane.
//
//	panx, pany: Panning coordinates.
//
void DView::panCamera(GLdouble panx, GLdouble pany)
{
	Panx = panx;
	Pany = pany;
}

// pickProjection:
//	Resets projection matrix,
//
//	x,y :	x and y	coordinates of the picked pixel	in the window,
//		note that y starts at 0	from the top of	the window.
//	delX, delY : region around the pixel to	be picked
//
void DView::pickProjection(int x, int y,	double delX, double delY)
{
    GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm) ;
    if( rm != GL_SELECT )
	glutSetWindow(WindowID);
    
    
    // Get viewport	data.
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    
    // Load	special	Picking	Matrix Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x,viewport[3]-y, delX,delY,viewport);
    glMultMatrixd(Projection);
}

// positionCamera:
//	Positions the camera in	the world space.
//
void DView::PositionCamera()
{
	GLint rm ;
    glGetIntegerv(GL_RENDER_MODE, &rm)  ;
	if( rm == GL_RENDER )
		glutSetWindow(WindowID);
	
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();

	 // Panning translation.
	 glTranslated(-1.0*Panx,-1.0*Pany,0.0);

	 // Sets distance from viewer to target
	 // (valid only	for perspective	projection)
	 // RECALL: OpenGL uses	a right-handed coordinate system,
	 // so z positive is coming out	of the screen.
	 if (Perspective) // perspective projection
	   gluLookAt(0.0,0.0,Dist,0.0,0.0,0.0,0.0,1.0,0.0);

	 // Arcball rotation transformation.
	 HMatrix arcball_rot;
	 Ball_Value(Arcball,arcball_rot);
	 glMultMatrixf((float *)arcball_rot);

	 // Make adjustments (rotations) to achieve different views.
	 switch(ProjectionType)	{
		case VIEW_TOP:
		     glRotatef(90.0,1.0,0.0,0.0);
		break;
		case VIEW_RIGHT:
		     glRotatef(-90.0,0.0,1.0,0.0);
		break;
	 }

	 // Points camera to desired target.
	 glTranslated(-1.0*Target[0], -1.0*Target[1], -1.0*Target[2]);

	 // Store the modelview	matrix.
	 glGetDoublev(GL_MODELVIEW_MATRIX, Modelview);
}

// resetCamera:
//	Resets camera to original orientation and pan.
//
void DView::resetCamera()
{
	panCamera(0.0,0.0);
	Ball_Init(Arcball);
	Ball_Place(Arcball,qOne,0.75);
}


// setArcballConstraints:
//	Sets constraints for arcball to	rotate about specified axes.
//
//	axisset: Axisset to activate.
void DView::setArcballConstraints(AxisSet axisset)
{
	Ball_UseSet(Arcball,axisset);
}

// setBackgroundColor:
//	r,g,b,a	: Sets background color	to r,g,b,a
//
void DView::setBackgroundColor(float r, float g,	float b, float a)
{
	BackgroundColor[0] = r;
	BackgroundColor[1] = g;
	BackgroundColor[2] = b;
	BackgroundColor[3] = a;
}

// setCamera:
//	Sets the projection matrix and viewing for the given view.
//	Ensures	that we	can initially see the contents of the
//	bounding box with corners (minx,miny,minz) and (maxx, maxy, maxz).
//
//	perspective	: 0 for	orthographic, 1	for perspective
//	scale		: amount viewing volume	is larger than bounding	box
//	minx, miny, minz,
//	maxx, maxy, maxz: Bounds for bounding box of visuals.
//
//	NOTES:
void DView::setCamera(double scale,
	   double minx,	double miny, double minz, double maxx, double maxy, double maxz)
{
	// Initialize arcball.
	if (Arcball == NULL) {
	    Arcball = new BallData;
	    Ball_Init(Arcball);
	    Ball_Place(Arcball,qOne,0.75);
	}

	// Calculate camera target.
	double target[3];
	target[0] = (minx + maxx)/2.0;
	target[1] = (miny + maxy)/2.0;
	target[2] = (minz + maxz)/2.0;

	// Since we want the entire bounding box to be seen, even if
	// we tumble around, we	must ensure that all box dimensions
	// can be seen from any	angle about the	target.
	// We calculate	the maximum radius about the target.
	double max_radius = sqrt(
			      pow(maxx-target[0],2.0) +
			      pow(maxy-target[1],2.0) +
			      pow(maxz-target[2],2.0)
			    );

	// Calculate the clipping planes for each dimension.
	double half_x =	max_radius*scale;
	double half_y =	max_radius*scale;
	double half_z =	max_radius*scale;


	
	// DO NOT use glutGet cause we do not know which window
	// is active!
	//double aspect = (double) glutGet((GLenum)GLUT_WINDOW_WIDTH)/
	// (double) glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	double aspect = ((double)Width) / (double) Height ;
	double half_size = half_x ;
	if (half_y > half_size)	half_size = half_y;
	if (half_z > half_size)	half_size = half_z;
	
	// Calculate size of viewing volume.
	GLdouble left =	-aspect*half_size ;
	GLdouble right = aspect*half_size ;
	GLdouble bottom	= -half_size;
	GLdouble top = half_size;

	GLdouble nearV, farV, dist;


	// Projection parameters.
	if (Perspective	== 0) {	// orthographic
	     nearV = -1.0*half_size;
	     farV = half_size;

	     //	Although this distance is really meaningless.
	     //	This value can be used to gauge	how much to
	     //	pan a camera.
	     dist = half_size;
	}
	else { // Perspective projection
	     //	Both near and far must be positive.
	     //	We scale the viewing volume a bit more in the z	direction,
	     //	to allow a slightly larger space between the near and far
	     //	clipping planes.
	     //

	     //	Move out about 5 times the depth of the	bounding box.
	     dist = 2.0*half_size;
	     nearV = half_size;
	     farV = 3.0*half_size;
	}

	setProjection(left,right,bottom,top,nearV,farV);

	HVect arccoords;
	arccoords.x = arccoords.y = 0.0;
	moveCamera(dist,0.0,0.0,target,arccoords);

	// For correct dolly operations.
	// The setting of virtual_near allows us to clip inside	a solid	and still
	// keep	a very tight bound for the front and back clipping.
	Virtual_near = Near;
	Limit_near = 0.01;

}

// setProjection:
//	Sets the projection matrix from	the preset values.
//
void DView::setProjection()
{
	glutSetWindow(WindowID);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (Perspective	== 0)
	    glOrtho(Left,Right,	Bottom,Top, Near,Far);
	else
	    glFrustum(Left,Right,Bottom,Top,Near,Far);
	glGetDoublev(GL_PROJECTION_MATRIX,Projection);
}

// setProjection:
//	Sets the projection matrix for the given window	to be orthographic
//	or perspective.
//
//	perspective: 0 for orthographic, 1 for perspective
//	left	   : left side of viewing volume.
//	right	   : right side	of viewing volume.
//	bottom	   : bottom side of viewing volume.
//	top	   : top side of viewing volume.
//	near	   : near clipping plane of viewing volume.
//	far	   : far clipping plane	of viewing volume.
//
void DView::setProjection(
	GLdouble left, GLdouble	right, GLdouble	bottom,	GLdouble top,
	GLdouble nearV,	GLdouble farV)
{
	glutSetWindow(WindowID);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (Perspective	== 0)
	    glOrtho(left,right,bottom,top,nearV,farV);
	else
	    glFrustum(left,right,bottom,top,nearV,farV);
	glGetDoublev(GL_PROJECTION_MATRIX,Projection);
	
	Near = nearV;
	Far = farV;
	Left = left;
	Right =	right;
	Top = top;
	Bottom = bottom;
}

// start:
//	Initialization stuff before drawing
//
void DView::start()
{
	glClearColor(BackgroundColor[0],BackgroundColor[1],
		     BackgroundColor[2],BackgroundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if (Lights)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}

// zoomCamera:
//	Zoom camera in as a percentage of the original viewport	size.
//
//	percentage: percentage to zoom in or out.
//
void DView::zoomCamera(GLdouble percentage)
{
	Left *=	percentage;
	Right *= percentage;
	Bottom *= percentage;
	Top *= percentage;
	setProjection(Left,Right,Bottom, Top, Near, Far);
}

void DView::print(FILE * fptr)
{
	char resultString[256];
	if (ProjectionType == VIEW_PERSP) strcpy(resultString,"persp");
	if (ProjectionType == VIEW_TOP) strcpy(resultString,"top");			
	if (ProjectionType == VIEW_RIGHT) strcpy(resultString,"right");
	if (ProjectionType == VIEW_FRONT) strcpy(resultString,"front");

	fprintf(fptr,"instance view %s %s %d %d %d %d\n",
		getName(),resultString, X, Y,  
				Width, Height) ;
	if (Perspective) {
		HMatrix mat;
		Ball_Value(Arcball,mat);
		fprintf(fptr,"view %s orientation ",getName());
		for (int i=0; i < 16; i++)
			fprintf(fptr,"%f ",((float *)mat)[i]);
		fprintf(fptr,"\n");	
		
		fprintf(fptr,"view %s distance %f\n",getName(),Dist);
	}
	fprintf(fptr,"view %s clipBounds %f %f %f %f %f %f\n",getName(),
		Left,Right,Bottom,Top,Near,Far);
	fprintf(fptr,"view %s target %f %f %f\n",getName(),Target[0],Target[1],Target[2]);
	fprintf(fptr,"view %s pan %f %f\n",getName(),Panx,Pany);
	fprintf(fptr,"view %s background %f %f %f %f\n",
		getName(),BackgroundColor[0],BackgroundColor[1],BackgroundColor[2],BackgroundColor[3]);
	if (Lights)
		fprintf(fptr,"view %s lights on\n",getName());
	if (Solids)
		fprintf(fptr,"view %s solids on\n",getName());

	fprintf(fptr,"\n");
}

void DView::getNearFar(double * nearplane, double * farplane)
{
	*nearplane = Near;
	*farplane = Far;
}

// Returns the Frustum width at the given depth level (0,1)
double DView::getFrustumWidth(double depth)
{
	if (Perspective) {
		double ratio = (Right-Left)*0.5/Near;
		double dist = Near*(1.0-depth) + depth*Far;
		return(ratio*dist*2.0);
	}
	else 
		return(Right-Left);
}


double DView::getDepth(int x, int y)
{
	int viewport[4]; glGetIntegerv(GL_VIEWPORT,(GLint *)viewport);

	int winx = x;
	int winy = viewport[3] - y;

	float zfloat ;
	glReadPixels( winx, winy,
		  1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&zfloat);
	return( (double) zfloat );
	
}


void DView::ReshapeCB(int width, int height)
{

    DView *window = dance::AllViews->getViewFocus() ;


    if( window == NULL ) return ;

	glViewport(0,0,width,height);
	
	GLdouble proj_height = window->Top - window->Bottom;
	GLdouble proj_width = ((double)width/(double)height)*(double)proj_height;
	window->Right =	proj_width/2.0;
	window->Left = -1*proj_width/2.0;


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (window->Perspective == 0)
	    glOrtho(window->Left, window->Right, window->Bottom, window->Top,
		    window->Near, window->Far);
	else
	    glFrustum(window->Left, window->Right, window->Bottom, window->Top,
		      window->Near, window->Far);
	glGetDoublev(GL_PROJECTION_MATRIX, window->Projection);

	// New x and y offsets for window.
	int newx = glutGet((GLenum)GLUT_WINDOW_X);
	int newy = glutGet((GLenum)GLUT_WINDOW_Y);

	// Old x and y offsets for window.
	int oldx = window->X;
	int oldy = window->Y;

	// Displacement	change in window size.
	int dispx = width - window->Width;
	int dispy = height - window->Height;

	// Record new window changes for the triggering	window.
	window->X = newx;
	window->Y = newy;
	window->Width = width;
	window->Height = height;

	// return back to model view
	glMatrixMode(GL_MODELVIEW) ;
}


void DView::targetCamera(GLdouble target[])
{
	memcpy(Target,target,3*sizeof(GLdouble));
}

void DView::GetState(double *state)
{
    state[0] = Target[0] ;
    state[1] = Target[1] ;
	state[2] = Target[2] ;
	state[3] = Left;
	state[4] = Right;
	state[5] = Top;
	state[6] = Bottom;

	Quaternion quat;
	float mat[4][4];
	getCameraOrientation(mat);
	quat.fromMatrix(mat);
	quat.getAxisAngle(&(state[8]),&(state[7]));
	
}    

void DView::UpdateState(double *state)
{
	// Set target position.
    Target[0] = state[0] ;
    Target[1] = state[1] ;
	Target[2] = state[2] ;

	// Set viewing frustum (for zoom)
	Left = state[3];
	Right = state[4];
	Top = state[5];
	Bottom = state[6];
    setProjection(Left,Right,Bottom, Top, Near, Far);

	// Set camera orientation.
	Quaternion quat;
	float mat[4][4];

	quat.set(state[7],&(state[8]));
	quat.toMatrix(mat);
	Ball_Init(Arcball,(float *)mat);

    postRedisplay() ;
}

void DView::SaveFrame(void)
{
    FILE * fp ;
    char fname_t[MAX_LINE] ;
    char fname[MAX_LINE] ;

    sprintf(fname,"%s/%s%d.ppm", m_DumpDirectory,m_DumpFileName, m_FrameNumber) ;
    if( m_HalfSizeCom[0] != '\0' )
    {
	sprintf(fname_t,"%s/%s%d_t.ppm", m_DumpDirectory, m_DumpFileName,  m_FrameNumber) ;
	
	if(	(fp = fopen(fname_t,"w")) == NULL )
	{
	    danceTcl::OutputMessage("Cannot open %s\n", fname_t) ;
	    return ;
	}
    }
    else if( (fp = fopen(fname,"w")) == NULL )
    {
	danceTcl::OutputMessage("Cannot open %s\n", fname) ;
	return ;
    }

    danceTcl::OutputMessage("Dumping %s\n", fname) ;
    DumpPPM(fp, 1)	;
    fclose(fp) ;
    if( m_HalfSizeCom[0]  != '\0' )
    {
	char com[MAX_LINE] ;
	
	sprintf(com,"%s %s %s", m_HalfSizeCom, fname_t, fname) ;
	danceTcl::ExecuteCommand(com) ;
	
#ifdef WIN32
	/*
	// flip the / in the file name since it goes to cmd.exe
	s = &fname_t[0] ;
	for( ; *s ; s++ )
	    if( *s == '/')  *s = '\\' ;
	*/
	sprintf(com, "rm %s", fname_t) ;
#else
	sprintf(com, "/bin/rm %s", fname_t) ;
#endif
       	danceTcl::ExecuteCommand(com) ;
    }
    m_FrameNumber++ ;
}

void DView::DumpPPM(char *fname)
{
	FILE *fp ;
    if( (fp = fopen(fname, "w")) == NULL )
    {
	danceTcl::OutputMessage("View:DumpPPM: cannot open file %s", fname) ;
	return ;
    }
    DumpPPM(fp) ;
    fclose(fp) ;
}

// dumps a PPM raw (P6) file
void DView::DumpPPM(FILE *fp, int buffer)
{
    const int maxVal=255;
    register int y;
    unsigned char *pixels;

    int	width, height;
    getSize(&width,&height);
    danceTcl::OutputMessage("width = %d height = %d\n",width, height) ;

    fprintf(fp,	"P6 ");
    fprintf(fp,	"%d %d ", width, height);
    fprintf(fp,	"%d\n",	maxVal);

    pixels = new unsigned char [3*width];
    if(	pixels == NULL )
    {
	fprintf(stderr,"Cannot allocate	enough memory\n") ;
	return ;
    }

    if( buffer == 0 )
	glReadBuffer(GL_FRONT) ;
    else
	glReadBuffer(GL_BACK) ;   
    for	( y = height-1;	y>=0; y-- ) {
	glReadPixels(0,y,width,1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);
#ifdef WIN32
	//  RGB <-> GBR for windows (beats me why!)
	unsigned char *p = &pixels[0] ;
	for( int i = 0 ; i < 3*width ; i += 3 )
	{
	    unsigned char v[3] ;
	    v[0] = p[i+1] ;
	    v[1] = p[i+2] ;
	    v[2] = p[i] ;
	    fwrite(v, 3*sizeof(unsigned char), 1, fp);
	}
#else
	fwrite(pixels, 3, width, fp);
#endif
    }
    delete [] pixels;
}
