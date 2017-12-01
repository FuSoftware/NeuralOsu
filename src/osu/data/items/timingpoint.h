#ifndef TIMINGPOINT_H
#define TIMINGPOINT_H

#include <QString>
#include <QStringList>

//Offset, Milliseconds per Beat, Meter, Sample Type, Sample Set, Volume, Inherited, Kiai Mode

class TimingPoint
{
public:
    TimingPoint(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode);
    TimingPoint(QStringList raw_data);
    TimingPoint(QString raw_data);

private:
    long offset;
    float ms_per_beat;
    long meter; //Beats per mesure
    int sample_type;
    int sample_set;
    int volume;
    bool kiai_mode;
};

#endif // TIMINGPOINT_H
