#ifndef OSUTESTS_H
#define OSUTESTS_H

#include <QString>
#include <QFileInfo>

#include "data/qosufile.h"

class OsuTests
{
public:
    OsuTests();

    static void testOsuFile(QString file);
};

#endif // OSUTESTS_H
