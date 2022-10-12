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



#ifndef	_JOINT_H_
#define	_JOINT_H_ 1

#include "Quaternion.h"

#ifdef WIN32
#ifdef _EXPORTING_AR
#define DLLENTRY_AR __declspec(dllexport)
#else
#define DLLENTRY_AR __declspec(dllimport)
#endif
#else
#define DLLENTRY_AR
#endif

// types of joints
#define	J_UNDEF	     0
#define	J_PIN	     1
#define	J_BALL	     2
#define	J_CYLINDER   3
#define	J_SLIDER     4
#define	J_FREE	     5
#define	J_GIMBAL     6
#define	J_WELD	     7
#define	J_PLANAR     8
#define	J_BEARING    9
#define	J_UNIVERSAL 10
#define	J_BUSHING   11

class DanceObject ;

class DLLENTRY_AR Joint : public DanceObject {
friend class Link ;
private:
	int setDof(int dof, double value);

	double m_OldState[7];   // the old state vector of this joint.
	double m_State[7] ;	// the state vector of this joint

public:
	void CalcState(void);
	int isChanged();
	void addDof(int index, double deltaAngle, double deltaTrans);
	int getAvailableTypes(Tcl_Interp *interp);
	int getJointType(char *typeString);

	double getDof(int dof);
	int getLabel(int dof, char *label);

    Joint() ;
	~Joint();
    void create(int num, int t, Link *p, Link *l) ;
    inline int getNumber() { return m_jointNumber	;} ;
    inline int getJointType() {	return m_jointType ; } ;
    inline Link *getInboardLink()	{ return inboardLink ; } ;
    inline Link	*getOutboardLink() { return outboardLink ; } ;
    int	getAxis(double a[3][3])	;
    int	getNumAxis(void) { return m_numAxis ; } ;
    int	getOrientation(double m[4][4]);
    void getPosition(double p[3]) ;
    inline void	getInbToJoint(double p[3]) { VecCopy(p,m_InbToJoint) ;} ;
    inline void	getBodyToJoint(double p[3]) { VecCopy(p,m_BodyToJoint) ; } ;
    double getState(int	index);
    int	getStateSize(void);
    int	getNumDof(void)	;
    void setLastState(void);
    void revertToLast(void);
    void setPosition(double p[3]);
    void setRelativePosition(double p[3]);
    void setInbToJoint(double p[3]);
    inline void	setBodyToJoint(double p[3]) { VecCopy(m_BodyToJoint,p) ; } ;
    void setState(int index, double state, int batch = FALSE) ;
    void applyTransformation(void) ;
    void changeType(int	newtype);
    void display(int mode=0);
    void displayRefFrame(double	length,	double frame[4][4]);
    void displayAxis(double axis[3], double length, int	arrowtype=0);
    void displayManipulators(void);
    void print(FILE *fptr) ;
    void setParam(int ax, double stif, double damp) ;
    void getLimits(int dof, double *low, double *high);
    void setLimits(int dof, double low, double high);
	void WriteBVHFile(FILE *fp, int depth) ;
	void WriteMayaFile(FILE *fp) ;
    
	int	Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv);

    int	m_jointNumber ;		// number of joint
    int	m_jointType ;			// type	of joint

    double m_axis[3][3] ;		// the up to three rotational axis
    double damping[7] ;
    double stiffness[7]	;
    double maxDamping[7] ;
    double maxStiffness[7] ;
    double m_Limits[6][2];
    int	m_numAxis	;		// 0 1 2 3 depending on	the joint type
    Quaternion m_Frame;		// the initial orientation quaternion
	Quaternion m_AuxFrame;  // Auxiliary reference frame for a joint.
    Link *inboardLink ;		// Inboard link	of joint.
    Link *outboardLink ;	// Outboard link of joint.
    double m_InbToJoint[3] ;	// inboard to joint (parent to joint)
    double m_BodyToJoint[3] ;	// child link to joint vector
	double m_OldInbToJoint[3]; 
	double m_OldBodyToJoint[3];
} ;
#endif
