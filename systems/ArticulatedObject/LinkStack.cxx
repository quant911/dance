#include "defs.h"
#include "danceTcl.h"
#include "LinkStack.h"

#include "Link.h"

#ifdef WIN32
#ifndef printf
#define printf danceTcl::OutputResult
#endif
#endif

LinkStack::~LinkStack()
{
    LinkStackElement *l ;
	for( l = first ; l != NULL ; l = l->next )
	{
		if( l->previous != NULL ) delete l->previous ;
	}
	if( l != NULL ) delete l ;
}

void LinkStack::Push(Link *link)
{
	LinkStackElement *lse = new LinkStackElement(link) ;
	if( lse == NULL )
	{
		printf("LinkStack::Push(): ERROR: out of memory!\n") ;
		return ;
	}
	lse->previous = top ;
	lse->next = NULL ;
	if( top != NULL ) top->next = lse ;
	if( first == NULL )
	{
		first = lse ;
	}
	top = lse ;
	size++ ;
}

Link *LinkStack::Pop(void)
{
	if( top == NULL )
	{
		printf("Warning the stack is empty!\n") ;
		return NULL ;
	}
	Link *res = top->link ;
	LinkStackElement *prev_top = top ;
	top = top->previous ;
	delete prev_top ;
	if( top != NULL ) top->next = NULL ;
	else first = NULL ;
	size-- ;
	return res ;
}

void LinkStack::Print(void)
{	
	for( LinkStackElement *lse = first ; lse != NULL ; lse = lse->next )
		printf("%s ", lse->link->getName()) ;
	printf("\n") ;
}


