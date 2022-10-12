
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
#include "list.h"
#include <stddef.h>
#include <assert.h>

list::list(){
     first = new storageClass; 
     last = new storageClass;
     last->previous = first;
     first->next = last;
     numElements = 0;
}

list::~list(){  
  storageClass *current = first;
  // storageClass *toDelete = first;
  storageClass *toDelete = NULL;

  while(current != NULL){
	  toDelete = current;
      current = current->next;
      delete toDelete;
      // toDelete = current;
  }
  
}

//adds on to the end of the list

void list::add(storageClass *s){
    assert(s != NULL);
    s->next = last;
    s->previous = last->previous;
    last->previous->next = s;
    last->previous = s;
    numElements ++;    
}


void list::merge(list *append){
    append->first->next->previous = last->previous;
    append->last->previous->next = last;
    last->previous->next = append->first->next; 
    last->previous = append->last->previous;
    
    append->last->previous = NULL;
    append->first->next = NULL;
    delete append->last;
    delete append->first;
    numElements = numElements + append->getLength();
}


int list::getLength(void){
   return numElements;
}




