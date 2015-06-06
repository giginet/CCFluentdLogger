//
//  CCFLogger.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFluentdMacros.h"

#ifndef __CCFluentdLogger__Logger__
#define __CCFluentdLogger__Logger__

NS_LOGGER_BEGIN

struct Configuration {
    std::string host;
    int port;
};

class Logger {
public:
    static Logger * getInstance();
    static void purgeLogger();
    void setConfiguration(Configuration &config);
private:
    Configuration _configuration;
    static Logger * _instance;
};

NS_LOGGER_END

#endif /* defined(__CCFLogger__Logger__) */
