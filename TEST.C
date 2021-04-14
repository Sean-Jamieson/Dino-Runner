#include <stdio.h>
#include <osbind.h>
#include "SOUND.H"
#include "SONG.H"
#include "GET_TIME.H"

int main()
{
    long time;
    long prev_time;
    long time_passed;

    start_music();
    prev_time = get_time();
    while (!Cconis())
    {
        time = get_time();
        time_passed = time - prev_time;
        
        if(time_passed >=1)
        {
        if (update_music(time_passed)==1)
            prev_time = get_time();   
        }
    }
    stop_sound();
    return 0;
}