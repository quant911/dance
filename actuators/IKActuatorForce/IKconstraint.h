
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



#ifndef	_IKconstraint_h_
#define	_IKconstraint_h_


#include "list.h"
class IK_Joint;
class DanceObject;
class BoundingBox;
class Link;
class DView;

class IKconstraint : public storageClass{
public:
   	double goal[3];
    IKconstraint();
	IKconstraint(int num);
    virtual void initGoal(void);
	int constraintNumber;
    int isGlobalyPositioned;
	double weight;
    void getGoal(double g[3]);
    void setGoal(double g[3]);
    IK_Joint *endEffector;
    virtual double errorFunction(void){return 0.0;}
    DanceObject *realEndEffector;
    virtual double optimize(IK_Joint *j, double &errorCoefficient){return 0.0;}
    virtual double derivative(IK_Joint *j){return 0.0;}
    virtual void HandleConstraintEdit(DView *focus, int button, int x, int y, int diffX, int diffY, 
	int width, int height, Link *root){}
    virtual void display(double baseMat[4][4], double radius){}
    int highlight;
    virtual BoundingBox *calcBoundingBox(BoundingBox &b, Link *r);
};

#endif

















