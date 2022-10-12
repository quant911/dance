/**************************************************************************
	----------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
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



#ifndef	_EVENT_H_
#define	_EVENT_H_ 1

class DView;

class Event {
public:
	DView *Window;
	int winDiffX, winDiffY;
	int winX, winY;
	int winWidth, winHeight;

	double winBasisX[3], winBasisY[3], winBasisZ[3];

	int buttonID;
	int buttonState;

	int pickNumber;
	int pickItem[256];

	inline void setWindow(DView *win, int x,	int y, int width, int height)
			{ Window = win;	winX = x; winY = y; winWidth = width; winHeight	= height; };
	inline void setWindowDiffs(int diffx, int diffy) { winDiffX = diffx; winDiffY =	diffy;};
	void setWindowBasis(double basisX[3], double basisY[3],	double basisZ[3])
			{ memcpy(winBasisX,basisX,3*sizeof(double));
			  memcpy(winBasisY,basisY,3*sizeof(double));
			  memcpy(winBasisZ,basisZ,3*sizeof(double)); };
	inline void setButtons(int ID, int state) { buttonID	= ID; buttonState = state; };
	void setSelected(int number, int item[256])
			{ pickNumber= number; memcpy(pickItem,item,256*sizeof(int));};
	int getSelected(int **item) { *item = pickItem; return (pickNumber); }; 
};
#endif
