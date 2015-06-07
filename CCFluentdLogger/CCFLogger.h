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
CC_CONSTRUCTOR_ACCESS:
    Logger();
    virtual ~Logger();
public:
    /// Get default configuration struct.
    static Configuration getDefaultConfiguration();
    
    /// Get shared logger instance.
    static Logger * getInstance();
    
    /// Purge shared logger instance
    static void purgeLogger();
    
    /// Setter for configuration
    void setConfiguration(Configuration &config);
    
    /** Post log to server
     *  @param Strings for tagging a log
     *  @param Posting data in json11::Json::object
     *  @param Boolean value which indicates to enable buffering or not. 
     *         If not specified, Use config.isBufferingEnabled value.
     *  @return true if the log is posted
     */
    bool postLog(const char* tag, json11::Json obj);
    bool postLog(const char* tag, json11::Json obj, bool isBuffering);
    
    /** Post log to server
     *  @return numbers of sent logs.
     */
    size_t postBuffered();
    
    /// Get number of buffered logs.
    size_t getBufferdCount();
    
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
