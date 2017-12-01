#include "osutests.h"

OsuTests::OsuTests()
{

}

void OsuTests::testOsuFile(QString file)
{
    QOsuFile *f = new QOsuFile(QFileInfo(file));
    f->getMusicFile();
}
