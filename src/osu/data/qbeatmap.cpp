#include "qbeatmap.h"
#include "qosufile.h"

QBeatmap::QBeatmap(QString folder) : QBeatmap(QDir(folder))
{

}

QBeatmap::QBeatmap(QDir folder)
{
    this->load(folder);
}

void QBeatmap::load(QString folder)
{
    this->load(QDir(folder));
}

void QBeatmap::load(QDir folder)
{
    this->folder = folder;
    this->folder.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    this->folder.setNameFilters(QStringList() << "*.osu");

    this->maps.clear();
    QFileInfoList entries = this->folder.entryInfoList();
    for(int i=0;i<entries.size();i++)
    {
        QOsuFile *f = new QOsuFile(entries[i].absoluteFilePath(), this);
        this->maps.push_back(f);
    }

    if(!this->maps.empty())
    {
        this->id = this->maps[0]->getBeatmapID();
        this->artist = this->maps[0]->getArtist();
        this->song = this->maps[0]->getTitle();
    }
    else
    {
        this->id = -1;
        this->artist = "Unknown Artist";
        this->song = "Unknown Title";
    }

    this->valid = true;
}

QVector<QOsuFile*> QBeatmap::getMaps()
{
    return this->maps;
}

QString QBeatmap::getArtist()
{
    return this->artist;
}

QString QBeatmap::getSong()
{
    return this->song;
}

int QBeatmap::getId()
{
    return this->id;
}

bool QBeatmap::isValid()
{
    return this->valid;
}
