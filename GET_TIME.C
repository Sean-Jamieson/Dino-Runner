#include <stdio.h>
#include <osbind.h>
#include "GET_TIME.H"

long get_time()
{
    long var;
    long *timer = (long *)0x462;
    long old_ssp;

    old_ssp = Super(0);  
    var = *timer;
    Super(old_ssp);
    
    return var;
}