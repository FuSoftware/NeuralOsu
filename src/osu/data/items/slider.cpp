#include "slider.h"

Slider::Slider(QString data) : HitObject(data)
{
    this->load(data);
}

void Slider::load(QString data)
{
    QStringList d = data.split(",");

    QStringList path = d[5].split("|");

    if(path[0] == "L")
        this->slider_type = Slider::LINEAR;
    else if(path[0] == "P")
        this->slider_type = Slider::PERFECT;
    else if(path[0] == "B")
        this->slider_type = Slider::BEZIER;

    for(int i=1;i<path.length();i++)
    {
        QStringList point = path[i].split(":");
        this->curve_points.push_back(QPoint(point[0].toInt(), point[1].toInt()));
    }

    this->repeat = d[6].toInt();
    this->pixel_length = d[7].toFloat();

    if(d.size() >= 9)
    {
        QStringList edgeHitSoundList = d[8].split("|");

        for(int i=0;i<edgeHitSoundList.length();i++)
            this->edge_hit_sounds.push_back(edgeHitSoundList[i].toInt());
    }

    //TODO : Edge Additions
}

bool Slider::isSlider(QString data)
{
    QStringList d = data.split(",");

    if(d.size() >= 6)
    {
        return d[5].split("|").size()>1;
    }
    else
    {
        return false;
    }
}

