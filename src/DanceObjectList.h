#ifndef	_DANCEOBJECTLIST_H_
#define	_DANCEOBJECTLIST_H_ 1

#include "DanceObject.h"

class DLLENTRY DanceObjectList {
private:
  DanceObject *Active;
  char Type[MAX_LINE];
  
protected:
  int numDanceObjects;
  
public:
  DanceObject **DanceObjects;
  int numDanceBins;
  
  inline char *getType() { return	&Type[0]; };
  inline void setType(char *type)	{ strcpy(Type,type); };
  
  DanceObjectList();
  ~DanceObjectList();
  
  int add(DanceObject *obj);
  int remove(int index);
  int remove(char	*name);
  inline int size() { return numDanceObjects;};
  
  DanceObject	*get(int index);
  DanceObject *get(char *name);
  int getIndex(char *name);
  inline DanceObject *getActive(void) { return Active; };
  DanceObject *setActive(char *name);
  DanceObject *setActive(int index);
  void print(FILE	*fptr);
  virtual	int Command(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
    {return	TCL_OK;};
  void output(int	mode);
  DanceObject *getByFileName(char *fname) ;
  int KeyboardCB(unsigned char key, int x, int y) ;
  
};

#endif
