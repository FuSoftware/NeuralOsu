#include "spinner.h"

Spinner::Spinner(QString data) : HitObject(data)
{
    QStringList d = data.split(",");
    this->endTime = d[5].toInt();
}

bool Spinner::isSpinner(QString data)
{
    QStringList d = data.split(",");

    if(d.size() >= 6)
    {
        return d[5].split(":").size() == 1;
    }
    else
    {
        return false;
    }
}
