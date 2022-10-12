
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


#ifndef	_IKassembler_h_
#define	_IKassembler_h_


#include "IK_Joint.h"
#include "list.h"
#include <assert.h>

#define MAX_CONSTRAINTS 10

class list;
class IK_Joint;

class IKassembler{

private:
  //list *joints;
                
public:
    list *joints;
    IK_Joint *root;	
    IKassembler();
    ~IKassembler();
    list *allConstraints;
    void addConstraint(IKconstraint *newC);
    void removeConstraint(IKconstraint *c,int *delJoints,int &numDelJoints);
    void addJoint(IK_Joint *j);
    void printJointStructure(void);
    void printJoint(IK_Joint *ikJ);
    void display(double baseMat[4][4],double rad);
	double rand(double &lastnum, double range);
    void solve(int mode);
    double errorFunction(void);
    int numJoints;
    int numConstraints;
  
    
};
#endif














