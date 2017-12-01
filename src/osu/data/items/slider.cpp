#include "slider.h"

Slider::Slider(QString data) : Slider(data.split(","))
{

}

Slider::Slider(QStringList data) : HitObject(data)
{
    QStringList path = data[5].split("|");

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

    this->repeat = data[6].toInt();
    this->pixel_length = data[7].toFloat();

    if(data.size() >= 9)
    {
        QStringList edgeHitSoundList = data[8].split("|");

        for(int i=0;i<edgeHitSoundList.length();i++)
            this->edge_hit_sounds.push_back(edgeHitSoundList[i].toInt());
    }

    //TODO : Edge Additions

}

bool Slider::isSlider(QString data)
{
    return Slider::isSlider(data.split(","));
}

bool Slider::isSlider(QStringList data)
{
    if(data.size() >= 6)
    {
        return data[5].split("|").size()>1;
    }
    else
    {
        return false;
    }
}

