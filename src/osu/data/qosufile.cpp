#include "qosufile.h"
#include "qbeatmap.h"

QStringList QOsuFile::sections = {"General","Editor","Metadata","Difficulty","Events","TimingPoints","Colours","Hitobjects"};

QOsuFile::QOsuFile(QString path, QBeatmap* parent) : QOsuFile(QFileInfo(path), parent)
{

}

QOsuFile::QOsuFile(QFileInfo info, QBeatmap *parent)
{
    this->load(info);
}

void QOsuFile::save()
{

}

void QOsuFile::load(QFileInfo info)
{
    this->fileInfo = info;

    if(this->fileInfo.exists())
    {

        QFile f(this->fileInfo.absoluteFilePath());

        if(f.exists())
        {
            qDebug() << "Parsing " << fileInfo.baseName();

            //Read the file's content
            f.open(QIODevice::ReadOnly);
            QString text = f.readAll();
            f.close();

            //Separate the different categories
            QStringList sections = text.split("\r\n\r\n");

            //Format
            QRegularExpression re("osu file format v(.+)");
            QRegularExpressionMatch match = re.match(sections[0]);
            this->format = match.captured(1).toInt();

            //Data sections
            for(int i=1;i<sections.length();i++)
            {
                //Section title
                re.setPattern("\\[(.+)\\]");
                QString title = re.match(sections[i]).captured(1);

                if(title == "Events")
                {

                }
                else if(title == "TimingPoints")
                {
                    this->timingPoints.clear();

                    //Offset, Milliseconds per Beat, Meter, Sample Type, Sample Set, Volume, Inherited, Kiai Mode
                    QStringList lines = sections[i].split("\r\n");

                    //Starting at 1 to exclude the title
                    for(int j=1;j<lines.size();j++)
                    {
                        TimingPoint *p = new TimingPoint(lines.at(j));
                        this->timingPoints.push_back(p);
                    }
                }
                else if(title == "Colours")
                {

                }
                else if(title == "HitObjects")
                {
                    this->hitObjects.clear();

                    QStringList lines = sections[i].split("\r\n");

                    //Remove the last one if it's empty
                    if(lines[lines.size()-1] == "") lines.pop_back();
                    if(lines[0] == "") lines.pop_front();

                    int non_parsed = 0;

                    //Starting at 1 to exclude the title
                    for(int j=1;j<lines.size();j++)
                    {
                        if(Spinner::isSpinner(lines[j]))
                        {
                            this->hitObjects.push_back(new Spinner(lines[j]));
                        }
                        else if(Slider::isSlider(lines[j]))
                        {
                            this->hitObjects.push_back(new Slider(lines[j]));
                        }
                        else
                        {
                            this->hitObjects.push_back(new HitObject(lines[j]));
                        }
                    }

                    //qDebug() << "Parsed" << lines.size() -1 << "items";
                }
                else
                {
                    //Metadata
                    re.setPattern("(.+):(.+)\\s");
                    QRegularExpressionMatchIterator it = re.globalMatch(sections[i]);
                    this->metadata[title] = QHash<QString, QString>();

                    while(it.hasNext())
                    {
                        match = it.next();
                        QString param = match.captured(1).trimmed();
                        QString value = match.captured(2).trimmed();
                        this->metadata[title][param] = value;
                    }
                }
            }
            qDebug() << "Parsed " << fileInfo.baseName();
        }
        else
        {
             qDebug() << "Error parsing" << fileInfo.absoluteFilePath() << "(doesn't exist)";
        }
    }
    else
    {
        qDebug() << "Error parsing" << fileInfo.absoluteFilePath() << "(doesn't exist)";
    }
}

QString QOsuFile::getData(QString category, QString variable, QString def)
{
    if(this->metadata.contains(category))
    {
        if(this->metadata[category].contains(variable))
        {
            return this->metadata[category][variable];
        }
    }

    return def;

}

bool QOsuFile::hasData(QString category, QString variable)
{
    if(this->metadata.contains(category))
    {
        return this->metadata[category].contains(variable);
    }
    else
    {
        return false;
    }
}

QHash<QString,QString> QOsuFile::getCategory(QString category)
{
    if(this->metadata.contains(category))
        return this->metadata[category];
    else
        return QHash<QString,QString>();
}

QString QOsuFile::getMusicFile()
{
    return getData("General", "AudioFilename");
}

QString QOsuFile::getArtist()
{
    return this->getData("Metadata","Artist");
}

int QOsuFile::getBeatmapID()
{
    if(this->hasData("Metadata", "BeatmapSetID"))
        return this->getData("Metadata","BeatmapSetID").toInt();
    else
        return -1;
}

QString QOsuFile::getTitle()
{
    return this->getData("Metadata","Title");
}
