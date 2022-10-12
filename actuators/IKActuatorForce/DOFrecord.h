
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


#ifndef	_DOFrecord_h_
#define	_DOFrecord_h_


#include "list.h"

class storageClass;
class IK_Joint;

class DOFrecord : public storageClass {

private:
	IK_Joint *j[3];
	int parentJointNumber;
	int root;
       
public:	
        
        DOFrecord();
	~DOFrecord();
	IK_Joint *getIKjoint(int dof);
	void setIKjoint(int dof, IK_Joint *ikJ);
	void setJointNumber(int n);
	int getJointNumber(void);
	int isRoot(void){return root;}
        int isReversed;
        int numIKjoints;
        double weight;
	void setRoot(int r){root =r;}
        DOFrecord *find(int jointNum);
        void add(DOFrecord *rec);
        void linkJoints(void);
        void linkTo(DOFrecord *nextRec);
        void reverse(void);      
};
#endif






