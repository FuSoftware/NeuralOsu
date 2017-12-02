#ifndef QBEATMAPSCANNER_H
#define QBEATMAPSCANNER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QVector>
#include "../data/qbeatmap.h"
#include "../data/qosufile.h"

class QBeatmapScanner : public QObject
{
    Q_OBJECT
public:
    QBeatmapScanner(QString folder, QObject *parent = nullptr);
    QBeatmapScanner(QDir folder, QObject *parent = nullptr);

    QString toAsciiTree();

signals:

public slots:
    void scan();

private:
    QVector<QBeatmap*> beatmaps;
    QDir folder;
};

#endif // QBEATMAPSCANNER_H
