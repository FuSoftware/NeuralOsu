#ifndef BEATMAPENGINE_H
#define BEATMAPENGINE_H

#include <QObject>

class QBeatmapEngine : public QObject
{
    Q_OBJECT
public:
    QBeatmapEngine(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BEATMAPENGINE_H
