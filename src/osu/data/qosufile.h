#ifndef OSUFILE_H
#define OSUFILE_H

//https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osu_(file_format)

#include <QObject>
#include <QSettings>
#include <QFileInfo>
#include <QVector>
#include <QColor>
#include <QFile>
#include <QStringList>
#include <QDebug>

#include "items/event.h"
#include "items/timingpoint.h"
#include "items/hitobject.h"
#include "items/slider.h"
#include "items/spinner.h"

#include <QRegularExpression>

class QBeatmap;

class QOsuFile
{
public:
    QOsuFile(QString path, QBeatmap* parent = 0);
    QOsuFile(QFileInfo info, QBeatmap* parent = 0);

    void save();
    void load(QFileInfo info);

    QString getData(QString category, QString variable, QString def = "");

    QString getMusicFile();

private:
    QFileInfo fileInfo;

    int format = 0;

    QHash<QString, QHash<QString, QString>> metadata; // Contains the beatmap's String data
    QVector<QVector<Event*>> events;
    QVector<TimingPoint*> timingPoints;
    QVector<HitObject*> hitObjects;
    QHash<QString, QColor> colors;

    static QStringList sections;
};

#endif // OSUFILE_H
