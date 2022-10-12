
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
#include "DOFrecord.h"
#include "vector.h"
#include <stddef.h>
#include <assert.h>

DOFrecord::DOFrecord(){
       root = FALSE; previous = NULL; next = NULL;
       j[0]=NULL;
       j[1]=NULL;
       j[2]=NULL;
       numIKjoints = 0;
       isReversed = FALSE;
       weight = 1;
}

//remove itself cleanly from the list, do not delete IK joints
DOFrecord::~DOFrecord(){
  remove();
}

IK_Joint *DOFrecord::getIKjoint(int dof){
	assert(0 <= dof && dof <3);
	return j[dof];
}

void DOFrecord::setIKjoint(int dof, IK_Joint *ikJ){
	assert(0 <= dof && dof <3);
	j[dof] = ikJ;
}

void DOFrecord::setJointNumber(int n){parentJointNumber = n;}
int DOFrecord::getJointNumber(void){return parentJointNumber;}

//linear search
DOFrecord *DOFrecord::find(int jointNum){
   if(parentJointNumber == jointNum){return this;}
   else if((parentJointNumber > jointNum) || (next->next  == NULL)){return NULL;}
   else {return ((DOFrecord *)next)->find(jointNum);}
}

void DOFrecord::add(DOFrecord *rec){
   int jointNum = rec->getJointNumber();
   assert(jointNum != parentJointNumber);
   if (jointNum < parentJointNumber){//add the joint behind
      rec->previous = previous;
      rec->next = this;
      previous->next = rec;
      previous = rec;
   }
   else if(next->next == NULL){//add in front
      rec->next = next;
      rec->previous = this;
      next->previous = rec;
      next = rec;
   }
   else{ ((DOFrecord *)next)->DOFrecord::add(rec);}
}

void DOFrecord::linkJoints(void){
    int i;
    if(numIKjoints > 2){
      if(isReversed){
         j[0]->setParentJoint(j[1]);
         j[1]->addChildJoint(j[0]);
         j[1]->setParentJoint(j[2]);
         j[2]->addChildJoint(j[1]);
      }
      else{
         j[0]->addChildJoint(j[1]);
         j[1]->setParentJoint(j[0]);
         j[1]->addChildJoint(j[2]);
         j[2]->setParentJoint(j[1]);
      }
    }
    else if(numIKjoints > 1){
      if(isReversed){
         j[0]->setParentJoint(j[1]);
         j[1]->addChildJoint(j[0]);
      }
      else{
         j[0]->addChildJoint(j[1]);
         j[1]->setParentJoint(j[0]);
      }   
    }
    
    for(i=0; i<numIKjoints; i++){
        j[i]->jointNumber = parentJointNumber;
        j[i]->rec = this;
    }
     
}

void DOFrecord::linkTo(DOFrecord *nextRec){
     IK_Joint *end;
     IK_Joint *beginning;
     if(isReversed){end = j[0];}
     else{end = j[numIKjoints-1];}
     if(nextRec->isReversed){
          beginning = nextRec->getIKjoint(nextRec->numIKjoints-1);
     }
     else{beginning = nextRec->getIKjoint(0);}
     end->addChildJoint(beginning);
     beginning->setParentJoint(end);
}

//reverses all angles, places the non zero position vector at the 
//correct spot
//does not reverse the pointers between joints
void DOFrecord::reverse(void){
    int i;
    double vec[3];
    double d1, d2;
   
    j[0]->getLocalPosition(vec);
    j[numIKjoints-1]->setLocalPosition(vec);
    if(numIKjoints > 1){vec[0]=0;vec[1]=0;vec[2]=0; j[0]->setLocalPosition(vec);} 
    for(i=0; i<numIKjoints; i++){
      //j[i]->getAxis(vec);
      //vec[0]=-vec[0];
      //vec[1]=-vec[1];
      //vec[2]=-vec[2];
      //j[i]->setAxis(vec);
      d1 = j[i]->getVariable();
      j[i]->setVariable(-d1);
      j[i]->getLimits(d1,d2);
      j[i]->setLimits(-d2,-d1);
      j[i]->updateLocalTransform();
    }
    isReversed = TRUE;
}


