#ifndef BEATMAP_H
#define BEATMAP_H

#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QVector>
#include <QRegularExpression>

class QOsuFile;

class QBeatmap
{
public:
    QBeatmap(QString folder);
    QBeatmap(QDir folder);

    void load(QString folder);
    void load(QDir folder);

    QVector<QOsuFile*> getMaps();

    bool isValid();

    QString getArtist();
    QString getSong();
    int getId();

private:
    QString artist;
    QString song;
    int id;

    QDir folder;
    QVector<QOsuFile*> maps;
    bool valid = false;
};

#endif // BEATMAP_H
