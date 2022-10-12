#include "defs.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include <stdlib.h>
#include <GL/gl.h>




#define	BINSIZE	10

DanceObjectList::DanceObjectList()
{
	numDanceObjects	= 0;
	numDanceBins = BINSIZE;
	Active = NULL;

	// Initialize plugin list.
	DanceObjects = (DanceObject **)malloc(sizeof(DanceObject *)*numDanceBins);
}

DanceObjectList::~DanceObjectList()
{
	for (int i=0; i	< numDanceObjects; i++)
		if (DanceObjects[i]) delete DanceObjects[i];
}

// add:
//	Adds an	object to the list and set it as the active one.
int DanceObjectList::add(DanceObject *obj)
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
		Active = DanceObjects[numDanceObjects] = obj;
		numDanceObjects++;
	}
	else {
		danceTcl::OutputMessage("ERROR: add, passed in NULL pointer.");
		return(0);
	}
	return(1);

}

int DanceObjectList::remove(int	index)
{
	// Find	object at this index.
	DanceObject *obj = get(index);

	if (obj) {
	   if (Active == obj) Active = NULL;
	   delete obj;

	   // Now shift	over all items down one.
	   for (int i =	index+1; i < numDanceObjects; i++)
		DanceObjects[i-1] = DanceObjects[i];
	   DanceObjects[numDanceObjects-1] = NULL;
	   numDanceObjects--;
	   return(1);
	}
	return(0);
}

int DanceObjectList::remove(char *name)
{
	// Find	object at this index.
	int index = getIndex(name);
	return(remove(index));
}


void DanceObjectList::output(int mode)
{
	glPushName((GLuint)-1);
	for (int i=0; i	< numDanceObjects; i++)	{
		glLoadName(i);
		DanceObjects[i]->output(mode);
	}
	glPopName();
}

void DanceObjectList::print(FILE *fptr)
{
	for (int i=0; i	< numDanceObjects; i++)
		DanceObjects[i]->print(fptr);
}

DanceObject *DanceObjectList::get(int index)
{
	if (index < 0 || index >= numDanceObjects)
		return NULL;
	return (DanceObjects[index]);
}


// get:	Returns	plugin by name
//
DanceObject *DanceObjectList::get(char *name)
{
	DanceObject *plugin = NULL;
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getName(),name) == 0) {
			plugin = DanceObjects[i];
			break;
		}
	}

	return(plugin);
}

// getIndex: returns index, given name.
//
int DanceObjectList::getIndex(char *name)
{
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getName(),name) == 0)
			return(i);
	}
	return(-1);
}

// Takes the name of the shared	object and finds the plugin
// The calling procedure has to	make sure that names
// are consistent!!

DanceObject *DanceObjectList::getByFileName(char *name)
{
	DanceObject *plugin = NULL;
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getFileName(),name)	== 0) {
			plugin = DanceObjects[i];
			break;
		}
	}

	return(plugin);
}

// setActive:
//	Sets the active	object.
//
DanceObject *DanceObjectList::setActive(char *name)
{
	if (name == NULL) {
		Active = NULL;
		return Active;
	}

	DanceObject *plugin = NULL;
	for (int i=0; i	< numDanceObjects; i++)	{
		if (strcmp(DanceObjects[i]->getName(),name) == 0) {
			plugin = DanceObjects[i];
			break;
		}
	}

	Active = plugin;
	return(Active);
}

// setActive:
//	Sets the active	object.
DanceObject *DanceObjectList::setActive(int index)
{
	if (index >= numDanceObjects ||	index <	0)
		Active = NULL;
	else
		Active = DanceObjects[index];
	return(Active);
}

// returns the number of objects that handled the keystroke
int DanceObjectList::KeyboardCB(unsigned char key, int x, int y)
{
    int count = 0 ;
    for (int i = 0; i	< numDanceObjects; i++)	{
       count += DanceObjects[i]->KeyboardCB(key, x, y) ;
    }
    return count ;
}
