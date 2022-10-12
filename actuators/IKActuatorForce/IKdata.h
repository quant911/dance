
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


#ifndef	_IKdata_h_
#define	_IKdata_h_

#include "list.h"

class IK_Joint;
class list;
class IKconstraint;

class IKdata: public storageClass{
    
public:
        IKdata();
        ~IKdata();
        IK_Joint *joint;
        list *constraints;
        void addConstraint(IKconstraint *c);
        int numConstraints;
};

#endif







