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


#ifndef	_DANCE_H
#define	_DANCE_H_ 1

#include <stdio.h>
#include <tcl.h>
#include "defs.h"


class DanceObject;
class DanceObjectList;
class PlugInManager;
class DSimulatorManager;
class DView ;
class ViewManager ;
class BoundingBox;


class Proximity;
class Volume;

// Various selection modes
#define	SYSTEM_SELECTION 1001
#define	GEOMETRY_SELECTION 1002
#define	ACTUATOR_SELECTION 1003
#define	LIGHT_SELECTION	1004

// Various enumerations;
enum AppModeStates {
	actuator_mode,
	command_mode,
	camera_mode,
	arcball_mode,
	pan_mode,
	zoom_mode,
	dolly_mode,
	light_mode,
	system_mode,
	pointer_mode
};


class DLLENTRY dance {
	public:
		static void DeleteAll();
		static Volume * m_AllVolumes;
        static int m_SimulBlock ;

		static int m_ModifierKey;
		static DView *FocusWindow;

	    static double CursorPosn[3];
	    static int m_NoDisplay ;

	    // Flags
	    static int m_DisplayActuators;
	    static int AppMode;
	    static int AppModeModifier;
	    static int FitviewAlways;
	    static int LastMode;
	    static int Monitorpts ;
            static int UpdateAllWindows;

		static Proximity *m_Proximity;

	    static DanceObjectList **DanceLists;
	    static int numDanceLists;

	    static DanceObjectList *AllActuators;
	    static DanceObjectList *AllLights;
	    static DanceObjectList *AllSystems;
	    static DanceObjectList *AllGeometry;
	    static ViewManager *AllViews;
            static PlugInManager *AllPlugIns;
	    static DSimulatorManager *AllSimulators;

	    static DanceObject *getInstance(Tcl_Interp *interp,
					    char *type,	char *name, int	argc, char **argv);
	    static void	getLists(int *number, DanceObjectList ***list);

	    static DanceObjectList *getList(char *listname);
	    static void	initialize(int argc, char **argv);
	    static void	parseArguments(int argc, char **argv) ;

	    // Callbacks
	    static void	KeyboardCB(unsigned char key, int x, int y);
	    static void	DisplayCB(void);
	    static void	IdleCB(void);
	    static void	MotionCB(int x,	int y);
	    static void	MouseCB(int button, int	state, int x, int y);
	    static void	PassiveMotionCB(int x, int y);

	    // View related
	    static void	dumpWindow(DView *, FILE	*) ;
	    static BoundingBox *GetSceneBox(void);

	    static void	EnterCommandMode(void);

	    // Interaction related
	    static int handleSelection(int x, int y, int button, int &number,
			int *item, int type);
	    static void	handleActuatorEdits(DView *focus, int x,	int y,
			int width, int height, int diffx, int diffy);
	    static void	handleCameraButtons(DView *focus, int button, int state,
			int x, int y, int width, int height);
	    static void	handleCameraMotions(DView *focus, int x,	int y,
			int width, int height, int diffx, int diffy);
            static void	handleLightEdits(DView *focus, int x, int y,
			int width, int height, int diffx, int diffy);
            static void mainLoop(ClientData	clientData);

            static void saveKeyFrame(DView *view) ;
            static void SetMode(char *name) ;
  static void Refresh(void) ;
private:
		static DanceObject * m_ActiveObject;
};
#endif



