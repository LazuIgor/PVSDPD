#include "fileparser.h"
#include "QFileDialog"

Fileparser::Fileparser()
{

}

void Fileparser::parse(QString filename, QDateTime start, QDateTime finish)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    for(int i =0; i < 13; i++)
    {
        data_container_.append(QVector<double>());
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList data = line.split(" ");
        QString time = data[0];
        QString date = data[1];
        QDateTime dateTime = QDateTime(QDate(date.split(".")[2].toInt(),
                                             date.split(".")[1].toInt(),
                                             date.split(".")[0].toInt()),
                                       QTime(time.split(":")[0].toInt(),
                                             time.split(":")[1].toInt(),
                                             time.split(":")[2].toInt()));
        if(start <= dateTime && dateTime <= finish)
        {
            data.pop_front();
            data.pop_front();
            for(int index = 0; index <data.length(); index++)
            {
                data_container_[index].append(data[index].toDouble());
            }
        }
    }
}

QVector<QVector<double>> Fileparser::data_container()
{
    return data_container_;
}
