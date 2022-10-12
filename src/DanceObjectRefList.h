#ifndef	_DanceObjectRefList_h_
#define	_DanceObjectRefList_h_ 1

#include "DanceObject.h"

class DLLENTRY DanceObjectRefList {
protected:
  int numDanceObjects;
  
public:
  DanceObject **DanceObjects;
  int numDanceBins;
  
  DanceObjectRefList();
  ~DanceObjectRefList();
  
  int add(DanceObject *obj);
  int remove(int index);
  int remove(char	*name);
  inline int size() { return numDanceObjects;};
  
  DanceObject	*get(int index);
  DanceObject *get(char *name);
  int getIndex(char *name);
  
};

#endif
