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

void Logger::purgeLogger()
{
    CC_SAFE_DELETE(_instance);
}

void Logger::setConfiguration(ccFluentdLogger::Configuration &config)
{
    _configuration = config;
}

NS_LOGGER_END