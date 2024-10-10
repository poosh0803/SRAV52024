enum loggerLevel {
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
};

void logVal(loggerLevel level, const char* message, double data);
void logVal(loggerLevel level, const char* message, double* data = nullptr);