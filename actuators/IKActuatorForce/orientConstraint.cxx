
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
#include "orientConstraint.h"
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

orientConstraint::orientConstraint(int num){
    constraintNumber = num;
    isGlobalyPositioned = TRUE; //if the contriant is not globally positioned, then when the simulator
    // moves the root, then  the goals move with it
    weight = 1;
    endEffector = NULL;
    realEndEffector = NULL;
    highlight = FALSE;
}

/**
 * Sets the goal to where the endEffector is already
 *
 * @param void
 * @return void
 */
void orientConstraint::initGoal(void){
  endEffector->getAxis(goal);
}

/**
 * Returns the derivative of the constraint errorFunction with respect to the variable of j
 *
 * @param IK_Joint *j
 * @return double
 */
double orientConstraint::derivative(IK_Joint *j){
   double utilVector[3];//handy variable
   double localTarget[3];//target from the joints reference frame
   double localEE[3];//end effector from the joints reference frame
   double target[3];
   double EEpos[3];     

   j->updateInverse();

   endEffector->getAxis(utilVector);
   endEffector->rotateToGlobal(EEpos,utilVector);       
   getGoal(target);
   j->rotateToLocal(localTarget,target);
   j->rotateToLocal(localEE,EEpos);
   VecNormalize(localTarget);
   VecNormalize(localEE);

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
    danceTcl::OutputMessage("targetProj %lf %lf %lf",targetProj[0],targetProj[1],targetProj[2]);
    danceTcl::OutputMessage("ouch");  
    char ch = getchar();
  }
  double d = j->distance(localEE,localTarget);
  if(fabs(d) < 1e-8){
    return -sinTheta*T*E;}
  else{
    return -sinTheta*T*E/d/sin(acos(d/2));
  } 
}

/**
 *Returns the angle in radians between the goal vector and the end effectors axis
 *
 * @param void
 * @return double
 */
double orientConstraint::errorFunction(void){
  double ax[3]; double vec[3];
  endEffector->getAxis(vec);
  endEffector->rotateToGlobal(ax,vec);
                   
  double d;
  d = VecDotProd(ax,goal)/VecLength(goal)/VecLength(ax);
  if(d>1.0){d=1.0;}
  else if(d<-1.0) {d =-1.0;}
  return acos(d);
}


/**
 *returns the difference between the current variable of j and its optimum position with respect the errorFuntion
 *of the constraint
 *
 * @param IK_Joint *j
 * @param double &errorCoefficient is set by the proc to the (inital errorFunction)/(final errorFunction)
 * @return double
 */
double orientConstraint::optimize(IK_Joint *j, double &errorCoefficient){
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
  endEffector->getAxis(utilVector);
  endEffector->rotateToGlobal(EEpos,utilVector);       
  getGoal(target);
  j->rotateToLocal(localTarget,target);
  j->rotateToLocal(localEE,EEpos);
  //initialError =  j->distance(localEE,localTarget); 
  initialError = errorFunction();
  
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
   double targetProj[3]; // the projection of the target onto the plane of the axis
   double endProj[3]; //the projection of the endEffector

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
   if(VecLength(endProj) < 1.0e-8 ){errorCoefficient =0 ;return 0;}//if endEffector is aligned with axis, then no rotion will help

   //danceTcl::OutputMessage("endProj %lf %lf %lf",endProj[0],endProj[1],endProj[2]);
   //danceTcl::OutputMessage("targetProj %lf %lf %lf",targetProj[0],targetProj[1],targetProj[2]);
   VecCrossProd(utilVector,endProj,targetProj);
   double deltaAng = VecLength(utilVector)/VecLength(endProj)/VecLength(targetProj);       
   deltaAng = asin(deltaAng);
   if(VecDotProd(utilVector,j->axis) < 0){deltaAng = -deltaAng;}

  double a = VecDotProd(localEE,axis)*VecDotProd(localTarget,axis);
  double d1 = VecDotProd(endProj, localEE)/VecLength(endProj)/VecLength(localEE);
  if(d1 > 1){d1 = 1.0;} if(d1 < -1){d1 = -1.0;}
  d1 = acos(d1);
  double d2 = VecDotProd(targetProj,localTarget)/VecLength(targetProj)/VecLength(localTarget);
  if(d2 > 1){d2 = 1.0;} if(d2 < -1){d2 = -1.0;}
  d2 = acos(d2);
  if(a >= 0){finalError = fabs(d1 - d2);}
  else{finalError = fabs(d1+d2);}
  //finalError = 1;

 
  //danceTcl::OutputMessage("initial error %lf final error %lf",initialError,finalError);
  
  if(finalError != 0){errorCoefficient = (initialError/finalError);}
  else{errorCoefficient = 1000000;} // if final error is zero set the erroCoefficient to a large number
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
 * Updates the goal field based on mouse movement
 * 
 * @param DView *focus
 * @param int button The buttonID of button thats down
 * @param int x, int y
 * @param int diffX, int diffY
 * @return void
 */
void orientConstraint::HandleConstraintEdit(DView *focus, int button, int x, int y, int diffX, int diffY, int width, int height, Link * root)
{
   // danceTcl::OutputMessage("HandleConstraintEdit called");
    double utilVec[3],jpos[3];
    getGoal(utilVec);
    Quaternion q;
    double a[3];
	danceTcl::OutputMessage("button id %d",button);
	switch(button){
	case GLUT_LEFT_BUTTON:
	  a[0]=0;a[1]=1;a[2]=0; //rotate on y axis
	  break;
	case GLUT_RIGHT_BUTTON:
	  a[0]=0;a[1]=0;a[2]=1; //rotate on z axis
	break;
	}
	if(dance::m_ModifierKey ==GLUT_ACTIVE_SHIFT) {//rotate axis instead of goal
	  danceTcl::OutputMessage("shift on");
	  q.set(diffX*0.04,a);
          endEffector->updateInverse();
          endEffector->getAxis(utilVec);
          endEffector->rotateToGlobal(jpos,utilVec);
          double mat[3][3];
          q.toMatrix(mat);
	  for(int i=0; i<3; i++){
	    jpos[i]=mat[i][0]*utilVec[0]+mat[i][1]*utilVec[1]+mat[i][2]*utilVec[2];
	  }
          endEffector->rotateToLocal(utilVec,jpos);
          endEffector->setAxis(utilVec);
	}
	else{
	  q.set(diffX*0.04,a);
	  double mat[3][3];
	  q.toMatrix(mat);
	  for(int i=0; i<3; i++){
	    jpos[i]=mat[i][0]*utilVec[0]+mat[i][1]*utilVec[1]+mat[i][2]*utilVec[2];
	  }
	  setGoal(jpos);
    }
}
/**
 *displays the constraint endEffector axis and goal axis
 *
 * @param double baseMat[4][4] the trasformation matrix of the root joint
 * @param double radius the length of the axis is global coordinates
 * @return void
 */
void orientConstraint::display(double baseMat[4][4], double radius){
  glPushName(constraintNumber);
  //mark end effector
 
  glLineWidth(2.0);
  glPushMatrix();
  glMultMatrixd((GLdouble *)((Link *)realEndEffector)->m_transMat);
  //glMultMatrixd((GLdouble *)endEffector->globalTransform);
  if(highlight == TRUE){glColor3f(0.0f,0.7f,0.7f);}
  else{glColor3f(0.0f,0.7f,0.0f);}
  
  displayAxis(endEffector->axis,radius*2);
   //glutSolidSphere(radius*0.5,5,5);
  glPopMatrix();
  
  //draw goal
  glPushMatrix();
  glMultMatrixd((GLdouble *)baseMat);
  double vec[3];
  endEffector->getGlobalPosition(vec);
  glTranslatef(vec[0],vec[1],vec[2]);
   
  if(highlight == TRUE){glColor3f(0.7f,0.0f,0.0f);}
  else{glColor3f(0.7f,0.0f,0.0f);}
  displayAxis(goal,radius*2.5);
  
  glPopMatrix();
  glPopName();
}
/**
 * Draws an arrow
 * @param double axis[3]
 * @param double length
 * @return void
 */
void orientConstraint::displayAxis(double axis[3],	double length){
  double point[3]; point[0] =	0.0; point[1] =	0.0; point[2] =	0.0;
    GLdrawVector(point,	axis, length);
}



BoundingBox *orientConstraint::calcBoundingBox(BoundingBox &b, Link *r){
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




























































