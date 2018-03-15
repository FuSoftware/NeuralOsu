#ifndef TIMINGPOINT_H
#define TIMINGPOINT_H

#include <QString>
#include <QStringList>

//Offset, Milliseconds per Beat, Meter, Sample Type, Sample Set, Volume, Inherited, Kiai Mode

class TimingPoint
{
public:
    TimingPoint();
    TimingPoint(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode);
    TimingPoint(QString raw_data);

    void loadString(QString raw_data);
    void load(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode);

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
