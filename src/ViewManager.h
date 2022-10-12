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



#ifndef	_VIEWMANAGER_H_
#define	_VIEWMANAGER_H_	1

#include "DanceObjectList.h"

class BoundingBox;

class DLLENTRY ViewManager : public DanceObjectList
{
private:
	int QuadViewWidth, QuadViewHeight;

public:
	int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
	ViewManager();
	ViewManager(int	argc, char **argv);
	~ViewManager();

	DView *getViewFocus();

	void AttachCameras(BoundingBox *box);
	void attachMenu(int menu);
	int createQuadView();
	void detachMenu(int menu);
    void FitView();
	int KeyboardCB( unsigned char key, int x, int y );
	void move(void);
	void postRedisplay(void);
	void postRedisplayActive(void);
	static void reshape(int	width, int height);
} ;

#endif
