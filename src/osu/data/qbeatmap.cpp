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

    //Beatmap's metadata
    QRegularExpression re("([0-9]+) (.+) - (.+)");
    QRegularExpressionMatch match = re.match(this->folder.dirName());
    if(match.hasMatch())
    {
        //Standard name
        this->id = match.captured(1).toInt();
        this->artist = match.captured(2);
        this->song = match.captured(3);
    }
    else
    {
        this->song = this->folder.dirName();
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
