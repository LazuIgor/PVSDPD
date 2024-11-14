#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "QString"
#include "QDateTime"

class Fileparser
{
public:
    Fileparser();

    QVector<QVector<double>> data_container();
    void parse(QString filename, QDateTime start, QDateTime finish);
    QVector<QDateTime> times;

private:
    QVector<QVector<double>> data_container_;
};

#endif // FILEPARSER_H
