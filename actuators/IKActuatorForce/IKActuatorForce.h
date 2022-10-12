#ifndef	_IKActuatorForce
#define	_IKActuatorForce

#include "defs.h"
#include "DActuator.h"
#include "list.h"
#include "GLutilities.h"
#include "IPoseGraph.h"

class ArticulatedObject ;

/***************************************************************************
	----------------------------------------------
	ORIGINAL AUTHOR: Gordon Cook
	-----------------------------------------------
		gcook@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project

 **************************************************************
 ******General License Agreement and Lack of Warranty ***********
 ****************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/


class IKassembler;
class Link;
class IK_Joint;
class Joint;
class DOFrecord;

const int MAXDIM = 100 ;

class IKActuatorForce : public DActuator {
private:
  ArticulatedObject *m_artObj;
  list *recs;
  Link *root;
  IKassembler *assembler;
  double m_graphicsRad;
  int newConstraintType;
  void findChainBody(Link *previousLink, Link *rootLink, Link *endEffector, list *chain);
  //figure out so only WrootMat needed.
  double initialRootMat[4][4];
  double initialWRootMat[4][4];
  double initialRootPos[3];
  double originalJointPos[3];

  int numConstraints;
  int Actuator_mode;
  int solveMode;
  IKconstraint *activeConstraint;
 
  DOFrecord *activeJoint;
  
  double m_p[3] ;
  double m_v1[3] ;
  double m_v2[3] ;

  // added by petros
  double m_q[MAXDIM] ;
  double m_kd[MAXDIM] ;
  double m_ks[MAXDIM] ;
  double m_q_prev[MAXDIM] ;
  double m_kd_prev[MAXDIM] ;
  double m_ks_prev[MAXDIM] ;
  int m_usePG ;
  IPoseGraph m_pg ;
  int m_isSimInit ;
  int m_needsSolving ; // When m_solveContSim is FALSE it ensures the we solve once only
  int m_solveContSim ; // is TRUE then the solver solves at every time step
                               // otherwise solve once after the button is released.


  void ApplyState(double *qpos, DSimulator *sim, 
		  double *state, double *dstate);
  void Reset(ArticulatedObject *ao) ;
  void LinkVariables(ArticulatedObject *ao) ;
  void UnlinkVariables(ArticulatedObject *ao) ;
  void SetJointState(int nj, int ndof) ;
  void SetJointState(int argc, char **argv) ;
  void updateVariables(void) ;
public:
  IKActuatorForce() ;
  IKActuatorForce(ArticulatedObject *a);
  ~IKActuatorForce();
  PlugIn *Proxy(void);
  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  void output(int mode);
  int commandPlugIn(ClientData clientData, Tcl_Interp *interp,int argc, char **argv);
  int InteractStart(Event *event);
  void Interact(Event *event);
  int InteractEnd(Event *event);  

  void reset(void);   
  void setRoot(Link *r);
  void IKoutput(void);
  void solveIK();
  void findChain(Link *endEffector,list *chain);
  IK_Joint *createIKjoints(Link *endEffector);
  void updateJoints(void);
  void updateIKjoints(void);
  void setup(void);
  DOFrecord *copyJoint(Joint *j,int isReversed, int lastJointIsReversed,  DanceObject *lastJoint);
  IKconstraint *addConstraint(Link *endEffector);
  void removeActiveConstraint(void);
  void printOutChain(list *chain);	
  void multiplyMat(double a[4][4],double b[4][4],double result[4][4]);	
  void multiplyVec(double mat[4][4], double vec[3], double result[3]);   
  int handleSelection( DView *view, int x, int y, int button, int &number, int *item, int type);
  void setActiveConstraint(IKconstraint *aCon);
  void setActiveJoint(DOFrecord * aDOF);
  BoundingBox *calcBoundingBox(BoundingBox *b) ;
  void unLinkVariables(Tcl_Interp *interp) ;
  int linkVariables(Tcl_Interp *interp) ;
  void display(int mode);
  void HandleConstraintEdit(DView *focus, int button, int x, int y, int width, int height, int diffx, int diffy);
  void mulitplyVec(double mat[4][4], double vec[3], double result[3]);

  // added by petros
  void ExertLoad(DSystem *sys, double time, double dt,
		 double *state, double *dstate);
  void InitSimul(DSystem *sys, double time) ;
  void AtEndSimul(DSystem *sys, double time) ;
 };
#endif







