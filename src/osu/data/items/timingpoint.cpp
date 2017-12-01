#include "timingpoint.h"

TimingPoint::TimingPoint(long offset, float ms_per_beat, long meter, int sample_type, int sample_set, int volume, bool kiai_mode)
{
    this->offset = offset;
    this->ms_per_beat = ms_per_beat;
    this->meter = meter;
    this->sample_type = sample_type;
    this->sample_set = sample_set;
    this->volume = volume;
    this->kiai_mode = kiai_mode;
}

TimingPoint::TimingPoint(QStringList raw_data)
{
    this->offset = raw_data[0].toLong();
    this->ms_per_beat = raw_data[1].toFloat();
    this->meter = raw_data[2].toLong();
    this->sample_type = raw_data[3].toInt();
    this->sample_set = raw_data[4].toInt();
    this->volume = raw_data[5].toInt();
    this->kiai_mode = raw_data[6].toInt() == 1;
}

TimingPoint::TimingPoint(QString raw_data) : TimingPoint(raw_data.split(","))
{

}
