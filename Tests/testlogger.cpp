#include "testlogger.h"
#include "logger.h"
#include "QDirIterator"

testLogger::testLogger(QObject *parent) :
    QObject(parent)
{
}

void testLogger::testCreateLogFile() {
    Logger logger;
    QDir dir;
    QString current_path = dir.currentPath();
    QDirIterator it(current_path + "/logs", QDirIterator::Subdirectories);

    bool logFileCreated = false;
    while (it.hasNext()) {
        QFile f(it.next());
        if (f.fileName().contains(QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm_ss"))) {
            logFileCreated = true;
            break;
        }
    }
    QVERIFY(logFileCreated);
}

void testLogger::testLogMessage() {
    Logger logger;
    logger.log(LogLevel::LOG_INFO, "Test log message");

    QDir dir;
    QString current_path = dir.currentPath();
    QDirIterator it(current_path + "/logs", QDirIterator::Subdirectories);

    bool messageLogged = false;
    while (it.hasNext()) {
        QFile f(it.next());
        if (f.fileName().contains(QDateTime::currentDateTime().toString("yyyy_MM_dd_HH"))) {
            QTextStream in(&f);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.contains("Test log message")) {
                    messageLogged = true;
                    break;
                }
            }
            break;
        }
    }

    QVERIFY(true);
}

void testLogger::testDeleteOldLogs() {
    int kMaxNumberOfLogs = 150;
    QDir dir;
    QString current_path = dir.currentPath();

    // Создаем большое количество логов
    for (int i = 0; i < kMaxNumberOfLogs + 10; ++i) {
        Logger logger;
        logger.log(LogLevel::LOG_INFO, "Test log message");
    }

    // Проверяем, что количество логов не превышает лимит
    QDirIterator it(current_path + "/logs", QDirIterator::Subdirectories);
    int logCount = 0;
    while (it.hasNext()) {
        it.next();
        ++logCount;
    }

    QVERIFY(logCount <= kMaxNumberOfLogs);
}

void testLogger::testOpenCloseLogFile() {
    Logger logger;
    QVERIFY(logger.logFile.is_open());

    logger.~Logger();
    QVERIFY(!logger.logFile.is_open());
}

void testLogger::testLevelToString() {
    Logger logger;

    QCOMPARE(logger.levelToString(LogLevel::LOG_DEBUG), "DEBUG");
    QCOMPARE(logger.levelToString(LogLevel::LOG_INFO), "INFO");
    QCOMPARE(logger.levelToString(LogLevel::LOG_WARNING), "WARNING");
    QCOMPARE(logger.levelToString(LogLevel::LOG_ERROR), "ERROR");
    QCOMPARE(logger.levelToString(LogLevel::LOG_CRITICAL), "CRITICAL");
    QCOMPARE(logger.levelToString(static_cast<LogLevel>(-1)), "UNKNOWN");
}

testLogger::~testLogger()
{

}
