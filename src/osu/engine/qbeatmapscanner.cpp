#include "qbeatmapscanner.h"

QBeatmapScanner::QBeatmapScanner(QString folder, QObject *parent) : QBeatmapScanner(QDir(folder), parent)
{

}

QBeatmapScanner::QBeatmapScanner(QDir folder, QObject *parent )  : QObject(parent)
{
    this->folder = folder;
}

void QBeatmapScanner::scan()
{
    this->beatmaps.clear();
    this->folder.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);

    QFileInfoList folders = this->folder.entryInfoList();

    for(int i=0;i<folders.size();i++)
    {
        QBeatmap *b = new QBeatmap(folders[i].absoluteFilePath());
        if(b->isValid()) this->beatmaps.push_back(b);
    }
}

QString QBeatmapScanner::toAsciiTree()
{
    QString output = "";

    for(int i=0;i<this->beatmaps.size();i++)
    {
        QBeatmap *b = this->beatmaps[i];
        output += QString("- %1 - %2 %3 \r\n").arg(QString::number(b->getId()), b->getArtist(), b->getSong());

        for(int j=0;j<b->getMaps().size();j++)
        {
            QOsuFile *f = b->getMaps()[j];
            output += QString("  - %1 - %2 \r\n").arg(f->getData("Metadata","BeatmapID","#VALUE"), f->getData("Metadata","Version"));
        }
    }

    return output;
}
