#ifndef HITCIRCLE_H
#define HITCIRCLE_H

#include "hitobject.h"

#include <QVector>
#include <QPoint>

class Slider : public HitObject
{
public:
    Slider(QString data);
    Slider(QStringList data);

    static bool isSlider(QString data);
    static bool isSlider(QStringList data);

    enum SliderType
    {
        LINEAR = 0,
        PERFECT,
        BEZIER
    };

private:
    QVector<QPoint> curve_points;
    QVector<int> edge_hit_sounds;
    int slider_type;
    int repeat;
    float pixel_length;

};

#endif // HITCIRCLE_H
