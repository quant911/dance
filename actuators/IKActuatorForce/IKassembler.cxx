
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
#include "IK_Joint.h"
#include "IKassembler.h"
#include "list.h"
#include "IKdata.h"
#include "IKconstraint.h"
#include "posConstraint.h"
#include "danceTcl.h"
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

IKassembler::IKassembler(){   
    joints = new list;
    allConstraints = new list;
    numConstraints = 0;
    numJoints = 0;
    root = NULL;   
} 

IKassembler::~IKassembler(){
  if(root){delete root; root = NULL;}
  if(joints != NULL){delete joints;} 
  if(allConstraints != NULL){delete allConstraints;}
}

/**
 *adds a constraint to the assembler
 *
 *The IK_Joints have to added as for the assembler to move the endEffector
 * @param IKConstraint *newC
 * @return void
 */
void IKassembler::addConstraint(IKconstraint *newC){
    storageClass *current;
    current = joints->first->next;
    IK_Joint *ikJ;
    while(current != joints->last){
        ikJ = ((IKdata *)current)->joint;
        if(newC->endEffector->isChildOf(ikJ)==TRUE){
             ((IKdata *)current)->addConstraint(newC); 
	}  
        current = current->next;
    }
    allConstraints->add(newC);
    numConstraints++;
}

/**
 * Removes c from the data structure
 *
 * @param int *delJoints A list of joints that are no longer needed (should be preallocated)
 * @param int &numDelJoints the lenght of delJoints
 * @return void
 */
void IKassembler::removeConstraint(IKconstraint *c,int *delJoints,int &numDelJoints){
   numDelJoints = 0;
   storageClass *ikD = joints->first->next;
   storageClass *conStr;
  
   //search all IK_Data for the joints with only the constraint and destroy
   while(ikD != joints->last){
     conStr = ((IKdata *)ikD)->constraints->first->next;
     //remove all pointers to the constraint c
     while(conStr != ((IKdata *)ikD)->constraints->last){
       if(((conStorage *)conStr)->constraint == c){
	 conStorage *temp  = ((conStorage *)conStr);
	 conStr = conStr->previous;
	 danceTcl::OutputMessage("deleting constraint %i from IKdata %i",temp->constraint->constraintNumber
                                  ,((IKdata *)ikD)->joint->jointNumber);
	 delete temp;
         ((IKdata *)ikD)->numConstraints--;
       }
       conStr = conStr->next;
     }
     if(((IKdata *)ikD)->numConstraints == 0){
       IKdata * temp =(IKdata *)ikD;
       ikD = ikD->previous;
       delJoints[numDelJoints]=temp->joint->jointNumber;
       danceTcl::OutputMessage("Attempting to delete IKdata on joint # %i",delJoints[numDelJoints]);
       delete temp;         
       numDelJoints ++;
     }
     ikD = ikD->next;
   }
   numJoints -= numDelJoints;
}

/**
 * Adds a joint to the assembler
 * 
 * Creates an IKData and links it to any IKconstraints effected by the IK_Joint
 * @param IK_Joint *j
 * @return void
 */
void IKassembler::addJoint(IK_Joint *j){
    IKdata *ikD = new IKdata;
    joints->add(ikD);
    ikD->joint = j;    
    storageClass *con = allConstraints->first->next;
    while(con != allConstraints->last){
        if( ((IKconstraint *)con)->endEffector->isChildOf(j) == TRUE){ 
	      ikD->addConstraint(((IKconstraint *)con));        
	}
        con = con->next;
    }
    numJoints++;
}

/**
 *Solves for all constraints, and moves the IK_Joints
 *
 * @param int mode  mode 0 uses the optimum angle method, mode 1 uses the derivative method
 * @return void
 */
void IKassembler::solve(int mode){
    assert(mode == 0 || mode ==1);
    double ang;
    double deltaAng;
  
    double weightSum;
    double conWeight;

    double errorDelta = 0.00000001;
    double perf = 1;  //perf is the performance of the solver based on how the
    //errorFunction is decreasing.  The solver stops when perf is below errorDelta
    double error = errorFunction();
    double lastError = 100;  
    int maxIterations = 3000;// in mode 1 the solver always uses the maxIterations
    int iterations = 0;
    int bounceCount = 0;//the number of times the errorFunction increases after an iteration
    
    double stepSize = 0.1;
    double velocity[100]; // should be changed to an array of size numJoints, however V C++ does not allow this
    //The velocity[i] is the change in angle of joint i at the last iteration. Used by mode 1 only
   
    int i;
    for( i=0; i< numJoints; i++){velocity[i]=0;}
    int count=0;
    int numConstraints;
    
    
    IK_Joint *ikJ;
    while( iterations < maxIterations && perf > errorDelta){
      double e;
      lastError = error;
      iterations ++;
      storageClass *current = joints->first->next;
      count =0;
      while(current != joints->last){
	      ikJ = ((IKdata *)current)->joint;
	      //danceTcl::OutputMessage("joint number %i",ikJ->jointNumber);
	      numConstraints = ((IKdata *)current)->numConstraints;
	      if (numConstraints > 0){
		      ang = 0;
		      weightSum = 0;
		      storageClass *con = ((IKdata *)current)->constraints->first->next;
		      for(i = 0; i < numConstraints; i++){
			if(((conStorage *)con)->constraint->endEffector != ikJ){
			  if(mode ==1){          
			    deltaAng = ((conStorage *)con)->constraint->derivative(ikJ);
			    e= ((conStorage *)con)->constraint->errorFunction();
			    deltaAng = deltaAng*e*0.5;
			    conWeight = ((conStorage *)con)->constraint->weight;	     
			    weightSum += conWeight;
			    ang += deltaAng*conWeight;
			  }
			  else{
			    deltaAng = ((conStorage *)con)->constraint->optimize(ikJ,e);
			    conWeight = ((conStorage *)con)->constraint->weight*e;	     
			    weightSum += conWeight*e; 
			    ang+= deltaAng*conWeight*e; //take a weighted average of the deltaAngs'
                            //based on the value of e and conWeight
			  }
			  
			}
			else{ang =0; weightSum =1;}
			con = con->next;
		      }
		      
		      if(fabs(weightSum) > 1e-6){
			ang = ang/weightSum*ikJ->getWeight();}
		      else{ang = 0;}

		      if(mode == 1){
			ang =ang + velocity[count]*0.5;  //the velocity addition seems to smooth out the motion considerably
			velocity[count] = ang;
		      }
		      else{ang = ang * 0.1+velocity[count]*0.5; velocity[count] = ang;}//the 0.1 factor is the damping
		
		      if(!((ang < 0) ||(ang >= 0))){
			danceTcl::OutputMessage("ouch in assembler code ,delta angle bad  caused unknown cause");
			danceTcl::OutputMessage("ouch");   
			char c = getchar();
		      }
                
		      
		      //danceTcl::OutputMessage("final delta angle decision: %lf", ang);
		      ang += ikJ->getVariable();
		      //danceTcl::OutputMessage("setting variable to %lf",ang);
		      if(!((ang < 0) ||(ang >= 0))){
			danceTcl::OutputMessage("ouch in assembler code, update angle bad");
			danceTcl::OutputMessage("ouch");   
			char c = getchar();
		      }
		      ikJ->setVariable(ang);
		      ikJ->moveJoint();
	      }
	      count++;
	      current = current->next;
      }
      error = errorFunction();
      if(mode == 0){perf = ((lastError-error)+10*perf)/11;} // perf is averaged over the last few iterations so one freak
      //iteration will not cause problems
      else{perf = 1;}
      if(error - lastError > 1e-5){// error function has increased- set the velocity to zero, decrease step size
	bounceCount++;
	     for(int b=0; b < numJoints; b++){
	       velocity[b]=0;
	     }
	        
      }  
     
	  
    }	
    
    // danceTcl::OutputMessage("solve: %d iterations, %d bounces",iterations,bounceCount);
    //if(error - lastError > 0.0)
    //danceTcl::OutputMessage("error %lf last Error %lf",error ,lastError);
    
}

/**
 * Returns a scalar based on how far the endEffectors are from their goals
 *
 * The weights of the constraints are factored in to the sum
 * @param void
 * @return double
 */
double IKassembler::errorFunction(void){
  double error = 0;
  storageClass *s = allConstraints->first->next;
  while(s != allConstraints->last){
     error += ((IKconstraint *)s)->errorFunction()*((IKconstraint *)s)->weight; 
     s = s->next;
  }
  return error;
}
/**
 *Prints information on the joints from root down
 *
 * @param void
 * @return void
 */
void IKassembler::printJointStructure(void){
  root->moveJoint();
  printJoint(root);
  //storageClass *s = allConstraints->first->next;
  //IKconstraint *c;
  //while(s != allConstraints->last){
  // c = ((IKconstraint *)s);
  // danceTcl::OutputMessage("constraint # %i, weight %lf",c->constraintNumber,c->weight);
  // s= s->next;
  // }
 
}

/**
 *Prints information about ikJ
 *
 * @param IK_Joint *ikJ
 * @teturn void
 */
void IKassembler::printJoint(IK_Joint *ikJ){
     assert(ikJ != NULL);
     int n = ikJ->getNumChildren();
     double vec[3];
     double d1;
     double d2;
     ikJ->getGlobalPosition(vec);
     danceTcl::OutputMessage("");
     danceTcl::OutputMessage("JOINT:");
     danceTcl::OutputMessage("%i children", n);
     danceTcl::OutputMessage("global position %lf %lf %lf", vec[0], vec[1], vec[2]);
     ikJ->getAxis(vec);
     danceTcl::OutputMessage("axis %lf %lf %lf", vec[0], vec[1], vec[2]);
     ikJ->getLimits(d1,d2);
     danceTcl::OutputMessage("limits %lf to  %lf ", d1, d2);
     danceTcl::OutputMessage("weight %lf",ikJ->getWeight());
     int i;
     for(i = 0; i < n; i++){
        printJoint(ikJ->getChildJoint(i));
     }
}
/**
 *Displays all the constraints
 *
 * @param double baseMat[4][4] The global transformation of the root link
 * @param double rad The radius of the spheres displayed
 * @return void
 */
void IKassembler::display(double baseMat[4][4],double rad){
   storageClass *s = allConstraints->first->next;
   while(s != allConstraints->last){
       ((IKconstraint *)s)->display(baseMat,rad);
       s= s->next;
   }
}















































