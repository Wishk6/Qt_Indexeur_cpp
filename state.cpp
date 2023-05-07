#include "state.h"

int State::_currentIndex = 0;



int State::id() const
{
    return _id;
}

void State::setId(int newId)
{
    _id = newId;
}

QString State::stateName() const
{
    return _stateName;
}

void State::setStateName(const QString &newStateName)
{
    _stateName = newStateName;
}
