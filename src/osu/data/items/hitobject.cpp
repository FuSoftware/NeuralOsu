#include "hitobject.h"

HitObject::HitObject(int x, int y, int time, int type, int hitSound, QString extras)
{
    this->load(x,y,time,type,hitSound,extras);
}

HitObject::HitObject(QString data)
{
    this->load(data);
}

void HitObject::load(QString s)
{
    QStringList d = s.split(",");
    this->load(
            d[0].toInt(),
            d[1].toInt(),
            d[2].toInt(),
            d[3].toInt(),
            d[4].toInt(),
            d[d.size()-1]);
}

void HitObject::load(int x, int y, int time, int type, int hitSound, QString extras)
{
    this->x = x;
    this->y = y;
    this->time = time;
    this->type = type;
    this->hitSound = hitSound;

    this->setExtras(extras);
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

