//
//  CCFConnector.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFluentdMacros.h"
#include "cocos2d.h"

#include "CCFLog.h"

#ifndef __CCFluentdLogger__CCFConnector__
#define __CCFluentdLogger__CCFConnector__

NS_LOGGER_BEGIN

class Connector :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    bool init(const char* host, int port);
    Connector();
    virtual ~Connector();
private:
    int _port;
    std::string _host;
    std::string getEndPoint(const char* tag);
public:
    static Connector* create(const char* host, int port);
    bool post(Log* log);
};

NS_LOGGER_END

#endif /* defined(__CCFluentdLogger__CCFConnector__) */
