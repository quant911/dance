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

#include "defs.h"
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "Link.h"

#include "DSimulator.h"
#include "ArticulatedObject.h"
#include "Joint.h"
#include "ViewManager.h"
#include "DView.h"
#include "GLutilities.h"
#include "VCollide.h"
#include "RAPID.h" // VIC: For test
#include <assert.h>

////////////////////////////////
//// GLOBALS
////////////////////////////////

// VCOLLIDE collision detection engine for multi-body collisions.
//
VCollide *Link::m_VCollideEngine = NULL;

// VCOLLIDE global list of links indexed by the m_VCollideID number.
#define BINSIZE 100
int Link::m_numGlobalLinks = 0;
Link **Link::m_GlobalLinks = NULL;

Link::~Link()
{
	// NOTE: Geometry deletion is handled by the Geometry instance itself. Do not
	// delete it twice here.

	// Remove references to link and parent joint from articulated object. We do
	// this here because it must be done for every link in subtree.
	int found = -1;
	Link **wlink = ao->getLinks();
	int numLinks = ao->getNumLinks();
	for (int i = 0; i < numLinks; i++)
		if (wlink[i] == this) {
			found = i;
			break;
		}

	assert(found != -1);
	Joint **wjoint = ao->getJoints();
	int numJoints = ao->getNumJoints();

	// Remove link and joint from articulated figure list.
	if (found < numLinks-1) { 
		memcpy(&wlink[found],&wlink[found+1],sizeof(Link *)*(numLinks-1-found));
		memcpy(&wjoint[found],&wjoint[found+1],sizeof(Joint *)*(numJoints-1-found));
	}
	ao->m_numJoints--;
	ao->m_numLinks--;
	
	// Remove parent joint and all its hooks.
	if (parentJoint)
		delete parentJoint;

	// Remove from Global link list.
	RemoveGlobalLink(this);

	// Delete VCollideID object.
	if (m_VCollideID != -1)
		m_VCollideEngine->DeleteObject(m_VCollideID);

	// Remove all child links.
	for (int c = 0; c <  m_numChildLinks; c++)
		delete childLink[c];
}

// constructor that sets the link number too
Link::Link(int ln)
{

    m_inCollision.objectName[0] = '\0' ;
    m_inCollision.linkNumber = -1 ;
	// General properties
    m_linkNumber = ln ;
    m_VCollideID = -1;
    sprintf(getName(), "link%d", ln) ;
    setType("Link");
	setBaseType("Link");

    ao = NULL ;
    parentLink = NULL ;
    parentJoint	= NULL ;
    m_numChildLinks = 0 ;

    setIdentMat(&m_transMat[0][0],4) ;
    invSmart4(m_invTransMat,m_transMat) ;
    endEffector[0] = endEffector[1] = endEffector[2] = 0.0;
	
	// Geometry properties.
    m_Geom = NULL;
    geomScale[0] = geomScale[1]	= geomScale[2] = 1.0;
    geomFix = 0;

	// Viewing properties.
	m_DisplayGeometry = TRUE ;
	m_DisplayAxes = FALSE ;
	m_DisplayBoundingBox = FALSE;
	m_DisplayNormals = FALSE ;
	m_InCollision = FALSE;

	m_Transparency = 0.0;

	// Mass Properties.
    m_Mass = 1.0 ;
    m_InerTensorIsDiagonal = 1;

    for( int i = 0 ; i < 3 ; i++ )
		for( int j = 0 ; j < 3 ; j++ ) {
			if (i == j)
				m_InerTensor[i][j] = 1.0 ;
			else
				m_InerTensor[i][j] = 0.0 ;
		}
    
}

// writeSdFile():
// writes the info of a	link and its parent joint on sdfast format
// Question marks allow	for quantities to be modified at a later stage.
// NOTE: sdfast	uses the minus sign convention for off-diagonal	elements.
// this	routines assumes that the inertia tensor is already calculated
// properly.
int Link::writeSdFile(FILE *fp)
{
    int	i ;

    fprintf(fp,"body = %s ",getName()) ;
    if(	parentLink == NULL)
	fprintf(fp,"inb	= $ground ");
    else
	fprintf(fp,"inb	= %s ",	parentLink->getName()) ;

    if (parentJoint == NULL) return 0;

    switch (parentJoint->m_jointType)
    {
	case J_PIN:
	    fprintf(fp,"joint = pin\n")	;
	    break ;
	case J_PLANAR:
	    fprintf(fp,"joint = planar\n")	;
	    break ;
	case J_BALL:
	    fprintf(fp,"joint = ball\n") ;
	    break ;
	case J_CYLINDER:
	    fprintf(fp,"joint = cylinder\n") ;
	    break ;
	case J_SLIDER:
	    fprintf(fp,"joint = slider\n") ;
	    break ;
	case J_FREE:
	    fprintf(fp,"joint = free\n") ;
	    break ;
	case J_GIMBAL:
	    fprintf(fp,"joint = gimbal\n") ;
	    break ;
	case J_UNIVERSAL:
	    fprintf(fp,"joint = ujoint\n") ;
	    break ;
	case J_BUSHING:
	    fprintf(fp,"joint = bushing\n") ;
	    break ;
	case J_BEARING:
	    fprintf(fp,"joint = bearing\n") ;
	    break ;
	default:
	    fprintf(fp,"Unkonw type of joint!\n") ;
	    return ERR ;
    }
    fprintf(fp,"\tmass = %f\n",	m_Mass) ;
    fprintf(fp,"\tinertia = ") ;
    // print the inertia matrix. If the	matrix is diagonal
    // exploit it and print only the diagonal elements.
    // That makes the dynamics run faster.
    if (m_InerTensorIsDiagonal)
		fprintf(fp,"%f %f %f\n",m_InerTensor[0][0], m_InerTensor[1][1],m_InerTensor[2][2]) ;
    else
    {
		// sdfast follows the minus sign covention for non-diagonal elements
		fprintf(fp,"%f %f %f\n",m_InerTensor[0][0],m_InerTensor[0][1],m_InerTensor[0][2]) ;
		fprintf(fp,"\t\t%f %f %f\n",m_InerTensor[1][0],m_InerTensor[1][1],m_InerTensor[1][2])	;
		fprintf(fp,"\t\t%f %f %f\n",m_InerTensor[2][0],m_InerTensor[2][1],m_InerTensor[2][2])	;
    }

    Vector inbToJ ;
    Vector outToJ ;

    VecCopy(inbToJ,parentJoint->m_InbToJoint) ;
    //if( parentJoint->inboardLink != NULL )
    //	rotPoint_mat4(inbToJ,parentJoint->inboardLink->m_transMat) ;
    if(	m_linkNumber == 0)
	fprintf(fp,"\tinbtojoint = %f %f %f\n", inbToJ[0], inbToJ[1],inbToJ[2]) ;
    else
	fprintf(fp,"\tinbtojoint = %f %f %f\n",	inbToJ[0], inbToJ[1],inbToJ[2])	;

    VecCopy(outToJ, parentJoint->m_BodyToJoint) ;
    //rotPoint_mat4(outToJ,parentJoint->outboardLink->m_transMat)	;
    fprintf(fp,"\tbodytojoint =	%f %f %f\n", outToJ[0],	outToJ[1], outToJ[2]) ;

    // print the line that will	allow the axis to be prescribed	if needed
    // by default no presecribed motion	is on
    int	ndof = parentJoint->getNumDof()	;
    for( i = 0 ; i < parentJoint->getNumDof() ;	i++ )
    {
	if( i == 0)
	    fprintf(fp,"\tprescribed = 0?") ;
	else
	    fprintf(fp," 0?") ;
	if( i == (ndof-1))
	    fprintf(fp,"\n") ;
    }



    // print the pin axis
    for( i = 0 ; i < parentJoint->m_numAxis ; i++	)
	fprintf(fp,"\tpin = %f %f %f\n", parentJoint->m_axis[i][0],
		parentJoint->m_axis[i][1],parentJoint->m_axis[i][2]) ;

    return OK ;

}

// reads in the	link information and creates a new joint
// It follows only the format produced by the Link::writeSdFile()
Link *Link::readSdfast(FILE *fp)
{
    char line[MAX_LINE], tok[MAX_LINE] ;
    char parent_name[MAX_LINE],joint_type[MAX_LINE] ;
    int	found =	FALSE, i, j,numAxis, itype ;
    Vector bodyToJoint,	inbToJoint, axis[3] ;
    char *types[12] = {"unknown","pin","ball","cylinder","slider","free",
		       "gimbal","weld","planar","bearing","ujoint","bushing"} ;

    while(!feof(fp) && (found == FALSE))
    {
	fgets(line,MAX_LINE,fp)	;
	sscanf(line,"%s", tok) ;
	if(strcmp(tok,"body") == 0)
	{
	    if(sscanf(line,"body = %s inb = %s joint = %s", getName(),parent_name,
		      joint_type) != 3)
	    {
		danceTcl::OutputMessage("Can't find body line: %s",line) ;
		return NULL ;
	    }
	    else
		found =	TRUE ;
	}
    }

    if(	found != TRUE) danceTcl::OutputMessage("Cannot find body!") ;
    // read mass
    found = FALSE ;
    while(!feof(fp) && (found == FALSE))
    {
	fgets(line,MAX_LINE,fp)	;
	sscanf(line,"\t%s", tok) ;
	if(strcmp(tok,"mass") == 0)
	{
	    if(sscanf(line,"\tmass = %lf", &m_Mass) != 1)
	    {
		danceTcl::OutputMessage("Can't find mass line:%s",line) ;
		return NULL ;
	    }
	    else
		found =	TRUE ;
	}
    }
     if( found != TRUE)	danceTcl::OutputMessage("Cannot find mass!") ;

    // read inertia
    int	alreadyRead = FALSE ;	// read	from inertia
    found = FALSE ;
    while(!feof(fp) && (found == FALSE))
    {
	fgets(line,MAX_LINE,fp)	;
	sscanf(line,"\t%s", tok) ;
	if(strcmp(tok,"inertia") == 0)
	{
	    if(sscanf(line,"\tinertia =	%lf %lf	%lf", &m_InerTensor[0][0],
		      &m_InerTensor[0][1],&m_InerTensor[0][2]) != 3)
	    {
			danceTcl::OutputMessage("Bad inertia line: %s\n",line) ;
			return NULL ;
	    }
	    fgets(line,MAX_LINE,fp) ;
	    alreadyRead	= TRUE ;
	    if(sscanf(line,"\t%lf %lf %lf", &m_InerTensor[1][0],&m_InerTensor[1][1],
		      &m_InerTensor[1][2]) == 3)
	    {
		m_InerTensorIsDiagonal = 0;
		fgets(line,MAX_LINE,fp)	;
		if(sscanf(line,"\t%lf %lf %lf",	&m_InerTensor[2][0],
			  &m_InerTensor[2][1],&m_InerTensor[2][2]) != 3)
		{
		    danceTcl::OutputMessage("Bad inertial values: %s\n",line) ;
		    return NULL	;
		}
		found =	TRUE ;
		alreadyRead = FALSE ;
	    }
	    else // The inertia tensor is a diagonal matrix with three moments of inertia.
	    {
		found =	TRUE ;
		// bring it in diagonal	form
		m_InerTensorIsDiagonal = 1;
		m_InerTensor[1][1] = m_InerTensor[0][1] ;
		m_InerTensor[2][2] = m_InerTensor[0][2] ;
		for( i = 0 ; i < 3 ; i++ )
		    for( j = 0 ; j < 3 ; j ++)
			if( i != j) m_InerTensor[i][j] = 0.0 ;
	    }	
	}
    }
    
    if( found != TRUE)	danceTcl::OutputMessage("Cannot find inertia!\n") ;
    
    // read inb	to joint
    found = 0 ;
    while(!feof(fp) && (found != 2))
    {
	//danceTcl::OutputMessage("Reading inbtojoint\n") ;
	if( alreadyRead	== FALSE )
	{
	    fgets(line,MAX_LINE,fp) ;
	}
	else alreadyRead = FALSE ;
	sscanf(line,"\t%s", tok) ;
	char dummy[50] ;
	if( (strcmp(tok,"inbtojoint") == 0) || (strcmp(tok, "inbToJoint") == 0))
	{
	    found++  ;
	    //danceTcl::OutputMessage("This is |%s|",line) ;
	    //danceTcl::OutputMessage("Link number = %d\n", m_linkNumber) ;
	    if(sscanf(line,"\t%s = %lf %lf %lf", dummy,
		      &inbToJoint[0],&inbToJoint[1], &inbToJoint[2]) != 4)
	    {
		if(sscanf(line,"\t%s = %lf? %lf? %lf?", dummy,
			  &inbToJoint[0],&inbToJoint[1], &inbToJoint[2]) != 4)
		{
		    danceTcl::OutputMessage("Bad inbtojoint with link: %s\n",line);
		    return NULL	;
		}
	    }
	}
	else if( (strcmp(tok,"bodytojoint") == 0) || (strcmp(tok,"bodyToJoint") == 0) )
	{
	    found++ ;
	    if(sscanf(line,"\t%s = %lf	%lf %lf", dummy,
		      &bodyToJoint[0],&bodyToJoint[1], &bodyToJoint[2])	!= 4)
	    {
		danceTcl::OutputMessage("7:Wrong format of input file. Aborting!\n") ;
		return NULL ;
	    }
	}
    }
    if(	found != 2 )
	danceTcl::OutputMessage("WARNING: No inbtojoint or bodytojoint"
				"found for link %d\n", m_linkNumber) ;


    // find the	type of	the Joint

    found = FALSE ;
    for( i = J_UNDEF ; i <= J_BUSHING && (found	== FALSE) ; i++)
    {
	if( strcmp(joint_type,types[i])	== 0)
	{
	    itype = i ;
	    found = TRUE ;
	}
    }

    if(	found == FALSE)
    {
	danceTcl::OutputMessage("Unknown	type of	joint! Aborting\n") ;
	return NULL ;
    }

    //-- read axis---
    // first see how many axis we expect
    switch(itype)
    {
	case J_PIN:
	    numAxis =	1 ;
	    break ;
	case J_PLANAR:
	    numAxis = 3 ;
	    break ;
	case J_FREE:
	    numAxis =	3 ;
	    break ;
	case J_BALL:
	    numAxis =	0 ;
	    break ;
	case J_GIMBAL:
	    numAxis =	3;
	    break;
	case J_UNIVERSAL:
	    numAxis =	2 ;
	    break ;
	case J_WELD :
	    numAxis = 0 ;
	    break ;
	default:
	    danceTcl::OutputMessage("Not implemented yet!\n") ;
	    break ;
    }


    // now read	them
    for( i = 0 ; i < numAxis ; i++)
    {

	found =	FALSE ;
	if( feof(fp)) danceTcl::OutputMessage("END\n") ;
	while(!feof(fp)	&& (found == FALSE))
	{
	    fgets(line,MAX_LINE,fp) ;
	    sscanf(line,"\t%s",	tok) ;
	    // danceTcl::OutputMessage("|%s|",line) ;
	    if(	strcmp(tok,"prescribed") == 0) // consume the prescribed motion	line
		continue ;
	    if(strcmp(tok,"pin") == 0)
	    {
		found =	TRUE ;
		if(sscanf(line,"\tpin =	%lf %lf	%lf",&axis[i][0],&axis[i][1], &axis[i][2]) != 3)
		{
		    danceTcl::OutputMessage("8:Wrong format of input file. Aborting!\n")	;
		    return NULL	;
		}
	    }
	}

	if (found == FALSE)
	{
	    danceTcl::OutputMessage("readSdfast:	missing	axis information! Aborting!\n")	;
	    return NULL	;
	}
    }

    /****** Debugging **********
    danceTcl::OutputMessage("mass: %f\n", m_Mass) ;
    danceTcl::OutputMessage("axis read:\n") ;
    for( i = 0 ; i < numAxis ; i++ )
	danceTcl::OutputMessage("pin = %f %f %f\n", axis[i][0], axis[i][1], axis[i][2]) ;

    danceTcl::OutputMessage("inertia read:\n") ;
    for( i = 0 ; i < 3 ; i++ )
	danceTcl::OutputMessage("%f %f %f\n", m_InerTensor[i][0], m_InerTensor[i][1], m_InerTensor[i][2]) ;

    danceTcl::OutputMessage("Inboard = %s name =	%s joint type =	%s\n", parent_name, name, joint_type) ;
    *****************************/

    // ***********************************************************************
    // now all the information we need is found. Fill in all the proper	fields
    // and create the joint
    // ***********************************************************************


    // find and	set parent

    setParentLink(NULL)	;
    if(	strcmp(parent_name,"$ground") != 0)
    {
	Link **links = ao->getLinks() ;
	for( i = 0 ; i < ao->getNumLinks() ; i++ )
	{
	    if(strcmp(links[i]->getName(), parent_name)	== 0 )
		setParentLink(links[i])	;
	}
	if( parentLink == NULL )
	{
	    danceTcl::OutputMessage("Couldn't find parent link with the name %s\n", parent_name)	;
	    return NULL	;
	}
    }

    // define the coordinate system
    Link *pl = getParentLink() ;
    CoordSystem	cs;
    setVector(cs.x, 1.0,0.0,0.0) ;
    setVector(cs.y, 0.0,1.0,0.0) ;
    setVector(cs.z, 0.0,0.0,1.0) ;
    VecSubtract(cs.origin, inbToJoint, bodyToJoint) ;

    // give the link an end effector.
    // A good guess is the -bodyToJoint 
    Vector endeff ;
    VecNumMul(endeff, bodyToJoint, -1) ;
    setEndEffector(endeff) ;

    if(	pl != NULL )
    {
	Vector parent_position ; pl->getPosition(parent_position) ;
	VecAdd(cs.origin, parent_position, cs.origin) ;
    }
    setCenterMass(m_transMat[3]) ;

    setTransMat(cs);

    // allocate	joint and fill in the fields
    // Caution!! All link fields must be properly set
    // to ensure that the joint	is created properly
    Joint *joint = new Joint;
    if(	joint == NULL)
    {
	danceTcl::OutputMessage("Cannot allocate joint!\n") ;
	return NULL ;
    }

    joint->create(ao->getNumJoints(), itype,pl, this) ;
    joint->m_numAxis = numAxis ;
    for( i = 0 ; i < numAxis ; i++)
		VecCopy(joint->m_axis[i],axis[i]);

	// Make special axes for BALL joint.
	if (itype == J_BALL) {
		setVector(joint->m_axis[0], 1.0,0.0,0.0) ;
		setVector(joint->m_axis[1], 0.0,1.0,0.0) ;
		setVector(joint->m_axis[2], 0.0,0.0,1.0) ;
	}

    VecCopy(joint->m_InbToJoint,inbToJoint) ;
    VecCopy(joint->m_BodyToJoint,bodyToJoint) ;
    // add joint in the	articulated object
    ao->addJoint(joint)	;


    // set parent joint	for the	link
    setParentJoint(joint) ;

    danceTcl::OutputMessage("Read joint %s\n", joint->getName()) ;
    return this	;
}


void Link::print(FILE *fptr)
{
    fprintf(fptr,"\n     # Link %d\n",m_linkNumber);
    if (m_Geom) {
	fprintf(fptr,"     system %s link %s geometry %s\n",
		ao->getName(),getName(),m_Geom->getName());
	fprintf(fptr,"     system %s link %s scale %f %f %f\n",
		ao->getName(),getName(),geomScale[0],geomScale[1],geomScale[2]);
	
	if (fabs((double)m_Transparency) > 0.01)
	    fprintf(fptr,"     system %s link %s transparency %f\n",
		    ao->getName(),getName(),m_Transparency);
	if (m_DisplayNormals == TRUE)
	    fprintf(fptr,"     system %s link %s normals on\n",
		    ao->getName(),getName());
	if (m_DisplayBoundingBox == TRUE)
	    fprintf(fptr,"     system %s link %s boundingBox on\n",
		    ao->getName(),getName());
    }
}


//
//	mode: 1	for axes and origin, 2 for bounding box	of geometry,
//	      4	for bounding boxes for links, 8	for shadows, 16	for wire frame,
//	      32 for solid, 64 for monitor points
void Link::Display(int mode)
{
    
    glPushAttrib(GL_ENABLE_BIT);
    
    if( mode & LDISPLAY_SHADOW )
	glDisable(GL_LIGHTING);
    
    int noskip = ((mode & LDISPLAY_SELECTION) == 0 && (mode & LDISPLAY_SHADOW) == 0);
    
    if(	m_Geom != NULL ) {
	// Turn on back face culling to prevent uneven transparency due to
	// additional blending operations. Also gives a solid wireframe effect.
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	// Do something if in collision.
	if (m_InCollision == TRUE && noskip) {
	    glPushAttrib(GL_ENABLE_BIT);
	    glDisable(GL_LIGHTING);
	    glColor4f(1.0,0.0,0.0,1.0);
	    displayBoundingBox(1.0,0.0,0.0,1.0);
	    glPopAttrib();
	}
	
	
	glPushMatrix() ;
	glMultMatrixd(&m_transMat[0][0]);
	
	
	if (noskip) {
	    
	    if (m_DisplayAxes) 
		displayAxes();
	    
	    // Bounding box	is in world coordinates, don't multiply	again by m_transMat
	    if (m_DisplayBoundingBox) {
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		m_Geom->displayBoundingBox((float)0.0,(float)0.0,(float)0.7,(float)1.0);
		glPopAttrib();
	    }
	}
	
	if (mode & (unsigned int) (LDISPLAY_WIRE | LDISPLAY_SOLID | LDISPLAY_SHADOW )) {
	    
	    if (fabs((double)m_Transparency) > 0.01) {
		
				// Set blending parameters.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		
				// Adjust geometry transparency level.
		m_Geom->setTransparency(m_Transparency);
	    }
	    
	    //MonitorPoints *mptsStruct = getMonitorPoints() ;
	    
	    //glPointSize(4) ;
	    //glBegin(GL_POINTS) ;
	    //for( int i = 0 ; i < mptsStruct->m_NumPoints ; i++ )
	    //	{
	    //		glColor3f(1.0, 0.0, 0.0) ;
	    //		glVertex3dv(mptsStruct->m_Point[i]) ;
	    //}
	    //glEnd() ;
	    //glPointSize(1) ;
	    
	    if (geomFix)
		glScaled(geomScale[0],geomScale[1],geomScale[2]);
	    
	    
	    
	    
	    // display normals
	    if (m_DisplayNormals && noskip)
		m_Geom->displayNormals();
	    
	    // display object
	    if( m_DisplayGeometry == TRUE )
		m_Geom->display(mode);
	    
	    if (fabs((double)m_Transparency) > 0.01) { 
		glDisable(GL_BLEND);
		m_Geom->setTransparency(0.0);
	    }
	    
	}
	
	glPopMatrix() ;
    }
    else  { // No geometry, draw default geometry.
	double pos[3]; getPosition(pos);
	
	glDisable(GL_LIGHTING);
	
	// Draw an end-effector
	if (noskip) {
	    if (getNumChildLinks() == 0) {
		double pos[3], endeffector[3];
		getPosition(pos);
		getEndEffectorWC(endeffector);
		glLineWidth(2.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1,0x00ff);
		glColor3f(1.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex3dv(pos);
		glVertex3dv(endeffector);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glLineWidth(1.0);
	    }
	}
	
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glPointSize(10.0);
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_POINTS);
	glVertex3dv(pos);
	glEnd();
	glDepthFunc(GL_LESS); // Default
	
    }
    
    glPopAttrib();
}

// calcBoundingBox:
//	Calculates bounding box	in world coordinates.
//
BoundingBox *Link::calcBoundingBox(BoundingBox *b)
{
    if(	m_Geom != NULL )
    {
	// Take	geometry bounding box.
	m_Geom->calcBoundingBox(b) ;
	
	if (geomFix)
	    b->scale(geomScale[0],geomScale[1],geomScale[2]);
	
	// Now we must adjust it via the m_transMat matrix.
	b->update(m_transMat);
	
	return b ;
    }
    else {
	double pos[3];
	memcpy(pos,m_transMat[3],3*sizeof(double));
	b->xMin	= pos[0]; b->xMax = pos[0];
	b->yMin	= pos[1]; b->yMax = pos[1];
	b->zMin	= pos[2]; b->zMax = pos[2];
	if (endEffector[0] < b->xMin) b->xMin =	endEffector[0];
	if (endEffector[1] < b->yMin) b->yMin =	endEffector[1];
	if (endEffector[2] < b->zMin) b->zMin =	endEffector[2];
	if (endEffector[0] > b->xMax) b->xMax =	endEffector[0];
	if (endEffector[1] > b->yMax) b->yMax =	endEffector[1];
	if (endEffector[2] > b->zMax) b->zMax =	endEffector[2];
	return b;
    }
}

void Link::displayBoundingBox(float r, float g,	float b, float a)
{
    calcBoundingBox(&boundingBox);
    boundingBox.display(r,g,b,a);
}


void Link::setPosition(double p[3])
{
    memcpy(m_transMat[3],p,3*sizeof(double));
    invSmart4(m_invTransMat,m_transMat) ;
}

// Retrieves a list of all children of this link.
int Link::getChildren(Tcl_Interp *interp)
{
	Link **wlink = getChildLinks();
	if (wlink) {
		for (int i =0; i < getNumChildLinks(); i++)
			Tcl_AppendElement(interp,wlink[i]->getName());
	}
	return TCL_OK;
}

void Link::getPosition(double p[3])
{
    memcpy(p,m_transMat[3],3*sizeof(double));
}

void Link::getAxes(double x[3],	double y[3], double z[3])
{
    for	(int i=0; i < 3; i++) {
	 x[i] =	m_transMat[i][0];
	 y[i] =	m_transMat[i][1];
	 z[i] =	m_transMat[i][2];
    }
}

void Link::getEndEffectorWC(double p[3])
{

    double p4[4]; memcpy(p4,endEffector,3*sizeof(double));p4[3]	= 1.0;
    double p4_t[4];
    double tm[4][4];

    if (ao->areLinksRelativeToParent() != TRUE )
	multArray(&p4_t[0],&p4[0],&m_transMat[0][0],1,4,4) ;
    else
    {
	// compute the transf matrix that transforms points form the
	// local cs to the world cs
	getWTransMat(tm) ;
	multArray(&p4_t[0],&p4[0],&tm[0][0],1,4,4);
    }

    // Assumes homogeneous point w is 1.0
    memcpy(p,p4_t,3*sizeof(double));

}

void Link::setEndEffectorWC(double p[3])
{
	getLocalCoord(endEffector,p);
}

void Link::getTransMat(double m[4][4])
{
    for( int i = 0 ; i < 4 ; i++ )
	for( int j = 0 ; j < 4 ; j++ )
	    m[i][j] = m_transMat[i][j] ;
}


void Link::getInvTransMat(double m[4][4])
{
    for( int i = 0 ; i < 4 ; i++ )
	for( int j = 0 ; j < 4 ; j++ )
	    m[i][j] = m_invTransMat[i][j]	;
}

// PROC: getWTransMat()
// It calculates the transformation matrix that	transforms
// points form the link	cs to the world	cs.
// Works both when the links are and are  not considered relative to their parents.
void Link::getWTransMat(double tm[4][4])
{
    Link *pl ;
    double tm1[4][4] ;
    int	flip = 0 ;

    D2ArrayCopy(4,4,&tm[0][0], &m_transMat[0][0])	;


    if(	ao->areLinksRelativeToParent() == TRUE )
    {
	pl = getParentLink() ;
	while( pl != NULL )
	{
	    if(	flip ==	0)
	    {
		multArray(&tm1[0][0],&tm[0][0],&pl->m_transMat[0][0],4,4,4) ;
		flip = 1 ;
	    }
	    else
	    {
		multArray(&tm[0][0],&tm1[0][0],&pl->m_transMat[0][0],4,4,4) ;
		flip = 0 ;
	    }
	    pl = pl->getParentLink() ;
	}
	if( flip == 1)
	    D2ArrayCopy(4,4,&tm[0][0], &tm1[0][0]) ;
    }
}

void Link::getWTransMat(float tm[4][4])
{
	double t[4][4];
	getWTransMat(t);
	for (int i=0; i	< 4; i++)
	    for	(int j=0; j < 4; j++)
		 tm[i][j] = (float)t[i][j];
}

void Link::getOrientation(float	tm[4][4])
{
    double mat[4][4];
    getWTransMat(mat);
    // Remove translational component.
    mat[3][0] =	mat[3][1] = mat[3][2] =	0.0; mat[3][3] = 1.0;

    // Transfer	to a float.
    for	(int i=0; i < 4; i++)
	for (int j=0; j	< 4; j++)
	     tm[i][j] =	(float)mat[i][j];
}

void Link::getOrientation(double tm[4][4])
{
    getWTransMat(tm);
    // Remove translational component.
    tm[3][0] = tm[3][1]	= tm[3][2] = 0.0; tm[3][3] = 1.0;
}

void Link::getRotation(double tm[3][3])
{
    double mat[4][4];
    getWTransMat(mat);
    // Move to 3x3 matrix.
    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		tm[i][j] = mat[i][j];
}

void Link::setOrientation(int naxis, double v[3])
{
    double t[3];

    if (naxis >	2)
    {
	danceTcl::OutputMessage("setOrientation:	index out of bounds.\n") ;
	return;
    }
    VecCopy(t,v) ;
    VecNormalize(t) ;
    memcpy(m_transMat[naxis],t,3*sizeof(double));
}

void Link::getCoordSystem(CoordSystem *cs)
{
    memcpy(cs->x,m_transMat[0],3*sizeof(double));
    memcpy(cs->y,m_transMat[1],3*sizeof(double));
    memcpy(cs->z,m_transMat[2],3*sizeof(double));
    memcpy(cs->origin,m_transMat[3],3*sizeof(double));
}

void Link::setTransMat(double tm[4][4])
{
    int	i,j ;

    for( i = 0 ; i < 4 ; i++ )
	for( j = 0 ; j < 4 ; j++ )
	    m_transMat[i][j] = tm[i][j] ;
    /* calculate inverse too */
    invSmart4(m_invTransMat,m_transMat) ;
}

void Link::setTransMat(CoordSystem cs)
{
    memcpy(m_transMat[0],cs.x,3*sizeof(double));
    memcpy(m_transMat[1],cs.y,3*sizeof(double));
    memcpy(m_transMat[2],cs.z,3*sizeof(double));
    memcpy(m_transMat[3],cs.origin,3*sizeof(double));

    // calculate inverse too
    invSmart4(m_invTransMat,m_transMat) ;
}

void Link::setOrientation(double tm[4][4])
{
    int	i,j ;
    // ignore the translational	component
    for( i = 0 ; i < 3 ; i++ )
	for( j = 0 ; j < 3 ; j++ )
	    m_transMat[i][j] = tm[i][j] ;
}

// display a link hierarchy in which each link is considered
// relative to each parent link
void Link::displayTree()
{
    int	i ;

    glPushMatrix() ;		// the transformation matrix is	relative to
				// the previous	link
    glMultMatrixd(&m_transMat[0][0]) ;
    Display()	;

    for( i = 0 ; i < m_numChildLinks ; i++ )
    {
	 childLink[i]->displayTree() ;
     }

    glPopMatrix() ;
    return ;
}

// changeToLocal:
//	Recursively descends link and its children and changes transformation matrices to be
//	relative to its parent.
void Link::changeToLocal()
{
    double tm[4][4] ;
    int	i ;

    for(i = 0 ;	i < m_numChildLinks ; i++)
	childLink[i]->changeToLocal() ;

    if(	parentLink != NULL )
    {
		// WC =	WP*PC -> PC = WP^(-1)*WC and all of this
		// transpose so	the other way around
		multArray(&tm[0][0],&m_transMat[0][0],&parentLink->m_invTransMat[0][0],4,4,4) ;

		// CAUTION: it has to be after so that the WP are valid
		// through out the whole recursion
		D2ArrayCopy(4,4,&m_transMat[0][0],&tm[0][0]) ;
		// calculate the inverse too
		invSmart4(m_invTransMat,m_transMat)	;
    }
}


// changeToGlobal:
//	Recursively descends link and its children and flattens the hierarchy so each link
//	has the stored global transformation matrix relative to the world.
void Link::changeToGlobal()
{
    double tm[4][4] ;
    int	i ;

    if(parentLink != NULL)
    {
		// WC =	WP*PC and after	transposition WC = PC*WP
		multArray(&tm[0][0],&m_transMat[0][0],&parentLink->m_transMat[0][0],4,4,4) ;
	
		// it has to be	right away, because it has to propagate
		// right away for the children
		D2ArrayCopy(4,4,&m_transMat[0][0],&tm[0][0]) ;
		invSmart4(m_invTransMat,m_transMat)	;
	}
	
	// Update VCOLLIDE objects for collision detection calculations.
	if (m_VCollideID != -1 && ao->m_CheckCollisions) {
			double fixed_transp[4][4];
			transpArray(&fixed_transp[0][0],&m_transMat[0][0],4,4);
			if( geomFix == 1 )
			{
			    fixed_transp[0][0] *= geomScale[0] ;
			    fixed_transp[1][1] *= geomScale[1] ;
			    fixed_transp[2][2] *= geomScale[2] ;
			}
			    
			m_VCollideEngine->UpdateTrans(m_VCollideID, fixed_transp);
	}
	// Initialize collision check to false, so we can identify later the links in
	// collision.
	m_InCollision = FALSE;

    for(i = 0 ;	i < m_numChildLinks ; i++)
		childLink[i]->changeToGlobal() ;
}

void Link::getPoint(int	index, int modifier, double *point)
{
	double wpoint[3];
	switch(index) {
	   case	0:
		getPosition(wpoint);
	   break;
	   case	1:
		getEndEffectorWC(wpoint);
	   break;
	}
	memcpy(point,wpoint,3*sizeof(double));
}

// getLocalCoord:
//	Transforms a world point to local point
void Link::getLocalCoord(double	local[3], double world[3])
{
	double cm[3];
	getPosition(cm);
	VecSubtract(local,world,cm);
	rotPoint_mat4(local,m_invTransMat);
}

// getWorldCoord:
// Transforms a local point to its world point.
// The world and local can be the same pointer
void Link::getWorldCoord(double world[3], double local[3])
{
    if( ao->isSimul != TRUE )
    {
	double tm[4][4] ;
	VecCopy(world, local) ;
	getWTransMat(tm) ;
	transformPoint_mat(world,tm) ;
    }
    else
    {
	// Use the simulator to get the position information. Potentially more accurate.
	ao->simulator->GetPosition(m_linkNumber, local, world) ;
    }
}

// getWorldNormal:
//	Transforms the local normal to its orientation wrt world frame.
void Link::getWorldNormal(double world[3], double local[3])
{
    double tm[4][4] ;
    getWTransMat(tm) ;
    for (int i = 0; i < 3; i++)
	world[i] = local[0]*tm[0][i] +
	  local[1]*tm[1][i] +
	  local[2]*tm[2][i];
}

int Link::Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{
    // check if	the arguments are valid
    if(	argc < 1)
    {
	danceTcl::OutputMessage("ERROR: Expected a command \n") ;
	return TCL_ERROR ;
    }
    
    // parse the different commands
    int count = 0;
    
    // for compatability, "set" keyword no longer needed.
    if (strcmp(argv[count],"set") == 0) count = 1;
    
    if( (count == 1) && (argc == 1) )
    {
	danceTcl::OutputMessage("set what?\n") ;
	return TCL_ERROR ;
    }
    // Assigns geometry instance to link.
    if( strcmp(argv[count], "geometry")	== 0 ) {
	if (argc-1-count == 1) {
	    return replaceGeometry(interp, argc - count-1, &argv[count+1]);
	} else {
	    if (m_Geom) 
		danceTcl::OutputResult("%s", m_Geom->getName());
	}
    }
    // Returns the list of immediate children of this link.
    else if (strcmp(argv[count], "children") == 0)
    {
    	if (argc-1 != count)
	{
	    danceTcl::OutputMessage("ERROR: children accepts no extra arguments.");
	    return TCL_ERROR;
	}
	return getChildren(interp);
    }
    else if (strcmp(argv[count],"collideID") == 0)
    {
	danceTcl::OutputResult("ID is %d\n",m_VCollideID);
    }
    else if (strcmp(argv[count],"parentJoint") == 0)
    {
	Joint *joint = getParentJoint();
	assert(joint);
	Tcl_AppendResult(interp,joint->getName(),NULL);
	return TCL_OK;
    }
    else if (strcmp(argv[count],"name") == 0)
    {
        if (argc-count-1 == 0)
            Tcl_AppendResult(interp,getName(),NULL);
        else
            setName(argv[count+1]);
    }
    else if (strcmp(argv[count],"boundingBox") == 0)
    {
	if (argc-1-count != 1)
	{
	    if (m_DisplayBoundingBox == TRUE)
		danceTcl::OutputMessage("on");
	    else 
		danceTcl::OutputMessage("off");
	    return TCL_OK;
	}
	if (strcmp(argv[count+1],"on") == 0)
	    m_DisplayBoundingBox = TRUE;
	else
	    m_DisplayBoundingBox = FALSE;
	if (dance::FocusWindow)
	    dance::FocusWindow->postRedisplay();
	return TCL_OK;
    }
    else if (strcmp(argv[count],"displayGeometry") == 0)
    {
	if (argc-1-count != 1)
	{
	    if (m_DisplayGeometry == TRUE)
		danceTcl::OutputResult("on");
	    else 
		danceTcl::OutputResult("off");
	    return TCL_OK;
	}
	if (strcmp(argv[count+1],"on") == 0)
	    m_DisplayGeometry = TRUE;
	else
	    m_DisplayGeometry = FALSE;
	if (dance::FocusWindow)
	    dance::FocusWindow->postRedisplay();
	return TCL_OK;
    }
    else if (strcmp(argv[count],"normals") == 0)
    {
	if (argc-1-count != 1)
	{
	    if (m_DisplayNormals == TRUE)
		danceTcl::OutputMessage("on");
	    else 
		danceTcl::OutputMessage("off");
	    return TCL_OK;
	}
	if (strcmp(argv[count+1],"on") == 0)
	    m_DisplayNormals = TRUE;
	else
	    m_DisplayNormals = FALSE;
	
	if (dance::FocusWindow)
	    dance::FocusWindow->postRedisplay();
	return TCL_OK;
    }
    else if (strcmp(argv[count],"axes") == 0)
    {
	if (argc-1-count != 1)
	{
	    if (m_DisplayAxes == TRUE)
		danceTcl::OutputMessage("on");
	    else 
		danceTcl::OutputMessage("off");
	    return TCL_OK;
	}
	if (strcmp(argv[count+1],"on") == 0)
	    m_DisplayAxes = TRUE;
	else
	    m_DisplayAxes = FALSE;
	
	if (dance::FocusWindow)
	    dance::FocusWindow->postRedisplay();
	return TCL_OK;
    }
    else if (strcmp(argv[count],"resetInbAndOutb") == 0)
    {
	if (argc-1-count == 1) { // check flip
	    if (strcmp(argv[count+1],"flip") == 0) 
		resetInbAndOutb(1);
	}
	else
	    resetInbAndOutb();
	if (dance::FocusWindow)
	    dance::FocusWindow->postRedisplay();
	return TCL_OK;
    }
    else if( strcmp(argv[count], "toworld") == 0 )
    {
	if( argc-1-count == 3)
	{
	    Vector local ;
	    local[0] = atof(argv[count+1]) ;
	    local[1] = atof(argv[count+2]) ;
	    local[2] = atof(argv[count+3]) ;
	    Vector wpoint ;
	    getWorldCoord(wpoint, local) ;
	    danceTcl::OutputListElement("%lf", wpoint[0]) ;
	    danceTcl::OutputListElement("%lf", wpoint[1]) ;
	    danceTcl::OutputListElement("%lf", wpoint[2]) ;
	}
	else
	{
	    danceTcl::OutputResult("toworld: needs x y z") ;
	    return TCL_ERROR ;
	}
    }
    else if (strcmp(argv[count],"transparency") == 0) 
    {
	if (argc-1-count != 1) 
	    danceTcl::OutputResult("%f",m_Transparency);
	else {
	    m_Transparency = (float)atof(argv[count+1]);
	    if (dance::FocusWindow)
		dance::FocusWindow->postRedisplay();
	}
	return TCL_OK;
    }
    else if (strcmp(argv[count],"mass") == 0) 
    {
	if (argc-1-count != 1)
	    danceTcl::OutputResult("%f",m_Mass);
	else 
	    m_Mass = atof(argv[count+1]);
	return TCL_OK;
    }
    else if (strcmp(argv[count],"moments") == 0) 
    {
	if (argc-1-count != 3) {
	    danceTcl::OutputListElement("%f",m_InerTensor[0][0]);
	    danceTcl::OutputListElement("%f",m_InerTensor[1][1]);
	    danceTcl::OutputListElement("%f",m_InerTensor[2][2]);
	}
	else {
	    double moments[3];
	    moments[0] = atof(argv[count+1]);
	    moments[1] = atof(argv[count+2]);
	    moments[2] = atof(argv[count+3]);
	    setMoments(moments);
	}
	return TCL_OK;
    }
    // Scales the geometry in this link.
    else if( strcmp(argv[count], "scale") == 0 )
    {
	if( m_Geom == NULL )
	{
	    danceTcl::OutputMessage("WARNING: no geometry present.\n") ;
	    return TCL_OK ;
	}
	double scaleX, scaleY, scaleZ ;
	int center = 0 ;
	if( (argc-1-count > 0 ) && (argc-1-count < 3)  )
	{
	    double sc = atof(argv[count+1]);
	    scaleX = sc ;
	    scaleY = sc ;
	    scaleZ = sc ;

	    if( argc-1-count  == 2 ) center = atoi(argv[count+2]) ;
	}
	else if( (argc-1-count > 2 ) && (argc-1-count < 5) )
	{
	    scaleX = atof(argv[count+1]);
	    scaleY = atof(argv[count+2]);
	    scaleZ = atof(argv[count+3]);
	    if( argc-1-count == 4 )  center = atoi(argv[count+4]) ;
	}
	else
	{
	    danceTcl::OutputMessage("ERROR: expected \"scale <scale factor>|"
			  "<scale factorX factorY factorZ > [<around_center_flag>]\"\n") ;
	    return TCL_ERROR ;
	}
	//geomScale[0] = scaleX ;
	//geomScale[1] = scaleY ;
	//geomScale[2] = scaleZ ;
	//geomFix = TRUE ;
	m_Geom->Scale(scaleX, scaleY, scaleZ, center) ;
    }
    else if( strcmp(argv[count], "translate") == 0 )
    {
	if( m_Geom == NULL )
	{
	    danceTcl::OutputMessage("No geometry present!") ;
	    return TCL_OK ;
	}
	if( argc-1-count != 3)
	{
	    danceTcl::OutputMessage("ERROR: expected \"translate <x y >\"") ;
	    return TCL_ERROR ;
	}
	if( m_Geom == NULL ) 
	{
	    danceTcl::OutputMessage("WARNING: Geometry is NULL.") ;
	    return TCL_OK ;
	}
	double x = atof(argv[count+1]);
	double y = atof(argv[count+2]);
	double z = atof(argv[count+3]);
	m_Geom->Translate(x,y,z) ;
    }
    else if( strcmp(argv[count], "fit") == 0 )
	FitGeometryToLink(argc-1, &argv[1]) ;
    else if( strcmp(argv[count], "center") == 0 )
    {
	if( m_Geom == NULL )
	{
	    danceTcl::OutputMessage("No geometry present!") ;
	    return TCL_OK ;
	}
	m_Geom->Center() ;
    }
    else if( strcmp(argv[count], "assign_monitor_points") == 0 )
	assignMonitorPoints(clientData,	interp,	argc-count-1,	&argv[count+1]) ;
    else if( strcmp(argv[count], "rotate") == 0 )
	rotateGeometry(argc-1, &argv[1]) ;
    else if( strcmp(argv[count], "attach") == 0 )
    {
	AttachGeom() ;
    }
    else if( strcmp(argv[count], "update_monitor_points") == 0 )
	getMonitorPointsFromGeom() ;
    else
	danceTcl::OutputMessage("USAGE: [set] geometry"
	       "|boundingBox [on/off]"
	       "|scale|make_triangle"
	       "|assign_monitor_points"
	       "|update_monitor_points"
	       "|center|rotate|fit|attach")	;
    
    return TCL_OK;
}

// replaceGeometry:
//		Replaces the current pointer to geometry (if any) to point to a new geometry object.
//		Also uses the geometry to create any monitor points.
//
int Link::replaceGeometry(Tcl_Interp *interp, int argc,char **argv)
{
    // First argument should be	name of	geometry.
    m_Geom = (DGeometry *)dance::AllGeometry->get(argv[0]);
    if (m_Geom == NULL) {
	     danceTcl::OutputMessage("ERROR: Could not find geometry with the given name.\n");
	     return TCL_ERROR;
    }

	// Perform setup for collision detection.
    if (m_Geom->m_RAPIDmodel) {
		if (m_VCollideEngine == NULL) m_VCollideEngine = new VCollide;
		m_VCollideEngine->NewObject(&m_VCollideID, m_Geom->m_RAPIDmodel);
		AddGlobalLink(this);
	}

    // calculate monitor points.
    getMonitorPointsFromGeom();

    if(	dance::m_NoDisplay == FALSE )
		dance::AllViews->postRedisplay();

    return TCL_OK;

}

// PROC:   getMonitorPointFromGeom()
// DOES:   allocates space and gets the points from geometry.
//         The point are scaled appropriately by geom scale.
int Link::getMonitorPointsFromGeom(void)
{
	if (m_Geom) {
		Vector *pts;
		int num	= m_Geom->getMonitorPoints(&pts);
		if (num	> 0) {
		    if( m_MonitorPoints.Allocate(num) == 0 )
		    {
			danceTcl::OutputMessage("Link::getMonitorPointsFromGeom: " 
			       "Cannot allocate memory!\n") ;
			return 0 ;
		    }
		    for	(int i = 0; i <	num ; i++) {
			for (int j = 0;	j < 3; j++) {
			    m_MonitorPoints.m_Point[i][j] = geomScale[j]*pts[i][j];
			}
		    }
		    return(m_MonitorPoints.m_NumPoints);
		}
	}
	return(0);
}

int Link::getMonitorPoints(Vector **pts)
{
	if( m_MonitorPoints.m_NumPoints == 0 ) 
		pts = NULL ;
	else
		*pts = m_MonitorPoints.m_Point;
	return m_MonitorPoints.m_NumPoints;
}

int Link::assignMonitorPoints(ClientData clientData, Tcl_Interp	*interp,
				int argc, char **argv)
{
    int	i,j ;
    int	n ;
    Vector *p ;


    if( m_Geom == NULL )
    {
	danceTcl::OutputMessage("WARNING: there is no geometry for link %s.\n",
	       getName()) ;
	return TCL_OK ;
    }
    
    if( argc <= 1 )
    {
	int npoints = 0 ;
	if( argc == 1 )
	{
	    npoints = atoi(argv[0]) ;
	}
	danceTcl::OutputMessage("Creating default monitor points\n") ;
	// make the geometry monitor points
	m_Geom->assignMonitorPoints(npoints) ;
	// get them in the link properly scaled
	getMonitorPointsFromGeom() ;
	return TCL_OK ;
    }
    n =	argc / 3 ;
    if(	n < 1 )	return TCL_OK ;
    p =	(Vector	*) malloc(n*sizeof(Vector)) ;
    for(j = 0, i = 0 ; i < n ; i++, j +=3)
    {
	p[i][0]	= atof(argv[j])	;
	p[i][1]	= atof(argv[j+1]) ;
	p[i][2]	= atof(argv[j+2]) ;
    }

    if(	m_Geom->assignMonitorPoints(n,p) == n )
    {
	danceTcl::OutputMessage("Assigned %d monitor points.\n", n) ;
	getMonitorPointsFromGeom() ;
   	free(p)	;
	return TCL_OK ;
    }
    else
    {
	free(p)	;
	return TCL_ERROR ;
    }
}


void Link::displayMonitorPoints()
{
    int lightOn = glIsEnabled(GL_LIGHTING) ;
    if( lightOn == GL_TRUE) glDisable(GL_LIGHTING) ;

    glColor4f(0.9f,0.0f,0.0f,1.0f-m_Transparency);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < m_MonitorPoints.m_NumPoints; i++) 
   	glVertex3dv(m_MonitorPoints.m_Point[i]);
    glEnd();
    glPointSize(1.0);
    if( lightOn == GL_TRUE) glEnable(GL_LIGHTING) ;
}

// resetInbAndOutb:
//	Takes account of geometry in a link and resets the inboard and outboard
//	(if applicable, otherwise the end effector) to be at the extreme ends of
//  the longest bounding box dimension of the geometry. If there is no geometry,
//  nothing is changed. 
//	
void Link::resetInbAndOutb(int flip)
{
	if (m_Geom == NULL) return;

	BoundingBox box; m_Geom->calcBoundingBox(&box);

	// Find the largest axis
	int largest = 0; double largestVal = box.xMax;
	double otherSide = box.xMin;
	if (box.yMax > largestVal) { 
		largest = 1; largestVal = box.yMax; otherSide = box.yMin;
	}
	if (box.zMax > largestVal) { 
		largest = 2; largestVal = box.zMax; otherSide = box.zMin;
	}

	// Find new world space positions of inboard and outboard joints.
	Joint *jnt = getParentJoint();
	assert(jnt);

	// If the flip flag is on, we reverse the inboard and outboard vectors to 
	if (flip) {
		double temp; temp = largestVal; 
		largestVal = otherSide;
		otherSide = temp;
	}
	
	double bodytojnt[3] = {0.0,0.0,0.0}; bodytojnt[largest] = largestVal;
	jnt->setBodyToJoint(bodytojnt);

	double inbtojnt[3] = {0.0,0.0,0.0}; inbtojnt[largest] = otherSide;
	
	
	if (getNumChildLinks() == 0) {
		// Adjust end-effector.
		setEndEffector(inbtojnt);
		return;
	}

	// Sets the inboard to joint for each child joint.
	Link **childlinks = getChildLinks();
	for (int i = 0; i < getNumChildLinks(); i++) {
		Link *child = childlinks[i];
		Joint *cjnt = child->getParentJoint();
		cjnt->setInbToJoint(inbtojnt);
	}

	// Update new joint configuration in articulated object.
	ao->updateStateConfig(-1);
}

// setMoments:
//		Builds an inertia tensor matrix as a diagonal matrix where the entries are the 
//		given moments of inertia. The products of inertia are zero.
//
void Link::setMoments(double moments[3]) 
{
		m_InerTensorIsDiagonal = 1;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				if (i == j)
					m_InerTensor[i][j] = moments[i];
				else
					m_InerTensor[i][j] = 0.0;
			}
}

void Link::setEndEffector(double pnt [ 3 ])
{
	memcpy(endEffector,pnt,3*sizeof(double));
}


// Adds the given link to the global link list.
void Link::AddGlobalLink(Link *wlink)
{
	assert(m_numGlobalLinks == m_VCollideID);
	
	if (m_numGlobalLinks % BINSIZE == 0) {
		// Allocate more memory.
		Link **newList = (Link **)malloc((m_numGlobalLinks + BINSIZE)*sizeof(Link *));
		if (m_GlobalLinks != NULL)
		{
			memcpy(newList,m_GlobalLinks,m_numGlobalLinks*sizeof(Link *));
			free(m_GlobalLinks);
		}
		m_GlobalLinks = newList;
	}
	m_GlobalLinks[m_numGlobalLinks] = wlink;

	m_numGlobalLinks++;

}

// Returns the Link pointer corresponding to the collision ID.
Link * Link::GetGlobalLink(int collideID)
{
	if (collideID < 0 || collideID > m_numGlobalLinks) return NULL;
	return m_GlobalLinks[collideID];
}

void Link::displayAxes()
{
	glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_LIGHTING);
			double arrowLength = 1.0;
			DView *wview = dance::AllViews->getViewFocus();
			if (wview) {
				double pos[3]; getPosition(pos);		
				double win[3]; wview->getWindowCoords(pos,win);
				double worldwidth = wview->getFrustumWidth(win[2]);
				arrowLength = 0.05*worldwidth;
			}
			GLdrawAxes(arrowLength);
	glPopAttrib();
}

// scales the geometry such that the bounding box of the gometry fits the link size
void Link::FitGeometryToLink(int argc, char **argv)
{
    if( m_Geom == NULL ) return ;

    // center the geometry around its geometric center
    m_Geom->Center() ;
    // get the BoundingBox of the geometry
    BoundingBox b ;
    m_Geom->calcBoundingBox(&b) ;
    // Find the body to joint distance 
    Joint *jnt = getParentJoint();
    assert(jnt);
    Vector bodyToJ ;
    jnt->getBodyToJoint(bodyToJ) ;
    
    // find the direction of the bodyToJ
    Vector axis[3] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
    double max = 0 ;
    int dir ;
    for( int i = 0 ; i < 3 ; i++ )
    {
	double res ;
	if( (res = fabs(VecDotProd(bodyToJ, axis[i]))) > max ) 
	{
	    dir = i ;
	    max = res ;
	}
    }

    Vector endPoint ;
    if( getNumChildLinks() != 0 )
    {
	if( strcmp(getName(), "Hip") == 0 )
	{
	    if( strcmp(childLink[0]->getName(), "Abdomen") == 0 )
		childLink[1]->getParentJoint()->getInbToJoint(endPoint) ;
	    else
		childLink[0]->getParentJoint()->getInbToJoint(endPoint) ;
	}
	else
	    childLink[0]->getParentJoint()->getInbToJoint(endPoint) ;
	// projected on the bodyToJoint direction
    }
    else
	getEndEffector(endPoint) ;
    
    double aMax, aMin ;
    switch (dir)
    {
	case 0: 
	    aMax = b.xMax ;
	    aMin = b.xMin ;
	    break ;
	case 1:
	    aMax = b.yMax ;
	    aMin = b.yMin ;
	    break ;
	case 2:
	    aMax = b.zMax ;
	    aMin = b.zMin ;
	    break ;
	default:
	    danceTcl::OutputMessage("ERROR: cannot determine the direction of body to joint!\n") ;
	    return ;
    }

    // compute the length of the link
    double lengthLink  = fabs(bodyToJ[dir] - endPoint[dir]) ;
    danceTcl::OutputMessage("bodyToJ[%d] = %lf endPoint[%d] = %lf\n", dir, bodyToJ[dir], dir, endPoint[dir]) ;
    double divisor ;
    divisor = (aMax-aMin) ;
    
    double scale = lengthLink / divisor  ;
    geomScale[0] *= scale ;
    geomScale[1] *= scale ;
    geomScale[2] *= scale ;
    geomFix = 1;

    danceTcl::OutputMessage("Scale %lf\n", scale) ;
    // now move the geometry so that its middle
    // is in the middle of the link which is not neccessarily the
    // origin of the local coordinate system
    // Currently the geometric center of the geometry is 0,0,0 in local coordinates
    // which is not the middle of the geometry
    
    // the new bounding box is

    Vector middle ;
    setVector(middle, 0.0, 0.0, 0.0) ;
    // do not scale the aMax and aMin because the 
    // scale params are stored out of the vertices.
    // We still have the old value of the vertices.
    middle[dir] = -0.5*(aMax + aMin) ;
    m_Geom->Translate(middle[0], middle[1], middle[2]) ;

    danceTcl::OutputMessage("middle: %lf %lf %lf\n", middle[0], middle[1], middle[2]) ;
    getMonitorPointsFromGeom(); // Recalculate monitor points.
}

void Link::WriteBVHFile(FILE *fp, int depth)
{
	char prfx[MAX_LINE] = "" ;
	
	if( parentJoint == NULL )
	{
		danceTcl::OutputMessage("ERROR: WriteBVHFile: link without a parent joint!\n") ;
		return ;
	}


	int i ;
	for( i = 1 ; i < depth ; i++ )
		strcat(prfx, "\t") ;

	if( depth == 1 )
	{
		fprintf(fp, "HIERARCHY\n") ;
		fprintf(fp, "ROOT %s\n", getName()) ;
	}
	else
	{
		fprintf(fp, "%sJOINT %s\n", prfx, getName()) ;
	}
	fprintf(fp, "%s{\n", prfx) ;

	// print the parameters of this link which are actually stored in the parent
	// joint. 
	parentJoint->WriteBVHFile(fp, depth) ;
	
	if( m_numChildLinks == 0 )
	{
		fprintf(fp, "%s\tEnd Site\n", prfx) ;
		fprintf(fp, "%s\t{\n", prfx) ;
		fprintf(fp, "%s\t\tOFFSET %lf %lf %lf\n", prfx, endEffector[0], 
			endEffector[1], endEffector[2]) ;
		fprintf(fp, "%s\t}\n", prfx) ;
	}			
	// write the children 
	for( i = 0 ; i < m_numChildLinks ; i++ )
		childLink[i]->WriteBVHFile(fp, depth+1) ;

	fprintf(fp, "%s}\n", prfx) ;
	return ;
}

int Link::rotateGeometry(int argc, char **argv)
{
    if( (argc != 2 ) && (argc != 3))
    {
	danceTcl::OutputMessage("ERROR: Link::rotateGeometry: usage: 'rotate x|y|z degrees [<around center flag>]'.\n") ;
	return TCL_ERROR ;
    }
    
    if( m_Geom == NULL )
    {
	danceTcl::OutputMessage("ERROR: Link::rotateGeometry: no geometry present.\n") ;
	return TCL_ERROR ;
    }
    
    int center ;
    if( argc == 3 ) center = atoi(argv[2]) ;
    // if center is 1 then the rotation happens around the 
    // the center of the bounding box of the geometry
    // otherwise around the current origin (default)
    m_Geom->Rotate(argv[0], atof(argv[1]), center) ;

    getMonitorPointsFromGeom();
    return TCL_OK ;
}

void Link::getWorldVelocity(double worldvel[3], double local[3])
{
    if (ao->isSimul) {
	// Get velocity from SD/FAST calls.
	ao->simulator->GetVel(m_linkNumber,local,worldvel);
    }
    else { // Assume static conditions and return zero velocity.
		worldvel[0] = worldvel[1] = worldvel[2] = 0.0;
    }
}

// PROC:   AttachGeom()
// DOES:   Transforms the geometry from world coordinates
//         to link coordinates.
void Link::AttachGeom(void)
{
    if( m_Geom == NULL ) return ;

    // get the origin of the link in world coordinates
    Vector p ;
    getPosition(p) ;
   
    m_Geom->SetOrigin(p) ;
}

void Link::Highlight(float r, float g, float b, float a)
{
	double point[3];
	getEndEffectorWC(point);
	glPointSize(15.0);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glColor4f(r,g,b,a);
	glBegin(GL_POINTS);
	glVertex3dv(point);
	glEnd();
	glPointSize(1.0);
	
	glPopAttrib();
}

void Link::RemoveChildJoint(Joint *wjoint)
{
	if (wjoint == NULL) return;

	// Find wjoint amongst children joints.
	int n = getNumChildLinks();

	int found = -1;
	for (int i = 0; i < n; i++) {
		if (childLink[i]->parentJoint == wjoint) {
			found = i;
			break;
		}
	}

	
	if (found == -1) return; // Not found among links.

	// Now shift all the links over. No need to shift if entry is last in list.
	if (found < n-1)
		memcpy(&childLink[found],&childLink[found+1],sizeof(Link *)*(n-1-found));
	m_numChildLinks--;

}

// Remove from Global link list.
void Link::RemoveGlobalLink(Link *wlink)
{
	// Find link within global links.
	int found = -1;
	for (int i = 0 ; i < m_numGlobalLinks; i++)
		if (m_GlobalLinks[i] == wlink) {
			found = i;
			break;
		}

	if (found == -1) return;
	if (found < m_numGlobalLinks-1)
			memcpy(&m_GlobalLinks[found],&m_GlobalLinks[found+1],sizeof(Link *)*(m_numGlobalLinks-1-found));

	m_numGlobalLinks--;
}

void Link::DeleteChildren()
{
	for (int i = 0; i < m_numChildLinks; i++)
		delete childLink[i];
	m_numChildLinks = 0;
}

// uses the simulator instead of the links structure
void Link::getLocalCoordSim(double local[3], double world[3])
{
        Vector cmlocal = {0.0, 0.0, 0.0}, cm ;
        getAo()->simulator->GetPosition(m_linkNumber, cmlocal, cm) ;
        VecSubtract(local, world, cm) ;

	// WORLDFRAME defined in DSimulator.h
        getAo()->simulator->GetOrientation(WORLDFRAME, local, m_linkNumber, local) ;
}

//  void Link::setPrevWTransMat(void)
//  {
//      getWTransMat(m_prevWTransMat) ;
//  }

//  // returns the prev position of a local point in world coordinates    
// void Link::getWPrevPos(Vector pointLocal, Vector prevPos)
//  {
//      VecCopy(prevPos, pointLocal) ;
//      transformPoint_mat(pointLocal, m_prevWTransMat) ;
//  }

// Returns the proper transformatin matrix for the geometry
// cause the geometry may be separate scaled using geomScale
void Link::getWTransMatGeom(double transMat[4][4])
{
    getWTransMat(transMat) ;
    if( geomFix == 1) 
    {
	transMat[0][0] *= geomScale[0] ;
	transMat[1][1] *= geomScale[1] ;
	transMat[2][2] *= geomScale[2] ;
    }
}
    
void Link::GetRapidTriangle(int n, Vector v1, Vector v2, Vector v3)
{
    m_Geom->GetRapidTriangle(n, v1, v2, v3) ;
    if( geomFix )
    {
	v1[0] *= geomScale[0] ;
	v2[0] *= geomScale[0] ;
	v3[0] *= geomScale[0] ;

	v1[1] *= geomScale[1] ;
	v2[1] *= geomScale[1] ;
	v3[1] *= geomScale[1] ;

	v1[2] *= geomScale[2] ;
	v2[2] *= geomScale[2] ;
	v3[2] *= geomScale[2] ;
    }
} 
