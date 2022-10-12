
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



#ifndef	_PosConstraint_h_
#define	_PosConstraint_h_

#define Position_Goal 1
#define Orientation_Goal 2

#include "list.h"
#include "IKconstraint.h"
class IK_Joint;
class DanceObject;
class BoundingBox;
class Link;
class DView;

class posConstraint : public IKconstraint{

public:
        posConstraint(int num);
        void initGoal(void);
        double errorFunction(void);
        void display(double baseMat[4][4], double radius);
        double derivative(IK_Joint *j);
        double optimize(IK_Joint *j, double &errorCoefficient);
        void HandleConstraintEdit(DView *focus, int button, int x, int y, int diffX, int diffY,
					  int width, int height, Link *root);
        BoundingBox *calcBoundingBox(BoundingBox &b, Link *r);
};

#endif

















