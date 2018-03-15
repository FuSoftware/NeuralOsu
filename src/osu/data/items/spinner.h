#ifndef SPINNER_H
#define SPINNER_H

#include "hitobject.h"

class Spinner : public HitObject
{
public:
    Spinner(QString data);

    static bool isSpinner(QString data);

private:
    int endTime;

};

#endif // SPINNER_H
