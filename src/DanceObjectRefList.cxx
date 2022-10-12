#include "defs.h"
#include "danceTcl.h"
#include "DanceObjectRefList.h"
#include <stdlib.h>
#include <GL/gl.h>

#define	BINSIZE	10

DanceObjectRefList::DanceObjectRefList()
{
	numDanceObjects	= 0;
	numDanceBins = BINSIZE;

	// Initialize plugin list.
	DanceObjects = (DanceObject **)malloc(sizeof(DanceObject *)*numDanceBins);
}

DanceObjectRefList::~DanceObjectRefList()
{
    return ;
}

// add:
//	Adds an	object to the list and set it as the active one.
int DanceObjectRefList::add(DanceObject *obj)
{
	if (obj) {
		if (numDanceObjects == numDanceBins) {
		  numDanceBins += BINSIZE;
		  DanceObject **temp =
		  (DanceObject **)malloc(sizeof(DanceObject *)*numDanceBins);
		  memcpy(temp,DanceObjects,
			numDanceObjects	* sizeof(DanceObject *));
		  free(DanceObjects);
		  DanceObjects = temp;
		}
		DanceObjects[numDanceObjects] = obj;
		numDanceObjects++;
	}
	else {
		danceTcl::OutputMessage("ERROR: add, passed in NULL pointer.");
		return(0);
	}
	return(1);

}

int DanceObjectRefList::remove(int	index)
{
	// Find	object at this index.
	DanceObject *obj = get(index);

	if (obj) {
	   // Now shift	over all items down one.
	   for (int i =	index+1; i < numDanceObjects; i++)
		DanceObjects[i-1] = DanceObjects[i];
	   DanceObjects[numDanceObjects-1] = NULL;
	   numDanceObjects--;
	   return(1);
	}
	return(0);
}

int DanceObjectRefList::remove(char *name)
{
	// Find	object at this index.
	int index = getIndex(name);
	return(remove(index));
}

DanceObject *DanceObjectRefList::get(int index)
{
	if (index < 0 || index >= numDanceObjects)
		return NULL;
	return (DanceObjects[index]);
}


// get:	Returns	plugin by name
//
DanceObject *DanceObjectRefList::get(char *name)
{
	DanceObject *obj = NULL;
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getName(),name) == 0) {
			obj = DanceObjects[i];
			break;
		}
	}

	return(obj);
}

// getIndex: returns index, given name.
//
int DanceObjectRefList::getIndex(char *name)
{
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getName(),name) == 0)
			return(i);
	}
	return(-1);
}

