#ifndef HITOBJECT_H
#define HITOBJECT_H

#include <QString>
#include <QStringList>

class HitObject
{
public:
    HitObject(int x, int y, int time, int type, int hitSound, QString extras);
    HitObject(QString data);
    HitObject(QStringList data);

    void setExtras(QString extras);

    bool isType(int mask);
    bool isCircle();
    bool isSlider();
    bool isNewCombo();
    bool isSpinner();

    enum Type
    {
        CIRCLE = 0,
        SLIDER = 2,
        NEW_COMBO = 4,
        SPINNER = 8,

    };
    enum HitSound
    {
        NORMAL = 0,
        WHISTLE = 2,
        FINISH = 4,
        CLAP = 8
    };

protected:
    int x; //0-512 (inclusive)
    int y; //0-384 (inclusive)
    int time; //Start time in ms
    int type;
    int hitSound;

    //Extras
    int sampleSet;
    int customindex;
    int sampleVolume;
    QString filename;
};

#endif // HITOBJECT_H
