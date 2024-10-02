// C++ program to implement a basic logging system.
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
};

class Logger {
public:

    // Constructor: Opens the log file in append mode
    Logger(const string& filename);
    Logger();

    // Destructor: Closes the log file
    ~Logger();

    // Logs a message with a given log level
    void log(LogLevel level, const string& message);


private:
    ofstream logFile; // File stream for the log file

    // Converts log level to a string for output
    string levelToString(LogLevel level);
};

extern Logger logger;
