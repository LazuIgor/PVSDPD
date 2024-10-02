#include "fileparser.h"
#include "QFileDialog"

Fileparser::Fileparser()
{

}

void Fileparser::parse(QString filename)
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

        data.pop_front();
        data.pop_front();
        for(int index = 0; index <data.length(); index++)
        {
            data_container_[index].append(data[index].toDouble());
        }
    }
}

QVector<QVector<double>> Fileparser::data_container()
{
    return data_container_;
}
