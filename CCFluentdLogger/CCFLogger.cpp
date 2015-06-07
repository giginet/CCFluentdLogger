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
, _buffer(nullptr)
{
    _buffer = Buffer::create();
    _buffer->retain();
}

Logger::~Logger()
{
    CC_SAFE_RELEASE_NULL(_connector);
    CC_SAFE_RELEASE_NULL(_buffer);
}

void Logger::purgeLogger()
{
    CC_SAFE_DELETE(_instance);
}

void Logger::setConfiguration(ccFluentdLogger::Configuration &config)
{
    _configuration = config;
    if (_connector) {
        _connector->setHost(config.host);
        _connector->setPort(config.port);
    }
}

bool Logger::registerLog(const char *tag, json11::Json obj)
{
    Log *log = Log::create(tag, obj);
    if (_configuration.isBufferingEnabled) {
        _buffer->addBuffer(log);
    } else {
        auto connector = this->getConnector();
        connector->post(log);
        return true;
    }
    return false;
}

size_t Logger::postBuffer()
{
    auto connector = this->getConnector();
    size_t num = _buffer->getLogs().size();
    for (auto log : _buffer->getLogs()) {
        connector->post(log);
    }
    _buffer->flush();
    return num;
}

Connector * Logger::getConnector()
{
    if (_connector == nullptr) {
        _connector = Connector::create(_configuration.host.c_str(), _configuration.port);
        _connector->retain();
    }
    return _connector;
}

NS_LOGGER_END