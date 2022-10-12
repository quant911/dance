
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


#ifndef	_list_h_
#define	_list_h_

#include<stddef.h>


class storageClass{
public:
   storageClass(){next = NULL; previous = NULL;}
   virtual ~storageClass(){remove();}
   storageClass *next;
   storageClass *previous;
   void remove(void){
     if(next != NULL){next->previous = previous;}
     if(previous != NULL){previous->next = next;}
   }
};


class intStorage: public storageClass{
public:
  intStorage(){theInt = 0;}
   int theInt;
};

class IKconstraint;
class conStorage : public storageClass{

public:
     conStorage(){constraint = NULL;}
     IKconstraint *constraint;
};

class list{
private:
     int numElements;
public:
	list();
	~list();
        storageClass *first;
        storageClass *last;
        void add(storageClass *s);
        void merge(list *append);
        int getLength(void);
};

#endif

















