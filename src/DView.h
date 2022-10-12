/**************************************************************************
	----------------------------------------------
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



#ifndef	_VIEW_H_
#define	_VIEW_H_ 1

#include <tcl.h>
#include "GL/glutShared.h"

#include "DanceObject.h"
#include "Ball.h"

#ifdef SGI
#define	WINTITLEBAR_HEIGHT 24
#define	WINFRAME_WIDTH 8
#else
#define	WINTITLEBAR_HEIGHT 17
#define	WINFRAME_WIDTH 5
#endif

#define	SCALE_FOR_BB 1.0

enum EditModes {
	camera_arcball,
	camera_pan,
	camera_zoom
};

enum BufferModes {
	normal_mode=1,
	depth_mode=2
};

#define VIEWSTATESIZE 11
enum ViewStateType {
	eTargetx,
	eTargety,
	eTargetz,
	eLeft,
	eRight,
	eTop,
	eBottom,
	eAngle,
	eAxisx,
	eAxisy,
	eAxisz
};

class DLLENTRY DView : public DanceObject	{
	private:

		int WindowID;

		int Lights;
		int Shadows;
		int Solids;

		float BackgroundColor[4];

		// Camera data
		double Dist;
		double Panx, Pany;
		double Target[3];
		BallData *Arcball;
		double *Modelview;


		// Handles zooming with	clipping
		double Virtual_near;
		double Limit_near;

		void usage(Tcl_Interp *interp);
                char m_DumpDirectory[MAX_LINE] ;
                char m_HalfSizeCom[MAX_LINE] ;
                int m_FrameNumber ;
                int m_IsDumped ;
                char m_DumpFileName[MAX_LINE] ;
                void SetStartFrameNumber(int n) {m_FrameNumber = n;} ;
  
	public:
		void targetCamera(GLdouble target[3]);
		double getDepth(int x, int y);
		inline void adjustOffset(double dist) { Dist = dist;};
		double getFrustumWidth(double depth);
		void getNearFar(double *nearplane, double *farplane);
		void print(FILE *fptr);
		static int MasterWindow;
        int KeyboardCB( unsigned char key, int x, int y ) ;
		int X;
		int Y;
		int Width;
		int Height;
		int Perspective;

		// Projection data
		int ProjectionType;
		double *Projection;

		double Left,Right,Bottom,Top,Near,Far;

		DView();
		DView(Tcl_Interp	*interp,  char *name,int argc, char **argv);
		~DView();

                static void ReshapeCB(int width, int height);
	
		void adjustArcballCamera(HVect coords);
		void adjustArcballCircle(double	x, double y, double radius);
		void AttachCamera(BoundingBox *box);
		void attachMenu(int menu);
		void beginInteraction(int mode);
		int Command(ClientData clientData, Tcl_Interp *interp,
			    int	argc, char **argv);
		int create(char	*name, char *typeString, int x,	int y, int width, int height);
		void destroy();
		void detachMenu(int menu);
		void dollyCamera(double	percentage);
		void dollyCameraDist(double dist);
		void drawArcball();
		inline void end() {glutSwapBuffers();};
		void endInteraction(int	mode);
		void getBackgroundColor(float color[4]);
		inline double getCameraDistance() { return Dist;};
		void getCameraParms(double *dist,
				    double *panx, double *pany,	double target[3]);
		void getCameraOrientation(float	mat[4][4]);
		void getCameraTransformation(float mat[4][4]);
		void getProjection(double *projection);
		void getReferenceFrame(double basisX[3], double	basisY[3], double basisZ[3]);
		void getBounds(double *left, double *right, double *top,
			double *bottom);
		void getCenter(double center[3]);
		inline void getPosition(int *x,	int *y)	{ *x=X;	*y=Y;};
		void getSize(int *width, int *height);
		void getViewPlane(double basisX[3], double basisY[3]);
		void getViewport(int viewport[4]);
		inline int  getWindowID() {return WindowID;};
		int getWindowIndex(char	*name);
		void getWindowCoords(double *world, double *win);
		double getWorldCoords(double *world, int x, int y, double	z=-1.0);
		inline int isLights() {	return(Lights);};
		inline int isShadows() { return(Shadows);};
		inline int isSolids() {	return(Solids);};
		void moveCamera(double dist,
				double panx, double pany,
				double target[3],HVect arccoords);
		void panCamera(double panx, double pany);
		void pickProjection(int	x, int y, double delX, double delY);
		void PositionCamera();
		inline void postRedisplay(void)	{ if (WindowID > 0) {set();glutPostRedisplay();}};
		void resetCamera();
		inline void set() {if (WindowID	!= -1) glutSetWindow(WindowID);};
		void setArcballConstraints(AxisSet axisset);
		void setBackgroundColor(float r, float g, float	b, float a);
		void setCamera(double scale,
			       double minx, double miny, double	minz,
			       double maxx, double maxy, double	maxz);

		void setProjection();
		void setProjection(
			double left, double right,
			double bottom, double top,
			double nearV, double farV);
		void start();
		void zoomCamera(double percentage);

                int GetStateSize(void) { return VIEWSTATESIZE ;} ;
                void UpdateState(double *state) ;
                void GetState(double *state) ;

                void SaveFrame(void) ;
                void DumpPPM(FILE *fp, int buffer = 0) ;
                void DumpPPM(char *fname) ;
                int IsDumped(void) { return m_IsDumped ;} ;
};
#endif
