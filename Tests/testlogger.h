#ifndef TESTLOGGER_H
#define TESTLOGGER_H
#include <QtTest/QTest>

class testLogger: public QObject {
    Q_OBJECT
public:
    testLogger(QObject *parent = 0);
    ~testLogger();
private slots:
    void testCreateLogFile();
    void testLogMessage();
    void testDeleteOldLogs();
    void testOpenCloseLogFile();
    void testLevelToString();
};

#endif // TESTLOGGER_H


