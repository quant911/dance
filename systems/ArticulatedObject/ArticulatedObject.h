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

#ifndef	_ARTICOBJECT_H_
#define	_ARTICOBJECT_H_

//********************************************************
//-------- Articulated objects header file  --------------
//********************************************************

#include "defs.h"
#include "DSystem.h"
#include "Link.h"
#include "Joint.h"

#define MAX_LINKS 100
#define MAX_JOINTS 100

#ifdef WIN32
#ifdef _EXPORTING_AR
#define DLLENTRY_AR __declspec(dllexport)
#else
#define DLLENTRY_AR __declspec(dllimport)
#endif
#else
#define DLLENTRY_AR
#endif

enum ArtObjAppModeEnum {
  Normal_mode,
  Skeleton_creation_mode,
  Joint_edit_mode,
} ;

class DView ;
class DSimulator ;
class DSystem ;
//class SimulatorEvents ;
class BoundingBox ;

class DLLENTRY_AR ArticulatedObject : public DSystem {
public:
	friend Link;
	void DeleteLinkChildren(Link *wlink);
	int m_CheckCollisions;
	int isChangeAboveLinks(Link *distal);
	Joint * m_ActiveJoint;
    ArticulatedObject()	;
    ~ArticulatedObject() ;



    void print(FILE *fptr);
	void printFile(char *filename);
	
    void output(int mode);
    void displayLinks(int mode = 0) ;	// display links assuming that the transformation
				// matrices of each link are with respect to the
				// global frame
    void displayJoints(int mode	= 0) ;
    int	 areLinksRelativeToParent() { return treeFlag ;} ;
				// it true draw	each link with respect to each parent
    inline int getNumLinks() {return m_numLinks ;	};
    inline Link	** getLinks() {return &link[0] ; } ;
    inline Link	*getLink(int i)	{return	link[i]	; } ;
	Joint * getJoint(char *name);
    Link *getLink(char *name);
    inline int getNumJoints() {	return m_numJoints ; } ;
    Joint ** getJoints() { return &joint[0] ; }	;
    Joint *getJoint(int	) ;
    inline double *getCM(double	v[3]) {	VecCopy(v,m_cm) ; return &v[0] ; } ;
    inline double getMass() { return m_Mass ; } ;
    inline Link	*getActiveParent() { return m_ActiveParent ;} ;
    void getCurrentEndEffector(double pt[3]) ;

    void changeToLocal() ;
    void changeToGlobal() ;
    void translate(Vector) ;	// translate object
    void moveJointAndParents(int jointID, double pos[3]);
    void moveJointAndChildren(int jointID, double pos[3]);
    void addJoint(Joint	*) ;
    void removeLink(Link *) ;
    virtual void saveKeyFrame (void) {return;};
    // set functions
    int	setNumLinks(int) ;
    int	setNumJoints(int) ;
    void setJointParam(int nj,int ax, double stif, double damp)	;
    void addLink(Link *) ;
    Link *addLink(double pt1[3],double pt2[3]) ;
    double *calcCM(void) ;
    double *calcCMVelocity(Vector vcm) ;

    void setCurrentEndEffector(double pt[3]) ;
    inline void	setActiveParent(Link *l) { m_ActiveParent	= l ; }	;
    int	simul(void);

  void BuildAndLinkSimulator(void) ;
  int loadVelocities(char *fname)  ;
  int	loadSdfast(char	*filename) ;
  int writeSdFile(char *filename = NULL) ;
  void WriteMayaFile(char *filename = NULL) ;
  void WriteBVHFile(char *filename) ;
  void WriteBVHFile(FILE *fp) ;
  int ReadBVHFile(FILE *fp) ;
  int ReadBVHFile(char *filename) ;
  virtual int saveObj(Tcl_Interp *interp, char format[256], char *filename);
  // int	simul(ClientData clientdata, Tcl_Interp	*interp, int argc, char	**argv)	;
  // int	SetParamAndInitSimul(Tcl_Interp *interp, int argc, char **argv) ;
    int	loadStateConfig(char *fname = NULL);
    int	saveStateConfig(char *fname = NULL);

    int GetStateSize(void) ;
    void GetState(double *state) ;
    void UpdateState(double *state) ;
    void revertToLast(void);
    void SetLastState(void);
    void updateStateConfig(int index = -1);

  //int  InvKinSim(double *dq, int *nq,
  //			    int *nlinks,
  //			    int *mapc,
  //			    int *chain,
  //			    int rootLink, int endEffLink,
  //			    Vector localPoint,
  //			    Vector dpos, Vector dorien);
  
  int commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);
  int ReadChannels(char *line, Joint *joint) ;

	int combineLinks(int argc, char **argv) ;

  Link *m_ActiveParent ;
    int	m_numLinks ;		// number of links
    int	m_numJoints ;		// number of joints
    Link   *link[MAX_LINKS] ;	// all links
    Joint  *joint[MAX_JOINTS] ;	 // all	joints
    Vector  m_cm ;
    double m_Mass ;
    double density ;
    int	treeFlag ;		// if true then	each link is considered	relative to its	parent
    double m_CurrentEndEffector[3] ;
	double m_AnchorPoint[3];

  void  HandleJointEdits(DView *focus, int x, int y, int width, int height, 
						 int diffx, int diffy) ;
  int KeyboardCB( unsigned char key, int x, int y ) ;
  void Interact(Event *event)  ;
  int InteractStart(Event *event) ;
  int InteractEnd(Event *event) ;
  int PassiveMotionCB(DView *focus, int x, int y) ;

  int HandleSelection(DView *v, int x, int y, int button, int &number, int *item, int type) ;
  void HandleSkeletonButtons(DView *focus, int button, int state, int x, int y, int width, int height) ;

  PlugIn *create(Tcl_Interp *interp, int argc, char **argv) ;
  // functions and wrapper functions for DSystem stuff
  double GetGroupMass(int index) { return link[index]->getMass() ; } ;
  int GetNumGroups(void) { return m_numLinks ;} ;
  DSystem *GetGroup(int index)  { return getLink(index) ; } ;
  DSystem *GetGroup(char *name) { return getLink(name) ; } ;
  BoundingBox	*calcBoundingBox(BoundingBox *b)	;  
  int BeforeSimStep(double time, DSimulator *sim) ;
  int AfterSimStep(double time, DSimulator *sim) ;
  /** must be Called by the DSimulator::Start proc to initialize the system for simulation */
  int InitSimulation(double time, DSimulator *sim) ; 
  
private:
  int ArtObjAppMode ;
  int m_PickedDof ;
  int m_JointDirectionMode;
  int m_SkeletonCreateMode;  
  static int ProcessCollisions(void) ;
  
} ;

#endif

