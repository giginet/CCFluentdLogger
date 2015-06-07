//
//  CCFLogger.cpp
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFLogger.h"

NS_LOGGER_BEGIN

Logger* Logger::_instance = nullptr;

Logger* Logger::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Logger();
    }
    return _instance;
}

Logger::Logger()
: _connector(nullptr)
{
    
}

Logger::~Logger()
{
    CC_SAFE_RELEASE_NULL(_connector);
}

void Logger::purgeLogger()
{
    CC_SAFE_DELETE(_instance);
}

void Logger::setConfiguration(ccFluentdLogger::Configuration &config)
{
    _configuration = config;
}

bool Logger::postLog(const char *tag, json11::Json obj)
{
    // Currently, logs are posted in realtime.
    // TODO buffering
    Log *log = Log::create(tag, obj);
    _connector->post(log);
    return true;
}

NS_LOGGER_END