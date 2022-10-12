
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
#include "math.h"
#include "myMath.h"
#include "IK_Joint.h"
#include "vector.h"
#include "IKconstraint.h"
#include "stddef.h"
#include <assert.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLutilities.h"
#include "danceTcl.h"
#include "DOFrecord.h"
#include <stdio.h>

 

 #include "Quaternion.h"
 // Currently set up using all radian input and output!!!!!!!


 // Default constructor and initializer for class IK_Joint
 IK_Joint::IK_Joint(){
   rec = NULL;
   endEffectorMark = FALSE;
   lastJoint = NULL;
   numChildren = 0;
   for(int i=0; i<4; i++)
     for(int j=0; j<4; j++){
       localTransform[i][j]=0;
       globalTransform[i][j]=0;
     }
   localTransform[0][0]=localTransform[1][1]=localTransform[2][2]=localTransform[3][3]=1;
   globalTransform[0][0]=globalTransform[1][1]=globalTransform[2][2]=globalTransform[3][3]=1;
   axis[0] = 1;
   axis[1] = 0;
   axis[2] = 0;
   ang = 0;
 }

 // removes the joint , but not its children
 IK_Joint::~IK_Joint(){
   if(lastJoint != NULL){lastJoint->removeChildJoint(this);}
   int i;
   for(i=0; i<numChildren; i++){
     childJoint[i]->setParentJoint(NULL);
   }

 }

 void IK_Joint::removeChildJoint(IK_Joint *c){
    int i=-1;
    int found=FALSE;

    while(found == FALSE && i < numChildren-1){
      i++;
      if(childJoint[i] == c){
	found = TRUE; 
      }     
    }
    int j;
    for(j=i; j<numChildren-1; j++){
       childJoint[j]=childJoint[j+1];
    }
    if(found == TRUE){numChildren--;}
    else{danceTcl::OutputMessage("IK_Joint::removeChildJoint-joint is not a child of this joint, cannot be removed");}
 }

 int IK_Joint::isEndEffector(void){return endEffectorMark;}
 /****************************************************************************************
 //multiply the transformation matrices down the chain until you get to the endEffector;
 //the result can be used to determine the position of the endEffector
 //the initial call must pass an identity matrix to getEndMatrix

 void IK_Joint::getEndMatrix(double mat[4][4]){
	 int i ;
	 double newMat[4][4];
	 //can be refined to make the multiplication more efficient re: 1's and 0's that don't change
	 //check matrix routines for help
	 for( i = 0 ; i < 4 ; i++) {
		 for( int j = 0 ; j < 4 ; j++) {
		     newMat[i][j] = mat[i][0]*localTransform[0][j]+mat[i][1]*localTransform[1][j]+mat[i][2]*localTransform[2][j]+mat[i][3]*localTransform[3][j];
		 }
	 }
	 for( i = 0 ; i < 4 ; i++) {
		 for( int j = 0 ; j < 4 ; j++) {
		     mat[i][j] = newMat[i][j];
		 }
	 }	
	 if(endEffectorMark == FALSE){nextJoint->getEndMatrix(mat); }	
 }
 **********************************************************************************************/


 //does not update local transform or global transform;
 void IK_Joint::setAxis(double a[3]){
   axis[0] = a[0];
   axis[1] = a[1];
   axis[2] = a[2];
   q.set(ang,a);
   //q.calcAzimElevTwist;
 }
 void IK_Joint::resetQuat(void){

 }

void IK_Joint::getAxis(double a[3]){
   a[0]=axis[0];a[1]=axis[1];a[2]=axis[2];    
 }

void IK_Joint::setVariable(double inputAngle){
	 ang = inputAngle;

	 if(ang>upperLim) {ang = upperLim;}
	 if(ang<lowerLim) {ang = lowerLim;}

	 double quatAngle;
	 if (inputAngle < 0 ){ quatAngle = M_PI*2+inputAngle;}
	 if (inputAngle < 0 ){ quatAngle = M_PI*2+inputAngle;}
	 else {quatAngle = inputAngle;}        
	 q.set(quatAngle,axis);
	 updateLocalTransform();
}
void IK_Joint::AET(double &a, double &e, double &t){
    double x = axis[0];
    double y = axis[2];
    double azim = acos(x/sqrt(x*x+y*y));
    double elev = acos(axis[1]/sqrt(axis[2]*axis[2]+axis[1]*axis[1]));
    a = azim;
    e =elev;
    t= ang;
}
double IK_Joint::getVariable(void){
  return ang;
}

 //position is relative to the parent joints reference frame
 void IK_Joint::getLocalPosition(double p[3]){
	 p[0] = localTransform[3][0];
	 p[1] = localTransform[3][1];
	 p[2] = localTransform[3][2];
 }

 void IK_Joint::setLocalPosition(double p[3]){
	 localTransform[3][0] = p[0];
	 localTransform[3][1] = p[1];
	 localTransform[3][2] = p[2];
 }

 void IK_Joint::getGlobalPosition(double p[3]){
	 p[0] = globalTransform[3][0];
	 p[1] = globalTransform[3][1];
	 p[2] = globalTransform[3][2];
 }

 // changes the local transform;
 void IK_Joint::updateLocalTransform(void){
	 double p[3]; //position

	 p[0] = localTransform[3][0];
	 p[1] = localTransform[3][1];
	 p[2] = localTransform[3][2];

	 q.toMatrix(localTransform);
      
	 localTransform[3][0] = p[0];
	 localTransform[3][1] = p[1];
	 localTransform[3][2] = p[2];

 }

 // updates the global positions of the joint and all child joints
 // this replaces the getEndMatrix routine


 void IK_Joint::moveJoint(void){
	 if (lastJoint != NULL){  //update the global matrix of this joint
		 double lastMat[4][4];
		 lastJoint->getGlobalMat(lastMat);
		 multiplyMatrices(lastMat, localTransform, globalTransform);
	 }
	 else{ // the joint is the root; set the global matrix to the local matrix
		 for(int i=0; i<4; i++){
			 for(int j=0; j<4; j++){
				 globalTransform[i][j] = localTransform[i][j];
			 }
		 }
	 }
	 //move all child joints
	 int i;	
	 for(i=0; i < numChildren; i++){
	       childJoint[i]->moveJoint(); 
	 }	
 }


void IK_Joint::getGlobalMat(double m[4][4]){
	 for (int i =0; i<4; i++){
		 for (int j=0; j<4; j++){
			 m[i][j]=globalTransform[i][j];
		 }
	 }	
 }



void IK_Joint::multiplyMatrices(double b[4][4],double a[4][4], double result[4][4]){
  //double answer[4][4];
	 int i ;
	 for( i = 0 ; i < 4 ; i++) {
		 for( int j = 0 ; j < 4 ; j++) {
		     result[i][j] = a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j]+a[i][3]*b[3][j];
		 }
	 }
	
 }



 //returns the optimal addition to the variable of the joint
 // target is given in global (root) co-ordinate system
 //assumes all matrices are up to date
 double IK_Joint::optimize(IKconstraint *c, double &errorCoefficient){
   double utilVector[3];//handy variable
   double localTarget[3];//target from the joints reference frame
   double localEE[3];//end effector from the joints reference frame
   double target[3]; 
   double initialError;
   double finalError;
   double endEffector[3];     

   updateInverse();

   //find the co-ordinates in the joints referce frame
	 //and set the initiatial Error variable

   c->endEffector->getGlobalPosition(endEffector);       
   c->getGoal(target);
   changeToLocal(localTarget,target);
   changeToLocal(localEE,endEffector);
   initialError =  distance(localEE,localTarget); 



   double ortho1[3]; //orthonormal vectors in the plane defined by the axis of the joint
   double ortho2[3];

   //find orthagonal vectors
   //by finding the cross product of the x and y axi and the  rotational axis

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
  double d1 = distance(endProj, localEE);
  double d2 = distance(targetProj, localTarget);
  if(a >= 0){finalError = fabs(d1 - d2);}
  else{finalError = fabs(d1+d2);}
 

	
	
  if(initialError != 0){errorCoefficient = (initialError-finalError)/initialError;}
  else{errorCoefficient = 0;}
  
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


void IK_Joint::updateInverse(void){
        invSmart4(globalInverse,globalTransform);
}


void IK_Joint::changeToLocal(double local[3], double global[3]){
	
        local[0] = global[0]*globalInverse[0][0]+global[1]*globalInverse[1][0]+global[2]*globalInverse[2][0]+globalInverse[3][0];
        local[1] = global[0]*globalInverse[0][1]+global[1]*globalInverse[1][1]+global[2]*globalInverse[2][1]+globalInverse[3][1];
	local[2] = global[0]*globalInverse[0][2]+global[1]*globalInverse[1][2]+global[2]*globalInverse[2][2]+globalInverse[3][2];
	
}

void IK_Joint::rotateToLocal(double local[3], double global[3]){
  local[0] = global[0]*globalInverse[0][0]+global[1]*globalInverse[1][0]+global[2]*globalInverse[2][0];
  local[1] = global[0]*globalInverse[0][1]+global[1]*globalInverse[1][1]+global[2]*globalInverse[2][1];
  local[2] = global[0]*globalInverse[0][2]+global[1]*globalInverse[1][2]+global[2]*globalInverse[2][2];
}

//use forward multiplication
void IK_Joint::rotateToGlobal(double global[3], double local[3]){
  global[0] = local[0]*globalTransform[0][0]+local[1]*globalTransform[1][0]+local[2]*globalTransform[2][0];
  global[1] = local[0]*globalTransform[0][1]+local[1]*globalTransform[1][1]+local[2]*globalTransform[2][1];
  global[2] = local[0]*globalTransform[0][2]+local[1]*globalTransform[1][2]+local[2]*globalTransform[2][2];
}

int IK_Joint::isChildOf(IK_Joint *j){
  if(lastJoint == NULL){return FALSE;}
  else if(lastJoint == j || this == j){return TRUE;}
  else{return lastJoint->isChildOf(j);}
}
 


void IK_Joint::display(double baseMat[4][4],double rad){
  glLineWidth(2.0);
  glPushMatrix();
  glMultMatrixd((GLdouble *)baseMat);
  double pos[3];
  getGlobalPosition(pos);
  glTranslated(pos[0],pos[1],pos[2]);
  //danceTcl::OutputMessage("joint position %lf %lf %lf",pos[0],pos[1],pos[2]);
  glColor3f(0.0f,0.0f,0.7f);
  GLUquadricObj *sphr = gluNewQuadric();
  gluSphere(sphr,rad,5,5);
  glPopMatrix();
}

double IK_Joint::distance(double p1[3], double p2[3]){
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1])+(p1[2]-p2[2])*(p1[2]-p2[2]));   
}

double IK_Joint::getWeight(void){
  if(rec == NULL){return 1.0;}
  else{return rec->weight;}
}


























