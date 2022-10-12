
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


#ifndef	_IK_Joint_h_
#define	_IK_Joint_h_ 1

#include "defs.h"//used when including  any classes used in another DLL !!!!!!!!
#include "Quaternion.h"
#include <assert.h>
#include "IKconstraint.h"

#define MAX_CHILDREN 10

class DOFrecord;
class IK_Joint{
  
private:

  IK_Joint *lastJoint;
  IK_Joint *childJoint[MAX_CHILDREN]; 
  int numChildren;
  Quaternion q;
  
  double ang;
  double lowerLim;
  double upperLim;
  double globalInverse[4][4]; 
 
	
public:	
  double localTransform[4][4];
  double globalTransform[4][4];
  double axis[3];
  IK_Joint();
  ~IK_Joint();
  int getNumChildren(void){return numChildren;}
  int jointNumber;// two joints may have the same number if they are copies of each other
  int endEffectorMark;
  DOFrecord *rec;
  void AET(double &a, double &e, double &t);
  int isEndEffector(void);
  void setAxis(double a[3]);
  void getAxis(double a[3]);
  void setVariable(double value);
  double getVariable(void);
  void getLocalPosition(double p[3]);
  void setLocalPosition(double p[3]);
  void getGlobalPosition(double p[3]);
  void updateLocalTransform(void);
  void moveJoint(void);
  IK_Joint *getParentJoint(void){return lastJoint;}
  IK_Joint *getChildJoint(int n){assert(n >= 0 && n < numChildren); return childJoint[n];}
  void setParentJoint(IK_Joint *p){lastJoint = p;}
  void addChildJoint(IK_Joint *c){assert(numChildren < MAX_CHILDREN); childJoint[numChildren] = c; numChildren++;}
  void removeChildJoint(IK_Joint *c);
  void getGlobalMat(double m[4][4]);
  void setLimits(double l, double u){lowerLim = l; upperLim = u;}
  void getLimits(double &l ,double &u){l = lowerLim; u = upperLim;}
  void multiplyMatrices(double a[4][4],double b[4][4], double result[4][4]);
  double distance(double p1[3],double p2[3]);
  double optimize(IKconstraint *c, double &errorCoefficient);
  int isChildOf(IK_Joint *j);
  void display(double baseMat[4][4], double rad);
  void rotateToGlobal(double global[3], double local[3]);
  void updateInverse(void);        
  void changeToLocal(double local[3], double global[3]);
  void rotateToLocal(double local[3], double global[3]);
  double getWeight(void);
  void resetQuat(void);
};
#endif




















