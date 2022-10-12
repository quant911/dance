#include <stdlib.h>
#include "defs.h"
#include "DActuator.h"
#include "dance.h"
#include "DanceObjectList.h"
#include "danceTcl.h"
#include "ViewManager.h"

DActuator::DActuator()
{
	controlled = 0;
	applyList = NULL;
	applyAllObjects	= 0;
	setBaseType("actuator");
}

/** Returns TRUE if ao is in the applylist of the actuator */
int DActuator::IsInApplyList(DanceObject *ao)
{
	if( applyAllObjects == 1 ) return TRUE ;

	AppliedObject *wApplyObject = applyList;

	while (wApplyObject) {
	    if (wApplyObject->ao == ao)
		break;
	    wApplyObject = wApplyObject->next;
	}
	if( wApplyObject ) 
		return TRUE ;
	else
		return FALSE ;	
}

void DActuator::removeAppliedObject(DanceObject *ao)
{

        // Search applyList for articulated object.
	AppliedObject *wApplyObject = applyList;

	AppliedObject *prevObject = NULL ;
	while (wApplyObject) {
	    if (wApplyObject->ao == ao)
		break;
	    prevObject = wApplyObject ;
	    wApplyObject = wApplyObject->next;

	}

	if( wApplyObject )if( wApplyObject )
	{
	    if(	prevObject == NULL )
		applyList = wApplyObject->next ;
	    else
		prevObject->next = wApplyObject->next ;
	    if(	wApplyObject->unitList != NULL )
		delete wApplyObject->unitList ;
	    delete wApplyObject	;
	}

	return ;
}

void DActuator::setAppliedObject(DanceObject *ao, int linkNo, int jointNo)
{

	// Search applyList for	articulated object.
	AppliedObject *wApplyObject = applyList;

	while (wApplyObject) {
		if (wApplyObject->ao ==	ao)
			break;
		wApplyObject = wApplyObject->next;
	}

	if (wApplyObject == NULL) {
	     wApplyObject = new	AppliedObject;
	     wApplyObject->ao =	ao;
	     wApplyObject->next	= applyList;
	     wApplyObject->unitList = NULL;
	     applyList = wApplyObject;
	}

	AppliedUnit *wunit = NULL;
	if (linkNo >= 0	|| jointNo >= 0) {
	    AppliedUnit	*wunit = new AppliedUnit;
	    wunit->linkNo = linkNo;
	    wunit->jointNo = jointNo;
	    wunit->pointOnObj[0] = 0.0;
	    wunit->pointOnObj[1] = 0.0;
	    wunit->pointOnObj[2] = 0.0;
	    wunit->forceOnObj[0] = 0.0;
	    wunit->forceOnObj[1] = 0.0;
	    wunit->forceOnObj[2] = 0.0;
	    wunit->index = -1;
	    wunit->modifier = -1;
	    wunit->next	= wApplyObject->unitList;
	    wApplyObject->unitList = wunit;
	}
}

void DActuator::setAppliedObject(DanceObject *ao, int linkNo,
	double pointOnObj[3], int index, int modifier)
{
	// Search applyList for	articulated object.
	AppliedObject *wApplyObject = applyList;

	while (wApplyObject) {
		if (wApplyObject->ao ==	ao)
			break;
		wApplyObject = wApplyObject->next;
	}

	if (wApplyObject == NULL) {
	     wApplyObject = new	AppliedObject;
	     wApplyObject->ao =	ao;
	     wApplyObject->next	= applyList;
	     wApplyObject->unitList = NULL;
	     applyList = wApplyObject;
	}

	AppliedUnit *wunit = NULL;
	if (linkNo >= 0) {
	    AppliedUnit	*wunit = new AppliedUnit;
	    wunit->linkNo = linkNo;
	    wunit->jointNo = -1;
	    memcpy(wunit->pointOnObj,pointOnObj,3*sizeof(double));
	    wunit->index = index;
	    wunit->modifier = modifier;
	    wunit->next	= wApplyObject->unitList;
	    wApplyObject->unitList = wunit;
	}
}


// command
//
int DActuator::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{

    if( DanceObject::Command(clientData, interp, argc, argv) == TCL_OK ) return TCL_OK ;

    DanceObject *ao ;
    // check actuator base class commands
    if (strcmp(argv[0],"apply") == 0) {
	if (argc <= 1) {
	    danceTcl::OutputMessage("USAGE:apply [all|<objectName>|",
			     "<objectName> <linkID>	[<jointID>]") ;
	    return TCL_ERROR;
	}
	else if (strcmp(argv[1],"all") == 0)
	{
	    setAppliedAllObjects();
	    return TCL_OK ;
	}
	else if (argc >= 1) {
	    ao = (DanceObject *)
	      dance::AllSystems->get(argv[1]);
	    if (ao == NULL )
	    {
		ao = (DanceObject *)
		  dance::AllActuators->get(argv[1]);
	    }
	    if( ao == NULL )
		ao = (DanceObject *) dance::AllViews->get(argv[1]) ;
	    if( ao == NULL )
		ao = (DanceObject *) dance::AllLights->get(argv[1]) ;
	    if( ao) {
		if (argc == 2)
		    setAppliedObject(ao);
		else {
		    int	linkID = atoi(argv[2]);
		    int	jointID	= -1;
		    if (argc ==	4)
			jointID	= atoi(argv[3]);
		    
		    setAppliedObject(ao,linkID,jointID);
		}

		danceTcl::OutputMessage("Object %s applied to actuator %s",
			argv[1],getName());
	    }
	    return TCL_OK ;
	}
	else {
	    danceTcl::OutputMessage("ERROR: Invalid arguments.") ;
	    return TCL_ERROR;
	}
	
    }
    else if( strcmp(argv[0], "remove") == 0	)
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("Expected: remove <object name>\n") ;
	    return TCL_ERROR;
	}
	DanceObject *ao = (DanceObject *)
	  dance::AllSystems->get(argv[1]);
	if( ao == NULL ) // try actuators
	{
	    ao = (DanceObject *) dance::AllActuators->get(argv[1]) ;
	}
	if( ao )
	{
       	    removeAppliedObject(ao) ;
	    danceTcl::OutputMessage("Removed object %s from actuator %s\n", ao->getName(),
		    this->getName()) ;
	    return TCL_OK ;
	}
	else
	{
	    danceTcl::OutputMessage("No such object or actuator!\n") ;
	    return TCL_ERROR ;
	}
    }
    
    return commandPlugIn(clientData, interp, argc, argv) ;
}

void DActuator::InitSimul(DSystem *ao, double time) 
{
    danceTcl::OutputMessage("Did you forget to initialize actuator %s for simulation?",
	   getName()) ;
}


