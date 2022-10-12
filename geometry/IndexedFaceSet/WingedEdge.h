#ifndef _WINGEDEDGE_H_
#define _WINGEDEDGE_H_

class WingedEdge {
public:
	// Vertices are ordered from a counter-clockwise direction.
	int v1;
	int v2;

	// f1 is from the left of edge, f2 from the right when traversing
	// the edge from v1 to v2
	int f1;
	int f2;

};

#endif
