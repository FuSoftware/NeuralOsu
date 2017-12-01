#include "hitobject.h"

HitObject::HitObject(int x, int y, int time, int type, int hitSound, QString extras)
{
    this->x = x;
    this->y = y;
    this->time = time;
    this->type = type;
    this->hitSound = hitSound;

    this->setExtras(extras);
}

HitObject::HitObject(QString data) : HitObject(data.split(","))
{

}

HitObject::HitObject(QStringList data)
{
    //These 5 settings are present whatever item type we have
    this->x = data[0].toInt();
    this->y = data[1].toInt();
    this->time = data[2].toInt();
    this->type = data[3].toInt();
    this->hitSound = data[4].toInt();

    //Extras are the last item from the set, whatever input type we have
    this->setExtras(data[data.size()-1]);
}

void HitObject::setExtras(QString extras)
{
    QStringList l = extras.split(":");

    if(l.size() > 1)
    {
        if(l.size() > 4)
            l.pop_front();
        this->sampleSet = l[0].toInt();
        this->customindex = l[1].toInt();
        this->sampleVolume = l[2].toInt();
        this->filename = l[3];
    }
}

bool HitObject::isType(int mask)
{
    return this->type & mask;
}

bool HitObject::isCircle()
{
    return this->isType(HitObject::CIRCLE);
}

bool HitObject::isSlider()
{
    return this->isType(HitObject::SLIDER);
}

bool HitObject::isNewCombo()
{
    return this->isType(HitObject::NEW_COMBO);
}

bool HitObject::isSpinner()
{
    return this->isType(HitObject::SPINNER);
}

