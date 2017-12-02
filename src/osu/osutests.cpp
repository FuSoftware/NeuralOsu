#include "osutests.h"

OsuTests::OsuTests()
{

}

void OsuTests::testOsuFile(QString file)
{
    QOsuFile *f = new QOsuFile(QFileInfo(file));
    f->getMusicFile();
}

void OsuTests::testBeatmapFolder()
{
    QString dir = QFileDialog::getExistingDirectory(0, "Open Directory","/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QBeatmap *b = new QBeatmap(dir);
    b->isValid();
}

void OsuTests::testBeatmapScanner()
{
    QString dir = QFileDialog::getExistingDirectory(0, "Open Directory","/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QBeatmapScanner *e = new QBeatmapScanner(dir);
    e->scan();

    std::cout << e->toAsciiTree().toStdString();

}
