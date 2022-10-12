/**************************************************************************
	----------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project


 ***************************************************************
 ****** General License Agreement and Lack of Warranty *********
 ***************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/


// This is a template for an event-driven application, using the	viewer class.
#include "dance.h"
#include "danceTcl.h"
#include "DActuator.h"
#include "DSystem.h"
#include "DLight.h"
#include "DView.h"
#include "ViewManager.h"
#include "PlugInManager.h"
#include "DSimulatorManager.h"
#include "GLutilities.h"
#include "VCollide.h"
#include "Proximity.h"
#include <assert.h>

enum MenuChoices {
	eConstraintPickObj1,
	eConstraintPickObj2,
	eConstraintPickPoint,
	eConstraintSet,
	eConstraintQuit,
};


int dance::AppMode=command_mode;     //	Application mode
int dance::AppModeModifier = -1;
int dance::LastMode=command_mode;     // Application mode


				     //	picked item.
DView *dance::FocusWindow = NULL;

int dance::numDanceLists = 0;
DanceObject *dance::m_ActiveObject = NULL;
DanceObjectList	**dance::DanceLists = NULL;
DanceObjectList	*dance::AllActuators = NULL;
DanceObjectList	*dance::AllSystems = NULL;
DanceObjectList	*dance::AllLights = NULL;
DanceObjectList	*dance::AllGeometry = NULL;
PlugInManager *dance::AllPlugIns = NULL;
ViewManager *dance::AllViews = NULL;
DSimulatorManager *dance::AllSimulators = NULL;

int dance::m_SimulBlock = FALSE ;
int dance::m_ModifierKey = 0;
int dance::m_NoDisplay = FALSE ;
int dance::FitviewAlways = FALSE;
int dance::Monitorpts =	TRUE ;
int dance::m_DisplayActuators = TRUE;  // Display actuators or not
int dance::UpdateAllWindows = 0; // Update all windows

double dance::CursorPosn[3] = { 0,0,0} ;
static int ProximityOn = FALSE ;
Proximity *dance::m_Proximity = new Proximity;
Volume *dance::m_AllVolumes = NULL;

// Static globals restricted to this file's scope.
// Better to leave them here, then in the physical interface as private
// static members.
static int InitMousePosition = 0; // Flag if mouse position is initialized.
static int HandleMoreEvents = TRUE;
static int PickedItem =	-1;	      // Identifies the picked item.
static int PressedButtonID = 0 ; // glut mouse callaback doesn't return the button id.
				// so we use this to fill in event->buttonID
	   
void CheckError(char *mes)
{
	const GLubyte *errString ;
	GLenum errCode ;
	if((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode) ;
		danceTcl::OutputMessage("%s ------------- Open gl error: %s",mes, errString) ;
	}
}

/**
 *  Display callback
 *
 *  Display callback for glut, redraws the scene.
 * @return void 
 */
void dance::DisplayCB(void)
{
	HandleMoreEvents = TRUE;

	FocusWindow = AllViews->getViewFocus();
	if (FocusWindow == NULL) return;
	FocusWindow->start();

	// Adjust the camera for this window.
	FocusWindow->PositionCamera();

	// position the	lights
	if (FocusWindow->isLights()) {
	  int i ;
	  for(i = 0	; i < AllLights->size(); i++)
	  {
	    DanceObject	*light = AllLights->get(i);
	    light->output();
	  }
	  //if( i == 0 ) 
		//  glDisable(GL_LIGHTING) ;
	  // else 
		  glEnable(GL_LIGHTING) ;
	}
	
     	// ... deleted the drawing of end effector

	if (ProximityOn == TRUE)	{
	    glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT);
	    glDisable(GL_LIGHTING);
	    glDepthMask(GL_FALSE);
	    glPointSize(5.0);
	    glColor4f(1.0,0.0,0.0,1.0);
	    glBegin(GL_POINTS);
	    glVertex3dv(CursorPosn);
	    glEnd();
	    
	    
	    
	    double closest[3],  normal[3];
	    DanceObject *obj; box *OBB;
	    double result = m_Proximity->FindClosest(CursorPosn,closest,normal,&obj,&OBB);
	    
	    if (result > 0) {
		
		/* Uncomment if wish to see closest distance value.
		   glRasterPos3dv(closest);
		   double dist = pow(closest[0]-CursorPosn[0],2.0)
		   + pow(closest[1]-CursorPosn[1],2.0)
		   + pow(closest[2]-CursorPosn[2],2.0);
		   
		   sprintf(label,"%f",dist);
		   GLlabel(label);
		*/
		
		// Draw vector from closest point to test point.
		// Draw normal at closest point.
		glLineWidth(3.0);
		glBegin(GL_LINES);
		//glColor3f(0.0f,1.0f,0.0f);
		//glVertex3dv(closest);
		//glVertex3d(closest[0]+normal[0],closest[1]+normal[1],closest[2]+normal[2]);
		if (result == 1)
		    glColor3f(0.0f,0.0f,0.0f);
		else
		    glColor3f(1.0f,0.0f,0.0f);
		glVertex3dv(closest);
		glVertex3dv(CursorPosn);
		
		glEnd();
		glLineWidth(1.0);
		
		// Draw cursor point position.
		/*
		  char label[256]; 
			sprintf(label,"(%1.2f,%1.2f,%1.2f)", CursorPosn[0],CursorPosn[1],CursorPosn[2]);
			glRasterPos3dv(CursorPosn);
			GLlabel(label);
			*/
	    }

	    glPopAttrib();
	
	}

	int mode = 0 ;
	if( FocusWindow->isSolids())
	    mode  = mode |  LDISPLAY_SOLID ;
	else
	    mode  = mode |  LDISPLAY_WIRE;

	if( dance::Monitorpts == TRUE)
	    mode = mode	| LDISPLAY_MONITOR ;

	// Done in articulated object now
	// Set joint mode for display.
	//if (AppMode == joint_edit_mode) {
	//mode = mode | JDISPLAY_CENTRES | JDISPLAY_SELECTION;
	//}

	AllSystems->output(mode);
	
	// display actuators
	if ( dance::m_DisplayActuators == TRUE) {
	    if(FocusWindow->isShadows())
			mode = mode | LDISPLAY_SHADOW ;
	    AllActuators->output(mode); 
	}

	// display active danceObjects
	if ( dance::m_ActiveObject ) 
		dance::m_ActiveObject->Highlight(0.0f,1.0f,0.0f,1.0f);
	
	if (AppModeModifier == arcball_mode)
		 FocusWindow->drawArcball();

	
	FocusWindow->end();

	if (FocusWindow->IsDumped() == TRUE)
	{
	    // CAUTION: Do not call glutSwapBuffers.
	    // Instead read from the back one 
	    // that's what SaveFrame does.
	    FocusWindow->SaveFrame() ;
	}

	CheckError("Display callback") ;
}

// getInstance:
//
DanceObject *dance::getInstance(Tcl_Interp *interp,
				char *type, char *name,	int argc, char **argv)
{
	     DanceObject *obj =	NULL;
	     if	(strcmp(type,"light") == 0)
		 obj = new DLight(interp,	name, argc, argv);
	     else if (strcmp(type,"view") == 0) {	
		 if( dance::m_NoDisplay == TRUE ) 
		     return NULL ;
		 else if (strcmp(name,"quadview") == 0)
		     AllViews->createQuadView();
		 else {
		     obj	= new DView(interp, name,argc, argv);
		     DView *view = (DView *)obj;
		 }
	     }
	     
	     if( dance::m_NoDisplay != TRUE )
		 AllViews->postRedisplay();
	     
	     //	set the	name! This is important!
	     if( obj !=	NULL ) obj->setName(name) ;
	     return(obj);
}

// getLists:
//	Returns	list of	lists of dance objects.
//
void dance::getLists(int *number, DanceObjectList ***lists)
{
	*number	= numDanceLists;
	*lists = DanceLists;
}

DanceObjectList	*dance::getList(char *listname)
{
	if (strcmp(listname,"actuator")	== 0) return (AllActuators);
	if (strcmp(listname,"system") == 0) return (AllSystems);
	if (strcmp(listname,"light") ==	0) return (AllLights);
	if (strcmp(listname,"geometry")	== 0) return (AllGeometry);
	if (strcmp(listname,"simulator") == 0) return (AllSimulators);
    if (strcmp(listname,"view")	== 0) return (AllViews);
	return (NULL);
}

// initialize:
//	Initializes Tcl	Interpretor.
//	Parse arguments	for dance.
//	Opens Display
//
//
void dance::initialize(int argc, char **argv)
{
	// Parse arguments first!! This is where m_NoDisplay is set
    	parseArguments(argc,argv);

	// Initialize Dance lists.
	numDanceLists = 6;
	DanceLists = new DanceObjectList *[numDanceLists];
	// Order is important, some objects will not work without others 
	// already defined.
	DanceLists[0] =	AllViews = new ViewManager(argc,argv); AllViews->setType("view");
	DanceLists[1] =	AllLights = new	DanceObjectList; AllLights->setType("light");
	DanceLists[2] =	AllGeometry = new DanceObjectList; AllGeometry->setType("geometry");
	DanceLists[3] =	AllSystems = new DanceObjectList; AllSystems->setType("system");
	DanceLists[4] =	AllActuators = new DanceObjectList; AllActuators->setType("actuator");
	DanceLists[5] = AllSimulators = new DSimulatorManager; AllSimulators->setType("simulator");
	AllPlugIns = new PlugInManager;	AllPlugIns->setType("plugin");

    	danceTcl::InitTclTk(argc,argv);
}

void dance::parseArguments(int argc, char **argv)
{
    char usage[] = "dance [-n]\n"
      "-n for no display\n" ;

    // parse the command line arguments
    int	i = 1 ;
    while( i < argc )
    {
	if( argv[i][0] == '-' )	{
	    if(	strcmp(&argv[i][1], "n"	) == 0)
	    {
		dance::m_NoDisplay = TRUE	;
		fprintf(stderr,"NO DISPLAY\n") ;
	    }
	    else
	    {
		fprintf(stderr,"dance: No such option\n");
		fprintf(stderr,"dance:\n%s\n", usage);
	    }
	}
	i++ ;
    }
    // end parsing the command line arguments

}


void dance::KeyboardCB(unsigned	char key, int x, int y)
{


	int count = 0 ;

	// call all plugin keyboardCB
	count += AllSystems->KeyboardCB(key,x,y) ;
	count += AllLights->KeyboardCB(key,x,y) ;
	count += AllActuators->KeyboardCB(key,x,y) ;
	count += AllGeometry->KeyboardCB(key,x,y) ;
	count += AllSimulators->KeyboardCB(key,x,y) ;
	count += AllViews->KeyboardCB(key,x,y) ;

	// if any of the lists returned non zero
	// do not check the standard ones.
	if( count > 0 ) return ;

	switch((char)key)
	{
	  
	    case 'a':
		dance::AppMode	= actuator_mode;
		dance::m_DisplayActuators = TRUE;
		AllViews->getViewFocus()->postRedisplay();
		break;
	    case 'l':
		 AppMode = light_mode;
		 break;
	    case 'p':
		if( ProximityOn == TRUE )
		    ProximityOn = FALSE ;
		else
		    ProximityOn = TRUE ;
		    
//  	if (AppMode == pointer_mode) {
//  		    if (CursorPosn) delete [] CursorPosn;
//  		    CursorPosn = NULL;
//  		    AppMode = camera_mode;
//  		}
//  		else {
//  		    if (CursorPosn==NULL)
//  			CursorPosn = new GLdouble[3];
//  		    view->getCenter(CursorPosn);
//  		    AppMode = pointer_mode;
//  		}
		break;
	    case 27: // ESC key
		EnterCommandMode();
		break;
	}
	
}

// Handle camera motions.
void dance::handleCameraMotions(DView *focus, int x, int	y,
		int width, int height, int diffx, int diffy)
{

	switch(AppModeModifier)	{
	   case	arcball_mode:
	   {
		 HVect arcball_coords;
		 arcball_coords.x = 2.0*(float)x/(float)width-1.0;
		 arcball_coords.y = -2.0*(float)y/(float)height+1.0;
		 focus->adjustArcballCamera(arcball_coords);
		 focus->postRedisplay();
	   }
	   break;
	   case	pan_mode:
	   {
	     GLdouble dist, panx, pany,	target[3];
	     focus->getCameraParms(&dist, &panx,&pany,target);
		 
		 double worldwidth = focus->getFrustumWidth(0.0);
		 // More intelligent pan that moves rotation point with it.
		 double basisx[3], basisy[3]; focus->getViewPlane(basisx,basisy);
		 for (int i = 0; i < 3; i++)
			 target[i] += -diffx*basisx[i]*0.01*worldwidth + diffy*basisy[i]*0.01*worldwidth;
		 focus->targetCamera(target);
	         focus->postRedisplay();
	   }
	   break;
	   case	zoom_mode:
	     //	Orthographic zoom and non-forshortening	zoom
	     if	(diffx + diffy > 0)
		     focus->zoomCamera(1.10);
	     else
		     focus->zoomCamera(0.9);
	     focus->postRedisplay();
	   break;
	   case	dolly_mode:
	     //	Only for Perspective window, displays forshortening effects.
	     if	(diffx + diffy > 0)
		     focus->dollyCamera(1.10);
	     else
		     focus->dollyCamera(0.9);
	     focus->postRedisplay();
	   break;
	}
}


// Callback for	mouse motion with button pressed.
void dance::MotionCB(int x, int	y)
{
	if (HandleMoreEvents ==	FALSE)
		return;

	if ( y < 0 )
	{
	    // danceTcl::OutputMessage("y = %d", y) ;
	    return ;
	}
	if ( x < 0 )
	{
	    // danceTcl::OutputMessage("x = %d", x) ;
	    return ;
	}

	// Calculate differentials of mouse position.
	static int oldx, oldy;
	if (InitMousePosition) {
	     oldx = x; oldy = y;
	     InitMousePosition = 0;
	}
	int diffx = x -	oldx;
	int diffy = y -	oldy;
	oldx = x; oldy = y;

	// Get window parameters.
	FocusWindow = AllViews->getViewFocus();
	if (FocusWindow	== NULL) return;

	int width, height;
	FocusWindow->getSize(&width,&height);
	FocusWindow->getWorldCoords(CursorPosn,x,y);
	
	if( PickedItem > -1 )
	{
	    double basisX[3],	basisY[3], basisZ[3];
	      FocusWindow->getReferenceFrame(basisX,basisY,basisZ);
	      Event event;
	      event.setWindow(FocusWindow,x,y,width,height);
	      event.setWindowDiffs(diffx,diffy);
	      event.setWindowBasis(basisX,basisY,basisZ);
	      // use the static to retrieve the button ID
	      event.buttonID = PressedButtonID ;

	      HandleMoreEvents = FALSE;
	      
	      DActuator *wactuator ;
	      DSystem *sys ;
	      DLight *wlight ;
	      switch(AppMode)
	      {
		  case actuator_mode:
		      wactuator = (DActuator *)AllActuators->getActive() ;;
		      if (wactuator) wactuator->Interact(&event);
		      FocusWindow->postRedisplay();	
		      break;
		  case system_mode: {
		      sys = (DSystem *)AllSystems->getActive();
		      if (sys) sys->Interact(&event);

		      // Update all actuators
		      for (int i = 0; i < dance::AllActuators->size(); i++) {
			  DActuator *act = (DActuator *) dance::AllActuators->get(i);
			  if (sys)
				act->afterObjectUpdate(sys);
		      }
		      FocusWindow->postRedisplay();	
							}
		      break;
		  case light_mode:
		      wlight = (DLight *)AllLights->getActive();
		      if( wlight) wlight->Interact(&event);
		      FocusWindow->postRedisplay();	
		      break;
	      }
	}
	switch(AppMode)
	{
	    case command_mode:
	    case camera_mode:
		handleCameraMotions(FocusWindow,x,y,width,height,diffx,diffy);
		break;
	    case pointer_mode:
		// Move the pointer to the mouse position.
		FocusWindow->getWorldCoords(CursorPosn,x,y);
		FocusWindow->postRedisplay();
		break;
	}

	
	if (FitviewAlways == TRUE)
	    AllViews->FitView();

}

void dance::PassiveMotionCB(int	x, int y) {

	// Check if mouse is outside of window.
	if ( x < 0 || y < 0)
	    return ;

	DView *view = AllViews->getViewFocus();
	if( view == NULL ) return ;
	
	if( PickedItem > -1 )
	{
	      switch(AppMode)
	      {
		  case actuator_mode: {
		      DActuator *wactuator = (DActuator *)AllActuators->get(PickedItem);
		      if (wactuator) wactuator->PassiveMotionCB(view,x,y);
		      FocusWindow->postRedisplay();	
		      }
		      break;
		  case system_mode: { 
		
		      GLdouble point[3];
		      view->getWorldCoords(point,x,y,0.5);
		      memcpy(dance::CursorPosn,point,3*sizeof(GLdouble));
		      DSystem *sys = (DSystem *)AllSystems->get(PickedItem);
		      if (sys) 
			  sys->PassiveMotionCB(view, x, y);
		      
		      // Update all actuators
		      for (int i = 0; i < dance::AllActuators->size(); i++) {
			  DActuator *act = (DActuator *) dance::AllActuators->get(i);
			  if (sys)
				act->afterObjectUpdate(sys);
		      }
		      FocusWindow->postRedisplay();
							}
		      break;
		  case light_mode: {
		      DLight *wlight = (DLight *)AllLights->get(PickedItem);
		      if( wlight) wlight->PassiveMotionCB(view, x, y);
		      FocusWindow->postRedisplay();	
		      }
		      break;
	      }
	}    
	
}

void dance::handleCameraButtons(DView *focus, int button, int state, int	x, int y, int width, int height)
{
	switch(button) {
	    case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)	{
		    AppModeModifier = arcball_mode;
		    int	modifier = glutGetModifiers();
		    switch(modifier) {
		       case GLUT_ACTIVE_ALT:
			  focus->setArcballConstraints(BodyAxes);
		       break;
		       case GLUT_ACTIVE_SHIFT:
			  focus->setArcballConstraints(CameraAxes);
		       break;
		       default:
			  focus->setArcballConstraints(NoAxes);
		    }

		    HVect arcball_coords;
		    arcball_coords.x = 2.0*(float)x/(float)width-1.0;
		    arcball_coords.y = -2.0*(float)y/(float)height+1.0;
		    focus->adjustArcballCamera(arcball_coords);
		    focus->beginInteraction(camera_arcball);
		}
		else { // GLUT_UP
		    focus->endInteraction(camera_arcball);
			AppModeModifier = -1;
		    focus->postRedisplay();
		}
	     break;
	     case GLUT_MIDDLE_BUTTON:
		  if (state == GLUT_DOWN)
		      AppModeModifier =	pan_mode;
	     break;
	     case GLUT_RIGHT_BUTTON:
		  if (state == GLUT_DOWN) {
		      int modifier = glutGetModifiers();
		      switch(modifier) {
			  case GLUT_ACTIVE_SHIFT: // In order to accomodate two-button mice.
				  AppModeModifier = pan_mode;
				 break;
			  case GLUT_ACTIVE_CTRL:
			     AppModeModifier = dolly_mode;
			     break;
			 default:
			     AppModeModifier = zoom_mode;
		      }
		  }
	}

}

int dance::handleSelection(int x, int y, int button, int &number, int *item, int type)
{
	int selection_mode = -1;

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);

	// Set up selection buffer.
	static GLuint SelectBuffer[512];
	glSelectBuffer(512,SelectBuffer);

	// Begin picking.
	glRenderMode(GL_SELECT);
	glInitNames();

	DView *view = AllViews->getViewFocus();
	view->pickProjection(x,y,7.0,7.0);
	view->PositionCamera();

	int mode = LDISPLAY_SOLID | LDISPLAY_SELECTION ;
	//	DSystem *active =(DSystem *)AllSystems->getActive();
	switch(type) {
	   case	ACTUATOR_SELECTION:
	     if (AllActuators)	{
		  glPushName(ACTUATOR_SELECTION);
		  // must LDISPLAY_SELECTION otherwise the
		  // actuator display will produce wrong window coordinates
		  // for glReadPixels and core dump.
		  // selection changes the projection matrix!!
		  AllActuators->output(mode);
		  glPopName();
	      }
	   break;
	   case	SYSTEM_SELECTION:
	    glPushName(SYSTEM_SELECTION);

	    // Must use	output with two	arguments.
	    AllSystems->output(mode);
	    glPopName();
	    break;
	   case	GEOMETRY_SELECTION:
	       danceTcl::OutputMessage("Selection for geometries not implemented.") ;
	   break;
	   case	LIGHT_SELECTION:
	     glPushName(LIGHT_SELECTION);
	     AllLights->output(mode);
	     glPopName();
	   break;
	}

	glFlush() ;

	// Process hits.
	int hits = glRenderMode(GL_RENDER);



	view->setProjection();

	int hp = 0;

	// Must use unsigned int for distance calculations to be correct.
	unsigned int closest = 0;

	// Loop	through	and pick the front-most	item
	for (int h = 0;	h < hits; h++) {
		int pickThis = 0;
		int numNames = SelectBuffer[hp++];
		unsigned int minz = SelectBuffer[hp++];
		unsigned int maxz = SelectBuffer[hp++];
		if (h==0) {
			closest	= minz;
			pickThis = 1;
		}
		else if	(minz <= closest)
			pickThis = 1;
		
		
		if (pickThis) {
		    number = 0;
		    for	(int ns	= hp; ns < hp+numNames;	ns++) {
		      if (ns ==	hp)
		       switch(SelectBuffer[ns])	{
			   case ACTUATOR_SELECTION:
			       selection_mode = ACTUATOR_SELECTION;
			       break;
			   case SYSTEM_SELECTION:
			       selection_mode = SYSTEM_SELECTION;
			       break;
			   case GEOMETRY_SELECTION:
			       selection_mode = GEOMETRY_SELECTION;
			       break;
			   case LIGHT_SELECTION:
			       selection_mode = LIGHT_SELECTION;
			       break;
		       }
		      else {
			  item[ns-hp-1] =	SelectBuffer[ns];
			  number = ns-hp;
		      }
		    }
		    if (number == 0) item[0] = -1;
		}
		hp += numNames;
		
	}
	glPopAttrib() ;
	return(selection_mode);
}


// Callback for	mouse button presses and releases.
void dance::MouseCB(int	button,	int state, int x, int y)
{

    // set the pressed button id
    PressedButtonID = button ;
    if ( x < 0 || y < 0 )
	{
	    // danceTcl::OutputMessage("x,y = %d, %d", x, y) ;
	    return ;
	}

	// Get window parameters.
	FocusWindow = AllViews->getViewFocus();
	if (FocusWindow == NULL) return;

	int width,height;
	int numSelected	= 0;
	m_ModifierKey = glutGetModifiers();

	FocusWindow->getSize(&width,&height);
	Event event;
	event.setWindow(FocusWindow, x,y, width,height);
	event.setButtons(button,state);

	if (state == GLUT_DOWN)
	    InitMousePosition =	1;

	static int item[256];
	item[0]	= -1;

	DSystem *active = (DSystem *) AllSystems->getActive();
	switch(AppMode)	{
	   case actuator_mode:
		if	(state == GLUT_DOWN) {
		    if (handleSelection(x,y,button,numSelected,item,ACTUATOR_SELECTION) == ACTUATOR_SELECTION) {
			PickedItem = item[0];
			DActuator *wactuator = (DActuator *) AllActuators->get(PickedItem);
			event.setSelected(numSelected,item);
			if (wactuator)
			{
			    AllActuators->setActive(PickedItem) ;
			    wactuator->InteractStart(&event);
			}
			else
			    PickedItem	= -1;
		    }
		    else {
			// Check if there is an	active actuator.
			DActuator *wactuator = (DActuator	*)AllActuators->getActive();
			if (wactuator)	{
			    event.setSelected(numSelected,item);
			    wactuator->InteractStart(&event);
			}
			else {
			    LastMode =	actuator_mode;
			    AppMode = camera_mode;
			    handleCameraButtons(FocusWindow,	button,	state, x, y, width, height);
			    PickedItem	= -1; 
			}
		    }
		}
		else {
		    if (PickedItem >= 0) {
			DActuator *wactuator	= (DActuator *)AllActuators->get(PickedItem);
			if (wactuator)
			    wactuator->InteractEnd(&event);
			PickedItem = -1;
		    }
		}
		break;
	   case light_mode:
		if (handleSelection(x,y,button,numSelected,item,LIGHT_SELECTION) == LIGHT_SELECTION)
		{
		    PickedItem = item[0];
		    AllLights->setActive(PickedItem) ;
		}
		else {
		    LastMode = light_mode;
		    AppMode = camera_mode;
		    handleCameraButtons(FocusWindow, button, state, x,y,width,height);
		    PickedItem = -1; 
		}
		break;
	   case system_mode:
		if (state == GLUT_DOWN) {
		    if (handleSelection(x,y,button,numSelected,item,SYSTEM_SELECTION) 
			== SYSTEM_SELECTION) 
		    {
				PickedItem = item[0];
				DSystem *sys = (DSystem *) AllSystems->get(PickedItem);
				event.setSelected(numSelected,item);
				if( sys )
				{
					AllSystems->setActive(PickedItem);
					if( sys->InteractStart(&event) == 0 )
					{
						AppMode = command_mode;
						PickedItem = -1;
					}
				}
				else
					PickedItem = -1;
		    }
		    else {
			// Check if there is an	active system.
			DSystem *sys = (DSystem *)AllSystems->getActive();
			if (sys)	{
			    event.setSelected(numSelected,item);
			    if( sys->InteractStart(&event) == 0 )
			    {
				AppMode = command_mode;
				PickedItem = -1;
			    }
			    PickedItem = AllSystems->getIndex(sys->getName()) ;
			}
			else {
			    danceTcl::OutputMessage("No systems present."
						    "Please create one first") ;
			    LastMode =	system_mode;
			    AppMode = camera_mode;
			    handleCameraButtons(FocusWindow, button, state, x, y, width, height);
			    PickedItem	= -1; 
			}
		    }
		}
		else {
		    if (PickedItem >= -1) {
			DSystem *sys= (DSystem *)AllSystems->get(PickedItem);
			if (sys)
			{
			    if( sys->InteractEnd(&event) == 0 )
				PickedItem = -1;
			}
		    }
		}
		break;
	    case pointer_mode:
		// Move the pointer to the mouse position.
  		FocusWindow->getWorldCoords(CursorPosn,x,y);
		FocusWindow->postRedisplay();
		break;
	    default: // camera navigation, joint	editing
		handleCameraButtons(FocusWindow, button, state, x, y, width, height);
		
		// We only want to set	the last mode if we are	clicking up.
		if (state == GLUT_UP) 
		    AppMode = LastMode;
		
	} // end switch	of edit	modes
	FocusWindow->postRedisplay() ;
}

// EnterCommandMode:
//	Enters command mode, clearing out picked items and the
//	cursor position.
//
void dance::EnterCommandMode(void)
{	
    PickedItem = -1;
    AppMode =	command_mode;
    LastMode = command_mode;
}



/**
 * Gets a bounding box for the entire scne.
 *
 * <full description>
 * @param void
 * @return BoundingBox *
 */
BoundingBox *dance::GetSceneBox(void)
{
      static BoundingBox b; // Use static to allow returnable pointer.
	  b.MakeEmpty();

	  // Loop through objects.
	  int i;
	  for( i = 0 ; i < AllSystems->size() ;	i++ )
	  {
	      BoundingBox box;
	      DSystem *obj = (DSystem *) AllSystems->get(i);
	      obj->calcBoundingBox(&box) ;
	      b.merge(&b,&box);
	  }
	  
	  // Loop through actuators.
	  for (	i=0; i < AllActuators->size(); i++)
	  {
	      BoundingBox box;
	      DActuator *wactuator	= (DActuator *)AllActuators->get(i);
	      if (wactuator->calcBoundingBox(&box))
		  b.merge(&b,&box);
	  }
      

      // If bounding box is empty, do NOT attempt to change the viewing volume
      // to be an empty box. Instead, we return early (and keep the current viewing
      // volume.
      if (b.isEmpty())
		return NULL;
	  return (&b);
    
}

// Initialize visual objects here.
//
// minx,miny,minz,
// maxx,maxy,maxz: Bounding box	of initial geometry.
static void initializeObjects(double *minx, double *miny, double *minz,
							  double *maxx, double *maxy, double *maxz)
{
	// If you have custom geometry.	You can	intialize and
	// customize the object	here. You will also need to
	// compute a bounding box for the geometry to ensure
	// the camera initially	encompasses the	geometry.

	// Initial bounding box.
	*minx =	-20.0;
	*miny =	-20.0;
	*minz =	-20.0;

	*maxx =	20.0;
	*maxy =	20.0;
	*maxz =	20.0;
}

void dance::mainLoop(ClientData	clientData)
{
    if (dance::AllViews->size() > 0) // Enter the event loop
		glutMainLoop();
}

void dance::IdleCB()
{
    int	i ;
    
    
    int isSimulating = FALSE ;
    // this do { while} loop allows the simulation
    // to run in blocking mode. No events are processed Tcl or glut
    // until the simulation has finished.
	
    if( (m_SimulBlock != TRUE ) || (AllSimulators->GetState() != SM_RUNNING))
	danceTcl::checkEvents() ;
    do 
    {
	int redisplay = 0 ;
 
	// if needed simulate
	if( AllSimulators->GetState() == SM_RUNNING )
	{
	    isSimulating = TRUE ;
	    
	    // redisplay shows whether we want to redisplay
	    // because of simulation or not.
	    redisplay = AllSimulators->Step() ;
	}
	else
		isSimulating = FALSE ;
       
	for( i = 0 ; i < AllActuators->size() ; i++ )
	{
	    redisplay += AllActuators->get(i)->IdleCB() ;
	}
	
	// if something changed redisplay
	if ((m_NoDisplay == FALSE) && (redisplay > 0))
	{ 
	    if( dance::m_SimulBlock != TRUE )
	    {
		if (dance::UpdateAllWindows)
		    AllViews->postRedisplay();
		else
		    AllViews->postRedisplayActive()	;
		// Must come after redisplay calls to redisplay proper active window
	    }
	    else
	    {
		// -- This works in case we invoked blocked simulation --
		if( (AllViews != NULL) && (AllViews->getActive() != NULL ) )
		{
		    DisplayCB() ;

		}
	    }
	    // --- end of the above ------
	    if (FitviewAlways == TRUE)
			AllViews->FitView();
	} 

	
    } while ((dance::m_SimulBlock == TRUE) && (isSimulating == TRUE)) ;

    // restore the non blocking mode
    m_SimulBlock = FALSE ;
    
    return ;
}

void dance::DeleteAll()
{
	delete AllSystems;
	delete AllActuators;
	delete AllGeometry;
	delete AllLights;
	delete AllViews;
	delete AllSimulators;
}

void dance::SetMode(char *name)
{
    if (strcmp(name,"system") == 0) {
	danceTcl::OutputMessage( "System edit mode on\n");
	dance::AppMode = system_mode;
    }
    else if	(strcmp(name,"actuator") == 0) {
	danceTcl::OutputMessage("Actuator edit	mode on.\n");
	dance::AppMode = actuator_mode;
	dance::m_DisplayActuators = TRUE;
    }
    else if	(strcmp(name,"camera") == 0)	{
	danceTcl::OutputMessage("Camera edit mode on.\n");
	dance::AppMode = camera_mode;
	dance::LastMode = camera_mode;
    }
    else if	(strcmp(name,"light") == 0) {
	danceTcl::OutputMessage("Light	edit mode on.\n");
	dance::AppMode = light_mode;
    }
    else if	(strcmp(name,"command") == 0) {
	danceTcl::OutputMessage("Back to command mode.\n");
	dance::EnterCommandMode();
    }
    else
	danceTcl::OutputMessage( "ERROR: invalid edit mode.\n");
}

void dance::Refresh(void)
{
    AllViews->postRedisplay() ;
}
