/***************************************************************************
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

#include <ctype.h>
#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "DSystem.h"
#include "ArticulatedObject.h"
#include "SimulatorEvents.h"
#include "ViewManager.h"
#include "DView.h"
#include "DSimulator.h"
#include "VCollide.h"
#include "LinkStack.h"

#define MAX_LINKS 100
#define MAX_JOINTS 100

#ifdef macintosh
#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
#ifdef __cplusplus
}
#endif
#else
#include <assert.h>
#endif

static char Sep[2] = {(char) 32, '\t'} ;

static int PickedItem = -1 ;

enum SelectionModes { Link_selection, Joint_selection } ;
enum DirectionMode {
	x_direction,
	y_direction,
	z_direction,
	global_direction,
	up_direction,
	down_direction
};

enum SkeletonCreateMode {
	eChooseParentLink,
	eDefineEndEffector,
	eDefineJointPosition
};

// to be used when reading a bvh file
static Link *AddLink(ArticulatedObject *ao, char *linkName, double *linkOffset, 
		     char *childLinkName, 
		     Vector childPos, char *channelLine) ;


PlugIn *
Proxy(void) { return (new ArticulatedObject) ;}

PlugIn *ArticulatedObject::create(Tcl_Interp *interp, int argc, char **argv)
{
    ArticulatedObject *f = new ArticulatedObject ;

    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}

ArticulatedObject::ArticulatedObject()
{
    int	i ;

    ArtObjAppMode = Normal_mode ;
    density = 1.0 ;
    setName("DummyArticulatedObject") ;
    m_numLinks = 0 ;
    m_numJoints =	0 ;
	m_JointDirectionMode = global_direction;
    m_Mass = 0.0 ;
    treeFlag = FALSE ;		// by default links are	considered independently
				// when	they are drawn
    m_ActiveParent = NULL	;
    m_SkeletonCreateMode = eChooseParentLink;
	m_CheckCollisions = 0;
    m_ActiveJoint = NULL;
    m_PickedDof = -1 ;
    for( i = 0 ; i < MAX_LINKS ; i++ )
	link[i]	= NULL ;
    for( i = 0 ; i < MAX_JOINTS	; i++ )
	joint[i] = NULL	;
    simulator =	NULL ;
    isSimul = FALSE ;
    setType("ArticulatedObject");
    setBaseType("system");
    //events = new SimulatorEvents ;
}

ArticulatedObject::~ArticulatedObject()
{
    int	i ;

    while ( getNumLinks() )
    {
	i = getNumLinks() ;
	delete link[i - 1] ; // this call reduces m_numLinks, 
	// m_numJoints
	link[i - 1] = NULL ;
    }
    
    
    // this should never execute cause all joints are deleted by
    // the links destructors
    for( i = 0 ; i < getNumJoints() ; i++ )
    {
	delete joint[i]	;
	joint[i] = NULL	;
    }
}

// saveObj:
//	Saves object with given	format.
//
// filename: Pointer to	filename.
// format  : Format to save under.
// returns: 1 on success, 0 on failure
//
int ArticulatedObject::saveObj(Tcl_Interp *interp, char format[256], char *filename)
{  
    // make the	name the of file to be name/name
    // sdfast format can only be named following this convention
    char *name = getName();
    char fileRoot[MAX_LINE];
    sprintf(fileRoot,"%s/sdfastObjs/%s/%s",	getenv("DANCE_DIR"),name,name) ;

    char newFilename[MAX_LINE];
    if( filename == NULL )
    {
	// make the	directory if needed.
	char command[MAX_LINE] ;
	sprintf(command,"cd $env(DANCE_DIR)/sdfastObjs ; catch {mkdir %s}",name) ;
	Tcl_Eval(interp,command);
    }
    else
	strcpy(newFilename, filename) ;
    
    if (strcmp(format,"sdfast") == 0) {
	if( filename == NULL )
	{
	    // Add .sd extension
	    sprintf(newFilename,"%s.sd",fileRoot);
	}
	if (writeSdFile(newFilename)) {
		if (interp)
			Tcl_SetResult(interp,newFilename,TCL_VOLATILE);
	    return(1);
	}
	else {
		if (interp)
			Tcl_SetResult(interp,"",TCL_VOLATILE);
	    return(0);
	}
    }
    else if (strcmp(format,"state")	== 0) {
	if( filename == NULL )
	{
	    // Add .Init extension
	    sprintf(newFilename,"%s.Init",fileRoot);
	}
	if (saveStateConfig(newFilename) == OK) {
		if (interp)
			Tcl_SetResult(interp,newFilename,TCL_VOLATILE);
	    return 1;
	}
	else {
		if (interp)
			Tcl_SetResult(interp,"",TCL_VOLATILE);
	    return 0;
	}
    }
    else if (strcmp(format,"dstate") == 0) {
	if( filename == NULL )
	{
	    sprintf(newFilename,"%s.dstate",fileRoot);
	}
	if( simulator == NULL ) return 0;
	FILE *fp = fopen(newFilename, "w") ; 
	if( fp   == NULL )
	{
		if (interp)
			danceTcl::OutputMessage("Cannot open %s.", newFilename) ;
	    return 0 ;
	}
	double *dstate = simulator->GetVel() ; 
	int size = simulator->GetVelSize() ;
	for( int i = 0 ; i < (size - 1)  ; i++ )
	    fprintf(fp, "%lf ", dstate[i]) ;
	fprintf(fp, "%lf", dstate[size-1]) ;
	fclose(fp) ;
	return 1 ;
    }
    else if( strcmp(format, "maya") == 0)
	WriteMayaFile(filename) ;
    else if( strcmp(format, "bvh") == 0 ) {
	WriteBVHFile(filename) ;
    }
    return 0;
}

int ArticulatedObject::setNumLinks(int n)
{
    if(	n > MAX_LINKS)
    {
	danceTcl::OutputMessage("Maximum number of links exceeded.") ;
	return ERR ;
    }
    if(	n < 0)
    {
	danceTcl::OutputMessage("Attempt to set link counter to a negative value.") ;
	return ERR ;
    }
    m_numLinks = n ;
    return n ;
}


int ArticulatedObject::setNumJoints(int	n)
{
    if(	n > MAX_JOINTS)
    {
	danceTcl::OutputMessage("Maximum number of joints exceeded.\n") ;
	return ERR ;
    }

    if(	n < 0)
    {
	danceTcl::OutputMessage("Attempt to set joint counter to a negative value.\n") ;
	return ERR ;
    }
    m_numJoints =	n ;
    return n ;
}

// Gets called when creating link from an SD/FAST file.
//
void ArticulatedObject::addLink(Link *l)
{
    int	nl = getNumLinks() ;

    if(setNumLinks(nl+1) == ERR)
    {
	danceTcl::OutputMessage("Cannot add  link!  Returning.\n") ;
	return ;
    }
    link[nl] = l ;

    l->ao = this ;
    m_Mass += l->getMass() ;

    // assuming	that all the fields in the link	are valid
    // update the parent link of this link about new joint and its
    // new child
    Link * pl ;
    if((pl = l->getParentLink()) != NULL )
    {
	pl->incNumChildLinks(l)	; // updates the pointers too
	// pl->incNumChildJoints()	;
    }
}


void ArticulatedObject::addJoint(Joint *j)
{
    int	nj = getNumJoints() ;

    if(setNumJoints(nj+1) == ERR)
    {
	danceTcl::OutputMessage("Cannot add Joint!  Returning.\n") ;
	return ;
    }
    joint[nj] =	j ;

}

// You can only	remove a leaf link
void ArticulatedObject::removeLink(Link	*l)
{
    int	nl = l->getNumber() ;

    if(	(nl < 0	) && (nl >= MAX_LINKS))
    {
	danceTcl::OutputMessage("Index out of bounds 1!\n") ;
	return ;
    }
    if(	l->getNumChildLinks() != 0)
    {
	danceTcl::OutputMessage("Cannot a remove a non-leaf link!\n") ;
	danceTcl::OutputMessage("Link not removed!\n") ;
	return	;
    }
    delete link[nl] ;
    setNumLinks(getNumLinks() -	1) ;
}

void ArticulatedObject::print(FILE *fptr)
{
	fprintf(fptr,"instance ArticulatedObject %s\n",getName());
	fprintf(fptr,"system %s load sdfast %s.sd\n",getName(),getName());
	fprintf(fptr,"system %s load state\n",getName());
	

	// Traverse through the links.
	int i;
	Link *wlink;
	for (i = 0; i < m_numLinks; i++) {
		wlink = getLink(i);
		wlink->print(fptr);
	}

	// Traverse through the joints.
	Joint *wjoint;
	for (i = 0; i < m_numJoints; i++) {
		wjoint = getJoint(i);
		wjoint->print(fptr);
	}


}

void ArticulatedObject::printFile(char * filename)
{
	FILE *fptr = fopen(filename,"a");
	print(fptr);
	fclose(fptr);
}

void ArticulatedObject::displayLinks(int mode)
{
    int	i ;

    if(	areLinksRelativeToParent() == FALSE)
    {
	glPushName(m_numLinks);
	for( i = 0 ; i < m_numLinks ; i++) {
	    glLoadName(i); // For picking operations
	    link[i]->Display(mode) ;
	}
	glPopName();
    }
    else
	link[0]->displayTree() ;
}

// PROC: displayJoints()
// displays all	joints.	It gets	the position of
// each	joint in world coordinates and then displays it.
//
// mode: 0,  joint centres
//	 1,  inboard and outboard vectors
//	 2,  manipulators
//
void ArticulatedObject::displayJoints(int mode)
{
    int	i ;

    glPushName((GLuint) -1);
    for( i = 0 ; i < m_numJoints ; i++)
    {
	glLoadName(i) ;
	joint[i]->display(mode)	;
    }
    glPopName() ;
    if (mode & JDISPLAY_SELECTION)
	if (m_ActiveJoint) m_ActiveJoint->displayManipulators();

    //  glPopName() ;
}

// display:
//	Displays the articulated object.
//
//	linkmode: Modes	for displaying links
//	jointmode: Modes for displaying	joints
//
void ArticulatedObject::output(int mode)
{
    if( dance::AppMode == system_mode )
    {
	if (ArtObjAppMode == Skeleton_creation_mode 
		&& m_SkeletonCreateMode != eChooseParentLink) {
	
		glPushAttrib(GL_ENABLE_BIT|GL_DEPTH_BUFFER_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		// Draw position of InbToJoint vector joint position.
		if (m_SkeletonCreateMode == eDefineJointPosition) {
			glPointSize(5.0);
			glColor3f(0.0,0.0,1.0);
			glBegin(GL_POINTS);
			glVertex3dv(m_CurrentEndEffector);
			glEnd();
		}

		// Draw end effector vector or joint position.
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,0.0);
		if (m_SkeletonCreateMode == eDefineEndEffector) {	
			glVertex3dv(m_AnchorPoint);
			glVertex3dv(dance::CursorPosn);
		}
		else if (m_SkeletonCreateMode == eDefineJointPosition) {
			glVertex3dv(m_AnchorPoint);
			glVertex3dv(m_CurrentEndEffector);
			glColor3f(1.0,0.0,0.0);
			glVertex3dv(m_CurrentEndEffector);
			glVertex3dv(dance::CursorPosn);
		}
		glEnd();
		glPopAttrib();
		
	}
    }
    else
   		ArtObjAppMode = Normal_mode ;
    
    // Set joint mode for display.
    if (ArtObjAppMode == Joint_edit_mode || ArtObjAppMode == Skeleton_creation_mode) 
		mode = mode | JDISPLAY_CENTRES | JDISPLAY_SELECTION ;
    
    
    // Draw joints first so they can be seen if the links are transparent.
    displayJoints(mode) ;
    displayLinks(mode) ;
}   

// PROC: changeToLocal
// changes all transformation matrices from the	world form to the local	tree form
void ArticulatedObject::changeToLocal()
{
    if(	treeFlag == TRUE ) return ;
    treeFlag = TRUE ;
    if(	getNumLinks() >	0)
	link[0]->changeToLocal() ;
}

// PROC: changeToGlobal
// changes all transformation matrices from the	local systems to the global one
void ArticulatedObject::changeToGlobal()
{
    if(	treeFlag != TRUE ) return ;
    treeFlag = FALSE ;
    if(	getNumLinks() >	0)
	link[0]->changeToGlobal() ;
}


BoundingBox *ArticulatedObject::calcBoundingBox(BoundingBox *b)
{
    int	i ;
    int	n = getNumLinks() ;
    BoundingBox	b1 ;

    if(	n < 1 )	return NULL ;

    b->copy(link[0]->calcBoundingBox(&b1)) ;
    for( i = 1 ; i < getNumLinks() ; i++ )
    {
	b->merge(b,link[i]->calcBoundingBox(&b1)) ;
    }
    return b ;
}

// addLink()
// pt1 first point, pt2	second point.
// as a	default	the link is created as a line segment.
// the activeParent and	currentEndEffector are updated!
// Called when creating links interactively.
//
Link *ArticulatedObject::addLink(double	pt1_t[3],double	pt2_t[3])
{   
    // see if we can add a new link
	int nl = getNumLinks() ;
    if ( setNumLinks(nl+1) == ERR )
    {
		danceTcl::OutputMessage("addLink: Cannot create link! Returning.\n") ;
		return NULL ;
    }
    // allocate	the link
    link[nl] = new Link(nl) ;
   
	// set up default name
	char linkname[256];
    sprintf(linkname,"link%d",nl);
    link[nl]->setName(linkname);

	// set pointers to dependent instances
    link[nl]->ao = this	;
    link[nl]->m_Geom = NULL;

    // fill in the cs parameters
	CoordSystem	cs ;
    Vector cm; 
	link[nl]->getCoordSystem(&cs);
    VecAdd(cm,pt1_t,pt2_t);
    VecNumMul(cm,cm,0.5);
    VecCopy(cs.origin,cm);


    // calculate a coordinate system that corresponds to this two points
    // Contraint: y axis must be aligned with that coordinate system
    VecSubtract(cs.y,pt2_t,pt1_t) ;
    double den, len	= VecLength(cs.y) ;
    if(	len == (double)	0.0)
    {
		setVector(cs.x,-1.0,0.0,0.0) ;	// for the *(-1.0) later on
		setVector(cs.y,0.0,1.0,0.0) ;
    }
    else if( (den = sqrt(cs.y[0]*cs.y[0] + cs.y[1]*cs.y[1])) ==	(double) 0.0)
    {
		setVector(cs.x,0.0,1.0,0.0) ;
		if( (pt1_t[2]-pt2_t[2]) < 0.0)
			setVector(cs.y,1.0,0.0,0.0)	;
		else
			setVector(cs.y,-1.0,0.0,0.0) ;
    }
    else
    {
		double cos_x =	-(cs.y[1])/den ;
		cs.x[0]	= cos_x	;
		cs.x[1]= sqrt(1	- cos_x*cos_x) ;
		cs.x[2]	= 0.0 ;
		if( cs.y[0] > 0.0) cs.x[1] =  fabs(cs.x[1]) ;
		else	cs.x[1]	= -(fabs(cs.x[1])) ;
    }

    // Added in	to make	it a right-handed system
    VecNumMul(cs.x,cs.x,-1.0);

    VecNormalize(cs.y) ;
    VecCrossProd(cs.z,cs.x,cs.y) ;

    VecNormalize(cs.z) ;
    link[nl]->setTransMat(cs);

    // set end effector	for link and articulated object.
    // Must set	the link's transformation matrix first.
    link[nl]->setEndEffectorWC(pt2_t);

    // set parent link and update new active parent
    if (m_ActiveParent != NULL) 
		m_ActiveParent->incNumChildLinks(link[nl]);
    
    link[nl]->setParentLink(m_ActiveParent) ;
    m_ActiveParent = link[nl] ;

    // fill in joint information
    int nj = getNumJoints()	;
    if(setNumJoints(nj+1) == ERR )
    {
		danceTcl::OutputMessage("addLink: no joint can be added\n") ;
		danceTcl::OutputMessage("This is serious. Remove the last link added.\n") ;
		return NULL ;
    }
    if(	link[nl]->parentLink !=	NULL ) // we have a new	joint
    {
		// create new ball joint
		joint[nj] = new	Joint;
		joint[nj]->create(nj,J_BALL,link[nl]->getParentLink(),link[nl]) ;
		// set parent joint
		link[nl]->parentJoint =	joint[nj] ;
		// set default position
		// joint[nj]->getInboardLink()->getEndEffectorWC(p)  ;
		joint[nj]->setPosition(pt1_t) ;
    }
    else // create a free joint	with the ground	assuming ground	at y = 0
    {
		joint[nj] = new	Joint;
		joint[nj]->create(nj,J_FREE,NULL,link[nl]) ;
		link[nl]->parentJoint =	joint[nj] ;
		// set position
		joint[nj]->setPosition(pt1_t) ;
    }

    return link[nl] ;
}

// Moves the joint position and	the parent links above it.
// Must call update state to visually see new configuration.
//
void ArticulatedObject::moveJointAndParents(int	jointID, double	pos[3])
{
	// Set joint position
	Joint *jnt = joint[jointID];
	Joint *parentJoint = link[0]->getParentJoint();	
	if (jnt == parentJoint) {
		moveJointAndChildren(parentJoint->m_jointNumber,pos);
		return;
	}
	// Find new updated outboard (body to joint) vector.
	double linkpos[3]; jnt->outboardLink->getPosition(linkpos);
	double outb[3];
	VecSubtract(outb,pos,linkpos);

	// Convert back to outboard's frame of reference.
	rotPoint_mat4(outb,jnt->outboardLink->m_invTransMat) ;
	jnt->setBodyToJoint(outb);

	// Now translate topmost joint.

	// Calculate delta change.
	double delta[3];
	double opos[3]; jnt->getPosition(opos);
	VecSubtract(delta,pos,opos);

	// Translate top joint to new translated position.						
	double jpos[3]; parentJoint->getPosition(jpos);
	VecAdd(jpos,jpos,delta);
	moveJointAndChildren(parentJoint->m_jointNumber,jpos);
}

// Moves the joint and the children underneath it by a relative	amount
// Must apply transformation on entire articulated figure to correctly update
// state.
//
void ArticulatedObject::moveJointAndChildren(int jointID, double pos[3])
{
	Joint *jnt = joint[jointID];

	// Adjust the inboard joint	vector.
	double inb[3]; jnt->getInbToJoint(inb);

	if (jnt->inboardLink) { // Transform to world coordinates from inboard frame.
		transformPoint_mat(inb,jnt->inboardLink->m_transMat);

		// Subtract of origin of inboard link frame to get actual vector in world space.
		double linkpos[3]; jnt->inboardLink->getPosition(linkpos);
		VecSubtract(inb,inb,linkpos);
	}
	// Add the delta to the inboard position.
	double opos[3]; jnt->getPosition(opos);	
	double delta[3];
	for	(int i = 0;	i < 3; i++) {
		delta[i] = pos[i]-opos[i];
		inb[i] += delta[i];
	}

	if (jnt->inboardLink) // bring it back to local coordinates of inboard frame.
		rotPoint_mat4(inb,jnt->inboardLink->m_invTransMat) ;
	jnt->setInbToJoint(inb);

}


// set the current end effector	of the object
void ArticulatedObject::setCurrentEndEffector(Vector p)
{
    VecCopy(m_CurrentEndEffector,p) ;
}

void ArticulatedObject::getCurrentEndEffector(Vector p)
{
    VecCopy(p,m_CurrentEndEffector) ;
}

// writeSdFile:
//
// Writes the system description file for sdfast
// returns 1 on success, 0 on failure
//
int ArticulatedObject::writeSdFile(char *filename)
{  
	FILE *fp;
    if((fp = fopen(filename,"w")) == NULL )
		return 0 ;

	char *name = getName();
    fprintf(fp,"# This is the system description file for object %s\n", name) ;
    fprintf(fp,"\ngravity = 0 0 0\n") ;
    fprintf(fp,"language = c\n\n") ;
    fprintf(fp,"double\n") ;
    fprintf(fp,"prefix = %s\n\n", name)	;
    for( int i = 0 ; i < m_numLinks ;	i++ )
	if( link[i]->writeSdFile(fp) ==	ERR)
	    return 0;
	
    fclose(fp) ;

    return(1);
}


Joint *ArticulatedObject::getJoint(int index)
{
    if(	(index < 0) || (!(index	< m_numJoints)) )
    {
	danceTcl::OutputMessage("Index out of bounds!\n") ;
	return NULL ;
    }
    else return	joint[index] ;
}

// Returns the link given its name.
Link *ArticulatedObject::getLink(char *name)
{
	Link *wlink = NULL;
	Link **linkList = getLinks();
	for (int i = 0; i < getNumLinks(); i++) {
		if (strcmp(name,linkList[i]->getName()) == 0) {
			wlink = linkList[i];	
			break;
		}
	}
	return (wlink);
}


//		   loadSdfast
// reads in an sdfast file. It follows only the	format printed by
// writeSdFile!!
int ArticulatedObject::loadSdfast(char *fname)
{
    FILE *fp = NULL;
    char line[MAX_LINE], tok[MAX_LINE] ;
    int	numLinks_temp =	0 ;
    int	i ;

    m_Mass = 0.0 ;

	char filename[MAX_LINE];
    if (fname) 
		fp = fopen(fname,"r");
	

    if( fp == NULL ) {
		

		if (fname == NULL) // Create default name.
			sprintf(filename,"%s/sdfastObjs/%s/%s.sd",getenv("DANCE_DIR"),
				getName(), getName());
		else // Add default path to name.
			sprintf(filename,"%s/sdfastObjs/%s/%s",getenv("DANCE_DIR"),
				getName(), fname);

		fp = fopen(filename,"r");
		if( fp == NULL )
		{
			danceTcl::OutputMessage("Error:ArticulatedObject::loadSdfast: "
				"Cannot open %s", filename) ;
			return ERR ;
		}
    }
	else
		strcpy(filename,fname);
		

    int	found =	FALSE ;
    fgets(line,MAX_LINE,fp) ;
    while(!feof(fp) && (found == FALSE)	)
    {
	fgets(line,MAX_LINE,fp)	;
	sscanf(line,"%s", tok) ;
	if(strcmp(tok,"prefix")	== 0)
	{
	    sscanf(line,"prefix	= %s", tok) ;
	    found = TRUE ;
	    setName(tok);
	}
    }

    if(	found == FALSE )
    {
	danceTcl::OutputMessage("Prefix not found! Using TestObj\n") ;
	setName("TestObj");
    }

    // do a first pass to find the number of links

    while(!feof(fp))
    {
	fgets(line,MAX_LINE,fp)	;
	sscanf(line,"%s", tok) ;
	if(strcmp(tok,"body") == 0)
	    numLinks_temp++ ;
    }
    fclose(fp) ;

    fp = fopen(filename,"r") ;
    Link *l ;
    for( i = 0 ; i < numLinks_temp ; i++ )
    {
	l = new	Link(i)	;
	l->ao =	this ;
	if( l == NULL )
	{
	    danceTcl::OutputMessage("Cannot allocate link!\n") ;
	    return ERR;
	}
	if( l->readSdfast(fp) == NULL)
	{
	    danceTcl::OutputMessage("Cannot read link number %d!\n",i) ;
	    return ERR ;
	}
	addLink(l) ;
    }

    fclose(fp) ;
    danceTcl::OutputMessage("Object loaded successfully.\n") ;
    return OK ;
}


//	     read the state from a file

int ArticulatedObject::loadStateConfig(char *fname)
{
    char filename[MAX_LINE], line[MAX_LINE] ;
    int	i, nj ;
    char *s ;
    double st ;

    if (fname)
	strcpy(filename,fname);
    else
   	// use default file
	sprintf(filename,"%s/sdfastObjs/%s/%s.Init", 
		getenv("DANCE_DIR"),getName(),getName()) ;
    
    FILE *fp = fopen(filename, "r") ;
    if( fp == NULL )
    {
	danceTcl::OutputMessage("Cannot open %s", fname) ;
	return ERR ;
    }
    fgets(line,MAX_LINE,fp) ;
    // eat comments and	blank lines
    while((!feof(fp)) && ((line[0] == '#') || (line[0] == '\n')) )
    {
	fgets(line,MAX_LINE,fp)	;
    }


    // set all link transformation matrices to the indentity matrix
    // cause updateStateConfig does a change to local. If the matrices
    // have been corrupted (i.e bad simulation, we can never get the
    // state back.
    for( i = 0 ; i < m_numLinks ; i++ )
    {
	setIdentMat(&link[i]->m_transMat[0][0],4) ;
	setIdentMat(&link[i]->m_invTransMat[0][0],4) ;
    }

    for( nj = 0	; nj < m_numJoints ; nj++ )
    {
	if( feof(fp) && (joint[nj]->m_jointType != J_WELD) )
	{
	    danceTcl::OutputMessage("loadStateConfig: unexpected end of file!\n") ;
	    return ERR ;
	}
	for( i = 0 ; i < joint[nj]->getStateSize() ; i++ )
	{
	   
	    if(	i == 0)
	    {
		if( (s = strtok(line, Sep)) == NULL )
		{
		    danceTcl::OutputMessage("loadStateConfig: missing info!\n") ;
		    return ERR ;
		}
	    }
	    else if( (s	= strtok(NULL, Sep)) == NULL )
	    {
		danceTcl::OutputMessage("loadStateConfig: missing info!\n") ;
		return ERR ;
	    }
	    sscanf(s,"%lf",&st)	;
	    joint[nj]->setState(i,st) ;
	}
	line[0]	= '\0' ;
	fgets(line,MAX_LINE,fp)	;
    }

    fclose(fp) ;
    updateStateConfig(); // Update entire articulated object's joints.

    return OK ;
}





// saveStateConfig:
// save	the state on file. Depending on	the type of joint
// for each joint a quaternion or 1,2,3	angles are saved.
// Also	the global position is saved too.
//
// returns 1 on success 0 on failure
int ArticulatedObject::saveStateConfig(char *filename)
{

    FILE *fp;
    if((fp = fopen(filename,"w")) == NULL )
	return 0;
    
    char *name = getName();
    fprintf(fp,"# This is the configuration file for object %s\n", name) ;
    fprintf(fp,"# Number of Joints: %d\n", m_numJoints) ;
    fprintf(fp,"\n") ;
    for(int i = 0 ; i < m_numJoints	; i++ )
    {
	for(int j =	0 ; j <	joint[i]->getStateSize() ; j++ )
	{
	    if( j != 0) fprintf(fp," ") ;
	    fprintf(fp,"%lf", joint[i]->getState(j)) ;
	}
	fprintf(fp,"\n") ;
    }
    fclose(fp);
    
    return OK ;
}


// UpdateState: 
//      Sets the state of all joints and then calls updateStateConfig
//      to calculate the transformation matrices etc.
// Assumes that the parameters of all joints are grouped together in
// sequence. This is not the case if state comes directly from sdfast
// where the fourth quaternion parameter of the free joint is at the end.
void ArticulatedObject::UpdateState(double *state)
{ 
	int count = 0 ;
    for( int  i = 0 ; i < getNumJoints() ; i++ )
	for( int j = 0 ; j < joint[i]->getStateSize() ; j++)
	{
	    joint[i]->setState(j,state[count]) ;
	    count++ ;
	}
    updateStateConfig() ;
}

// updateStateConfig:
//	Uses the already loaded	 information to	assume
//	the initial position.
//
//
void ArticulatedObject::updateStateConfig(int index)
{
    changeToLocal() ;

    int	i;
    if (index == -1)
	for( i = 0 ; i < m_numJoints ; i++ )
	     joint[i]->applyTransformation() ;
    else
	     joint[index]->applyTransformation() ;

    changeToGlobal();

    return ;
}

void ArticulatedObject::SetLastState(void) 
{
	for (int i = 0; i < m_numJoints; i++)
		joint[i]->setLastState();
}

void ArticulatedObject::revertToLast(void)
{
	for (int i = 0; i < m_numJoints; i++)
		joint[i]->revertToLast();
}


// sets	the stiffness and joint	of joint nj or all of the joints
// if nj = -1
void ArticulatedObject::setJointParam(int nj, int axis,	 double	stiff, double damp)
{
    int	i,j ;

    if(	nj == -1)
    {
	danceTcl::OutputMessage("Setting	the damp and stiffness of all joint\n")	;
	for( i = 0 ; i < m_numJoints ; i++ )
	    for( j = 0 ; j < joint[i]->getStateSize() ;	j++)
		joint[i]->setParam(j,stiff,damp) ;
    }
    else
    {
	if( (nj	> -1) && (nj < m_numJoints))
	{
	    joint[nj]->setParam(axis,stiff,damp) ;
	}
	else
	   danceTcl::OutputMessage("Index out of bounds	3") ;
    }
}

int ArticulatedObject::commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    if (strcmp(argv[0],"save") == 0) {
		if (argc < 2) {
			danceTcl::OutputMessage("USAGE: save <format> [<filename>]\n",(char *)NULL);
			return TCL_ERROR;
		}
		char *filename = NULL;
		if (argc == 3)
			filename = argv[2];
		if (saveObj(interp,argv[1],filename)) 
			return TCL_OK;
		else
			return TCL_ERROR;
    }
    else if (strcmp(argv[0],"load") == 0) {
		if (argc < 2) {
			danceTcl::OutputMessage("USAGE: load <format> <filename>\n");
			return TCL_ERROR;
		}
		char *file ;
		if( argc == 2 ) 
		    file = NULL ;
		else 
		    file = argv[2] ;
		if (strcmp(argv[1],"sdfast") ==	0)
			loadSdfast(file);
		else if	(strcmp(argv[1],"state") == 0)
			loadStateConfig(file);
		else if ( strcmp(argv[1], "bvh") == 0 )
			ReadBVHFile(file) ;
		return TCL_OK;
	}
	else if (strcmp(argv[0],"show") == 0) {
		if (argc == 2) {
			if (strcmp(argv[1],"links") == 0) {
				for (int i=0; i < getNumLinks(); i++) 
				{
				    if( i != 0 ) danceTcl::OutputResult("%c", 32) ;
				    danceTcl::OutputResult("%s", link[i]->getName());
				}
			}
			else if (strcmp(argv[1],"joints") == 0) {
				for (int i=0; i < getNumJoints(); i++)
				{
				    if( i != 0 ) danceTcl::OutputResult("%c", 32) ;
				    danceTcl::OutputResult("%s", joint[i]->getName());
				}
			}
			else if (strcmp(argv[1],"number_of_joints") == 0) {
			    danceTcl::OutputResult("%d", getNumJoints()) ;
			}
			else if (strcmp(argv[1],"number_of_links") == 0) {
			    danceTcl::OutputResult("%d", getNumLinks()) ;
			}
			else if (strcmp(argv[1],"max_dimensions") == 0) {
				BoundingBox b ;
				Vector dim ;
				calcBoundingBox(&b) ;
				b.getDimensions(dim) ;
				danceTcl::OutputResult("%lf %lf %lf\n", dim[0], dim[1], dim[2]) ;
			}
			else {
			     danceTcl::OutputResult("usage: show links|joints|"
						    "number_of_links|"
						    "number_of_joints|"
						    "max_dimensions.") ;
			}
			danceTcl::OutputResult("\n") ;
		}
		return TCL_OK;
	}
        else if (strcmp(argv[0],"reset") == 0) {
		revertToLast();
		updateStateConfig();
		return TCL_OK;
	}
	else if (strcmp(argv[0],"snapshot") == 0) {
		SetLastState();
		return TCL_OK;
	}
	else if (strcmp(argv[0],"update") == 0) {
		updateStateConfig(); // Update configuration of object.
		return TCL_OK;
	}
	else if (strcmp(argv[0], "transparency") == 0 )
	{
		if( argc == 1 )
		{
			danceTcl::OutputMessage("usage: transparency <value>") ;
			danceTcl::OutputMessage("where value is between 0, 1") ;
			return TCL_ERROR;
		}
		double tr = atof(argv[1]) ;
		for( int i = 0 ; i < getNumLinks() ; i++ )
		{
			link[i]->m_Transparency = (float) tr ;
		}
	}
	else if( strcmp(argv[0], "link")  == 0 )
        {
		if (argc == 1) {
			danceTcl::OutputMessage("USAGE: link <name|number>\n") ;
			return TCL_ERROR;
		}
		// Get link number
		int link; 
		int isNumber = sscanf(argv[1],"%d",&link);

		Link **linkList	= getLinks();
		if (linkList ==	NULL)
		{
			danceTcl::OutputMessage("ERROR: No links existing for this object.\n");
			return TCL_ERROR;
		}

		// Get the link.
		Link *wlink = NULL;
		if (isNumber != 1) { // Could be a name string.
		
			wlink = getLink(argv[1]);
			if (wlink == NULL) {
				danceTcl::OutputMessage("ERROR: No link exists with the given name.");
				return TCL_ERROR;
			}
		}
		else {
			// check if the	object has such	a link
			if (link >= getNumLinks() || link < 0)
			{	
	    		danceTcl::OutputMessage("ERROR: Link index does not exist.\n");
	    		return TCL_ERROR;
			}

			wlink = linkList[link];
        }

		return wlink->Command(clientData, interp, argc-2, argv+2) ;
    }
    else if (strcmp(argv[0], "root") == 0)
    {
		if (getNumLinks() > 0) {
		    Link **linkList = getLinks();
		    danceTcl::OutputResult("%s",linkList[0]->getName());
		}
		else 
			danceTcl::OutputResult("");
		return TCL_OK;
    }
    else if( strcmp(argv[0], "joint") == 0 )
    {
        int joint; 
	int isNumber = sscanf(argv[1],"%d",&joint);
	
	Joint **jointList	= getJoints();
	if (jointList ==	NULL)
	{
	danceTcl::OutputMessage("ERROR: No joints existing for this object.\n");
	    return TCL_ERROR;
	}
	
	// Get the link.
	Joint *wjoint = NULL;
	if (isNumber != 1) { // Could be a name string.
	    
	    wjoint = getJoint(argv[1]);
	    if (wjoint == NULL) {
		danceTcl::OutputMessage("ERROR: No joint exists with the given name.");
		return TCL_ERROR;
	    }
        }
        else {
            if (joint < 0 || joint >= getNumJoints()) {
                danceTcl::OutputMessage("ERROR: Joint index does not exist.");
                return TCL_ERROR;
            }
            wjoint = jointList[joint];
        }
	return wjoint->Command(clientData, interp, argc-2, argv+2);
    }
    
    //    else if( strcmp(argv[0], "make_sdfast") == 0 )
    //{
    //		SdfastSimul::makeCompile(getName());
    //		return TCL_OK;
    //}
    //else if( strcmp(argv[0], "simul") == 0 )
    //{
    //	simul(clientData, interp, argc-1, &argv[1]);
    //	return TCL_OK;
    //}
    else if( strcmp(argv[0], "combine") == 0 )
    {
	return combineLinks(argc-1, &argv[1]) ;
    }
    else if (strcmp(argv[0], "usage") == 0 )
    {
		danceTcl::OutputMessage("USAGE: object <name> load|save|link|scale"
		      "|make_sdfast\n") ;
		return TCL_OK;
    }
   
    return TCL_OK ;
}

// start stop or re-start the simulation
// Also	makes the shared object	using the system function
// when	a simulation starts
//  int ArticulatedObject::simul(ClientData	clientData, Tcl_Interp *interp,	int argc, char **argv)
//  {
//      if( isImobile == TRUE ) return TCL_OK ;

//      if(	argc < 1 )
//      {
//  	danceTcl::OutputMessage("USAGE: simul start [<dt>]|stop|pause|cont|"
//  		      "assemble|static|initvel|steady|set\n") ;
//  	return TCL_ERROR ;
//      }
//      if( strcmp(argv[0],"load") == 0 )
//      {
//  	LoadSimulator(interp) ;
//      }
//      else if (strcmp(argv[0],"start")	== 0 ) // start new simulation
//      {
//  	// if no simulator present load it
//  	if( simulator == NULL )	
//  	{
//  	    if( LoadSimulator(interp) == TCL_ERROR )
//  		return TCL_ERROR ;
//  	}
//  	isSimul	= TRUE ;
//  	// set state from joint	configuration of object
//  	SdfastSimul *sim = simulator;

//  	sim->time = 0.0 ;
//  	if( simulator->init() == ERR )
//  	{
//  	    danceTcl::OutputMessage("Error in init()") ;
//  	    isSimul = FALSE ;
//  	    delete simulator ;
//  	    simulator = NULL ;
//  	    return TCL_ERROR ;
//  	}
//  	if( SetParamAndInitSimul(interp, argc-1, &argv[1]) == TCL_ERROR )
//  	{
//  	    isSimul = FALSE ;
//  	    danceTcl::OutputMessage("Problem starting the simulation.") ;
//  	}
	
//      }
//      else if (strcmp(argv[0],"stop") == 0 ) // stop simulation and delete the	simulator
//      {
//  	isSimul	= FALSE	;
//         	if( simulator != NULL )
//  	{
//  	    simulator->EndSimul(this) ;
//  	    //delete simulator ;
//  	    //simulator = NULL ;
//  	}
//      }
//      else if (strcmp(argv[0],"pause") ==	0 ) // pause	simulation
//      {
//  	isSimul	= FALSE	;
//      }
//      else if ((strstr(argv[0],"assemble") != NULL)
//  	     ||	 (strstr(argv[0],"static") != NULL)
//  	     ||	 (strstr(argv[0],"initvel") != NULL)
//  	     ||	 (strstr(argv[0],"steady") != NULL)
//  	     ) // assemble and static analysis
//      {
//  	if (simulator != NULL) {
//  	    SdfastSimul	*sim = simulator;
//  	    SdfastSimul::CurrentSimulObject = sim->ao ;
//  	    sim->setStateVectorFromJoints();
//  	    sim->assemblyAnalysis();
//  	    if ( (strstr(argv[0],"initvel") != NULL)
//  		 ||(strstr(argv[0],"steady") !=	NULL) )
//  		sim->initVelocityAnalysis();
//  	    if (strstr(argv[0],"static") != NULL)
//  		sim->staticAnalysis();
//  	    if (strstr(argv[0],"steady") != NULL)
//  		sim->steadyStateAnalysis();
//  	    sim->setJointsFromStateVector();
//  	    updateStateConfig();
//  	}
//      }
//      else if (strcmp(argv[0],"cont") == 0 )
//      {
//  	if( simulator == NULL )
//  	    danceTcl::OutputMessage("No existing simulator, use 'start'\n") ;
//  	else
//  	{
//  	    // In case simulation configuration	was changed by editor,
//  		// update the SD/FAST state.

//  	    SdfastSimul	*sim = simulator;
//  	    sim->setStateVectorFromJoints();
//  	    sim->assemblyAnalysis();

//  	    isSimul = TRUE ;
//  	}
//      }

//      return TCL_OK ;
//  }


//  int ArticulatedObject::SetParamAndInitSimul(Tcl_Interp	*interp, int argc, char	**argv)
//  {

//      int new_vel = FALSE ;

//      if(	simulator == NULL )
//      {
//  	danceTcl::OutputMessage("Simulator not present!! Cannot set the parameters!\n") ;
//  	return TCL_ERROR ;
//      }
//      while(argc)
//      {
//  	if( strcmp(argv[0], "dt") == 0)
//  	{
//  	    if(	argc < 2 )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected: dt <dt>\n");
//  		return TCL_ERROR ;
//  	    }
//  	    if(	!isdigit(argv[1][0]) )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected dt <dt>\n");
//  		continue ;
//  	    }
//  	    simulator->dt = atof(argv[1]) ;
//  	    argc -= 2 ;
//  	    argv += 2 ;
//  	}
//  	else if( strcmp(argv[0], "integ") == 0)
//  	{
//  	    if(	argc < 2 )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected: integ 0|<value>\n");
//  		return TCL_ERROR ;
//  	    }
//  	    simulator->m_integrator = atoi(argv[1]) ;
//  	    argc -= 2 ;
//  	    argv += 2 ;
//  	}
//  	else if( strcmp(argv[0], "tol") == 0)
//  	{
//  	    if(	argc < 2 )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected: tol <tol>\n");
//  		return TCL_ERROR ;
//  	    }
//  	    if(	!isdigit(argv[1][0]) )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected tol <tol>\n");
//  		continue ;
//  	    }
//  	    simulator->tol = atof(argv[1]) ;
//  	    argc -= 2 ;
//  	    argv += 2 ;
//  	}
//  	else if( strcmp(argv[0], "ctol") == 0)
//  	{
//  	    if(	argc < 2 )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected: ctol <ctol>\n");
//  		return TCL_ERROR ;
//  	    }
//  	    if(	!isdigit(argv[1][0]) )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected ctol <ctol>\n");
//  		argc -= 1 ;
//  		argv += 1 ;

//  		continue ;
//  	    }
//  	    simulator->ctol = atof(argv[1]) ;
//  	    argc -= 2 ;
//  	    argv += 2 ;
//  	}
//  	else if( strcmp(argv[0], "f") == 0 )
//  	{
//  	    danceTcl::OutputMessage("Using fixed time step\n") ;
//  	    simulator->fixedStep = TRUE	;
//  	    argc -= 1 ;
//  	    argv += 1 ;
//  	}
//  	else if( strcmp(argv[0], "v") == 0 )
//  	{
//  	    danceTcl::OutputMessage("Using variable time step\n") ;
//  	    simulator->fixedStep = FALSE ;
//  	    argc -= 1 ;
//  	    argv += 1 ;
//  	}
//  	else if( strcmp(argv[0], "end")	== 0)
//  	{
//  	    if(	argc < 2 )
//  	    {
//  		danceTcl::OutputMessage("ERROR: expected: dt <dt>\n");
//  		return TCL_ERROR ;
//  	    }

//  	    if(	!isdigit(argv[1][0]) )
//  	    {
//  	        danceTcl::OutputMessage("ERROR: expected dt <dt>\n");
//  		argc -= 1 ;
//  		argv += 1 ;
//  		continue ;
//  	    }
//  	    simulator->end = atof(argv[1]) ;
//  	    argc -= 2 ;
//  	    argv += 2 ;
//  	}
//  	else if( (strcmp(argv[0], "sstate") == 0 ) || (strcmp(argv[0], "dstate") == 0 ) )
//  	{
//  	    // read the velocities from the given file
//  	    if( argc > 1 )
//  	    {
//  		FILE *fp = fopen(argv[1], "r") ;
//  		if( fp == NULL )
//  		{
//  		    danceTcl::OutputMessage("Cannot open %s", argv[1]) ;
//  		    danceTcl::OutputMessage("Using 0 velocities") ;
//  		    argc -= 2 ;
//  		    argv += 2 ;
//  		    return TCL_ERROR ;
//  		}
//  		for( int i = 0 ; i < simulator->nu ; i++ )
//  		{
//  		    if( fscanf(fp, "%lf", &simulator->m_dstate[i]) != 1 )
//  		    {
//  			danceTcl::OutputMessage("Error reading velocity file.") ;
//  			fclose(fp) ;
//  			argc -= 2 ;
//  			argv += 2 ;
//  			fclose(fp) ;
//  			return TCL_ERROR ;
//  		    }
//  		    simulator->m_state[simulator->nq+i] = simulator->m_dstate[i] ;
//  		}
//  		danceTcl::OutputMessage("Read new velocities") ;
//  		new_vel = TRUE ;		
//  		fclose(fp) ;
	
//  	    }

	   
//  	    argc -= 2 ;
//  	    argv += 2 ;

//  	}
//  	else
//  	{
//  	    danceTcl::OutputMessage("Unknown parameter %s.", argv[0]) ;
//  	    return TCL_ERROR ;
//  	}
//      }

//      simulator->setStateVectorFromJoints();
//      simulator->sdinit() ;		  // initialize	sdfast
//      danceTcl::OutputMessage("Starting simulation dt = %lf time = %lf tol = %lf\n",
//  			    simulator->dt,
//  			    simulator->time,
//  			    simulator->tol) ;
    
//      simulator->assemblyAnalysis();
//      simulator->initVelocityAnalysis();
    
//      if( new_vel == TRUE ) 
//  	simulator->sdstate(simulator->time,
//  			   simulator->m_state, 
//  			   simulator->m_dstate) ;
//      return TCL_OK ;
//  }


Joint * ArticulatedObject::getJoint(char * name)
{
  	Joint *wjnt = NULL;
	Joint **jointList = getJoints();
	for (int i = 0; i < getNumJoints(); i++) {
		if (strcmp(name,jointList[i]->getName()) == 0) {
			wjnt = jointList[i];	
			break;
		}
	}
	return (wjnt);
}

 
int ArticulatedObject::GetStateSize(void)
{
    int size = 0 ;
    for( int i = 0 ; i < getNumJoints() ; i++ )
   	size += joint[i]->getStateSize() ;
    return size ;
}

// state must be allocated by the caller
void ArticulatedObject::GetState(double *state)
{
    int count = 0 ;
    for( int i = 0 ; i < getNumJoints() ; i++ )
    {
	for( int j = 0 ; j < joint[i]->getStateSize() ; j++)
	{
	    state[count] = joint[i]->getState(j) ;
	    count ++ ;
	}
    }
}


void ArticulatedObject::WriteBVHFile(char *filename)
{
	FILE *fp = fopen(filename, "w") ;
	if( fp == NULL ) 
	{
		danceTcl::OutputMessage("ERROR: WriteBVH: cannot open %s.\n", filename) ;
		return ;
	}
	WriteBVHFile(fp) ;
	fclose(fp) ;
	return ;
}

void ArticulatedObject::WriteBVHFile(FILE *fp)
{
	Link *RootLink = NULL ;
	
	// find the root link which is the one whose parent is NULL
	for( int i = 0 ; i < m_numLinks ; i++ )
		if( link[i]->getParentLink() == NULL )
			RootLink = link[i] ;
	if( RootLink == NULL )
	{
		danceTcl::OutputMessage("ERROR: WriteBVH: cannot find root link!") ;
		return ;
	}

	RootLink->WriteBVHFile(fp, 1) ;
	return ;
}

int ArticulatedObject::ReadBVHFile(char *filename)
{
	FILE *fp = fopen(filename, "r") ;
	if( fp == NULL ) 
	{
		danceTcl::OutputMessage("ERROR: ReadBVH: cannot open %s.\n", filename) ;
		return TCL_ERROR;
	}
	
	int res = ReadBVHFile(fp) ;
	fclose(fp) ;

	return res ;
}


static LinkStack *g_ls ;
static int returnError(char *s = NULL )
{
	delete g_ls ;
	danceTcl::OutputMessage("ERROR: ReadBVHFile %s\n", s) ;
	return TCL_ERROR ;
}
int ArticulatedObject::ReadBVHFile(FILE *fp)
{
	int i ;
	// Initialize everything
	m_ActiveParent = NULL ;
	// remove the links and joints
	for( i = 0 ; i < getNumLinks() ; i++ )
    {
	delete link[i] ;
	link[i]	= NULL ;
    }
	m_numLinks = 0 ;
    for( i = 0 ; i < getNumJoints() ; i++ )
    {
	delete joint[i]	;
	joint[i] = NULL	;
    }
	m_numJoints = 0 ;

	danceTcl::OutputMessage("Reading bvh file\n") ;
	char token[MAX_LINE] = "" ;
	LinkStack *g_ls = new LinkStack() ;
	char linkName[MAX_LINE] ;
	Link *activeParentHere = NULL ;

	if( g_ls == NULL )
	{
		danceTcl::OutputMessage("ERROR: ReadBVHFile: cannot allocate memory!\n") ;
		return TCL_ERROR ;
	}		
	
	int numOpenBrackets = 0 ;
	int numCloseBrackets = 0 ;
	// Read first links
	fscanf(fp, "%s", token) ;
	while((!feof(fp)) &&  (strcmp(token, "HIERARCHY") != 0))
		fscanf(fp, "%s", token) ;
	if( feof(fp) )
	{
		returnError() ;
	}

	// Read the links
	// read the root link
	fscanf(fp, "%s", token) ;
	if(strcmp(token, "ROOT") != 0)
	{
		returnError() ;
	}
	// read the name
	if( fscanf(fp, "%s", linkName) != 1 )
		returnError("expected link name") ;
	fscanf(fp, "%s", token) ;
	if( strcmp(token, "{") != 0 )
		returnError("expected {") ;
	numOpenBrackets++ ;

	Vector offset ;
	fscanf(fp, "%s", token) ;
	if( strcmp(token, "OFFSET") != 0 )
		returnError("expected OFFSET") ;
	if( fscanf(fp, "%lf %lf %lf", &offset[0], &offset[1], &offset[2]) != 3 )
		returnError("expected three numbers.") ;

	char channelLine[MAX_LINE] ;
	char childLinkName[MAX_LINE] ;
	
	Vector childOffset ;
	fscanf(fp, "%s", token) ;
	while(!feof(fp))
	{
		if( strcmp(token, "End") == 0 )
		{
			fscanf(fp, "%s", token) ;
			if( strcmp(token, "Site") != 0 )
				returnError("expected Site") ;
			else
			{
				fscanf(fp, "%s", token) ;
				if( strcmp(token, "{") != 0 )
					returnError("expected '{'\n") ;
				fscanf(fp, "%s", token) ;
				if( strcmp(token, "OFFSET") != 0 )
					returnError("expected 'OFFSET'\n") ;
				if( fscanf(fp, "%lf %lf %lf", &childOffset[0],
						&childOffset[1], 
						&childOffset[2]) != 3 )
					returnError("expected three numbers.") ;
				fscanf(fp, "%s", token) ;
				if( strcmp(token, "}") != 0 )
					returnError("expected '}'\n") ;
				AddLink(this, linkName, offset, "End", childOffset, channelLine) ;
			}
		}
		else if( strcmp(token, "}") == 0 )
		{	
			numCloseBrackets++  ;
			if( numCloseBrackets > numOpenBrackets )
				returnError("mismatch brackets.\n") ;
			if( numCloseBrackets < (numOpenBrackets - 1))
			{
				g_ls->Pop() ;
				activeParentHere = g_ls->GetTop() ;
			}
			else activeParentHere = NULL ;
		}
		else if( strcmp(token, "JOINT") == 0 )
		{
		    // read this link as child
		    // construct the previous link 
		    // and then make this link the current link to be
		    // constructed when one of his children is found
			// read the name
			if( fscanf(fp, "%s", childLinkName) != 1 )
				returnError("expected link name") ;

			fscanf(fp, "%s", token) ;
			if( strcmp(token, "{") != 0 )
				returnError("expected {") ;
			numOpenBrackets++ ;
			fscanf(fp, "%s", token) ;
			if( strcmp(token, "OFFSET") != 0 )
				returnError("expected OFFSET") ;
			if( fscanf(fp, "%lf %lf %lf", &childOffset[0], &childOffset[1], 
				&childOffset[2]) != 3 )
					returnError("expected three numbers.") ;
		
			// now construct the parent link
			Link *link = AddLink(this, linkName, offset, childLinkName, childOffset, channelLine) ;
			g_ls->Push(link) ;
			activeParentHere = link ;
			
			if( ReadChannels(channelLine, joint[m_numJoints-1]) == TCL_ERROR )
				returnError("couldn't read channels.\n") ;

			// make the child link the actual link
			strcpy(linkName, childLinkName) ;
			VecCopy(offset, childOffset) ;
		}
		else if( strcmp(token, "CHANNELS") == 0 )
			fgets(channelLine, MAX_LINE, fp) ;
		fscanf(fp, "%s", token) ;
	}

	if( numCloseBrackets != numOpenBrackets )
		returnError("mismatch brackets.\n") ;
	danceTcl::OutputMessage("Successfully parsed bvh file.\n") ;
	delete g_ls ;

	return TCL_OK ;
}

int ArticulatedObject::ReadChannels(char *channelLine, Joint *joint)
{
	char *token = NULL ;
	char line[MAX_LINE] ;
	strcpy(line, channelLine) ;

	int numChannels = 0 ;
	
	token = strtok(line, Sep) ;
	if( sscanf(token, "%d", &numChannels) != 1 )
	{
		danceTcl::OutputMessage("ReadChannels: expected the number of channels.\n") ;
		return TCL_ERROR ;
	}

	if( numChannels == 0 )
		joint->changeType(J_WELD); // sets the number of axis etc
	else if( strstr(channelLine, "position") )
	{
		if( numChannels == 6 )
			joint->changeType(J_FREE) ;
		else
			joint->changeType(J_SLIDER) ;
	}
	else
	{
		if( numChannels == 3 )
			joint->changeType(J_GIMBAL) ;
		else if( numChannels == 2 )
			joint->changeType(J_UNIVERSAL) ;
		else if( numChannels == 1 )
			joint->changeType(J_PIN) ;
		else
		{
			danceTcl::OutputMessage("ReadChannels: Wrong kind of channels.\n") ;
			return TCL_ERROR ;
		}
	}

	char * s ;
	int i ;
    
	switch(joint->m_jointType)
	{
	case J_FREE:
		// consume the three translation parameters
		for( i = 0 ; i < 3 ; i++ )
		{
			s = strtok(NULL, Sep) ;
			if( s == NULL )
			{
				danceTcl::OutputMessage("ReadChannels: Missing a channel!.\n") ;
				return TCL_ERROR ;
			}
		}
	  // know go on and read the rotational ones
	case J_SLIDER:
	case J_PIN:
	case J_UNIVERSAL:
	case J_GIMBAL:
		for( i = 0 ; i < joint->m_numAxis ; i++ )
		{
			s = strtok(NULL, Sep) ;
			if( s == NULL )
			{
				danceTcl::OutputMessage("ReadChannels: Missing a channel!.\n") ;
				return TCL_ERROR ;
				}
			if( s[0] == 'X')
				setVector(joint->m_axis[i], 1.0, 0.0, 0.0) ;
			else if( s[0] == 'Y')
				setVector(joint->m_axis[i], 0.0, 1.0, 0.0) ;
			else if( s[0] == 'Z' )
				setVector(joint->m_axis[i], 0.0, 0.0, 1.0) ;
			else 
			{
				danceTcl::OutputMessage("ReadChannels: '%s' unkown channel identifier.\n", s) ;
				return TCL_ERROR ;
			}
	    }
	  break ;
	}
	return TCL_OK ;
}


Link *AddLink(ArticulatedObject *ao, char *linkName, Vector linkOffset, 
	      char *childName, Vector childOffset, char *channelLine)
{
	// make the offset absolute positions
	Vector pp ;
	Joint *pJoint ;
	Vector linkPos, childPos ;
	
	printf("----------------------------------\n") ;
	printf("Linkoffset %lf %lf %lf\n", linkOffset[0], 
		linkOffset[1], linkOffset[2]) ;
	if( ao->m_ActiveParent == NULL )
		pJoint = NULL ;
	else
		pJoint = ao->m_ActiveParent->getParentJoint() ;
	if( pJoint == NULL )
	{
		VecCopy(linkPos, linkOffset) ;
		VecCopy(pp, linkOffset) ;
	}
	else
	{
		pJoint->getPosition(pp) ;
		VecAdd(linkPos, pp, linkOffset) ;
	}
	VecAdd(childPos, linkPos, childOffset) ;
	if( ao->m_ActiveParent != NULL )
		printf("Parent link %s\n", ao->m_ActiveParent->getName()) ;
	Vector linkPosWhole ;
	VecCopy(linkPosWhole, linkPos) ;

	// align everything with this links coordinates
	childPos[0] = linkPos[0] ;
	childPos[2] = linkPos[2] ;
		
	Link *link = ao->addLink(linkPos, childPos) ;
    if( link == NULL ) return NULL ;

	// now that the link is made and correctly aligned with world
	// fix its position with respect to its parent
	Vector pos ;

	VecSubtract(pos, linkPos, pp) ;
	ao->moveJointAndChildren(ao->m_numJoints - 1, pos) ; 
	Vector btj ; setVector(btj, 0.0, -childOffset[1]*0.5 , 0.0) ;
	link->getParentJoint()->setBodyToJoint(btj) ;
	
	printf("Parent joint position %lf %lf %lf\n", pp[0], pp[1], pp[2]) ;
	printf("Added link first point: %lf %lf %lf ", linkPos[0], 
		linkPos[1], linkPos[2]) ;
	printf("second point %lf %lf %lf\n", childPos[0], 
		childPos[1], childPos[2]) ;

	Vector jp ;
	link->getParentJoint()->getPosition(jp) ;
	printf("New Joint position %lf %lf %lf\n", jp[0], jp[1], jp[2]) ;
	Vector itj ;
	link->getParentJoint()->getInbToJoint(itj) ;
	printf("\tinbtoJ %lf %lf %lf", itj[0], itj[1], itj[2]);
	link->getParentJoint()->getBodyToJoint(btj) ;
	printf("\tbtoJ %lf %lf %lf\n", btj[0], btj[1], btj[2]);
    link->setName(linkName) ;
    ao->ReadChannels(channelLine, link->getParentJoint()) ;

    return link ;
}

// Returns 1 if there is a change between the distal and proximal link given.
int ArticulatedObject::isChangeAboveLinks(Link *distal)
{
	int result = 0;

	// Start with distal.
	Link *wlink = distal;
	while (wlink != NULL) {
		// Get parent joint.
		Joint *parent = wlink->getParentJoint();
		if (parent->isChanged()) {
			result = 1;
			break;
		}
		wlink = wlink->getParentLink();
	}

	return (result);
}


// PROC:  combineLinks()
// DOES: combines two links into one. The links
//       must have a parent->child relationship and must
//       be given in parent first, child second order.
int ArticulatedObject::combineLinks(int argc, char **argv)
{
	if( argc != 2 ) 
	{
		printf("usage: combine <name of link1> <name of link2>\n") ;
		return TCL_OK ;
	}
	struct Link_s {
		Vector inbToJ ;
		Vector bodyToJ ;
		char name[MAX_LINE] ;
	} plink, clink, combinedLink ;
		
	int i ;
	

	Link *pl = getLink(argv[0]) ;
	if( pl == NULL )
	{
		printf("Link %s not found! Aborting operation.\n", argv[0]) ;
		return TCL_ERROR ;
	}
	Vector v ;
	pl->getParentJoint()->getInbToJoint(v) ;
	VecCopy(plink.inbToJ, v) ;
	pl->getParentJoint()->getBodyToJoint(v) ;
	VecCopy(plink.bodyToJ, v) ;
	strcpy(plink.name, pl->getName()) ;
	
	Link *cl = getLink(argv[1]) ;
	if( cl == NULL )
	{
		printf("Link %s not found! Aborting operation.\n", argv[1]) ;
		return TCL_ERROR ;
	}

	cl->getParentJoint()->getInbToJoint(v) ;
	VecCopy(clink.inbToJ, v) ;
	cl->getParentJoint()->getBodyToJoint(v) ;
	VecCopy(clink.bodyToJ, v) ;
	strcpy(clink.name, cl->getName()) ;

	// first calculate the new center of mass as
	// the average of the center of masses of the links being combined.
	// assumed that the coordinate system used is the one of the parent.
	Vector combCM ;
	VecSubtract(combCM, clink.inbToJ, clink.bodyToJ) ;
	VecScale(combCM, 0.5) ;
	// now combCM is the combined cm in the cs of the parent link.
	// for the combined links this is where its origin should be
	// so produce the appropriate body to joint. inb stays the same
	// as the parent link's
	VecCopy(combinedLink.inbToJ, plink.inbToJ) ;
	VecSubtract(combinedLink.bodyToJ, plink.bodyToJ, combCM) ;

	printf("Link combined inbtoJ %lf %lf %lf\n",
			combinedLink.inbToJ[0], 
			combinedLink.inbToJ[1], 
			combinedLink.inbToJ[2]) ;
	printf("\tbodyToJ %lf %lf %lf\n",
			combinedLink.bodyToJ[0], 
			combinedLink.bodyToJ[1],
			combinedLink.bodyToJ[2]) ;

	// now for every child link of the two links that combined
	// update the inbToJoint
	Link **childs = pl->getChildLinks() ;
	for( i = 0 ; i < pl->getNumChildLinks() ; i++ )
	{
		Vector citj, newcitj ;
		childs[i]->getParentJoint()->getInbToJoint(citj) ;
		VecAdd(newcitj, citj, combCM) ;
		printf("Link %s new parent combined\n", childs[i]->getName()) ;
		printf("\tinbtoj %lf %lf %lf\n", 
			newcitj[0], 
			newcitj[1], newcitj[2]) ;
	}

	childs = cl->getChildLinks() ;
	for( i = 0 ; i < cl->getNumChildLinks() ; i++ )
	{
		Vector citj, newcitj ;
		childs[i]->getParentJoint()->getInbToJoint(citj) ;
		VecAdd(newcitj, citj, combCM) ;
		printf("Link %s new parent combined\n", childs[i]->getName()) ;
		printf("\tinbtoj %lf %lf %lf\n", 
			newcitj[0], 
			newcitj[1], newcitj[2]) ;
	}

	return TCL_OK ;
}

// calculates the center of mass of the articulated object in world cordinates
// If a simulator is present then this it uses the simulator so that the
// center of mass is valid when the simulator uses a variable time step .
double *ArticulatedObject::calcCM(void)
{
    Vector origin = {0.0, 0.0, 0.0} ;
    Vector cm_link ;
    m_cm[0] = m_cm[1] = m_cm[2] = 0.0 ; 

    for( int i = 0 ; i < m_numLinks ; i++ )
    {
	if( simulator != NULL )
	    simulator->GetPosition(i, origin, cm_link) ;
	else
	    getWorldCoord(cm_link, origin) ;
	VecScale(cm_link, link[i]->getMass()) ; 
	VecAdd(m_cm, m_cm, cm_link) ;
    }
    VecScale(m_cm, 1.0 / (double) m_Mass) ;
    return &m_cm[0] ;
}

double *ArticulatedObject::calcCMVelocity(Vector vcm)
{
    if( simulator == NULL ) return NULL ;

    Vector origin = { 0.0, 0.0, 0.0 } ;
    Vector vcm_link = { 0.0, 0.0, 0.0 } ;

    for( int i = 0 ; i < m_numLinks ; i++ )
    {
	simulator->GetVel(i, origin, vcm_link) ;
	VecScale(vcm_link, link[i]->getMass()) ; 
	VecAdd(vcm, vcm, vcm_link) ;
    }
    VecScale(vcm, 1.0 / (double) m_Mass) ;
 
    return &vcm[0] ;
}

// This function calculates the delta-state that 
// that needs to be added to the current state in order
// to achieve the delta change given in the
// dpos of the point localPoint. The dpos is given in world coordinates.!!
// The number of parameters is nq and the delta values are returned in dq.
// If nlinkx is not zero then the chain is considered given by the caller
// and it is not calculated.
// LIMITATIONS: chains up to 50 links
//              uses the simulator only
// REQUIREMENTS: preallocate dq, nq, mapc, chain, nlinks
//                       dq : size NC at least
//                       mapc: size *nq
//                       chain: size *nlinks
//  int ArticulatedObject::InvKinSim(double *dq, int *nq, 
//  				 int *nlinks,
//  				 int *mapc,
//  				 int *chain,
//  				 int rootLink, int endEffLink,
//  				 Vector localPoint,
//  				 Vector dposition,
//  				 Vector dorien)
//  {
//      const int NC = 150 ;
//      const int NR = 6 ;
//      double Jac[NR][NC] ;
//      int i ;

//      Vector dpos ;
//      VecCopy(dpos, dposition) ;
//      if( (rootLink > m_numLinks) || (rootLink < 0) )
//      {
//  	danceTcl::OutputMessage("error: rootLink out of bounds.") ;
//  	return TCL_ERROR ;
//      }
//      if( (endEffLink > m_numLinks) || (endEffLink < 0) )
//      {
//  	danceTcl::OutputMessage("error: endEffLink out of bounds.") ;
//  	return TCL_ERROR ;
//      }
    
//      if( endEffLink == rootLink )
//      {
//  	danceTcl::OutputMessage("error: rootLink same as endEffLink.") ;
//  	return TCL_ERROR ;
//      }
//      // find the chain if not given
//      if( nlinks[0] == 0 )
//      {
//  	Link *p, *l = link[endEffLink] ;
//  	chain[0] = endEffLink ;
//  	for( i = 1 ; (l->m_linkNumber != rootLink) && 
//  	       ((p = l->getParentLink()) != NULL); i++ )
//  	{
//  	    chain[i] = p->m_linkNumber ;
//  	    if( p->getParentJoint()->getJointType() == J_BALL )
//  	    {
//  		danceTcl::OutputMessage("Ball joints not supported! Aborting.") ;
//  		return TCL_ERROR ;
//  	    }
//  	    l = p ;
//  	}
//  	nlinks[0] = i ;
//      }

//      int nca = 0 ;
//      for( i = 0 ; i < nlinks[0] ; i++ )
//      {
//         	Joint *pj = link[chain[i]]->getParentJoint() ;
//  	for( int j = 0 ; j <  pj->getNumAxis() ; j++ )
//  	    nca++ ;
//      }    
    
//      int nca_t = nca ;
//      for( i = 0 ; i < nlinks[0] ; i++ )
//      {
//         	Joint *pj = link[chain[i]]->getParentJoint() ;
//  	int naxis  =  pj->getNumAxis() ;
//  	for( int j = 0 ; j <  naxis ; j++ )
//  	{
//  	    Vector lin, rot ;
//  	    int coord = simulator->sdindx(pj->getNumber(),j) ;
//  		simulator->sdrel2cart(coord, chain[i], localPoint, lin, rot) ;
//  	    Jac[0][coord] = lin[0] ;
//  	    Jac[1][coord] = lin[1] ;
//  	    Jac[2][coord] = lin[2] ;
//  	    Jac[3][coord] = rot[0] ;
//  	    Jac[4][coord] = rot[1] ;
//  	    Jac[5][coord] = rot[2] ;
//  	    mapc[nca_t - naxis + j] = coord ;

//  	}
//  	nca_t -= naxis ;
//      }

  
//      // we have the jacobian so let's calculate the dq
//      int nra = 6 ;
//      int mapr[NR] ;
//      for( i = 0 ; i < NR ; i++ )
//  	mapr[i] = i ;
    
//      for( int j = 0 ; j < nca ; j++ )
//      {
//  	for( i = 0 ; i < NR ; i++ )
//  	    danceTcl::OutputMessage(" %lf", Jac[mapr[i]][mapc[j]]) ;
//  	danceTcl::OutputMessage("\n") ;
//      }
 	
//      int nranca = nca+nra ;
//      double *dw = new double[2*nranca*nranca] ;
//      if( dw == NULL )
//  	{
//  		danceTcl::OutputMessage("No more memory") ;
//  		return TCL_ERROR ;
//  	}
//      double *rw = new double[4*nranca] ;
//      if( rw == NULL )
//  	{
//  		danceTcl::OutputMessage("No more memory") ; ;
//  		return TCL_ERROR ;
//  	}
//      int *iw = new int[3*nranca] ;
//      if( iw == NULL )
//      {
//  	danceTcl::OutputMessage("No more memory") ; ;
//  	return TCL_ERROR ;
//      }
    
//      double dx[NR] = {0,0,0,0,0,0} ;
   
//      // transform all the vectors of the equation to the same system
//      // that the Jacobian applies. That system is the coord system
//      // of the father of the root node
    
//      int coordSysBody = SD_GROUND ;
//      Link *coordSysLink = link[rootLink]->getParentLink() ;
//      if( coordSysLink != NULL )
//  	coordSysBody = coordSysLink->getNumber() ;
    
//      simulator->sdtrans(SD_GROUND, dpos, coordSysBody, dpos) ;
//      VecCopy(&dx[0], dpos) ;
//      VecCopy(&dx[3], dorien) ;

//      // for testing
//      //VecCopy(&dx[0], newPosition) ;
   
//      danceTcl::OutputMessage("dx = %lf %lf %lf %lf %lf %lf",
//  			    dx[0],dx[1], dx[2], dx[3], dx[4], dx[5]) ;
    
//      simulator->sdlsslv(NR, NC, nra, nca, 0, mapr, mapc, 0.001, dw, rw, iw, 
//      		 &Jac[0][0], dx, dq) ; 

//      *nq = nca ;
    
//      delete [] dw ;
//      delete [] rw ;
//      delete [] iw ;
    
//      return TCL_OK ;
//  }


void ArticulatedObject::DeleteLinkChildren(Link *wlink)
{
	
	double point[3] = {0.0,0.0,0.0};
	if (wlink) {
		wlink->getEndEffectorWC(point);	
		wlink->DeleteChildren();
	}
	m_ActiveParent = wlink;
	setCurrentEndEffector(point);

}


//  // Makes and loads the simulator
//  int ArticulatedObject::LoadSimulator(Tcl_Interp *interp)
//  {
//      danceTcl::OutputMessage("Allocating simulator\n") ;	
//      simulator = (SdfastSimul *) new SdfastSimul(this, interp) ;
//      if( simulator == NULL )
//      {
//  	danceTcl::OutputMessage("Cannot allocate simulator!\n") ;
//  	return TCL_ERROR ;
//      }
    
//      // make	the shared object that holds the simulation routines
    
//      SdfastSimul::makeCompile(getName()) ;

//      return TCL_OK ;
//  }

int ArticulatedObject::BeforeSimStep(double time, DSimulator *sim)
{
   

    if(	isSimul	== FALSE )
	return 0 ;

    if(	simulator == NULL )
    {
		danceTcl::OutputResult("No simulator initalized	for %s\n", getName());
		return 0 ;
    }


    // added recently by Petros
    // reset the monitor points not to be underground
  //    MonitorPoints *mptsStruct ;
//      for( i = 0 ; i < m_numLinks ; i++ )
//      {
//  	mptsStruct = link[i]->getMonitorPoints() ;
//  	for( int j = 0; j < mptsStruct->m_NumPoints; j++ )
//  	{
//  	    mptsStruct->m_IsUnderGround[j] = FALSE ;
//  	}
//      }

    // calculate the next step
    // SdfastSimul::CurrentSimulObject = this ;
    return TCL_OK ;
}

int ArticulatedObject::AfterSimStep(double time, DSimulator *sim)
{
    Vector orig	= {0.0,0.0,0.0}	;
    Vector x = {1.0,0.0,0.0} ;
    Vector y = {0.0,1.0,0.0} ;
    Vector z = {0.0,0.0,1.0} ;

    // SdfastSimul::CurrentSimulObject = NULL ;

    int i ;
    for( i = 0 ; i < m_numLinks ; i++ )
    {
	// Update the transformation matrices in my structure for displaying.
	double x_axis[]	= {1.0,0.0,0.0};
	double y_axis[]	= {0.0,1.0,0.0};
	double z_axis[]	= {0.0,0.0,1.0};

	// For each link, find out the position	of the origin and axes
	// of the link frame in	world space.
	CoordSystem cs;
	simulator->GetPosition(link[i]->m_linkNumber,orig,cs.origin)	;
	simulator->GetOrientation(link[i]->m_linkNumber,x_axis,-1,cs.x) ;
	simulator->GetOrientation(link[i]->m_linkNumber,y_axis,-1,cs.y) ;
	simulator->GetOrientation(link[i]->m_linkNumber,z_axis,-1,cs.z) ;
//	link[i]->setPrevWTransMat() ;
	link[i]->setTransMat(cs);

    }

 
    // update joint positions ;
    // simulator->SetObjectStateFromState();
    return 1 ;
}

//  Handle skeleton motions.
int ArticulatedObject::PassiveMotionCB(DView *focus, int x, int y)
{

    // temp
    //    // Highlight a link if we are over it.
    static int item[256], numSelected ;
    if (HandleSelection(focus, x,y,GLUT_LEFT_BUTTON,
			       numSelected,item,Link_selection) == Link_selection) {
	PickedItem = item[0];
	
	if (PickedItem >= 0) { 
	    if (numSelected > 1) // Create a new branch in tree skeleton
		if	(item[1] < getNumLinks()) {
		    //Link **wLink = getLinks();
		    //dance::m_ActiveObject = wLink[item[1]]->getParentLink();
		    PickedItem = link[item[1]]->getParentLink()->m_linkNumber ;

		}
	}
    }
    return 1 ;
}

// Process collisions.
int ArticulatedObject::ProcessCollisions(void)
{
	// Check for collisions
	if (Link::m_VCollideEngine) {
		Link::m_VCollideEngine->Collide(); // Compute collisions
		const int size = 20 ; 
		VCReportType vcrep[size];
		int numCollisions = Link::m_VCollideEngine->Report(size, vcrep);
		//for (int i = 0 ; i < numCollisions; i++) {
		int numc ;
		if( numCollisions < size ) numc = numCollisions ;
		else numc = size ;
		for( int i = 0 ; i < numc ; i++ ) {
			Link *link1 = Link::GetGlobalLink(vcrep[i].id1);
			Link *link2 = Link::GetGlobalLink(vcrep[i].id2);
			link1->m_InCollision = TRUE;
			link2->m_InCollision = TRUE;	
		}
		return(numCollisions);
	}
	return(0);
}

// Returning 1 means that it matched the keystroke
// 0 means that it didn't.
int ArticulatedObject::KeyboardCB( unsigned char key, int x, int y )
{
    int matched = 0 ;
  
    switch((char) key)
    {
	case 'c':
		m_CheckCollisions = (m_CheckCollisions + 1) % 3;
		danceTcl::OutputMessage("Collision detection mode: %d",m_CheckCollisions);
		break;
	case 'j': 
	    ArtObjAppMode = Joint_edit_mode ;
	    dance::AppMode = system_mode ;
	    matched = 1 ;
	    danceTcl::OutputMessage("Joint edit mode.") ;
	    break ;
	case 's':
	    ArtObjAppMode = Skeleton_creation_mode ;
		m_SkeletonCreateMode = eChooseParentLink;
	    dance::AppMode = system_mode ;
	    danceTcl::OutputMessage("Skeleton creation mode.") ;
	    matched = 1 ;
	    break ;
    }

	// Update display.
	DView *view = dance::AllViews->getViewFocus();
	if (view) view->postRedisplay();
    return matched ;
}	    


// Start the interaction and set the local mode.
// If the interaction finishes here we return 0
// else we return 1
int ArticulatedObject::InteractStart(Event *event)
{

    int *item = event->pickItem ;
	double depth = event->Window->getDepth(event->winX,event->winY);
	if (depth == 1.0) {
		if (m_SkeletonCreateMode != eChooseParentLink) {
			// Point selected is on far clipping plane, move it forward to the
			// depth value of the anchor point for more intuitive joint positions.
			double winpoint[3];
			event->Window->getWindowCoords(m_AnchorPoint,winpoint);
			depth = winpoint[2];
		}
		else
			depth = 0.5; // half way point in viewing volume
	}
	else {// Selected something in the depth buffer. 

		// Choose point in depth buffer.
		depth = -1.0;

		// Create a new chain from the selected link.
		if (m_SkeletonCreateMode != eDefineEndEffector)
			m_SkeletonCreateMode = eChooseParentLink;
	}

	event->Window->getWorldCoords(dance::CursorPosn,event->winX,event->winY, depth);
    
	switch( ArtObjAppMode )
    {
	case Skeleton_creation_mode:
	    if (event->buttonID == GLUT_LEFT_BUTTON && event->buttonState == GLUT_DOWN)
	    {
		
			switch(m_SkeletonCreateMode) {
			case eChooseParentLink:
				if (getNumLinks() == 0) { // No links exist yet.
					m_ActiveParent = NULL;
					setCurrentEndEffector(dance::CursorPosn);
					getCurrentEndEffector(m_AnchorPoint);
					m_SkeletonCreateMode = eDefineJointPosition;
				}
				else {
				int numSelected = 0 ;
				HandleSelection(event->Window, event->winX, event->winY, event->buttonID,numSelected,item,Link_selection) ;
				if( numSelected > 0 ) // Selected a link.
				{
					PickedItem = item[0];
					if (PickedItem >= 0 && PickedItem < getNumLinks())  // Selected a link
						if (m_SkeletonCreateMode == eChooseParentLink) {
							// Create a new chain extension.
							Link **wLink = getLinks();					
							m_ActiveParent = wLink[PickedItem];
						
							m_ActiveParent->getPosition(m_AnchorPoint);
							m_SkeletonCreateMode = eDefineEndEffector;
						}
				}
				
				}
				break;
			case eDefineEndEffector: // Selected an end-effector
				setCurrentEndEffector(dance::CursorPosn);
				m_SkeletonCreateMode = eDefineJointPosition;
				break;
			case eDefineJointPosition:
				{
				// Make a link.
				addLink(m_CurrentEndEffector,dance::CursorPosn);			
				setCurrentEndEffector(dance::CursorPosn);
				getCurrentEndEffector(m_AnchorPoint);
				}
				break;
			}
	    }
	    else // Recalculate bounding box
	    {
			BoundingBox b;
			calcBoundingBox(&b);			
			PickedItem = -1 ;
			return 0 ;	// shows we are finished with the interaction	
		
	    }
	    break;
	case Joint_edit_mode:
	    
	    if (event->buttonState == GLUT_DOWN) 
	    {
		int numSelected = 0;
		if (HandleSelection(event->Window, event->winX,event->winY,event->buttonID,
			numSelected,item,Joint_selection) == Joint_selection) {
		    PickedItem = item[0];
		    
		    // Ignore modifier if we are choosing the right or middle button
			m_ActiveJoint = joint[item[0]];
			m_PickedDof = -1;
		    if (numSelected > 1) 
				m_PickedDof = item[1];
		    else
				m_PickedDof = -1;
		    
		    // Determine DirectionMode
		    switch(dance::m_ModifierKey) {
			case GLUT_ACTIVE_SHIFT: 
				m_JointDirectionMode = up_direction; 
				break;
			case GLUT_ACTIVE_CTRL:  
				m_JointDirectionMode = down_direction; 
				break;
			default: 
				m_JointDirectionMode = global_direction;
		    }
		}
		else
		{ 
		    m_PickedDof = -1 ;
		    PickedItem = -1 ;
		    m_ActiveJoint = NULL ;
		    return 0 ;
		}
	
        }
	    break;
	    
    }
    
    return 1 ;
}

int ArticulatedObject::HandleSelection(DView *view, int x, int y, int button, 
				       int &number, int *item, int type)
{
	int selection_mode = -1;

	// Set up selection buffer.
	static GLuint SelectBuffer[512];
	glSelectBuffer(512,SelectBuffer);

	// Begin picking.
	glRenderMode(GL_SELECT);
	glInitNames();

	view->pickProjection(x,y,7.0,7.0);
	view->PositionCamera();

	switch(type) {
	    case Joint_selection:
		glPushName(Joint_selection);
		if (button == GLUT_LEFT_BUTTON)
		    displayJoints(JDISPLAY_MANIPS);
		else
		    displayJoints(JDISPLAY_CENTRES);
		glPopName();
		break;
	    case Link_selection:
		glPushName(Link_selection);
		
		// Must use	output with two	arguments.
		displayLinks(LDISPLAY_SOLID|LDISPLAY_SELECTION);
		glPopName();
		break;
	}
	
	glFlush() ;

	// Process hits.
	int hits = glRenderMode(GL_RENDER);

	view->setProjection();

	int hp = 0;

	// Must use unsigned int for distance calculations to be correct.
	unsigned int closest = 0;

	// Loop	through	and pick the front-most	item
	for (int h = 0;	h < hits; h++) {
		int pickThis = 0;
		int numNames = SelectBuffer[hp++];
		unsigned int minz = SelectBuffer[hp++];
		unsigned int maxz = SelectBuffer[hp++];
		if (h==0) {
			closest	= minz;
			pickThis = 1;
		}
		else if	(minz <= closest)
			pickThis = 1;
		
		
		if (pickThis) {
		    number = 0;
		    for	(int ns	= hp; ns < hp+numNames;	ns++) {
			if (ns == hp)
			    switch(SelectBuffer[ns])	{
				case Joint_selection:
				    selection_mode = Joint_selection ;
				    break;
				case Link_selection:
				    selection_mode = Link_selection;
				    break;
			    }
			else {
			    item[ns-hp-1] =	SelectBuffer[ns];
			    number = ns-hp;
			}
		    }
		    if (number == 0) item[0] = -1;
		}
		hp += numNames;
		
	}
	
	return(selection_mode);
}

void ArticulatedObject::HandleSkeletonButtons(DView *focus, int button, 
					      int state, int x, int y, int width, int height)
{
        GLdouble point[3];
        static GLdouble oldpoint[3];
        enum skeleton_status {
           waitingFirstPoint,
           waitingSecondPoint
        };
        
        //ArticulatedObject *active =(ArticulatedObject *)AllSystems->getActive();
	
        switch(button) {
	    case GLUT_LEFT_BUTTON:
		// get 3D point from 2D window
			focus->getWorldCoords(dance::CursorPosn,x,y,0.5);
		
		if (state == GLUT_DOWN) {
		    
		    if (m_SkeletonCreateMode == eDefineJointPosition) {
				// Make a link.
				getCurrentEndEffector(oldpoint) ;
				addLink(oldpoint,point);
		    }
		    setCurrentEndEffector(point);
		    ArtObjAppMode = Skeleton_creation_mode ;
		}
		break;
	    default:
		 if( ArtObjAppMode == Skeleton_creation_mode ) 
		     ArtObjAppMode = Normal_mode ;
        }
	
}

void ArticulatedObject::Interact(Event *event)
{
    switch(ArtObjAppMode)
    {
	case Joint_edit_mode:
	
	    HandleJointEdits(event->Window,event->winX,event->winY,
			     event->winWidth,event->winHeight,
			     event->winDiffX,event->winDiffY);
	    break;
    }
    return ;
}

int ArticulatedObject::InteractEnd(Event *event)
{
    return 1 ;
}

//  Handle joint editing
void ArticulatedObject::HandleJointEdits(DView *focus, int x, int y, int width, int height, int diffx, int diffy)
{
    if (PickedItem == -1)	return;

    if( m_ActiveJoint == NULL )
	return ;

	SetLastState();

	if (m_PickedDof == -1) { // Move the	joint
	   GLdouble win[3], jpos[3];

	   // This code will move the joint to the mouse position. It uses the depth value
	   // of the old joint position.
	   m_ActiveJoint->getPosition(jpos);
	   focus->getWindowCoords(jpos,win);
	   focus->getWorldCoords(jpos,	x, y, win[2]);

	   switch(m_JointDirectionMode) {
	      case global_direction:
		   m_ActiveJoint->setPosition(jpos);
	      break;
	      case down_direction:
		   moveJointAndChildren(m_ActiveJoint->m_jointNumber,jpos);
	      break;
	      case up_direction:
		   moveJointAndParents(m_ActiveJoint->m_jointNumber,jpos);
	      break;
	   }
	   updateStateConfig(); // Updates all joints.
	}
	else { // Handle joint state editing
	

		// Calculate delta value for angles.
	    double delta_angle = 2.0*M_PI/(double)width*(diffx+diffy); 
		
		// Calculate delta value for translations
		double pos[3]; m_ActiveJoint->getPosition(pos);
		double win[3]; focus->getWindowCoords(pos,win);
		double worldwidth = focus->getFrustumWidth(win[2]);
		double delta_trans = (diffx+diffy)*worldwidth/width;
		
		m_ActiveJoint->addDof(m_PickedDof,delta_angle,delta_trans);
	
	    updateStateConfig(m_ActiveJoint->m_jointNumber);
	}
	
	if (m_CheckCollisions) {
		if (ProcessCollisions())  // Test out the collision engine.
			if (m_CheckCollisions == 2) {
				revertToLast();
				updateStateConfig();
			}
	}
	
	focus->postRedisplay();	// Redisplay
}

int ArticulatedObject::InitSimulation(double time, DSimulator *sim)
{
	int i ;
	simulator = sim ;
    // reset the monitor points not to be underground
    MonitorPoints *mptsStruct ;
    for( i = 0 ; i < m_numLinks ; i++ )
    {
	mptsStruct = link[i]->GetMonitorPoints() ;
	for( int j = 0; j < mptsStruct->m_NumPoints; j++ )
	{
	    mptsStruct->m_InCollision[j] = FALSE ;
	}
    }
    return TCL_OK ;
}

void ArticulatedObject::WriteMayaFile(char *fname)
{
    if( getNumJoints() < 1 ) return ;
    FILE *fp ;
    if( fname == NULL ) 
	fp = stdin ;
    else
	fp = fopen(fname, "w") ;
    if( fp == NULL ) 
    {
	danceTcl::OutputMessage("WriteMayaFile: ERROR: Cannot open %s", fname) ;
	return ;
    }
    Joint **j = getJoints() ;
    for( int i = 0 ; i < getNumJoints(); i++ )
   	j[i]->WriteMayaFile(fp) ;
	fclose(fp) ;

	danceTcl::OutputMessage("Maya mel format saved in %s", fname) ;
		
    return ;
}

void ArticulatedObject::BuildAndLinkSimulator(void)
{

	if( simulator != NULL ) return ;

    char sdname[132] ;
    sdname[0] = '\0' ;
    char command[132] ;
    command[0] = '\0' ;
    // check to see if we have to save the file
    
    sprintf(sdname, "%s/sdfastObjs/%s/%s.sd", getenv("DANCE_DIR"),
	    getName(), getName()) ;
    FILE *fp = fopen(sdname, "r") ;
    
    if( fp == NULL )
    {
	command[0] = '\0' ;
	sprintf(command, "system %s save sdfast", getName()) ;
	danceTcl::ExecuteCommand(command) ;
	fp = fopen(sdname, "r") ;
	if( fp == NULL )
	{
	    danceTcl::OutputMessage("ERROR: Cannot save sdfast file."
				    " Simulator not loaded.") ;
	    return ;
	}
	
    }
    fclose(fp) ;

    char *argv = "SdfastSimul" ;

    command[0] = '\0' ;
    char simulName[50] ;
    simulName[0] = '\0' ;
    sprintf(simulName, "%sSimulator", getName()) ;
    sprintf(command, "instance SdfastSimul %s %s", simulName, getName()) ;
    danceTcl::ExecuteCommand(command) ;
}

