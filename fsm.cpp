#include "fsm.h"
#include <QDebug>

Fsm::Fsm()
{
}

bool Fsm::checkState(State& src, const State& target, bool cond, FsmFn callback){

    qDebug() << __FUNCTION__ << _currentState.stateName() << _currentState.id();
    if (src == _currentState && cond) {
        qDebug() << _currentState.stateName();
        _currentState = target;
        if (callback != nullptr) {
            callback();
        }
        return true;
    }
    return false;
}
