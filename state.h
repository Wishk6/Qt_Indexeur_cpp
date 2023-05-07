#ifndef STATE_H
#define STATE_H
#include <QString>
#include <QDebug>
typedef void (*FsmFn)();

class State{
    static int _currentIndex;
    int _id = 0;
    QString _stateName = "";


public:

    State(QString stateName = "UNKNOWN"): _stateName(stateName){

        _id = _currentIndex;
        qDebug()<< __FUNCTION__ << _id;
        _currentIndex++;
    }

    bool operator == ( const State& st1) {
        qDebug() << __FUNCTION__ << st1._id << _id;
        qDebug() << __FUNCTION__ << st1.stateName() << stateName();

       return st1._id == _id;
    }


    QString stateName() const;
    void setStateName(const QString &newStateName);
    int id() const;
    void setId(int newId);
};

#endif // STATE_H
