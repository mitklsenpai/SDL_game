
#ifndef TIMER_H_
#define TIMER_H_

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();


    void start();  // ham cong dung cho game
    void stop();
    void paused();    // ham paused va unpaused se tich hop sau
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick_;
    int paused_tick_;

    bool is_paused_;
    bool is_started_;

};


#endif // TIMER_H_
