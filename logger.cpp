// C++ program to implement a basic logging system.

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <logger.h>
#include <QDir>
#include <QDebug>
#include <QDirIterator>

const int kMaxNumberOfLogs = 150;

/**
 * \brief Constructor: Opens the log file in append mode(Never works :) )
**/
Logger::Logger(const std::string& filename)
{
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
    }
}

/**
 * \brief Constructor fo logger
 */
Logger::Logger()
{
    QDir dir;
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[75];

    dir.mkdir("logs");
    strftime(timestamp, sizeof(timestamp),
             "logs/%Y_%m_%d_%H_%M_%S.txt", timeinfo);
    //qDebug() << "f.fileName()";
    QString current_path = dir.currentPath();

    //Delete old loggs
    QDirIterator it(current_path + "/logs", QDirIterator::Subdirectories);
    QList<QString> files;
    while (it.hasNext()) {
        QFile f(it.next());
        files.append(f.fileName());
    }
    //2 is logs/. and logs/.. We don't need to delete it
    //- 1 is logs we create latter. When app will close, there will be 20 logs
    if(files.length() > kMaxNumberOfLogs + 2 - 1){
        for(int positionInList = 0; positionInList < files.length() - (kMaxNumberOfLogs + 2); positionInList++){
            QFile file (files[positionInList + 2]);
            file.remove();
        }
    }

    ofstream MyFile(timestamp);
    MyFile.close();

    logFile.open(timestamp, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
    }
}

/**
 * \brief Destructor: Closes the log file
**/

Logger::~Logger() { logFile.close(); }

/**
 * Logs a message with a given log level
**/
void Logger::log(LogLevel level, const std::string& message)
{
    // Get current timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S", timeinfo);

    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] "
             << levelToString(level) << ": " << message
             << std::endl;

    // Output to log file
    if (logFile.is_open()) {
        logFile << logEntry.str();
        logFile
            .flush(); // Ensure immediate write to file
    }
}

/**
 * \brief Converts log level to a string for output
**/
std::string Logger::levelToString(LogLevel level)
{
    switch (level) {
    case LOG_DEBUG:
        return "DEBUG";
    case LOG_INFO:
        return "INFO";
    case LOG_WARNING:
        return "WARNING";
    case LOG_ERROR:
        return "ERROR";
    case LOG_CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}
