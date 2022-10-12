
/***************************************************************************
	----------------------------------------------
	ORIGINAL AUTHOR: Gordon Cook
	-----------------------------------------------
		gcook@dgp.toronto.edu
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
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLutilities.h"
#include <GL/glutShared.h>
#include <GL/glutShared.h>
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "ViewManager.h"
#include "DView.h"

#include "IKActuatorForce.h"
#include "list.h"
#include "IKassembler.h"
#include "IKconstraint.h"
#include "posConstraint.h"
#include "orientConstraint.h"
#include "DOFrecord.h"
#include "IKdata.h"
#include "ArticulatedObject.h"
#include "DSimulator.h"


#define IKDISPLAYLINKS 0
#define IKDISPLAYNORMAL 1
#define IKDISPLAYACTIVEONLY 2

enum Actuator_mode{
	changeRoot_mode,
	newConstraint_mode,
        default_mode,//default mode, joints can be picked, or another constraint picked
        editCon_mode
};

enum newConstraintType{
  position,
  orientation
};


/** Returns the controllable degrees of freedom */
static int CalcControlNdof(ArticulatedObject *ao) ;


IKActuatorForce::IKActuatorForce()
{
    m_artObj = NULL ;
    activeJoint = NULL ;
    root = NULL ;
    recs = NULL ;
    activeConstraint = NULL ;
    newConstraintType = position;
    m_usePG = FALSE ;
    m_isSimInit = FALSE ;
    m_solveContSim = FALSE ;
    m_needsSolving = FALSE ;
}

IKActuatorForce::IKActuatorForce(ArticulatedObject *a) 
{
   m_artObj = a; assembler = new IKassembler; recs = new list; numConstraints = 0; activeConstraint = NULL;
   Actuator_mode = changeRoot_mode; activeJoint = NULL; 
   root = NULL ;
   solveMode = 0;
   //link the graphics size
   m_graphicsRad = 0.03;
   //char *varName;
   //sprintf(varName,"graphicsRad%s", getName()) ;
   //if ( Tcl_LinkVar(interpreter,varName, (char *) &m_graphicsRad,TCL_LINK_DOUBLE) == TCL_ERROR){
   //danceTcl::OutputMessage("Cannot link variable %s", varName) ;

   //}

   // added by petros
   m_solveContSim = FALSE ;
   m_needsSolving = FALSE ;
   for( int i = 0 ; i < MAXDIM ; i++ )
   {
       m_q_prev[i] = m_q[i] = 0 ;
       m_ks_prev[i] = m_ks[i] = 5.0 ;
       m_kd_prev[i] = m_kd[i] = 1.5 ;
   }
   m_usePG = FALSE ;
   m_isSimInit = FALSE ;
   if(!a->joint[0]){danceTcl::OutputMessage("IKActuatorForce: trouble with base joint in the ArticulatedObject");
       return;
   }
   a->joint[0]->getInbToJoint(originalJointPos);
   
   
}
IKActuatorForce::~IKActuatorForce()
{
  delete assembler;
  delete recs;
  if( interpreter != NULL )
    unLinkVariables(interpreter) ;
  // Cannot inlink variables cause m_artObj may get deleted before the actuator upon exit
  //UnlinkVariables(m_artObj) ;
}

PlugIn *Proxy(void){ return (new IKActuatorForce); }
PlugIn *IKActuatorForce::create(Tcl_Interp *interp, int argc, char **argv)
{
 if( argc != 1  )

    {
	danceTcl::OutputMessage("usage: instance IKActuatorForce "
				"<actuator name> <articulated object name>") ;
	return NULL ;
    }
    
    ArticulatedObject *ao = (ArticulatedObject *) dance::AllSystems->get(argv[0]) ;
    if( ao == NULL ) 
    {
	danceTcl::OutputMessage("No such object: %s", argv[0]) ;
	return NULL ;
    }
    IKActuatorForce *f = new IKActuatorForce(ao) ;

    if(	f == NULL )
    {
	danceTcl::OutputMessage("Cannot allocate memory!\n") ;
	return NULL ;
    }
    f->interpreter = interp;
    return f ;
 
}

/**
 */
int IKActuatorForce::commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{ 
    char *usage = "usage: \n"
      "\tresetPos\n"
      "\treset\n"
      "\tndof\n"
      "\tsetJointState\n"
      "\tloadPG <file_name>\n"
      "\tsavePG <file_name>\n"
      "\tsavePose\n"
      "\tsystemName"
      "\tresetVariable"
      "\tprint\n"
      "\taddConstraint\n"
      "\taremoveConstraint\n"
      "\twhatever\n"
      "\tsolveMode\n"
      "\tsolve\n"
      "\tusePG on/off\n"
      "\tsavePoise\n"
      "\tloadPG <file name>\n"
      "\tsavePG\n"
      "\tresetPG\n" ;
    
    if( strcmp(argv[0], "setup") == 0) {
	setup();
    }
    else if( strcmp(argv[0], "print") == 0) {
	double pos[3];
	
	m_artObj->joint[0]->getPosition(pos);
	danceTcl::OutputMessage("root joint  position %lf %lf %lf",pos[0],pos[1],pos[2]);
	danceTcl::OutputMessage("root joint state");
	int i;
	for(i=0; i<6; i++){
	    danceTcl::OutputMessage("%lf", m_artObj->joint[0]->getState(i));
	}
	m_artObj->joint[0]->getInbToJoint(pos);
	danceTcl::OutputMessage("root  inb to joint %lf %lf %lf",pos[0],pos[1],pos[2]);
	m_artObj->joint[0]->getBodyToJoint(pos);
	danceTcl::OutputMessage("root  body to joint %lf %lf %lf",pos[0],pos[1],pos[2]);
	m_artObj->changeToGlobal();		        
    }
    else if( strcmp(argv[0], "solve") == 0) {
	assembler->solve(solveMode);
	updateJoints();
    }  
    else if( strcmp(argv[0], "reset") == 0){
	reset();
    }
    else if( strcmp(argv[0], "addConstraint") == 0){
	int error = FALSE;
	if(root != NULL){
	    if(argc > 1){
		if( strcmp(argv[1], "position") ==0){ 
		    Actuator_mode = newConstraint_mode;
		    int errorFlag = FALSE;
		    newConstraintType = position;
		}
		else if( strcmp(argv[1], "orientation") ==0){
		    Actuator_mode = newConstraint_mode;
		    int errorFlag = FALSE;
		    newConstraintType = orientation;
		}
		else{error = TRUE;}
	    }
	    else{error = TRUE;}
	    if(error == TRUE){danceTcl::OutputMessage("'orientation' or 'position' must be specified");}
	}
	else{
	    danceTcl::OutputMessage("there must be a root link chosen before");
	    danceTcl::OutputMessage("constraints are added");
	}
	if ( error != TRUE )
	{
		dance::SetMode("actuator") ;
		danceTcl::OutputMessage("Switching to actuator more") ;
	}

    }
    else if( strcmp(argv[0], "solveMode")==0){
	solveMode ++;
	if( solveMode > 1) solveMode = 0;
    }
    else if( strcmp(argv[0], "whatever") == 0) {
	/*if(activeConstraint != NULL){
	  double ax[3]; double g[3]; double vec[3];
	  activeConstraint->endEffector->getAxis(vec);
	  activeConstraint->endEffector->rotateToGlobal(ax,vec);
	  activeConstraint->getGoal(g);
	  danceTcl::OutputMessage("axis %lf %lf %lf",ax[0],ax[1],ax[2]);
	  danceTcl::OutputMessage("goal %lf %lf %lf",g[0],g[1],g[2]);
	  }
	*/
	double o;
	IKconstraint *c;
	c = ((IKconstraint *)assembler->allConstraints->first->next);
	storageClass *s= assembler->joints->first->next;
	while(s != assembler->joints->last){
	    o = c->derivative(((IKdata *)s)->joint);
	    danceTcl::OutputMessage("constraint #%i %lf ",c->constraintNumber,o);
	    c = (IKconstraint *)c->next;
	    o = c->derivative(((IKdata *)s)->joint);
	    danceTcl::OutputMessage("constraint #%i %lf",c->constraintNumber,o);
	    c = (IKconstraint *)c->previous;
	    s= s->next;
	}
	
	//storageClass *s;
	s = assembler->allConstraints->first->next;
	double tot = 0;
	while(s != assembler->allConstraints->last){
	    tot += ((IKconstraint *)s)->errorFunction();
	    danceTcl::OutputMessage("constraint # %i error %lf", ((IKconstraint *)s)->constraintNumber,
				    ((IKconstraint *)s)->errorFunction());
	    s=s->next;
	}
	danceTcl::OutputMessage("TotalError %lf", tot);
    }
    else if( strcmp(argv[0], "removeConstraint") == 0) {
	removeActiveConstraint();
    }
    else if( strcmp(argv[0], "resetVariables") == 0) Reset(m_artObj) ;
    else if( strcmp(argv[0], "resetPos") == 0) {
	m_artObj->joint[0]->setInbToJoint(originalJointPos);
	m_artObj->updateStateConfig(-1);
    } 
    else if( strcmp(argv[0], "systemName") == 0)
    {
	if( m_artObj != NULL )
	    danceTcl::OutputResult("%s", m_artObj->getName()) ;
	else
	    danceTcl::OutputResult("%s","") ;
	
    } 
    else if( strcmp(argv[0], "ndof") == 0)
    {
	danceTcl::OutputResult("%d", CalcControlNdof(m_artObj)) ;
    }
    else if( strcmp(argv[0], "setJointState") == 0 )
	SetJointState(argc - 1, &argv[1]) ;
    else if( strcmp(argv[0], "savePG") == 0 )
    {
	if( argc != 2 ) 
	{
	    danceTcl::OutputMessage("expected filename") ;
	}
	else
	{
	    m_pg.Save(argv[1]) ;
	}
    }
    else if( strcmp(argv[0], "loadPG") == 0 )
    {
	if( argc != 2 ) 
	{
	    danceTcl::OutputMessage("expected filename") ;
	}
	else
	{
	    m_pg.Load(argv[1]) ;
	}
    }
    else if( strcmp(argv[0], "usePG") == 0 )
    {
	if( argc != 2 )
	{
	    if( m_usePG == FALSE )
		danceTcl::OutputResult("off") ;
	    else
		danceTcl::OutputResult("on") ;
	}
	else
	{
	    if( strcmp(argv[1], "on") == 0 )
		m_usePG = TRUE ;
	    else
		m_usePG = FALSE ;
	}
    }
    else if ( strcmp(argv[0], "savePose") == 0)
    {
	CtrPrm q[MAXDIM] ;
	Joint **joints = m_artObj->getJoints() ;
	
	int count = 0 ;
	for( int i = 0 ; i < m_artObj->getNumJoints() ; i++ )
	{
	    Joint *joint = joints[i] ;
	    if( joint->getJointType() == J_FREE ) continue ;
	    for( int j = 0 ; j < joint->getStateSize() ; j++ )
	    {
		int indx = m_artObj->simulator->GetIndex(i,j) ;
		q[count].v = m_q[indx] ;
		q[count].ks = m_ks[indx] ;
		q[count].kd = m_kd[indx] ;
		if( m_artObj->isSimul != TRUE )
		    q[count].v = joint->getState(j) ;
		count++ ;
	    }
	}
	 danceTcl::OutputMessage("Using default transition time 0.5 for the new pose.") ;
	 if( m_artObj->IsSimul() == TRUE )
	    m_pg.Add(count, q, 0.5, m_artObj->simulator->GetTime() ) ;
	else
	    m_pg.Add(count, q, 0.5) ;
    }
    else if (strcmp(argv[0], "resetPG") == 0 )
	m_pg.DeletePoses() ;
    
    else{
	danceTcl::OutputMessage("$s", usage) ;
	return TCL_ERROR ;
    }  
    return TCL_OK;
}
/**
 *Displays everything in the IK
 *
 * @param int mode unless mode is LDISPLAY_SELECTION (value 16)
 * @return void
 */
void IKActuatorForce::output(int mode){
	if( mode & LDISPLAY_SELECTION ) 
		display(LDISPLAY_SELECTION) ;
	else
	  display(IKDISPLAYNORMAL);
}


/**
 * Handles a mouse click event
 *
 * Picks links or joints or constraints (depending on Actuator_mode),
 * and updates activeJoint and activeConstraint and/or picks a root.
 * the IK_Joints are also updated at the beginning of the proc
 * @param Event *event  data about of mouse activity
 * @return void
 */
int IKActuatorForce::InteractStart(Event *event)
{ 
  //danceTcl::OutputMessage("interactStart: mode is %i",Actuator_mode);
  updateIKjoints();
  int *item = event->pickItem ;
  double depth = event->Window->getDepth(event->winX,event->winY);
  int numSelected = 0 ;

  handleSelection(event->Window, event->winX, event->winY, event->buttonID,numSelected,item,Actuator_mode) ;
 // danceTcl::OutputMessage("interactStart (after handle selection): mode is %i",Actuator_mode);
  if( numSelected > 0 ){
    
    int pickedItem = item[numSelected-1];
   
    
      switch(Actuator_mode){
      case changeRoot_mode:
	 //find out which link is being picked and set it to the root
         setRoot(m_artObj->link[pickedItem]);
	 if( root == NULL ) danceTcl::OutputMessage("InteractStart::Root is null! Something is wrong.") ;
         Actuator_mode = default_mode;
         break;
      case newConstraint_mode: 
	//danceTcl::OutputMessage("adding constraint");
	 //find out which link is being picked and set add a constraint to for that mode
		  if( m_artObj->link[pickedItem] == root )
		  {
			  danceTcl::OutputMessage ("Root and endeffector cannot coincide.") ;
			  return 0;
		  }
         IKconstraint *con;
         con = addConstraint(m_artObj->link[pickedItem]);
         setActiveConstraint(con);
         Actuator_mode = editCon_mode;
         break;
      case default_mode:
	//find the appropriate constraint or joint and set it to the active constraint
	if(item[0]==1){//constraints
	  
	  storageClass *s = assembler->allConstraints->first->next;
	  setActiveConstraint(NULL);
	  while(activeConstraint == NULL && s != assembler->allConstraints->last){
	    if(((IKconstraint *)s)->constraintNumber == pickedItem){setActiveConstraint((IKconstraint *)s);}
	    s = s->next;
	  }
          Actuator_mode = editCon_mode;
	}
        else if(item[0]==0){//joints
	  
	  storageClass *s = recs->first->next;
          setActiveJoint(NULL);
	  while(s != recs->last){
            if(((DOFrecord *)s)->getJointNumber()== pickedItem){setActiveJoint((DOFrecord *)s);}  
	    s=s->next;
	  }
        }
	break;
    
      } 
  }
  else{
	  if( Actuator_mode != changeRoot_mode )
		Actuator_mode = default_mode; 
	  setActiveConstraint(NULL);
  }
 // danceTcl::OutputMessage("interactStart:(at end of proc) mode is %i",Actuator_mode);
 // if(activeConstraint ==NULL){danceTcl::OutputMessage("activeconstraint is null");}
  return 1 ;
  
}


/**
 *  Handles mouse dragging
 * 
 * Moves the constraint goal of the activeConstraint if appropriate, 
 * and solves new IK problem.  Joints of the m_artObj are updated.
 * @param Event *event: information on mouse activity
 * @return void
 */
void IKActuatorForce::Interact(Event *event){
 
  if(Actuator_mode == editCon_mode && activeConstraint != NULL){
  
    activeConstraint->HandleConstraintEdit(event->Window,event->buttonID,event->winX, event->winY, event->winDiffX, event->winDiffY,
                         event->winWidth, event->winHeight,root);
  }
  
  assembler->solve(solveMode);

  if( m_isSimInit == TRUE )
    updateVariables() ;
  if( m_artObj->isSimul != TRUE )
    updateJoints();
}
/**
 * Cleans up after the actuator is finished with a mouse event
 * 
 * does nothing currently
 * @param void
 * @return int
 */
int IKActuatorForce::InteractEnd(Event *event){

   m_needsSolving = TRUE ; // for use in exertLoad during simulation
   return 1;
}

/**
 * Removes all constraints and IK_Joints
 *
 * removes the IK data structures, but leaves the articulted Object in the same position
 * @param void
 * @retrun void
 */

void IKActuatorForce::reset(void){
    if( assembler ) delete assembler;
     assembler = new IKassembler; 
     if( recs ) delete recs;
     recs = new list; 
     numConstraints = 0; 
     setActiveConstraint(NULL);
     setActiveJoint(NULL);
     root = NULL;
     
  
    
     // set the actuator mode in the one that will set the root
     Actuator_mode = changeRoot_mode ;
     
}
/**  
 * sets the root pointer to r
 *
 * sets the root and updates all necessary data structures.  
 * The root should not be changed without using setRoot.
 * @param Link *r the new root
 * @return void
 */
void IKActuatorForce::setRoot(Link *r){
    if(root != NULL){ 
	reset();
    } 
    root = r;
    DOFrecord *d = new DOFrecord ;
    d->setJointNumber(-1);
    d->numIKjoints = 1;
    recs->add(d);
    IK_Joint *ikJ = new IK_Joint;
    assembler->root = ikJ;
    double vec[3];vec[0]=0.0;vec[1]=0.0;vec[2]=0.0;  
    ikJ->setLocalPosition(vec);
    ikJ->setLimits(0,0);
    ikJ->setVariable(0);
    d->setIKjoint(0,ikJ);
    //danceTcl::OutputMessage("Root added");
    m_artObj->changeToGlobal();
    r->getTransMat(initialRootMat);
    r->getWTransMat(initialWRootMat);
    r->getPosition(initialRootPos);
}

/**
 * used by the findChain procedure
 *
 * @param Link *previousLink  the procedure does not look for chains that go through previous link
 * @param Link *rootLink the starting point of the chain
 * @param Link *endEffector the target of the chain
 * @param list *chain the resulting chain
 * @return void
 */
 

//find out weather a chain exists and if so stores it in a new chain object
//the last element will be -1 if it is the end effector, null if it is not
void IKActuatorForce::findChainBody(Link *previousLink, Link *rootLink, Link *endEffector,list *chain){
      
        if(rootLink == endEffector){
           intStorage *iS = new intStorage ;
           iS->theInt = -2;
           chain->add(iS);
	   //danceTcl::OutputMessage("End Effector found"); 
           return; 
        }
    
        int numLinks = rootLink->getNumChildLinks();
	Link **children;
        children = rootLink->getChildLinks(); 
        list *childChain = NULL;
        int i;
	
     
        
	//danceTcl::OutputMessage("currently at link %i and checking %i children and a parent for end effector",rootLink->getNumber(), numLinks); 
        for( i=0; i < numLinks;  i++){
	    if(children[i] != previousLink){
            
		childChain = new list ;
	    //  danceTcl::OutputMessage("checking child number %i, link number %i", i, children[i]->getNumber());
		findChainBody(rootLink, children[i],endEffector,childChain);
		//danceTcl::OutputMessage("last child on end of childChain is %i", ((intStorage *)childChain->last->previous)->theInt);
		if(((intStorage *)childChain->last->previous)->theInt == -2){//the end effector has been found;
		    //  danceTcl::OutputMessage("end effector found, appending chain");
		    //add a link to the chain indicating the child number 
		    intStorage *iS = new intStorage ;
		    iS->theInt = i;
		    chain->add(iS);
		    chain->merge(childChain);
		    return;
		}                
		else{ if( childChain ) delete childChain; childChain = NULL ; }
	    }  
        }
        if(rootLink->getParentLink() != previousLink && rootLink->getParentLink() != NULL){
	    childChain = new list ;
	    //danceTcl::OutputMessage("checking parent, link number %i", i, rootLink->getParentLink()->getNumber());
	    findChainBody(rootLink, rootLink->getParentLink(),endEffector,childChain);
	    //danceTcl::OutputMessage("last child on end of childChain is %i", ((intStorage *)childChain->last->previous)->theInt);
            if(((intStorage *)childChain->last->previous)->theInt == -2){//the end effector has been found;
		// danceTcl::OutputMessage("end effector found, appending chain");
	        //add a link to the chain indicating the child number -1 in this case 
                intStorage *iS = new intStorage ;
                iS->theInt = -1;
                chain->add(iS);
                chain->merge(childChain);
	        return;
	    }                
            else{if (childChain) delete childChain; childChain = NULL ; }
        }

	//danceTcl::OutputMessage("came to dead end");
        intStorage *iS = new intStorage ;
        iS->theInt = -3;
        chain->add(iS);
}

/**
 * Finds a chain used to link the root and endEffector
 *
 * To the chain is a list of intStorage.  The integers are index numbers for the childLinks arrays 
 * Links.  root->childLink[<ist integer>]->childLink[<2nd integer>]... will eventully get to the
 * endEffector.  If an integer is -1, this means choose the <current link>->getParentLink() pointer.
 * -2 indicates a the end of a successful list, -3 the end of an unsuccessful list.
 * @param Link *endEffector the target of the chain
 * @param list *chain the resulting chain
 * @return void
 */
void IKActuatorForce::findChain(Link *endEffector, list *chain){
     findChainBody(NULL, root, endEffector, chain);
}

/** 
 * Traces through and prints all the links in a chain
 *
 * @param list *chain The chain must be of the format outputed by the findChain procedure
 * @return void
 */
void IKActuatorForce::printOutChain(list *chain){
     danceTcl::OutputMessage("starting at root, link number %i", root->getNumber());
     int i;
     storageClass *s;
     Link *l = root;
     Link **children;
     s = chain->first->next;
     while(((intStorage *)s)->theInt != -2){
        children = l->getChildLinks();
        i = ((intStorage *)s)->theInt;
        assert(i < l->getNumChildLinks() && i > -2);
        if(i >= 0){
           l = children[i];
	   danceTcl::OutputMessage("going through joint %i (type %i) to link number %i", 
                                 l->getParentJoint()->getNumber(),l->getParentJoint()->getJointType(), l->getNumber());
         }  
        else{
	   danceTcl::OutputMessage("going throught joint %i (type %i) to link number%i (reversed)",
            l->getParentJoint()->getNumber(),l->getParentJoint()->getJointType(), l->getParentLink()->getNumber());
          l = l->getParentLink();
        }
        s = s->next;
     }
}

/**
 * Creates all the IK_Joints neccessary to solve the IK for the endEffector
 *
 * Will not duplicate the IK_Joints if some or all of them are already in place.
 * Updates all the neccesarry data structures, but does not create an IKconstraint.
 * @ param Link *endEffector
 * @ return IK_Joint * This IK_Joint corresponds to the endEffector
 */
IK_Joint *IKActuatorForce::createIKjoints(Link *endEffector){
       
    intStorage *iS = NULL;
    DOFrecord *rec = NULL;
    DOFrecord *lastRec = NULL;
    IK_Joint *ikJ = NULL;
    DanceObject *lastJoint = NULL;
    Joint *j = NULL;
    Link *current = NULL;
    Link **childLinks = NULL;

    int ErrorFlag = FALSE;
   
    double zeroVec[3];
    zeroVec[0] = 0;
    zeroVec[1] = 0;
    zeroVec[2] = 0;	
    double utilVec[3];
    double useful[3];


    list *chain = new list ;
    findChain(endEffector,chain);
    if (((intStorage *)chain->last->previous)->theInt != -2){
		danceTcl::OutputMessage("error finding chain"); 
		return NULL;
	} //error has occured, chain is no good;
    //danceTcl::OutputMessage("chain found, theoretical path to endEffector is:");    
    //printOutChain(chain);
    
        
    if(root == NULL){danceTcl::OutputMessage("null root"); return NULL;}
    //then the root has not been added yet root should be added before this routine is called}     
       
    current = root;
    rec = ((DOFrecord *)recs->first->next);
    lastRec = rec; 
    iS = ((intStorage *)chain->first->next);
    childLinks = current->getChildLinks();
   
    m_artObj->changeToGlobal();
    int isRev;
    int lastRev = FALSE;
    lastJoint = root;
    while(iS->theInt != -2){
           if(iS->theInt >= 0){j = childLinks[iS->theInt]->getParentJoint(); isRev = FALSE;}
	   else{j = current->getParentJoint(); isRev = TRUE;}
           //danceTcl::OutputMessage("searching for joint number %i in DOFrecords", j->getNumber());
	   rec = ((DOFrecord *)recs->first->next)->find(j->getNumber());
  
           if(rec == NULL){ 
                 rec = copyJoint(j,isRev,lastRev, lastJoint);
                 ((DOFrecord *)recs->first->next)->add(rec);
                 lastRec->linkTo(rec); 
	   }
           lastJoint = j;
           lastRec = rec;
           lastRev = isRev;
	   if(iS->theInt >= 0){current = childLinks[iS->theInt];}
           else{current = current->getParentLink();}
           childLinks = current->getChildLinks();
           iS = ((intStorage *)iS->next); 
     }
      
     //add an end Effector
     int EEfound = FALSE;
     storageClass *con =  assembler->allConstraints->first->next;   
     
     while(con != assembler->allConstraints->last && EEfound == FALSE){
       //danceTcl::OutputMessage("looking at constraint");
       if(((IKconstraint *)con)->realEndEffector == endEffector){EEfound = TRUE;}
       con = con->next;
     }   
     if(EEfound == FALSE){
       rec = new DOFrecord; 
       ikJ = new IK_Joint;
       rec->setIKjoint(0,ikJ);
       rec->numIKjoints=1;
       assembler->addJoint(ikJ);
       
       iS= ((intStorage *)iS->previous);
       if(iS->theInt >= 0){endEffector->getParentJoint()->getBodyToJoint(utilVec);}
       else{m_artObj->joint[lastRec->getJointNumber()]->getInbToJoint(utilVec);}
       utilVec[0]=-utilVec[0];
       utilVec[1]=-utilVec[1];
       utilVec[2]=-utilVec[2];
       ikJ->setLocalPosition(utilVec);
       ikJ->setLimits(0,0);
       ikJ->setVariable(0.0);   
       ikJ->jointNumber = -2;
       lastRec->linkTo(rec);
       ikJ->rec = NULL;
       delete rec;
       rec = NULL ;
       
       //danceTcl::OutputMessage("end effector joint added");
       ikJ->getGlobalPosition(useful);
       //danceTcl::OutputMessage("   position %lf %lf %lf",useful[0],useful[1],useful[2]);
     }
     else{//danceTcl::OutputMessage("end effector already added in previous constraint");
	 }

     if(ErrorFlag){danceTcl::OutputMessage("Error creating IK chain");}  	
     delete chain;
     chain = NULL ;
     //update the IKjoints to ensure that positions are good
     //otherwise there may be difficuties in the limits  of the reversed IK_Joints
     updateIKjoints();
     if(EEfound == FALSE){return ikJ;}     
     else{return ((IKconstraint *)con->previous)->endEffector;}
  
	 return  NULL ;
}
    
/**
 * Creates a DOFrecord corresponding to j
 *
 * The IK_Joints in the DOFrecord are linked together properly.
 * @param Joint *j the Joint to be copied into IK joints
 * @param int isReversed TRUE if the IK_Joints are linking a child Link to a parent Link, FALSE if vice versa
 * @param int lastJointIsReversed TRUE if the last Joint is reversed FALSE otherwise
 * @param DanceObject *lastJoint The last Joint in the chain, but can also be a Link if the last joint was the root
 * @return DOFrecord * The complete DOFrecord corresponding to j
 */
DOFrecord *IKActuatorForce::copyJoint(Joint *j, int isReversed, int lastJointIsReversed, DanceObject *lastJoint){
  //danceTcl::OutputMessage("copying joint %i", j->getNumber());
      DOFrecord *rec = new DOFrecord;
      rec->setJointNumber(j->getNumber());
      IK_Joint *ikJ;
      double ulim = 0;
      double llim = 0;
      double zeroVec[3];
      zeroVec[0] = 0;
      zeroVec[1] = 0;
      zeroVec[2] = 0;	

      double useful[3];    
      double ax[3][3];

      int ErrorFlag = FALSE;
      
      char *type;
      type = lastJoint->getType();
      //set up position
      if(strcmp(type,"Joint") == 0){
	if( isReversed == FALSE){j->getInbToJoint(m_v1);}
        else{j->getBodyToJoint(m_v1);}
        if(lastJointIsReversed == FALSE){((Joint *)lastJoint)->getBodyToJoint(m_v2);}
	else{((Joint *)lastJoint)->getInbToJoint(m_v2);}
	VecSubtract(m_p,m_v1,m_v2);
      }
      else{
	 if( isReversed == FALSE){
          j->getInbToJoint(m_p);
	 }
	 else{
	  j->getBodyToJoint(m_p);
	 }
      }   
      
      switch(j->m_jointType){
      case J_FREE:
      	 danceTcl::OutputMessage("Free joints are not supported by the IK solver");
	      ErrorFlag = TRUE;
	      break;
      case J_SLIDER:
	      danceTcl::OutputMessage("Slider joints are not supproted by the IKsolver");
	      ErrorFlag = TRUE;
	      break;
      case J_PIN:
	      rec->numIKjoints = 1;
              ikJ = new IK_Joint ;
              j->getLimits(0,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      ikJ->setLocalPosition(m_p);
	      j->getAxis(ax);
	      ikJ->setAxis(ax[0]);
	      ikJ->setVariable(j->getDof(0)*M_PI/180.0);
	      rec->setIKjoint(0,ikJ);
              assembler->addJoint(ikJ);
	      //danceTcl::OutputMessage("Pin joint converted");
	      break;
       case J_UNIVERSAL:
	      rec->numIKjoints = 2;
              //danceTcl::OutputMessage("converting universal joint");	
	      
              ikJ = new IK_Joint ;
	      j->getLimits(1,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      j->getAxis(ax);
	      ikJ->setAxis(ax[1]);
              ikJ->setLocalPosition(zeroVec);
	      ikJ->setVariable(j->getDof(1)*M_PI/180.0);
              rec->setIKjoint(1,ikJ);
              assembler->addJoint(ikJ);
	     
	      //danceTcl::OutputMessage("joint added: info");
	      //danceTcl::OutputMessage("	axis %lf %lf %lf",ax[1][0], ax[1][1], ax[1][2]);
	      //danceTcl::OutputMessage("	variable %lf",ikJ->getVariable());
	      //danceTcl::OutputMessage("       limits %lf to %lf",llim,ulim);
	      //ikJ->getLocalPosition(useful);
	      //danceTcl::OutputMessage("   position %lf %lf %lf",useful[0],useful[1],useful[2]);
       
	      ikJ = new IK_Joint ;
	      j->getLimits(0,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      ikJ->setAxis(ax[0]);
	      ikJ->setLocalPosition(m_p);
	      ikJ->setVariable(j->getDof(0)*M_PI/180.0);
	      rec->setIKjoint(0,ikJ);
	      assembler->addJoint(ikJ);

	      //danceTcl::OutputMessage("joint added: info");
	      //danceTcl::OutputMessage("	axis %lf %lf %lf",ax[0][0], ax[0][1], ax[0][2]);
	      //danceTcl::OutputMessage("	variable %lf",ikJ->getVariable());
	      //danceTcl::OutputMessage("       limits %lf to %lf",llim,ulim);
	      ikJ->getLocalPosition(useful);
	      //danceTcl::OutputMessage("   position %lf %lf %lf",useful[0],useful[1],useful[2]);
	      //danceTcl::OutputMessage("Universal joint converted");
	      break;
      case J_GIMBAL:
	      rec->numIKjoints = 3;
              //danceTcl::OutputMessage("converting gimbal joint");	
	      ikJ = new IK_Joint ;
	      j->getLimits(2,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      j->getAxis(ax);
	      ikJ->setAxis(ax[2]);
              ikJ->setLocalPosition(zeroVec);
	      ikJ->setVariable(j->getDof(2)*M_PI/180.0);
              rec->setIKjoint(2,ikJ);
              assembler->addJoint(ikJ);

              ikJ = new IK_Joint ;
	      j->getLimits(1,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      j->getAxis(ax);
	      ikJ->setAxis(ax[1]);
              ikJ->setLocalPosition(zeroVec);
	      ikJ->setVariable(j->getDof(1)*M_PI/180.0);
              rec->setIKjoint(1,ikJ);
              assembler->addJoint(ikJ);
	     
	      ikJ = new IK_Joint ;
	      j->getLimits(0,&llim,&ulim);
	      ikJ->setLimits(llim*M_PI/180.0,ulim*M_PI/180.0);
	      ikJ->setAxis(ax[0]);
	      ikJ->setLocalPosition(m_p);
	      ikJ->setVariable(j->getDof(0)*M_PI/180.0);
	      rec->setIKjoint(0,ikJ);
	      assembler->addJoint(ikJ);
	      break;
      case J_BALL:
	      danceTcl::OutputMessage("Ball not Supported Yet");
	      ErrorFlag = TRUE;
	      break ;
      }
     
     //clean up
     if(isReversed){rec->reverse();}
     rec->linkJoints(); // also assigns correct number to the IK joints
     //danceTcl::OutputMessage("Joint copying finished");
     return rec;
}


/**
 *Moves the IK_Joints if the m_ArtObj has moved without the knowledge the actuator
 *
 *@param void
 *@retrun void
 */
void IKActuatorForce::updateIKjoints(void){
  //update the position of the root;
 




  if(root != NULL){
    root->getTransMat(initialRootMat);
    root->getPosition(initialRootPos); 
    //move all constraints that are globally positioned
    
    double oldConstraintPos[3];
    double newConstraintPos[3];
    
    storageClass *s = assembler->allConstraints->first->next;
    while(s != assembler->allConstraints->last){
	//   danceTcl::OutputMessage("going through constraints");
      if(((IKconstraint *)s)->isGlobalyPositioned == TRUE){
	//danceTcl::OutputMessage("updating position of constraint # %i",((IKconstraint *)s)->constraintNumber);
	//change to old constraint position to global
	((IKconstraint *)s)->getGoal(oldConstraintPos);
	transformPoint_mat(oldConstraintPos, initialWRootMat) ;
	//change the new constraint position back to local
	root->getLocalCoord(newConstraintPos,oldConstraintPos);
	((IKconstraint *)s)->setGoal(newConstraintPos);
      }
      s = s->next;
    }
    root->getWTransMat(initialWRootMat);
  }
  else 
		return ;  // WHILE DEBUGGING

  int i = 0;
  int ErrorFlag = FALSE;
  Joint *j = NULL;
  storageClass *rec = recs->first->next;
  while(rec != recs->last){
   
    if(((DOFrecord *)rec)->getJointNumber() >= 0){	
      j = m_artObj->joint[((DOFrecord *)rec)->getJointNumber()];
      switch(j->m_jointType){
      case J_FREE:
	danceTcl::OutputMessage("Free joints are not supported by the IK solver");
	ErrorFlag = TRUE;
	break;
      case J_SLIDER:
	danceTcl::OutputMessage("Slider joints are not supproted by the IKsolver");
	ErrorFlag = TRUE;
	break;
      case J_PIN:
	if(((DOFrecord *)rec)->isReversed == FALSE){
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(j->getState(0));
	}
	else{
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(-j->getState(0)); 
	}
	break;
      case J_UNIVERSAL:
	if(((DOFrecord *)rec)->isReversed == FALSE){
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(j->getState(0));
	  ((DOFrecord *)rec)->getIKjoint(1)->setVariable(j->getState(1));
	}
	else{
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(-j->getState(0));
	  ((DOFrecord *)rec)->getIKjoint(1)->setVariable(-j->getState(1));
	    
	}
	break;
      case J_GIMBAL:
	if(((DOFrecord *)rec)->isReversed == FALSE){
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(j->getState(0));
	  ((DOFrecord *)rec)->getIKjoint(1)->setVariable(j->getState(1));
	  ((DOFrecord *)rec)->getIKjoint(2)->setVariable(j->getState(2));
	}
	else{
	  ((DOFrecord *)rec)->getIKjoint(0)->setVariable(-j->getState(0));
	  ((DOFrecord *)rec)->getIKjoint(1)->setVariable(-j->getState(1));
	  ((DOFrecord *)rec)->getIKjoint(2)->setVariable(-j->getState(2));
	}
	break ;
      case J_BALL:
	  danceTcl::OutputMessage("BALL not supported yet");
	  ErrorFlag = TRUE;
	  break ;
      }
    }
    rec = rec->next;
 }
 if(ErrorFlag){danceTcl::OutputMessage("Error updating IK joints");}
 if(assembler->root != NULL){assembler->root->moveJoint();}
}

/**
 *Moves the m_artObj to correspond to the position of the IK_Joints
 *
 *@param void
 *@return void
 */
void IKActuatorForce::updateJoints(void){
     
  int i = 0;
  int ErrorFlag = FALSE;
  Joint *j = NULL;
  storageClass *rec = recs->first->next;
   m_artObj->changeToLocal();	
   while(rec != recs->last){
     if(((DOFrecord *)rec)->getJointNumber() >= 0){	
        j = m_artObj->joint[((DOFrecord *)rec)->getJointNumber()];
        switch(j->m_jointType){
	case J_FREE:
	  danceTcl::OutputMessage("Free joints are not supported by the IK solver");
	  ErrorFlag = TRUE;
	  break;
	case J_SLIDER:
	  danceTcl::OutputMessage("Slider joints are not supproted by the IKsolver");
	  ErrorFlag = TRUE;
	  break;
	case J_PIN:
	  if(((DOFrecord *)rec)->isReversed == FALSE){
	    j->setState(0,((DOFrecord *)rec)->getIKjoint(0)->getVariable(),FALSE);}
	  else{j->setState(0,-((DOFrecord *)rec)->getIKjoint(0)->getVariable(),FALSE);}
	  j->applyTransformation();
	  break;
	case J_UNIVERSAL:
          if(((DOFrecord *)rec)->isReversed == FALSE){
	    j->setState(0,((DOFrecord *)rec)->getIKjoint(0)->getVariable(),TRUE);
	    j->setState(1,((DOFrecord *)rec)->getIKjoint(1)->getVariable(),FALSE);
	  }  
          else{ 
	    j->setState(0,-((DOFrecord *)rec)->getIKjoint(0)->getVariable(),TRUE);
	    j->setState(1,-((DOFrecord *)rec)->getIKjoint(1)->getVariable(),FALSE);
	  }
	  j->applyTransformation();
	  //danceTcl::OutputMessage("UNIVERSAL joint updated");
	  break;
	case J_GIMBAL:
	  if(((DOFrecord *)rec)->isReversed == FALSE){
	    j->setState(0,((DOFrecord *)rec)->getIKjoint(0)->getVariable(),TRUE);
	    j->setState(1,((DOFrecord *)rec)->getIKjoint(1)->getVariable(),TRUE);
	    j->setState(2,((DOFrecord *)rec)->getIKjoint(2)->getVariable(),FALSE);
	  }  
          else{ 
	    j->setState(0,-((DOFrecord *)rec)->getIKjoint(0)->getVariable(),TRUE);
	    j->setState(1,-((DOFrecord *)rec)->getIKjoint(1)->getVariable(),TRUE);   
            j->setState(2,-((DOFrecord *)rec)->getIKjoint(2)->getVariable(),FALSE);
	  }
	  j->applyTransformation();
	  break ;
	case J_BALL:
	  danceTcl::OutputMessage("BALL not supported yet");
	  ErrorFlag = TRUE;
	  break ;
	}
   }
     else{//danceTcl::OutputMessage("joint %i not updated",((DOFrecord *)rec)->getJointNumber());
      }
   rec = rec->next;
 }

 if(ErrorFlag){danceTcl::OutputMessage("Error updating joints");}
 
 //m_artObj->changeToGlobal();
 //m_artObj->updateStateConfig(-1);
 

 double mat[4][4];
 double newMat[4][4];
 double oldMat[4][4];
 double invRoot[4][4];

 double actualIKrootPos[3];
 double AOrootPos[3];
 double utilVec[3];
 //only adjust m_frame????
 m_artObj->changeToGlobal();
 m_artObj->updateStateConfig(-1);
 
 Joint *AOroot = m_artObj->joint[0];
 Link *l = AOroot->getOutboardLink();
 int jointType=AOroot->getJointType();
 root->getInvTransMat(invRoot);
 l->getTransMat(oldMat);
 multiplyMat(oldMat,invRoot,mat);
 multiplyMat(mat,initialRootMat,newMat);
   
 m_artObj->changeToLocal();
 l->setTransMat(newMat);
 //get the old state variables for position
 double state[3];
 if(jointType == 5 || jointType ==4){//slider of free joint
   state[0]=AOroot->getState(0);
   state[1]=AOroot->getState(1);
   state[2]=AOroot->getState(2);
 }
 AOroot->create(0,jointType,NULL,l);
 if(jointType == 5 || jointType == 4){//slider or free joint
   AOroot->setState(0,state[0],TRUE);      
   AOroot->setState(1,state[1],TRUE);
   AOroot->setState(2,state[2],FALSE);
 }  

 m_artObj->changeToGlobal();
 m_artObj->updateStateConfig(-1);
 
 root->getPosition(actualIKrootPos);
 m_artObj->joint[0]->getPosition(AOrootPos);
 VecSubtract(utilVec,initialRootPos,actualIKrootPos);
 VecAdd(AOrootPos,AOrootPos,utilVec);
 m_artObj->moveJointAndChildren(0,AOrootPos);
 m_artObj->updateStateConfig(-1);
   
}

void IKActuatorForce::updateVariables(void){
     
    int i = 0;
    int ErrorFlag = FALSE;
    Joint *joint = NULL;
    storageClass *rec = recs->first->next;
    DSimulator *sim = m_artObj->simulator ;
    while(rec != recs->last){
	if(((DOFrecord *)rec)->getJointNumber() >= 0){	
	    int nj = ((DOFrecord *)rec)->getJointNumber() ;
	    joint = m_artObj->joint[nj] ;
	    int indx ;
	    switch(joint->m_jointType){
		case J_FREE:
		    danceTcl::OutputMessage("Free joints are not supported by the IK solver");
		    ErrorFlag = TRUE;
		    break;
		case J_SLIDER:
		    danceTcl::OutputMessage("Slider joints are not supproted by the IKsolver");
		    ErrorFlag = TRUE;
		    break;
		case J_PIN:
		    indx = sim->GetIndex(nj,0) ;
		    if(((DOFrecord *)rec)->isReversed == FALSE)
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(0)->getVariable() ;
		    else
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(0)->getVariable();
		    break;
		case J_UNIVERSAL:
		    if(((DOFrecord *)rec)->isReversed == FALSE){
			indx = sim->GetIndex(nj,0) ;
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(0)->getVariable() ;
			indx = sim->GetIndex(nj,1) ;
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(1)->getVariable() ;
		    }  
		    else{ 
			indx = sim->GetIndex(nj,0) ;
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(0)->getVariable() ;
			indx = sim->GetIndex(nj,1) ;
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(1)->getVariable() ;
		    }
		    break;
		case J_GIMBAL:
		    if(((DOFrecord *)rec)->isReversed == FALSE)
		    {
			indx = sim->GetIndex(nj,0) ;
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(0)->getVariable() ;
			indx = sim->GetIndex(nj,1) ;
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(1)->getVariable() ;
			indx = sim->GetIndex(nj,2) ;
			m_q[indx] = ((DOFrecord *)rec)->getIKjoint(2)->getVariable() ;
		    }
		    else
		    {
			indx = sim->GetIndex(nj,0) ;
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(0)->getVariable() ;
			indx = sim->GetIndex(nj,1) ;
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(1)->getVariable() ;
			indx = sim->GetIndex(nj,2) ;
			m_q[indx] = -((DOFrecord *)rec)->getIKjoint(2)->getVariable() ;
		    }
		    break ;
		case J_BALL:
		    danceTcl::OutputMessage("BALL not supported yet");
		    ErrorFlag = TRUE;
		    break ;
	    }
	}
	else{//danceTcl::OutputMessage("joint %i not updated",((DOFrecord *)rec)->getJointNumber());
	}
	rec = rec->next;
    }
    
    if(ErrorFlag){danceTcl::OutputMessage("Error updating joints");}
   
    //do we need all this stuff for the variables?
    //this section only translates the root joint, illegal in simulation
    /*********************************************************************************
 double testMat[4][4];
 double mat[4][4];
 double newMat[4][4];
 double oldMat[4][4];
 double invRoot[4][4];

 double actualIKrootPos[3];
 double AOrootPos[3];
 double utilVec[3];
 
 m_artObj->changeToGlobal();
 m_artObj->updateStateConfig(-1);
 
 Joint *AOroot = m_artObj->joint[0];
 Link *l = AOroot->getOutboardLink();
 int jointType=AOroot->getJointType();
 root->getInvTransMat(invRoot);
 root->getTransMat(testMat);
 l->getTransMat(oldMat);
 multiplyMat(oldMat,invRoot,mat);
 multiplyMat(mat,initialRootMat,newMat);

   
 m_artObj->changeToLocal();
 l->setTransMat(newMat);
 AOroot->create(0,jointType,NULL,l);
 m_artObj->changeToGlobal();
 m_artObj->updateStateConfig(-1);
 root->getPosition(actualIKrootPos);
 m_artObj->joint[0]->getPosition(AOrootPos);
 VecSubtract(utilVec,initialRootPos,actualIKrootPos);
 VecAdd(AOrootPos,AOrootPos,utilVec);
 m_artObj->moveJointAndChildren(0,AOrootPos);
 m_artObj->updateStateConfig(-1);
    *************************************************/
}

/**
 * Creates an IKconstraint and updates all the data structures.
 *
 * @param Link *endEffector The endEffector of the desired constraint
 * @return IKconstraint * The completed IKconstraint, which has already been added to the data structures
 */
IKconstraint *IKActuatorForce::addConstraint(Link *endEffector){
    IK_Joint *ikJ;
    ikJ = createIKjoints(endEffector);
    assembler->root->moveJoint();
    IKconstraint *c;
    if(newConstraintType == position){c = new posConstraint(numConstraints);}
    else{c = new orientConstraint(numConstraints);}
    numConstraints++;
    c->endEffector = ikJ;  
    c->realEndEffector = endEffector;
    c->initGoal();
    assembler->addConstraint(c);
    return (IKconstraint *)c;  
}

/**
 * Removes the activeConstraint
 *
 * Removes the activeConstraint, and removes any unecessary parts of the data 
 * structures.  activeConstraint and activeJoint are set to NULL
 * @param void
 * @return void
 */
void IKActuatorForce::removeActiveConstraint(void){
  IKconstraint *con = activeConstraint;
  setActiveConstraint(NULL);
  setActiveJoint(NULL);
  if( assembler->numJoints == 0 ) return ;

  int *delList = new int [assembler->numJoints];
  if( delList == NULL )
  {
	  danceTcl::OutputMessage("ERROR: Cannot allocate memory.") ;
	  return ;
  }
  int listLength;
  storageClass *s;
  assembler->removeConstraint(con,&delList[0],listLength);
  int i;
  danceTcl::OutputMessage("%i joints to be deleted", listLength);
  
  for(i=0; i<listLength; i++){danceTcl::OutputMessage("%i",delList[i]);}
  for(i=0; i<listLength; i++){
    s = recs->first->next;
    s = ((DOFrecord *)s)->find(delList[i]);
    if(s == NULL){danceTcl::OutputMessage("joints to be deleted not found in DOFrecords");}
    delete s; s = NULL ;
  }
  delete con;
  delete [] delList ;
}

/**
 * Multiplies only the orientation section of the trasformation matrices
 *
 * Foward matrix multiplication, result = a*b
 * @param double a[4][4]
 * @param double b[4][4]
 * @param double result[4][4]
 * @return void
 */
void IKActuatorForce::multiplyMat(double a[4][4],double b[4][4],double result[4][4]){
    int i; int j;
    for(i=0; i<3; i++){
      for(j=0; j<3; j++){
	 result[i][j]=a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j];
      }
    }
     result[3][0]=result[3][1]=result[3][2]=result[0][3]=result[1][3]=result[2][3]=0;
     result[3][3]=1;
}

//useful for debugging
void IKActuatorForce::setup(void){
    setRoot(m_artObj->joint[6]->getOutboardLink());      
    addConstraint(m_artObj->joint[4]->getOutboardLink());
    danceTcl::OutputMessage("adding second constraint");
    addConstraint(m_artObj->link[1]);
    updateJoints();
}

/**
 * Shows the GLNameStack when something is selected.
 *
 * @param DView The the view where the user is selecting
 * @param int x, int y Coordinates of the click
 * @param button The buttonID of the mouse click (currently not used)
 * @param int &number The height of the name stack (0 if nothing is selected)
 * @param int *item A copy of the GL name stack
 * @param int type Should be one of the Actuator_Modes, indicates what is being selected
 * @return int
 */
int IKActuatorForce::handleSelection(DView *view, int x, int y, int button, 
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
	case default_mode:
	  glPushName(default_mode);
	  display(IKDISPLAYNORMAL);
	  glPopName();
	  break;
        case editCon_mode:
          glPushName(editCon_mode);
          display(IKDISPLAYACTIVEONLY);
	  glPopName() ;
	  break;
	case newConstraint_mode:
	case changeRoot_mode:
	  glPushName(changeRoot_mode);
	  // Must use	output with two	arguments.
	  m_artObj->displayLinks(LDISPLAY_SOLID);
	  glPopName();
	  break;
	}
	
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
		      if(ns != hp) {
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

/**
 * Sets the activeConstraint and links it to the interface
 *
 * @param IKconstraint * aCon  is allowed to be NULL
 * @return void
 */
void IKActuatorForce::setActiveConstraint(IKconstraint * aCon){
  char varName[256] ;
  if(activeConstraint != NULL){
    activeConstraint->highlight = FALSE;
    sprintf(varName,"ConstraintWeight%s", getName()) ;
    Tcl_UnlinkVar(interpreter, varName) ;
  }
  activeConstraint = aCon;
  if(activeConstraint != NULL){ 
    activeConstraint->highlight = TRUE;   
   
    sprintf(varName,"ConstraintWeight%s", getName()) ;
    if ( Tcl_LinkVar(interpreter,varName, (char *) &activeConstraint->weight,TCL_LINK_DOUBLE) == TCL_ERROR){
      danceTcl::OutputMessage("Cannot link variable %s", varName) ;

    }
  }
}

/**
 * Sets the activeJoint and links it to the interface
 *
 * @param DOFrecrod * aDOF  is allowed to be NULL
 * @return void
 */
void IKActuatorForce::setActiveJoint(DOFrecord * aDOF){
  char varName[256] ;
  if(activeJoint != NULL){
    sprintf(varName,"JointWeight%s", getName()) ;
    Tcl_UnlinkVar(interpreter, varName) ;
  }
  activeJoint = aDOF;
  if(activeJoint != NULL){    
    sprintf(varName,"JointWeight%s", getName());
   
    if ( Tcl_LinkVar(interpreter,varName, (char *) &activeJoint->weight,TCL_LINK_DOUBLE) == TCL_ERROR){
      danceTcl::OutputMessage("Cannot link variable %s", varName) ;
      
    }
  }
}

/**
 * Gets a bounding box for the entire actuator.
 *
 * @param void
 * @return BoundingBox *
 */
BoundingBox *IKActuatorForce::calcBoundingBox(BoundingBox *b)
{
  
  b->xMin = 0;
  b->xMax = 0;
  b->yMin = 0;
  b->zMin = 0;
  b->yMax = 0;
  b->zMax = 0;

  
  storageClass *s = assembler->allConstraints->first->next;
  while(s != assembler->allConstraints->last){
    BoundingBox box;
    ((IKconstraint *)s)->calcBoundingBox(box,root);
    b->merge(b,&box);
  }
  return b;

}
  

int IKActuatorForce::linkVariables(Tcl_Interp *interp)
{/*
  char varName[256] ;
    sprintf(varName,"IKActuatorForceJointWeight", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &activeJoint->weight,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable %s", varName) ;
	return TCL_ERROR ;
    }
    

    sprintf(varName,"IKJointWeight", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &activeJoint,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable %s", varName) ;
	return TCL_ERROR ;
    }
    
 */
    return TCL_OK ;
}
/**
 * UnLinks the variables connected to the interface
 *
 * @param Tcl_Interp *interp
 * @return void
 */
void IKActuatorForce::unLinkVariables(Tcl_Interp *interp)
{
    char name[256] ;
    sprintf(name, "ConstraintWeight%s", getName()) ;
    Tcl_UnlinkVar(interp, name) ;
    sprintf(name, "JointWeight%s", getName()) ;
    Tcl_UnlinkVar(interp, name) ;
    return ;
}

/**
 * Updates the goal field of the activeConstraint
 * 
 * @param DView *focus
 * @param int button The buttonID of button thats down.  Not used currently
 * @param int x, int y
 * @param int diffx, int diffy (not used currently)
 * @return void
 */
void IKActuatorForce::HandleConstraintEdit(DView *focus, int button, int x, int y, int width, int height, int diffx, int diffy)
{
   // danceTcl::OutputMessage("HandleConstraintEdit called");
 
    GLdouble win[3], jpos[3];
    double utilVec[3];
    activeConstraint->getGoal(utilVec);
    root->getWorldCoord(jpos,utilVec);
    focus->getWindowCoords(jpos,win);
    focus->getWorldCoords(jpos,x, y, win[2]);
    //event->Window->getWorldCoords(jpos,event->winX, event->winY, -1); 
    root->getLocalCoord(utilVec,jpos);
    activeConstraint->setGoal(utilVec);
    
}

/**
 * Foward multiplication of mat*vec using only the orientation part of mat
 *
 * @param double mat[4][4]
 * @param double vec[3]
 * @param double result[3]
 * @return void
 */
void IKActuatorForce::multiplyVec(double mat[4][4], double vec[3], double result[3]){
  int i;
   for(i = 0; i<3; i++){
     result[i]=mat[i][0]*vec[0]+mat[i][1]*vec[1]+mat[i][2]*vec[2];
   }
}

/**
 * Display all or part of the actuator
 *
 * The modes are: IKDISPLAYNORMAL (1) display everything
 * IKDISPLAYACTIVEONLY (2) display only the active constraint
 * IKDISPLAYLINKS (0) display only the links of the m_artObj
 * @param int mode
 * @return void
 */
void IKActuatorForce::display(int mode){

  //update the graphics size based on the volume of the view
  DView *wview = dance::AllViews->getViewFocus();
  if (wview) {
    double pos[3]; if(root){root->getPosition(pos);}else{pos[0]=0;pos[1]=0;pos[2]=0;}		
    double win[3]; wview->getWindowCoords(pos,win);
    double worldwidth = wview->getFrustumWidth(win[2]);
    m_graphicsRad = 0.015*worldwidth;
  }

  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING);
  storageClass *s = recs->first->next;
  switch(mode){
  case IKDISPLAYNORMAL:
  
    glPushName(0);//joint code
    while(s != recs->last){
      glPushName(((DOFrecord *)s)->getJointNumber());
      ((DOFrecord *)s)->getIKjoint(0)->display(initialRootMat,m_graphicsRad*0.5);
      glPopName();
      s = s->next;
    }
    if(root != NULL){  
      glLineWidth(2.0);
      glPushMatrix();
      glMultMatrixd((GLdouble *)root->m_transMat);
      glPushName(4200);
      glColor3f(0.7f,0.0f,0.7f);
      glutSolidSphere(m_graphicsRad*0.6,4,4);
      glPopName();
      glPopMatrix();    
    }
    if(activeJoint != NULL){  
      glLineWidth(2.0);
      glPushMatrix();
      glMultMatrixd((GLdouble *)root->m_transMat);
      double pos[3];
      activeJoint->getIKjoint(0)->getGlobalPosition(pos);
      glTranslatef(pos[0],pos[1],pos[2]);
      glPushName(4201);
      glColor3f(0.7f,0.7f,0.0f);
      glutSolidSphere(m_graphicsRad*0.5,4,4);
      glPopName();
      glPopMatrix();    
    }
    glPopName();
    glPushName(1);//constraint code
    assembler->display(initialRootMat,m_graphicsRad);
    glPopName();
    break;
  case LDISPLAY_SELECTION:
  case IKDISPLAYLINKS:
    m_artObj->displayLinks(LDISPLAY_SOLID);
    break;
  case IKDISPLAYACTIVEONLY:
  
    if(activeConstraint != NULL){
       activeConstraint->display(initialRootMat,m_graphicsRad+0.02);
    } 
  }
  glPopAttrib();
}

void IKActuatorForce::ExertLoad(DSystem *ao, double time, 
				 double dt, double *state, double *dstate)
{
    
    if( ao != m_artObj ) return ;

    DSimulator *sim = ao->simulator;
    if (sim == NULL) {
	danceTcl::OutputMessage("ExertLoad: Simulator not present.");
	return;
    }
    
    if (applyAllObjects) {
	danceTcl::OutputMessage("InteractActuator actuator should be applied"
		      "	to only	one object!!") ;
	return ;
    }
    
   
    if( m_usePG == TRUE )
    {	
 	CtrPrm *q = m_pg.GetParams(time) ;
	if( q == NULL ) return ;
	Joint **joints = m_artObj->getJoints() ;
	int count = 0 ;
	for( int i = 0 ; i < m_artObj->getNumJoints() ; i++ )
	{
	    Joint *joint = joints[i] ;
	    if( joint->getJointType() == J_FREE ) continue ;
	    for( int j = 0 ; j < joint->getNumDof() ; j++ )
	    {
		int indx = m_artObj->simulator->GetIndex(i,j) ;
		m_q[indx] = q[count].v;
		m_ks[indx] = q[count].ks ;
		m_kd[indx] = q[count].kd ;
		count++ ;
	    }
	}
    }
    else
    {
	// synchronize IK structure
	if( root != NULL )
	{
	    updateIKjoints() ;
	    // solve ik
	    if ( (m_solveContSim == TRUE ) || (m_needsSolving == TRUE) )
		{
			assembler->solve(solveMode) ;
			m_needsSolving = 0 ;
		    // update the variables
		    updateVariables() ;
		}
	}
    }
    
    ApplyState(m_q, sim, state, dstate) ; 
}


void IKActuatorForce::ApplyState(double *qpos, DSimulator *sim, 
				      double *state, double *dstate)
{
    int	i, j, indx ;
    double torq = 0 ;

//     for ( i = 0 ; i < 19 ; i++ )
//	danceTcl::OutputMessage("%lf ", qpos[i])	;
//     danceTcl::OutputMessage("\n") ;
//     fflush(stdout) ;


	ArticulatedObject *ao = (ArticulatedObject *) m_artObj ;
    Joint **joint = m_artObj->getJoints()	;
    // start from 1 since 0 is a free joint and it is not controlled
    for( i = 1 ; i < ao->getNumJoints()  ; i++ )
    {
	if( joint[i]->getJointType() ==	J_FREE)	;
	else if( joint[i]->getJointType() == J_BALL )
	{
	    danceTcl::OutputMessage("ERROR: Ball joints cannot be handled yet!\n") ;
	}
	else
	{
	    for( j = 0 ; j < joint[i]->getNumAxis() ; j++ )
	    {
		indx = sim->GetIndex(i,j) ;

		if( joint[i]->getJointType() ==	J_SLIDER)
		{
		    danceTcl::OutputMessage("Slider joint currently not supported!\n") ;
		    // do some different stuff
		    ;
		}
		else
		{
		    // set the proper stiffness and damping
		    joint[i]->stiffness[j] = m_ks[indx]*joint[i]->maxStiffness[j] ;
		    joint[i]->damping[j] = m_kd[indx]*joint[i]->maxDamping[j] ;

		    torq = joint[i]->stiffness[j]*
		      (qpos[indx] - state[indx]) -
		      joint[i]->damping[j]*dstate[indx] ;
		//    if( torq*(qpos[indx] - state[indx]) <
		  //  	(double) 0.0) torq = 0.0 ;

		    
		    // maintain the limits
		    if( joint[i]->getJointType() != J_FREE )
		    {
			//double linSpringStiff = 100.0 ;
			//double expSpringStiff = 10.0 ;
			//double expSpringDamp = 10.0 ;

			double linSpringStiff = 10.0 ;
			double expSpringStiff = 1.0 ;
			double expSpringDamp = 10.0 ;

			double low, high, diff ;
			joint[i]->getLimits(j, &low, &high) ;
			double st = state[indx] * 180.0 / M_PI ; // transform to degrees
			double expSpringTorq ;
			if( (diff = (low - st)) > 0.00001 )
			{
			    expSpringTorq = linSpringStiff*(exp(expSpringStiff*diff) - 1 ) -
			      expSpringDamp*dstate[indx] ;
			    if( expSpringTorq > 0.0 ) // avoid sticky effect
				torq = torq + expSpringTorq ;
			}
			else if( (diff = st - high) > 0.00001 )
			{
			    expSpringTorq = - linSpringStiff*(exp(expSpringStiff*diff) - 1) 
			      - expSpringDamp*dstate[indx] ;
			    if( expSpringTorq < 0.0 ) // avoid sticky effect
				torq = torq + expSpringTorq ;
			}
			//if( diff > 0.0000001) 
			//  danceTcl::OutputMessage(" low %lf high %lf diff %lf torq 
			// = %lf st %lf\n", low, high, diff, torq, st) ;
		    }
		    
		    // danceTcl::OutputMessage("joint %d	axis %d	qpos[%d] %lf torq %lf\n",
		    //	   joint_number, j, indx, qpos[indx], torq) ;
		    
// 		    danceTcl::OutputMessage("joint %d axis %d Torque: %lf ", i, j, torq) ;
// 		    danceTcl::OutputMessage("ks %lf kd %lf state %lf dstate %lf \n",
// 			   joint[i]->stiffness[j],
// 		   	   joint[i]->damping[j],
		    //		    sim->state[indx], sim->dstate[indx]) ;
		    // equivalent to sdfast's sdhinget
		    sim->GeneralizedForce(i,j,torq) ;

		}
	    }
	}
    }
}


void IKActuatorForce::Reset(ArticulatedObject *ao)
{
  UnlinkVariables(m_artObj) ;
  if( ao == NULL )
    {
      if( applyList->ao != NULL )
	m_artObj = (ArticulatedObject *) applyList->ao ;
    }
  else
    m_artObj = ao ;
  
  danceTcl::OutputMessage ("Reread the system.") ;
  if( m_artObj == NULL )
    {
      danceTcl::OutputMessage("ERROR:IKActuatorForce::Reset: "
			      "articulated object is null") ;
      return ;
    }
  
  if( m_artObj->simulator == NULL )
    {
      danceTcl::OutputMessage("ERROR:IKActuatorForce::Reset: "
			      "simulator is null") ;
      return ;
    }
  
  
  LinkVariables(m_artObj) ;
    
  Joint **joints = m_artObj->getJoints() ;

  // set the initial state to the current one
  for( int i = 0 ; i < m_artObj->getNumJoints() ; i++ )
    {
      Joint *joint = joints[i] ;
      if( joint->getJointType() == J_FREE ) continue ;
	for( int j = 0 ; j < joint->getNumDof() ; j++ )
	  {
	    int indx = m_artObj->simulator->GetIndex(i,j) ;
	    m_q_prev[indx] = m_q[indx] = joint->getDof(j) * M_PI / 180.0;
	    
	  }
    }
}

void IKActuatorForce::SetJointState(int argc, char **argv)
{
	if( argc < 2 ) // actually argc is 3 because this is a callback from a tk scale.
	{
		danceTcl::OutputMessage("expected: joint_index dof_index") ;
		return ;
	}

	Joint *joint = m_artObj->getJoint(argv[0]) ;
	int nj = joint->getNumber() ;
	int ndof = atoi(argv[1]) ;

	danceTcl::OutputMessage("Setting state for joint %s", argv[0]) ;
	SetJointState(nj,ndof) ;

}

void IKActuatorForce::SetJointState(int nj, int ndof)
{
	Joint *joint = m_artObj->getJoint(nj) ;

	if( joint == NULL )
	{
		danceTcl::OutputMessage("Joint is null!") ;
		return ;
	}
	int indx = m_artObj->simulator->GetIndex(nj, ndof) ;
	joint->setState(ndof, m_q[indx]) ;
	m_artObj->updateStateConfig() ;
}

void IKActuatorForce::LinkVariables(ArticulatedObject *ao)
{
    if( ao->simulator == NULL )
    {
	danceTcl::OutputMessage("ERROR:IKActuatorForce::LinkVariables: "
				"simulator is null") ;
	return ;
    }

    Joint **joints = ao->getJoints() ;
    for( int i = 0 ; i < ao->getNumJoints() ; i++ )
    {
	Joint *joint = joints[i] ;
	if( joint->getJointType() == J_FREE ) continue ;
	for( int j = 0 ; j < joint->getNumDof() ; j++ )
	{
	    int indx = ao->simulator->GetIndex(i,j) ;
	    char vname[50] ;
	    sprintf(vname, "%s_%d_%d_v",getName(), i,j) ; 
	    if( Tcl_LinkVar(interpreter, vname, (char *) &m_q[indx], TCL_LINK_DOUBLE) == TCL_ERROR )
	    {
		  danceTcl::OutputMessage("ERROR: Cannot link	variable %s", vname);
		  return ;
	    }
	    sprintf(vname, "%s_%d_%d_ks",getName(), i,j) ; 
	    if( Tcl_LinkVar(interpreter, vname, (char *) &m_ks[indx], TCL_LINK_DOUBLE) == TCL_ERROR )
	    {
		  danceTcl::OutputMessage("ERROR: Cannot link	variable %s", vname);
		  return ;
	    }
	    sprintf(vname, "%s_%d_%d_kd",getName(), i,j) ; 
	    if( Tcl_LinkVar(interpreter, vname, (char *) &m_kd[indx], TCL_LINK_DOUBLE) == TCL_ERROR )
	    {
		  danceTcl::OutputMessage("ERROR: Cannot link  variable %s", vname);
		  return ;
	    }
	}
    }
    danceTcl::OutputMessage("Variables linked ok.") ;
}

void IKActuatorForce::UnlinkVariables(ArticulatedObject *ao)
{
  if( ao == NULL ) return ;

    Joint **joints = ao->getJoints() ;

    for( int i = 0 ; i < ao->getNumJoints() ; i++ )
    {
	Joint *joint = joints[i] ;
	if( joint->getJointType() == J_FREE ) continue ;
	for( int j = 0 ; j < joint->getNumDof() ; j++ )
	{
	    char vname[50] ;
	    sprintf(vname, "%s_%d_%d_v",getName(), i,j) ; 
	    Tcl_UnlinkVar(interpreter, vname) ;
	    sprintf(vname, "%s_%d_%d_ks",getName(), i,j) ; 
	    Tcl_UnlinkVar(interpreter, vname) ;
	    sprintf(vname, "%s_%d_%d_kd",getName(), i,j) ; 
	    Tcl_UnlinkVar(interpreter, vname) ;
	}
    }
}

void IKActuatorForce::InitSimul(DSystem *sys, double time)
{
	if( m_artObj == (ArticulatedObject *) sys )
	{
		m_isSimInit = TRUE ;
		Reset(m_artObj) ;
	}
	m_pg.InitSimul(time) ;
}


void IKActuatorForce::AtEndSimul(DSystem *sys, double time)
{
	if( m_artObj == (ArticulatedObject *) sys )
	{
		m_isSimInit = FALSE ;
	}
}
static int CalcControlNdof(ArticulatedObject *ao)
{
    if( ao == NULL ) return 0 ;

    Joint **joints = ao->getJoints() ;
    int count = 0 ;
    for( int i = 0 ; i < ao->getNumJoints() ; i++ )
    {
	Joint *joint = joints[i] ;
	if( joint->getJointType() == J_FREE ) continue ;
	count += joint->getNumDof() ;
    }
    return count ;
}

















