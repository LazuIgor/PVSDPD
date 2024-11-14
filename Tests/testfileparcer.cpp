#include "testfileparcer.h"
#include "fileparser.h"
#include "mainwindow.h"
#include "QDebug"

TestFileparcer::TestFileparcer(QObject *parent) :
    QObject(parent)
{

}

void TestFileparcer::testParserDataLengh()
{
    Fileparser parser;
    parser.parse("C:/Users/Sergeinder/Desktop/PVSDPD/line1_20240913.txt",
                 QDateTime(QDate(2000, 1, 1),QTime()),
                 QDateTime(QDate(2024, 12, 31),QTime()));
    QCOMPARE(parser.data_container().length(), 6);
}

void TestFileparcer::testParserError()
{
    Fileparser parser;
    parser.parse("C:/Users/Sergeinder/Desktop/PVSDPD/line1_20240913.txt",
                 QDateTime(QDate(2000, 1, 1),QTime()),
                 QDateTime(QDate(2000, 12, 31),QTime()));
    QCOMPARE(parser.data_container().at(0).length(), 0);
}

void TestFileparcer::testDateTimeChange() {
    MainWindow mainWindow;
    mainWindow.show();
    QTest::qWaitForWindowExposed(&mainWindow);

    QDateTime newDateTime = QDateTime::currentDateTime().addDays(1);

    // Эмулируем изменение даты и времени в первом QDateTimeEdit
    QTest::keyClicks(mainWindow.findChild<QDateTimeEdit*>("dateTimeEdit"), newDateTime.toString("dd.MM.yyyy HH:mm::ss"));
    QCOMPARE(mainWindow.date_time_start_.date(), newDateTime.date());

    // Эмулируем изменение даты и времени во втором QDateTimeEdit
    QTest::keyClicks(mainWindow.findChild<QDateTimeEdit*>("dateTimeEdit_2"), newDateTime.toString("dd.MM.yyyy HH:mm::ss"));
    QCOMPARE(mainWindow.date_time_finish_.date(), newDateTime.date());

    mainWindow.close();
}

TestFileparcer::~TestFileparcer()
{

}


