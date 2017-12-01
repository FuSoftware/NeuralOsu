#ifndef SPINNER_H
#define SPINNER_H

#include "hitobject.h"

class Spinner : public HitObject
{
public:
    Spinner(QString data);
    Spinner(QStringList data);

    static bool isSpinner(QString data);
    static bool isSpinner(QStringList data);

private:
    int endTime;

};

#endif // SPINNER_H
