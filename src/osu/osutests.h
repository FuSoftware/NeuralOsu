#ifndef OSUTESTS_H
#define OSUTESTS_H

#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

#include "engine/qbeatmapscanner.h"
#include "data/qbeatmap.h"
#include "data/qosufile.h"

#include <iostream>

class OsuTests
{
public:
    OsuTests();

    static void testOsuFile(QString file);
    static void testBeatmapFolder(QString folder = "E:/Program Files (x86)/osu!/Songs");
    static void testBeatmapScanner(QString folder = "E:/Program Files (x86)/osu!/Songs");

};

#endif // OSUTESTS_H
