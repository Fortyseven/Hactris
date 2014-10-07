#include "Main.h"

#define TIMER_SPEED_TICKS_PER_SEC 60

unsigned long timer;


void timer_proc()
{
    timer++;
}
END_OF_FUNCTION(ticker)

void timer_init()
{
    timer = 0;
    install_int_ex(timer_proc, BPS_TO_TIMER( TIMER_SPEED_TICKS_PER_SEC ));

    LOCK_VARIABLE(my_time);
    LOCK_FUNCTION(my_timer);
}

void timer_done()
{
    remove_int(timer_proc);
}
