#include "spinner.h"

Spinner::Spinner(QString data) : Spinner(data.split(","))
{

}

Spinner::Spinner(QStringList data) : HitObject(data)
{
    this->endTime = data[5].toInt();
}

bool Spinner::isSpinner(QString data)
{
    return Spinner::isSpinner(data.split(","));
}

bool Spinner::isSpinner(QStringList data)
{
    if(data.size() >= 6)
    {
        return data[5].split(":").size() == 1;
    }
    else
    {
        return false;
    }
}
