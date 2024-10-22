#include "../include/robot-config.h"
#include "../include/logger.h"

void logVal(loggerLevel level, const char* message, double data) {
    logVal(level, message, &data);
}

void logVal(loggerLevel level, const char* message, double* data) 
{
    const char* levelStr;
    const char* levelMsg;

    switch (level) {
        case LOG_ERROR:
            levelStr = ERROR;
            levelMsg = "ERROR";
            break;
        case LOG_WARNING:
            levelStr = WARN;
            levelMsg = "WARN";
            break;
        case LOG_INFO:
            levelStr = INFO;
            levelMsg = "INFO";
            break;
        case LOG_DEBUG:
            levelStr = DEBUG;
            levelMsg = "DEBUG";
            break;
        default:
            levelStr = NORM;
            levelMsg = "MSG";
            break;
    }
    
    printf("%sT: %.2f ", levelStr, Brain.Timer.value());

    if (level == LOG_INFO) {
        printf("%s%s %s", levelMsg, NORM, message);
    } else {
        printf("%s %s", levelMsg, message);
    }

    if (data != nullptr) {
        printf("%.2f", *data);
    }

    printf("%s\n", NORM);
}