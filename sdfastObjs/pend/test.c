#include "sdfast.h"


/* This is the routine that calculates the derivatives needed by the
   lsodes intergrator  who uses the fortran convention.
   CAUTION: All state arrays (y, dy) are considered y[0..NQ-1], dy[NQ...NQ+NU-1]
*/

void pendMyderiv(double time, double *y, double *dy, double *param, int *status)
{
    double errs[NC] ;		// add 1 to avoid errs[0]

    pendstate(time, &y[0], &y[NQ]) ;
    // penduforce(double t, double *q, double *u);
    penduforce(time, &y[0], &y[NQ]) ;
    // motions(time, &y[0], &y[NQ]) ; // if we had prescribed motions
    pendderiv(&dy[0], &dy[NQ]) ;

    // check the constraints
    *status = 1 ;
    pendverr(errs) ;
    for( int i = 0 ; i < NC ; i++ )
    {
	if ( fabs(errs[i]) > param[0] ) return ;
    }
    pendperr(errs) ;
    for( int i = 0 ; i < NC ; i++ )
    {
	if ( fabs(errs[i]) > param[0] ) return ;
    }
    
    *status = 0 ;
    return ;
}
    

