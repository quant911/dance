
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
#include "IKconstraint.h"
#include <stddef.h>
#include "defs.h"
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

IKconstraint::IKconstraint(int num){
    constraintNumber = num;
    isGlobalyPositioned = TRUE;
    weight = 1;
    endEffector = NULL;
    realEndEffector = NULL;
    highlight = FALSE;
}
IKconstraint::IKconstraint(void){
    constraintNumber = -1;
    isGlobalyPositioned = TRUE;
    weight = 1;
    endEffector = NULL;
    realEndEffector = NULL;
    highlight = FALSE;
}

void IKconstraint::getGoal(double g[3]){
    g[0]=goal[0];
    g[1]=goal[1];
    g[2]=goal[2];
}
void IKconstraint::setGoal(double g[3]){
    goal[0]=g[0];
    goal[1]=g[1];
    goal[2]=g[2];
}

void IKconstraint::initGoal(void){
  endEffector->getGlobalPosition(goal);
}


BoundingBox *IKconstraint::calcBoundingBox(BoundingBox &b, Link *r){
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


























