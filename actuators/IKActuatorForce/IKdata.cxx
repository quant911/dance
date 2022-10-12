
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
#include "IKdata.h"
#include <stddef.h>
#include "IKconstraint.h"
#include "list.h"
#include "IK_Joint.h"


IKdata::IKdata(){
       constraints = new list; 
       joint=NULL; 
       numConstraints =0;
}
IKdata::~IKdata(){remove(); delete joint; delete constraints;}

void IKdata::addConstraint(IKconstraint *c){
    conStorage *con = new conStorage;
    con->constraint = c;
    constraints->add(con);
    numConstraints++;
}
