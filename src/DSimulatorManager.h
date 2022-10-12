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



#ifndef	_DSIMULATORMANAGER_H_
#define	_DSIMULATORMANAGER_H_	1

#include "defs.h"
#include "DanceObjectList.h"

enum {SM_RUNNING, SM_NOT_RUNNING, SM_PAUSED} ;


/**
 * This class manages all the simulators in the system
 * @author Victor Ng-Thow-Hing
 * @author Petros Faloutsos
 * @version $Id: DSimulatorManager.h,v 1.10 2000/09/19 21:46:46 pfal Exp $
 * @see DanceObjectList
 */
class DLLENTRY DSimulatorManager : public DanceObjectList
{
public:
	double m_CurrentTime;
	double m_DisplayTimeStep;
        double m_SimulationTimeStep ;
        double m_EndTime ;
        int m_state ;
        int m_autoMake ;

        int Simul(int argc, char **argv) ;
        void BuildSimulators(void) ;

	DSimulatorManager();
	~DSimulatorManager();

	int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);

	void InitInterface(Tcl_Interp *interp) ;
	void SetTime(double currTime, double displayTimeStep);
	int Step(void);
        void Start(void) ;
        void Pause(void) ;
        void Continue(void) ;
        void Stop(void) ; 
        int IsSimulating(void) ;
		int GetState(void) { return m_state;} ;
} ;

#endif
