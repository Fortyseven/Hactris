#ifndef __TIMER_H__
#define __TIMER_H__

extern unsigned long timer;

extern void timer_init();
extern void timer_done();

class Delay
{
    private:
        unsigned long delaylength, lasttimer;
    public:
        Delay(unsigned long delaylength)
        {
            this->delaylength = delaylength;
            reset();
        }

        bool hasPassed()
        {
            if ((timer - lasttimer) >= delaylength) {
                this->lasttimer = timer;
                return true;
            };

            return false;
        }

        void reset()
        {
            this->lasttimer = timer;
        }
};

#endif
