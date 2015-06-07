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

Configuration Logger::getDefaultConfiguration()
{
    
    Configuration config;
    config.host = "http://127.0.0.1";
    config.port = 8888;
    config.isBufferingEnabled = false;
    return std::move(config);
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
    return this->registerLog(tag, obj, _configuration.isBufferingEnabled);
}

bool Logger::registerLog(const char *tag, json11::Json obj, bool isBuffering)
{
    Log *log = Log::create(tag, obj);
    _buffer->addBuffer(log);
    if (!isBuffering) {
        this->postBuffer();
    }
    return false;
}

size_t Logger::postBuffer()
{
    size_t num = _buffer->getLogs().size();
    for (auto log : _buffer->getLogs()) {
        this->postLog(log);
    }
    return num;
}

size_t Logger::getBufferdCount()
{
    return _buffer->getLogs().size();
}

Connector * Logger::getConnector()
{
    if (_connector == nullptr) {
        _connector = Connector::create(_configuration.host.c_str(), _configuration.port);
        _connector->retain();
    }
    return _connector;
}

void Logger::postLog(Log * log)
{
    auto connector = this->getConnector();
    connector->post(log,
                    [this, log](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
                        if (response->isSucceed()) {
                            cocos2d::log("Post succeed %s", log->dump().c_str());
                            _buffer->removeLog(log);
                        } else {
                            cocos2d::log("Post failed %s", log->dump().c_str());
                        }
                    });
}

NS_LOGGER_END