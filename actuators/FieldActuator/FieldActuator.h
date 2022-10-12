#ifndef	_FIELD_ACTUATOR_H_
#define	_FIELD_ACTUATOR_H_ 1

#include <stdlib.h>
#include "Ball.h"
#include "BallMath.h"
#include "DActuator.h"

enum FieldActuatorParms
{
	pDirection,
	pMagnitude,
	pPosition
};

class FieldActuator : public DActuator {
	private:
		double startVector[3];
		double position[3];
		double direction[3];
		double magnitude;
		BallData *arcball;
		int interactionMode;

		Tcl_Interp *TclInterp;

	public:
		FieldActuator();
		~FieldActuator();

		PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
		void bindCommands(Tcl_Interp *interp, ClientData data, int noDisplay=0)	{TclInterp = interp;};
		void output(int	mode);
		void Interact(Event *event) ;
		int InteractEnd(void);
		int InteractStart(Event *event) ;
		void ExertLoad(DSystem *ao, double time, double dt,
			       double *state, double *dstate);
		void print(void);
		void saveScript(char *)	;
		void saveScript(FILE *)	;
		int commandPlugIn(ClientData clientData, Tcl_Interp *interp,
				 int argc, char	**argv)	;
		int set(Tcl_Interp *interp, int	argc, char **argv) ;


};


#endif
