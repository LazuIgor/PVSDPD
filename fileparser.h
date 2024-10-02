#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "QString"
#include "qcustomplot.h"

class Fileparser
{
public:
    Fileparser();

    QVector<QVector<double>> data_container();
    void parse(QString filename);

private:
    QVector<QVector<double>> data_container_;
};

#endif // FILEPARSER_H
