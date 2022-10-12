
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
#include "posConstraint.h"
#include "IKconstraint.h"
#include <stddef.h>
#include "vector.h"
#include "math.h"
#include "myMath.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLutilities.h"
#include "DanceObject.h"
#include "dance.h"
#include "DView.h"
#include "ViewManager.h"
#include "Link.h"
#include "danceTcl.h"
#include "IK_Joint.h"

posConstraint::posConstraint(int num){
    constraintNumber = num;
    isGlobalyPositioned = TRUE;
    weight = 1;
    endEffector = NULL;
    realEndEffector = NULL;
    highlight = FALSE;
}





void posConstraint::initGoal(void){
  endEffector->getGlobalPosition(goal);
}
double posConstraint::errorFunction(void){
  double ee[3]; endEffector->getGlobalPosition(ee);
  return sqrt((ee[0]-goal[0])*(ee[0]-goal[0])+(ee[1]-goal[1])*(ee[1]-goal[1])+(ee[2]-goal[2])*(ee[2]-goal[2]))*weight;
}
double posConstraint::derivative(IK_Joint *j){
   double utilVector[3];//handy variable
   double localTarget[3];//target from the joints reference frame
   double localEE[3];//end effector from the joints reference frame
   double target[3]; 
   double EEpos[3];     

   j->updateInverse();

   //find the co-ordinates in the joints referce frame
	 //and set the initiatial Error variable

   endEffector->getGlobalPosition(EEpos);       
   getGoal(target);
   j->changeToLocal(localTarget,target);
   j->changeToLocal(localEE,EEpos);
  

   double ortho1[3]; //orthonormal vectors in the plane defined by the axis of the joint
   double ortho2[3];

   //find orthagonal vectors
   //by finding the cross product of the x and y axi and the  rotational axis
   double axis[3];
   j->getAxis(axis);

   // check to make sure the axis of rotation is not aligned with the x axis
   if((fabs(axis[1]) < 1.0e-8) && (fabs(axis[2]) < 1.0e-8)){
     utilVector[0] = 0;
     utilVector[1] = 0;
     utilVector[2] = 1;
   }
   else{
     utilVector[0] = 1;
     utilVector[1] = 0;
     utilVector[2] = 0;
   }
   VecCrossProd(ortho1,axis,utilVector);
   if(VecLength(ortho1) < 1.0e-8){return 42.1;}
   VecNormalize(ortho1);

	 //check to make sure the axis of rotation is not aligned with the y axis
   if((fabs(axis[0]) < 1.0e-8) && (fabs(axis[2]) < 1.0e-8)){
     utilVector[0] = 0;
     utilVector[1] = 0;
     utilVector[2] = 1;
   }
   else{
     utilVector[0] = 0;
     utilVector[1] = 1;
     utilVector[2] = 0;
   }
   VecCrossProd(ortho2,axis,utilVector);
   if(VecLength(ortho2) < 1.0e-8){return 42.2;}
   VecNormalize(ortho2);

   //danceTcl::OutputMessage("ortho 1 %lf %lf %lf",ortho1[0],ortho1[1],ortho1[2]);
   //danceTcl::OutputMessage("ortho 2 %lf %lf %lf",ortho2[0],ortho2[1],ortho2[2]);
   double targetProj[3];
   double endProj[3];

   double c1 = VecDotProd(ortho1,localTarget);
   double c2 = VecDotProd(ortho2,localTarget);
   targetProj[0] = c1*ortho1[0]+c2*ortho2[0];
   targetProj[1] = c1*ortho1[1]+c2*ortho2[1];
   targetProj[2] = c1*ortho1[2]+c2*ortho2[2];
   if(VecLength(targetProj) < 1.0e-8){return 0;}//if target is aligned with axis, then no rotation will help

   c1 = VecDotProd(ortho1,localEE);
   c2 = VecDotProd(ortho2,localEE);
   endProj[0] = c1*ortho1[0]+c2*ortho2[0];
   endProj[1] = c1*ortho1[1]+c2*ortho2[1];
   endProj[2] = c1*ortho1[2]+c2*ortho2[2];
   if(VecLength(endProj) == 0){return 0;}//if endEffector is aligned with axis, then no rotion will help

   VecCrossProd(utilVector,endProj,targetProj);
   double E = VecLength(endProj);
   double T = VecLength(targetProj);
   double sinTheta = VecLength(utilVector)/T/E;       
   if(VecDotProd(utilVector,axis) > 0){sinTheta = -sinTheta;}
 
  if(!((sinTheta < 0) ||(sinTheta >= 0))){
    danceTcl::OutputMessage("ouch in opitize code, caused by bad final angle calcualtion");
    danceTcl::OutputMessage("localEE %lf %lf %lf",localEE[0],localEE[1],localEE[2]);
    danceTcl::OutputMessage("endProj %lf %lf %lf",endProj[0],endProj[1],endProj[2]);
    danceTcl::OutputMessage("localTarget %lf %lf %lf",localTarget[0],localTarget[1],localTarget[2]);
    danceTcl::OutputMessage("targetProj %lf %lf %lf",targetProj[0],targetProj[1],targetProj[2]);
    danceTcl::OutputMessage("ouch");  
    char ch = getchar();
  }
  return -sinTheta*T*E/2*j->distance(EEpos,target);
}  

//returns the optimal addition to the variable of the joint
 // target is given in global (root) co-ordinate system
 //assumes all matrices are up to date
double posConstraint::optimize(IK_Joint *j, double &errorCoefficient){
   double utilVector[3];//handy variable
   double localTarget[3];//target from the joints reference frame
   double localEE[3];//end effector from the joints reference frame
   double target[3]; 
   double initialError;
   double finalError;
   double EEpos[3];     

   j->updateInverse();

   //find the co-ordinates in the joints referce frame
	 //and set the initiatial Error variable

   endEffector->getGlobalPosition(EEpos);       
   getGoal(target);
   j->changeToLocal(localTarget,target);
   j->changeToLocal(localEE,EEpos);
   initialError =  errorFunction(); 

   double ortho1[3]; //orthonormal vectors in the plane defined by the axis of the joint
   double ortho2[3];

   //find orthagonal vectors
   //by finding the cross product of the x and y axi and the  rotational axis
   double axis[3];
   j->getAxis(axis);

   // check to make sure the axis of rotation is not aligned with the x axis
   if((fabs(axis[1]) < 1.0e-8) && (fabs(axis[2]) < 1.0e-8)){
     utilVector[0] = 0;
     utilVector[1] = 0;
     utilVector[2] = 1;
   }
   else{
     utilVector[0] = 1;
     utilVector[1] = 0;
     utilVector[2] = 0;
   }
   VecCrossProd(ortho1,axis,utilVector);
   if(VecLength(ortho1) < 1.0e-8){return 42.1;}
   VecNormalize(ortho1);

	 //check to make sure the axis of rotation is not aligned with the y axis
   if((fabs(axis[0]) < 1.0e-8) && (fabs(axis[2]) < 1.0e-8)){
     utilVector[0] = 0;
     utilVector[1] = 0;
     utilVector[2] = 1;
   }
   else{
     utilVector[0] = 0;
     utilVector[1] = 1;
     utilVector[2] = 0;
   }
   VecCrossProd(ortho2,axis,utilVector);
   if(VecLength(ortho2) < 1.0e-8){return 42.2;}
   VecNormalize(ortho2);

   //danceTcl::OutputMessage("ortho 1 %lf %lf %lf",ortho1[0],ortho1[1],ortho1[2]);
   //danceTcl::OutputMessage("ortho 2 %lf %lf %lf",ortho2[0],ortho2[1],ortho2[2]);
   double targetProj[3];
   double endProj[3];

   double c1 = VecDotProd(ortho1,localTarget);
   double c2 = VecDotProd(ortho2,localTarget);
   targetProj[0] = c1*ortho1[0]+c2*ortho2[0];
   targetProj[1] = c1*ortho1[1]+c2*ortho2[1];
   targetProj[2] = c1*ortho1[2]+c2*ortho2[2];
   if(VecLength(targetProj) < 1.0e-8){errorCoefficient=0;return 0;}//if target is aligned with axis, then no rotation will help

   c1 = VecDotProd(ortho1,localEE);
   c2 = VecDotProd(ortho2,localEE);
   endProj[0] = c1*ortho1[0]+c2*ortho2[0];
   endProj[1] = c1*ortho1[1]+c2*ortho2[1];
   endProj[2] = c1*ortho1[2]+c2*ortho2[2];
   if(VecLength(endProj) == 0){errorCoefficient =0 ;return 0;}//if endEffector is aligned with axis, then no rotion will help


   VecCrossProd(utilVector,endProj,targetProj);
   double deltaAng = VecLength(utilVector)/VecLength(endProj)/VecLength(targetProj);       

   deltaAng = asin(deltaAng);
   if(VecDotProd(utilVector,axis) < 0){deltaAng = -deltaAng;}


  double a = VecDotProd(localEE,axis)*VecDotProd(localTarget,axis);
  double d1 = j->distance(endProj, localEE);
  double d2 = j->distance(targetProj, localTarget);
  if(a >= 0){finalError = fabs(d1 - d2);}
  else{finalError = fabs(d1+d2);}
  
  a  = fabs(VecLength(endProj)-VecLength(targetProj));
  finalError = sqrt(a*a+finalError*finalError);
  //danceTcl::OutputMessage("initial error %lf final error %lf",initialError,finalError);

  
  if(finalError != 0){errorCoefficient = (initialError/finalError);}
  else{errorCoefficient = 1000000;}
  errorCoefficient = errorCoefficient*errorCoefficient;
  
  
  if(!((deltaAng < 0) ||(deltaAng >= 0))){
    danceTcl::OutputMessage("ouch in opitize code, caused by bad final angle calcualtion");
    danceTcl::OutputMessage("localEE %lf %lf %lf",localEE[0],localEE[1],localEE[2]);
    danceTcl::OutputMessage("endProj %lf %lf %lf",endProj[0],endProj[1],endProj[2]);
    danceTcl::OutputMessage("localTarget %lf %lf %lf",localTarget[0],localTarget[1],localTarget[2]);
    danceTcl::OutputMessage("targetProj %lf %lf %lf",targetProj[0],targetProj[1],targetProj[2]);
    danceTcl::OutputMessage("ouch");  
    char ch = getchar();
  }
        return deltaAng;
}       

/**
 * Updates the goal field
 * 
 * @param DView *focus
 * @param int button The buttonID of button thats down.  Not used currently
 * @param int x, int y
 * @param int diffX, int diffY
 * @param int width, int height
 * @param Link * root
 * @return void
 */
void posConstraint::HandleConstraintEdit(DView *focus, int button, int x, int y, int diffY, int diffX, 
					 int width, int height, Link * root)
{
   // danceTcl::OutputMessage("HandleConstraintEdit called");
 
    GLdouble win[3], jpos[3];
    double utilVec[3];
    getGoal(utilVec);
    root->getWorldCoord(jpos,utilVec);
    focus->getWindowCoords(jpos,win);
    focus->getWorldCoords(jpos,x, y, win[2]);
    //event->Window->getWorldCoords(jpos,event->winX, event->winY, -1); 
    root->getLocalCoord(utilVec,jpos);
    setGoal(utilVec);
    
}

/**
 *displays the constraint endEffector position and goal position using spheres
 *
 * @param double baseMat[4][4] the trasformation matrix of the root joint
 * @param double the radius of the spheres displayed
 * @return void
 */
void posConstraint::display(double baseMat[4][4], double radius){
  glPushName(constraintNumber);
  //mark end effector
 
  glLineWidth(2.0);
  glPushMatrix();
  glMultMatrixd((GLdouble *)((Link *)realEndEffector)->m_transMat);
  if(highlight == TRUE){glColor3f(0.0f,0.7f,0.7f);}
  else{glColor3f(0.0f,0.7f,0.0f);}
  
  glutSolidSphere(radius*0.5,5,5);
  glPopMatrix();
  
  //draw goal
  glPushMatrix();
  glMultMatrixd((GLdouble *)baseMat);
  glTranslatef(goal[0],goal[1],goal[2]);
   
  if(highlight == TRUE){glColor3f(0.7f,0.0f,0.0f);}
  else{glColor3f(0.7f,0.0f,0.0f);}
  glutSolidSphere(radius,5,5);
  
  glPopMatrix();
  glPopName();
}


BoundingBox *posConstraint::calcBoundingBox(BoundingBox &b, Link *r){
  double min[3];
  double max[3];
  r->getWorldCoord(min,goal); 
  r->getWorldCoord(max,goal);
  b.xMin = min[0] - 0.04;
  b.yMin = min[1] - 0.04;
  b.zMin = min[2] - 0.04;
  b.xMax = max[0] + 0.04;
  b.yMax = max[1] + 0.04;
  b.zMax = max[2] + 0.04;

  return &b ;
}


























