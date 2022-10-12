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



#ifndef	_PLUGINMANAGER_H_
#define	_PLUGINMANAGER_H_ 1

#include "DanceObjectList.h"
#include "PlugIn.h"

class PlugInManager : public DanceObjectList
{

private:
	PlugIn *LoadPlugIn(char	*filename);
	char *GetPlugInFilename(char *type);

public:
	int IsPlugin(char *type);
	PlugIn *GetInstance(Tcl_Interp *interp,	char *type, char *name,
			    int	argc, char **argv);
	PlugIn *AddProxy(char *type);

} ;

#endif
