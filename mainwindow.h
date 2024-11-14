#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUserInfo(QString name, QString surname, QString position);
    Ui::MainWindow *ui;
    QVector<QCPGraph> graphs_;
    QDateTime date_time_start_;
    QDateTime date_time_finish_;
private slots:
    void checkDataFromDatabase();
    QString isValidData(int dataType, QVector<double> data);


};
#endif // MAINWINDOW_H
