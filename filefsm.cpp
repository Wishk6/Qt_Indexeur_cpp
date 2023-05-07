#include "filefsm.h"

#include "fsm.h"

FileFsm::FileFsm()
{
    qDebug() << __FUNCTION__;
    UNKNOWN.setStateName("UNKNOWN");
    START.setStateName("START");
}

void FileFsm::run()
{
    qDebug("Animal fsm running");

    checkState(UNKNOWN, START, 1, [](){
        qDebug() << "not start";
    });
}
