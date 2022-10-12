#ifndef LinkStack_h 
#define LinkStack_h

#ifdef WIN32
#ifdef _EXPORTING_AR
#define DLLENTRY_AR __declspec(dllexport)
#else
#define DLLENTRY_AR __declspec(dllimport)
#endif
#else
#define DLLENTRY_AR
#endif


class Link ;

class DLLENTRY_AR LinkStackElement {
public:
	LinkStackElement(Link *l) { link = l ; next = NULL ; previous = NULL ;} ;
	Link *link ;
	LinkStackElement *next ;
	LinkStackElement *previous ;
} ;

class DLLENTRY_AR LinkStack {
public:

	LinkStack() { size = 0 ; top = NULL ; first = NULL ; } ;
	~LinkStack() ;
	void Print(void) ;
	void Push(Link *link) ;
	Link *Pop() ;
	Link *GetTop() { if( top == NULL) return NULL ; 
		else return top->link ;} ;

private:

	int size ;
	LinkStackElement *top ;
	LinkStackElement *first ;
} ;

#endif

