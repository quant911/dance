#include "dance.h"
#include "ViewManager.h"
#include "DView.h"

static DView *QTop	= NULL;
static DView *QRight = NULL;
static DView *QFront = NULL;
static DView *QPersp = NULL;

ViewManager::ViewManager()
{
	QuadViewWidth =	-1; QuadViewHeight = -1;
}



#ifdef macintosh
extern "C" {
extern void my_glutInit(int *argc, char	**argv);
}
#endif

ViewManager::ViewManager(int argc, char	**argv)
{
	QuadViewWidth =	-1; QuadViewHeight = -1;

	// if no display is used do not intialize glut
	if( dance::m_NoDisplay == FALSE )
	{
		// Initialize glut
#ifdef macintosh
		// use custom glutInit that doesn't collide with tcl when handling
		// events.
		my_glutInit(&argc,argv);
#else
		glutInit(&argc,argv);
#endif
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	}
}

void ViewManager::AttachCameras(BoundingBox *box)
{
	for (int i=0; i	< size(); i++) {
		DView *view = (DView *)get(i);
		if (view->getWindowID()	!= -1)
		    view->AttachCamera(box);
	}

}

ViewManager::~ViewManager()
{
		for (int i=0; i	< numDanceObjects; i++)
			if (DanceObjects[i]) {
				delete DanceObjects[i];
				DanceObjects[i] = NULL;
			}
		numDanceObjects = 0;
		if (DView::MasterWindow != -1)
			glutDestroyWindow(DView::MasterWindow);

}

// attachMenu
//
void ViewManager::attachMenu(int menu) {
	for (int i=0; i	< numDanceObjects; i++)	{
		DView *view = (DView *)get(i);
		if (view->getWindowID()	!= -1)
		    view->attachMenu(menu);
	}

}

// detachMenu
//
void ViewManager::detachMenu(int menu) {
	for (int i=0; i	< numDanceObjects; i++)	{
		DView *view = (DView *)get(i);
		if (view->getWindowID()	!= -1)
		    view->detachMenu(menu);
	}

}

void ViewManager::FitView()
{  
	BoundingBox *box = dance::GetSceneBox();
	AttachCameras(box);
}

// getViewFocus
//
DView *ViewManager::getViewFocus()
{
	int winID = glutGetWindow();
	DView *view = NULL;
	for (int i= 0; i < numDanceObjects; i++) {
		view = (DView *)get(i);
		if (view->getWindowID()	== winID)
			break;
	}
	return(view);

}

// createQuadView:
//	Creates	the classic quad view of four windows.
//
//     returns:	1 on success, 0	on failure.
//
int ViewManager::createQuadView()
{
	int rootwidth =	glutGet((GLenum)GLUT_SCREEN_WIDTH);
	int rootheight = glutGet((GLenum)GLUT_SCREEN_HEIGHT);

	int x =	(int)(rootheight*.1);
	int y =	(int)(rootheight*.1);
	int width = (int)(rootheight*.75);
	int height= (int)(rootheight*.75);
	QuadViewWidth =	width;
	QuadViewHeight = height;

	// Calculate window height and width minus the title bar and
	// frames.
	int new_width =	(width-4*WINFRAME_WIDTH)/2;
	int new_height = (height - 4*WINFRAME_WIDTH - 2*WINTITLEBAR_HEIGHT)/2;

	// Top
	QTop = new DView;
	QTop->create("top", "top",x,y,new_width,new_height);
	glutReshapeFunc(reshape);
	add(QTop);

	// Front
	QFront = new DView;
	QFront->create("front","front",x,y+height/2,new_width,new_height);
	glutReshapeFunc(reshape);
	add(QFront);

	// Right
	QRight = new DView;
	QRight->create("right","right",x+width/2,y+height/2,new_width,new_height);
	glutReshapeFunc(reshape);
	add(QRight);

	// Perspective
	QPersp = new DView;
	QPersp->create("perspective","persp", x+width/2,y,new_width,new_height);
	glutReshapeFunc(reshape);
	add(QPersp);

	AttachCameras(NULL);
	return(1);
}

int ViewManager::KeyboardCB( unsigned char key, int x, int y )
{
    int value = 0;
    if( dance::FocusWindow != NULL )
    {
	value = dance::FocusWindow->KeyboardCB(key, x,y) ;
    }
    
    if( value != 0 ) return value ;
    
    switch((char)key)
    {
	case 'F':
	    FitView();
	    value = 1;
	    break;
    }
    return value;
}

// move:
//	Callback that moves all	the Quadview windows.
//
//	view: View ID of the active window.
//
void ViewManager::move(void)
{

    int	activeWindow = glutGetWindow();

    // We only want to check for moving	windows	periodically to
    // save computational expense. This	also prevents racing conditions
    // where a window has been moved, but hasn't been updated yet,
    // causing a chain reaction	to occur as all	the other windows are
    // needlessly moved	temporarily to their previous positions	and back
    // again to	their new positions.
    // As a result, the	upper limit of count should be set accordingly for
    // different windowing systems. 10000 seems	like a good figure.

    // Commented out, since now	called explicitly by user.
    // static int count	= 0;
    // if (++count < 10000) return;
    // count = 0;

    // WARNING:	This routines assumes that Views[view] == view+1
    // Makes checks faster.
    for	(int i = 0; i <	size();	i++) {
	 DView *view = (DView *)get(i);
	 glutSetWindow(view->getWindowID());

	 // Get	current	x and y	offsets	for window.
	 int currx = glutGet((GLenum)GLUT_WINDOW_X);
	 int curry = glutGet((GLenum)GLUT_WINDOW_Y);

	 // Get	current	width and height of window.
	 int currw = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	 int currh = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	 // Check if window was	moved.
	 if (currx != view->X || curry != view->Y)
	     //	The window *might* have	moved. Check if	it really has.
	     if	(currw == view->Width && currh == view->Height){
		 int diffx = currx - view->X;
		 int diffy = curry - view->Y;
		 view->X = currx; view->Y = curry;
		 glutPopWindow();

		 // Position the other windows.
		 int index = getIndex(view->getName());

		 for (int j = 1; j <= size()-1 ; j++) {
		   DView	*wview = (DView *)get((index+j)%size());
		   wview->X += diffx;
		   wview->Y += diffy;
		   glutSetWindow(wview->getWindowID());
		   glutPositionWindow(wview->X,	wview->Y);
		   glutPopWindow();
		 }
#ifdef macintosh
		 // Only really	needed for active moving
		 glutSetWindow(activeWindow);
		 glutPopWindow();
#endif
		 break;
	     } // end check if window moved.
     } // end for

     glutSetWindow(activeWindow);
}

// postRedisplay:
//	Send a signal to redisplay all views.
//
void ViewManager::postRedisplay()
{
       for (int	i=0; i < size(); i++) {
		DView *view = (DView *)get(i);
		if (view->getWindowID()	!= -1) view->postRedisplay();
       }
}

// postRedisplayActive:
//
void ViewManager::postRedisplayActive()
{
	DView *view = getViewFocus();
    if (view)
	    view->postRedisplay();
}

// reshape:
//	Reshapes the QuadView to stay within the defined size.
//
// NOTE: No reshaped events are	generated if the width and height are
// unchanged.
void ViewManager::reshape(int width, int height)
{
	int winID = glutGetWindow();
	glViewport(0,0,width,height);

	// Determine which window was initially	reshaped and define
	// complement windows that are associated with this window.
	// xcomp shares	the same x offset characteristics while
	// ycomp shares	the same y offset characteristics.
	// window stores the window initially reshaped.
	//
	DView *window, *xcomp, *ycomp;
	if (winID == QTop->getWindowID()) {
		window = QTop;
		xcomp =	QFront;	ycomp =	QPersp;
	}
	else if	(winID == QFront->getWindowID()) {
		window = QFront;
		xcomp =	QTop;
		ycomp =	QRight;
	}
	else if	(winID == QRight->getWindowID()) {
		window = QRight;
		xcomp =	QPersp;	ycomp =	QFront;
	}
	else if	(winID == QPersp->getWindowID()) {
		window = QPersp;
		xcomp =	QRight;	ycomp =	QTop;
	}

	// Adjust aspect ratio of window.
	GLdouble proj_height = window->Top - window->Bottom;
	GLdouble proj_width = ((double)width/(double)height)*(double)proj_height;
	window->Right =	proj_width/2.0;
	window->Left = -1*proj_width/2.0;


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (window->Perspective	== 0)
	    glOrtho(window->Left,window->Right,	window->Bottom,window->Top,
		    window->Near,window->Far);
	else
	    glFrustum(window->Left,window->Right, window->Bottom,window->Top,
		      window->Near,window->Far);
	glGetDoublev(GL_PROJECTION_MATRIX,window->Projection);

	// New x and y offsets for window.
	int newx = glutGet((GLenum)GLUT_WINDOW_X);
	int newy = glutGet((GLenum)GLUT_WINDOW_Y);

	// Old x and y offsets for window.
	int oldx = window->X;
	int oldy = window->Y;

	// Displacement	change in window size.
	int dispx = width - window->Width;
	int dispy = height - window->Height;

	// Reshape all quad view windows.

	// There are four main cases:
	// (oldx == newx) , (oldx != newx), (oldy == newy), (oldy != newy)
	// Each	of these cases is grouped into similar adjustments for two
	// groups of windows which affect other	windows	in about the same
	// way.
	//
	if (oldx == newx) {
		if (window == QRight ||	window == QPersp)
			xcomp->Width +=	dispx;
		else { // window == QTop || window == QFront
			xcomp->Width +=	dispx;
			QRight->X += dispx;
			QRight->Width -= dispx;
			QPersp->X += dispx;
			QPersp->Width -= dispx;
		}
	}
	else { // (oldx	!= newx)
		if (window == QRight ||	window == QPersp) {
			QTop->Width -= dispx;
			QFront->Width -= dispx;
			xcomp->X -= dispx;
			xcomp->Width +=	dispx;
		}
		else { // window == QTop || window == QFront
			xcomp->X -= dispx;
			xcomp->Width +=	dispx;
		}
	}

	if (oldy == newy) {
		if (window == QFront ||	window == QRight)
			ycomp->Height += dispy;

		else { // window == QTop || window == QPersp
			ycomp->Height += dispy;
			QFront->Y += dispy;
			QFront->Height -= dispy;
			QRight->Y += dispy;
			QRight->Height -= dispy;
		}
	}
	else { // (oldy	!= newy)
		if (window == QFront ||	window == QRight) {
			QTop->Height -=	dispy;
			QPersp->Height -= dispy;
			ycomp->Y -= dispy;
			ycomp->Height += dispy;
		}
		else { // window == QTop || window == QPersp
			ycomp->Y -= dispy;
			ycomp->Height += dispy;
		}
	}


	// Resize the other three windows. No need to reshape the window
	// that	triggered this callback	since it was already done by the
	// user.

	// Start index at zero.	Assumption is windowID increments as
	// windows are added.
	int index = window->getWindowID()-1;
	for (int i=index + 1; i	< index	+ 4; i++)
	{
		DView *wview = NULL;
		if (i%4	== 0) wview = QTop;
		if (i%4	== 1) wview = QFront;
		if (i%4	== 2) wview = QRight;
		if (i%4	== 3) wview = QPersp;
		wview->set();
		glutPositionWindow(wview->X, wview->Y);
		glutReshapeWindow(wview->Width,	wview->Height);
	}

	// Record new window changes for the triggering	window.
	window->X = newx;
	window->Y = newy;
	window->Width =	width;
	window->Height = height;
}


int ViewManager::Command(ClientData clientData, Tcl_Interp * interp, int argc, char * * argv)
{
	if (strcmp(argv[0],"refresh") == 0)
		postRedisplay();
	else if (strcmp(argv[0],"fitview") == 0)
		FitView();
	return TCL_OK;
}
