#include "timingpoint.h"

TimingPoint::TimingPoint()
{

}

TimingPoint::TimingPoint(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode)
{
    this->load(offset, ms_per_beat, meter, sample_type, sample_set, volume, kiai_mode);
}

TimingPoint::TimingPoint(QString raw_data)
{
    this->loadString(raw_data);
}

void TimingPoint::loadString(QString raw_data)
{
    QStringList d = raw_data.split(",");

    //Older beatmaps don't have that property
    bool kiai = d.size() > 6 ? (d[6].toInt() == 1) : false;

    this->load(
            d[0].toLong(),
            d[1].toFloat(),
            d[2].toLong(),
            d[3].toInt(),
            d[4].toInt(),
            d[5].toInt(),
            kiai
            );
}

void TimingPoint::load(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode)
{
    this->offset = offset;
    this->ms_per_beat = ms_per_beat;
    this->meter = meter;
    this->sample_type = sample_type;
    this->sample_set = sample_set;
    this->volume = volume;
    this->kiai_mode = kiai_mode;
}
