#ifndef FSM_H
#define FSM_H
#include "state.h"
#include <QDebug>


class Fsm
{

    State _currentState;

public:
    Fsm();
    virtual void run()=0;
    bool checkState(State& src, const State& target, bool cond, FsmFn callback);
};

#endif // FSM_H
