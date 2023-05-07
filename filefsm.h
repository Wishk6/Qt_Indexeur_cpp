#ifndef FILEFSM_H
#define FILEFSM_H

#include <fsm.h>

class FileFsm : public Fsm
{
    State UNKNOWN;
    State START;

public:
    FileFsm();

    virtual void run();
};

#endif // FILEFSM_H
