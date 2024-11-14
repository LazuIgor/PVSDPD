#include "mainwindow.h"

#include <QApplication>
#include <QTest>
#include "Tests/testfileparcer.h"
#include "Tests/testlogger.h"
#include "logindialog.h"
//#include "realiselogger.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    freopen("testing.log", "w", stdout);
    //QTest::qExec(new TestFileparcer, argc, argv);
    //QTest::qExec(new testLogger, argc, argv);
    MainWindow w;
    LoginDialog dialog(w.parentWidget());
    if(dialog.exec() == QDialog::Accepted)
    {
        w.setUserInfo(dialog.getName(), dialog.getSurname(), dialog.getPosition());
        w.show();
    }
    else
    {
        QApplication::quit();
    }
    return a.exec();
}
