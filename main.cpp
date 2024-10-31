#include "mainwindow.h"

#include <QApplication>
#include <QTest>
#include "Tests/testfileparcer.h"
#include "Tests/testlogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    freopen("testing.log", "w", stdout);
    QTest::qExec(new TestFileparcer, argc, argv);
    QTest::qExec(new testLogger, argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
