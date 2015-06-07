//
//  CCFLogger.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFluentdMacros.h"
#include "cocos2d.h"
#include "json11.hpp"

#include "CCFConnector.h"
#include "CCFBuffer.h"


#ifndef __CCFluentdLogger__Logger__
#define __CCFluentdLogger__Logger__

NS_LOGGER_BEGIN

struct Configuration {
    std::string host;
    int port;
    bool isBufferingEnabled;
};

class Logger {
public:
    Logger();
    virtual ~Logger();
    static Configuration getDefaultConfiguration();
    static Logger * getInstance();
    static void purgeLogger();
    void setConfiguration(Configuration &config);
    size_t postBuffer();
    size_t getBufferdCount();
    bool registerLog(const char* tag, json11::Json obj);
    bool registerLog(const char* tag, json11::Json obj, bool isBuffering);
private:
    Configuration _configuration;
    static Logger * _instance;
    Connector * _connector;
    Buffer * _buffer;
    void postLog(Log * log);
    Connector * getConnector();
};

NS_LOGGER_END

#endif /* defined(__CCFLogger__Logger__) */
